#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // Works on `this` (esi = ecx at 0x404AEC). entityType and the slot index are compared signed (jle/jl/jge),
        // also against the undefined4 fields nextFreeEntitySearchStart (cmp edi, 0xbb8; jge 0x404B5D) and
        // maxEntityCount (cmp edi, [esi+4]; jl 0x404B90). The three switches follow the jump tables at 0x405038
        // (eviction-capable types), 0x4050A0 (evictable entity types) and 0x4050C0 (map-bounds checked types). Tile
        // coordinates are signed micro / 8 compared unsigned (ja). Random remainders are signed (movsx; idiv).
        // FUNCTION: STRONGHOLDCRUSADER 0x00404AE0
        uint EntityState::spawnEntity(int unitID, undefined4 playerID1, uint ownerColorUnk, int microX, int microY,
            int totalHeight, int targetX, int targetY, int targetZUnk, EntityType entityType, int param_11)
        {
            int entityID;
            int isFlamingVariant = 0;
            if (((entityType > 0x2b) && (entityType < 0x5b)) || (entityType > 0x5e)) {
                return 0;
            }
            if (entityType != -1) {
                if ((uint)(entityType - 0x28) <= 7) {
                    for (entityID = 1; entityID < 25; entityID++) {
                        if (this->entityArray[entityID].logicalState == 0) {
                            break;
                        }
                        if (entityID >= 24) {
                            return 0;
                        }
                    }
                }
                else {
                    for (entityID = this->nextFreeEntitySearchStart; entityID < 3000; entityID++) {
                        if (this->entityArray[entityID].logicalState == 0) {
                            break;
                        }
                        if (entityID >= 2999) {
                            switch (entityType) {
                            case ET_ARROW_AND_DEFAULT:
                            case ET_CATAPULT:
                            case ET_TREBUCHET:
                            case ET_MANGONEL:
                            case ET_CROSSBOWARROW:
                            case 8:
                            case ET_DISEASE_CLOUD:
                            case ET_COW_FLYING:
                            case 0x18:
                            case 0x19:
                            case ET_EXPLOSION:
                            case ET_SLINGER:
                            case ET_FIRETHROWER:
                            case ET_SLINGER_UNTARGETED:
                            case ET_FIRETHROWER_UNTARGETED:
                            case ET_FIREBALLISTA:
                            case 0x5b:
                            case 0x5c:
                            case 0x5d:
                            case 0x5e:
                                this->maxEntityCount = 3000;
                                for (entityID = 25; entityID < 3000; entityID++) {
                                    if (this->entityArray[entityID].logicalState == 0) {
                                        goto slotFound;
                                    }
                                    switch (this->entityArray[entityID].entityType) {
                                    case ET_FIRE:
                                    case ET_DUST_CLOUD:
                                    case ET_WALL_DEBRIS:
                                    case ET_PUFF_EFFECT:
                                    case 0x1f:
                                        MACRO_CALL_MEMBER(EntityState_Func::deleteEntity, this)(entityID);
                                        goto slotFound;
                                    }
                                }
                                break;
                            }
                            this->nextFreeEntitySearchStart = 2999;
                            return 0;
                        }
                    }
                    if (entityID >= (int)this->maxEntityCount) {
                        this->maxEntityCount = entityID + 1;
                    }
                    this->nextFreeEntitySearchStart = entityID;
                }
            }
            else {
                entityID = 0;
                entityType = (EntityType)8;
            }
        slotFound:
            this->entityArray[entityID].variantOrLifetime = 0;
            if (entityType == 0x5b) {
                isFlamingVariant = 1;
                this->entityArray[entityID].variantOrLifetime = 1;
                entityType = ET_ARROW_AND_DEFAULT;
            }
            else if (entityType == ET_FIREBALLISTA) {
                isFlamingVariant = 1;
                this->entityArray[entityID].isFireBallistaBolt = 1;
                entityType = ET_BALLISTA;
            }
            else {
                if ((entityType == ET_FIRETHROWER) || (entityType == ET_FIRETHROWER_UNTARGETED)) {
                    isFlamingVariant = 1;
                }
                if (entityType == 0x5c) {
                    isFlamingVariant = 1;
                    this->entityArray[entityID].variantOrLifetime = 1;
                    entityType = (EntityType)0x18;
                }
                else if (entityType == 0x5d) {
                    isFlamingVariant = 1;
                    this->entityArray[entityID].variantOrLifetime = 2;
                    entityType = ET_ARROW_AND_DEFAULT;
                }
                else if (entityType == 0x5e) {
                    isFlamingVariant = 1;
                    this->entityArray[entityID].variantOrLifetime = 2;
                    entityType = (EntityType)0x18;
                }
                else if (entityType == ET_WALL_DEBRIS) {
                    short randomValue = SEC_RNG::instance.currentNumber2;
                    targetX = targetX - 0xa0 + (randomValue % 0x50) * 4;
                    targetY = targetY - 0xa0 + ((randomValue >> 8) % 0x50) * 4;
                }
                else if (entityType == 0x20) {
                    short randomValue = SEC_RNG::instance.currentNumber2;
                    targetX = targetX - 0x18 + randomValue % 0x30;
                    targetY = targetY - 0x18 + (randomValue >> 8) % 0x30;
                }
            }
            switch (entityType) {
            case ET_ARROW_AND_DEFAULT:
            case ET_CATAPULT:
            case ET_TREBUCHET:
            case ET_MANGONEL:
            case ET_CROSSBOWARROW:
            case ET_BALLISTA:
            case ET_COW_FLYING:
            case 0x18:
            case 0x19:
            case ET_WALL_DEBRIS:
            case 0x20:
            case ET_SLINGER:
            case ET_FIRETHROWER:
            case ET_SLINGER_UNTARGETED:
            case ET_FIRETHROWER_UNTARGETED:
            case ET_FIREBALLISTA:
            case 0x5b:
            case 0x5c:
            case 0x5d:
            case 0x5e: {
                uint tileY = microY / 8;
                uint tileX = microX / 8;
                if ((tileX > 399) || (tileY > 399)
                    || (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[tileY * 400 + tileX] == 0)) {
                    return 0;
                }
                tileY = targetY / 8;
                tileX = targetX / 8;
                if ((tileX > 399) || (tileY > 399)
                    || (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[tileY * 400 + tileX] == 0)) {
                    return 0;
                }
            }
            }
            if (entityID < 25) {
                this->entityArray[entityID].uid = 0;
            }
            else {
                this->entityArray[entityID].uid = DAT_GameCore::instance.uniqueGameObjectTracker;
                DAT_GameCore::instance.uniqueGameObjectTracker++;
            }
            this->entityArray[entityID].unitID_OR_seaGullID = unitID;
            this->entityArray[entityID].targetX = targetX;
            this->entityArray[entityID].targetY = targetY;
            this->entityArray[entityID].targetZ = targetZUnk;
            this->entityArray[entityID].heightDifference = targetZUnk - totalHeight;
            this->entityArray[entityID].spawnTick = DAT_GameCore::instance.mapTimeInTicks;
            this->entityArray[entityID].unitID = param_11;
            this->entityArray[entityID].owner = playerID1;
            this->entityArray[entityID].microX = microX;
            this->entityArray[entityID].x_2 = microX;
            this->entityArray[entityID].logicalState = 1;
            this->entityArray[entityID].microY = microY;
            this->entityArray[entityID].y_2 = microY;
            this->entityArray[entityID].height = totalHeight;
            this->entityArray[entityID].startingHeight_2 = totalHeight;
            this->entityArray[entityID].height_2 = totalHeight;
            this->entityArray[entityID].startingHeight = totalHeight;
            this->entityArray[entityID].fadeLevel = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::somethingWithProjectileDistance,
                DAT_DirectionAlgorithmState::ptr)(microX, microY, targetX, targetY);
            this->entityArray[entityID].orientation = DAT_DirectionAlgorithmState::instance.orientation;
            this->entityArray[entityID].ownerColorIndex = 0;
            if ((entityType == ET_FLAG_1) || (entityType == ET_FLAG_4) || (entityType == ET_FLAG_2) || (entityType == ET_FLAG_3)) {
                this->entityArray[entityID].ownerColorIndex = ownerColorUnk;
            }
            MACRO_CALL_MEMBER(EntityState_Func::setProjectileEntityValues2, this)(entityID, entityType);
            if (this->entityArray[entityID].variantOrLifetime != 0) {
                this->entityArray[entityID].gmID = 0x91;
            }
            this->entityArray[entityID].animFrameTickCounter = 0;
            this->entityArray[entityID].animFrameCounter = 0;
            if (entityType == ET_DUST_CLOUD) {
                if (param_11 == 1) {
                    this->entityArray[entityID].animFrameCounter = 200;
                }
            }
            else if (entityType == 8) {
                this->entityArray[entityID].rng_1 = DAT_UnitsState::instance.units[unitID].fixedRng;
                goto initVelocities;
            }
            this->entityArray[entityID].rng_1 = SEC_RNG::instance.currentNumber2;
            if (entityID >= 25) {
                MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            }
            if (entityType == ET_SEAGULL) {
                this->entityArray[entityID].variantOrLifetime = SEC_RNG::instance.currentNumber2 % 100 + 0x78;
            }
            else if (entityType == 0x1f) {
                if (unitID != 0) {
                    this->entityArray[entityID].ticksPerAnimFrame = 2;
                }
            }
            else if (entityType == ET_HEADS_ON_SPIKES) {
                this->entityArray[entityID].variantOrLifetime = SEC_RNG::instance.currentNumber2 % 500 + 300;
                this->entityArray[entityID].rng_1 = ownerColorUnk;
            }
        initVelocities:
            MACRO_CALL_MEMBER(EntityState_Func::initializeProjectileVelocities, this)(
                entityID, microX, microY, totalHeight, targetX, targetY, targetZUnk);
            if (this->entityArray[entityID].entityType == 0x18) {
                this->entityArray[entityID].entityType = ET_ARROW_AND_DEFAULT;
            }
            if (this->entityArray[entityID].entityType == 0x19) {
                this->entityArray[entityID].entityType = ET_CROSSBOWARROW;
            }
            if (this->entityArray[entityID].entityType == ET_SLINGER_UNTARGETED) {
                this->entityArray[entityID].entityType = ET_SLINGER;
            }
            if (this->entityArray[entityID].entityType == ET_FIRETHROWER_UNTARGETED) {
                this->entityArray[entityID].entityType = ET_FIRETHROWER;
            }
            if (isFlamingVariant != 0) {
                this->entityArray[entityID].gmLookupValue = 1;
            }
            if (entityID != 0) {
                MACRO_CALL_MEMBER(EntityState_Func::processEntityHitBuildingOrUnit, this)(entityID);
                MACRO_CALL_MEMBER(EntityState_Func::calculateEntityDrawOffset, this)(entityID);
                uint savedCurrentEntityID = DAT_CurrentEntityID::instance;
                DAT_CurrentEntityID::instance = entityID;
                ((void(__cdecl*)())DAT_EntityDefinedData::instance
                        .EntityCallbacks[this->entityArray[entityID].entityType])();
                DAT_CurrentEntityID::instance = savedCurrentEntityID;
            }
            return entityID;
        }

    }
}
}
