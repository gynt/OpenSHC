#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // Unit position bounds unsigned (ja); unit area read signed (movsx) and must be > 0 (jle 0x4F3BF6). Per tree
    // the first neighbour within +-16 height (building height added, signed jg/jl) that playerID can reach is
    // taken (loop break; dir < 8 test at 0x4F3CC5), closest by distanceHigh (signed jge 0x4F3CF1).
    // FUNCTION: STRONGHOLDCRUSADER 0x004F3B90
    int LandscapeState::findTree(int playerID, uint unitXPosition, uint unitYPosition)
    {
        if (unitXPosition > 399 || unitYPosition > 399
            || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[unitYPosition * 400 + unitXPosition] == 0) {
            return 0;
        }
        else {
        int const unitArea = (short)DAT_TileMapState::instance.PathConnectionLayer
                                 [DAT_ViewportRenderState::instance.translationMatrix[unitYPosition].addXgetTile
                                     + unitXPosition];
        int bestDistance = 10000;
        int bestTreeID = 0;
        if (unitArea <= 0) {
            return 0;
        }
        for (int treeID = 1; treeID < this->maxTreeCount; treeID++) {
            if (this->trees[treeID].stage >= 4) {
                continue;
            }
            if (this->trees[treeID].state != 2) {
                continue;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::isTreeAdult, this)(
                    treeID, this->trees[treeID].uid)
                == FALSE) {
                continue;
            }
            int const treeHeight = DAT_TileMapState::instance.HeightLayer[this->trees[treeID].tile];
            int direction;
            for (direction = 0; direction < 8; direction++) {
                int const neighbourTile
                    = DAT_TileMapState::instance
                          .directionTranslationMatrix[(short)this->trees[treeID].yPosition][direction]
                    + this->trees[treeID].tile;
                int neighbourHeight = DAT_TileMapState::instance.HeightLayer[neighbourTile];
                if (DAT_TileMapState::instance.BuildingLayer[neighbourTile] != 0) {
                    neighbourHeight += MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                        DAT_BuildingsState::ptr)(DAT_TileMapState::instance.BuildingLayer[neighbourTile]);
                }
                if (treeHeight > neighbourHeight + 16 || treeHeight < neighbourHeight - 16) {
                    continue;
                }
                if (MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                        DAT_PathFindingState::ptr)(
                        playerID, unitArea, (short)DAT_TileMapState::instance.PathConnectionLayer[neighbourTile], 0)
                    != 0) {
                    break;
                }
            }
            if (direction < 8) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(unitXPosition, unitYPosition,
                    (short)this->trees[treeID].xPosition, (short)this->trees[treeID].yPosition);
                if (DAT_DirectionAlgorithmState::instance.distanceHigh < bestDistance) {
                    bestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                    bestTreeID = treeID;
                }
            }
        }
        return bestTreeID;
        }
    }

}
}
