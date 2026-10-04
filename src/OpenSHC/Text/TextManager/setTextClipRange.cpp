#include "../TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00469F20
    void TextManager::setTextClipRange(dword param_1, dword param_2)
    {
        this->textClipMin = param_1;
        this->textClipMax = param_2;
        return;
    }

}
}
