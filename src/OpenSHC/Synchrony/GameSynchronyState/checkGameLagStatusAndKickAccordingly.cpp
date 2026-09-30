#include "../../Synchrony.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Commands::GameCommandType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0048F4C0
    void GameSynchronyState::checkGameLagStatusAndKickAccordingly()
    {
        int* piVar1;
        DWORD _now2;
        DWORD _now1;
        int _player;
        piVar1 = DAT_GameSynchronyState::instance.announcementReceivedByPlayer + 1;
        while (*piVar1 != 0) {
            piVar1 = piVar1 + 1;
            if (0x191e423 < (int)piVar1) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, this)(
                    OpenSHC::Commands::GCT_CLOSE_MODAL_DIALOG_FOR_ALL);
            }
        }
        if (DAT_GameSynchronyState::instance.announcementReceivedBool == FALSE) {
            _now1 = timeGetTime();
            if (_now1 - DAT_GameSynchronyState::instance.announcementReceiveTime < 45000) {}
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 0;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, this)(
                OpenSHC::Commands::GCT_KILL_GAME);
        }
        _now2 = timeGetTime();
        if (_now2 - DAT_GameSynchronyState::instance.announcementReceiveTime < 45000) {}
        _player = 1;
        piVar1 = DAT_GameSynchronyState::instance.receivedSyncStatusByPlayerUnk;
        do {
            piVar1 = piVar1 + 1;
            if (DAT_GameSynchronyState::instance.announcementReceivedByPlayer[_player] == 0) {
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 63;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = _player;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, this)(
                    OpenSHC::Commands::GCT_LEAVE_GAME);
                *piVar1 = 2;
            }
            _player = _player + 1;
        } while (_player < 9);
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, this)(
            OpenSHC::Commands::GCT_CLOSE_MODAL_DIALOG_FOR_ALL);
    }

}
}
