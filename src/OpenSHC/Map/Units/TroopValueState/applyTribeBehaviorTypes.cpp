#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::SomeTribeBehaviorType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00518870
        void TroopValueState::applyTribeBehaviorTypes(
            SomeTribeBehaviorType tribeBehaviorType, SomeTribeBehaviorType tribeBehaviorType2, int off1, int off2)
        {
            int assignedCount = 0;
            DAT_TroopValueState::instance.attackInfo.assignedTribeCount = assignedCount;
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.tribeIDArraySize; ++i) {
                int const tribeID = DAT_TroopValueState::instance.attackInfo.tribeIDArray[i];
                if (DAT_TroopValueState::instance.attackInfo.tribeTypePriorityRank[i] >= 11) {
                    if (tribeBehaviorType2 != STBT_NONE) {
                        DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType
                            = (SomeTribeBehaviorTypeShort)tribeBehaviorType2;
                    }
                } else {
                    DAT_TribesState::instance.tribes[tribeID].behaviorDelayTicks = (i + 1) * off2 + off1;
                    DAT_TribesState::instance.tribes[tribeID].waveAssignmentSlot = assignedCount++;
                    DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType
                        = (SomeTribeBehaviorTypeShort)tribeBehaviorType;
                    DAT_TribesState::instance.tribes[tribeID].attackInfo_someCounter1
                        = DAT_TroopValueState::instance.attackInfo.someCounter1;
                    DAT_TroopValueState::instance.attackInfo.assignedTribeCount = assignedCount;
                }
                DAT_TribesState::instance.tribes[tribeID].behaviorTickCounter = 0;
            }
        }

    }
}
}
