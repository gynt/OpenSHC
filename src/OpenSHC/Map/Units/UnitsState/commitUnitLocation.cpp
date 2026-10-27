#include "OpenSHC/Map/Units/UnitsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0053E820
        void UnitsState::commitUnitLocation(int unitID)
        {
            this->units[unitID].currentIndexInPathPlan = 0;
            this->units[unitID].movementState = 0;
            this->units[unitID].pendingPositionValid = 0;
            this->units[unitID].unknownMovementRelated_0x2d2 = 0;
            this->units[unitID].subTileStepProgress = 8;
            this->units[unitID].isHiddenInBuilding = 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setupUnitSharingCurrentTilePosition, this)(unitID);
        }

    }
}
}
