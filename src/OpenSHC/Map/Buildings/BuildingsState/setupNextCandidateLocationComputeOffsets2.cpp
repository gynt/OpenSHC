#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040BC40
        void BuildingsState::setupNextCandidateLocationComputeOffsets2(int size, int nudge, int try_, int offset)
        {
            // Offset of the try_-th tile around a building of the given size
            switch (size) {
            case 1:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.candidateOffsetsSize1[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.candidateOffsetsSize1[try_].y;
                break;
            case 2:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.candidateOffsetsSize2[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.candidateOffsetsSize2[try_].y;
                break;
            case 3:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.candidateOffsetsSize3[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.candidateOffsetsSize3[try_].y;
                break;
            case 4:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.candidateOffsetsSize4[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.candidateOffsetsSize4[try_].y;
                break;
            case 5:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.candidateOffsetsSize5[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.candidateOffsetsSize5[try_].y;
                break;
            case 6:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.candidateOffsetsSize6[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.candidateOffsetsSize6[try_].y;
                break;
            case 7:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.candidateOffsetsSize7[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.candidateOffsetsSize7[try_].y;
                break;
            case 8:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.candidateOffsetsSize8[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.candidateOffsetsSize8[try_].y;
                break;
            case 9:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.candidateOffsetsSize9[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.candidateOffsetsSize9[try_].y;
                break;
            case 10:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.candidateOffsetsSize10[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.candidateOffsetsSize10[try_].y;
                break;
            case 11:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.candidateOffsetsSize11[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.candidateOffsetsSize11[try_].y;
                break;
            case 12:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.candidateOffsetsSize12[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.candidateOffsetsSize12[try_].y;
                break;
            case 13:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.candidateOffsetsSize13[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.candidateOffsetsSize13[try_].y;
                break;
            }

            // Move the tile away from the side of the building it belongs to
            switch (try_ / size * 2) {
            case 0:
                this->DAT_TempYOffset -= offset;
                break;
            case 4:
                this->DAT_TempYOffset += offset;
                break;
            case 2:
                this->DAT_TempXOffset += offset;
                break;
            case 6:
                this->DAT_TempXOffset -= offset;
                break;
            }
            if (this->DAT_TempXOffset < size && this->DAT_TempYOffset < size) {
                if (this->DAT_TempXOffset <= -1) {
                    this->DAT_TempXOffset = this->DAT_TempXOffset - nudge + 1;
                    return;
                }
                if (this->DAT_TempYOffset <= -1) {
                    this->DAT_TempYOffset = this->DAT_TempYOffset - nudge + 1;
                }
            }
        }

    }
}
}
