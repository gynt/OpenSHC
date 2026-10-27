/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/DisableWeapon.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace DisableWeapon {

            /**
             * Scenario editor 'disable weapons' handler: buttons 0..5 toggle producibility of crossbow, pike,
             * sword, bow, spear, mace; -3 returns to building availability.
             */
            void __cdecl MenuItemActionHandler_DisableWeapon_Main(int param_1, ...);

            /**
             * Render of 'disable weapons' dialog: draws weapon buttons 0..5 (button 1 drawn 1 px lower when
             * hovered, compensated in the icon Y) with a cross icon overlay if the weapon is not producible
             * (buttons 1..5 shift the icon 4 px left); -3 draws the Exit button. The same local holds the icon Y
             * offset and, in the Exit path, the text X.
             */
            void __cdecl MenuItemRenderFunction_DisableWeapon_Main(int param_1, ...);

        } // namespace DisableWeapon
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
