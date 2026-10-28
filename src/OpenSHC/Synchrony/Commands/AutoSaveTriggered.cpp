#include "../../Synchrony.func.hpp"
#include "../Commands.func.hpp"

#include "OpenSHC/IO.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/IO/Base64State.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Commands::GameCommandParameterLocation;
    using OpenSHC::Commands::GameCommandParameterReadWrite;
    using OpenSHC::Commands::GameCommandScheduling;
    using OpenSHC::IO::Base64State;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00489880
    void Commands::ExecuteSaveGameCommand()
    {
        int iVar2;
        undefined1 auStack_5c[3];
        char local_59;
        Base64State _base64State;
        WCHAR local_4c[36];
        DAT_GameSynchronyState::instance.DAT_CommandSize = 0x4b;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam1, 4,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam2, 1,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
            MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::multiByteToWideCharWithSize,
                DAT_WideCharMultiByteState::ptr)(
                local_4c, (LPCSTR)((int)(DAT_GameSynchronyState::instance.shortMapName)), (int)((int)(33)));
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(local_4c, (size_t)((int)(66)),
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
            iVar2 = 1;
            do {
                if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar2] == -1)
                    || (iVar2 == DAT_GameSynchronyState::instance.currentPlayerSlotID)) {
                    DAT_GameSynchronyState::instance.announcementReceivedByPlayer[iVar2] = 1;
                } else {
                    DAT_GameSynchronyState::instance.announcementReceivedByPlayer[iVar2] = 0;
                }
                iVar2 = iVar2 + 1;
            } while (iVar2 < 9);
            ;
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam1, 4,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&local_59, 1, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
            DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = (int)local_59;
            if (DAT_GameSynchronyState::instance.isHost != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(local_4c, 0x42, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
                MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::wideCharToMultiByteWithSize,
                    DAT_WideCharMultiByteState::ptr)(DAT_GameSynchronyState::instance.shortMapName, local_4c, 1000);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(local_4c, 0x42, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
                MACRO_CALL(OpenSHC::IO_Func::Base64EncodeInit)(&_base64State);
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_IntegerValue, DAT_LowLevelMemory::ptr)(
                    120, 0, (void*)((int)(DAT_GameSynchronyState::instance.shortMapName)));
                MACRO_CALL(OpenSHC::IO_Func::Base64Encode)((char*)local_4c, (int)(wcslen(local_4c) * 2),
                    (char*)((int)(DAT_GameSynchronyState::instance.shortMapName)), &_base64State);
            }
            DAT_GameSynchronyState::instance.savedMapTimeInTicks
                = DAT_GameSynchronyState::instance.DAT_GameCommandParam0;
            DAT_GameSynchronyState::instance.savedUnitsCRC32Hash
                = DAT_GameSynchronyState::instance.DAT_GameCommandParam1;
            MACRO_CALL(OpenSHC::UI::Helpers_Func::ShowProgressBarSaveLoadDialog)(
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2);
            DAT_GameSynchronyState::instance.lastSaveTimeMs = timeGetTime();
            DAT_GameSynchronyState::instance.saveRelated = 1;
            if (DAT_GameSynchronyState::instance.isHost == FALSE) {
                DAT_GameSynchronyState::instance.shouldSendSaveAck = 1;
            } else {
                DAT_GameSynchronyState::instance.announcementReceiveTime = timeGetTime();
                DAT_GameSynchronyState::instance.announcementReceivedBool = FALSE;
            }
        };
    }

}
}
