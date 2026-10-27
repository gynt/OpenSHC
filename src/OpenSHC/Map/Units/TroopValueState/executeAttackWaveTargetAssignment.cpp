#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Audio/mss/SoundSystem.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"

#include "OpenSHC/Globals/DAT_AttackInfoDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005205A0
        void TroopValueState::executeAttackWaveTargetAssignment(int attackID)
        {
            int playerID = (char)DAT_TroopValueState::instance.attackInfo.attackWavePlayerIDArray[attackID];
            // extra target-assignment rounds before the archer-point [0] and hack-point [1] groups are released
            int extraRounds[2];
            extraRounds[0] = 0;
            extraRounds[1] = 0;
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CUSTOM_MAP
                && DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE) {
                playerID = 2;
                extraRounds[0] = 5;
                extraRounds[1] = -1;
            }
            DAT_TroopValueState::instance.attackInfo.attackWaveTicker[attackID]++;
            if (DAT_TroopValueState::instance.attackInfo.attackWaveTicker[attackID]
                < DAT_AttackInfoDefinedData::instance
                      .targetAssignmentIntervalPerAttacker[DAT_TroopValueState::instance.attackInfo.attacker]) {
                return;
            }
            DAT_TroopValueState::instance.attackInfo.attackWaveTicker[attackID] = 0;
            DAT_TroopValueState::instance.attackInfo.targetRecomputeCount++;
            if (MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::canKeepReachSignpostZone, DAT_GameState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, playerID, attackID)
                    != FALSE
                && DAT_TroopValueState::instance.attackInfo.attacker != 8) {
                DAT_TroopValueState::instance.attackInfo.attackWaveState[attackID] = 4;
                DAT_TroopValueState::instance.attackInfo.attackWaveTicker[attackID] = 10000;
                DAT_TroopValueState::instance.attackInfo.attackWaveRecomputeStep[attackID] = 0;
                return;
            }
            DAT_TroopValueState::instance.attackInfo.someCounter1++;
            MACRO_CALL_MEMBER(TroopValueState_Func::aiRecomputeAttacks2, this)(0, attackID);
            if (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].minGateLayerValue
                < DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].minHackLayerValue) {
                DAT_TroopValueState::instance.attackInfo.field_0x20f58++;
            }
            if (DAT_TroopValueState::instance.attackInfo.attacker == 8) {
                if (DAT_TroopValueState::instance.attackInfo.someCounter1 >= 10) {
                    DAT_TroopValueState::instance.attackInfo.attackWaveTicker[attackID] = 0;
                    DAT_TroopValueState::instance.attackInfo.attackWaveState[attackID] = 6;
                    MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::handleBattleEndMusicTransition,
                        DAT_SoundSystemState::ptr)();
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::canKeepReachSignpostZone,
                        DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, playerID, attackID)
                        != FALSE
                    && DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].gate2 != 0) {
                    MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                        attackID, 1000, 10000, STBT_0x3f6);
                    MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x3f6, STBT_1, 0, 10);
                }
                if (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].town2 != 0) {
                    MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(attackID, 1000,
                        DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].town2, STBT_0x3f5);
                    MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x3f5, STBT_1, 0, 20);
                }
                MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                    attackID, 1000, DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].hack3, STBT_0x3f2);
                MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x3f2, STBT_1, 0, 10);
                return;
            }
            DAT_TroopValueState::instance.attackInfo.catapultLeadRounds = 0;
            if (DAT_TroopValueState::instance.attackInfo.catapults != 0) {
                DAT_TroopValueState::instance.attackInfo.catapultLeadRounds
                    = DAT_AttackInfoDefinedData::instance
                          .catapultHoldbackRoundsPerAttacker[DAT_TroopValueState::instance.attackInfo.attacker];
                if (DAT_TroopValueState::instance.attackInfo.zoneSize < 3000) {
                    DAT_TroopValueState::instance.attackInfo.catapultLeadRounds += 10;
                }
                MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                    attackID, 1, 10000, STBT_0x401);
                MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x401, STBT_1, 0, 50);
            }
            if (DAT_TroopValueState::instance.attackInfo.lordTargetsAvailable != 0
                && DAT_TroopValueState::instance.attackInfo.targetRecomputeCount
                        - DAT_TroopValueState::instance.attackInfo.catapultLeadRounds
                    > 2) {
                if (DAT_TroopValueState::instance.attackInfo.attacker == 4) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f3c *= 2;
                }
                MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                    attackID, DAT_TroopValueState::instance.attackInfo.field_0x20f3c, 1000, STBT_0x3fd);
                MACRO_CALL_MEMBER(TroopValueState_Func::assignBehaviorTypeToNearbyTribes, this)(STBT_0x3fd, 1, 0, 1);
            }
            if (DAT_TroopValueState::instance.attackInfo.attacker == 3) {
                DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].town2 *= 2;
            }
            if (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].town2 != 0
                && DAT_TroopValueState::instance.attackInfo.targetRecomputeCount
                        - DAT_TroopValueState::instance.attackInfo.catapultLeadRounds
                    > 2) {
                MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(attackID,
                    DAT_TroopValueState::instance.attackInfo.field_0x20f48,
                    DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].town2, STBT_0x3f5);
                MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x3f5, STBT_1, 0, 20);
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::canKeepReachSignpostZoneViaPathfinder,
                    DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, playerID, attackID)
                != FALSE) {
                MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                    attackID, DAT_TroopValueState::instance.attackInfo.field_0x20f44, 10000, STBT_0x3fa);
                MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_7, STBT_1, 10, 20);
            }
            if (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moat2 > 0
                && DAT_TroopValueState::instance.attackInfo.targetRecomputeCount
                        - DAT_TroopValueState::instance.attackInfo.catapultLeadRounds
                    > 2) {
                if (DAT_TroopValueState::instance.attackInfo.attacker == 4) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f4c /= 2;
                }
                MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(attackID,
                    DAT_TroopValueState::instance.attackInfo.field_0x20f4c,
                    DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moat2, STBT_0x3f7);
                MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x3f7, STBT_1, 10, 10);
                DAT_TroopValueState::instance.attackInfo.moatTribesAssignedCount
                    = DAT_TroopValueState::instance.attackInfo.assignedTribeCount;
            }
            MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                attackID, 1000, 10000, STBT_0x418);
            MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x418, STBT_1, 20, 70);
            MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                attackID, 1000, 10000, STBT_0x419);
            MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x419, STBT_1, 20, 70);
            if (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].gate2 != 0) {
                MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                    attackID, 2, 10000, STBT_0x41a);
                MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x41a, STBT_1, 10, 30);
            }
            MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                attackID, 1000, 10000, STBT_0x41b);
            MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x41b, STBT_1, 20, 20);
            if (DAT_TroopValueState::instance.attackInfo.archerPoints > 0
                && DAT_TroopValueState::instance.attackInfo.targetRecomputeCount
                        - DAT_TroopValueState::instance.attackInfo.catapultLeadRounds
                    > extraRounds[0] + 1) {
                DAT_TroopValueState::instance.attackInfo.field_0x21c54++;
                MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                    attackID, DAT_TroopValueState::instance.attackInfo.archerPoints, 10000, STBT_0x3fc);
                MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x3fc, STBT_1, 0, 5);
            }
            if (DAT_TroopValueState::instance.attackInfo.peopleTargetsAvailable != 0) {
                MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(attackID,
                    DAT_TroopValueState::instance.attackInfo.field_0x20f54,
                    DAT_TroopValueState::instance.attackInfo.peopleTargetsAvailable, STBT_0x3fb);
                MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x3fb, STBT_1, 5, 30);
            }
            if (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].gate2 != 0
                && DAT_TroopValueState::instance.attackInfo.targetRecomputeCount
                        - DAT_TroopValueState::instance.attackInfo.catapultLeadRounds
                    > 3) {
                MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                    attackID, DAT_TroopValueState::instance.attackInfo.field_0x20f58, 10000, STBT_0x3f6);
                MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x3f6, STBT_1, 0, 10);
            }
            if (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wide3 != 0
                && DAT_TroopValueState::instance.attackInfo.targetRecomputeCount
                        - DAT_TroopValueState::instance.attackInfo.catapultLeadRounds
                    > 3) {
                MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                    attackID, DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wide3, 10000, STBT_0x413);
                MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x413, STBT_1, 0, 40);
            }
            if (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wide3 != 0) {
                MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                    attackID, DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wide3, 10000, STBT_0x414);
                MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x414, STBT_1, 0, 40);
            }
            MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                attackID, 1000, 10000, STBT_0x411);
            MACRO_CALL_MEMBER(TroopValueState_Func::assignBehaviorTypeAndLinkSupportTribe, this)(
                attackID, playerID, STBT_0x411, 0, 20);
            if (DAT_TroopValueState::instance.attackInfo.aiTribeSizesPerTribeType.aiTroops_L > 5
                && DAT_TroopValueState::instance.attackInfo.targetRecomputeCount
                        - DAT_TroopValueState::instance.attackInfo.catapultLeadRounds
                    > 2) {
                int const scale3 = DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale3;
                if (scale3 > 1) {
                    if (scale3 <= 2) {
                        MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                            attackID, 1, 10000, STBT_0x3f4);
                    } else if (scale3 <= 6) {
                        MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                            attackID, 2, 10000, STBT_0x3f4);
                    } else if (scale3 <= 12) {
                        MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                            attackID, 3, 10000, STBT_0x3f4);
                    } else {
                        MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                            attackID, 4, 10000, STBT_0x3f4);
                    }
                    MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x3f4, STBT_5, 0, 25);
                }
                if (DAT_TroopValueState::instance.attackInfo.moatTribesAssignedCount != 0) {
                    MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                        attackID, DAT_TroopValueState::instance.attackInfo.moatTribesAssignedCount, 10000, STBT_0x3f4);
                    // the original sorts with STBT_0x3f4 but applies STBT_0x3fc (0x520B9C / 0x520BB5)
                    MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x3fc, STBT_1, 0, 20);
                }
            }
            if (DAT_TroopValueState::instance.attackInfo.targetRecomputeCount
                    - DAT_TroopValueState::instance.attackInfo.catapultLeadRounds
                > extraRounds[1] + 4) {
                MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                    attackID, 1000, DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].hack3, STBT_0x3f2);
                MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x3f2, STBT_NONE, 0, 10);
            }
            if (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moat2 > 0
                && DAT_TroopValueState::instance.attackInfo.targetRecomputeCount
                        - DAT_TroopValueState::instance.attackInfo.catapultLeadRounds
                    > 4) {
                MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                    attackID, 1000, DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moat2, STBT_0x3f7);
                MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x3f7, STBT_1, 10, 5);
            }
            if (DAT_TroopValueState::instance.attackInfo.knights != 0
                && DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].gate2 != 0
                && DAT_TroopValueState::instance.attackInfo.targetRecomputeCount
                        - DAT_TroopValueState::instance.attackInfo.catapultLeadRounds
                    > 3) {
                MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                    attackID, 1000, 10000, STBT_0x417);
                // the original sorts with STBT_0x417 but applies STBT_0x3f6 (0x520C65 / 0x520C82)
                MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x3f6, STBT_1, 0, 10);
            }
            MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                attackID, 1000, 10000, STBT_0x41e);
            MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x41e, STBT_1, 10, 40);
        }

    }
}
}
