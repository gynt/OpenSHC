#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // renderAnimation = (usesGfxOffsetLayer == 0) (sete at 0x418B55); map orientations 0 and 4 use the first
    // offset/frame set (je at 0x418B8E / 0x418B93 and 0x418C00 / 0x418C05).
    // FUNCTION: STRONGHOLDCRUSADER 0x00418B20
    void Buildings::UpdateKeepDoor()
    {
        int buildingID = DAT_CurrentBuildingID::instance;
        int keepBuildingID = (short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].linkedBuildingID;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].orientation
            = DAT_BuildingsState::instance.buildings[keepBuildingID].orientation;
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation
            = DAT_BuildingsState::instance.buildings[buildingID].usesGfxOffsetLayer == 0;
        OpenSHC::Map::Buildings::BuildingTypeShort keepType
            = DAT_BuildingsState::instance.buildings[keepBuildingID].buildingType;
        if (keepType == OpenSHC::Map::Buildings::BT_MANORHOUSE) {
            int mapOrientation = DAT_TileMapState::instance.mapOrientation;
            DAT_BuildingsState::instance.buildings[buildingID].gfxOffset = 0x533;
            DAT_BuildingsState::instance.buildings[buildingID].spriteID = 0x52f;
            DAT_BuildingsState::instance.buildings[buildingID].spriteFrameOffset = 0;
            if (mapOrientation == 0 || mapOrientation == 4) {
                DAT_BuildingsState::instance.buildings[buildingID].spriteOffetX = -2;
                DAT_BuildingsState::instance.buildings[buildingID].spriteOffetY = -0x2c;
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 0x20;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].spriteOffetX = 0;
                DAT_BuildingsState::instance.buildings[buildingID].spriteOffetY = -0x2a;
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 0x22;
            }
        } else if (keepType == OpenSHC::Map::Buildings::BT_STONEKEEP || keepType == OpenSHC::Map::Buildings::BT_STRONGHOLD) {
            int mapOrientation = DAT_TileMapState::instance.mapOrientation;
            DAT_BuildingsState::instance.buildings[buildingID].gfxOffset = 0x52e;
            DAT_BuildingsState::instance.buildings[buildingID].spriteID = 0x52a;
            DAT_BuildingsState::instance.buildings[buildingID].spriteFrameOffset = 0;
            if (mapOrientation == 0 || mapOrientation == 4) {
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
            != DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                buildingID);
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState
                = (short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteID;
        }
    }

}
}
