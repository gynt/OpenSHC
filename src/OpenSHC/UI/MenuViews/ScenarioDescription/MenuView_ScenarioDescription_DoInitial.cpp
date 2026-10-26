#include "../ScenarioDescription.func.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x004DD300
        void ScenarioDescription::MenuView_ScenarioDescription_DoInitial()
        {
            int menuY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            int menuX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            Menu* pMVar1 = DAT_MenuHandlerState::instance.currentMenu;
            pMVar1->xPosition = menuX;
            pMVar1->yPosition = menuY;
            DAT_MenuHandlerState::instance.y = menuY;
            DAT_MenuHandlerState::instance.x = menuX;
            MACRO_CALL(OpenSHC::UI::Helpers_Func::ColorEntireScreen)(COL_BLACK::instance.shortValue);
            MACRO_CALL(OpenSHC::UI::Rendering_Func::DrawOuterMenuBorder)();
            MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderGfxHelperUnk)(0, 0, 0);
        }

    }
}
}
