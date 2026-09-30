#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00525300
        void TribesState::setStateForAllTribeUnits(int param_1, undefined4 param_2)
        {
            int iVar1;
            int unitSelectionIndex;
            unitSelectionIndex = 0;
            if (0 < this->tribes[param_1].size) {
                do {
                    iVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        param_1, unitSelectionIndex);
                    unitSelectionIndex = unitSelectionIndex + 1;
                    if ((DAT_UnitsState::instance.units[iVar1].logicalState == OpenSHC::Map::Units::ULS_NORMAL)
                        && (DAT_UnitsState::instance.units[iVar1].dying == 0)) {
                        DAT_UnitsState::instance.units[iVar1].state.generic = (short)param_2;
                        DAT_UnitsState::instance.units[iVar1].animationCycleNumber = 0;
                        DAT_UnitsState::instance.units[iVar1].seated = 0;
                    }
                } while (unitSelectionIndex < this->tribes[param_1].size);
            }
        }

    }
}
}
