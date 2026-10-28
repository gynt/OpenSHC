#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitSelectionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // ALG_ResultTileIndex and pathEaseBalance are compared signed (jge 0xfa0 at 0x52691A, jl at 0x526E84 /
        // 0x526E93). UnitInstructionMoveDelay is read as a word (0x526E72). The search radius starts at 500 and is
        // grown by 500 per round (0x5266F0); the formation step is 1 on walls/keep or when climbing, 3 for animal
        // tribes, 4 for the slow siege engines, 2 otherwise (0x526A53..0x526AA7).
        // FUNCTION: STRONGHOLDCRUSADER 0x005263A0
        undefined4 TribesState::giveTribeMoveInstruction(
            int tribeID, uint x1, uint y1, int rallyBool, int storeAsRallyPoint, UnitMatchSpeedEnum speedMatching)
        {
            int destOnWallOrKeep = 0;
            int useClimbingPath = 0;
            int unitIndex = 0;
            int radius = 500;
            int useCrossAreaBridge = 0;
            int bridgeTargetTile = 0;
            int bridgeResultTile = 0;
            int allAssassins = 0;
            if ((x1 == 0 && y1 == 0) || (int)x1 < 0 || (int)x1 >= 400 || y1 > 399
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y1 * 400 + x1] == 0) {
                return 0;
            }
            int leaderID = this->tribes[tribeID].leaderUnitID;
            int const leaderX = DAT_UnitsState::instance.units[leaderID].x;
            int const leaderY = DAT_UnitsState::instance.units[leaderID].y;
            int leaderArea = (short)DAT_TileMapState::instance
                                 .PathConnectionLayer[DAT_ViewportRenderState::instance.translationMatrix[leaderY].addXgetTile
                                     + leaderX];
            int const destTile = DAT_ViewportRenderState::instance.translationMatrix[y1].addXgetTile + x1;
            int const destArea = (short)DAT_TileMapState::instance.PathConnectionLayer[destTile];
            if ((DAT_TileMapState::instance.LogicLayer[destTile] & 0x30) != 0) {
                return 0;
            }
            DAT_PathFindingState::instance.areaRouteNeedsLadders = 0;
            ++this->fcn_mtribe;
            if (leaderID
                == MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getFirstUnitInTribeThatIsOnXTerrain, this)(
                    tribeID)) {
                leaderArea = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::canNavigateFunctionReturnsArea,
                    DAT_PathFindingState::ptr)(this->tribes[tribeID].owner, destArea,
                    DAT_UnitsState::instance.units[leaderID].x, DAT_UnitsState::instance.units[leaderID].y);
                if (leaderArea == 0) {
                    return MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::TribesState_Func::applyMoveCommandOrRallyCommandToTribe, this)(
                        tribeID, x1, y1, rallyBool, storeAsRallyPoint);
                }
                leaderID = this->tribes[tribeID].leaderUnitID;
                useClimbingPath = 1;
            } else if (leaderArea == 0) {
                return MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::TribesState_Func::applyMoveCommandOrRallyCommandToTribe, this)(
                    tribeID, x1, y1, rallyBool, storeAsRallyPoint);
            }
            if (destArea <= 0) {
                return 0;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::isTribeAllAssassins, this)(tribeID)
                != FALSE) {
                allAssassins = 1;
            } else if (destArea != leaderArea) {
                int const canClimb = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::TribesState_Func::tribeContainsUnitThatCanClimb, this)(tribeID);
                int const ladderArea = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                    DAT_PathFindingState::ptr)(this->tribes[tribeID].owner, leaderArea, destArea, canClimb);
                if (ladderArea == 0) {
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isUnitStrandedOnWallsOrKeep,
                            DAT_PathFindingState::ptr)(leaderID)
                        == 0) {
                        return 0;
                    }
                    if (MACRO_CALL_MEMBER(
                            OpenSHC::Map::Navigation::PathFindingState_Func::findCrossAreaBridgeTileToTarget,
                            DAT_PathFindingState::ptr)(leaderID, x1, y1)
                        == 0) {
                        return 0;
                    }
                    useCrossAreaBridge = 1;
                    bridgeTargetTile = DAT_PathFindingState::instance.ALG_TargetTile;
                    bridgeResultTile = DAT_PathFindingState::instance.ALG_ResultTile;
                } else if (MACRO_CALL_MEMBER(
                               OpenSHC::Map::Navigation::PathFindingState_Func::setClimbBasedOnClosestClimbData,
                               DAT_PathFindingState::ptr)(leaderID, leaderArea, ladderArea)
                    == 0) {
                    return 0;
                }
            }
            if (storeAsRallyPoint != 0) {
                this->tribes[tribeID].rallyMode = (short)rallyBool;
                this->tribes[tribeID].rallyPointArray[0][0] = DAT_UnitsState::instance.units[leaderID].x;
                this->tribes[tribeID].rallyPointArray[0][1] = DAT_UnitsState::instance.units[leaderID].y;
                this->tribes[tribeID].rallyPointArray[1][0] = (short)x1;
                this->tribes[tribeID].rallyPointArray[1][1] = (short)y1;
                this->tribes[tribeID].currentRallyPointIndex = 1;
                this->tribes[tribeID].rallyPointCount = 2;
                this->tribes[tribeID].rabbitAttackOrdered = 0;
            }
            this->ALG_ResultTileIndex = 0;
            this->pathEaseBalance = 0;
            int const destLogic = DAT_TileMapState::instance.LogicLayer[destTile];
            int searchExhausted = 0;
            if ((destLogic & 0x100) != 0) {
                destOnWallOrKeep = 1;
            }
            if ((destLogic & 0x10000000) != 0) {
                destOnWallOrKeep = 1;
            }
            int previousDistance = 1;
            if (allAssassins != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::pathFindingWithBuildingsIncluded,
                    DAT_PathFindingState::ptr)(x1, y1, 0xffffffff, 0xffffffff, 500, 0);
            } else if (useClimbingPath != 0) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::findPathUsingClimbingWithHeightMargin16,
                    DAT_PathFindingState::ptr)(x1, y1, 0xffffffff, 0xffffffff, 500, FALSE);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findLinkageBasedPathOrWalkRadius,
                    DAT_PathFindingState::ptr)(x1, y1, -1, -1, 500, FALSE);
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::areAllTribeUnitsCoveredBySearch, this)(
                    tribeID, DAT_PathFindingState::instance.searchGeneration)
                == FALSE) {
                do {
                    radius += 500;
                    if (radius >= 0x13a10 || ((useClimbingPath != 0 || destOnWallOrKeep != 0) && radius >= 8000)) {
                        if (DAT_PathFindingState::instance.areaRouteNeedsLadders == 0) {
                            if (allAssassins != 0) {
                                if (MACRO_CALL_MEMBER(
                                        OpenSHC::Map::Navigation::PathFindingState_Func::pathFindingWithBuildingsIncluded,
                                        DAT_PathFindingState::ptr)(x1, y1, leaderX, leaderY, 100000, 0)
                                    == FALSE) {
                                    return 0;
                                }
                            } else if (useClimbingPath != 0) {
                                if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                          findPathUsingClimbingWithHeightMargin16,
                                        DAT_PathFindingState::ptr)(x1, y1, leaderX, leaderY, 100000, FALSE)
                                    == FALSE) {
                                    return 0;
                                }
                            } else if (MACRO_CALL_MEMBER(
                                           OpenSHC::Map::Navigation::PathFindingState_Func::findLinkageBasedPathOrWalkRadius,
                                           DAT_PathFindingState::ptr)(x1, y1, leaderX, leaderY, 100000, FALSE)
                                == FALSE) {
                                return 0;
                            }
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::
                                              applyMovementDistanceToUnitsInTribeBasedOnUnitNumberInTribe,
                            this)(tribeID);
                        goto planDestinations;
                    }
                    previousDistance = DAT_PathFindingState::instance.searchQueue.currentDistance;
                    if (allAssassins != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Navigation::PathFindingState_Func::pathFindingWithBuildingsIncluded,
                            DAT_PathFindingState::ptr)(x1, y1, 0xffffffff, 0xffffffff, radius, 1);
                    } else if (useClimbingPath != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Navigation::PathFindingState_Func::findPathUsingClimbingWithHeightMargin16,
                            DAT_PathFindingState::ptr)(x1, y1, 200, 0, radius, TRUE);
                    } else {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Navigation::PathFindingState_Func::findLinkageBasedPathOrWalkRadius,
                            DAT_PathFindingState::ptr)(x1, y1, -1, -1, radius, TRUE);
                    }
                } while (MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::areAllTribeUnitsCoveredBySearch,
                             this)(tribeID, DAT_PathFindingState::instance.searchGeneration)
                    == FALSE);
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::applyMovementDistanceToUnitsInTribe, this)(tribeID);
        planDestinations:
            if (this->tribes[tribeID].size > 0) {
                do {
                    int const unitID = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(tribeID, unitIndex);
                    ++unitIndex;
                    if (DAT_UnitsState::instance.units[unitID].logicalState != ULS_NORMAL
                        || DAT_UnitsState::instance.units[unitID].dying != 0
                        || DAT_UnitsState::instance.units[unitID].usingTeleport != 0
                        || DAT_UnitsState::instance.units[unitID].isAssassinHookClimbing != 0
                        || DAT_UnitsState::instance.units[unitID].state.generic == 0xcf
                        || DAT_UnitsState::instance.units[unitID].rallyRelatedFlag != 0
                        || DAT_UnitsState::instance.units[unitID].moveRelatedFlag == 1
                        || DAT_UnitsState::instance.units[unitID].isMovable == 0) {
                        continue;
                    }
                    if (DAT_UnitsState::instance.units[unitID].unitType == UT_S_TREBUCHET || DAT_UnitsState::instance.units[unitID].unitType == UT_S_MANGONEL || DAT_UnitsState::instance.units[unitID].unitType == UT_S_BALLISTA) {
                        continue;
                    }
                    if (DAT_UnitsState::instance.units[unitID].unitType == UT_S_CATAPULT
                        && DAT_UnitsState::instance.units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                            != 2) {
                        continue;
                    }
                    if (DAT_UnitsState::instance.units[unitID].unitType == UT_S_FBALLISTA
                        && DAT_UnitsState::instance.units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                            != 2) {
                        continue;
                    }
                    if (DAT_UnitsState::instance.units[unitID].unitType == UT_S_TOWER
                        && DAT_UnitsState::instance.units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                            != 4) {
                        continue;
                    }
                    if (DAT_UnitsState::instance.units[unitID].unitType == UT_S_BATTERINGRAM
                        && DAT_UnitsState::instance.units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                            != 4) {
                        continue;
                    }
                    if (DAT_UnitsState::instance.units[unitID].unitType == UT_S_SHIELD
                        && DAT_UnitsState::instance.units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                            != 1) {
                        continue;
                    }
                    if (DAT_UnitsState::instance.units[unitID].unitType == UT_E_ENGINEER) {
                        DAT_UnitsState::instance.units[unitID].isManningBuilding = 0;
                    }
                    if (allAssassins != 0) {
                        if (destOnWallOrKeep != 0) {
                            if (searchExhausted == 0) {
                                dword const found = MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Navigation::PathFindingState_Func::pathFindingResultBased,
                                    DAT_PathFindingState::ptr)(1, x1, y1, previousDistance);
                                ++this->ALG_ResultTileIndex;
                                if (found == 0) {
                                    searchExhausted = 1;
                                    this->ALG_ResultTileIndex = 0;
                                }
                            }
                            if (searchExhausted == 1) {
                                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                      findNextTileInExistingSearchThatIsModuloDistanceAway,
                                    DAT_PathFindingState::ptr)(1, x1, y1);
                                ++this->ALG_ResultTileIndex;
                            }
                        } else {
                            if (searchExhausted == 0) {
                                dword const found = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                                          findNextTileByModuloAmongPreviousSearchNotOnDefensiveStructure,
                                    DAT_PathFindingState::ptr)(3, x1, y1);
                                ++this->ALG_ResultTileIndex;
                                if (found == 0) {
                                    searchExhausted = 1;
                                    this->ALG_ResultTileIndex = 0;
                                }
                            }
                            if (searchExhausted == 1) {
                                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                      findNextTileInExistingSearchThatIsModuloDistanceAway,
                                    DAT_PathFindingState::ptr)(3, x1, y1);
                                ++this->ALG_ResultTileIndex;
                            }
                        }
                    } else {
                        if (this->tribes[tribeID].unkIsAnimalTribe != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                  findNextTileInExistingSearchThatIsModuloDistanceAway,
                                DAT_PathFindingState::ptr)(3, x1, y1);
                            ++this->ALG_ResultTileIndex;
                        } else if (destOnWallOrKeep != 0 || useClimbingPath != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                  findNextTileInExistingSearchThatIsModuloDistanceAway,
                                DAT_PathFindingState::ptr)(1, x1, y1);
                            ++this->ALG_ResultTileIndex;
                        } else if (DAT_UnitsState::instance.units[unitID].unitType == UT_S_CATAPULT || DAT_UnitsState::instance.units[unitID].unitType == UT_S_FBALLISTA || DAT_UnitsState::instance.units[unitID].unitType == UT_S_TOWER
                            || DAT_UnitsState::instance.units[unitID].unitType == UT_S_BATTERINGRAM || DAT_UnitsState::instance.units[unitID].unitType == UT_S_SHIELD) {
                            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                  findNextTileInExistingSearchThatIsModuloDistanceAway,
                                DAT_PathFindingState::ptr)(4, x1, y1);
                            ++this->ALG_ResultTileIndex;
                        } else {
                            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                  findNextTileInExistingSearchThatIsModuloDistanceAway,
                                DAT_PathFindingState::ptr)(2, x1, y1);
                            ++this->ALG_ResultTileIndex;
                        }
                    }
                    if ((int)this->ALG_ResultTileIndex >= 4000) {
                        break;
                    }
                    DAT_UnitsState::instance.units[unitID].plannedDestinationX = (short)this->ALG_ResultX;
                    DAT_UnitsState::instance.units[unitID].plannedDestinationY = (short)this->ALG_ResultY;
                } while (unitIndex < this->tribes[tribeID].size);
            }
            int moveIndex = 0;
            if (this->tribes[tribeID].size > 0) {
                do {
                    int const unitID = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(tribeID, moveIndex);
                    ++moveIndex;
                    if (DAT_UnitsState::instance.units[unitID].logicalState != ULS_NORMAL
                        || DAT_UnitsState::instance.units[unitID].dying != 0
                        || DAT_UnitsState::instance.units[unitID].usingTeleport != 0
                        || DAT_UnitsState::instance.units[unitID].isAssassinHookClimbing != 0
                        || DAT_UnitsState::instance.units[unitID].state.generic == 0xcf
                        || DAT_UnitsState::instance.units[unitID].rallyRelatedFlag != 0
                        || DAT_UnitsState::instance.units[unitID].moveRelatedFlag == 1
                        || DAT_UnitsState::instance.units[unitID].isMovable == 0) {
                        continue;
                    }
                    if (DAT_UnitsState::instance.units[unitID].unitType == UT_S_TREBUCHET || DAT_UnitsState::instance.units[unitID].unitType == UT_S_MANGONEL || DAT_UnitsState::instance.units[unitID].unitType == UT_S_BALLISTA) {
                        continue;
                    }
                    if (DAT_UnitsState::instance.units[unitID].unitType == UT_S_CATAPULT
                        && DAT_UnitsState::instance.units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                            != 2) {
                        continue;
                    }
                    if (DAT_UnitsState::instance.units[unitID].unitType == UT_S_FBALLISTA
                        && DAT_UnitsState::instance.units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                            != 2) {
                        continue;
                    }
                    if (DAT_UnitsState::instance.units[unitID].unitType == UT_S_TOWER
                        && DAT_UnitsState::instance.units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                            != 4) {
                        continue;
                    }
                    if (DAT_UnitsState::instance.units[unitID].unitType == UT_S_BATTERINGRAM
                        && DAT_UnitsState::instance.units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                            != 4) {
                        continue;
                    }
                    if (DAT_UnitsState::instance.units[unitID].unitType == UT_S_SHIELD
                        && DAT_UnitsState::instance.units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                            != 1) {
                        continue;
                    }
                    if (DAT_UnitsState::instance.units[unitID].state.generic == States::US_MELEE_ATTACK) {
                        DAT_UnitsState::instance.units[unitID].unknownMovementRelated_0x2d2
                            = DAT_UnitsState::instance.units[unitID].movementSpeed * -4;
                    }
                    int const state = DAT_UnitsState::instance.units[unitID].state.generic;
                    DAT_UnitsState::instance.units[unitID].state.generic = States::US_MOVE_TO_DESTINATION;
                    DAT_UnitsState::instance.units[unitID].chaseTargetUnitID = 0;
                    DAT_UnitsState::instance.units[unitID].targetedBuildingTile = 0;
                    if (allAssassins != 0) {
                        DAT_PathFindingState::instance.pathForAssassins = 1;
                    } else if (useClimbingPath != 0) {
                        DAT_PathFindingState::instance.skipLocalPathSearch = 0;
                    } else {
                        DAT_PathFindingState::instance.skipLocalPathSearch = DAT_EntityState::instance.fireCount == 0;
                    }
                    DAT_UnitsState::instance.units[unitID].chaseReturnX = 0;
                    DAT_UnitsState::instance.units[unitID].chaseReturnY = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::throttledMultiplayerSyncUpdate,
                        DAT_GameSynchronyState::ptr)();
                    if (state == States::US_MELEE_ATTACK
                        || DAT_UnitsState::instance.units[unitID].plannedDestinationX
                            != DAT_UnitsState::instance.units[unitID].destinationXPosition
                        || DAT_UnitsState::instance.units[unitID].plannedDestinationY
                            != DAT_UnitsState::instance.units[unitID].destinationYPosition
                        || DAT_UnitsState::instance.units[unitID].movementState != 2) {
                        if (MACRO_CALL_MEMBER(UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(unitID,
                                DAT_UnitsState::instance.units[unitID].plannedDestinationX,
                                DAT_UnitsState::instance.units[unitID].plannedDestinationY, 0)
                            == FALSE) {
                            if (useCrossAreaBridge == 0
                                || (DAT_TileMapState::instance.LogicLayer[DAT_UnitsState::instance.units[unitID].tile]
                                       & 0x10000100)
                                    == 0) {
                                goto skipMarker;
                            }
                            int const bridgeY
                                = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[bridgeTargetTile];
                            MACRO_CALL_MEMBER(UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(unitID,
                                bridgeTargetTile - DAT_ViewportRenderState::instance.translationMatrix[bridgeY].addXgetTile,
                                bridgeY, 0);
                            DAT_UnitsState::instance.units[unitID].state.generic = States::US_APPEAR;
                            DAT_UnitsState::instance.units[unitID]
                                .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                                = bridgeResultTile;
                        }
                        if (speedMatching == OpenSHC::Map::Units::Instructions::UMSE_0) {
                            goto skipMarker;
                        }
                    }
                    DAT_UnitsState::instance.units[unitID].destinationMarkerTimer = 0x10;
                skipMarker:
                    DAT_PathFindingState::instance.skipLocalPathSearch = 0;
                    if (DAT_PathFindingState::instance.lastPathWasDirect == 0) {
                        ++this->pathEaseBalance;
                    } else {
                        --this->pathEaseBalance;
                    }
                } while (moveIndex < this->tribes[tribeID].size);
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::applyUnitTopSpeedDelayBasedOnTribeSize, this)(
                tribeID, FALSE);
            int delayIndex = 0;
            this->tribes[tribeID].attackTargetUnitID = 0;
            if (this->tribes[tribeID].size > 0) {
                do {
                    int const unitID = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(tribeID, delayIndex);
                    ++delayIndex;
                    if (DAT_UnitsState::instance.units[unitID].logicalState != ULS_NORMAL
                        || DAT_UnitsState::instance.units[unitID].dying != 0
                        || DAT_UnitsState::instance.units[unitID].usingTeleport != 0
                        || DAT_UnitsState::instance.units[unitID].isAssassinHookClimbing != 0
                        || DAT_UnitsState::instance.units[unitID].state.generic == 0xcf
                        || DAT_UnitsState::instance.units[unitID].rallyRelatedFlag != 0
                        || DAT_UnitsState::instance.units[unitID].moveRelatedFlag == 1
                        || DAT_UnitsState::instance.units[unitID].isMovable == 0) {
                        continue;
                    }
                    if (DAT_UnitsState::instance.units[unitID].unitType == UT_S_TREBUCHET || DAT_UnitsState::instance.units[unitID].unitType == UT_S_MANGONEL || DAT_UnitsState::instance.units[unitID].unitType == UT_S_BALLISTA) {
                        continue;
                    }
                    if (DAT_UnitsState::instance.units[unitID].unitType == UT_S_CATAPULT
                        && DAT_UnitsState::instance.units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                            != 2) {
                        continue;
                    }
                    if (DAT_UnitsState::instance.units[unitID].unitType == UT_S_FBALLISTA
                        && DAT_UnitsState::instance.units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                            != 2) {
                        continue;
                    }
                    if (DAT_UnitsState::instance.units[unitID].unitType == UT_S_TOWER
                        && DAT_UnitsState::instance.units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                            != 4) {
                        continue;
                    }
                    if (DAT_UnitsState::instance.units[unitID].unitType == UT_S_BATTERINGRAM
                        && DAT_UnitsState::instance.units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                            != 4) {
                        continue;
                    }
                    if (DAT_UnitsState::instance.units[unitID].unitType == UT_S_SHIELD
                        && DAT_UnitsState::instance.units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                            != 1) {
                        continue;
                    }
                    int const speedIndex = DAT_UnitsState::instance.units[unitID].topSpeedDelayIndex;
                    short moveInstructionDelay
                        = *(short*)&DAT_UnitSelectionDefinedData::instance.UnitInstructionMoveDelay[speedIndex];
                    if (this->tribes[tribeID].unkIsAnimalTribe != 0) {
                        moveInstructionDelay *= 3;
                    } else if ((int)this->pathEaseBalance >= 0) {
                        moveInstructionDelay *= 2;
                    }
                    DAT_UnitsState::instance.units[unitID].moveInstructionSpeedDelayTracker = moveInstructionDelay;
                    if ((int)this->pathEaseBalance >= 0) {
                        DAT_UnitsState::instance.units[unitID].moveDelay
                            = (short)(DAT_UnitSelectionDefinedData::instance.UnitMoveDelay[speedIndex] / 2);
                    } else {
                        DAT_UnitsState::instance.units[unitID].moveDelay = 0;
                    }
                    if (DAT_UnitsState::instance.units[unitID].unknownMovementRelated_0x2d2 != 0) {
                        DAT_UnitsState::instance.units[unitID].moveDelay = 0;
                    }
                    DAT_UnitsState::instance.units[unitID].moveInstructionSpeedDelayTracker = 0;
                    DAT_UnitsState::instance.units[unitID].moveDelay = 0;
                    DAT_UnitsState::instance.units[unitID].horseArcherShootingVariation = 0;
                    DAT_UnitsState::instance.units[unitID].targetingType_OR_performanceStep
                        = UIT_NO_INSTRUCTION_OR_MOVE;
                } while (delayIndex < this->tribes[tribeID].size);
            }
            return 1;
        }

    }
}
}
