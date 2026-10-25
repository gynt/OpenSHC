#include "../GreatestLord.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D5780
    int GreatestLord::ComputeSkMasterScore(int playerID)
    {
        int iVar2;
        int iVar3;
        iVar3 = DAT_GameSynchronyState::instance.finalResults.finalBuildingsDestroyedWeighted[playerID] * 100
            + DAT_GameSynchronyState::instance.finalResults.finalGold[playerID] / 10
            + DAT_GameSynchronyState::instance.finalResults.finalTroopsKilledWeighted[playerID];
        int iVar1 = (char)DAT_GameSynchronyState::instance.finalResults.finalKilledLords[playerID] * iVar3;
        iVar2 = ((DAT_GameSynchronyState::instance.finalResults.yearEnd
                     - DAT_GameSynchronyState::instance.finalResults.yearStart)
                        * 0xc
                    - DAT_GameSynchronyState::instance.finalResults.monthStart)
            + DAT_GameSynchronyState::instance.finalResults.monthEnd;
        if (iVar2 < 1) {
            iVar2 = 1;
        }
        return ((iVar3 + (iVar1 / 4)) * 200) / (iVar2 + 200);
    }

}
}
