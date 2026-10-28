#include "OpenSHC/UI/MenuViews/UnusedChooseAvailableKeeps.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace UnusedChooseAvailableKeeps {

            // FUNCTION: STRONGHOLDCRUSADER 0x0042FAA0
            void MenuView_UnusedChooseAvailableKeeps_Prepare()
            {
                DAT_GameCore::instance.availableKeepFlags[0] = 1;
                DAT_GameCore::instance.availableKeepFlags[1] = 1;
                DAT_GameCore::instance.availableKeepFlags[2] = 1;
                DAT_GameCore::instance.availableKeepFlags[3] = 1;
                DAT_GameCore::instance.availableKeepFlags[4] = 1;
            }

        }
    }
}
}
