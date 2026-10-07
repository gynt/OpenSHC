#include "../../../Map.func.hpp"
#include "../DirectionAlgorithmState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          Iterates over param_2 (a uint array) in 4-byte steps for param_1 / 4 iterations. Each step ANDs   the current
          word with param_3, adds it to the accumulator, then left-rotates the accumulator by 1   (via multiply-by-2
          with carry). Returns the final accumulated value. Used for compact bit-flag or   direction-mask aggregation.
          renamed by: Claude Sonnet 4.6
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0046CDF0
        uint DirectionAlgorithmState::computeMaskedBitAccumulator(int param_1, uint* param_2, uint param_3)
        {
            uint uVar1;
            int iVar2;
            uVar1 = 0;
            for (; 3 < param_1; param_1 = param_1 + -4) {
                iVar2 = uVar1 + (*param_2 & param_3);
                uVar1 = iVar2 * 2 | (uint)(iVar2 < 0);
                param_2 = param_2 + 1;
            }
            return uVar1;
        }

    }
}
}
