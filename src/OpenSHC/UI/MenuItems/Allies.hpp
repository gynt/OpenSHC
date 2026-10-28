/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/Allies.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace Allies {

            /**
             * Allies modal render callback, dispatched on the button index. 1-6: ally portrait (shield + lord icon
             * / AI face / bitmap face, selected ally highlighted, others blended) with badges for a pending goods
             * request, 'help needed' and the ally's current Attack/Defend order. 10: info panel of the selected
             * ally (name, requested goods + amount, its order 'No Orders'/'Attack'+target/'Defend', 'Help Needed!',
             * and - if that ally ordered YOU to attack - the attack target). 0x14-0x16 set the hover tooltip id,
             * 200 draws it; 0x6E/0x6F (reply buttons) are shown only when the selected ally asked you to attack or
             * needs help; 100 does nothing; with no allies every button except -1 is hidden.
             */
            void __cdecl MenuItemRenderFunction_Allies_Main(int param_1, ...);

            /**
             * Allies modal action handler: -1/100 close the dialog; 0-6 run RecalculateAllies and select ally
             * (button-1) if it exists; 0x14 opens the order dialog; 0x15 opens the send-goods dialog pre-filled
             * with the selected ally's pending goods request (goods index = request-1, amount) and sets
             * g_alliesHasMultipleAllies to whether such a request exists; 0x16 opens the request-goods dialog with
             * nothing selected; 0x6E/0x6F queue a player-to-player request of type 4 / 5 to the selected ally.
             */
            void __cdecl MenuItemActionHandler_Allies_Main(int param_1, ...);

        } // namespace Allies
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
