#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

namespace OpenSHC {
namespace Synchrony {

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0047E830
    int GameSynchronyState::countActiveHumanPlayers()
    {
        uint uVar1;
        uVar1 = (uint)(this->currentPlayerFullIDArray[1] != -1);
        if (this->currentPlayerFullIDArray[2] != -1) {
            uVar1 = uVar1 + 1;
        }
        if (this->currentPlayerFullIDArray[3] != -1) {
            uVar1 = uVar1 + 1;
        }
        if (this->currentPlayerFullIDArray[4] != -1) {
            uVar1 = uVar1 + 1;
        }
        if (this->currentPlayerFullIDArray[5] != -1) {
            uVar1 = uVar1 + 1;
        }
        if (this->currentPlayerFullIDArray[6] != -1) {
            uVar1 = uVar1 + 1;
        }
        if (this->currentPlayerFullIDArray[7] != -1) {
            uVar1 = uVar1 + 1;
        }
        if (this->currentPlayerFullIDArray[8] != -1) {
            uVar1 = uVar1 + 1;
        }
        return (int)(uVar1);
    }

}
}
