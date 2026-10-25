#include "../AlliesSendAndRequestGoods.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RequestedGoodsByWhoArray.hpp"
#include "OpenSHC/Globals/DAT_SentOrRequestedGoodsAmount.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eGM;
        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::IO::Graphics::GmID;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004AD920
        void AlliesSendAndRequestGoods::MenuItemRenderFunction_AlliesSendAndRequestGoods_Main(int actionParam, ...)
        {
            int iVar1;
            int iVar2;
            int iVar3;
            int iVar4;
            eTextSections offsetIndex;
            int iVar5;
            BOOLEnum keepOffsetX;
            int _gmID;
            /*
              first render resource type in condensed form
             */
            if (actionParam < 20) {
                int _xOffset = 0;
                if (actionParam == 6 || actionParam == 0xb || actionParam == 0x14) {
                    _xOffset = 8;
                }
                /*
                  skip unusable resources
                 */
                if (4 <= actionParam) {
                    actionParam = actionParam + 1;
                }
                if (6 <= actionParam) {
                    actionParam = actionParam + 1;
                }
                if (actionParam == 0xe) {
                    actionParam = 0x17;
                }
                _gmID = actionParam * 2 + 0x269;
                if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                    _gmID = actionParam * 2 + 0x26a;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, _gmID,
                    DAT_ButtonX::instance + _xOffset, (int)(DAT_ButtonY::instance));
                if (actionParam == 7) {
                    actionParam = 6;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[actionParam + 1],
                    (int)(DAT_ButtonX::instance + 0x15), (int)(DAT_ButtonY::instance + 0x28), OpenSHC::Text::TTA_CENTER,
                    0xc2f0eb, 0, 0x13, FALSE, 0);
            } else if (actionParam == 21) {
                if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                    iVar1 = 0x285;
                } else {
                    iVar1 = 0x286;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar1,
                    (int)(DAT_ButtonX::instance), (int)(DAT_ButtonY::instance));
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[0xf],
                    (int)(DAT_ButtonX::instance + 0x15), (int)(DAT_ButtonY::instance + 0x14), OpenSHC::Text::TTA_CENTER,
                    0xc2f0eb, 0, 0x13, FALSE, 0);
                return;
            }
            iVar5 = DAT_ButtonY::instance;
            iVar1 = DAT_ButtonX::instance;
            /*
              then draw the rest
             */
            if (actionParam == 40) {
                /*
                  everything below belongs to actionParam == 40 only
                 */
                if (0 < (int)DAT_ButtonH::instance) {
                    for (int iVar2 = 0; iVar2 < (int)DAT_ButtonH::instance; iVar2 = iVar2 + 24) {
                        if (iVar2 == 0) {
                        iVar3 = 1;
                        } else {
                        if (iVar2 == DAT_ButtonH::instance + -0x18) {
                            iVar3 = 0xd;
                        } else {
                            iVar3 = 0x7;
                        }
                        }
                        iVar4 = 0;
                        do {
                        int imageID = iVar3;
                        if (iVar4 == 0) {
                        LAB_004adacf:
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                                imageID, iVar4 + iVar1, iVar2 + iVar5, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                                imageID + 3, 0);
                        } else {
                            if (iVar4 == 0x210) {
                                imageID = iVar3 + 2;
                                goto LAB_004adacf;
                            }
                            if (iVar3 != 7) {
                                imageID = iVar3 + 1;
                                goto LAB_004adacf;
                            }
                            return;
                        }
                        iVar4 = iVar4 + 0x18;
                        } while (iVar4 < 0x228);
                    }
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox, DAT_PencilRenderCore::ptr)(
                    iVar1 + 0x18, iVar5 + 0x18, iVar1 + 0x20f, DAT_ButtonH::instance + -0x19 + iVar5, 0x14);
                if (DAT_RequestedGoodsByWhoArray::instance[0] == 6) {
                    iVar1 = 7;
                LAB_004adb48:
                    if (DAT_SentOrRequestedGoodsAmount::instance != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                            DAT_SentOrRequestedGoodsAmount::instance, (int)(DAT_ButtonX::instance + 0x24),
                            (int)(DAT_ButtonY::instance + 0x24), OpenSHC::Text::TTA_LEFT, 0xccfaff, 0, 0x11, FALSE, 0);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                            iVar1 * 2 + 0x26a,
                            (int)(DAT_TextManagerObject::instance.currentXOffset_0x0 + 0x2e + DAT_ButtonX::instance),
                            (int)(DAT_ButtonY::instance + 0x18));
                        keepOffsetX = TRUE;
                        iVar1 = DAT_ButtonX::instance + 0x60;
                        iVar5 = DAT_RequestedGoodsByWhoArray::instance[0] + 1;
                        offsetIndex = OpenSHC::DE::SHCDE::TEXT_GOODS;
                        goto LAB_004adbc8;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar1 * 2 + 0x26a,
                        (int)(DAT_ButtonX::instance + 0x24), (int)(DAT_ButtonY::instance + 0x18));
                    iVar1 = DAT_ButtonX::instance + 0x54;
                    iVar5 = 0xe;
                } else {
                    iVar1 = DAT_RequestedGoodsByWhoArray::instance[0];
                    if (0 < DAT_RequestedGoodsByWhoArray::instance[0])
                        goto LAB_004adb48;
                    iVar1 = DAT_ButtonX::instance + 0x24;
                    iVar5 = 0xd;
                }
                keepOffsetX = FALSE;
                offsetIndex = OpenSHC::DE::SHCDE::TEXT_ALLIES;
            LAB_004adbc8:
                iVar2 = DAT_ButtonY::instance + 0x24;
                iVar4 = 0;
                iVar3 = 0x11;
                /*
                  added by script: "Choose Goods"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(offsetIndex, iVar5),
                    iVar1, iVar2, OpenSHC::Text::TTA_LEFT, 0xccfaff, iVar3, keepOffsetX, iVar4);
                return;
            }
            if (0x64 <= actionParam) {
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderButtonImageWithBlending)();
                return;
            }
            /*
              the original ends this bound with `jl`, so 0x32 is inside it; written as
              `50 <` the `actionParam == 0x32` test below could never be true
             */
            if (0x32 <= actionParam) {
                MACRO_CALL(
                    OpenSHC::UI::Rendering_Func::RenderCurrentNotActiveButtonWithPossibleAlphaTexOnCurrentSurfaceUnk)();
                if (actionParam == 0x32) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(10,
                        (int)(DAT_ButtonX::instance + 0x12), (int)(DAT_ButtonY::instance + 0x10),
                        OpenSHC::Text::TTA_LEFT, 0xb8eefb, 0, 0x11, FALSE, 0);
                    return;
                }
                if (actionParam == 0x33) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(25,
                        (int)(DAT_ButtonX::instance + 0xf), (int)(DAT_ButtonY::instance + 0x10),
                        OpenSHC::Text::TTA_LEFT, 0xb8eefb, 0, 0x11, FALSE, 0);
                    return;
                }
                if (actionParam == 0x34) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(100,
                        (int)(DAT_ButtonX::instance + 0xc), (int)(DAT_ButtonY::instance + 0x10),
                        OpenSHC::Text::TTA_LEFT, 0xb8eefb, 0, 0x11, FALSE, 0);
                    return;
                }
                if (actionParam == 0x35) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(5,
                        (int)(DAT_ButtonX::instance + 0x15), (int)(DAT_ButtonY::instance + 0x10),
                        OpenSHC::Text::TTA_LEFT, 0xb8eefb, 0, 0x11, FALSE, 0);
                    return;
                }
                if (actionParam == 0x36) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(500,
                        (int)(DAT_ButtonX::instance + 0xb), (int)(DAT_ButtonY::instance + 0x10),
                        OpenSHC::Text::TTA_LEFT, 0xb8eefb, 0, 0x11, FALSE, 0);
                    return;
                }
            }
        }

    }
}
}
