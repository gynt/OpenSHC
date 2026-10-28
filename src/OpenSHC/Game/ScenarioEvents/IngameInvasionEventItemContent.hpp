/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/ScenarioEvents/IngameInvasionEventItemContent.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {
    namespace ScenarioEvents {

#pragma pack(push, 1)
        // SIZE: 0x000000B0
        typedef struct IngameInvasionEventItemContent {

            int totalUnitCount; // 0x00000000 length: 4
            // spawnInvasionEventAttackWave loops edx=0..24 (cmp edx,0x19) over [ebp+edx*4+0x145F4]; slot 24 is the
            // separately named unitCountSlot24.
            int unitCountsPerUnitType[25]; // 0x00000004 length: 100
            int messageMonth; // 0x00000068 length: 4
            int messageYear; // 0x0000006C length: 4
            int repeatMonths; // 0x00000070 length: 4
            int crusaderArabian; // 0x00000074 length: 4
            int markerIDUnk; // 0x00000078 length: 4
            undefined1 padding_0x7c[36]; // 0x0000007C length: 36
            // action/event id chosen in the trigger-event menu (e.g. 0x8B plague, 0x91, 0x92, 0x94, 0xB3); drives
            // the TriggerEventMenu switch
            int triggerEventActionId; // 0x000000A0 length: 4
            // accessed by 0x4b9e86, 0x4c1b64, 0x4c1b78
            undefined1 field_0xa4[4]; // 0x000000A4 length: 4
            // slider value of the trigger-event menu (count of units/animals/poison clouds), min 1
            int triggerEventAmount; // 0x000000A8 length: 4
            undefined1 padding_0xac[4]; // 0x000000AC length: 4

        } IngameInvasionEventItemContent;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(IngameInvasionEventItemContent) == 176, IngameInvasionEventItemContent);
    } // namespace ScenarioEvents
} // namespace Game
} // namespace OpenSHC
