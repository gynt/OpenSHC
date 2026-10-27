#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::SomeTribeBehaviorType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00518A10
        void TroopValueState::assignBehaviorTypeAndLinkSupportTribe(
            int param_1, int param_2, SomeTribeBehaviorType param_3, undefined4 param_4, undefined4 param_5)
        {
            // param_1 = attackID, param_2 = playerID, param_3 = behaviour type,
            // param_4 = delay base, param_5 = delay step
            if (param_2 <= 0) {
                param_2 = 2;
            }
            for (int tribeID = 1; tribeID < 1250; ++tribeID) {
                if (DAT_TribesState::instance.tribes[tribeID].owner == param_2) {
                    DAT_TribesState::instance.tribes[tribeID].linkedByTribeID = 0;
                }
            }

            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.tribeIDArraySize; ++i) {
                int const attackTribeID = DAT_TroopValueState::instance.attackInfo.tribeIDArray[i];
                if (DAT_TroopValueState::instance.attackInfo.tribeTypePriorityRank[i] >= 11) {
                    return;
                }
                int supportTribeID = DAT_TribesState::instance.tribes[attackTribeID].linkedTribeID;
                if (supportTribeID != 0
                    && DAT_TribesState::instance.tribes[attackTribeID].linkedTribeUID
                        == DAT_TribesState::instance.tribes[supportTribeID].uid) {
                    return;
                }
                DAT_TribesState::instance.tribes[attackTribeID].behaviorDelayTicks = (i + 1) * param_5 + param_4;
                DAT_TribesState::instance.tribes[attackTribeID].tribeBehaviorType
                    = (SomeTribeBehaviorTypeShort)param_3;
                DAT_TribesState::instance.tribes[attackTribeID].attackInfo_someCounter1
                    = DAT_TroopValueState::instance.attackInfo.someCounter1;
                DAT_TribesState::instance.tribes[attackTribeID].behaviorTickCounter = 0;

                // stone throwing siege engines first
                for (supportTribeID = 1; supportTribeID < 1250; ++supportTribeID) {
                    if (DAT_TribesState::instance.tribes[supportTribeID].tribeState != 0
                        && DAT_TribesState::instance.tribes[supportTribeID].tribeState != 3
                        && DAT_TribesState::instance.tribes[supportTribeID].owner
                            == DAT_TribesState::instance.tribes[attackTribeID].owner
                        && DAT_TribesState::instance.tribes[supportTribeID].linkedByTribeID == 0
                        && (DAT_TribesState::instance.tribes[supportTribeID].tribeType == AI::Tribes::AITT_CATAPULTS
                            || DAT_TribesState::instance.tribes[supportTribeID].tribeType
                                == AI::Tribes::AITT_TREBUCHETS)) {
                        goto linkSupportTribe;
                    }
                }
                // otherwise ranged units
                for (supportTribeID = 1; supportTribeID < 1250; ++supportTribeID) {
                    if (DAT_TroopValueState::instance.attackInfo.attackWaveState[param_1] == 4) {
                        break;
                    }
                    if (DAT_TribesState::instance.tribes[supportTribeID].tribeState != 0
                        && DAT_TribesState::instance.tribes[supportTribeID].tribeState != 3
                        && DAT_TribesState::instance.tribes[supportTribeID].owner
                            == DAT_TribesState::instance.tribes[attackTribeID].owner
                        && DAT_TribesState::instance.tribes[supportTribeID].linkedByTribeID == 0
                        && (DAT_TribesState::instance.tribes[supportTribeID].tribeType == AI::Tribes::AITT_ARCHERS
                            || DAT_TribesState::instance.tribes[supportTribeID].tribeType
                                == AI::Tribes::AITT_CROSSBOWMEN)) {
                        goto linkSupportTribe;
                    }
                }
                continue;

            linkSupportTribe:
                DAT_TribesState::instance.tribes[attackTribeID].linkedTribeID = supportTribeID;
                DAT_TribesState::instance.tribes[attackTribeID].linkedTribeUID
                    = DAT_TribesState::instance.tribes[supportTribeID].uid;
                DAT_TribesState::instance.tribes[supportTribeID].linkedByTribeID = attackTribeID;
            }
        }

    }
}
}
