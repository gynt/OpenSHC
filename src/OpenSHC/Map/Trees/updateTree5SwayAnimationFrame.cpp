#include "OpenSHC/Map/Trees.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentTreeID.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    // Signed sway byte <= 0 (jg 0x4F266A) wraps the index to 0 and re-picks the table (B if windState == 2);
    // the frame is the signed sway byte (movsx 0x4F2695 / 0x4F269E), 0 while treeAnimFrozen.
    // FUNCTION: STRONGHOLDCRUSADER 0x004F2640
    void Trees::updateTree5SwayAnimationFrame()
    {
        int frameIndex = DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex;
        if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].useSwayTableB) {
            if (((signed char*)DAT_OrganismDefinedData::instance.Tree_1_B)[frameIndex] <= 0) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex = 0;
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].useSwayTableB
                    = DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].windState == 2;
            }
        } else if (((signed char*)DAT_OrganismDefinedData::instance.Tree_1_A)[frameIndex] <= 0) {
            DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex = 0;
            DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].useSwayTableB
                = DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].windState == 2;
        }
        frameIndex = DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex;
        DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].currentGmFrame
            = DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].useSwayTableB
            ? (int)((signed char*)DAT_OrganismDefinedData::instance.Tree_1_B)[frameIndex]
            : (int)((signed char*)DAT_OrganismDefinedData::instance.Tree_1_A)[frameIndex];
        if (DAT_LandscapeState::instance.treeAnimFrozen != 0) {
            DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].currentGmFrame = 0;
        }
    }

}
}
