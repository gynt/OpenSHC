/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/Siege/SiegeGameModeRelatedSection.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {
    namespace Siege {

#pragma pack(push, 1)
        // SIZE: 0x0000001C
        typedef struct SiegeGameModeRelatedSection {

            // attacking-force siege engine count -> attack slot 0 (M_MAPPER_CATAPULT)
            int catapults; // 0x00000000 length: 4
            // siege engine count -> attack slot 1 (M_MAPPER_TREBUCHET)
            int trebuchets; // 0x00000004 length: 4
            // siege engine count -> attack slot 3 (M_MAPPER_SIEGE_TOWER)
            int siegeTowers; // 0x00000008 length: 4
            // siege engine count -> attack slot 2 (M_MAPPER_BATTERING_RAM)
            int batteringRams; // 0x0000000C length: 4
            // siege engine count -> attack slot 4 (M_MAPPER_PORTABLE_SHIELD)
            int portableShields; // 0x00000010 length: 4
            // siege engine count -> attack slot 8 (AttackInfoDefinedData siege mapper 358, engine type unverified)
            int siegeEngineSlot8Count; // 0x00000014 length: 4
            int tunnelersCount; // 0x00000018 length: 4

        } SiegeGameModeRelatedSection;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(SiegeGameModeRelatedSection) == 28, SiegeGameModeRelatedSection);
    } // namespace Siege
} // namespace Game
} // namespace OpenSHC
