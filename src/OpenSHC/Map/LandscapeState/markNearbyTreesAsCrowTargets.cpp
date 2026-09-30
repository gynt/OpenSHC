#include "../../Map.func.hpp"

#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F30D0
    void LandscapeState::markNearbyTreesAsCrowTargets(int x, int y)
    {
        BOOLEnum BVar1;
        Tree* piVar2;
        int _treeID;
        _treeID = 1;
        if (1 < this->maxTreeCount) {
            piVar2 = &this->trees[1];
            do {
                if ((((piVar2->state == 2) && (piVar2->stage < 4))
                        && (BVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::isTreeAdult, this)(
                                _treeID, piVar2->uid),
                            BVar1 != FALSE))
                    && (MACRO_CALL_MEMBER(
                            OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                            DAT_DirectionAlgorithmState::ptr)(
                            x, y, (int)((int)((short)piVar2->xPosition)), (int)((int)((short)piVar2->yPosition))),
                        DAT_DirectionAlgorithmState::instance.distanceHigh < 4)) {
                    piVar2->unknownDistanceRelatedToCrow = 1;
                }
                _treeID = _treeID + 1;
                piVar2 = piVar2 + 0x27;
            } while (_treeID < this->maxTreeCount);
        }
    }

}
}
