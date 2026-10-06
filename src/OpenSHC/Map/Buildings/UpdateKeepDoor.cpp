#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    using Map::Buildings::BuildingType;

    // FUNCTION: STRONGHOLDCRUSADER 0x00418B20
    void Buildings::UpdateKeepDoor()
    {
        short sVar1;
        BuildingTypeShort BVar2;
        int buildingID;
        int iVar3;
        bool bVar4;
        buildingID = DAT_CurrentBuildingID::instance;
        sVar1 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].quarryStockpileID;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].orientation
            = DAT_BuildingsState::instance.buildings[sVar1].orientation;
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation
            = (ushort)(DAT_BuildingsState::instance.buildings[buildingID].useOffsetGraphics == 0);
        iVar3 = DAT_TileMapState::instance.mapOrientation;
        BVar2 = DAT_BuildingsState::instance.buildings[sVar1].buildingType;
        if (BVar2 == Map::Buildings::BT_MANORHOUSE) {
            bVar4 = DAT_TileMapState::instance.mapOrientation == 0;
            DAT_BuildingsState::instance.buildings[buildingID].gfxOffset = 0x533;
            DAT_BuildingsState::instance.buildings[buildingID].spriteID = 0x52f;
            DAT_BuildingsState::instance.buildings[buildingID].unknownManorHouseOrStoneKeepRelated = 0;
            if ((bVar4) || (iVar3 == 4)) {
                DAT_BuildingsState::instance.buildings[buildingID].spriteOffetX = -2;
                DAT_BuildingsState::instance.buildings[buildingID].spriteOffetY = -0x2c;
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 0x20;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].spriteOffetX = 0;
                DAT_BuildingsState::instance.buildings[buildingID].spriteOffetY = -0x2a;
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 0x22;
            }
        } else if ((BVar2 == Map::Buildings::BT_STONEKEEP)
            || (BVar2 == Map::Buildings::BT_STRONGHOLD)) {
            bVar4 = DAT_TileMapState::instance.mapOrientation == 0;
            DAT_BuildingsState::instance.buildings[buildingID].gfxOffset = 0x52e;
            DAT_BuildingsState::instance.buildings[buildingID].spriteID = 0x52a;
            DAT_BuildingsState::instance.buildings[buildingID].unknownManorHouseOrStoneKeepRelated = 0;
            if ((bVar4) || (iVar3 == 4)) {
                DAT_BuildingsState::instance.buildings[buildingID].spriteOffetY = -0x3f;
                DAT_BuildingsState::instance.buildings[buildingID].spriteOffetX = 0;
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 0x1c;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].spriteOffetY = -0x40;
                DAT_BuildingsState::instance.buildings[buildingID].spriteOffetX = 0xe;
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 0x1e;
            }
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].spriteID
            != (int)DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState) {
            MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                buildingID);
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState
                = (short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteID;
        }
    }

}
}
