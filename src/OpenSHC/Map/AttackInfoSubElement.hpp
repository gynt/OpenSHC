/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/AttackInfoSubElement.hpp'
*/

#pragma once

#include "OpenSHC/Map/AttackInfoSomeArrayElement.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::AttackInfoSomeArrayElement;

#pragma pack(push, 1)
    // SIZE: 0x000177BC
    typedef struct AttackInfoSubElement {

        // Created by retype action
        int currentPlayerID_OR_attackedPlayerID_OR_one; // 0x00000000 length: 4
        int hack1; // 0x00000004 length: 4
        int hack2; // 0x00000008 length: 4
        int hack3; // 0x0000000C length: 4
        // Hack list entries are 16 bytes {tile, tile2, score, unitID} like the other lists (LAYOUT func:155); same
        // length, shape only.
        int field4_0x10[4000]; // 0x00000010 length: 16000
        undefined1 padding_0x3e90[16]; // 0x00003E90 length: 16
        // [155 0x00519990] block+0x3EA0 (accessed as scaleValuesArray-0x1C) is set to the minimum tile-layer value
        // over the hack entries
        int minHackLayerValue; // 0x00003EA0 length: 4
        // 0x3EA4 (scaleValuesArray-0x18) = min per-player tile-layer byte over gate entries (sibling 0x3EA0 = min
        // over hack entries); Unk name Per-player AttackInfoSubElement value only cleared (for players 0..7) in
        // initializeAttackWaveSlot.
        int minGateLayerValue; // 0x00003EA4 length: 4
        // accessed by 0x5181ed, 0x5181f9, 0x518205, 0x518211
        undefined1 field_0x3ea8[4]; // 0x00003EA8 length: 4
        // Created by retype action
        int stone1; // 0x00003EAC length: 4
        // Created by retype action
        int scale1; // 0x00003EB0 length: 4
        // Created by retype action
        int scale2; // 0x00003EB4 length: 4
        // Created by retype action
        int scale3; // 0x00003EB8 length: 4
        int field31_0x3ebc[1000][4]; // 0x00003EBC length: 16000
        undefined1 padding_0x7d3c[16]; // 0x00007D3C length: 16
        // Created by retype action
        int town1; // 0x00007D4C length: 4
        int some1000ArrayIndex; // 0x00007D50 length: 4
        // Created by retype action
        int town2; // 0x00007D54 length: 4
        AttackInfoSomeArrayElement some1000Array[1000]; // 0x00007D58 length: 16000
        undefined1 padding_0xbbd8[16]; // 0x0000BBD8 length: 16
        // Created by retype action
        int gate1; // 0x0000BBE8 length: 4
        int some1000ArrayIndex_2; // 0x0000BBEC length: 4
        // Created by retype action
        int gate2; // 0x0000BBF0 length: 4
        int field71_0xbbf4[1000][4]; // 0x0000BBF4 length: 16000
        undefined1 padding_0xfa74[16]; // 0x0000FA74 length: 16
        // Created by retype action
        int moat1; // 0x0000FA84 length: 4
        int field89_0xfa88; // 0x0000FA88 length: 4
        // Created by retype action
        int moat2; // 0x0000FA8C length: 4
        // Moat list: count at +0xFA88 capped at 1000 (cmp 0x3E8), entries of 16 bytes from +0xFA90
        // ({tile,tile2,score,unitID}).
        int moatEntries[1000][4]; // 0x0000FA90 length: 16000
        undefined1 padding_0x13910[16]; // 0x00013910 length: 16
        // Created by retype action
        int wide1; // 0x00013920 length: 4
        // Created by retype action
        int wide2; // 0x00013924 length: 4
        int wide3; // 0x00013928 length: 4
        // Wide list: count at +0x13924 capped at 1000, 16-byte entries from +0x1392C; ends at +0x177AC inside the
        // 0x177BC block.
        int wideEntries[1000][4]; // 0x0001392C length: 16000
        undefined1 padding_0x177ac[16]; // 0x000177AC length: 16

    } AttackInfoSubElement;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(AttackInfoSubElement) == 96188, AttackInfoSubElement);
} // namespace Map
} // namespace OpenSHC
