#include "../Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TroopDefinedData.hpp"

namespace OpenSHC {
namespace UI {

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00464E80
    int Helpers::GetUnitRecruitPermission(int param_1)
    {
        if (*(int*)(DAT_GameState::instance.mapAndTime.playerIsAlive + param_1 * 2 + 0x16) == 0) {
            return 2;
        }
        if (DAT_GameState::instance.mapAndTime.armySizeLimit
            <= DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].count_2
                + DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .armySize) {
            return 3;
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .currentResources[0xf]
            < DAT_TroopDefinedData::instance.field279_0x210[param_1]) {
            /*
              not enough gold
             */
            return 0;
        }
        int iVar1 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .availablePeasantsOrHousedPeasants;
        int iVar2 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].count;
        return ((iVar1 != iVar2 && -1 < iVar1 - iVar2) - 1 & 3) + 1;
    }

}
}
