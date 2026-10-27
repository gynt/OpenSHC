#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // Only types < 5 or > 19 grow (jl 0x4F39B7 / jle 0x4F39BC); hit points must be >= max (signed 16-bit jl
    // 0x4F39DE). Stage >= 6 -> state 3; stage >= 4 -> lightningCounter > lightningPower (signed) sends the tree to
    // stage 5, otherwise stage 3 and a seedling via setupBabyTreeLocation (on this) / createTree (on the global
    // instance 0xF2CC38, like getValueFrom0UpTo3ForTreeTypeAndTreeStage). createTree's result is not checked.
    // FUNCTION: STRONGHOLDCRUSADER 0x004F3960
    void LandscapeState::updateTreeStage(uint treeID, uint rng)
    {
        if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
            if (DAT_GameCore::instance.isTimeHalted != FALSE) {
                return;
            }
            if (MACRO_CALL(OpenSHC::UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                    OpenSHC::UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO)
                != FALSE) {
                return;
            }
        }
        if ((this->trees[treeID].rng1 & 0x3f) != rng) {
            return;
        }
        int const treeType = this->trees[treeID].treeType;
        if (treeType >= 5 && treeType <= 19) {
            return;
        }
        if (this->trees[treeID].fellState != 0) {
            return;
        }
        if ((short)this->trees[treeID].hitPoints < (short)this->trees[treeID].maxHitPoints) {
            return;
        }
        if (this->treeGrowthEnabled == 0) {
            return;
        }
        if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
            return;
        }
        this->trees[treeID].stageTracker++;
        int const stage = this->trees[treeID].stage;
        if (this->trees[treeID].stageTracker < DAT_OrganismDefinedData::instance.TreeStageLevels[treeType][stage + 1]) {
            return;
        }
        this->trees[treeID].stage = stage + 1;
        MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::setTreeStageRelatedValues, this)(treeID, stage + 1);
        if (this->trees[treeID].stage >= 6) {
            this->trees[treeID].state = 3;
            return;
        }
        if (this->trees[treeID].stage < 4) {
            return;
        }
        DAT_GameState::instance.mapAndTime.lightningCounter++;
        if (DAT_GameState::instance.mapAndTime.lightningCounter > DAT_GameState::instance.mapAndTime.lightningPower) {
            DAT_GameState::instance.mapAndTime.lightningCounter = 0;
            this->trees[treeID].stage = 5;
            this->trees[treeID].stageTracker = DAT_OrganismDefinedData::instance.TreeStageLevels[this->trees[treeID].treeType][5];
            return;
        }
        this->trees[treeID].stageTracker = DAT_OrganismDefinedData::instance.TreeStageLevels[this->trees[treeID].treeType][3];
        this->trees[treeID].stage = 3;
        DAT_GameState::instance.mapAndTime.newOrganismsValue2++;
        if (MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::setupBabyTreeLocation, this)(
                treeID, this->trees[treeID].treeType, (short)this->trees[treeID].xPosition, (short)this->trees[treeID].yPosition)
            == 0) {
            return;
        }
        int const newTreeType = this->trees[treeID].treeType;
        undefined4 const size = MACRO_CALL_MEMBER(
            OpenSHC::Map::LandscapeState_Func::getValueFrom0UpTo3ForTreeTypeAndTreeStage, DAT_LandscapeState::ptr)(
            newTreeType, 0);
        int const newTreeID = MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::createTree, DAT_LandscapeState::ptr)(
            DAT_PathFindingState::instance.ALG_ResultX, DAT_PathFindingState::instance.ALG_ResultY,
            (TreeType)newTreeType, size, 0, 0, 0);
        int const tile = DAT_PathFindingState::instance.ALG_ResultTile;
        DAT_TileMapState::instance.LogicLayer[tile] |= 0x1000;
        DAT_TileMapState::instance.OrganismLayer[tile] = (short)newTreeID;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::applyTreeBrushToLogicalLayer, DAT_TileMapState::ptr)(
            newTreeID, 0);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
            DAT_PathFindingState::ptr)((short)this->trees[newTreeID].yPosition, this->trees[newTreeID].tile);
        DAT_GameState::instance.mapAndTime.newOrganisms++;
        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
    }

}
}
