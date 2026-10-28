#include "OpenSHC/Map/WildlifeState.func.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    // BFS over the 40x40 grid writing dangerInfluence (+0x34). The start sets floodCurrentValue = 1 as the original does.
    // A dequeued value <= 1 ends the fill (signed jle 0x52C604); neighbours are tested with unsigned bounds (ja 0x27),
    // validTileCount > 0 and a lower current value (signed jge 0x52C641). Queue indices wrap at 0x640 (signed jl).
    // The three queue fields are declared undefined4 (unsigned), so they are cast to int for the signed compares.
    // FUNCTION: STRONGHOLDCRUSADER 0x0052C570
    void WildlifeState::floodFillField13FromCell(int seedX, int seedY, int seedValue)
    {
        this->floodQueueTail = 1;
        this->floodCurrentValue = 1;
        this->floodQueueX[0] = (short)seedX;
        this->floodQueueY[0] = (short)seedY;
        this->floodQueueHead = 0;
        this->grid[seedX][seedY].dangerInfluence = seedValue;
        while (this->floodQueueHead != this->floodQueueTail) {
            seedX = this->floodQueueX[this->floodQueueHead];
            seedY = this->floodQueueY[this->floodQueueHead];
            this->floodCurrentValue = this->grid[seedX][seedY].dangerInfluence;
            if ((int)this->floodCurrentValue <= 1) {
                return;
            }
            int const nextValue = this->floodCurrentValue - 1;
            for (int dir = 0; dir < 8; dir++) {
                unsigned int const x = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[dir].int_.xOffset + seedX;
                unsigned int const y = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[dir].int_.yOffset + seedY;
                if (x <= 39 && y <= 39 && this->grid[x][y].validTileCount > 0 && this->grid[x][y].dangerInfluence < nextValue) {
                    this->grid[x][y].dangerInfluence = nextValue;
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
