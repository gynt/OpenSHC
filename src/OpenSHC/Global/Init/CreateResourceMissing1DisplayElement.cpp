#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElementRenderFunc.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/ResourceMissing1DisplayElement.hpp"

namespace OpenSHC {
namespace Global {

    using DE::SHCDE::eOnScreenText;
    using UI::Enums::DisplayElementPositionModifier;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C480
    void Init::CreateResourceMissing1DisplayElement()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement, ResourceMissing1DisplayElement::ptr)(
            DE::SHCDE::OST_FEEDBACK_1, 10, 0x193, 0,
            MACRO_CALL(UI::DisplayElements_Func::RenderResourceMissing1DisplayElement),
            (UI::Enums::DisplayElementPositionModifier)(UI::Enums::DEPM_RESOLUTION_X | UI::Enums::DEPM_TOWARDS_MID_Y));
        return;
    }

}
}
