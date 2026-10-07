#include "../Rendering.func.hpp"

#include "OpenSHC/UI/Rendering.func.hpp"

#include "OpenSHC/Globals/DAT_MissionDefinedData.hpp"
#include "OpenSHC/Globals/FLOAT_00ed312c.hpp"
#include "OpenSHC/Globals/FLOAT_Between1And5.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DB490
    void Rendering::RenderHistoryBookEdgeUnk()
    {
        int iVar1;
        int xPosInMenuRect;
        int yPosInMenuRect;
        FLOAT_00ed312c::instance = FLOAT_Between1And5::instance / 6.0 + FLOAT_00ed312c::instance;
        if (50.0 <= FLOAT_00ed312c::instance) {
            FLOAT_00ed312c::instance = 0.0;
        }
        yPosInMenuRect = 0xf;
        xPosInMenuRect = 0x2a0;
        iVar1 = (long)((double)FLOAT_00ed312c::instance);
        MACRO_CALL(UI::Rendering_Func::RenderGfxHelperUnk)(
            DAT_MissionDefinedData::instance.HistoryBookEdgeSpriteIDs[iVar1] + 1, xPosInMenuRect, yPosInMenuRect);
        return;
    }

}
}
