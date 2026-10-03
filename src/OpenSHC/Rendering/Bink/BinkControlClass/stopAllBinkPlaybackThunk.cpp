#include "../../../Rendering.func.hpp"

#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        // FUNCTION: STRONGHOLDCRUSADER 0x004092B0
        void BinkControlClass::stopAllBinkPlaybackThunk()
        {
            int binkObjIndex;
            binkObjIndex = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::stopBinkPlayback, this)(
                    binkObjIndex);
                binkObjIndex = binkObjIndex + 1;
            } while (binkObjIndex < 2);
        }

    }
}
}
