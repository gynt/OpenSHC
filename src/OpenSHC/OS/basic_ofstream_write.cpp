#include "../OS.func.hpp"

#include "OpenSHC/Globals/EH_FUN_00599f20.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

#include "HoldStrong_lib.func.hpp"
#include "HoldStrong_lib/LockClass1.func.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x004791B0
int* __stdcall OS::basic_ofstream_write(void* param_1, uint param_2)
{
    byte bVar1;
    int* piVar2;
    int* piVar3;
    byte* pbVar4;
    undefined1* puVar5;
    bool bVar6;
    uint uVar7;
    int iVar8;
    uint uVar9;
    int* unaff_FS_OFFSET;
    uint uStack_34;
    int* local_24;
    char local_20;
    undefined4 local_1c;
    int local_18;
    undefined1* local_14;
    int local_10;
    code* pcStack_c;
    undefined4 local_8;
    local_8 = 0xffffffff;
    pcStack_c = HoldStrong_lib::EH_FUN_00599f20::instance;
    local_10 = *unaff_FS_OFFSET;
    uStack_34 = MSVC_SecurityCookie::instance ^ (uint)&stack0xfffffffc;
    local_14 = (undefined1*)&uStack_34;
    *unaff_FS_OFFSET = (int)&local_10;
    uVar9 = 0;
    local_1c = 0;
    MACRO_CALL(HoldStrong_lib_Func::FUN_00478dc0)(&local_24, param_1);
    if (local_20 != '\0') {
        local_18 = *(int*)(*(int*)(*(int*)param_1 + 4) + 0x18 + (int)param_1);
        if (local_18 < 2) {
            local_18 = 0;
        } else {
            local_18 = local_18 + -1;
        }
        local_8 = 1;
        if ((*(uint*)((int)param_1 + *(int*)(*(int*)param_1 + 4) + 0x10) & 0x1c0) == 0x40) {
        LAB_00479280:
            piVar2 = *(int**)(*(int*)(*(int*)param_1 + 4) + 0x28 + (int)param_1);
            if ((*(int*)piVar2[9] == 0) || (piVar3 = (int*)piVar2[0xd], *piVar3 < 1)) {
                uVar7 = (**(code**)(*piVar2 + 4))(param_2 & 0xff);
            } else {
                *piVar3 = *piVar3 + -1;
                puVar5 = *(undefined1**)piVar2[9];
                *(undefined1**)piVar2[9] = puVar5 + 1;
                *puVar5 = (undefined1)param_2;
                uVar7 = param_2 & 0xff;
            }
            if (uVar7 == 0xffffffff) {
                uVar9 = 4;
                local_1c = 4;
            }
            for (; (!uVar9 && (0 < local_18)); local_18 = local_18 + -1) {
                bVar1 = *(byte*)(*(int*)(*(int*)param_1 + 4) + 0x30 + (int)param_1);
                piVar2 = *(int**)((int)param_1 + *(int*)(*(int*)param_1 + 4) + 0x28);
                if ((*(int*)piVar2[9] == 0) || (piVar3 = (int*)piVar2[0xd], *piVar3 < 1)) {
                    uVar7 = (**(code**)(*piVar2 + 4))(bVar1);
                } else {
                    *piVar3 = *piVar3 + -1;
                    pbVar4 = *(byte**)piVar2[9];
                    *(byte**)piVar2[9] = pbVar4 + 1;
                    *pbVar4 = bVar1;
                    uVar7 = (uint)bVar1;
                }
                if (uVar7 == 0xffffffff) {
                    uVar9 = 4;
                    local_1c = 4;
                }
            }
        } else {
            while (!uVar9) {
                if (local_18 < 1)
                    goto LAB_00479280;
                bVar1 = *(byte*)((int)param_1 + *(int*)(*(int*)param_1 + 4) + 0x30);
                piVar2 = *(int**)((int)param_1 + *(int*)(*(int*)param_1 + 4) + 0x28);
                if ((*(int*)piVar2[9] == 0) || (piVar3 = (int*)piVar2[0xd], *piVar3 < 1)) {
                    uVar7 = (**(code**)(*piVar2 + 4))(bVar1);
                } else {
                    *piVar3 = *piVar3 + -1;
                    pbVar4 = *(byte**)piVar2[9];
                    *(byte**)piVar2[9] = pbVar4 + 1;
                    *pbVar4 = bVar1;
                    uVar7 = (uint)bVar1;
                }
                if (uVar7 == 0xffffffff) {
                    uVar9 = 4;
                    local_1c = 4;
                }
                local_18 = local_18 + -1;
            }
        }
    }
    local_8 = 0;
    *(undefined4*)((int)param_1 + *(int*)(*(int*)param_1 + 4) + 0x18) = 0;
    iVar8 = *(int*)(*(int*)param_1 + 4) + (int)param_1;
    if (uVar9) {
        uVar9 = *(uint*)(iVar8 + 8) | uVar9;
        if (*(int*)(iVar8 + 0x28) == 0) {
            uVar9 = uVar9 | 4;
        }
        MACRO_CALL(HoldStrong_lib_Func::FUN_00477540)(iVar8, uVar9, '\0');
    }
    local_8 = 6;
    bVar6 = MACRO_CALL(HoldStrong_lib_Func::thunk_FUN_00586363)();
    if (!bVar6) {
        MACRO_CALL(HoldStrong_lib_Func::FUN_00478e50)(local_24);
    }
    iVar8 = *(int*)(*(int*)(*local_24 + 4) + 0x28 + (int)local_24);
    local_8 = 0xffffffff;
    if (iVar8) {
        MACRO_CALL_MEMBER(HoldStrong_lib::LockClass1_Func::releaseLock, (LockClass1*)(iVar8 + 4))();
    }
    *unaff_FS_OFFSET = local_10;
    return (int*)(param_1);
}

}
