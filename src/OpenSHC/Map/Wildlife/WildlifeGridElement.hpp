/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Wildlife/WildlifeGridElement.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Wildlife {

#pragma pack(push, 1)
        // SIZE: 0x000000A0
        typedef struct WildlifeGridElement {

            // [172 0x0052BA10] incremented once per valid map tile in the 10x10 cell; elsewhere used as the 'cell
            // exists' test
            int validTileCount; // 0x00000000 length: 4
            // [172 0x0052BA10] set to the most frequent PathConnectionLayer value among the cell's tiles
            int dominantPathAreaId; // 0x00000004 length: 4
            int unclaimedArea; // 0x00000008 length: 4
            // Number of tiles in the cell covered by a building other than a signpost; seeds the danger flood fill
            // and blocks deer/lion rally points.
            int buildingTileCount; // 0x0000000C length: 4
            int keeps; // 0x00000010 length: 4
            // Number of wall tiles (LogicLayer 0x100) in the cell.
            int wallTileCount; // 0x00000014 length: 4
            int trees; // 0x00000018 length: 4
            int unitCount; // 0x0000001C length: 4
            // Number of animal units (isStalked != 0) standing in the cell.
            int animalCount; // 0x00000020 length: 4
            int camelCount; // 0x00000024 length: 4
            int lionCount; // 0x00000028 length: 4
            int deerCount; // 0x0000002C length: 4
            // Number of non-animal units in the cell ("Humans" debug view); seeds the danger flood fill.
            int humanCount; // 0x00000030 length: 4
            // Flood-filled danger value: 2 from cells with humans/buildings, 3 from lions, decreasing by 1 per cell
            // ("Mankind" debug view); animals avoid such cells.
            int dangerInfluence; // 0x00000034 length: 4
            // [172 0x0052CAB0] BFS value decreasing from the leader cell, used to pick route steps
            int routeBfsValue; // 0x00000038 length: 4
            // Cleared together with casDisRelated2 before each rally-point BFS; marks cells already used on an
            // animal route.
            int routeVisited; // 0x0000003C length: 4
            // Number of tiles with LogicLayer bit 0x20000000 in the cell; non-zero makes deer flee and blocks
            // rabbit spawning.
            int flag20000000TileCount; // 0x00000040 length: 4
            // Number of tiles with LogicLayer bits 0x20000/0x80/0x40000 in the cell; deer flee when > 20.
            int disturbedTileCount; // 0x00000044 length: 4
            // Humans plus panicking deer in the cell ("Panic" debug view); makes deer herds start fleeing.
            int panicSourceCount; // 0x00000048 length: 4
            // Number of farm field tiles (LogicLayer 0x1000000/0x2000000) in the cell ("Farmland" debug view);
            // seeds farmlandInfluence.
            int farmlandTileCount; // 0x0000004C length: 4
            // Flood-filled value (6 from farmland cells, decreasing) used to route rabbits towards farms
            // (buildRallyPointPathForTribe).
            int farmlandInfluence; // 0x00000050 length: 4
            int rabbitCount; // 0x00000054 length: 4
            // [172 0x0052BA10] counts tiles whose path area equals the campground area of a slot with a human
            // player ID (debug view 'Chimps'); not units
            int humanPlayerAreaTileCount; // 0x00000058 length: 4
            int castlebuildings; // 0x0000005C length: 4
            // Recomputed per tick: (keep-area tiles present) * ((keeps != 0) + (castlebuildings != 0)); seed of the
            // castle zone ("Siege" debug view).
            int castleCoreScore; // 0x00000060 length: 4
            // Castle zone grown 20 iterations from castleCoreScore over cells with castle buildings
            // (updateSection1034Info); flood-fills unknownNonZero01.
            int castleZoneSpread; // 0x00000064 length: 4
            // [173 0x0052D720] decaying BFS gradient (seed 6, -1 per step) around cells with
            // field24_0x60/field25_0x64 set; 0 = outside the zone
            int zoneProximity; // 0x00000068 length: 4
            // Set when the cell is outside the castle zone and isSuitableWildlifeSpawnCell accepts it (candidate
            // siege camp / spawn cell; red in "Siege" view).
            int siegeCampSuitable; // 0x0000006C length: 4
            // Sum of tile heights in the cell; divided by 100 in updateWildlife to give the average height.
            int heightSum; // 0x00000070 length: 4
            // 0/1 visited flag (incremented once per new cell, distance lives in routeBfsValue); review 356
            // verified offsets Flood-filled distance from the signpost (floodFillCasDisFromSignpost, "Slink" debug
            // view).
            int reachedFromSignpost; // 0x00000074 length: 4
            undefined1 padding_0x78[40]; // 0x00000078 length: 40

        } WildlifeGridElement;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(WildlifeGridElement) == 160, WildlifeGridElement);
    } // namespace Wildlife
} // namespace Map
} // namespace OpenSHC
