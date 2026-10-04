#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Entities/EntityState.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        /*
          Two dimensional enum graphic[type1][type2]   decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004083A0
        uint EntityState::spawnEntityEffect1(
            short x, short y, undefined4 height, undefined4 entityType, int graphicType1, int graphicType2)
        {
            uint uVar1;
            short* psVar2;
            uint entityID;
            entityID = this->every10Ticks;
            if ((int)this->every10Ticks < 3000) {
                psVar2 = &this->entityArray[this->every10Ticks].logicalState;
                do {
                    if (*psVar2 == 0)
                        break;
                    if (0xbb6 < (int)entityID) {
                        return 0;
                    }
                    entityID = entityID + 1;
                    psVar2 = psVar2 + 0x74;
                } while ((int)entityID < 3000);
            }
            if (this->maxEntityCount <= (int)entityID) {
                this->maxEntityCount = entityID + 1;
            }
            this->every10Ticks = entityID;
            this->entityArray[entityID].uid = DAT_GameCore::instance.uniqueGameObjectTracker;
            DAT_GameCore::instance.uniqueGameObjectTracker = DAT_GameCore::instance.uniqueGameObjectTracker + 1;
            this->entityArray[entityID].field21_0x34 = DAT_GameCore::instance.mapTimeInTicks;
            this->entityArray[entityID].microX = x;
            this->entityArray[entityID].microY = y;
            this->entityArray[entityID].height = (short)height;
            this->entityArray[entityID].logicalState = 5;
            this->entityArray[entityID].colorUnk = 0;
            MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::drawEntityEffect, this)(
                entityID, (undefined4)((int)(entityType)), graphicType1, graphicType2);
            this->entityArray[entityID].field7_0x12 = 0;
            this->entityArray[entityID].unknownAnimationFrameRelated = 0;
            this->entityArray[entityID].unkMinusOne = 0;
            MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::processEntityHitBuildingOrUnit, this)(entityID);
            MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::calculateEntityDrawOffset, this)(entityID);
            uVar1 = DAT_CurrentEntityID::instance;
            DAT_CurrentEntityID::instance = entityID;
            ((void (*)())
                    DAT_EntityDefinedData::instance.EntityCallbacks[(short)this->entityArray[entityID].entityType])();
            DAT_CurrentEntityID::instance = uVar1;
            return entityID;
        }

    }
}
}
