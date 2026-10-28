/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/MissionEndscreen.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace MissionEndscreen {

            /**
             * Skirmish/multiplayer end-screen click handler: when the overlay flag isExtremeTrailGame is clear, -0x65
             * switches to the second page of the current pair (DAT_EndscreenStatsPage 0/1 -> 1, 2/3 -> 3) and -100 to the
             * first (-> 0 or 2), mirrored in activeMenuTab; -1 requests leaving (INT_00ed279c=1) or, with the
             * overlay shown, blacks the screen and closes it; -2 (as column 0) and column headers clear the overlay
             * flag and set the results sort column DAT_FinalResultsOrderByColumn.
             */
            void __cdecl MenuItemActionHandler_MissionEndscreen_Main(int param_1, ...);

            /**
             * Skirmish/multiplayer end-screen button render (disabled outside GM_SKIRMISH_AND_MULTIPLAYER; item -2,
             * and in the Extreme trial the page arrows -100/-101, are enabled but not drawn): draws the page arrows
             * -100/-101 disabled (frame +2) when already on that page of the pair, highlights the column header
             * (items 0..15) matching DAT_FinalResultsOrderByColumn (frame +0xE for columns < 0xD, else +1), records
             * the hovered column in endscreenHoveredColumn (0x10/0x11 for -1/-10), otherwise renders the standard
             * button.
             */
            void __cdecl MenuItemRenderFunction_MissionEndscreen_Main(int param_1, ...);

        } // namespace MissionEndscreen
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
