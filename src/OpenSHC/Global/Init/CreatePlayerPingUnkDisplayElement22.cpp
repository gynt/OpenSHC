#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElementRenderFunc.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/PlayerPingUnkDisplayElement22.hpp"

namespace OpenSHC {
namespace Global {

    using DE::SHCDE::eOnScreenText;
    using UI::Enums::DisplayElementPositionModifier;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C5E0
    void Init::CreatePlayerPingUnkDisplayElement22()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement,
            PlayerPingUnkDisplayElement22::ptr)(DE::SHCDE::OST_PINGS, 0x294, 0x28, 0,
            (UI::DisplayElementRenderFunc*)MACRO_CALL(
                UI::DisplayElements_Func::RenderPlayerPingUnkDisplayElement22),
            UI::Enums::DEPM_TOWARDS_MID_X);
        return;
    }

}
}
