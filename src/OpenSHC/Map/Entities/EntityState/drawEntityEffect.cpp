#include "../../../Map.func.hpp"
#include "../EntityState.func.hpp"

#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        /*
          Two dimensional enum graphic[type1][type2]   decompilerscript: committed: 2025-01-30 21:56:35.138000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00401380
        void EntityState::drawEntityEffect(int entityID, undefined4 entityType, int graphicType1, int graphicType2)
        {
            short sVar1;
            this->entityArray[entityID].graphicType2 = graphicType2;
            this->entityArray[entityID].entityType = (EntityTypeShort)entityType;
            sVar1 = (short)graphicType1;
            this->entityArray[entityID].gmID = sVar1;
            this->entityArray[entityID].originX
                = (short)DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[sVar1].originX;
            this->entityArray[entityID].originY
                = (short)DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[sVar1].originY;
            this->entityArray[entityID].unkOne_1 = (short)DAT_EntityDefinedData::instance.field50_0x8b0;
            this->entityArray[entityID].unkThree_1 = (short)DAT_EntityDefinedData::instance.field47_0x7f8;
            if (graphicType1 == 0x87) {
                this->entityArray[entityID].unkOne_1 = 1;
                this->entityArray[entityID].unkThree_1 = 3;
            }
        }

    }
}
}
