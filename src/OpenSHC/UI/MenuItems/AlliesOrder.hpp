/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/AlliesOrder.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace AlliesOrder {

            /**
             * Allies-order modal render: buttons 1-6 draw the portrait of enemy
             * DAT_AllyMenuSelectionArray[button] (slots 1..6 hold enemy player ids; empty slots >=
             * DAT_EnemyArrayIndex get a black border box) with a hover highlight that also sets the 'attack
             * <player>' tooltip and g_alliesOrderTargetPlayer; 10 first clears the tooltip each frame, then 10/11
             * set tooltip texts (group 0xE0, 8/9) on hover; -2 draws a plain button; -1 renders the tooltip,
             * appending the target's player name or AI name for the attack tooltip.
             */
            void __cdecl MenuItemRenderFunction_AlliesOrder_Main(int param_1, ...);

            /**
             * Allies-order modal action: for an enemy button (1-6, within DAT_EnemyArrayIndex) or a general order
             * button (>6), and only if the selected ally is human or an active AI, queues a player-to-player
             * request of type 0 (param1 = enemy target or 0, param2 = ally, param3 = current player, param4 =
             * button); then closes the dialog, or for button 10 returns to the Allies modal. -2 also returns to the
             * Allies modal.
             */
            void __cdecl MenuItemActionHandler_AlliesOrder_Main(int param_1, ...);

        } // namespace AlliesOrder
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
