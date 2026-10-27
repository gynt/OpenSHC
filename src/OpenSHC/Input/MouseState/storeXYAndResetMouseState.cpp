#include "../MouseState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Input {

    // FUNCTION: STRONGHOLDCRUSADER 0x004687F0
    void MouseState::storeXYAndResetMouseState()
    {
        for (int i = 0; i < 10; ++i) {
            this->mouseXY[i].x = 0;
            this->mouseXY[i].y = 0;
            this->mouseXY[i].unknownZero01 = 0;
            this->mouseXY[i].unknownOne02 = 0;
        }

        this->index = 0;

        this->storedScreenSpaceX = this->screenSpaceX;
        this->storedScreenSpaceY = this->screenSpaceY;

        for (int i = 0; i < 10; ++i) {
            this->mouseXY8[i] = 8;
        }

        this->rightDragField184 = 0;
        this->rightDragTickCount = 0;
        this->rotateGestureRepeat = 8;
        this->zoomGestureState = 0;
        this->flatViewGestureState = 0;

        this->mapOrientationCopy1 = DAT_TileMapState::instance.mapOrientation;
        this->mapOrientationCopy2 = DAT_TileMapState::instance.mapOrientation;
        this->mapOrientationCopy3 = DAT_TileMapState::instance.mapOrientation;

        this->rotateGestureFired = 0;

        this->currentTime1 = timeGetTime();
        this->currentTime2 = timeGetTime();
        this->currentTime3 = timeGetTime();

        this->gestureElapsedMs = 0;
        this->activeCameraGesture = 0;
        this->rotateGestureLocked = 0;
        this->scrollGestureLocked = 0;
        this->flatViewGestureLocked = 0;
        this->zoomGestureLocked = 0;
    }

}
}
