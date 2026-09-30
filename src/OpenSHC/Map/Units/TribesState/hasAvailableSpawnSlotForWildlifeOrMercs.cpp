#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Game::GameMode;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00523520
        undefined4 TribesState::hasAvailableSpawnSlotForWildlifeOrMercs()
        {
            int iVar1;
            uint uVar2;
            uint uVar3;
            bool bVar4;
            if ((DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY)
                && (iVar1 = 0, DAT_GameState::instance.mapAndTime.field3166_0x277c < 0xa0)) {
                do {
                    if (iVar1 < 4) {
                        uVar3 = (uint)DAT_GameState::instance.mapAndTime.rabbitSpawnXY[iVar1][0];
                        uVar2 = (uint)DAT_GameState::instance.mapAndTime.rabbitSpawnXY[iVar1][1];
                        if ((uVar3 < 400) && (uVar2 < 400)) {
                            bVar4 = *(char*)(uVar2 * 400 + 0x21aec98 + uVar3) == '\0';
                            goto LAB_00523574;
                        }
                    } else {
                        bVar4 = DAT_GameState::instance.mapAndTime.mercRecruitable[iVar1 + 4] == 0;
                    LAB_00523574:
                        if (!bVar4) {
                            return (undefined4)(1);
                        }
                    }
                    iVar1 = iVar1 + 1;
                } while (iVar1 < 0xc);
            }
            return (undefined4)(0);
        }

    }
}
}
