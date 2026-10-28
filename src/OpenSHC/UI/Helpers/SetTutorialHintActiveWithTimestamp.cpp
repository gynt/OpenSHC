#include "OpenSHC/UI/Helpers.func.hpp"

#include "OpenSHC/Globals/g_tutorialHintActive.hpp"
#include "OpenSHC/Globals/DWORD_00df5568.hpp"

namespace OpenSHC {
namespace UI {
    namespace Helpers {

        // FUNCTION: STRONGHOLDCRUSADER 0x004BC770
        void SetTutorialHintActiveWithTimestamp()
        {
            g_tutorialHintActive::instance = 1;
            DWORD_00df5568::instance = timeGetTime();
        }

    }
}
}
