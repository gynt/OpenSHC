#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElementRenderFunc.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/ConnectAndPathLinkageInfoTextDisplayElement.hpp"

namespace OpenSHC {
namespace Global {

    using DE::SHCDE::eOnScreenText;
    using UI::Enums::DisplayElementPositionModifier;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C440
    void Init::CreateConnectAndPathLinkageInfoTextDisplayElement()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement,
            ConnectAndPathLinkageInfoTextDisplayElement::ptr)(((eOnScreenText)2), (int)((int)(630)), 9, 0,
            MACRO_CALL(UI::DisplayElements_Func::RenderConnectAndPathLinkageInfoTextDisplayElement),
            (UI::Enums::DisplayElementPositionModifier)(UI::Enums::DEPM_TOWARDS_MID_X | UI::Enums::DEPM_RESOLUTION_Y));
        return;
    }

}
}
