#include "../TextManager.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x004243E0
    void TextManager::renderText2(eTextSections textOffsetIndex, int textNumInGroup, int xParam, int yParam,
        TextAlignment alignment, uint color, int fontSize, BOOLEnum keepOffsetX)
    {
        char* textAddress;
        int blendStrength;
        blendStrength = 0;
        textAddress = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, this)(
            textOffsetIndex, textNumInGroup);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, this)(
            textAddress, xParam, yParam, alignment, (BGR24)((int)(color)), fontSize, keepOffsetX, blendStrength);
        return;
    }

}
}
