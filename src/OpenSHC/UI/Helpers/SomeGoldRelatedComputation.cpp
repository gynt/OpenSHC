#include "../Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x0043E5F0
    int Helpers::SomeGoldRelatedComputation()
    {
        int iVar1 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[0xf];
        if (!iVar1) {
            return 0x1d;
        }
        if (999 < iVar1) {
            return 0x20;
        }
        int iVar2 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .blessedPeoplePercentage;
        if (0x4f < iVar2) {
            return 0x17;
        }
        int iVar3 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .workingInnsCount;
        if (2 < iVar3) {
            return 0x1b;
        }
        if (0x27 < iVar2) {
            return 0x16;
        }
        if (iVar3 == 2) {
            return 0x1a;
        }
        if (4999 < iVar1) {
            return 0x1f;
        }
        if (0x13 < iVar2) {
            return 0x15;
        }
        if (iVar3 == 1) {
            return 0x19;
        }
        if (iVar1 < 500) {
            return 0x1e;
        }
        if (4 < DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .totalEnemyUnitsCount) {
            return 0x24;
        }
        iVar1 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .currentPopulation;
        if (!iVar1) {
            return 0x22;
        }
        return (uint)(4 < iVar1) * 4 + 0x23;
    }

}
}
