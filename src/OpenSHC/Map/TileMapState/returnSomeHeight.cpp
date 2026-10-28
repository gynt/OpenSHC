#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
    using OpenSHC::Map::LogicHelpers::L_ROCKY;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FF990
    uint TileMapState::getObstacleTopHeightAtTile(int tile, int param_2)
    {
        int extraHeight = 0;
        if ((this->LogicLayer[tile] & L_KEEP_NON_MANOR_HOUSE) != 0) {
            extraHeight = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                DAT_BuildingsState::ptr)(this->BuildingLayer[tile]);
        } else if ((this->LogicLayer[tile] & L_BUILDING) != 0) {
            int buildingID = this->BuildingLayer[tile];
            int buildingType = DAT_BuildingsState::instance.buildings[buildingID].buildingType;
            switch (buildingType) {
            case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
            case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
            case OpenSHC::Map::Buildings::BT_TOWER:
            case OpenSHC::Map::Buildings::BT_TOWER1:
            case OpenSHC::Map::Buildings::BT_TOWER2:
            case OpenSHC::Map::Buildings::BT_TOWER3:
            case OpenSHC::Map::Buildings::BT_TOWER4:
            case OpenSHC::Map::Buildings::BT_TOWER5:
                extraHeight = MACRO_CALL_MEMBER(
                                  OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                                  DAT_BuildingsState::ptr)(buildingID)
                    + 10;
                break;
            case OpenSHC::Map::Buildings::BT_HUNTERSHUT:
                if (param_2 != 0) {
                    extraHeight = 0;
                    break;
                }
            default:
                extraHeight = DAT_BuildingDefinedData::instance.BuildingHeights[buildingType];
                break;
            case OpenSHC::Map::Buildings::BT_MANORHOUSE:
            case OpenSHC::Map::Buildings::BT_STONEKEEP:
            case OpenSHC::Map::Buildings::BT_STRONGHOLD:
            case OpenSHC::Map::Buildings::BT_KEEPFOUR:
            case OpenSHC::Map::Buildings::BT_KEEPFIVE:
                extraHeight = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                    DAT_BuildingsState::ptr)(buildingID);
                break;
            }
        } else if ((this->LogicLayer[tile] & L_ROCKY) != 0 && (this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) == 0) {
            /*
              OrganismLayer holds tree ids below 2000 and rock ids biased by 2000; Ghidra rendered the
              rock lookup as an out-of-bounds index into trees[0x636].
            */
            int rockID = this->OrganismLayer[tile];
            if (rockID >= 2000) {
                rockID -= 2000;
                short rockType = DAT_LandscapeState::instance.rocks[rockID].type;
                if (rockType >= 0xd) {
                    extraHeight = 0x46;
                } else if (rockType >= 9) {
                    extraHeight = 0x32;
                }
            }
        }
        return this->HeightLayer[tile] + extraHeight;
    }

}
}