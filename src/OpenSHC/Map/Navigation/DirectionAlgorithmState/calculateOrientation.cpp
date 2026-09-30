#include "../../../Map.func.hpp"
#include "../DirectionAlgorithmState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0046C920
        void DirectionAlgorithmState::calculateOrientation(
            int currentXPosition, int currentYPosition, int destinationXPosition, int destinationYPosition)
        {
            if (destinationYPosition < currentYPosition) {
                if (destinationXPosition < currentXPosition) {
                    this->orientation = 7;
                }
                this->orientation = (uint)(currentXPosition < destinationXPosition);
            }
            if (destinationYPosition <= currentYPosition) {
                if (destinationXPosition < currentXPosition) {
                    this->orientation = 6;
                }
                this->orientation = ((destinationXPosition <= currentXPosition) - 1 & 0xfffffff3) + 0xf;
            }
            if (destinationXPosition < currentXPosition) {
                this->orientation = 5;
            }
            this->orientation = (destinationXPosition <= currentXPosition) + 3;
        }

    }
}
}
