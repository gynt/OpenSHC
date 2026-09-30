#include "../../../Map.func.hpp"
#include "../EntityState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        /*
          decompilerscript: committed: 2025-01-30 21:56:35.138000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00402BD0
        undefined4 EntityState::angleToRotationFrameIndex(int param_1)
        {
            if (param_1 < 6) {
                if (param_1 < -0x31) {
                    return (undefined4)(0);
                }
                if (param_1 < -0x22) {
                    return (undefined4)(1);
                }
                if (param_1 < -0x10) {
                    return (undefined4)(2);
                }
                if (param_1 < -4) {
                    return (undefined4)(3);
                }
            } else {
                if (param_1 < 0x15) {
                    return (undefined4)(5);
                }
                if (param_1 < 0x24) {
                    return (undefined4)(6);
                }
                if (param_1 < 0x33) {
                    return (undefined4)(7);
                }
                if (param_1 < 0x5b) {
                    return (undefined4)(8);
                }
            }
            return (undefined4)(4);
        }

    }
}
}
