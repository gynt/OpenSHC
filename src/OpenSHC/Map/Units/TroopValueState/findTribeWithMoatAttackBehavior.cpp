#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A920
        undefined4 TroopValueState::findTribeWithMoatAttackBehavior()
        {
            for (int i = 1; i < 1250; ++i) {
                if (DAT_TribesState::instance.tribes[i].tribeState != 0
                    && MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::isPlayerSlotNotHuman,
                           DAT_GameState::ptr)(DAT_TribesState::instance.tribes[i].owner)
                        != FALSE
                    && DAT_TribesState::instance.tribes[i].tribeBehaviorType == STBT_0x3f7) {
                    this->x = DAT_TribesState::instance.tribes[i].targetX;
                    this->y = DAT_TribesState::instance.tribes[i].targetY;
                    DAT_TroopValueState::instance.attackInfo.moatAttackTribeId = i;
                    return 1;
                }
            }
            return 0;
        }

    }
}
}
