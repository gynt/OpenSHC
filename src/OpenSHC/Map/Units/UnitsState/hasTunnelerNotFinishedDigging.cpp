#include "../UnitsState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x005339F0
        BOOLEnum UnitsState::isUnitMovementIdle(int unitID)
        {
            return this->units[unitID].movementState == 0;
        }

    }
}
}
