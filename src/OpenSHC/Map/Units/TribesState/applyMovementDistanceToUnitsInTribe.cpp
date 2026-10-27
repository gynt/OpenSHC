#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // The tribe size is re-read every iteration (0x52518B).
        // FUNCTION: STRONGHOLDCRUSADER 0x00525130
        void TribesState::applyMovementDistanceToUnitsInTribe(int tribeID)
        {
            for (int unitSelectionIndex = 0; unitSelectionIndex < this->tribes[tribeID].size;) {
                int const unitID = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(tribeID, unitSelectionIndex);
                ++unitSelectionIndex;
                if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                    && DAT_UnitsState::instance.units[unitID].dying == 0) {
                    DAT_UnitsState::instance.units[unitID].movementDistance
                        = DAT_TileMapState::instance.SearchDistanceLayer[DAT_UnitsState::instance.units[unitID].tile];
                }
            }
        }

    }
}
}
