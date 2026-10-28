/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/Roundtable.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace Roundtable {

            /**
             * Action handler of the multiplayer 'round table' alliance screen (host only). Clicking a portrait slot
             * 1-8 selects it; with a slot selected, a further slot click is treated as id+10 and targets player
             * RoundTableOrderArray[id-10]: if both players are active and the target has no team both get a new
             * team (highest team + 1) and, with 3+ active players, a random genie ally line plays; otherwise the
             * selected player joins the target's team (genie one-off remarks when the selected player is AI type 1
             * or 7 and 3+ players). Clicking the selected slot again keeps it selected once (g_roundtableSameSlotClickedOnce), any
             * other target click re-orders teams and deselects. 0x15 removes the selected player from its team, 100
             * confirms (closes, reorders, 'The sides are drawn' if any team), 0x65 cancels by restoring the backup
             * team array, 200 deselects, 0xC9 deselects and 0xCA deselects unless the same-slot flag is set.
             */
            void __cdecl MenuItemActionHandler_Roundtable_Main(int param_1, ...);

            /**
             * Render callback of the round-table screen. Slots 1-8 draw the occupant's shield (0x222+player),
             * portrait (AI icon, default lord icon or custom face), dim when selected, hover frame, team badge and
             * name (AI name from TEXT_XPLAY_WAITING_ROOM or player name, in player colour); empty slots are flagged
             * disabled and non-hosts cannot click. Target slots (ids 9-0x12) show an alliance marker when hovering
             * a valid target, 0x14 draws the blended background, 100/0x65 are disabled while a slot is selected or
             * for non-hosts, and 200 draws the selected player's portrait following the mouse (clamped to the
             * menu).
             */
            void __cdecl MenuItemRenderFunction_Roundtable_Main(int param_1, ...);

        } // namespace Roundtable
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
