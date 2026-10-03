#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::Unit;

    // FUNCTION: STRONGHOLDCRUSADER 0x0053B4F0
    void Version::UpgradeMapUnitsAttackTileLogicTo_122()
    {
        Unit* psVar1;
        psVar1 = &DAT_UnitsState::instance.units[1];
        DAT_CurrentUnitSlotID::instance = 0x9c4;
        do {
            if (psVar1->logicalState == OpenSHC::Map::Units::ULS_NORMAL) {
                psVar1->attackAtTileX = psVar1->targetedUnitID__OR__engineerMannedSiegeEngineRef;
                psVar1->attackAtTileY
                    = (short)
                          psVar1->targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID;
            }
            psVar1 = psVar1 + 0x248;
        } while ((int)psVar1 < 0x165172a);
    }

}
}
