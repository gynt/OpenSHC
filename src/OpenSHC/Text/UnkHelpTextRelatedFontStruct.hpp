/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Text/UnkHelpTextRelatedFontStruct.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Text {

#pragma pack(push, 1)
    // SIZE: 0x00000008
    typedef struct UnkHelpTextRelatedFontStruct {

        // [197 0x0045D950] points to strings like 'Stronghold 24 aa'
        char* fontName; // 0x00000000 length: 4
        // [197 0x0045D950] compared against the requested id; values 15..19 next to font names, -1 terminates the
        // table
        int fontID; // 0x00000004 length: 4

    } UnkHelpTextRelatedFontStruct;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(UnkHelpTextRelatedFontStruct) == 8, UnkHelpTextRelatedFontStruct);
} // namespace Text
} // namespace OpenSHC
