#include "../Unknown26.func.hpp"

#include "OpenSHC/Rendering.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x004E1E30
        void Unknown26::MenuView_Unknown26_CampaignRelatedUnk_DoInitial()
        {
            int menuY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            int menuX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            Menu* pMVar1 = DAT_MenuHandlerState::instance.currentMenu;
            pMVar1->xPosition = menuX;
            pMVar1->yPosition = menuY;
            DAT_MenuHandlerState::instance.y = menuY;
            DAT_MenuHandlerState::instance.x = menuX;
            MACRO_CALL(OpenSHC::UI::Helpers_Func::ColorEntireScreen)(COL_BLACK::instance.shortValue);
            MACRO_CALL(OpenSHC::Rendering_Func::RenderActiveCreditsElements)();
        }

    }
}
}
