/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/UnusedEconomicGametypeSelect.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace UnusedEconomicGametypeSelect {

            /**
             * Prepare handler of the unused economic game-type select menu: loads frontend_economics.tgx /
             * frontend_economics2.tgx and the shc_back gfx, sets the animation base times of buttons 0x168..0x16A
             * to now-4800/-3200/-1600 ms (staggered), resets DAT_LastHoveredMenuButtonId to -1 and clears isTimeHalted2.
             */
            void __cdecl MenuView_UnusedEconomicGametypeSelect_Prepare();

            /**
             * DoInitial of the unused economic game-type select menu: clears screen to black, draws the outer menu
             * border and centred gfx 0, positions the current menu at the main-menu border origin and clears
             * DAT_EditorUnsavedChanges.
             */
            void __cdecl MenuView_UnusedEconomicGametypeSelect_DoInitial();

        } // namespace UnusedEconomicGametypeSelect
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
