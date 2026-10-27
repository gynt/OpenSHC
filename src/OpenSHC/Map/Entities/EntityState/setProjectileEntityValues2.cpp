#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using OpenSHC::Map::Entities::EntityType;

        // FUNCTION: STRONGHOLDCRUSADER 0x004011D0
        void EntityState::setProjectileEntityValues2(int entityID, EntityType entityType)
        {
            this->entityArray[entityID].entityType = entityType;
            this->entityArray[entityID].gmID = DAT_EntityDefinedData::instance.EntityPropertyArray_1[entityType];
            this->entityArray[entityID].graphicType2RelatedOffset
                = DAT_EntityDefinedData::instance.EntityPropertyArray_2[entityType];
            this->entityArray[entityID].originX = DAT_TextureRenderCoreObject::instance
                                                      .gmFileHeaderColorpaletteArray[this->entityArray[entityID].gmID]
                                                      .originX;
            this->entityArray[entityID].originY = DAT_TextureRenderCoreObject::instance
                                                      .gmFileHeaderColorpaletteArray[this->entityArray[entityID].gmID]
                                                      .originY;
            this->entityArray[entityID].ticksPerAnimFrame
                = DAT_EntityDefinedData::instance.EntityPropertyArray_3[entityType];
            int curveType = DAT_EntityDefinedData::instance.EntityArrayCurveTypeForProjectileType[entityType];
            if (curveType == 0 || curveType == 6 || curveType == 9) {
                this->entityArray[entityID].launchSpeedOrDriftPeriodY
                    = DAT_EntityDefinedData::instance.EntityArrayProjectileVelocityForProjectileType[entityType];
            } else {
                this->entityArray[entityID].moveDirOrDriftXOrLaunchPitch
                    = DAT_EntityDefinedData::instance.EntityArrayProjectileVelocityForProjectileType[entityType];
            }
            this->entityArray[entityID]._elapsedTimeOrGravityAccumulator
                = DAT_EntityDefinedData::instance.initialGravityAccumPerType[entityType];
            this->entityArray[entityID].projectileParam5a
                = DAT_EntityDefinedData::instance.projectileParamPerType[entityType];
            this->entityArray[entityID].gmLookupValue
                = DAT_EntityDefinedData::instance.losClearanceStepsPerType[entityType];
            switch (entityType) {
            case OpenSHC::Map::Entities::ET_FLAG_4:
                this->entityArray[entityID].originX += -1;
                this->entityArray[entityID].originY += -2;
                break;
            case OpenSHC::Map::Entities::ET_FLAG_2:
                this->entityArray[entityID].originX += 8;
                this->entityArray[entityID].originY += -8;
                break;
            case OpenSHC::Map::Entities::ET_FLAG_3:
                this->entityArray[entityID].originX += 8;
                this->entityArray[entityID].originY += -7;
                break;
            case OpenSHC::Map::Entities::ET_FLAG_1:
            case OpenSHC::Map::Entities::ET_BRAZIER:
            case OpenSHC::Map::Entities::ET_HEADS_ON_SPIKES:
                this->entityArray[entityID].originX += -1;
                this->entityArray[entityID].originY += -7;
                break;
            }
        }

    }
}
}
