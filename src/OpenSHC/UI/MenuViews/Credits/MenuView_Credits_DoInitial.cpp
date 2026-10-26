#include "../Credits.func.hpp"

#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextEditorState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004262B0
        void Credits::MenuView_Credits_DoInitial()
        {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(0,
                0, DAT_WindowAndDirectDraw::instance.resolutionX, DAT_WindowAndDirectDraw::instance.resolutionY,
                (ushort)(COL_BLACK::instance.shortValue));
            MACRO_CALL(OpenSHC::UI::Rendering_Func::DrawOuterMenuBorder)();
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                DAT_TextureRenderCoreObject::ptr)(0,
                (DAT_WindowAndDirectDraw::instance.resolutionX
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].width)
                    / 2,
                (DAT_WindowAndDirectDraw::instance.resolutionY
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height)
                    / 2);
            int menuY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            int menuX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            Menu* pMVar1 = DAT_MenuHandlerState::instance.currentMenu;
            pMVar1->xPosition = menuX;
            pMVar1->yPosition = menuY;
            DAT_MenuHandlerState::instance.x = menuX;
            DAT_MenuHandlerState::instance.y = menuY;
            DAT_TextEditorState::instance.pendingCreditsFadeBorder = TRUE;
            return;
        }

    }
}
}
