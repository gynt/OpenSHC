#include "../../../Rendering.func.hpp"

#include "../BinkControlClass.func.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        // FUNCTION: STRONGHOLDCRUSADER 0x00408E10
        void BinkControlClass::zeroBinkPtrAndLoadBinkSoundSystem(HDIGDRIVER drvrPtr)
        {
            this->binkObjPtrArray[0] = (HBINK)0x0;
            this->binkObjPtrArray[1] = (HBINK)0x0;
            BinkSetSoundSystem(BinkOpenMiles, (ulong)drvrPtr);
            return;
        }

    }
}
}
