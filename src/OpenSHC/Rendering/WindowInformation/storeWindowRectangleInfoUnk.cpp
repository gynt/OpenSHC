#include "OpenSHC/Rendering/WindowInformation.func.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x00467F60
    void WindowInformation::setGameWindowRect(LONG left, LONG right, LONG top, LONG bottom)
    {
        this->gameWindowRect.left = left;
        this->gameWindowRect.top = top;
        this->gameWindowRect.right = right;
        this->gameWindowRect.bottom = bottom;
    }

}
}
