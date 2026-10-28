#include "../TextEditorState.func.hpp"

#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_UserHelpDefinedData.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045F130
    TextEditorState* TextEditorState::Constructor_TextEditorState()
    {
        this->isDialogStateInitialized = 0;
        this->helpDialogVariant = 0;
        this->restoreScreenBltPending = 0;
        this->showTagSymbols = 0;
        this->isEditorMode = 0;
        this->helpTextLength = 0;
        this->pendingTokenTypeToSkip = 0;
        this->useWideHelpLayout = 0;

        MACRO_CALL_MEMBER(TextEditorState_Func::resetHelpStateFields, this)();

        this->DAT_PointerToTemporaryTextMemory = (LPWSTR)MACRO_CALL(OS_Func::_malloc)(40000);
        this->customTextMaxLength = -1;

        // FIXME:: Requires a finishing zero case, or it will not set the counter
        for (int counter = 0; counter < 500; ++counter) {
            if (strlen(DAT_UserHelpDefinedData::instance.HelpSections[counter])) {
                continue;
            }
            this->helpSectionCount = counter;
            break;
        }

        for (int i = 0; i < 20; ++i) {
            this->stringSubstitutions[i] = 0;
        }
        return this;
    }

}
}
