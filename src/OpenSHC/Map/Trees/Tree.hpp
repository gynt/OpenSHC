/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Trees/Tree.hpp'
*/

#pragma once

#include "OpenSHC/Map/Trees/TreeTypeShort.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Trees {

        using OpenSHC::Map::Trees::TreeTypeShort;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)
        // SIZE: 0x0000009C
        typedef struct Tree {

            // [UNK PASS] was animationFrameUnk
            int currentGmFrame; // 0x00000000 length: 4
            // [077 0x004F1CE0] used as index into gmFileHeaderColorpaletteArray to fetch originX/originY
            short gmImageIndex; // 0x00000004 length: 2
            undefined1 padding_0x6[2]; // 0x00000006 length: 2
            // [077 0x004F1CE0] set for every tree type (1-9) from rng/constants, and from the generic
            // stageRelatedValue parameter, not only apple trees
            int visualVariation; // 0x00000008 length: 4
            short gmOriginX; // 0x0000000C length: 2
            short gmOriginY; // 0x0000000E length: 2
            // [078 0x004F3D60] animationFrameIndex advances when timeGetTime() - field8_0x14 >= this value
            int animFrameIntervalMs; // 0x00000010 length: 4
            // timeGetTime of the last animation frame advance; next frame when treeTypeRelated2 ms passed
            dword lastFrameTimeMs; // 0x00000014 length: 4
            int zero; // 0x00000018 length: 4
            short animationFrameIndex; // 0x0000001C length: 2
            undefined1 padding_0x1e[26]; // 0x0000001E length: 26
            // [109 0x004F2380] selects Tree_1_B instead of Tree_1_A; recomputed as (one == 2) when the sway
            // animation wraps Created by retype action
            BOOLEnum useSwayTableB; // 0x00000038 length: 4
            // [UNK PASS] was animationFrame2Unk
            int fixedGmFrame; // 0x0000003C length: 4
            undefined1 padding_0x40[4]; // 0x00000040 length: 4
            short state; // 0x00000044 length: 2
            // Created by retype action
            TreeTypeShort treeType; // 0x00000046 length: 2
            undefined1 padding_0x48[4]; // 0x00000048 length: 4
            int uid; // 0x0000004C length: 4
            undefined1 padding_0x50[12]; // 0x00000050 length: 12
            short microX; // 0x0000005C length: 2
            short microY; // 0x0000005E length: 2
            undefined1 padding_0x60[2]; // 0x00000060 length: 2
            ushort xPosition; // 0x00000062 length: 2
            ushort yPosition; // 0x00000064 length: 2
            undefined1 padding_0x66[2]; // 0x00000066 length: 2
            uint tile; // 0x00000068 length: 4
            short size; // 0x0000006C length: 2
            // only written from 6th arg of 0x4F1CE0, all three callers push 0; param_6 is a leaked parameter name
            short unknownInitZero6E; // 0x0000006E length: 2
            undefined1 padding_0x70[2]; // 0x00000070 length: 2
            // [077 0x004F3010] reduced by woodcutter damage; reaching <=0 fells the tree Created by retype action
            undefined2 hitPoints; // 0x00000072 length: 2
            // [077 0x004F3960] loaded with the same table value as stageRelated1 (hit points); growth requires
            // stageRelated2 <= stageRelated1, i.e. undamaged Created by retype action
            undefined2 maxHitPoints; // 0x00000074 length: 2
            // 0 standing (sway anim), 1 felled (fall anim held), 2 logs being taken; both suggestions describe same
            // states.
            short fellState; // 0x00000076 length: 2
            // [077 0x004F2FE0] decremented per harvest in advanceTreeDecayState; tree removed (state 3) when it
            // reaches 0 Created by retype action
            undefined2 woodChunksRemaining; // 0x00000078 length: 2
            // Created by retype action
            undefined2 stageRelated4; // 0x0000007A length: 2
            // [078 0x004F3D60] overwritten with LandscapeState.wind.value as the wind front passes the tree's row;
            // non-zero enables animation, value 3 sets zeroUpTo2=1
            short windState; // 0x0000007C length: 2
            undefined1 padding_0x7e[2]; // 0x0000007E length: 2
            // Season if an apple tree, else, it is how grown up the tree is
            int stage; // 0x00000080 length: 4
            int stageTracker; // 0x00000084 length: 4
            int rng1; // 0x00000088 length: 4
            // Created by retype action
            short appleFarmID; // 0x0000008C length: 2
            undefined1 padding_0x8e[2]; // 0x0000008E length: 2
            int appleFarmUID; // 0x00000090 length: 4
            // [077 0x004F30D0] set to 1 here (word at Tree+0xB0, 0x4F312F) for trees near a newly created animal,
            // and the same offset is checked at 0x4F31D3 as the precondition to spawn a crow in
            // spawnCrowFromNearbyTree
            short hasCrows; // 0x00000094 length: 2
            // [077 0x004F3150] set to 200+rng%100 after a crow is spawned; crow only spawns when it is 0;
            // decremented each tick in updateTrees
            short crowCooldown; // 0x00000096 length: 2
            // Set to 20 when the tree is set on fire; decremented to 1 while burning; non-zero blocks re-ignition
            short burnTimer; // 0x00000098 length: 2
            short igniterPlayer; // 0x0000009A length: 2

        } Tree;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(Tree) == 156, Tree);
    } // namespace Trees
} // namespace Map
} // namespace OpenSHC
