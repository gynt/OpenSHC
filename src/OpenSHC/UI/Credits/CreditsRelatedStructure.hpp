/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Credits/CreditsRelatedStructure.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace Credits {

#pragma pack(push, 1)
        // SIZE: 0x00000034
        typedef struct CreditsRelatedStructure {

            // Compared with 1..4 (gfx/text/button/box), 0 = free slot; not a boolean
            int elementType; // 0x00000000 length: 4
            // Matched against command argument to find an element; returned by hit test
            int elementId; // 0x00000004 length: 4
            // Offset 8 is the element x (compared with mouse screenSpaceX, x of render call)
            int x; // 0x00000008 length: 4
            // Offset 0xC is the element y (compared with mouse screenSpaceY, y of render call)
            int y; // 0x0000000C length: 4
            // [176 0x004E12C0] x + it is the right edge of the hover hit test and box width
            int width; // 0x00000010 length: 4
            // Element height in pixels (someX/someY are y/width in practice); used for mouse hit tests
            int height; // 0x00000014 length: 4
            // 0 static, 1 fading in (alpha float in 'flag' from 31 down), 2 fading out (element freed when alpha >
            // 31); script waits until 0
            int fadeState; // 0x00000018 length: 4
            // Render layer index; RenderActiveCreditsElements draws elements layer by layer (7 for text)
            int drawLayer; // 0x0000001C length: 4
            // Text element font size passed to DrawLoadedMenuStringHelper
            int fontSize; // 0x00000020 length: 4
            // Text element: TRUE = centered single line, FALSE = word-wrapped
            int isSingleLine; // 0x00000024 length: 4
            // Text element: 1 -> color 0 (black), else 0xccfaff
            int useBlackTextColor; // 0x00000028 length: 4
            // Image element: alternate gfx shown when mouse is over it, -1 none
            int hoverGfxIndex; // 0x0000002C length: 4
            // Float at 0x30 stepped by the fade and passed as blend strength (31.0/1.0); not a flag
            int fadeLevel; // 0x00000030 length: 4

        } CreditsRelatedStructure;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(CreditsRelatedStructure) == 52, CreditsRelatedStructure);
    } // namespace Credits
} // namespace UI
} // namespace OpenSHC
