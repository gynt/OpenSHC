#include "../../Map.func.hpp"
#include "../WildlifeState.func.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    /*
      BFS flood fill propagating field13_0x34 outward from a seed cell at (param_1, param_2) with   initial value
      param_3. Each neighbour in the cardinal translation matrix receives a value of   (current - 1), stopping when the
      value drops below 2. Uses the shared   candidateIndex/candidateIndex2 circular queue. One of several influence-map
      flood fills in   WildlifeState, distinguished by which grid field it writes.      renamed by: Claude Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0052C570
    void WildlifeState::floodFillField13FromCell(int param_1, int param_2, int param_3)
    {
        int iVar1;
        uint uVar2;
        uint uVar3;
        int iVar4;
        int iVar5;
        int* piVar6;
        this->candidateIndex2 = 1;
        this->casDisRelated = 1;
        this->DAT_X10_Array_Section1034[0] = (short)param_1;
        this->DAT_Y10_Array_Section1034[0] = (short)param_2;
        this->candidateIndex = 0;
        this->grid[param_1][param_2].field13_0x34 = param_3;
        if (this->candidateIndex != this->candidateIndex2) {
            do {
                iVar4 = (int)this->DAT_X10_Array_Section1034[this->candidateIndex];
                iVar5 = (int)this->DAT_Y10_Array_Section1034[this->candidateIndex];
                this->casDisRelated = this->grid[iVar4][iVar5].field13_0x34;
                if (this->casDisRelated < 2) {}
                iVar1 = this->casDisRelated + -1;
                piVar6 = &DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[0].int_.yOffset;
                do {
                    uVar2 = ((Point8IntXY*)(piVar6 + -1))->xOffset + iVar4;
                    uVar3 = *piVar6 + iVar5;
                    if ((((uVar2 < 0x28) && (uVar3 < 0x28)) && (0 < this->grid[uVar2][uVar3].firstMember))
                        && (this->grid[uVar2][uVar3].field13_0x34 < iVar1)) {
                        this->grid[uVar2][uVar3].field13_0x34 = iVar1;
                        this->DAT_X10_Array_Section1034[this->candidateIndex2] = (short)uVar2;
                        this->DAT_Y10_Array_Section1034[this->candidateIndex2] = (short)uVar3;
                        this->candidateIndex2 = this->candidateIndex2 + 1;
                        if (0x63f < this->candidateIndex2) {
                            this->candidateIndex2 = 0;
                        }
                    }
                    uVar3 = piVar6[2] + iVar5;
                    uVar2 = piVar6[1] + iVar4;
                    if (((uVar2 < 0x28) && (uVar3 < 0x28))
                        && ((0 < this->grid[uVar2][uVar3].firstMember
                            && (this->grid[uVar2][uVar3].field13_0x34 < iVar1)))) {
                        this->grid[uVar2][uVar3].field13_0x34 = iVar1;
                        this->DAT_X10_Array_Section1034[this->candidateIndex2] = (short)uVar2;
                        this->DAT_Y10_Array_Section1034[this->candidateIndex2] = (short)uVar3;
                        this->candidateIndex2 = this->candidateIndex2 + 1;
                        if (0x63f < this->candidateIndex2) {
                            this->candidateIndex2 = 0;
                        }
                    }
                    uVar3 = piVar6[4] + iVar5;
                    uVar2 = piVar6[3] + iVar4;
                    if (((uVar2 < 0x28) && (uVar3 < 0x28))
                        && ((0 < this->grid[uVar2][uVar3].firstMember
                            && (this->grid[uVar2][uVar3].field13_0x34 < iVar1)))) {
                        this->grid[uVar2][uVar3].field13_0x34 = iVar1;
                        this->DAT_X10_Array_Section1034[this->candidateIndex2] = (short)uVar2;
                        this->DAT_Y10_Array_Section1034[this->candidateIndex2] = (short)uVar3;
                        this->candidateIndex2 = this->candidateIndex2 + 1;
                        if (0x63f < this->candidateIndex2) {
                            this->candidateIndex2 = 0;
                        }
                    }
                    uVar3 = piVar6[6] + iVar5;
                    uVar2 = piVar6[5] + iVar4;
                    if ((((uVar2 < 0x28) && (uVar3 < 0x28)) && (0 < this->grid[uVar2][uVar3].firstMember))
                        && (this->grid[uVar2][uVar3].field13_0x34 < iVar1)) {
                        this->grid[uVar2][uVar3].field13_0x34 = iVar1;
                        this->DAT_X10_Array_Section1034[this->candidateIndex2] = (short)uVar2;
                        this->DAT_Y10_Array_Section1034[this->candidateIndex2] = (short)uVar3;
                        this->candidateIndex2 = this->candidateIndex2 + 1;
                        if (0x63f < this->candidateIndex2) {
                            this->candidateIndex2 = 0;
                        }
                    }
                    piVar6 = piVar6 + 8;
                } while ((int)piVar6 < 0xb4908c);
                this->candidateIndex = this->candidateIndex + 1;
                if (0x63f < this->candidateIndex) {
                    this->candidateIndex = 0;
                }
            } while (this->candidateIndex != this->candidateIndex2);
        }
    }

}
}
