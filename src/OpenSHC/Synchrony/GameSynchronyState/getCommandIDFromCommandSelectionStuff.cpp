#include "../../Synchrony.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandState.hpp"
#include "OpenSHC/Commands/GameCommandStateByte.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::GameCommandState;
    using Commands::GameCommandStateByte;

    // FUNCTION: STRONGHOLDCRUSADER 0x00480440
    int GameSynchronyState::getCommandIDFromCommandSelectionStuff()
    {
        GameCommandStateByte* _stateAddress;
        int _currentIndexCounter;
        int _commandID;
        int _nextPlayerID;
        int _playerID;
        int _reorderedAnyoneUnk;
        this->someIndex = 0;
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            800, '\0', (void*)((int)(this->selectedGameCommands)));
        if ((int)this->gameCommandID < 200) {
            _stateAddress = &this->DAT_GameCommandArray[this->gameCommandID].stateUnk;
            for (_currentIndexCounter = this->gameCommandID; _currentIndexCounter < 200;
                _currentIndexCounter = _currentIndexCounter + 1, _stateAddress = _stateAddress + 0x4f8) {
                /*
                  _stateAddress points at GameCommand::stateUnk, which the header puts at +9, so -9 reaches
                  ::time and -5 reaches ::playerUnk. Walking a GameCommand* and naming the three members
                  instead reads better but measures 72.8% -> 70.7%, so the pointer stays.
                 */
                if (*_stateAddress != (GameCommandState)0 && (char)*_stateAddress < '\n'
                    && (int)((GameCommand*)(_stateAddress + -9))->time <= (int)DAT_GameCore::instance.mapTimeInTicks) {
                    /*
                      the command has not been processed yet, should be processed, and its time has come
                     */
                    this->protocolInvokerPlayerID
                        = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::translateMultiplayerIDsIntoPlayerIDs,
                            this)(*(int*)(_stateAddress + -5));
                    this->selectedGameCommands[this->someIndex][0] = _currentIndexCounter;
                    this->selectedGameCommands[this->someIndex][1] = this->protocolInvokerPlayerID;
                    this->someIndex = this->someIndex + 1;
                    if (this->someIndex >= 100)
                        break;
                }
            }
        }
        /*
          reorder the selected commands list so that player ids with a lower number are   processed first.
         */
        int _counter2 = 0;
        if (0 < this->someIndex) {
            _reorderedAnyoneUnk = 1;
            for (_counter2 = 0; _counter2 < 100; _counter2 = _counter2 + 1) {
                if (!_reorderedAnyoneUnk)
                    break;
                _reorderedAnyoneUnk = 0;
                if (1 < this->someIndex) {
                    for (_currentIndexCounter = 1; _currentIndexCounter < this->someIndex;
                        _currentIndexCounter = _currentIndexCounter + 1) {
                        _nextPlayerID = this->selectedGameCommands[_currentIndexCounter][1];
                        _commandID = this->selectedGameCommands[_currentIndexCounter - 1][0];
                        _playerID = this->selectedGameCommands[_currentIndexCounter - 1][1];
                        if (!_nextPlayerID) {
                            return 0;
                        }
                        if (_nextPlayerID < _playerID) {
                            this->selectedGameCommands[_currentIndexCounter - 1][0]
                                = this->selectedGameCommands[_currentIndexCounter][0];
                            this->selectedGameCommands[_currentIndexCounter - 1][1] = _nextPlayerID;
                            this->selectedGameCommands[_currentIndexCounter][0] = _commandID;
                            this->selectedGameCommands[_currentIndexCounter][1] = _playerID;
                            _reorderedAnyoneUnk = 1;
                        }
                    }
                }
            }
            _counter2 = 1;
        }
        return _counter2;
    }

}
}
