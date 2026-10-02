#include "../Helpers.func.hpp"

#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_MissionScores.hpp"

namespace OpenSHC {
namespace UI {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004DAF50
    void Helpers::LoadScoresFileToMemory(char* filename)
    {
        FILE* _File;
        int* dstBuffer;
        _File = MACRO_CALL(OpenSHC::OS_Func::_fopen)(filename, "rb");
        if (_File != (FILE*)0x0) {
            MACRO_CALL(OpenSHC::OS_Func::_fseek)(_File, 4, FILE_BEGIN);
            dstBuffer = DAT_MissionScores::instance;
            do {
                MACRO_CALL(OpenSHC::OS_Func::_fread)(dstBuffer, 4, 1, _File);
                dstBuffer = dstBuffer + 1;
            } while ((int)dstBuffer < 0xed27f0);
            MACRO_CALL(OpenSHC::OS_Func::_fclose)(_File);
        }
        return;
    }

}
}
