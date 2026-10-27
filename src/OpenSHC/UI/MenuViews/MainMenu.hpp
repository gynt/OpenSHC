/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/MainMenu.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace MainMenu {

            /**
             * Prepare handler of the main menu: loads frontend_main/frontend_main2 TGX backgrounds and shc_back,
             * resets background index and video selector, sets game mode to campaign, closes all three modal
             * compositions and resets difficulty to 1.
             */
            void __cdecl MenuView_MainMenu_Prepare();

            /**
             * Initial-draw handler of the main menu: clears the screen, draws the outer border and the background
             * gfx centred, positions the current menu at the menu border origin and starts richard_swordswing.bik
             * in Bink slot 0.
             */
            void __cdecl MenuView_MainMenu_DoInitial();

            /**
             * Per-frame handler of the main menu: when a modal is open switches to background 1 and stops the Bink
             * video; otherwise, once the previous video has ended (and no menu switch is pending), starts the next
             * one, redraws the background and prints the version string "V1.41". The selector is rng%3 but any
             * positive remainder is reset to 0, so in practice richard_ambient.bik is always chosen and the
             * richard_swordswing.bik branch (selector == 1) is unreachable; sword-swing plays only from DoInitial.
             */
            void __cdecl MenuView_MainMenu_DoEveryFrame();

        } // namespace MainMenu
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
