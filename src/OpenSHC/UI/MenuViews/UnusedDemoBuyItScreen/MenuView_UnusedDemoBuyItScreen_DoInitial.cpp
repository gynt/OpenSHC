#include "../UnusedDemoBuyItScreen.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00b960e0.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::Rendering::ScreenResolutionEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00426600
        void UnusedDemoBuyItScreen::MenuView_UnusedDemoBuyItScreen_DoInitial()
        {
            Menu* pMVar1;
            int iVar2;
            bool bVar3;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(0,
                0, DAT_WindowAndDirectDraw::instance.resolutionX, DAT_WindowAndDirectDraw::instance.resolutionY,
                (ushort)((int)(COL_BLACK::instance.shortValue)));
            iVar2 = 0;
            INT_00b960e0::instance = 0;
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
                iVar2 = 0x18;
                INT_00b960e0::instance = 0x18;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                DAT_TextureRenderCoreObject::ptr)(0,
                (DAT_WindowAndDirectDraw::instance.resolutionX
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].width)
                        / 2
                    + iVar2,
                (DAT_WindowAndDirectDraw::instance.resolutionY
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height)
                    / 2);
            int borderWidth = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            int borderHeight = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            pMVar1 = DAT_MenuHandlerState::instance.currentMenu;
            pMVar1->yPosition = borderHeight;
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
                borderWidth = borderWidth + 0x18;
            }
            pMVar1->xPosition = borderWidth;
            DAT_MenuHandlerState::instance.y = borderHeight;
            DAT_MenuHandlerState::instance.x = borderWidth;
            return;
        }

    }
}
}
