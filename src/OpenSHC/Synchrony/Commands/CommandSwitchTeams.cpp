#include "../../Synchrony.func.hpp"
#include "../Commands.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Commands::GameCommandParameterLocation;
    using OpenSHC::Commands::GameCommandParameterReadWrite;
    using OpenSHC::Commands::GameCommandScheduling;
    using OpenSHC::DE::SHCDE::eTextSections;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0048ACB0
    void Commands::CommandSwitchTeams()
    {
        char c;
        char* text;
        char* dest;
        int teamCount;
        short param[2];
        int teamCounts[9];
        DAT_GameSynchronyState::instance.DAT_CommandSize = 3;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 2,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam1, 1,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_WRITE_VAR_TO_STREAM);
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE) {
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(param, 2, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = (int)param[0];
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(param, 1, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_READ_STREAM_TO_VAR);
        DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = (int)(char)param[0];
        if (DAT_GameSynchronyState::instance.DAT_GameCommandParam1 == 0) {
            if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                return;
            }
            teamCount = 0;
            teamCounts[1] = 0;
            teamCounts[2] = 0;
            teamCounts[3] = 0;
            teamCounts[4] = 0;
            teamCounts[5] = 0;
            teamCounts[6] = 0;
            teamCounts[7] = 0;
            teamCounts[8] = 0;
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[1] != -1) {
                teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[1]]
                    = teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[1]] + 1;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[2] != -1) {
                teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[2]]
                    = teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[2]] + 1;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[3] != -1) {
                teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[3]]
                    = teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[3]] + 1;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[4] != -1) {
                teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[4]]
                    = teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[4]] + 1;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[5] != -1) {
                teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[5]]
                    = teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[5]] + 1;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[6] != -1) {
                teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[6]]
                    = teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[6]] + 1;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[7] != -1) {
                teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[7]]
                    = teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[7]] + 1;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[8] != -1) {
                teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[8]]
                    = teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[8]] + 1;
            }
            if (teamCounts[1] != 0) {
                teamCount = teamCount + 1;
            }
            if (teamCounts[2] != 0) {
                teamCount = teamCount + 1;
            }
            if (teamCounts[3] != 0) {
                teamCount = teamCount + 1;
            }
            if (teamCounts[4] != 0) {
                teamCount = teamCount + 1;
            }
            if (teamCounts[5] != 0) {
                teamCount = teamCount + 1;
            }
            if (teamCounts[6] != 0) {
                teamCount = teamCount + 1;
            }
            if (teamCounts[7] != 0) {
                teamCount = teamCount + 1;
            }
            if (teamCounts[8] != 0) {
                teamCount = teamCount + 1;
            }
            if ((teamCount > 2) || (teamCounts[DAT_GameSynchronyState::instance.protocolInvokerPlayerID] != 1)) {
                DAT_GameSynchronyState::instance
                    .allianceRequestTime[DAT_GameSynchronyState::instance.protocolInvokerPlayerID]
                    = timeGetTime();
                /*
                  "Wishes to become an ally"   added by script: "wishes to become an ally."
                 */
                text = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x25);
                dest = DAT_GameSynchronyState::instance.receivedChatMessage;
                do {
                    c = *text;
                    *dest = c;
                    text = text + 1;
                    dest = dest + 1;
                } while (c != '\0');
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                    0);
            }
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_GameCommandParam1 == 2) {
            teamCounts[1] = 0;
            teamCounts[2] = 0;
            teamCounts[3] = 0;
            teamCounts[4] = 0;
            teamCounts[5] = 0;
            teamCounts[6] = 0;
            teamCounts[7] = 0;
            teamCounts[8] = 0;
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[1] != -1) {
                teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[1]] = 1;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[2] != -1) {
                teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[2]] = 1;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[3] != -1) {
                teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[3]] = 1;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[4] != -1) {
                teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[4]] = 1;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[5] != -1) {
                teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[5]] = 1;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[6] != -1) {
                teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[6]] = 1;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[7] != -1) {
                teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[7]] = 1;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[8] != -1) {
                teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[8]] = 1;
            }
            for (int teamSlot = 1; teamSlot < 9; teamSlot++) {
                if (teamCounts[teamSlot] == 0) {
                    DAT_GameState::instance.mapAndTime
                        .playerTeams[DAT_GameSynchronyState::instance.protocolInvokerPlayerID] = teamSlot;
                    break;
                }
            }
            /*
              "has cancelled the alliance"   added by script: "has cancelled the alliance"
             */
            text = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x27);
            dest = DAT_GameSynchronyState::instance.receivedChatMessage;
            do {
                c = *text;
                *dest = c;
                text = text + 1;
                dest = dest + 1;
            } while (c != '\0');
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                0);
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_GameCommandParam1 == 1) {
            int canJoin = 0;
            teamCount = 0;
            teamCounts[1] = 0;
            teamCounts[2] = 0;
            teamCounts[3] = 0;
            teamCounts[4] = 0;
            teamCounts[5] = 0;
            teamCounts[6] = 0;
            teamCounts[7] = 0;
            teamCounts[8] = 0;
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[1] != -1) {
                teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[1]]
                    = teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[1]] + 1;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[2] != -1) {
                teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[2]]
                    = teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[2]] + 1;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[3] != -1) {
                teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[3]]
                    = teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[3]] + 1;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[4] != -1) {
                teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[4]]
                    = teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[4]] + 1;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[5] != -1) {
                teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[5]]
                    = teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[5]] + 1;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[6] != -1) {
                teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[6]]
                    = teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[6]] + 1;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[7] != -1) {
                teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[7]]
                    = teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[7]] + 1;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[8] != -1) {
                teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[8]]
                    = teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[8]] + 1;
            }
            if (teamCounts[1] != 0) {
                teamCount = teamCount + 1;
            }
            if (teamCounts[2] != 0) {
                teamCount = teamCount + 1;
            }
            if (teamCounts[3] != 0) {
                teamCount = teamCount + 1;
            }
            if (teamCounts[4] != 0) {
                teamCount = teamCount + 1;
            }
            if (teamCounts[5] != 0) {
                teamCount = teamCount + 1;
            }
            if (teamCounts[6] != 0) {
                teamCount = teamCount + 1;
            }
            if (teamCounts[7] != 0) {
                teamCount = teamCount + 1;
            }
            if (teamCounts[8] != 0) {
                teamCount = teamCount + 1;
            }
            int target = DAT_GameSynchronyState::instance.DAT_GameCommandParam0;
            if ((teamCount > 2) || (teamCounts[target] != 1)) {
                canJoin = 1;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::countPlayersInSameTeam,
                    DAT_GameSynchronyState::ptr)(target)
                <= 1) {
                int invoker = DAT_GameSynchronyState::instance.protocolInvokerPlayerID;
                if ((MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::countPlayersInSameTeam,
                         DAT_GameSynchronyState::ptr)(invoker)
                        <= 1)
                    && (canJoin)) {
                    DAT_GameState::instance.mapAndTime.playerTeams[target]
                        = DAT_GameState::instance.mapAndTime.playerTeams[invoker];
                    /*
                      "has joined with"   added by script: "has joined with"
                     */
                    text = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x26);
                    dest = DAT_GameSynchronyState::instance.receivedChatMessage;
                    do {
                        c = *text;
                        *dest = c;
                        text = text + 1;
                        dest = dest + 1;
                    } while (c != '\0');
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                        DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.DAT_GameCommandParam0,
                        DAT_GameSynchronyState::instance.protocolInvokerPlayerID);
                }
            }
        }
    }

}
}
