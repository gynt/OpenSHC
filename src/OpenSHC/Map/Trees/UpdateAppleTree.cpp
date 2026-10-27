#include "OpenSHC/Map/Trees.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentTreeID.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    // Season stage < 6 (jge 0x4F26DB): stageTracker++, next season when tracker >= TreeStageLevels[15][stage + 1]
    // (signed jl 0x4F26FB), stage > 5 wraps to 0. Colour = rng1 & 7, remapped: early spring (stage 0, tracker <
    // 250) and stage 5 give 0->2, 1->4, 3->5, else 7 (the two blocks share code from 0x4F274D); the other seasons
    // give 2->0, 4->1, 5->3, else 6. Stage >= 6: colour 0, tracker++, tracker > 1200 sets state 3. Then the sway
    // wrap and one frame value per stage (jump table 0x4F28D0, stages 0..6; the original shares one store at
    // 0x4F28B6, written here per case); other stages keep the old frame (ja 0x4F28BC). 0 while treeAnimFrozen.
    // FUNCTION: STRONGHOLDCRUSADER 0x004F26C0
    void Trees::UpdateAppleTree()
    {
        if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stage < 6) {
            DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stageTracker++;
            if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stageTracker
                >= DAT_OrganismDefinedData::instance
                       .TreeStageLevels[15][DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stage + 1]) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stageTracker = 0;
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stage++;
                if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stage > 5) {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stage = 0;
                }
            }
            int const colorRng = DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].rng1 & 7;
            DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].visualVariation = colorRng;
            int const stage = DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stage;
            if (stage == 0 && DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stageTracker < 0xfa) {
                if (colorRng == 0) {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].visualVariation = 2;
                } else if (colorRng == 1) {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].visualVariation = 4;
                } else {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].visualVariation
                        = colorRng == 3 ? 5 : 7;
                }
            } else if (stage == 5) {
                if (colorRng == 0) {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].visualVariation = 2;
                } else if (colorRng == 1) {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].visualVariation = 4;
                } else {
                    DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].visualVariation
                        = colorRng == 3 ? 5 : 7;
                }
            } else if (colorRng == 2) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].visualVariation = 0;
            } else if (colorRng == 4) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].visualVariation = 1;
            } else {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].visualVariation = colorRng == 5 ? 3 : 6;
            }
        } else {
            DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].visualVariation = 0;
            DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stageTracker++;
            if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stageTracker > 0x4b0) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].state = 3;
            }
        }
        int const frameIndex = DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex;
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
        switch (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].stage) {
        case 0:
        case 6:
            if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].useSwayTableB) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].currentGmFrame
                    = ((signed char*)DAT_OrganismDefinedData::instance.Tree_1_B)[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex];
            } else {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].currentGmFrame
                    = ((signed char*)DAT_OrganismDefinedData::instance.Tree_1_A)[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex];
            }
            break;
        case 1:
            if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].useSwayTableB) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].currentGmFrame
                    = ((signed char*)DAT_OrganismDefinedData::instance.Tree_1_B)[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex] + 0x19;
            } else {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].currentGmFrame
                    = ((signed char*)DAT_OrganismDefinedData::instance.Tree_1_A)[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex] + 0x19;
            }
            break;
        case 2:
        case 4:
        case 5:
            if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].useSwayTableB) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].currentGmFrame
                    = ((signed char*)DAT_OrganismDefinedData::instance.Tree_1_B)[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex] + 0x4b;
            } else {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].currentGmFrame
                    = ((signed char*)DAT_OrganismDefinedData::instance.Tree_1_A)[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex] + 0x4b;
            }
            break;
        case 3:
            if (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].useSwayTableB) {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].currentGmFrame
                    = ((signed char*)DAT_OrganismDefinedData::instance.Tree_1_B)[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex] + 0x32;
            } else {
                DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].currentGmFrame
                    = ((signed char*)DAT_OrganismDefinedData::instance.Tree_1_A)[DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameIndex] + 0x32;
            }
            break;
        }
        if (DAT_LandscapeState::instance.treeAnimFrozen != 0) {
            DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].currentGmFrame = 0;
        }
    }

}
}
