#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElementRenderFunc.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/UnknownDisplayElement18.hpp"

namespace OpenSHC {
namespace Global {

    using OpenSHC::DE::SHCDE::eOnScreenText;
    using OpenSHC::UI::Enums::DisplayElementPositionModifier;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C400
    void Init::CreateUnknownDisplayElement18()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::DisplayElement_Func::Constructor_DisplayElement, UnknownDisplayElement18::ptr)(
            ((eOnScreenText)0x12), 200, 4, 1,
            (OpenSHC::UI::DisplayElementRenderFunc*)MACRO_CALL(OpenSHC::Global_Func::DoNothing),
            (OpenSHC::UI::Enums::DisplayElementPositionModifier)(OpenSHC::UI::Enums::DEPM_RESOLUTION_X
                | OpenSHC::UI::Enums::DEPM_RESOLUTION_Y));
        return;
    }

}
}
