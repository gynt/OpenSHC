#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x0053D850
        void UnitsState::resumeMovementAfterInterruption(int unitID)
        {
            if (this->units[unitID].dying != 0) {
                return;
            }
            if (this->units[unitID].logicalState == OpenSHC::Map::Units::ULS_REMOVE) {
                return;
            }
            short _destinationY = this->units[unitID].savedDestinationY;
            short _destinationX = this->units[unitID].savedDestinationX;
            this->units[unitID].state = this->units[unitID].state_3;
            this->units[unitID].movementState = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, this)(
                unitID, _destinationX, _destinationY, 0);
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::changeDestinationByLeftover, this)(unitID);
            if (this->units[unitID].unitType != OpenSHC::Map::Units::UT_LIONSHWOLF
                && this->units[unitID].unitType != OpenSHC::Map::Units::UT_CAGEDOG) {
                return;
            }
            int const currentUnitID = DAT_CurrentUnitSlotID::instance;
            DAT_UnitsState::instance.units[currentUnitID].state.generic
                = OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                DAT_UnitsState::ptr)(currentUnitID);
        }

    }
}
}
