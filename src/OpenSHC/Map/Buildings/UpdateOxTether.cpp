#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // spriteID = base sprite + resources[4] * 4, compared with the signed short oldVisualActiveState (0x41CA36).
    // typeSpecificTimer and oxUnitID are signed shorts (jle 0x41CAEE, jg 0x41CB07); tickDivider spawns at >= 100
    // (jl 0x41CB28). The ox is spawned only when both entrance coordinates are non-zero (0x41CB68, 0x41CB78);
    // DAT_CurrentBuildingID is re-read after determineBuildingEntranceFromCampgroundArea and after spawnUnit.
    // FUNCTION: STRONGHOLDCRUSADER 0x0041CA00
    void Buildings::UpdateOxTether()
    {
        int buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        int sprite = DAT_BuildingDefinedData::instance
                         .Building_Sprite_ID_Array_1[(short)DAT_BuildingsState::instance.buildings[buildingID].buildingType]
            + DAT_BuildingsState::instance.buildings[buildingID].resources[4] * 4;
        DAT_BuildingsState::instance.buildings[buildingID].spriteID = sprite;
        if (sprite != DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                buildingID);
            buildingID = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState
                = (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID;
        }
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        buildingID = DAT_CurrentBuildingID::instance;
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].showOverlays = 1;
            int* counterPtr = &DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13;
            *counterPtr = *counterPtr + 1;
            if ((char)DAT_BuildingDefinedData::instance
                    .ownerFlagFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 / 2]
                <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 = 0;
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame14 = (char)DAT_BuildingDefinedData::instance
                .ownerFlagFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 / 2];
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame14 = 0;
        }
        short timer = DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer;
        if (timer > 0) {
            DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer = timer - 1;
            return;
        }
        short oxID = DAT_BuildingsState::instance.buildings[buildingID].oxUnitID;
        if (oxID <= 0) {
            if (DAT_BuildingsState::instance.buildings[buildingID].workerID[0] != 0) {
                int* tickPtr = &DAT_BuildingsState::instance.buildings[buildingID].tickDivider;
                *tickPtr = *tickPtr + 1;
                if (DAT_BuildingsState::instance.buildings[buildingID].tickDivider >= 100) {
                    DAT_BuildingsState::instance.buildings[buildingID].tickDivider = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setBuildingInitialEntryTileTry,
                        DAT_BuildingsState::ptr)(buildingID, 1);
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::determineBuildingEntranceFromCampgroundArea,
                        DAT_BuildingsState::ptr)(buildingID, 1, TRUE);
                    buildingID = DAT_CurrentBuildingID::instance;
                    short entryX = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryX;
                    if (entryX != 0) {
                        short entryY = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryY;
                        if (entryY != 0) {
                            int oxUnitID = MACRO_CALL_MEMBER(
                                OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                                DAT_BuildingsState::instance.buildings[buildingID].owner, 0, entryX * 8, entryY * 8,
                                DAT_BuildingsState::instance.buildings[buildingID].terrainHeight,
                                OpenSHC::Map::Units::UT_QUARRYOX);
                            buildingID = DAT_CurrentBuildingID::instance;
                            if (oxUnitID != 0) {
                                OpenSHC::Map::Units::Unit* ox = &DAT_UnitsState::instance.units[oxUnitID];
                                ox->workplaceBuildingOrTraderUID
                                    = DAT_BuildingsState::instance.buildings[buildingID].uid;
                                ox->targetX_2
                                    = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryX;
                                entryY = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryY;
                                DAT_BuildingsState::instance.buildings[buildingID].oxUnitID = (short)oxUnitID;
                                int oxUID = DAT_UnitsState::instance.units[oxUnitID].uid;
                                ox->targetY_2 = entryY;
                                ox->workplaceOrHomeBuildingID = (short)buildingID;
                                DAT_BuildingsState::instance.buildings[buildingID].oxUnitUID = oxUID;
                            }
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setBuildingInitialEntryTileTry,
                        DAT_BuildingsState::ptr)(buildingID, 0);
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::determineBuildingEntranceFromCampgroundArea,
                        DAT_BuildingsState::ptr)(buildingID, 1, FALSE);
                }
            }
        } else {
            if (DAT_BuildingsState::instance.buildings[buildingID].oxUnitUID != DAT_UnitsState::instance.units[oxID].uid) {
                DAT_BuildingsState::instance.buildings[buildingID].oxUnitID = 0;
                return;
            }
            if (DAT_UnitsState::instance.units[oxID].unitType == OpenSHC::Map::Units::UT_BURNING_ANIMAL_BIG) {
                DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer = 300;
            }
        }
    }

}
}