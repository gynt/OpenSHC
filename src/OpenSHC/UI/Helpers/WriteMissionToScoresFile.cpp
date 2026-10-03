#include "../Helpers.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_MissionScores.hpp"
#include "OpenSHC/Globals/INT_00ec0828.hpp"
#include "OpenSHC/Globals/INT_00ed2790.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004E1810
    void Helpers::WriteMissionToScoresFile(char* param_1, int param_2)
    {
        FILE* _fileHandle;
        FILE* _fileHandle2;
        FILE* _File;
        int iVar1;
        int iVar2;
        int* piVar3;
        int local_2c[11];
        INT_00ed2790::instance = -1;
        DAT_MissionScores::instance[0] = 0;
        DAT_MissionScores::instance[1] = 0;
        DAT_MissionScores::instance[2] = 0;
        DAT_MissionScores::instance[3] = 0;
        DAT_MissionScores::instance[4] = 0;
        DAT_MissionScores::instance[5] = 0;
        DAT_MissionScores::instance[6] = 0;
        DAT_MissionScores::instance[7] = 0;
        DAT_MissionScores::instance[8] = 0;
        DAT_MissionScores::instance[9] = 0;
        _fileHandle = MACRO_CALL(OpenSHC::OS_Func::_fopen)(param_1, "rb");
        local_2c[0] = 1;
        if ((_fileHandle == (FILE*)0x0)
            || (MACRO_CALL(OpenSHC::OS_Func::_fread)(local_2c, 4, 1, _fileHandle), local_2c[0] != 1)) {
            local_2c[0] = 0;
            _fileHandle2 = MACRO_CALL(OpenSHC::OS_Func::_fopen)(param_1, "wb");
            if (_fileHandle2 == (FILE*)0x0) {}
            local_2c[0] = 1;
            MACRO_CALL(OpenSHC::OS_Func::_fwrite)(local_2c, 4, 1, _fileHandle2);
            if (param_2 < 0) {
                param_2 = 0;
            } else {
                INT_00ed2790::instance = 0;
            }
            MACRO_CALL(OpenSHC::OS_Func::_fwrite)(&param_2, 4, 1, _fileHandle2);
            local_2c[0] = 0;
            iVar2 = 9;
            do {
                MACRO_CALL(OpenSHC::OS_Func::_fwrite)(local_2c, 4, 1, _fileHandle2);
                iVar2 = iVar2 + -1;
            } while (iVar2 != 0);
            MACRO_CALL(OpenSHC::OS_Func::_fclose)(_fileHandle2);
            INT_00ec0828::instance = 0;
            MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadScoresFileToMemory)(param_1);
        }
        piVar3 = local_2c;
        iVar2 = 10;
        do {
            piVar3 = (int*)((int)piVar3 + 4);
            MACRO_CALL(OpenSHC::OS_Func::_fread)(piVar3, 4, 1, _fileHandle);
            iVar2 = iVar2 + -1;
        } while (iVar2 != 0);
        MACRO_CALL(OpenSHC::OS_Func::_fclose)(_fileHandle);
        INT_00ec0828::instance = local_2c[1];
        iVar2 = 0;
        while (param_2 <= local_2c[iVar2 + 1]) {
            iVar2 = iVar2 + 1;
            if (9 < iVar2) {}
        }
        iVar1 = 9;
        if (iVar2 < 9) {
            do {
                local_2c[iVar1 + 1] = local_2c[iVar1];
                iVar1 = iVar1 + -1;
            } while (iVar2 < iVar1);
        }
        local_2c[iVar2 + 1] = param_2;
        local_2c[0] = 1;
        INT_00ed2790::instance = iVar2;
        _File = MACRO_CALL(OpenSHC::OS_Func::_fopen)(param_1, "wb");
        if (_File == (FILE*)0x0) {}
        local_2c[0] = 1;
        MACRO_CALL(OpenSHC::OS_Func::_fwrite)(local_2c, 4, 1, _File);
        piVar3 = local_2c;
        iVar2 = 10;
        do {
            piVar3 = (int*)((int)piVar3 + 4);
            MACRO_CALL(OpenSHC::OS_Func::_fwrite)(piVar3, 4, 1, _File);
            iVar2 = iVar2 + -1;
        } while (iVar2 != 0);
        MACRO_CALL(OpenSHC::OS_Func::_fclose)(_File);
        MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadScoresFileToMemory)(param_1);
    }

}
}
