#include "../Helpers.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Commands::GameCommandType;
    using OpenSHC::DE::SHCDE::eTextSections;

    // FUNCTION: STRONGHOLDCRUSADER 0x00429650
    void Helpers::CallbackSetMultiplayerSpeedLevel()
    {
        char* pcVar1;
        int iVar2;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
            OpenSHC::Commands::GCT_CHANGE_GAME_INTENSITY_OR_BALANCE);
        DAT_GameSynchronyState::instance.field235_0x1072e8 = -1;
        DAT_GameSynchronyState::instance.field236_0x1072ec = -1;
        iVar2 = DAT_GameSynchronyState::instance.skirmishGameSpeedLevel;
        /*
          added by script: "Game Speed"
         */
        pcVar1 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x52);
        MACRO_CALL(OpenSHC::OS_Func::_sprintf)(
            DAT_GameSynchronyState::instance.receivedChatMessage, "%s :%d", pcVar1, iVar2);
        MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(
            DAT_GameSynchronyState::instance.receivedChatMessage);
        DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[0] = 1;
        DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[1] = 1;
        DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[2] = 1;
        DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[3] = 1;
        DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[4] = 1;
        DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[5] = 1;
        DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[6] = 1;
        DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[7] = 1;
        DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[8] = 1;
        DAT_GameSynchronyState::instance
            .DAT_ChatMessageReceiverArray[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 0;
        DAT_GameSynchronyState::instance.DAT_ChatTauntOrMessage = 10000;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
            OpenSHC::Commands::GCT_TAUNT_OR_CHAT);
        MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::clearEntry, DAT_UserTextHandlerState::ptr)(
            DAT_UserTextHandlerState::instance.textArrayIndex);
    }

}
}
