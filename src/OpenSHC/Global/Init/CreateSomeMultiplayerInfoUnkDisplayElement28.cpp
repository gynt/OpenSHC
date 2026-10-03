#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElementRenderFunc.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/SomeMultiplayerInfoUnkDisplayElement28.hpp"

namespace OpenSHC {
namespace Global {

    using OpenSHC::DE::SHCDE::eOnScreenText;
    using OpenSHC::UI::Enums::DisplayElementPositionModifier;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C6C0
    void Init::CreateSomeMultiplayerInfoUnkDisplayElement28()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::DisplayElement_Func::Constructor_DisplayElement,
            SomeMultiplayerInfoUnkDisplayElement28::ptr)(OpenSHC::DE::SHCDE::OST_PING_ERROR, 400, 10, 0,
            (OpenSHC::UI::DisplayElementRenderFunc*)MACRO_CALL(
                OpenSHC::UI::DisplayElements_Func::RenderSomeMultiplayerInfoUnkDisplayElement28),
            OpenSHC::UI::Enums::DEPM_RESOLUTION_Y);
        return;
    }

}
}
