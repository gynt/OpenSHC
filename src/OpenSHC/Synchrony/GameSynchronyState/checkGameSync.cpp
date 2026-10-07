#include "../../Synchrony.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::GameCommandType;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0048CB00
    void GameSynchronyState::checkGameSync()
    {
        int* piVar1;
        int _playerID;
        int* piVar2;
        int iVar3;
        int _currentMatchTime;
        int _currentHash;
        _currentHash = 0;
        _currentMatchTime = 0;
        if (!this->DAT_HashCountdown) {
            piVar1 = this->unknownPlayerInfo_03 + 1;
            this->DAT_GameHalted = 0;
            _playerID = 1;
            piVar2 = piVar1;
            do {
                if ((piVar2[-0x419d4] != -1) && (*piVar2 == 0)) {
                    _currentHash = this->HASH_HashTotal[_playerID];
                    _currentMatchTime = this->DAT_PlayerMatchTimes[_playerID];
                    break;
                }
                _playerID = _playerID + 1;
                piVar2 = piVar2 + 1;
            } while (_playerID < 9);
            if ((this->isHost) && (!this->flag_0xbec)) {
                iVar3 = 1;
                piVar2 = piVar1;
                do {
                    if ((piVar2[-0x419d4] != -1) && (*piVar2 == 0)) {
                        if (piVar2[-0x23158] == 0) {
                            this->DAT_GameHalted = 0;
                        }
                        if (piVar2[-0x2314f] < 10) {
                            this->DAT_GameHalted = 0;
                        }
                    }
                    iVar3 = iVar3 + 1;
                    piVar2 = piVar2 + 1;
                } while (iVar3 < 9);
                iVar3 = 1;
                do {
                    if ((piVar1[-0x419d4] != -1) && (*piVar1 == 0)) {
                        if (piVar1[-0x23158] == 0) {
                            this->DAT_GameHalted = 0;
                        }
                        if ((piVar1[-0x2314f] == _currentMatchTime) && (piVar1[-0x23158] != _currentHash)) {
                            /*
                              hash mismatch for same game time
                             */
                            if (this->syncRelatedCountdown) {
                                this->syncRelatedCountdown = 0;
                                this->commandDelay = 0x1e;
                            }
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                Commands::GCT_GAME_DESYNCUnk);
                            this->flag_0xbec = 1;
                            this->receivedSyncStatusByPlayerUnk[1] = 0;
                            this->receivedSyncStatusByPlayerUnk[2] = 0;
                            this->receivedSyncStatusByPlayerUnk[3] = 0;
                            this->receivedSyncStatusByPlayerUnk[4] = 0;
                            this->receivedSyncStatusByPlayerUnk[5] = 0;
                            this->receivedSyncStatusByPlayerUnk[6] = 0;
                            this->receivedSyncStatusByPlayerUnk[7] = 0;
                            this->receivedSyncStatusByPlayerUnk[8] = 0;
                            this->syncStatus10Related[1] = 0;
                            this->syncStatus10Related[2] = 0;
                            this->syncStatus10Related[3] = 0;
                            this->syncStatus10Related[4] = 0;
                            this->syncStatus10Related[5] = 0;
                            this->syncStatus10Related[6] = 0;
                            this->syncStatus10Related[7] = 0;
                            this->syncStatus10Related[8] = 0;
                        }
                    }
                    iVar3 = iVar3 + 1;
                    piVar1 = piVar1 + 1;
                    if (8 < iVar3) {}
                } while (true);
            }
        }
    }

}
}
