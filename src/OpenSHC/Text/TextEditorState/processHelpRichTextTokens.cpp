// disable deprecation warnings for wcscpy and wcscat
#pragma warning(disable : 4996)

#include "../TextEditorState.func.hpp"

#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Text/Enums/HelpTextPicturePositionToken.hpp"
#include "OpenSHC/wstring-literals.hpp"

#include "OpenSHC/Globals/COL_DARK_LIME.hpp"
#include "OpenSHC/Globals/DAT_HelpEditorCursorColumn.hpp"
#include "OpenSHC/Globals/DAT_HelpEditorCursorMoved.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UserHelpDefinedData.hpp"

namespace OpenSHC {
namespace Text {

    union TextMemUnion {
        int value;
        wchar_t* text;
        HelpTextToken helpToken;
        Enums::HelpTextPicturePositionToken picturePositionToken;
    };

    // FUNCTION: STRONGHOLDCRUSADER 0x0045FDC0
    int TextEditorState::processHelpRichTextTokens(int param_1)
    {
        int iVar5;
        wchar_t* pwVar6;
        int iVar12;
        int dVar14;
        int iVar17;
        int local_12c;
        int local_118;
        int local_114;
        int local_104;
        int local_f8;
        int local_f4;
        wchar_t wideTextBuffer[100];
        int currentLinkId = -1;
        int textMemIndex = 0;
        FontSizeClass* currentFontClass = DAT_TextManagerObject::instance.fontSizeClassArray + 17;
        int currentFontLineHeight = DAT_TextManagerObject::instance.fontSizeClassArray[17].lineHeight_0x14;
        BOOL local_f0 = FALSE;
        BGR24 color = 0xccfaff;
        BGR24 linkColor = 0x8bcf84;
        int imageCount = -1;
        BOOL centreActive = FALSE;
        BOOL local_120 = FALSE;
        int lineStartY = 0;
        int lineEndY = 0;
        int local_11c = 0;
        int local_100 = 0;
        int local_10c = 0;
        BOOL local_e4 = FALSE;
        int local_134 = -10000;
        if (this->helpDialogVariant == 2 || this->isCustomTextMode) {
            color = 0xc2f0eb;
        }
        if (!this->isTextHelpDialogMode) {
            return 1;
        }
        this->hoveredCharIndex = -1;
        this->hoveredLinkTarget = -1;
        if (this->pendingCaretLineMove) {
            DAT_HelpEditorCursorMoved::instance = 1;
        }
        if (this->caretTextPos < 0) {
            this->caretTextPos = 0;
        }
        if (this->caretTextPos > this->helpTextLength) {
            this->caretTextPos = this->helpTextLength;
        }
        int leftPosition;
        int lineY = -1;
        do {
            leftPosition = this->lineLayoutTable[++lineY].leftBorder;
        } while (leftPosition == -1);
        while (true) {
            iVar5 = textMemIndex;
            BGR24 charColor = color;
            local_12c = 1;
            if (0 <= currentLinkId) {
                charColor = linkColor;
            }
            local_114 = textMemIndex;
            TextMemUnion textMemUnion;
            textMemUnion.value
                = MACRO_CALL_MEMBER(TextEditorState_Func::readNextControlCharOrWord, this)(&textMemIndex);
            if (this->isEditorMode && textMemUnion.value < L' '
                && textMemUnion.helpToken != Enums::HTT_NEWPARAGRAPH && iVar5 == this->caretTextPos) {
                lineEndY = lineY + currentFontLineHeight;
                lineStartY = lineY;
                if (param_1 == 1) {
                    int xModify = 0;
                    if (local_120) {
                        xModify = this->lineLayoutTable[lineY].unknown2 / 2;
                    }
                    local_10c = local_114 - local_11c;
                    if (this->pendingCaretLineMove < 0) {
                        this->caretTextPos = local_100 + DAT_HelpEditorCursorColumn::instance;
                        if (this->caretTextPos >= local_11c) {
                            this->caretTextPos = local_11c - 1;
                        }
                        this->pendingCaretLineMove = 0;
                    }
                    local_134 = 0;
                    MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                        this->dialogContentX + xModify - 1 + leftPosition,
                        this->dialogContentY - this->helpContentScrollOffsetY - 1 + lineY,
                        this->dialogContentX + xModify - 1 + leftPosition,
                        this->dialogContentY - this->helpContentScrollOffsetY + 1 + lineEndY,
                        COL_DARK_LIME::instance.shortValue);
                    MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                        this->dialogContentX + xModify + leftPosition,
                        this->dialogContentY - this->helpContentScrollOffsetY - 1 + lineY,
                        this->dialogContentX + xModify + leftPosition,
                        this->dialogContentY - this->helpContentScrollOffsetY + 1 + lineEndY,
                        COL_DARK_LIME::instance.shortValue);
                    local_e4 = TRUE;
                }
            }

