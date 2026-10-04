#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace Synchrony {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0047DA70
    void GameSynchronyState::setDPlaySessionNameValue()
    {
        char* pcVar1;
        char local_100[252];
        uint local_4;
        local_4 = MSVC_SecurityCookie::instance ^ (uint)local_100;
        if (this->useTCPIP != FALSE) {
            MACRO_CALL(Global_Func::PrintToDestination)(this->DPLAYX_SessionName, L"Crusader");
            ;
        }
        pcVar1 = MACRO_CALL_MEMBER(
            Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(0);
        MACRO_CALL(OS_Func::_sprintf)(local_100, "Stronghold-%s", pcVar1);
        MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::multiByteToWideCharacter,
            DAT_WideCharMultiByteState::ptr)(this->DPLAYX_SessionName, (LPCSTR)((int)(local_100)));
        ;
    }

}
}
