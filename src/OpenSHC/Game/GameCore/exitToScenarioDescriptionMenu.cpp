#include "../GameCore.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x00471A80
    void GameCore::exitToScenarioDescriptionMenu()
    {
        MACRO_CALL_MEMBER(GameCore_Func::removeLadyAndJester, this)();
        DAT_GameCore::instance.briefingOpenedFromInGame = 0;
        MACRO_CALL_MEMBER(GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(UI::Enums::MVT_SCENARIO_DESCRIPTION, 0);
    }

}
}
