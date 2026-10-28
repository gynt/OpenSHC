#include "../TextEditor.func.hpp"

#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"
#include "OpenSHC/Text/Enums/HelpTextToken.hpp"

#include "OpenSHC/Globals/DAT_TextEditorState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Text::Enums::HelpTextToken;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00461570
        void TextEditor::MenuItemActionHandler_TextEditor_HandleKeyboardInput()
        {
            WCHAR WVar1;
            uint uVar2;
            int iVar3;
            WCHAR* pWVar4;
            int iVar5;
            int iVar6;
            WCHAR* pWVar7;
            if (DAT_TextEditorState::instance.isEditorMode == 0) {
                uVar2 = MACRO_CALL_MEMBER(
                    OpenSHC::Text::UserTextHandler_Func::dequeueInputBufferChar, DAT_UserTextHandlerState::ptr)();
                if ((int)uVar2 < 0xf0) {
                    return; // 0x46158F jl ret
                }
                switch (uVar2) {
                case 0xf4:
                    if ((int)DAT_TextEditorState::instance.helpContentScrollOffsetY < 0x12) {
                        DAT_TextEditorState::instance.helpContentScrollOffsetY = 0;
                        return; // 0x461678 store 0 + ret
                    }
                    DAT_TextEditorState::instance.helpContentScrollOffsetY
                        = DAT_TextEditorState::instance.helpContentScrollOffsetY + -0x12;
                    return;
                case 0xf5:
                    uVar2 = DAT_TextEditorState::instance.totalContentHeight
                        - DAT_TextEditorState::instance.dialogContentHeight;
                    if ((int)((((int)uVar2 < 1) - 1 & uVar2) - 0x12)
                        <= (int)DAT_TextEditorState::instance.helpContentScrollOffsetY)
                        goto LAB_004615e1;
                    DAT_TextEditorState::instance.helpContentScrollOffsetY
                        = DAT_TextEditorState::instance.helpContentScrollOffsetY + 0x12;
                    break;
                case 0xf6:
                    DAT_TextEditorState::instance.helpContentScrollOffsetY = 0;
                    return;
                case 0xf7:
                    DAT_TextEditorState::instance.helpContentScrollOffsetY
                        = DAT_TextEditorState::instance.totalContentHeight
                            - DAT_TextEditorState::instance.dialogContentHeight
                        & (DAT_TextEditorState::instance.totalContentHeight
                                  - DAT_TextEditorState::instance.dialogContentHeight
                              < 1)
                            - 1;
                    return;
                default:
                    return; // 0x46159D ja ret (0xf8/0xf9 table entries -> 0x46197F ret)
                case 0xfa:
                    if ((int)DAT_TextEditorState::instance.helpContentScrollOffsetY
                        < DAT_TextEditorState::instance.dialogContentHeight) {
                        DAT_TextEditorState::instance.helpContentScrollOffsetY = 0;
                        return; // 0x461678 store 0 + ret
                    }
                    DAT_TextEditorState::instance.helpContentScrollOffsetY
                        = DAT_TextEditorState::instance.helpContentScrollOffsetY
                        - DAT_TextEditorState::instance.dialogContentHeight;
                    return;
                case 0xfb:
                    uVar2 = DAT_TextEditorState::instance.totalContentHeight
                        - DAT_TextEditorState::instance.dialogContentHeight;
                    if ((int)((((int)uVar2 < 1) - 1 & uVar2) - DAT_TextEditorState::instance.dialogContentHeight)
                        <= (int)DAT_TextEditorState::instance.helpContentScrollOffsetY)
                        goto LAB_004615e1;
                    DAT_TextEditorState::instance.helpContentScrollOffsetY
                        = DAT_TextEditorState::instance.helpContentScrollOffsetY
                        + DAT_TextEditorState::instance.dialogContentHeight;
                }
                if ((int)DAT_TextEditorState::instance.helpContentScrollOffsetY
                    <= (int)(((int)uVar2 < 1) - 1 & uVar2)) {
                    return; // 0x4615DF jle -> store ecx + ret
                }
            LAB_004615e1:
                DAT_TextEditorState::instance.helpContentScrollOffsetY = ((int)uVar2 < 1) - 1 & uVar2;
                return; // 0x4615F5 ret (non-editor mode never reaches the editor input below)
            }
            uVar2 = MACRO_CALL_MEMBER(
                OpenSHC::Text::UserTextHandler_Func::dequeueInputBufferChar, DAT_UserTextHandlerState::ptr)();
            iVar3 = DAT_TextEditorState::instance.caretTextPos;
            pWVar7 = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory;
            if (uVar2 != 0xffffffff) {
                if ((int)uVar2 < 0xf0) {
                    if (DAT_TextEditorState::instance.pendingTokenTypeToSkip != ((HelpTextToken)0)) {
                        iVar3 = MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                            DAT_TextEditorState::ptr)(
                            (OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance.pendingTokenTypeToSkip);
                        DAT_TextEditorState::instance.caretTextPos
                            = DAT_TextEditorState::instance.caretTextPos + iVar3;
                        DAT_TextEditorState::instance.pendingTokenTypeToSkip = ((HelpTextToken)0);
                    }
                    if ((DAT_TextEditorState::instance.isCustomTextMode != 0)
                        && (-1 < DAT_TextEditorState::instance.customTextMaxLength)) {
                        pWVar4 = pWVar7;
                        do {
                            WVar1 = *pWVar4;
                            pWVar4 = pWVar4 + 1;
                        } while (WVar1 != L'\0');
                        if (DAT_TextEditorState::instance.customTextMaxLength <= (int)pWVar4 - (int)(pWVar7 + 1) >> 1)
                            goto switchD_00461715_caseD_a;
                    }
                LAB_004616f7:
                    iVar3 = DAT_TextEditorState::instance.helpTextLength;
                    if (DAT_TextEditorState::instance.caretTextPos
                        <= DAT_TextEditorState::instance.helpTextLength) {
                        do {
                            pWVar7[iVar3 + 1] = pWVar7[iVar3];
                            iVar3 = iVar3 + -1;
                            pWVar7 = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory;
                        } while (DAT_TextEditorState::instance.caretTextPos <= iVar3);
                    }
                    WVar1 = MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::singleMultiByteToWideChar,
                        DAT_WideCharMultiByteState::ptr)((char)uVar2);
                    /*
                      put character in memory
                     */
                    DAT_TextEditorState::instance
                        .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.caretTextPos] = WVar1;
                    DAT_TextEditorState::instance.helpTextLength
                        = DAT_TextEditorState::instance.helpTextLength + 1;
                    DAT_TextEditorState::instance.caretTextPos
                        = DAT_TextEditorState::instance.caretTextPos + 1;
                } else {
                    switch (uVar2) {
                    case 0xf0:
                        if (DAT_TextEditorState::instance.isCustomTextMode == 0) {
                            uVar2 = 9;
                            goto LAB_004616f7;
                        }
                        break;
                    case 0xf1:
                        if (DAT_TextEditorState::instance.isCustomTextMode == 0) {
                            uVar2 = 6;
                            goto LAB_004616f7;
                        }
                        break;
                    case 0xf2:
                        if (0 < DAT_TextEditorState::instance.caretTextPos) {
                            if ((ushort)DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory
                                    [DAT_TextEditorState::instance.caretTextPos + -1]
                                < ((HelpTextToken)0x20)) {
                                iVar5 = MACRO_CALL_MEMBER(
                                    OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                                    DAT_TextEditorState::ptr)((OpenSHC::Text::Enums::HelpTextToken)
                                        DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory
                                            [DAT_TextEditorState::instance.caretTextPos + -1]);
                                DAT_TextEditorState::instance.caretTextPos = iVar3 - iVar5;
                            } else {
                                DAT_TextEditorState::instance.caretTextPos
                                    = DAT_TextEditorState::instance.caretTextPos + -1;
                            }
                        }
                        break;
                    case 0xf3:
                        if (DAT_TextEditorState::instance.caretTextPos
                            < DAT_TextEditorState::instance.helpTextLength) {
                            if ((ushort)DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory
                                    [DAT_TextEditorState::instance.caretTextPos]
                                < ((HelpTextToken)0x20)) {
                                iVar5 = MACRO_CALL_MEMBER(
                                    OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                                    DAT_TextEditorState::ptr)(
                                    (OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance
                                        .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance
                                                .caretTextPos]);
                                DAT_TextEditorState::instance.caretTextPos = iVar3 + iVar5;
                            } else {
                                DAT_TextEditorState::instance.caretTextPos
                                    = DAT_TextEditorState::instance.caretTextPos + 1;
                            }
                        }
                        break;
                    case 0xf4:
                        DAT_TextEditorState::instance.pendingCaretLineMove = -1;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextEditorState_Func::renderHelpTextContent, DAT_TextEditorState::ptr)();
                        break;
                    case 0xf5:
                        DAT_TextEditorState::instance.pendingCaretLineMove = 1;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextEditorState_Func::renderHelpTextContent, DAT_TextEditorState::ptr)();
                        break;
                    case 0xf6:
                        DAT_TextEditorState::instance.caretTextPos = 0;
                        break;
                    case 0xf7:
                        DAT_TextEditorState::instance.caretTextPos
                            = DAT_TextEditorState::instance.helpTextLength;
                        break;
                    case 0xf8:
                        if (0 < DAT_TextEditorState::instance.caretTextPos) {
                            iVar5 = MACRO_CALL_MEMBER(
                                OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                                DAT_TextEditorState::ptr)((OpenSHC::Text::Enums::HelpTextToken)
                                    DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory
                                        [DAT_TextEditorState::instance.caretTextPos + -1]);
                            if (iVar3 < DAT_TextEditorState::instance.helpTextLength + iVar5) {
                                iVar6 = (iVar3 - iVar5) * 2;
                                do {
                                    /*
                                      delete character in memory
                                     */
                                    *(WCHAR*)(iVar6 + (int)pWVar7) = pWVar7[iVar3];
                                    if (DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory[iVar3] == L'\0')
                                        break;
                                    iVar3 = iVar3 + 1;
                                    iVar6 = iVar6 + 2;
                                    pWVar7 = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory;
                                } while (iVar3 < DAT_TextEditorState::instance.helpTextLength + iVar5);
                            }
                            DAT_TextEditorState::instance.helpTextLength
                                = DAT_TextEditorState::instance.helpTextLength - iVar5;
                            DAT_TextEditorState::instance.caretTextPos
                                = DAT_TextEditorState::instance.caretTextPos - iVar5;
                        }
                        break;
                    case 0xf9:
                        iVar5 = MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                            DAT_TextEditorState::ptr)((OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance
                                .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance
                                        .caretTextPos]);
                        if (iVar3 < DAT_TextEditorState::instance.helpTextLength) {
                            if (iVar3 < DAT_TextEditorState::instance.helpTextLength + iVar5) {
                                iVar6 = (iVar3 + iVar5) * 2;
                                do {
                                    pWVar7[iVar3] = *(WCHAR*)(iVar6 + (int)pWVar7);
                                    if (DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory[iVar3] == L'\0')
                                        break;
                                    iVar3 = iVar3 + 1;
                                    iVar6 = iVar6 + 2;
                                    pWVar7 = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory;
                                } while (iVar3 < DAT_TextEditorState::instance.helpTextLength + iVar5);
                            }
                            DAT_TextEditorState::instance.helpTextLength
                                = DAT_TextEditorState::instance.helpTextLength - iVar5;
                        }
                    }
                }
            switchD_00461715_caseD_a:
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
            }
            if ((ushort)DAT_TextEditorState::instance
                    .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.caretTextPos]
                < 0x20) {
                DAT_TextEditorState::instance.tokenTypeAtCursor
                    = (uint)(ushort)DAT_TextEditorState::instance
                          .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.caretTextPos];
                return; // 0x461978 ret
            }
            DAT_TextEditorState::instance.tokenTypeAtCursor = 0;
        }

    }
}
}
