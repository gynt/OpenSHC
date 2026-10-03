#include "../Rendering.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x004B2A60
int Rendering::ViewportBasedTileNumber()
{
    int iVar1;
    iVar1 = 8;
    if (DAT_TileMapState::instance.mapOrientation != 0) {
        if (DAT_TileMapState::instance.mapOrientation == 6) {
            iVar1 = 80408;
        } else if (DAT_TileMapState::instance.mapOrientation == 4) {
            iVar1 = 160808;
        } else if (DAT_TileMapState::instance.mapOrientation == 2) {
            iVar1 = 241208;
        }
    }
    return DAT_ViewportRenderState::instance
        .screenPointToTileNumber[((int)(DAT_ViewportRenderState::instance.viewportState.viewportX
                                      + (DAT_ViewportRenderState::instance.viewportState.viewportX >> 0x1f & 0x1fU))
                                     >> 5)
            + ((int)DAT_ViewportRenderState::instance.viewportState.mbr_0xb0 / 2
                  + ((int)(DAT_ViewportRenderState::instance.viewportState.viewportY
                         + (DAT_ViewportRenderState::instance.viewportState.viewportY >> 0x1f & 0xfU))
                      >> 4))
                * 0x191
            + DAT_ViewportRenderState::instance.viewportState.mbr_0xac + iVar1 + -8];
}

}
