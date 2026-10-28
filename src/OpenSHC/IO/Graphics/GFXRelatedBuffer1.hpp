/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/IO/Graphics/GFXRelatedBuffer1.hpp'
*/

#pragma once

namespace OpenSHC {
namespace IO {
    namespace Graphics {

#pragma pack(push, 1)
        // SIZE: 0x00011DF0
        typedef struct GFXRelatedBuffer1 {

            // number of hotspot runs found on this scanline of campaign_map_england_hotspots.bmp (max 12)
            undefined1 runCount; // 0x00000000 length: 1
            undefined1 padding_0x1[1]; // 0x00000001 length: 1
            // start x of each hotspot run on this scanline (short array)
            short runStartX; // 0x00000002 length: 2
            undefined1 padding_0x4[46]; // 0x00000004 length: 46
            // length in pixels of each hotspot run (short array)
            short runLength; // 0x00000032 length: 2
            undefined1 padding_0x34[46]; // 0x00000034 length: 46
            // region id per run = 40 - palette index of the hotspot colour (byte array)
            undefined1 runRegionId; // 0x00000062 length: 1
            undefined1 padding_0x63[23]; // 0x00000063 length: 23
            // end of this 0x7A-byte scanline record (start of the next row); used only as stride
            undefined1 nextRowRecord; // 0x0000007A length: 1
            undefined1 padding_0x7b[219]; // 0x0000007B length: 219
            undefined1 field340_0x156; // 0x00000156 length: 1
            undefined1 padding_0x157[72857]; // 0x00000157 length: 72857

        } GFXRelatedBuffer1;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(GFXRelatedBuffer1) == 73200, GFXRelatedBuffer1);
    } // namespace Graphics
} // namespace IO
} // namespace OpenSHC
