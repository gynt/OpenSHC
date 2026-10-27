#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"

namespace OpenSHC {
namespace Map {

    // Live (state 2) apple trees in stage 3 only; closest by distanceHigh (signed jge 0x4F366C). Result needs
    // best < 30 (jl 0x4F3686) and treeID > 0 (jle 0x4F3697), both signed.
    // FUNCTION: STRONGHOLDCRUSADER 0x004F3610
    int LandscapeState::selectClosestAppleTree(int xPosition, int yPosition, int approachSide)
    {
        int bestDistance = 1000;
        int selectedTreeID = 0;
        for (int treeID = 1; treeID < this->maxTreeCount; treeID++) {
            if (this->trees[treeID].state == 2 && this->trees[treeID].treeType == OpenSHC::Map::Trees::TT_APPLE
                && this->trees[treeID].stage == 3) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(xPosition, yPosition, (short)this->trees[treeID].xPosition,
                    (short)this->trees[treeID].yPosition);
                if (DAT_DirectionAlgorithmState::instance.distanceHigh < bestDistance) {
                    bestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                    selectedTreeID = treeID;
                }
            }
        }
        if (bestDistance >= 30 || selectedTreeID <= 0) {
            return 0;
        }
        this->x = (short)this->trees[selectedTreeID].xPosition;
        this->y = (short)this->trees[selectedTreeID].yPosition;
        if (approachSide == 0) {
            this->x -= 2;
        }
        else if (approachSide == 1) {
            this->y += 2;
        }
        else if (approachSide == 2) {
            this->x += 2;
        }
        else {
            this->y -= 2;
        }
        return selectedTreeID;
    }

}
}
