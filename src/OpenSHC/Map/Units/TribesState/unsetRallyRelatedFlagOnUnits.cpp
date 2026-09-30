#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00524000
        void TribesState::unsetRallyRelatedFlagOnUnits(int tribeID)
        {
            int _unitID;
            int _unitSelectionIndex;
            _unitSelectionIndex = 0;
            if (0 < this->tribes[tribeID].size) {
                do {
                    _unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        tribeID, _unitSelectionIndex);
                    _unitSelectionIndex = _unitSelectionIndex + 1;
                    if ((DAT_UnitsState::instance.units[_unitID].logicalState == OpenSHC::Map::Units::ULS_NORMAL)
                        && (DAT_UnitsState::instance.units[_unitID].dying == 0)) {
                        DAT_UnitsState::instance.units[_unitID].rallyRelatedFlag = 0;
                    }
                } while (_unitSelectionIndex < this->tribes[tribeID].size);
            }
        }

    }
}
}
