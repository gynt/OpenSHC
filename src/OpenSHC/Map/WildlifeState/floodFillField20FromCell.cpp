#include "../../Map.func.hpp"
#include "../WildlifeState.func.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    /*
      BFS flood fill propagating field20_0x50 outward from a seed cell at (param_1, param_2) with   initial value
      param_3. Structurally identical to floodFillField13FromCell but targets a different   grid field, suggesting it
      tracks a separate influence layer (e.g. a second animal or resource   type). Stops when value drops below 2.
      renamed by: Claude Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0052C810
    void WildlifeState::floodFillField20FromCell(int param_1, int param_2, int param_3)
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
        this->grid[param_1][param_2].field20_0x50 = param_3;
        if (this->candidateIndex != this->candidateIndex2) {
            do {
                iVar4 = (int)this->DAT_X10_Array_Section1034[this->candidateIndex];
                iVar5 = (int)this->DAT_Y10_Array_Section1034[this->candidateIndex];
                this->casDisRelated = this->grid[iVar4][iVar5].field20_0x50;
                if (this->casDisRelated < 2) {}
                iVar1 = this->casDisRelated + -1;
                piVar6 = &DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[0].int_.yOffset;
                do {
                    uVar2 = ((Point8IntXY*)(piVar6 + -1))->xOffset + iVar4;
                    uVar3 = *piVar6 + iVar5;
                    if ((((uVar2 < 0x28) && (uVar3 < 0x28)) && (0 < this->grid[uVar2][uVar3].firstMember))
                        && (this->grid[uVar2][uVar3].field20_0x50 < iVar1)) {
                        this->grid[uVar2][uVar3].field20_0x50 = iVar1;
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
                            && (this->grid[uVar2][uVar3].field20_0x50 < iVar1)))) {
                        this->grid[uVar2][uVar3].field20_0x50 = iVar1;
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
                            && (this->grid[uVar2][uVar3].field20_0x50 < iVar1)))) {
                        this->grid[uVar2][uVar3].field20_0x50 = iVar1;
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
                        && (this->grid[uVar2][uVar3].field20_0x50 < iVar1)) {
                        this->grid[uVar2][uVar3].field20_0x50 = iVar1;
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
