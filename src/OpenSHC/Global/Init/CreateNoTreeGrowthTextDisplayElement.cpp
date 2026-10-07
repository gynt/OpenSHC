#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElementRenderFunc.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/NoTreeGrowthTextDisplayElement.hpp"

namespace OpenSHC {
namespace Global {

    using DE::SHCDE::eOnScreenText;
    using UI::Enums::DisplayElementPositionModifier;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C520
    void Init::CreateNoTreeGrowthTextDisplayElement()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement, NoTreeGrowthTextDisplayElement::ptr)(
            (DE::SHCDE::eOnScreenText)0xe, 200, 0x22, 0,
            MACRO_CALL(UI::DisplayElements_Func::RenderNoTreeGrowthTextDisplayElement), UI::Enums::DEPM_RESOLUTION_Y);
        return;
    }

}
}
