/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Buildings/BuildingFailReasonEnum.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Buildings {
        typedef enum BuildingFailReasonEnum {

            BFRE_MISSING5 = -5, // 0x-0000005
            BFRE_MISSING4 = -4, // 0x-0000004
            BFRE_MUST_BE_PLACED_ON_OASES = -3, // 0x-0000003
            BFRE_MISSING2 = -2, // 0x-0000002
            BFRE_DEFAULT_CANT_PLACE_THAT_THERE1 = -1, // 0x-0000001
            BFRE_DEFAULT_CANT_PLACE_THAT_THERE = 0, // 0x00000000
            BFRE_NOT_ENOUGH_WORKERS = 1, // 0x00000001
            BFRE_WORKSHOP_NOT_AGAINST_WALL = 2, // 0x00000002
            BFRE_NOT_ADJ_STOCKPILE = 3, // 0x00000003
            BFRE_NOT_ADJ_ARMORY = 4, // 0x00000004
            BFRE_NOT_IRON_ORE = 5, // 0x00000005
            BFRE_NOT_OIL_MARSH = 6, // 0x00000006
            BFRE_NOT_ADJ_GRANARY = 7, // 0x00000007
            BFRE_NOT_ADJ_BARRACKS = 8, // 0x00000008
            BFRE_TOO_CLOSE_TO_ENEMY = 9, // 0x00000009
            BFRE_GRANARY_FULL = 10, // 0x0000000A
            BFRE_STOCKPILE_FULL = 11, // 0x0000000B
            BFRE_ARMORY_FULL = 12, // 0x0000000C
            BFRE_FARM_NOT_ON_VALLEY_FLOOR = 13, // 0x0000000D
            BFRE_LAND_INACCESSIBLE = 14, // 0x0000000E
            BFRE_TOO_FAR = 15, // 0x0000000F
            BFRE_NOT_ADJ_CASTLE_WALLS = 16, // 0x00000010
            BFRE_TOO_CLOSE_TO_ENEMY_2 = 17, // 0x00000011
            BFRE_TOO_FAR_2 = 18, // 0x00000012
            BFRE_NOT_NEXT_TO_WALL = 19, // 0x00000013
            BFRE_TOO_CLOSE_TO_ENEMY_TO_DELETE = 20, // 0x00000014
            BFRE_TOO_CLOSE_TO_SIGNPOST = 21, // 0x00000015
            BFRE_FARM_NOT_ON_OASIS = 22, // 0x00000016
            BFRE_LAND_NOT_FERTILE = 23, // 0x00000017
            BFRE_STRUCTURE_WAS = 24, // 0x00000018
            BFRE_THIS_WAS_A_HOVEL = 25, // 0x00000019
            BFRE_TOO_MANY_DOG_CAGES = 1000 // 0x000003E8

        } BuildingFailReasonEnum;

        static_assert_cpp98_obj(sizeof(BuildingFailReasonEnum) == 4, BuildingFailReasonEnum);
    } // namespace Buildings
} // namespace Map
} // namespace OpenSHC
