/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/LoadMap.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace LoadMap {

            /**
             * Load-map list row click handler: selects the clicked row (relative to the scroll offset) if
             * offset+row is below the entry count; a second click on the same absolute entry within 500 ms acts as
             * a double-click and calls SaveLoadMap_Buttons(2). Remembers the last clicked absolute index and click
             * time.
             */
            void __cdecl MenuItemActionHandler_LoadMap_TableContent(int param_1, ...);

        } // namespace LoadMap
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
