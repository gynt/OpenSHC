#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00518180
        void TroopValueState::initializeAttackWaveSlot(int waveSlot, int signpostNumber)
        {
            DAT_TroopValueState::instance.attackInfo.attackWaveState[waveSlot] = 0;
            DAT_TroopValueState::instance.attackInfo.attackWaveTicker[waveSlot] = 0;
            DAT_TroopValueState::instance.attackInfo.attackWaveAgeTicks[waveSlot - 1] = 0;
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                10, 0, DAT_TroopValueState::instance.attackInfo.waveSiegeEngineCounts[waveSlot]);
            DAT_TroopValueState::instance.attackInfo.defenseScheduleTick = 0;
            DAT_TroopValueState::instance.attackInfo.counter = 16;
            // field_0x20e00 is declared as undefined1[4] in the header, the original stores an int
            *(int*)DAT_TroopValueState::instance.attackInfo.field_0x20e00 = -1;
            DAT_TroopValueState::instance.attackInfo.breachWarningGate = 0;
            DAT_TroopValueState::instance.attackInfo.buildingDamageEventCount = 0;
            DAT_TroopValueState::instance.attackInfo.enemyUnitsOnKeepCount = 0;
            for (int i = 0; i < 8; ++i) {
                DAT_TroopValueState::instance.attackInfo.playerInfo[i].minGateLayerValue = 0;
                *(int*)DAT_TroopValueState::instance.attackInfo.playerInfo[i].field_0x3ea8 = 0;
            }
            int const randomSignpost
                = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::pickRandomAccessibleSignpostEntry,
                    DAT_GameState::ptr)();
            if (signpostNumber
                    <= MACRO_CALL_MEMBER(
                        OpenSHC::Game::GameStateStructures_Func::countActiveSignposts, DAT_GameState::ptr)()
                && signpostNumber != 0) {
                (&DAT_TroopValueState::instance.attackInfo.attackWaveSignpostIndex)[waveSlot] = signpostNumber - 1;
            } else {
                (&DAT_TroopValueState::instance.attackInfo.attackWaveSignpostIndex)[waveSlot] = randomSignpost;
            }
            DAT_TroopValueState::instance.attackInfo.activeAttackSignpostIndex
                = (&DAT_TroopValueState::instance.attackInfo.attackWaveSignpostIndex)[waveSlot];
        }

    }
}
}
