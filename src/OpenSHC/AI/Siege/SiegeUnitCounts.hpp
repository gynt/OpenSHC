/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/AI/Siege/SiegeUnitCounts.hpp'
*/

#pragma once

namespace OpenSHC {
namespace AI {
    namespace Siege {

#pragma pack(push, 1)
        // SIZE: 0x00000050
        typedef struct SiegeUnitCounts {

            int archers; // 0x00000000 length: 4
            // siege/starting-army unit count, index 1 (UT_E_XBOW); array also read as mapAndTime.startGoods[0x19+i]
            // in spawnQueuedReinforcementWaves
            int crossbowmen; // 0x00000004 length: 4
            // unit count, index 2 (UT_E_SPEAR)
            int spearmen; // 0x00000008 length: 4
            // unit count, index 3 (UT_E_PIKE)
            int pikemen; // 0x0000000C length: 4
            // unit count, index 4 (UT_E_MACE)
            int macemen; // 0x00000010 length: 4
            // unit count, index 5 (UT_E_SWORD)
            int swordsmen; // 0x00000014 length: 4
            // unit count, index 6 (UT_E_KNIGHT)
            int knights; // 0x00000018 length: 4
            // unit count, index 7 (UT_E_LADDER)
            int laddermen; // 0x0000001C length: 4
            // unit count, index 8 (UT_E_ENGINEER)
            int engineers; // 0x00000020 length: 4
            // unit count, index 9 (UT_E_MONK)
            int monks; // 0x00000024 length: 4
            // unit count, index 10 (UT_A_ARCHER)
            int arabianArchers; // 0x00000028 length: 4
            // unit count, index 11 (UT_A_SLAVE)
            int slaves; // 0x0000002C length: 4
            // unit count, index 12 (UT_A_SLINGER)
            int slingers; // 0x00000030 length: 4
            // unit count, index 13 (UT_A_ASSASSIN)
            int assassins; // 0x00000034 length: 4
            // unit count, index 14 (UT_A_HARCHER)
            int horseArchers; // 0x00000038 length: 4
            // unit count, index 15 (UT_A_SWORDSMAN)
            int arabianSwordsmen; // 0x0000003C length: 4
            // unit count, index 16 (UT_A_FIRETHROWER)
            int fireThrowers; // 0x00000040 length: 4
            // unit count, index 17 (UT_S_FBALLISTA)
            int fireBallistas; // 0x00000044 length: 4
            // unit count slot 18; spawnQueuedReinforcementWaves switch has no case for it (only 0..17); included in
            // sumUnitPoints
            int unknownUnitCount18; // 0x00000048 length: 4
            // unit count slot 19; no spawn case (only 0..17); included in sumUnitPoints
            int unknownUnitCount19; // 0x0000004C length: 4

        } SiegeUnitCounts;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(SiegeUnitCounts) == 80, SiegeUnitCounts);
    } // namespace Siege
} // namespace AI
} // namespace OpenSHC
