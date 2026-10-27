#include "../EntityState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00403790
        void EntityState::initializeSeagullMovementVector(int seagullID, int startX, int startY, int targetX, int targetY)
        {
            int dy = startY > targetY ? startY - targetY : targetY - startY;
            int dx = startX > targetX ? startX - targetX : targetX - startX;
            if (startX > targetX) {
                this->seagullArray[seagullID].lineStepDirX = -1;
            }
            else {
                this->seagullArray[seagullID].lineStepDirX = 1;
            }
            this->seagullArray[seagullID].lineStepDirY = startY <= targetY ? 1 : -1;
            if (dx == 0) {
                if (dy == 0) {
                    this->seagullArray[seagullID].lineStepMode = 0;
                }
                else {
                    this->seagullArray[seagullID].lineStepMode = 1;
                }
            }
            else if (dy == 0) {
                this->seagullArray[seagullID].lineStepMode = 2;
            }
            else if (dy > dx) {
                this->seagullArray[seagullID].lineStepMode = 3;
            }
            else {
                this->seagullArray[seagullID].lineStepMode = 4;
            }
            this->seagullArray[seagullID].lineStepsLeft = dx > dy ? dx : dy;
            if (this->seagullArray[seagullID].lineStepMode == 3) {
                this->seagullArray[seagullID].lineStepIncMinor = dx * 2;
                this->seagullArray[seagullID].lineStepError = dx * 2 - dy;
                this->seagullArray[seagullID].lineStepIncMajor = dx * 2 - dy * 2;
            }
            else if (this->seagullArray[seagullID].lineStepMode == 4) {
                this->seagullArray[seagullID].lineStepIncMinor = dy * 2;
                this->seagullArray[seagullID].lineStepError = dy * 2 - dx;
                this->seagullArray[seagullID].lineStepIncMajor = dy * 2 - dx * 2;
            }
        }

    }
}
}
