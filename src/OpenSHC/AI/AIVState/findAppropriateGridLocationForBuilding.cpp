#include "../AIVState.func.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"

namespace OpenSHC {
namespace AI {

    // breadth first search for a grid cell whose eight neighbours are all free
    // FUNCTION: STRONGHOLDCRUSADER 0x004EEE10
    void AIVState::findAppropriateGridLocationForBuilding(uint gridX, uint gridY)
    {
        this->visitCount = 1;
        this->bfsQueueHead = 0;
        this->bfsQueueTail = 1;
        this->heatMapXArray[0] = gridX;
        this->heatMapYArray[0] = gridY;
        this->buildingApproriateGridXPosition = -1;
        this->buildingAppropriateGridYPosition = -1;
        if (gridX > 79 || gridY > 79 || this->heatMaps[gridX][gridY].isEdgeOrOffMapCell) {
            return;
        }
        ++this->mapExtraInfo.algorithmIterationNumber;
        this->heatMaps[gridX][gridY].algorithmIterationNumber = this->mapExtraInfo.algorithmIterationNumber;
        this->heatMaps[gridX][gridY].bfsDepth = this->visitCount;

        int x;
        int y;
        while (this->bfsQueueHead != this->bfsQueueTail) {
            int freeCount = 0;
            x = this->heatMapXArray[this->bfsQueueHead];
            y = this->heatMapYArray[this->bfsQueueHead];
            if (!this->heatMaps[x][y].tilesNotPartOfLargestAreaCount) {
                freeCount = 1;
            }
            this->visitCount = (char)this->heatMaps[x][y].bfsDepth;
            for (int direction = 0; direction < 8; ++direction) {
                uint const candidateX
                    = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[direction].int_.xOffset + x;
                uint const candidateY
                    = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[direction].int_.yOffset + y;
                if (this->heatMaps[x][y].isEdgeOrOffMapCell && (candidateX > 79 || candidateY > 79)) {
                    continue;
                }
                int const notInLargestArea
                    = (char)this->heatMaps[candidateX][candidateY].tilesNotPartOfLargestAreaCount;
                if (!this->heatMaps[candidateX][candidateY].terrainDiffHigherThan12
                    && !this->heatMaps[candidateX][candidateY].structureCount
                    && !this->heatMaps[candidateX][candidateY].isEdgeOrOffMapCell
                    && !this->heatMaps[candidateX][candidateY].destructionBasedPlacementCooldown
                    && !this->heatMaps[candidateX][candidateY].treeCount
                    && (char)this->heatMaps[candidateX][candidateY].bouldersCount <= 0 && !notInLargestArea) {
                    ++freeCount;
                }
                if (this->heatMaps[candidateX][candidateY].algorithmIterationNumber
                    == this->mapExtraInfo.algorithmIterationNumber) {
                    continue;
                }
                this->heatMaps[candidateX][candidateY].algorithmIterationNumber
                    = this->mapExtraInfo.algorithmIterationNumber;
                if (notInLargestArea >= 15) {
                    continue;
                }
                this->heatMaps[candidateX][candidateY].bfsDepth = this->visitCount + 1;
                this->heatMapXArray[this->bfsQueueTail] = candidateX;
                this->heatMapYArray[this->bfsQueueTail] = candidateY;
                ++this->bfsQueueTail;
                if ((int)this->bfsQueueTail >= 6400) {
                    this->bfsQueueTail = 0;
                }
            }
            if (freeCount == 9) {
                goto found;
            }
            ++this->bfsQueueHead;
            if ((int)this->bfsQueueHead >= 6400) {
                this->bfsQueueHead = 0;
            }
        }
        return;

    found:
        // the result is the last visited neighbour (direction 7)
        int const resultY = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[7].int_.yOffset + y;
        int const resultX = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[7].int_.xOffset + x;
        this->buildingApproriateGridXPosition = resultX;
        this->buildingAppropriateGridYPosition = resultY;
    }

}
}
