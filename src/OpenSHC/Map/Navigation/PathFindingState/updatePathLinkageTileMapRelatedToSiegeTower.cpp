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
        // FUNCTION: STRONGHOLDCRUSADER 0x0049A2E0
        void PathFindingState::updatePathLinkageTileMapRelatedToSiegeTower(int param_1)
        {
            int iVar4 = (int)(short)DAT_BuildingsState::instance.buildings[param_1].x;
            int iVar2 = (int)(short)DAT_BuildingsState::instance.buildings[param_1].y;
            int _tile = DAT_ViewportRenderState::instance.translationMatrix[iVar2 + -1].addXgetTile + iVar4 + 1;
            DAT_TileMapState::instance.PathLinkageLayer[_tile] |= 0x10;
            _tile = DAT_ViewportRenderState::instance.translationMatrix[iVar2].addXgetTile + iVar4 + 1;
            DAT_TileMapState::instance.PathLinkageLayer[_tile] |= 0x11;
            _tile = DAT_ViewportRenderState::instance.translationMatrix[iVar2 + 2].addXgetTile + iVar4 + 1;
            DAT_TileMapState::instance.PathLinkageLayer[_tile] |= 0x11;
            _tile = DAT_ViewportRenderState::instance.translationMatrix[iVar2 + 3].addXgetTile + iVar4 + 1;
            int iVar3 = DAT_ViewportRenderState::instance.translationMatrix[iVar2 + 1].addXgetTile + iVar4;
            DAT_TileMapState::instance.PathLinkageLayer[_tile] |= 1;
            /* 0x1E1E4F7: byte before PathLinkageLayer[iVar3] */
            DAT_TileMapState::instance.PathLinkageLayer[iVar3 - 1] |= 4;
            DAT_TileMapState::instance.PathLinkageLayer[iVar3] |= 0x44;
            DAT_TileMapState::instance.PathLinkageLayer[iVar3 + 2] |= 0x44;
            DAT_TileMapState::instance.PathLinkageLayer[iVar3 + 3] |= 0x40;
        }

    }
}
}
