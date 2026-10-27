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

        // FUNCTION: STRONGHOLDCRUSADER 0x00461570
        void TextEditor::MenuItemActionHandler_TextEditor_TextInputRelatedUnk()
        {
            WCHAR WVar1;
            uint uVar2;
            int iVar3;
            WCHAR* pWVar4;
            int iVar5;
            int iVar6;
            WCHAR* pWVar7;
            if (DAT_TextEditorState::instance.useAlternateHelpTab == 0) {
                uVar2 = MACRO_CALL_MEMBER(
                    OpenSHC::Text::UserTextHandler_Func::dequeueInputBufferChar, DAT_UserTextHandlerState::ptr)();
                if ((int)uVar2 < 0xf0) {
                    return;
                }
                switch (uVar2) {
                case 0xf5:
                    iVar5 = DAT_TextEditorState::instance.topVisibleLineIndex
                        - DAT_TextEditorState::instance.dialogContentHeight;
                    iVar3 = DAT_TextEditorState::instance.helpContentScrollOffsetY;
                    if (iVar3 < ((iVar5 <= 0) - 1 & iVar5) - 0x12) {
                        iVar3 = iVar3 + 0x12;
                        if (((iVar5 <= 0) - 1 & iVar5) < iVar3) {
                            iVar3 = (iVar5 <= 0) - 1 & iVar5;
                        }
                    } else {
                        iVar3 = (iVar5 <= 0) - 1 & iVar5;
                    }
                    DAT_TextEditorState::instance.helpContentScrollOffsetY = iVar3;
                    return;
                case 0xf4:
                    iVar3 = DAT_TextEditorState::instance.helpContentScrollOffsetY;
                    if (0x12 <= iVar3) {
                        DAT_TextEditorState::instance.helpContentScrollOffsetY = iVar3 - 0x12;
                        return;
                    }
                    DAT_TextEditorState::instance.helpContentScrollOffsetY = 0;
                    return;
                case 0xf6:
                    DAT_TextEditorState::instance.helpContentScrollOffsetY = 0;
                    return;
                case 0xf7:
                    iVar5 = DAT_TextEditorState::instance.topVisibleLineIndex
                        - DAT_TextEditorState::instance.dialogContentHeight;
                    DAT_TextEditorState::instance.helpContentScrollOffsetY = (iVar5 <= 0) - 1 & iVar5;
                    return;
                case 0xfb:
                    iVar5 = DAT_TextEditorState::instance.topVisibleLineIndex
                        - DAT_TextEditorState::instance.dialogContentHeight;
                    iVar3 = DAT_TextEditorState::instance.helpContentScrollOffsetY;
                    if (iVar3 < ((iVar5 <= 0) - 1 & iVar5) - DAT_TextEditorState::instance.dialogContentHeight) {
                        iVar3 = iVar3 + DAT_TextEditorState::instance.dialogContentHeight;
                        if (((iVar5 <= 0) - 1 & iVar5) < iVar3) {
                            iVar3 = (iVar5 <= 0) - 1 & iVar5;
                        }
                    } else {
                        iVar3 = (iVar5 <= 0) - 1 & iVar5;
                    }
                    DAT_TextEditorState::instance.helpContentScrollOffsetY = iVar3;
                    return;
                case 0xfa:
                    iVar3 = DAT_TextEditorState::instance.helpContentScrollOffsetY;
                    iVar6 = DAT_TextEditorState::instance.dialogContentHeight;
                    if (iVar3 >= iVar6) {
                        DAT_TextEditorState::instance.helpContentScrollOffsetY = iVar3 - iVar6;
                        return;
                    }
                    DAT_TextEditorState::instance.helpContentScrollOffsetY = 0;
                    return;
                default:
                    return;
                }
            }
            uVar2 = MACRO_CALL_MEMBER(
                OpenSHC::Text::UserTextHandler_Func::dequeueInputBufferChar, DAT_UserTextHandlerState::ptr)();
            iVar3 = DAT_TextEditorState::instance.activeHelpHotspotIndex;
            pWVar7 = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory;
            if (uVar2 != 0xffffffff) {
                if ((int)uVar2 < 0xf0) {
                    if (DAT_TextEditorState::instance.pendingTokenTypeToSkip != (HelpTextToken)0) {
                        iVar3 = MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                            DAT_TextEditorState::ptr)(
                            (OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance.pendingTokenTypeToSkip);
                        DAT_TextEditorState::instance.activeHelpHotspotIndex
                            = DAT_TextEditorState::instance.activeHelpHotspotIndex + iVar3;
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
                    iVar3 = DAT_TextEditorState::instance.customHelpTextLength;
                    if (DAT_TextEditorState::instance.activeHelpHotspotIndex
                        <= DAT_TextEditorState::instance.customHelpTextLength) {
                        do {
                            pWVar7[iVar3 + 1] = pWVar7[iVar3];
                            iVar3 = iVar3 + -1;
                            pWVar7 = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory;
                        } while (iVar3 >= DAT_TextEditorState::instance.activeHelpHotspotIndex);
                    }
                    WVar1 = MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::singleMultiByteToWideChar,
                        DAT_WideCharMultiByteState::ptr)((char)uVar2);
                    /*
                      put character in memory
                     */
                    DAT_TextEditorState::instance
                        .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex] = WVar1;
                    DAT_TextEditorState::instance.customHelpTextLength
                        = DAT_TextEditorState::instance.customHelpTextLength + 1;
                    DAT_TextEditorState::instance.activeHelpHotspotIndex
                        = DAT_TextEditorState::instance.activeHelpHotspotIndex + 1;
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
                        iVar3 = DAT_TextEditorState::instance.activeHelpHotspotIndex;
                        if (iVar3 <= 0)
                            break;
                        iVar6 = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory[iVar3 + -1];
                        if ((HelpTextToken)0x20 <= iVar6) {
                            DAT_TextEditorState::instance.activeHelpHotspotIndex = iVar3 + -1;
                            break;
                        }
                        iVar5 = MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                            DAT_TextEditorState::ptr)((OpenSHC::Text::Enums::HelpTextToken)iVar6);
                        DAT_TextEditorState::instance.activeHelpHotspotIndex = iVar3 - iVar5;
                        break;
                    case 0xf3:
                        iVar3 = DAT_TextEditorState::instance.activeHelpHotspotIndex;
                        if (iVar3 >= DAT_TextEditorState::instance.customHelpTextLength)
                            break;
                        iVar6 = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory[iVar3];
                        if ((HelpTextToken)0x20 <= iVar6) {
                            DAT_TextEditorState::instance.activeHelpHotspotIndex = iVar3 + 1;
                            break;
                        }
                        iVar5 = MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                            DAT_TextEditorState::ptr)((OpenSHC::Text::Enums::HelpTextToken)iVar6);
                        DAT_TextEditorState::instance.activeHelpHotspotIndex = iVar3 + iVar5;
                        break;
                    case 0xf4:
                        DAT_TextEditorState::instance.field51_0x2396c = -1;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextEditorState_Func::setTextRenderingLogic, DAT_TextEditorState::ptr)();
                        break;
                    case 0xf5:
                        DAT_TextEditorState::instance.field51_0x2396c = 1;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextEditorState_Func::setTextRenderingLogic, DAT_TextEditorState::ptr)();
                        break;
                    case 0xf6:
                        DAT_TextEditorState::instance.activeHelpHotspotIndex = 0;
                        break;
                    case 0xf7:
                        DAT_TextEditorState::instance.activeHelpHotspotIndex
                            = DAT_TextEditorState::instance.customHelpTextLength;
                        break;
                    case 0xf8:
                        iVar3 = DAT_TextEditorState::instance.activeHelpHotspotIndex;
                        if (iVar3 <= 0)
                            break;
                        pWVar7 = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory;
                        iVar6 = pWVar7[iVar3 + -1];
                        iVar5 = MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                            DAT_TextEditorState::ptr)((OpenSHC::Text::Enums::HelpTextToken)iVar6);
                        if (DAT_TextEditorState::instance.customHelpTextLength > iVar3 + iVar5) {
                            iVar6 = (iVar3 - iVar5) * 2;
                            do {
                                /*
                                  delete character in memory
                                 */
                                *(WCHAR*)(iVar6 + (int)pWVar7) = pWVar7[iVar3];
                                pWVar7 = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory;
                                if (pWVar7[iVar3] == L' ')
                                    break;
                                iVar3 = iVar3 + 1;
                                iVar6 = iVar6 + 2;
                            } while (iVar3 < DAT_TextEditorState::instance.customHelpTextLength + iVar5);
                        }
                        DAT_TextEditorState::instance.customHelpTextLength
                            = DAT_TextEditorState::instance.customHelpTextLength - iVar5;
                        DAT_TextEditorState::instance.activeHelpHotspotIndex
                            = DAT_TextEditorState::instance.activeHelpHotspotIndex - iVar5;
                        break;
                    case 0xf9:
                        iVar5 = MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                            DAT_TextEditorState::ptr)((OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance
                                .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance
                                        .activeHelpHotspotIndex]);
                        if (iVar3 < DAT_TextEditorState::instance.customHelpTextLength) {
                            if (DAT_TextEditorState::instance.customHelpTextLength > iVar3 + iVar5) {
                                iVar6 = (iVar3 + iVar5) * 2;
                                do {
                                    pWVar7[iVar3] = *(WCHAR*)(iVar6 + (int)pWVar7);
                                    if (DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory[iVar3] == L'\0')
                                        break;
                                    iVar3 = iVar3 + 1;
                                    iVar6 = iVar6 + 2;
                                    pWVar7 = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory;
                                } while (iVar3 < DAT_TextEditorState::instance.customHelpTextLength + iVar5);
                            }
                            DAT_TextEditorState::instance.customHelpTextLength
                                = DAT_TextEditorState::instance.customHelpTextLength - iVar5;
                        }
                    }
                }
            switchD_00461715_caseD_a:
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
            }
            if ((ushort)DAT_TextEditorState::instance
                    .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex]
                < 0x20) {
                DAT_TextEditorState::instance.field52_0x23970
                    = (uint)(ushort)DAT_TextEditorState::instance
                          .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex];
                return;
            }
            DAT_TextEditorState::instance.field52_0x23970 = 0;
        }

    }
}
}
