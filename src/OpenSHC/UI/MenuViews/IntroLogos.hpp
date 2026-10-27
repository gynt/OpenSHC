/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/IntroLogos.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace IntroLogos {

            /**
             * Prepare handler of the intro logos view: loads logo1.tgx or logo2.tgx for intro step 0/1 (nothing for
             * step 2), resets the blend strength and records the start time.
             */
            void __cdecl MenuView_IntroLogos_Prepare();

            /**
             * Initial handler of the intro logos view: positions the current menu and restarts the intro timestamp.
             */
            void __cdecl MenuView_IntroLogos_DoInitial();

            /**
             * Per-frame handler of the intro logos: draws logo 1/2 (or, at step 2, the 'Gameplay may change during
             * online play' notice on black), then runs fade-in (20 ms per blend step up to 32), hold (2.5 s, 6 s
             * for logo 2) and fade-out with a blended black box; after fade-out advances to the next intro step or,
             * after step 2, to the intro video view.
             */
            void __cdecl MenuView_IntroLogos_DoEveryFrame();

        } // namespace IntroLogos
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
