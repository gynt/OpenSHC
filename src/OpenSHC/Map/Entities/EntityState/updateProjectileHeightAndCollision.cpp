#include "../EntityState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x004081E0
        void EntityState::updateProjectileHeightAndCollision(
            uint entityID, undefined4 heightDelta, int pitchAngle, int skipCollision)
        {
            short newHeight = this->entityArray[entityID].startingHeight + (short)heightDelta;
            this->entityArray[entityID].height = newHeight;
            if (newHeight <= 2 && skipCollision == 0) {
                MACRO_CALL_MEMBER(EntityState_Func::unlinkEntityFromTile, this)(entityID);
                MACRO_CALL_MEMBER(EntityState_Func::processEntityHitBuildingOrUnit, this)(entityID);
            }
            newHeight = this->entityArray[entityID].height;
            if (newHeight > 10000) {
                MACRO_CALL_MEMBER(EntityState_Func::markEntityDestroyed, this)(entityID);
                return;
            }
            this->entityArray[entityID].pitchFrameIndex
                = (short)MACRO_CALL_MEMBER(EntityState_Func::angleToRotationFrameIndex, this)(pitchAngle);
            this->entityArray[entityID].height_2 = newHeight;
        }

    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
