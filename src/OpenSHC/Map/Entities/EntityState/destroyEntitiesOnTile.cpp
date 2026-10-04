#include "../../../Map.func.hpp"
#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using Map::Entities::EntityType;

        // FUNCTION: STRONGHOLDCRUSADER 0x004019D0
        void EntityState::destroyEntitiesOnTile(int tile)
        {
            EntityTypeShort EVar1;
            Entity* pEVar2;
            int iVar2;
            if (((DAT_TileMapState::instance.MiscDisplayLayer[tile] & 0x1000) != 0)
                && (iVar2 = 1, 1 < this->maxEntityCount)) {
                pEVar2 = &this->entityArray[1];
                do {
                    if (((pEVar2->logicalState == 2)
                            && ((((EVar1 = pEVar2->entityType,
                                      EVar1 == Map::Entities::ET_FLAG_1
                                          || (EVar1 == Map::Entities::ET_FLAG_4))
                                     || (EVar1 == Map::Entities::ET_FLAG_2))
                                || (((EVar1 == Map::Entities::ET_FLAG_3
                                         || (EVar1 == Map::Entities::ET_BRAZIER))
                                    || (EVar1 == Map::Entities::ET_HEADS_ON_SPIKES))))))
                        && (pEVar2->tile == tile)) {
                        pEVar2->logicalState = 3;
                        DAT_TileMapState::instance.MiscDisplayLayer[tile]
                            = DAT_TileMapState::instance.MiscDisplayLayer[tile] & 0xefff;
                    }
                    iVar2 = iVar2 + 1;
                    pEVar2 = pEVar2 + 0x74;
                } while (iVar2 < this->maxEntityCount);
            }
        }

    }
}
}
