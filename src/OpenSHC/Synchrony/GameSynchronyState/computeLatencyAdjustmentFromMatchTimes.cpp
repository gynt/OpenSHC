#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_ProtocolDefinedData.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047E5B0
    void GameSynchronyState::computeLatencyAdjustmentFromMatchTimes(int param_1)
    {
        GameSynchronyState* _gameSynchronyState;
        int (*paiVar1)[3];
        int iVar2;
        int iVar3;
        this->field310_0x109e98 = -1;
        this->mapTimeInTicksSinglePlayer = -1;
        _gameSynchronyState = (GameSynchronyState*)this->matchTimesArray;
        iVar3 = 2;
        do {
            if (_gameSynchronyState->currentPlayerFullIDArray[1] != -1) {
                if (_gameSynchronyState->matchTimesArray[0] == -1) {
                    _gameSynchronyState->matchTimesArray[0] = DAT_GameCore::instance.mapTimeInTicks;
                }
                if (this->field310_0x109e98 == -1) {
                    iVar2 = _gameSynchronyState->matchTimesArray[0];
                    this->field310_0x109e98 = iVar2;
                } else {
                    if (_gameSynchronyState->matchTimesArray[0] < this->field310_0x109e98) {
                        this->field310_0x109e98 = _gameSynchronyState->matchTimesArray[0];
                    }
                    iVar2 = _gameSynchronyState->matchTimesArray[0];
                    if (iVar2 <= this->mapTimeInTicksSinglePlayer)
                        goto LAB_0047e614;
                }
                this->mapTimeInTicksSinglePlayer = iVar2;
            }
        LAB_0047e614:
            if (_gameSynchronyState->currentPlayerFullIDArray[2] != -1) {
                if (_gameSynchronyState->matchTimesArray[1] == -1) {
                    _gameSynchronyState->matchTimesArray[1] = DAT_GameCore::instance.mapTimeInTicks;
                }
                if (this->field310_0x109e98 == -1) {
                    iVar2 = _gameSynchronyState->matchTimesArray[1];
                    this->field310_0x109e98 = iVar2;
                } else {
                    if (_gameSynchronyState->matchTimesArray[1] < this->field310_0x109e98) {
                        this->field310_0x109e98 = _gameSynchronyState->matchTimesArray[1];
                    }
                    iVar2 = _gameSynchronyState->matchTimesArray[1];
                    if (iVar2 <= this->mapTimeInTicksSinglePlayer)
                        goto LAB_0047e65d;
                }
                this->mapTimeInTicksSinglePlayer = iVar2;
            }
        LAB_0047e65d:
            if (_gameSynchronyState->currentPlayerFullIDArray[3] != -1) {
                if (_gameSynchronyState->matchTimesArray[2] == -1) {
                    _gameSynchronyState->matchTimesArray[2] = DAT_GameCore::instance.mapTimeInTicks;
                }
                if (this->field310_0x109e98 == -1) {
                    iVar2 = _gameSynchronyState->matchTimesArray[2];
                    this->field310_0x109e98 = iVar2;
                } else {
                    if (_gameSynchronyState->matchTimesArray[2] < this->field310_0x109e98) {
                        this->field310_0x109e98 = _gameSynchronyState->matchTimesArray[2];
                    }
                    iVar2 = _gameSynchronyState->matchTimesArray[2];
                    if (iVar2 <= this->mapTimeInTicksSinglePlayer)
                        goto LAB_0047e6a6;
                }
                this->mapTimeInTicksSinglePlayer = iVar2;
            }
        LAB_0047e6a6:
            if (_gameSynchronyState->currentPlayerFullIDArray[4] != -1) {
                if (_gameSynchronyState->matchTimesArray[3] == -1) {
                    _gameSynchronyState->matchTimesArray[3] = DAT_GameCore::instance.mapTimeInTicks;
                }
                if (this->field310_0x109e98 == -1) {
                    iVar2 = _gameSynchronyState->matchTimesArray[3];
                    this->field310_0x109e98 = iVar2;
                } else {
                    if (_gameSynchronyState->matchTimesArray[3] < this->field310_0x109e98) {
                        this->field310_0x109e98 = _gameSynchronyState->matchTimesArray[3];
                    }
                    iVar2 = _gameSynchronyState->matchTimesArray[3];
                    if (iVar2 <= this->mapTimeInTicksSinglePlayer)
                        goto LAB_0047e6ef;
                }
                this->mapTimeInTicksSinglePlayer = iVar2;
            }
        LAB_0047e6ef:
            _gameSynchronyState = (GameSynchronyState*)(_gameSynchronyState->matchTimesArray + 4);
            iVar3 = iVar3 + -1;
            if (iVar3 == 0) {
                this->field313_0x109ea4 = this->mapTimeInTicksSinglePlayer - this->field310_0x109e98;
                this->field312_0x109ea0 = this->matchTimesArray[param_1 + -1];
                iVar3 = 0;
                this->field314_0x109ea8 = 0;
                this->field315_0x109eac = 0;
                if (this->field312_0x109ea0 == this->field310_0x109e98) {
                    this->field315_0x109eac = this->field312_0x109ea0 - this->mapTimeInTicksSinglePlayer;
                } else {
                    this->field314_0x109ea8 = this->field312_0x109ea0 - this->field310_0x109e98;
                }
                if (this->field315_0x109eac < 0) {
                    this->field318_0x109eb8 = 1;
                    iVar3 = 0;
                    do {
                        if (DAT_ProtocolDefinedData::instance.field4_0x4[iVar3][0] < this->field315_0x109eac) {
                            this->field318_0x109eb8 = DAT_ProtocolDefinedData::instance.field4_0x4[iVar3][1];
                        }
                        iVar3 = iVar3 + 1;
                    } while (iVar3 < 0xc);
                }
                paiVar1 = DAT_ProtocolDefinedData::instance.field5_0x64;
                do {
                    if (this->field314_0x109ea8 <= (*paiVar1)[0]) {
                        this->field316_0x109eb0 = DAT_ProtocolDefinedData::instance.field5_0x64[iVar3][1];
                        this->field317_0x109eb4 = DAT_ProtocolDefinedData::instance.field5_0x64[iVar3][2];
                    }
                    paiVar1 = paiVar1 + 1;
                    iVar3 = iVar3 + 1;
                } while ((int)paiVar1 < 0xb38dc0);
            }
        } while (true);
    }

}
}
