/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/IntroVideo.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace IntroVideo {

            /**
             * Prepare handler of the intro video view: positions the current menu, clears the screen, starts
             * intro.bik and records the start time.
             */
            void __cdecl MenuView_IntroVideo_Prepare();

            /**
             * Per-frame handler of the intro video: after 400 ms a click stops the Bink, and once playback has
             * ended switches to the game-start enter-name view.
             */
            void __cdecl MenuView_IntroVideo_DoEveryFrame();

        } // namespace IntroVideo
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
