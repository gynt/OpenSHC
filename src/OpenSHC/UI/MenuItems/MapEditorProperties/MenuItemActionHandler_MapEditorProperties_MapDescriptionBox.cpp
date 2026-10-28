#include "../MapEditorProperties.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_TextEditorState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/DAT_EditorUnsavedChanges.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::UI::Enums::MenuModalType;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0042EDF0
        void MapEditorProperties::MenuItemActionHandler_MapEditorProperties_MapDescriptionBox()
        {
            if ((((DAT_GameCore::instance.U2_mapType_singleOrMulti != 0)
                     && (DAT_GameCore::instance.editorMapLoaded != 0))
                    && (DAT_MenuTextInputState::instance.currentModalDialog == OpenSHC::UI::Enums::MMT_NO_MENU))
                && ((DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE
                    && (DAT_EditorUnsavedChanges::instance = 1, DAT_GameCore::instance.mapDescriptionLocked == 0)))) {
                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    9);
                DAT_TextEditorState::instance.customTextMaxLength = 1000;
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextEditorState_Func::openMapDescriptionEditorDialog, DAT_TextEditorState::ptr)(0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::setCustomHelpText, DAT_TextEditorState::ptr)(
                    DAT_GameCore::instance.temporaryTextBufferOfSize1000, 999);
                MACRO_CALL(OpenSHC::OS_Func::_memset)(DAT_GameCore::instance.temporaryTextBufferOfSize1000, 0, 1000);
                DAT_GameCore::instance.descriptionUseStringTable = 0;
            }
        }

    }
}
}
