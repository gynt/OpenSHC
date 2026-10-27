#include "../EditScenario.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::UI::Enums::MenuModalType;

        // FUNCTION: STRONGHOLDCRUSADER 0x004B8080
        void EditScenario::MenuView_EditScenario_DoEveryFrame()
        {
            DAT_TextureRenderCoreObject::instance.currentRenderSurfaceIdentifierUnk_0x8
                = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                DAT_TextureRenderCoreObject::ptr)(0,
                (DAT_WindowAndDirectDraw::instance.resolutionX
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].width)
                    / 2,
                (DAT_WindowAndDirectDraw::instance.resolutionY
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height)
                    / 2);
            if (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE) {
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                /*
                  added by script: "Scenario Editor"
                 */
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner, DAT_PencilRenderCore::ptr)(
                    199, 2, DAT_MenuHandlerState::instance.x, DAT_MenuHandlerState::instance.y, 800, 0x3c);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                int x1_00 = DAT_MenuHandlerState::instance.x + 0x10e;
                int x2_00 = DAT_MenuHandlerState::instance.x + 0x302;
                int top = DAT_MenuHandlerState::instance.y + 0x5a;
                int bottom = DAT_MenuHandlerState::instance.y + 0x1e9;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                    x1_00, top, x2_00 + -0x14, bottom);
                int x2 = x2_00 + 1;
                int x1 = x1_00 + -1;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    x1, top + -1, x2, top + -1, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    x1, bottom + 1, x2, bottom + 1, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    x2_00 + -0x14, top + 0x14, x2, top + 0x14, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    x1, top, x1, bottom, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    x2, top, x2, bottom, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    x2_00 + -0x14, top, x2_00 + -0x14, bottom, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    x2_00 + -0x13, bottom + -0x14, x2_00, bottom + -0x14,
                    (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            }
            return;
        }

    }
}
}
