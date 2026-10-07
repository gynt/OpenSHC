#include "../TextEditorState.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045F080
    int TextEditorState::helpToken_getHelpTokenAdvanceLength(HelpTextToken token)
    {
        switch (token) {
        case Text::Enums::HTT_PIC:
            return 4;
        case Text::Enums::HTT_FONT:
        case Text::Enums::HTT_COLOUR:
        case Text::Enums::HTT_LINK:
        case Text::Enums::HTT_SOUND:
        case Text::Enums::HTT_STRING:
        case Text::Enums::HTT_ENDCENTRE | Text::Enums::HTT_LINK:
        case Text::Enums::HTT_ENDCENTRE | Text::Enums::HTT_NEWPARAGRAPH:
            return 3;
        default:
            return 1;
        }
    }

}
}
