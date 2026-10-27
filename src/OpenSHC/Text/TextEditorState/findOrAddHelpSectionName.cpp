// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../TextEditorState.func.hpp"

#include "OpenSHC/Text/TextEditorState.func.hpp"

#include "OpenSHC/Globals/DAT_UserHelpDefinedData.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045D1A0
    int TextEditorState::findOrAddHelpSectionName(char* param_1)
    {
        int helpSectionId
            = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::findHelpSectionIndexByName, this)(param_1);
        if (helpSectionId != -1) {
            return helpSectionId;
        }
        // FIXME:: This should overflow the buffer if filled to much. The counter can reach 500, which is one over the
        // buffer, ignoring that it will just overwrite this again and again.
        helpSectionId = this->helpSectionCount;
        strcpy(DAT_UserHelpDefinedData::instance.HelpSections[helpSectionId], param_1);
        if (this->helpSectionCount < 500) {
            ++this->helpSectionCount;
        }
        return helpSectionId;
    }

}
}
