/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuModals/GreatestLord.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace GreatestLord {

            /**
             * Renders the multiplayer ranking ('Greatest Lord') modal: tiled frame and inner box, then builds a
             * table of active players (finalResults.active, players 1..8), 3 ints per entry {playerId, primaryKey,
             * secondaryKey}: tableSortBy 1 = gold then army size ('Sorted by gold'), 0 = army size then gold
             * ('Sorted by troops'), -1 = ComputePlayerPoints1 only ('Greatest Lord'); a player with no living lord
             * once mapTimeInTicks > section1127+200 gets keys 0 and an eliminated flag. A selection sort
             * (descending primary key, ties by higher secondary key) writes the rank order; each rank row shows the
             * team icon or the eliminated icon, the name in the player colour and, if not eliminated, gold and army
             * size; finally the sort caption.
             */
            void __cdecl MenuModalRenderFunction_GreatestLord(int x, int y, int width, int height);

        } // namespace GreatestLord
    } // namespace MenuModals
} // namespace UI
} // namespace OpenSHC
