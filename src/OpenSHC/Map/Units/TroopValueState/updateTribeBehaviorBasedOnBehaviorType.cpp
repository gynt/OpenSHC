#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // attackWaveSignpostIndex is an int[50] (header declares a single int followed by padding).
        // Cases 0x3f8/0x3f9/0x412 read the result position through this (0x0051DE48 mov eax, [ebx + 4]).
        // FUNCTION: STRONGHOLDCRUSADER 0x0051D7F0
        void TroopValueState::updateTribeBehaviorBasedOnBehaviorType(int tribeID)
        {
            if (DAT_TribesState::instance.tribes[tribeID].attackWave != 0
                && DAT_TribesState::instance.tribes[tribeID].attackWave < DAT_TroopValueState::instance.attackInfo.index) {
                DAT_TribesState::instance.tribes[tribeID].attackWave = (short)DAT_TroopValueState::instance.attackInfo.index;
            }
            DAT_TroopValueState::instance.attackInfo.waveTribeCountThisTick[DAT_TribesState::instance.tribes[tribeID].attackWave]++;
            if (DAT_TribesState::instance.tribes[tribeID].percentageMoving <= 0) {
                DAT_TroopValueState::instance.attackInfo
                    .nofStationaryTribesPerWave[DAT_TribesState::instance.tribes[tribeID].attackWave]++;
            }
            DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter++;
            DAT_TribesState::instance.tribes[tribeID].behaviorResetFlag2ae = 0;
            switch (DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType) {
            case STBT_3:
                if (MACRO_CALL_MEMBER(TribesState_Func::stopTribeMovementAndCheckIdle, DAT_TribesState::ptr)(tribeID)
                    != 0) {
                    MACRO_CALL_MEMBER(TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(tribeID,
                        DAT_GameState::instance.mapAndTime
                            .unitMoveDestinationXYPairs[(&DAT_TroopValueState::instance.attackInfo.attackWaveSignpostIndex)
                                    [DAT_TribesState::instance.tribes[tribeID].attackWave]]
                                                       [DAT_TribesState::instance.tribes[tribeID].nearbyTileOffsetStartIndex]
                            .x,
                        DAT_GameState::instance.mapAndTime
                            .unitMoveDestinationXYPairs[(&DAT_TroopValueState::instance.attackInfo.attackWaveSignpostIndex)
                                    [DAT_TribesState::instance.tribes[tribeID].attackWave]]
                                                       [DAT_TribesState::instance.tribes[tribeID].nearbyTileOffsetStartIndex]
                            .y,
                        0, 0, Instructions::UMSE_0);
                    DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType = STBT_4;
                }
                break;
            case STBT_5:
                if (DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter
                    >= DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks) {
                    DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0;
                    MACRO_CALL_MEMBER(TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(tribeID,
                        DAT_GameState::instance.mapAndTime
                            .regionSeedPoints[DAT_TribesState::instance.tribes[tribeID].nearbyTileOffsetStartIndex]
                            .x,
                        DAT_GameState::instance.mapAndTime
                            .regionSeedPoints[DAT_TribesState::instance.tribes[tribeID].nearbyTileOffsetStartIndex]
                            .y,
                        0, 0, Instructions::UMSE_0);
                    DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType = STBT_6;
                }
                break;
            case STBT_7:
                if (DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter
                    >= DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks) {
                    int slot;
                    int const playerSlot = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                    DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0;
                    for (slot = 0; slot < 49; ++slot) {
                        if (DAT_GameState::instance.mapAndTime.attackVectors[playerSlot][slot].tribeID == 0) {
                            DAT_GameState::instance.mapAndTime.attackVectors[playerSlot][slot].tribeID = tribeID;
                            break;
                        }
                    }
                    MACRO_CALL_MEMBER(TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(tribeID,
                        DAT_GameState::instance.mapAndTime.attackVectors[playerSlot][slot].x,
                        DAT_GameState::instance.mapAndTime.attackVectors[playerSlot][slot].y, 0, 0,
                        Instructions::UMSE_0);
                    DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType = STBT_8;
                }
                break;
            case STBT_8:
                if (DAT_UnitsState::instance.units[DAT_TribesState::instance.tribes[tribeID].leaderUnitID]
                        .totalSizeOfPathPlan
                    < 25) {
                    DAT_TribesState::instance.tribes[tribeID].unitStance = Behavior::USE_AGGRESSIVE;
                }
                break;
            case STBT_1:
                if (DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter >= 30) {
                    DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0;
                    if (MACRO_CALL_MEMBER(TribesState_Func::isTribeUnitBlockedByOtherUnit, DAT_TribesState::ptr)(tribeID)
                        != 0) {
                        MACRO_CALL_MEMBER(TribesState_Func::moveTribeToNearbyClearTile, DAT_TribesState::ptr)(tribeID);
                    }
                }
                break;
            case STBT_0x3f2:
                DAT_TribesState::instance.tribes[tribeID].unitStance = Behavior::USE_STAND_GROUND;
                if (DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks != 0
                    && DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter
                        >= DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks) {
                    DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0;
                    DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks = 0;
                    MACRO_CALL_MEMBER(TribesState_Func::assignAttackTargetsForTribe, DAT_TribesState::ptr)(
                        tribeID, STBT_0x3f2);
                }
                break;
            case STBT_0x3ff:
                if (DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter
                    >= DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks) {
                    DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0;
                    MACRO_CALL_MEMBER(TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(tribeID,
                        DAT_GameState::instance.mapAndTime
                            .signpostsMapEdge[(&DAT_TroopValueState::instance.attackInfo.attackWaveSignpostIndex)
                                    [DAT_TribesState::instance.tribes[tribeID].attackWave]][0]
                            .x,
                        DAT_GameState::instance.mapAndTime
                            .signpostsMapEdge[(&DAT_TroopValueState::instance.attackInfo.attackWaveSignpostIndex)
                                    [DAT_TribesState::instance.tribes[tribeID].attackWave]][0]
                            .y,
                        0, 0, Instructions::UMSE_0);
                    DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType = STBT_0x400;
                }
                break;
            case STBT_0x3f6:
                DAT_TribesState::instance.tribes[tribeID].unitStance = Behavior::USE_STAND_GROUND;
                if (DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks != 0
                    && DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter
                        >= DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks) {
                    DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0;
                    DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks = 0;
                    MACRO_CALL_MEMBER(TribesState_Func::assignAttackTargetsForTribe, DAT_TribesState::ptr)(
                        tribeID, STBT_0x3f6);
                }
                break;
            case STBT_0x413:
                DAT_TribesState::instance.tribes[tribeID].unitStance = Behavior::USE_STAND_GROUND;
                if (DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks != 0
                    && DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter
                        >= DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks) {
                    DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0;
                    DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks = 0;
                    MACRO_CALL_MEMBER(TribesState_Func::assignAttackTargetsForTribe, DAT_TribesState::ptr)(
                        tribeID, STBT_0x413);
                }
                break;
            case STBT_0x414:
                DAT_TribesState::instance.tribes[tribeID].unitStance = Behavior::USE_STAND_GROUND;
                if (DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks != 0
                    && DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter
                        >= DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks) {
                    DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0;
                    DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks = 0;
                    MACRO_CALL_MEMBER(TribesState_Func::assignAttackTargetsForTribe, DAT_TribesState::ptr)(
                        tribeID, STBT_0x414);
                }
                break;
            case STBT_0x3f5:
                DAT_TribesState::instance.tribes[tribeID].unitStance = Behavior::USE_STAND_GROUND;
                if (DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks != 0
                    && DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter
                        >= DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks) {
                    DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0;
                    DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks = 0;
                    MACRO_CALL_MEMBER(TribesState_Func::assignAttackTargetsForTribe, DAT_TribesState::ptr)(
                        tribeID, STBT_0x3f5);
                }
                break;
            case STBT_0x3fb:
                if (DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks != 0
                    && DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter
                        >= DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks) {
                    DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0;
                    DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks = 0;
                    DAT_TribesState::instance.tribes[tribeID].unitStance = Behavior::USE_AGGRESSIVE;
                    MACRO_CALL_MEMBER(TribesState_Func::assignAttackTargetsForTribe, DAT_TribesState::ptr)(
                        tribeID, STBT_0x3fb);
                }
                break;
            case STBT_0x401:
                DAT_TribesState::instance.tribes[tribeID].unitStance = Behavior::USE_AGGRESSIVE;
                if (MACRO_CALL_MEMBER(TribesState_Func::allUnitsReachedTheirDestination, DAT_TribesState::ptr)(tribeID)
                    != FALSE) {
                    DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0;
                    MACRO_CALL_MEMBER(TroopValueState_Func::buildRallyPointsFromSiegeUnits, this)(tribeID);
                    int rallyIndex = DAT_TribesState::instance.tribes[tribeID].currentRallyPointIndex + 1;
                    if (rallyIndex >= DAT_TribesState::instance.tribes[tribeID].rallyPointCount) {
                        rallyIndex = 0;
                    }
                    int const rallyX = DAT_TribesState::instance.tribes[tribeID].rallyPointArray[rallyIndex][0];
                    int const rallyY = DAT_TribesState::instance.tribes[tribeID].rallyPointArray[rallyIndex][1];
                    DAT_TribesState::instance.tribes[tribeID].currentRallyPointIndex = (short)rallyIndex;
                    if (DAT_TribesState::instance.tribes[tribeID].rallyPointCount > 1
                        && DAT_UnitsState::instance.units[DAT_TribesState::instance.tribes[tribeID].leaderUnitID]
                                .closestEnemyMicroDistance
                            > 96) {
                        MACRO_CALL_MEMBER(TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                            tribeID, rallyX, rallyY, 0, 0, Instructions::UMSE_0);
                    }
                }
                break;
            case STBT_0x3fe:
                DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0;
                DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks = 0;
                DAT_TribesState::instance.tribes[tribeID].unitStance = Behavior::USE_AGGRESSIVE;
                break;
            case STBT_0x3fd:
                if (DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks != 0
                    && DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter
                        >= DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks) {
                    DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0;
                    DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks = 0;
                    MACRO_CALL_MEMBER(TribesState_Func::assignAttackTargetsForTribe, DAT_TribesState::ptr)(
                        tribeID, STBT_0x3fd);
                }
                break;
            case STBT_0x416:
                if (DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks != 0
                    && DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter
                        >= DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks
                    && MACRO_CALL_MEMBER(TribesState_Func::stopTribeMovementAndCheckIdle, DAT_TribesState::ptr)(tribeID)
                        != 0) {
                    int const keepID
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .keep.id;
                    DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0;
                    DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks = 0;
                    if (keepID > 0) {
                        int x;
                        int y;
                        if (DAT_BuildingsState::instance.buildings[keepID].buildingType == Buildings::BT_MANORHOUSE) {
                            x = DAT_BuildingsState::instance.buildings[keepID].x + 3;
                            y = DAT_BuildingsState::instance.buildings[keepID].y + 8;
                        }
                        else if (DAT_BuildingsState::instance.buildings[keepID].buildingType == Buildings::BT_STONEKEEP) {
                            x = DAT_BuildingsState::instance.buildings[keepID].x + 3;
                            y = DAT_BuildingsState::instance.buildings[keepID].y + 3;
                        }
                        else if (DAT_BuildingsState::instance.buildings[keepID].buildingType == Buildings::BT_STRONGHOLD) {
                            x = DAT_BuildingsState::instance.buildings[keepID].x + 3;
                            y = DAT_BuildingsState::instance.buildings[keepID].y + 3;
                        }
                        else if (DAT_BuildingsState::instance.buildings[keepID].buildingType == Buildings::BT_KEEPFOUR) {
                            x = DAT_BuildingsState::instance.buildings[keepID].x + 4;
                            y = DAT_BuildingsState::instance.buildings[keepID].y + 4;
                        }
                        else if (DAT_BuildingsState::instance.buildings[keepID].buildingType == Buildings::BT_KEEPFIVE) {
                            x = DAT_BuildingsState::instance.buildings[keepID].x + 5;
                            y = DAT_BuildingsState::instance.buildings[keepID].y + 5;
                        }
                        else {
                            return;
                        }
                        MACRO_CALL_MEMBER(TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                            tribeID, x, y, 0, 0, Instructions::UMSE_0);
                        DAT_TribesState::instance.tribes[tribeID].unitStance = Behavior::USE_AGGRESSIVE;
                    }
                }
                break;
            case STBT_0x3f8:
                if (DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks != 0
                    && DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter
                        >= DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks) {
                    DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0;
                    DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks = 0;
                    MACRO_CALL_MEMBER(TroopValueState_Func::calculateHigh2ClostestToTribeTargetUnit, this)(tribeID);
                    MACRO_CALL_MEMBER(TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                        tribeID, this->x, this->y, 0, 0, Instructions::UMSE_0);
                }
                break;
            case STBT_0x3f9:
                if (DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks != 0
                    && DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter
                        >= DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks) {
                    DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0;
                    DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks = 0;
                    MACRO_CALL_MEMBER(TroopValueState_Func::calculateArch2ClosestToTribeTargetUnit, this)(tribeID);
                    MACRO_CALL_MEMBER(TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                        tribeID, this->x, this->y, 0, 0, Instructions::UMSE_0);
                }
                break;
            case STBT_0x3f7:
                if (DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks != 0
                    && DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter
                        >= DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks) {
                    DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0;
                    DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks = 0;
                    MACRO_CALL_MEMBER(TribesState_Func::assignAttackTargetsForTribe, DAT_TribesState::ptr)(
                        tribeID, STBT_0x3f7);
                }
                break;
            case STBT_0x418:
                if (DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter
                    >= DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks) {
                    DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0;
                    MACRO_CALL_MEMBER(TroopValueState_Func::sendAttackingPatrolTribeToComputedDestination, this)(
                        tribeID);
                }
                break;
            case STBT_0x41e:
                if (DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks != 0
                    && DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter
                        >= DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks) {
                    DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0;
                    DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks = 0;
                    MACRO_CALL_MEMBER(TroopValueState_Func::moveTribeToReachableNearbyTile, this)(tribeID);
                }
                break;
            case STBT_0x419:
                if (DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks != 0
                    && DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter
                        >= DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks) {
                    DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0;
                    DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks = 0;
                    MACRO_CALL_MEMBER(TroopValueState_Func::decideAndExecuteTribeAttackAction, this)(tribeID);
                }
                break;
            case STBT_0x41a:
                if (DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks != 0
                    && DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter
                        >= DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks) {
                    DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0;
                    DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks = 0;
                    MACRO_CALL_MEMBER(TroopValueState_Func::moveTribeToNearbyGatehouse, this)(tribeID);
                }
                break;
            case STBT_0x41b:
                if (DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks != 0
                    && DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter
                        >= DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks) {
                    DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0;
                    DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks = 0;
                    MACRO_CALL_MEMBER(TroopValueState_Func::moveTowardsParticularUnits, this)(tribeID);
                }
                break;
            case STBT_0x3fc:
                if (DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks != 0
                    && DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter
                        >= DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks) {
                    DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0;
                    DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks = 0;
                    DAT_TribesState::instance.tribes[tribeID].unitStance
                        = DAT_TroopValueState::instance.attackInfo.field_0x21c54 > 2 ? Behavior::USE_DEFENSIVE
                                                                                      : Behavior::USE_STAND_GROUND;
                    if (DAT_TribesState::instance.tribes[tribeID].countdown2 <= 0) {
                        MACRO_CALL_MEMBER(TroopValueState_Func::claimArcherAttackPoint, this)(tribeID);
                    }
                }
                break;
            case STBT_0x412:
                if (DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks != 0
                    && DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter
                        >= DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks) {
                    DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0;
                    DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks = 0;
                    if (DAT_TribesState::instance.tribes[tribeID].countdown2 <= 0) {
                        if (MACRO_CALL_MEMBER(TroopValueState_Func::findTribeWithMoatAttackBehavior, this)() != 0) {
                            MACRO_CALL_MEMBER(TroopValueState_Func::assignTribeToSupportPoint, this)(
                                this->x, this->y, tribeID);
                        }
                        else {
                            MACRO_CALL_MEMBER(TroopValueState_Func::claimArcherAttackPoint, this)(tribeID);
                        }
                    }
                }
                break;
            case STBT_0x406:
                if (DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter
                    >= DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks) {
                    DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0;
                    MACRO_CALL_MEMBER(TroopValueState_Func::setRallyPointForLaddermenTribe, this)(tribeID);
                    if (DAT_TribesState::instance.tribes[tribeID].countdown2 <= 0) {
                        MACRO_CALL_MEMBER(TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(tribeID,
                            DAT_TribesState::instance.tribes[tribeID].rallyPointArray[0][0],
                            DAT_TribesState::instance.tribes[tribeID].rallyPointArray[0][1], 0, 0,
                            Instructions::UMSE_0);
                    }
                }
                break;
            case STBT_0x3f3:
                if (DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks != 0
                    && DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter
                        >= DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks) {
                    DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0;
                    DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks = 0;
                }
                break;
            case STBT_0x3f4:
                if (DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks != 0
                    && DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter
                        >= DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks) {
                    DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0;
                    DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks = 0;
                    MACRO_CALL_MEMBER(TribesState_Func::assignAttackTargetsForTribe, DAT_TribesState::ptr)(
                        tribeID, STBT_0x3f4);
                }
                break;
            case STBT_0x411: {
                int const linkedTribeID = DAT_TribesState::instance.tribes[tribeID].linkedTribeID;
                if (linkedTribeID == 0
                    || DAT_TribesState::instance.tribes[tribeID].linkedTribeUID
                        != DAT_TribesState::instance.tribes[linkedTribeID].uid) {
                    DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType = STBT_1;
                    break;
                }
                if (DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter
                    >= DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks) {
                    DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0;
                    int const leaderUnitID = DAT_TribesState::instance.tribes[linkedTribeID].leaderUnitID;
                    int const tile = MACRO_CALL_MEMBER(
                        Map::Navigation::PathFindingState_Func::findReachableTileWithLowestZoneDistance,
                        DAT_PathFindingState::ptr)(2, DAT_UnitsState::instance.units[leaderUnitID].x,
                        DAT_UnitsState::instance.units[leaderUnitID].y,
                        DAT_UnitsState::instance.units[leaderUnitID].siegeTargetPlayerID);
                    if (tile > 0) {
                        int const y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                        int const x = tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                        MACRO_CALL_MEMBER(TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                            tribeID, x, y, 0, 0, Instructions::UMSE_0);
                        MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::calculatePreferredRelativeOrientation,
                            DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[leaderUnitID].x,
                            DAT_UnitsState::instance.units[leaderUnitID].y, x, y);
                        DAT_TribesState::instance.tribes[tribeID].orientation
                            = (short)DAT_DirectionAlgorithmState::instance.orientation;
                    }
                }
                break;
            }
            default:
                MACRO_CALL_MEMBER(TribesState_Func::updateTribeCombatStanceBehavior, DAT_TribesState::ptr)(tribeID);
                break;
            case STBT_4:
            case STBT_6:
                break;
            case STBT_0x400:
                break;
            }
        }

    }
}
}
