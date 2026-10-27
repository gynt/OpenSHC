/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/SFX.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        /**
         * Computes a player's 'greatest lord' score: (raw goods value: wood, hops, stone, iron, partial pitch
         * (RT_PARTIALPITCH, slot 8), ale, flour)/10 + (weapons and armour value)/10 + (food value: bread, apples,
         * meat, cheese)/10 + population*10 + totalTroopValue + gold/10, where each goods value is stock *
         * getSalePriceOfGood. Wheat and RT_PITCH (7) are not counted.
         */
        int __cdecl ComputePlayerPoints1(int playerID);

        /**
         * Rates the ratio of two values (both clamped to >= 1) for Genie speech: if the first is larger, ratio
         * first*100/second gives 0 below 150%, then 1..7 in 20% steps (150,170,190,210,230,250,270%); otherwise the
         * inverse ratio gives 0 below 150%, -1 (<190%), -2 (<240%) or -3. Parameter names are misleading: the
         * caller passes (unit value killed by the local player, unit value lost by the local player), not values
         * ordered by size; positive = local player winning.
         */
        int __cdecl UpdateUnitLossSpeechFeedback_RelativeValueForGenie(int larger, int smaller);

        /**
         * Returns the 1-based rank of playerID by ComputePlayerPoints1 among active players (finalResults.active);
         * players without a living lord score 0, and 0 is returned if playerID itself has no living lord or is not
         * found. Uses repeated selection of the highest remaining score.
         */
        int __cdecl ComputePlayerRanking(int playerID);

        /**
         * Per-tick Genie battle commentary (build view only, local player alive and lord not killed, not campaign):
         * shifts the 10-entry histories and records this interval's unit value killed by the local player
         * (unitValueKilledByCurrentPlayer - misnamed) and the local player's losses per killing player
         * (currentPlayerUnitValueLostToPlayer) plus their sum. When a fight has just died down (>= 151 combined over
         * the previous two intervals, <= 49 now) it rates short-term (previous 2 intervals) and long-term (previous
         * 9 intervals) kill/loss ratios and, if genieVoiceActive, plays 'valiant effort' (both 0), praise
         * (Genie_30..39) or defeat lines (Genie_42..44); on a heavy defeat the enemy (other team) that killed the
         * most of the local player's units in the history plays its victory video. Also says 'Where is your castle'
         * when > 5 buildings were destroyed recently.
         */
        void __cdecl UpdateUnitLossSpeechFeedback();

        /**
         * Returns ComputePlayerRanking for the local player slot.
         */
        int __cdecl ComputeCurrentPlayerRanking();

    } // namespace SFX
} // namespace Audio
} // namespace OpenSHC
