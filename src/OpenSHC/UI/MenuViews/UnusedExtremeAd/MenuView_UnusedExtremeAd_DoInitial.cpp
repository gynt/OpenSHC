#include "../UnusedExtremeAd.func.hpp"

#include "OpenSHC/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x004E1A50
        void UnusedExtremeAd::MenuView_UnusedExtremeAd_DoInitial()
        {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(0,
                0, DAT_WindowAndDirectDraw::instance.resolutionX, DAT_WindowAndDirectDraw::instance.resolutionY,
                (ushort)(COL_BLACK::instance.shortValue));
            int menuY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            int menuX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            Menu* pMVar1 = DAT_MenuHandlerState::instance.currentMenu;
            pMVar1->xPosition = menuX;
            pMVar1->yPosition = menuY;
            DAT_MenuHandlerState::instance.x = menuX;
            DAT_MenuHandlerState::instance.y = menuY;
            MACRO_CALL(OpenSHC::Rendering_Func::RenderActiveCreditsElements)();
        }

    }
}
}
