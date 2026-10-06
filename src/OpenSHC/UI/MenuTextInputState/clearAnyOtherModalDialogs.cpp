#include "../MenuTextInputState.func.hpp"

#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    using UI::Enums::MenuModalType;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00491750
    void MenuTextInputState::clearAnyOtherModalDialogs()
    {
        DAT_UserTextHandlerState::instance.allowUserTextInput = 0;
        MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
            this->DAT_SomeTextArrayIndex);
        if (this->DAT_SomeTextArrayIndex) {
            MACRO_CALL_MEMBER(Text::UserTextHandler_Func::clearTextAndCursor, DAT_UserTextHandlerState::ptr)();
        }
        this->currentModalDialog = UI::Enums::MMT_NO_MENU;
        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
            UI::Enums::MMT_NONE, TRUE);
        MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::clearModalDialog2to6, this)();
        if (this->field42_0x9c) {
            DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
            DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 1;
        }
        this->field42_0x9c = 0;
    }

}
}
