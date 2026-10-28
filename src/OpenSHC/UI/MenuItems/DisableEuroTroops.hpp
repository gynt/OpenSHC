/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/DisableEuroTroops.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace DisableEuroTroops {

            /**
             * Scenario editor 'disable European troops' handler: a troop button toggles barracksRecruitability[i]
             * (decompiled as SEC_MercRecruitable[i-7]: the instruction XORs the word at 0x1653DDA+2*i, which is the
             * 7-short barracksRecruitability array directly before SEC_MercRecruitable at 0x1653DE8); -3 returns to
             * building availability.
             */
            void __cdecl MenuItemActionHandler_DisableEuroTroops_Main(int param_1, ...);

            /**
             * Render of 'disable European troops' dialog: draws troop buttons (button 2 shifted 8 px left while
             * drawing) and a cross overlay when barracksRecruitability[i] (decompiled as SEC_MercRecruitable[i-7])
             * is 0; -3 draws the Exit button.
             */
            void __cdecl MenuItemRenderFunction_DisableEuroTroops_Main(int param_1, ...);

        } // namespace DisableEuroTroops
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
