#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // The tribe size is read once before the loop (0x5242C5); an empty tribe returns UT_E_ARCHER (0x5242D6).
        // FUNCTION: STRONGHOLDCRUSADER 0x005242B0
        UnitType TribesState::getMajorityArcherTypeEuropeanOrArabian(int selectionID)
        {
            int const tribeSize = this->tribes[selectionID].size;
            int archerCounts[2]; // [0] European, [1] Arabian
            archerCounts[0] = 0;
            archerCounts[1] = 0;
            for (int unitSelectionIndex = 0; unitSelectionIndex < tribeSize;) {
                int const unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe,
                    this)(selectionID, unitSelectionIndex);
                ++unitSelectionIndex;
                if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                    && DAT_UnitsState::instance.units[unitID].dying == 0) {
                    UnitTypeShort const unitType = DAT_UnitsState::instance.units[unitID].unitType;
                    if (unitType == UT_A_ARCHER) {
                        ++archerCounts[1];
                    }
                    if (unitType == UT_E_ARCHER) {
                        ++archerCounts[0];
                    }
                }
            }
            if (archerCounts[1] > archerCounts[0]) {
                return UT_A_ARCHER;
            }
            return UT_E_ARCHER;
        }

    }
}
}
