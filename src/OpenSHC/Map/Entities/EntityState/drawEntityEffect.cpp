#include "../EntityState.func.hpp"

#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00401380
        void EntityState::drawEntityEffect(int entityID, undefined4 entityType, int graphicType1, int graphicType2)
        {
            this->entityArray[entityID].entityType = entityType;
            this->entityArray[entityID].graphicType2 = graphicType2;
            this->entityArray[entityID].gmID = graphicType1;
            this->entityArray[entityID].originX = DAT_TextureRenderCoreObject::instance
                                                      .gmFileHeaderColorpaletteArray[this->entityArray[entityID].gmID]
                                                      .originX;
            this->entityArray[entityID].originY = DAT_TextureRenderCoreObject::instance
                                                      .gmFileHeaderColorpaletteArray[this->entityArray[entityID].gmID]
                                                      .originY;
            this->entityArray[entityID].ticksPerAnimFrame = DAT_EntityDefinedData::instance.frameTicksPerGmLookup[3];
            this->entityArray[entityID].animFrameCount = DAT_EntityDefinedData::instance.frameCountPerGmLookup[3];
            if (graphicType1 == 0x87) {
                this->entityArray[entityID].ticksPerAnimFrame = 1;
                this->entityArray[entityID].animFrameCount = 3;
            }
        }

    }
}
}
