/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/UnusedCreateSiege.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace UnusedCreateSiege {

            /**
             * Prepare handler of the unused create-siege view: resets text input, loads frontend_builder2.tgx and
             * shc_back and clears the map-name-set flag INT_00b960e4.
             */
            void __cdecl MenuView_UnusedCreateSiege_Prepare();

            /**
             * Per-frame handler of the unused create-siege view: forces map type Siege, draws background, header,
             * help text TEXT_MAPEDIT 0x25 (unless a bottom-left message is shown), the type label (0x22) and map
             * name (or 'Untitled'); if no modal is open the editor minimap (100/160/200 1:1, 300 at 150, 0 as 400
             * at 200) with frames and 'NxN' label. Clears the unsaved-changes flag after a completed save and
             * stores whether the local player has a keep in siegeThatMapReady.
             */
            void __cdecl MenuView_UnusedCreateSiege_DoEveryFrame();

        } // namespace UnusedCreateSiege
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
