/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/ScenarioEvents/IngameScenarioEventItemContent.hpp'
*/

#pragma once

#include "OpenSHC/Game/ScenarioEvents/ScenarioEventCondition.hpp"

namespace OpenSHC {
namespace Game {
    namespace ScenarioEvents {

        using OpenSHC::Game::ScenarioEvents::ScenarioEventCondition;

#pragma pack(push, 1)
        // SIZE: 0x000000D4
        typedef struct IngameScenarioEventItemContent {

            int actionData; // 0x00000000 length: 4
            int ScenarioEventType; // 0x00000004 length: 4
            // [081 0x004C31A0] 0x4C37E7 cmp word ptr [data+8],0 (16-bit read, includes 'magic'): non-zero -> fires
            // only when met count >= active count; zero -> fires when any condition is met.
            byte requireAllConditions; // 0x00000008 length: 1
            byte magic; // 0x00000009 length: 1
            // [081 0x004C31A0] Byte data+0xA (0x4C4582 mov al,[ebp+0x5ca]): 0 = no repeat; otherwise added to the
            // current month/year to reschedule (plus rand % (n/4) when n >= 4). Editor clamps it 0..60 and prints
            // it before 'Months'. It is the interval, not a flag/count.
            byte repeatIntervalMonths; // 0x0000000A length: 1
            // [081 0x004C31A0] Byte data+0xB (0x4C4590 mov cl,[ebp+0x5cb]): 1 = stop repeating, 10 = repeat
            // forever, otherwise decremented each time the event fires; editor clamps it 1..10 and prints it as the
            // 'N x' multiplier. Names of repeat/repeatMonths are swapped (the invasion variant's int repeatMonths
            // at +0x70 really is months).
            byte repeatCount; // 0x0000000B length: 1
            ScenarioEventCondition conditions[39]; // 0x0000000C length: 156
            undefined1 padding_0xa8[44]; // 0x000000A8 length: 44

        } IngameScenarioEventItemContent;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(IngameScenarioEventItemContent) == 212, IngameScenarioEventItemContent);
    } // namespace ScenarioEvents
} // namespace Game
} // namespace OpenSHC
