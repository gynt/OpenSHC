#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040CB90
        undefined4 BuildingsState::findNextWheatFarmWorkTile(int param_1)
        {
            // The damage layer holds the growth stage of the wheat on the field tiles
            for (int i = 0; i < 36; ++i) {
                int tile = this->buildings[param_1].tileRefs[i];
                int stage = (char)DAT_TileMapState::instance.DamageOrCropStageLayer[tile];
                DAT_BuildingsState::instance.farmerDestinationTile = tile;
                if (*(short*)&this->buildings[param_1].farmerNextWorkState == 6) {
                    if (stage >= 11 && stage < 101) {
                        return 1;
                    }
                } else if (*(short*)&this->buildings[param_1].farmerNextWorkState == 8) {
                    if (stage == 121) {
                        return 1;
                    }
                } else if (*(short*)&this->buildings[param_1].farmerNextWorkState == 3) {
                    if (stage == 0 || stage == 120 || (stage >= 101 && stage < 120)) {
                        return 1;
                    }
                } else if (*(short*)&this->buildings[param_1].farmerNextWorkState == 5) {
                    if (stage >= 1 && stage < 2) {
                        return 1;
                    }
                } else {
                    return 0;
                }
            }
            return 0;
        }

    }
}
}
