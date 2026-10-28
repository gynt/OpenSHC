/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/GreatestLord.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace GreatestLord {

        /**
         * Builds a rank->player table for all occupied (human or AI) slots 0..8 using ComputePlayerRanking (rank r
         * stored at index r) and returns the player at index rankingPosition+1 (so 0 = first place), or -1 if none.
         */
        int __cdecl GetPlayerAtRank(int rankingPosition);

        /**
         * If the first-ranked player is a non-zero slot controlled by AI, returns its aiType - 1, else 0 (ambiguous
         * with the first AI type).
         */
        int __cdecl IfAiGreatestLordGetAiType();

        /**
         * Counts players 1..8 that still have a living lord and returns GetPlayerAtRank(count - 1), i.e. the
         * lowest-ranked surviving player assuming living players rank above dead ones.
         */
        int __cdecl GetLowestRankedAlivePlayer();

        /**
         * Skirmish-master score for a player: base = buildingsDestroyedWeighted*100 + gold/10 +
         * troopsKilledWeighted; score = (base + killedLords*base/4) * 200 / (gameMonths + 200), gameMonths = months
         * between start and end, at least 1.
         */
        int __cdecl ComputeSkMasterScore(int playerID);

    } // namespace GreatestLord
} // namespace UI
} // namespace OpenSHC
