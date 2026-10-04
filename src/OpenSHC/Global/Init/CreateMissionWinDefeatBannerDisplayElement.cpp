#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElementRenderFunc.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/MissionWinDefeatBannerDisplayElement.hpp"

namespace OpenSHC {
namespace Global {

    using DE::SHCDE::eOnScreenText;
    using UI::Enums::DisplayElementPositionModifier;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C560
    void Init::CreateMissionWinDefeatBannerDisplayElement()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement,
            MissionWinDefeatBannerDisplayElement::ptr)(DE::SHCDE::OST_MISSION_FINISHED, 400, 0x1e, 0,
            MACRO_CALL(UI::DisplayElements_Func::RenderMissionWinDefeatBannerDisplayElement),
            UI::Enums::DEPM_RESOLUTION_Y);
        return;
    }

}
}
