#include "../PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0049A1C0
        void PathFindingState::updatePathLinkageTileMapRelatedToKeeps(int buildingID)
        {
            int iVar2;
            int iVar3;
            int iVar4;
            int iVar5;
            short _orientation;
            _orientation = DAT_BuildingsState::instance.buildings[buildingID].orientation;
            if (_orientation == 4) {
                iVar4 = (int)(short)DAT_BuildingsState::instance.buildings[buildingID].y - 1;
                iVar3 = (int)DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight / 2
                    + (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x;
                iVar5 = DAT_ViewportRenderState::instance.translationMatrix[iVar4].addXgetTile + iVar3;
                DAT_TileMapState::instance.PathLinkageLayer[iVar5] = DAT_TileMapState::instance.PathLinkageLayer[iVar5] | 0x10;
                iVar5 = DAT_ViewportRenderState::instance.translationMatrix[iVar4 + 1].addXgetTile + iVar3;
                DAT_TileMapState::instance.PathLinkageLayer[iVar5] = DAT_TileMapState::instance.PathLinkageLayer[iVar5] | 1;
                return;
            }
            if (_orientation == 6) {
                iVar3 = (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x - 1;
                iVar4 = (int)DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight / 2
                    + (int)(short)DAT_BuildingsState::instance.buildings[buildingID].y;
            } else {
                if (_orientation == 2) {
                    iVar2 = (int)DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight;
                    iVar3 = (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x + iVar2 - 1;
                    iVar4 = (int)(short)DAT_BuildingsState::instance.buildings[buildingID].y + iVar2 / 2;
                } else {
                    iVar2 = (int)DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight;
                    iVar4 = (int)(short)DAT_BuildingsState::instance.buildings[buildingID].y + iVar2 - 1;
                    iVar3 = (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x + iVar2 / 2;
                    iVar5 = DAT_ViewportRenderState::instance.translationMatrix[iVar4].addXgetTile + iVar3;
                    DAT_TileMapState::instance.PathLinkageLayer[iVar5] = DAT_TileMapState::instance.PathLinkageLayer[iVar5] | 0x10;
                    iVar5 = DAT_ViewportRenderState::instance.translationMatrix[iVar4 + 1].addXgetTile + iVar3;
                    DAT_TileMapState::instance.PathLinkageLayer[iVar5] = DAT_TileMapState::instance.PathLinkageLayer[iVar5] | 1;
                    return;
                }
            }
            iVar3 = DAT_ViewportRenderState::instance.translationMatrix[iVar4].addXgetTile + iVar3;
            DAT_TileMapState::instance.PathLinkageLayer[iVar3] = DAT_TileMapState::instance.PathLinkageLayer[iVar3] | 4;
            DAT_TileMapState::instance.PathLinkageLayer[iVar3 + 1]
                = DAT_TileMapState::instance.PathLinkageLayer[iVar3 + 1] | 0x40;
            return;
        }

    }
}
}
