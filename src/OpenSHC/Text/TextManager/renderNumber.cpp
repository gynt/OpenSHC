#include "../TextManager.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

namespace OpenSHC {
namespace Text {

    using Text::TextAlignment;

    // FUNCTION: STRONGHOLDCRUSADER 0x00424620
    void TextManager::renderNumber(
        int number, int xPosition, int yPosition, uint color1, uint color2, int fontSize, BOOLEnum keepOffsetX)
    {
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumber2, this)(
            number, xPosition, yPosition, Text::TTA_LEFT, color1, color2, fontSize, keepOffsetX, 0);
        return;
    }

}
}
