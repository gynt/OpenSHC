#include "OpenSHC/Map/WildlifeState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {

    // BFS from the cell of the active attack signpost (tile / 10, signed idiv by 10) writing the step distance into
    // routeBfsValue (start = 1). A dequeued distance >= 100 ends the fill (signed jge 0x52DAD7). Neighbours need
    // unsigned bounds (ja 0x27), validTileCount > 0, the start cell's dominantPathAreaId, zoneProximity == 0 and
    // routeBfsValue == 0; each entered cell also gets reachedFromSignpost incremented. The original leaves the last
    // compared value in eax, the only caller (updateNofFpoints, 0x52E18B) does not read it.
    // FUNCTION: STRONGHOLDCRUSADER 0x0052D9D0
    void WildlifeState::floodFillCasDisFromSignpost()
    {
        int cellX = DAT_GameState::instance.mapAndTime
                        .signpostEntryData[DAT_TroopValueState::instance.attackInfo.activeAttackSignpostIndex]
                        .x
            / 10;
        int cellY = DAT_GameState::instance.mapAndTime
                        .signpostEntryData[DAT_TroopValueState::instance.attackInfo.activeAttackSignpostIndex]
                        .y
            / 10;
        this->floodCurrentValue = 1;
        this->floodQueueHead = 0;
        this->floodQueueTail = 1;
        for (int y = 0; y < 40; y++) {
            for (int x = 0; x < 40; x++) {
                this->grid[x][y].routeBfsValue = 0;
                this->grid[x][y].reachedFromSignpost = 0;
            }
        }
        this->floodQueueY[0] = (short)cellY;
        this->floodQueueX[0] = (short)cellX;
        int const areaID = this->grid[cellX][cellY].dominantPathAreaId;
        this->grid[cellX][cellY].routeBfsValue = 1;
        while (this->floodQueueHead != this->floodQueueTail) {
            cellX = this->floodQueueX[this->floodQueueHead];
            cellY = this->floodQueueY[this->floodQueueHead];
            this->floodCurrentValue = this->grid[cellX][cellY].routeBfsValue;
            if ((int)this->floodCurrentValue >= 100) {
                return;
            }
            int const nextValue = this->floodCurrentValue + 1;
            for (int dir = 0; dir < 8; dir++) {
                uint const x = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[dir].int_.xOffset + cellX;
                uint const y = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[dir].int_.yOffset + cellY;
                if (x <= 39 && y <= 39 && this->grid[x][y].validTileCount > 0
                    && areaID == this->grid[x][y].dominantPathAreaId && this->grid[x][y].zoneProximity == 0
                    && this->grid[x][y].routeBfsValue == 0) {
                    this->grid[x][y].routeBfsValue = nextValue;
                    this->grid[x][y].reachedFromSignpost++;
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
