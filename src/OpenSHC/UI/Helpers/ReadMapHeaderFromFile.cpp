#include "../Helpers.func.hpp"

#include "OpenSHC/IO/FilePackager.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/FilePackagerObj.hpp"
#include "OpenSHC/Globals/INT_00eb9ae8.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::IO::FileResourceType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004D8A20
    void Helpers::ReadMapHeaderFromFile(char* param_1)
    {
        char cVar1;
        int iVar2;
        uint uVar3;
        char* puVar4;
        char local_3f4[1008];
        char* puVar3;
        uVar3 = MSVC_SecurityCookie::instance ^ (uint)local_3f4;
        iVar2 = -(int)param_1;
        do {
            cVar1 = *param_1;
            param_1[(int)(local_3f4 + iVar2)] = cVar1;
            param_1 = param_1 + 1;
        } while (cVar1 != '\0');
        puVar3 = (local_3f4 - 1);
        do {
            puVar4 = puVar3;
            puVar3 = puVar4 + 1;
        } while (puVar4[1] != '\0');
        strcpy(puVar4 + 1, ".map");
        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
            OpenSHC::IO::FRT_MAPS, (char const*)((int)(local_3f4)));
        MACRO_CALL_MEMBER(OpenSHC::IO::FilePackager_Func::readMapHeader, FilePackagerObj::ptr)(TRUE);
        INT_00eb9ae8::instance = 1;
        ;
    }

}
}
