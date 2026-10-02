#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElementRenderFunc.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/DebugNumbersDisplayElement.hpp"

namespace OpenSHC {
namespace Global {

    using OpenSHC::DE::SHCDE::eOnScreenText;
    using OpenSHC::UI::Enums::DisplayElementPositionModifier;

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059C4C0
    void Init::CreateDebugNumbersDisplayElement()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::DisplayElement_Func::Constructor_DisplayElement,
            DebugNumbersDisplayElement::ptr)(OpenSHC::DE::SHCDE::OST_FRAMERATE, 0x2da, 9, 0,
            (OpenSHC::UI::DisplayElementRenderFunc*)MACRO_CALL(
                OpenSHC::UI::DisplayElements_Func::RenderDebugNumbersDisplayElement),
            (OpenSHC::UI::Enums::DisplayElementPositionModifier)(OpenSHC::UI::Enums::DEPM_TOWARDS_MID_X
                | OpenSHC::UI::Enums::DEPM_RESOLUTION_Y));
        return;
    }

}
}
