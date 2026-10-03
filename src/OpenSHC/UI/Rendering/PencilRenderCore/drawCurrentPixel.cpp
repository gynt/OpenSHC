#include "../PencilRenderCore.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00468F20
        void PencilRenderCore::drawCurrentPixel()
        {
            *(ushort*)((int)this->surfacePtr + this->currentY * this->horizontalByteSize + this->currentX * 2)
                = this->drawColor;
        }

    }
}
}
