#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElementRenderFunc.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/NoRushDisplayElementUnk.hpp"

namespace OpenSHC {
namespace Global {

    using DE::SHCDE::eOnScreenText;
    using UI::Enums::DisplayElementPositionModifier;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C680
    void Init::CreateNoRushDisplayElementUnk()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement, NoRushDisplayElementUnk::ptr)(
            DE::SHCDE::OST_MESSAGE_BAR, 0, 8, 0,
            (UI::DisplayElementRenderFunc*)MACRO_CALL(
                UI::DisplayElements_Func::RenderNoRushDisplayElementUnk),
            UI::Enums::DEPM_RESOLUTION_Y);
        return;
    }

}
}
