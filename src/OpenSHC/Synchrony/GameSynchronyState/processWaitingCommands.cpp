#include "../../Synchrony.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/Commands/GameCommandState.hpp"

#include "OpenSHC/Globals/DAT_ProtocolDefinedData.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Commands::GameCommandScheduling;
    using OpenSHC::Commands::GameCommandState;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004892F0
    void GameSynchronyState::processWaitingCommands()
    {
        int _gameCommandID;
        int (*paiVar1)[2];
        _gameCommandID = MACRO_CALL_MEMBER(
            OpenSHC::Synchrony::GameSynchronyState_Func::getCommandIDFromCommandSelectionStuff, this)();
        if ((_gameCommandID != 0) && (_gameCommandID = 0, 0 < this->MBR_someIndex)) {
            paiVar1 = this->MBR_SelectedGameCommands;
            do {
                /*
                  process all commands that should have been executed by now
                 */
                this->DAT_CurrentGameCommandID = (*paiVar1)[0];
                this->protocolInvokerPlayerID = MACRO_CALL_MEMBER(
                    OpenSHC::Synchrony::GameSynchronyState_Func::translateMultiplayerIDsIntoPlayerIDs, this)(
                    this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].playerUnk);
                this->DAT_GameCommandParam5 = 0;
                this->DAT_GameCommandParam4 = 0;
                this->DAT_GameCommandParam3 = 0;
                this->DAT_GameCommandParam2 = 0;
                this->DAT_GameCommandParam1 = 0;
                this->DAT_GameCommandParam0 = 0;
                this->DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
                this->DAT_CommandParameterOffset = 0;
                ((void (*)())DAT_ProtocolDefinedData::instance
                        .commandFunctions[this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].commandType
                            + 0x15])();
                _gameCommandID = _gameCommandID + 1;
                this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].stateUnk = OpenSHC::Commands::GCS_PROCESSED;
                paiVar1 = paiVar1 + 1;
            } while (_gameCommandID < this->MBR_someIndex);
        }
    }

}
}
