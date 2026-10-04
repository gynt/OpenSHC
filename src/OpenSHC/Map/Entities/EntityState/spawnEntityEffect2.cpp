#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Entities/EntityState.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x004082A0
        uint EntityState::spawnEntityEffect2(
            undefined4 microX, undefined4 microY, undefined4 height, undefined4 entityType, int gmLookupValue)
        {
            uint uVar1;
            dword dVar2;
            short* psVar3;
            uint entityID;
            entityID = this->every10Ticks;
            if (this->every10Ticks < 3000) {
                psVar3 = &this->entityArray[this->every10Ticks].logicalState;
                do {
                    if (*psVar3 == 0)
                        break;
                    if (0xbb6 < (int)entityID) {
                        return 0;
                    }
                    entityID = entityID + 1;
                    psVar3 = psVar3 + 0x74;
                } while ((int)entityID < 3000);
            }
            if (this->maxEntityCount <= (int)entityID) {
                this->maxEntityCount = entityID + 1;
            }
            this->every10Ticks = entityID;
            this->entityArray[entityID].uid = DAT_GameCore::instance.uniqueGameObjectTracker;
            dVar2 = DAT_GameCore::instance.mapTimeInTicks;
            DAT_GameCore::instance.uniqueGameObjectTracker = DAT_GameCore::instance.uniqueGameObjectTracker + 1;
            this->entityArray[entityID].microX = (short)microX;
            this->entityArray[entityID].field21_0x34 = dVar2;
            this->entityArray[entityID].microY = (short)microY;
            this->entityArray[entityID].height = (short)height;
            this->entityArray[entityID].logicalState = 5;
            this->entityArray[entityID].colorUnk = 0;
            MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::setEntityParameters, this)(
                entityID, (undefined4)((int)(entityType)), gmLookupValue);
            this->entityArray[entityID].field7_0x12 = 0;
            this->entityArray[entityID].unknownAnimationFrameRelated = 0;
            this->entityArray[entityID].unkMinusOne = 0;
            MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::processEntityHitBuildingOrUnit, this)(entityID);
            MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::calculateEntityDrawOffset, this)(entityID);
            uVar1 = DAT_CurrentEntityID::instance;
            /*
              what is the point of this mov ecx?
             */
            DAT_CurrentEntityID::instance = entityID;
            ((void (*)())
                    DAT_EntityDefinedData::instance.EntityCallbacks[(short)this->entityArray[entityID].entityType])();
            DAT_CurrentEntityID::instance = uVar1;
            return entityID;
        }

    }
}
}
