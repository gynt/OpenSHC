#include "../BitMapState.func.hpp"

#include "OpenSHC/Globals/COL_MAGENTA.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046C680
    void BitMapState::blitBitmap24BitToSurface565(int addExtra)
    {
        for (int y = this->height - 1; y >= 0; y -= this->rowStep) {
            int local_4 = 0;
            for (int x = 0; x < this->width; x += this->colStep) {

                unsigned short blue = ((unsigned char*)(this->address + this->stride24bit * y + x * 3))[0] >> 3;

                unsigned short green = ((unsigned char*)(this->address + this->stride24bit * y + x * 3))[1];
                if (this->forceRgb555 == 0 && DAT_WindowAndDirectDraw::instance.colorBitMode == Rendering::RGB_565) {
                    green >>= 2;
                } else {
                    green >>= 3;
                }
                green <<= 5;

                unsigned short red = ((unsigned char*)(this->address + this->stride24bit * y + x * 3))[2] >> 3;
                if (this->forceRgb555 == 0 && DAT_WindowAndDirectDraw::instance.colorBitMode == Rendering::RGB_565) {
                    red <<= 11;
                } else {
                    red <<= 10;
                }

                unsigned short uVar3 = red + green + blue;
                if (DAT_WindowAndDirectDraw::instance.colorBitMode != Rendering::RGB_565 || this->forceRgb555 != 0) {
                    uVar3 |= 0x8000;
                    if (uVar3 == 0xfc1f) {
                        uVar3 = COL_MAGENTA::instance.shortValue;
                    }
                }
                *this->surface = uVar3;
                ++this->surface;
                ++local_4;
            }
            if (addExtra != 0) {
                this->surface += (this->destRowPixels - local_4);
            }
        }
        this->forceRgb555 = 0;
    }

}
}
