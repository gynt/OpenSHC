#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElementRenderFunc.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/GameSpeedTextDisplayElement.hpp"

namespace OpenSHC {
namespace Global {

    using DE::SHCDE::eOnScreenText;
    using UI::Enums::DisplayElementPositionModifier;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C620
    void Init::CreateGameSpeedTextDisplayElement()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement,
            GameSpeedTextDisplayElement::ptr)(DE::SHCDE::OST_GAME_SPEED, 0x302, 9, 0,
            (UI::DisplayElementRenderFunc*)MACRO_CALL(
                UI::DisplayElements_Func::RenderGameSpeedTextDisplayElement),
            UI::Enums::DEPM_MAIN_MENU_X_Y);
        return;
    }

}
}
