#include "../../Map.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F3B90
    int LandscapeState::findTree(int playerID, uint unitXPosition, uint unitYPosition)
    {
        ushort uVar2;
        BOOLEnum BVar3;
        int iVar6;
        short* psVar8;
        int local_18;
        int local_14;
        int local_10;
        if (((unitXPosition < 400) && (unitYPosition < 400))
            && (*(char*)(unitYPosition * 400 + 0x21aec98 + unitXPosition) != '\0')) {
            uVar2
                = DAT_TileMapState::instance.PathConnectionLayer
                      [DAT_ViewportRenderState::instance.translationMatrix[unitYPosition].addXgetTile + unitXPosition];
            local_14 = 10000;
            local_10 = 0;
            if (0 < (short)uVar2) {
                local_18 = 1;
                if (1 < this->maxTreeCount) {
                    psVar8 = &this->trees[1].state;
                    do {
                        if (((*(int*)(psVar8 + 0x1e) < 4) && (*psVar8 == 2))
                            && (BVar3 = MACRO_CALL_MEMBER(Map::LandscapeState_Func::isTreeAdult, this)(
                                    local_18, (int)((int)(*(int*)(psVar8 + 4)))),
                                BVar3 != FALSE)) {
                            byte bVar1 = DAT_TileMapState::instance.HeightLayer[*(uint*)(psVar8 + 0x12)];
                            for (iVar6 = 0; iVar6 < 8; iVar6++) {
                                int iVar7 = DAT_TileMapState::instance.directionTranslationMatrix[psVar8[0x10]][iVar6]
                                    + *(uint*)(psVar8 + 0x12);
                                uint uVar5 = (uint)DAT_TileMapState::instance.HeightLayer[iVar7];
                                if (DAT_TileMapState::instance.BuildingLayer[iVar7] != 0) {
                                    int iVar4 = MACRO_CALL_MEMBER(
                                        Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                                        DAT_BuildingsState::ptr)((int)DAT_TileMapState::instance.BuildingLayer[iVar7]);
                                    uVar5 = uVar5 + iVar4;
                                }
                                if ((((int)(uint)bVar1 <= (int)(uVar5 + 0x10))
                                        && ((int)(uVar5 - 0x10) <= (int)(uint)bVar1))
                                    && (iVar7 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                                      calculateCanPlayerUnitsNavigateToAreaFromArea,
                                            DAT_PathFindingState::ptr)(playerID, (dword)((int)((int)(short)uVar2)),
                                            (dword)((int)((
                                                int)(short)DAT_TileMapState::instance.PathConnectionLayer[iVar7])),
                                            0),
                                        iVar7 != 0)) {
                                    if ((iVar6 < 8)
                                        && (MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::
                                                                  setAxisBasedDistanceResult,
                                                DAT_DirectionAlgorithmState::ptr)(unitXPosition,
                                                (int)((int)(unitYPosition)), (int)((int)(psVar8[0xf])),
                                                (int)((int)(psVar8[0x10]))),
                                            DAT_DirectionAlgorithmState::instance.distanceHigh < local_14)) {
                                        local_14 = DAT_DirectionAlgorithmState::instance.distanceHigh;
                                        local_10 = local_18;
                                    }
                                    break;
                                }
                            }
                        }
                        local_18 = local_18 + 1;
                        psVar8 = psVar8 + 0x4e;
                    } while (local_18 < this->maxTreeCount);
                }
                return local_10;
            }
        }
        return 0;
    }

}
}
