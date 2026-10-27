#include "../EntityState.func.hpp"

#include "OpenSHC/Random/RNG.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        /* The loop index is the global DAT_CurrentEntityID (re-read after every call, as in the original). The dust
           cloud has two identical bodies for unitID == 2 and the rest (0x408912 / 0x4089d9 in the original). */
        // FUNCTION: STRONGHOLDCRUSADER 0x004087C0
        void EntityState::updateEntities()
        {
            if (DAT_GameState::instance.gameTicksLoadBalancer % 10 == 0) {
                this->nextFreeEntitySearchStart = 0x19;
            }
            int highestUsedIDPlusOne = 0;
            this->totalEntityCount = 0;
            for (DAT_CurrentEntityID::instance = 1; (int)DAT_CurrentEntityID::instance < (int)this->maxEntityCount;
                 DAT_CurrentEntityID::instance++) {
                if (this->entityArray[DAT_CurrentEntityID::instance].logicalState == 0) {
                    continue;
                }
                this->totalEntityCount++;
                highestUsedIDPlusOne = DAT_CurrentEntityID::instance + 1;
                switch (this->entityArray[DAT_CurrentEntityID::instance].logicalState) {
                case 1:
                    this->entityArray[DAT_CurrentEntityID::instance].logicalState = 2;
                    break;
                case 5:
                    this->entityArray[DAT_CurrentEntityID::instance].logicalState = 6;
                    break;
                case 4:
                    MACRO_CALL_MEMBER(EntityState_Func::activateProjectileEntity, this)(DAT_CurrentEntityID::instance);
                    break;
                case 7:
                    MACRO_CALL_MEMBER(EntityState_Func::tickEntityDecayCounter, this)(DAT_CurrentEntityID::instance);
                    continue;
                case 8:
                    MACRO_CALL_MEMBER(EntityState_Func::tickEntityDecayCounter, this)(DAT_CurrentEntityID::instance);
                    break;
                case 3:
                    MACRO_CALL_MEMBER(EntityState_Func::deleteEntity, this)(DAT_CurrentEntityID::instance);
                    continue;
                }
                if ((int)DAT_CurrentEntityID::instance
                    == this->entityArray[DAT_CurrentEntityID::instance].nextEntityOnThisTileByID) {
                    MACRO_CALL_MEMBER(EntityState_Func::deleteEntity, this)(DAT_CurrentEntityID::instance);
                    continue;
                }
                if (this->entityArray[DAT_CurrentEntityID::instance].animFrameTickCounter
                    >= this->entityArray[DAT_CurrentEntityID::instance].ticksPerAnimFrame) {
                    this->entityArray[DAT_CurrentEntityID::instance].animFrameCounter++;
                    this->entityArray[DAT_CurrentEntityID::instance].animFrameTickCounter = 0;
                }
                this->entityArray[DAT_CurrentEntityID::instance].animFrameTickCounter++;
                if (this->entityArray[DAT_CurrentEntityID::instance].logicalState != 6) {
                    switch (this->entityArray[DAT_CurrentEntityID::instance].entityType) {
                    case ET_FIRE:
                        break;
                    case ET_DUST_CLOUD:
                        if (this->entityArray[DAT_CurrentEntityID::instance].unitID != 2) {
                            if ((this->entityArray[DAT_CurrentEntityID::instance].animFrameCounter & 1) != 0) {
                                MACRO_CALL_MEMBER(EntityState_Func::unlinkEntityFromTile, this)(
                                    DAT_CurrentEntityID::instance);
                                this->entityArray[DAT_CurrentEntityID::instance].height++;
                                if (this->entityArray[DAT_CurrentEntityID::instance].moveDirOrDriftXOrLaunchPitch < 0) {
                                    if (this->entityArray[DAT_CurrentEntityID::instance].animFrameCounter
                                            % this->entityArray[DAT_CurrentEntityID::instance].moveDirOrDriftXOrLaunchPitch
                                        == 0) {
                                        this->entityArray[DAT_CurrentEntityID::instance].microX--;
                                    }
                                } else if (this->entityArray[DAT_CurrentEntityID::instance].animFrameCounter
                                        % this->entityArray[DAT_CurrentEntityID::instance].moveDirOrDriftXOrLaunchPitch
                                    == 0) {
                                    this->entityArray[DAT_CurrentEntityID::instance].microX++;
                                }
                                if (this->entityArray[DAT_CurrentEntityID::instance].launchSpeedOrDriftPeriodY < 0) {
                                    if (this->entityArray[DAT_CurrentEntityID::instance].animFrameCounter
                                            % this->entityArray[DAT_CurrentEntityID::instance].launchSpeedOrDriftPeriodY
                                        == 0) {
                                        this->entityArray[DAT_CurrentEntityID::instance].microY--;
                                    }
                                } else if (this->entityArray[DAT_CurrentEntityID::instance].animFrameCounter
                                        % this->entityArray[DAT_CurrentEntityID::instance].launchSpeedOrDriftPeriodY
                                    == 0) {
                                    this->entityArray[DAT_CurrentEntityID::instance].microY++;
                                }
                                MACRO_CALL_MEMBER(EntityState_Func::processEntityHitBuildingOrUnit, this)(
                                    DAT_CurrentEntityID::instance);
                                MACRO_CALL_MEMBER(EntityState_Func::calculateEntityDrawOffset, this)(
                                    DAT_CurrentEntityID::instance);
                            }
                        } else if ((this->entityArray[DAT_CurrentEntityID::instance].animFrameCounter & 1) != 0) {
                            MACRO_CALL_MEMBER(EntityState_Func::unlinkEntityFromTile, this)(
                                DAT_CurrentEntityID::instance);
                            this->entityArray[DAT_CurrentEntityID::instance].height++;
                            if (this->entityArray[DAT_CurrentEntityID::instance].moveDirOrDriftXOrLaunchPitch < 0) {
                                if (this->entityArray[DAT_CurrentEntityID::instance].animFrameCounter
                                        % this->entityArray[DAT_CurrentEntityID::instance].moveDirOrDriftXOrLaunchPitch
                                    == 0) {
                                    this->entityArray[DAT_CurrentEntityID::instance].microX--;
                                }
                            } else if (this->entityArray[DAT_CurrentEntityID::instance].animFrameCounter
                                    % this->entityArray[DAT_CurrentEntityID::instance].moveDirOrDriftXOrLaunchPitch
                                == 0) {
                                this->entityArray[DAT_CurrentEntityID::instance].microX++;
                            }
                            if (this->entityArray[DAT_CurrentEntityID::instance].launchSpeedOrDriftPeriodY < 0) {
                                if (this->entityArray[DAT_CurrentEntityID::instance].animFrameCounter
                                        % this->entityArray[DAT_CurrentEntityID::instance].launchSpeedOrDriftPeriodY
                                    == 0) {
                                    this->entityArray[DAT_CurrentEntityID::instance].microY--;
                                }
                            } else if (this->entityArray[DAT_CurrentEntityID::instance].animFrameCounter
                                    % this->entityArray[DAT_CurrentEntityID::instance].launchSpeedOrDriftPeriodY
                                == 0) {
                                this->entityArray[DAT_CurrentEntityID::instance].microY++;
                            }
                            MACRO_CALL_MEMBER(EntityState_Func::processEntityHitBuildingOrUnit, this)(
                                DAT_CurrentEntityID::instance);
                            MACRO_CALL_MEMBER(EntityState_Func::calculateEntityDrawOffset, this)(
                                DAT_CurrentEntityID::instance);
                        }
                        break;
                    case ET_EXPLOSION:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                        this->entityArray[DAT_CurrentEntityID::instance].height++;
                        break;
                    case ET_DISEASE_CLOUD:
                        this->entityArray[DAT_CurrentEntityID::instance].launchSpeedOrDriftPeriodY++;
                        if (this->entityArray[DAT_CurrentEntityID::instance].launchSpeedOrDriftPeriodY > 0x1e) {
                            MACRO_CALL_MEMBER(EntityState_Func::unlinkEntityFromTile, this)(
                                DAT_CurrentEntityID::instance);
                            if (this->entityArray[DAT_CurrentEntityID::instance].launchSpeedOrDriftPeriodY != 1000) {
                                this->entityArray[DAT_CurrentEntityID::instance].wanderCountdownOrPitchDegrees--;
                                if ((short)this->entityArray[DAT_CurrentEntityID::instance].wanderCountdownOrPitchDegrees <= 0) {
                                    this->entityArray[DAT_CurrentEntityID::instance].wanderCountdownOrPitchDegrees
                                        = (char)(((byte*)&SEC_RNG::instance.currentNumber2)[1] & 0x3f);
                                    this->entityArray[DAT_CurrentEntityID::instance].moveDirOrDriftXOrLaunchPitch
                                        = (char)SEC_RNG::instance.currentNumber2 >> 4 & 7;
                                    MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                                }
                            }
                            this->entityArray[DAT_CurrentEntityID::instance].launchSpeedOrDriftPeriodY = 0;
                            switch (this->entityArray[DAT_CurrentEntityID::instance].moveDirOrDriftXOrLaunchPitch) {
                            case 0:
                                this->entityArray[DAT_CurrentEntityID::instance].microY--;
                                break;
                            case 4:
                                this->entityArray[DAT_CurrentEntityID::instance].microY++;
                                break;
                            case 2:
                                this->entityArray[DAT_CurrentEntityID::instance].microX++;
                                break;
                            case 6:
                                this->entityArray[DAT_CurrentEntityID::instance].microX--;
                                break;
                            case 7:
                                this->entityArray[DAT_CurrentEntityID::instance].microX--;
                                this->entityArray[DAT_CurrentEntityID::instance].microY--;
                                break;
                            case 1:
                                this->entityArray[DAT_CurrentEntityID::instance].microX++;
                                this->entityArray[DAT_CurrentEntityID::instance].microY--;
                                break;
                            case 5:
                                this->entityArray[DAT_CurrentEntityID::instance].microX--;
                                this->entityArray[DAT_CurrentEntityID::instance].microY++;
                                break;
                            case 3:
                                this->entityArray[DAT_CurrentEntityID::instance].microX++;
                                this->entityArray[DAT_CurrentEntityID::instance].microY++;
                                break;
                            }
                            MACRO_CALL_MEMBER(EntityState_Func::processEntityHitBuildingOrUnit, this)(
                                DAT_CurrentEntityID::instance);
                            MACRO_CALL_MEMBER(EntityState_Func::calculateEntityDrawOffset, this)(
                                DAT_CurrentEntityID::instance);
                        }
                        this->entityArray[DAT_CurrentEntityID::instance].height
                            = DAT_TileMapState::instance
                                  .HeightLayer[this->entityArray[DAT_CurrentEntityID::instance].tile]
                            + 0x14;
                        break;
                    case ET_FLAG_1:
                    case ET_FLAG_4:
                    case ET_FLAG_2:
                    case ET_FLAG_3:
                    case ET_BRAZIER:
                    case ET_HEADS_ON_SPIKES:
                        MACRO_CALL_MEMBER(EntityState_Func::unlinkEntityFromTile, this)(DAT_CurrentEntityID::instance);
                        MACRO_CALL_MEMBER(EntityState_Func::processEntityHitBuildingOrUnit, this)(
                            DAT_CurrentEntityID::instance);
                        break;
                    default:
                        this->entityArray[DAT_CurrentEntityID::instance].screenDirectionIndex
                            = (short)this->entityArray[DAT_CurrentEntityID::instance].orientation - 0x3c;
                        this->entityArray[DAT_CurrentEntityID::instance].screenDirectionIndex
                            += -DAT_TileMapState::instance.mapOrientation * 2;
                        if (this->entityArray[DAT_CurrentEntityID::instance].screenDirectionIndex < 0) {
                            this->entityArray[DAT_CurrentEntityID::instance].screenDirectionIndex += 0x10;
                        }
                        if (*(float*)&this->entityArray[DAT_CurrentEntityID::instance].flightTime != 0
                            && this->entityArray[DAT_CurrentEntityID::instance].gmLookupValue != 0
                            && this->entityArray[DAT_CurrentEntityID::instance].burnCyclesOrImpactCountdown == 0) {
                            if (this->entityArray[DAT_CurrentEntityID::instance].gmLookupValue != 3) {
                                MACRO_CALL_MEMBER(EntityState_Func::spawnEntityEffect2, this)(
                                    this->entityArray[DAT_CurrentEntityID::instance].microX,
                                    this->entityArray[DAT_CurrentEntityID::instance].microY,
                                    this->entityArray[DAT_CurrentEntityID::instance].height, 5,
                                    this->entityArray[DAT_CurrentEntityID::instance].gmLookupValue);
                            } else {
                                MACRO_CALL_MEMBER(EntityState_Func::spawnEntityEffect1, this)(
                                    this->entityArray[DAT_CurrentEntityID::instance].microX,
                                    this->entityArray[DAT_CurrentEntityID::instance].microY,
                                    this->entityArray[DAT_CurrentEntityID::instance].height, 6,
                                    this->entityArray[DAT_CurrentEntityID::instance].gmID,
                                    this->entityArray[DAT_CurrentEntityID::instance].graphicType2);
                            }
                        }
                        if (this->entityArray[DAT_CurrentEntityID::instance].burnCyclesOrImpactCountdown == 0) {
                            MACRO_CALL_MEMBER(EntityState_Func::moveProjectileEntity, this)(
                                DAT_CurrentEntityID::instance);
                        }
                        break;
                    }
                }
                ((void(__cdecl*)())DAT_EntityDefinedData::instance
                        .EntityCallbacks[this->entityArray[DAT_CurrentEntityID::instance].entityType])();
                if (this->entityArray[DAT_CurrentEntityID::instance].entityType == ET_SEAGULL) {
                    MACRO_CALL_MEMBER(EntityState_Func::processSeaGulls, this)(
                        this->entityArray[DAT_CurrentEntityID::instance].unitID_OR_seaGullID);
                }
            }
            this->maxEntityCount = highestUsedIDPlusOne;
        }

    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
