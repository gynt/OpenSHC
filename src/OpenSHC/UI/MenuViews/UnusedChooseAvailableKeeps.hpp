/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/UnusedChooseAvailableKeeps.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace UnusedChooseAvailableKeeps {

            /**
             * Prepare handler of the unused choose-available-keeps view: sets mapU2MiddleBytes[0..4] to 1 (all keep
             * options enabled).
             */
            void __cdecl MenuView_UnusedChooseAvailableKeeps_Prepare();

            /**
             * Per-frame handler of the unused choose-available-keeps view: draws background, header and title text
             * (TEXT_MAPEDIT 0x15), renders the editor minimap for the map size (100/160/200 drawn 1:1, 300 drawn at
             * 150, 0 treated as 400 and drawn at 200) with two black frames and a dimmed 'NxN' size label at its
             * lower right. Same body as the new-map-size view apart from the title string.
             */
            void __cdecl MenuView_UnusedChooseAvailableKeeps_DoEveryFrame();

        } // namespace UnusedChooseAvailableKeeps
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
