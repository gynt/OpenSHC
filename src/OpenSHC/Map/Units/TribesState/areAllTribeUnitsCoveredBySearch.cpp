#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // The tribe size is read once before the loop (0x5250C2); SearchGenerationLayer is read signed (0x5250FC).
        // FUNCTION: STRONGHOLDCRUSADER 0x005250B0
        BOOLEnum TribesState::areAllTribeUnitsCoveredBySearch(int tribeID, int algTileFlag)
        {
            int const tribeSize = this->tribes[tribeID].size;
            for (int unitSelectionIndex = 0; unitSelectionIndex < tribeSize;) {
                int const unitID = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(tribeID, unitSelectionIndex);
                ++unitSelectionIndex;
                if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                    && DAT_UnitsState::instance.units[unitID].dying == 0
                    && DAT_TileMapState::instance.SearchGenerationLayer[DAT_UnitsState::instance.units[unitID].tile]
                        != algTileFlag) {
                    return FALSE;
                }
            }
            return TRUE;
        }

    }
}
}
