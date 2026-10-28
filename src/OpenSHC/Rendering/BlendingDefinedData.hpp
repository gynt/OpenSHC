/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Rendering/BlendingDefinedData.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Rendering {

#pragma pack(push, 1)
    // SIZE: 0x000036F4
    typedef struct BlendingDefinedData {

        int field0_0x0; // 0x00000000 length: 4
        char field1_0x4[10][1000]; // 0x00000004 length: 10000
        int DefaultPlayerSlotUnitColor[9]; // 0x00002714 length: 36
        int PlayerSlotUnitColor[9]; // 0x00002738 length: 36
        undefined1 padding_0x275c[160]; // 0x0000275C length: 160
        // Per-pixel destination offsets used by ApplyBlending at normal zoom.
        int blendPixelOffsets[256]; // 0x000027FC length: 1024
        // Per-pixel destination offsets for ApplyBlending when zoomed out, even screen rows.
        int blendPixelOffsetsZoomEven[128]; // 0x00002BFC length: 512
        // Per-pixel destination offsets for ApplyBlending when zoomed out, odd rows;
        // moveOverlappingMenuPartsToMapSurface indexes far past it (decompiler alias for the following menu-
        // rectangle table)
        int blendPixelOffsetsZoomOdd[128]; // 0x00002DFC length: 512
        pointer campaign_map_england[6]; // 0x00002FFC length: 24
        // Menu-tab overlap rectangle lists: moveOverlappingMenuPartsToMapSurface reads (tab*5-5)*32 + 0xAB8730 =
        // +0x3014 + (tab-1)*0xA0, rows of 40 ints ({x,y,w,h}..., -2 separator, -1 end); 11 rows = 1760 bytes. The
        // claimed split at +0x2ED4 is wrong (0xAB8730-0xAB571C = 0x3014); blendPixelOffsetsZoomOdd stays unchanged.
        int field168_0x3014[55][8]; // 0x00003014 length: 1760

    } BlendingDefinedData;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(BlendingDefinedData) == 14068, BlendingDefinedData);
} // namespace Rendering
} // namespace OpenSHC
