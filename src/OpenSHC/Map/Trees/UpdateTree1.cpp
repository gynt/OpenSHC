#include "OpenSHC/Map/Trees.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentTreeID.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    // Felled (fellState != 0): when the Tree_2 entry (A for stage 0) is <= 0 (signed jg 0x4F23C0) the index steps
    // back one. Standing: when the signed Tree_1 sway byte is <= 0 (jg 0x4F23EE) the index wraps to 0 and the
    // table is re-picked (B if windState == 2). Frame per stage (jump table 0x4F2620, stages 0..4, rest 0x92);
    // 0x94 while treeAnimFrozen.
    // FUNCTION: STRONGHOLDCRUSADER 0x004F2380
    void Trees::UpdateTree1()
    {
        if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].fellState != 0) {
            short const frameIndex = DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex;
            if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stage == 0) {
                if (DAT_OrganismDefinedData::instance.Tree_2_A[frameIndex] <= 0) {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex = frameIndex - 1;
                }
            } else if (DAT_OrganismDefinedData::instance.Tree_2_B[frameIndex] <= 0) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex = frameIndex - 1;
            }
        } else {
            int const frameIndex = DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex;
            if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].useSwayTableB) {
                if (((signed char*)DAT_OrganismDefinedData::instance.Tree_1_B)[frameIndex] <= 0) {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex = 0;
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].useSwayTableB = DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].windState == 2;
                }
            } else if (((signed char*)DAT_OrganismDefinedData::instance.Tree_1_A)[frameIndex] <= 0) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex = 0;
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].useSwayTableB = DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].windState == 2;
            }
        }
        switch (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stage) {
        case 0: {
            short const fellState = DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].fellState;
            if (fellState == 1) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].currentGmFrame
                    = DAT_OrganismDefinedData::instance
                          .Tree_2_A[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex]
                    + 0x8b;
                break;
            }
            if (fellState != 2) {
                if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].useSwayTableB) {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].currentGmFrame
                        = ((signed char*)DAT_OrganismDefinedData::instance.Tree_1_B)[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex] + 0x4b;
                } else {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].currentGmFrame
                        = ((signed char*)DAT_OrganismDefinedData::instance.Tree_1_A)[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex] + 0x4b;
                }
                break;
            }
        }
        // stage 0 with fellState 2 shares the default frame (je 0x4F2600)
        default:
            DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].currentGmFrame = 0x92;
            break;
        case 1: {
            short const fellState = DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].fellState;
            if (fellState == 1) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].currentGmFrame
                    = DAT_OrganismDefinedData::instance
                          .Tree_2_B[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex]
                    + 0x81;
            } else if (fellState == 2) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].currentGmFrame
                    = 0x8c - (short)DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].woodChunksRemaining;
            } else {
                if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].useSwayTableB) {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].currentGmFrame
                        = ((signed char*)DAT_OrganismDefinedData::instance.Tree_1_B)[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex] + 0x32;
                } else {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].currentGmFrame
                        = ((signed char*)DAT_OrganismDefinedData::instance.Tree_1_A)[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex] + 0x32;
                }
            }
            break;
        }
        case 2: {
            short const fellState = DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].fellState;
            if (fellState == 1) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].currentGmFrame
                    = DAT_OrganismDefinedData::instance
                          .Tree_2_B[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex]
                    + 0x75;
            } else if (fellState == 2) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].currentGmFrame
                    = 0x82 - (short)DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].woodChunksRemaining;
            } else {
                if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].useSwayTableB) {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].currentGmFrame
                        = ((signed char*)DAT_OrganismDefinedData::instance.Tree_1_B)[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex] + 0x19;
                } else {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].currentGmFrame
                        = ((signed char*)DAT_OrganismDefinedData::instance.Tree_1_A)[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex] + 0x19;
                }
            }
            break;
        }
        case 3:
        case 4: {
            short const fellState = DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].fellState;
            if (fellState == 1) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].currentGmFrame
                    = DAT_OrganismDefinedData::instance
                          .Tree_2_B[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex]
                    + 100;
            } else if (fellState == 2) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].currentGmFrame
                    = 0x76 - (short)DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].woodChunksRemaining;
            } else {
                if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].useSwayTableB) {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].currentGmFrame
                        = ((signed char*)DAT_OrganismDefinedData::instance.Tree_1_B)[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex];
                } else {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].currentGmFrame
                        = ((signed char*)DAT_OrganismDefinedData::instance.Tree_1_A)[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex];
                }
            }
            break;
        }
        }
        if (DAT_LandscapeState::instance.treeAnimFrozen != 0) {
            DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].currentGmFrame = 0x94;
        }
    }

}
}
