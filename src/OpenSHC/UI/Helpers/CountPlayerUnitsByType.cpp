#include "../Helpers.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitTypeInt.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitTypeRelatedCounter.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Map::Units::Unit;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::UnitTypeInt;

    // FUNCTION: STRONGHOLDCRUSADER 0x00440360
    void Helpers::CountPlayerUnitsByType()
    {
        UnitTypeInt _unitType;
        Unit* _unit;
        int iVar2;
        int iVar1 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        MACRO_CALL(OpenSHC::OS_Func::_memset)(DAT_UnitTypeRelatedCounter::instance, 0, (size_t)((int)(320)));
        if (1 < (int)DAT_UnitsState::instance.maxUnitCount) {
            iVar2 = DAT_UnitsState::instance.maxUnitCount - 1;
            _unit = &DAT_UnitsState::instance.units[1];
            do {
                if ((((_unit->logicalState != OpenSHC::Map::Units::ULS_INVISIBLE) && (_unit->owner == iVar1))
                        && (_unit->isStalked == 0))
                    && ((_unitType = (UnitTypeInt)(short)_unit->unitType,
                        0 < (int)_unitType && (((int)_unitType < 66 || (70 < (int)_unitType)))))) {
                    DAT_UnitTypeRelatedCounter::instance[_unitType]
                        = DAT_UnitTypeRelatedCounter::instance[_unitType] + 1;
                }
                _unit = _unit + 0x248;
                iVar2 = iVar2 + -1;
            } while (iVar2 != 0);
        }
    }

}
}
