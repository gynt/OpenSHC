#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElementRenderFunc.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/UnknownDisplayElement7.hpp"

namespace OpenSHC {
namespace Global {

    using DE::SHCDE::eOnScreenText;
    using UI::Enums::DisplayElementPositionModifier;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C4E0
    void Init::CreateUnknownDisplayElement7()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement, UnknownDisplayElement7::ptr)(
            (DE::SHCDE::eOnScreenText)(DE::SHCDE::OST_FRAMERATE | DE::SHCDE::OST_DATE), 700, 9, 0,
            MACRO_CALL(UI::DisplayElements_Func::RenderUnknownDisplayElement7),
            (UI::Enums::DisplayElementPositionModifier)(UI::Enums::DEPM_TOWARDS_MID_X | UI::Enums::DEPM_RESOLUTION_Y));
        return;
    }

}
}
