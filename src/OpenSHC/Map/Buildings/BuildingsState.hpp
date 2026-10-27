/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Buildings/BuildingsState.hpp'
*/

#pragma once

#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/Player/PlayerID.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/IO/PackagedFileMagicNum.hpp"
#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/Map/Buildings/BuildingCostStruct.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Commands::MappersEnum;
        using OpenSHC::Game::Player::PlayerID;
        using OpenSHC::Game::Resources::ResourceType;
        using OpenSHC::IO::PackagedFileMagicNum;
        using OpenSHC::Map::Buildings::Building;
        using OpenSHC::Map::Buildings::BuildingCostStruct;
        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

        // SIZE: 0x0018E088
        class BuildingsState {
        public:
            int structCount; // 0x00000000 length: 4
            // Cleared to 0 at the start of every updateBuildings pass; no reader seen
            undefined4 perTickReset4; // 0x00000004 length: 4
            int maxBuildingsCount; // 0x00000008 length: 4
            // [072 0x00422E20] set to 2000 - structCount each tick and decremented when setupBuildingData allocates
            // a building
            int freeBuildingSlots; // 0x0000000C length: 4
            // Countdown: set to 3 by setupBuildingData and 5 by changeMapOrientation, decremented at the end of
            // updateBuildings; while non-zero UpdateDairyFarm calls updateBuildingAreaTileGraphics (only the dairy
            // farm reads it)
            undefined4 areaGfxRefreshTicks; // 0x00000010 length: 4
            Building buildings[2000]; // 0x00000014 length: 1624000
            BuildingCostStruct buildingCosts[110]; // 0x0018C7D4 length: 2200
            // [070 0x00419C70] dirty flag that triggers relinking of gates, keeps and siege towers, not only keeps
            undefined4 pathLinkageDirty; // 0x0018D06C length: 4
            undefined4 counter; // 0x0018D070 length: 4
            undefined2 DAT_BuildingIDsNeedPeasantsQueue[2000]; // 0x0018D074 length: 4000
            undefined4 DAT_CountOfBuildingsNeedPeasants; // 0x0018E014 length: 4
            int campfireSpotX; // 0x0018E018 length: 4
            int campfireSpotY; // 0x0018E01C length: 4
            int campfireSpotOrientation; // 0x0018E020 length: 4
            // When 1 (constructor, gfx-layer changes) wheat/hops field graphics are redrawn fully; 0 = incremental
            // one-tile-per-tick update; cleared after updateBuildings
            undefined4 farmFieldGfxFullRefresh; // 0x0018E024 length: 4
            int DAT_TempXOffset; // 0x0018E028 length: 4
            int DAT_TempYOffset; // 0x0018E02C length: 4
            int farmerDestinationTile; // 0x0018E030 length: 4
            int hopFarmerDestinationOffsetX; // 0x0018E034 length: 4
            int hopFarmerDestinationOffsetY; // 0x0018E038 length: 4
            int menuSelectedBuildingID; // 0x0018E03C length: 4
            int newSelectedBuildingID; // 0x0018E040 length: 4
            int menuSelectedUnitID; // 0x0018E044 length: 4
            int newSelectedUnitID; // 0x0018E048 length: 4
            // Help section name (char*) of the building/unit shown in the status menu; NULL hides the help button
            undefined4 statusMenuHelpSectionName; // 0x0018E04C length: 4
            // Index returned by findOrAddHelpSectionName for statusMenuHelpSectionName; passed to
            // openBuildingHelpDialog
            undefined4 statusMenuHelpSectionIndex; // 0x0018E050 length: 4
            char* DAT_CurrentlyPlayingBuildingBik; // 0x0018E054 length: 4
            BOOLEnum DAT_IsBuildingOrPeasantBinkPlaying; // 0x0018E058 length: 4
            // Set when a building click opens no status menu, cleared when a menu opens; renderer shows its health.
            // Not the status-menu building Building ID whose status menu was opened (highlighted in the overlay
            // render)
            int clickedNoMenuBuildingID; // 0x0018E05C length: 4
            // UID partner of clickedNoMenuBuildingID UID of the building whose status menu was opened (validates
            // statusMenuBuildingID)
            undefined4 clickedNoMenuBuildingUID; // 0x0018E060 length: 4
            BOOLEnum isFirstTickInLoop; // 0x0018E064 length: 4
            int DAT_DraggedTileCountVerified; // 0x0018E068 length: 4
            // [214 0x00466160] compared with currentResources[2] (wood), triggers RLSFX_WOOD, sent as the wood cost
            // param1 of GCT_REPAIR_TOWER
            int selectedBuildingRepairWoodCost; // 0x0018E06C length: 4
            int INT_SelectedBuildingStoneRepairCost; // 0x0018E070 length: 4
            // Set when buildings are set up / logical tile map changes; towers then re-apply their MiscDisplayLayer
            // tile flags; cleared after updateBuildings
            undefined4 towerTilesRefreshPending; // 0x0018E074 length: 4
            // decremented per frame; at 0 selects units[newSiegeEngineUnitID] and opens the siege tent tab
            int selectNewSiegeEngineCountdown; // 0x0018E078 length: 4
            // unit auto-selected when the countdown ends (freshly built siege engine)
            int newSiegeEngineUnitID; // 0x0018E07C length: 4
            // timeGetTime() captured in Constructor_BuildingsState
            undefined4 constructTimeMs; // 0x0018E080 length: 4
            int unused01; // 0x0018E084 length: 4

        private:
            BuildingsState(BuildingsState const&);
            void operator=(BuildingsState const&);

        public:
            BuildingsState() {};
            ~BuildingsState() {};

            // Constructor
            /**
             * BuildingsState constructor: stores timeGetTime() in field37_0x18e080, sets field14_0x18e024 = 1,
             * clears pathLinkageKeepWasUpdatedUnk and counter, calls clearBuildings and sets maxBuildingsCount =
             * 2000.
             */
            BuildingsState* Constructor_BuildingsState();

            /**
             * Returns resources[resourceType] of the building if its uid still matches the expected uid, else 0
             * (guards against a reused building slot).
             */
            int getBuildingResourceAmountByUid(int buildingID, int expectedUid, ResourceType resourceType);

            /**
             * Maps a command/mapper building type (MappersEnum, valid range 0x1c..0x166) to the internal
             * BuildingType via a byte index table + jump table; returns 0 for unmapped values. __stdcall with one
             * stack argument (no this).
             */
            BuildingType convertCommandBuildingTypeToBuildingType(MappersEnum commandBuildingType);

            /**
             * Inverse mapping: BuildingType -> MappersEnum command building type (M_MAPPER_NULL if none). Several
             * pairs disagree with the enum labels: BT_SIEGETOWER->SIEGE_TOWER and BT_BATTERINGRAM->BATTERING_RAM,
             * BT_TOWER1_RUIN_OR_MANGONEL/BT_TOWER2_RUIN_OR_BALLISTA/BT_TOWER3_RUIN/6/3 -> TOWERn_DESTROYED, BT_TUNNEL_CONSTRUCTION -> TUNNEL_CONSTRUCTION,
             * BT_HOUSE -> value 53 (labelled OUTPOST_BEDOUIN), BT_MERCENARYPOST -> BARRACKS_EURO, BT_UNKNOWN1 ->
             * unnamed value 248.
             */
            MappersEnum convertBuildingTypeToCommandBuildingType(BuildingType buildingType);

            /**
             * Returns a per-type height value for tall buildings (manor/stone keep/stronghold 0x40/0x5c/0xbe,
             * gatehouses 0x80, placed siege tower 0x76, towers 1..5), 0 for all other types; used when locating
             * entrances/accessibility around tall buildings.
             */
            undefined4 getBuildingHeightForBuildingID(int buildingID);

            /**
             * If the building's field62_0xb0 is non-zero, returns a per-type height for keeps, gatehouses and
             * towers 1..5 (smaller than getBuildingHeightForBuildingID's values); else 0. Used by
             * recomputeUnitStandingHeight, i.e. likely the height units stand at on top of the building.
             */
            undefined4 getBuildingHeightForBuildingID2(int buildingID);

            /**
             * Returns the base sprite ID for a command building type. Multi-variant decorations (12 gardens, 4
             * cesspits, 5 statues, 5 shrines, 4 ponds) use the group's base sprite plus a per-variant offset from
             * an int table indexed by commandBuildingType (decompiler shows it as misaligned struct members of
             * DAT_BuildingDefinedData); others map to BuildingType and index Building_Sprite_ID_Array_1.
             */
            int getSpriteID(MappersEnum commandBuildingType);

            /**
             * Returns the alternate sprite ID Building_Sprite_ID_Array_2[buildingType] for a command building type,
             * falling back to (tail-calling) getSpriteID with the same commandBuildingType when it is 0. The
             * decompiler's 64-bit return and unassigned this_00 are artefacts: EDX keeps the argument across the
             * call and ECX is passed through unchanged.
             */
            int getSpriteID2(MappersEnum commandBuildingType);

            /**
             * Clears the building array: structCount = 0, zero-fills all 2000 building records (0x32c bytes each,
             * starting at 0xF98534) and sets maxBuildingsCount = 2000.
             */
            void clearBuildings();

            /**
             * Spawns a floating info popup entity above a building whose owner is not currentPlayerSlotID: keep ->
             * owner's gold (entity 0x28, clamped >= 0), campground -> popularity/100 (0x29), marketplace -> trade
             * popup 0x2a/0x2b (by tradeKindFlag) showing tradeAmount with goods icon goodsType*2+0x8d. Nothing is
             * spawned if the owner already has an entity of that type; other building types return immediately. The
             * buildingID parameter is reused as the popup's height offset above the terrain.
             */
            void displayPopularityAndGoldPopups(int buildingID, int tradeKindFlag, int tradeAmount, undefined4 goodsType);

            /**
             * On building deletion spawns entity type 0x1e at the building centre and, for each footprint tile
             * whose RandomLayer value is divisible by 5, another one with a negative (delay) start value
             * -((rand>>4)%20); the buildingID parameter is reused as the tile loop counter. Skipped for drawbridge,
             * tunnel, campfire, signpost, parade grounds, fire ballista, campground, killing pit, siege
             * engines/shield, BT_TUNNEL_CONSTRUCTION and dancing bear. Return value is meaningless (last spawn result or a
             * scratch value).
             */
            int spawnCrowForBuilding(int buildingID);

            /**
             * Returns 1 if the building type is a fear-factor/entertainment-affecting building (gallows, stocks,
             * witch hoist, cesspit, burning stake, gibbet, dungeon, racks, chopping block, dunking stool, maypole,
             * garden, statue, shrine, dancing bear, pond, well, beehive), else 0.
             */
            uint isFearFactorBuilding(int buildingID);

            /**
             * Returns TRUE if the building is a chapel, church or cathedral.
             */
            BOOLEnum isReligiousBuilding(int buildingID);

            /**
             * Transfers ownership of every BLS_NORMAL building (slots 1..1999) owned by playerID to playerID2;
             * outside GM_SOLITARY it also sets the building's playerColorUnk (offset 0x08) to playerID2. If any
             * building moved, copies the primary-building references (keep, marketplace, guilds, stockpile, armory,
             * granary, barracks, merc post, campground, unknown6, oil smelter: id/entry x/y/tile/area) from
             * playerID to playerID2 and clears the old player's ids when the players differ. NAME? more a
             * transferBuildingsToPlayer than a plain copy.
             */
            void copyPlayerDataArrayValues(int playerID, int playerID2);

            /**
             * Counts playerID's BLS_NORMAL workshops of buildingType by what they currently produce
             * (producedItemTypeNext) and returns the weapon type to make next so production stays balanced:
             * blacksmith -> sword (0x16) if swords <= maces else mace (0x15); poleturner -> pike (0x14) if pikes <
             * spears else spear (0x13); fletcher -> crossbow (0x12) if crossbows < bows else bow (0x11); other
             * types -> 0.
             */
            int chooseProductionItemType(int playerID, BuildingType buildingType);

            /**
             * Counts playerID's BLS_NORMAL buildings of buildingType whose currentNumberOfResource (offset 0x184,
             * int at owner+0xAE) is < 1, i.e. storage buildings that currently hold no goods. Returns the count.
             */
            int getEmptyBuildingCount(int playerID, BuildingType buildingType);

            /**
             * Counts playerID's BLS_NORMAL buildings of buildingType. If includeBool is non-zero only buildings
             * whose field242_0x2c8 (short at owner+0x1F2) is 0 are counted (the flag acts as a filter, not an
             * include switch).
             */
            int countBuildingsForPlayer(PlayerID playerID, BuildingType buildingType, int includeBool);

            /**
             * Counts playerID's BLS_NORMAL wheat, apple and dairy farms (hop farms are not counted). If the second
             * argument is non-zero only farms whose field242_0x2c8 is 0 are counted (same filter as
             * countBuildingsForPlayer).
             */
            int countFarms(PlayerID playerID, int onlyIfFlagClear);

            /**
             * Returns the lowest building ID (>=1) whose logical state is BLS_NORMAL, owned by playerID and of
             * buildingType, or 0 if none.
             */
            int findFirstBuildingOfType(int playerID, BuildingType buildingType);

            /**
             * Returns the lowest building ID whose logical state is neither 0 (unused) nor BLS_REMOVE, owned by
             * playerID and of buildingType; 0 if none. Unlike findFirstBuildingOfType it accepts any live state,
             * not only BLS_NORMAL.
             */
            int findFirstBuildingIDForPlayerAndType(int playerID, BuildingType buildingType);

            /**
             * Linear search continuing after buildingID: returns the next live (state != 0 and != BLS_REMOVE)
             * building owned by playerID of buildingType, or 0 when the end of the array is reached (no wrap-
             * around).
             */
            int findNextBuildingForPlayerAndType(PlayerID playerID, BuildingType buildingType, int buildingID);

            /**
             * Cyclic search: starting after the given building ID and wrapping from maxBuildingsCount back to 1,
             * returns the next live building owned by the given player with the given type; gives up after
             * maxBuildingsCount steps and returns 0.
             */
            int findNextBuildingIDForOwnerAndType(int playerID, int buildingType, int startBuildingID);

            /**
             * Cyclic search (wraps to 1) starting after startBuildingID for the next live building owned by
             * playerID whose type equals any of three given building types; returns its ID or 0 after a full lap.
             */
            int findNextBuildingForPlayerAndOneOfThreeTypes(
                int param_1, int param_2, int param_3, int param_4, int param_5);

            /**
             * Cyclic search (wraps to 1) after buildingID for playerID's live defensive building (towers 1-5, manor
             * house, keeps incl. KEEPFOUR/FIVE, large/small gatehouse) that has a non-zero someX and whose
             * PathConnectionLayer area at (someX,someY) is reachable for the player's units from the area of tile
             * (buildingXPosition,buildingYPosition). Returns that building ID or 0. NAME? returns a building ID,
             * not a bool; the x/y params are the start position, not a building's; buildingYPosition is reused as
             * the loop counter.
             */
            int canNavigateToDefensiveBuilding(
                int playerID, int buildingXPosition, int buildingYPosition, int buildingID);

            /**
             * Same as canNavigateToDefensiveBuilding but also accepts shrines: cyclic search after startBuildingID
             * for the given player's live tower/manor/keep/gatehouse/shrine whose someX/someY tile area is
             * reachable from the area of tile (fromX,fromY). Returns building ID or 0. fromY is reused as the
             * iteration counter.
             */
            int findNextReachableDefensiveBuildingForPlayer(int playerID, int fromX, int fromY, int startBuildingID);

            /**
             * Counts playerID's live buildings of buildingType, picks one uniformly using SEC_RNG.currentNumber2 %
             * count (then advances the RNG) and returns its building ID; 0 if none.
             */
            int pickARandomBuildingOfType(int playerID, BuildingType buildingType);

            /**
             * Counts playerID's live buildings whose type is one of three given types, picks a random one via
             * SEC_RNG.currentNumber2 % count (advancing the RNG) and returns its ID; 0 if none.
             */
            int pickARandomBuildingIDOfTheseThreeTypes(
                int playerID, BuildingType buildingType1, BuildingType buildingType2, BuildingType buildingType3);

            /**
             * Picks a random live building of playerID among maypole, garden, statue, shrine, dancing bear, pond,
             * well and beehive (SEC_RNG-based uniform pick) and returns its ID or 0. Used to choose where a resting
             * unit goes. NAME? pond/well/beehive are not counted as good things in recomputeAllFearFactors, so this
             * is a leisure/rest-spot picker rather than a fear-factor one.
             */
            int pickARandomPositiveFearFactorBuilding(int playerID);

            /**
             * Finds the inn owned by the unit's owner that has ale (flagonsOfAleOrCheeseOrReleaseDogs > 0) and
             * whose entry tile (buildingEntryX/Y) is nearest to the unit's x/y by DirectionAlgorithmState axis-
             * based distance (distanceHigh, start 10000). Returns the inn's building ID or 0. The unitID parameter
             * is reused to hold the best building ID.
             */
            int findClosestInnBuildingID(int unitID);

            /**
             * Resets players 1-8 bad/good-thing counters, counts every live building per owner as bad (gallows,
             * stocks, witch hoist, cesspit, burning stake, gibbet, dungeon, rack, flogging rack, chopping block,
             * dunking stool) or good (maypole, garden, statue, shrine, dancing bear), then per player sets
             * fearFactorLevel = (good-bad)/(currentPopulation/16+1) clamped to [-5,5] and objectsLeftUntilNextLevel
             * to the items missing for the next level. If the player's lord (lordID/lordUID) is alive and
             * ULS_NORMAL, records new extremes in finalResults.finalMaxGoodThings/finalMaxBadThings.
             */
            void recomputeAllFearFactors();

            /**
             * Returns 1 if playerID owns any building of buildingType with a non-zero logical state (including
             * BLS_REMOVE), else 0. NAME? returns a bool, not the building (playerHasBuildingOfType).
             */
            undefined4 findBuildingOfTypeForPlayer(int playerID, BuildingType buildingType);

            /**
             * Marks for removal (logicalState = BLS_REMOVE) all of playerID's live tunnels regardless of wave, and
             * its catapults, fire ballistae, trebuchets, battering rams, siege towers and shields whose attackWave
             * (> 0) equals the given attackWave.
             */
            void removeSiegeBuildings(int attackWave, int playerID);

            /**
             * Initialises Building.entranceAttemptTileIndex: direction = (buildingVariation+4) mod 8 (variation
             * 0xF: 4, tunnels/BT_TUNNEL_CONSTRUCTION: 2), index = (direction/2) * (widthOrHeight + 2*ringOffset), i.e. the
             * first perimeter tile of side direction/2; ox tethers always get 9.
             */
            void setBuildingInitialEntryTileTry(int buildingID, undefined4 ringOffset);

            /**
             * If playerID has a campground, writes a gathering tile into BuildingsState.DAT_TempXOffset/YOffset
             * depending on the campground orientation (2: x+1,y+3; 4: x+3,y+5; 6: x+5,y+3; else x+3,y+1) and
             * returns 1; returns 0 when there is no campground.
             */
            undefined4 prepareCampgroundCoords(int playerID);

            /**
             * Returns 1 if the building's per-side byte flag (field_0x280..0x283) for the side selected by the
             * current map orientation (0->0x281, 2->0x282, 4->0x283, 6->0x280) is set, else 0.
             */
            undefined4 hasBuildingEntranceFlagForOrientation(int buildingID);

            /**
             * Like hasBuildingEntranceFlagForOrientation but checks the next side in rotation (one step further,
             * not the opposite side): map orientation 0->field_0x282, 2->0x283, 4->0x280, 6->0x281; returns 1 if
             * that flag is set.
             */
            undefined4 hasBuildingExitFlagForOrientation(int buildingID);

            /**
             * For buildingID 0 returns 0. For large/small gatehouses (0x2D/0x2E) and towers 1-5 (0x4A-0x4E) returns
             * 1 if the current player's units cannot path from the area of fromTileIndex to the area of the
             * building's (x+1,y+1) tile; for all other types returns BuildingTypeHasHealth[type] != 0.
             */
            uint isBuildingPathBlockerOrDamageable(uint buildingID, int fromTileIndex);

            /**
             * Returns FALSE for buildingID 0, TRUE for gatehouses (0x2D/0x2E) and towers 1-5 (0x4A-0x4E), otherwise
             * BuildingTypeHasHealth[type] != 0. The second argument is ignored (same signature as
             * isBuildingPathBlockerOrDamageable).
             */
            BOOLEnum getBuildingHasHealthProperty(uint buildingID, int unusedTileIndex);

            /**
             * Scans the building's square footprint (widthOrHeight x widthOrHeight from x,y) in
             * TileMapState.UnitLayer and returns TRUE if any unit there belongs to an owner with
             * currentPlayerFullIDArray[owner] != -1 (a human/connected player slot), else FALSE.
             */
            BOOLEnum hasHumanPlayerUnitsOnBuilding(int buildingID);

            /**
             * Looks up the x/y offset of perimeter tile perimeterIndex for a footprint of size 1..13 from
             * BuildingDefinedData.entranceOffsetsSizeN into BuildingsState.DAT_TempXOffset/YOffset (0,0 for other
             * sizes), then pushes it outward by ringOffset (4th stack arg, shown as stackArg3) according to side =
             * perimeterIndex/size via a jump table (0: y -= r, 1: x += r, 2: y += r, 3: x -= r; Ghidra shows it as
             * an indirect call). Afterwards, for EVERY side (Ghidra only shows it on the side >= 4 path): if both
             * offsets are < size, a negative x becomes x - placedSize + 1, else a negative y becomes y - placedSize
             * + 1, so a multi-tile object placed on the negative side still touches the footprint. Almost all
             * callers pass placedSize = 1 and ringOffset = 0. Real convention __thiscall (ECX = BuildingsState),
             * stack args footprintSize, placedSize, perimeterIndex, ringOffset, ret 0x10; EAX return is junk.
             */
            void setupBuildingEntrancesOffset(int footprintSize, int placedSize, int perimeterIndex, int stackArg3);

            /**
             * Twin of setupBuildingEntrancesOffset with other tables: looks up the x/y offset of candidate tile
             * `try` around a footprint of the given size (1..13) from BuildingDefinedData field179..field191 into
             * BuildingsState.DAT_TempXOffset/YOffset (left unchanged for other sizes), pushes it outward by
             * `offset` according to side = try/size (0: y-=offset, 1: x+=offset, 2: y+=offset, 3: x-=offset; the
             * decompiler shows this switch as an indirect call), then for every side: if both offsets are < size
             * and x < 0, x = x - nudge + 1 (moved further out), else if y < 0, y = y - nudge + 1.
             */
            void setupNextCandidateLocationComputeOffsets2(int size, int nudge, int try_, int offset);

            /**
             * Returns TRUE if the building (stockpile slot) is empty, or already holds resourceType and that amount
             * is below StorageLimitResourceTypeArray[resourceType]; FALSE if it holds something but none of
             * resourceType, or is full.
             */
            BOOLEnum buildingHasSpaceForResource(int buildingID, ResourceType resourceType);

            /**
             * For every BLS_NORMAL building of the given type owned by the given player, raises
             * Building.deliveryActivityCountdown (offset 0xA4) to newValue if it is currently <= newValue (max-
             * assign of a countdown). Real convention: __thiscall with 3 stack args (buildingType, newValue,
             * playerID).
             */
            void extendResourceCountdownForPlayerBuildingsOfType(
                BuildingType buildingType, int someCountdown, int playerID);

            /**
             * If the building holds no resource type other than resourceType (scans resources[1..24]) returns
             * storageLimit minus the stored amount of resourceType (0 if full); returns 0 if any other resource is
             * present.
             */
            int canBuildingStoreTheAmount(int buildingID, ResourceType resourceType, int storageLimit);

            /**
             * Returns capacity - Building.currentNumberOfResource (0 if already at or above capacity). The resource
             * type argument is ignored. Real convention: __thiscall (ECX = BuildingsState) with 3 stack args, ret
             * 0xC.
             */
            int getResourceCountThatCanBeDeposited(int buildingID, undefined4 unusedResourceType, int capacity);

            /**
             * Returns BuildingDefinedData.StorageBuildingTypeArray[resourceType]: the building type
             * (stockpile/granary/armory/...) that stores the resource. Machine code is __stdcall with one stack arg
             * (ret 4) that leaves ECX/EDX untouched; Ghidra models it as caller-cleaned, which causes the
             * extraout_ECX / shifted-stack artefacts in its callers.
             */
            BuildingType getBuildingStorageTypeForResourceType(ResourceType resourceType);

            /**
             * Searches building IDs downward from maxBuildingsCount-1 for a BLS_NORMAL building of the storage type
             * for resourceType, owned by `owner`, holding at least `amount` of the resource; returns its ID or 0.
             * Ghidra's stack tracking is off after the getBuildingStorageTypeForResourceType call, so the
             * decompiled comparisons show owner==amount and resources[type]>=resourceType; the machine code
             * compares owner with the 3rd arg and resources[type] with the 2nd.
             */
            int getStorageBuildingForResourceTypeAndAmount(ResourceType resourceType, int amount, int owner);

            /**
             * If buildingID is a BLS_NORMAL armory owned by playerID, computes free space as 50 minus the sum of
             * resources[0..24] and returns buildingID when free space >= resourceCount, else 0. Non-matching
             * buildings also return 0; resourceID is unused.
             */
            uint getArmoryIDIfSpaceLeft(uint buildingID, undefined4 resourceID, int playerID, int resourceCount);

            /**
             * For a BLS_NORMAL armory returns 50 minus the sum of resources[0..24] (if non-negative); otherwise 0.
             * The resource type argument is unused.
             */
            int computeArmoryRemainingCapacity(int buildingID, int unusedResourceType);

            /**
             * Recomputes Building.currentNumberOfResource as the sum of resources[1..24] and sets
             * currentLimitOfResource/currentStoredResourceType from the first non-zero resource type (its
             * StorageLimitResourceTypeArray entry). Returns the total.
             */
            uint computeResourceSumForBuilding(int buildingID);

            /**
             * Free-woodcutter rule: when not in Siege That mode and the building type being placed is 3
             * (woodcutter's hut), returns 1 if the player has no BLS_NORMAL woodcutter's hut and less wood
             * (currentResources[2]) than buildingCosts[3].requiredWood; otherwise 0.
             */
            uint hasLessWoodThanTheCostOfAWoodcuttersHutAndNoWoodcutters(int playerID, int buildingType);

            /**
             * Returns the total free space the player has for resourceType across BLS_NORMAL storage buildings of
             * the matching storage type: armories via computeArmoryRemainingCapacity, granaries via
             * getResourceCountThatCanBeDeposited(.., 250), stockpiles the full StorageLimitResourceTypeArray limit
             * if the stockpile is empty (field at +0xB2 of the type field = 0) or limit - stored if it already
             * holds this resource (non-empty stockpiles holding other goods add nothing). Returns 1000000 for
             * storage type 0x28 and -1 if the player has no such building. Real convention: __thiscall(playerID,
             * resourceType), ret 8; Ghidra's stack drift makes the declared resourceType parameter really the
             * playerID compared with the owner, and in_stack_00000008 the resourceType reused as a pointer to
             * resources[resourceType].
             */
            int getResourceSpace(int playerID, int* resourceType);

            /**
             * Recomputes playerID's currentResources[] (except gold, index 15, which is saved and restored) from
             * BLS_NORMAL buildings: stockpiles contribute resources[2..16], granaries [10..13], armories [17..24].
             */
            void countPlayerResources(int playerID);

            /**
             * For players 1-8 saves gold, zeroes currentResources[0..24], then adds resources[0..24] of every
             * BLS_NORMAL stockpile, granary and armory to its owner's currentResources, and finally restores each
             * player's gold.
             */
            void recomputePlayerDataStocksBasedOnStorageBuildings();

            /**
             * Converts a MappersEnum placement command to a building type and writes
             * buildingCosts[type].requiredStone_0x4 to *pStone and buildingCosts[type].requiredGold to *pGold;
             * then, by command, overrides *pGold with fixed prices (killing pit/brazier 5, pitch ditch 2,
             * moat/laddermen 1, archers 12, spearmen 8, pikemen/macemen/crossbowmen/tunnelers 20, swordsmen/knights
             * 40, engineers 30, monks 10) or with the requiredGold of the matching siege-engine entry. Real
             * convention: __thiscall, 3 stack args, ret 0xC.
             */
            void getBuildingCost(MappersEnum commandBuildingType, int* pStone, int* pGold);

            /**
             * Writes to *outPrice the gold value of a unit type (troops: fixed prices, e.g. archer 12, spearman 8,
             * swordsman/knight 40; siege engines: requiredGold of the matching buildingCosts entry); unknown types
             * leave it unchanged.
             */
            void getPriceForDisbandedUnitType(UnitType unitType, int* outPrice);

            /**
             * Returns the stone and gold cost of buildingType from BuildingsState.buildingCosts, overriding gold
             * with 5 for killing pits and 2 for pitch ditches. NAME? a cost lookup (getBuildingStoneAndGoldCost),
             * not specific to resource gain.
             */
            void resourceGainForKillingPitAndPitchDitch(
                BuildingType buildingType, int* ptrRequiredStone, int* ptrRequiredGold);

            /**
             * Siege That only: counts pitch-ditch entries with a non-zero owner in TileMapState.pitchDitches (any
             * owner), then deducts from the current player's starting gold the gold cost of moat tiles and pitch-
             * ditch tiles added since the last call (difference to the counts stored in the player data), and
             * stores the new moat/pitch-ditch counts.
             */
            void subtractPitchAndMoatFromStartingGoldInSiegeThatMode();

            /**
             * Siege That moat check: returns 1 if the current player's starting gold covers (new moat tiles since
             * last charge + 1) times the per-tile moat gold cost.
             */
            uint hasEnoughGoldForMoat();

            /**
             * Returns the ID of the BLS_NORMAL wheat/hop/apple/dairy farm whose 36 field-tile references
             * (tileRef1..tileRef36) include tile; 0 if none.
             */
            int getFarmThatHasTile(int tile);

            /**
             * Walks the farm's 36 field tiles (tileRef1..), storing each into BuildingsState.farmerDestinationTile,
             * and returns 1 at the first tile whose crop stage (DamageLayer byte) needs work for the farm state:
             * state 6 -> stage 11..100, 8 -> 121, 3 -> 0, 120 or 101..119, 5 -> 1 (farmerDestinationTile then holds
             * that tile). Returns 0 otherwise or for other states.
             */
            undefined4 findNextWheatFarmWorkTile(int buildingID);

            /**
             * Wheat farm tick: advances every field tile whose crop stage is 2..102 by one, counts tiles by new
             * stage (<=0, 1, 11..100, 102, 103..119, 120, 121), then sets wheatGrowStateRelated in this order: more
             * than 3 tiles at 121 -> 8; more than 11 growing tiles (11..100) or growing tiles together with 120
             * tiles -> 6; any tile at 121 -> 8; no empty tile and no 120/102/103..119 tile -> 5 if some tile is at
             * stage 1 else 2; otherwise 3.
             */
            void growWheat(int buildingID);

            /**
             * Updates the GfxLayer sprite of wheat field tiles from their crop stage (GMFirstPictureIndex[0xE]
             * + stage offset + RandomLayer&3; only stage 121 gets no random variant). When
             * BuildingsState.farmFieldGfxFullRefresh is 0 it processes exactly one tile per call in WheatFieldTile_Unknown
             * order and saves the resume cursor in Building.field_0x2fc; otherwise it refreshes all 36 tiles. The
             * local_8 counter has no effect on control flow.
             */
            void updateWheatFieldTileGraphics(int buildingID);

            /**
             * Scripted crop damage: for every wheat farm of playerID (any non-zero logical state, scan starts at
             * building 0) sets each of its 36 field tiles' stage to 0 if below 8 else 101, then sets growCounter =
             * -1200 and wheatGrowStateRelated = 2.
             */
            void harmWheatFarmsOfPlayer(int playerID);

            /**
             * Clears the player's 0x6C0-byte barracks parade-ground position table and total; if the player has a
             * barracks, finds the player's three parade-ground parts (PARADEGROUND2/3/4 whose parent building is a
             * barracks) and, if all exist, sets the total to 0x48 and fills 3 x 24 XY positions per layout row =
             * paradeLayoutOffsets + the x/y of the part chosen by paradeGroundPartSelectors. The parameter named
             * buildingID is really the playerID (later reused as the selected part's building ID); locals
             * groundSelectorRow/destPosPtr really hold the PARADEGROUND2/3 IDs and local_14 the PARADEGROUND4 ID.
             */
            void setupBarracksCampgroundPositions(int playerIDThenPartID);

            /**
             * Mercenary-post twin of setupBarracksCampgroundPositions: clears the player's 0x6C0-byte
             * mercenaryParadegroundLocations table and mercenaryParadeLocationsTotal, finds the PARADEGROUND2/3/4
             * parts whose parent building is a mercenary post and, if all exist, sets the total to 0x48 and fills
             * XY positions from the same layout tables. playerID is reused as the selected part's building ID;
             * _chosenParadeGround3/_chosenParadeGround4/_chosenBuilding really hold the PARADEGROUND2/3/4 part IDs.
             */
            void setupMercenaryPostCampgroundPositions(int playerIDThenPartID);

            /**
             * Finds a gathering tile for a barracks-trained unit of slot value0to6 (slot 6 shares slot 5's parade
             * list). For AI players in non-solitary games (unit aiUnitBehaviourType != 2) it returns the keep's
             * someX/someY (1, or 0 if there is no keep). Otherwise, with no assembly point set (and a barracks
             * present), scans the 72 barracks parade-ground locations from rallySearchOffsetsUnk[slot] for an in-
             * map, valid tile that is free (or holds this unit, or unit movementRelated != 8); with an assembly
             * point set, scans the 49 SearchRelatedXYOffsets_1 around it for such a tile that is also path-
             * reachable from the unit's area. Result in BuildingsState.DAT_TempXOffset/YOffset; returns 1 only if a
             * tile was found and differs from the unit's current position. NAME? it finds the rally tile
             * (findFreeBarracksAssemblyTile), not just a yes/no.
             */
            undefined4 isSpaceAvailableAtUnitRallyPoint(int playerID, int value0to6, int unitID);

            /**
             * Mercenary-post twin of isSpaceAvailableAtUnitRallyPoint: for AI players in non-solitary games returns
             * the keep's someX/someY; otherwise picks a free gathering tile for mercenary slot param_2 (10..16; 16
             * shares 13's parade list) from the mercenary parade-ground positions (no assembly point) or from the
             * 49 search offsets around mercenaryAssemblyPoints[slot-10] (with reachability check). Output in
             * DAT_TempXOffset/YOffset, returns 1 if found and not the unit's current tile. Quirk: for slot 13
             * without assembly point it tests countPitchRigs, which is mercenaryAssemblyPoints[16] (raw slot used
             * as index) where the barracks twin tests the partner slot's assembly point. NAME? the keep is only the
             * AI fallback; this is findFreeMercenaryAssemblyTile.
             */
            undefined4 getKeepLocationForAIUnit(int playerID, int mercSlot, int unitID);

            /**
             * For the currently open building menu tab (barracks, mercenary post, engineers guild, tunnelers guild,
             * cathedral) creates floating-layer render elements at each of the current player's set assembly
             * points: an animated flag (GID_FLOATS_NEW frame 0x61 + field165_0x5549d0 % 10) plus the unit-type icon
             * for that slot (tables field382/384/401, tunneler/fighting-monk bodies; barracks slot 6 and mercenary
             * slot 1 get a second icon from field383). NAME? it draws assembly-point markers, no game entity is
             * created.
             */
            void createEntityForAssemblyPointsForActiveTabType();

            /**
             * Clears the player's 25 engineer parade-ground positions (100 bytes) and their total; if the player
             * has an engineers guild, finds the last live BT_PARADEGROUND building owned by playerID (Ghidra shows
             * the owner compare as unaff_ESI; machine code compares with the stack argument playerID) and fills 25
             * positions = EngineersParagroundOffsets + its x/y, total 0x19.
             */
            void setupEngineersGuildParagroundPositions(int playerID);

            /**
             * Finds a free gathering tile for an engineer or ladderman (assembly slot 0/1). Without an assembly
             * point it scans the 25 engineer parade positions (engineers forward from index
             * someCount27-someCount28, laddermen backward from entry 24-someCount28); with one it scans the 49
             * search offsets around it requiring path reachability. Output in DAT_TempXOffset/YOffset; returns 1 if
             * found and not the unit's tile.
             */
            int findFreeEngineerAssemblyTile(int playerIndex, int unitID);

            /**
             * Clears the player's 25 tunneler parade-ground positions and total; if the player has a tunnelers
             * guild, finds the last live BT_PARADEGROUND5 owned by playerID (shown as unaff_ESI; really the stack
             * argument) and fills 25 positions = TunnelersGuildParadegroundLocationOffsets + its x/y, total 0x19.
             */
            void setupTunnelersGuildCampgroundPositions(int playerID);

            /**
             * Finds a free gathering tile for a tunneler: around the tunnelers-guild assembly point via the 49
             * search offsets (path-reachable) if one is set, else among the 25 tunneler parade positions; both
             * searches start at someCount29. Output in DAT_TempXOffset/YOffset; returns 1 if found and not the
             * unit's tile.
             */
            undefined4 findFreeTunnelerAssemblyTile(int playerID, int unitID);

            /**
             * Finds a free gathering tile for a monk around the cathedral assembly point; returns 0 if none is set.
             * Original-game bug (confirmed in machine code): the loop counter runs from someCount30 to 48 but the
             * candidate is always SearchRelatedXYOffsets_1[3] (fixed address), so the same tile is re-tested each
             * iteration. Output in DAT_TempXOffset/YOffset; returns 1 if that tile is free/reachable and not the
             * unit's tile.
             */
            undefined4 findFreeCathedralAssemblyTile(int playerID, int unitID);

            /**
             * Fills the oil smelter's 16 tile references (int array at Building.workers+0x10 bytes, i.e. the
             * tileRef array) with tile indices of building x/y + field412_0xa00c offsets, skipping out-of-map or
             * invalid tiles (byte table at 0x21AEC98).
             */
            void setTileRefsForOilSmelter(int buildingID);

            /**
             * Computes an engineer's work tile at a building (oil smelter tile refs): slot 0 if unit.isManningBuilding
             * != 0, else slot (15 - slot) when carrying a resource, else slot; converts the building's tile
             * reference for that slot to DAT_TempXOffset/YOffset and returns 1 if the unit is not standing on it.
             */
            undefined4 isEngineerNotAtAssignedWorkTile(int buildingID, int unitID, int workSlot);

            /**
             * Returns the unit ID in Building.workerID[0] if it is still the same unit (uid match), alive
             * (ULS_NORMAL, not dying), an engineer, assigned to this building and has field252_0x3c4 set; otherwise
             * 0.
             */
            uint getActiveEngineerForBuilding(int buildingID);

            /**
             * Hop farmer: for each of the farm's 24 tiles (sets farmerDestinationTile) whose crop stage matches the
             * farm state (state 5: stage 14..27; state 3: stage 0..1; other states return 0), tries up to 4
             * cardinal neighbours (start direction 2, or 4 if field_0x26e == 0x51; direction carries over between
             * tiles) that share the farm entry's path area and differ in height by < 16; on success the direction
             * offset stays in hopFarmerDestinationOffsetX/Y and returns 1. Returns 0 otherwise. The buildingID
             * parameter is reused as a pointer into the tile-ref array.
             */
            undefined4 setNewOnFarmDestination(int buildingID);

            /**
             * Hop farm tick over 24 field tiles: stages 2..31 and 80..84 advance by one, 32..79 and >=85 reset to
             * 0; counts empty (<2), growing (14..27) and ripe (>80) tiles. Sets wheatGrowStateRelated to 5 if more
             * than 5 growing or growing and ripe coexist, else 3 if any tile is empty, else 2.
             */
            void growHops(int buildingID);

            /**
             * Updates GfxLayer of hop field tiles: frame = GMFirstPictureIndex[0xE] + 0x25 + 9*(RandomLayer&1)
             * + stage bucket (0..8). Unless BuildingsState.farmFieldGfxFullRefresh is set it processes one tile per call,
             * advancing the cursor Building.field_0x2fc (stored mod 36 but used mod 24); the 3-unchanged counter
             * has no practical effect.
             */
            void updateHopsFieldTileGraphics(int buildingID);

            /**
             * Scripted crop damage: for each hop farm of the player (non-zero logical state) sets its 24 field
             * tiles' stage to 0 if below 6 else 28, writes -1800 to the short at Building.owner+0xEE and sets
             * wheatGrowStateRelated (owner+0x182) to 2.
             */
            void harmHopFarmsOfPlayer(int playerID);

            /**
             * For the 23 tiles referenced from Building.tileRef5 sets GfxLayer to GMFirstPictureIndex[0xE] +
             * 0x37 + getRubbleGraphicStageForDamageLevel(stage byte) when it changed, clearing MiscDisplayLayer
             * bits 2-3. Used by the dairy farm; return value is incidental. NAME? dairy-farm specific.
             */
            ushort* updateBuildingAreaTileGraphics(int buildingID);

            /**
             * Scripted event: for every dairy farm of the player (non-zero logical state) sets the short at
             * Building.owner+0x1DA to 1600.
             */
            void setDairyFarmCheeseCounter(int playerID);

            /**
             * Scripted event: for every apple farm of the player sets the 8 orchard trees on its tileRef1..tileRef8
             * tiles (via OrganismLayer) to stage 4 with stageTracker -1200.
             */
            void harmAppleFarmTreesOfPlayer(int playerID);

            /**
             * After map load, registers every signpost building (IDs 0..1999) in the first free (< 1) slot of
             * mapAndTime.signpostIDs[8], skipping buildings already registered. The in-code 'missing break' bug
             * note is wrong: machine code jumps past the assignment when the ID is found.
             */
            void setSignpostDataForBuildings();

            /**
             * Clears every mapAndTime.signpostIDs slot equal to the destroyed building ID together with its
             * signpostEntryData (x, y, tile, unknown).
             */
            void destroySignpostData(int buildingID);

            /**
             * Sets the render-animation mode of a punishment/'bad' building (gallows, stocks, dungeon...). Mode 2
             * resets state/animationIndex/field14_0x2c and returns 0; otherwise sets animationIncrement (0 for mode
             * 3, else 1), stores the mode in renderAnimation (forced to 0 when unknownStockpileOrSignpostRelated is
             * 0, which also resets animationIndex/field13_0x28/field14_0x2c) and returns field14_0x2c. NAME? it
             * sets an animation mode rather than updating a signpost counter.
             */
            int updateWorkshopProgressSign(int buildingID, int animationMode);

            /**
             * Sets field66_0xbe of the given building to 0x20 (32). Called only by the hunter unit update.
             * field66_0xbe is a render blend/fade level (ViewportRenderState passes it to renderGMWithBlending when
             * non-zero; building updates load 0x1F and count it down). NAME? nothing makes the building an apple
             * farm; 0x20 merely equals BT_APPLEFARM.
             */
            void setBuildingBlendLevelTo32(int buildingID);

            /**
             * During map preparation iterates all building slots (1..maxBuildingsCount-1) and zeroes
             * animStateCounterTracker of every building whose logicalState is BLS_NORMAL.
             */
            void clearBuildingValueWhenStateIsTwo();

            /**
             * Returns buildings[buildingID].unknownFlag3 (used by tile luminescence computation).
             */
            int getBuildingFlag3(int buildingID);

            /**
             * Returns buildings[buildingID].flag1 (used when updating logical tile map sections). Really __thiscall
             * on BuildingsState (ECX = this).
             */
            int getBuildingFlag1(int buildingID);

            /**
             * Picks the sitting spot for a peasant at a campfire: clamps availablePeasants to 23, reads the
             * corresponding tile index from the campfire building's tile-ref table, converts it to campfireSpotX/Y
             * and computes campfireSpotOrientation facing the campfire centre (x+3,y+3). Always returns 1.
             */
            undefined4 determinePeasantSitPosition(int campfireID, int availablePeasants);

            /**
             * After a map rotation, re-applies display flags/entities and the misc display layer for every building
             * slot whose logicalState is non-zero.
             */
            void refreshAllBuildingTileDisplays();

            /**
             * Returns true if worker slot workerIndex of the building holds a unit (id > 0) whose logicalState is
             * not ULS_REMOVE/ULS_INVISIBLE, that is still assigned to this building and whose uid matches the
             * stored workerUID. Really __thiscall on BuildingsState (ECX = this, preserved).
             */
            BOOLEnum hasWorker(int buildingID, int workerIndex);

            /**
             * Links a unit to a building worker slot: stores unitID and its uid in workerID/workerUID[workerIndex]
             * and sets the unit's workerIndex and buildingID.
             */
            void assignWorkerToBuilding(int buildingID, int unitID, int workerIndex);

            /**
             * Recounts a building's employees: for awake, non-mercenary-post/non-barracks buildings with employee
             * slots, validates each slot with hasWorker (clearing invalid slots' workerUID/workerID; extraout_ECX
             * is just this, preserved by hasWorker), sets currentEmployeeCount, stores currentlyNeededEmployeeCount
             * = slots - employed and adds that deficit to the owner's countEconomyBuilding_fixme. Buildings with
             * slots that are sleeping, barracks or mercenary posts get currentlyNeededEmployeeCount = 0.
             */
            void updateNeededEmployeeCount(int buildingID);

            /**
             * Returns the index of buildingType in the worker-assignment priority list (BuildingPrioritiesWhenFire
             * when the player has a burning building, else BuildingPrioritiesWhenNoFire); 30 if not listed. Lower
             * value = higher priority.
             */
            int getBuildingPriority(int buildingType, int hasBurningBuilding);

            /**
             * Applies the player's snooze toggle for one building type (<0x5B): for every normal building of that
             * owner and type, copies the player's per-type snooze flag into Building.sleeping and (unconditionally)
             * zeroes currentEmployeeCount, animationIndex, renderAnimation, the 27 stored ints at
             * Building+0x118..+0x180 and all 4 workerID/workerUID slots (unassigning its workers). The buildingType
             * parameter is reused as the building loop counter.
             */
            void updateAllBuildingsSnoozedState(int playerID, int buildingType);

            /**
             * For every normal building, syncs Building.sleeping with the owner's per-type snooze table (player
             * data +0x115DF8C); when the flag changes it resets currentEmployeeCount, animationIndex,
             * renderAnimation, the same 27 stored ints and the 4 workerID/workerUID slots as
             * updateAllBuildingsSnoozedState. Building types >= 0x5B are always set awake.
             */
            void applySnoozedStateBasedOnPlayerData();

            /**
             * Walks the queue of buildings needing peasants for playerID and assigns workers via
             * UnitsState::assignPeasantToBuilding + assignWorkerToBuilding (the returned unit ID is stored even if
             * 0). Single-slot buildings always get their type's worker in slot 0 (no hasWorker check); quarry fills
             * 3 mason slots, iron mine a miner (slot 0) + transport miner (slot 1), mill/water pot/cathedral 3
             * slots, church 2 slots, each only where hasWorker reports the slot empty.
             */
            void processBuildingIDsNeedPeasantsQueue(undefined4 playerID);

            /**
             * Maintains the player's lady, lord, jester and ghost units. In single-player with no keep (or dead
             * player) it kills lady/lord/jester and the ghost and returns; in multiplayer it returns early when
             * mapU4Int0 is set and playerID == mapAndTime.somePlayerID. Otherwise it spawns a missing lord (and
             * lady/jester if enabled on the map) at the campground entrance (y-1 unless the keep is a manor house),
             * validates each by stored uid and points it at the keep / entrance; AI lords in non-solitary games get
             * health scaled via MaxLordHealthMapping. In single-player for the local player with a shrine and
             * population >= 40, it spawns/maintains a ghost at the shrine entrance.
             */
            void updateLordLadyJesterAndGhostUnits(int playerID);

            /**
             * Returns how many engineers a siege-engine building needs: trebuchet 3, battering ram/siege tower 4,
             * mantlet (shield) 1, catapult/fire ballista 2, other types 0. buildingID 0 returns 2.
             */
            undefined4 getRequiredEngineerCountForSiegeBuilding(int buildingID);

            /**
             * Smooths a building's 'visually active' indicator: while buildingIsVisuallyActive is set the counter
             * ramps up toward 5 (by isFirstTickInLoop per call, 0 jumps to 1); while it is clear the counter ramps
             * down (5 jumps to 4) and buildingIsVisuallyActive is set to counter != 0.
             */
            void updateVisuallyActiveState(int buildingID);

            /**
             * If the building is damaged, computes its repair cost proportional to missing health (min 1 when the
             * base cost is non-zero) into INT_SelectedBuildingStoneWoodCost (from requiredWood) and
             * INT_SelectedBuildingStoneRepairCost (from requiredStone_0x4) and returns TRUE; returns FALSE at full
             * health.
             */
            BOOLEnum updateRepairCostAndReturnIfDamaged(int buildingIndex);

            /**
             * Returns 1 if the unit can reach any accessible perimeter tile of the building (id 1..1999): the
             * tile's height (HeightLayer, plus getBuildingHeightForBuildingID if a building stands there) must be
             * within 16 of the building's DefaultHeightLayer base height and the tile must have a path area;
             * reachability uses calculateCanPlayerUnitsNavigateToAreaFromArea with canAUnitClimb (or
             * calculateCanReachUsingCachedAreaLogic when only Arab assassins are selected). Returns 0 otherwise.
             * The buildingID parameter is reused as the perimeter loop index.
             */
            undefined4 canUnitReachBuildingPerimeter(int buildingIDOrPerimIndex, int unitID);

            /**
             * Returns 1 if the unit's path area can reach (canAUnitClimb rules) any of the 8 neighbours of
             * tileIndex that has a path area; returns 0 immediately when only assassins are selected. Original-game
             * bug (confirmed in machine code): the height check compares HeightLayer[tileIndex] with itself, so
             * neighbour height is never tested. The tileIndex parameter is reused as the direction counter.
             */
            undefined4 canUnitReachAdjacentTile(int tileIndexOrDirIndex, int unitID);

            /**
             * Damages every unit standing on the building's footprint tiles by maxHealth*damageBonus/100
             * (damageBonus acts as a percent of max health); units reaching 0 health die with US_STONE_DEATH_01.
             * Updates healthPercentage and healthbar (percent/10).
             */
            void processDamageToUnitsOnBuilding(int buildingID, int damageBonus);

            /**
             * For buildings burning for >= 400 ticks, when (fireRelatedRNG1 + fireDuration) is a multiple of a
             * size-dependent interval (24-5*size for size < 4, else (8 or 16 - size)*5) spawns a fire entity (type
             * 5) at a random tile of the footprint and, with 50% chance, plays FX_FIRE_POP there.
             */
            void spawnRandomFireEffectOnBuilding(int buildingID, undefined4 playerID);

            /**
             * Returns a fire category for the building type: 1 for ordinary flammable buildings, 5 for fire-using
             * workshops (blacksmith, bakery, inn, oil smelter), 4 for parade grounds/campground, 0 for all other
             * types. Really __thiscall on BuildingsState (ECX = this).
             */
            undefined4 getBuildingFlammabilityFactor(int buildingID);

            /**
             * Puts out a burning building: clears fireDuration, sets cooldownTimer = 2000 and calls
             * updateAllFireEntitiesAtTile on every footprint tile (farms use enlarged footprints 9/9/10/11) and
             * every accessible perimeter tile (via setupBuildingEntrancesOffset). The local named buildingX is
             * really the footprint tile index and then the perimeter tile count.
             */
            void extinguishBuildingFire(int buildingID);

            /**
             * Returns the nearest building (axis distance from the unit to the building entrance, < 1000) that is
             * alive, owned by a player on the unit's team, currently burning (fireDuration != 0) and whose entrance
             * area is reachable from the unit's path area; 0 if none. NAME? it only considers burning buildings
             * (used by the fire watch).
             */
            int findClosestReachableAlliedBuilding(int unitID);

            /**
             * Returns 1 if the player owns any existing (not removed) building with non-zero fireDuration, else 0.
             */
            undefined4 playerHasBurningBuilding(int playerID);

            /**
             * Validates the 4 tethered-unit slots of a building (e.g. stables horses): slots whose unit uid no
             * longer matches are cleared, and randomOutpostField is set to the count of valid slots.
             */
            void validateBuildingTetheredUnits(int buildingID);

            /**
             * Removes unitID from the building's 4 tethered-unit slots (if the stored uid matches), decrementing
             * numberOfAnimals, then revalidates all slots.
             */
            void removeTetheredUnitFromBuilding(int buildingID, int unitID);

            /**
             * Returns how many more engineers a siege-engine building needs: required count (trebuchet 3,
             * catapult/fire ballista 2, ram/siege tower 4, shield 1) minus currentEmployeeCount; 0 for other types.
             */
            int getRequiredEngineersCount(int buildingID);

            /**
             * Copies the static BuildingCost table (5 ints per building type) into the runtime
             * BuildingsState.buildingCosts array up to address 0x5C2A6C.
             */
            void initBuildingCosts();

            /**
             * Calls TileMapState::updatePathLinkagesForBuilding for every non-empty building slot (logicalState !=
             * 0). Walks slots 1..1999 by pointer (end address 0x1124DC4), ignoring maxBuildingsCount.
             */
            void updatePathLinkageLayerForAllBuildings();

            /**
             * Killing-pit trap check for a moving unit: if the unit's tile holds an untriggered (state 0)
             * BT_KILLINGPIT of a different team, the unit is not a trader/trader horse, not stalked and not dying
             * (outside skirmish/multiplayer only when the pit or the unit belongs to the local player), subtracts
             * 18000 health (at <= 0: health 0, US_STONE_DEATH_01, dying = 1), updates healthPercentage and
             * healthbar (= percent/10) and marks the pit triggered (state = 1).
             */
            void processDamageFromKillingPit(int unitID);

            /**
             * Temporarily overrides gatehouse states for pathfinding: for each existing large/small gatehouse, mode
             * 1 saves the gate open-state byte pathLinkageRelated2 (0 open, 2 closed) into pathLinkageRelated1 and
             * forces it to 2, mode 2 saves it and forces 0, any other mode restores the saved value.
             * climbData[...].isRecognizedByPathfinding is set to 0 when the state is 2, else 1, then
             * PathFindingState::updatePathLinkageTileMapRelatedToGates is called for the gate.
             */
            void updatePathLinkageTileMap(int gateOverrideMode);

            /**
             * For each existing large/small gatehouse owned by playerID whose field241_0x2c6 is 0, marks its climb
             * data (index laddermanDataID) as recognized by pathfinding, sets pathLinkageRelated2 = 0 (open),
             * gateState = 0x0B (open command, cf. applyGateOrDrawbridgeOpenCloseChange) and gateCloseOpenTimer =
             * 2500, then refreshes gate path linkage.
             */
            void initializeGatePathfindingForOwner(int playerID);

            /**
             * Map-version upgrade: for every existing BT_GATEHOUSELARGE/BT_GATEHOUSESMALL/BT_WOODGATE1
             * (0x2D/0x2E/0x2F) re-stamps its footprint tiles. Wood gate: clears LogicLayer bits 0x10100, sets
             * 0x10000000, clears MiscDisplayLayer bit 0x20 and writes the building's stored height byte into
             * HeightLayer; stone gatehouses: set LogicLayer 0x100 and put owner-1 into the low 3 bits of
             * WallOwnerLayer. All clear LogicLayer bit 0x400. NAME? only gates are handled, no walls.
             */
            void rebuildTileLogicLayerForGatesAndWalls();

            /**
             * Map-version upgrade: for every existing keep-type building (BuildingIsKeepArray) clears LogicLayer
             * bit 0x400 and sets bit 0x10000000 on all footprint tiles.
             */
            void rebuildTileLogicLayerForKeeps();

            /**
             * When pathLinkageKeepWasUpdatedUnk > 0, clears it, increments counter and refreshes path linkage for
             * every live (not BLS_REMOVE) gatehouse/wood gate 1, keep (stone keep, stronghold, keep four/five) and
             * placed siege tower via the matching PathFindingState updater.
             */
            void updatePathLinkageForGatesKeepsSiegeTowers();

            /**
             * Rebuilds playerID's enemy building list (only if the slot is active: single-player, human or AI):
             * stores id and uid of every existing building of another team into playerEnemyBuildingIDs/UID; count
             * in playerBuildingInfoIndex. Skipped types: stockpiles, BT_UNKNOWN1, manor house, keeps, drawbridge,
             * tunnel, campfire, signpost, parade grounds, campground, fire ballista, killing pit, keep doors, siege
             * engines (0x50-0x55), pond. Gatehouses and towers are NOT skipped.
             */
            void updateEnemyBuildings(int playerID);

            /**
             * Scans playerID's enemy building list and returns the closest building whose uid still matches, that
             * is not burning (fireDuration 0) and whose getBuildingFlammabilityFactor is neither 0 nor 4, within
             * radius of (x,y) (squared distance), else 0. Only caller: UpdateFireBallista for AI-owned ballistas
             * with no unit target. playerID is reused as the remaining-entries counter; local idListDelta really
             * holds the flammability factor, then dy, then the squared distance.
             */
            int aiFindBuildingToAttack(int playerIDThenEntriesLeft, int x, int y, int radius);

            /**
             * Returns the closest building from playerID's enemy building list (uid still matches) whose x/y lies
             * within radius of (x,y) (squared distance), else 0. Used by the mangonel. playerID is reused as the
             * remaining-entries counter.
             */
            int findClosestEnemyBuildingWithinRadius(int playerID, int x, int y, int radius);

            /**
             * Marks a building BLS_REMOVE (noRubble = 1 when showNoRubbleWhenDestroyingBuilding is 0), tears down
             * signpost data for signposts, recomputes fear factors / religion bonuses if relevant, and also marks
             * BLS_REMOVE every live building whose int at logicalState+0x1D8 equals this building's non-zero
             * uidWhenPlaced (same noRubble rule). Finally resets showNoRubbleWhenDestroyingBuilding to 0.
             */
            void destroyBuilding(int buildingID);

            /**
             * Destroys every non-empty building owned by playerID via destroyBuilding, setting
             * showNoRubbleWhenDestroyingBuilding per type from BuildingShowRubbleWhenDestroyed beforehand.
             */
            void destroyBuildings(int playerID);

            /**
             * Swaps ownership of all BLS_NORMAL buildings (slots 1..1999) between two players (outside single-
             * player also updating an int field 0xCE bytes before owner) and, if anything was swapped, exchanges
             * their key-building entry records (keep, marketplace, guilds, stockpile, armory, granary, barracks,
             * mercenary post, campground, unknown6, oil smelter).
             */
            void swapOwnersOfCastle(int playerA, int playerB);

            /**
             * Chooses a building's entry tile (buildingEntryX/Y) = the workerIndexPlus1-th valid candidate (counter
             * shared by all passes). A tile is valid when free (LogicLayer & 0x50501481 == 0) and its height (+
             * height of a building on it) is within tolerance of the building's terrainHeight. Pass 1: ring of
             * size+2*flag from entranceAttemptTileIndex, tolerance 16 (32 for quarry), area equal to or navigable
             * from the owner's campground entry area, or ABuildingTypeValueArray[type] set; pass 2: next larger
             * ring, tolerance 16, same rule; both return 1. Pass 3: ring again, tolerance 16, any non-zero path
             * area; returns 2. Else 0. Locals are misnamed: buildingIDThenTile holds the building's terrainHeight,
             * buildingHeight the ring start/loop index, the pass-1 tile, a reachability result and the pass-2/3
             * ring tile counts, ringCountOrTile the buildingID (then the pass-3 tile), and flag the step counter.
             */
            undefined4 determineBuildingEntranceFromCampgroundArea(int buildingIDThenRingIdx, int workerIndexPlus1, BOOLEnum borderFlagThenStepCount);

            /**
             * Variant of determineBuildingEntranceFromCampgroundArea whose reference area is the path area of tile
             * (x,y): pass 1 (ring of size+2*border, tolerance 16/32 for quarry) requires the tile area to equal or
             * be navigable from that area, pass 2 (larger ring, tolerance 16) also accepts
             * ABuildingTypeValueArray[type]; both return 1 for the matchIndex-th valid tile and store it in
             * buildingEntryX/Y. Fallback pass 3 accepts any free height-matching ring tile with a path area and
             * returns 2; else 0. The y parameter is reused as the loop counter.
             */
            undefined4 determineBuildingEntranceFromCustomArea(int buildingID, int matchIndex, int border, int x, int yThenLoopIdx);

            /**
             * For towers of footprint 4/5/6 (other sizes: return untouched), clears the 4 per-side bytes
             * wallOnSide[] and walks the perimeter ring once, starting at index count-1 (size 4) or count-2 (size
             * 5/6) and wrapping; at step i it sets wallOnSide[i / size] = 1 when the current ring tile is a wall
             * tile (LogicLayer 0x100 set, 0x2 and 0x200 clear). The side index comes from the step counter, not
             * from the ring index, so the start offset rotates sides by one/two tiles.
             */
            void computeBuildingEntranceFlagsForOrientations(int buildingID);

            /**
             * Searches the ring around a quarry (footprint buildingSize, starting a quarter of the way round) for
             * an offset where a building of commandBuildingType (the quarry pile) with size pileSize can be placed:
             * each try calls setupBuildingEntrancesOffset(buildingSize, pileSize, index, tryUnk as ring offset) and
             * checkBuildingCanBePlacedHere at (x,y)+offset, stopping when buildingPlacementResult is FALSE; the
             * found offset stays in DAT_TempXOffset/YOffset (on failure the last tried one remains). buildingSize
             * is reused as the attempt counter.
             */
            void findQuarryPileLocation(undefined4 playerID, int x, int y, int buildingSize, int pileSize, int tryUnk,
                MappersEnum commandBuildingType);

            /**
             * Returns TRUE if any tile on the ring around a footprint of size at (x,y) holds a BLS_NORMAL building
             * of the given type owned by playerID, else FALSE. size is reused as the loop counter.
             */
            BOOLEnum hasBuildingAsNeighbour(int playerID, int x, int y, int sizeThenLoopIdx, BuildingType type);

            /**
             * Returns the ID of the first BLS_NORMAL building of buildingType (other than buildingID) found on the
             * ring around a footprint of buildingSize at (x,y), else 0. The first stack argument (callers pass the
             * building's owner) is never read; buildingSize is reused as the loop counter.
             */
            int findParticularBuilding(
                undefined4 param_1, int x, int y, int buildingSize, BuildingType buildingType, int buildingID);

            /**
             * Returns the path-connection area ID of the first tile on the ring around a footprint of buildingSize
             * at (x,y) that has one, else 0. The local named perimeterTileCount actually holds the tile index.
             */
            int findAccessibleAreaNearBuildingLocation(int x, int y, int buildingSize);

            /**
             * Adds `amount` of resourceType to a storage building's slot if the building UID still matches:
             * maxCapacity 0 clears the slot and returns 0; otherwise the new total must lie in [0, maxCapacity]
             * (else 0). Only if recomputeResources is set it commits the value, adds amount to the owner's
             * currentResources for stockpile/armory/granary, extends the resource countdown of the LOCAL player's
             * buildings of that type (600), recomputes building/player sums and refreshes the building graphics.
             * Returns 1 whenever the amount fits (also in check-only mode).
             */
            undefined4 addResourceToStockpile(int buildingID, int buildingUID, ResourceType resourceType, int amount,
                int maxCapacity, int recomputeResources);

            /**
             * Distributes `amount` units of resourceType one at a time into granary records owned by playerID (no
             * logicalState check; slot capacity 250 via getResourceCountThatCanBeDeposited/addResourceToStockpile),
             * stopping when amount reaches 0 or all granaries were tried. The 64-bit deposit value is an artefact:
             * its high half is just the saved BuildingsState pointer.
             */
            void addResourceToGranary(ResourceType resourceType, int playerID, int amount);

            /**
             * Stores weapons into the player's armories (slot capacity 50): first puts the whole amount into the
             * first armory getArmoryIDIfSpaceLeft accepts; otherwise deposits units one by one across armories
             * until amount is exhausted (any rest is dropped).
             */
            void addResourceToArmory(ResourceType resourceType, int playerID, int amount);

            /**
             * Removes `amount` of resourceType from playerID. Siege That: pendingResources -= amount (only if
             * !previewOnly). Unstored types (storage type 0x28, e.g. gold): currentResources -= amount (only if
             * !previewOnly). Otherwise walks all BLS_NORMAL buildings of the storage type owned by the player that
             * hold the good: preview writes the share to take into pendingResourceLossPreview; real mode zeroes it,
             * deducts building stock and player total and recomputes sums; graphics refreshed. The walk never stops
             * early. If no such building held the good, currentResources[resourceType] is forced to 0 (also in
             * preview).
             */
            void processResourceLoss(int playerID, ResourceType resourceType, int amount, int previewOnly);

            /**
             * If the building is a stockpile, granary or armory, subtracts each of its stored resource amounts
             * (types 1..24) from the owner's currentResources (clamped at 0) and recounts the player's resources.
             * Called from deleteBuilding.
             */
            void subtractResourcesStoredInBuilding(int buildingID);

            /**
             * Charges playerID the placement cost of buildingType via processResourceLoss (preview flag passed
             * through), unless buildings are free, in the editor, a manor/keep in single-player, or
             * hasLessWoodThanTheCostOfAWoodcuttersHutAndNoWoodcutters exempts it. Pitch ditch: 1 pitch on every 4th
             * tile via pitchDitchCounterTo4 (free in Siege That). Siege That: only stone and gold are charged,
             * after resourceGainForKillingPitAndPitchDitch adjusts them; wood/iron/pitch are free. Otherwise wood,
             * stone, iron, pitch, gold from buildingCosts.
             */
            void processPlacementResourceLossForBuildingType(int playerID, BuildingType buildingType, int isPreview);

            /**
             * Charges stone for wall tiles: cost = (lowCount + 2*highCount + carried remainder)/4; the remainder
             * (total & 3) is stored back in partialStoneCounter only on a real placement (zero == 0, i.e. not
             * preview). Siege That charges highCount directly. Stores the cost in wallPlacementCost and, for the
             * local player on a real placement with non-zero cost, sets WallAndPitchState.flag = 0 and counter =
             * cost.
             */
            void processWallBuildingLoss(int playerID, int highCount, int lowCount, int zero);

            /**
             * Removes lossPercent % of the player's bread, cheese, meat and apples (currentResources[10..13]) via
             * processResourceLoss (real, not preview).
             */
            void applyFoodLossPercentageToPlayer(int playerID, int lossPercent);

            /**
             * Gives playerID `amount` of resourceType if getResourceSpace suffices (else FALSE); amount <= 0 ->
             * TRUE. Unstored types (storage 0x28) go straight to currentResources; armory (0xb) and granary (0x13)
             * types are delegated to addResourceToArmory/addResourceToGranary. Stockpile goods are added unit by
             * unit: pass 1 tops up BLS_NORMAL stockpiles already holding goods and this good, pass 2 fills
             * completely empty ones; TRUE once all is stored, else recount and FALSE. The local
             * buildingResourcePtr2 is really the pass-2 building ID.
             */
            BOOLEnum processResourceGain(int playerID, ResourceType resourceType, int amount);

            /**
             * Opens (open = TRUE) or closes a gatehouse/drawbridge pair. For a drawbridge it finds the adjoining
             * large or small gatehouse and, if its pathLinkageRelated2 is 2 (closed) sets gateState = 0xB (open;
             * timer 600 if setAutoTimer), or if 0 (open) sets gateState = 10 (close; timer -1 if setAutoTimer). For
             * a gatehouse it updates up to two adjoining drawbridges' drawbridgeState2 (0xB when drawBridgeState1
             * == 2, 10 when 0).
             */
            void applyGateOrDrawbridgeOpenCloseChange(int buildingID, BOOLEnum open, BOOLEnum setAutoTimer);

            /**
             * Bubble-sorts DAT_BuildingIDsNeedPeasantsQueue: ascending by building idleTimerUnk, ties broken by
             * getBuildingPriority (lower value first; priorities depend on whether the player has a burning
             * building).
             */
            void sortBuildingIDsNeedPeasantsQueue(int playerID);

            /**
             * Sets a building on fire. Returns 0 if it is cooling down (except campfire/parade grounds/campground),
             * not flammable, or owned by burnerPlayerID with flammability factor != 4. Returns 1 if already
             * burning, or (spareGrounds != 0) for campfire/parade grounds/campground without igniting. Otherwise
             * fireDuration = 1, ifFireThenResponsiblePlayer = burnerPlayerID, plays General_Warning16 for the local
             * owner (at most every 800 ticks) and ignites fire entities (attributed to burnerPlayerID) on footprint
             * tiles without fire, with a random start delay; returns 1. Local existingFireID really holds
             * flammability, then owner, then building y.
             */
            undefined4 lightUpBuilding(int buildingIDThenFootprintIdx, int burnerPlayerID, int spareGrounds);

            /**
             * Migrates loaded building data for older map versions: always runs base fixups, rebuilds gate and keep
             * logic-layer bits and relinks gates/keeps/siege towers (pathLinkageKeepWasUpdatedUnk = 1); then, if
             * receivedMapVersion != packagerMapVersion, applies each Version::Upgrade* step whose threshold
             * (0x67..0xAC) is above receivedMapVersion.
             */
            void upgradeBuildingsForMapVersion(
                PackagedFileMagicNum receivedMapVersion, PackagedFileMagicNum packagerMapVersion);

            /**
             * Allocates a free building slot (1..1999, 0 if none or tile (x,y) invalid), zeroes it and initialises
             * it: uid, owner, position, type, size, height, variation, sprite/GFX data, HP, employee counts,
             * cooldown (2000 for AI in multiplayer, else 400), entrance; then type-specific setup (category entry
             * points, workshop products, cage dogs, cesspit ET_DISEASE_CLOUD entity + FX_FLIES, outposts, siege-
             * equipment orders) and fear/religion recompute. Returns buildingID. Decompiled body refs after
             * fillMemory are shifted 4 slots: x=buildingType, y=width, playerID=averageHeight,
             * averageHeight=playerID_dup (playerColorUnk), buildingType=variationIndex,
             * unaff_EBX/ESI/retaddr=playerID/x/y.
             */
            int setupBuildingData(int playerID, uint x, uint y, undefined4 averageHeight, BuildingType buildingType,
                uint width, int playerID_dup, int variationIndex);

            /**
             * Deletes a building: leaves its status menu if selected, subtracts stored resources, idles siege
             * engines on it, re-registers an outpost's still-valid tribe with the AI, removes the ox-tether's ox
             * from its tribe, sets cathedralRelated1 for a cathedral, spawns crows, clears it from the terrain,
             * updates player references and zeroes the 0x32C-byte record.
             */
            void deleteBuilding(uint buildingID);

            /**
             * Immediate version of destroyBuilding: marks the building BLS_REMOVE (noRubble = 1 unless suppressed),
             * destroys signpost data, deletes it via deleteBuilding, then marks and deletes every live building
             * whose link field (logicalState+0x1D8) equals its non-zero uidWhenPlaced, and resets
             * showNoRubbleWhenDestroyingBuilding.
             */
            void destroyBuildingAndLinkedDuplicates(uint targetBuildingID);

            /**
             * Validates a building's entry tile (buildingEntryX/Y): invalid if (0,0), blocked by LogicLayer &
             * 0x50501481, height (+ building on it) differing from the base tile height by more than 16, or (unless
             * ABuildingTypeValueArray[type]) its path area differs from the owner's campground area and is not
             * navigable from it. Sets hasAccessToKeep = 1 and returns 1 if valid; else recomputes via
             * setBuildingInitialEntryTileTry + determineBuildingEntranceFromCampgroundArea(id, amountUnk, FALSE): 0
             * -> hasAccessToKeep = 0, return 0; 1 -> 1; 2 (fallback tile with a path area not reachable from the
             * campground area, e.g. behind a closed gate) -> 2.
             */
            int buildingIsAccessible(int buildingID, int amountUnk);

            /**
             * Like buildingIsAccessible, but the reference area is the path area of tile (x, y), there is no
             * ABuildingTypeValueArray exemption, and an invalid entrance (zero, blocked by LogicLayer mask
             * 0x50501481, height step > 16, or area unreachable for the owner) is recomputed with
             * determineBuildingEntranceFromCustomArea(id, matchIndex, 0, x, y). Sets hasAccessToKeep; returns 0
             * (none), 1 (valid/reachable) or 2 (fallback tile not reachable from the area).
             */
            int resolveBuildingEntryAccessibility(int buildingID, int matchIndex, int x, int y);

            /**
             * Refunds refundPercent (forced to 100 in Siege That) of a demolished structure's cost via
             * processResourceGain, playing the 'no space in stockpile' sound for each failed gain; nothing if
             * refundPercent is 0. -1: wall stone, -2: wood, each 2*percent/100 quarter units accumulated in
             * stoneGainedFraction/woodGainedFraction (Siege That -1: startResources[stone] += 1 instead). -3/-4:
             * wood/stone/iron/pitch/gold of buildingCosts[BT_TOWER1_RUIN_OR_MANGONEL]/[BT_TOWER2_RUIN_OR_BALLISTA] (tower engines). Otherwise the
             * building type's five costs; in Siege That only stone and gold, adjusted by
             * resourceGainForKillingPitAndPitchDitch, are added to startResources.
             */
            void giveBackResourceForDestroyedBuilding(int buildingIDORIfNegResourceType, int playerID, int refundPercent);

            /**
             * Finds a storage building owned by playerID for a producer to deliver resourceType to: stockpile goods
             * -> first a BLS_NORMAL stockpile already holding that good below its storage limit, else an empty one
             * (currentNumberOfResource <= 0); granary goods -> the first BLS_NORMAL granary with
             * computeResourceSumForBuilding < 250 that buildingIsAccessible. Returns buildingID or 0. The 2nd
             * argument (amount) is never read; the decompiled body is shifted (`amount` = playerID, unaff_retaddr =
             * resourceType).
             */
            int getBuildingThatCanStoreThisResource(ResourceType resourceType, int amount, int playerID);

            /**
             * Returns an armory able to take resourceToDeposit of the produced weapon: if targetBuildingID is
             * given, returns getArmoryIDIfSpaceLeft for it directly; otherwise the first building of type armory
             * that buildingIsAccessible and for which getArmoryIDIfSpaceLeft succeeds; 0 if none.
             */
            uint getArmoryWithSpaceLeft(
                uint targetBuildingID, undefined4 producedItemTypeUnk, int playerID, int resourceToDeposit);

            /**
             * Chooses a quarry stockpile (BLS_NORMAL, owned by playerID, resources[stone] > 0,
             * buildingIsAccessible(id,1)) for a quarry worker: score = 400 - distanceHigh from (x,y), plus a stone
             * bonus (stone/2 for 8..40, full stone above 40) when the unit's field300_0x410 is set. Returns the
             * best-scoring buildingID (later wins ties; scores below 0 never chosen) or 0.
             */
            int findQuarryPileThatIsCloseAndHasMostStone(int playerID, int x, int y, int unitID);

            /**
             * Per-tick gatehouse logic for DAT_CurrentBuildingID. Every 10 ticks (phase from fireRelatedRNG1) sums
             * troop values per player of selectable units on the footprint. Only enemies there: spawn ET_FLAG_1 if
             * no flag, the player with the highest value captures it (field241_0x2c6), flags recoloured, warning 19
             * if the local owner loses it, gate opened. A friendly unit there clears the capture. Not captured:
             * gateState2 counts down (0 if owner has no enemies); with gateCloseOpenTimer > 0 it counts down, < 0
             * disables auto mode; at 0, every 50 ticks an enemy within 200 micro units (Chebyshev) sets gateState2
             * = 1200 and closes the open gate, else gateState2 == 0 reopens a closed gate; drawbridges synced.
             * Capture by the owner itself resets field241_0x2c6.
             */
            void updateGateDrawBridgeOpenCloseLogic();

            /**
             * Rebuilds DAT_BuildingIDsNeedPeasantsQueue for a player: every BLS_NORMAL building of theirs with
             * currentlyNeededEmployeeCount > 0 (excluding mercenary post and barracks) gets buildingIsAccessible
             * refreshed and is appended if its entry tile's path area is navigable from the campground area.
             */
            void checkBuildingsNeedPeasants(int playerID);

            /**
             * Scenario event: sets fireCount random buildings of playerID on fire (only if the player has a
             * campground). Weight total over live, not burning, not cooling-down buildings: 1 per flammable
             * building (factor not 0/4), 5 for factor 5. Each round picks rng % total, walks the weights and lights
             * the hit building (lightUpBuilding(id,0,0)) and marks it on the minimap. BUG: the weight is then
             * reduced using getBuildingFlammabilityFactor(2000) instead of the lit building, so a factor-5 pick
             * usually reduces the total by 1 only and later rounds can miss (round consumed without a fire).
             */
            void spreadFireRandomlyToBuildings(int playerID, int fireCount);

            /**
             * Main per-tick building update: every 10 ticks recomputes maxBuildingsCount; resets killing-pit and
             * dog-cage counters; per building: INITIAL -> NORMAL, REMOVE -> deleteBuilding, otherwise counts
             * killing pits, advances animation, recruitTimer (0..99), timeAlive, AI-only idleTimerUnk countdown,
             * needed employees, field127_0x194, adds population cap, calls the per-type update function, refreshes
             * graphics, handles fire (every 20 ticks 4 damage for hovel/woodcutter/hunter/farms, else 1; parade
             * grounds/campground lose 1 HP and self-extinguish below 490), removes AI fire-ballista/catapult siege
             * buildings with unknownSiegeTentRelated01 == 2, no attackWave and timeAlive > 2400, decrements
             * cooldown, clears workers[]. Finally unknownCountdown01 = 2000 - structCount.
             */
            void updateBuildings();

            /**
             * Calls buildingIsAccessible for every live (not BLS_REMOVE) building to refresh entrances and
             * hasAccessToKeep.
             */
            void recomputeAccessibilityForAllBuildings();

            /**
             * For each live building of playerID whose type is not exempt (ABuildingTypeValueArray), checks
             * buildingIsAccessible; results 0 (no entrance) and 2 (entrance not reachable from the campground area)
             * mark it BLS_REMOVE and reset the AI heat-map countdown at its x/y. NAME? effectively removes the AI's
             * inaccessible buildings.
             */
            void updateHeatmapBasedOnBuildingAccessibility(int playerID);

            /**
             * Map-load hook: ignores both version arguments and calls recomputeAccessibilityForAllBuildings.
             */
            void applyVersionUpgradeAccessibilityRecompute(
                PackagedFileMagicNum receivedMapVersion, PackagedFileMagicNum packagerMapVersion);
        };

        static_assert_cpp98_obj(sizeof(BuildingsState) == 1630344, BuildingsState);

#pragma pack(pop)

    } // namespace Buildings
} // namespace Map
} // namespace OpenSHC
