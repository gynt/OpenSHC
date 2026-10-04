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

    using DE::SHCDE::eOnScreenText;
    using UI::Enums::DisplayElementPositionModifier;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C460
    void Init::CreateInGameChatDisplayElementUnk()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement, InGameChatDisplayElement::ptr)(
            DE::SHCDE::OST_MULTI_CHAT, 4, (int)((int)(367)), 1,
            (UI::DisplayElementRenderFunc*)MACRO_CALL(
                UI::DisplayElements_Func::RenderInGameChatDisplayElement),
            (UI::Enums::DisplayElementPositionModifier)(UI::Enums::DEPM_RESOLUTION_X
                | UI::Enums::DEPM_TOWARDS_MID_Y));
        return;
    }

}
}
