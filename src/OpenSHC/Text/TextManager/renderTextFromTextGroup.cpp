#include "../TextManager.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00424470
    void TextManager::renderTextFromTextGroup(eTextSections offsetIndex, int numInGroup, int xParam, int yParam,
        TextAlignment alignment, uint color, int fontSize, BOOLEnum keepOffsetX, int blendStrength)
    {
        char* _textAddress;
        _textAddress = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, this)(
            offsetIndex, numInGroup);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, this)(
            _textAddress, xParam, yParam, alignment, (BGR24)((int)(color)), fontSize, keepOffsetX, blendStrength);
        return;
    }

}
}
