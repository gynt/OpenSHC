#include "../Unknown61ReturnToSkrimishMenuUnk.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x004272C0
        void Unknown61ReturnToSkrimishMenuUnk::MenuView_Unknown61ReturnToSkrimishMenuUnk_DoEveryFrame()
        {
            int menuY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            int menuX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            Menu* _menuPtr = DAT_MenuHandlerState::instance.currentMenu;
            _menuPtr->yPosition = menuY;
            _menuPtr->xPosition = menuX;
            DAT_MenuHandlerState::instance.y = menuY;
            DAT_MenuHandlerState::instance.x = menuX;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                DAT_TextureRenderCoreObject::ptr)(0,
                (DAT_WindowAndDirectDraw::instance.resolutionX
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].width)
                    / 2,
                (DAT_WindowAndDirectDraw::instance.resolutionY
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height)
                    / 2);
            return;
        }

    }
}
}
