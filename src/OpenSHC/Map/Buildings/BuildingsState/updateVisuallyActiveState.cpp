#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00410290
        void BuildingsState::updateVisuallyActiveState(int buildingID)
        {
            if (this->buildings[buildingID].buildingIsVisuallyActive != 0) {
                if (this->buildings[buildingID].overlayFadeStep >= 5) {
                    return;
                }
                if (this->buildings[buildingID].overlayFadeStep == 0) {
                    this->buildings[buildingID].overlayFadeStep = 1;
                    return;
                }
                this->buildings[buildingID].overlayFadeStep += this->isFirstTickInLoop;
                return;
            }

            if (this->buildings[buildingID].overlayFadeStep > 0) {
                if (this->buildings[buildingID].overlayFadeStep == 5) {
                    this->buildings[buildingID].overlayFadeStep = 4;
                } else {
                    this->buildings[buildingID].overlayFadeStep -= this->isFirstTickInLoop;
                }
            }
            this->buildings[buildingID].buildingIsVisuallyActive
                = this->buildings[buildingID].overlayFadeStep != 0;
        }

    }
}
}
