#include "../Chat.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

#include "HoldStrong_lib.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using DE::SHCDE::eTextSections;
        using Rendering::Enums::RenderTarget;
        using Text::TextAlignment;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0047FD50
        void Chat::MenuItemRenderFunction_Chat_MostButtons(int param_1, ...)
        {
            char cVar1;
            RGB15 color;
            char* pcVar2;
            int iVar3;
            int iVar4;
            int iVar5;
            int iVar6;
            TextAlignment alignment;
            BGR24 BVar7;
            BOOLEnum keepOffsetX;
            undefined4 local_68;
            undefined1 local_5;
            uint local_4;
            local_4 = MSVC_SecurityCookie::instance ^ (uint)&local_68;
            iVar6 = 0;
            DAT_ButtonUnknownZero::instance = 0;
            if (-1 < param_1) {
                MACRO_CALL_MEMBER(UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, Rendering::Enums::RT_CONTEXT_BASED);
                iVar4 = 0;
                iVar6 = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                iVar3 = DAT_ButtonY::instance + 7;
                keepOffsetX = FALSE;
                iVar5 = 0x12;
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    BVar7 = 0xc2f0eb;
                } else {
                    BVar7 = 0xccfaff;
                }
                alignment = Text::TTA_CENTER;
                pcVar2 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, param_1);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    pcVar2, iVar6, iVar3, alignment, BVar7, iVar5, keepOffsetX, iVar4);
                ;
                return;
            }
            if (*(int*)((int)DAT_GameSynchronyState::ptr + param_1 * -4 + 0x6a8) == -1) {
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
                DAT_ButtonUnknownZero::instance = 1;
                ;
                return;
            }
            MACRO_CALL(HoldStrong_lib_Func::FUN_00583630)(
                &local_68, (uint*)((int)(((int)DAT_GameSynchronyState::ptr + param_1 * -0xfa + 0x105c1c))), 99);
            pcVar2 = (char*)&local_68;
            local_5 = 0;
            do {
                cVar1 = *pcVar2;
                pcVar2 = pcVar2 + 1;
            } while (cVar1 != '\0');
            iVar3 = (int)pcVar2 - ((int)&local_68 + 1);
            iVar5 = 0;
            if (0 < iVar3) {
                do {
                    iVar4 = MACRO_CALL_MEMBER(Text::TextManager_Func::getCharWidth,
                        DAT_TextManagerObject::ptr)(*(char*)((int)&local_68 + iVar5), 0x12);
                    iVar6 = iVar6 + iVar4;
                    if (0xaa < iVar6) {
                        *(undefined1*)((int)&local_68 + iVar5) = 0;
                        break;
                    }
                    iVar5 = iVar5 + 1;
                } while (iVar5 < iVar3);
            }
            DAT_ButtonCurrentlyInteracting::instance
                = (BOOLEnum)(*(int*)((int)DAT_GameSynchronyState::ptr + param_1 * -4 + 0x109264) != 0);
            MACRO_CALL_MEMBER(UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                AlphaAndButtonSurfaceObj::ptr)(0, Rendering::Enums::RT_CONTEXT_BASED);
            if (!DAT_ButtonCurrentlyInteracting::instance) {
                BVar7 = DAT_RenderingDefinedData::instance
                            .ColorArray[*(int*)((int)DAT_BlendingDefinedData::ptr + param_1 * -4 + 0x2738)];
            } else {
                BVar7 = DAT_RenderingDefinedData::instance
                            .ColorArray[*(int*)((int)DAT_BlendingDefinedData::ptr + param_1 * -4 + 0x2738)];
            }
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)&local_68, (int)((int)(DAT_ButtonX::instance + 5)), (int)((int)(DAT_ButtonY::instance + 7)),
                Text::0xaa, BVar7, 0x12, FALSE, 0);
            iVar6 = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::countPlayersInSameTeam,
                DAT_GameSynchronyState::ptr)(-param_1);
            if (1 < iVar6) {
                iVar6 = 0;
                for (iVar3 = 0; iVar3 < 0x20; iVar3 += 4) {
                    if (*(int*)((int)DAT_GameState::instance.mapAndTime.playerTeams + iVar3 + 4)
                        == *(int*)((int)DAT_GameState::ptr + param_1 * -4 + 0x52490)) {
                        iVar5 = iVar6 + DAT_ButtonX::instance;
                        color = MACRO_CALL_MEMBER(
                            UI::Rendering::TextureRenderCore_Func::transformBGR24ToScreenColor,
                            DAT_TextureRenderCoreObject::ptr)(DAT_RenderingDefinedData::instance.ColorArray[*(
                            int*)((int)DAT_BlendingDefinedData::instance.PlayerSlotUnitColor + iVar3 + 4)]);
                        MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawColorBox,
                            DAT_PencilRenderCore::ptr)(iVar5 + 4, (int)((int)(DAT_ButtonY::instance + 4)), iVar5 + 0xc,
                            (int)((int)(DAT_ButtonY::instance + 6)), (ushort)((int)(color)));
                        iVar6 = iVar6 + 7;
                    }
                }
            };
            return;
        }

    }
}
}
