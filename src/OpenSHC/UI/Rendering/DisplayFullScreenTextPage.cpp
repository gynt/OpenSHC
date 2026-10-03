#include "../Rendering.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_00ed2784.hpp"
#include "OpenSHC/Globals/DAT_ARRAY_00ed26d0.hpp"
#include "OpenSHC/Globals/DAT_ArrayOfStoredMenuStrings.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/INT_00eb0e28.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Rendering::Enums::RenderTarget;

    // FUNCTION: STRONGHOLDCRUSADER 0x004DB0D0
    void Rendering::DisplayFullScreenTextPage(int param_1)
    {
        RenderTargetInt RVar1;
        RenderTargetInt RVar2;
        RVar2 = DAT_TextManagerObject::instance.textSurfaceTarget;
        RVar1 = DAT_PencilRenderCore::instance.surfaceTarget;
        DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
            0, 0, 600, 800, (ushort)((int)(COL_BLACK::instance.shortValue)));
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
            DAT_ArrayOfStoredMenuStrings::instance[param_1], 0xf, 0xcd, 0x20d, 0xccfaff, 0x11, 0);
        INT_00eb0e28::instance = DAT_TextManagerObject::instance.field1_0x4 + 0xd7;
        if (INT_00eb0e28::instance < 0xdc) {
            INT_00eb0e28::instance = 0xdc;
        }
        DAT_00ed2784::instance = 0;
        DAT_PencilRenderCore::instance.surfaceTarget = RVar1;
        DAT_TextManagerObject::instance.textSurfaceTarget = RVar2;
        DAT_ARRAY_00ed26d0::instance[0].x = timeGetTime();
        return;
    }

}
}
