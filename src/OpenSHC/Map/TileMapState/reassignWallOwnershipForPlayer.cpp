#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F9000
    void TileMapState::reassignWallOwnershipForPlayer(int playerID, int newOwner)
    {
        for (int tile = 0; tile < 80400; tile += 6) {
            if ((this->LogicLayer[tile + 0] & L_WALL_OR_GATEHOUSE) != 0) {
                int building = this->BuildingLayer[tile + 0];
                if (building != 0 ? DAT_BuildingsState::instance.buildings[building].owner == newOwner
                                  : (this->WallOwnerLayer[tile + 0] & 7) + 1 == playerID) {
                    this->WallOwnerLayer[tile + 0] = this->WallOwnerLayer[tile + 0] & 0xf8 | (char)newOwner - 1U;
                }
            }
            if ((this->LogicLayer[tile + 1] & L_WALL_OR_GATEHOUSE) != 0) {
                int building = this->BuildingLayer[tile + 1];
                if (building != 0 ? DAT_BuildingsState::instance.buildings[building].owner == newOwner
                                  : (this->WallOwnerLayer[tile + 1] & 7) + 1 == playerID) {
                    this->WallOwnerLayer[tile + 1] = this->WallOwnerLayer[tile + 1] & 0xf8 | (char)newOwner - 1U;
                }
            }
            if ((this->LogicLayer[tile + 2] & L_WALL_OR_GATEHOUSE) != 0) {
                int building = this->BuildingLayer[tile + 2];
                if (building != 0 ? DAT_BuildingsState::instance.buildings[building].owner == newOwner
                                  : (this->WallOwnerLayer[tile + 2] & 7) + 1 == playerID) {
                    this->WallOwnerLayer[tile + 2] = this->WallOwnerLayer[tile + 2] & 0xf8 | (char)newOwner - 1U;
                }
            }
            if ((this->LogicLayer[tile + 3] & L_WALL_OR_GATEHOUSE) != 0) {
                int building = this->BuildingLayer[tile + 3];
                if (building != 0 ? DAT_BuildingsState::instance.buildings[building].owner == newOwner
                                  : (this->WallOwnerLayer[tile + 3] & 7) + 1 == playerID) {
                    this->WallOwnerLayer[tile + 3] = this->WallOwnerLayer[tile + 3] & 0xf8 | (char)newOwner - 1U;
                }
            }
            if ((this->LogicLayer[tile + 4] & L_WALL_OR_GATEHOUSE) != 0) {
                int building = this->BuildingLayer[tile + 4];
                if (building != 0 ? DAT_BuildingsState::instance.buildings[building].owner == newOwner
                                  : (this->WallOwnerLayer[tile + 4] & 7) + 1 == playerID) {
                    this->WallOwnerLayer[tile + 4] = this->WallOwnerLayer[tile + 4] & 0xf8 | (char)newOwner - 1U;
                }
            }
            if ((this->LogicLayer[tile + 5] & L_WALL_OR_GATEHOUSE) != 0) {
                int building = this->BuildingLayer[tile + 5];
                if (building != 0 ? DAT_BuildingsState::instance.buildings[building].owner == newOwner
                                  : (this->WallOwnerLayer[tile + 5] & 7) + 1 == playerID) {
                    this->WallOwnerLayer[tile + 5] = this->WallOwnerLayer[tile + 5] & 0xf8 | (char)newOwner - 1U;
                }
            }
        }
    }

}
}
