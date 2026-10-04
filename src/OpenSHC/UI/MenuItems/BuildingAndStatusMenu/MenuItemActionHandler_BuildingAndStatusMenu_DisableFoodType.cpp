#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using Game::GameMode;
        using Game::GameMode2;

        // FUNCTION: STRONGHOLDCRUSADER 0x0043FBB0
        void BuildingAndStatusMenu::MenuItemActionHandler_BuildingAndStatusMenu_DisableFoodType(int param_1, ...)
        {
            short* psVar1;
            if ((DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY)
                || (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER)) {
                if (DAT_GameCore::instance.gameMode_2 == Game::GM_CRUSADER_TUTORIAL) {
                    MACRO_CALL(UI::Helpers_Func::SetTutorialHintActiveWithTimestamp)();
                }
                psVar1 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                             .isFoodTypeBanned
                    + param_1;
                *psVar1 = *psVar1 ^ 1;
            }
        }

    }
}
}
