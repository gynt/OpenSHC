#include "../TextManager.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

namespace OpenSHC {
namespace Text {

    using OpenSHC::Text::TextAlignment;

    // FUNCTION: STRONGHOLDCRUSADER 0x00424650
    void TextManager::renderLeftAlignedNumberToScreen(
        int number, int xParam, int yParam, uint color, int fontSize, BOOL keepOffsetX)
    {
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, this)(
            number, xParam, yParam, OpenSHC::Text::TTA_LEFT, color, fontSize, (BOOLEnum)((int)(keepOffsetX)), 0);
        return;
    }

}
}
