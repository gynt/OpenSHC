#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Synchrony {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0047EDE0
    undefined4 GameSynchronyState::checkAllPlayersReadyAndCleanupSlots()
    {
        if (this->isHost) {
            for (int iVar2 = 1; iVar2 < 9; iVar2 = iVar2 + 1) {
                if ((this->DAT_CurrentPlayerFullIDArray2[iVar2] != -1)
                    && (this->unknownPlayerInfo_01[iVar2] == 0)) {
                    return (undefined4)(0);
                }
            }
            if (this->somePlayerRelatedArray[1] == 0) {
                this->currentPlayerFullIDArray[1] = -1;
            }
            if (this->somePlayerRelatedArray[2] == 0) {
                this->currentPlayerFullIDArray[2] = -1;
            }
            if (this->somePlayerRelatedArray[3] == 0) {
                this->currentPlayerFullIDArray[3] = -1;
            }
            if (this->somePlayerRelatedArray[4] == 0) {
                this->currentPlayerFullIDArray[4] = -1;
            }
            if (this->somePlayerRelatedArray[5] == 0) {
                this->currentPlayerFullIDArray[5] = -1;
            }
            if (this->somePlayerRelatedArray[6] == 0) {
                this->currentPlayerFullIDArray[6] = -1;
            }
            if (this->somePlayerRelatedArray[7] == 0) {
                this->currentPlayerFullIDArray[7] = -1;
            }
            if (this->somePlayerRelatedArray[8] == 0) {
                this->currentPlayerFullIDArray[8] = -1;
            }
            return (undefined4)(1);
        }
        if (this->lobbyStateReceived) {
            return (undefined4)(1);
        }
        return (undefined4)(0);
    }

}
}
