#include "OpenSHC/Map/WildlifeState.func.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    // Rabbit route towards farmland. The BFS copies farmlandInfluence (signed > 0, jle 0x52D156) into routeBfsValue
    // over populated cells of the start's dominantPathAreaId; the original stores scoreThreshold into
    // floodCurrentValue at the start and never updates it in this BFS. The hill climb scans the 8 neighbours from
    // a random start direction (SEC_RNG byte & 7, drawn once), zeroing every neighbour whose routeBfsValue is non-zero
    // and above the running threshold (signed jle 0x52D40D), and steps to the last such one.
    // FUNCTION: STRONGHOLDCRUSADER 0x0052CFE0
    BOOLEnum WildlifeState::buildRallyPointPathForTribe(int tribeIndex, int scoreThreshold)
    {
        int const leader = DAT_TribesState::instance.tribes[tribeIndex].leaderUnitID;
        int cellX = DAT_UnitsState::instance.units[leader].x / 10;
        int cellY = DAT_UnitsState::instance.units[leader].y / 10;
        int curX;
        int curY;
        this->floodCurrentValue = scoreThreshold;
        this->floodQueueHead = 0;
        this->floodQueueTail = 1;
        if (this->grid[cellX][cellY].farmlandInfluence == 0) {
            return FALSE;
        }
        for (int y = 0; y < 40; y++) {
            for (int x = 0; x < 40; x++) {
                this->grid[x][y].routeBfsValue = 0;
                this->grid[x][y].routeVisited = 0;
            }
        }
        this->floodQueueY[0] = (short)cellY;
        this->floodQueueX[0] = (short)cellX;
        this->grid[cellX][cellY].routeBfsValue = this->grid[cellX][cellY].farmlandInfluence;
        int const areaID = this->grid[cellX][cellY].dominantPathAreaId;
        while (this->floodQueueHead != this->floodQueueTail) {
            curX = this->floodQueueX[this->floodQueueHead];
            curY = this->floodQueueY[this->floodQueueHead];
            for (int dir = 0; dir < 8; dir++) {
                uint const x = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[dir].int_.xOffset + curX;
                uint const y = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[dir].int_.yOffset + curY;
                if (x <= 39 && y <= 39 && this->grid[x][y].validTileCount > 0
                    && areaID == this->grid[x][y].dominantPathAreaId) {
                    int const value = this->grid[x][y].farmlandInfluence;
                    if (value > 0 && this->grid[x][y].routeBfsValue == 0) {
                        this->grid[x][y].routeBfsValue = value;
                        this->floodQueueX[this->floodQueueTail] = (short)x;
                        this->floodQueueY[this->floodQueueTail] = (short)y;
                        this->floodQueueTail++;
                        if ((int)this->floodQueueTail >= 0x640) {
                            this->floodQueueTail = 0;
                        }
                    }
                }
            }
            this->floodQueueHead++;
            if ((int)this->floodQueueHead >= 0x640) {
                this->floodQueueHead = 0;
            }
        }
        int const startDir = (byte)SEC_RNG::instance.currentNumber2 & 7;
        int bestValue = scoreThreshold;
        DAT_TribesState::instance.tribes[tribeIndex].currentRallyPointIndex = 0;
        DAT_TribesState::instance.tribes[tribeIndex].rallyPointCount = 0;
        this->grid[cellX][cellY].routeVisited = 1;
        this->grid[cellX][cellY].routeBfsValue = 0;
        curX = cellX;
        curY = cellY;
        while (true) {
            int bestDir = -1;
            for (int i = 0; i < 8; i++) {
                int dir = startDir + i;
                if (dir >= 8) {
                    dir -= 8;
                }
                uint const x = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[dir].int_.xOffset + curX;
                uint const y = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[dir].int_.yOffset + curY;
                if (x <= 39 && y <= 39 && this->grid[x][y].validTileCount > 0) {
                    int const value = this->grid[x][y].routeBfsValue;
                    if (value != 0 && value > bestValue) {
                        this->grid[x][y].routeBfsValue = 0;
                        bestValue = value;
                        bestDir = dir;
                    }
                }
            }
            if (bestDir <= -1) {
                break;
            }
            curX += DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[bestDir].int_.xOffset;
            curY += DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[bestDir].int_.yOffset;
            this->grid[curX][curY].routeVisited = 1;
            uint const tileY = curY * 10 + 5;
            uint const tileX = curX * 10 + 5;
            if (tileX <= 399 && tileY <= 399
                && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[tileY * 400 + tileX] != 0) {
                DAT_TribesState::instance.tribes[tribeIndex]
                    .rallyPointArray[DAT_TribesState::instance.tribes[tribeIndex].rallyPointCount][0]
                    = (short)(curX * 10 + 5);
                DAT_TribesState::instance.tribes[tribeIndex]
                    .rallyPointArray[DAT_TribesState::instance.tribes[tribeIndex].rallyPointCount][1]
                    = (short)(curY * 10 + 5);
                DAT_TribesState::instance.tribes[tribeIndex].rallyPointCount++;
            }
        }
        return TRUE;
    }

}
}
