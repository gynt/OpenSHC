#include "../MouseState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"

namespace OpenSHC {
namespace Input {

    // FUNCTION: STRONGHOLDCRUSADER 0x00470BC0
    void MouseState::updateRightDragCameraControl()
    {
        int iVar6 = this->mapOrientationCopy3;

        this->mouseBasedEvent = 0;
        this->rightDragField17c = 0;
        this->rightDragScrollSpeed = 0;
        this->activeCameraGesture = 0;

        DWORD DVar4 = timeGetTime();

        this->currentTime3 = DVar4;
        this->gestureElapsedMs = DVar4 - this->currentTime2;

        ++this->rightDragTickCount;
        if (this->gestureElapsedMs > this->gestureTimeoutMs) {
            this->currentTime2 = DVar4;
            this->rotateGestureFired = 0;
            this->zoomGestureState = 0;
            this->flatViewGestureState = 0;
        }

        int iVar5
            = MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::getMouseVectorLengthBasedOnDirection,
                DAT_DirectionAlgorithmState::ptr)(
                this->storedScreenSpaceX, this->storedScreenSpaceY, this->screenSpaceX, this->screenSpaceY, 4);

        if (iVar5 < 12 || this->scrollGestureLocked) {
            this->rightDragScrollSpeed = 0;
        } else if (iVar5 < 28) {
            this->rightDragScrollSpeed = iVar5 / 2;
            this->mouseBasedEvent = 2;
        } else {
            this->activeCameraGesture = 1;
            this->rotateGestureLocked = 1;
            this->flatViewGestureLocked = 1;
            this->zoomGestureLocked = 1;
            this->rightDragScrollSpeed = 40;
            this->mouseBasedEvent = 1;
        }

        iVar5 = MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::getMouseVectorLengthBasedOnDirection,
            DAT_DirectionAlgorithmState::ptr)(
            this->storedScreenSpaceX, this->storedScreenSpaceY, this->screenSpaceX, this->screenSpaceY, 0);
        if (iVar5 < 22 || this->rotateGestureLocked) {
            this->rightDragTickCount = 0;
            this->rotateGestureFired = 0;

            if (this->activeCameraGesture == 2 || iVar5 < 22) {
                this->currentTime2 = DVar4;
            }
        } else {
            this->scrollGestureLocked = 1;
            this->flatViewGestureLocked = 1;
            this->zoomGestureLocked = 1;
            this->activeCameraGesture = 2;
            this->gestureTimeoutMs = 1500;

            if (!this->rotateGestureFired) {
                this->rotateGestureFired = 1;

                iVar6 = this->mapOrientationCopy3 + 6;
                if (iVar6 >= 8) {
                    iVar6 -= 8;
                }

                this->rotateGestureRepeat = 0;
            } else {
                this->rotateGestureRepeat = 8;
            }
        }

        if (iVar6 != this->mapOrientationCopy2) {
            this->mapOrientationCopy2 = iVar6;
            this->mapOrientationCopy3 = iVar6;
            this->mouseBasedEvent = 3;
        }

        if (MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::getMouseVectorLengthBasedOnDirection,
                DAT_DirectionAlgorithmState::ptr)(
                this->storedScreenSpaceX, this->storedScreenSpaceY, this->screenSpaceX, this->screenSpaceY, 2)
                < 55
            || this->zoomGestureLocked) {

            this->rightDragTickCount = 0;
            if (this->activeCameraGesture == 3) {
                this->currentTime2 = DVar4;
            }
        } else {
            this->scrollGestureLocked = 1;
            this->flatViewGestureLocked = 1;
            this->rotateGestureLocked = 1;
            this->gestureTimeoutMs = 2000;
            this->activeCameraGesture = 3;

            if (this->zoomGestureState != 2) {
                this->mouseBasedEvent = 4;
                this->zoomGestureState = 1;
            }
        }

        if (MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::getMouseVectorLengthBasedOnDirection,
                DAT_DirectionAlgorithmState::ptr)(
                this->storedScreenSpaceX, this->storedScreenSpaceY, this->screenSpaceX, this->screenSpaceY, 6)
                < 55
            || this->flatViewGestureLocked) {

            this->rightDragTickCount = 0;
            if (this->activeCameraGesture == 4) {
                this->currentTime2 = DVar4;
            }
        } else {
            this->scrollGestureLocked = 1;
            this->zoomGestureLocked = 1;
            this->rotateGestureLocked = 1;
            this->gestureTimeoutMs = 2000;
            this->activeCameraGesture = 4;

            if (this->flatViewGestureState != 2) {
                this->mouseBasedEvent = 5;
                this->flatViewGestureState = 1;
            }
        }
    }

}
}
