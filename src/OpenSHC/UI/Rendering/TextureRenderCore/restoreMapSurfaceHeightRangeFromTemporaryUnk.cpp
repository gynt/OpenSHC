#include "../TextureRenderCore.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044CCF0
        void TextureRenderCore::restoreMapSurfaceHeightRange()
        {
            this->mapGameSurfaceHeightRange.start = this->savedMapGameSurfaceHeightRange.start;
            this->mapGameSurfaceHeightRange.end = this->savedMapGameSurfaceHeightRange.end;
        }

    }
}
}
