#include "../../Map.func.hpp"
#include "../WildlifeState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      BFS from the current attack signpost position, restricted to the same separateAreaID. Returns the   casDisRelated2
      depth (1-99) at which it first encounters a cell with unknownNonZero01 set,   indicating the BFS distance to the
      nearest wildlife habitat or patrol marker from the signpost.   Returns 0 if none found within 99 steps or the
      queue is exhausted.      renamed by: Claude Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0052DD20
    int WildlifeState::getDistanceToNearestUnknownNonZero01FromSignpost()
    {
        uint _newZoneX;
        int* piVar1;
        uint _newZoneY;
        int* piVar2;
        int iVar3;
        int iVar4;
        int _area;
        short _candidateZoneX;
        short _candidateZoneY;
        int _zoneX;
        int _zoneY;
        _zoneX = DAT_GameState::instance.mapAndTime
                     .signpostEntryData[DAT_TroopValueState::instance.attackInfo.field128056_0x469d4]
                     .x
            / 10;
        this->DAT_X10_Array_Section1034[0] = (short)_zoneX;
        _zoneY = DAT_GameState::instance.mapAndTime
                     .signpostEntryData[DAT_TroopValueState::instance.attackInfo.field128056_0x469d4]
                     .y
            / 10;
        this->casDisRelated = 1;
        this->candidateIndex = 0;
        this->candidateIndex2 = 1;
        piVar2 = &this->grid[0][0].casDisRelated2;
        iVar3 = 0x28;
        do {
            iVar4 = 0x28;
            piVar1 = piVar2;
            do {
                *piVar1 = 0;
                piVar1 = piVar1 + 0x640;
                iVar4 = iVar4 + -1;
            } while (iVar4 != 0);
            piVar2 = piVar2 + 0x28;
            iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
        this->DAT_Y10_Array_Section1034[0] = (short)_zoneY;
        _area = this->grid[_zoneX][_zoneY].separateAreaID;
        this->grid[_zoneX][_zoneY].casDisRelated2 = 1;
        if (this->candidateIndex != this->candidateIndex2) {
            do {
                _candidateZoneX = this->DAT_X10_Array_Section1034[this->candidateIndex];
                _candidateZoneY = this->DAT_Y10_Array_Section1034[this->candidateIndex];
                this->casDisRelated = this->grid[_candidateZoneX][_candidateZoneY].casDisRelated2;
                if (99 < this->casDisRelated) {
                    return 0;
                }
                iVar3 = this->casDisRelated + 1;
                piVar2 = &DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[0].int_.yOffset;
                do {
                    _newZoneX = ((Point8IntXY*)(piVar2 + -1))->xOffset + (int)_candidateZoneX;
                    _newZoneY = *piVar2 + (int)_candidateZoneY;
                    if ((((_newZoneX < 0x28) && (_newZoneY < 0x28))
                            && (0 < this->grid[_newZoneX][_newZoneY].firstMember))
                        && (_area == this->grid[_newZoneX][_newZoneY].separateAreaID)) {
                        if (this->grid[_newZoneX][_newZoneY].unknownNonZero01 != 0) {
                            return (int)(this->casDisRelated);
                        }
                        if (this->grid[_newZoneX][_newZoneY].casDisRelated2 == 0) {
                            this->grid[_newZoneX][_newZoneY].casDisRelated2 = iVar3;
                            this->DAT_X10_Array_Section1034[this->candidateIndex2] = (short)_newZoneX;
                            this->DAT_Y10_Array_Section1034[this->candidateIndex2] = (short)_newZoneY;
                            this->candidateIndex2 = this->candidateIndex2 + 1;
                            if (1600 < this->candidateIndex2) {
                                this->candidateIndex2 = 0;
                            }
                        }
                    }
                    piVar2 = piVar2 + 2;
                } while ((int)piVar2 < 0xb4908c);
                this->candidateIndex = this->candidateIndex + 1;
                if (1600 < this->candidateIndex) {
                    this->candidateIndex = 0;
                }
            } while (this->candidateIndex != this->candidateIndex2);
        }
        return 0;
    }

}
}
