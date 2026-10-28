#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // The tribe size is read once before the loop (0x5240E2); LogicLayer bit 0x40000000 (0x52411E).
        // FUNCTION: STRONGHOLDCRUSADER 0x005240D0
        int TribesState::getFirstUnitInTribeThatIsOnXTerrain(int selectionID)
        {
            int const tribeSize = this->tribes[selectionID].size;
            for (int unitSelectionIndex = 0; unitSelectionIndex < tribeSize;) {
                int const unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe,
                    this)(selectionID, unitSelectionIndex);
                ++unitSelectionIndex;
                if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                    && DAT_UnitsState::instance.units[unitID].dying == 0
                    && (DAT_TileMapState::instance.LogicLayer[DAT_UnitsState::instance.units[unitID].tile] & 0x40000000)
                        != 0) {
                    return unitID;
                }
            }
            return 0;
        }

    }
}
}
