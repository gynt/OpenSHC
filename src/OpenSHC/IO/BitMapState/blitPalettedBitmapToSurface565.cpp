#include "../BitMapState.func.hpp"

#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046C7A0
    void BitMapState::blitPalettedBitmapToSurface565(int param_1)
    {
        for (int y = this->height - 1; y >= 0; y -= this->rowStep) {
            int _counter = 0;
            for (int x = 0; x < this->width; x += this->colStep) {
                unsigned char index = ((unsigned char*)this->address)[this->stride8bit * y + x];

                unsigned short blue = this->palette[index][0] >> 3;

                unsigned short green = this->palette[index][1];
                if (this->forceRgb555 == 0 && DAT_WindowAndDirectDraw::instance.colorBitMode == Rendering::RGB_565) {
                    green >>= 2;
                } else {
                    green >>= 3;
                }
                green <<= 5;

                unsigned short red = this->palette[index][2] >> 3;
                if (this->forceRgb555 == 0 && DAT_WindowAndDirectDraw::instance.colorBitMode == Rendering::RGB_565) {
                    red <<= 11;
                } else {
                    red <<= 10;
                }

                unsigned short _outcome = red + green + blue;
                if (DAT_WindowAndDirectDraw::instance.colorBitMode != Rendering::RGB_565 || this->forceRgb555 != 0) {
                    _outcome |= 0x8000;
                    if (_outcome == 0xfc1f) {
                        _outcome = 0xf81f; // NOTE: Standard Magenta for RGB555 instead of the value of COL_MAGENTA
                    }
                }
                *this->surface = _outcome;
                ++this->surface;
                ++_counter;
            }
            if (param_1 != 0) {
                this->surface += (this->destRowPixels - _counter);
            }
        }
        this->forceRgb555 = 0;
    }

}
}
