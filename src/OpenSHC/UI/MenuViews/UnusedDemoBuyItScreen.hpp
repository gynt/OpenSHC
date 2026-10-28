/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/UnusedDemoBuyItScreen.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace UnusedDemoBuyItScreen {

            /**
             * Prepare handler of the unused demo "buy it" screen: loads "demo buy it screen.tgx", clears the
             * screen, records the start time and x offset (24 px at 800x600), shuts down the sound system and
             * requests window close if openOnClose is set.
             */
            void __cdecl MenuView_UnusedDemoBuyItScreen_Prepare();

            /**
             * Initial-draw handler of the unused demo "buy it" screen: clears the screen, draws the centred image
             * shifted 24 px right at 800x600 and positions the menu accordingly.
             */
            void __cdecl MenuView_UnusedDemoBuyItScreen_DoInitial();

            /**
             * Per-frame handler of the unused demo 'buy it' screen: blits loaded gfx 0 centred on screen, shifted
             * horizontally by the global INT_00b960e0.
             */
            void __cdecl MenuView_UnusedDemoBuyItScreen_DoEveryFrame();

        } // namespace UnusedDemoBuyItScreen
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
