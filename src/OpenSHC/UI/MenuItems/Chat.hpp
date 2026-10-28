/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/Chat.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace Chat {

            /**
             * Render callback for chat dialog buttons: id >= 0 draws a captioned button
             * TEXT_MULTIPLAYER_CONNECTION[id] (the merged locals are just the text call arguments there). Negative
             * id = recipient toggle for player slot -id: hidden when that slot's entry at GameSynchronyState+0x6a8
             * is -1; otherwise draws the player name truncated at 170 px in the player's colour, pressed while
             * DAT_ChatMessageReceiverArray[slot] is set, and when the slot's team has more than one player a small
             * colour box for every team member.
             */
            void __cdecl MenuItemRenderFunction_Chat_MostButtons(int param_1, ...);

            /**
             * Action handler for chat recipient buttons: for negative ids XOR-toggles
             * DAT_ChatMessageReceiverArray[-id] (shown by Ghidra as a raw GameSynchronyState+0x109264 offset);
             * always forces the local player's own receiver flag to 1.
             */
            void __cdecl MenuItemActionHandler_Chat_SendMessageToPlayer(int param_1, ...);

            /**
             * Render callback for taunt buttons: draws a basic button with the taunt number and, while hovered,
             * sets DAT_InsultTextIndex so that taunt's text is shown.
             */
            void __cdecl MenuItemRenderFunction_Chat_TauntButtons(int param_1, ...);

            /**
             * Action handler for chat recipient/send buttons: negative id selects only player -id; 0x1f all
             * players; 0x20 none; 0x21 sends the typed text via GCT_TAUNT_OR_CHAT and closes the dialog unless it
             * is empty or all spaces; 0x22 closes; 0x23 selects the players of the local player's team (slots 1-8);
             * 0x45 opens the allies dialog (Genie_11). The local player's own receiver flag is always set.
             */
            void __cdecl MenuItemActionHandler_Chat_RecipientAndSendButtons(int param_1, ...);

            /**
             * Action handler for taunt buttons: stores the taunt number in DAT_ChatTauntOrMessage and queues
             * GCT_TAUNT_OR_CHAT.
             */
            void __cdecl MenuItemActionHandler_Chat_TauntButtons(int param_1, ...);

        } // namespace Chat
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
