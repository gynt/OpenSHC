#include "../UserTextHandler.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00469790
    void UserTextHandler::resetToTextIndex(int textIndex)
    {
        if ((!this->allowUserTextInput) && ((uint)textIndex < 0x10)) {
            this->textArrayIndex = textIndex;
            this->textCursorIndexArray[textIndex] = 0;
            this->unknown01 = 1;
            this->returnPressed = 0;
        }
        return;
    }

}
}
