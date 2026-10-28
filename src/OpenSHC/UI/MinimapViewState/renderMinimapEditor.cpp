#include "../MinimapViewState.func.hpp"

#include "OpenSHC/UI/MinimapViewState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004B7530
    void MinimapViewState::renderMinimapEditor(int xPos, int yPos, int width, int height)
    {
        int yOffset;
        int xOffset;
        int widthFactor;
        int heightFactor;
        xOffset = (DAT_ViewportRenderState::instance.viewportState.viewportTileColumns + -5) / 2
            + ((int)(DAT_ViewportRenderState::instance.viewportState.viewportX
                   + (DAT_ViewportRenderState::instance.viewportState.viewportX >> 0x1f & 0x1fU))
                >> 5);
        yOffset = DAT_ViewportRenderState::instance.viewportState.viewportTileRows / 2
            + ((int)(DAT_ViewportRenderState::instance.viewportState.viewportY
                   + (DAT_ViewportRenderState::instance.viewportState.viewportY >> 0x1f & 7U))
                >> 3);
        this->DAT_SomeMiniMapCounterTill4 = 0;
        if (((this->forceRedraw != 0) || (xOffset != this->lastRenderedViewX)) || (yOffset != this->lastRenderedViewY)) {
            if (DAT_TileMapState::instance.mapSize < 0xc9) {
                heightFactor = 2;
                widthFactor = 4;
            } else {
                heightFactor = 1;
                widthFactor = 2;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::drawMinimap, this)(
                xPos, yPos, width, height, 5, xOffset, yOffset, widthFactor, heightFactor, -1);
            DAT_WindowAndDirectDraw::instance.pendingOverlayBltMode = 2;
        }
        this->lastRenderedViewX = xOffset;
        this->lastRenderedViewY = yOffset;
        this->forceRedraw = 0;
        this->skipMenuRedrawFlag = 0;
    }

}
}
