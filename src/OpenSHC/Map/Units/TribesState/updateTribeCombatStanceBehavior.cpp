#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // Ring slot = (recentAttackerIndex - i + 10) % 10 (idiv at 0x52A8C6). Unit types whose SA == 0 block the
        // aggressive orders: jump tables 0x52ACB4 (instruction 0x20) and 0x52ACF4 (building/wall attack, adds the
        // Arabian slave/assassin/swordsman). Instructions 0x20/0x25/0x26 have no enum names.
        // FUNCTION: STRONGHOLDCRUSADER 0x0052A7D0
        void TribesState::updateTribeCombatStanceBehavior(int tribeID)
        {
            int const leaderUnitID = this->tribes[tribeID].leaderUnitID;
            short const attackTargetUnitID = this->tribes[tribeID].attackTargetUnitID;
            if (attackTargetUnitID != 0) {
                int const targetUnitID = attackTargetUnitID;
                if (DAT_UnitsState::instance.units[targetUnitID].uid == this->tribes[tribeID].attackTargetUnitUID) {
                    if (DAT_ViewportRenderState::instance
                                .translationMatrix[DAT_UnitsState::instance.units[targetUnitID].savedDestinationY]
                                .addXgetTile
                            + DAT_UnitsState::instance.units[targetUnitID].savedDestinationX
                        == this->tribes[tribeID].someTile2) {
                        short const retargetDelay = this->tribes[tribeID].attackRetargetDelay;
                        if (retargetDelay != 0) {
                            this->tribes[tribeID].attackRetargetDelay = retargetDelay - 1;
                            goto tick;
                        }
                        if (DAT_UnitsState::instance.units[targetUnitID].tile == this->tribes[tribeID].targetUnitTile) {
                            goto tick;
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeAnInstruction, this)(tribeID,
                        UIT_UNIT_ATTACK_UNIT, targetUnitID, this->tribes[tribeID].attackTargetUnitUID, 1);
                } else {
                    this->tribes[tribeID].attackTargetUnitID = 0;
                }
            } else if (this->tribes[tribeID].unitStance == Behavior::USE_AGGRESSIVE) {
                for (int i = 0; i < 10; ++i) {
                    int const slot = (this->tribes[tribeID].recentAttackerIndex - i + 10) % 10;
                    int const attackerUnitID = this->tribes[tribeID].recentAttackerUnitIDs[slot];
                    if (attackerUnitID == 0) {
                        continue;
                    }
                    if (DAT_UnitsState::instance.units[attackerUnitID].logicalState == ULS_NORMAL
                        && DAT_UnitsState::instance.units[attackerUnitID].dying == 0
                        && DAT_UnitsState::instance.units[attackerUnitID].uid
                            == this->tribes[tribeID].recentAttackerUIDs[slot]
                        && DAT_GameState::instance.mapAndTime
                                .playerTeams[DAT_UnitsState::instance.units[leaderUnitID].owner]
                            != DAT_GameState::instance.mapAndTime
                                .playerTeams[DAT_UnitsState::instance.units[attackerUnitID].owner]
                        && DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[leaderUnitID].tile]
                            == DAT_TileMapState::instance
                                .PathConnectionLayer[DAT_UnitsState::instance.units[attackerUnitID].tile]) {
                        int const dy = DAT_UnitsState::instance.units[leaderUnitID].microYPosition
                            - DAT_UnitsState::instance.units[attackerUnitID].microYPosition;
                        int const dx = DAT_UnitsState::instance.units[leaderUnitID].microXPosition
                            - DAT_UnitsState::instance.units[attackerUnitID].microXPosition;
                        if (dx * dx + dy * dy < 250000) {
                            if (this->tribes[tribeID].behaviorTickCounter == 0
                                && this->tribes[tribeID].aggressiveScanTimer == 0x3b) {
                                for (int memberIndex = 0; memberIndex < this->tribes[tribeID].size;) {
                                    int const memberUnitID = MACRO_CALL_MEMBER(
                                        OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                                        tribeID, memberIndex);
                                    ++memberIndex;
                                    if (DAT_UnitsState::instance.units[memberUnitID].logicalState == ULS_NORMAL
                                        && DAT_UnitsState::instance.units[memberUnitID].dying == 0
                                        && DAT_UnitsState::instance.units[memberUnitID].state.generic
                                            != States::US_MELEE_ATTACK) {
                                        switch (DAT_UnitsState::instance.units[memberUnitID].unitType) {
                                        case UT_TUNNELER:
                                        case UT_E_SPEAR:
                                        case UT_E_PIKE:
                                        case UT_E_MACE:
                                        case UT_E_SWORD:
                                        case UT_E_KNIGHT:
                                        case UT_E_MONK:
                                        case UT_S_BATTERINGRAM:
                                            if (DAT_UnitsState::instance.units[memberUnitID].SA == 0) {
                                                goto tick;
                                            }
                                            break;
                                        }
                                    }
                                }
                                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeAnInstruction, this)(
                                    tribeID, (UnitInstructionType)0x20, attackerUnitID,
                                    DAT_UnitsState::instance.units[attackerUnitID].uid, 0);
                            }
                            break;
                        }
                    } else {
                        this->tribes[tribeID].recentAttackerUnitIDs[slot] = 0;
                    }
                }
            }
        tick:
            this->tribes[tribeID].behaviorTickCounter++;
            if (this->tribes[tribeID].behaviorTickCounter <= 0x32) {
                return;
            }
            if (this->tribes[tribeID].rallyMode != 0) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::allUnitsReachedTheirDestination, this)(
                        tribeID)
                    == FALSE) {
                    return;
                }
                int nextRallyIndex = this->tribes[tribeID].currentRallyPointIndex + 1;
                this->tribes[tribeID].behaviorTickCounter = 0;
                if (nextRallyIndex >= this->tribes[tribeID].rallyPointCount) {
                    if (this->tribes[tribeID].rallyMode == -1) {
                        this->tribes[tribeID].currentRallyPointIndex = 0;
                        this->tribes[tribeID].rallyMode = 0;
                    }
                    nextRallyIndex = 0;
                }
                if (this->tribes[tribeID].rallyMode != 0) {
                    int const x = this->tribes[tribeID].rallyPointArray[nextRallyIndex][0];
                    int const y = this->tribes[tribeID].rallyPointArray[nextRallyIndex][1];
                    this->tribes[tribeID].currentRallyPointIndex = (short)nextRallyIndex;
                    UnitTypeShort const leaderType = DAT_UnitsState::instance.units[leaderUnitID].unitType;
                    if (leaderType == UT_E_ARCHER || leaderType == UT_E_XBOW || leaderType == UT_A_ARCHER
                        || leaderType == UT_A_SLINGER || leaderType == UT_A_FIRETHROWER) {
                        if (DAT_UnitsState::instance.units[leaderUnitID].closestEnemyMicroDistance > 0x1b0) {
                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction, this)(
                                tribeID, x, y, 0, 0, Instructions::UMSE_0);
                        }
                    } else if (leaderType == UT_A_HARCHER) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::TribesState_Func::giveUnitSelectionMoveInstructionNoMatchedSpeed, this)(
                            tribeID, x, y, 0, 0);
                    } else if (DAT_UnitsState::instance.units[leaderUnitID].closestEnemyMicroDistance > 0x60
                        || this->tribes[tribeID].unitStance != Behavior::USE_AGGRESSIVE) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::TribesState_Func::giveUnitSelectionMoveInstructionNoMatchedSpeed, this)(
                            tribeID, x, y, 0, 0);
                    }
                }
            } else if (this->tribes[tribeID].unitStance == Behavior::USE_AGGRESSIVE) {
                this->tribes[tribeID].aggressiveScanTimer++;
                if (this->tribes[tribeID].aggressiveScanTimer < 0x3c) {
                    return;
                }
                short const size = this->tribes[tribeID].size;
                this->tribes[tribeID].aggressiveScanTimer = 0;
                if (size > 0) {
                    int memberIndex = 0;
                    do {
                        int const memberUnitID = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                            tribeID, memberIndex);
                        ++memberIndex;
                        if (DAT_UnitsState::instance.units[memberUnitID].logicalState == ULS_NORMAL
                            && DAT_UnitsState::instance.units[memberUnitID].dying == 0
                            && DAT_UnitsState::instance.units[memberUnitID].state.generic != States::US_MELEE_ATTACK) {
                            switch (DAT_UnitsState::instance.units[memberUnitID].unitType) {
                            case UT_TUNNELER:
                            case UT_E_SPEAR:
                            case UT_E_PIKE:
                            case UT_E_MACE:
                            case UT_E_SWORD:
                            case UT_E_KNIGHT:
                            case UT_E_MONK:
                            case UT_S_BATTERINGRAM:
                            case UT_A_SLAVE:
                            case UT_A_ASSASSIN:
                            case UT_A_SWORDSMAN:
                                if (DAT_UnitsState::instance.units[memberUnitID].SA == 0) {
                                    goto spread;
                                }
                                break;
                            }
                        }
                    } while (memberIndex < this->tribes[tribeID].size);
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::aggressiveStanceTargetBuildingAtRange,
                    DAT_PathFindingState::ptr)(leaderUnitID, 15);
                if (DAT_PathFindingState::instance.ALG_ResultTile != 0) {
                    short const buildingID = DAT_TileMapState::instance.BuildingLayer[DAT_PathFindingState::instance.ALG_ResultTile];
                    if (buildingID != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeAnInstruction, this)(tribeID,
                            (UnitInstructionType)0x26, buildingID, DAT_BuildingsState::instance.buildings[buildingID].uid,
                            0);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeAnInstruction, this)(tribeID,
                            (UnitInstructionType)0x25, DAT_PathFindingState::instance.ALG_ResultTile, 0, 0);
                    }
                }
            }
        spread:
            if (this->tribes[tribeID].spreadOnSpawnPending != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::moveTribeToIndexedNearbyTile, this)(tribeID);
                this->tribes[tribeID].spreadOnSpawnPending = 0;
            }
        }

    }
}
}
