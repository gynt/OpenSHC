/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/AiLordSelect.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace AiLordSelect {

            /**
             * AI lord selection modal action: button 100 resets the mouse and closes it. Otherwise (button <=
             * available AI count) puts the chosen AI lord into the first free player slot 1-8 (closes the dialog if
             * none is free), resets its variation, queues a resync command, plays AI speech 0x16 and reorders
             * teams. The dialog stays open for more picks unless all 8 slots are now filled, in which case it
             * resets the mouse and closes.
             */
            void __cdecl MenuItemActionHandler_AiLordSelect_Main(int param_1, ...);

            /**
             * AI lord selection modal render: button 100 renders the generic button; button 1 first clears the
             * hovered AI; buttons beyond the available AI count are hidden (DAT_ButtonDisabled=1); otherwise
             * draws the frame (icon 0x22B) and the AI lord's portrait (icon 0x20A + lord id), plus a highlight when
             * hovered, remembering that AI as hovered.
             */
            void __cdecl MenuItemRenderFunction_AiLordSelect_Main(int param_1, ...);

        } // namespace AiLordSelect
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
