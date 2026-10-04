#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/OS.func.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047E490
    void GameSynchronyState::readGameSpyConfig()
    {
        char* pcVar1;
        LONG LVar2;
        char* pcVar3;
        FILE* _File;
        undefined2* puVar4;
        HKEY__* local_c;
        DWORD local_8;
        DWORD local_4;
        local_8 = 0x200;
        this->gameSpyArcadeAvailable = 0;
        LVar2 = RegOpenKeyExA((HKEY__*)0x80000001, "Software\\GameSpy\\GameSpy Arcade", 0, 0x20019, &local_c);
        if (LVar2 == 0) {
            LVar2 = RegQueryValueExA(
                local_c, "InstDir", (DWORD*)0x0, &local_4, (BYTE*)this->shellExecuteTarget, &local_8);
            RegCloseKey(local_c);
            pcVar1 = this->shellExecuteTarget;
            if (LVar2 == 0) {
                do {
                    pcVar3 = pcVar1;
                    pcVar1 = pcVar3 + 1;
                } while (*pcVar3 != '\0');
                if (*pcVar3 != '\\') {
                    puVar4 = (undefined2*)((int)&this->willHost + 3);
                    do {
                        pcVar1 = (char*)((int)puVar4 + 1);
                        puVar4 = (undefined2*)((int)puVar4 + 1);
                    } while (*pcVar1 != '\0');
                    *puVar4 = 0x5c;
                }
                pcVar1 = (char*)((int)&this->willHost + 3);
                do {
                    pcVar3 = pcVar1;
                    pcVar1 = pcVar3 + 1;
                } while (pcVar3[1] != '\0');
                strcpy(pcVar3 + 1, "aphex.exe");
                _File = MACRO_CALL(OS_Func::_fopen)(this->shellExecuteTarget, "rb");
                if (_File != (FILE*)0x0) {
                    this->gameSpyArcadeAvailable = 1;
                    MACRO_CALL(OS_Func::_fclose)(_File);
                }
            }
        }
    }

}
}
