/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Moat.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {

#pragma pack(push, 1)
    // SIZE: 0x00000010
    typedef struct Moat {

        int tile; // 0x00000000 length: 4
        short x; // 0x00000004 length: 2
        short y; // 0x00000006 length: 2
        short zeroOrTwo; // 0x00000008 length: 2
        undefined1 padding_0xa[2]; // 0x0000000A length: 2
        char owner; // 0x0000000C length: 1
        // 0 planned, 4 dug; incremented per dig step, decremented when filling.
        byte digProgress; // 0x0000000D length: 1
        byte stage; // 0x0000000E length: 1
        // [106 0x005111D0] compared <100 when choosing a moat, added to the score, +20 when a unit selects the
        // moat, -20 in the unit update functions when the unit cannot path to it, reset to 0 when digging completes
        char workerReservation; // 0x0000000F length: 1

    } Moat;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(Moat) == 16, Moat);
} // namespace Map
} // namespace OpenSHC
