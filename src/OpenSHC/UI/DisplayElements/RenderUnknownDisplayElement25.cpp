#include "../DisplayElements.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

#include "HoldStrong_lib.func.hpp"

namespace OpenSHC {
namespace UI {

    using Rendering::Enums::RenderTarget;
    using Text::TextAlignment;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004B0820
    void DisplayElements::RenderUnknownDisplayElement25(int posX, int posY, DWORD elementState)
    {
        char cVar1;
        bool bVar2;
        char* pcVar3;
        int iVar4;
        int iVar5;
        int iVar6;
        int iVar7;
        int iVar8;
        int local_84;
        int local_80;
        int local_7c;
        int local_78;
        int* local_74;
        char (*local_70)[250];
        int local_6c;
        undefined4 local_68;
        undefined1 local_5;
        uint local_4;
        local_4 = MSVC_SecurityCookie::instance ^ (uint)&local_84;
        iVar6 = posX + -0x5f;
        local_6c = 0x5f - posX;
        local_74 = &DAT_GameState::instance.playerDataArray[1].field695_0x229c;
        local_70 = DAT_GameSynchronyState::instance.DAT_PlayerNames + 1;
        local_80 = 0;
        local_7c = iVar6;
        do {
            if (*(int*)((int)DAT_GameSynchronyState::instance.currentPlayerFullIDArray + local_80 + 4) != -1) {
                MACRO_CALL(HoldStrong_lib_Func::FUN_00583630)(&local_68, (uint*)((int)(local_70)), 99);
                pcVar3 = (char*)&local_68;
                local_5 = 0;
                do {
                    cVar1 = *pcVar3;
                    pcVar3 = pcVar3 + 1;
                } while (cVar1 != '\0');
                iVar4 = (int)pcVar3 - ((int)&local_68 + 1);
                iVar8 = 0;
                iVar7 = 0;
                if (0 < iVar4) {
                    do {
                        if (*(char*)((int)&local_68 + iVar7) == '\n') {
                            *(undefined1*)((int)&local_68 + iVar7) = 0x20;
                        }
                        iVar5 = MACRO_CALL_MEMBER(Text::TextManager_Func::getCharWidth,
                            DAT_TextManagerObject::ptr)(*(char*)((int)&local_68 + iVar7), 0x12);
                        iVar8 = iVar8 + iVar5;
                        if (0xaa < iVar8) {
                            *(undefined1*)((int)&local_68 + iVar7) = 0;
                            break;
                        }
                        iVar7 = iVar7 + 1;
                    } while (iVar7 < iVar4);
                }
                DAT_PencilRenderCore::instance.surfaceTarget = Rendering::Enums::RT_MAP_GAME;
                MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(iVar6, posY + -5, iVar6 + 0xbe, posY + 0x32, 0x10);
                bVar2 = false;
                DAT_PencilRenderCore::instance.surfaceTarget = Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow,
                    DAT_TextManagerObject::ptr)((char const*)&local_68, iVar6 + 0x5f, posY, Text::TTA_CENTER,
                    (uint)((int)(DAT_RenderingDefinedData::instance.ColorArray[*(
                        int*)((int)DAT_BlendingDefinedData::instance.PlayerSlotUnitColor + local_80 + 4)])),
                    0, 0x12, FALSE, 0);
                if (DAT_GameSynchronyState::instance.skirmishPoints < 1000000) {
                    if (DAT_GameSynchronyState::instance.skirmishPoints < 100000) {
                        if (DAT_GameSynchronyState::instance.skirmishPoints < 10000) {
                            if (DAT_GameSynchronyState::instance.skirmishPoints < 1000) {
                                if (DAT_GameSynchronyState::instance.skirmishPoints < 100) {
                                    local_84 = ((DAT_GameSynchronyState::instance.skirmishPoints < 10) - 1 & 0xb) + 0xb;
                                } else {
                                    local_84 = 33;
                                }
                            } else {
                                local_84 = 44;
                            }
                        } else {
                            local_84 = 55;
                        }
                    } else {
                        local_84 = 66;
                    }
                } else {
                    local_84 = 77;
                }
                iVar4 = 10000000;
                local_78 = 7;
                iVar6 = iVar6 + local_6c;
                iVar7 = 0x4d;
                do {
                    iVar8 = (*local_74 / iVar4) % 10;
                    if (((iVar8 != 0) || (bVar2)) || (local_78 == 0)) {
                        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                            iVar8, (local_84 / 2 - iVar7) + iVar6 + posX, posY + 0x19, Text::TTA_RIGHT,
                            (uint)((int)(DAT_RenderingDefinedData::instance.ColorArray[*(
                                int*)((int)DAT_BlendingDefinedData::instance.PlayerSlotUnitColor + local_80 + 4)])),
                            0, 0x11, FALSE, 0);
                        bVar2 = true;
                    }
                    iVar4 = iVar4 / 10;
                    if (iVar4 < 1) {
                        iVar4 = 1;
                    }
                    local_78 = local_78 + -1;
                    iVar7 = iVar7 + -0xb;
                } while (-1 < iVar7);
                iVar6 = local_7c + 200;
                local_7c = iVar6;
            }
            local_74 = local_74 + 0xe7d;
            local_80 = local_80 + 4;
            local_70 = local_70 + 1;
            if (0x1a23c4d < (int)local_70) {
                ;
                return;
            }
        } while (true);
    }

}
}
