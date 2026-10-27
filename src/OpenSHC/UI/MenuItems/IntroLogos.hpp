/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/IntroLogos.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace IntroLogos {

            /**
             * Intro logos click handler: on mouse release after a click, advances the intro logo sequence (step 0
             * -> 1 -> 2, resetting blend and timestamp and re-entering MVT_INTRO_LOGOS); after the last logo
             * switches to the intro video view.
             */
            void __cdecl MenuItemActionHandler_IntroLogos_General(int unused, ...);

        } // namespace IntroLogos
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
