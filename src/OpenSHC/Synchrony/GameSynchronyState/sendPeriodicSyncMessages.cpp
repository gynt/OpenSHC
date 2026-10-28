#include "../GameSynchronyState.func.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0048C750
    void GameSynchronyState::sendPeriodicSyncMessages()
    {
        DWORD _now = timeGetTime();
        if (1800 < (int)(_now - this->lastPingSendTime)) {
            this->lastPingSendTime = _now;
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendSyncPacket126, this)();
        }
        if (180 <= (int)(_now - this->lastSyncMessageTime)) {
            this->lastSyncMessageTime = _now;
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendSomeMultiplayerSyncMessageWithType, this)(0);
            if (0 < this->syncRelatedCountdown) {
                --this->syncRelatedCountdown;
            }
        }
    }

}
}
