/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/NewEventAction.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace NewEventAction {

            /**
             * Action handler of the 'new event action' dialog. 0x25 returns to the new-event dialog. Buttons
             * 0x80-0x9B and 0xB1-0xBB (mapped to 0x9C-0xA6) select scenario action type id-0x80; on a change
             * actionData and repeat are cleared, repeatMonths = 10, and actionData = -1 for types 2/0x1A/0x1B. For
             * value actions (0x84/0x8B/0x91/0xB3 max 10, 0x92/0x94 max 50, 0xB2 max 100) it sets actionData to 1 if
             * it is 0, configures the overlay slider (min 1) on actionData and stores the slider position (button
             * X+0x3A, Y+0x1C) plus a countdown of 2 that the render function uses to open it.
             */
            void __cdecl MenuItemActionHandler_NewEventAction_Main(int param_1, ...);

            /**
             * Render callback of the 'new event action' dialog. 0x25 draws OK; 0x26/0x27/0x28 all draw label 0x28
             * and are shown only for action types 0x1B/0x1A/2 respectively (else flagged disabled); unknown ids are
             * not drawn. Action-type buttons (0x80-0x9B, 0xB1-0xBB) draw their TEXT_SCENARIO label (0x92 and 0x94
             * share label 0x92, with ' - ' and INTERFACE_ICONS2 icon 0x82/0x80), highlighted when selected; the
             * selected one counts down the pending slider delay and opens the overlay slider at the stored
             * position, and value actions print actionData (0xB2 with '%').
             */
            void __cdecl MenuItemRenderFunction_NewEventAction_Main(int param_1, ...);

        } // namespace NewEventAction
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
