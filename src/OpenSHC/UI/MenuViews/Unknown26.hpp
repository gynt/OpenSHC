/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/Unknown26.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace Unknown26 {

            /**
             * Prepare handler of the mission intro sequence view: resets the credits engine, builds the intro
             * logo/credits sequence for the current mission and section, and starts the tick counter.
             */
            void __cdecl MenuView_MissionIntroSequence_Prepare();

            /**
             * Initial-draw handler of the mission intro sequence view: positions the menu, clears the screen black
             * and renders the active credits elements.
             */
            void __cdecl MenuView_MissionIntroSequence_DoInitial();

            /**
             * Per-frame handler of the mission intro sequence: once ticks have elapsed, right click stops / left
             * click advances the credits script, runs and renders it, and when all segments are done switches to
             * the intro video (mission 1000); for section 2 to the campaign map view (mission < 22, clearing the
             * section) or credits; otherwise to the scenario description, or the campaign map view for mission 1.
             */
            void __cdecl MenuView_MissionIntroSequence_DoEveryFrame();

        } // namespace Unknown26
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
