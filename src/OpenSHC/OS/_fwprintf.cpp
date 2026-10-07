#include "../OS.func.hpp"

#include "HoldStrong_lib.func.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x005807A8
int OS::_fwprintf(FILE* param_1, WCHAR_CONST* param_2, ...)
{
    DWORD* pDVar1;
    int iVar2;
    int extraout_EAX;
    if ((param_1 == (FILE*)0x0) || (param_2 == (WCHAR_CONST*)0x0)) {
        pDVar1 = MACRO_CALL(HoldStrong_lib_Func::FUN_00589837)();
        *pDVar1 = 0x16;
        MACRO_CALL(HoldStrong_lib_Func::FUN_005825fa)((wchar_t*)0x0, (wchar_t*)0x0, (wchar_t*)0x0, 0, 0);
        iVar2 = -1;
    } else {
        /*
          1 arg
         */
        MACRO_CALL(HoldStrong_lib_Func::FUN_0058c5fb)((uint)param_1);
        /*
          1 arg
         */
        iVar2 = MACRO_CALL(HoldStrong_lib_Func::__stbuf)(param_1);
        /*
          0x1c - (4*4) / 4 = 3 arg
         */
        MACRO_CALL(HoldStrong_lib_Func::FUN_0058d200)(
            (int)param_1, (ushort*)((int)(param_2)), (localeinfo_struct*)0x0, (wchar_t*)&stack0x0000000c);
        /*
          2 arg
         */
        MACRO_CALL(HoldStrong_lib_Func::FUN_0058de02)(iVar2, param_1);
        /*
          0 arg
         */
        MACRO_CALL(HoldStrong_lib_Func::FUN_00580832)();
        iVar2 = extraout_EAX;
    }
    return iVar2;
}

}
