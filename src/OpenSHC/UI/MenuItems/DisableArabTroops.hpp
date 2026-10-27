/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/DisableArabTroops.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace DisableArabTroops {

            /**
             * Scenario editor 'disable Arab troops' handler: a troop button toggles SEC_MercRecruitable[i] (word
             * XOR 1 at 0x1653DE8+2*i; the range check accepts 0..7 although the array has 7 entries); -3 returns to
             * the building availability dialog.
             */
            void __cdecl MenuItemActionHandler_DisableArabTroops_Main(int param_1, ...);

            /**
             * Render of 'disable Arab troops' dialog: draws troop buttons (indices < 8) and overlays a cross icon
             * (GID_INTERFACE_ICONS_2 #0x2d) when SEC_MercRecruitable[i] is 0; -3 draws the Exit button with
             * centered text.
             */
            void __cdecl MenuItemRenderFunction_DisableArabTroops_Main(int param_1, ...);

        } // namespace DisableArabTroops
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
