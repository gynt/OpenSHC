#include "../TextManager.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00424390
    void TextManager::renderText(eTextSections textGroupIndex, int textNumInGroup, int xPosition, int yPosition,
        TextAlignment textShift, uint color, uint param_7, int fontSize, BOOLEnum param_9)
    {
        char* _textAddress;
        int blendStrength;
        blendStrength = 0;
        _textAddress = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, this)(
            textGroupIndex, textNumInGroup);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, this)(
            _textAddress, xPosition, yPosition, textShift, color, param_7, fontSize, param_9, blendStrength);
        return;
    }

}
}
