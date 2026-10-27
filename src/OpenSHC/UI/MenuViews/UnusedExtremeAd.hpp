/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/UnusedExtremeAd.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace UnusedExtremeAd {

            /**
             * Prepare of the unused Extreme advert screen: resets credits playback, deactivates modal dialog 3
             * (MMT_NONE), builds the Extreme demo intro credits script, starts the tick counter and zeroes
             * g_extremeAdFrameCounter.
             */
            void __cdecl MenuView_UnusedExtremeAd_Prepare();

            /**
             * DoInitial of the unused Extreme advert screen: clears to black, positions the current menu at the
             * border origin and renders the active credits elements.
             */
            void __cdecl MenuView_UnusedExtremeAd_DoInitial();

            /**
             * Per-frame handler of the unused Extreme advert: when TicksSinceCounterStart is non-zero, right click
             * stops the credits; left click on hotspot 1 ends the current credits segment, and after the 3rd such
             * advance the window close is requested. Then processes credits script commands, renders the credits
             * elements while the script index is below the command count, increments INT_00ed3140 and requests
             * window close once the script is exhausted.
             */
            void __cdecl MenuView_UnusedExtremeAd_DoEveryFrame();

        } // namespace UnusedExtremeAd
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
