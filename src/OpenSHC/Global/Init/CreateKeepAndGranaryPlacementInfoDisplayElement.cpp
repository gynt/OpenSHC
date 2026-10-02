#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElementRenderFunc.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/KeepAndGranaryPlacementInfoDisplayElement.hpp"

namespace OpenSHC {
namespace Global {

    using OpenSHC::DE::SHCDE::eOnScreenText;
    using OpenSHC::UI::Enums::DisplayElementPositionModifier;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C5A0
    void Init::CreateKeepAndGranaryPlacementInfoDisplayElement()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::DisplayElement_Func::Constructor_DisplayElement,
            KeepAndGranaryPlacementInfoDisplayElement::ptr)(OpenSHC::DE::SHCDE::OST_KEEP_MESSAGE, 0x2d5, 0x1bf, 0,
            (OpenSHC::UI::DisplayElementRenderFunc*)MACRO_CALL(
                OpenSHC::UI::DisplayElements_Func::RenderAndPlayKeepAndGranaryPlacementInfoDisplayElement),
            OpenSHC::UI::Enums::DEPM_TOWARDS_MID_Y);
        return;
    }

}
}
