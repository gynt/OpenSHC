#include "../../Synchrony.func.hpp"
#include "../Commands.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Commands::GameCommandParameterLocation;
    using OpenSHC::Commands::GameCommandParameterReadWrite;
    using OpenSHC::Commands::GameCommandScheduling;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      called in multiplayer: code 0xC   decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00480B10
    void Commands::CommandCheckSync()
    {
        int iVar1;
        GameCommandParameterReadWrite destSwitch;
        DAT_GameSynchronyState::instance.DAT_CommandSize = 10;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.DAT_LagIndicatorPerPlayer
                    + DAT_GameSynchronyState::instance.currentPlayerSlotID,
                2, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                DAT_GameSynchronyState::instance.HASH_HashTotal + DAT_GameSynchronyState::instance.currentPlayerSlotID,
                4, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            destSwitch = OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1;
            iVar1 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        } else {
            if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE) {}
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.DAT_LagIndicatorPerPlayer
                    + DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                2, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_HashTotal
                    + DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                4, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            destSwitch = OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1;
            iVar1 = DAT_GameSynchronyState::instance.protocolInvokerPlayerID;
        }
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.DAT_PlayerMatchTimes + iVar1, 4,
            OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, destSwitch);
    }

}
}
