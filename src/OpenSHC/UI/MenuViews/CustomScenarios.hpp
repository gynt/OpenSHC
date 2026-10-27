/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/CustomScenarios.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace CustomScenarios {

            /**
             * Prepare handler of the custom scenarios (map editor start) view: loads
             * frontend_builder/frontend_builder2 and shc_back, staggers the four button animation start times,
             * resets the text-input result and mission number, switches game mode to GM_EDITOR, ensures a current
             * player slot (1 if none) marked human, resets teams and selects the default build menu tab.
             */
            void __cdecl MenuView_CustomScenarios_Prepare();

            /**
             * Per-frame handler of the custom scenarios view: draws background image 0 or 1 (1 while a modal dialog
             * is open) centred; switches to the map editor properties view when the text input result is 1, or re-
             * runs Prepare when it is -1.
             */
            void __cdecl MenuView_CustomScenarios_DoEveryFrame();

        } // namespace CustomScenarios
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
