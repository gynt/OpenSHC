#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040BA10
        void BuildingsState::setupBuildingEntrancesOffset(int buildingSize, int nudge, int try_, int offset)
        {
            // Offset of the try_-th tile around a building of the given size
            switch (buildingSize) {
            case 1:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.entranceOffsetsSize1[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.entranceOffsetsSize1[try_].y;
                break;
            case 2:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.entranceOffsetsSize2[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.entranceOffsetsSize2[try_].y;
                break;
            case 3:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.entranceOffsetsSize3[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.entranceOffsetsSize3[try_].y;
                break;
            case 4:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.entranceOffsetsSize4[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.entranceOffsetsSize4[try_].y;
                break;
            case 5:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.entranceOffsetsSize5[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.entranceOffsetsSize5[try_].y;
                break;
            case 6:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.entranceOffsetsSize6[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.entranceOffsetsSize6[try_].y;
                break;
            case 7:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.entranceOffsetsSize7[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.entranceOffsetsSize7[try_].y;
                break;
            case 8:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.entranceOffsetsSize8[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.entranceOffsetsSize8[try_].y;
                break;
            case 9:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.entranceOffsetsSize9[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.entranceOffsetsSize9[try_].y;
                break;
            case 10:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.entranceOffsetsSize10[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.entranceOffsetsSize10[try_].y;
                break;
            case 11:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.entranceOffsetsSize11[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.entranceOffsetsSize11[try_].y;
                break;
            case 12:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.entranceOffsetsSize12[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.entranceOffsetsSize12[try_].y;
                break;
            case 13:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.entranceOffsetsSize13[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.entranceOffsetsSize13[try_].y;
                break;
            default:
                this->DAT_TempYOffset = 0;
                this->DAT_TempXOffset = 0;
                break;
            }

            // Move the tile away from the side of the building it belongs to
            switch (try_ / buildingSize * 2) {
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
            if (this->DAT_TempXOffset < buildingSize && this->DAT_TempYOffset < buildingSize) {
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
