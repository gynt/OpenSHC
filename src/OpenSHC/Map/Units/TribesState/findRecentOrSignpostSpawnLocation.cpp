#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00523410
        undefined4 TribesState::findRecentOrSignpostSpawnLocation(uint* param_1, uint* param_2)
        {
            short sVar1;
            uint uVar2;
            uint uVar3;
            int iVar4;
            iVar4 = 0;
            do {
                uVar2 = DAT_GameState::instance.mapAndTime.field2269_0xdee + iVar4 & 0x80000003;
                if ((int)uVar2 < 0) {
                    uVar2 = (uVar2 - 1 | 0xfffffffc) + 1;
                }
                sVar1 = DAT_GameState::instance.mapAndTime.lionLocationsXY[uVar2].x;
                if (sVar1 != 0) {
                    *param_1 = (int)sVar1;
                    uVar2 = DAT_GameState::instance.mapAndTime.field2269_0xdee + iVar4 & 0x80000003;
                    if ((int)uVar2 < 0) {
                        uVar2 = (uVar2 - 1 | 0xfffffffc) + 1;
                    }
                    uVar3 = (uint)DAT_GameState::instance.mapAndTime.lionLocationsXY[uVar2].y;
                    *param_2 = uVar3;
                    uVar2 = *param_1;
                    if ((((uVar2 < 400) && (uVar3 < 400)) && (*(char*)(uVar2 + 0x21aec98 + uVar3 * 400) != '\0'))
                        && ((DAT_TileMapState::instance
                                    .LogicLayer[DAT_ViewportRenderState::instance.translationMatrix[uVar3].addXgetTile
                                        + uVar2]
                                & 0x4a5014b1U)
                            == 0)) {
                        uVar2 = DAT_GameState::instance.mapAndTime.field2269_0xdee + 1 + iVar4 & 0x80000003;
                        if ((int)uVar2 < 0) {
                            uVar2 = (uVar2 - 1 | 0xfffffffc) + 1;
                        }
                        DAT_GameState::instance.mapAndTime.field2269_0xdee = (short)uVar2;
                        return (undefined4)(1);
                    }
                }
                iVar4 = iVar4 + 1;
                if (3 < iVar4) {
                    iVar4 = 0;
                    do {
                        if (DAT_GameState::instance.mapAndTime.signpostIDs[iVar4] != 0) {
                            *param_1 = DAT_GameState::instance.mapAndTime.signpostsMapEdge[iVar4][0].x;
                            *param_2 = DAT_GameState::instance.mapAndTime.signpostsMapEdge[iVar4][0].y;
                            return (undefined4)(1);
                        }
                        iVar4 = iVar4 + 1;
                    } while (iVar4 < 8);
                    return (undefined4)(0);
                }
            } while (true);
        }

    }
}
}
