#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Text/UserTextHandler.func.hpp"

#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00486F20
    void GameSynchronyState::initializeFinalResultsForActivePlayers()
    {
        byte* pbVar1;
        char cVar2;
        char* pcVar3;
        int* piVar4;
        char (*pacVar5)[250];
        int iVar6;
        int (*paiVar7)[9];
        undefined2* local_c;
        int local_8;
        char (*local_4)[250];
        pcVar3 = MACRO_CALL_MEMBER(
            Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(0);
        pacVar5 = this->DAT_PlayerNames + 1;
        do {
            cVar2 = *pcVar3;
            (*pacVar5)[0] = cVar2;
            pcVar3 = pcVar3 + 1;
            pacVar5 = (char (*)[250])(*pacVar5 + 1);
        } while (cVar2 != '\0');
        iVar6 = 1;
        local_c = (undefined2*)((int)this->finalResults.unusedUnk + 2);
        local_4 = this->DAT_PlayerNames;
        local_8 = 0x1a26d86;
        piVar4 = this->currentPlayerFullIDArray;
        do {
            piVar4 = piVar4 + 1;
            local_4 = local_4 + 1;
            if ((*piVar4 == -1) && (piVar4[0x1b] == 0)) {
                this->finalResults.active[iVar6] = 0;
            } else {
                this->finalResults.active[iVar6] = 1;
                pacVar5 = local_4;
                do {
                    cVar2 = (*pacVar5)[0];
                    *(char*)((int)pacVar5 + (local_8 - (int)local_4)) = cVar2;
                    pacVar5 = (char (*)[250])(*pacVar5 + 1);
                } while (cVar2 != '\0');
                piVar4[0x42494] = 0;
                local_c[-0x1b6] = 0;
                this->finalResults.finalMaxGoodThings[iVar6] = 0;
                this->finalResults.finalMaxBadThings[iVar6] = 0;
                piVar4[0x424fe] = 0;
                piVar4[0x42542] = 0;
                piVar4[0x42507] = 0;
                piVar4[0x42539] = 0;
                piVar4[0x42510] = 0;
                piVar4[0x42519] = 0;
                piVar4[0x42522] = 0;
                piVar4[0x4252b] = 0;
                this->finalResults.finalKilledLords[iVar6] = 0;
                piVar4[0x4254b] = 0;
                piVar4[0x42554] = 0;
                piVar4[0x424a4] = 0;
                piVar4[0x4255d] = 0;
                piVar4[0x42566] = 0;
                piVar4[0x4256f] = 0;
                *local_c = 0;
                local_c[9] = 0;
                piVar4[0x42581] = 0;
                piVar4[0x4258a] = 0;
                pbVar1 = (byte*)(piVar4 + 0x42593);
                pbVar1[0] = 0;
                pbVar1[1] = 0;
                pbVar1[2] = 0;
                pbVar1[3] = 0;
                pbVar1 = (byte*)(piVar4 + 0x4259c);
                pbVar1[0] = 0;
                pbVar1[1] = 0;
                pbVar1[2] = 0;
                pbVar1[3] = 0;
            }
            iVar6 = iVar6 + 1;
            local_c = local_c + 1;
            local_8 = local_8 + 0x5a;
        } while (iVar6 < 9);
        paiVar7 = this->finalResults.finalKillMatrix;
        for (iVar6 = 0x51; iVar6 != 0; iVar6 = iVar6 + -1) {
            (*paiVar7)[0] = 0;
            paiVar7 = (int (*)[9])(*paiVar7 + 1);
        }
    }

}
}
