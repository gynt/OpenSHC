#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Buildings::BuildingType;

    // FUNCTION: STRONGHOLDCRUSADER 0x00418A60
    void Buildings::UpdateKeepDoorRight()
    {
        short sVar1;
        BuildingTypeShort BVar2;
        int buildingID;
        buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        sVar1 = DAT_BuildingsState::instance.buildings[buildingID].quarryStockpileID;
        DAT_BuildingsState::instance.buildings[buildingID].orientation
            = DAT_BuildingsState::instance.buildings[sVar1].orientation;
        BVar2 = DAT_BuildingsState::instance.buildings[sVar1].buildingType;
        if (BVar2 == OpenSHC::Map::Buildings::BT_MANORHOUSE) {
            DAT_BuildingsState::instance.buildings[buildingID].gfxOffset = 0x531;
            DAT_BuildingsState::instance.buildings[buildingID].spriteID = 0x528;
        } else {
            if ((BVar2 != OpenSHC::Map::Buildings::BT_STONEKEEP) && (BVar2 != OpenSHC::Map::Buildings::BT_STRONGHOLD))
                goto LAB_00418ae1;
            DAT_BuildingsState::instance.buildings[buildingID].gfxOffset = 0x52c;
            DAT_BuildingsState::instance.buildings[buildingID].spriteID = 0x526;
        }
        DAT_BuildingsState::instance.buildings[buildingID].unknownManorHouseOrStoneKeepRelated = 0;
    LAB_00418ae1:
        if (DAT_BuildingsState::instance.buildings[buildingID].spriteID
            != (int)DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                buildingID);
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState
                = (short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteID;
        }
    }

}
}
