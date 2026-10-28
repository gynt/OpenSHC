#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // The new state 0x78 has no enum name. computeRandomWanderPath gets (1, 0, 1) when
        // tribe.pendingEventFlag == 0, else (0, 0, 0) (0x524E9A..0x524EB8). The tribe size is re-read every
        // iteration (0x524ECA).
        // FUNCTION: STRONGHOLDCRUSADER 0x00524E20
        void TribesState::applyLadderDestructionToTribeUnits(int tribeID)
        {
            int unitSelectionIndex = 0;
            if (this->tribes[tribeID].size > 0) {
                do {
                    int const unitID
                        = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                            tribeID, unitSelectionIndex);
                    ++unitSelectionIndex;
                    if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                        && DAT_UnitsState::instance.units[unitID].dying == 0) {
                        if (DAT_UnitsState::instance.units[unitID].usingTeleport != 0
                            || DAT_UnitsState::instance.units[unitID].isAssassinHookClimbing != 0
                            || DAT_UnitsState::instance.units[unitID].movementState == 2
                            || DAT_UnitsState::instance.units[unitID].state.generic == States::US_MELEE_ATTACK) {
                            return;
                        }
                        BOOLEnum pathFound;
                        if (this->tribes[tribeID].pendingEventFlag != 0) {
                            pathFound = MACRO_CALL_MEMBER(
                                UnitsState_Func::computeRandomWanderPath, DAT_UnitsState::ptr)(unitID, 0, 0, 0);
                        } else {
                            pathFound = MACRO_CALL_MEMBER(
                                UnitsState_Func::computeRandomWanderPath, DAT_UnitsState::ptr)(unitID, 1, 0, 1);
                        }
                        if (pathFound != FALSE) {
                            DAT_UnitsState::instance.units[unitID].state.generic = 0x78;
                        }
                    }
                } while (unitSelectionIndex < this->tribes[tribeID].size);
            }
        }

    }
}
}
