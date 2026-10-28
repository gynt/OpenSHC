#include "../BitMapState.func.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046C8D0
    void BitMapState::copyBitmapToTextureBuffer()
    {
        unsigned char* dest = (unsigned char*)DAT_TextureRenderCoreObject::instance.address2;
        for (int y = this->height - 1; y >= 0; --y) {
            for (int x = 0; x < this->width; ++x) {
                *dest = *(unsigned char*)(this->stride8bit * y + this->address + x);
                ++dest;
            }
        }
    }

}
}
