#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::Map::Units::Unit;
    using OpenSHC::Map::Units::UnitTypeShort;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0053B800
    void Version::UpgradeMapUnitsTo_170()
    {
        UnitTypeShort UVar1;
        short sVar2;
        int iVar3;
        short* psVar4;
        int* piVar5;
        Unit* pUVar6;
        pUVar6 = &DAT_UnitsState::instance.units[1];
        do {
            UVar1 = pUVar6->unitType;
            if ((((((UVar1 == OpenSHC::Map::Units::UT_S_CATAPULT) || (UVar1 == OpenSHC::Map::Units::UT_S_TREBUCHET))
                      || (UVar1 == OpenSHC::Map::Units::UT_S_MANGONEL))
                     || ((UVar1 == OpenSHC::Map::Units::UT_S_TOWER
                         || (UVar1 == OpenSHC::Map::Units::UT_S_BATTERINGRAM))))
                    || ((UVar1 == OpenSHC::Map::Units::UT_S_SHIELD
                        || ((UVar1 == OpenSHC::Map::Units::UT_S_BALLISTA
                            || (UVar1 == OpenSHC::Map::Units::UT_S_FBALLISTA))))))
                && (iVar3 = 0, 0 < pUVar6->digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300)) {
                piVar5 = pUVar6->manningEngineerUIDRef;
                psVar4 = pUVar6->manningEngineerRef;
                do {
                    sVar2 = *psVar4;
                    if ((DAT_UnitsState::instance.units[sVar2].uid == *piVar5)
                        && (DAT_UnitsState::instance.units[sVar2].state.generic
                            == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk)) {
                        DAT_UnitsState::instance.units[sVar2].state.generic
                            = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
                    }
                    iVar3 = iVar3 + 1;
                    psVar4 = psVar4 + 1;
                    piVar5 = piVar5 + 1;
                } while (iVar3 < pUVar6->digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300);
            }
            pUVar6 = pUVar6 + 0x248;
        } while ((int)pUVar6 < 0x165141a);
    }

}
}
