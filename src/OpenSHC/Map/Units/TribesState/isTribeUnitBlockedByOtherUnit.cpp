#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // The tribe size is read once before the loop (0x524B44). UnitLayer is read signed (movsx, 0x524BB6).
        // FUNCTION: STRONGHOLDCRUSADER 0x00524B30
        undefined4 TribesState::isTribeUnitBlockedByOtherUnit(int tribeID)
        {
            int unitSelectionIndex = 0;
            int const tribeSize = this->tribes[tribeID].size;
            for (;;) {
                int unitID;
                do {
                    if (unitSelectionIndex >= tribeSize) {
                        return 0;
                    }
                    unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        tribeID, unitSelectionIndex);
                    ++unitSelectionIndex;
                } while (DAT_UnitsState::instance.units[unitID].logicalState != ULS_NORMAL
                    || DAT_UnitsState::instance.units[unitID].dying != 0);
                if (DAT_UnitsState::instance.units[unitID].usingTeleport != 0
                    || DAT_UnitsState::instance.units[unitID].isAssassinHookClimbing != 0
                    || DAT_UnitsState::instance.units[unitID].movementState == 2
                    || DAT_UnitsState::instance.units[unitID].state.generic == States::US_MELEE_ATTACK
                    || DAT_UnitsState::instance.units[unitID].laddermanIsInPosition != 0) {
                    return 0;
                }
                int const occupantUnitID
                    = (short)DAT_TileMapState::instance.UnitLayer[DAT_UnitsState::instance.units[unitID].tile];
                if (occupantUnitID != 0 && unitID != occupantUnitID
                    && DAT_UnitsState::instance.units[occupantUnitID].movementState != 2) {
                    return 1;
                }
            }
        }

    }
}
}
