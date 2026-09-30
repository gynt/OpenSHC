#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Map/Entities/EntityState.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00408250
    void Version::UpgradeFirst25Entities()
    {
        uint entityID;
        DAT_CurrentEntityID::instance = 1;
        do {
            entityID = DAT_CurrentEntityID::instance;
            if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState == 2) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::removeEntityFromTileLinkedList,
                    DAT_EntityState::ptr)(DAT_CurrentEntityID::instance);
                MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::processEntityHitBuildingOrUnit,
                    DAT_EntityState::ptr)(entityID);
            }
            DAT_CurrentEntityID::instance = DAT_CurrentEntityID::instance + 1;
        } while ((int)DAT_CurrentEntityID::instance < 25);
    }

}
}
