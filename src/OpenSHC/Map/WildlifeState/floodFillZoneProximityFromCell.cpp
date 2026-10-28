#include "OpenSHC/Map/WildlifeState.func.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    // BFS over the 40x40 grid writing zoneProximity (+0x68). A dequeued value <= 1 ends the fill (signed jle
    // 0x52D7B4); neighbours need unsigned bounds (ja 0x27), validTileCount > 0, unclaimedArea <= 10 (signed jg
    // 0x52D7F2) and a lower current value (signed jge 0x52D7F7). The queue indices are undefined4, so they are cast to
    // int for the signed wrap compares (jl 0x640).
    // FUNCTION: STRONGHOLDCRUSADER 0x0052D720
    void WildlifeState::floodFillZoneProximityFromCell(int cellX, int cellY, int strength)
    {
        this->floodQueueTail = 1;
        this->floodCurrentValue = 1;
        this->floodQueueX[0] = (short)cellX;
        this->floodQueueY[0] = (short)cellY;
        this->floodQueueHead = 0;
        this->grid[cellX][cellY].zoneProximity = strength;
        while (this->floodQueueHead != this->floodQueueTail) {
            cellX = this->floodQueueX[this->floodQueueHead];
            cellY = this->floodQueueY[this->floodQueueHead];
            this->floodCurrentValue = this->grid[cellX][cellY].zoneProximity;
            if ((int)this->floodCurrentValue <= 1) {
                return;
            }
            int const nextValue = this->floodCurrentValue - 1;
            for (int dir = 0; dir < 8; dir++) {
                uint const x = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[dir].int_.xOffset + cellX;
                uint const y = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[dir].int_.yOffset + cellY;
                if (x <= 39 && y <= 39 && this->grid[x][y].validTileCount > 0 && this->grid[x][y].unclaimedArea <= 10
                    && this->grid[x][y].zoneProximity < nextValue) {
                    this->grid[x][y].zoneProximity = nextValue;
                    this->floodQueueX[this->floodQueueTail] = (short)x;
                    this->floodQueueY[this->floodQueueTail] = (short)y;
                    this->floodQueueTail++;
                    if ((int)this->floodQueueTail >= 0x640) {
                        this->floodQueueTail = 0;
                    }
                }
            }
            this->floodQueueHead++;
            if ((int)this->floodQueueHead >= 0x640) {
                this->floodQueueHead = 0;
            }
        }
    }

}
}
