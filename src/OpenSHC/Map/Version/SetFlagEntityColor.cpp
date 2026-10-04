#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Map/Entities/Entity.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Entities/EntityTypeShort.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    using Map::Entities::EntityType;
    using Map::Entities::Entity;
    using Map::Entities::EntityTypeShort;

    // FUNCTION: STRONGHOLDCRUSADER 0x004038B0
    void Version::SetFlagEntityColor()
    {
        EntityTypeShort EVar1;
        Entity* pEVar2;
        pEVar2 = &DAT_EntityState::instance.entityArray[1];
        DAT_CurrentEntityID::instance = 3000;
        do {
            if ((pEVar2->logicalState == 2)
                && ((((EVar1 = pEVar2->entityType,
                          EVar1 == Map::Entities::ET_FLAG_1 || (EVar1 == Map::Entities::ET_FLAG_4))
                         || (EVar1 == Map::Entities::ET_FLAG_2))
                    || (EVar1 == Map::Entities::ET_FLAG_3)))) {
                pEVar2->colorUnk = (int)pEVar2->owner;
            }
            pEVar2 = pEVar2 + 0x74;
        } while ((int)pEVar2 < 0x23fa1fe);
    }

}
}
