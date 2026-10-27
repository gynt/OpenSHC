/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/UnknownMenuSubStruct.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {

#pragma pack(push, 1)
    // SIZE: 0x00000004
    typedef struct UnknownMenuSubStruct {

        short field0_0x0; // 0x00000000 length: 2
        // Hover feedback type of a menu item: 1 plays SFX 0x88, 2..7 other hover sounds
        short hoverSoundType; // 0x00000002 length: 2

    } UnknownMenuSubStruct;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(UnknownMenuSubStruct) == 4, UnknownMenuSubStruct);
} // namespace UI
} // namespace OpenSHC
