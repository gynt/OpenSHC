#include "../Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_00df5540.hpp"
#include "OpenSHC/Globals/DAT_00df5544.hpp"
#include "OpenSHC/Globals/DWORD_00df5548.hpp"

namespace OpenSHC {
namespace UI {

    /*
      Records the current time into DAT_00df5548, stores param_1 into DAT_00df5540, and sets   DAT_00df5544 to 1 (or 31
      if param_1 == 1). Used to initiate a timed fade/transition between   tutorial steps.      renamed by: Claude
      Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004BC5F0
    void Helpers::InitTutorialStepTransition(int param_1)
    {
        DWORD_00df5548::instance = timeGetTime();
        DAT_00df5540::instance = param_1;
        DAT_00df5544::instance = 1;
        if (param_1 == 1) {
            DAT_00df5544::instance = 0x1f;
        }
    }

}
}
