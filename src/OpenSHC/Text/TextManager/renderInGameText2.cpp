#include "../TextManager.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00424420
    void TextManager::renderInGameText2(eTextSections textOffsetIndex, int textNumInGroup, int xParam, int yParam,
        TextAlignment alignment, uint color1, uint color2, int fontSize, BOOLEnum keepOffsetX, int blendStrength)
    {
        char* textAddress;
        textAddress = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, this)(
            textOffsetIndex, textNumInGroup);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, this)(
            textAddress, xParam, yParam, alignment, color1, color2, fontSize, keepOffsetX, blendStrength);
        return;
    }

}
}
