#include "../TribesState.func.hpp"

#include <stdlib.h>

#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"

#include "OpenSHC/Globals/DAT_AttackInfoDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

#define GTAI_UNIT(i) DAT_UnitsState::instance.units[i]
#define GTAI_BUILDING(i) DAT_BuildingsState::instance.buildings[i]
#define GTAI_TILE_Y(t) DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[t]
#define GTAI_ROW(y) DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile
#define GTAI_DESTS DAT_PathFindingState::instance.searchQueue.destinationsArray
#define GTAI_GET_UNIT(index)                                                                                       \
    MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(tribeID, index)
#define GTAI_STOP(u)                                                                                               \
    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,        \
        DAT_UnitsState::ptr)(u)
#define GTAI_SET_DEST(u, x, y)                                                                                     \
    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(u, x, y, 0)
#define GTAI_ALL_ASSASSINS()                                                                                       \
    MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::isTribeAllAssassins, this)(tribeID)
#define GTAI_DESELECT(u)                                                                                           \
    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::deselectUnit, DAT_UnitsState::ptr)(u)
#define GTAI_CLEAR_SELECTION(owner, u)                                                                             \
    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::clearOrDeselectUnitFromSelection, DAT_UnitsState::ptr)( \
        owner, u, 0)
#define GTAI_AREA(tile) ((short)DAT_TileMapState::instance.PathConnectionLayer[tile])

        // Tribe fields are addressed from this + tribeID * 0x334 (ebp at 0x527C93), units through the global array.
        // Only the attack/shoot uid mismatch (0x527E19) and an off-map building entry (construct, tunneler) return
        // 0; every other path, including unhandled instructions (jump table 0x52A234), returns 1 (0x52A156).
        // The engineer type is compared with itself at 0x52996E (cmp cx, cx), as in machine code.
        // FUNCTION: STRONGHOLDCRUSADER 0x00527C80
        undefined4 TribesState::giveTribeAnInstruction(
            int tribeID, UnitInstructionType unitInstructionType, int id__x__tile, int unitUID__Y, int param_5)
        {
            int const size = this->tribes[tribeID].size;
            int ramOrHorse = 0;
            int ramCount = 0;
            int ramTried = 0;
            int const originalX = id__x__tile;
            int const originalY = unitUID__Y;
            this->tribes[tribeID].attackTargetUnitID = 0;
            this->tribes[tribeID].rabbitAttackOrdered = 0;
            switch (unitInstructionType) {
            case UIT_NO_INSTRUCTION_OR_MOVE: {
                int index = 0;
                if (size > 0) {
                    do {
                        int const unitID = GTAI_GET_UNIT(index);
                        ++index;
                        if (GTAI_UNIT(unitID).logicalState == ULS_NORMAL && GTAI_UNIT(unitID).dying == 0) {
                            GTAI_UNIT(unitID).pendingTargetingType = 3;
                            GTAI_UNIT(unitID).targetingType_OR_performanceStep = UIT_NO_INSTRUCTION_OR_MOVE;
                            GTAI_UNIT(unitID).throwCowNext = 0;
                        }
                    } while (index < this->tribes[tribeID].size);
                    return 1;
                }
                break;
            }
            case UIT_STOP: {
                int index = 0;
                this->tribes[tribeID].rallyMode = 0;
                this->tribes[tribeID].attackTargetUnitID = 0;
                if (size > 0) {
                    do {
                        int const unitID = GTAI_GET_UNIT(index);
                        ++index;
                        if (GTAI_UNIT(unitID).logicalState == ULS_NORMAL && GTAI_UNIT(unitID).dying == 0
                            && GTAI_UNIT(unitID).isAssassinHookClimbing == 0) {
                            GTAI_UNIT(unitID).pendingTargetingType = 3;
                            GTAI_UNIT(unitID).targetingType_OR_performanceStep = UIT_NO_INSTRUCTION_OR_MOVE;
                            GTAI_UNIT(unitID).throwCowNext = 0;
                            GTAI_STOP(unitID);
                            GTAI_UNIT(unitID).targetedBuildingTile = 0;
                            GTAI_UNIT(unitID).chaseTargetUnitID = 0;
                        }
                    } while (index < this->tribes[tribeID].size);
                    return 1;
                }
                break;
            }
            case UIT_UNIT_ATTACK_UNIT: {
                this->tribes[tribeID].rallyMode = 0;
                int index = 0;
                int meleeCount = 0;
                if (GTAI_UNIT(id__x__tile).uid != unitUID__Y) {
                    return 0;
                }
                if (size > 0) {
                    do {
                        int const unitID = GTAI_GET_UNIT(index);
                        ++index;
                        if (GTAI_UNIT(unitID).logicalState != ULS_NORMAL || GTAI_UNIT(unitID).dying != 0
                            || GTAI_UNIT(unitID).isAssassinHookClimbing != 0) {
                            continue;
                        }
                        GTAI_UNIT(unitID).chaseReturnX = 0;
                        GTAI_UNIT(unitID).chaseReturnY = 0;
                        switch (GTAI_UNIT(unitID).unitType) {
                        case UT_S_MANGONEL:
                        case UT_S_BALLISTA:
                        case UT_S_FBALLISTA:
                            GTAI_UNIT(unitID).targetingType_OR_performanceStep = UIT_UNIT_ATTACK_UNIT;
                            GTAI_UNIT(unitID).targetUnitId = (short)id__x__tile;
                            GTAI_UNIT(unitID)
                                .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                                = unitUID__Y;
                            GTAI_UNIT(unitID).idleInterruptedForAttack = 0;
                            GTAI_STOP(unitID);
                            GTAI_UNIT(unitID).shootBeforeStop = 10;
                        attackRabbitCheck:
                            if (GTAI_UNIT(id__x__tile).unitType == UT_RABBIT) {
                                this->tribes[tribeID].rabbitAttackOrdered = 1;
                            }
                            break;
                        case UT_E_ARCHER:
                        case UT_E_XBOW:
                        case UT_A_ARCHER:
                        case UT_A_SLINGER:
                        case UT_A_HARCHER:
                        case UT_A_FIRETHROWER:
                            if (GTAI_UNIT(unitID).state.generic == States::US_RALLYING) {
                                GTAI_UNIT(unitID).state.generic = States::US_MOVE_TO_DESTINATION;
                            }
                            GTAI_UNIT(unitID)
                                .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                                = unitUID__Y;
                            GTAI_UNIT(unitID).targetUID = unitUID__Y;
                            GTAI_UNIT(unitID).targetingType_OR_performanceStep = UIT_UNIT_ATTACK_UNIT;
                            GTAI_UNIT(unitID).targetUnitId = (short)id__x__tile;
                            GTAI_UNIT(unitID).shootTargetedUnit = (short)id__x__tile;
                            GTAI_UNIT(unitID).idleInterruptedForAttack = 0;
                            GTAI_STOP(unitID);
                            goto attackRabbitCheck;
                        case UT_TUNNELER:
                        case UT_E_SPEAR:
                        case UT_E_PIKE:
                        case UT_E_MACE:
                        case UT_E_SWORD:
                        case UT_E_KNIGHT:
                        case UT_E_MONK:
                        case UT_LORD:
                        case UT_A_SLAVE:
                        case UT_A_ASSASSIN:
                        case UT_A_SWORDSMAN:
                            if (GTAI_UNIT(id__x__tile).unitType != UT_ANTELOPESHDEER
                                && (param_5 != 1 || GTAI_UNIT(id__x__tile).state.generic != States::US_MELEE_ATTACK)) {
                                ++meleeCount;
                            }
                            break;
                        case UT_S_CATAPULT:
                        case UT_S_TREBUCHET:
                            GTAI_UNIT(unitID).pendingTargetingType = 5;
                            GTAI_UNIT(unitID).targetingType_OR_performanceStep = UIT_ATTACK_LAND;
                            GTAI_UNIT(unitID).attackAtTileX = GTAI_UNIT(id__x__tile).x;
                            GTAI_UNIT(unitID).attackAtTileY = GTAI_UNIT(id__x__tile).y;
                            GTAI_UNIT(unitID).unkAttackRelated = 0xb;
                            GTAI_UNIT(unitID).shootBeforeStop = 10;
                            break;
                        }
                    } while (index < this->tribes[tribeID].size);
                    if (meleeCount != 0) {
                        int const leaderID = this->tribes[tribeID].leaderUnitID;
                        int interceptX = GTAI_UNIT(leaderID).x;
                        int interceptY = GTAI_UNIT(leaderID).y;
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::predictUnitInterceptPosition, this)(
                            leaderID, id__x__tile, &interceptX, &interceptY);
                        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::pathPlanningForTribe,
                            DAT_PathFindingState::ptr)(tribeID, id__x__tile, interceptX, interceptY, meleeCount,
                            GTAI_AREA(GTAI_UNIT(leaderID).tile), GTAI_UNIT(leaderID).owner);
                        this->tribes[tribeID].attackTargetUnitID = (short)id__x__tile;
                        this->tribes[tribeID].attackTargetUnitUID = unitUID__Y;
                        this->tribes[tribeID].targetUnitTile = GTAI_UNIT(id__x__tile).tile;
                        index = 0;
                        this->tribes[tribeID].someTile2 = GTAI_UNIT(id__x__tile).savedDestinationX
                            + GTAI_ROW(GTAI_UNIT(id__x__tile).savedDestinationY);
                        int maxHalfPath = 0;
                        if (this->tribes[tribeID].size > 0) {
                            Navigation::PathHelper12* dest = GTAI_DESTS;
                            do {
                                int const unitID = GTAI_GET_UNIT(index);
                                ++index;
                                if (GTAI_UNIT(unitID).logicalState != ULS_NORMAL || GTAI_UNIT(unitID).dying != 0
                                    || GTAI_UNIT(unitID).isAssassinHookClimbing != 0) {
                                    continue;
                                }
                                UnitTypeShort const unitType = GTAI_UNIT(unitID).unitType;
                                switch (unitType) {
                                case UT_TUNNELER:
                                case UT_E_SPEAR:
                                case UT_E_PIKE:
                                case UT_E_MACE:
                                case UT_E_SWORD:
                                case UT_E_KNIGHT:
                                case UT_E_MONK:
                                case UT_LORD:
                                case UT_A_SLAVE:
                                case UT_A_ASSASSIN:
                                case UT_A_SWORDSMAN: {
                                    if (param_5 == 1 && GTAI_UNIT(unitID).state.generic == States::US_MELEE_ATTACK) {
                                        break;
                                    }
                                    int const tile = dest->tile1;
                                    if (tile == 0) {
                                        break;
                                    }
                                    short const tileY = GTAI_TILE_Y(tile);
                                    int const tileX = tile - GTAI_ROW(tileY);
                                    if (dest->tile2OrAHelper != 0) {
                                        GTAI_UNIT(unitID).targetingType_OR_performanceStep = UIT_UNIT_ATTACK_UNIT;
                                        GTAI_UNIT(unitID).targetUnitId = (short)id__x__tile;
                                        GTAI_UNIT(unitID)
                                            .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                                            = unitUID__Y;
                                    } else {
                                        GTAI_UNIT(unitID).targetingType_OR_performanceStep = UIT_NONE;
                                        if (unitType == UT_LORD) {
                                            break;
                                        }
                                    }
                                    short const state = GTAI_UNIT(unitID).state.generic;
                                    GTAI_UNIT(unitID).plannedDestinationX = (short)tileX;
                                    GTAI_UNIT(unitID).plannedDestinationY = tileY;
                                    GTAI_UNIT(unitID).targetedBuildingTile = 0;
                                    GTAI_UNIT(unitID).chaseTargetUnitID = 0;
                                    if (state == States::US_MELEE_ATTACK) {
                                        GTAI_UNIT(unitID).unknownMovementRelated_0x2d2
                                            = GTAI_UNIT(unitID).movementSpeed * -4;
                                    }
                                    GTAI_UNIT(unitID).state.generic = States::US_MOVE_TO_DESTINATION;
                                    if (GTAI_ALL_ASSASSINS() != FALSE) {
                                        DAT_PathFindingState::instance.pathForAssassins = 1;
                                    } else {
                                        DAT_PathFindingState::instance.skipLocalPathSearch = 1;
                                    }
                                    GTAI_SET_DEST(unitID, tileX, tileY);
                                    int const halfPath = GTAI_UNIT(unitID).totalSizeOfPathPlan / 2;
                                    GTAI_UNIT(unitID).lookForEnemy = -50;
                                    if (halfPath > maxHalfPath) {
                                        maxHalfPath = halfPath;
                                    }
                                    ++dest;
                                    DAT_PathFindingState::instance.skipLocalPathSearch = 0;
                                    break;
                                }
                                }
                            } while (index < this->tribes[tribeID].size);
                        }
                        int retargetDelay = maxHalfPath * 8;
                        if (retargetDelay <= 8) {
                            retargetDelay = 8;
                        }
                        this->tribes[tribeID].attackRetargetDelay = (short)retargetDelay;
                        return 1;
                    }
                }
                break;
            }
            case 0x20:
            case UIT_RANGED_ATTACK_UNIT: {
                int index = 0;
                int meleeCount = 0;
                if (GTAI_UNIT(id__x__tile).uid != unitUID__Y) {
                    return 0;
                }
                if (size > 0) {
                    do {
                        int const unitID = GTAI_GET_UNIT(index);
                        ++index;
                        if (GTAI_UNIT(unitID).logicalState != ULS_NORMAL || GTAI_UNIT(unitID).dying != 0
                            || GTAI_UNIT(unitID).isAssassinHookClimbing != 0) {
                            continue;
                        }
                        short const state = GTAI_UNIT(unitID).state.generic;
                        if (state == States::US_MELEE_ATTACK) {
                            continue;
                        }
                        switch (GTAI_UNIT(unitID).unitType) {
                        case UT_S_MANGONEL:
                        case UT_S_BALLISTA:
                        case UT_S_FBALLISTA:
                            if (unitInstructionType == UIT_RANGED_ATTACK_UNIT) {
                                break;
                            }
                            GTAI_UNIT(unitID).shootBeforeStop = 10;
                        // fall through
                        case UT_E_ARCHER:
                        case UT_E_XBOW:
                        case UT_E_ARCHER_DEBUG:
                        case UT_A_ARCHER:
                        case UT_A_SLINGER:
                        case UT_A_HARCHER:
                        case UT_A_FIRETHROWER:
                            if (state == States::US_RALLYING) {
                                GTAI_UNIT(unitID).state.generic = States::US_MOVE_TO_DESTINATION;
                            }
                            GTAI_UNIT(unitID).targetingType_OR_performanceStep = UIT_UNIT_ATTACK_UNIT;
                            GTAI_UNIT(unitID).targetUnitId = (short)id__x__tile;
                            GTAI_UNIT(unitID)
                                .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                                = unitUID__Y;
                            GTAI_UNIT(unitID).idleInterruptedForAttack = 0;
                            if (GTAI_UNIT(id__x__tile).unitType == UT_RABBIT) {
                                this->tribes[tribeID].rabbitAttackOrdered = 1;
                            }
                            if (GTAI_UNIT(unitID).chaseReturnX == 0) {
                                short const savedY = GTAI_UNIT(unitID).savedDestinationY;
                                GTAI_UNIT(unitID).chaseReturnX = GTAI_UNIT(unitID).savedDestinationX;
                                GTAI_UNIT(unitID).chaseReturnY = savedY;
                            }
                            GTAI_STOP(unitID);
                            break;
                        case UT_TUNNELER:
                        case UT_E_SPEAR:
                        case UT_E_PIKE:
                        case UT_E_MACE:
                        case UT_E_SWORD:
                        case UT_E_KNIGHT:
                        case UT_E_MONK:
                        case UT_LORD:
                        case UT_A_SLAVE:
                        case UT_A_ASSASSIN:
                        case UT_A_SWORDSMAN:
                            if (unitInstructionType != UIT_RANGED_ATTACK_UNIT) {
                                ++meleeCount;
                            }
                            break;
                        case UT_S_CATAPULT:
                        case UT_S_TREBUCHET:
                            if (unitInstructionType != UIT_RANGED_ATTACK_UNIT) {
                                short const chaseReturnX = GTAI_UNIT(unitID).chaseReturnX;
                                GTAI_UNIT(unitID).pendingTargetingType = 5;
                                GTAI_UNIT(unitID).targetingType_OR_performanceStep = UIT_ATTACK_LAND;
                                GTAI_UNIT(unitID).attackAtTileX = GTAI_UNIT(id__x__tile).x;
                                GTAI_UNIT(unitID).attackAtTileY = GTAI_UNIT(id__x__tile).y;
                                GTAI_UNIT(unitID).unkAttackRelated = 0xb;
                                if (chaseReturnX == 0) {
                                    short const savedY = GTAI_UNIT(unitID).savedDestinationY;
                                    GTAI_UNIT(unitID).chaseReturnX = GTAI_UNIT(unitID).savedDestinationX;
                                    GTAI_UNIT(unitID).chaseReturnY = savedY;
                                }
                                GTAI_STOP(unitID);
                                GTAI_UNIT(unitID).shootBeforeStop = 10;
                            }
                            break;
                        }
                    } while (index < this->tribes[tribeID].size);
                    if (meleeCount != 0) {
                        int const leaderID = this->tribes[tribeID].leaderUnitID;
                        int interceptX = GTAI_UNIT(leaderID).x;
                        int interceptY = GTAI_UNIT(leaderID).y;
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::predictUnitInterceptPosition, this)(
                            leaderID, id__x__tile, &interceptX, &interceptY);
                        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::pathPlanningForTribe,
                            DAT_PathFindingState::ptr)(tribeID, id__x__tile, interceptX, interceptY, meleeCount,
                            GTAI_AREA(GTAI_UNIT(leaderID).tile), GTAI_UNIT(leaderID).owner);
                        this->tribes[tribeID].attackTargetUnitID = (short)id__x__tile;
                        this->tribes[tribeID].attackTargetUnitUID = unitUID__Y;
                        this->tribes[tribeID].targetUnitTile = GTAI_UNIT(id__x__tile).tile;
                        index = 0;
                        this->tribes[tribeID].someTile2 = GTAI_UNIT(id__x__tile).savedDestinationX
                            + GTAI_ROW(GTAI_UNIT(id__x__tile).savedDestinationY);
                        int maxHalfPath = 0;
                        if (this->tribes[tribeID].size > 0) {
                            Navigation::PathHelper12* dest = GTAI_DESTS;
                            do {
                                int const unitID = GTAI_GET_UNIT(index);
                                ++index;
                                if (GTAI_UNIT(unitID).logicalState != ULS_NORMAL || GTAI_UNIT(unitID).dying != 0
                                    || GTAI_UNIT(unitID).isAssassinHookClimbing != 0
                                    || GTAI_UNIT(unitID).state.generic == States::US_MELEE_ATTACK) {
                                    continue;
                                }
                                switch (GTAI_UNIT(unitID).unitType) {
                                case UT_TUNNELER:
                                case UT_E_SPEAR:
                                case UT_E_PIKE:
                                case UT_E_MACE:
                                case UT_E_SWORD:
                                case UT_E_KNIGHT:
                                case UT_E_MONK:
                                case UT_LORD:
                                case UT_A_SLAVE:
                                case UT_A_ASSASSIN:
                                case UT_A_SWORDSMAN: {
                                    int const tile = dest->tile1;
                                    if (tile == 0) {
                                        break;
                                    }
                                    short const tileY = GTAI_TILE_Y(tile);
                                    int const tileX = tile - GTAI_ROW(tileY);
                                    if (dest->tile2OrAHelper != 0) {
                                        GTAI_UNIT(unitID).targetingType_OR_performanceStep = UIT_UNIT_ATTACK_UNIT;
                                        GTAI_UNIT(unitID).targetUnitId = (short)id__x__tile;
                                        GTAI_UNIT(unitID)
                                            .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                                            = unitUID__Y;
                                    } else {
                                        GTAI_UNIT(unitID).targetingType_OR_performanceStep = UIT_NONE;
                                        if (GTAI_UNIT(unitID).unitType == UT_LORD) {
                                            break;
                                        }
                                    }
                                    GTAI_UNIT(unitID).plannedDestinationX = (short)tileX;
                                    GTAI_UNIT(unitID).plannedDestinationY = tileY;
                                    GTAI_UNIT(unitID).targetedBuildingTile = 0;
                                    if (GTAI_UNIT(unitID).state.generic == States::US_MELEE_ATTACK) {
                                        GTAI_UNIT(unitID).unknownMovementRelated_0x2d2
                                            = GTAI_UNIT(unitID).movementSpeed * -4;
                                    }
                                    if (GTAI_UNIT(unitID).chaseReturnX == 0) {
                                        GTAI_UNIT(unitID).chaseReturnX = GTAI_UNIT(unitID).savedDestinationX;
                                        GTAI_UNIT(unitID).chaseReturnY = GTAI_UNIT(unitID).savedDestinationY;
                                    }
                                    GTAI_UNIT(unitID).state.generic = States::US_MOVE_TO_DESTINATION;
                                    if (GTAI_ALL_ASSASSINS() != FALSE) {
                                        DAT_PathFindingState::instance.pathForAssassins = 1;
                                    } else {
                                        DAT_PathFindingState::instance.skipLocalPathSearch = 1;
                                    }
                                    GTAI_SET_DEST(unitID, tileX, tileY);
                                    GTAI_UNIT(unitID).moveDelay = 0;
                                    GTAI_UNIT(unitID).lookForEnemy = -50;
                                    if (GTAI_UNIT(unitID).chaseTargetUnitID != id__x__tile) {
                                        GTAI_UNIT(unitID).chaseTargetUnitID = (short)id__x__tile;
                                        ++GTAI_UNIT(id__x__tile).huntedBy;
                                    }
                                    int const halfPath = GTAI_UNIT(unitID).totalSizeOfPathPlan / 2;
                                    if (halfPath > maxHalfPath) {
                                        maxHalfPath = halfPath;
                                    }
                                    ++dest;
                                    DAT_PathFindingState::instance.skipLocalPathSearch = 0;
                                    break;
                                }
                                }
                            } while (index < this->tribes[tribeID].size);
                        }
                        int retargetDelay = maxHalfPath * 8;
                        if (retargetDelay <= 8) {
                            retargetDelay = 8;
                        }
                        this->tribes[tribeID].attackRetargetDelay = (short)retargetDelay;
                        return 1;
                    }
                }
                break;
            }
            case 0x1a: {
                int index = 0;
                if (size > 0) {
                    do {
                        int const unitID = GTAI_GET_UNIT(index);
                        ++index;
                        if (GTAI_UNIT(unitID).logicalState == ULS_NORMAL && GTAI_UNIT(unitID).dying == 0
                            && (uint)(GTAI_UNIT(unitID).unitType - UT_S_CATAPULT) < 2) {
                            GTAI_UNIT(unitID).throwCowNext = 1;
                        }
                    } while (index < this->tribes[tribeID].size);
                    return 1;
                }
                break;
            }
            case UIT_ATTACK_LAND:
            case UIT_THROW_COW: {
                int const owner = this->tribes[tribeID].owner;
                this->tribes[tribeID].rallyMode = 0;
                int index = 0;
                if (size > 0) {
                    do {
                        int const unitID = GTAI_GET_UNIT(index);
                        ++index;
                        if (GTAI_UNIT(unitID).logicalState == ULS_NORMAL && GTAI_UNIT(unitID).dying == 0) {
                            switch (GTAI_UNIT(unitID).unitType) {
                            case UT_E_ARCHER:
                            case UT_E_XBOW:
                            case UT_E_ARCHER_DEBUG:
                            case UT_S_MANGONEL:
                            case UT_S_BALLISTA:
                            case UT_A_ARCHER:
                            case UT_A_SLINGER:
                            case UT_A_HARCHER:
                            case UT_A_FIRETHROWER:
                            case UT_S_FBALLISTA:
                                if (GTAI_UNIT(unitID).state.generic == States::US_RALLYING) {
                                    GTAI_UNIT(unitID).state.generic = States::US_MOVE_TO_DESTINATION;
                                }
                                GTAI_UNIT(unitID).idleInterruptedForAttack = 0;
                                GTAI_UNIT(unitID).targetingType_OR_performanceStep
                                    = (UnitInstructionTypeShort)unitInstructionType;
                                goto attackLandCommon;
                            case UT_S_CATAPULT:
                            case UT_S_TREBUCHET:
                                if (GTAI_UNIT(unitID)
                                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                                    == 0) {
                                    break;
                                }
                            attackLandCommon: {
                                GTAI_UNIT(unitID).pendingTargetingType = (byte)unitInstructionType;
                                if (unitInstructionType == UIT_THROW_COW) {
                                    UnitTypeShort const unitType = GTAI_UNIT(unitID).unitType;
                                    if (unitType == UT_S_CATAPULT || unitType == UT_S_TREBUCHET) {
                                        if (DAT_GameState::instance.playerDataArray[owner].cowCount > 0) {
                                            GTAI_UNIT(unitID).targetingType_OR_performanceStep = UIT_THROW_COW;
                                            GTAI_UNIT(unitID).shootTargetMicroX = (short)id__x__tile * 8;
                                            GTAI_UNIT(unitID).shootTargetMicroY = (short)unitUID__Y * 8;
                                            GTAI_UNIT(unitID).shootTargetZ = DAT_TileMapState::instance
                                                                                  .HeightLayer[GTAI_ROW(unitUID__Y) + id__x__tile];
                                        } else {
                                            GTAI_UNIT(unitID).pendingTargetingType = 5;
                                        }
                                    }
                                }
                                GTAI_UNIT(unitID).attackAtTileX = (short)id__x__tile;
                                GTAI_UNIT(unitID).attackAtTileY = (short)unitUID__Y;
                                GTAI_UNIT(unitID).unkAttackRelated = (short)param_5;
                                GTAI_UNIT(unitID).chaseReturnX = 0;
                                GTAI_UNIT(unitID).chaseReturnY = 0;
                                GTAI_STOP(unitID);
                                GTAI_UNIT(unitID).shootBeforeStop = 10;
                                break;
                            }
                            }
                        }
                    } while (index < this->tribes[tribeID].size);
                    return 1;
                }
                break;
            }
            case UIT_THROW_OIL: {
                int index = 0;
                this->tribes[tribeID].rallyMode = 0;
                if (size > 0) {
                    do {
                        int const unitID = GTAI_GET_UNIT(index);
                        ++index;
                        if (GTAI_UNIT(unitID).logicalState == ULS_NORMAL && GTAI_UNIT(unitID).dying == 0
                            && GTAI_UNIT(unitID).unitType == UT_E_ENGINEER) {
                            GTAI_UNIT(unitID).targetingType_OR_performanceStep = UIT_THROW_OIL;
                            GTAI_UNIT(unitID).attackAtTileX = (short)id__x__tile;
                            GTAI_UNIT(unitID).attackAtTileY = (short)unitUID__Y;
                            GTAI_UNIT(unitID).plannedDestinationX = (short)id__x__tile;
                            GTAI_UNIT(unitID).plannedDestinationY = (short)unitUID__Y;
                            GTAI_DESELECT(unitID);
                            GTAI_CLEAR_SELECTION(this->tribes[tribeID].owner, unitID);
                            GTAI_UNIT(unitID).chaseReturnX = 0;
                            GTAI_UNIT(unitID).chaseReturnY = 0;
                        }
                    } while (index < this->tribes[tribeID].size);
                    return 1;
                }
                break;
            }
            case UIT_LIGHT_PITCH: {
                this->tribes[tribeID].rallyMode = 0;
                int index = 0;
                if (DAT_TileMapState::instance.pitchDitches[id__x__tile].uid == unitUID__Y && size > 0) {
                    do {
                        int const unitID = GTAI_GET_UNIT(index);
                        ++index;
                        if (GTAI_UNIT(unitID).logicalState == ULS_NORMAL && GTAI_UNIT(unitID).dying == 0) {
                            GTAI_UNIT(unitID).chaseReturnX = 0;
                            GTAI_UNIT(unitID).chaseReturnY = 0;
                            UnitTypeShort const unitType = GTAI_UNIT(unitID).unitType;
                            if (unitType == UT_E_ARCHER || unitType == UT_A_ARCHER) {
                                short const ditchY = DAT_TileMapState::instance.pitchDitches[id__x__tile].y;
                                GTAI_UNIT(unitID).shootTargetMicroX
                                    = DAT_TileMapState::instance.pitchDitches[id__x__tile].x * 8 + 4;
                                int const ditchTile = DAT_TileMapState::instance.pitchDitches[id__x__tile].tile;
                                GTAI_UNIT(unitID).shootTargetMicroY = ditchY * 8 + 4;
                                GTAI_UNIT(unitID).shootTargetZ = DAT_TileMapState::instance.HeightLayer[ditchTile];
                                GTAI_UNIT(unitID).shootTargetedUnit = -1;
                                GTAI_UNIT(unitID).targetID_OR_targetBuildingID = (short)id__x__tile;
                                GTAI_UNIT(unitID)
                                    .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                                    = unitUID__Y;
                                GTAI_UNIT(unitID).pendingTargetingType = 0x22;
                                GTAI_UNIT(unitID).targetingType_OR_performanceStep = UIT_LIGHT_PITCH;
                                GTAI_UNIT(unitID).idleInterruptedForAttack = 0;
                                GTAI_STOP(unitID);
                                GTAI_UNIT(unitID).shootBeforeStop = 10;
                            }
                        }
                    } while (index < this->tribes[tribeID].size);
                    return 1;
                }
                break;
            }
            case UIT_ATTACK_BUILDING:
            case 0x24:
            case 0x26: {
                int index = 0;
                int meleeCount = 0;
                this->tribes[tribeID].targetBuildingID = (short)id__x__tile;
                this->tribes[tribeID].targetBuildingUID = unitUID__Y;
                this->tribes[tribeID].rallyMode = 0;
                if (size > 0) {
                    do {
                        int const unitID = GTAI_GET_UNIT(index);
                        ++index;
                        if (GTAI_UNIT(unitID).logicalState != ULS_NORMAL || GTAI_UNIT(unitID).dying != 0
                            || GTAI_UNIT(unitID).isAssassinHookClimbing != 0) {
                            continue;
                        }
                        GTAI_UNIT(unitID).chaseReturnX = 0;
                        GTAI_UNIT(unitID).chaseReturnY = 0;
                        switch (GTAI_UNIT(unitID).unitType) {
                        case UT_A_HARCHER:
                            ++ramOrHorse;
                        // fall through
                        case UT_E_ARCHER:
                        case UT_E_XBOW:
                        case UT_A_ARCHER:
                        case UT_A_SLINGER:
                        case UT_A_FIRETHROWER:
                            if (unitInstructionType == 0x24) {
                                switch (GTAI_BUILDING(id__x__tile).buildingType) {
                                case Buildings::BT_GATEHOUSELARGE:
                                case Buildings::BT_GATEHOUSESMALL:
                                case Buildings::BT_WOODGATE1:
                                case Buildings::BT_WOODGATE2:
                                case Buildings::BT_TOWER1:
                                case Buildings::BT_TOWER2:
                                case Buildings::BT_TOWER3:
                                case Buildings::BT_TOWER4:
                                case Buildings::BT_TOWER5:
                                    goto buildingShoot;
                                }
                                goto buildingMelee;
                            }
                            if (unitInstructionType == 0x26) {
                                break;
                            }
                        buildingShoot: {
                            if (GTAI_UNIT(unitID).state.generic == States::US_RALLYING) {
                                GTAI_UNIT(unitID).state.generic = States::US_MOVE_TO_DESTINATION;
                            }
                            short const halfWidth = (short)((int)(GTAI_BUILDING(id__x__tile).widthOrHeight * 8) / 2);
                            GTAI_UNIT(unitID).shootTargetMicroX = GTAI_BUILDING(id__x__tile).x * 8 + halfWidth;
                            short const height = GTAI_BUILDING(id__x__tile).terrainHeight;
                            GTAI_UNIT(unitID).shootTargetMicroY = GTAI_BUILDING(id__x__tile).y * 8 + halfWidth;
                            GTAI_UNIT(unitID).shootTargetZ = height;
                            GTAI_UNIT(unitID).shootTargetedUnit = -1;
                            GTAI_UNIT(unitID).targetID_OR_targetBuildingID = (short)id__x__tile;
                            GTAI_UNIT(unitID)
                                .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                                = unitUID__Y;
                        }
                        buildingTargetCommon:
                            GTAI_UNIT(unitID).pendingTargetingType = 9;
                            GTAI_UNIT(unitID).targetingType_OR_performanceStep = UIT_ATTACK_BUILDING;
                            GTAI_UNIT(unitID).idleInterruptedForAttack = 0;
                            GTAI_STOP(unitID);
                            GTAI_UNIT(unitID).shootBeforeStop = 10;
                            break;
                        case UT_S_CATAPULT:
                        case UT_S_TREBUCHET:
                        case UT_S_MANGONEL:
                        case UT_S_BALLISTA:
                        case UT_S_FBALLISTA:
                            if (unitInstructionType == 0x26
                                || GTAI_BUILDING(id__x__tile).buildingType == Buildings::BT_PITCHDITCH) {
                                break;
                            }
                            GTAI_UNIT(unitID).targetID_OR_targetBuildingID = (short)id__x__tile;
                            GTAI_UNIT(unitID)
                                .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                                = unitUID__Y;
                            goto buildingTargetCommon;
                        case UT_S_BATTERINGRAM:
                            if (GTAI_BUILDING(id__x__tile).buildingType != Buildings::BT_PITCHDITCH
                                && GTAI_UNIT(unitID)
                                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                                    == 4) {
                                ++meleeCount;
                                ++ramOrHorse;
                            }
                            break;
                        case UT_E_KNIGHT:
                            if (GTAI_BUILDING(id__x__tile).buildingType != Buildings::BT_PITCHDITCH) {
                                ++ramOrHorse;
                            }
                        // fall through
                        case UT_TUNNELER:
                        case UT_E_SPEAR:
                        case UT_E_PIKE:
                        case UT_E_MACE:
                        case UT_E_SWORD:
                        case UT_E_MONK:
                        case UT_LORD:
                        case UT_A_SLAVE:
                        case UT_A_ASSASSIN:
                        case UT_A_SWORDSMAN:
                        buildingMelee:
                            if (GTAI_BUILDING(id__x__tile).buildingType != Buildings::BT_PITCHDITCH) {
                                ++meleeCount;
                            }
                            break;
                        }
                    } while (index < this->tribes[tribeID].size);
                }
                if ((DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY
                        || DAT_GameState::instance.mapAndTime.skirmishStrongWalls == 0
                        || (uint)(GTAI_BUILDING(id__x__tile).buildingType - Buildings::BT_TOWER1) > 4)
                    && meleeCount != 0) {
                    short const leaderID = this->tribes[tribeID].leaderUnitID;
                    int const leaderArea = GTAI_AREA(GTAI_UNIT(leaderID).tile);
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::computeAttackDestinationsAroundBuilding,
                        DAT_PathFindingState::ptr)(tribeID, id__x__tile, meleeCount, leaderArea,
                        (unitInstructionType == UIT_ATTACK_BUILDING || unitInstructionType == 0x26)
                            ? GTAI_UNIT(leaderID).owner
                            : 0);
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::sortTribePathDestinationsByCost, this)(
                        tribeID, ramOrHorse);
                    if (GTAI_DESTS[0].tile2OrAHelper != 0) {
                        index = 0;
                        if (this->tribes[tribeID].size > 0) {
                            int* dest = &GTAI_DESTS[0].tile2OrAHelper;
                            do {
                                int const unitID = GTAI_GET_UNIT(index);
                                ++index;
                                if (GTAI_UNIT(unitID).logicalState != ULS_NORMAL || GTAI_UNIT(unitID).dying != 0
                                    || GTAI_UNIT(unitID).isAssassinHookClimbing != 0) {
                                    continue;
                                }
                                UnitTypeShort const unitType = GTAI_UNIT(unitID).unitType;
                                switch (unitType) {
                                case UT_E_ARCHER:
                                case UT_E_XBOW:
                                case UT_A_ARCHER:
                                case UT_A_SLINGER:
                                case UT_A_HARCHER:
                                case UT_A_FIRETHROWER:
                                    if (unitInstructionType != 0x24) {
                                        break;
                                    }
                                // fall through
                                case UT_TUNNELER:
                                case UT_E_SPEAR:
                                case UT_E_PIKE:
                                case UT_E_MACE:
                                case UT_E_SWORD:
                                case UT_E_KNIGHT:
                                case UT_E_MONK:
                                case UT_LORD:
                                case UT_S_BATTERINGRAM:
                                case UT_A_SLAVE:
                                case UT_A_ASSASSIN:
                                case UT_A_SWORDSMAN: {
                                    short attackX;
                                    if (unitType == UT_S_BATTERINGRAM) {
                                        if (GTAI_UNIT(unitID)
                                                .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                                            != 4) {
                                            break;
                                        }
                                        if (ramTried == 0) {
                                            int const accessTile = MACRO_CALL_MEMBER(
                                                OpenSHC::Map::Navigation::PathFindingState_Func::findBuildingAccessPoint,
                                                DAT_PathFindingState::ptr)(unitID, id__x__tile, &param_5);
                                            ramTried = 1;
                                            if (accessTile != 0) {
                                                short tileY = GTAI_TILE_Y(accessTile);
                                                int const tileX = accessTile - GTAI_ROW(tileY);
                                                if (GTAI_SET_DEST(unitID, tileX, tileY) != FALSE) {
                                                    GTAI_UNIT(unitID).targetingType_OR_performanceStep = UIT_NONE;
                                                    GTAI_UNIT(unitID).plannedDestinationX = (short)tileX;
                                                    GTAI_UNIT(unitID).plannedDestinationY = tileY;
                                                    if (GTAI_UNIT(unitID).state.generic == States::US_MELEE_ATTACK) {
                                                        GTAI_UNIT(unitID).unknownMovementRelated_0x2d2
                                                            = GTAI_UNIT(unitID).movementSpeed * -4;
                                                    }
                                                    GTAI_UNIT(unitID).state.generic = States::US_MOVE_TO_DESTINATION;
                                                    GTAI_UNIT(unitID).chaseTargetUnitID = 0;
                                                    DAT_PathFindingState::instance.skipLocalPathSearch = 0;
                                                    tileY = GTAI_TILE_Y(param_5);
                                                    GTAI_UNIT(unitID).targetedBuildingTile = param_5;
                                                    GTAI_UNIT(unitID).attackAtTileY = tileY;
                                                    attackX = (short)param_5 - (short)GTAI_ROW(tileY);
                                                    goto buildingPlanStoreX;
                                                }
                                            }
                                        }
                                    }
                                    {
                                        int const tile = dest[-1];
                                        if (tile == 0) {
                                            break;
                                        }
                                        short tileY = GTAI_TILE_Y(tile);
                                        int const tileX = tile - GTAI_ROW(tileY);
                                        GTAI_UNIT(unitID).targetingType_OR_performanceStep = UIT_NONE;
                                        GTAI_UNIT(unitID).plannedDestinationX = (short)tileX;
                                        GTAI_UNIT(unitID).plannedDestinationY = tileY;
                                        if (GTAI_UNIT(unitID).state.generic == States::US_MELEE_ATTACK) {
                                            GTAI_UNIT(unitID).unknownMovementRelated_0x2d2
                                                = GTAI_UNIT(unitID).movementSpeed * -4;
                                        }
                                        GTAI_UNIT(unitID).state.generic = States::US_MOVE_TO_DESTINATION;
                                        if (GTAI_ALL_ASSASSINS() != FALSE) {
                                            DAT_PathFindingState::instance.pathForAssassins = 1;
                                        } else {
                                            DAT_PathFindingState::instance.skipLocalPathSearch = 1;
                                        }
                                        GTAI_SET_DEST(unitID, tileX, tileY);
                                        GTAI_UNIT(unitID).chaseTargetUnitID = 0;
                                        DAT_PathFindingState::instance.skipLocalPathSearch = 0;
                                        int const buildingTile = *dest;
                                        GTAI_UNIT(unitID).targetedBuildingTile = buildingTile;
                                        tileY = GTAI_TILE_Y(buildingTile);
                                        GTAI_UNIT(unitID).attackAtTileY = tileY;
                                        attackX = *(short*)dest - (short)GTAI_ROW(tileY);
                                        dest += 3;
                                    }
                                buildingPlanStoreX:
                                    GTAI_UNIT(unitID).attackAtTileX = attackX;
                                    break;
                                }
                                }
                            } while (index < this->tribes[tribeID].size);
                            return 1;
                        }
                    }
                }
                break;
            }
            case UIT_ATTACK_WALL:
            case 0x23:
            case 0x25: {
                int index = 0;
                int meleeCount = 0;
                this->tribes[tribeID].rallyMode = 0;
                if (size > 0) {
                    do {
                        int const unitID = GTAI_GET_UNIT(index);
                        ++index;
                        if (GTAI_UNIT(unitID).logicalState != ULS_NORMAL || GTAI_UNIT(unitID).dying != 0
                            || GTAI_UNIT(unitID).isAssassinHookClimbing != 0) {
                            continue;
                        }
                        GTAI_UNIT(unitID).chaseReturnX = 0;
                        GTAI_UNIT(unitID).chaseReturnY = 0;
                        switch (GTAI_UNIT(unitID).unitType) {
                        case UT_A_HARCHER:
                            ++ramOrHorse;
                        // fall through
                        case UT_E_ARCHER:
                        case UT_E_XBOW:
                        case UT_A_ARCHER:
                        case UT_A_SLINGER:
                        case UT_A_ASSASSIN:
                        case UT_A_FIRETHROWER:
                            if (unitInstructionType == 0x23) {
                                goto wallMelee;
                            }
                            break;
                        case UT_S_CATAPULT:
                        case UT_S_TREBUCHET:
                        case UT_S_MANGONEL:
                        case UT_S_BALLISTA:
                        case UT_S_FBALLISTA:
                            if (unitInstructionType != 0x25) {
                                short const tileY = GTAI_TILE_Y(id__x__tile);
                                GTAI_UNIT(unitID).targetID_OR_targetBuildingID = (short)id__x__tile;
                                GTAI_UNIT(unitID)
                                    .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                                    = unitUID__Y;
                                GTAI_UNIT(unitID).attackAtTileY = tileY;
                                GTAI_UNIT(unitID).attackAtTileX = (short)id__x__tile - (short)GTAI_ROW(tileY);
                                GTAI_UNIT(unitID).pendingTargetingType = 0x17;
                                GTAI_UNIT(unitID).targetingType_OR_performanceStep = UIT_ATTACK_WALL;
                                GTAI_STOP(unitID);
                                GTAI_UNIT(unitID).shootBeforeStop = 10;
                            }
                            break;
                        case UT_S_TOWER: {
                            uint const freeTile = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::findFreeTileNearby,
                                DAT_UnitsState::ptr)(unitID, id__x__tile);
                            if (freeTile != 0) {
                                GTAI_SET_DEST(unitID, freeTile - GTAI_ROW(GTAI_TILE_Y(freeTile)), GTAI_TILE_Y(freeTile));
                                short const tileY = GTAI_TILE_Y(id__x__tile);
                                GTAI_UNIT(unitID).targetingType_OR_performanceStep = UIT_ATTACK_WALL;
                                GTAI_UNIT(unitID).state.generic = States::US_MOVE_TO_DESTINATION;
                                GTAI_UNIT(unitID).targetID_OR_targetBuildingID = (short)id__x__tile;
                                GTAI_UNIT(unitID).targetedBuildingTile = id__x__tile;
                                GTAI_UNIT(unitID).digTileTarget = freeTile;
                                GTAI_UNIT(unitID).attackAtTileY = tileY;
                                GTAI_UNIT(unitID).attackAtTileX = (short)id__x__tile - (short)GTAI_ROW(tileY);
                            }
                            break;
                        }
                        case UT_S_BATTERINGRAM:
                            if (GTAI_UNIT(unitID).digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                                != 4) {
                                break;
                            }
                            ++ramCount;
                        // fall through
                        case UT_E_KNIGHT:
                            ++ramOrHorse;
                        // fall through
                        case UT_TUNNELER:
                        case UT_E_SPEAR:
                        case UT_E_PIKE:
                        case UT_E_MACE:
                        case UT_E_SWORD:
                        case UT_E_MONK:
                        case UT_LORD:
                        case UT_A_SLAVE:
                        case UT_A_SWORDSMAN:
                        wallMelee:
                            ++meleeCount;
                            break;
                        }
                    } while (index < this->tribes[tribeID].size);
                }
                if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
                    && DAT_GameState::instance.mapAndTime.skirmishStrongWalls != 0) {
                    meleeCount = ramCount;
                }
                if (meleeCount != 0) {
                    short const leaderID = this->tribes[tribeID].leaderUnitID;
                    short facing;
                    int playerID;
                    if (unitInstructionType == UIT_ATTACK_WALL || unitInstructionType == 0x25) {
                        facing = GTAI_UNIT(leaderID).facingDirection;
                        playerID = GTAI_UNIT(leaderID).owner;
                    } else {
                        facing = GTAI_UNIT(leaderID).facingDirection;
                        playerID = 0;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                          findFreeSpaceNextToEnemyDefensiveStructureInSameAreaWithinDistance,
                        DAT_PathFindingState::ptr)(id__x__tile, meleeCount,
                        (int*)(int)GTAI_AREA(GTAI_UNIT(leaderID).tile), playerID, 0, facing);
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::sortTribePathDestinationsByCost, this)(
                        tribeID, ramOrHorse);
                    if (GTAI_DESTS[0].tile2OrAHelper != 0) {
                        index = 0;
                        if (this->tribes[tribeID].size > 0) {
                            int* dest = &GTAI_DESTS[0].tile2OrAHelper;
                            do {
                                int const unitID = GTAI_GET_UNIT(index);
                                ++index;
                                if (GTAI_UNIT(unitID).logicalState != ULS_NORMAL || GTAI_UNIT(unitID).dying != 0
                                    || GTAI_UNIT(unitID).isAssassinHookClimbing != 0) {
                                    continue;
                                }
                                UnitTypeShort const unitType = GTAI_UNIT(unitID).unitType;
                                switch (unitType) {
                                case UT_E_ARCHER:
                                case UT_E_XBOW:
                                case UT_A_ARCHER:
                                case UT_A_SLINGER:
                                case UT_A_ASSASSIN:
                                case UT_A_HARCHER:
                                case UT_A_FIRETHROWER:
                                    if (unitInstructionType != 0x23) {
                                        break;
                                    }
                                // fall through
                                case UT_TUNNELER:
                                case UT_E_SPEAR:
                                case UT_E_PIKE:
                                case UT_E_MACE:
                                case UT_E_SWORD:
                                case UT_E_KNIGHT:
                                case UT_E_MONK:
                                case UT_LORD:
                                case UT_A_SLAVE:
                                case UT_A_SWORDSMAN:
                                    if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
                                        && DAT_GameState::instance.mapAndTime.skirmishStrongWalls != 0) {
                                        break;
                                    }
                                // fall through
                                case UT_S_BATTERINGRAM: {
                                    if (unitType == UT_S_BATTERINGRAM) {
                                        if (GTAI_UNIT(unitID)
                                                .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                                            != 4) {
                                            break;
                                        }
                                        if (ramTried == 0) {
                                            ramTried = 1;
                                            int const ramTile = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::
                                                                                       PathFindingState_Func::
                                                                                           findUnitPreferredOrientationBasedConnectedTile,
                                                DAT_PathFindingState::ptr)(unitID, id__x__tile);
                                            if (ramTile != 0) {
                                                short tileY = GTAI_TILE_Y(ramTile);
                                                int const tileX = ramTile - GTAI_ROW(tileY);
                                                if (GTAI_SET_DEST(unitID, tileX, tileY) != FALSE) {
                                                    GTAI_UNIT(unitID).targetingType_OR_performanceStep = UIT_NONE;
                                                    GTAI_UNIT(unitID).plannedDestinationX = (short)tileX;
                                                    GTAI_UNIT(unitID).plannedDestinationY = tileY;
                                                    if (GTAI_UNIT(unitID).state.generic == States::US_MELEE_ATTACK) {
                                                        GTAI_UNIT(unitID).unknownMovementRelated_0x2d2
                                                            = GTAI_UNIT(unitID).movementSpeed * -4;
                                                    }
                                                    GTAI_UNIT(unitID).state.generic = States::US_MOVE_TO_DESTINATION;
                                                    GTAI_UNIT(unitID).chaseTargetUnitID = 0;
                                                    DAT_PathFindingState::instance.skipLocalPathSearch = 0;
                                                    tileY = GTAI_TILE_Y(id__x__tile);
                                                    GTAI_UNIT(unitID).targetedBuildingTile = id__x__tile;
                                                    GTAI_UNIT(unitID).attackAtTileY = tileY;
                                                    GTAI_UNIT(unitID).attackAtTileX
                                                        = (short)id__x__tile - (short)GTAI_ROW(tileY);
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                    int const tile = dest[-1];
                                    if (tile != 0) {
                                        short tileY = GTAI_TILE_Y(tile);
                                        int const tileX = tile - GTAI_ROW(tileY);
                                        GTAI_UNIT(unitID).targetingType_OR_performanceStep = UIT_NONE;
                                        GTAI_UNIT(unitID).plannedDestinationX = (short)tileX;
                                        GTAI_UNIT(unitID).plannedDestinationY = tileY;
                                        DAT_PathFindingState::instance.skipLocalPathSearch = 1;
                                        if (GTAI_UNIT(unitID).state.generic == States::US_MELEE_ATTACK) {
                                            GTAI_UNIT(unitID).unknownMovementRelated_0x2d2
                                                = GTAI_UNIT(unitID).movementSpeed * -4;
                                        }
                                        GTAI_UNIT(unitID).state.generic = States::US_MOVE_TO_DESTINATION;
                                        GTAI_SET_DEST(unitID, tileX, tileY);
                                        DAT_PathFindingState::instance.skipLocalPathSearch = 0;
                                        int const wallTile = *dest;
                                        short const wallTileLow = *(short*)dest;
                                        GTAI_UNIT(unitID).chaseTargetUnitID = 0;
                                        GTAI_UNIT(unitID).targetedBuildingTile = wallTile;
                                        short const wallY = GTAI_TILE_Y(wallTile);
                                        GTAI_UNIT(unitID).attackAtTileY = wallY;
                                        dest += 3;
                                        GTAI_UNIT(unitID).attackAtTileX = wallTileLow - (short)GTAI_ROW(wallY);
                                    }
                                    break;
                                }
                                }
                            } while (index < this->tribes[tribeID].size);
                            return 1;
                        }
                    }
                }
                break;
            }
            case UIT_SET_LADDER: {
                int index = 0;
                int ladderCount = 0;
                this->tribes[tribeID].rallyMode = 0;
                if (size > 0) {
                    do {
                        int const unitID = GTAI_GET_UNIT(index);
                        ++index;
                        if (GTAI_UNIT(unitID).logicalState == ULS_NORMAL && GTAI_UNIT(unitID).dying == 0
                            && GTAI_UNIT(unitID).unitType == UT_E_LADDER) {
                            ++ladderCount;
                            GTAI_UNIT(unitID).chaseReturnX = 0;
                            GTAI_UNIT(unitID).chaseReturnY = 0;
                        }
                    } while (index < this->tribes[tribeID].size);
                    if (ladderCount != 0) {
                        short const leaderID = this->tribes[tribeID].leaderUnitID;
                        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                              populateDestinationsArrayWithWallTileAndFreeTilePairInSameArea,
                            DAT_PathFindingState::ptr)(
                            id__x__tile, ladderCount, GTAI_AREA(GTAI_UNIT(leaderID).tile), GTAI_UNIT(leaderID).owner);
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::sortTribePathDestinationsByCost,
                            this)(tribeID, 0);
                        if (GTAI_DESTS[0].tile2OrAHelper != 0) {
                            index = 0;
                            if (this->tribes[tribeID].size > 0) {
                                int* dest = &GTAI_DESTS[0].tile2OrAHelper;
                                do {
                                    int const unitID = GTAI_GET_UNIT(index);
                                    ++index;
                                    if (GTAI_UNIT(unitID).logicalState == ULS_NORMAL && GTAI_UNIT(unitID).dying == 0
                                        && GTAI_UNIT(unitID).unitType == UT_E_LADDER) {
                                        int const tile = dest[-1];
                                        if (tile != 0) {
                                            short tileY = GTAI_TILE_Y(tile);
                                            int const tileX = tile - GTAI_ROW(tileY);
                                            GTAI_UNIT(unitID).targetingType_OR_performanceStep = UIT_NONE;
                                            GTAI_UNIT(unitID).plannedDestinationX = (short)tileX;
                                            GTAI_UNIT(unitID).plannedDestinationY = tileY;
                                            DAT_PathFindingState::instance.skipLocalPathSearch = 1;
                                            if (GTAI_UNIT(unitID).state.generic == States::US_MELEE_ATTACK) {
                                                GTAI_UNIT(unitID).unknownMovementRelated_0x2d2
                                                    = GTAI_UNIT(unitID).movementSpeed * -4;
                                            }
                                            GTAI_UNIT(unitID).state.generic
                                                = (short)((*dest != 0) * 2 + States::US_MOVE_TO_DESTINATION);
                                            GTAI_SET_DEST(unitID, tileX, tileY);
                                            DAT_PathFindingState::instance.skipLocalPathSearch = 0;
                                            int const wallTile = *dest;
                                            short const wallTileLow = *(short*)dest;
                                            GTAI_UNIT(unitID).targetedBuildingTile = wallTile;
                                            tileY = GTAI_TILE_Y(wallTile);
                                            GTAI_UNIT(unitID).attackAtTileY = tileY;
                                            dest += 3;
                                            GTAI_UNIT(unitID).attackAtTileX = wallTileLow - (short)GTAI_ROW(tileY);
                                        }
                                    }
                                } while (index < this->tribes[tribeID].size);
                                return 1;
                            }
                        }
                    }
                }
                break;
            }
            case UIT_FILL_MOAT: {
                int const leaderArea = GTAI_AREA(GTAI_UNIT(this->tribes[tribeID].leaderUnitID).tile);
                this->tribes[tribeID].rallyMode = 0;
                if (leaderArea != 0) {
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::canNavigateFunctionReturnsArea,
                            DAT_PathFindingState::ptr)(this->tribes[tribeID].owner, leaderArea, id__x__tile, unitUID__Y)
                        == 0) {
                        return 1;
                    }
                    unitUID__Y = DAT_PathFindingState::instance.climbY;
                    id__x__tile = DAT_PathFindingState::instance.climbX;
                }
            }
            // fall through
            case UIT_DIG_MOAT: {
                int index = 0;
                this->tribes[tribeID].rallyMode = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveUnitSelectionMoveInstructionNoMatchedSpeed,
                    this)(tribeID, id__x__tile, unitUID__Y, 0, 1);
                if (this->tribes[tribeID].size > 0) {
                    do {
                        int const unitID = GTAI_GET_UNIT(index);
                        ++index;
                        if (GTAI_UNIT(unitID).logicalState == ULS_NORMAL && GTAI_UNIT(unitID).dying == 0) {
                            switch (GTAI_UNIT(unitID).unitType) {
                            case UT_E_ARCHER:
                            case UT_E_SPEAR:
                            case UT_E_PIKE:
                            case UT_E_MACE:
                            case UT_E_ENGINEER:
                            case UT_A_SLAVE:
                                if (GTAI_UNIT(unitID).state.generic == States::US_RALLYING) {
                                    GTAI_UNIT(unitID).state.generic = States::US_MOVE_TO_DESTINATION;
                                }
                                GTAI_UNIT(unitID).targetingType_OR_performanceStep
                                    = (UnitInstructionTypeShort)unitInstructionType;
                                GTAI_UNIT(unitID).attackAtTileX = (short)id__x__tile;
                                GTAI_UNIT(unitID).attackAtTileY = (short)unitUID__Y;
                                GTAI_UNIT(unitID).targetX = (short)originalX;
                                GTAI_UNIT(unitID).targetY = (short)originalY;
                                GTAI_UNIT(unitID).targetedBuildingTile = 0;
                                GTAI_UNIT(unitID).chaseTargetUnitID = 0;
                                GTAI_UNIT(unitID).chaseReturnX = 0;
                                GTAI_UNIT(unitID).chaseReturnY = 0;
                                break;
                            }
                        }
                    } while (index < this->tribes[tribeID].size);
                    return 1;
                }
                break;
            }
            case UIT_CONSTRUCT_SIEGE_EQUIPMENTOIL_DUTYENGINEERRELATED: {
                this->tribes[tribeID].rallyMode = 0;
                int const entryY = GTAI_BUILDING(id__x__tile).buildingEntryY;
                int const entryX = GTAI_BUILDING(id__x__tile).buildingEntryX;
                int index = 0;
                if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(entryX, entryY)
                    == FALSE) {
                    return 0;
                }
                int const area = GTAI_AREA(GTAI_ROW(entryY) + entryX);
                int required = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getRequiredEngineersCount,
                    DAT_BuildingsState::ptr)(id__x__tile);
                if ((required != 0 || GTAI_BUILDING(id__x__tile).buildingType == Buildings::BT_OILSMELTER)
                    && this->tribes[tribeID].size > 0) {
                    do {
                        int const unitID = GTAI_GET_UNIT(index);
                        int next = index + 1;
                        if (GTAI_UNIT(unitID).logicalState == ULS_NORMAL && GTAI_UNIT(unitID).dying == 0) {
                            UnitTypeShort const unitType = GTAI_UNIT(unitID).unitType;
                            if (unitType == UT_E_ENGINEER) {
                                short const state = GTAI_UNIT(unitID).state.generic;
                                if (state != 9 && state != 10 && state != 11 && state != 12 && state != 13
                                    && state != 14 && state != 15 && unitType == unitType) {
                                    GTAI_UNIT(unitID).chaseReturnX = 0;
                                    GTAI_UNIT(unitID).chaseReturnY = 0;
                                    if (MACRO_CALL_MEMBER(
                                            OpenSHC::Map::Buildings::BuildingsState_Func::resolveBuildingEntryAccessibility,
                                            DAT_BuildingsState::ptr)(
                                            id__x__tile, 1, GTAI_UNIT(unitID).x, GTAI_UNIT(unitID).y)
                                            != 0
                                        && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                                 calculateCanPlayerUnitsNavigateToAreaFromArea,
                                               DAT_PathFindingState::ptr)(
                                               GTAI_UNIT(unitID).owner, area, GTAI_AREA(GTAI_UNIT(unitID).tile), 0)
                                            != 0) {
                                        GTAI_UNIT(unitID).targetID_OR_targetBuildingID = (short)id__x__tile;
                                        GTAI_UNIT(unitID).targetUID = GTAI_BUILDING(id__x__tile).uid;
                                        GTAI_SET_DEST(unitID, GTAI_BUILDING(id__x__tile).buildingEntryX,
                                            GTAI_BUILDING(id__x__tile).buildingEntryY);
                                        if (GTAI_BUILDING(id__x__tile).buildingType == Buildings::BT_OILSMELTER) {
                                            GTAI_UNIT(unitID).state.generic = States::US_STATE_9Unk;
                                            GTAI_UNIT(unitID).workplaceOrHomeBuildingID = (short)id__x__tile;
                                        } else {
                                            next = index;
                                            GTAI_UNIT(unitID).state.generic = States::US_STAND_UPUnk;
                                            GTAI_UNIT(unitID).resourceToDeposit = 0;
                                            GTAI_DESELECT(unitID);
                                            GTAI_CLEAR_SELECTION(this->tribes[tribeID].owner, unitID);
                                            if (--required == 0) {
                                                return 1;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        index = next;
                    } while (index < this->tribes[tribeID].size);
                    return 1;
                }
                break;
            }
            case UIT_MAN_SIEGE_EQUIPMENT: {
                this->tribes[tribeID].rallyMode = 0;
                if (GTAI_UNIT(id__x__tile).uid == unitUID__Y) {
                    int required = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getRemainingRequiredEngineers,
                        DAT_UnitsState::ptr)(id__x__tile);
                    if (required != 0) {
                        int index = 0;
                        if (this->tribes[tribeID].size > 0) {
                            do {
                                int const unitID = GTAI_GET_UNIT(index);
                                int next = index + 1;
                                if (GTAI_UNIT(unitID).logicalState == ULS_NORMAL && GTAI_UNIT(unitID).dying == 0
                                    && GTAI_UNIT(unitID).unitType == UT_E_ENGINEER) {
                                    GTAI_UNIT(id__x__tile).chaseReturnX = 0;
                                    GTAI_UNIT(id__x__tile).chaseReturnY = 0;
                                    int const unitArea = GTAI_AREA(GTAI_UNIT(unitID).tile);
                                    int x;
                                    int y;
                                    int attempt = 0;
                                    do {
                                        int const slot = GTAI_UNIT(id__x__tile).digTileY__OR__crewScatterSlotIndex;
                                        x = DAT_AttackInfoDefinedData::instance.unitScatterOffsetsXY[slot][0]
                                            + GTAI_UNIT(id__x__tile).x;
                                        y = DAT_AttackInfoDefinedData::instance.unitScatterOffsetsXY[slot][1]
                                            + GTAI_UNIT(id__x__tile).y;
                                        GTAI_UNIT(id__x__tile).digTileY__OR__crewScatterSlotIndex
                                            = (short)((slot + 1) % 16);
                                        if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                                DAT_ViewportRenderState::ptr)(x, y)
                                            != FALSE) {
                                            int const tile = GTAI_ROW(y) + x;
                                            int const tileArea = GTAI_AREA(tile);
                                            int const heightDiff = GTAI_UNIT(id__x__tile).buildingHeight
                                                + GTAI_UNIT(id__x__tile).terrainOrClimbHeight
                                                - (int)MACRO_CALL_MEMBER(
                                                    OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile,
                                                    DAT_TileMapState::ptr)(tile);
                                            if (abs(heightDiff) < 0x11
                                                && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                                         calculateCanPlayerUnitsNavigateToAreaFromArea,
                                                       DAT_PathFindingState::ptr)(
                                                       GTAI_UNIT(id__x__tile).owner, unitArea, tileArea, 0)
                                                    != 0) {
                                                break;
                                            }
                                        }
                                        ++attempt;
                                    } while (attempt < 16);
                                    GTAI_SET_DEST(unitID, x, y);
                                    GTAI_UNIT(unitID).state.generic = States::US_MOVE_TO_DESTINATION;
                                    GTAI_UNIT(unitID).targetingType_OR_performanceStep = UIT_MAN_SIEGE_EQUIPMENT;
                                    GTAI_UNIT(unitID).targetUnitId = (short)id__x__tile;
                                    GTAI_UNIT(unitID).resourceToDeposit = 0;
                                    GTAI_DESELECT(unitID);
                                    GTAI_CLEAR_SELECTION(this->tribes[tribeID].owner, unitID);
                                    next = index;
                                    if (--required == 0) {
                                        return 1;
                                    }
                                }
                                index = next;
                            } while (index < this->tribes[tribeID].size);
                            return 1;
                        }
                    }
                }
                break;
            }
            case UIT_EXIT_SIEGE_EQUIPMENT: {
                short const stateAfterFade = param_5 != 0 ? 0x10 : 0;
                int scatterSlot = SEC_RNG::instance.currentNumber2 % 16;
                MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                if (GTAI_UNIT(id__x__tile).uid == unitUID__Y) {
                    GTAI_UNIT(id__x__tile).state.generic = States::US_FIRE_WEAPONUnk;
                    int crewIndex = 0;
                    if (GTAI_UNIT(id__x__tile).digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                        > 0) {
                        short* crewRef = GTAI_UNIT(id__x__tile).manningEngineerRef;
                        do {
                            int const crewID = *crewRef;
                            *crewRef = 0;
                            GTAI_UNIT(crewID).manningReleaseUnk3c0 = 0;
                            GTAI_UNIT(crewID).retargetDelayOrSiegeTile = 0;
                            GTAI_UNIT(crewID).animationCycleNumber = 0;
                            GTAI_UNIT(crewID).state.generic = States::US_FADE_TRANSITION;
                            GTAI_UNIT(crewID).fadeLevel = 0x20;
                            GTAI_UNIT(crewID).fadeAlphaStep = 0xfe;
                            GTAI_UNIT(crewID).stateAfterFade = stateAfterFade;
                            UnitTypeShort const engineType = GTAI_UNIT(id__x__tile).unitType;
                            if (engineType == UT_S_MANGONEL || engineType == UT_S_BALLISTA) {
                                GTAI_UNIT(crewID).goToRallyPoint = 1;
                            }
                            GTAI_UNIT(crewID).updateTickTracker = 0;
                            GTAI_UNIT(crewID).faceViewer = 1;
                            int attempt = 0;
                            short x;
                            short y;
                            int tile;
                            do {
                                uint const scatterX = DAT_AttackInfoDefinedData::instance.unitScatterOffsetsXY[scatterSlot][0]
                                    + GTAI_UNIT(id__x__tile).x;
                                uint const scatterY = DAT_AttackInfoDefinedData::instance.unitScatterOffsetsXY[scatterSlot][1]
                                    + GTAI_UNIT(id__x__tile).y;
                                scatterSlot = (scatterSlot + 1) % 16;
                                MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Navigation::PathFindingState_Func::findWalkableTileThatDoesNotContainUnit,
                                    DAT_PathFindingState::ptr)(id__x__tile, scatterX, scatterY, 1);
                                if (DAT_PathFindingState::instance.ALG_ResultTile == 0) {
                                    MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                          findWalkableTileThatDoesNotContainUnit,
                                        DAT_PathFindingState::ptr)(id__x__tile, scatterX, scatterY, 0);
                                    x = (short)DAT_PathFindingState::instance.ALG_ResultX;
                                    y = (short)DAT_PathFindingState::instance.ALG_ResultY;
                                    tile = DAT_PathFindingState::instance.ALG_ResultTile;
                                    if (tile != 0) {
                                        break;
                                    }
                                    ++attempt;
                                    if (attempt != 16) {
                                        continue;
                                    }
                                    x = GTAI_UNIT(id__x__tile).x;
                                    y = GTAI_UNIT(id__x__tile).y;
                                    tile = GTAI_UNIT(id__x__tile).tile;
                                } else {
                                    x = (short)DAT_PathFindingState::instance.ALG_ResultX;
                                    y = (short)DAT_PathFindingState::instance.ALG_ResultY;
                                    tile = DAT_PathFindingState::instance.ALG_ResultTile;
                                }
                            } while (tile == 0);
                            byte const height = DAT_TileMapState::instance.HeightLayer[tile];
                            GTAI_UNIT(crewID).totalSizeOfPathPlan = 0;
                            GTAI_UNIT(crewID).x = x;
                            GTAI_UNIT(crewID).mimicCurrentXPosition = x;
                            GTAI_UNIT(crewID).y = y;
                            GTAI_UNIT(crewID).mimicCurrentYPosition = y;
                            GTAI_UNIT(crewID).terrainOrClimbHeight = height;
                            GTAI_UNIT(crewID).tile = tile;
                            GTAI_UNIT(crewID).moveToTile = tile;
                            GTAI_UNIT(crewID).microXPosition = x * 8 + 4;
                            GTAI_UNIT(crewID).microYPosition = y * 8 + 4;
                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::updateMicroPosition,
                                DAT_UnitsState::ptr)(crewID);
                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resetUnitMovementState,
                                DAT_UnitsState::ptr)(crewID);
                            ++crewRef;
                            GTAI_UNIT(crewID).animationSheetFrameOffset = 1;
                            GTAI_UNIT(crewID).field_0x30_animRelated = 0x10;
                            ++crewIndex;
                        } while (crewIndex
                            < GTAI_UNIT(id__x__tile)
                                  .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300);
                    }
                    GTAI_UNIT(id__x__tile).digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300 = 0;
                    GTAI_STOP(id__x__tile);
                    return 1;
                }
                break;
            }
            case UIT_DISBAND: {
                this->tribes[tribeID].rallyMode = 0;
                int index = 0;
                if (size > 0) {
                    do {
                        int const unitID = GTAI_GET_UNIT(index);
                        ++index;
                        if (GTAI_UNIT(unitID).logicalState == ULS_NORMAL && GTAI_UNIT(unitID).dying == 0) {
                            switch (GTAI_UNIT(unitID).unitType) {
                            case UT_TUNNELER:
                            case UT_E_ARCHER:
                            case UT_E_XBOW:
                            case UT_E_SPEAR:
                            case UT_E_PIKE:
                            case UT_E_MACE:
                            case UT_E_SWORD:
                            case UT_E_KNIGHT:
                            case UT_E_LADDER:
                            case UT_E_ENGINEER:
                            case UT_E_MONK:
                            case UT_A_ARCHER:
                            case UT_A_SLAVE:
                            case UT_A_SLINGER:
                            case UT_A_ASSASSIN:
                            case UT_A_HARCHER:
                            case UT_A_SWORDSMAN:
                            case UT_A_FIRETHROWER:
                                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::disbandUnit,
                                    DAT_UnitsState::ptr)(unitID);
                                break;
                            case UT_S_CATAPULT:
                            case UT_S_TREBUCHET:
                            case UT_S_MANGONEL:
                            case UT_S_TOWER:
                            case UT_S_BATTERINGRAM:
                            case UT_S_SHIELD:
                            case UT_S_BALLISTA:
                            case UT_S_FBALLISTA: {
                                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeAnInstruction, this)(
                                    tribeID, UIT_EXIT_SIEGE_EQUIPMENT, unitID, GTAI_UNIT(unitID).uid, 1);
                                bool const isSiegeThat = DAT_GameCore::instance.gameMode_2 == Game::GM_SIEGE_THAT;
                                GTAI_UNIT(unitID).state.generic = States::US_DISAPPEAR;
                                if (isSiegeThat) {
                                    int price;
                                    MACRO_CALL_MEMBER(
                                        OpenSHC::Map::Buildings::BuildingsState_Func::getPriceForDisbandedUnitType,
                                        DAT_BuildingsState::ptr)((UnitType)GTAI_UNIT(unitID).unitType, &price);
                                    DAT_GameState::instance
                                        .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                        .pendingResources[15]
                                        += price;
                                }
                                break;
                            }
                            }
                        }
                    } while (index < this->tribes[tribeID].size);
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::clearOrDeselectUnitFromSelection,
                    DAT_UnitsState::ptr)(this->tribes[tribeID].owner, 0, 0);
                return 1;
            }
            case 0x15: {
                this->tribes[tribeID].rallyMode = 0;
                int const entryY = GTAI_BUILDING(id__x__tile).buildingEntryY;
                int index = 0;
                if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(GTAI_BUILDING(id__x__tile).buildingEntryX, entryY)
                    == FALSE) {
                    return 0;
                }
                int const area = GTAI_AREA(GTAI_ROW(entryY) + GTAI_BUILDING(id__x__tile).buildingEntryX);
                if (size > 0) {
                    do {
                        int const unitID = GTAI_GET_UNIT(index);
                        ++index;
                        if (GTAI_UNIT(unitID).logicalState == ULS_NORMAL && GTAI_UNIT(unitID).dying == 0
                            && GTAI_UNIT(unitID).unitType == UT_TUNNELER) {
                            GTAI_UNIT(unitID).chaseReturnX = 0;
                            GTAI_UNIT(unitID).chaseReturnY = 0;
                            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                                    DAT_BuildingsState::ptr)(id__x__tile, 1)
                                    != 0
                                && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                         calculateCanPlayerUnitsNavigateToAreaFromArea,
                                       DAT_PathFindingState::ptr)(
                                       GTAI_UNIT(unitID).owner, area, GTAI_AREA(GTAI_UNIT(unitID).tile), 0)
                                    != 0) {
                                GTAI_UNIT(unitID).workplaceOrHomeBuildingID = (short)id__x__tile;
                                GTAI_UNIT(unitID).targetID_OR_targetBuildingID = (short)id__x__tile;
                                GTAI_UNIT(unitID).targetUID = GTAI_BUILDING(id__x__tile).uid;
                                GTAI_SET_DEST(unitID, GTAI_BUILDING(id__x__tile).buildingEntryX,
                                    GTAI_BUILDING(id__x__tile).buildingEntryY);
                                GTAI_UNIT(unitID).state.generic = States::US_LOOK_AROUNDUnk;
                                GTAI_UNIT(unitID).targetingType_OR_performanceStep = 0x15;
                                GTAI_DESELECT(unitID);
                                GTAI_CLEAR_SELECTION(this->tribes[tribeID].owner, unitID);
                                return 1;
                            }
                        }
                    } while (index < this->tribes[tribeID].size);
                }
                DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding,
                    DAT_BuildingsState::ptr)(id__x__tile);
                break;
            }
            }
            return 1;
        }

#undef GTAI_UNIT
#undef GTAI_BUILDING
#undef GTAI_TILE_Y
#undef GTAI_ROW
#undef GTAI_DESTS
#undef GTAI_GET_UNIT
#undef GTAI_STOP
#undef GTAI_SET_DEST
#undef GTAI_ALL_ASSASSINS
#undef GTAI_DESELECT
#undef GTAI_CLEAR_SELECTION
#undef GTAI_AREA

    }
}
}
