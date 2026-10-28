#include "../EntityState.func.hpp"

#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x004012F0
        void EntityState::setEntityParameters(int entityID, undefined4 entityType, int gmLookupValue)
        {
            this->entityArray[entityID].entityType = entityType;
            this->entityArray[entityID].gmLookupValue = gmLookupValue;
            this->entityArray[entityID].gmID = DAT_EntityDefinedData::instance.gmIDPerGmLookup[gmLookupValue];
            this->entityArray[entityID].graphicType2RelatedOffset
                = DAT_EntityDefinedData::instance.graphicOffsetPerGmLookup[gmLookupValue];
            this->entityArray[entityID].originX = DAT_TextureRenderCoreObject::instance
                                                      .gmFileHeaderColorpaletteArray[this->entityArray[entityID].gmID]
                                                      .originX;
            this->entityArray[entityID].originY = DAT_TextureRenderCoreObject::instance
                                                      .gmFileHeaderColorpaletteArray[this->entityArray[entityID].gmID]
                                                      .originY;
            this->entityArray[entityID].ticksPerAnimFrame
                = DAT_EntityDefinedData::instance.frameTicksPerGmLookup[gmLookupValue];
            this->entityArray[entityID].animFrameCount
                = DAT_EntityDefinedData::instance.frameCountPerGmLookup[gmLookupValue];
            if (gmLookupValue == 1) {
                this->entityArray[entityID].animFrameCount = 5;
                this->entityArray[entityID].ticksPerAnimFrame = 3;
                this->entityArray[entityID].fadeLevel = 16;
            }
        }

    }
}
}
