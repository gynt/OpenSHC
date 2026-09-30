#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00524060
        BOOLEnum TribesState::isTribeAllAssassins(int tribeID)
        {
            int _unitID;
            int iVar1;
            int _unitSelectionIndex;
            iVar1 = (int)this->tribes[tribeID].size;
            _unitSelectionIndex = 0;
            if (0 < iVar1) {
                do {
                    _unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        tribeID, _unitSelectionIndex);
                    _unitSelectionIndex = _unitSelectionIndex + 1;
                    if (((DAT_UnitsState::instance.units[_unitID].logicalState == OpenSHC::Map::Units::ULS_NORMAL)
                            && (DAT_UnitsState::instance.units[_unitID].dying == 0))
                        && (DAT_UnitsState::instance.units[_unitID].unitType != OpenSHC::Map::Units::UT_A_ASSASSIN)) {
                        return FALSE;
                    }
                } while (_unitSelectionIndex < iVar1);
            }
            return TRUE;
        }

    }
}
}
