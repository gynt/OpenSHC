/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/CrusadeMap.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace CrusadeMap {

            /**
             * Crusade trail map button handler. 1000: if skips remain (DAT_TrailMissionSkipsLeft > 0) and the
             * furthest mission of the current trail is unplayed (months == -1) and not the last, marks it skipped
             * (months = -1200), advances progress and furthest mission, calls setStartDateUnk(trail 1/2/3),
             * decrements the skip count and plays SFX 0x102. 10: copies the selected lord portrait into the
             * player's face bitmap slot and opens the mission intro; 11: back to Select Crusade; 99: rankings; 1:
             * map click selects the unlocked mission whose pin (per-trail MissionDefinedData coordinate table) lies
             * within +-10 px of the mouse.
             */
            void __cdecl MenuItemActionHandler_CrusadeMap_Main(int param_1, ...);

        } // namespace CrusadeMap
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
