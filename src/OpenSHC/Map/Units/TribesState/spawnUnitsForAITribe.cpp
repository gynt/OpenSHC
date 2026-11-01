#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00522F70
        void TribesState::spawnUnitsForAITribe(undefined4 param_1, int tileX, int tileY, int spawnOwnerUnk,
            UnitType unitType, int unitCount, int ownerPlayerIndex)
        {
            int unitID;
            if ((0 < tileX || 0 < tileY) && 0 < unitCount) {
                /*
                  The Y scaling is computed first: the original has `lea ebx, [edx*8]` for
                  tileY and `lea ebp, [ecx*8]` for tileX, which is the opposite register
                  pairing from declaring X first.
                 */
                int microYPosition = tileY * 8;
                int microXPosition = tileX * 8;
                int _remainingUnits = unitCount;
                do {
                    unitID = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                        spawnOwnerUnk, spawnOwnerUnk, microXPosition, microYPosition, 8, unitType);
                    if (unitID) {
                        DAT_UnitsState::instance.units[unitID].calculatedOwnerPlayerIndex = ownerPlayerIndex;
                        UnitTypeShort _spawnedUnitType = DAT_UnitsState::instance.units[unitID].unitType;
                        /*
                          The call is written out in both arms. The original pushes the
                          behaviour constant straight from each one - `push 20`,
                          `jmp 0x2`, `push 17` - and shares the `push eax` and the call
                          after them, which is what MSVC produces when it tail-merges two
                          call sites. Assigning a local and calling once makes it
                          materialise the value instead (`mov ecx, 20` / `mov ecx, 17`
                          and a `push ecx`), five bytes more, and that is what every
                          branch displacement in this function was out by. Declaring the
                          local at its use rather than at function scope does not change
                          it; the two call sites do.
                         */
                        if (_spawnedUnitType == Map::Units::UT_E_ARCHER || _spawnedUnitType == Map::Units::UT_E_XBOW
                            || _spawnedUnitType == Map::Units::UT_A_ARCHER
                            || _spawnedUnitType == Map::Units::UT_A_SLINGER
                            || _spawnedUnitType == Map::Units::UT_A_HARCHER
                            || _spawnedUnitType == Map::Units::UT_A_FIRETHROWER) {
                            MACRO_CALL_MEMBER(AI::AICState_Func::addUnitToItsTribe, DAT_AICState::ptr)(unitID, 17);
                        } else {
                            MACRO_CALL_MEMBER(AI::AICState_Func::addUnitToItsTribe, DAT_AICState::ptr)(unitID, 20);
                        }
                    }
                    --_remainingUnits;
                } while (_remainingUnits);
            }
        }

    }
}
}
