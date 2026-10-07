#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElementRenderFunc.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/SomeMissionNumberUnkDisplayElement9.hpp"

namespace OpenSHC {
namespace Global {

    using DE::SHCDE::eOnScreenText;
    using UI::Enums::DisplayElementPositionModifier;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C500
    void Init::CreateSomeMissionNumberUnkDisplayElement9()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement,
            SomeMissionNumberUnkDisplayElement9::ptr)(((eOnScreenText)9), 0x122, 0xe1, 0,
            MACRO_CALL(UI::DisplayElements_Func::RenderSomeMissionNumberUnkDisplayElement9),
            UI::Enums::DEPM_MAIN_MENU_X_Y);
        return;
    }

}
}
