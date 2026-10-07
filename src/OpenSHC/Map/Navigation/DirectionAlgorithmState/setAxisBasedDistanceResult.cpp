#include "../../../Map.func.hpp"
#include "../DirectionAlgorithmState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          Sets a low value and high value, depending on which axis is further away   decompilerscript: committed:
          2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0046CC80
        int DirectionAlgorithmState::setAxisBasedDistanceResult(
            int destinationXPosition, int destinationYPosition, int fromXPosition, int fromYPosition)
        {
            if (fromXPosition < destinationXPosition) {
                this->distanceX = destinationXPosition - fromXPosition;
            } else {
                this->distanceX = fromXPosition - destinationXPosition;
            }
            if (fromYPosition < destinationYPosition) {
                this->distanceY = destinationYPosition - fromYPosition;
            } else {
                this->distanceY = fromYPosition - destinationYPosition;
            }
            if (this->distanceX < this->distanceY) {
                this->distanceLow = this->distanceX;
                this->distanceHigh = this->distanceY;
                return this->distanceX + this->distanceY;
            }
            this->distanceHigh = this->distanceX;
            this->distanceLow = this->distanceY;
            return this->distanceX + this->distanceY;
        }

    }
}
}
