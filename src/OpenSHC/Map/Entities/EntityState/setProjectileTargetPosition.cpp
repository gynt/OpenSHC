#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00405CF0
        void EntityState::setProjectileTargetPosition(
            int entityID, int x, int y, int height, int targetX, int targetY, int targetZ)
        {
            short _height;
            this->entityArray[entityID].targetZ = (short)targetZ;
            this->entityArray[entityID].targetY = (short)targetY;
            this->entityArray[entityID].microX = (short)x;
            this->entityArray[entityID].x_2 = (short)x;
            this->entityArray[entityID].microY = (short)y;
            this->entityArray[entityID].y_2 = (short)y;
            _height = (short)height;
            this->entityArray[entityID].height = _height;
            this->entityArray[entityID].startingHeight_2 = _height;
            this->entityArray[entityID].height_2 = _height;
            this->entityArray[entityID].startingHeight = _height;
            this->entityArray[entityID].targetX = (short)targetX;
            this->entityArray[entityID].heightDifference = targetZ - height;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::somethingWithProjectileDistance,
                DAT_DirectionAlgorithmState::ptr)(x, y, targetX, targetY);
            this->entityArray[entityID].orientation = DAT_DirectionAlgorithmState::instance.orientation;
            MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::initializeProjectileVelocities, this)(
                entityID, x, y, height, targetX, targetY, targetZ);
        }

    }
}
}
