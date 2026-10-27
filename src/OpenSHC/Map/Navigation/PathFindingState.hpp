/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Navigation/PathFindingState.hpp'
*/

#pragma once

#include "OpenSHC/Map/ClimbData.hpp"
#include "OpenSHC/Map/Navigation/PathFindingStatePartB.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "WinDef.h"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Map::ClimbData;
        using OpenSHC::Map::Navigation::PathFindingStatePartB;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

        // SIZE: 0x000CC670
        class PathFindingState {
        public:
            int maxClimbDataCount; // 0x00000000 length: 4
            int searchGeneration; // 0x00000004 length: 4
            int unitX; // 0x00000008 length: 4
            int unitY; // 0x0000000C length: 4
            int destinationX; // 0x00000010 length: 4
            int destinationY; // 0x00000014 length: 4
            int climbX; // 0x00000018 length: 4
            int climbY; // 0x0000001C length: 4
            // [085 0x0049AAD0] min tile y of reached tiles; reset to 1000 together with yLimit=0
            int dirtyMinY; // 0x00000020 length: 4
            // [085 0x0049AAD0] max tile y of reached tiles
            int dirtyMaxY; // 0x00000024 length: 4
            // When non-zero, setChangedLayerZeroBasedOn40x40Layer skips the per-section ChangedLayer clearing,
            // resets the dirty row range to 0..399 and section box to 0..39 (whole map) and clears this flag
            int forceFullDirtyReset; // 0x00000028 length: 4
            int ALG_TargetX; // 0x0000002C length: 4
            int ALG_TargetY; // 0x00000030 length: 4
            int ALG_TargetTile; // 0x00000034 length: 4
            int resultX; // 0x00000038 length: 4
            int resultY; // 0x0000003C length: 4
            int resultTile; // 0x00000040 length: 4
            int ALG_ResultX; // 0x00000044 length: 4
            int ALG_ResultY; // 0x00000048 length: 4
            int ALG_ResultTile; // 0x0000004C length: 4
            undefined1 padding_0x50[12]; // 0x00000050 length: 12
            int ALGO_TotalTroopValue; // 0x0000005C length: 4
            int ALGO_TotalTroopCount; // 0x00000060 length: 4
            // First unit counted by computeTotalUnitsWithinDistance (target for automatic oil throwing)
            int firstMatchingUnitID; // 0x00000064 length: 4
            undefined1 padding_0x68[4]; // 0x00000068 length: 4
            int toggleUpdateSeparateAreaTileMap; // 0x0000006C length: 4
            // Zeroed in constructor only
            int unkInit70; // 0x00000070 length: 4
            // Incremented each time updateSeparateAreaTileMap recomputes
            int separateAreaUpdateCount; // 0x00000074 length: 4
            // [093 0x004A97D0] incremented when tracing gets stuck, right before all path linkage layers are
            // rebuilt
            int linkageRebuildCount; // 0x00000078 length: 4
            // 1 if doPathfinding found the cheap direct path, 0 if it fell back to the full search
            int lastPathWasDirect; // 0x0000007C length: 4
            // Not assassin-related: nonzero skips the local radius search in path planning and goes straight to the
            // full linkage search (0x4A9C..); set for ladder/wall/no-fire cases
            int skipLocalPathSearch; // 0x00000080 length: 4
            int climbIsIllegal; // 0x00000084 length: 4
            // [151 0x005244D0] set to 1 right before setDestinationForUnit when isTribeAllAssassins returned TRUE
            int pathForAssassins; // 0x00000088 length: 4
            int distance; // 0x0000008C length: 4
            // Area-pair accept/reject cache initialised this tick; reset each processGameTick
            int areaPairCacheReady; // 0x00000090 length: 4
            // Counts traced tiles with wall flag (LogicLayer 0x10000100), not generic blocked tiles. Count of
            // wall/non-gatehouse building tiles on the traced path; non-zero triggers recalculation with keep/walls
            // excluded
            int pathWallTileCount; // 0x00000094 length: 4
            // Set 1 when calculateCanPlayerUnitsNavigateToAreaFromArea enters the second pass that includes type-1
            // (ladder) climb entries, 0 when no route exists; giveTribeMoveInstruction clears it and checks it
            int areaRouteNeedsLadders; // 0x00000098 length: 4
            // Set by pathFindingRelated: start tile value minus best (lowest, >= 4) value of the AI zone-distance
            // byte layer found by the BFS; catapult/fire ballista react while < 3
            int zoneDistanceGain; // 0x0000009C length: 4
            int calculations; // 0x000000A0 length: 4
            int DAT_Mini_spreads; // 0x000000A4 length: 4
            int DAT_Easy; // 0x000000A8 length: 4
            int DAT_Hard; // 0x000000AC length: 4
            int searchNonmatchCount; // 0x000000B0 length: 4
            int searchMatchCounter; // 0x000000B4 length: 4
            undefined1 padding_0xb8[4]; // 0x000000B8 length: 4
            // [083 0x00498400] counter incremented once per call of this wall-scaling BFS
            int wallScalingSearchCount; // 0x000000BC length: 4
            // 0 when the last area route was found or decided without ladder (type-1) climb entries, 1 when the
            // ladder-inclusive pass ran; setClimbBasedOnClosestClimbData / registerUnitOnClimbData do nothing while
            // it is 0
            int areaSearchLadderPass; // 0x000000C0 length: 4
            // [091 0x004A5320] only incremented once per call, like a statistics counter
            int areaRouteSearchCount; // 0x000000C4 length: 4
            // [091 0x004A58A0] only incremented once per call, like a statistics counter; nothing gatehouse-
            // specific
            int nonLadderAreaRouteSearchCount; // 0x000000C8 length: 4
            int totalZones; // 0x000000CC length: 4
            undefined1 padding_0xd0[8]; // 0x000000D0 length: 8
            int numberOfClimbTeleports; // 0x000000D8 length: 4
            int debugGreatestClimbLoading; // 0x000000DC length: 4
            int zoneSizesArray[1000]; // 0x000000E0 length: 4000
            // [084 0x004995E0] sum of zoneSizesArray[1..999] after the flood fill
            int totalZonedTiles; // 0x00001080 length: 4
            ClimbData climbData[200]; // 0x00001084 length: 103200
            PathFindingStatePartB searchQueue; // 0x0001A3A4 length: 729804

        private:
            PathFindingState(PathFindingState const&);
            void operator=(PathFindingState const&);

        public:
            PathFindingState() {};
            ~PathFindingState() {};

            // Constructor
            /**
             * Constructor of the global PathFindingState: zeroes the statistic/debug counters, clears the
             * pathfinding tile maps and all climb data, and sets searchGeneration to 1. Returns
             * &DAT_PathFindingState.
             */
            PathFindingState* Constructor_PathFindingState();

            /**
             * Returns DAT_PathFindingState.searchQueue.writeIndex (number of tiles written into the search queue).
             */
            undefined4 getComputationalTileIndex();

            /**
             * Returns the tile index stored at position index of the pathfinding search queue.
             */
            int getTileInSearchQueue(int index);

            /**
             * Zeroes four pathfinding tile layers of DAT_TileMapState at construction: PathConnectionLayer
             * (0x1DF70D8, 0x27420 bytes), PathLinkageLayer (0x1E1E4F8, 0x13A10 bytes), CertainPathLayer (0x1E45918)
             * and WalkLayer (0x1E6CD38), 0x27420 bytes each; OccupancyLayer between them is skipped.
             */
            void clearPathFindingTileMaps();

            /**
             * Sets the search queue's output path-plan pointer to pPathPlan and resets the path-plan write index to
             * 0.
             */
            void bindPathPlanToAlgorithmStateAndReset(byte* pPathPlan);

            /**
             * Scans the previous search queue from TribesState.ALG_ResultTileIndex while tiles stay in the start
             * tile's walk region (max 4000 entries) and picks the tile with the smallest positive path distance
             * (CertainPathLayer) whose distance difference to the start tile is divisible by distanceModulo. Stores
             * its queue index and x/y in TribesState.ALG_Result* and returns the tile (index 0 if none found).
             */
            int findClosestTileToStartingTile(int distanceModulo);

            /**
             * Continues scanning the search queue from TribesState.ALG_ResultTileIndex for the first reached tile
             * (path distance 1..3999) whose Manhattan distance to (x,y) is divisible by modulo, stopping when the
             * walk region changes or after 4000 entries. Stores the found queue index (0 if none) and its x/y in
             * TribesState.ALG_Result*.
             */
            void findNextTileInExistingSearchThatIsModuloDistanceAway(int modulo, int x, int y);

            /**
             * NAME? Scans the search queue from TribesState.ALG_ResultTileIndex for a tile flagged 0x10000100 in
             * LogicLayer (by contrast with the sibling ...NotOnDefensiveStructure: a defensive-structure tile) with
             * positive path distance (CertainPathLayer) < 4000 whose Manhattan distance to (x,y) is divisible by
             * modulo. Returns 0 if a flagged tile's path distance exceeds extraDistance+12, the walk region changes
             * or more than 4000 entries pass. On success stores index/x/y in TribesState.ALG_Result* and returns
             * the tile. Better name: findNextTileByModuloOnDefensiveStructure.
             */
            dword pathFindingResultBased(int modulo, int x, int y, int extraDistance);

            /**
             * Scans the search queue from TribesState.ALG_ResultTileIndex for a tile NOT flagged 0x10000100 in
             * LogicLayer, with path distance 1..3999 and Manhattan distance to (x,y) divisible by modulo; returns 0
             * if the walk region changes or 4000 entries pass. On success stores index/x/y in
             * TribesState.ALG_Result* and returns the tile.
             */
            dword findNextTileByModuloAmongPreviousSearchNotOnDefensiveStructure(int modulo, int x, int y);

            /**
             * Decides whether unit unitID may step from tile in direction. checkMode 1 only rejects targets with
             * LogicLayer bits 0x30 or 0x1; other non-zero modes always allow. Mode 0, linkage allows the direction:
             * refuses once to step from a non-fire tile into a fire tile (counter++, field295_0x40a=1,
             * field280_0x3f4=5); if no fires exist or field295_0x40a is already set, resets counter and allows.
             * Mode 0, linkage blocks: without ignoreAssassinClimbing only an assassin may pass, by crossing between
             * a 0x100 (wall) tile and a non-0x100 tile without obstacle bits 0x4a5014b1 - entering
             * US_ASSASSIN_THROWING_HOOK (up, stores height difference and wall owner+1) or
             * US_ASSASSIN_START_CLIMBING_DOWN; other units are refused. With ignoreAssassinClimbing: allowed if the
             * target has 0x40000000, or the current tile has 0x40000000 and the target has neither obstacle bits
             * 0x4a5014b1 nor 0x100.
             */
            BOOLEnum doMoveFromTileToTile(
                int unitID, int tile, int y, int direction, int param_5, int ignoreAssassinClimbing);

            /**
             * NAME? Among the 8 neighbours of (x2,y2) finds one in the same path-connection area as (x,y), free of
             * units, whose terrain+building height is within 16 of the (x2,y2) terrain+building height; picks the
             * one with the smallest Chebyshev distance to (x,y) and stores it in
             * DAT_PathFindingState.climbX/climbY. Returns TRUE if one was found; FALSE if none or either point is
             * off-map/invalid. Used by woodcutters, so it is a generic 'reachable neighbour of target' search
             * rather than a climb point.
             */
            BOOL findNeighbourTileThatCanServeAsClimbPointClosestToXY(uint x, uint y, uint x2, uint y2);

            /**
             * Tries the 8 neighbours of (x,y) in DAT_ClimbLogicDefinedData.DirectionArray order and stores the
             * first one whose PathConnectionLayer equals area into DAT_PathFindingState.climbX/climbY; leaves them
             * unchanged if none matches or (x,y) is invalid.
             */
            void findPositionForGivenClimbArea(int area, uint x, uint y);

            /**
             * Breadth-first reachability search from (x,y) following only PathLinkageLayer direction bits; cardinal
             * steps add 1 and diagonal steps 2 to the distance written in CertainPathLayer, visited tiles are
             * stamped with searchGeneration in WalkLayer. Returns TRUE when tile (x2,y2) is dequeued (x2 = -1 means
             * explore only), FALSE when the queue empties, maxIterations dequeues are used (capped at 500 if the
             * target is invalid) or distance reaches 800. Search state can be continued via continuePreviousSearch.
             */
            BOOLEnum findLinkageBasedPathOrWalkRadius(
                uint x, uint y, int x2, int y2, int maxIterations, BOOLEnum continuePreviousSearch);

            /**
             * NAME? Same BFS as findLinkageBasedPathOrWalkRadius (PathLinkage directions, +1 cardinal/+2 diagonal,
             * generation-stamped WalkLayer) but additionally skips neighbours whose OccupancyLayer is non-zero (the
             * PathLinkageLayer[i+0x13a0f] accesses alias OccupancyLayer[i-1]). Returns 1 if (x2,y2) is reached,
             * else 0; maxIterations capped at 500 for an invalid target. Better name:
             * findPathAvoidingOccupiedTiles.
             */
            undefined4 findPathWithBudget(int x, int y, int x2, int y2, int maxIterations, int continueThenIterationCount);

            /**
             * BFS over a circular queue (x/y/tile) from (x,y) toward (x2,y2) (x2=-1: explore; invalid target
             * returns FALSE). Neighbours allowed by PathLinkage are always enqueued; otherwise, only from a tile
             * without 0x100: into a 0x40000000 tile from a non-0x40000000 tile, or from a 0x40000000 tile into one
             * with 0x40000800 bits or without obstacle bits 0x4a5015b1, provided the terrain height difference
             * (neighbour + building height if 0x10000000) is within 16, retried with a -90 adjustment when either
             * tile is a gatehouse. Stops at distance > 120 or after budget queue entries. Returns TRUE and bumps
             * searchMatchCounter when the target is dequeued, otherwise bumps searchNonmatchCount and returns
             * FALSE.
             */
            BOOLEnum findPathUsingClimbingWithHeightMargin16(
                uint x, uint y, uint x2, uint y2, int budget, BOOLEnum continueSearch);

            /**
             * NAME? BFS from (x,y) to (x2,y2) (x2=-1: explore) over a circular queue; a neighbour is enqueued if
             * path linkage allows it or, for cardinal directions only, if neither tile has a building, the
             * neighbour has no obstacle bits (0x4a5014b1) and exactly one of the two tiles carries the 0x100 (wall)
             * flag - i.e. scaling onto/off walls as assassins do (increments DAT_PathFindingState.wallScalingSearchCount). Gives
             * up at distance 400 or maxOptionsToTry entries. Better name: pathFindingAllowingWallScaling.
             * (Disassembly: the extended rule's diagonal copies are guarded by a direction&1 test, which Ghidra
             * removed as unreachable - diagonals really use linkage only.)
             */
            BOOLEnum pathFindingWithBuildingsIncluded(
                uint x, uint y, uint x2, uint y2, int maxOptionsToTry, int zeroMeansResetAlgorithm);

            /**
             * NAME? Fresh BFS from (x1,y1) to (x2,y2) following PathLinkage directions, but a neighbour is only
             * entered if it has LogicLayer bit 2, lacks the keep/wall flags 0x10000100, or is a gatehouse building
             * - so keep and walls are excluded while gatehouses are allowed. Returns 1 if the target is reached
             * within maxTries queue entries, else 0. Better name: calculatePathAvoidingKeepAndWalls.
             */
            undefined4 calculatePathKeepAndWallsGatesNotAllowed(int x1, int y1, int x2, int y2, int maxTries);

            /**
             * Builds a path plan from (unitX,unitY) for ladder climbing: requires a valid tile with a nonzero
             * PathConnectionLayer zone, runs findSuitableSpawnLocationUnk with a range chosen by param_1 (0..4 ->
             * 80/200/500/1000/2000) which leaves a distance value in CertainPathLayer (low 14 bits), then greedily
             * walks among neighbours with the same WalkLayer value as the start tile: first uphill to ever larger
             * values (visited tiles marked 0x8000), then, if allowDescentPhase, downhill (marked 0x4000) until the
             * value drops below 2. Candidate scores are the level +/- ((RandomLayer ^ rotating rng) & 7), with a
             * 1-point bias for keeping the previous direction; requireStrictChange excludes equal levels.
             * Directions are packed 2 per byte into searchQueue.ptrPathPlan (stops at 800). Returns the number of
             * steps (pathPlanIndex). param_1 and iVar11 are reused (best score / previous direction) after their
             * first role.
             */
            uint commitUnitPathPlanUsingWalkLayer(uint rangeLevelOrBestScore, int allowDescentPhase, int requireStrictChange);

            /**
             * Decrements counterForUpdatingSeparateAreaTileMaps; when it reaches 0 (immediately if forceUpdate,
             * which also sets the toggle) it is reset to 200 and, only if toggleUpdateSeparateAreaTileMap is set,
             * the zone map is rebuilt: clears PathConnectionLayer and zoneSizesArray, temporarily applies building
             * path linkage, then BFS flood-fills from every unzoned tile not in LogicLayer mask 0x4a5014b1 along
             * the 8 PathLinkageLayer direction bits, numbering zones 1..999 and counting tiles per zone. Stores
             * totalZones (next free zone id, or 1000 at the limit) and the sum of zoneSizesArray[1..999], restores
             * linkage and returns TRUE (FALSE when no rebuild). forceUpdate is reused as the BFS write index;
             * MacroLayer[t+0x13a0f] is PathConnectionLayer[t-1] (array aliasing).
             */
            BOOLEnum updateSeparateAreaTileMap(int forceUpdateThenBfsWriteIdx);

            /**
             * Recomputes the 8-direction PathLinkageLayer mask of a tile (tile height includes the building height
             * for LogicLayer 0x10000000 keep tiles). Tile class from LogicLayer: 0x800000 = no class (neighbours
             * still tested), 0x10000000 = keep, 0x800 = stairs, 0x100 = wall, 0x400000 or blocked mask 0x4a5014b1 =
             * no links at all (mask left 0), otherwise ground. A neighbour link is allowed only if the neighbour
             * type is compatible and its height is within +-16, or for wall/keep/stairs transitions if
             * DamageOrCropStageLayer <= 20. Ground tiles drop a diagonal link when both adjacent orthogonal
             * neighbours are obstacles and not linked; other tiles drop a diagonal between two wall/keep orthogonal
             * neighbours when the diagonal itself is not wall/keep/stairs. Returns TRUE if the tile's building is a
             * gatehouse or keep.
             */
            BOOLEnum updatePathLinkageForTile(int yUnk, int tile);

            /**
             * Makes neighbour links reciprocal: for each of the 8 neighbours of the tile that is not border and not
             * blocked, sets or clears the neighbour's PathLinkageLayer bit for the opposite direction ((d+4)%8) to
             * match this tile's bit for direction d.
             */
            void updatePathLinkageLayerAtTileForSomeLogicalReason(int tile, int y);

            /**
             * Updates the path links through a gatehouse: for buildingVariation != 0x50 it links the tile above the
             * first row / below the last row with the gate tile at the middle column (bits 0x10/0x01), otherwise
             * the tiles left/right of the middle row (bits 0x04/0x40). A link is set only if the outside tile is
             * not in LogicLayer mask 0x4a5014b1, its height is within +-16 of the inside tile's DefaultHeightLayer
             * value and gateOpenState != 2, else the bits are cleared. Array aliasing: raw 0x1d46648 is
             * DefaultHeightLayer, EntityLayerLT25[t+0x13a10] is HeightLayer[t], HeightLayer[t+0x13a0f] is
             * DefaultHeightLayer[t-1], PathConnectionLayer+0x27420 is PathLinkageLayer.
             */
            void updatePathLinkageTileMapRelatedToGates(int buildingID);

            /**
             * Links a keep's entrance tile with the outside tile depending on building orientation (4: above the
             * top row, 6: left of the middle row, 2: right of the last column, else: below the last row), setting
             * the matching PathLinkageLayer bits on both tiles (raw 0x1e1e4f8 is PathLinkageLayer).
             */
            void updatePathLinkageTileMapRelatedToKeeps(int buildingID);

            /**
             * Adds fixed PathLinkageLayer bits for a siege tower building at (x,y): column x+1 gets S at row y-1,
             * N+S at rows y and y+2, N at row y+3; row y+1 gets E at x-1 (decompiled as
             * PathConnectionLayer+0x2741f), E+W at x and x+2, W at x+3. Bits are only added, never cleared.
             */
            void updatePathLinkageTileMapRelatedToSiegeTower(int buildingID);

            /**
             * Tries a direct greedy route from (x,y) to (destX,destY): each step moves in the straight/diagonal
             * direction toward the destination if that PathLinkageLayer bit is set, marking WalkLayer with a new
             * search generation and appending the direction (4 bits) to the path plan. Fails after 399 steps, on a
             * blocked step, or on an occupied tile while any fire exists. Returns TRUE when the destination is
             * reached; pathPlanIndex is updated either way.
             */
            BOOLEnum tracePathPlanToDestinationViaUnoccupiedTiles(uint x, uint y, uint destX, uint destY);

            /**
             * Reverses the nibble-packed direction list in searchQueue.ptrPathPlan in place (pathPlanIndex entries,
             * swapping from both ends). Directions are not inverted, only their order.
             */
            void reverseCurrentPathPlan();

            /**
             * Raise-land tool: breadth-first fills CertainPathLayer with distances from (x,y) over non-border tiles
             * of the same path zone, calling raiseLand(tile, y, 4, 1) on every tile up to maxDistance (the
             * decompiler shows the limit as unaff_retaddr), then forces logic/texture/GFX layer refresh.
             */
            void raiseLand2(uint x, uint y, int maxDistance);

            /**
             * Breadth-first flood (8 directions) from (xPosition,yPosition) over all tiles not flagged as map edge
             * (LogicLayer & 0x30), ignoring path linkage, writing BFS distance into CertainPathLayer and the search
             * generation into WalkLayer, up to distance maxDistance. Every dequeued tile marks its 10x10 section in
             * TileMapState.mapping40x40 (0x1F93438) with 2 and widens the dirty tile-row range and section bounding
             * box; tiles within range also get ChangedLayer=2. Finally forces logical/texture/GFX layer redraws.
             * 0x21aec98 is the 400x400 valid-tile mask.
             */
            void updateWalkAndPathLayer(int maxDistance, uint xPosition, uint yPosition);

            /**
             * Clears the dirty state: if no full refresh is pending (field10_0x28==0 and flag_and_offset==0) it
             * walks the sections of mapping40x40 inside the dirty section box (rows someIndex..dirtySectionRowMax, columns
             * someYLike..dirtySectionColMax), and for each flagged section clears the flag and sets ChangedLayer
             * (0x1C5AD88+tile) to 0 for every valid tile of its 10x10 block; then resets the dirty row range and
             * section box to empty (min 1000, max 0). Otherwise it clears field10_0x28 and sets the dirty row range
             * to 0..399 and the section box to 0..39 (section flags are not touched).
             */
            void setChangedLayerZeroBasedOn40x40Layer(uint flag_and_offset);

            /**
             * Returns TRUE if the dirty tile-row range is non-empty (mappingYRelated <= yLimit), i.e. some rows
             * need GFX update.
             */
            BOOLEnum getYSmallerThanYLimit();

            /**
             * BFS from (destinationX,destinationY) up to distance 6, returning (in climbX/climbY) the first tile
             * whose PathConnectionLayer area equals originArea; climbX/Y default to the destination. Neighbors are
             * only filtered by map edge (no visited check), so tiles may be enqueued repeatedly.
             */
            void findNearbyTileInConnectionArea(int originArea, uint destinationX, uint destinationY);

            /**
             * Tunneler target search: zeroes CertainPathLayer, then BFS (4 cardinal directions) from
             * (originX,originY) over tiles without LogicLayer bits 0xb1/0x301000/0x40000000 and without buildings
             * other than types 0x4a-0x4c, up to distance maxDistance. Stops at the first dequeued tile that is an
             * enemy wall (LogicLayer 0x100 set, 0x2 clear; owner = (WallOwnerLayer&7)+1) or carries an enemy
             * building, where enemy = different team from playerID and, if targetPlayerID != 0, owned by
             * targetPlayerID; stores it in ALG_TargetX/Y/Tile (0 if none). The declared prototype is correct; the
             * decompiler's use of playerID/targetPlayerID as start x/y and unaff_EBX/EBP/retaddr is a stack-depth
             * artefact after fillMemory_ByteValue (ret 0xC).
             */
            void algTunnelerFindTarget(int playerID, int targetPlayerID, int distance, int originX, int originY);

            /**
             * BFS from (x,y) up to maxDistance following PathLinkageLayer cardinal links; whenever an unvisited
             * neighbor is a map-edge tile (LogicLayer & 0x30) the current tile is appended to
             * signpostsMapEdge[signpostID] (up to 50 entries) and stored as resultX/Y/Tile.
             */
            void findMapBorderEdgeTileAndStoreInSignpostData(int signpostID, int maxDistance, uint x, uint y);

            /**
             * Flood fill over sea tiles (LogicLayer & 1) from (x,y) in 4 cardinal directions; returns in
             * ALG_ResultX/Y/Tile the tile being processed once more than 'budget' tiles were queued, otherwise the
             * last tile dequeued (the furthest sea tile). Used to pick seagull destinations.
             */
            void findFurthestSeaTile(int budget, uint x, uint y);

            /**
             * Enumerates tiles around (x,y) in BFS order over 4 cardinal neighbours (local 1000-entry tile/y
             * queues; expansion stops at map-edge tiles) and returns in resultTile/resultY the brushTileIndex-th
             * newly discovered tile (index < 1 returns the center); resultX stays 0. BUG (original game): the
             * center tile is never stamped in WalkLayer, so it is rediscovered as the 7th tile (south neighbour of
             * the first, northern neighbour) and all later indices are shifted by one. Queue entries are bounded by
             * brushTileIndex+1, so the local arrays (wrap only at 0x13a10) are safe for brush indices < 1000.
             */
            void getTileInSquareBrush(int brushTileIndex, uint x, uint y);

            /**
             * Checks whether a baby tree of treeType may be planted at (x,y): BFS over 8 directions up to param_1
             * distance through free tiles (LogicLayer mask 0x703e25b5 clear, Logic2 0x90 clear for type 1 / set for
             * others, only farm/woodcutter/quarry/signpost/pond buildings allowed). Returns 1 if the radius is
             * exceeded without meeting a tree (types 1-4), 0 if a tree or other building is met or the queue
             * empties.
             */
            undefined4 setupBabyTreeLocationInfo(int maxDistance, int treeType, uint x, uint y);

            /**
             * BFS from (x,y) over 8 directions through non-edge tiles; returns TRUE if distance 'budget' is
             * exceeded without touching a tree of type 1-4 in OrganismLayer, FALSE if such a tree is found or the
             * search exhausts. Only yQueue is maintained (x not tracked).
             */
            BOOLEnum findNoTreeInRange(int budget, uint x, uint y);

            /**
             * Rescans the queue of the previous BFS (from index 0 to writeIndex) for a tile visited in the current
             * generation whose value in TileMapState.aiZoneDistanceLayers[tile] (0x1EE2998 +
             * tile*0x13A10, a per-player/per-index cost map) is 40..45 and whose BFS distance is >= maxDistance;
             * stores it in ALG_ResultX/Y/Tile and returns TRUE, else FALSE. NAME? 'CostLowerThan6' is (cost-40) <
             * 6; parameter 'tile' is actually the cost-map index and 'maxDistance' is a minimum distance.
             */
            BOOLEnum findQueuedTileWithPathCost40to45(int tile, int maxDistance);

            /**
             * BFS flood fill (8 directions) from `tile` that sums getValueOfTroopType and counts live (dying==0),
             * owned (owner!=0) units on visited tiles into ALGO_TotalTroopValue/ALGO_TotalTroopCount; the first
             * counted unit ID goes to field34_0x64. sameTeamUnits==1 counts only units of playerID's team, 0 only
             * units of other teams, any other value all units. Expansion: if someLogicalTileProperty==0, onto
             * neighbours without LogicLayer&0x30, otherwise along PathLinkageLayer climb bits; the search stops at
             * the first tile whose BFS level exceeds `distance` (start tile = level 1), after that tile's units
             * were already counted.
             */
            void computeTotalUnitsWithinDistance(
                int playerID, int sameTeamUnits, int someLogicalTileProperty, int tile, int distance);

            /**
             * BFS (4 of the 8 directions: entries 0,2,4,6 of clockwiseCardinalTranslationMatrix) from (xPos,yPos)
             * across tiles without sea/rock/border (0xb1) or building/tree/keep (0x10001400) flags. Stops at the
             * first tile that holds unitID, or that is unoccupied (OccupancyLayer==0) and has no unit, and stores
             * it in ALG_ResultX/Y/Tile (all 0 if nothing is found). It is a generic nearest-free-tile search that
             * callers use for rally/spawn points.
             */
            void computeNextRallyPointDestination(int unitID, int xPos, int yPos);

            /**
             * Checks the 8 direct neighbours of (x,y) in clockwise order and returns TRUE on the first one that is
             * inside the map (bounds and valid-tile byte map) and has no blocking LogicLayer flags (0xb1
             * sea/rock/border, 0x50101400 building/tree/river/keep/moat). It stores that neighbour in
             * ALG_ResultX/Y/Tile. Returns FALSE if none qualifies or (x,y) is invalid.
             */
            BOOLEnum findDirectNeighbourWalkableTile(uint x, uint y);

            /**
             * BFS (4 directions, stops once the BFS level exceeds 25) from (x,y) over pathable tiles
             * (PathConnectionLayer!=0, no 0xb1 or 0x1000 flags). Returns the first tile that holds unitID, or that
             * is unoccupied, has no unit and has the same BuildingLayer ID as the start tile. The result goes to
             * ALG_ResultX/Y/Tile (0 if nothing is found).
             */
            void findPathableTileWithoutUnitWithBuildingAtXY(int unitID, int x, int y);

            /**
             * BFS (4 directions) from (x,y) that only expands onto wall/gatehouse/tower/keep tiles (LogicLayer &
             * 0x10000100). Returns the first tile with no unit, or with unitID itself, in ALG_ResultX/Y/Tile. The
             * start tile is checked first, so it wins if it is empty.
             */
            void findFreeTileOnDefensiveStructure(int unitID, int x, int y);

            /**
             * BFS (4 directions) from (x,y), limited to the unit's path-connection area and to tiles without
             * 0xb1/0x1400 flags. Returns in ALG_ResultX/Y/Tile the first tile that does not hold the unit itself,
             * has no unit (unless considerUnits==0), and whose total height differs by less than 16 from the unit's
             * buildingHeight+terrainOrClimbHeight. It aborts immediately if the start tile has LogicLayer&0x30.
             */
            void findWalkableTileThatDoesNotContainUnit(int unitID, uint x, uint y, int considerUnits);

            /**
             * BFS (all 8 directions) from the unit's tile within its path-connection area. Returns 0 as soon as a
             * reachable neighbour is not wall/keep (LogicLayer & 0x10000100 == 0) or has flag 0x400000. Returns 1
             * if the whole reachable area consists of wall/keep tiles, meaning the unit is stranded on them.
             */
            undefined4 isUnitStrandedOnWallsOrKeep(int unitID);

            /**
             * BFS (4 directions) from the unit's tile over unit-free tiles of the same path area that belong to
             * buildingID. Writes into *pX/*pY the visited tile closest to (x,y) by Chebyshev distance
             * max(|dx|,|dy|) (first one wins on ties); the in-code comment saying 'manhattan' is wrong. *pX/*pY
             * default to the unit's own position, and the function always returns 1.
             */
            undefined4 findClosestFreeTileNearUnitOnBuilding(
                int buildingID, int unitID, int x, int y, int* pX, int* pY);

            /**
             * Unrestricted BFS (4 directions) from (x,y) that ends once the BFS level exceeds 12. Returns TRUE if a
             * visited tile holds a building of another team (pitch ditches and killing pits excluded), or a
             * wall/tower/gatehouse tile (LogicLayer&0x100) whose owner (WallOwnerLayer&7)+1 is on another team than
             * playerID. Otherwise returns FALSE.
             */
            BOOLEnum checkEnemyBuildingOrDefensiveStructureWithin12Tiles(int playerID, uint x, uint y);

            /**
             * Secondary flood fill with its own 1000-entry stack queue, starting at (x,y) and moving in 8
             * directions over tiles visited by the current searchGeneration with positive CertainPathLayer. It
             * overwrites their CertainPathLayer with `marker`, so it carves a region out of a previous search.
             * Every neighbour that is already marked or outside the current search decrements `budget`. The fill
             * stops when the number of enqueued tiles reaches budget or 999, or the queue empties.
             */
            void budgetFloodFillOnSearchDistanceLayer(uint x, uint y, int marker, int budget);

            /**
             * Called when a unit dies at (x,y). BFS along PathLinkageLayer climb links (8 directions) over BFS
             * levels 1-3 (the death tile and up to 2 steps away), adding 4-level to unitDeathHeatMap on each
             * visited tile: +3 on the death tile, +2 one step away, +1 two steps away. Tiles already at 250 or more
             * are left unchanged.
             */
            void updateUnitDeathHeatmapIn3SpacesAroundTile(uint x, uint y);

            /**
             * NAME? Flood-fills an AI zone flag instead of recomputing a path map. Runs only if the start tile has
             * no AIInfoLayer zone bits (&0xf); then BFS (8 directions) out to BFS level someMax ORs the flag byte
             * param_4 into AIInfoLayer of every visited tile (the OR happens before the level check, so the first
             * tile beyond someMax is flagged too). It expands only from tiles without LogicLayer&0x30; for flag 8
             * the source tile must also lack 0x6a5014b1 obstacle flags, and neighbours must have AIInfoLayer==0
             * unless the flag is 0x80.
             */
            void floodFillAIZoneFlag(int someMax, uint x, uint y, undefined4 aiZoneFlag);

            /**
             * BFS (8 directions) from (x,y) out to BFS level `max` that ORs 0x20 into AIInfoLayer of every visited
             * tile. It expands only from tiles without LogicLayer&0x30 (the nested ifs all test the same source
             * tile), and neighbours need no obstacle check. Unlike the sibling searches, tile indices and levels
             * are not bounds-checked (no 0x13a10 tests).
             */
            void updateAIZoneWithFloodFill0x20(int max, uint x, uint y);

            /**
             * BFS along PathLinkageLayer climb links (8 directions) from (x,y) out to maxDistance. Returns TRUE
             * once an unvisited neighbour has AIInfoLayer & aiInfoFlags, and stores the coordinates of the current
             * tile (not that neighbour) in ALG_ResultX/Y; ALG_ResultTile is not written. Returns FALSE otherwise.
             */
            BOOLEnum findAIZoneWithFlags(int maxDistance, uint x, uint y, undefined4 aiInfoFlags);

            /**
             * BFS along climb links (8 directions) from (x,y) out to `max`. For neighbour tiles farther than 4
             * steps that carry the archer-point AI flag (AIInfoLayer&0x10), it takes the point index from
             * findOrReserveArcherPointSlot. It returns the first nonzero index that is neither of the tribe's two
             * current archer points and whose 32-byte archer-point record has two zero dword fields (absolute
             * 0x177E9B4+index*32 and 0x177E9BC+index*32, i.e. unclaimed; the decompiler shows them as out-of-range
             * arch2ValuesArray tile/buildingID). Returns 0 if none.
             */
            int findArcherRelatedAttackInfoIndex(int max, uint x, uint y, int tribeID);

            /**
             * BFS along climb links (8 directions) from (x,y) out to `max`. For neighbour tiles farther than 4
             * steps with the support-point AI flag (AIInfoLayer&0x40), it returns the first nonzero
             * getSupportPointIndex result that differs from the tribe's current supportPointIndex and has no tribe
             * assigned (supportPointsArray[i].tribeID==0). Returns 0 if none.
             */
            int findSupportPointIndex(int max, uint x, uint y, int tribeID);

            /**
             * NAME? Finds a free siege-tent point index rather than an angle. BFS along climb links (8 directions)
             * from (x,y) out to maxDistance200; for neighbour tiles farther than 4 steps with AIInfoLayer&0x80 it
             * returns the first nonzero getSiegeIndexForTile result that is neither of the tribe's
             * siegeIndexValue1/2 and whose tentPointsValues entry has three==0 and tribeID==0. Returns 0 if none.
             */
            int findFreeSiegeTentPointIndex(int maxDistance200, uint x, uint y, int tribeID);

            /**
             * BFS along climb links (8 directions) from (x,y) out to distanceUnk. Returns the first neighbour tile
             * that is more than 4 steps away and has no unit; if requiredDistanceFromAIZone!=0, the playerID's AI
             * zone-distance byte layer must also equal it at that tile. All 8 surrounding tiles must be free of
             * obstacles (0x4a7014b1, 0x4), units and buildings, and the height spread of the candidate plus its 8
             * neighbours must be under 12. Returns 0 if none; selectionID is unused, and x/y are reused as min-
             * height and direction.
             */
            dword findAppropriateLocationForSiegeTent(
                int distanceUnk, uint x, uint y, undefined4 selectionID, uint requiredDistanceFromAIZone, int playerID);

            /**
             * NAME? BFS along climb links (8 directions) from (x,y) out to maxDistance. It looks for the reachable
             * tile with the lowest value in byte layer zoneLayerIndex of the 0x13a10-byte layers at 0x1ee2998 (the
             * AI zone-distance layers); values below 4 are treated as 0 and never win. Ties go to the smallest
             * setAxisBasedDistanceResult distance to (x,y). Returns that tile (0 if none, 1000 if the start is
             * invalid) and stores startValue - bestValue in field51_0x9c.
             */
            dword findReachableTileWithLowestZoneDistance(int maxDistance, uint x, uint y, int zoneLayerIndex);

            /**
             * NAME? BFS along climb links (8 directions) from (x,y); it does not expand from wall/keep tiles
             * (LogicLayer & 0x10000100 on the source tile). A candidate is a non-burning neighbour whose value in
             * playerID's zone-distance layer equals distanceUnk. When a candidate is met beyond BFS level 16 while
             * a best tile exists, that best tile is returned at once; candidates beyond level 10 are scored level +
             * 2*SEC_TileMap1104 (penalty only if param_5 != 0) and the lowest score is kept. Returns the best tile
             * (0 if none, 1000 if the start is invalid). Variant of findBestAttackTileByPathCost.
             */
            dword findTileAtZoneDistanceByPathCost(uint x, uint y, int playerID, uint distanceUnk, int useTileCostPenalty);

            /**
             * BFS along climb links (8 directions) from (x,y). A candidate is a non-burning neighbour where the
             * zone-distance layer of the player (selected through attackInfo.hackValuesArray) equals
             * targetZoneValue. When a candidate is met beyond BFS level 10 while a best tile exists, that best tile
             * is returned at once; candidates beyond level 6 are scored level + 3*SEC_TileMap1104 and the lowest
             * score is kept. Returns the best tile (0 if none, 1000 if the start is invalid).
             */
            dword findBestAttackTileByPathCost(uint x, uint y, int playerID, uint targetZoneValue);

            /**
             * BFS (8 directions) from (x,y) out to maxDistance over tiles without LogicLayer&0x30; the start
             * coordinates are not bounds-checked. Returns the building ID on the first newly visited tile holding a
             * building that belongs to another team than playerID, has logicalState neither 0 nor BLS_REMOVE, is
             * not burning, and has a getBuildingFlammabilityFactor result other than 0 and 4. Returns 0 if none.
             */
            int findNearestEnemyBuildingWithinDistance(int playerID, int x, int y, int maxDistance);

            /**
             * BFS (8 directions) from (x,y) out to maxDistance over tiles without LogicLayer&0x30. Returns the unit
             * ID on the first newly visited tile holding a unit of another team than playerID that is not
             * ULS_INVISIBLE or ULS_REMOVE and not dying. Returns 0 if none.
             */
            int findNearestEnemyUnitWithinDistance(int playerID, int x, int y, int maxDistance);

            /**
             * NAME? Finds the nearest enemy gatehouse. BFS (8 directions) from (x,y) out to maxDistance, entering a
             * neighbour if it holds a building or a climb link allows it. Returns the ID of the first reached large
             * or small gatehouse that belongs to another team than playerID, has logicalState neither 0 nor
             * BLS_REMOVE, and is not burning. Returns 0 if none.
             */
            int findNearestEnemyGatehouseWithinDistance(int playerID, int x, int y, int maxDistance);

            /**
             * NAME? BFS (8 directions) from (x,y) out to maxDistance over tiles without 0x4a5014b1 obstacles. Each
             * unit on a newly visited tile that belongs to another team than playerID, is not ULS_INVISIBLE, not
             * dying and has isSelectable_OR_matchTime != 0 gets score = typeBonus + 1 + BFS level; the highest-
             * scoring unit ID is returned (earlier one on ties, 0 if none). typeBonus: 40 mangonel/ballista, 30
             * trebuchet, 20 engineer/catapult/fire thrower, 12 archer/crossbowman/Arabian archer/horse archer/fire
             * ballista, 8 lord/slinger, 4 spearman/ladderman/siege tower/ram/shield/slave, 2 maceman/monk, 0
             * pikeman/swordsman/knight/assassin/Arabian swordsman. BUG (original game): any other type, e.g. the
             * tunneler, matches no case and reuses the previous score as its bonus (initially the y coordinate).
             */
            int findHighestPriorityEnemyUnitInRange(int playerID, int x, int yThenScore, int maxDistance);

            /**
             * Flood fill (8 directions, no distance limit) starting at map coordinate (198,2), presumably a corner
             * outside the playable diamond. It ORs LogicLayer 0x10 into every reachable tile lacking 0x30, so the
             * off-map area of smaller maps becomes impassable border. It also clears resultX/resultY/resultTile.
             */
            void setWalkabilityBorderLogicLayerForSmallerMapSizes();

            /**
             * BFS flood fill from unit unitID's tile, up to maxDistance steps, over 4 of the 8 directions (the even
             * entries of the direction table: (0,-1),(1,0),(0,1),(-1,0)), looking for the nearest enemy-team
             * target. A target is either an enemy wall tile (LogicLayer 0x100, only in GM_SOLITARY or when
             * skirmishStrongWalls is off) or an enemy building that has health and is not a stockpile, keep,
             * campfire, signpost, parade ground, campground, killing pit or keep door. The found tile goes to
             * DAT_PathFindingState.ALG_ResultTile (0 = nothing found; ALG_ResultX/Y are only zeroed). Returns
             * nothing. Nothing is searched if the start tile has LogicLayer 0x30 set.
             */
            void aggressiveStanceTargetBuildingAtRange(int unitID, int maxDistance);

            /**
             * Returns TRUE if one of playerID's enemy units (enemyIDArray) is within Euclidean distance
             * requiredDistance of tile (x,y), using a strict < test. The unit must not be dying, its uid must match
             * a parallel per-player uid array at 0x11A66F0+playerID*10000, unknownTestAgainst0_2 must be 0,
             * moveRelatedFlag must not be 1, it must not be stalked and its owner must not be 0. Returns FALSE
             * otherwise, or if (x,y) is off-map.
             */
            BOOLEnum isEnemyUnitWithinDistance(int playerID, uint x, uint y, int requiredDistance);

            /**
             * BFS from (x,y) over 8 directions. A neighbour is enqueued only when the current tile's
             * PathLinkageLayer has that direction's BitFlagHelperForPathLinkage bit set. When the bit is not set
             * and the neighbour holds a barracks, mercenary post, keep, gatehouse or tower of playerID's team, the
             * function returns the current tile index. Returns 0 if nothing is found or (x,y) is invalid.
             */
            int findReachableTileNextToFriendlyDefense(int playerID, uint x, uint y);

            /**
             * BFS from (x,y) that only expands along directions allowed by the PathLinkageLayer bits. When a
             * blocked direction touches a gatehouse (building type 0x2D/0x2E) owned by exactly playerID, it returns
             * the current tile index, which is the tile next to the gatehouse. Returns 0 if none is found or (x,y)
             * is invalid.
             */
            dword findOwnedGatehouse(int playerID, uint x, uint y);

            /**
             * NAME? The return value is inverted relative to the name. Returns 0 (allowed) if (x,y) is off-map, if
             * playerID's own keep entry is within range (axis distance distanceHigh <= range), or if any player
             * 1..8 (self included) with a keep on playerID's team is within range/2. Otherwise it sets
             * TileMapState.buildingPlacementFailReason = 0x12 and returns 1. All callers treat nonzero as a
             * placement failure.
             */
            undefined4 isTileOutsideKeepRange(int playerID, uint x, uint y, int range);

            /**
             * NAME? BFS (8 directions) from (x,y) up to maxDistance steps; each dequeued tile, the start included,
             * is tested. Returns 1 if it reaches a building of another team (quarries and killing pits excepted) or
             * an enemy-team wall tile (LogicLayer 0x100 without 0x2), else 0. Used by building and wall placement
             * checks to forbid building near enemies.
             */
            undefined4 isEnemyBuildingOrWallWithinDistance(int playerID, uint x, uint y, int maxDistance);

            /**
             * Picks a random statue mapper, M_MAPPER_STATUE1 + SEC_RNG % 5. It then BFS-searches (8 directions, up
             * to 20 steps) from playerID's someKeepRelatedX2/Y2 for the first tile where
             * checkBuildingCanBePlacedHere succeeds. The statue is placed there with placeBuilding(...,2,0xF) after
             * setting TileMapState.forcePlaceBuilding = 1; the statue's owner is set to 0 and
             * statueCommemoratingPlayerID = playerID. If no tile is found, no statue is placed. Called from
             * checkSkirmishGameDefeat.
             */
            void placeCommemoratingStatueAtGoodLocation(int playerID);

            /**
             * Works only in GM_SOLITARY mode. BFS (8 directions) from (x,y) up to limit steps; returns TRUE if a
             * tile holding a signpost building is reached, the start tile included. Always returns FALSE in other
             * game modes or for off-map tiles.
             */
            BOOLEnum isSignPostWithinDistance(uint x, uint y, int limit);

            /**
             * BFS from (x,y) up to maxDistance steps over the 4 axis directions. On each tile it walks the entity
             * chain, at most 9 entities, looking for playerID's flags, heads on spikes or braziers (entity types
             * 10-15; brazier = 14). If removeExisting == 0 it returns 1 on the first match. Otherwise
             * destroyEntitiesOnTile clears the tile and the search continues. A brazier in GM_SIEGE_THAT whose
             * logicalState is not 3 also refunds its getBuildingCost gold to the local player (currentPlayerSlotID,
             * not playerID) before that. Returns 0 when the search ends.
             */
            undefined4 findOrRemoveOwnDecorationsInRange(int playerID, uint x, uint y, int maxDistance, int removeExisting);

            /**
             * BFS (8 directions) from tile up to maxDistance steps that collects every visited tile into a local
             * 100-entry array with no bounds check. It then calls IgniteFireAtMiniTile_Convenience(playerID, x*8,
             * y*8, HeightLayer, 2) for each collected tile. The only caller, LandscapeState::lightUpTree, passes
             * maxDistance 1 or 2 (at most 9 tiles), so the array cannot overflow in practice. Always returns 0.
             */
            undefined4 igniteFireAtTilesDistanceAway(int tile, int maxDistance, int playerID);

            /**
             * Siege-tower helper: BFS (8 directions) from tile, at most 12 steps. At distance > 3, a wall/gatehouse
             * tile (LogicLayer 0x100) is accepted if UnitsState::findFreeTileNearby(unitID, tile) succeeds: the
             * free tile goes to *pFreeTile, the wall tile to *pDefensesTile, and the function returns TRUE.
             * *pFreeTile is also overwritten (with 0) on failed attempts. The direction order is rotated by 4 for
             * odd unitIDs so that units spread out. Returns FALSE if nothing is found.
             */
            BOOLEnum findAccessibleWallAndNearbyFreeTile(uint unitID, int tile, int* pFreeTile, int* pDefensesTile);

            /**
             * Tactical-power heal: BFS (8 directions) from tile up to maxDistance steps. Every unit owned by
             * playerID on a visited tile gains healAmount health, clamped to maxHealth, and its healthPercentage
             * and healthbar (percent/10) are recomputed. Dying units are not excluded. Always returns 0.
             */
            undefined4 healUnitsOfPlayerWithinRadius(int tile, int maxDistance, int playerID, int healAmount);

            /**
             * NAME? Tactical-power barrage: an arrow volley if isArrowVolley != 0, otherwise catapult stones. BFS
             * (8 directions) from tile up to maxDistance. When attackerPlayerID != 0, non-lord units of other teams
             * lose damage health; at <= 0 they are killed (death state, SFX, tunnelerFinishedDigging = 1), and the
             * health bar is updated. On about 50% of visited tiles (RNG parity) a cosmetic projectile entity
             * (ET_ARROW_AND_DEFAULT or ET_CATAPULT) is spawned 50-99 minitiles to the +x side. The -x side is used
             * when the tile 100 to the right of the start is off-map. Always returns 0.
             */
            undefined4 damageEnemyUnitsInRadiusTacticalPower(int tile, int maxDistance, int attackerPlayerID, int damage, undefined4 isArrowVolley);

            /**
             * Clears SearchDistanceLayer, then BFS (4 axis directions, ring queue) from (x,y) - only if the start
             * is on the map and the byte layer at 0x21aec98 is set - for the nearest reachable wall tile
             * (LogicLayer 0x100 without 0x2) whose WallOwnerLayer&7 + 1 == wallOwnerPlayerID, or a neighbouring
             * moat tile (0x40000000) for which findMoatIdByTileAndOwner != 0. Returns TRUE (AL) with
             * *out_successUnk = 1 (wall) / 0 (moat) and the coords in *out_x/*out_y (both zeroed first), FALSE when
             * the queue empties. Passable tiles: no LogicLayer 0x31/0x80/0x1000, no 0x100000 unless 0x200000, and
             * no building or building type 0x4A-0x4C. The current decompile matches the real 7-argument prototype;
             * playerID is never read.
             */
            BOOLEnum findNearestReachableWallOrMoatOfPlayer(undefined4 playerID, int wallOwnerPlayerID, uint x, uint y,
                byte* out_successUnk, int* out_x, int* out_y);

            /**
             * Builds TileMapState.AIZoneLayer for attackedPlayerID (only if the player has a keep), bracketed by
             * updatePathLinkageTileMap(1) and (0). Phase 1 floods from the campground entry over tiles with
             * PathConnectionLayer != 0 that are reached through PathLinkageLayer bits or gatehouses (0x2D/0x2E),
             * marking them 1. Phase 2 marks each unmarked, non-blocked neighbour of those tiles (no LogicLayer
             * 0x31, no building with unknownFlag4) with value + 1, or + 7 for walls, without enqueuing them. The
             * outer loop always ends after one pass, so the moat '-1 on odd passes' branch never runs. Phase 1
             * aborts (and phase 2 is skipped) once writeIndex reaches 2000 when canReachKeep != 0, or 6000 in any
             * case.
             */
            void computeAIZoneLayer(int attackedPlayerID, int canReachKeep, int unusedArg3);

            /**
             * Chooses the climb-data entry unitID should use to cross between ladderWallGroup and ladderArea.
             * Returns 200 if field63_0xc0 == 0 (the last area search needed no ladder pass). First pass over
             * entries 1..maxClimbDataCount-1 considers usable (canBeUsed == 1), recognised type-1 entries that the
             * unit's type may use and whose (area, wallGroupAreaID) equals (ladderWallGroup, ladderArea), using the
             * bottom end, or (ladderArea, ladderWallGroup), using the top end. The lowest axis distance from the
             * unit to that end + 8*numberOfUnitsUsing wins, and its end goes to climbX/climbY. The unit's
             * climbDirection is always written (0 = bottom, 1 = top). Fallback when nothing is found: entries
             * 1..199 (fixed bound) of any type usable by the unit with the int at +0x1E8 > 0; the first whose area
             * (bottom end) or wallGroupAreaID (top end) equals ladderArea is returned. Returns the climb-data
             * index, or 0.
             */
            int setClimbBasedOnClosestClimbData(int unitID, int ladderWallGroup, int ladderArea);

            /**
             * Returns TRUE if climbData[wallDataID] is usable (canBeUsed == 1), recognised by pathfinding, and its
             * area or wallGroupAreaID equals area; otherwise FALSE.
             */
            BOOLEnum isUsableClimbWithinArea(int area, int wallDataID);

            /**
             * Zeroes the whole 0x204-byte ClimbData entry climbData[climbDataID] (array base 0x12BC94C) via
             * fillMemory_ByteValue.
             */
            void clearClimbData(int climbDataID);

            /**
             * Recomputes climbData[climbDataID].numberOfUnitsUsing by scanning its 50 unit slots. A slot counts
             * only if the unit is ULS_NORMAL, its uid still matches the stored uid and its climbDataID points back
             * to this entry; stale slots (unitID and uid) are cleared. If the entry is not usable, it only resets
             * the count to 0.
             */
            void recountUnitsUsingClimbData(int climbDataID);

            /**
             * Registers unitID on climbData[climbDataID]. Returns 0 if field63_0xc0 == 0 (no ladder pass in the
             * last area search), and -1 if the entry is unusable or already has 50 users. Otherwise it increments
             * numberOfUnitsUsing, copies climbDataRelated to the unit (0 for climb types 3/4/5), stores unitID and
             * uid in the first free slot, and returns 1 (also when no slot was free).
             */
            undefined4 registerUnitOnClimbData(int climbDataID, int unitID);

            /**
             * Clears (via clearClimbData) every usable climb-data entry 1..199 whose type is 6 or 7. The loop bound
             * is a fixed 200 (cmp esi,0xC8), not maxClimbDataCount. Called from migrateGameStateForMapVersion, i.e.
             * when loading older save or map versions.
             */
            void clearActiveClimbDataOfType6And7();

            /**
             * Area-graph BFS over climb-data entries; each entry links area, wallGroupAreaID and buildingArea.
             * Candidates are usable, recognised entries allowed by permitClimb (type-1 ladders excluded if
             * permitClimb == 0, other types if permitClimb == 2) that belong to playerID's team, or any entry when
             * playerID == 0 or its building has field241_0x2c6 set. Pass 1 searches from toArea while skipping
             * type-1 entries (field63_0xc0 = 0). If that fails, pass 2 includes them (field63_0xc0 = 1,
             * field50_0x98 = 1). Returns the area next to fromArea on the found route (toArea if directly linked;
             * fromArea if fromArea == toArea; 0 if either is 0). Returns 0 with field50_0x98 = 0 if unreachable.
             * The area queue is a 200-entry stack array with no bounds check.
             */
            int calculateCanPlayerUnitsNavigateToAreaFromArea(
                int playerID, dword fromArea, dword toArea, int permitClimb);

            /**
             * Variant of the climb-data area BFS used by doPathfinding. Candidates are usable, recognised non-
             * ladder entries (type != 1) of playerID's team, or any such entry when playerID == 0 or its building
             * has field241_0x2c6 set. Searches from toArea towards fromArea and returns the area next to fromArea
             * on the route (toArea if directly linked, fromArea if fromArea == toArea), or 0 if unreachable. Does
             * not touch field63_0xc0 or field50_0x98. The 200-entry area queue has no bounds check.
             */
            dword findConnectingAreaBetweenTwoAreas(int playerID, dword fromArea, dword toArea);

            /**
             * Returns whether tile1 can reach tile2. Returns TRUE if both have the same PathConnectionLayer area
             * and FALSE if either area is 0. Otherwise it consults a 10-entry accept cache and a 10-entry reject
             * cache of area pairs; these are reset to -1 on first use, guarded by field48_0x90. On a cache miss it
             * runs pathFindingWithBuildingsIncluded between the tiles (budget 100000) and stores the pair in the
             * matching cache if a free slot exists.
             */
            BOOLEnum calculateCanReachUsingCachedAreaLogic(int tile1, int tile2);

            /**
             * NAME? For target tile (targetX,targetY), checks all 8 neighbours. A neighbour qualifies if
             * calculateCanPlayerUnitsNavigateToAreaFromArea(playerID, area of (fromX,fromY), neighbour area, 0)
             * succeeds and its height (+ building height) is within a fixed +-0x10 of the target's height (+
             * building height). The qualifying neighbour with the smallest axis distance
             * (setAxisBasedDistanceResult.distanceHigh) to (fromX,fromY) is written to climbX/climbY. Returns 1 if
             * one was found, else 0. Not climb-specific: the woodcutter uses it to find a standing tile next to a
             * tree.
             */
            undefined4 findClosestReachableNeighborOfTarget(
                int param_1, uint param_2, uint param_3, uint param_4, uint param_5);

            /**
             * Calls updatePathLinkageLayerBasedOnBuildingsUnk for every map tile (0..0x13A0F) with that tile's y,
             * rebuilding the whole PathLinkageLayer.
             */
            void updatePathLinkageLayerForEachBuildingAtEachTile();

            /**
             * Recomputes the path linkage of tile and of its 8 neighbours via
             * updatePathLinkageLayerBasedOnBuildingsUnk. If any neighbour update reports a change, it sets
             * BuildingsState.pathLinkageDirty = 1; the result for the centre tile itself is ignored.
             */
            void updatePathLinkagesInAllEightDirections(int y, int tile);

            /**
             * Siege-AI target search: height-weighted BFS from (x,y) up to maxDistance, taking 1 (even distance) or
             * 3 (odd distance) directions per step from ClimbLogicDefinedData.directionArcTriples[dirListIndex];
             * step cost +1..+3 by neighbour height above the start relative to maxHeightRise (target-owned
             * walls/buildings always enterable, other terrain only up to start + maxHeightRise). Candidates need a
             * per-player byte layer value (0x1EE2998 for targetPlayerID) in 1..maxZoneValue-1 (forced to 1 in
             * GM_SOLITARY once attackDirectionAttempt > 7); they are targetPlayerID's buildings with health on
             * 0x400/0x10000000 tiles (if onlyFlammable: flammable and not burning; score base*d, base 150 on 0x400
             * tiles else 75, or (base-100)*d + 1500 for d < 16) or targetPlayerID's walls (only when onlyFlammable
             * == 0; score wall height above default + (20-d)*300, or + 100*d for d >= 16). The lowest score within
             * approximate Euclidean maxDistance goes to ALG_TargetX/Y/Tile (zeroed first). Note: locals 'zoneValue'
             * and 'startHeight' are swapped in meaning (zoneValue = start tile height, startHeight = zone byte).
             */
            void findBestAttackTargetTileWithHeightAndOwner(int param_1, uint param_2, uint param_3, int param_4,
                int param_5, int param_6, int param_7, int param_8, int param_9);

            /**
             * Walks the tile queue left by the previous search. For each tile whose CertainPathLayer is not 100
             * (not yet suppressed), it runs budgetFloodFillOnCertainPathLayer(x,y,100,30) to suppress the
             * surroundings and stores (x,y) in GameState.mapAndTime.unitMoveDestinationXYPairs[signpostID][n].
             * Stops after 40 spread-out destinations.
             */
            void storeSpreadOutSignpostDestinations(int signpostID);

            /**
             * Walks the tile queue of the previous search. Tiles visited in the current generation whose per-player
             * zone value (byte layer 0x1EE2998 for attackedPlayerID) is 0x48..0x4B and whose CertainPathLayer is <
             * 0x4C (not 100) are stored as spread-out move destinations in
             * unitMoveDestinationXYPairs[playerIDMin1][n], up to 40. Each one suppresses its surroundings via
             * budgetFloodFillOnCertainPathLayer(...,100,50).
             */
            void setDestinationPairsBasedOnPreviousSearch(int playerIDMin1, int attackedPlayerID);

            /**
             * Walks the tile queue of the previous search and stores up to 20 spread-out move destinations in
             * unitMoveDestinationXYPairs[playerIDmin1]. It picks tiles whose per-player zone value (byte layer
             * 0x1EE2998 for playerID) is in [maxCost, maxCost+10], with maxCost clamped to 100, and whose
             * CertainPathLayer is not 100. Each chosen tile suppresses its surroundings via
             * budgetFloodFillOnCertainPathLayer(...,100,200).
             */
            void setMoveDestinationPairs(int playerIDmin1, int playerID, int maxCost);

            /**
             * Walks the tiles left in the PathFindingState BFS queue by a previous search; for each tile whose
             * CertainPathLayer is not 100 it spawns a unitType unit for playerID/displayColor at that tile (pixel
             * coords tile*8) and adds it to tribeID, then calls budgetFloodFillOnCertainPathLayer(x,y,marker
             * 10,budget 2) and records (x,y) in DAT_GameState.mapAndTime.regionSeedPoints (max 40 entries; the loop
             * stops when it is full). Returns once `count` units were spawned; any remainder is spawned stacked on
             * the last used tile (count is decremented there even if spawnUnit fails). Note the flood marks with 10
             * while the skip test is for 100, so it does not exclude neighbouring tiles.
             */
            void spawnUnitAndAddToTribe(
                int playerID, int displayColor, int count, UnitType unitType, undefined4 tribeID);

            /**
             * Walks the tiles in the current BFS queue and picks up to 50 spread-out tiles as attack vectors for
             * playerID: each tile whose CertainPathLayer is not 100 is taken, then
             * budgetFloodFillOnCertainPathLayer(x,y,marker 100,budget 100) marks the nearby visited tiles with 100
             * so they are skipped; x/y go into DAT_GameState.mapAndTime.attackVectors[playerID][i] with
             * tribeUIDUnk/tribeID cleared.
             */
            void computeAttackVectorsBasedOnXAndY(int playerID);

            /**
             * BFS over the 4 cardinal directions from unit unitID's tile through tiles of its own
             * PathConnectionLayer area or wall/building tiles (LogicLayer 0x10000100), skipping LogicLayer 0x400000
             * tiles. Each neighbour in a different area that calculateCanPlayerUnitsNavigateToAreaFromArea (unit
             * owner, unitCanClimb) says connects to the area of (targetX,targetY) is scored by Chebyshev distance
             * to the target; the best one is stored in ALG_ResultTile and the tile it was reached from in
             * ALG_TargetTile. Returns 1 if found, else 0 (also 0 for an invalid target tile).
             */
            undefined4 findCrossAreaBridgeTileToTarget(int unitID, uint targetX, uint targetY);

            /**
             * BFS (8 directions) from (unitX,unitY) through tiles with LogicLayer flag 0x40000000. For each
             * unvisited neighbour without any of the flags 0x4a5014b1, checks whether its PathConnectionLayer area
             * connects to targetArea for playerID; on the first hit stores that neighbour's coordinates in
             * climbX/climbY and returns its area. Clears ALG_ResultTile/X/Y first; returns 0 if nothing found or
             * the start tile is invalid.
             */
            int canNavigateFunctionReturnsArea(int playerID, dword targetArea, uint unitX, uint unitY);

            /**
             * Multi-source BFS (4 cardinal directions) seeded with every tile whose AIZoneLayer == 1: writes the
             * distance (1 at the zone, +1 per step, byte) into TileMapState.aiZoneDistanceLayers[k][tile]
             * (0x1EE2998), where k =
             * TroopValueState.attackInfo.playerInfo[playerID-1].currentPlayerID_OR_attackedPlayerID_OR_one. Does
             * not expand out of sea/border/river tiles (LogicLayer 0x100031). Tracks the max distance in
             * PathFindingState.distance, stops beyond `limit`, and appends tiles at exactly borderDistance that are
             * reachable from fromArea to DAT_AICState.aiBorderTiles (max 1000).
             */
            void updateWalkLayerAndAIPathCostLayer(int limit, uint borderDistance, dword fromArea, int playerID);

            /**
             * Builds searchQueue.destinationsArray for attacking building buildingID: walks the accessible tiles
             * around the footprint (setupBuildingEntrancesOffset for its size), keeps tiles whose HeightLayer is
             * within 32 of the DefaultHeightLayer at the building tile, that are in/connected to fromArea for
             * playerID (or, for all-assassin tribes, reachable from the tribe leader unit's tile via cached area
             * logic) and within 16 of the building's terrainHeight; tile2 = first adjacent tile
             * (CardinalHorizontalFirstSearchOrder) belonging to the building without LogicLayer 0x0F000000 flags,
             * else 0. Then tries larger rings (sizes up to 13, on-map tiles only) with terrainHeight tolerance 32,
             * 48, ... and tile2 = 0. Count capped at 2*maxDestinations clamped to 50..500; the zero terminator is
             * written only if the cap is not reached. tribeID is reused as the loop counter.
             */
            void computeAttackDestinationsAroundBuilding(int tribeIDThenLoopIdx, int buildingID, int maxDestinations, dword fromArea, int playerID);

            /**
             * BFS (8 directions, max distance 10) from target (x,y) over tiles in `area` or connected to it for
             * playerID (all-assassin tribes may also use cached reachability from the target tile), then fills
             * searchQueue.destinationsArray: first tiles at Chebyshev distance 2 from the target with height
             * difference < 32 to the target (building height included) with tile2 flag 1, then (only if 4 or fewer
             * were found) distance-1 tiles likewise, then all tiles farther than 2 (flag 0). Count capped at
             * 2*unitCount clamped to 50..500; zero terminator only if the cap is not reached. The tribeID parameter
             * is reused as the target tile's height; targetUnitID is unused.
             */
            void pathPlanningForTribe(
                uint tribeID, undefined4 targetUnitID, uint x, uint y, int unitCount, dword area, int playerID);

            /**
             * BFS (8 directions, max distance 10, or 3 when shortenedDistance == 1) from `tile` over tiles in
             * `area` or connected to it for playerID. Then for each reached open tile (LogicLayer & 0x10000300 ==
             * 0) checks its 4 neighbours (order from OrderedOrientationBasedCardinalDirectionList[direction]) for
             * an enemy-team wall/structure tile (LogicLayer 0x10000300, not flag 2, building type not 10 and not
             * 0x28-0x2a); such pairs go into destinationsArray as (tile, structureTile) and the tile is marked -1
             * in the queue (with shortenedDistance == 1 the structure tile must have no unit). The other open tiles
             * follow with tile2 = 0. Count capped at 2*maxDestinations clamped to 50..500; zero terminator only if
             * the cap is not reached.
             */
            void findFreeSpaceNextToEnemyDefensiveStructureInSameAreaWithinDistance(
                int tile, int maxDestinations, int* area, int playerID, int shortenedDistance, int direction);

            /**
             * BFS (8 directions, max distance 10) from `tile` over tiles in `area` or connected to it for playerID.
             * Then for every reached tile that is not wall/tower/keep (LogicLayer 0x10000300) it looks at the 4
             * cardinal neighbours (CardinalHorizontalFirstSearchOrder) and stops at the first wall/tower tile
             * (0x300, not 0x400000) whose WallOwnerLayer owner is not playerID, storing (freeTile, wallTile) in
             * searchQueue.destinationsArray and marking the queue entry -1. The other free tiles follow with tile2
             * = 0. Count capped at 2*maxDestinations clamped to 50..500; zero terminator only if the cap is not
             * reached. Owner check is per player, not per team.
             */
            void populateDestinationsArrayWithWallTileAndFreeTilePairInSameArea(
                int tile, int maxDestinations, dword area, int playerID);

            /**
             * Computes the preferred orientation between `tile` and unit unitID
             * (calculatePreferredRelativeOrientation(tileX,tileY,unitX,unitY)) and checks the 4 cardinal neighbours
             * of `tile` in OrderedOrientationBasedCardinalDirectionList[orientation] order; returns the first
             * neighbour whose PathConnectionLayer area equals the unit's area or is reachable from it for the
             * unit's owner, else 0. The `tile` parameter is reused as the loop counter.
             */
            int findUnitPreferredOrientationBasedConnectedTile(int unitID, int tile);

            /**
             * Finds where unit unitID should stand to reach building buildingID: walks the accessible tiles around
             * the footprint, keeps those whose HeightLayer is within 32 of the building's foundation
             * DefaultHeightLayer, that are in or connected to the unit's PathConnectionLayer area for its owner,
             * and within 16 of the building's terrainHeight, pairing each with the first adjacent building tile
             * (else 0). Returns the kept tile closest to the unit (DirectionAlgorithmState distanceHigh) and writes
             * its building tile to *pResultTile (set to 0 first); returns 0 if none. Note: local
             * 'buildingBaseHeight' actually holds the access tile's height, 'heightDiff' the sign mask, and
             * 'entranceYOffset' the building y then the phase-2 loop index.
             */
            int findBuildingAccessPoint(int unitID, int buildingID, int* pResultTile);

            /**
             * NAME? Seeds the BFS queue with the tiles of up to 8 signpost buildings
             * (DAT_GameState.mapAndTime.signpostIDs) and floods 8 directions (avoiding LogicLayer 0x30 tiles) out
             * to distance `radius`, clearing what it reaches: destroys buildings (except types
             * 10,0xb,0x13,0x24-0x26,0x28-0x2a,0x34,0x37,0x47-0x49) with smash SFX, removes walls (flag 0x100
             * without 2: destroys entities, clears flags, height = DefaultHeightLayer, DamageLayer = 0) and moats
             * (0x40000000: clearMoatDataAtTile, height 8), and clears flag 8. Changed tiles are collected in the
             * queue arrays from index 0x9d08 and get updatePathLinkagesInAllEightDirections +
             * updateWalkAndPathLayer(7,x,y) at the end. BUG: writeIndex stays 1, so only the first present signpost
             * is expanded (the others are only marked visited); with no signpost at all the stale tilesQueue[0] is
             * expanded. Better name: clearObstaclesAroundSignposts.
             */
            void clearObstaclesAroundSignposts(int radius);

            /**
             * BFS (4 cardinal directions, avoiding LogicLayer 0x30 tiles) from (x,y) out to distance range; returns
             * 1 as soon as it reaches an ownable building or a wall tile (0x100, not 2) belonging to a different
             * team than playerID. If nothing is found and keepRange != -1, also returns 1 when
             * isTileOutsideKeepRange(playerID,x,y,keepRange) returns nonzero. Otherwise 0 (also 0 for an invalid
             * start tile). param_5/param_6 are real stack args (ret 0x1C) but never read.
             */
            undefined4 isOpponentBuildingInRange(
                int playerID, int x, int y, int range, int param_5, int param_6, int keepRange);

            /**
             * Resets numberOfClimbTeleports and clears all 200 ClimbData slots via clearClimbData.
             */
            void clearAllClimbData();

            /**
             * Allocates the first free ClimbData slot (1..199; returns 0 if full) and initialises it: type = size,
             * isRecognizedByPathfinding = 0, a new uid from DAT_GameCore.uniqueGameObjectTracker++, and source
             * uid/owner/bottom position from buildingID (gatehouses; also stores ladderDirection for sizes 3-6) or
             * else from unitID (ladder; sets the unit's wallDataID). If both IDs are 0 the slot is cleared again
             * but its index is still returned. Returns the slot index. The 5th stack argument (ret 0x14) is never
             * read.
             */
            int createClimbData(int size, int buildingID, int unitID, int direction, int unused5);

            /**
             * Per-tick update of all ClimbData slots 1..199: for each active slot calls the per-type handler
             * DAT_ClimbLogicDefinedData.updateFunctions[ClimbData.type] (10-entry table at 0xB3907C; types
             * 0,2,6,8,9 point to an empty ret), recounts units using it and clears it if it became unusable.
             * Recomputes numberOfClimbTeleports (active count), maxClimbDataCount (highest active id + 1) and
             * debugGreatestClimbLoading (max numberOfUnitsUsing). DAT_CurrentClimbDataID is the global loop index
             * the handlers read.
             */
            void updateClimbData();

            /**
             * Traces the result of the last search back from destination (x2,y2) to start (x,y): at each step picks
             * a neighbour visited in the same search generation whose CertainPathLayer distance is 1-2 lower,
             * subject to pathMode rules (0 any direction; 1 PathLinkageLayer bit required; 2 linkage bit or a step
             * into a LogicLayer 0x40000000 tile, or out of one onto a tile without 0xa5014b1 flags within 16
             * height; 3 linkage bit or a cardinal wall-boundary (0x100) crossing between tiles without buildings).
             * The forward step directions are packed two per byte into searchQueue.ptrPathPlan (max 800 steps) and
             * the plan is then reversed. Counts traversed wall/structure tiles (0x10000100, not 2, not gatehouse)
             * in field49_0x94. If stuck, resets pathPlanIndex, rebuilds path linkage and area maps (DAT_lWys++) and
             * returns.
             */
            void traceAndCommitPathPlan(uint x, uint y, uint x2, uint y2, int pathMode);

            /**
             * Plans a path from (unitX,unitY) to (destinationX,destinationY) stored in PathFindingState. If the
             * areas differ (and neither climbIsIllegal nor allAssassinsUnk), requires
             * findConnectingAreaBetweenTwoAreas for playerID. First tries
             * tracePathPlanToDestinationViaUnoccupiedTiles (normal units); else runs a budgeted search
             * ((distance+4)^2*10) chosen by the assassin/climb flags, falling back to unlimited (100000) searches,
             * then traceAndCommitPathPlan with mode 1 (normal) / 2 (climbIsIllegal) / 3 (assassins). If
             * allowWallCrossing == 0 and the path went over walls, re-plans with keep/walls/gates forbidden
             * (falling back to the linkage-based search). Returns pathPlanIndex (path length), 0 on failure.
             */
            dword doPathfinding(int playerID, int allowWallCrossing);

            /**
             * Resets pathPlanIndex and re-traces the path from (unitX,unitY) to (destinationX,destinationY) with
             * traceAndCommitPathPlan mode 0 (no linkage restrictions); returns the resulting path length.
             */
            undefined4 retraceAndCommitPathPlan();
        };

        static_assert_cpp98_obj(sizeof(PathFindingState) == 837232, PathFindingState);

#pragma pack(pop)

    } // namespace Navigation
} // namespace Map
} // namespace OpenSHC
