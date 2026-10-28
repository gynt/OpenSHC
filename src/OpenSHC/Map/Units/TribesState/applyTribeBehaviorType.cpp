#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::SomeTribeBehaviorType;

        // the original reads DAT_TribesState::instance instead of this
        // FUNCTION: STRONGHOLDCRUSADER 0x005221A0
        void TribesState::applyTribeBehaviorType(int attackWave, SomeTribeBehaviorType tribeBehaviorType)
        {
            int const currentCounter = DAT_TroopValueState::instance.attackInfo.someCounter1;
            for (int i = 1; i < 1250; ++i) {
                if (DAT_TribesState::instance.tribes[i].tribeState != 0
                    && DAT_TribesState::instance.tribes[i].attackWave == attackWave
                    && DAT_TribesState::instance.tribes[i].tribeBehaviorType != tribeBehaviorType
                    && DAT_TribesState::instance.tribes[i].attackInfo_someCounter1 != currentCounter) {
                    DAT_TribesState::instance.tribes[i].tribeBehaviorType
                        = (SomeTribeBehaviorTypeShort)tribeBehaviorType;
                    DAT_TribesState::instance.tribes[i].behaviorTickCounter = 0;
                }
            }
        }

    }
}
}
