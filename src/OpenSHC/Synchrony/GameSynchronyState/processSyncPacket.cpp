#include "../../Synchrony.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00488010
    void GameSynchronyState::processSyncPacket(int param_1)
    {
        int iVar1;
        uint _player;
        int iVar2;
        uint _difference;
        int _absoluteDifference;
        int _newDiff2;
        uint _min1IfNegative;
        int _newDiff;
        int _countDown;
        _player = MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::translateMultiplayerIDsIntoPlayerIDs,
            this)(this->DPLAYX_ReceivedPlayerID);
        this->matchTimesArray[_player - 1]
            = this->receivedCommandMapTimeInTicks + this->connectionLagInfoArray[_player].average1;
        _countDown = this->commandDelay;
        iVar2 = (char)this->DPLAY_ReceiveData.packet.payload[0] + 10;
        if ((this->commandDelay < iVar2)
            && (iVar1 = this->commandDelay + 5, this->commandDelay = iVar2, iVar1 <= iVar2)) {
            this->commandDelay = iVar1;
        }
        _difference = (DAT_GameCore::instance.mapTimeInTicks - this->receivedCommandMapTimeInTicks)
            - this->connectionLagInfoArray[_player].average1;
        _min1IfNegative = (int)_difference >> 0x1f;
        _absoluteDifference = (_difference ^ _min1IfNegative) - _min1IfNegative;
        if (this->clTimeDiff < _absoluteDifference) {
            _newDiff = this->clTimeDiff + 5;
            if (_newDiff <= _absoluteDifference) {
                _absoluteDifference = _newDiff;
            }
            this->clTimeDiff = _absoluteDifference;
            if (0x2d < _absoluteDifference) {
                this->clTimeDiff = 45;
            }
        }
        _newDiff2 = this->clTimeDiff + 10;
        if ((this->commandDelay < _newDiff2) && (this->commandDelay = _newDiff2, _countDown + 5 <= _newDiff2)) {
            this->commandDelay = _countDown + 5;
        }
        if (this->syncRelatedCountdown != 0) {
            this->commandDelay = 1;
        }
    }

}
}
