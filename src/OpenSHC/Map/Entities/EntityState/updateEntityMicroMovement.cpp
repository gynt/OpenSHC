#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Entities/EntityType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00402AE0
        void EntityState::updateEntityMicroMovement(int entityID)
        {
            if (this->entityArray[entityID].entityType == OpenSHC::Map::Entities::ET_SEAGULL
                && this->entityArray[entityID].targetZ == 0
                && this->entityArray[entityID].microX == this->entityArray[entityID].targetX
                && this->entityArray[entityID].microY == this->entityArray[entityID].targetY) {
                return;
            }
            short lineError;
            switch (this->entityArray[entityID].lineStepMode) {
            case 0:
                return;
            case 2:
                this->entityArray[entityID].microX += this->entityArray[entityID].stepX;
                return;
            case 1:
                this->entityArray[entityID].microY += this->entityArray[entityID].stepY;
                return;
            case 4:
                lineError = this->entityArray[entityID].lineStepError;
                this->entityArray[entityID].microX += this->entityArray[entityID].stepX;
                if (lineError > 0) {
                    this->entityArray[entityID].microY += this->entityArray[entityID].stepY;
                    this->entityArray[entityID].lineStepError = this->entityArray[entityID].lineStepIncMajor + lineError;
                    return;
                }
                break;
            case 3:
                lineError = this->entityArray[entityID].lineStepError;
                if (lineError > 0) {
                    this->entityArray[entityID].microX += this->entityArray[entityID].stepX;
                    this->entityArray[entityID].microY += this->entityArray[entityID].stepY;
                    this->entityArray[entityID].lineStepError = this->entityArray[entityID].lineStepIncMajor + lineError;
                    return;
                }
                this->entityArray[entityID].microY += this->entityArray[entityID].stepY;
                break;
            default:
                return;
            }
            this->entityArray[entityID].lineStepError = this->entityArray[entityID].lineStepIncMinor + lineError;
        }

    }
}
}
