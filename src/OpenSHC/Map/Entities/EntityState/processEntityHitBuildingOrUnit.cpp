#include "../EntityState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

#include <stdlib.h>

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using OpenSHC::DE::SHCDE::FX_COW_SPLAT;
        using OpenSHC::DE::SHCDE::FX_FLIES;
        using OpenSHC::DE::SHCDE::FX_IGNITE_PITCH;
        using OpenSHC::DE::SHCDE::FX_LITTLE_PLOP;
        using OpenSHC::DE::SHCDE::FX_MED_PLOP;
        using OpenSHC::DE::SHCDE::FX_ROCK_HIT_GROUND;
        using OpenSHC::DE::SHCDE::FX_ROCK_HIT_WALL;
        using OpenSHC::DE::SHCDE::FX_ROCK_SPLASH;

        /* Returns 1 by default and 0 when the entity was removed or after the arrow / siege rock / cow impact
           branches (store at 0x408148); every path except the early returns links the entity into the tile entity
           list at 0x408150. */
        // FUNCTION: STRONGHOLDCRUSADER 0x00407190
        undefined4 EntityState::processEntityHitBuildingOrUnit(int entityID)
        {
            uint y;
            uint x;
            EntityTypeShort entityType;
            int tile;
            int result;
            int entityTile;
            int buildingID;
            int unitID;
            int direction;
            int neighbourTile;
            int ditchID;
            int obstacleHeight;
            short height;
            uint logic;
            int buildingType;

            this->entityArray[entityID].yPosition = this->entityArray[entityID].microY / 8;
            y = this->entityArray[entityID].yPosition;
            this->entityArray[entityID].xPosition = this->entityArray[entityID].microX / 8;
            x = this->entityArray[entityID].xPosition;
            entityType = this->entityArray[entityID].entityType;
            tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            result = 1;
            this->entityArray[entityID].tile = tile;
            if (entityType == ET_SEAGULL) {
                if (x <= 399 && y <= 399 && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] != 0
                    && (DAT_TileMapState::instance.LogicLayer[tile] & 0x30) == 0
                    && this->entityArray[entityID].height > 0) {
                    this->entityArray[entityID].nextEntityOnThisTileByID = DAT_TileMapState::instance.EntityLayer[tile];
                    DAT_TileMapState::instance.EntityLayer[tile] = (short)entityID;
                    return 1;
                }
                this->entityArray[entityID].tile = 0;
                return 0;
            }
            if (x > 399 || y > 399 || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == 0) {
                this->entityArray[entityID].logicalState = 3;
                return 0;
            }
            if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x30) != 0) {
                MACRO_CALL_MEMBER(EntityState_Func::markEntityDestroyed, this)(entityID);
                return 0;
            }

            if ((uint)(entityType - ET_FLAG_1) <= 5) {
                DAT_TileMapState::instance.MiscDisplayLayer[tile] |= 0x1000;
                if (this->entityArray[entityID].entityType == ET_BRAZIER
                    || this->entityArray[entityID].entityType == ET_HEADS_ON_SPIKES) {
                    entityTile = this->entityArray[entityID].tile;
                    if (DAT_TileMapState::instance.BuildingLayer[entityTile] != 0) {
                        switch (DAT_BuildingsState::instance.buildings[DAT_TileMapState::instance.BuildingLayer[entityTile]]
                                    .buildingType) {
                        case OpenSHC::Map::Buildings::BT_STONEKEEP:
                        case OpenSHC::Map::Buildings::BT_STRONGHOLD:
                        case OpenSHC::Map::Buildings::BT_KEEPFOUR:
                        case OpenSHC::Map::Buildings::BT_KEEPFIVE:
                        case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
                        case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
                        case OpenSHC::Map::Buildings::BT_TOWER1:
                        case OpenSHC::Map::Buildings::BT_TOWER2:
                        case OpenSHC::Map::Buildings::BT_TOWER3:
                        case OpenSHC::Map::Buildings::BT_TOWER4:
                        case OpenSHC::Map::Buildings::BT_TOWER5:
                            this->entityArray[entityID].height
                                = (short)MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile,
                                    DAT_TileMapState::ptr)(entityTile);
                            goto linkToTile;
                        }
                    } else if ((DAT_TileMapState::instance.LogicLayer[entityTile] & 0x100) != 0) {
                        if (DAT_TileMapState::instance.DamageOrCropStageLayer[entityTile] != 0) {
                            this->entityArray[entityID].height
                                = DAT_TileMapState::instance.HeightLayer[entityTile] + 0xf;
                        } else {
                            this->entityArray[entityID].height = DAT_TileMapState::instance.HeightLayer[entityTile];
                        }
                        goto linkToTile;
                    }
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        int stone;
                        int gold;
                        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingCost,
                            DAT_BuildingsState::ptr)(OpenSHC::Commands::M_MAPPER_BRAZIER, &stone, &gold);
                        DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .pendingResources[15]
                            += gold;
                    }
                    MACRO_CALL_MEMBER(EntityState_Func::markEntityDestroyed, this)(entityID);
                } else {
                    entityTile = this->entityArray[entityID].tile;
                    logic = DAT_TileMapState::instance.LogicLayer[entityTile];
                    if (logic != 0) {
                        if (DAT_TileMapState::instance.DamageOrCropStageLayer[entityTile] != 0) {
                            if ((logic & 0x400000) != 0) {
                                this->entityArray[entityID].height
                                    = DAT_TileMapState::instance.HeightLayer[entityTile] + 0x14;
                            } else if ((logic & 0x200) != 0) {
                                this->entityArray[entityID].height
                                    = DAT_TileMapState::instance.HeightLayer[entityTile] + 10;
                            } else {
                                this->entityArray[entityID].height = DAT_TileMapState::instance.HeightLayer[entityTile];
                            }
                        }
                    } else if (DAT_TileMapState::instance.BuildingLayer[entityTile] == 0) {
                        MACRO_CALL_MEMBER(EntityState_Func::markEntityDestroyed, this)(entityID);
                    }
                }
                goto linkToTile;
            }

            unitID = (short)DAT_TileMapState::instance.UnitLayer[tile];
            if (!(entityType == ET_ARROW_AND_DEFAULT && this->entityArray[entityID].variantOrLifetime == 2)) {
                if (entityType == ET_DISEASE_CLOUD || entityType == ET_TREBUCHET || entityType == ET_CATAPULT
                    || entityType == ET_MANGONEL || this->entityArray[entityID].launchSpeedOrDriftPeriodY > 0x50) {
                    while (unitID != 0) {
                        if (this->entityArray[entityID].logicalState == 2
                            && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::processEntityDamageToUnit,
                                   DAT_UnitsState::ptr)(unitID, entityID, 0)
                                != FALSE) {
                            if (this->entityArray[entityID].entityType != ET_COW_FLYING) {
                                MACRO_CALL_MEMBER(EntityState_Func::markEntityDestroyed, this)(entityID);
                                return 0;
                            }
                            this->entityArray[entityID].height = (short)MACRO_CALL_MEMBER(
                                OpenSHC::Map::TileMapState_Func::getObstacleTopHeightAtTile, DAT_TileMapState::ptr)(
                                tile, 0);
                            goto cowImpact;
                        }
                        unitID = (short)DAT_UnitsState::instance.units[unitID].nextUnitOnTheSameTile;
                    }
                }
                if (this->entityArray[entityID].entityType == ET_TREBUCHET
                    || this->entityArray[entityID].entityType == ET_CATAPULT
                    || this->entityArray[entityID].entityType == ET_MANGONEL
                    || this->entityArray[entityID].launchSpeedOrDriftPeriodY > 0x50) {
                    for (direction = 1; direction < 8; direction += 2) {
                        unitID = (short)DAT_TileMapState::instance.UnitLayer
                                     [DAT_TileMapState::instance
                                             .directionTranslationMatrix[this->entityArray[entityID].yPosition][direction]
                                         + tile];
                        while (unitID != 0) {
                            if (DAT_UnitsState::instance.units[unitID].occupiesNeighbourTiles != 0
                                && this->entityArray[entityID].logicalState == 2
                                && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::processEntityDamageToUnit,
                                       DAT_UnitsState::ptr)(unitID, entityID, 1)
                                    != FALSE) {
                                MACRO_CALL_MEMBER(EntityState_Func::markEntityDestroyed, this)(entityID);
                                return 0;
                            }
                            unitID = (short)DAT_UnitsState::instance.units[unitID].nextUnitOnTheSameTile;
                        }
                    }
                }
            }

            if (this->entityArray[entityID].entityType == ET_DISEASE_CLOUD) {
                int refHeight = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile,
                    DAT_TileMapState::ptr)(tile);
                for (direction = 0; direction < 8; direction++) {
                    neighbourTile = DAT_TileMapState::instance
                                        .directionTranslationMatrix[this->entityArray[entityID].yPosition][direction]
                        + tile;
                    for (unitID = (short)DAT_TileMapState::instance.UnitLayer[neighbourTile]; unitID != 0;
                         unitID = (short)DAT_UnitsState::instance.units[unitID].nextUnitOnTheSameTile) {
                        if (abs(refHeight
                                - (int)MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile,
                                    DAT_TileMapState::ptr)(neighbourTile))
                                < 0x78
                            && this->entityArray[entityID].logicalState == 2) {
                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::processEntityDamageToUnit,
                                DAT_UnitsState::ptr)(unitID, entityID, 1);
                        }
                    }
                }
                for (direction = 0; direction < 16; direction++) {
                    neighbourTile = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::computeTileAlongAxisOffset,
                        DAT_TileMapState::ptr)(tile, DAT_EntityDefinedData::instance.poisonCloudRing2Offsets[direction].xOffset,
                        DAT_EntityDefinedData::instance.poisonCloudRing2Offsets[direction].yOffset);
                    for (unitID = (short)DAT_TileMapState::instance.UnitLayer[neighbourTile]; unitID != 0;
                         unitID = (short)DAT_UnitsState::instance.units[unitID].nextUnitOnTheSameTile) {
                        if (abs(refHeight
                                - (int)MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile,
                                    DAT_TileMapState::ptr)(neighbourTile))
                                < 0x78
                            && this->entityArray[entityID].logicalState == 2) {
                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::processEntityDamageToUnit,
                                DAT_UnitsState::ptr)(unitID, entityID, 2);
                        }
                    }
                }
            }

            if (this->entityArray[entityID].entityType == ET_FIRE
                && (DAT_TileMapState::instance.LogicLayer[this->entityArray[entityID].tile] & 8) != 0) {
                ditchID = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getPitchDitchIDForTile,
                    DAT_TileMapState::ptr)(this->entityArray[entityID].tile);
                if (ditchID != 0 && DAT_TileMapState::instance.pitchDitches[ditchID].state == 1) {
                    MACRO_CALL(OpenSHC::Map::Entities_Func::SetPlaceOnFire)(this->entityArray[entityID].owner,
                        DAT_TileMapState::instance.pitchDitches[ditchID].x * 8,
                        DAT_TileMapState::instance.pitchDitches[ditchID].y * 8,
                        DAT_TileMapState::instance.HeightLayer[DAT_TileMapState::instance.pitchDitches[ditchID].tile], 3);
                    DAT_TileMapState::instance.pitchDitches[ditchID].state = 2;
                }
            }

            obstacleHeight = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getObstacleTopHeightAtTile,
                DAT_TileMapState::ptr)(tile, 0);
            buildingID = DAT_TileMapState::instance.BuildingLayer[tile];
            if (buildingID != 0) {
                buildingType = DAT_BuildingsState::instance.buildings[buildingID].buildingType;
                if ((buildingType == OpenSHC::Map::Buildings::BT_TOWER
                        || (uint)(buildingType - OpenSHC::Map::Buildings::BT_TOWER1) <= 4)
                    && (this->entityArray[entityID].rng_1 & 4) != 0) {
                    obstacleHeight += 0x14;
                }
            }
            height = this->entityArray[entityID].height;
            if (obstacleHeight <= height) {
                goto linkToTile;
            }

            entityType = this->entityArray[entityID].entityType;
            if (entityType == 0x20) {
                if (height < DAT_TileMapState::instance.DefaultHeightLayer[tile]) {
                    this->entityArray[entityID].burnCyclesOrImpactCountdown = 1;
                    if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x10000100) == 0
                        && DAT_TileMapState::instance.DefaultHeightLayer[tile]
                            < this->entityArray[entityID].startingHeight_2 + 0x32) {
                        MACRO_CALL(OpenSHC::Map::Entities_Func::IgniteFireAtMiniTile_Convenience)(
                            this->entityArray[entityID].owner, this->entityArray[entityID].microX,
                            this->entityArray[entityID].microY,
                            DAT_TileMapState::instance.HeightLayer[this->entityArray[entityID].tile] - 8, 2);
                        if ((DAT_TileMapState::instance.LogicLayer[tile] & 8) != 0) {
                            ditchID = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getPitchDitchIDForTile,
                                DAT_TileMapState::ptr)(tile);
                            if (ditchID != 0) {
                                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation,
                                    DAT_SFXState::ptr)(this->entityArray[entityID].xPosition,
                                    this->entityArray[entityID].yPosition, FX_IGNITE_PITCH);
                                MACRO_CALL(OpenSHC::Map::Entities_Func::SetPlaceOnFire)(this->entityArray[entityID].owner,
                                    DAT_TileMapState::instance.pitchDitches[ditchID].x * 8,
                                    DAT_TileMapState::instance.pitchDitches[ditchID].y * 8,
                                    DAT_TileMapState::instance
                                        .HeightLayer[DAT_TileMapState::instance.pitchDitches[ditchID].tile],
                                    3);
                                if (DAT_TileMapState::instance.pitchDitches[ditchID].state == 1) {
                                    DAT_TileMapState::instance.pitchDitches[ditchID].state = 2;
                                }
                            }
                        }
                    }
                }
                goto linkToTile;
            }
            if (entityType == ET_WALL_DEBRIS) {
                if (height <= DAT_TileMapState::instance.DefaultHeightLayer[tile]) {
                    this->entityArray[entityID].burnCyclesOrImpactCountdown = 1;
                    if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x40100001) != 0
                        && this->entityArray[entityID].unitID_OR_seaGullID == 0) {
                        MACRO_CALL_MEMBER(EntityState_Func::spawnEntity, this)(1, 0, 0,
                            this->entityArray[entityID].microX, this->entityArray[entityID].microY,
                            DAT_TileMapState::instance.HeightLayer[this->entityArray[entityID].tile] + 2,
                            this->entityArray[entityID].microX, this->entityArray[entityID].microY,
                            DAT_TileMapState::instance.HeightLayer[this->entityArray[entityID].tile] + 2,
                            (EntityType)0x1f, 0);
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition, FX_MED_PLOP);
                    }
                }
                goto linkToTile;
            }
            if (entityType == 8) {
                if (abs(height - this->entityArray[entityID].targetZ) < 0x14 || height <= 8) {
                    this->entityArray[entityID].burnCyclesOrImpactCountdown = 1;
                }
                goto linkToTile;
            }
            if (entityType == ET_ARROW_AND_DEFAULT || entityType == ET_CROSSBOWARROW || entityType == ET_BALLISTA
                || entityType == ET_SLINGER || entityType == ET_FIRETHROWER) {
                if (this->entityArray[entityID].variantOrLifetime == 2) {
                    for (direction = 0; direction < 8; direction++) {
                        neighbourTile = DAT_TileMapState::instance
                                            .directionTranslationMatrix[this->entityArray[entityID].yPosition][direction]
                            + tile;
                        if ((DAT_TileMapState::instance.LogicLayer[neighbourTile] & 8) != 0) {
                            ditchID = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getPitchDitchIDForTile,
                                DAT_TileMapState::ptr)(neighbourTile);
                            if (ditchID != 0) {
                                goto igniteDitch;
                            }
                        }
                    }
                }
                buildingID = DAT_TileMapState::instance.BuildingLayer[tile];
                if (this->entityArray[entityID].travelledDistance <= this->entityArray[entityID].lineOfSightDistance / 2) {
                    goto linkToTile;
                }
                logic = DAT_TileMapState::instance.LogicLayer[tile];
                if ((logic & 0x40100001) != 0) {
                    MACRO_CALL_MEMBER(EntityState_Func::spawnEntity, this)(1, 0, 0,
                        this->entityArray[entityID].microX, this->entityArray[entityID].microY,
                        DAT_TileMapState::instance.HeightLayer[this->entityArray[entityID].tile] + 2,
                        this->entityArray[entityID].microX, this->entityArray[entityID].microY,
                        DAT_TileMapState::instance.HeightLayer[this->entityArray[entityID].tile] + 2,
                        (EntityType)0x1f, 0);
                    this->entityArray[entityID].logicalState = 3;
                    result = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition, FX_LITTLE_PLOP);
                    goto linkToTile;
                }
                if ((logic & 0x10000100) == 0
                    && (buildingID == 0
                        || (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                                != OpenSHC::Map::Buildings::BT_STONEKEEP
                            && DAT_BuildingsState::instance.buildings[buildingID].buildingType
                                != OpenSHC::Map::Buildings::BT_STRONGHOLD
                            && DAT_BuildingsState::instance.buildings[buildingID].buildingType
                                != OpenSHC::Map::Buildings::BT_KEEPFOUR
                            && DAT_BuildingsState::instance.buildings[buildingID].buildingType
                                != OpenSHC::Map::Buildings::BT_KEEPFIVE))) {
                    if ((logic & 8) != 0) {
                        if (this->entityArray[entityID].variantOrLifetime == 2) {
                            ditchID = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getPitchDitchIDForTile,
                                DAT_TileMapState::ptr)(tile);
                            if (ditchID != 0) {
                            igniteDitch:
                                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation,
                                    DAT_SFXState::ptr)(this->entityArray[entityID].xPosition,
                                    this->entityArray[entityID].yPosition, FX_IGNITE_PITCH);
                                MACRO_CALL(OpenSHC::Map::Entities_Func::SetPlaceOnFire)(this->entityArray[entityID].owner,
                                    DAT_TileMapState::instance.pitchDitches[ditchID].x * 8,
                                    DAT_TileMapState::instance.pitchDitches[ditchID].y * 8,
                                    DAT_TileMapState::instance
                                        .HeightLayer[DAT_TileMapState::instance.pitchDitches[ditchID].tile],
                                    3);
                                if (DAT_TileMapState::instance.pitchDitches[ditchID].state == 1) {
                                    DAT_TileMapState::instance.pitchDitches[ditchID].state = 2;
                                }
                            }
                        }
                        this->entityArray[entityID].burnCyclesOrImpactCountdown = 1;
                    } else if (buildingID != 0) {
                        short shooterUnitID = this->entityArray[entityID].unitID_OR_seaGullID;
                        buildingType = DAT_BuildingsState::instance.buildings[buildingID].buildingType;
                        if ((buildingType >= OpenSHC::Map::Buildings::BT_TOWER1
                                && buildingType <= OpenSHC::Map::Buildings::BT_TOWER5)
                            || DAT_BuildingsState::instance.buildings[buildingID].currentHealth == 0
                            || (logic & 0xf000000) != 0) {
                            goto linkToTile;
                        }
                        if (DAT_UnitsState::instance.units[shooterUnitID].unitType
                            == OpenSHC::Map::Units::UT_S_FBALLISTA) {
                            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::processDamageToBuilding,
                                DAT_TileMapState::ptr)(tile, this->entityArray[entityID].xPosition,
                                this->entityArray[entityID].yPosition, 10, 0, this->entityArray[entityID].owner, FALSE,
                                shooterUnitID);
                            if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getNonFarmFieldBuildingHealthAtTileOr1000,
                                    DAT_TileMapState::ptr)(tile)
                                < 0x32) {
                                MACRO_CALL(OpenSHC::Map::Entities_Func::SetPlaceOnFire)(this->entityArray[entityID].owner,
                                    this->entityArray[entityID].xPosition * 8, this->entityArray[entityID].yPosition * 8,
                                    DAT_TileMapState::instance.HeightLayer[this->entityArray[entityID].tile], 3);
                                this->entityArray[entityID].burnCyclesOrImpactCountdown = 1;
                                goto clearResult;
                            }
                        } else if (this->entityArray[entityID].entityType == ET_BALLISTA) {
                            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::processDamageToBuilding,
                                DAT_TileMapState::ptr)(tile, this->entityArray[entityID].xPosition,
                                this->entityArray[entityID].yPosition, 2, 0, this->entityArray[entityID].owner, FALSE,
                                shooterUnitID);
                        } else {
                            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::processDamageToBuilding,
                                DAT_TileMapState::ptr)(tile, this->entityArray[entityID].xPosition,
                                this->entityArray[entityID].yPosition, 1, 0, this->entityArray[entityID].owner, FALSE,
                                shooterUnitID);
                        }
                        this->entityArray[entityID].burnCyclesOrImpactCountdown = 1;
                    } else {
                        this->entityArray[entityID].burnCyclesOrImpactCountdown = 0x28;
                    }
                } else {
                    if ((this->entityArray[entityID].pitchFrameIndex < 3
                            && this->entityArray[entityID].moveDirOrDriftXOrLaunchPitch < 0)
                        || this->entityArray[entityID].impactEffectDone != 0
                        || this->entityArray[entityID].losClearanceStepsLeft > 0) {
                        goto linkToTile;
                    }
                    MACRO_CALL_MEMBER(EntityState_Func::handleProjectileWallBounce, this)(entityID);
                }
            } else if (entityType == ET_TREBUCHET || entityType == ET_CATAPULT || entityType == ET_MANGONEL) {
                this->entityArray[entityID].burnCyclesOrImpactCountdown = 1;
                logic = DAT_TileMapState::instance.LogicLayer[tile];
                int damage = 10;
                int collateralDamage = 10;
                uint waterBits = logic & 0x40100001;
                if (waterBits != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition, FX_ROCK_SPLASH);
                }
                uint wallBit = logic & 0x100;
                if (wallBit == 0 && (logic & 0x10000400) == 0 && DAT_TileMapState::instance.BuildingLayer[tile] == 0) {
                    DAT_UnitsState::instance.units[this->entityArray[entityID].unitID_OR_seaGullID].missedShotCount++;
                    if ((logic & 0x4a5014b1) != 0) {
                        if (waterBits != 0) {
                            for (int count = 0; count < this->entityArray[entityID].rng_1 % 16 + 10; count++) {
                                MACRO_CALL_MEMBER(EntityState_Func::spawnEntity, this)(1, 0, 0,
                                    this->entityArray[entityID].microX, this->entityArray[entityID].microY,
                                    DAT_TileMapState::instance.HeightLayer[this->entityArray[entityID].tile] + 2,
                                    SEC_RNG::instance.currentNumber2 % 0x50 - 0x28 + this->entityArray[entityID].microX,
                                    (SEC_RNG::instance.currentNumber2 >> 8) % 0x50 - 0x28
                                        + this->entityArray[entityID].microY,
                                    8, ET_WALL_DEBRIS, 0);
                            }
                            MACRO_CALL_MEMBER(EntityState_Func::spawnEntity, this)(0, 0, 0,
                                this->entityArray[entityID].microX, this->entityArray[entityID].microY,
                                DAT_TileMapState::instance.HeightLayer[this->entityArray[entityID].tile] + 2,
                                this->entityArray[entityID].microX, this->entityArray[entityID].microY,
                                DAT_TileMapState::instance.HeightLayer[this->entityArray[entityID].tile] + 2,
                                (EntityType)0x1f, 0);
                        }
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition,
                            FX_ROCK_HIT_GROUND);
                        this->entityArray[entityID].burnCyclesOrImpactCountdown = 0x28;
                        for (int count = 0; count < this->entityArray[entityID].rng_1 % 8 + 5; count++) {
                            MACRO_CALL_MEMBER(EntityState_Func::spawnEntity, this)(2, 0, 0,
                                this->entityArray[entityID].microX, this->entityArray[entityID].microY,
                                DAT_TileMapState::instance.HeightLayer[this->entityArray[entityID].tile] + 2,
                                SEC_RNG::instance.currentNumber2 % 0x50 - 0x28 + this->entityArray[entityID].microX,
                                (SEC_RNG::instance.currentNumber2 >> 8) % 0x50 - 0x28
                                    + this->entityArray[entityID].microY,
                                8, ET_WALL_DEBRIS, 0);
                        }
                    }
                } else {
                    MACRO_CALL_MEMBER(EntityState_Func::spawnProjectileImpactDebris, this)(entityID);
                    entityType = this->entityArray[entityID].entityType;
                    if (entityType == ET_TREBUCHET) {
                        damage = 0x3c;
                        collateralDamage = 0x1e;
                    } else if (entityType == ET_CATAPULT) {
                        damage = 0x14;
                    } else if (entityType == ET_MANGONEL) {
                        damage = 5;
                        collateralDamage = 0;
                    }
                    buildingID = DAT_TileMapState::instance.BuildingLayer[tile];
                    if (buildingID != 0) {
                        if (DAT_GameState::instance.mapAndTime
                                .playerTeams[DAT_BuildingsState::instance.buildings[buildingID].owner]
                            == DAT_GameState::instance.mapAndTime.playerTeams[this->entityArray[entityID].owner]) {
                            damage = 0;
                            collateralDamage = 0;
                        }
                    } else if (wallBit != 0
                        && DAT_GameState::instance.mapAndTime.playerTeams[this->entityArray[entityID].owner]
                            == DAT_GameState::instance.mapAndTime
                                   .playerTeams[(DAT_TileMapState::instance.WallOwnerLayer[tile] & 7) + 1]) {
                        damage = 0;
                        collateralDamage = 0;
                    }
                    if (entityType == ET_MANGONEL) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::processDamageToBuilding,
                            DAT_TileMapState::ptr)(tile, this->entityArray[entityID].xPosition,
                            this->entityArray[entityID].yPosition, damage, 0, -this->entityArray[entityID].owner, FALSE,
                            this->entityArray[entityID].unitID_OR_seaGullID);
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::processEntityDamageToBuildingCollateral,
                            DAT_TileMapState::ptr)(tile, this->entityArray[entityID].xPosition,
                            this->entityArray[entityID].yPosition, collateralDamage, -this->entityArray[entityID].owner,
                            0, this->entityArray[entityID].unitID_OR_seaGullID);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::processDamageToBuilding,
                            DAT_TileMapState::ptr)(tile, this->entityArray[entityID].xPosition,
                            this->entityArray[entityID].yPosition, damage, 0, this->entityArray[entityID].owner, FALSE,
                            this->entityArray[entityID].unitID_OR_seaGullID);
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::processEntityDamageToBuildingCollateralThunk,
                            DAT_TileMapState::ptr)(tile, this->entityArray[entityID].xPosition,
                            this->entityArray[entityID].yPosition, collateralDamage, this->entityArray[entityID].owner,
                            0);
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition, FX_ROCK_HIT_WALL);
                }
            } else {
                if (entityType != ET_COW_FLYING) {
                    goto linkToTile;
                }
            cowImpact:
                if (this->entityArray[entityID].impactEffectDone == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition, FX_COW_SPLAT);
                    this->entityArray[entityID].impactEffectDone = 1;
                    if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x401000b1) != 0) {
                        this->entityArray[entityID].burnCyclesOrImpactCountdown = 1;
                    } else {
                        this->entityArray[entityID].burnCyclesOrImpactCountdown = 0x28;
                        DAT_GameCore::instance.battleLevelAccumulator += 500;
                        for (int count = SEC_RNG::instance.currentNumber2 % 5 - 2; count < 8; count++) {
                            MACRO_CALL_MEMBER(EntityState_Func::spawnEntity, DAT_EntityState::ptr)(0,
                                this->entityArray[entityID].owner,
                                0, this->entityArray[entityID].microX, this->entityArray[entityID].microY,
                                this->entityArray[entityID].height, 0, 0, 0, ET_DISEASE_CLOUD, 0);
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition, FX_FLIES);
                    }
                }
            }
        clearResult:
            result = 0;
        linkToTile:
            if (entityID != 0) {
                if (entityID < 0x19) {
                    this->entityArray[entityID].nextEntityOnThisTileByID = DAT_TileMapState::instance.EntityLayerLT25[tile];
                    DAT_TileMapState::instance.EntityLayerLT25[tile] = (byte)entityID;
                    return result;
                }
                this->entityArray[entityID].nextEntityOnThisTileByID = DAT_TileMapState::instance.EntityLayer[tile];
                DAT_TileMapState::instance.EntityLayer[tile] = (short)entityID;
            }
            return result;
        }

    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
