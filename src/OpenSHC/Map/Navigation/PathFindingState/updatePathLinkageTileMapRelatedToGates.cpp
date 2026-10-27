#include "../PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        static inline bool isGateLinkBlocked(int tile, int height, int otherHeight, int closed)
        {
            return (DAT_TileMapState::instance.LogicLayer[tile] & 0x4a5014b1U) != 0 || height > otherHeight + 0x10
                || height < otherHeight - 0x10 || closed != 0;
        }

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00499FA0
        void PathFindingState::updatePathLinkageTileMapRelatedToGates(int buildingID)
        {
            int _x = (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x;
            int _widthOrHeight = DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight;
            int _half = _widthOrHeight / 2;
            if (DAT_BuildingsState::instance.buildings[buildingID].buildingVariation == 80) {
                int _y = (int)(short)DAT_BuildingsState::instance.buildings[buildingID].y;
                byte _gateOpenState = DAT_BuildingsState::instance.buildings[buildingID].gateOpenState;
                int _row = _y + _half;
                int _xRight = _widthOrHeight + _x;
                int _tile = DAT_ViewportRenderState::instance.translationMatrix[_row].addXgetTile + _x - 1;
                int _height = DAT_TileMapState::instance.HeightLayer[_tile];
                int _otherHeight = DAT_TileMapState::instance.DefaultHeightLayer[_tile + 1];
                if (isGateLinkBlocked(_tile, _height, _otherHeight, _gateOpenState == 2)) {
                    DAT_TileMapState::instance.PathLinkageLayer[_tile] &= 0xfb;
                    DAT_TileMapState::instance.PathLinkageLayer[_tile + 1] &= 0xbf;
                } else {
                    DAT_TileMapState::instance.PathLinkageLayer[_tile] |= 4;
                    DAT_TileMapState::instance.PathLinkageLayer[_tile + 1] |= 0x40;
                }
                _tile = DAT_ViewportRenderState::instance.translationMatrix[_row].addXgetTile + _xRight;
                _height = DAT_TileMapState::instance.HeightLayer[_tile];
                _otherHeight = DAT_TileMapState::instance.DefaultHeightLayer[_tile - 1];
                if (isGateLinkBlocked(_tile, _height, _otherHeight, _gateOpenState == 2)) {
                    DAT_TileMapState::instance.PathLinkageLayer[_tile] &= 0xbf;
                    DAT_TileMapState::instance.PathLinkageLayer[_tile - 1] &= 0xfb;
                } else {
                    DAT_TileMapState::instance.PathLinkageLayer[_tile] |= 0x40;
                    DAT_TileMapState::instance.PathLinkageLayer[_tile - 1] |= 4;
                }
            } else {
                int _xMiddle = _x + _half;
                int _y = (int)(short)DAT_BuildingsState::instance.buildings[buildingID].y;
                byte _gateOpenState = DAT_BuildingsState::instance.buildings[buildingID].gateOpenState;
                int _yBottom = _widthOrHeight + _y;
                int _tile = DAT_ViewportRenderState::instance.translationMatrix[_y - 1].addXgetTile + _xMiddle;
                int _otherTile = DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile + _xMiddle;
                int _height = DAT_TileMapState::instance.DefaultHeightLayer[_tile];
                if (isGateLinkBlocked(_tile, _height, DAT_TileMapState::instance.DefaultHeightLayer[_otherTile], _gateOpenState == 2)) {
                    DAT_TileMapState::instance.PathLinkageLayer[_tile] &= 0xef;
                    DAT_TileMapState::instance.PathLinkageLayer[_otherTile] &= 0xfe;
                } else {
                    DAT_TileMapState::instance.PathLinkageLayer[_tile] |= 0x10;
                    DAT_TileMapState::instance.PathLinkageLayer[_otherTile] |= 1;
                }
                _tile = DAT_ViewportRenderState::instance.translationMatrix[_yBottom].addXgetTile + _xMiddle;
                _otherTile = DAT_ViewportRenderState::instance.translationMatrix[_yBottom - 1].addXgetTile + _xMiddle;
                _height = DAT_TileMapState::instance.DefaultHeightLayer[_tile];
                int _otherHeight = DAT_TileMapState::instance.DefaultHeightLayer[_otherTile];
                if (isGateLinkBlocked(_tile, _height, _otherHeight, _gateOpenState == 2)) {
                    DAT_TileMapState::instance.PathLinkageLayer[_tile] &= 0xfe;
                    DAT_TileMapState::instance.PathLinkageLayer[_otherTile] &= 0xef;
                } else {
                    DAT_TileMapState::instance.PathLinkageLayer[_tile] |= 1;
                    DAT_TileMapState::instance.PathLinkageLayer[_otherTile] |= 0x10;
                }
            }
        }

    }
}
}
