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
            Menu* pMVar1;
            DAT_MenuHandlerState::instance.y = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            DAT_MenuHandlerState::instance.x = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            pMVar1 = DAT_MenuHandlerState::instance.currentMenu;
            (DAT_MenuHandlerState::instance.currentMenu)->xPosition
                = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            pMVar1->yPosition = DAT_MenuHandlerState::instance.y;
            MACRO_CALL(UI::Helpers_Func::ColorEntireScreen)(COL_BLACK::instance.shortValue);
            MACRO_CALL(Rendering_Func::RenderActiveCreditsElements)();
        }

    }
}
}
