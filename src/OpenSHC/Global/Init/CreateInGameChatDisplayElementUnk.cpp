#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElementRenderFunc.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/InGameChatDisplayElement.hpp"

namespace OpenSHC {
namespace Global {

    using OpenSHC::DE::SHCDE::eOnScreenText;
    using OpenSHC::UI::Enums::DisplayElementPositionModifier;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C460
    void Init::CreateInGameChatDisplayElementUnk()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::DisplayElement_Func::Constructor_DisplayElement, InGameChatDisplayElement::ptr)(
            OpenSHC::DE::SHCDE::OST_MULTI_CHAT, 4, (int)((int)(367)), 1,
            (OpenSHC::UI::DisplayElementRenderFunc*)MACRO_CALL(
                OpenSHC::UI::DisplayElements_Func::RenderInGameChatDisplayElement),
            (OpenSHC::UI::Enums::DisplayElementPositionModifier)(OpenSHC::UI::Enums::DEPM_RESOLUTION_X
                | OpenSHC::UI::Enums::DEPM_TOWARDS_MID_Y));
        return;
    }

}
}
