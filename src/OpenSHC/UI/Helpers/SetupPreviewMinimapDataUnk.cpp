#include "../Helpers.func.hpp"

#include "OpenSHC/IO/FilePackager.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/FilePackagerObj.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Game::GameMode;
    using OpenSHC::IO::FileResourceType;
    using OpenSHC::UI::Enums::MenuViewType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00493050
    void Helpers::SetupPreviewMinimapDataUnk()
    {
        char cVar1;
        int iVar2;
        char* pcVar3;
        undefined4 uVar4;
        char* pcVar5;
        FileResourceType resourceType;
        char local_3f4[4];
        char local_3f0[1004];
        uint local_4;
        local_4 = MSVC_SecurityCookie::instance ^ (uint)local_3f4;
        iVar2 = DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionIndex
            + DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset;
        if ((iVar2 == -1) || (DAT_MenuTextInputState::instance.field43_0xa0 == iVar2))
            goto LAB_00493187;
        DAT_MenuTextInputState::instance.field43_0xa0 = iVar2;
        pcVar3 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
            DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar2 + -1]);
        pcVar5 = local_3f4;
        do {
            cVar1 = *pcVar3;
            *pcVar5 = cVar1;
            pcVar3 = pcVar3 + 1;
            pcVar5 = pcVar5 + 1;
        } while (cVar1 != '\0');
        if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_UNUSED_CREATE_SIEGE) {
            pcVar3 = (local_3f4 - 1);
            do {
                pcVar5 = pcVar3 + 1;
                pcVar3 = pcVar3 + 1;
            } while (*pcVar5 != '\0');
            (*(char*)&uVar4) = '.';
            (*(char*)((char*)&uVar4 + 1)) = 't';
            (*(char*)((char*)&uVar4 + 2)) = 'm';
            (*(char*)((char*)&uVar4 + 3)) = 'p';
        LAB_00493166:
            *(undefined4*)pcVar3 = uVar4;
            pcVar3[4] = '\0';
            resourceType = OpenSHC::IO::FRT_MAPS;
        } else {
            if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_CUSTOM_SCENARIOS) {
                pcVar3 = (local_3f4 - 1);
                do {
                    pcVar5 = pcVar3 + 1;
                    pcVar3 = pcVar3 + 1;
                } while (*pcVar5 != '\0');
                (*(char*)&uVar4) = '.';
                (*(char*)((char*)&uVar4 + 1)) = 'm';
                (*(char*)((char*)&uVar4 + 2)) = 'a';
                (*(char*)((char*)&uVar4 + 3)) = 'p';
                goto LAB_00493166;
            }
            if ((DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY)
                || (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)) {
                pcVar3 = (local_3f4 - 1);
                do {
                    pcVar5 = pcVar3;
                    pcVar3 = pcVar5 + 1;
                } while (pcVar5[1] != '\0');
                strcpy(pcVar5 + 1, ".sav");
                resourceType = OpenSHC::IO::FRT_UNKNOWN;
            } else {
                pcVar3 = (local_3f4 - 1);
                do {
                    pcVar5 = pcVar3;
                    pcVar3 = pcVar5 + 1;
                } while (pcVar5[1] != '\0');
                strcpy(pcVar5 + 1, ".msv");
                resourceType = OpenSHC::IO::FRT_UNKNOWN;
            }
        }
        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
            resourceType, (char const*)((int)(local_3f4)));
        MACRO_CALL_MEMBER(OpenSHC::IO::FilePackager_Func::readMapHeader, FilePackagerObj::ptr)(TRUE);
    LAB_00493187:;
    }

}
}
