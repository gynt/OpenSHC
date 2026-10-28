#include "../TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_UnitSelectionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // The parameter is a unit ID (header name tribeID); the original divides it signed (cdq at 0x52256B).
        // FUNCTION: STRONGHOLDCRUSADER 0x00522550
        BOOLEnum TribesState::unitIsSelectedByPlayer(uint tribeID)
        {
            int const unitID = (int)tribeID;
            return (BOOLEnum)((((short*)DAT_UnitsState::instance.selectedUnitsBitFlags)[unitID / 16]
                                  & (unsigned short)DAT_UnitSelectionDefinedData::instance.BitMaskHelper[unitID % 16])
                != 0);
        }

    }
}
}
