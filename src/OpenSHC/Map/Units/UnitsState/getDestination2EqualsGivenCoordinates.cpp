#include "../UnitsState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00533920
        BOOLEnum UnitsState::destination2DiffersFrom(int unitID, int x, int y)
        {
            if (this->units[unitID].savedDestinationX != x) {
                return TRUE;
            }
            return this->units[unitID].savedDestinationY != y;
        }

    }
}
}
