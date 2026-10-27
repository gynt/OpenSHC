/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/LandscapeState.hpp'
*/

#pragma once

#include "OpenSHC/IO/PackagedFileMagicNum.hpp"
#include "OpenSHC/Map/Rocks/Rock.hpp"
#include "OpenSHC/Map/Trees/Tree.hpp"
#include "OpenSHC/Map/Trees/TreeType.hpp"
#include "OpenSHC/Map/WindState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "WinDef.h"

namespace OpenSHC {
namespace Map {

    using OpenSHC::IO::PackagedFileMagicNum;
    using OpenSHC::Map::WindState;
    using OpenSHC::Map::Rocks::Rock;
    using OpenSHC::Map::Trees::Tree;
    using OpenSHC::Map::Trees::TreeType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x0006B700
    class LandscapeState {
    public:
        // Set each updateTrees when TileMapState.fullHeightViewActive == 0 or the flat view is on; tree updaters then
        // use a constant frame (0x94 / 0); createTree clears it temporarily around the UpdateTree callback
        // Set each updateTrees when TileMapState.refreshRelatedOne == 0 or the flat view is on; tree updaters then
        // use a constant frame (0x94 / 0); createTree clears it temporarily around the UpdateTree callback
        undefined4 treeAnimFrozen; // 0x00000000 length: 4
        // Set 1 in constructor; updateTreeStage only advances growth when non-zero
        undefined4 treeGrowthEnabled; // 0x00000004 length: 4
        undefined4 DAT_TotalOrganisms; // 0x00000008 length: 4
        // Reset to 0 in clearRocksAndTrees
        int organismCounterC; // 0x0000000C length: 4
        int maxTreeCount; // 0x00000010 length: 4
        undefined4 x; // 0x00000014 length: 4
        undefined4 y; // 0x00000018 length: 4
        Tree trees[2000]; // 0x0000001C length: 312000
        WindState wind; // 0x0004C2DC length: 28
        Rock rocks[4000]; // 0x0004C2F8 length: 128000
        DWORD creationTime; // 0x0006B6F8 length: 4
        undefined1 padding_0x6b6fc[4]; // 0x0006B6FC length: 4

    private:
        LandscapeState(LandscapeState const&);
        void operator=(LandscapeState const&);

    public:
        LandscapeState() {};
        ~LandscapeState() {};

        // Constructor
        /**
         * LandscapeState constructor: records creation time, clears all trees/rocks, resets wind and sets
         * field1_0x4 = 1 (enables tree growth in updateTreeStage). Returns the global instance.
         */
        LandscapeState* Construct_LandscapeState();

        /**
         * Maps an editor/UI tree item ID (0x28-0x2B, 0x82-0x8B, 0x99-0x9C) to the logical TreeType value (1-4,
         * 5-14, 16-19); returns 0 for anything else. Type 15 (TT_APPLE) is never produced here (apple trees come
         * from apple farms).
         */
        undefined4 mapUITreeTypeToLogicalTreeType(undefined4 uiTreeType);

        /**
         * Returns a size class 0..3 for a tree type at a given stage: stage<2 or types 5-9 -> 1, types 1-2 -> 3,
         * types 3, 4 and 15 (apple) -> 2, everything else -> 0. Used as the tree 'size' argument when
         * creating/updating trees.
         */
        undefined4 getValueFrom0UpTo3ForTreeTypeAndTreeStage(undefined4 treeType, int treeStage);

        /**
         * Resets the landscape: zeroes organism counters (total organisms, field3_0xc, new-organism stats) and
         * clears all 2000 tree records (0x9C bytes each at 0xF2CC54) and 4000 rock records (0x20 bytes each at
         * 0xF78F30); sets maxTreeCount to 2000.
         */
        void clearRocksAndTrees();

