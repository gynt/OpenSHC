#include "OpenSHC/Map/WildlifeState.func.hpp"

#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    // Deer/lion wander route. BFS from the leader's cell writes routeBfsValue (seed always2or3or5, -1 per step,
    // stops when the dequeued value is <= 1, signed jle 0x52CCF1) over populated cells of the same path area
    // that are safe: mode 0 needs dangerInfluence == 0 and, for AITT_DEER tribes only, no deer and no lions;
    // mode 1 needs no humans, no buildings and no lions. A cell is (re)queued only when its value is below the
    // new one (signed jge 0x52CCAB). The hill climb then scans the 8 neighbours from a random start direction
    // (SEC_RNG byte & 7, drawn once), zeroing every neighbour whose routeBfsValue is non-zero and below the
    // running value (signed jge 0x52CDC0), steps to the last such one and appends the pathfinding-adjusted
    // cell centre (findNearbyTileInConnectionArea) to the tribe's rally points.
    // FUNCTION: STRONGHOLDCRUSADER 0x0052CAB0
    void WildlifeState::findAndSetNewRallyPointForDeerAndLions(int tribeID, int always2or3or5, int always0or1)
    {
        int const leader = DAT_TribesState::instance.tribes[tribeID].leaderUnitID;
        int cellX = DAT_UnitsState::instance.units[leader].x / 10;
        int cellY = DAT_UnitsState::instance.units[leader].y / 10;
        int curX;
        int curY;
        this->floodCurrentValue = always2or3or5;
        this->floodQueueHead = 0;
        this->floodQueueTail = 1;
        for (int y = 0; y < 40; y++) {
            for (int x = 0; x < 40; x++) {
                this->grid[x][y].routeBfsValue = 0;
                this->grid[x][y].routeVisited = 0;
            }
        }
        this->floodQueueY[0] = (short)cellY;
        this->floodQueueX[0] = (short)cellX;
        int const areaID = this->grid[cellX][cellY].dominantPathAreaId;
        this->grid[cellX][cellY].routeBfsValue = always2or3or5;
        while (this->floodQueueHead != this->floodQueueTail) {
            curX = this->floodQueueX[this->floodQueueHead];
            curY = this->floodQueueY[this->floodQueueHead];
            this->floodCurrentValue = this->grid[curX][curY].routeBfsValue;
            if ((int)this->floodCurrentValue <= 1) {
                break;
            }
            int const nextValue = this->floodCurrentValue - 1;
            for (int dir = 0; dir < 8; dir++) {
                uint const x = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[dir].int_.xOffset + curX;
                uint const y = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[dir].int_.yOffset + curY;
                if (x <= 39 && y <= 39 && this->grid[x][y].validTileCount > 0
                    && areaID == this->grid[x][y].dominantPathAreaId) {
                    if (always0or1 == 0) {
                        if (this->grid[x][y].dangerInfluence != 0) {
                            continue;
                        }
                        if (DAT_TribesState::instance.tribes[tribeID].tribeType == OpenSHC::AI::Tribes::AITT_DEER
                            && (this->grid[x][y].deerCount != 0 || this->grid[x][y].lionCount != 0)) {
                            continue;
                        }
                    } else if (this->grid[x][y].humanCount != 0 || this->grid[x][y].buildingTileCount != 0
                        || this->grid[x][y].lionCount != 0) {
                        continue;
                    }
                    if (this->grid[x][y].routeBfsValue < nextValue) {
                        this->grid[x][y].routeBfsValue = nextValue;
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
        int bestValue = always2or3or5;
        DAT_TribesState::instance.tribes[tribeID].currentRallyPointIndex = 0;
        DAT_TribesState::instance.tribes[tribeID].rallyPointCount = 0;
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
                    if (value != 0 && value < bestValue) {
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
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::findNearbyTileInConnectionArea,
                    DAT_PathFindingState::ptr)(areaID, tileX, tileY);
                DAT_TribesState::instance.tribes[tribeID]
                    .rallyPointArray[DAT_TribesState::instance.tribes[tribeID].rallyPointCount][0]
                    = (short)DAT_PathFindingState::instance.climbX;
                DAT_TribesState::instance.tribes[tribeID]
                    .rallyPointArray[DAT_TribesState::instance.tribes[tribeID].rallyPointCount][1]
                    = (short)DAT_PathFindingState::instance.climbY;
                DAT_TribesState::instance.tribes[tribeID].rallyPointCount++;
            }
        }
    }

}
}
