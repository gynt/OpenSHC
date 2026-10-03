#include "../Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x0043E540
    int Helpers::SomePopularityRelatedComputation()
    {
        int iVar1
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].popularity
            / 100;
        if (99 < iVar1) {
            return 0xc;
        }
        if (iVar1 < 1) {
            return 2;
        }
        int iVar2 = iVar1 >> 0x1f;
        int iVar3 = iVar1 / 10 + iVar2;
        if (iVar1 < 0x32) {
            return (iVar3 + 3) - iVar2;
        }
        return (iVar3 + 2) - iVar2;
    }

}
}
