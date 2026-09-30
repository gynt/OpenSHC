#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00524140
        undefined4 TribesState::tribeHasActiveLaddermanUnit(int param_1)
        {
            int iVar1;
            int iVar2;
            int unitSelectionIndex;
            iVar2 = (int)this->tribes[param_1].size;
            unitSelectionIndex = 0;
            if (0 < iVar2) {
                do {
                    iVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        param_1, unitSelectionIndex);
                    unitSelectionIndex = unitSelectionIndex + 1;
                    if ((((DAT_UnitsState::instance.units[iVar1].logicalState == OpenSHC::Map::Units::ULS_NORMAL)
                             && (DAT_UnitsState::instance.units[iVar1].dying == 0))
                            && (DAT_UnitsState::instance.units[iVar1].unitType == OpenSHC::Map::Units::UT_E_LADDER))
                        && (DAT_UnitsState::instance.units[iVar1].state.generic == ((UnitState)3))) {
                        return (undefined4)(1);
                    }
                } while (unitSelectionIndex < iVar2);
            }
            return (undefined4)(0);
        }

    }
}
}
