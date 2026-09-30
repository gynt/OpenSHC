#include "../../../Map.func.hpp"
#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using OpenSHC::Map::Entities::EntityType;

        /*
          decompilerscript: committed: 2025-01-30 21:56:35.138000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004011D0
        void EntityState::setProjectileEntityValues2(int entityID, EntityType entityType)
        {
            short* psVar1;
            short sVar2;
            int iVar3;
            this->entityArray[entityID].entityType = (EntityTypeShort)entityType;
            this->entityArray[entityID].gmID = (short)DAT_EntityDefinedData::instance.EntityPropertyArray_1[entityType];
            this->entityArray[entityID].graphicType2RelatedOffset
                = (short)DAT_EntityDefinedData::instance.EntityPropertyArray_2[entityType];
            sVar2 = this->entityArray[entityID].gmID;
            this->entityArray[entityID].originX
                = (short)DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[sVar2].originX;
            this->entityArray[entityID].originY
                = (short)DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[sVar2].originY;
            this->entityArray[entityID].unkOne_1
                = (short)DAT_EntityDefinedData::instance.EntityPropertyArray_3[entityType];
            iVar3 = DAT_EntityDefinedData::instance.EntityArrayCurveTypeForProjectileType[entityType];
            if (((iVar3 == 0) || (iVar3 == 6)) || (iVar3 == 9)) {
                this->entityArray[entityID].velocityUnk
                    = (short)DAT_EntityDefinedData::instance.EntityArrayProjectileVelocityForProjectileType[entityType];
            } else {
                this->entityArray[entityID].startingAngle
                    = (short)DAT_EntityDefinedData::instance.EntityArrayProjectileVelocityForProjectileType[entityType];
            }
            this->entityArray[entityID]._elapsedTimeOrGravityAccumulator
                = DAT_EntityDefinedData::instance.field43_0x5c4[entityType];
            this->entityArray[entityID].field37_0x5a = (short)DAT_EntityDefinedData::instance.field6_0x270[entityType
                + (OpenSHC::Map::Entities::ET_MANGONEL | OpenSHC::Map::Entities::ET_ARROW_AND_DEFAULT)];
            this->entityArray[entityID].gmLookupValue
                = (short)DAT_EntityDefinedData::instance.EntityPropertyArray_3[entityType + ((EntityType)0x2e)];
            switch (entityType - OpenSHC::Map::Entities::ET_FLAG_1) {
            case OpenSHC::Map::Entities::ET_UNKNOWN:
            case OpenSHC::Map::Entities::ET_MANGONEL:
            case OpenSHC::Map::Entities::ET_MANGONEL | OpenSHC::Map::Entities::ET_ARROW_AND_DEFAULT:
                psVar1 = &this->entityArray[entityID].originX;
                *psVar1 = *psVar1 + -1;
                psVar1 = &this->entityArray[entityID].originY;
                *psVar1 = *psVar1 + -7;
                break;
            case OpenSHC::Map::Entities::ET_ARROW_AND_DEFAULT:
                psVar1 = &this->entityArray[entityID].originX;
                *psVar1 = *psVar1 + -1;
                psVar1 = &this->entityArray[entityID].originY;
                *psVar1 = *psVar1 + -2;
                return;
            case OpenSHC::Map::Entities::ET_CATAPULT:
                psVar1 = &this->entityArray[entityID].originX;
                *psVar1 = *psVar1 + 8;
                psVar1 = &this->entityArray[entityID].originY;
                *psVar1 = *psVar1 + -8;
                return;
            case OpenSHC::Map::Entities::ET_TREBUCHET:
                psVar1 = &this->entityArray[entityID].originX;
                *psVar1 = *psVar1 + 8;
                psVar1 = &this->entityArray[entityID].originY;
                *psVar1 = *psVar1 + -7;
            }
        }

    }
}
}
