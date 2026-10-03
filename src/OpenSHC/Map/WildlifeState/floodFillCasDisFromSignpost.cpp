#include "../../Map.func.hpp"
#include "../WildlifeState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      BFS from the current attack signpost position (from TroopValueState.attackInfo), propagating   casDisRelated2
      outward (incrementing by 1 per step, capped at 99). Restricted to cells in the   same separateAreaID with
      unknownNonZero01 == 0. Also increments field29_0x74 on each visited   cell, building both a distance map and a
      visitation count. Used to measure reachable area or   routing cost from an attack waypoint.      renamed by:
      Claude Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0052D9D0
    void WildlifeState::floodFillCasDisFromSignpost()
    {
        int* piVar1;
        int iVar2;
        int iVar3;
        uint uVar4;
        int* piVar5;
        int iVar6;
        int iVar7;
        uint uVar8;
        iVar2 = DAT_GameState::instance.mapAndTime
                    .signpostEntryData[DAT_TroopValueState::instance.attackInfo.field128056_0x469d4]
                    .x
            / 10;
        this->DAT_X10_Array_Section1034[0] = (short)iVar2;
        iVar7 = DAT_GameState::instance.mapAndTime
                    .signpostEntryData[DAT_TroopValueState::instance.attackInfo.field128056_0x469d4]
                    .y
            / 10;
        this->casDisRelated = 1;
        this->candidateIndex = 0;
        this->candidateIndex2 = 1;
        piVar5 = &this->grid[0][0].field29_0x74;
        iVar6 = 0x28;
        do {
            iVar3 = 0x28;
            piVar1 = piVar5;
            do {
                piVar1[-0xf] = 0;
                *piVar1 = 0;
                piVar1 = piVar1 + 0x640;
                iVar3 = iVar3 + -1;
            } while (iVar3 != 0);
            piVar5 = piVar5 + 0x28;
            iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
        this->DAT_Y10_Array_Section1034[0] = (short)iVar7;
        iVar6 = this->grid[iVar2][iVar7].separateAreaID;
        this->grid[iVar2][iVar7].casDisRelated2 = 1;
        if (this->candidateIndex != this->candidateIndex2) {
            do {
                iVar7 = (int)this->DAT_X10_Array_Section1034[this->candidateIndex];
                iVar2 = (int)this->DAT_Y10_Array_Section1034[this->candidateIndex];
                this->casDisRelated = this->grid[iVar7][iVar2].casDisRelated2;
                if (99 < this->casDisRelated) {}
                iVar3 = this->casDisRelated + 1;
                piVar5 = &DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[0].int_.yOffset;
                do {
                    uVar4 = ((Point8IntXY*)(piVar5 + -1))->xOffset + iVar7;
                    uVar8 = *piVar5 + iVar2;
                    if ((((uVar4 < 0x28) && (uVar8 < 0x28)) && (0 < this->grid[uVar4][uVar8].firstMember))
                        && (((iVar6 == this->grid[uVar4][uVar8].separateAreaID
                                 && (this->grid[uVar4][uVar8].unknownNonZero01 == 0))
                            && (this->grid[uVar4][uVar8].casDisRelated2 == 0)))) {
                        piVar1 = &this->grid[uVar4][uVar8].field29_0x74;
                        *piVar1 = *piVar1 + 1;
                        this->grid[uVar4][uVar8].casDisRelated2 = iVar3;
                        this->DAT_X10_Array_Section1034[this->candidateIndex2] = (short)uVar4;
                        this->DAT_Y10_Array_Section1034[this->candidateIndex2] = (short)uVar8;
                        this->candidateIndex2 = this->candidateIndex2 + 1;
                        if (0x63f < this->candidateIndex2) {
                            this->candidateIndex2 = 0;
                        }
                    }
                    uVar4 = piVar5[1] + iVar7;
                    uVar8 = piVar5[2] + iVar2;
                    if (((uVar4 < 0x28) && (uVar8 < 0x28))
                        && ((0 < this->grid[uVar4][uVar8].firstMember
                            && (((iVar6 == this->grid[uVar4][uVar8].separateAreaID
                                     && (this->grid[uVar4][uVar8].unknownNonZero01 == 0))
                                && (this->grid[uVar4][uVar8].casDisRelated2 == 0)))))) {
                        this->grid[uVar4][uVar8].casDisRelated2 = iVar3;
                        piVar1 = &this->grid[uVar4][uVar8].field29_0x74;
                        *piVar1 = *piVar1 + 1;
                        this->DAT_X10_Array_Section1034[this->candidateIndex2] = (short)uVar4;
                        this->DAT_Y10_Array_Section1034[this->candidateIndex2] = (short)uVar8;
                        this->candidateIndex2 = this->candidateIndex2 + 1;
                        if (0x63f < this->candidateIndex2) {
                            this->candidateIndex2 = 0;
                        }
                    }
                    uVar4 = piVar5[3] + iVar7;
                    uVar8 = piVar5[4] + iVar2;
                    if (((uVar4 < 0x28) && (uVar8 < 0x28))
                        && (((0 < this->grid[uVar4][uVar8].firstMember
                                 && ((iVar6 == this->grid[uVar4][uVar8].separateAreaID
                                     && (this->grid[uVar4][uVar8].unknownNonZero01 == 0))))
                            && (this->grid[uVar4][uVar8].casDisRelated2 == 0)))) {
                        this->grid[uVar4][uVar8].casDisRelated2 = iVar3;
                        piVar1 = &this->grid[uVar4][uVar8].field29_0x74;
                        *piVar1 = *piVar1 + 1;
                        this->DAT_X10_Array_Section1034[this->candidateIndex2] = (short)uVar4;
                        this->DAT_Y10_Array_Section1034[this->candidateIndex2] = (short)uVar8;
                        this->candidateIndex2 = this->candidateIndex2 + 1;
                        if (0x63f < this->candidateIndex2) {
                            this->candidateIndex2 = 0;
                        }
                    }
                    uVar4 = piVar5[5] + iVar7;
                    uVar8 = piVar5[6] + iVar2;
                    if (((((uVar4 < 0x28) && (uVar8 < 0x28)) && (0 < this->grid[uVar4][uVar8].firstMember))
                            && ((iVar6 == this->grid[uVar4][uVar8].separateAreaID
                                && (this->grid[uVar4][uVar8].unknownNonZero01 == 0))))
                        && (this->grid[uVar4][uVar8].casDisRelated2 == 0)) {
                        this->grid[uVar4][uVar8].casDisRelated2 = iVar3;
                        piVar1 = &this->grid[uVar4][uVar8].field29_0x74;
                        *piVar1 = *piVar1 + 1;
                        this->DAT_X10_Array_Section1034[this->candidateIndex2] = (short)uVar4;
                        this->DAT_Y10_Array_Section1034[this->candidateIndex2] = (short)uVar8;
                        this->candidateIndex2 = this->candidateIndex2 + 1;
                        if (0x63f < this->candidateIndex2) {
                            this->candidateIndex2 = 0;
                        }
                    }
                    piVar5 = piVar5 + 8;
                } while ((int)piVar5 < 0xb4908c);
                this->candidateIndex = this->candidateIndex + 1;
                if (0x63f < this->candidateIndex) {
                    this->candidateIndex = 0;
                }
            } while (this->candidateIndex != this->candidateIndex2);
        }
    }

}
}
