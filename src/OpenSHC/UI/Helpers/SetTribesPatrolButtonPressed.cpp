#include "../Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace UI {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00434340
    void Helpers::SetTribesPatrolButtonPressed(BOOLEnum param_1)
    {
        DAT_TribesState::instance.patrolButtonPressed = param_1;
    }

}
}
