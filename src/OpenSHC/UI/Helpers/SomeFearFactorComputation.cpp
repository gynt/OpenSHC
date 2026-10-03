#include "../Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x0043E5A0
    undefined4 Helpers::SomeFearFactorComputation()
    {
        uint uVar1 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                         .fearFactorLevel;
        if ((int)uVar1 < -4) {
            return (undefined4)(0xe);
        }
        if ((int)uVar1 < -2) {
            return (undefined4)(0xf);
        }
        if (0x7fffffff < uVar1) {
            return (undefined4)(0x10);
        }
        if (4 < (int)uVar1) {
            return (undefined4)(0x13);
        }
        undefined4 uVar2 = 0x12;
        if ((int)uVar1 < 3) {
            uVar2 = 0x11;
        }
        return (undefined4)(uVar2);
    }

}
}
