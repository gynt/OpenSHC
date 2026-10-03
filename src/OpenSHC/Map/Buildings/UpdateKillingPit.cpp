#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0041E650
    void Buildings::UpdateKillingPit()
    {
        short* psVar1;
        int iVar2;
        int buildingID;
        buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[buildingID].animationIncrement = 1;
        if ((DAT_TileMapState::instance
                    .BuildingLayer[DAT_BuildingsState::instance.buildings[buildingID].currentTilePositionAdjusted]
                == 0)
            || (DAT_TileMapState::instance
                    .BuildingLayer[DAT_BuildingsState::instance.buildings[buildingID].currentTilePositionAdjusted]
                != buildingID)) {
            DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(
                buildingID);
            buildingID = DAT_CurrentBuildingID::instance;
        }
        switch (DAT_BuildingsState::instance.buildings[buildingID].state) {
        case 0:
            DAT_BuildingsState::instance.buildings[buildingID].spriteID
                = (DAT_BuildingsState::instance.buildings[buildingID].fireRelatedRNG1 & 7U) + 9;
            DAT_BuildingsState::instance.buildings[buildingID].field117_0x11a = 0;
            DAT_BuildingsState::instance.buildings[buildingID].animationIndex = 0;
            if (DAT_BuildingsState::instance.buildings[buildingID].killingPitField != 0) {}
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                buildingID);
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField = 1;
            return;
        case 1:
            DAT_BuildingsState::instance.buildings[buildingID].spriteID
                = (DAT_BuildingsState::instance.buildings[buildingID].fireRelatedRNG1 & 7U) + 1;
            DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 1;
            iVar2 = DAT_BuildingDefinedData::instance
                        .field418_0xa5a4[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
            if (iVar2 == -1) {
                DAT_BuildingsState::instance.buildings[buildingID].state = 2;
                DAT_BuildingsState::instance.buildings[buildingID].field117_0x11a = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                    buildingID);
            }
        LAB_0041e704:
            DAT_BuildingsState::instance.buildings[buildingID].animationFrame = iVar2;
            if (iVar2 != 0) {
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame
                    = iVar2 + (DAT_BuildingsState::instance.buildings[buildingID].fireRelatedRNG1 & 7U) * 4;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                    buildingID);
            }
            break;
        case 2:
            DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 1;
            psVar1 = &DAT_BuildingsState::instance.buildings[buildingID].field117_0x11a;
            *psVar1 = *psVar1 + 1;
            if (1999 < DAT_BuildingsState::instance.buildings[buildingID].field117_0x11a) {
                DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(buildingID);
            }
            break;
        case -2:
            DAT_BuildingsState::instance.buildings[buildingID].spriteID
                = (DAT_BuildingsState::instance.buildings[buildingID].fireRelatedRNG1 & 7U) + 1;
            DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 1;
            iVar2 = DAT_BuildingDefinedData::instance
                        .field417_0xa53c[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
            if (iVar2 != -1)
                goto LAB_0041e704;
            DAT_BuildingsState::instance.buildings[buildingID].state = 0;
            break;
        case -1:
            DAT_BuildingsState::instance.buildings[buildingID].spriteID
                = (DAT_BuildingsState::instance.buildings[buildingID].fireRelatedRNG1 & 7U) + 1;
            DAT_BuildingsState::instance.buildings[buildingID].state = -2;
            DAT_BuildingsState::instance.buildings[buildingID].field117_0x11a = 0;
            DAT_BuildingsState::instance.buildings[buildingID].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[buildingID].animationFrame
                = (DAT_BuildingsState::instance.buildings[buildingID].fireRelatedRNG1 & 7U) * 4 + 4;
            DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                buildingID);
            return;
        default:
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
            buildingID);
    }

}
}
