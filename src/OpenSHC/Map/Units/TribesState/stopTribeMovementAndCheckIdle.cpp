#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::States::UnitState;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00524890
        undefined4 TribesState::stopTribeMovementAndCheckIdle(int param_1)
        {
            short* psVar1;
            int unitID;
            int iVar2;
            int unitSelectionIndex;
            psVar1 = &this->tribes[param_1].size;
            unitSelectionIndex = 0;
            iVar2 = 0;
            if (0 < *psVar1) {
                do {
                    unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        param_1, unitSelectionIndex);
                    unitSelectionIndex = unitSelectionIndex + 1;
                    if ((DAT_UnitsState::instance.units[unitID].logicalState == OpenSHC::Map::Units::ULS_NORMAL)
                        && (DAT_UnitsState::instance.units[unitID].dying == 0)) {
                        if ((DAT_UnitsState::instance.units[unitID].usingTeleport == 0)
                            && (DAT_UnitsState::instance.units[unitID].field303_0x413 == 0)) {
                            if (DAT_UnitsState::instance.units[unitID].state.generic
                                != OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION)
                                continue;
                            MACRO_CALL_MEMBER(
                                OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                                DAT_UnitsState::ptr)(unitID);
                        }
                        iVar2 = iVar2 + 1;
                    }
                } while (unitSelectionIndex < *psVar1);
                if (iVar2 != 0) {
                    return (undefined4)(0);
                }
            }
            return (undefined4)(1);
        }

    }
}
}
