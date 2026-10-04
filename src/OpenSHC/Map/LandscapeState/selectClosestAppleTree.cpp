#include "../../Map.func.hpp"
#include "../LandscapeState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Trees/TreeType.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"

namespace OpenSHC {
namespace Map {

    using Map::Trees::TreeType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F3610
    int LandscapeState::selectClosestAppleTree(int xPosition, int yPosition, int param_3)
    {
        int _treeID;
        int _minimumDistance;
        Tree* pTVar3;
        int _selectedTreeID;
        _treeID = 1;
        _minimumDistance = 1000;
        _selectedTreeID = 0;
        if (1 < this->maxTreeCount) {
            pTVar3 = &this->trees[1];
            do {
                if (((pTVar3->state == 2) && (pTVar3->treeType == Map::Trees::TT_APPLEUnk))
                    && (pTVar3->stage == 3)) {
                    MACRO_CALL_MEMBER(
                        Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                        DAT_DirectionAlgorithmState::ptr)(xPosition, yPosition, (int)((int)((short)pTVar3->xPosition)),
                        (int)((int)((short)pTVar3->yPosition)));
                    if (DAT_DirectionAlgorithmState::instance.distanceHigh < _minimumDistance) {
                        _minimumDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                        _selectedTreeID = _treeID;
                    }
                }
                _treeID = _treeID + 1;
                pTVar3 = pTVar3 + 0x4e;
            } while (_treeID < this->maxTreeCount);
            if ((_minimumDistance < 30) && (0 < _selectedTreeID)) {
                this->x = (int)(short)this->trees[_selectedTreeID].xPosition;
                this->y = (int)(short)this->trees[_selectedTreeID].yPosition;
                if (param_3 == 0) {
                    this->x = this->x + -2;
                    return _selectedTreeID;
                }
                if (param_3 == 1) {
                    this->y = this->y + 2;
                    return _selectedTreeID;
                }
                if (param_3 == 2) {
                    this->x = this->x + 2;
                    return _selectedTreeID;
                }
                this->y = this->y + -2;
                return _selectedTreeID;
            }
        }
        return 0;
    }

}
}
