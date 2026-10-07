#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElementRenderFunc.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/BottomLeftDateDisplayElement.hpp"

namespace OpenSHC {
namespace Global {

    using DE::SHCDE::eOnScreenText;
    using UI::Enums::DisplayElementPositionModifier;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C3E0
    void Init::CreateBottomLeftDateDisplayElement()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement, BottomLeftDateDisplayElement::ptr)(
            DE::SHCDE::OST_DATE, 4, 0x1a8, 0, MACRO_CALL(UI::DisplayElements_Func::RenderBottomLeftDateDisplayElement),
            (UI::Enums::DisplayElementPositionModifier)(UI::Enums::DEPM_RESOLUTION_X | UI::Enums::DEPM_TOWARDS_MID_Y));
        return;
    }

}
}
