#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    // Start offset index = low byte of currentNumber2 & 7 (movzx byte 0x4F2E04). Bounds are unsigned (ja); the
    // height window is signed (jg 0x4F2F42 / jl 0x4F2F4D). Logic2Layer is read signed (movsx 0x4F2EEA).
    // FUNCTION: STRONGHOLDCRUSADER 0x004F2E00
    undefined4 LandscapeState::setupBabyTreeLocation(uint treeID, int treeType, uint x, uint y)
    {
        int offsetIndex = SEC_RNG::instance.currentNumber2 & 7;
        int spacingRadius = 3;
        if (treeID & 1) {
            spacingRadius = 4;
        }
        DAT_PathFindingState::instance.ALG_ResultTile = 0;
        DAT_PathFindingState::instance.ALG_ResultY = 0;
        DAT_PathFindingState::instance.ALG_ResultX = 0;
        if (x > 399 || y > 399 || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == 0) {
            return 0;
        }
        int const parentHeight = DAT_TileMapState::instance
                                     .HeightLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x];
        for (int attempt = 0; attempt < 8; attempt++) {
            uint const targetX = DAT_OrganismDefinedData::instance.TreeSpreadOffsets[offsetIndex].x + x;
            uint const targetY = DAT_OrganismDefinedData::instance.TreeSpreadOffsets[offsetIndex].y + y;
            offsetIndex++;
            if (offsetIndex >= 8) {
                offsetIndex = 0;
            }
            if (targetX > 399 || targetY > 399
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[targetY * 400 + targetX] == 0) {
                continue;
            }
            int targetTile = DAT_ViewportRenderState::instance.translationMatrix[targetY].addXgetTile;
            int const logic2Flags = DAT_TileMapState::instance.Logic2Layer[targetTile + targetX];
            targetTile += targetX;
            if (DAT_TileMapState::instance.OrganismLayer[targetTile] != 0
                || (DAT_TileMapState::instance.LogicLayer[targetTile] & 0x703e25b5) != 0
                || DAT_TileMapState::instance.UnitLayer[targetTile] != 0
                || DAT_TileMapState::instance.BuildingLayer[targetTile] != 0) {
                continue;
            }
            if (treeType == 1) {
                if (logic2Flags & 0x90) {
                    continue;
                }
            }
            else {
                if (!(logic2Flags & 0x90)) {
                    continue;
                }
            }
            int const height = DAT_TileMapState::instance.HeightLayer[targetTile];
            if (height > parentHeight + 0x40 || height < parentHeight - 0x40) {
                continue;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::setupBabyTreeLocationInfo,
                    DAT_PathFindingState::ptr)(spacingRadius, treeType, targetX, targetY)
                != 0) {
                DAT_PathFindingState::instance.ALG_ResultTile = targetTile;
                DAT_PathFindingState::instance.ALG_ResultX = targetX;
                DAT_PathFindingState::instance.ALG_ResultY = targetY;
                return 1;
            }
        }
        return 0;
    }

}
}
