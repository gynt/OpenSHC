#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::SomeTribeBehaviorType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00518930
        void TroopValueState::assignBehaviorTypeToNearbyTribes(
            SomeTribeBehaviorType param_1, undefined4 param_2, short param_3, short param_4)
        {
            // param_1 = behaviour type, param_2 is unused, param_3 = delay base, param_4 = delay step
            DAT_TroopValueState::instance.attackInfo.assignedTribeCount = 0;
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.tribeIDArraySize; ++i) {
                int const tribeID = DAT_TroopValueState::instance.attackInfo.tribeIDArray[i];
                int const area = (short)DAT_TileMapState::instance.PathConnectionLayer
                                     [DAT_UnitsState::instance.units[DAT_TribesState::instance.tribes[tribeID].leaderUnitID]
                                             .tile];
                if (DAT_TroopValueState::instance.attackInfo.tribeTypePriorityRank[i] < 11
                    && MACRO_CALL_MEMBER(
                           OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                           DAT_PathFindingState::ptr)(DAT_TribesState::instance.tribes[tribeID].owner, area,
                           DAT_TroopValueState::instance.attackInfo.lordConnectionArea, 1)
                        != 0) {
                    DAT_TribesState::instance.tribes[tribeID].attackInfo_someCounter1
                        = DAT_TroopValueState::instance.attackInfo.someCounter1;
                    DAT_TribesState::instance.tribes[tribeID].waveAssignmentSlot
                        = DAT_TroopValueState::instance.attackInfo.assignedTribeCount;
                    DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks = (i + 1) * param_4 + param_3;
                    DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType = (SomeTribeBehaviorTypeShort)param_1;
                    DAT_TroopValueState::instance.attackInfo.assignedTribeCount++;
                    if (DAT_TroopValueState::instance.attackInfo.assignedTribeCount >= 5) {
                        return;
                    }
                }
                DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0;
            }
        }

    }
}
}
