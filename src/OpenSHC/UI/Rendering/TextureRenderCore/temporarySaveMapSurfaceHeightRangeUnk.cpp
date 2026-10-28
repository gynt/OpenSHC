#include "../TextureRenderCore.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044CCD0
        void TextureRenderCore::saveMapSurfaceHeightRange()
        {
            this->savedMapGameSurfaceHeightRange.start = this->mapGameSurfaceHeightRange.start;
            this->savedMapGameSurfaceHeightRange.end = this->mapGameSurfaceHeightRange.end;
        }

    }
}
}
