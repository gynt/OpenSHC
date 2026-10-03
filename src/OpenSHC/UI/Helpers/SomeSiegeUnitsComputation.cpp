#include "../Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_00b960bc.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SiegeInformationArray.hpp"
#include "OpenSHC/Globals/DAT_SiegeInformationArray_2.hpp"
#include "OpenSHC/Globals/DAT_SiegeRemainingPoints.hpp"
#include "OpenSHC/Globals/INT_00b960b8.hpp"
#include "OpenSHC/Globals/INT_00b960c0.hpp"
#include "OpenSHC/Globals/INT_00b960c4.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x0042C1E0
    void Helpers::SomeSiegeUnitsComputation(int param_1)
    {
        int (*paaiVar7)[7][3];
        int iVar8;
        int iVar9;
        int iVar10;
        int iVar11;
        int iVar12;
        int iVar13;
        int* piVar14;
        int local_18;
        int* local_14;
        int local_10[4];
        int iVar2 = DAT_SiegeInformationArray::instance[0x14];
        int iVar1 = DAT_SiegeInformationArray::instance[0x13];
        iVar9 = DAT_SiegeInformationArray::instance[0x12];
        iVar11 = DAT_SiegeInformationArray::instance[0x11];
        iVar12 = DAT_SiegeInformationArray::instance[0x10];
        int iVar6 = 0;
        iVar13 = DAT_00b960bc::instance;
        do {
            iVar8 = iVar6 + 0x74;
            iVar10 = iVar6 + 0x70;
            int iVar3 = iVar6 + 8;
            int iVar4 = iVar6 + 4;
            piVar14 = (int*)((int)DAT_SiegeInformationArray_2::instance[1][0] + iVar6);
            int iVar5 = iVar6 + 0x6c;
            iVar6 = iVar6 + 12;
            iVar13 = *piVar14 * *(int*)((int)DAT_RenderingDefinedData::instance.NoRushTicks + iVar5) + iVar13
                + *(int*)((int)DAT_RenderingDefinedData::instance.NoRushTicks + iVar8)
                    * *(int*)((int)DAT_SiegeInformationArray_2::instance[1][0] + iVar3)
                + *(int*)((int)DAT_RenderingDefinedData::instance.NoRushTicks + iVar10)
                    * *(int*)((int)DAT_SiegeInformationArray_2::instance[1][0] + iVar4);
        } while (iVar6 < 84);
        local_10[0] = (DAT_RenderingDefinedData::instance.field1003_0x548dc * iVar13) / 100;
        local_10[1] = (DAT_RenderingDefinedData::instance.field1004_0x548e0 * iVar13) / 100;
        local_10[2] = (DAT_RenderingDefinedData::instance.field1005_0x548e4 * iVar13) / 100;
        local_10[3] = (DAT_RenderingDefinedData::instance.field1006_0x548e8 * iVar13) / 100;
        INT_00b960b8::instance = DAT_SiegeRemainingPoints::instance;
        DAT_00b960bc::instance = DAT_SiegeRemainingPoints::instance;
        INT_00b960c0::instance = DAT_SiegeRemainingPoints::instance;
        INT_00b960c4::instance = DAT_SiegeRemainingPoints::instance;
        paaiVar7 = DAT_SiegeInformationArray_2::instance;
        do {
            (*paaiVar7)[0][0] = DAT_SiegeInformationArray::instance[0];
            (*paaiVar7)[0][1] = DAT_SiegeInformationArray::instance[1];
            (*paaiVar7)[0][2] = DAT_SiegeInformationArray::instance[2];
            (*paaiVar7)[1][0] = DAT_SiegeInformationArray::instance[3];
            (*paaiVar7)[1][1] = DAT_SiegeInformationArray::instance[4];
            (*paaiVar7)[1][2] = DAT_SiegeInformationArray::instance[5];
            (*paaiVar7)[2][0] = DAT_SiegeInformationArray::instance[6];
            (*paaiVar7)[2][1] = DAT_SiegeInformationArray::instance[7];
            (*paaiVar7)[2][2] = DAT_SiegeInformationArray::instance[8];
            (*paaiVar7)[3][0] = DAT_SiegeInformationArray::instance[9];
            (*paaiVar7)[3][1] = DAT_SiegeInformationArray::instance[10];
            (*paaiVar7)[3][2] = DAT_SiegeInformationArray::instance[0xb];
            (*paaiVar7)[4][0] = DAT_SiegeInformationArray::instance[0xc];
            (*paaiVar7)[4][1] = DAT_SiegeInformationArray::instance[0xd];
            (*paaiVar7)[4][2] = DAT_SiegeInformationArray::instance[0xe];
            (*paaiVar7)[5][0] = DAT_SiegeInformationArray::instance[0xf];
            (*paaiVar7)[5][1] = iVar12;
            (*paaiVar7)[5][2] = iVar11;
            (*paaiVar7)[6][0] = iVar9;
            (*paaiVar7)[6][1] = iVar1;
            (*paaiVar7)[6][2] = iVar2;
            paaiVar7 = paaiVar7 + 1;
        } while ((int)paaiVar7 < 0xb95ab8);
        if (param_1 != 1) {
            iVar11 = DAT_RenderingDefinedData::instance.field1027_0x5493c[param_1 + -0x18];
            iVar12 = 0;
            iVar9 = 0;
            piVar14 = DAT_SiegeInformationArray_2::instance[param_1][0] + 1;
            do {
                iVar1 = *(int*)((int)DAT_RenderingDefinedData::instance.NoRushTicks + iVar9 + 0x74);
                iVar10 = iVar9 + 0xc;
                *(int*)((int)DAT_SiegeInformationArray_2::instance[1][0] + iVar9)
                    = ((*(int (*)[3])(piVar14 + -1))[0] * 100) / iVar11;
                *(int*)((int)DAT_SiegeInformationArray_2::instance[1][0] + iVar9 + 4) = (*piVar14 * 100) / iVar11;
                iVar8 = (piVar14[1] * 100) / iVar11;
                iVar2 = *(int*)((int)DAT_RenderingDefinedData::instance.NoRushTicks + iVar9 + 0x6c);
                iVar6 = *(int*)((int)DAT_SiegeInformationArray_2::instance[1][0] + iVar9);
                *(int*)((int)DAT_SiegeInformationArray_2::instance[1][0] + iVar9 + 8) = iVar8;
                iVar12 = *(int*)((int)DAT_RenderingDefinedData::instance.NoRushTicks + iVar9 + 0x70)
                        * *(int*)((int)DAT_SiegeInformationArray_2::instance[1][0] + iVar9 + 4)
                    + iVar12 + iVar2 * iVar6 + iVar1 * iVar8;
                iVar9 = iVar10;
                piVar14 = piVar14 + 3;
            } while (iVar10 < 0x54);
            DAT_00b960bc::instance = iVar13 - iVar12;
            if (DAT_00b960bc::instance < 0) {
                DAT_00b960bc::instance = 0;
            }
        }
        local_18 = 0;
        local_14 = DAT_SiegeInformationArray_2::instance[0][0] + 1;
        do {
            if ((local_18 != param_1) && (local_18 != 1)) {
                iVar12 = DAT_RenderingDefinedData::instance.field1027_0x5493c[local_18 + -0x18];
                iVar13 = 0;
                iVar11 = 0;
                piVar14 = local_14;
                do {
                    (*(int (*)[3])(piVar14 + -1))[0]
                        = (*(int*)((int)DAT_SiegeInformationArray_2::instance[1][0] + iVar11) * iVar12) / 100;
                    *piVar14 = (*(int*)((int)DAT_SiegeInformationArray_2::instance[1][0] + iVar11 + 4) * iVar12) / 100;
                    iVar9 = *(int*)((int)DAT_RenderingDefinedData::instance.NoRushTicks + iVar11 + 0x6c);
                    iVar1 = (*(int (*)[3])(piVar14 + -1))[0];
                    iVar10 = (*(int*)((int)DAT_SiegeInformationArray_2::instance[1][0] + iVar11 + 8) * iVar12) / 100;
                    iVar2 = *(int*)((int)DAT_RenderingDefinedData::instance.NoRushTicks + iVar11 + 0x70);
                    iVar6 = *piVar14;
                    iVar8 = *(int*)((int)DAT_RenderingDefinedData::instance.NoRushTicks + iVar11 + 0x74);
                    piVar14[1] = iVar10;
                    iVar11 = iVar11 + 0xc;
                    piVar14 = piVar14 + 3;
                    iVar13 = iVar2 * iVar6 + iVar9 * iVar1 + iVar8 * iVar10 + iVar13;
                } while (iVar11 < 0x54);
                iVar12 = local_10[local_18];
                (INT_00b960b8::ptr)[local_18] = iVar12 - iVar13;
                if (iVar12 - iVar13 < 0) {
                    (INT_00b960b8::ptr)[local_18] = 0;
                }
            }
            local_14 = local_14 + 0x15;
            local_18 = local_18 + 1;
        } while ((int)local_14 < 0xb95abc);
    }

}
}
