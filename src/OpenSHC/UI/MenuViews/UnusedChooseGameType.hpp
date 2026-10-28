/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/UnusedChooseGameType.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace UnusedChooseGameType {

            /**
             * Per-frame handler of the unused choose-game-type view: draws background, header and 'Select Game
             * Type', renders the editor minimap for the map size (100/160/200 drawn 1:1, 300 drawn at 150, 0
             * treated as 400 and drawn at 200) with two black frames and a dimmed 'NxN' size label at its lower
             * right.
             */
            void __cdecl MenuView_UnusedChooseGameType_DoEveryFrame();

        } // namespace UnusedChooseGameType
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
