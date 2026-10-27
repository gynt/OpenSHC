/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/OptionsMenu.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace OptionsMenu {

            /**
             * Render callback of the in-game options menu buttons (TEXT_GAME_OPTIONS[id]). Load (2), Save (3),
             * Briefing (0x27) and Restart Mission (0x2C) are drawn greyed when not allowed: e.g. dead player in
             * single player, editor/Siege-That/tutorial modes, non-host saving in multiplayer, briefing only for
             * campaign/economic/scenario missions.
             */
            void __cdecl MenuItemRenderFunction_OptionsMenu_Buttons(int param_1, ...);

            /**
             * Render callback of the options sub-menu buttons: draws the button and TEXT_GAME_OPTIONS[id] centred,
             * normal colour when idle and highlighted with shadow when hovered.
             */
            void __cdecl MenuItemRenderFunction_OptionsMenu_SubOptionsButtons(int param_1, ...);

            /**
             * Action handler of the options sub-menu: copies current settings into MenuTextInputState and opens the
             * matching dialog - 4 video (resolution, zoom, scroll speed, cursor), 5 sound (voice, sound on, stream
             * volumes 0/1/3), 6 network, 0x19 gameplay (speed, bubble help, unused option), 0x2D identity (name
             * text input); 0x11 pops the dialog.
             */
            void __cdecl MenuItemActionHandler_OptionsMenu_SubOptionsButtons(int param_1, ...);

            /**
             * Action handler of the in-game options menu: 2 Load / 3 Save (open the load/save dialog when allowed
             * by game mode, death state and host status), 7 Quit (multiplayer: online quit dialog, otherwise like
             * 9) and 9 Exit play the quit speech and open a yes/no confirm with the action id stored, 10 resumes,
             * 0x18 opens the options sub-menu, 0x1A opens in-game help, 0x27 opens the mission briefing
             * (campaign/scenario missions), 0x2C opens a restart-mission confirm when allowed.
             */
            void __cdecl MenuItemActionHandler_OptionsMenu_Buttons(int param_1, ...);

        } // namespace OptionsMenu
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
