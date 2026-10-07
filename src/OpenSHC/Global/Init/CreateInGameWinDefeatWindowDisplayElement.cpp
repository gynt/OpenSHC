#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElementRenderFunc.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/InGameWinDefeatWindowDisplayElement.hpp"

namespace OpenSHC {
namespace Global {

    using DE::SHCDE::eOnScreenText;
    using UI::Enums::DisplayElementPositionModifier;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C540
    void Init::CreateInGameWinDefeatWindowDisplayElement()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement,
            InGameWinDefeatWindowDisplayElement::ptr)(DE::SHCDE::OST_MP_GAME_OVER, 400, 0xf0, 0,
            MACRO_CALL(UI::DisplayElements_Func::RenderInGameWinDefeatWindowDisplayElement),
            UI::Enums::DEPM_MAIN_MENU_X_Y);
        return;
    }

}
}
