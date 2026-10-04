#include "../TextManager.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x004245D0
    void TextManager::renderMultilineText4Unk(eTextSections textOffsetIndex, int textNumInGroup, int xPos, int yPos,
        int maxWidth, uint color, int fontSize, int blendStrength)
    {
        char* text;
        this->field12_0x30 = 1;
        text = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, this)(
            textOffsetIndex, textNumInGroup);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText5Unk, this)(
            text, xPos, yPos, maxWidth, color, fontSize, blendStrength);
        return;
    }

}
}
