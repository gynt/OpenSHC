/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/IO/BitMapState.hpp'
*/

#pragma once

#include "wingdi.h"

namespace OpenSHC {
namespace IO {

#pragma pack(push, 1)

    // SIZE: 0x00000480
    class BitMapState {
    public:
        // Unsigned Double-Word (ddw, 4-bytes)
        dword mbr_0x0; // 0x00000000 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        dword mbr_0x4; // 0x00000004 length: 4
        // [052 0x00472270] set to biWidth; used as pixels-per-row loop bound in the blitters Unsigned Double-Word
        // (ddw, 4-bytes)
        int width; // 0x00000008 length: 4
        // [052 0x00472270] set to biHeight; used as row count in the blitters Unsigned Double-Word (ddw, 4-bytes)
        dword height; // 0x0000000C length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        dword size; // 0x00000010 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        dword biBitCount; // 0x00000014 length: 4
        // [052 0x0046C680] when non-zero the blitter uses the RGB555|0x8000 packing even in 565 display mode; reset
        // to 0 after each blit Unsigned Double-Word (ddw, 4-bytes)
        dword forceRgb555; // 0x00000018 length: 4
        byte palette[256][4]; // 0x0000001C length: 1024
        // Unsigned Double-Word (ddw, 4-bytes)
        dword paletteSize; // 0x0000041C length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        dword paletteStart; // 0x00000420 length: 4
        // [052 0x0046C680] increment of the source column index per output pixel Unsigned Double-Word (ddw,
        // 4-bytes)
        dword colStep; // 0x00000424 length: 4
        // [052 0x0046C680] decrement of the source row index per output row Unsigned Double-Word (ddw, 4-bytes)
        dword rowStep; // 0x00000428 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        dword stride32bit; // 0x0000042C length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        dword stride24bit; // 0x00000430 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        dword stride16bit; // 0x00000434 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        dword stride8bit; // 0x00000438 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        BITMAPFILEHEADER bitmapFileHeader; // 0x0000043C length: 14
        undefined1 padding_0x44a[2]; // 0x0000044A length: 2
        // Unsigned Double-Word (ddw, 4-bytes)
        BITMAPINFOHEADER bitmapInfoHeader; // 0x0000044C length: 40
        // Unsigned Double-Word (ddw, 4-bytes)
        dword address; // 0x00000474 length: 4
        ushort* surface; // 0x00000478 length: 4
        // [052 0x0046C680] with addExtra the surface pointer advances by (mbr_0x47c - pixels written) per row, i.e.
        // destination row width in pixels Unsigned Double-Word (ddw, 4-bytes)
        dword destRowPixels; // 0x0000047C length: 4

    private:
        BitMapState(BitMapState const&);
        void operator=(BitMapState const&);

    public:
        BitMapState() {};
        ~BitMapState() {};

        // Constructor
        /**
         * Constructor of the global DAT_BitMapState: clears the pixel-buffer pointer (address), the destination
         * surface pointer and the mbr_0x18 RGB555-override flag; returns &DAT_BitMapState.
         */
        BitMapState* Constructor_BitMapState();

        /**
         * Copies one 64x66-pixel 16-bit portrait (0x2100 bytes) from a decoded 16-bit surface at (x, y) into face
         * slot faceIndex of DAT_TextureRenderCoreObject.bitmapsFaces_0x94 (via a temporary malloc buffer) and
         * records its byte size 0x2100 in field69_0x98[faceIndex].
         */
        void readBitmapFace(uchar* surface, int x, int y, int faceIndex);

        /**
         * Converts the loaded 24-bit BMP pixel data (DAT_BitMapState.address, bottom-up rows, BGR) into 16-bit
         * pixels written sequentially to DAT_BitMapState.surface: RGB565 when the display is 565 and mbr_0x18 == 0,
         * otherwise RGB555 with bit 15 set, remapping 555 magenta 0xFC1F to COL_MAGENTA (transparency key). Rows
         * step by `step`, columns by `step2`; if addExtra != 0 the destination skips (mbr_0x47c - pixelsWritten)
         * pixels per row. Clears mbr_0x18 afterwards. NAME? also produces RGB555, not only 565.
         */
        void blitBitmap24BitToSurface565(int addExtra);

        /**
         * Paletted (8-bit) counterpart of blitBitmap24BitToSurface565: each source byte (bottom-up rows) indexes
         * DAT_BitMapState.palette (BGRx entries) and is packed to RGB565 or RGB555|0x8000 like the 24-bit blitter,
         * writing sequentially to DAT_BitMapState.surface. 555 magenta 0xFC1F is replaced by the literal 0xF81F
         * (565 magenta). Optional destination row padding when the flag is set; clears mbr_0x18 afterwards.
         */
        void blitPalettedBitmapToSurface565(int addRowPadding);

        /**
         * Copies the raw 8-bit palette indices of the loaded BMP into DAT_TextureRenderCoreObject.address2,
         * flipping the bottom-up BMP rows to top-down (width bytes per row, stride8bit = width, no padding
         * handling).
         */
        void copyBitmapToTextureBuffer();

        /**
         * Fills face slots 20..27 (byte offsets 0x29400..0x39C00 in steps of 0x2100) of
         * DAT_TextureRenderCoreObject.bitmapsFaces_0x94 with COL_MAGENTA (transparent), clearing the portrait slots
         * after the 20 loaded from faces.bmp. Called when setting up the skirmish lobby.
         */
        void setBMPFacesToMagenta();

        /**
         * Opens the current active resource file and reads its BITMAPFILEHEADER (14 bytes) and BITMAPINFOHEADER (40
         * bytes) into DAT_BitMapState, deriving width/height, bit count, 8/16/24/32-bit row strides (24-bit stride
         * padded to a multiple of 4) and pixel-data size. For 8-bit images it then reads the palette (0x300 bytes
         * if bfOffBits <= 1000, else 0x400) that ends at bfOffBits.
         */
        void loadBitmapHeader();

        /**
         * Allocates DAT_BitMapState.size bytes, reads the BMP pixel data from the current active resource at
         * bfOffBits, copies raw indices to the texture buffer for 8-bit images, then blits to the 16-bit `surface`
         * (step 1, no row padding) with the 24-bit or paletted blitter. Frees the pixel buffer and clears
         * address/surface.
         */
        void loadAndBlitBitmap(void* surface);

        /**
         * Loads faces.bmp: resolves the resource, parses the header, decodes it into a temporary 16-bit surface and
         * extracts 20 portraits (64x66) into face slots 0..19: ten from y=7 and ten from y=81, at x = 7 + 71*i.
         * Frees the temporary surface.
         */
        void loadFacesBMP();
    };

    static_assert_cpp98_obj(sizeof(BitMapState) == 1152, BitMapState);

#pragma pack(pop)

} // namespace IO
} // namespace OpenSHC
