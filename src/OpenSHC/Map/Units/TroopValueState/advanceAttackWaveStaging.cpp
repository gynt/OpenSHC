#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"

#include "OpenSHC/Globals/DAT_AttackInfoDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051D690
        void TroopValueState::advanceAttackWaveStaging(int attackWave)
        {
            DAT_TroopValueState::instance.attackInfo.attackAlarmPlayed = 0;
            DAT_TroopValueState::instance.attackInfo.attackWaveState[attackWave] = 2;
            DAT_TroopValueState::instance.attackInfo.attackWaveTicker[attackWave] = 0;
            MACRO_CALL_MEMBER(
                OpenSHC::Game::GameStateStructures_Func::collectReachableLocationsFromFirstNofFPoint, DAT_GameState::ptr)();
            DAT_TroopValueState::instance.attackInfo.someCounter1++;
            MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                attackWave, 2, 100000, STBT_0x3fb);
            MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_0x3fe, STBT_5, 0, 50);
            if (DAT_TroopValueState::instance.attackInfo.casDis
                >= DAT_AttackInfoDefinedData::instance
                       .castleDistanceThresholdPerAttacker[DAT_TroopValueState::instance.attackInfo.attacker]) {
                MACRO_CALL_MEMBER(TroopValueState_Func::collectWaveTribesSortedByTypePriority, this)(
                    attackWave, 1000, 10000, STBT_5);
                MACRO_CALL_MEMBER(TroopValueState_Func::applyTribeBehaviorTypes, this)(STBT_5, STBT_1, 0, 40);
            }
        }

    }
}
}
