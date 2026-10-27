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

    // FUNCTION: STRONGHOLDCRUSADER 0x00461CF0
    void TextEditorState::openScenarioHelpDialog(int sectionId)
    {
        if (!this->isDialogStateInitialized) {
            this->isDialogStateInitialized = TRUE;
            this->helpDialogVariant = 2;
            this->useInGameHelpHandler = FALSE;
            this->showTagSymbols = 0;
            this->isEditorMode = FALSE;
            this->isCustomTextMode = FALSE;
            DAT_UserTextHandlerState::instance.inputBufferIndex = 0;
            this->helpContentScrollX = 0;
            this->helpContentScrollY = 0;
        }
        this->caretTextPos = 0;
        if (sectionId == -1) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::closeHelpDialogAndReturnToMenu, this)();
            return;
        }
        this->isTextHelpDialogMode = TRUE;
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
            OpenSHC::UI::Enums::MMT_DISPLAY_SCENARIO_HELP_TEXT, FALSE);

        int modalX;
        int modalY;
        int modalWidth;
        int modalHeight;
        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::fillWithMenuModalDimensions, DAT_MenuModalComposition1::ptr)(
            &modalX, &modalY, &modalWidth, &modalHeight);

        g_textDialogPaddingX::instance = 10;
        g_textDialogPaddingY::instance = 10;
        g_textDialogMarginWidth::instance = 45;
        g_textDialogMarginHeight::instance = 20;
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

        this->currentHelpSectionID = sectionId;
        this->helpContentScrollOffsetY = 0;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::loadAndLayoutHelpContent, this)();
    }

}
}
