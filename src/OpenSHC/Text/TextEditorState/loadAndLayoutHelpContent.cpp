#include "../TextEditorState.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x004619D0
    void TextEditorState::loadAndLayoutHelpContent()
    {
        this->graphicFileCount = 0;
        this->soundFileCount = 0;
        this->totalContentHeight = -1;
        this->helpContentScrollOffsetY = 0;
        if (!this->isCustomTextMode) {
            MACRO_CALL_MEMBER(TextEditorState_Func::parseHlp, this)();
            MACRO_CALL_MEMBER(TextEditorState_Func::loadHelpSectionGraphics, this)();
        }
        this->caretTextPos = 0;
        MACRO_CALL_MEMBER(TextEditorState_Func::initializeAndLayoutHelpText, this)();
    }

}
}
