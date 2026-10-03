#include "../TextManager.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00469F70
    int TextManager::getTextWidthTillCursorUnk(char* text, int cursorIndex, int fontSize)
    {
        if (text == (char*)0x0) {
            return 0;
        }
        int _widthUnk = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::getWidthOfText,
            &DAT_TextManagerObject::instance.fontSizeClassArray[fontSize])(text, cursorIndex);
        return _widthUnk;
    }

}
}
