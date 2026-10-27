/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/RankingGames.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace RankingGames {

            /**
             * Prepare handler of the ranking-games (skirmish masters leaderboard) view: prepares leaderboard data,
             * clears the hovered button, loads frontend_combat3.tgx and shc_back and remembers the current game
             * mode.
             */
            void __cdecl MenuView_RankingGames_Prepare();

            /**
             * Per-frame handler of the ranking-games leaderboard: draws 8 rows from the scroll offset (rank, custom
             * map name or quoted trail-mission name truncated with '...', date, duration as
             * gameDurationInMinutes/60 ':' %60, local lord icon then the other players' icons grouped by team - own
             * team first, teams 1-4, then teamless - with separators, skulls for dead, alive/dead marker and
             * skMasterScore). Highlights the hovered row and shows the click/delete hint plus its trail and mission
             * number ('T / N.': index <0x33 -> '1 / index', <0x51 -> '2 / index-0x32', else '3 / index-0x50') and
             * quoted mission name, the game count or 'No Games Found', and the filter/sort header text depending on
             * the hovered button or current sort column.
             */
            void __cdecl MenuView_RankingGames_DoEveryFrame();

        } // namespace RankingGames
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
