/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/SelectCrusade.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace SelectCrusade {

            /**
             * Action handler of the 'select crusade / skirmish' menu. -1 returns to main menu; 1/3/4 clear
             * GameCore.field22 and pick a crusade trail type (4 = TT_EXTREME, 3 -> trail type 1, 1 -> 0) then open
             * the crusade map; 2 sets up a custom single-player skirmish lobby (opens lobby view, host,
             * GM_SKIRMISH_SINGLE_PLAYER, clears all player names, copies the local player name into slot 1, queues
             * slot assignment, sets all 9 slot flags to 1).
             */
            void __cdecl MenuItemActionHandler_SelectCrusade_Main(int param_1, ...);

            /**
             * Render callback of the select-crusade menu buttons: rendering button -1 first resets
             * DAT_HighlightedSkirmishType to 0, then any hovered button stores its id there (so the menu knows
             * which trail is highlighted); the button itself is drawn with the generic renderer.
             */
            void __cdecl MenuItemRenderFunction_SelectCrusade_Main(int param_1, ...);

        } // namespace SelectCrusade
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
