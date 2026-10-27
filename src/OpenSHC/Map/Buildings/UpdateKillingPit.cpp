#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // The pit destroys itself when its BuildingLayer tile is 0 or holds another (signed short, movsx at 0x41E688)
    // building ID. Jump table at 0x41E850 for state -2..2 (other states do nothing). The frame tables are ints
    // with -1 as terminator; frame 0 keeps animationFrame = 0. State 2 destroys the pit at subAnimState1 >= 2000
    // (signed short, jl 0x41E835). State 0 re-reads DAT_CurrentBuildingID after updateBuildingGraphicsLayer.
    // FUNCTION: STRONGHOLDCRUSADER 0x0041E650
    void Buildings::UpdateKillingPit()
    {
        int buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[buildingID].animationIncrement = 1;
        short layerID = DAT_TileMapState::instance
                            .BuildingLayer[DAT_BuildingsState::instance.buildings[buildingID].currentTilePositionAdjusted];
        if (layerID == 0 || buildingID != layerID) {
            DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(
                buildingID);
            buildingID = DAT_CurrentBuildingID::instance;
        }
        int frame;
        OpenSHC::Map::Buildings::Building* pit = &DAT_BuildingsState::instance.buildings[buildingID];
        switch (DAT_BuildingsState::instance.buildings[buildingID].state) {
        case -2:
            pit->spriteID
                = (DAT_BuildingsState::instance.buildings[buildingID].randomSeed & 7) + 1;
            pit->renderAnimation = 1;
            frame = DAT_BuildingDefinedData::instance
                        .killingPitResetAnimFrames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
            if (frame == -1) {
                pit->state = 0;
                break;
            }
            pit->animationFrame = frame;
            if (frame != 0) {
                pit->animationFrame
                    = frame + (DAT_BuildingsState::instance.buildings[buildingID].randomSeed & 7) * 4;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                    buildingID);
                return;
            }
            break;
        case -1:
            pit->spriteID
                = (DAT_BuildingsState::instance.buildings[buildingID].randomSeed & 7) + 1;
            pit->state = -2;
            pit->subAnimState1 = 0;
            pit->animationIndex = 0;
            pit->animationFrame
                = (DAT_BuildingsState::instance.buildings[buildingID].randomSeed & 7) * 4 + 4;
            pit->renderAnimation = 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                buildingID);
            return;
        case 0:
            pit->spriteID
                = (DAT_BuildingsState::instance.buildings[buildingID].randomSeed & 7) + 9;
            pit->subAnimState1 = 0;
            pit->animationIndex = 0;
            if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 != 0) {
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                buildingID);
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].subAnimState2 = 1;
            return;
        case 1:
            pit->spriteID
                = (DAT_BuildingsState::instance.buildings[buildingID].randomSeed & 7) + 1;
            pit->renderAnimation = 1;
            frame = DAT_BuildingDefinedData::instance
                        .killingPitTriggerAnimFrames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
            if (frame == -1) {
                pit->state = 2;
                pit->subAnimState1 = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                    buildingID);
                return;
            }
            pit->animationFrame = frame;
            if (frame != 0) {
                pit->animationFrame
                    = frame + (DAT_BuildingsState::instance.buildings[buildingID].randomSeed & 7) * 4;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                    buildingID);
                return;
            }
            break;
        case 2:
            pit->renderAnimation = 1;
            DAT_BuildingsState::instance.buildings[buildingID].subAnimState1 += 1;
            if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState1 >= 2000) {
                DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding,
                    DAT_BuildingsState::ptr)(buildingID);
                return;
            }
            break;
        default:
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
            buildingID);
    }

}
}
