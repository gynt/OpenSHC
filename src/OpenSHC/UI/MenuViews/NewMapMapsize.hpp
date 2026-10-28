/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/NewMapMapsize.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace NewMapMapsize {

            /**
             * Prepare handler of the new-map size view: loads frontend_builder2.tgx and shc_back.
             */
            void __cdecl MenuView_NewMapMapsize_Prepare();

            /**
             * Per-frame handler of the new-map size view: draws background, header banner and 'Select New Map
             * Size', renders the editor minimap for the current map size (100/160/200 drawn 1:1, 300 drawn at 150,
             * 0 treated as 400 and drawn at 200) with two black frames, and a dimmed right-aligned 'NxN' size label
             * at its lower right.
             */
            void __cdecl MenuView_NewMapMapsize_DoEveryFrame();

        } // namespace NewMapMapsize
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
