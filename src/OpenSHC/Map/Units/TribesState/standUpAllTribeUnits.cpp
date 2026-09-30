#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00525370
        void TribesState::standUpAllTribeUnits(int param_1)
        {
            int iVar1;
            int unitSelectionIndex;
            Tribe* psVar1;
            psVar1 = &this->tribes[param_1];
            unitSelectionIndex = 0;
            if (0 < psVar1->size) {
                do {
                    iVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        param_1, unitSelectionIndex);
                    unitSelectionIndex = unitSelectionIndex + 1;
                    if ((DAT_UnitsState::instance.units[iVar1].logicalState == OpenSHC::Map::Units::ULS_NORMAL)
                        && (DAT_UnitsState::instance.units[iVar1].dying == 0)) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::standUpIfSeated, DAT_UnitsState::ptr)(
                            iVar1);
                        DAT_UnitsState::instance.units[iVar1].animationCycleNumber = 0;
                        DAT_UnitsState::instance.units[iVar1].rabbitMovementSlowdown = '\0';
                    }
                } while (unitSelectionIndex < psVar1->size);
            }
        }

    }
}
}
