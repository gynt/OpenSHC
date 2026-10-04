#include "../TextManager.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00424540
    void TextManager::renderMultilineText2Unk(
        eTextSections textOffsetIndex, int textNumInGroup, int xPos, int yPos, int maxWidth, uint color, int fontSize)
    {
        char* text;
        int blendStrength;
        blendStrength = 0;
        text = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, this)(
            textOffsetIndex, textNumInGroup);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText5Unk, this)(
            text, xPos, yPos, maxWidth, color, fontSize, blendStrength);
        return;
    }

}
}
