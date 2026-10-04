#include "../../../Map.func.hpp"
#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Entities/EntityType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using Map::Entities::EntityType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00402AE0
        void EntityState::updateEntityMicroMovement(int param_1)
        {
            short* psVar1;
            short sVar2;
            if ((((this->entityArray[param_1].entityType != Map::Entities::ET_SEAGULLUnk)
                     || (this->entityArray[param_1].targetZ != 0))
                    || (this->entityArray[param_1].microX != this->entityArray[param_1].targetX))
                || (this->entityArray[param_1].microY != this->entityArray[param_1].targetY)) {
                switch (this->entityArray[param_1].field50_0x74) {
                default:
                    return;
                case 1:
                    this->entityArray[param_1].microY
                        = this->entityArray[param_1].microY + this->entityArray[param_1].someMicroY;
                    return;
                case 2:
                    this->entityArray[param_1].microX
                        = this->entityArray[param_1].microX + this->entityArray[param_1].someMicroX;
                    return;
                case 3:
                    sVar2 = this->entityArray[param_1].field49_0x72;
                    if (0 < sVar2) {
                        this->entityArray[param_1].microX
                            = this->entityArray[param_1].microX + this->entityArray[param_1].someMicroX;
                        this->entityArray[param_1].microY
                            = this->entityArray[param_1].microY + this->entityArray[param_1].someMicroY;
                        this->entityArray[param_1].field49_0x72 = this->entityArray[param_1].field48_0x70 + sVar2;
                    }
                    this->entityArray[param_1].microY
                        = this->entityArray[param_1].microY + this->entityArray[param_1].someMicroY;
                    break;
                case 4:
                    sVar2 = this->entityArray[param_1].field49_0x72;
                    this->entityArray[param_1].microX
                        = this->entityArray[param_1].microX + this->entityArray[param_1].someMicroX;
                    if (0 < sVar2) {
                        this->entityArray[param_1].microY
                            = this->entityArray[param_1].microY + this->entityArray[param_1].someMicroY;
                        this->entityArray[param_1].field49_0x72 = this->entityArray[param_1].field48_0x70 + sVar2;
                    }
                }
                this->entityArray[param_1].field49_0x72 = this->entityArray[param_1].field47_0x6e + sVar2;
            }
        }

    }
}
}
