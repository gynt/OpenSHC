/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/CustomScenarios.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace CustomScenarios {

            /**
             * Render callback of the Custom Scenarios menu: draws the button (hover SFX when the hovered button
             * 1..4 changes, remembered in DAT_LastHoveredMenuButtonId), then labels: buttons 2 and 4 get TEXT_SHC_STANDALONE
             * strings 1 and 0, buttons 1 and 3 get TEXT_MAP_TITLES strings 0 and 2 (buttonId-1).
             */
            void __cdecl MenuItemRenderFunction_CustomScenarios_Main(int param_1, ...);

            /**
             * Custom Scenarios menu action: 1 opens the load-map dialog, 2 new single-player map (map type view), 3
             * new multiplayer map (map size view), 4 free-build setup (builder game mode, all weapons producible,
             * teams reset, map mission type 3, single-player map choice), 5 main menu. Cases 2-4 reset player slot
             * unit colors to defaults.
             */
            void __cdecl MenuItemActionHandler_CustomScenarios_Main(int param_1, ...);

        } // namespace CustomScenarios
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
