#include "../../Map.func.hpp"
#include "../LandscapeState.func.hpp"

#include "OpenSHC/Globals/DAT_00ed31a0.hpp"
#include "OpenSHC/Globals/DAT_CurrentTreeID.hpp"

namespace OpenSHC {
namespace Map {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F20E0
    void LandscapeState::setCurrentTimeOnSomeTrees()
    {
        short sVar1;
        DAT_00ed31a0::instance = timeGetTime();
        DAT_CurrentTreeID::instance = 1;
        do {
            sVar1 = this->trees[DAT_CurrentTreeID::instance].state;
            if ((sVar1 != 0) && (sVar1 != 3)) {
                this->trees[DAT_CurrentTreeID::instance].field8_0x14 = DAT_00ed31a0::instance;
            }
            DAT_CurrentTreeID::instance = DAT_CurrentTreeID::instance + 1;
        } while (DAT_CurrentTreeID::instance < 2000);
    }

}
}
