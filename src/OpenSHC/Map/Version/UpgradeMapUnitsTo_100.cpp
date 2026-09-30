#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::Unit;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0053B380
    void Version::UpgradeMapUnitsTo_100()
    {
        int iVar1;
        int iVar2;
        Unit* psVar3;
        DAT_CurrentUnitSlotID::instance = 1;
        psVar3 = &DAT_UnitsState::instance.units[1];
        do {
            if ((psVar3->logicalState == OpenSHC::Map::Units::ULS_NORMAL)
                && (iVar2 = (int)psVar3->workplaceBuildingID_1, iVar2 != 0)) {
                iVar1 = psVar3->uid;
                DAT_BuildingsState::instance.buildings[iVar2].unitRefID = (short)DAT_CurrentUnitSlotID::instance;
                DAT_BuildingsState::instance.buildings[iVar2].unitRefUID = iVar1;
            }
            psVar3 = psVar3 + 0x248;
            DAT_CurrentUnitSlotID::instance = DAT_CurrentUnitSlotID::instance + 1;
        } while ((int)psVar3 < 0x16516c4);
    }

}
}