        /**
         * Allocates the first free tree slot (1..1999; returns 0 if none) and initialises it: uid, state (4 =
         * static for types 0x10-0x13, else 1), size, position/tile/micro coords, rng1 and animation start frame
         * from RandomLayer, stage-dependent wood chunks/hit points and stageTracker from OrganismDefinedData
         * tables, GM image/origin, anim interval, visualVariation (initially the stageRelatedValue argument, then
         * overridden per type 1-9) and the 16-bit Tree field at +0x6E from the 6th argument (all direct callers
         * pass 0). Types 5-10 and 0x10-0x13 are forced to stage 4. Sets DAT_CurrentTreeID and calls the per-type
         * UpdateTree callback with treeAnimFrozen temporarily cleared. Returns the tree ID.
         */
        int createTree(undefined4 x, undefined4 y, TreeType treeType, undefined4 size, int stageRelatedValue,
            undefined4 param_6, int stage);

        /**
         * Reloads a tree's stage-dependent values for the given stage from
         * OrganismDefinedData.TreeRelated1/TreeRelated2 (stageRelated4 + treeAdultHoodStageRelatedVisual3,
         * stageRelated2 + stageRelated1).
         */
        void setTreeStageRelatedValues(int treeID, int stage);

        /**
         * Removes a tree: clears its footprint flags on the tile map, refreshes pathfinding links around its tile
         * and flags the separate-area map for rebuild, re-applies its brush to the logical layer in clear mode (arg
         * 1), and zeroes its 0x9C-byte record.
         */
        void removeTree(int treeID);

        /**
         * Stores timeGetTime() in g_treeUpdateTime and writes it into field8_0x14 of every tree whose state is
         * neither 0 (free) nor 3 (dead). Leaves DAT_CurrentTreeID at 2000.
         */
        void setCurrentTimeOnSomeTrees();

        /**
         * Allocates the first free rock slot (1..3999), fills uid, size, x/y, tile, type, orientation and GM id
         * from OrganismDefinedData.Rock_field0xe, sets DAT_CurrentRockID and calls the per-rock-type update
         * callback (a function-pointer table that Ghidra shows as an offset from TreeRelated1). Returns the rock ID
         * or 0 if full.
         */
        int createRock(undefined4 x, undefined4 y, int rockType, undefined4 size, undefined4 orientation);

        /**
         * Removes a rock: clears its footprint flags, refreshes pathfinding links around its tile, flags separate-
         * area map rebuild and zeroes its 0x20-byte record.
         */
        void removeRock(int rockID);

        /**
         * Sets the tree on a tile on fire for playerID. Fails if the OrganismLayer ID is >1999 (not a tree) or the
         * tree was already lit (field92_0x98 != 0). Types 5-14 and 16-19 just die (state 3, no fire spread). Types
         * 1-4 need stage>=3 and fewer than 20 lit non-apple trees (mapAndTime.treesLitThisPass<=0x13); they get
         * stage 6, stageTracker=TreeStageLevels[type][0], burn timer 20 and fire spread radius 2. Type 15 (apple)
         * gets stage 6, stageTracker 0, burn timer 20, radius 1. For burning types it records the igniter and
         * spreads fire via PathFindingState. Returns TRUE if the tree was affected.
         */
        BOOLEnum lightUpTree(int tile, int playerID);

        /**
         * Returns OrganismDefinedData.RandomRockImageGMImageOffsets[index].
         */
        int getRandomRockImageOffset(int index);

        /**
         * Returns a growth size class for a tree from its type and stage: type 1 -> 1 (stage 0), 2, 3, else 4;
         * types 2-4 -> 1 (stage 0-1), 2 (stage 2), else 3; types 5-14 and 16-19 -> 1; type 15 (apple) and unknown
         * types -> 0. Used by tile luminescence computation.
         */
        undefined4 getTreeGrowthTargetStage(int treeID);

