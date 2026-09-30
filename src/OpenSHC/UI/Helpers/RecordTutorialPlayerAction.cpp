#include "../Helpers.func.hpp"

#include "OpenSHC/Globals/INT_00df5574.hpp"
#include "OpenSHC/Globals/INT_00df557c.hpp"
#include "OpenSHC/Globals/INT_00df5580.hpp"
#include "OpenSHC/Globals/INT_00df5584.hpp"
#include "OpenSHC/Globals/TUT_RotateMapHappened.hpp"

namespace OpenSHC {
namespace UI {

    /*
      Dispatches a tutorial player action event by param_1 type: 1=set INT_00df5574, 2=increment TUT_RotateMapHappened,
      3=increment INT_00df557c, 4=set INT_00df5580 to 1, 5=advance INT_00df5580   from 1 to 2, 0x11=increment
      INT_00df5584. Used to track which tutorial milestone actions the   player has completed.      renamed by: Claude
      Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004BC630
    void Helpers::RecordTutorialPlayerAction(int param_1)
    {
        if (param_1 == 1) {
            INT_00df5574::instance = 1;
        }
        if (param_1 == 2) {
            TUT_RotateMapHappened::instance = TUT_RotateMapHappened::instance + 1;
        }
        if (param_1 == 3) {
            INT_00df557c::instance = INT_00df557c::instance + 1;
        }
        if (param_1 == 4) {
            INT_00df5580::instance = 1;
        }
        if (param_1 == 5) {
            if (INT_00df5580::instance == 1) {
                INT_00df5580::instance = 2;
            }
        } else if (param_1 == 0x11) {
            INT_00df5584::instance = INT_00df5584::instance + 1;
        }
    }

}
}
