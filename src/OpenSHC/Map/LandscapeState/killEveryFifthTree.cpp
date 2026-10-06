#include "../../Map.func.hpp"
#include "../LandscapeState.func.hpp"

#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F2DA0
    void LandscapeState::killEveryFifthTree()
    {
        Tree* piVar1;
        int iVar1;
        iVar1 = 1;
        if (1 < this->maxTreeCount) {
            piVar1 = &this->trees[1];
            do {
                if ((((piVar1->state) && ((int)(short)piVar1->treeType - 1U < 4)) && (1 < piVar1->stage))
                    && ((piVar1->stage < 5 && (((int)SEC_RNG::instance.currentNumber2 ^ piVar1->rng1) % 5 != 0)))) {
                    piVar1->stage = 5;
                }
                iVar1 = iVar1 + 1;
                piVar1 = piVar1 + 0x27;
            } while (iVar1 < this->maxTreeCount);
        }
    }

}
}
