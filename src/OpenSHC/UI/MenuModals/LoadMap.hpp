/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuModals/LoadMap.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace LoadMap {

            /**
             * Renders the Load (map/game) modal: header, list frame lines, minimap preview of the selected file,
             * clears the current menu's 'zero' field, and stores the current list selection
             * index/offset/field33_0x78 into one of three saved triples chosen by field0_0x0 (1/2/3) for restoring
             * later.
             */
            void __cdecl MenuModalRenderFunction_LoadMap(int x, int y, int width, int height);

        } // namespace LoadMap
    } // namespace MenuModals
} // namespace UI
} // namespace OpenSHC
