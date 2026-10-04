#include "../Helpers.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00465040
    BOOLEnum Helpers::HasEnoughGold(int param_1)
    {
        int iVar1 = 0;
        if (param_1 == 0x1e) {
            iVar1 = 0x1e;
        } else if (param_1 == 0x1d) {
            iVar1 = 4;
        } else if (param_1 == 0x25) {
            /*
              cathedral/monks
             */
            iVar1 = 10;
        }
        return (
            uint)(iVar1 <= DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                      .currentResources[0xf]);
    }

}
}
