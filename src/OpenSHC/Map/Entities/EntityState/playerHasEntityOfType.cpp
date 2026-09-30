#include "../../../Map.func.hpp"
#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using OpenSHC::Map::Entities::EntityType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:56:35.138000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00401150
        BOOLEnum EntityState::playerHasEntityOfType(int playerID, EntityType entityType)
        {
            Entity* pEVar1;
            int iVar1;
            if (entityType == ((EntityType)0x28)) {
                if (DAT_GameState::instance.playerDataArray[playerID].someCount32 != 0) {
                    return TRUE;
                }
            } else if ((entityType == ((EntityType)0x29))
                && (DAT_GameState::instance.playerDataArray[playerID].someCount33 != 0)) {
                return TRUE;
            }
            iVar1 = 1;
            pEVar1 = &this->entityArray[1];
            while (((pEVar1->logicalState == 0 || ((int)(short)pEVar1->entityType != entityType))
                || (pEVar1->owner != playerID))) {
                iVar1 = iVar1 + 1;
                pEVar1 = pEVar1 + 0x74;
                if (25 < iVar1) {
                    return FALSE;
                }
            }
            return TRUE;
        }

    }
}
}
