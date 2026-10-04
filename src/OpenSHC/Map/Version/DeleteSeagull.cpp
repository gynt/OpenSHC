#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Entities/ExtraEntityInfo.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {

    using Map::Entities::EntityType;
    using Map::Entities::ExtraEntityInfo;

    // FUNCTION: STRONGHOLDCRUSADER 0x00404A70
    void Version::DeleteSeagull()
    {
        ExtraEntityInfo* destination;
        DAT_CurrentEntityID::instance = 1;
        do {
            if ((DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState == 2)
                && (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].entityType
                    == Map::Entities::ET_SEAGULLUnk)) {
                MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::deleteEntity, DAT_EntityState::ptr)(
                    DAT_CurrentEntityID::instance);
            }
            DAT_CurrentEntityID::instance = DAT_CurrentEntityID::instance + 1;
        } while ((int)DAT_CurrentEntityID::instance < 3000);
        destination = DAT_EntityState::instance.seagullArray;
        do {
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                100, '\0', (void*)((int)(destination)));
            destination = destination + 1;
        } while ((int)destination < 0x23fc8e4);
    }

}
}
