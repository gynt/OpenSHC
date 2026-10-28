#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051C470
        void TroopValueState::queueOilThrowForIdleEngineers()
        {
            for (int unitID = 1; unitID < (int)DAT_UnitsState::instance.maxUnitCount; ++unitID) {
                if (DAT_UnitsState::instance.units[unitID].logicalState != ULS_INVISIBLE
                    && MACRO_CALL_MEMBER(TroopValueState_Func::getPlayerNot1AndHasKeep, this)(
                           DAT_UnitsState::instance.units[unitID].owner)
                        != FALSE
                    && DAT_UnitsState::instance.units[unitID].unitType == UT_E_ENGINEER
                    && DAT_UnitsState::instance.units[unitID].dying == 0
                    && DAT_UnitsState::instance.units[unitID].state.generic == States::US_SIT_DOWNUnk) {
                    int range = 3;
                    if (DAT_UnitsState::instance.units[unitID].terrainOrClimbHeight > 110) {
                        range = 5;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::computeTotalUnitsWithinDistance,
                        DAT_PathFindingState::ptr)(DAT_TroopValueState::instance.attackInfo.pitchRelatedPlayerID, 0, 0,
                        DAT_UnitsState::instance.units[unitID].tile, range);
                    if (DAT_PathFindingState::instance.ALGO_TotalTroopValue >= 10
                        && DAT_PathFindingState::instance.ALGO_TotalTroopCount >= 2
                        && DAT_PathFindingState::instance.firstMatchingUnitID != 0) {
                        int const enemyUnitID = DAT_PathFindingState::instance.firstMatchingUnitID;
                        DAT_UnitsState::instance.units[unitID].targetingType_OR_performanceStep = UIT_THROW_OIL;
                        DAT_UnitsState::instance.units[unitID].attackAtTileX
                            = DAT_UnitsState::instance.units[enemyUnitID].x;
                        DAT_UnitsState::instance.units[unitID].attackAtTileY
                            = DAT_UnitsState::instance.units[enemyUnitID].y;
                        DAT_UnitsState::instance.units[unitID].animationFrame = 4;
                    }
                }
            }
        }

    }
}
}
