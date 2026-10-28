/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/WildlifeState.hpp'
*/

#pragma once

#include "OpenSHC/Map/Wildlife/WildlifeGridElement.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Wildlife::WildlifeGridElement;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x00040110
    class WildlifeState {
    public:
        WildlifeGridElement grid[40][40]; // 0x00000000 length: 256000
        int DAT_DebugDataMapDataDisplayType; // 0x0003E800 length: 4
        // [172 0x0052C570] holds the value of the dequeued cell during flood fill
        undefined4 floodCurrentValue; // 0x0003E804 length: 4
        // [172 0x0052C570] dequeue index of circular queue wrapping at 0x640
        undefined4 floodQueueHead; // 0x0003E808 length: 4
        // [172 0x0052C570] enqueue index of circular queue wrapping at 0x640
        undefined4 floodQueueTail; // 0x0003E80C length: 4
        // Y half of the BFS queue (with floodQueueX) in all three wildlife flood functions (review 356)
        short floodQueueY[1600]; // 0x0003E810 length: 3200
        // [172 0x0052C570] x coordinates of queued grid cells
        short floodQueueX[1600]; // 0x0003F490 length: 3200

    private:
        WildlifeState(WildlifeState const&);
        void operator=(WildlifeState const&);

    public:
        WildlifeState() {};
        ~WildlifeState() {};

        // Constructor
        /**
         * Constructor of the global DAT_WildlifeState: clears it via clearWildlifeState and sets
         * DAT_DebugDataMapDataDisplayType = 8. Returns &DAT_WildlifeState.
         */
        WildlifeState* Constructor_WildlifeState();

        /**
         * Zeroes the whole 0x3E800-byte DAT_WildlifeState.
         */
        void clearWildlifeState();

        /**
         * Solitary mode only: recomputes row _y10 of the 40x40 wildlife grid (each cell 10x10 tiles). Per cell
         * counts valid tiles, tiles of unclaimed path area (0), tiles whose path area equals a human player's
         * campground area (once per matching player), height sum, logic-flag tallies, trees (types 1..4),
         * keeps/campgrounds, gate/tower tiles, non-signpost building tiles, and units: those with isStalked==0
         * (workers/soldiers) vs isStalked!=0 (animals, women, children, entertainers) further split into
         * deer/rabbit/camel/lion; finally sets separateAreaID to the most frequent path area of the cell.
         */
        void updateWildlifeGrid(int _y10);

        /**
         * Debug overlay: draws the label of the selected DebugDataMapData display type (Connect, Chimps, Farmland,
         * Humans, Mankind, Deer, Route, Panic, Siege, Slink), a 41x41-line grid of 10-px cells, and fills each
         * wildlife grid cell with validTileCount > 0 with a colour chosen from that cell's fields for the selected
         * view.
         */
        void renderDebugDataMapData(int x, int y, int width, int height);

        /**
         * BFS flood fill on the 40x40 wildlife grid: seeds cell (x,y) with value, then spreads value-1 to the 8
         * neighbours (clockwiseCardinalTranslationMatrix, unrolled 4 per iteration) that exist and hold a lower
         * field13_0x34, using the shared 1600-entry circular queue; returns as soon as a dequeued value is below 2.
         */
        void floodFillField13FromCell(int seedX, int seedY, int seedValue);

        /**
         * BFS flood fill identical to floodFillField13FromCell but writing field20_0x50: seeds cell (x,y) with
         * value and spreads value-1 to the 8 neighbours that exist and hold a lower value, via the shared circular
         * queue; returns as soon as a dequeued value is below 2.
         */
        void floodFillField20FromCell(int seedX, int seedY, int seedValue);

        /**
         * Plans a wander route for an animal tribe: clears casDisRelated2 and field15_0x3c in all cells, BFS-fills
         * casDisRelated2 (seed always2or3or5, -1 per step) from the leader unit's cell over cells of the same path
         * area that are free of threats (mode 0: field13_0x34 == 0 and, for tribe type 13 only, no deer/lions; mode
         * 1: no humans, no buildings, no lions). Then from the leader cell repeatedly steps to the neighbour
         * (random start direction) with the smallest nonzero value below the current one, i.e. away from the
         * leader, zeroing and marking visited cells and appending the pathfinding-adjusted cell-centre tile to the
         * tribe's rallyPointArray.
         */
        void findAndSetNewRallyPointForDeerAndLions(int tribeID, int always2or3or5, int always0or1);

        /**
         * __thiscall (ECX = &DAT_WildlifeState, stack: tribeIndex, scoreThreshold; ret 8). Builds a wander path for
         * a tribe on the 40x40 coarse grid (cell = 10x10 tiles) starting at the cell of the tribe leader; returns
         * FALSE if that cell's farmlandInfluence is 0. Otherwise clears routeVisited/routeBfsValue, BFS-copies
         * farmlandInfluence into routeBfsValue for all cells reachable (8-neighbour) through populated cells with
         * farmlandInfluence > 0 in the start's dominantPathAreaId, resets the tribe's rally point count/index, then
         * hill-climbs: each step scans the 8 neighbours (scan start chosen once from SEC_RNG byte & 7), zeroes
         * every neighbour whose routeBfsValue beats the running threshold (initially scoreThreshold), moves to the
         * best one, marks it routeVisited and appends its centre tile (cell*10+5) to rallyPointArray when that
         * tile's byte in the 400x400 map at 0x21AEC98 is non-zero. Stops when no neighbour improves and returns
         * TRUE.
         */
        BOOLEnum buildRallyPointPathForTribe(int tribeIndex, int scoreThreshold);

        /**
         * __thiscall (ECX = WildlifeState*, stack: cellX, cellY; ret 8). Returns 1 if any of the 4 edge neighbours
         * (N, E, S, W; the loop steps clockwiseCardinalTranslationMatrix by 2 entries, skipping the diagonals) of
         * the coarse cell is in bounds, populated (firstMember > 0) and has field24_0x60 or field25_0x64 non-zero;
         * else 0.
         */
        undefined4 hasAdjacentCellWithField24Or25(int cellX, int cellY);

        /**
         * __thiscall (ECX = WildlifeState*, stack: cellX, cellY; ret 8). Returns 1 if the coarse cell has
         * unclaimedArea < 9, trees < 5, firstMember > 49 and at least one of its 4 edge neighbours (N, E, S, W) is
         * populated with unknownNonZero01 != 0; else 0. NAME? Its only caller, updateSection1034Info, uses it to
         * set field27_0x6c on open cells just outside the unknownNonZero01 zone; updateNofFpoints turns those cells
         * into AI attack staging points (attackInfo.nof_fpointsArray), so this is not about wildlife spawning.
         */
        undefined4 isAttackStagingCandidateCell(int cellX, int cellY);

        /**
         * __thiscall (ECX = WildlifeState*, stack: cellX, cellY, strength; ret 0xC). BFS flood fill on the coarse
         * grid: sets unknownNonZero01 = strength at the seed cell and gives value-1 to every 8-neighbour that is
         * populated, has unclaimedArea < 11 and a lower current value; stops as soon as a dequeued cell's value is
         * < 2. Uses the shared DAT_X10/Y10_Array_Section1034 ring queue (1600 entries).
         */
        void floodFillZoneProximityFromCell(int cellX, int cellY, int strength);

        /**
         * __thiscall (ECX = WildlifeState*, preserved). Clears routeBfsValue and signpostDistance on the coarse
         * grid, then BFS (8-neighbour) from the current attack signpost cell (tile/10), writing the step distance
         * into routeBfsValue (start = 1; returns early when a dequeued distance exceeds 99). Only populated cells
         * in the start's dominantPathAreaId with zoneProximity == 0 are entered; each entered cell gets
         * signpostDistance incremented once, so that field ends up a 0/1 reached flag (start cell stays 0). Returns
         * the >99 distance or the final queue head.
         */
        void floodFillCasDisFromSignpost();

        /**
         * Clears routeBfsValue, then BFS (8-neighbour) from the current attack signpost cell within its
         * dominantPathAreaId, writing step distance into routeBfsValue (start = 1). Returns the distance of the
         * first dequeued cell that has a populated same-area neighbour with zoneProximity != 0, i.e. the coarse-
         * grid distance from the signpost to the zone; returns 0 if the queue runs empty or the distance exceeds
         * 99.
         */
        int getDistanceFromAttackSignpostToZoneProximity();

        /**
         * Single-player only (currentGameMode == GM_SOLITARY). Pass 1 over all coarse cells: clears field13_0x34,
         * field20_0x50, field24_0x60 and field25_0x64, divides field28_0x70 by 100, and when chimps (+0x58) != 0
         * sets field24_0x60 = (keeps != 0) + (castlebuildings != 0). Pass 2 per cell (x, y):
         * floodFillField13FromCell(x, y, 2) if field12_0x30 or field3_0xc is set, else (x, y, 3) if lionCount is
         * set; and floodFillField20FromCell(x, y, 6) if field19_0x4c is set.
         */
        void updateWildlife();

        /**
         * __thiscall (ECX = WildlifeState*; the extraout_ECX values are just this, kept in ECX across the
         * __thiscall helpers). Single-player only. 20 passes over all cells: clear unknownNonZero01 and
         * field27_0x6c, and increment field25_0x64 of every cell with castlebuildings != 0 that has an edge
         * neighbour with field24_0x60 or field25_0x64 set (so the mark spreads through contiguous castle-building
         * cells and accumulates). Then floodFillUnknownNonZero01FromCell(x, y, 6) from every cell with field24_0x60
         * or field25_0x64 set, and finally increments field27_0x6c on each cell with unknownNonZero01 == 0 that
         * passes isSuitableWildlifeSpawnCell. NAME? Section1034 is only the shared BFS queue; the function builds
         * the zone gradient and the candidate layer read by updateNofFpoints.
         */
        void updateAttackCandidateLayers();

        /**
         * __thiscall (ECX = WildlifeState*). Single-player only, when the current attack signpost tile is valid:
         * runs floodFillCasDisFromSignpost, clears fields 0-3 of the 100-entry attackInfo.nof_fpointsArray and
         * resets nof_fpoints, then appends every coarse cell with field 0x6C (the flag before heightSum) set and
         * validTileCount > 0 whose centre tile (cell*10+5) is valid and in the same PathConnectionLayer region as
         * the signpost, as {tileX, tileY, 0, region, heightSum, routeBfsValue distance, score = (distance+4)*50 -
         * heightSum}; finally bubble-sorts the entries ascending by score. nof_fpoints is never compared against
         * the 100-entry capacity. The first test's MacroLayer[x + row + 0x13a06] is a decompiler rendering of
         * PathConnectionLayer[row + x - 10].
         */
        void updateNofFpoints();
    };

    static_assert_cpp98_obj(sizeof(WildlifeState) == 262416, WildlifeState);

#pragma pack(pop)

} // namespace Map
} // namespace OpenSHC
