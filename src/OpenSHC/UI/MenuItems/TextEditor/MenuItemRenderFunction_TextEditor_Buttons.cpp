#include "../TextEditor.func.hpp"

#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextEditorState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_UserHelpDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0045DE40
        void TextEditor::MenuItemRenderFunction_TextEditor_Buttons(int param_1, ...)
        {
            char* textAddress;
            int xParam;
            uint color;
            int iVar1;
            switch (param_1) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 0xb:
            case 0xc:
            case 0xd:
            case 0xe:
            case 0xf:
            case 0x14:
                if ((param_1 != -4) || (DAT_TextEditorState::instance.helpSectionHistoryStack[0] != -1)) {
                    if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                        DAT_TextManagerObject::instance.textColor = 0;
                        DAT_PencilRenderCore::instance.otherColorUnk_0x0 = COL_WHITE::instance.shortValue;
                    } else {
                        DAT_TextManagerObject::instance.textColor = 0xff;
                        DAT_PencilRenderCore::instance.otherColorUnk_0x0 = COL_BLACK::instance.shortValue;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                        (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                        (int)(DAT_ButtonH::instance + DAT_ButtonY::instance),
                        DAT_PencilRenderCore::instance.otherColorUnk_0x0);
                    switch (param_1 + 5) {
                    case 0:
                        /*
                          added by script: "Exit"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_HELP, 2, (int)(DAT_ButtonX::instance),
                            (int)(DAT_ButtonY::instance + 3), (TextAlignment)((int)(DAT_ButtonW::instance)),
                            (uint)(DAT_TextManagerObject::instance.textColor), 0x12, FALSE);
                        return;
                    case 1:
                        /*
                          added by script: "Back"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_HELP, 1, (int)(DAT_ButtonX::instance),
                            (int)(DAT_ButtonY::instance + 3), (TextAlignment)((int)(DAT_ButtonW::instance)),
                            (uint)(DAT_TextManagerObject::instance.textColor), 0x12, FALSE);
                        return;
                    case 6:
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2,
                            DAT_TextManagerObject::ptr)("Symbols", (int)(DAT_ButtonX::instance),
                            (int)(DAT_ButtonY::instance + 3), (TextAlignment)((int)(DAT_ButtonW::instance)),
                            (BGR24)((int)(DAT_TextManagerObject::instance.textColor)), 0x13, FALSE);
                        return;
                    case 7:
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2,
                            DAT_TextManagerObject::ptr)("New Page", (int)(DAT_ButtonX::instance),
                            (int)(DAT_ButtonY::instance + 3), (TextAlignment)((int)(DAT_ButtonW::instance)),
                            (BGR24)((int)(DAT_TextManagerObject::instance.textColor)), 0x13, FALSE);
                        return;
                    case 8:
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2,
                            DAT_TextManagerObject::ptr)("Load", (int)(DAT_ButtonX::instance),
                            (int)(DAT_ButtonY::instance + 3), (TextAlignment)((int)(DAT_ButtonW::instance)),
                            (BGR24)((int)(DAT_TextManagerObject::instance.textColor)), 0x13, FALSE);
                        return;
                    case 9:
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2,
                            DAT_TextManagerObject::ptr)("Save", (int)(DAT_ButtonX::instance),
                            (int)(DAT_ButtonY::instance + 3), (TextAlignment)((int)(DAT_ButtonW::instance)),
                            (BGR24)((int)(DAT_TextManagerObject::instance.textColor)), 0x13, FALSE);
                        return;
                    case 10:
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2,
                            DAT_TextManagerObject::ptr)("Pic", (int)(DAT_ButtonX::instance),
                            (int)(DAT_ButtonY::instance + 3), (TextAlignment)((int)(DAT_ButtonW::instance)),
                            (BGR24)((int)(DAT_TextManagerObject::instance.textColor)), 0x13, FALSE);
                        return;
                    case 0xb:
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2,
                            DAT_TextManagerObject::ptr)("Link", (int)(DAT_ButtonX::instance),
                            (int)(DAT_ButtonY::instance + 3), (TextAlignment)((int)(DAT_ButtonW::instance)),
                            (BGR24)((int)(DAT_TextManagerObject::instance.textColor)), 0x13, FALSE);
                        return;
                    case 0xc:
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2,
                            DAT_TextManagerObject::ptr)("\\Link", (int)(DAT_ButtonX::instance),
                            (int)(DAT_ButtonY::instance + 3), (TextAlignment)((int)(DAT_ButtonW::instance)),
                            (BGR24)((int)(DAT_TextManagerObject::instance.textColor)), 0x13, FALSE);
                        return;
                    case 0xd:
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2,
                            DAT_TextManagerObject::ptr)("Font", (int)(DAT_ButtonX::instance),
                            (int)(DAT_ButtonY::instance + 3), (TextAlignment)((int)(DAT_ButtonW::instance)),
                            (BGR24)((int)(DAT_TextManagerObject::instance.textColor)), 0x13, FALSE);
                        return;
                    case 0xe:
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2,
                            DAT_TextManagerObject::ptr)("Centre", (int)(DAT_ButtonX::instance),
                            (int)(DAT_ButtonY::instance + 3), (TextAlignment)((int)(DAT_ButtonW::instance)),
                            (BGR24)((int)(DAT_TextManagerObject::instance.textColor)), 0x13, FALSE);
                        return;
                    case 0xf:
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2,
                            DAT_TextManagerObject::ptr)("\\Centre", (int)(DAT_ButtonX::instance),
                            (int)(DAT_ButtonY::instance + 3), (TextAlignment)((int)(DAT_ButtonW::instance)),
                            (BGR24)((int)(DAT_TextManagerObject::instance.textColor)), 0x13, FALSE);
                        return;
                    case 0x10:
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2,
                            DAT_TextManagerObject::ptr)("Colour", (int)(DAT_ButtonX::instance),
                            (int)(DAT_ButtonY::instance + 3), (TextAlignment)((int)(DAT_ButtonW::instance)),
                            (BGR24)((int)(DAT_TextManagerObject::instance.textColor)), 0x13, FALSE);
                        return;
                    case 0x11:
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2,
                            DAT_TextManagerObject::ptr)("LinkClr", (int)(DAT_ButtonX::instance),
                            (int)(DAT_ButtonY::instance + 3), (TextAlignment)((int)(DAT_ButtonW::instance)),
                            (BGR24)((int)(DAT_TextManagerObject::instance.textColor)), 0x13, FALSE);
                        return;
                    case 0x12:
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2,
                            DAT_TextManagerObject::ptr)("Sound", (int)(DAT_ButtonX::instance),
                            (int)(DAT_ButtonY::instance + 3), (TextAlignment)((int)(DAT_ButtonW::instance)),
                            (BGR24)((int)(DAT_TextManagerObject::instance.textColor)), 0x13, FALSE);
                        return;
                    case 0x13:
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2,
                            DAT_TextManagerObject::ptr)("String", (int)(DAT_ButtonX::instance),
                            (int)(DAT_ButtonY::instance + 3), (TextAlignment)((int)(DAT_ButtonW::instance)),
                            (BGR24)((int)(DAT_TextManagerObject::instance.textColor)), 0x13, FALSE);
                        return;
                    case 0x14:
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2,
                            DAT_TextManagerObject::ptr)("Include", (int)(DAT_ButtonX::instance),
                            (int)(DAT_ButtonY::instance + 3), (TextAlignment)((int)(DAT_ButtonW::instance)),
                            (BGR24)((int)(DAT_TextManagerObject::instance.textColor)), 0x13, FALSE);
                        return;
                    case 0x19:
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2,
                            DAT_TextManagerObject::ptr)("ScrSize", (int)(DAT_ButtonX::instance),
                            (int)(DAT_ButtonY::instance + 3), (TextAlignment)((int)(DAT_ButtonW::instance)),
                            (BGR24)((int)(DAT_TextManagerObject::instance.textColor)), 0x13, FALSE);
                    }
                }
                break;
            case 0x1f:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                    (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                    (int)(DAT_ButtonH::instance + DAT_ButtonY::instance), (ushort)(COL_BLACK::instance.shortValue));
                switch (DAT_TextEditorState::instance.field52_0x23970) {
                case 1:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        "PIC", (int)(DAT_ButtonX::instance + 3), (int)(DAT_ButtonY::instance + 3),
                        OpenSHC::Text::TTA_LEFT, 0xffffff, 0x13, FALSE, 0);
                    return;
                case 2:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        "FONT", (int)(DAT_ButtonX::instance + 3), (int)(DAT_ButtonY::instance + 3),
                        OpenSHC::Text::TTA_LEFT, 0xffffff, 0x13, FALSE, 0);
                    return;
                case 3:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        "COLOUR", (int)(DAT_ButtonX::instance + 3), (int)(DAT_ButtonY::instance + 3),
                        OpenSHC::Text::TTA_LEFT, 0xffffff, 0x13, FALSE, 0);
                    return;
                case 4:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        "LINK", (int)(DAT_ButtonX::instance + 3), (int)(DAT_ButtonY::instance + 3),
                        OpenSHC::Text::TTA_LEFT, 0xffffff, 0x13, FALSE, 0);
                    return;
                case 5:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        "\\LINK", (int)(DAT_ButtonX::instance + 3), (int)(DAT_ButtonY::instance + 3),
                        OpenSHC::Text::TTA_LEFT, 0xffffff, 0x13, FALSE, 0);
                    return;
                case 7:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        "CENTRE", (int)(DAT_ButtonX::instance + 3), (int)(DAT_ButtonY::instance + 3),
                        OpenSHC::Text::TTA_LEFT, 0xffffff, 0x13, FALSE, 0);
                    return;
                case 8:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        "\\CENTRE", (int)(DAT_ButtonX::instance + 3), (int)(DAT_ButtonY::instance + 3),
                        OpenSHC::Text::TTA_LEFT, 0xffffff, 0x13, FALSE, 0);
                    return;
                case 10:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        "LINKCLR", (int)(DAT_ButtonX::instance + 3), (int)(DAT_ButtonY::instance + 3),
                        OpenSHC::Text::TTA_LEFT, 0xffffff, 0x13, FALSE, 0);
                    return;
                case 0xb:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        "SOUND", (int)(DAT_ButtonX::instance + 3), (int)(DAT_ButtonY::instance + 3),
                        OpenSHC::Text::TTA_LEFT, 0xffffff, 0x13, FALSE, 0);
                    return;
                case 0xc:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        "STRING", (int)(DAT_ButtonX::instance + 3), (int)(DAT_ButtonY::instance + 3),
                        OpenSHC::Text::TTA_LEFT, 0xffffff, 0x13, FALSE, 0);
                    return;
                case 0xe:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        "INCLUDE", (int)(DAT_ButtonX::instance + 3), (int)(DAT_ButtonY::instance + 3),
                        OpenSHC::Text::TTA_LEFT, 0xffffff, 0x13, FALSE, 0);
                }
                break;
            case 0x20:
                if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                    DAT_TextManagerObject::instance.textColor = 0xffffff;
                    DAT_PencilRenderCore::instance.otherColorUnk_0x0 = COL_BLACK::instance.shortValue;
                } else {
                    DAT_TextManagerObject::instance.textColor = 0xff;
                    DAT_PencilRenderCore::instance.otherColorUnk_0x0 = COL_WHITE::instance.shortValue;
                    return;
                }
                switch (DAT_TextEditorState::instance.field52_0x23970) {
                case 1:
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                        (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                        (int)(DAT_ButtonH::instance + DAT_ButtonY::instance),
                        DAT_PencilRenderCore::instance.otherColorUnk_0x0);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2, DAT_TextManagerObject::ptr)(
                        DAT_TextEditorState::instance.graphicFileNames[(ushort)DAT_TextEditorState::instance
                                .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex
                                    + 1]],
                        (int)(DAT_ButtonX::instance + 3), (int)(DAT_ButtonY::instance + 3), OpenSHC::Text::TTA_LEFT,
                        (BGR24)((int)(DAT_TextManagerObject::instance.textColor)), 0x13, FALSE);
                    return;
                case 2:
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                        (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                        (int)(DAT_ButtonH::instance + DAT_ButtonY::instance), (ushort)(COL_BLACK::instance.shortValue));
                    iVar1 = DAT_ButtonY::instance + 3;
                    xParam = DAT_ButtonX::instance + 3;
                    textAddress = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::getHelpSectionText,
                        DAT_TextEditorState::ptr)((uint)(ushort)DAT_TextEditorState::instance
                            .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex
                                + 1]);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        textAddress, xParam, iVar1, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x13, FALSE, 0);
                    return;
                case 3:
                case 10:
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                        (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                        (int)(DAT_ButtonH::instance + DAT_ButtonY::instance), (ushort)(COL_BLACK::instance.shortValue));
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        DAT_UserHelpDefinedData::instance
                            .field6_0x7a16c[(ushort)DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory
                                    [DAT_TextEditorState::instance.activeHelpHotspotIndex + 1]]
                            .name_0x0,
                        (int)(DAT_ButtonX::instance + 3), (int)(DAT_ButtonY::instance + 3), OpenSHC::Text::TTA_LEFT,
                        0xffffff, 0x13, FALSE, 0);
                    return;
                case 4:
                case 0xe:
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                        (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                        (int)(DAT_ButtonH::instance + DAT_ButtonY::instance),
                        DAT_PencilRenderCore::instance.otherColorUnk_0x0);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2, DAT_TextManagerObject::ptr)(
                        DAT_UserHelpDefinedData::instance.HelpSections[(ushort)DAT_TextEditorState::instance
                                .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex
                                    + 1]],
                        (int)(DAT_ButtonX::instance + 3), (int)(DAT_ButtonY::instance + 3), OpenSHC::Text::TTA_LEFT,
                        (BGR24)((int)(DAT_TextManagerObject::instance.textColor)), 0x13, FALSE);
                    return;
                default:
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                        (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                        (int)(DAT_ButtonH::instance + DAT_ButtonY::instance), (ushort)(COL_BLACK::instance.shortValue));
                    return;
                case 0xb:
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                        (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                        (int)(DAT_ButtonH::instance + DAT_ButtonY::instance),
                        DAT_PencilRenderCore::instance.otherColorUnk_0x0);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2, DAT_TextManagerObject::ptr)(
                        DAT_TextEditorState::instance.soundFileNames[(ushort)DAT_TextEditorState::instance
                                .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex
                                    + 1]],
                        (int)(DAT_ButtonX::instance + 3), (int)(DAT_ButtonY::instance + 3), OpenSHC::Text::TTA_LEFT,
                        (BGR24)((int)(DAT_TextManagerObject::instance.textColor)), 0x13, FALSE);
                    return;
                case 0xc:
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                        (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                        (int)(DAT_ButtonH::instance + DAT_ButtonY::instance),
                        DAT_PencilRenderCore::instance.otherColorUnk_0x0);
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen, DAT_TextManagerObject::ptr)(
                        (uint)(ushort)DAT_TextEditorState::instance
                            .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 1],
                        (int)(DAT_ButtonX::instance + 3), (int)(DAT_ButtonY::instance + 3), OpenSHC::Text::TTA_LEFT,
                        (uint)(DAT_TextManagerObject::instance.textColor), 0x13, FALSE);
                }
            case 0x21:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                    (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                    (int)(DAT_ButtonH::instance + DAT_ButtonY::instance), (ushort)(COL_BLACK::instance.shortValue));
                switch (DAT_TextEditorState::instance.field52_0x23970) {
                case 1:
                    DAT_TextManagerObject::instance.textColor
                        = (DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory
                                        [DAT_TextEditorState::instance.activeHelpHotspotIndex + 2]
                                    == L'\0'
                                ? 0xff
                                : 0xffffff);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        "Left", (int)(DAT_ButtonX::instance + 3), (int)(DAT_ButtonY::instance + 3),
                        OpenSHC::Text::TTA_LEFT, (BGR24)((int)(DAT_TextManagerObject::instance.textColor)), 0x13, FALSE,
                        0);
                    return;
                case 2:
                case 3:
                case 10:
                case 0xc:
                    if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                        DAT_TextManagerObject::instance.textColor = 0xffffff;
                        DAT_PencilRenderCore::instance.otherColorUnk_0x0 = COL_BLACK::instance.shortValue;
                    } else {
                        DAT_TextManagerObject::instance.textColor = 0xff;
                        DAT_PencilRenderCore::instance.otherColorUnk_0x0 = COL_WHITE::instance.shortValue;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                        (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                        (int)(DAT_ButtonH::instance + DAT_ButtonY::instance),
                        DAT_PencilRenderCore::instance.otherColorUnk_0x0);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2, DAT_TextManagerObject::ptr)(
                        "PREV", (int)(DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 3),
                        (TextAlignment)((int)(DAT_ButtonW::instance)),
                        (BGR24)((int)(DAT_TextManagerObject::instance.textColor)), 0x13, FALSE);
                }
                break;
            case 0x22:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                    (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                    (int)(DAT_ButtonH::instance + DAT_ButtonY::instance), (ushort)(COL_BLACK::instance.shortValue));
                switch (DAT_TextEditorState::instance.field52_0x23970) {
                case 1:
                    DAT_TextManagerObject::instance.textColor
                        = (DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory
                                        [DAT_TextEditorState::instance.activeHelpHotspotIndex + 2]
                                    == L'\x01'
                                ? 0xff
                                : 0xffffff);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        "Centre", (int)(DAT_ButtonX::instance + 3), (int)(DAT_ButtonY::instance + 3),
                        OpenSHC::Text::TTA_LEFT, (BGR24)((int)(DAT_TextManagerObject::instance.textColor)), 0x13, FALSE,
                        0);
                    return;
                case 2:
                case 3:
                case 10:
                case 0xc:
                    if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                        DAT_TextManagerObject::instance.textColor = 0xffffff;
                        DAT_PencilRenderCore::instance.otherColorUnk_0x0 = COL_BLACK::instance.shortValue;
                    } else {
                        DAT_TextManagerObject::instance.textColor = 0xff;
                        DAT_PencilRenderCore::instance.otherColorUnk_0x0 = COL_WHITE::instance.shortValue;
                        return;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                        (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                        (int)(DAT_ButtonH::instance + DAT_ButtonY::instance),
                        DAT_PencilRenderCore::instance.otherColorUnk_0x0);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2, DAT_TextManagerObject::ptr)(
                        "NEXT", (int)(DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 3),
                        (TextAlignment)((int)(DAT_ButtonW::instance)),
                        (BGR24)((int)(DAT_TextManagerObject::instance.textColor)), 0x13, FALSE);
                }
                break;
            case 0x23:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                    (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                    (int)(DAT_ButtonH::instance + DAT_ButtonY::instance), (ushort)(COL_BLACK::instance.shortValue));
                if (DAT_TextEditorState::instance.field52_0x23970 == 1) {
                    DAT_TextManagerObject::instance.textColor
                        = (DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory
                                        [DAT_TextEditorState::instance.activeHelpHotspotIndex + 2]
                                    == L'\x02'
                                ? 0xff
                                : 0xffffff);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        "Right", (int)(DAT_ButtonX::instance + 3), (int)(DAT_ButtonY::instance + 3),
                        OpenSHC::Text::TTA_LEFT, (BGR24)((int)(DAT_TextManagerObject::instance.textColor)), 0x13, FALSE,
                        0);
                }
                break;
            case 0x24:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                    (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                    (int)(DAT_ButtonH::instance + DAT_ButtonY::instance), (ushort)(COL_BLACK::instance.shortValue));
                if (DAT_TextEditorState::instance.field52_0x23970 == 1) {
                    DAT_TextManagerObject::instance.textColor
                        = (DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory
                                        [DAT_TextEditorState::instance.activeHelpHotspotIndex + 2]
                                    == L'\x03'
                                ? 0xff
                                : 0xffffff);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        "Here", (int)(DAT_ButtonX::instance + 3), (int)(DAT_ButtonY::instance + 3),
                        OpenSHC::Text::TTA_LEFT, (BGR24)((int)(DAT_TextManagerObject::instance.textColor)), 0x13, FALSE,
                        0);
                }
                break;
            case -5:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_HELP, 2,
                        (int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 7),
                        OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x12, FALSE, 4);
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_HELP, 2, (int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance),
                    (int)(DAT_ButtonY::instance + 7), OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x12, FALSE, 2);
                return;
            case -4:
                if (DAT_TextEditorState::instance.helpSectionHistoryStack[0] != -1) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                        iVar1 = 4;
                        color = 0xc2f0eb;
                    } else {
                        iVar1 = 2;
                        color = 0xccfaff;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_HELP, 1,
                        (int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 7),
                        OpenSHC::Text::TTA_CENTER, color, 0x12, FALSE, iVar1);
                }
                break;
            case -2:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                    DAT_PencilRenderCore::ptr)(1, 0);
                return;
            case -1:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                    DAT_PencilRenderCore::ptr)(0, 0);
            }
        }

    }
}
}
