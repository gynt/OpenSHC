#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Entities/EntityTypeShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::DE::SHCDE::eSFX;
        using OpenSHC::Game::GameMode;
        using OpenSHC::Map::Entities::EntityType;
        using OpenSHC::Map::Entities::EntityTypeShort;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00531920
        BOOLEnum UnitsState::processEntityDamageToUnit(int unitID, int entityID, int tileDistance)
        {
            int tribeID = this->units[unitID].tribeID;
            int isSiegeEngine = 0;
            int isSiegeProjectile = 0;
            int usesFemaleDeathScream = 0;
            UnitTypeShort unitType = this->units[unitID].unitType;
            int unitTypeID = unitType;
            int shooterUnitID = DAT_EntityState::instance.entityArray[entityID].unitID_OR_seaGullID;
            if (unitID <= 0) {
                return FALSE;
            }
            if (shooterUnitID == unitID) {
                return FALSE;
            }
            EntityTypeShort entityType = DAT_EntityState::instance.entityArray[entityID].entityType;
            if (entityType == OpenSHC::Map::Entities::ET_FIRE) {
                return FALSE;
            }
            if (entityType == OpenSHC::Map::Entities::ET_FIRETHROWER) {
                return FALSE;
            }
            if (entityType == OpenSHC::Map::Entities::ET_DISEASE_CLOUD) {
                /* dead units are not affected */
                if (this->units[unitID].dying != 0) {
                    return FALSE;
                }
                int unitTile = DAT_UnitsState::instance.units[unitID].tile;
                /* some tile properties protect the unit */
                if ((DAT_TileMapState::instance.LogicLayer[unitTile] & 0x10000100U) != 0) {
                    return FALSE;
                }
                /* so do keeps, gatehouses and towers */
                if (DAT_TileMapState::instance.BuildingLayer[unitTile] != 0) {
                    switch (DAT_BuildingsState::instance.buildings[DAT_TileMapState::instance.BuildingLayer[unitTile]]
                            .buildingType) {
                    case OpenSHC::Map::Buildings::BT_MANORHOUSE:
                    case OpenSHC::Map::Buildings::BT_STONEKEEP:
                    case OpenSHC::Map::Buildings::BT_STRONGHOLD:
                    case OpenSHC::Map::Buildings::BT_KEEPFOUR:
                    case OpenSHC::Map::Buildings::BT_KEEPFIVE:
                    case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
                    case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
                    case OpenSHC::Map::Buildings::BT_WOODGATE1:
                    case OpenSHC::Map::Buildings::BT_TOWER1:
                    case OpenSHC::Map::Buildings::BT_TOWER2:
                    case OpenSHC::Map::Buildings::BT_TOWER3:
                    case OpenSHC::Map::Buildings::BT_TOWER4:
                    case OpenSHC::Map::Buildings::BT_TOWER5:
                        return FALSE;
                    }
                }
                /* unit types that are immune to disease */
                if (DAT_UnitPropertiesDefinedData::instance
                        .diseaseVulnerable[0][DAT_UnitsState::instance.units[unitID].unitType]
                    == 0) {
                    return FALSE;
                }
                int diseaseDamage;
                if (tileDistance == 0) {
                    diseaseDamage = 400;
                } else {
                    diseaseDamage = tileDistance == 1 ? 200 : 150;
                }
                int healerCount = DAT_GameState::instance.playerDataArray[this->units[unitID].owner].healerCount;
                if (healerCount >= 3) {
                    diseaseDamage = diseaseDamage * 40 / 100;
                } else if (healerCount == 2) {
                    diseaseDamage = diseaseDamage * 60 / 100;
                } else if (healerCount == 1) {
                    diseaseDamage = diseaseDamage * 80 / 100;
                }
                this->units[unitID].health -= diseaseDamage;
                if (this->units[unitID].health <= 0) {
                    this->units[unitID].health = 0;
                    this->units[unitID].dying = 1;
                    this->units[unitID].animationCycleNumber = 0;
                    this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_STONE_DEATH_02;
                    this->units[unitID].movementState = 1;
                }
                int healthPercentage
                    = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHealthPercentage,
                        DAT_DirectionAlgorithmState::ptr)(this->units[unitID].health, this->units[unitID].maxHealth);
                this->units[unitID].healthPercentage = (short)healthPercentage;
                this->units[unitID].healthbar = (short)healthPercentage / 10;
                return FALSE;
            }
            int unitHeight;
            if (unitType == OpenSHC::Map::Units::UT_S_TREBUCHET) {
                unitHeight = tileDistance == 0 ? 80 : 40;
                isSiegeEngine = 1;
            } else if (unitType == OpenSHC::Map::Units::UT_S_TOWER) {
                unitHeight = 80;
                isSiegeEngine = 1;
            } else if (unitType == OpenSHC::Map::Units::UT_S_CATAPULT) {
                unitHeight = 50;
                isSiegeEngine = 1;
            } else if (unitType == OpenSHC::Map::Units::UT_S_SHIELD) {
                unitHeight = 90;
                isSiegeEngine = 1;
            } else if (unitType == OpenSHC::Map::Units::UT_S_BATTERINGRAM) {
                unitHeight = 40;
                isSiegeEngine = 1;
            } else if (unitType == OpenSHC::Map::Units::UT_S_MANGONEL) {
                unitHeight = 70;
                isSiegeEngine = 1;
            } else {
                if (unitType == OpenSHC::Map::Units::UT_S_BALLISTA || unitType == OpenSHC::Map::Units::UT_S_FBALLISTA) {
                    isSiegeEngine = 1;
                }
                unitHeight = 42;
            }
            if (entityType == OpenSHC::Map::Entities::ET_TREBUCHET || entityType == OpenSHC::Map::Entities::ET_CATAPULT
                || entityType == OpenSHC::Map::Entities::ET_MANGONEL
                || entityType == OpenSHC::Map::Entities::ET_BALLISTA
                || entityType == OpenSHC::Map::Entities::ET_FIREBALLISTA) {
                isSiegeProjectile = 1;
            }
            int unitOwner = this->units[unitID].owner;
            short entityOwner = DAT_EntityState::instance.entityArray[entityID].owner;
            /* friendly fire only hurts with some siege projectiles, and never siege engines that cover troops */
            if (DAT_GameState::instance.mapAndTime.playerTeams[entityOwner]
                == DAT_GameState::instance.mapAndTime.playerTeams[unitOwner]) {
                if (isSiegeProjectile == 0) {
                    return FALSE;
                }
                if (DAT_EntityState::instance.entityArray[entityID].entityType == OpenSHC::Map::Entities::ET_BALLISTA) {
                    return FALSE;
                }
                if (DAT_EntityState::instance.entityArray[entityID].entityType == OpenSHC::Map::Entities::ET_MANGONEL
                    && DAT_GameSynchronyState::instance.currentPlayerFullIDArray[entityOwner] == -1) {
                    return FALSE;
                }
                if (DAT_EntityState::instance.entityArray[entityID].entityType
                    == OpenSHC::Map::Entities::ET_FIREBALLISTA) {
                    return FALSE;
                }
                if (unitType == OpenSHC::Map::Units::UT_S_SHIELD || unitType == OpenSHC::Map::Units::UT_S_TOWER
                    || unitType == OpenSHC::Map::Units::UT_S_BATTERINGRAM) {
                    return FALSE;
                }
            }
            if (this->units[unitID].dying != 0) {
                return FALSE;
            }
            int unitAltitude = this->units[unitID].terrainOrClimbHeight + this->units[unitID].buildingHeight;
            int entityHeight = DAT_EntityState::instance.entityArray[entityID].height;
            if (unitAltitude > entityHeight) {
                return FALSE;
            }
            if (unitAltitude + unitHeight < entityHeight) {
                return FALSE;
            }
            if (entityOwner != 0 && entityOwner != this->units[unitID].owner) {
                this->units[unitID].lastEncounteredEnemyPlayerID = entityOwner;
                this->units[unitID].lastAttackerUnitID
                    = DAT_EntityState::instance.entityArray[entityID].unitID_OR_seaGullID;
            }
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                && unitOwner == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXWeAreUnderAttack, DAT_SFXState::ptr)();
            }
            EntityTypeShort projectileType = DAT_EntityState::instance.entityArray[entityID].entityType;
            int damage;
            if (isSiegeProjectile == 0) {
                if (projectileType == OpenSHC::Map::Entities::ET_ARROW_AND_DEFAULT) {
                    damage = DAT_UnitPropertiesDefinedData::instance.ARROW_DAMAGE[this->units[unitID].unitType];
                    /* laddermen climbing a ladder take a quarter */
                    if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_E_LADDER
                        && this->units[unitID].state.generic == (UnitState)3) {
                        damage = damage / 4;
                    }
                } else if (projectileType == OpenSHC::Map::Entities::ET_SLINGER) {
                    damage = DAT_UnitPropertiesDefinedData::instance.STONE_DAMAGE[this->units[unitID].unitType];
                } else {
                    damage = DAT_UnitPropertiesDefinedData::instance.BOLT_DAMAGE[this->units[unitID].unitType];
                }
                damage = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::computeDamageFearFactorBonus, this)(
                    damage, DAT_EntityState::instance.entityArray[entityID].owner);
                if (isSiegeEngine) {
                    damage = damage / 2;
                }
                if (this->units[unitID].isAnimalOrAmbient == 0) {
                    DAT_GameCore::instance.battleLevelAccumulator += 50;
                }
            } else {
                if (projectileType == OpenSHC::Map::Entities::ET_COW_FLYING) {
                    if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_LORD) {
                        damage = 50;
                    } else {
                        damage = this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_SHIELD ? 50 : 500;
                    }
                } else if (projectileType == OpenSHC::Map::Entities::ET_MANGONEL) {
                    UnitTypeShort targetType = this->units[unitID].unitType;
                    if (targetType == OpenSHC::Map::Units::UT_LORD) {
                        damage = 50;
                    } else if (targetType == OpenSHC::Map::Units::UT_S_SHIELD) {
                        damage = 1500;
                    } else if (targetType == OpenSHC::Map::Units::UT_S_BALLISTA) {
                        damage = 1000;
                    } else if (targetType == OpenSHC::Map::Units::UT_S_FBALLISTA) {
                        damage = 1000;
                    } else if (targetType == OpenSHC::Map::Units::UT_S_MANGONEL) {
                        damage = 500;
                    } else if (targetType == OpenSHC::Map::Units::UT_S_CATAPULT) {
                        damage = 5000;
                    } else if (targetType == OpenSHC::Map::Units::UT_S_TREBUCHET) {
                        damage = 5000;
                    } else if (targetType == OpenSHC::Map::Units::UT_S_BATTERINGRAM) {
                        damage = 10000;
                    } else {
                        damage = targetType == OpenSHC::Map::Units::UT_S_TOWER ? 10000 : 30000;
                    }
                } else if (projectileType == OpenSHC::Map::Entities::ET_BALLISTA) {
                    UnitTypeShort targetType = this->units[unitID].unitType;
                    if (targetType == OpenSHC::Map::Units::UT_LORD) {
                        damage = 50;
                    } else if (targetType == OpenSHC::Map::Units::UT_S_SHIELD) {
                        damage = 500;
                    } else if (targetType == OpenSHC::Map::Units::UT_S_BALLISTA) {
                        damage = 2000;
                    } else if (targetType == OpenSHC::Map::Units::UT_S_MANGONEL) {
                        damage = 2000;
                    } else if (targetType == OpenSHC::Map::Units::UT_S_FBALLISTA) {
                        damage = 2000;
                    } else if (targetType == OpenSHC::Map::Units::UT_S_CATAPULT) {
                        damage = 2500;
                    } else if (targetType == OpenSHC::Map::Units::UT_S_TREBUCHET) {
                        damage = 4000;
                    } else if (targetType == OpenSHC::Map::Units::UT_S_BATTERINGRAM) {
                        damage = 20000;
                    } else {
                        damage = targetType == OpenSHC::Map::Units::UT_S_TOWER ? 20000 : 10000;
                    }
                    if (DAT_EntityState::instance.entityArray[entityID].isFireBallistaBolt != 0) {
                        damage = damage * 2 / 3;
                    }
                } else {
                    /* every other siege projectile: 50 against the lord, 30000 otherwise */
                    damage = this->units[unitID].unitType == OpenSHC::Map::Units::UT_LORD ? 50 : 30000;
                }
                DAT_GameCore::instance.battleLevelAccumulator += 50;
                if (damage > 20000) {
                    this->units[unitID].dying = 1;
                    if (tribeID > 0) {
                        DAT_TribesState::instance.tribes[tribeID].wildlifeAlarmTimer = 1;
                    }
                    this->units[unitID].animationCycleNumber = 0;
                    this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_STONE_DEATH_01;
                    this->units[unitID].movementState = 1;
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_SPLAT);
                    this->units[unitID].health = 0;
                    return TRUE;
                }
            }
            /* projectiles that come down steeply hurt less */
            if (DAT_EntityState::instance.entityArray[entityID].startingHeight
                < DAT_EntityState::instance.entityArray[entityID].targetZ - 30) {
                if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_E_ENGINEER
                    && this->units[unitID].resourceToDeposit != 0) {
                    damage = damage / 20;
                } else if (projectileType == OpenSHC::Map::Entities::ET_BALLISTA) {
                    damage = damage / 2;
                } else {
                    damage = damage / 3;
                }
            }
            this->units[unitID].health -= damage;
            if (this->units[unitID].health <= 0) {
                this->units[unitID].health = 0;
            }
            if (shooterUnitID != 0) {
                if (this->units[unitID].recentDamageTimer < 1000) {
                    this->units[unitID].recentDamageTimer += 200;
                }
                DAT_TribesState::instance.tribes[tribeID].recentAttackerIndex += 1;
                DAT_TribesState::instance.tribes[tribeID].countdown = 100;
                if (DAT_TribesState::instance.tribes[tribeID].recentAttackerIndex >= 10) {
                    DAT_TribesState::instance.tribes[tribeID].recentAttackerIndex = 0;
                }
                DAT_TribesState::instance.tribes[tribeID]
                    .recentAttackerUnitIDs[DAT_TribesState::instance.tribes[tribeID].recentAttackerIndex]
                    = shooterUnitID;
                DAT_TribesState::instance.tribes[tribeID]
                    .recentAttackerUIDs[DAT_TribesState::instance.tribes[tribeID].recentAttackerIndex]
                    = this->units[shooterUnitID].uid;
            }
            int unitHealth = this->units[unitID].health;
            int healthPercentage
                = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHealthPercentage,
                    DAT_DirectionAlgorithmState::ptr)(unitHealth, this->units[unitID].maxHealth);
            this->units[unitID].healthPercentage = (short)healthPercentage;
            this->units[unitID].healthbar = (short)healthPercentage / 10;
            if (unitTypeID == OpenSHC::Map::Units::UT_BREWER || unitTypeID == OpenSHC::Map::Units::UT_TANNER
                || unitTypeID == OpenSHC::Map::Units::UT_LADY || unitTypeID == OpenSHC::Map::Units::UT_MOTHER
                || (unitTypeID == OpenSHC::Map::Units::UT_CHILD && this->units[unitID].spriteID == 0x81)) {
                usesFemaleDeathScream = 1;
            }
            int shotBySlinger = 0;
            if (this->units[shooterUnitID].unitType == OpenSHC::Map::Units::UT_A_SLINGER) {
                shotBySlinger = 1;
            }
            if (unitHealth <= 0 && this->units[unitID].dying == 0) {
                this->units[unitID].dying = 1;
                if (tribeID > 0) {
                    DAT_TribesState::instance.tribes[tribeID].wildlifeAlarmTimer = 1;
                }
                this->units[unitID].animationCycleNumber = 0;
                entityType = DAT_EntityState::instance.entityArray[entityID].entityType;
                if (entityType == OpenSHC::Map::Entities::ET_COW_FLYING) {
                    this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_STONE_DEATH_01;
                } else {
                    this->units[unitID].state.generic = entityType == OpenSHC::Map::Entities::ET_SLINGER
                        ? OpenSHC::Map::Units::States::US_STONE_DEATH_01
                        : OpenSHC::Map::Units::States::US_DEATH_01;
                }
                this->units[unitID].movementState = 1;
                if (this->units[unitID].isAnimalOrAmbient != 0) {
                    if (shotBySlinger == 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_ARROW_HIT_ANIMAL);
                    } else if (shotBySlinger == 1) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_HIT_SLINGSTONE);
                    }
                    return TRUE;
                }
                switch (this->units[unitID].unitType) {
                case OpenSHC::Map::Units::UT_S_SHIELD:
                    if (this->units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300 != 0
                        && shotBySlinger == 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_DEATH_ARROW);
                        return TRUE;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_SIEGE_DIE);
                    return TRUE;
                case OpenSHC::Map::Units::UT_S_CATAPULT:
                case OpenSHC::Map::Units::UT_S_MANGONEL:
                case OpenSHC::Map::Units::UT_S_TOWER:
                case OpenSHC::Map::Units::UT_S_BATTERINGRAM:
                case OpenSHC::Map::Units::UT_S_BALLISTA:
                case OpenSHC::Map::Units::UT_S_FBALLISTA:
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_SIEGE_DIE);
                    return TRUE;
                case OpenSHC::Map::Units::UT_S_TREBUCHET:
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_TR_DIE);
                    break;
                }
                if (usesFemaleDeathScream != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_GIRL_DIE);
                    if (shotBySlinger == 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_ARROW_HIT);
                    } else if (shotBySlinger == 1) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_HIT_SLINGSTONE);
                    }
                } else if (shotBySlinger == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_DEATH_ARROW);
                } else if (shotBySlinger == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_DEATH_SLINGSTONE);
                }
                return TRUE;
            }
            if (this->units[unitID].isAnimalOrAmbient != 0) {
                if (shotBySlinger == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_ARROW_HIT_ANIMAL);
                } else if (shotBySlinger == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_HIT_SLINGSTONE);
                }
                return TRUE;
            }
            switch (this->units[unitID].unitType) {
            case OpenSHC::Map::Units::UT_S_SHIELD:
                if (this->units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300 > 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT2);
                }
                break;
            case OpenSHC::Map::Units::UT_S_CATAPULT:
            case OpenSHC::Map::Units::UT_S_TREBUCHET:
            case OpenSHC::Map::Units::UT_S_MANGONEL:
            case OpenSHC::Map::Units::UT_S_TOWER:
            case OpenSHC::Map::Units::UT_S_BATTERINGRAM:
            case OpenSHC::Map::Units::UT_S_BALLISTA:
            case OpenSHC::Map::Units::UT_S_FBALLISTA:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_WOOD_HIT);
                break;
            case OpenSHC::Map::Units::UT_LORD:
                break;
            default:
                if ((this->units[unitID].fixedRng & 7) == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT);
                } else if ((this->units[unitID].fixedRng & 7) == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT2);
                } else if ((this->units[unitID].fixedRng & 7) == 2) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT3);
                } else if ((this->units[unitID].fixedRng & 7) == 3) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT4);
                } else if ((this->units[unitID].fixedRng & 7) == 4) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT5);
                } else if ((this->units[unitID].fixedRng & 7) == 5) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT6);
                } else if ((this->units[unitID].fixedRng & 7) == 6) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT7);
                } else if ((this->units[unitID].fixedRng & 7) == 7) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT8);
                }
                break;
            }
            return TRUE;
        }

    }
}
}
