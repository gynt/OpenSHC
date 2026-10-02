#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using OpenSHC::Map::Entities::EntityType;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004087C0
        void EntityState::updateEntities()
        {
            word* pwVar1;
            short sVar2;
            int iVar3;
            short* psVar4;
            int local_4;
            short _gmLookupValue;
            if (DAT_GameState::instance.gameTicksLoadBalancer % 10 == 0) {
                this->every10Ticks = 25;
            }
            this->totalEntityCount = 0;
            DAT_CurrentEntityID::instance = 1;
            local_4 = 0;
            iVar3 = 0;
            if (1 < this->maxEntityCount) {
                do {
                    if (this->entityArray[DAT_CurrentEntityID::instance].logicalState == 0)
                        goto LAB_00408d6d;
                    this->totalEntityCount = this->totalEntityCount + 1;
                    local_4 = DAT_CurrentEntityID::instance + 1;
                    psVar4 = &this->entityArray[DAT_CurrentEntityID::instance].logicalState;
                    /*
                      Switch entity state
                     */
                    switch (*psVar4) {
                    case 1:
                        *psVar4 = 2;
                        break;
                    case 3:
                        goto switchD_0040884c_caseD_3;
                    case 4:
                        MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::activateProjectileEntity, this)(
                            DAT_CurrentEntityID::instance);
                        break;
                    case 5:
                        *psVar4 = 6;
                        break;
                    case 7:
                        MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::tickEntityDecayCounter, this)(
                            DAT_CurrentEntityID::instance);
                        goto LAB_00408d6d;
                    case 8:
                        MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::tickEntityDecayCounter, this)(
                            DAT_CurrentEntityID::instance);
                    }
                    if (DAT_CurrentEntityID::instance
                        == (int)this->entityArray[DAT_CurrentEntityID::instance].nextEntityOnThisTileByID) {
                    switchD_0040884c_caseD_3:
                        MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::deleteEntity, this)(
                            DAT_CurrentEntityID::instance);
                        goto LAB_00408d6d;
                    }
                    if (this->entityArray[DAT_CurrentEntityID::instance].unkOne_1
                        <= this->entityArray[DAT_CurrentEntityID::instance].field7_0x12) {
                        psVar4 = &this->entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated;
                        *psVar4 = *psVar4 + 1;
                        this->entityArray[DAT_CurrentEntityID::instance].field7_0x12 = 0;
                    }
                    psVar4 = &this->entityArray[DAT_CurrentEntityID::instance].field7_0x12;
                    *psVar4 = *psVar4 + 1;
                    if (this->entityArray[DAT_CurrentEntityID::instance].logicalState == 6)
                        goto switchD_0040890b_caseD_9;
                    /*
                      Switch entity type
                     */
                    switch (this->entityArray[DAT_CurrentEntityID::instance].entityType) {
                    case OpenSHC::Map::Entities::ET_FIRE:
                        break;
                    case OpenSHC::Map::Entities::ET_FLAG_1:
                    case OpenSHC::Map::Entities::ET_FLAG_4:
                    case OpenSHC::Map::Entities::ET_FLAG_2:
                    case OpenSHC::Map::Entities::ET_FLAG_3:
                    case OpenSHC::Map::Entities::ET_BRAZIER:
                    case OpenSHC::Map::Entities::ET_HEADS_ON_SPIKES:
                        MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::doSomethingWithOtherEntitiesOnTile,
                            this)(DAT_CurrentEntityID::instance);
                        MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::processEntityHitBuildingOrUnit,
                            this)(DAT_CurrentEntityID::instance);
                        break;
                        default:
                            this->entityArray[DAT_CurrentEntityID::instance].field12_0x1c
                            = (short)this->entityArray[DAT_CurrentEntityID::instance].orientation + -0x3c;
                        psVar4 = &this->entityArray[DAT_CurrentEntityID::instance].field12_0x1c;
                        *psVar4 = *psVar4 + (short)DAT_TileMapState::instance.mapOrientation * -2;
                        psVar4 = &this->entityArray[DAT_CurrentEntityID::instance].field12_0x1c;
                        if (this->entityArray[DAT_CurrentEntityID::instance].field12_0x1c < 0) {
                            *psVar4 = *psVar4 + 0x10;
                        }
                        if ((((float)this->entityArray[DAT_CurrentEntityID::instance].speedUnk != 0.0)
                                && (_gmLookupValue = this->entityArray[DAT_CurrentEntityID::instance].gmLookupValue,
                                    _gmLookupValue != 0))
                            && (this->entityArray[DAT_CurrentEntityID::instance].someCounter_OR_hitGround == 0)) {
                            if (_gmLookupValue == 3) {
                                MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnEntityEffect1, this)(
                                    this->entityArray[DAT_CurrentEntityID::instance].microX,
                                    this->entityArray[DAT_CurrentEntityID::instance].microY,
                                    (undefined4)((int)((int)this->entityArray[DAT_CurrentEntityID::instance].height)),
                                    6, (int)((int)(this->entityArray[DAT_CurrentEntityID::instance].gmID)),
                                    this->entityArray[DAT_CurrentEntityID::instance].graphicType2);
                            } else {
                                MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnEntityEffect2, this)(
                                    (int)this->entityArray[DAT_CurrentEntityID::instance].microX,
                                    (undefined4)((int)((int)this->entityArray[DAT_CurrentEntityID::instance].microY)),
                                    (undefined4)((int)((int)this->entityArray[DAT_CurrentEntityID::instance].height)),
                                    5, (int)((int)(_gmLookupValue)));
                            }
                        }
                        if (this->entityArray[DAT_CurrentEntityID::instance].someCounter_OR_hitGround == 0) {
                            MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::moveProjectileEntity, this)(
                                DAT_CurrentEntityID::instance);
                        }
                        break;
                    case OpenSHC::Map::Entities::ET_DUST_CLOUD:
                        if (this->entityArray[DAT_CurrentEntityID::instance].unitID == 2) {
                            if ((this->entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated & 1)
                                != 0) {
                                MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Entities::EntityState_Func::doSomethingWithOtherEntitiesOnTile, this)(
                                    DAT_CurrentEntityID::instance);
                                psVar4 = &this->entityArray[DAT_CurrentEntityID::instance].height;
                                *psVar4 = *psVar4 + 1;
                                iVar3 = (int)this->entityArray[DAT_CurrentEntityID::instance]
                                            .unknownAnimationFrameRelated;
                                sVar2 = this->entityArray[DAT_CurrentEntityID::instance].startingAngle;
                                if (sVar2 < 0) {
                                    if (iVar3 % (int)sVar2 == 0) {
                                        psVar4 = &this->entityArray[DAT_CurrentEntityID::instance].microX;
                                        *psVar4 = *psVar4 + -1;
                                    }
                                } else if (iVar3 % (int)sVar2 == 0) {
                                    psVar4 = &this->entityArray[DAT_CurrentEntityID::instance].microX;
                                    *psVar4 = *psVar4 + 1;
                                }
                                sVar2 = this->entityArray[DAT_CurrentEntityID::instance].velocityUnk;
                                iVar3 = (int)this->entityArray[DAT_CurrentEntityID::instance]
                                            .unknownAnimationFrameRelated;
                                if (sVar2 < 0) {
                                    if (iVar3 % (int)sVar2 == 0) {
                                        psVar4 = &this->entityArray[DAT_CurrentEntityID::instance].microY;
                                        *psVar4 = *psVar4 + -1;
                                    }
                                } else if (iVar3 % (int)sVar2 == 0) {
                                    psVar4 = &this->entityArray[DAT_CurrentEntityID::instance].microY;
                                    *psVar4 = *psVar4 + 1;
                                }
                                MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Entities::EntityState_Func::processEntityHitBuildingOrUnit, this)(
                                    DAT_CurrentEntityID::instance);
                                MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::calculateEntityDrawOffset,
                                    this)(DAT_CurrentEntityID::instance);
                            }
                        } else if ((this->entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated & 1)
                            != 0) {
                            MACRO_CALL_MEMBER(
                                OpenSHC::Map::Entities::EntityState_Func::doSomethingWithOtherEntitiesOnTile, this)(
                                DAT_CurrentEntityID::instance);
                            psVar4 = &this->entityArray[DAT_CurrentEntityID::instance].height;
                            *psVar4 = *psVar4 + 1;
                            sVar2 = this->entityArray[DAT_CurrentEntityID::instance].startingAngle;
                            iVar3 = (int)this->entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated;
                            if (sVar2 < 0) {
                                if (iVar3 % (int)sVar2 == 0) {
                                    psVar4 = &this->entityArray[DAT_CurrentEntityID::instance].microX;
                                    *psVar4 = *psVar4 + -1;
                                }
                            } else if (iVar3 % (int)sVar2 == 0) {
                                psVar4 = &this->entityArray[DAT_CurrentEntityID::instance].microX;
                                *psVar4 = *psVar4 + 1;
                            }
                            sVar2 = this->entityArray[DAT_CurrentEntityID::instance].velocityUnk;
                            iVar3 = (int)this->entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated;
                            if (sVar2 < 0) {
                                if (iVar3 % (int)sVar2 == 0) {
                                    psVar4 = &this->entityArray[DAT_CurrentEntityID::instance].microY;
                                    *psVar4 = *psVar4 + -1;
                                }
                            } else if (iVar3 % (int)sVar2 == 0) {
                                psVar4 = &this->entityArray[DAT_CurrentEntityID::instance].microY;
                                *psVar4 = *psVar4 + 1;
                            }
                            MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::processEntityHitBuildingOrUnit,
                                this)(DAT_CurrentEntityID::instance);
                            MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::calculateEntityDrawOffset,
                                this)(DAT_CurrentEntityID::instance);
                        }
                        break;
                    case OpenSHC::Map::Entities::ET_COW_POISON_CLOUD:
                        psVar4 = &this->entityArray[DAT_CurrentEntityID::instance].velocityUnk;
                        *psVar4 = *psVar4 + 1;
                        if (this->entityArray[DAT_CurrentEntityID::instance].velocityUnk < 0x1f)
                            goto LAB_00408c15;
                        MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::doSomethingWithOtherEntitiesOnTile,
                            this)(DAT_CurrentEntityID::instance);
                        if (this->entityArray[DAT_CurrentEntityID::instance].velocityUnk != 1000) {
                            pwVar1 = &this->entityArray[DAT_CurrentEntityID::instance].graphicRotationUnk;
                            *pwVar1 = *pwVar1 - 1;
                            if ((short)this->entityArray[DAT_CurrentEntityID::instance].graphicRotationUnk < 1) {
                                this->entityArray[DAT_CurrentEntityID::instance].graphicRotationUnk
                                    = (short)(char)((*((char*)&SEC_RNG::instance.currentNumber2 + 1)) & 0x3f);
                                this->entityArray[DAT_CurrentEntityID::instance].startingAngle
                                    = (byte)((char)SEC_RNG::instance.currentNumber2 >> 4) & 7;
                                MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                            }
                        }
                        this->entityArray[DAT_CurrentEntityID::instance].velocityUnk = 0;
                        switch (this->entityArray[DAT_CurrentEntityID::instance].startingAngle) {
                        case 0:
                            psVar4 = &this->entityArray[DAT_CurrentEntityID::instance].microY;
                            *psVar4 = *psVar4 + -1;
                            break;
                        case 1:
                            psVar4 = &this->entityArray[DAT_CurrentEntityID::instance].microX;
                            *psVar4 = *psVar4 + 1;
                            psVar4 = &this->entityArray[DAT_CurrentEntityID::instance].microY;
                            *psVar4 = *psVar4 + -1;
                            break;
                        case 2:
                            psVar4 = &this->entityArray[DAT_CurrentEntityID::instance].microX;
                            *psVar4 = *psVar4 + 1;
                            break;
                        case 3:
                            psVar4 = &this->entityArray[DAT_CurrentEntityID::instance].microX;
                            *psVar4 = *psVar4 + 1;
                            goto LAB_00408bf2;
                        case 4:
                            psVar4 = &this->entityArray[DAT_CurrentEntityID::instance].microY;
                            *psVar4 = *psVar4 + 1;
                            break;
                        case 5:
                            psVar4 = &this->entityArray[DAT_CurrentEntityID::instance].microX;
                            *psVar4 = *psVar4 + -1;
                        LAB_00408bf2:
                            psVar4 = &this->entityArray[DAT_CurrentEntityID::instance].microY;
                            *psVar4 = *psVar4 + 1;
                            break;
                        case 6:
                            psVar4 = &this->entityArray[DAT_CurrentEntityID::instance].microX;
                            *psVar4 = *psVar4 + -1;
                            break;
                        case 7:
                            psVar4 = &this->entityArray[DAT_CurrentEntityID::instance].microX;
                            *psVar4 = *psVar4 + -1;
                            psVar4 = &this->entityArray[DAT_CurrentEntityID::instance].microY;
                            *psVar4 = *psVar4 + -1;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::processEntityHitBuildingOrUnit,
                            this)(DAT_CurrentEntityID::instance);
                        MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::calculateEntityDrawOffset, this)(
                            DAT_CurrentEntityID::instance);
                    LAB_00408c15:
                        this->entityArray[DAT_CurrentEntityID::instance].height
                            = DAT_TileMapState::instance
                                  .HeightLayer[this->entityArray[DAT_CurrentEntityID::instance].tile]
                            + 0x14;
                        break;
                    case OpenSHC::Map::Entities::EntityTypeInt__ET_EXPLOSION:
                    case ((EntityType)0x28):
                    case ((EntityType)0x29):
                    case ((EntityType)0x2a):
                    case ((EntityType)0x2b):
                        psVar4 = &this->entityArray[DAT_CurrentEntityID::instance].height;
                        *psVar4 = *psVar4 + 1;
                    }
                switchD_0040890b_caseD_9:
                    ((void (*)())DAT_EntityDefinedData::instance
                            .EntityCallbacks[(short)this->entityArray[DAT_CurrentEntityID::instance].entityType])();
                    if (this->entityArray[DAT_CurrentEntityID::instance].entityType
                        == OpenSHC::Map::Entities::ET_SEAGULLUnk) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::processSeaGulls, this)(
                            (int)this->entityArray[DAT_CurrentEntityID::instance].unitID_OR_seaGullID);
                    }
                LAB_00408d6d:
                    DAT_CurrentEntityID::instance = DAT_CurrentEntityID::instance + 1;
                    iVar3 = local_4;
                } while ((int)DAT_CurrentEntityID::instance < this->maxEntityCount);
            }
            this->maxEntityCount = iVar3;
        }

    }
}
}
