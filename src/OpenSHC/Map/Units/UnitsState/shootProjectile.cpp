#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Entities::EntityType;
        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00532700
        void UnitsState::shootProjectile(
            int unitID, EntityType projectileType, int targetX, int targetY, int targetZUnk)
        {
            int offsetX = 0;
            int offsetY = 0;
            if (projectileType == OpenSHC::Map::Entities::ET_TREBUCHET) {
                if (DAT_UnitsState::instance.units[unitID].throwCowNext != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnEntity, DAT_EntityState::ptr)(
                        unitID, this->units[unitID].owner, this->units[unitID].ownerColorIndex,
                        this->units[unitID].microXPosition, this->units[unitID].microYPosition,
                        this->units[unitID].buildingHeight + 0x82 + this->units[unitID].terrainOrClimbHeight, targetX,
                        targetY, targetZUnk, OpenSHC::Map::Entities::ET_COW_FLYING, 0);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnEntity, DAT_EntityState::ptr)(
                        unitID, this->units[unitID].owner, this->units[unitID].ownerColorIndex,
                        this->units[unitID].microXPosition, this->units[unitID].microYPosition,
                        this->units[unitID].buildingHeight + 0x82 + this->units[unitID].terrainOrClimbHeight, targetX,
                        targetY, targetZUnk, OpenSHC::Map::Entities::ET_TREBUCHET, 0);
                }
            } else if (projectileType == OpenSHC::Map::Entities::ET_CATAPULT) {
                switch (this->units[unitID].facingDirection) {
                case 5:
                    offsetX = -4;
                    offsetY = 4;
                    break;
                case 7:
                    offsetX = -4;
                    offsetY = -4;
                    break;
                case 1:
                    offsetX = 4;
                    offsetY = -4;
                    break;
                case 3:
                    offsetX = 4;
                    offsetY = 4;
                    break;
                case 0:
                    offsetY = -7;
                    break;
                case 2:
                    offsetX = 7;
                    break;
                case 4:
                    offsetY = 7;
                    break;
                case 6:
                    offsetX = -7;
                    break;
                }
                if (DAT_UnitsState::instance.units[unitID].throwCowNext != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnEntity, DAT_EntityState::ptr)(
                        unitID, this->units[unitID].owner, this->units[unitID].ownerColorIndex,
                        this->units[unitID].microXPosition + offsetX, this->units[unitID].microYPosition + offsetY,
                        this->units[unitID].buildingHeight + 0x38 + this->units[unitID].terrainOrClimbHeight, targetX,
                        targetY, targetZUnk, OpenSHC::Map::Entities::ET_COW_FLYING, 0);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnEntity, DAT_EntityState::ptr)(
                        unitID, this->units[unitID].owner, this->units[unitID].ownerColorIndex,
                        this->units[unitID].microXPosition + offsetX, this->units[unitID].microYPosition + offsetY,
                        this->units[unitID].buildingHeight + 0x38 + this->units[unitID].terrainOrClimbHeight, targetX,
                        targetY, targetZUnk, OpenSHC::Map::Entities::ET_CATAPULT, 0);
                }
            } else if (projectileType == OpenSHC::Map::Entities::ET_MANGONEL) {
                switch (this->units[unitID].facingDirection) {
                case 5:
                    offsetX = -2;
                    offsetY = 2;
                    break;
                case 7:
                    offsetX = 1;
                    offsetY = -1;
                    break;
                case 1:
                    offsetX = 0;
                case 4:
                    offsetY = 0;
                    break;
                case 3:
                    offsetX = -1;
                    offsetY = 1;
                    break;
                case 0:
                    offsetY = -2;
                    break;
                case 2:
                case 6:
                    offsetX = 0;
                    break;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnEntity, DAT_EntityState::ptr)(unitID,
                    this->units[unitID].owner, this->units[unitID].ownerColorIndex,
                    this->units[unitID].microXPosition + offsetX, this->units[unitID].microYPosition + offsetY,
                    this->units[unitID].buildingHeight + 64 + this->units[unitID].terrainOrClimbHeight, targetX,
                    targetY, targetZUnk, OpenSHC::Map::Entities::ET_MANGONEL, 0);
            } else if (projectileType == OpenSHC::Map::Entities::ET_BALLISTA
                || projectileType == OpenSHC::Map::Entities::ET_FIREBALLISTA) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnEntity, DAT_EntityState::ptr)(unitID,
                    this->units[unitID].owner, this->units[unitID].ownerColorIndex, this->units[unitID].microXPosition,
                    this->units[unitID].microYPosition,
                    this->units[unitID].buildingHeight + 25 + this->units[unitID].terrainOrClimbHeight, targetX,
                    targetY, targetZUnk, projectileType, 0);
            } else if (projectileType != (EntityType)8 && projectileType != ~OpenSHC::Map::Entities::ET_UNKNOWN) {
                if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_A_HARCHER) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnEntity, DAT_EntityState::ptr)(
                        unitID, this->units[unitID].owner, this->units[unitID].ownerColorIndex,
                        this->units[unitID].microXPosition, this->units[unitID].microYPosition,
                        this->units[unitID].buildingHeight + 45 + this->units[unitID].terrainOrClimbHeight, targetX,
                        targetY, targetZUnk, projectileType, this->units[unitID].shootTargetedUnit);
                } else {
                    /* This limits the range of arrow type projectiles */
                    MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnEntity, DAT_EntityState::ptr)(
                        unitID, this->units[unitID].owner, this->units[unitID].ownerColorIndex,
                        this->units[unitID].microXPosition, this->units[unitID].microYPosition,
                        this->units[unitID].buildingHeight + 30 + this->units[unitID].terrainOrClimbHeight, targetX,
                        targetY, targetZUnk, projectileType, this->units[unitID].shootTargetedUnit);
                }
            } else {
                switch (this->units[unitID].facingDirection) {
                case 5:
                    offsetY = 4;
                    offsetX = -10;
                    break;
                case 6:
                    offsetX = -10;
                    break;
                case 7:
                    offsetY = -4;
                    offsetX = -10;
                    break;
                case 1:
                    offsetX = 10;
                    offsetY = -4;
                    break;
                case 0:
                    offsetY = -4;
                    break;
                case 3:
                    offsetX = 10;
                    offsetY = 4;
                    break;
                case 4:
                    offsetY = 4;
                    break;
                case 2:
                    offsetX = 10;
                    break;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnEntity, DAT_EntityState::ptr)(unitID,
                    this->units[unitID].owner, this->units[unitID].ownerColorIndex,
                    this->units[unitID].microXPosition + offsetX, this->units[unitID].microYPosition + offsetY,
                    this->units[unitID].buildingHeight + 12 + this->units[unitID].terrainOrClimbHeight, targetX,
                    targetY, targetZUnk, projectileType, 0);
            }
            int tribeID = this->units[unitID].tribeID;
            if (tribeID != 0) {
                DAT_TribesState::instance.tribes[tribeID].countdown2 = 500;
            }
        }

    }
}
}
