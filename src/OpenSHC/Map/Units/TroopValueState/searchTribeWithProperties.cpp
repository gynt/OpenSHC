#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x005182A0
        BOOLEnum TroopValueState::searchTribeWithProperties(int waveSlot)
        {
            if (DAT_TroopValueState::instance.attackInfo.waveTribeCountThisTick[waveSlot] == 0) {
                return FALSE;
            }
            int playerID = 0;
            for (int i = 1; i < 1250; ++i) {
                if (DAT_TribesState::instance.tribes[i].tribeState == 2
                    && DAT_TribesState::instance.tribes[i].owner != 0
                    && DAT_TribesState::instance.tribes[i].owner
                        != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    playerID = DAT_TribesState::instance.tribes[i].owner;
                    break;
                }
            }
            if (playerID == 0) {
                DAT_TroopValueState::instance.attackInfo.waveTribeCountThisTick[waveSlot] = 0;
                DAT_TroopValueState::instance.attackInfo.nofStationaryTribesPerWave[waveSlot] = 0;
                return FALSE;
            }
            DAT_TroopValueState::instance.attackInfo.attackWavePlayerIDArray[waveSlot] = playerID;
            DAT_TroopValueState::instance.attackInfo.attacker = (char)playerID;
            DAT_TroopValueState::instance.attackInfo.attackWaveTicker[waveSlot] = 10000;
            DAT_TroopValueState::instance.attackInfo.attackWaveState[waveSlot] = 3;
            DAT_TroopValueState::instance.attackInfo.targetRecomputeCount = 10;
            return TRUE;
        }

    }
}
}
