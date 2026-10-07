#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElementRenderFunc.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/TimeUntilDefeatDisplayElement.hpp"

namespace OpenSHC {
namespace Global {

    using DE::SHCDE::eOnScreenText;
    using UI::Enums::DisplayElementPositionModifier;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C6A0
    void Init::CreateTimeUntilDefeatDisplayElement()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement, TimeUntilDefeatDisplayElement::ptr)(
            DE::SHCDE::OST_TIMETODEFEAT, 0, 8, 0,
            MACRO_CALL(UI::DisplayElements_Func::RenderTimeUntilDefeatDisplayElement), UI::Enums::DEPM_RESOLUTION_Y);
        return;
    }

}
}