        /**
         * Chooses mapAndTime.lightningPower from DAT_TotalOrganisms: 20 for <11, 15 for <101, 10 for <201, then
         * 9..1 in steps up to <1801, and 0 above. In updateTreeStage every (interval+1)-th tree reaching stage 4+
         * is sent to stage 5 instead of seeding, so more trees means fewer seedlings (population cap).
         */
        void setTreeSpreadInterval();

        /**
         * NAME? Affects most trees rather than every fifth: for every used tree slot of type 1-4 with stage 2..4,
         * sets stage 5 (the last stage before death) unless (SEC_RNG.currentNumber2 ^ tree.rng1) % 5 == 0, so
         * roughly four out of five matching trees are aged. Triggered by a scenario event / trigger-event menu.
         */
        void ageFourFifthsOfGrowingTrees();

        /**
         * Tries 8 neighbouring offsets (TreeSpreadOffsets, starting at a random index and wrapping) around the
         * parent tree at (x,y) to place a seedling: target must be in-bounds and valid, free of
         * organism/unit/building and of blocking LogicLayer flags (0x703E25B5), have the right Logic2Layer bits
         * (0x90 must be clear for type 1, set for other types), be within +-0x40 height of the parent tile and pass
         * setupBabyTreeLocationInfo with a BFS clearance radius of 3 (4 for odd tree IDs). On success stores
         * tile/x/y in PathFindingState.ALG_Result* and returns 1, else 0.
         */
        undefined4 setupBabyTreeLocation(uint treeID, int treeType, uint x, uint y);

        /**
         * Returns TRUE if trees[treeID].uid equals the given uid and the tree is still standing (zeroUpTo2 == 0).
         */
        BOOLEnum isTreeAliveAndMatchingUID(int treeID, int treeUID);

        /**
         * Returns TRUE if the tree UID matches and its treeAdultHoodStageRelatedVisual3 counter is positive (tree
         * has wood, i.e. is grown enough to cut).
         */
        BOOLEnum isTreeAdult(int treeID, int treeUID);

        /**
         * Woodcutter chop: if the UID matches and the tree is standing, adds healthDelta to stageRelated1 (tree hit
         * points; callers presumably pass a negative value); when it drops to <=0, sets it to 0, marks the tree
         * felled (zeroUpTo2=1), resets animationFrameIndex and re-applies the tree brush in clear mode. Returns 1
         * when the tree was felled, else 0.
         */
        undefined4 damageTreeAndTriggerDeathIfDepleted(int treeID, undefined4 healthDelta, int treeUID);

        /**
         * Woodcutter takes one piece from a felled tree: if the UID matches, decrements
         * treeAdultHoodStageRelatedVisual3 (remaining wood) if positive, sets state 3 (removed next update) when it
         * is <1, and sets zeroUpTo2=2 (being harvested).
         */
        void advanceTreeDecayState(int treeID, int treeUID);

        /**
         * For each live (state 2) tree with stage < 4 that isTreeAdult accepts and whose axis distance
         * (distanceHigh) to (x,y) is < 4, sets the short at stage+0x14 (Tree+0xB0 = unknownDistanceRelatedToCrow)
         * to 1 so crows can later fly out of it.
         */
        void markNearbyTreesAsCrowTargets(int x, int y);

        /**
         * When a unit moves, checks its 8 neighbouring tiles for live crow trees (state 2, hasCrows set, cooldown
         * rng200till300 == 0). For each, spawns an entity (spawnEntity with constants 0xFA, 0x1C) flying from the
         * tree top toward the entrance of the keep (of players 1-8 other than the unit's owner) nearest to the
         * unit, with +-2 random jitter, or to a random point within +-50 tiles if no such keep exists; sets a
         * 200-299 tick cooldown and plays FX_CROW once per call.
         */
        void spawnCrowFromNearbyTree(int unitID);

