#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElementRenderFunc.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/UnknownDisplayElement25.hpp"

namespace OpenSHC {
namespace Global {

    using OpenSHC::DE::SHCDE::eOnScreenText;
    using OpenSHC::UI::Enums::DisplayElementPositionModifier;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C640
    void Init::CreateUnknownDisplayElement25()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::DisplayElement_Func::Constructor_DisplayElement, UnknownDisplayElement25::ptr)(
            OpenSHC::DE::SHCDE::OST_KING_OF_THE_HILL, 100, 10, 0,
            (OpenSHC::UI::DisplayElementRenderFunc*)MACRO_CALL(
                OpenSHC::UI::DisplayElements_Func::RenderUnknownDisplayElement25),
            OpenSHC::UI::Enums::DEPM_RESOLUTION_Y);
        return;
    }

}
}
