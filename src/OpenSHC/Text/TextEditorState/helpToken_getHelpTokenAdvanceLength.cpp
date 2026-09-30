#include "../TextEditorState.func.hpp"

namespace OpenSHC {
namespace Text {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0045F080
    int TextEditorState::helpToken_getHelpTokenAdvanceLength(HelpTextToken token)
    {
        switch (token) {
        case OpenSHC::Text::Enums::HTT_PIC:
            return 4;
        case OpenSHC::Text::Enums::HTT_FONT:
        case OpenSHC::Text::Enums::HTT_COLOUR:
        case OpenSHC::Text::Enums::HTT_LINK:
        case OpenSHC::Text::Enums::HTT_SOUND:
        case OpenSHC::Text::Enums::HTT_STRING:
        case OpenSHC::Text::Enums::HTT_ENDCENTRE | OpenSHC::Text::Enums::HTT_LINK:
        case OpenSHC::Text::Enums::HTT_ENDCENTRE | OpenSHC::Text::Enums::HTT_NEWPARAGRAPH:
            return 3;
        default:
            return 1;
        }
    }

}
}