            iVar17 = local_11c;
            switch (textMemUnion.helpToken) {
            case Enums::HTT_PIC:
                if (this->showTagSymbols == 1) {
                    charColor = 0xff;
                    local_12c = 0;
                    MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__PIC__d__S__005a583c,
                        this->DAT_PointerToTemporaryTextMemory[textMemIndex],
                        this->graphicFileNames[this->DAT_PointerToTemporaryTextMemory[textMemIndex]]);
                    ++textMemIndex;
                    switch ((Enums::HelpTextPicturePositionToken)this->DAT_PointerToTemporaryTextMemory[textMemIndex]) {
                    case Enums::HTPPT_LEFT:
                        wcscat(wideTextBuffer, u_LEFT__005a5494);
                        textMemIndex += 2;
                        break;
                    case Enums::HTPPT_RIGHT:
                        wcscat(wideTextBuffer, u_RIGHT__005a5484);
                        textMemIndex += 2;
                        break;
                    case Enums::HTPPT_CENTRE:
                        wcscat(wideTextBuffer, u_CENTRE__005a5474);
                        textMemIndex += 2;
                        break;
                    case Enums::HTPPT_HERE:
                        wcscat(wideTextBuffer, u_HERE__005a5468);
                        textMemIndex += 2;
                        break;
                    default:
                        textMemIndex += 2;
                        break;
                    }
                    break;
                } else {
                    ++imageCount;
                    if (param_1 == 1) {
                        if (this->DAT_PointerToTemporaryTextMemory[textMemIndex + 1] != 3) {
                            textMemIndex += 3;
                            continue;
                        }
                    } else {
                        if (param_1
                            || (imageCount != this->imageHotspotCount
                                && this->DAT_PointerToTemporaryTextMemory[textMemIndex + 1] != 3)) {
                            textMemIndex += 3;
                            continue;
                        }
                        if (imageCount == this->imageHotspotCount) {
                            this->imageHotspotTable[this->imageHotspotCount].yPos = lineY + 25;
                            this->imageHotspotTable[this->imageHotspotCount].graphicId
                                = this->DAT_PointerToTemporaryTextMemory[textMemIndex];
                            this->imageHotspotTable[this->imageHotspotCount].unknown3 = currentLinkId;
                        }
                    }
                    Enums::HelpTextPicturePositionToken positionToken
                        = (Enums::HelpTextPicturePositionToken)this->DAT_PointerToTemporaryTextMemory[textMemIndex + 1];
                    int imageHeight = DAT_TextureRenderCoreObject::instance
                                          .loadedGfxArray[99 - this->DAT_PointerToTemporaryTextMemory[textMemIndex]]
                                          .height;
                    int imageWidth = DAT_TextureRenderCoreObject::instance
                                         .loadedGfxArray[99 - this->DAT_PointerToTemporaryTextMemory[textMemIndex]]
                                         .width;
                    switch (positionToken) {
                    case Enums::HTPPT_LEFT:
                        this->imageHotspotTable[this->imageHotspotCount].xPos = this->lineLayoutTable[lineY].leftBorder;
                        for (int i = 0; i < imageHeight + 50; ++i) {
                            this->lineLayoutTable[lineY + i].rightBorder
                                = this->lineLayoutTable[lineY].leftBorder + 25 + imageWidth;
                        }
                        break;
                    case Enums::HTPPT_RIGHT:
                        this->imageHotspotTable[this->imageHotspotCount].xPos
                            = this->lineLayoutTable[lineY].rightBorder - imageWidth;
                        for (int i = 0; i < imageHeight + 50; ++i) {
                            this->lineLayoutTable[lineY + i].rightBorder
                                = this->lineLayoutTable[lineY].rightBorder - imageWidth - 25;
                            this->lineLayoutTable[lineY + i].leftBorder = -1;
                        }
                        break;
                    case Enums::HTPPT_CENTRE:
                        this->imageHotspotTable[this->imageHotspotCount].xPos
                            = (this->dialogContentWidth - imageWidth) / 2;
                        for (int i = 0; i < imageHeight + 50; ++i) {
                            this->lineLayoutTable[lineY + i].leftBorder = -1;
                        }
                        break;
                    case Enums::HTPPT_HERE:
                        imageWidth += 3;
                        if (this->lineLayoutTable[lineY].rightBorder < imageWidth + leftPosition) {
                            local_f0 = FALSE;
                            if (local_120) {
                                this->lineLayoutTable[lineY].unknown2
                                    = this->lineLayoutTable[lineY].rightBorder - (short)leftPosition;
                                local_120 = centreActive;
                            }
                            do {
                                lineY += currentFontLineHeight + 1;
                                do {
                                    leftPosition = this->lineLayoutTable[lineY++].leftBorder;
                                } while (leftPosition == -1);
                            } while (this->lineLayoutTable[lineY].rightBorder < leftPosition + imageWidth);
                            if (this->isEditorMode && param_1 == 1) {
                                ++local_134;
                                local_100 = local_11c;
                                local_11c = local_114;
                                if (0 < this->pendingCaretLineMove && 1 < local_134) {
                                    this->caretTextPos = iVar17 + local_10c;
                                    local_134 = -10000;
                                    if (local_114 <= this->caretTextPos) {
                                        this->caretTextPos = local_114 + -1;
                                    }
                                    this->pendingCaretLineMove = 0;
                                }
                            }
                            currentFontLineHeight = currentFontClass->lineHeight_0x14;
                        }
                        if (currentFontLineHeight < imageHeight) {
                            currentFontLineHeight = imageHeight;
                        }
                        leftPosition += imageWidth;
                        if (param_1 != 1 && imageCount == this->imageHotspotCount) {
                            this->imageHotspotTable[this->imageHotspotCount].xPos = leftPosition - imageWidth;
                            this->imageHotspotTable[this->imageHotspotCount].yPos = lineY;
                            ++this->imageHotspotCount;
                        }
                        break;
                    }
                    textMemIndex += 3;
                    if (positionToken == Enums::HTPPT_HERE || param_1) {
                        continue;
                    }
                    ++this->imageHotspotCount;
                    DAT_TextManagerObject::instance.field6_0x18 = 0;
                    return FALSE;
                }
            case Enums::HTT_FONT:
                if (this->showTagSymbols == 1) {
                    charColor = 0xff;
                    local_12c = 0;
                    MACRO_CALL(Global_Func::PrintToDestination)(
                        wideTextBuffer, u__FONT__d__005a5454, this->DAT_PointerToTemporaryTextMemory[textMemIndex]);
                    textMemIndex += 2;
                    break;
                } else {
                    int fontSize = this->DAT_PointerToTemporaryTextMemory[textMemIndex];
                    if (fontSize < 15) {
                        fontSize += 5;
                    }
                    textMemIndex = textMemIndex + 2;
                    currentFontClass = DAT_TextManagerObject::instance.fontSizeClassArray + fontSize;
                    dVar14 = DAT_TextManagerObject::instance.fontSizeClassArray[fontSize].lineHeight_0x14;
                    if (currentFontLineHeight < dVar14 || !local_f0) {
                        currentFontLineHeight = dVar14;
                    }
                    continue;
                }
            case Enums::HTT_COLOUR:
                if (this->showTagSymbols == 1) {
                    charColor = 0xff;
                    local_12c = 0;
                    MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__COLOUR__S__005a5824,
                        DAT_UserHelpDefinedData::instance
                            .helpColorTable[this->DAT_PointerToTemporaryTextMemory[textMemIndex]]
                            .name_0x0);
                    textMemIndex += 2;
                    break;
                } else {
                    if (param_1 == 1) {
                        int const colorIndex = this->DAT_PointerToTemporaryTextMemory[textMemIndex];

                        uint colorRed;
                        uint colorGreen;
                        uint colorBlue;
                        if (this->helpDialogVariant == 2 && colorIndex == 1) {
                            colorRed = 0xd7;
                            colorGreen = 0xd2;
                            colorBlue = 0xa4;
                        } else {
                            colorRed = DAT_UserHelpDefinedData::instance.helpColorTable[colorIndex].r_0x4;
                            colorGreen = DAT_UserHelpDefinedData::instance.helpColorTable[colorIndex].g_0x8;
                            colorBlue = DAT_UserHelpDefinedData::instance.helpColorTable[colorIndex].b_0xc;
                        }
                        textMemIndex += 2;
                        color = ((colorBlue << 16) & 0xff0000) | ((colorGreen << 8) & 0x00ff00) | colorRed & 0x0000ff;
                    } else {
                        textMemIndex += 2;
                    }
                    continue;
                }
            case Enums::HTT_LINKCOLOUR:
                if (this->showTagSymbols == 1) {
                    charColor = 0xff;
                    local_12c = 0;
                    MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__LINKCOLOUR__S__005a5804,
                        DAT_UserHelpDefinedData::instance
                            .helpColorTable[this->DAT_PointerToTemporaryTextMemory[textMemIndex]]
                            .name_0x0);
                    textMemIndex += 2;
                    break;
                } else {
                    if (param_1 == 1) {
                        int const colorIndex = this->DAT_PointerToTemporaryTextMemory[textMemIndex];
                        textMemIndex += 2;
                        linkColor
                            = ((DAT_UserHelpDefinedData::instance.helpColorTable[colorIndex].b_0xc << 16) & 0xff0000)
                            | ((DAT_UserHelpDefinedData::instance.helpColorTable[colorIndex].g_0x8 << 8) & 0x00ff00)
                            | DAT_UserHelpDefinedData::instance.helpColorTable[colorIndex].r_0x4 & 0x0000ff;
                    } else {
                        textMemIndex += 2;
                    }
                    continue;
                }
            case Enums::HTT_LINK:
                if (this->showTagSymbols == 1) {
                    charColor = 0xff;
                    local_12c = 0;
                    MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__LINK_S__005a57ec,
                        DAT_UserHelpDefinedData::instance
                            .HelpSections[this->DAT_PointerToTemporaryTextMemory[textMemIndex]]);
                    textMemIndex += 2;
                    break;
                } else {
                    currentLinkId = this->DAT_PointerToTemporaryTextMemory[textMemIndex];
                    if (param_1 == 1) {
                        DAT_TextManagerObject::instance.field6_0x18 = 1;
                    }
                    textMemIndex += 2;
                    continue;
                }
            case Enums::HTT_INCLUDE:
                if (this->showTagSymbols == 1) {
                    charColor = 0xff;
                    local_12c = 0;
                    MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__INCLUDE_S__005a57cc,
                        DAT_UserHelpDefinedData::instance
                            .HelpSections[this->DAT_PointerToTemporaryTextMemory[textMemIndex]]);
                    textMemIndex += 2;
                    break;
                } else {
                    textMemIndex += 2;
                    continue;
                }
            case Enums::HTT_SOUND:
                if (this->showTagSymbols == 1) {
                    charColor = 0xff;
                    local_12c = 0;
                    MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__SOUND_S__005a57b0,
                        this->soundFileNames[this->DAT_PointerToTemporaryTextMemory[textMemIndex]]);
                    textMemIndex += 2;
                    break;
                } else {
                    if (param_1 == 1 && -1 < lineY - this->helpContentScrollOffsetY
                        && lineY - this->helpContentScrollOffsetY < this->dialogContentHeight
                        && !this->soundFilePlayedFlags[this->DAT_PointerToTemporaryTextMemory[textMemIndex]]) {
                        this->soundFilePlayedFlags[this->DAT_PointerToTemporaryTextMemory[textMemIndex]] = 1;
                    }
                    textMemIndex += 2;
                    continue;
                }
            case Enums::HTT_ENDLINK:
                if (this->showTagSymbols == 1) {
                    charColor = 0xff;
                    local_12c = 0;
                    wcscpy(wideTextBuffer, u__LINK__005a53d4);
                    break;
                } else {
                    currentLinkId = -1;
                    if (param_1 == 1) {
                        DAT_TextManagerObject::instance.field6_0x18 = 0;
                    }
                    continue;
                }
            case (wchar_t*)13: // unknown case?
            default:
                pwVar6 = textMemUnion.text;
                goto switchD_00460064_caseD_d;
            case Enums::HTT_STRING:
                if (this->showTagSymbols == 1) {
                    charColor = 0xff;
                    local_12c = 0;
                    MACRO_CALL(Global_Func::PrintToDestination)(
                        wideTextBuffer, u__STRING__d__005a5358, this->DAT_PointerToTemporaryTextMemory[textMemIndex]);
                    textMemIndex += 2;
                    break;
                } else {
                    textMemIndex += 2;
                    continue;
                }
            case Enums::HTT_CENTRE:
                if (this->showTagSymbols == 1) {
                    charColor = 0xff;
                    local_12c = 0;
                    wcscpy(wideTextBuffer, u__CENTRE__005a539c);
                    break;
                } else {
                    centreActive = TRUE;
                    local_120 = TRUE;
                    continue;
                }
            case Enums::HTT_ENDCENTRE:
                if (this->showTagSymbols == 1) {
                    charColor = 0xff;
                    local_12c = 0;
                    wcscpy(wideTextBuffer, u__CENTRE__005a5388);
                    break;
                } else {
                    centreActive = FALSE;
                    continue;
                }
            case Enums::HTT_NEWPARAGRAPH:
                if (local_120) {
                    this->lineLayoutTable[lineY].unknown2
                        = this->lineLayoutTable[lineY].rightBorder - (short)leftPosition;
                    local_120 = centreActive;
                }
                if (this->isEditorMode && iVar5 == this->caretTextPos) {
                    lineEndY = currentFontLineHeight + lineY;
                    iVar12 = 0;
                    lineStartY = lineY;
                    if (param_1 == 1) {
                        if (local_120) {
                            iVar12 = this->lineLayoutTable[lineY].unknown2 / 2;
                        }
                        MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                            this->dialogContentX + iVar12 - 1 + leftPosition,
                            this->dialogContentY - this->helpContentScrollOffsetY - 1 + lineY,
                            this->dialogContentX + iVar12 - 1 + leftPosition,
                            this->dialogContentY - this->helpContentScrollOffsetY + 1 + lineEndY,
                            COL_DARK_LIME::instance.shortValue);
                        MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                            this->dialogContentX + iVar12 + leftPosition,
                            this->dialogContentY - this->helpContentScrollOffsetY - 1 + lineY,
                            this->dialogContentX + iVar12 + leftPosition,
                            this->dialogContentY - this->helpContentScrollOffsetY + 1 + lineEndY,
                            COL_DARK_LIME::instance.shortValue);
                        local_e4 = TRUE;
                    }
                }
                lineY += 3 + currentFontLineHeight;
                local_f0 = FALSE;
                do {
                    leftPosition = this->lineLayoutTable[lineY++].leftBorder;
                } while (leftPosition == -1);
                currentFontLineHeight = currentFontClass->lineHeight_0x14;
                iVar12 = local_11c;
                if (this->isEditorMode != 0) {
                    local_100 = local_11c;
                    if (param_1 == 1) {
                        ++local_134;
                        if (0 < this->pendingCaretLineMove && 1 < local_134) {
                            this->caretTextPos = local_10c + local_11c;
                            local_134 = -10000;
                            if (iVar5 <= this->caretTextPos) {
                                this->caretTextPos = iVar5 + -1;
                            }
                            this->pendingCaretLineMove = 0;
                        }
                    }
                    iVar12 = iVar5;
                    if (iVar5 == this->caretTextPos && param_1 == 1) {
                        local_10c = 0;
                        if (this->pendingCaretLineMove < 0) {
                            this->caretTextPos = DAT_HelpEditorCursorColumn::instance + local_11c;
                            if (iVar5 <= this->caretTextPos) {
                                this->caretTextPos = iVar5 + -1;
                            }
                            this->pendingCaretLineMove = 0;
                        }
                        local_134 = 0;
                    }
                }
                local_11c = iVar12;
                if (this->showTagSymbols == 1) {
                    charColor = 0xff;
                    local_12c = 0;
                    wcscpy(wideTextBuffer, u__NEWPARAGRAPH__005a5790);
                    break;
                }
                continue;
            case Enums::HTT_TAB: // TODO?: unknown token
                if (this->showTagSymbols == 1) {
                    charColor = 0xff;
                    local_12c = 0;
                    wcscpy(wideTextBuffer, u__tab__005a5784);
                    break;
                } else {
                    if (this->lineLayoutTable[lineY].rightBorder < leftPosition + 30) {
                        local_f0 = FALSE;
                        if (local_120) {
                            this->lineLayoutTable[lineY].unknown2
                                = this->lineLayoutTable[lineY].rightBorder - (short)leftPosition;
                            local_120 = centreActive;
                        }
                        do {
                            lineY += currentFontLineHeight + 1;
                            do {
                                leftPosition = this->lineLayoutTable[lineY++].leftBorder;
                            } while (leftPosition == -1);
                        } while (this->lineLayoutTable[lineY].rightBorder < leftPosition + 30);
                        iVar12 = local_11c;
                        if (this->isEditorMode && param_1 == 1) {
                            ++local_134;
                            local_100 = local_11c;
                            iVar12 = iVar5;
                            if (0 < this->pendingCaretLineMove && 1 < local_134) {
                                this->caretTextPos = local_11c + local_10c;
                                local_134 = -10000;
                                if (iVar5 <= this->caretTextPos) {
                                    this->caretTextPos = iVar5 + -1;
                                }
                                this->pendingCaretLineMove = 0;
                            }
                        }
                        local_11c = iVar12;
                        currentFontLineHeight = currentFontClass->lineHeight_0x14;
                    }
                    leftPosition += 30;
                    continue;
                }
            case (wchar_t*)0: // TODO?: unknown token, or just NULL, meaning end?
                if (param_1 == 0) {
                    this->totalContentHeight = lineY + currentFontLineHeight - 1;
                    do {
                        ++this->totalContentHeight;
                        if (this->lineLayoutTable[this->totalContentHeight].leftBorder == 25
                            && this->lineLayoutTable[this->totalContentHeight].rightBorder
                                == this->dialogContentWidth - 25) {
                            break;
                        }
                    } while (this->totalContentHeight < 20000);
                    this->totalContentHeight += 5;
                    if (this->isEditorMode) {
                        if (lineStartY < this->helpContentScrollOffsetY) {
                            this->helpContentScrollOffsetY = lineStartY;
                        }
                        if (lineEndY > this->helpContentScrollOffsetY + this->dialogContentHeight) {
                            this->helpContentScrollOffsetY = (lineEndY - this->dialogContentHeight) + 5;
                            DAT_TextManagerObject::instance.field6_0x18 = 0;
                            return TRUE;
                        }
                    }
                    DAT_TextManagerObject::instance.field6_0x18 = 0;
                    return TRUE;
                }
                if (!this->isEditorMode) {
                    DAT_TextManagerObject::instance.field6_0x18 = 0;
                    return TRUE;
                }
                DAT_HelpEditorCursorColumn::instance = local_10c;
                if (0 < this->pendingCaretLineMove && local_134 == 1) {
                    this->caretTextPos = local_10c + local_11c;
                    if (this->caretTextPos > this->helpTextLength) {
                        this->caretTextPos = this->helpTextLength;
                    }
                    this->pendingCaretLineMove = 0;
                }
                if (!local_e4 && this->caretTextPos && DAT_HelpEditorCursorMoved::instance) {
                    --this->caretTextPos;
                    this->tokenTypeAtCursor = 0;
                    DAT_TextManagerObject::instance.field6_0x18 = 0;
                    return TRUE;
                }
                DAT_HelpEditorCursorMoved::instance = 0;
                DAT_TextManagerObject::instance.field6_0x18 = 0;
                return TRUE;
            }
            // NOTE: This is either the local text buffer, or the text directly from the text memory...
            pwVar6 = wideTextBuffer;
        switchD_00460064_caseD_d:
            if (0x1f < (int)pwVar6) {
                iVar12 = MACRO_CALL_MEMBER(FontSizeClass_Func::getWidthOfWideText, currentFontClass)(
                    pwVar6, wcslen((wchar_t*)pwVar6));
                iVar5 = local_11c;
                local_f4 = leftPosition + iVar12;
                if (this->lineLayoutTable[lineY].rightBorder < local_f4) {
                    local_f0 = FALSE;
                    if (local_120) {
                        this->lineLayoutTable[lineY].unknown2
                            = this->lineLayoutTable[lineY].rightBorder - (short)leftPosition;
                        local_120 = centreActive;
                    }
                    lineY += 1 + currentFontLineHeight;
                    do {
                        leftPosition = this->lineLayoutTable[lineY++].leftBorder;
                    } while (leftPosition == -1);
                    currentFontLineHeight = currentFontClass->lineHeight_0x14;
                    if (this->isEditorMode) {
                        ++local_134;
                        local_100 = local_11c;
                        local_11c = local_114;
                        if (0 < this->pendingCaretLineMove && 1 < local_134) {
                            this->caretTextPos = iVar5 + local_10c;
                            local_134 = -10000;
                            if (local_114 <= this->caretTextPos) {
                                this->caretTextPos = local_114 - 1;
                            }
                            this->pendingCaretLineMove = 0;
                        }
                    }
                    local_f4 = iVar12 + leftPosition;
                    if (this->lineLayoutTable[lineY].rightBorder < (int)local_f4) {
                        local_f8 = 0;
                        if (local_120) {
                            local_f8 = this->lineLayoutTable[lineY].unknown2 / 2;
                        }
                        int const wideStrLength = wcslen((wchar_t*)pwVar6);
                        for (local_118 = 0; local_118 < wideStrLength; ++local_118) {
                            int wideCharWidth = MACRO_CALL_MEMBER(
                                FontSizeClass_Func::getWideCharWidth, currentFontClass)(textMemUnion.text[local_118]);
                            while (this->lineLayoutTable[lineY].rightBorder < leftPosition + wideCharWidth) {
                                iVar5 = local_11c;
                                if (local_120) {
                                    this->lineLayoutTable[lineY].unknown2
                                        = this->lineLayoutTable[lineY].rightBorder - (short)leftPosition;
                                    local_120 = centreActive;
                                }
                                lineY += currentFontLineHeight + 1;
                                if (this->isEditorMode && param_1 == 1) {
                                    ++local_134;
                                    local_100 = local_11c;
                                    local_11c = local_114 + local_118;
                                    if (0 < this->pendingCaretLineMove && 1 < local_134) {
                                        this->caretTextPos = iVar5 + local_10c;
                                        local_134 = -10000;
                                        if (local_114 + local_118 <= this->caretTextPos) {
                                            this->caretTextPos = local_114 + local_118 - 1;
                                        }
                                        this->pendingCaretLineMove = 0;
                                    }
                                }
                                do {
                                    leftPosition = this->lineLayoutTable[lineY++].leftBorder;
                                } while (leftPosition == -1);
                                if (local_120) {
                                    local_f8 = this->lineLayoutTable[lineY].unknown2 / 2;
                                }
                            }
                            if (!this->isEditorMode || local_114 + local_118 != this->caretTextPos) {
                                if (param_1 == 1) {
                                    iVar5 = MACRO_CALL_MEMBER(FontSizeClass_Func::renderWideChar, currentFontClass)(
                                        textMemUnion.text[local_118], this->dialogContentX + local_f8 + leftPosition,
                                        this->dialogContentY - this->helpContentScrollOffsetY + lineY, charColor, 0);
                                    local_f0 = TRUE;
                                    if (MACRO_CALL_MEMBER(
                                            Input::MouseState_Func::isMouseInsideBox, DAT_MouseState::ptr)(
                                            this->dialogContentX + local_f8 + leftPosition - this->helpContentScrollX,
                                            this->dialogContentY - this->helpContentScrollOffsetY + lineY
                                                - this->helpContentScrollY,
                                            iVar5 - this->dialogContentX + local_f8 + leftPosition,
                                            currentFontLineHeight + 2)) {
                                        if (local_12c) {
                                            this->hoveredCharIndex = local_114 + local_118;
                                            this->hoveredLinkTarget = currentLinkId;
                                        } else {
                                            this->hoveredCharIndex = local_114;
                                        }
                                    }
                                }
                            } else {
                                lineEndY = lineY + currentFontLineHeight;
                                lineStartY = lineY;
                                if (param_1 == 1) {
                                    if (local_12c) {
                                        local_10c = (local_118 - local_11c) + local_114;
                                        if (this->pendingCaretLineMove < 0) {
                                            this->caretTextPos = DAT_HelpEditorCursorColumn::instance + local_100;
                                            if (this->caretTextPos >= local_11c) {
                                                this->caretTextPos = local_11c - 1;
                                            }
                                            this->pendingCaretLineMove = 0;
                                        }
                                        local_134 = 0;
                                        MACRO_CALL_MEMBER(
                                            UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                                            this->dialogContentX + local_f8 - 1 + leftPosition,
                                            this->dialogContentY - this->helpContentScrollOffsetY + -1 + lineY,
                                            this->dialogContentX + local_f8 - 1 + leftPosition,
                                            this->dialogContentY - this->helpContentScrollOffsetY + 1 + lineEndY,
                                            COL_DARK_LIME::instance.shortValue);
                                        MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine,
                                            DAT_PencilRenderCore::ptr)(this->dialogContentX + local_f8 + leftPosition,
                                            this->dialogContentY - this->helpContentScrollOffsetY - 1 + lineY,
                                            this->dialogContentX + local_f8 + leftPosition,
                                            this->dialogContentY - this->helpContentScrollOffsetY + 1 + lineEndY,
                                            COL_DARK_LIME::instance.shortValue);
                                        local_e4 = TRUE;
                                    }
                                    iVar5 = MACRO_CALL_MEMBER(FontSizeClass_Func::renderWideChar, currentFontClass)(
                                        textMemUnion.text[local_118], this->dialogContentX + local_f8 + leftPosition,
                                        this->dialogContentY - this->helpContentScrollOffsetY + lineY, charColor, 0);
                                    local_f0 = TRUE;
                                    if (MACRO_CALL_MEMBER(
                                            Input::MouseState_Func::isMouseInsideBox, DAT_MouseState::ptr)(
                                            this->dialogContentX + local_f8 + leftPosition - this->helpContentScrollX,
                                            this->dialogContentY - this->helpContentScrollOffsetY + lineY
                                                - this->helpContentScrollY,
                                            iVar5 - this->dialogContentX + local_f8 + leftPosition,
                                            currentFontLineHeight + 2)) {
                                        if (local_12c) {
                                            this->hoveredCharIndex = local_114 + local_118;
                                            this->hoveredLinkTarget = currentLinkId;
                                        } else {
                                            this->hoveredCharIndex = local_114;
                                        }
                                    }
                                }
                            }
                            leftPosition += wideCharWidth;
                        }
                        continue;
                    }
                }
                iVar5 = this->dialogContentX + leftPosition;
                local_104 = (this->dialogContentY - this->helpContentScrollOffsetY) + lineY;
                if (local_120) {
                    iVar5 += this->lineLayoutTable[lineY].unknown2 / 2;
                }
                int const wideStrLength = wcslen((wchar_t*)pwVar6);
                for (int i = 0; i < wideStrLength; ++i) {
                    local_f8 = local_114 - local_11c;
                    if ((this->isEditorMode == 0) || (i + local_114 != this->caretTextPos)) {
                        if (param_1 == 1) {
                            local_f0 = TRUE;
                            iVar12 = MACRO_CALL_MEMBER(FontSizeClass_Func::renderWideChar, currentFontClass)(
                                textMemUnion.text[i], iVar5, local_104, charColor, 0);
                            if (MACRO_CALL_MEMBER(Input::MouseState_Func::isMouseInsideBox, DAT_MouseState::ptr)(
                                    iVar5 - this->helpContentScrollX, local_104 - this->helpContentScrollY,
                                    iVar12 - iVar5, currentFontLineHeight + 2)) {
                                if (local_12c) {
                                    this->hoveredCharIndex = i + local_114;
                                    this->hoveredLinkTarget = currentLinkId;
                                } else {
                                    this->hoveredCharIndex = local_114;
                                }
                            }
                        } else {
                            dVar14 = MACRO_CALL_MEMBER(FontSizeClass_Func::getWideCharWidth, currentFontClass)(
                                textMemUnion.text[i]);
                            iVar12 = iVar5 + dVar14;
                        }
                    } else {
                        if (param_1 == 1 && local_12c) {
                            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine,
                                DAT_PencilRenderCore::ptr)(iVar5 + -1, local_104 - 1, iVar5 + -1,
                                local_104 + 1 + currentFontLineHeight, COL_DARK_LIME::instance.shortValue);
                            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine,
                                DAT_PencilRenderCore::ptr)(iVar5, local_104 - 1, iVar5,
                                local_104 + 1 + currentFontLineHeight, COL_DARK_LIME::instance.shortValue);
                            local_e4 = TRUE;
                        }
                        lineEndY = lineY + currentFontLineHeight;
                        lineStartY = lineY;
                        if (param_1 == 1) {
                            local_10c = local_f8 + i;
                            local_134 = 0;
                            if (this->pendingCaretLineMove < 0 && local_12c) {
                                this->caretTextPos = local_100 + DAT_HelpEditorCursorColumn::instance;
                                if (this->caretTextPos >= local_11c) {
                                    this->caretTextPos = local_11c + -1;
                                }
                                this->pendingCaretLineMove = 0;
                            }
                            local_f0 = TRUE;
                            iVar12 = MACRO_CALL_MEMBER(FontSizeClass_Func::renderWideChar, currentFontClass)(
                                textMemUnion.text[i], iVar5, local_104, charColor, 0);
                            if (MACRO_CALL_MEMBER(Input::MouseState_Func::isMouseInsideBox, DAT_MouseState::ptr)(
                                    iVar5 - this->helpContentScrollX, local_104 - this->helpContentScrollY,
                                    iVar12 - iVar5, currentFontLineHeight + 2)) {
                                if (local_12c) {
                                    this->hoveredCharIndex = i + local_114;
                                    this->hoveredLinkTarget = currentLinkId;
                                } else {
                                    this->hoveredCharIndex = local_114;
                                }
                            }
                        } else {
                            dVar14 = MACRO_CALL_MEMBER(FontSizeClass_Func::getWideCharWidth, currentFontClass)(
                                textMemUnion.text[i]);
                            iVar12 = iVar5 + dVar14;
                        }
                    }
                    iVar5 = iVar12;
                }
                leftPosition = local_f4;
            }
        }
    }

}
}
