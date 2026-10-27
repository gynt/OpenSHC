#include "../TextEditorState.func.hpp"

#include "OpenSHC/UI/MenuModalComposition.func.hpp"

#include "OpenSHC/Globals/g_textDialogPaddingX.hpp"
#include "OpenSHC/Globals/g_textDialogPaddingY.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/g_textDialogMarginWidth.hpp"
#include "OpenSHC/Globals/g_textDialogMarginHeight.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00461F90
    void TextEditorState::openMapDescriptionEditorDialog(int sectionId)
    {
        if (!this->isDialogStateInitialized) {
            this->isDialogStateInitialized = TRUE;
            this->helpDialogVariant = 0;
            this->useInGameHelpHandler = FALSE;
            this->showTagSymbols = 0;
            this->isEditorMode = TRUE;
            this->isCustomTextMode = TRUE;
            DAT_UserTextHandlerState::instance.inputBufferIndex = 0;
            this->helpContentScrollX = 0;
            this->helpContentScrollY = 0;
        }
        this->caretTextPos = 0;
        this->customHelpTextPointer = NULL;
        if (sectionId == -1) {
            MACRO_CALL_MEMBER(TextEditorState_Func::closeHelpDialogAndReturnToMenu, this)();
            return;
        }
        this->isTextHelpDialogMode = 0;
        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
            UI::Enums::MMT_MAP_DESCRIPTION_EDITOR, FALSE);

        int modalX;
        int modalY;
        int modalWidth;
        int modalHeight;
        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::fillWithMenuModalDimensions, DAT_MenuModalComposition1::ptr)(
            &modalX, &modalY, &modalWidth, &modalHeight);

        g_textDialogPaddingX::instance = 10;
        g_textDialogPaddingY::instance = 10;
        g_textDialogMarginWidth::instance = 45;
        g_textDialogMarginHeight::instance = 53;
        this->dialogX = modalX;
        this->dialogY = modalY;
        this->dialogWidth = modalWidth;
        this->dialogHeight = modalHeight;

        int const dialogContentX = this->dialogX + g_textDialogPaddingX::instance;
        int const dialogContentY = this->dialogY + g_textDialogPaddingY::instance;
        int const dialogContentHeight = this->dialogHeight - g_textDialogMarginHeight::instance;
        int const dialogContentWidth = this->dialogWidth - g_textDialogMarginWidth::instance;
        this->dialogContentX = dialogContentX;
        this->dialogContentY = dialogContentY;
        this->dialogContentWidth = dialogContentWidth;
        this->dialogContentHeight = dialogContentHeight;

        for (int i = 28; i >= 0; --i) {
            this->helpSectionHistoryStack[i + 1] = this->helpSectionHistoryStack[i];
        }
        this->helpSectionHistoryStack[0] = this->currentHelpSectionID;

        this->currentHelpSectionID = -1;
        this->helpContentScrollOffsetY = 0;
        MACRO_CALL_MEMBER(TextEditorState_Func::loadAndLayoutHelpContent, this)();
    }

}
}
