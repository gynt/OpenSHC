#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_ProtocolDefinedData.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047E5B0
    void GameSynchronyState::computeLatencyAdjustmentFromMatchTimes(int param_1)
    {
        int _player;
        int (*paiVar1)[3];
        int iVar2;
        int iVar3;
        this->minPlayerMapTime = -1;
        this->mapTimeInTicksSinglePlayer = -1;
        for (_player = 1; _player < 9; _player = _player + 1) {
            if (this->currentPlayerFullIDArray[_player] != -1) {
                if (this->matchTimes[_player] == -1) {
                    this->matchTimes[_player] = DAT_GameCore::instance.mapTimeInTicks;
                }
                if ((int)this->minPlayerMapTime == -1) {
                    iVar2 = this->matchTimes[_player];
                    this->minPlayerMapTime = iVar2;
                } else {
                    if (this->matchTimes[_player] < (int)this->minPlayerMapTime) {
                        this->minPlayerMapTime = this->matchTimes[_player];
                    }
                    iVar2 = this->matchTimes[_player];
                    if (iVar2 <= (int)this->mapTimeInTicksSinglePlayer)
                        continue;
                }
                this->mapTimeInTicksSinglePlayer = iVar2;
            }
        }
        this->playerMapTimeSpread = this->mapTimeInTicksSinglePlayer - this->minPlayerMapTime;
        this->localPlayerMapTime = this->matchTimes[param_1];
        iVar3 = 0;
        this->ticksAheadOfSlowestPlayer = 0;
        this->ticksBehindFastestPlayer = 0;
        if (this->localPlayerMapTime == this->minPlayerMapTime) {
            this->ticksBehindFastestPlayer = this->localPlayerMapTime - this->mapTimeInTicksSinglePlayer;
        } else {
            this->ticksAheadOfSlowestPlayer = this->localPlayerMapTime - this->minPlayerMapTime;
        }
        if ((int)this->ticksBehindFastestPlayer < 0) {
            this->field317_0x109eb8 = 1;
            for (iVar3 = 0; iVar3 < 0xc; iVar3 = iVar3 + 1) {
                if ((int)this->ticksBehindFastestPlayer
                    > DAT_ProtocolDefinedData::instance.field4_0x4[iVar3][0]) {
                    this->field317_0x109eb8 = DAT_ProtocolDefinedData::instance.field4_0x4[iVar3][1];
                    return;
                }
            }
            return;
        }
        for (iVar3 = 0; iVar3 < 40; iVar3 = iVar3 + 1) {
            if ((int)this->ticksAheadOfSlowestPlayer
                <= DAT_ProtocolDefinedData::instance.field5_0x64[iVar3][0]) {
                this->field315_0x109eb0 = DAT_ProtocolDefinedData::instance.field5_0x64[iVar3][1];
                this->field316_0x109eb4 = DAT_ProtocolDefinedData::instance.field5_0x64[iVar3][2];
                return;
            }
        }
        return;
    }

}
}
