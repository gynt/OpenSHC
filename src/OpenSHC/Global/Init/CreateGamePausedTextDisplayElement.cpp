#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElementRenderFunc.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/GamePausedTextDisplayElement.hpp"

namespace OpenSHC {
namespace Global {

    using DE::SHCDE::eOnScreenText;
    using UI::Enums::DisplayElementPositionModifier;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C600
    void Init::CreateGamePausedTextDisplayElement()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement, GamePausedTextDisplayElement::ptr)(
            DE::SHCDE::OST_GAME_PAUSED, 400, 0xe6, 0,
            MACRO_CALL(UI::DisplayElements_Func::RenderGamePausedTextDisplayElement), UI::Enums::DEPM_MAIN_MENU_X_Y);
        return;
    }

}
}
