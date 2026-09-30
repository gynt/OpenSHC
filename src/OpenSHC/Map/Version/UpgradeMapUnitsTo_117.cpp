#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::Unit;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0053B1F0
    void Version::UpgradeMapUnitsTo_117()
    {
        Unit* psVar1;
        psVar1 = &DAT_UnitsState::instance.units[1];
        DAT_CurrentUnitSlotID::instance = 2500;
        do {
            if (psVar1->logicalState == OpenSHC::Map::Units::ULS_NORMAL) {
                psVar1->movementSpeed
                    = (short)DAT_UnitPropertiesDefinedData::instance.UNIT_MOVEMENT_SPEED_ARRAY[(short)psVar1->unitType];
                if (psVar1->facingDirection == 0xf) {
                    psVar1->facingDirection = 4;
                }
                if (psVar1->unitType != OpenSHC::Map::Units::UT_A_ASSASSIN) {
                    psVar1->field306_0x418 = 0;
                }
            }
            psVar1 = psVar1 + 0x248;
        } while ((int)psVar1 < 0x1651640);
    }

}
}
