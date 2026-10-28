/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Text/ImageHotspot.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Text {

#pragma pack(push, 1)
    // SIZE: 0x00000008
    typedef struct ImageHotspot {

        short xPos; // 0x00000000 length: 2
        short yPos; // 0x00000002 length: 2
        // [199 0x0045FDC0] assigned the PIC token's graphic id
        short graphicId; // 0x00000004 length: 2
        // [199 0x0045FDC0] assigned the active link index (local_ec) for the picture
        short linkIndex; // 0x00000006 length: 2

    } ImageHotspot;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(ImageHotspot) == 8, ImageHotspot);
} // namespace Text
} // namespace OpenSHC
