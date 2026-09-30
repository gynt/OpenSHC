#include "../../../Map.func.hpp"
#include "../DirectionAlgorithmState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          in one instance, param_3 and param_4 are both 200 if you want to orientation towards the center   of the map
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0046C9E0
        void DirectionAlgorithmState::calculatePreferredRelativeOrientation(
            int param_1, int param_2, int param_3, int param_4)
        {
            if (param_3 < param_1) {
                this->distanceX = param_1 - param_3;
            } else {
                this->distanceX = param_3 - param_1;
            }
            if (param_4 < param_2) {
                this->distanceY = param_2 - param_4;
            } else {
                this->distanceY = param_4 - param_2;
            }
            if (this->distanceY * 2 < this->distanceX) {
                this->orientation = (uint)(param_3 < param_1) * 4 + 2;
            }
            if (this->distanceX * 2 < this->distanceY) {
                this->orientation = (param_4 < param_2) - 1 & 4;
            }
            if (param_4 < param_2) {
                this->orientation = ((param_1 <= param_3) - 1 & 6) + 1;
            }
            if (param_2 < param_4) {
                this->orientation = (uint)(param_3 < param_1) * 2 + 3;
            }
            /*
              sentinel for an invalid value?
             */
            this->orientation = 15;
        }

    }
}
}
