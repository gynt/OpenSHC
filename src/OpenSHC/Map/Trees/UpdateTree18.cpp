#include "../../Map.func.hpp"
#include "../Trees.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentTreeID.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F2970
    void Trees::UpdateTree18()
    {
        int iVar1;
        int iVar2;
        iVar1 = DAT_CurrentTreeID::instance;
        iVar2 = (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].rng1 & 3U) + 4;
        DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk = iVar2;
        if (iVar2 == 7) {
            DAT_LandscapeState::instance.trees[iVar1].animationFrameUnk = 6;
            DAT_LandscapeState::instance.trees[iVar1].animationFrame2Unk
                = DAT_LandscapeState::instance.trees[iVar1].animationFrameUnk;
        }
        DAT_LandscapeState::instance.trees[iVar1].animationFrame2Unk = iVar2;
    }

}
}
