/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/RankingGames.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace RankingGames {

            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            /**
             * Action handler of the skirmish ranking/leaderboard screen. -10/-11 scroll the 8-row list; row buttons
             * 0-7 load that record's final statistics into GameSynchronyState.finalResults, choose the win/lose
             * screen image by result and lord type (crusader/arab) and show the end-of-game screen; 0x28+ ask to
             * delete a record; 0xB returns to lobby or crusade map; 0x14-0x1D pick/toggle the sort column,
             * 0x1E/0x1F toggle sort mode 1/2, then rebuild the view and clamp the scroll offset.
             */
            void __cdecl MenuItemActionHandler_RankingGames_Main(int param_1, ...);

            /**
             * Render callback of the skirmish ranking screen. -10/-11 draw the scroll up/down arrow icons
             * (INTERFACE_ICONS3 0x55/0x51, +1 when hovered) with a border; column headers 0x14-0x1D and sort-mode
             * buttons 0x1E/0x1F are drawn in their pressed picture (+2) when they are the active sort column/mode,
             * otherwise generically; the hovered header id (0x14-0x1F) is remembered in DAT_RankingGamesHoveredButton. Row ids 0-7
             * draw nothing here.
             */
            void __cdecl MenuItemRenderFunction_RankingGames_Main(int param_1, ...);

            /**
             * Scrollbar callback of the ranking list: event 1 init (0..1), 2/3 set g_rankingGamesScrollOffset from
             * the thumb, 4 refresh (max = g_leaderboardEntryCount-8, clamped at 0), 5/6 scroll up/down by one, 7
             * returns page step 6. The item parameter is unused.
             */
            void __cdecl MenuItemActionHandler_RankingGames_Scrollbar(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            /**
             * Render callback of the ranking list scrollbar: black background, standard scrollbar with thumb, soft-
             * yellow border; also clears the disabled flag. The item parameter is unused.
             */
            void __cdecl MenuItemRenderFunction_RankingGames_Scrollbar(
                int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged);

        } // namespace RankingGames
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
