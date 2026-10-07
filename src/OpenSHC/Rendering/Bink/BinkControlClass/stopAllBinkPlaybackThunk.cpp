#include "../../../Rendering.func.hpp"

#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        // FUNCTION: STRONGHOLDCRUSADER 0x004092B0
        void BinkControlClass::stopAllBinkPlaybackThunk()
        {
            int binkObjIndex;
            for (binkObjIndex = 0; binkObjIndex < 2; binkObjIndex++) {
                MACRO_CALL_MEMBER(Rendering::Bink::BinkControlClass_Func::stopBinkPlayback, this)(
                    binkObjIndex);
            }
        }

    }
}
}