        /**
         * Creates an apple tree (TT_APPLE, size 1) at (treeX,treeY) for an apple farm: links it to the building ID
         * and UID, randomises stageTracker (rng1 & 0x1F), marks the tile with logic flag 0x1000 and OrganismLayer,
         * applies its brush and refreshes pathfinding.
         */
        void placeAppleTree(int buildingID, undefined4 treeX, undefined4 treeY);

        /**
         * Finds the nearest live (state 2) apple tree in stage 3 (presumably bearing fruit) to
         * (xPosition,yPosition). If within distance 30, stores an approach position 2 tiles to one side (side 0:
         * -x, 1: +y, 2: +x, else -y) in LandscapeState.x/y and returns the tree ID; otherwise returns 0.
         */
        int selectClosestAppleTree(int xPosition, int yPosition, int approachSide);

        /**
         * Zeroes the wind state (value, index, countdown, field4_0x10, counter).
         */
        void resetWind();

        /**
         * Advances the wind every 2nd call: decrements countdown and clears valueIs1/valueIs2; when countdown goes
         * negative, reloads 32, takes the next value from WindRelatedArray (40-entry cycle) and sets
         * valueIs1/valueIs2 if that value is 1/2 (so the flags are one-step pulses).
         */
        void updateWind();

        /**
         * Grows one tree when its rng1&0x3F matches this tick's rng, it is type 1-4 (types 5-19 incl. apple never
         * grow here), standing, at full hit points, growth is enabled, not in the landscaping editor and (single
         * player only) the game is not paused. Increments stageTracker and advances stage when it reaches
         * TreeStageLevels. Stage >5 kills it (state 3). Stage 4+ either (every treeSpreadInterval+1-th time) goes
         * to stage 5, or resets to stage 3 and tries to place a seedling of the same type (size class always 1) via
         * setupBabyTreeLocation/createTree, updating tile layers and pathfinding. createTree's return value is not
         * checked.
         */
        void updateTreeStage(uint treeID, uint rng);

        /**
         * Woodcutter target search: the unit's tile must be valid with PathConnectionLayer area > 0. Scans all live
         * (state 2) trees with stage < 4 that isTreeAdult accepts. For each tree it takes the first of its 8
         * neighbouring tiles that is within +-16 height of the tree tile (building height included) and that
         * playerID's units can reach from the unit's area. Returns the ID of the closest such tree by axis distance
         * (distanceHigh), or 0.
         */
        int findTree(int playerID, uint unitXPosition, uint unitYPosition);

        /**
         * Runs map-version upgrade fixes on trees and rocks after loading. Also removes rocks beyond index 1000
         * when the received map version differs from the packager's and is older than 0xA5.
         */
        void upgradeTreesAndRocksForMapVersion(
            PackagedFileMagicNum receivedMapVersion, PackagedFileMagicNum packagerMapVersion);

        /**
         * Per-tick tree update. Resets the lit-tree count (mapAndTime.treesLitThisPass). Every 10th tick it
         * recomputes maxTreeCount. On 1 tick in 8 (tick%8==4) it draws a 6-bit rng for growth. Per tree: state 1
         * becomes 2; state 3 is removed; state 4 (static) gets animationFrameUnk = animationFrame2Unk, or 0 when
         * field0_0x0 is set. Other live trees are counted in DAT_TotalOrganisms. They take wind.value into Tree.one
         * when wind.countdown <= (y & 0x1F), so a wave sweeps across rows; wind value 3 sets zeroUpTo2=1. Their
         * animation frame advances when treeTypeRelated2 ms have passed and Tree.one != 0. The crow cooldown ticks
         * down, updateTreeStage runs on the growth tick (not in the editor), and the per-type UpdateTree callback
         * runs. A non-zero burn timer counts the tree as lit (non-apple only) and is decremented down to 1.
         */
        void updateTrees();
    };

    static_assert_cpp98_obj(sizeof(LandscapeState) == 440064, LandscapeState);

#pragma pack(pop)

} // namespace Map
} // namespace OpenSHC
