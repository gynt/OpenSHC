/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/SelectCrusade.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace SelectCrusade {

            /**
             * Initial-draw handler of the select-crusade (skirmish type) view: clears the screen, draws the outer
             * border, positions the menu and resets the highlighted skirmish type.
             */
            void __cdecl MenuView_SelectCrusade_DoInitial();

            /**
             * Per-frame handler of the select-crusade view: draws background, panel and "Choose type of Crusader
             * game", plus title and description of the highlighted option (1 Crusader trail, 2 custom game, 3
             * Warchest trail, 4 Extreme trail).
             */
            void __cdecl MenuView_SelectCrusade_DoEveryFrame();

        } // namespace SelectCrusade
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
