#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051D510
        void TroopValueState::moveTowardsParticularUnits(int tribeID)
        {
            int const leaderUnitID = DAT_TribesState::instance.tribes[tribeID].leaderUnitID;
            int targetUnitID = MACRO_CALL_MEMBER(
                Map::Navigation::PathFindingState_Func::findHighestPriorityEnemyUnitInRange, DAT_PathFindingState::ptr)(
                DAT_TribesState::instance.tribes[tribeID].owner, DAT_UnitsState::instance.units[leaderUnitID].x,
                DAT_UnitsState::instance.units[leaderUnitID].y, 80);
            if (targetUnitID == 0) {
                targetUnitID = MACRO_CALL_MEMBER(
                    Map::Navigation::PathFindingState_Func::findHighestPriorityEnemyUnitInRange,
                    DAT_PathFindingState::ptr)(DAT_TribesState::instance.tribes[tribeID].owner,
                    DAT_UnitsState::instance.units[leaderUnitID].x, DAT_UnitsState::instance.units[leaderUnitID].y,
                    200);
                if (targetUnitID == 0) {
                    return;
                }
            }
            MACRO_CALL_MEMBER(TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(
                tribeID, UIT_NO_INSTRUCTION_OR_MOVE, 0, 0, 0);
            MACRO_CALL_MEMBER(TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(tribeID,
                DAT_UnitsState::instance.units[targetUnitID].x, DAT_UnitsState::instance.units[targetUnitID].y, 0, 0,
                Instructions::UMSE_0);
        }

    }
}
}
