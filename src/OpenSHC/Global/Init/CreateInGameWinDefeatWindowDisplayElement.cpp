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

    using OpenSHC::DE::SHCDE::eOnScreenText;
    using OpenSHC::UI::Enums::DisplayElementPositionModifier;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C540
    void Init::CreateInGameWinDefeatWindowDisplayElement()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::DisplayElement_Func::Constructor_DisplayElement,
            InGameWinDefeatWindowDisplayElement::ptr)(OpenSHC::DE::SHCDE::OST_MP_GAME_OVER, 400, 0xf0, 0,
            (OpenSHC::UI::DisplayElementRenderFunc*)MACRO_CALL(
                OpenSHC::UI::DisplayElements_Func::RenderInGameWinDefeatWindowDisplayElement),
            OpenSHC::UI::Enums::DEPM_MAIN_MENU_X_Y);
        return;
    }

}
}
