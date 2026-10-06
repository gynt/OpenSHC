#include "../MinimapViewState.func.hpp"

#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004B51A0
    void MinimapViewState::convertMinimapClickToTileXY(int* param_1, int* param_2)
    {
        short sVar1;
        int iVar2;
        int iVar3;
        if (this->field15_0x3c) {
            iVar2 = DAT_MouseState::instance.screenSpaceY - this->y;
            iVar3 = 0;
            *param_1 = (((DAT_MouseState::instance.screenSpaceX - this->x) * this->oneOrTwo) / this->widthFactor + 6
                           + this->field5_0x14)
                * 0x20;
            iVar2 = ((this->oneOrTwo * iVar2) / this->heightFactor + this->field4_0x10) * 8;
            *param_2 = iVar2;
            if (DAT_TileMapState::instance.mapOrientation) {
                if (DAT_TileMapState::instance.mapOrientation == 6) {
                    iVar3 = 0x13a10;
                } else if (DAT_TileMapState::instance.mapOrientation == 4) {
                    iVar3 = 0x27420;
                } else if (DAT_TileMapState::instance.mapOrientation == 2) {
                    iVar3 = 0x3ae30;
                }
            }
            iVar2 = DAT_ViewportRenderState::instance
                        .screenPointToTileNumber[(*param_1 / 32) + (iVar2 / 16) * 0x191 + iVar3 + -6];
            sVar1 = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[iVar2];
            *param_2 = (int)sVar1;
            *param_1 = iVar2 - DAT_ViewportRenderState::instance.translationMatrix[sVar1].addXgetTile;
        }
        *param_1 = -1;
        *param_2 = -1;
    }

}
}
