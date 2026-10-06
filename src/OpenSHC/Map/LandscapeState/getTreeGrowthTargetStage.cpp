#include "../../Map.func.hpp"
#include "../LandscapeState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F2C20
    undefined4 LandscapeState::getTreeGrowthTargetStage(int param_1)
    {
        int iVar1;
        switch (this->trees[param_1].treeType) {
        case ((TreeType)1):
            iVar1 = this->trees[param_1].stage;
            if (iVar1) {
                if (iVar1 == 1) {
                    return (undefined4)(2);
                }
                if (iVar1 == 2) {
                    return (undefined4)(3);
                }
                return (undefined4)(4);
            }
            break;
        case ((TreeType)2):
        case ((TreeType)3):
        case ((TreeType)4):
            iVar1 = this->trees[param_1].stage;
            if ((iVar1) && (iVar1 != 1)) {
                if (iVar1 != 2) {
                    return (undefined4)(3);
                }
                return (undefined4)(2);
            }
            break;
        case ((TreeType)5):
        case ((TreeType)6):
        case ((TreeType)7):
        case ((TreeType)8):
        case ((TreeType)9):
        case ((TreeType)10):
        case ((TreeType)0xb):
        case ((TreeType)0xc):
        case ((TreeType)0xd):
        case ((TreeType)0xe):
        case ((TreeType)0x10):
        case ((TreeType)0x11):
        case ((TreeType)0x12):
        case ((TreeType)0x13):
            break;
        default:
            return (undefined4)(0);
        }
        return (undefined4)(1);
    }

}
}
