#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00518BB0
        BOOLEnum TroopValueState::isLessThanPercentageOfTribesInAttackDying(int attackID, int leDyingPerc)
        {
            int healthyTribeCount = 0;
            int dyingTribeCount = 0;
            for (int tribeID = 1; tribeID < 1250; ++tribeID) {
                if (DAT_TribesState::instance.tribes[tribeID].tribeState == 0
                    || DAT_TribesState::instance.tribes[tribeID].tribeState == 3) {
                    continue;
                }
                if (DAT_GameSynchronyState::instance
                        .currentPlayerFullIDArray[DAT_TribesState::instance.tribes[tribeID].owner]
                    != -1) {
                    continue;
                }
                if (DAT_TribesState::instance.tribes[tribeID].attackWave != attackID) {
                    continue;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getTribeAliveStatus,
                        DAT_TribesState::ptr)(tribeID)
                    < 50) {
                    dyingTribeCount++;
                } else {
                    healthyTribeCount++;
                }
            }
            int const total = healthyTribeCount + dyingTribeCount;
            int percentage;
            if (total == 0) {
                percentage = 100;
            } else {
                percentage = healthyTribeCount * 100 / total;
            }
            if (percentage >= leDyingPerc) {
                return TRUE;
            }
            return FALSE;
        }

    }
}
}
