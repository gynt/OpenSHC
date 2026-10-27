#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_AttackInfoDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00520450
        void TroopValueState::updateInProgressAttackWave(int attackID)
        {
            int const playerID = (char)DAT_TroopValueState::instance.attackInfo.attackWavePlayerIDArray[attackID];
            if (MACRO_CALL_MEMBER(TroopValueState_Func::isLessThanPercentageOfTribesInAttackDying, this)(attackID, 50)
                    != FALSE
                && DAT_TroopValueState::instance.attackInfo.attackAlarmPlayed == 0) {
                MACRO_CALL_MEMBER(TroopValueState_Func::playAttackAlarmSound, this)();
            }
            if (DAT_TroopValueState::instance.attackInfo.attackAlarmPlayed == 0) {
                return;
            }
            if (DAT_TroopValueState::instance.attackInfo.attackWaveTicker[attackID] == 0) {
                DAT_TroopValueState::instance.attackInfo.someCounter1++;
                MACRO_CALL_MEMBER(TroopValueState_Func::aiRecomputeAttacks2, this)(1, attackID);
                if (DAT_TroopValueState::instance.attackInfo.tentPoints > 0) {
                    MACRO_CALL_MEMBER(TroopValueState_Func::placeSiegeTentsAndAssignEngineers, this)(attackID, 1);
                    MACRO_CALL_MEMBER(TroopValueState_Func::placeTunnelForEveryTunneler, this)(attackID);
                } else {
                    MACRO_CALL_MEMBER(TroopValueState_Func::placeSiegeTentsAndAssignEngineers, this)(attackID, 0);
                }
                int const town2 = DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].town2;
                if (town2 != 0) {
                    MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                        attackID, 2, town2, STBT_0x3f5);
                    MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x3f5, STBT_1, 0, 20);
                }
                int const peopleTargets = DAT_TroopValueState::instance.attackInfo.peopleTargetsAvailable;
                if (peopleTargets != 0) {
                    MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                        attackID, 2, peopleTargets, STBT_0x3fb);
                    MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x3fb, STBT_1, 5, 30);
                }
            }
            DAT_TroopValueState::instance.attackInfo.attackWaveTicker[attackID]++;
            if (DAT_TroopValueState::instance.attackInfo.attackWaveTicker[attackID]
                < DAT_AttackInfoDefinedData::instance
                      .AttackWaveDurationPerAttacker[DAT_TroopValueState::instance.attackInfo.attacker]) {
                return;
            }
            DAT_TroopValueState::instance.attackInfo.attackWaveTicker[attackID] = 10000;
            DAT_TroopValueState::instance.attackInfo.attackWaveState[attackID] = 3;
            DAT_TroopValueState::instance.attackInfo.targetRecomputeCount = 0;
            if (DAT_GameCore::instance.missionNumber == 39 && DAT_TroopValueState::instance.attackInfo.attacker == 4) {
                // "we are the macemen"
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(s_Mace_s4_wav_005abb68);
            }
        }

    }
}
}
