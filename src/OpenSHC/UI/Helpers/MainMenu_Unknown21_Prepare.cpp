#include "../Helpers.func.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Enums::MenuModalType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00427180
    void Helpers::MainMenu_Unknown21_Prepare()
    {
        Menu* pMVar1;
        DAT_GameCore::instance.currentlyInGameUnk_0xa4 = FALSE;
        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
            DAT_TextureRenderCoreObject::ptr)("frontend_combat3.tgx");
        MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadTGX_shc_back)();
        DAT_MenuHandlerState::instance.y = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
        DAT_MenuHandlerState::instance.x = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
        pMVar1 = DAT_MenuHandlerState::instance.currentMenu;
        (DAT_MenuHandlerState::instance.currentMenu)->xPosition = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
        pMVar1->yPosition = DAT_MenuHandlerState::instance.y;
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
            ((MenuModalType)0x14), FALSE);
    }

}
}
