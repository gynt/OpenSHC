#include "../MouseState.func.hpp"

namespace OpenSHC {
namespace Input {

    // FUNCTION: STRONGHOLDCRUSADER 0x004709B0
    MouseState* MouseState::Constructor_MouseState()
    {
        this->time0 = timeGetTime();
        MACRO_CALL_MEMBER(MouseState_Func::storeXYAndResetMouseState, this)();
        this->rightDragCameraWidgetEnabled = 0;
        this->flag = 0;
        this->resetPending = 0;
        this->waitCursorToggle = 0;
        this->cursorType = 0;
        this->ctorZeroed1e4 = 0;
        this->cursorOverlayMode = -1;
        return this;
    }

}
}
