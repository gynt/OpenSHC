#include "OpenSHC/UI/MinimapViewState.func.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004B5300
    void MinimapViewState::triggerMinimapRedraw(int unknown)
    {
        if (this->pendingRedrawPasses == 0) {
            this->incrementalRedrawPercent = 0;
            this->pendingRedrawPasses = 2;
            return;
        }
        this->pendingRedrawPasses = 1;
    }

}
}
