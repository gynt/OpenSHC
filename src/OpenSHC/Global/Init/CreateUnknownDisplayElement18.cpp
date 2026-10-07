#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElementRenderFunc.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/UnknownDisplayElement18.hpp"

namespace OpenSHC {
namespace Global {

    using DE::SHCDE::eOnScreenText;
    using UI::Enums::DisplayElementPositionModifier;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C400
    void Init::CreateUnknownDisplayElement18()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement, UnknownDisplayElement18::ptr)(
            ((eOnScreenText)0x12), 200, 4, 1,
            (UI::DisplayElementRenderFunc*)MACRO_CALL(Global_Func::DoNothing),
            (UI::Enums::DisplayElementPositionModifier)(UI::Enums::DEPM_RESOLUTION_X
                | UI::Enums::DEPM_RESOLUTION_Y));
        return;
    }

}
}
