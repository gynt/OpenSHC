#include "../../../Map.func.hpp"
#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using OpenSHC::Map::Entities::EntityType;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:56:35.138000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00401620
        void EntityState::recountActiveFires()
        {
            Entity* psVar1;
            int iVar1;
            iVar1 = 1;
            this->fireCount = 0;
            if (1 < this->maxEntityCount) {
                psVar1 = &this->entityArray[1];
                do {
                    if (((psVar1->logicalState != 0) && (psVar1->logicalState == 2))
                        && (psVar1->entityType == OpenSHC::Map::Entities::ET_FIRE)) {
                        DAT_TileMapState::instance.OccupancyLayer[psVar1->tile]
                            = DAT_TileMapState::instance.OccupancyLayer[psVar1->tile]
                            | '\x01' << ((char)psVar1->owner - 1U & 0x1f);
                        this->fireCount = this->fireCount + 1;
                    }
                    iVar1 = iVar1 + 1;
                    psVar1 = psVar1 + 0x74;
                } while (iVar1 < this->maxEntityCount);
            }
        }

    }
}
}
