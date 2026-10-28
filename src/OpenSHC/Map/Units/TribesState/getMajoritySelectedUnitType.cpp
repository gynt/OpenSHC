#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitType;

        // tribeID is unused. maxUnitCount (uint) is compared signed (jle at 0x521744).
        // FUNCTION: STRONGHOLDCRUSADER 0x00521720
        UnitType TribesState::getMajoritySelectedUnitType(undefined4 tribeID, int* maximumCount)
        {
            int countOfUnitTypes[80];
            MACRO_CALL(OpenSHC::OS_Func::_memset)(countOfUnitTypes, 0, sizeof(countOfUnitTypes));
            for (int unitID = 1; unitID < (int)DAT_UnitsState::instance.maxUnitCount; ++unitID) {
                if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                    && DAT_UnitsState::instance.units[unitID].dying == 0
                    && DAT_UnitsState::instance.units[unitID].owner
                        == DAT_GameSynchronyState::instance.currentPlayerSlotID
                    && DAT_UnitsState::instance.units[unitID].isSelected != 0) {
                    int const unitType = DAT_UnitsState::instance.units[unitID].unitType;
                    if (unitType < 80) {
                        ++countOfUnitTypes[unitType];
                    }
                }
            }
            UnitType majorityType = UT_NONE;
            int maximum = -1;
            for (int unitType = UT_PEASANT; unitType < 80; ++unitType) {
                if (countOfUnitTypes[unitType] > maximum) {
                    majorityType = (UnitType)unitType;
                    maximum = countOfUnitTypes[unitType];
                }
            }
            if (majorityType != UT_NONE && maximumCount != 0) {
                *maximumCount = maximum;
            }
            return majorityType;
        }

    }
}
}
