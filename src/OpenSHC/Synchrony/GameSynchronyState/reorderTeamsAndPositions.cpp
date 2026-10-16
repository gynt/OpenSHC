#include "../../Synchrony.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::GameCommandType;
    using Game::GameMode;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0048C7B0
    undefined4 GameSynchronyState::reorderTeamsAndPositions()
    {
        int iVar3;
        byte bVar4;
        int _counter2;
        int _counter3;
        int _counter;
        int* piVar5;
        int* piVar6;
        int local_4c;
        int _bestSlot;
        int local_38[14];
        byte _group;
        _counter2 = 0;
        for (int _slotIndex = 1; _slotIndex < 9; _slotIndex = _slotIndex + 1) {
            this->DAT_RoundTableOrderArray[_slotIndex] = 0;
        }
        local_38[6] = 0;
        local_38[7] = 0;
        local_38[8] = 0;
        local_38[9] = 0;
        local_38[10] = 0;
        local_38[11] = 0;
        local_38[12] = 0;
        local_38[13] = 0;
        local_38[0] = 0;
        local_38[1] = 0;
        local_38[2] = 0;
        local_38[3] = 0;
        local_38[4] = 0;
        for (_counter = 1; _counter < 9; _counter = _counter + 1) {
            /*
              fullIdArray == -1 && AI == 0
             */
            if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_counter] == -1) && (DAT_GameSynchronyState::instance.currentAIArray[_counter] == 0)) {
                this->DAT_PlayerGroupArray[_counter] = (char)0xff;
            } else {
                if (this->DAT_PlayerGroupArray[_counter] < '\0') {
                    this->DAT_PlayerGroupArray[_counter] = 0;
                }
                int _groupIndex = this->DAT_PlayerGroupArray[_counter];
                local_38[_groupIndex] = local_38[_groupIndex] + 1;
                if (_groupIndex != 0) {
                    local_38[0] = local_38[0] + 1;
                }
                _counter2 = _counter2 + 1;
            }
        }
        _counter = 1;
    LAB_0048c857:
        iVar3 = local_38[_counter];
        if (1 <= iVar3) {
            if (iVar3 == local_38[0]) {
                for (iVar3 = 1; iVar3 < 9; iVar3 = iVar3 + 1) {
                    if (0 <= this->DAT_PlayerGroupArray[iVar3]) {
                        this->DAT_PlayerGroupArray[iVar3] = 0;
                    }
                }
                local_38[_counter] = 0;
            LAB_0048c8b5:
                _counter3 = 1;
                do {
                    if ((local_38[_counter3] == 0) && (local_38[_counter3 + 1] != 0)) {
                        if ((char)this->DAT_PlayerGroupArray[1] > _counter3) {
                            this->DAT_PlayerGroupArray[1]
                                = this->DAT_PlayerGroupArray[1] - 1;
                        }
                        if ((char)this->DAT_PlayerGroupArray[2] > _counter3) {
                            this->DAT_PlayerGroupArray[2]
                                = this->DAT_PlayerGroupArray[2] - 1;
                        }
                        if ((char)this->DAT_PlayerGroupArray[3] > _counter3) {
                            this->DAT_PlayerGroupArray[3]
                                = this->DAT_PlayerGroupArray[3] - 1;
                        }
                        if ((char)this->DAT_PlayerGroupArray[4] > _counter3) {
                            this->DAT_PlayerGroupArray[4]
                                = this->DAT_PlayerGroupArray[4] - 1;
                        }
                        if ((char)this->DAT_PlayerGroupArray[5] > _counter3) {
                            this->DAT_PlayerGroupArray[5]
                                = this->DAT_PlayerGroupArray[5] - 1;
                        }
                        if ((char)this->DAT_PlayerGroupArray[6] > _counter3) {
                            this->DAT_PlayerGroupArray[6]
                                = this->DAT_PlayerGroupArray[6] - 1;
                        }
                        if ((char)this->DAT_PlayerGroupArray[7] > _counter3) {
                            this->DAT_PlayerGroupArray[7]
                                = this->DAT_PlayerGroupArray[7] - 1;
                        }
                        if ((char)this->DAT_PlayerGroupArray[8] > _counter3) {
                            this->DAT_PlayerGroupArray[8]
                                = this->DAT_PlayerGroupArray[8] - 1;
                        }
                        if (_counter3 + 1 < 5) {
                            piVar5 = local_38 + _counter3 + 1;
                            piVar6 = local_38 + _counter3;
                            for (_counter = 5 - (_counter3 + 1); _counter != 0; _counter = _counter + -1) {
                                *piVar6 = *piVar5;
                                piVar5 = piVar5 + 1;
                                piVar6 = piVar6 + 1;
                            }
                        }
                    }
                    _counter3 = _counter3 + 1;
                } while (_counter3 <= 3);
                local_4c = 1;
                if (0 < _counter2) {
                    do {
                        _bestSlot = -1;
                        _group = 0xff;
                        for (_counter3 = 1; _counter3 < 9; _counter3 = _counter3 + 1) {
                            bVar4 = this->DAT_PlayerGroupArray[_counter3];
                            if ((-1 < (char)bVar4) && (local_38[_counter3 + 5] == 0)) {
                                if (!bVar4) {
                                    bVar4 = 10;
                                }
                                if ((char)bVar4 < (char)_group || _bestSlot == -1) {
                                    _bestSlot = _counter3;
                                    _group = bVar4;
                                }
                            }
                        }
                        if (_bestSlot < 0)
                            break;
                        DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[local_4c] = (byte)_bestSlot;
                        local_4c = local_4c + 1;
                        local_38[_bestSlot + 5] = 1;
                    } while (local_4c <= _counter2);
                }
                if ((DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER)
                    && (DAT_GameSynchronyState::instance.isHost)) {
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        (Commands::GameCommandType)(Commands::GCT_START_OR_STOP_SEND_MAP_FILEUnk
                            | Commands::GCT_HOST_SHARE_LOBBY_STATE));
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        Commands::GCT_HOST_ANNOUNCE_TEAMS_AND_POSITIONS);
                }
                return (undefined4)(1);
            }
            if (iVar3 == 1) {
                for (iVar3 = 1; iVar3 < 9; iVar3 = iVar3 + 1) {
                    if (this->DAT_PlayerGroupArray[iVar3] == _counter) {
                        this->DAT_PlayerGroupArray[iVar3] = 0;
                    }
                }
                local_38[_counter] = 0;
            }
        }
        _counter = _counter + 1;
        if (4 < _counter)
            goto LAB_0048c8b5;
        goto LAB_0048c857;
    }

}
}
