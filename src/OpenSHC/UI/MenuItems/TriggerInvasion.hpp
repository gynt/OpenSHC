/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/TriggerInvasion.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace TriggerInvasion {

            /**
             * Action handler of the map-editor invasion trigger panel: opens an overlay slider for the invasion
             * unit count of the clicked unit type, with max = min(per-type limit, current + 500 - total units), and
             * sets the slider label text index (group 199) for that unit type.
             */
            void __cdecl MenuItemActionHandler_TriggerInvasion_Main(int param_1, ...);

            /**
             * Render callback of the invasion trigger panel: draws a button with the unit-type icon (GM_ARMY_UNITS)
             * and, if non-zero, the invasion unit count for that type.
             */
            void __cdecl MenuItemRenderFunction_TriggerInvasion_Main(int param_1, ...);

        } // namespace TriggerInvasion
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
