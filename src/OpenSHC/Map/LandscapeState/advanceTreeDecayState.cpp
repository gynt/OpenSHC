#include "../../Map.func.hpp"
#include "../LandscapeState.func.hpp"

namespace OpenSHC {
namespace Map {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F3080
    void LandscapeState::advanceTreeDecayState(int treeID, int param_2)
    {
        short sVar1;
        if (this->trees[treeID].uid == param_2) {
            sVar1 = this->trees[treeID].treeAdultHoodStageRelatedVisual3;
            if (0 < sVar1) {
                this->trees[treeID].treeAdultHoodStageRelatedVisual3 = sVar1 + -1;
            }
            if ((short)this->trees[treeID].treeAdultHoodStageRelatedVisual3 < 1) {
                this->trees[treeID].state = 3;
            }
            this->trees[treeID].zeroUpTo2 = 2;
        }
    }

}
}
