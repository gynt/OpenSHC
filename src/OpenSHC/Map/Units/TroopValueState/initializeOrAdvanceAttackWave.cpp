#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/WildlifeState.func.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"

#include "OpenSHC/Globals/DAT_AttackInfoDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_WildlifeState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051FF90
        void TroopValueState::initializeOrAdvanceAttackWave(int attackWave)
        {
            if (DAT_TroopValueState::instance.attackInfo.attackWaveTicker[attackWave] == 0) {
                DAT_TroopValueState::instance.attackInfo.attackWaveTicker[attackWave] = 1;
                DAT_TroopValueState::instance.attackInfo.attackWaveMusicPending++;
                DAT_TroopValueState::instance.attackInfo.someCounter1 = 1;
                DAT_TroopValueState::instance.attackInfo.attackAlarmPlayed = 0;
                DAT_TroopValueState::instance.attackInfo.field_0x21c54 = 0;
                MACRO_CALL_MEMBER(TroopValueState_Func::recountAttackTroopValue, this)(1);
                MACRO_CALL_MEMBER(TroopValueState_Func::computeAttackWaveTroopComposition, this)();
                MACRO_CALL_MEMBER(TroopValueState_Func::initializeAttackZoneSearch, this)(attackWave);
                MACRO_CALL_MEMBER(TroopValueState_Func::recountTotalTroopValue, this)();
                MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                    attackWave, 2, 100000, STBT_0x3fb);
                MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x3fe, STBT_1, 0, 50);
                DAT_TroopValueState::instance.attackInfo.casDis = MACRO_CALL_MEMBER(
                    OpenSHC::Map::WildlifeState_Func::getDistanceFromAttackSignpostToZoneProximity,
                    DAT_WildlifeState::ptr)();
                MACRO_CALL_MEMBER(TribesState_Func::applyTribeBehaviorType, DAT_TribesState::ptr)(attackWave, STBT_3);
            }
            if ((char)DAT_TroopValueState::instance.attackInfo.nofStationaryTribesPerWave[attackWave]
                < (char)DAT_TroopValueState::instance.attackInfo.waveTribeCountThisTick[attackWave] - 5) {
                return;
            }
            DAT_TroopValueState::instance.attackInfo.attackWaveTicker[attackWave]++;
            if (DAT_TroopValueState::instance.attackInfo.attackWaveTicker[attackWave]
                < DAT_AttackInfoDefinedData::instance
                      .attackWaveInitTicksPerAttacker[DAT_TroopValueState::instance.attackInfo.attacker]) {
                return;
            }
            if (DAT_TroopValueState::instance.attackInfo.attacker == 8) {
                MACRO_CALL_MEMBER(TroopValueState_Func::playAttackAlarmSound, this)();
                DAT_TroopValueState::instance.attackInfo.attackWaveTicker[attackWave] = 10000;
                DAT_TroopValueState::instance.attackInfo.attackWaveState[attackWave] = 3;
                DAT_TroopValueState::instance.attackInfo.targetRecomputeCount = 0;
                return;
            }
            DAT_TroopValueState::instance.attackInfo.attackWaveState[attackWave] = 1;
            DAT_TroopValueState::instance.attackInfo.attackWaveTicker[attackWave] = 0;
        }

    }
}
}
