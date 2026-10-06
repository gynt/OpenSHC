#include "../Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004347F0
    undefined4 Helpers::SomeUnitAndViewportCheck(int unitID)
    {
        int iVar4;
        int iVar6;
        int iVar7;
        if (((!DAT_MinimapViewState::instance.field15_0x3c)
                && (DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile))
            && ((DAT_TileMapState::instance
                     .LogicLayer[DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile]
                & 0x10000300U))) {
            int iVar1 = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent
                            [DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile];
            int iVar2 = DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile
                - DAT_ViewportRenderState::instance.translationMatrix[iVar1].addXgetTile;
            int iVar3 = (int)DAT_UnitsState::instance.units[unitID].x;
            int iVar5 = (int)DAT_UnitsState::instance.units[unitID].y;
            if (DAT_TileMapState::instance.mapOrientation == 2) {
                iVar6 = 400 - iVar2;
                iVar7 = 400 - iVar3;
                iVar2 = iVar1;
                iVar4 = iVar5;
            } else if (DAT_TileMapState::instance.mapOrientation == 4) {
                iVar6 = 400 - iVar1;
                iVar7 = 400 - iVar5;
                iVar2 = 400 - iVar2;
                iVar4 = 400 - iVar3;
            } else {
                iVar6 = iVar1;
                iVar4 = iVar3;
                iVar7 = iVar5;
                if (DAT_TileMapState::instance.mapOrientation == 6) {
                    iVar6 = iVar2;
                    iVar2 = 400 - iVar1;
                    iVar4 = 400 - iVar5;
                    iVar7 = iVar3;
                }
            }
            if (iVar7 + iVar4 < iVar2 + iVar6) {
                return (undefined4)(0);
            }
        }
        return (undefined4)(1);
    }

}
}
