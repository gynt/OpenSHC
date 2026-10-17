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
        int* _selectedPlayerIDAddress;
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
            _currentIndexCounter = this->gameCommandID;
            do {
                /*
                  stateAddress - 9 = time address
                 */
                if (*_stateAddress != (GameCommandState)0 && (char)*_stateAddress < '\n'
                    && (int)((GameCommand*)(_stateAddress + -9))->time <= (int)DAT_GameCore::instance.mapTimeInTicks) {
                    /*
                      if this command has not been processed, but should be processed, and it has   been its time state
                      address - 5 = player
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
                _currentIndexCounter = _currentIndexCounter + 1;
                /*
                  move to next command
                 */
                _stateAddress = _stateAddress + 0x4f8;
            } while (_currentIndexCounter < 200);
        }
        /*
          reorder the selected commands list so that player ids with a lower number are   processed first.
         */
        int _counter2 = 0;
        if (0 < this->someIndex) {
            _reorderedAnyoneUnk = 1;
            do {
                if (!_reorderedAnyoneUnk)
                    break;
                _currentIndexCounter = 1;
                _counter2 = _counter2 + 1;
                _reorderedAnyoneUnk = 0;
                if (1 < this->someIndex) {
                    _selectedPlayerIDAddress = this->selectedGameCommands[0] + 1;
                    do {
                        _nextPlayerID = _selectedPlayerIDAddress[2];
                        _commandID = _selectedPlayerIDAddress[-1];
                        _playerID = *_selectedPlayerIDAddress;
                        if (!_nextPlayerID) {
                            return 0;
                        }
                        if (_nextPlayerID < _playerID) {
                            _selectedPlayerIDAddress[-1] = _selectedPlayerIDAddress[1];
                            *_selectedPlayerIDAddress = _nextPlayerID;
                            _selectedPlayerIDAddress[1] = _commandID;
                            _selectedPlayerIDAddress[2] = _playerID;
                            _reorderedAnyoneUnk = 1;
                        }
                        _currentIndexCounter = _currentIndexCounter + 1;
                        _selectedPlayerIDAddress = _selectedPlayerIDAddress + 2;
                    } while (_currentIndexCounter < this->someIndex);
                }
            } while (_counter2 < 100);
            _counter2 = 1;
        }
        return _counter2;
    }

}
}
