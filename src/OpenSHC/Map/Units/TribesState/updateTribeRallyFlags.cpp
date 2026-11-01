#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;
        using WindowsHelper::Enums::BOOLEnum;

        /*
          One flag, not two: the original zeroes it once, writes 1 into it inside the loop
          and reloads it into the return register at the loop exit (0x523fef). The
          decompiler's `uVar3 = local_4` at the bottom of every iteration is that single
          reload hoisted into the body.

          The `rallyRelatedFlag = 0` store at 0x523fc7 sits between the two rally tests and
          runs for every living unit, so the gate has to be two nested ifs rather than one
          comma-spliced condition.
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00523F70
        undefined4 TribesState::updateTribeRallyFlags(int tribeID)
        {
            int unitSelectionIndex = 0;
            BOOLEnum _anyRallying = FALSE;
            short* const _size = &this->tribes[tribeID].size;
            if (0 < *_size) {
                do {
                    int const _unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        tribeID, unitSelectionIndex);
                    unitSelectionIndex = unitSelectionIndex + 1;
                    if (DAT_UnitsState::instance.units[_unitID].logicalState == Map::Units::ULS_NORMAL
                        && DAT_UnitsState::instance.units[_unitID].dying == 0) {
                        short const _isRallying = DAT_UnitsState::instance.units[_unitID].goToRallyPoint;
                        DAT_UnitsState::instance.units[_unitID].rallyRelatedFlag = 0;
                        if (_isRallying != 0
                            || DAT_UnitsState::instance.units[_unitID].isSelectable_OR_matchTime == 0) {
                            _anyRallying = TRUE;
                            DAT_UnitsState::instance.units[_unitID].rallyRelatedFlag = 1;
                        }
                    }
                } while (unitSelectionIndex < *_size);
            }
            return _anyRallying;
        }

    }
}
}
