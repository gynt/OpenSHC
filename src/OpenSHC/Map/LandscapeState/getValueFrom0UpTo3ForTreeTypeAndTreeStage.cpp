#include "../../Map.func.hpp"
#include "../LandscapeState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F1BE0
    undefined4 LandscapeState::getValueFrom0UpTo3ForTreeTypeAndTreeStage(undefined4 treeType, int treeStage)
    {
        if (treeStage < 2) {
        switchD_004f1bfb_caseD_5:
            return (undefined4)(1);
        }
        switch (treeType) {
        case 1:
        case 2:
            return (undefined4)(3);
        case 3:
        case 4:
        case 0xf:
            return (undefined4)(2);
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            goto switchD_004f1bfb_caseD_5;
        default:
            return (undefined4)(0);
        }
    }

}
}
