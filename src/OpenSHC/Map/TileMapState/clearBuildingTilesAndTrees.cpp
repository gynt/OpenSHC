#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    using namespace OpenSHC::Map::LogicHelpers; // L_* flags
    using OpenSHC::Map::Buildings::Building;

    // FUNCTION: STRONGHOLDCRUSADER 0x004FAAB0
    void TileMapState::clearBuildingTilesAndTrees(int buildingID, int surfaceArea)
    {
        for (int i = 0; i < surfaceArea; i++) {
            int tile = DAT_BuildingsState::instance.buildings[buildingID].tileRefs[i];
            if ((this->LogicLayer[tile] & L_FARM_FIELD_APPLE) != 0) {
                int treeID = this->OrganismLayer[tile];
                if (treeID != 0 && treeID < 2000) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::removeTree, DAT_LandscapeState::ptr)(treeID);
                }
            }
            this->LogicLayer[tile] = this->LogicLayer[tile]
                & ~(L_BUILDING | L_FARM_FIELD_WHEAT | L_FARM_FIELD_HOP | L_FARM_FIELD_APPLE | L_FARM_FIELD_DAIRY);
            this->DamageOrCropStageLayer[tile] = 0;
            this->BuildingLayer[tile] = 0;
            if (DAT_BuildingsState::instance.buildings[buildingID].leavesRubble == 0) {
                this->BuildingWasLayer[tile] = 0;
            }
            this->ChangedLayer[tile] = 2;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                DAT_PathFindingState::ptr)(
                (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile], tile);
        }
    }

}
}
