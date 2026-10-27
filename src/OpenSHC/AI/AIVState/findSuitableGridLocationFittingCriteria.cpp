#include "../AIVState.func.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"

namespace OpenSHC {
namespace AI {

    // breadth first search for the closest free grid cell
    // FUNCTION: STRONGHOLDCRUSADER 0x004EEBD0
    void AIVState::findSuitableGridLocationFittingCriteria(uint gridX, uint gridY)
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

        while (this->bfsQueueHead != this->bfsQueueTail) {
            int const x = this->heatMapXArray[this->bfsQueueHead];
            int const y = this->heatMapYArray[this->bfsQueueHead];
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
                if (this->heatMaps[candidateX][candidateY].algorithmIterationNumber
                    == this->mapExtraInfo.algorithmIterationNumber) {
                    continue;
                }
                this->heatMaps[candidateX][candidateY].algorithmIterationNumber
                    = this->mapExtraInfo.algorithmIterationNumber;
                if (notInLargestArea >= 15) {
                    continue;
                }
                if (!this->heatMaps[candidateX][candidateY].terrainDiffHigherThan12
                    && !this->heatMaps[candidateX][candidateY].structureCount
                    && !this->heatMaps[candidateX][candidateY].isEdgeOrOffMapCell
                    && !this->heatMaps[candidateX][candidateY].destructionBasedPlacementCooldown
                    && !this->heatMaps[candidateX][candidateY].treeCount
                    && (char)this->heatMaps[candidateX][candidateY].bouldersCount <= 0 && !notInLargestArea) {
                    this->buildingApproriateGridXPosition = candidateX;
                    this->buildingAppropriateGridYPosition = candidateY;
                    return;
                }
                this->heatMaps[candidateX][candidateY].bfsDepth = this->visitCount + 1;
                this->heatMapXArray[this->bfsQueueTail] = candidateX;
                this->heatMapYArray[this->bfsQueueTail] = candidateY;
                ++this->bfsQueueTail;
                if ((int)this->bfsQueueTail >= 6400) {
                    this->bfsQueueTail = 0;
                }
            }
            ++this->bfsQueueHead;
            if ((int)this->bfsQueueHead >= 6400) {
                this->bfsQueueHead = 0;
            }
        }
    }

}
}
