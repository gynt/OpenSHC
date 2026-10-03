#include "../Synchrony.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x00428050
void Synchrony::ResetAiVariationArrayValue(int playerID)
{
    int* piVar1;
    int iVar2;
    int local_24[9];
    if (playerID - 1U < 8) {
        local_24[1] = 0;
        local_24[2] = 0;
        local_24[3] = 0;
        local_24[4] = 0;
        local_24[5] = 0;
        local_24[6] = 0;
        local_24[7] = 0;
        local_24[8] = 0;
        DAT_GameSynchronyState::instance.aiVariationArray[playerID] = -1;
        local_24[0] = 0;
        piVar1 = DAT_GameSynchronyState::instance.aiVariationArray + 1;
        do {
            if (((piVar1[-0x24] == -1) && (piVar1[-9] == DAT_GameSynchronyState::instance.currentAIArray[playerID]))
                && (*piVar1 != -1)) {
                local_24[*piVar1] = 1;
            }
            if (((piVar1[-0x23] == -1) && (piVar1[-8] == DAT_GameSynchronyState::instance.currentAIArray[playerID]))
                && (piVar1[1] != -1)) {
                local_24[piVar1[1]] = 1;
            }
            if (((piVar1[-0x22] == -1) && (piVar1[-7] == DAT_GameSynchronyState::instance.currentAIArray[playerID]))
                && (piVar1[2] != -1)) {
                local_24[piVar1[2]] = 1;
            }
            if (((piVar1[-0x21] == -1) && (piVar1[-6] == DAT_GameSynchronyState::instance.currentAIArray[playerID]))
                && (piVar1[3] != -1)) {
                local_24[piVar1[3]] = 1;
            }
            piVar1 = piVar1 + 4;
        } while ((int)piVar1 < 0x191dec4);
        iVar2 = 0;
        while (local_24[iVar2] != 0) {
            iVar2 = iVar2 + 1;
            if (8 < iVar2) {}
        }
        DAT_GameSynchronyState::instance.aiVariationArray[playerID] = iVar2;
    }
}

}
