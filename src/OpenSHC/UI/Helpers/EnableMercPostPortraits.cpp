#include "OpenSHC/UI/Helpers.func.hpp"

#include "OpenSHC/Globals/g_mercPostPortraitsEnabled.hpp"

namespace OpenSHC {
namespace UI {
    namespace Helpers {

        // FUNCTION: STRONGHOLDCRUSADER 0x00466E10
        void EnableMercPostPortraits() { g_mercPostPortraitsEnabled::instance = 1; }

    }
}
}
