/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/ScenarioEvents/InGameEventExtra.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {
    namespace ScenarioEvents {

#pragma pack(push, 1)
        // SIZE: 0x000000A0
        typedef struct InGameEventExtra {

            // ResetEventStatusUnk walks one event block with ebx = event*0xA0 + 0x165F028, reading [ebx] and
            // stepping by 4 for 40 condition slots (cmp esi,0x28).
            int conditionIsTrue[40]; // 0x00000000 length: 160

        } InGameEventExtra;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(InGameEventExtra) == 160, InGameEventExtra);
    } // namespace ScenarioEvents
} // namespace Game
} // namespace OpenSHC
