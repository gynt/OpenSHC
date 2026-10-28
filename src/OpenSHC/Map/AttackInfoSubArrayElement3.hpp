/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/AttackInfoSubArrayElement3.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {

#pragma pack(push, 1)
    // SIZE: 0x00000020
    typedef struct AttackInfoSubArrayElement3 {

        int x; // 0x00000000 length: 4
        int y; // 0x00000004 length: 4
        int tile; // 0x00000008 length: 4
        // [156 0x0051B110] entries whose value != attackInfo.someCounter1 are wiped by the prune passes
        int attackCounterStamp; // 0x0000000C length: 4
        int tribeID; // 0x00000010 length: 4
        int tribeUID; // 0x00000014 length: 4
        // [156 0x0051B110] set to 3 when a tribe reserves the point, decremented each prune pass
        int reservationTimer; // 0x00000018 length: 4
        int zero; // 0x0000001C length: 4

    } AttackInfoSubArrayElement3;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(AttackInfoSubArrayElement3) == 32, AttackInfoSubArrayElement3);
} // namespace Map
} // namespace OpenSHC
