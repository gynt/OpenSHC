/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/GameStateStructures.hpp'
*/

#pragma once

#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/Player/PlayerData.hpp"
#include "OpenSHC/Game/Player/PlayerDataBuildingCategoryEnum.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Game/State/MapAndTimeState.hpp"
#include "OpenSHC/Game/State/UnitSelectionHotKeyEntry.hpp"
#include "OpenSHC/IO/PackagedFileMagicNum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::Game::Player::PlayerData;
    using OpenSHC::Game::Player::PlayerDataBuildingCategoryEnum;
    using OpenSHC::Game::Resources::ResourceType;
    using OpenSHC::Game::State::MapAndTimeState;
    using OpenSHC::Game::State::UnitSelectionHotKeyEntry;
    using OpenSHC::IO::PackagedFileMagicNum;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x00093BF4
    class GameStateStructures {
    public:
        UnitSelectionHotKeyEntry hotkeyTribes[10]; // 0x00000000 length: 200000
        PlayerData playerDataArray[9]; // 0x00030D40 length: 133524
        MapAndTimeState mapAndTime; // 0x000516D4 length: 262608
        // number that goes up to 200 that determines what game information has to recomputed
        int gameTicksLoadBalancer; // 0x000918A4 length: 4
        short first500BuildingsPerPlayer[9][500]; // 0x000918A8 length: 9000
        int first500BuildingsCurrentIndexCounter[9]; // 0x00093BD0 length: 36

    private:
        GameStateStructures(GameStateStructures const&);
        void operator=(GameStateStructures const&);

    public:
        GameStateStructures() {};
        ~GameStateStructures() {};

        /**
         * Returns TRUE if the two players are on the same team (mapAndTime.playerTeams).
         */
        BOOLEnum isSameTeam(int playerID1, int playerID2);

        /**
         * Zeroes all 9 player data records (0x39F4 bytes each starting at 0x115BDF8) and the 0x401D0-byte block at
         * 0x117C78C.
         */
        void clearMapAndTimeAndPlayerData();

        /**
         * Clears the 25 currentResources entries of players 1..8 and resets skirmish strong walls and alliances
         * flags.
         */
        void clearCurrentResourcesAndStrongWalls();

        /**
         * Per-player (1..8) game start reset: clears counters/statistics, sets popularity fields from
         * startingPopularity*10, taxes 3 and the rations fields from the current player's rationsSetting, copies
         * the 25 start goods into resources, applies scenario taxes/rations/gold overrides, and outside solitary
         * mode sets resource 15 (gold) = skirmishStartGoldTable[(advantageBalance + intensity*5)*2 + 0xC (human) /
         * 0xD (AI)] * multiplier (x3 on the extreme trail; empty slots skipped); then initializes AI attack
         * strength/raid parameters.
         */
        void resetVariousCountsAndStatisticsAndStartGoodsAndResources();

        /**
         * Per-tick reset for players 1..8: decrements several countdowns, snapshots some previous-tick values,
         * zeroes many per-tick counters and statistics (including a 50-entry short-pair array), and resets a few
         * defaults; also clears global deer and other map counters.
         */
        void resetCountsAndStatistics();

        /**
         * Returns TRUE if the player slot has no human player assigned (currentPlayerFullIDArray[playerID] == -1),
         * i.e. AI or empty.
         */
        BOOLEnum isPlayerSlotNotHuman(int playerID);

        /**
         * Records a unit death for player 1..8: increments troopsLost (siege engines count their manning engineers,
         * valued as troop type 0x1E each) and adds the troop value to weightedLosses; if the loss has value,
         * reports it via UpdateUnitLossData when the owner is the current player and via
         * addUnitValueKilledByCurrentPlayer when the unit's last enemy is the current player. Stores the last enemy
         * player (and sets a per-enemy flag byte for enemies 2..5); outside solitary mode also updates the final
         * kill matrix [enemy][player], the enemy's weighted kills (only vs other teams, quartered when unit
         * field323_0x442 is set) and a per-enemy death counter in the player's data; sets GameCore.countdown = 1 if
         * the unit was selected. (unaff_retaddr in the decompile is playerID, see review SIGNATURE note.)
         */
        void processUnitLossStatistic(int playerID, int unitID);

        /**
         * Outside solitary mode, for player 1..8 whose (worker) unit has a positive lastEncounteredEnemyUnitIDUnk:
         * increments unknownCounter_01, stores the unit's x/y, records the attacking unit id/uid as
         * lastEncounteredTroopUnit if that unit is selectable and on another team (else clears it), and increments
         * a per-enemy encounter counter in the player's data (indexed by the unit's last enemy player). The
         * returned value is a leftover (playerID-1 or the counter address), not meaningful.
         */
        uint setLastEncounteredTroopUnit(int playerID, int unitID);

        /**
         * Advances game time each tick: increments day/week/month tick counters, clears the change flags, sets
         * startOfDay (and resets dayTicks) every 50 ticks; unless time is halted or display element 0x14 is active,
         * at the start of a week advances week (4 per month), month (12 per year) and year, setting the
         * corresponding changed flags.
         */
        void updateDateAndTime(BOOLEnum startOfWeekAsCurrentTickIs0, int currentTick);

        /**
         * Sets the game date to the given month/year with week 0, clears change flags and sets day/week/month tick
         * counters to 100.
         */
        void setMonthAndYear(int month, int year);

        /**
         * Zeroes the signpost-related blocks in mapAndTime (0x40 bytes at 0x117F0A4, 0x100 at 0x117F0E4, 0x1900 at
         * 0x117F1E4, 0xA00 at 0x1180AE4).
         */
        void clearSignpostData();

        /**
         * Single-player only: for each of the 8 signpost entry points with nonzero coordinates runs a pathfinding
         * spawn-location search and stores the destination options for that signpost ID.
         */
        void computeSignPostEntryData();

        /**
         * Single-player only: runs a spawn-location search from the first AI attack point (nof_fpointsArray[0]),
         * then walks the pathfinder search queue and for each tile not yet marked 100 in CertainPathLayer flood-
         * fills it and appends its x/y to mapAndTime.regionSeedPoints until the array is full.
         */
        void collectReachableLocationsFromFirstNofFPoint();

        /**
         * Computes a path from the player's campground entry (keep and wall gates disallowed, budget 8000) and
         * derives attack vectors for that player from it.
         */
        void calculateAttackVectorsToCampFireOfPlayer(int playerID);

        /**
         * Returns how many of the 8 mapAndTime signpost IDs refer to existing signpost buildings.
         */
        int countActiveSignposts();

        /**
         * Returns TRUE if any of the 8 mapAndTime signpost IDs refers to an existing signpost building.
         */
        BOOLEnum hasAnySignpost();

        /**
         * Picks a signpost index for an attack/event: counts valid signposts and those whose entry tile lies in a
         * path zone larger than 10000 tiles; if more than one is valid returns a random one (RNG currentNumber1,
         * not advanced) among the first N slots if all are reachable, else the slot of a random reachable one;
         * returns 0 otherwise.
         */
        int pickRandomAccessibleSignpostEntry();

        /**
         * After map load: clears signpost path data blocks, drops signpost IDs that no longer refer to signpost
         * buildings, compacts the 8-entry ID list (bubbling non-zero IDs forward), then recomputes each signpost's
         * entrance x/y/tile and the map-border edge tile stored in the signpost data.
         */
        void clearDataAndSignpostDataIfNecessary();

        /**
         * Registers a newly built signpost: stores buildingID in the first free signpost slot (empty or no longer a
         * signpost); if all 8 are used deletes the slot-7 signpost and replaces it. Then computes its entrance
         * x/y/tile and the map-border edge tile for that slot.
         */
        void addSignpostToBuildingEntryData(int buildingID);

        /**
         * Registers a key building in the player's building category table. Keep: destroys a different older keep
         * (and in the landscaping editor the stockpile) and derives the entry from x/y by orientation;
         * marketplace/guilds/barracks/mercenary post: destroys the currently referenced building, entry =
         * buildingEntryX/Y; stockpile/armory/granary: returns if one is already registered; oil smelter: entry =
         * buildingEntryX/Y; campground: entry from x/y by orientation; other categories use entry (0,0) without
         * range check. If the entry is inside 400x400 and the tile byte at 0x21AEC98 is set, stores id, entry
         * x/y/tile and path area. showNoRubbleWhenDestroyingBuilding is set to 1 on entry and cleared only after a
         * successful registration.
         */
        void computeBuildingCategoryEntryPointAndDestroyEarlierBuilding(
            uint buildingID, int playerID, PlayerDataBuildingCategoryEnum category);

        /**
         * Validates the player's building reference for a category: clears it if the id is out of range 1..1999,
         * the building type does not match the category (keep types, stockpile, granary, armory, barracks, merc
         * post, oil smelter, marketplace, guilds), or the building is inactive, has uid 0 or is not on the
         * BuildingLayer at its tile.
         */
        void validateBuildingCategoryReference(int playerID, int category);

        /**
         * Returns TRUE if the player's keep is enclosed: the player needs a campground whose entry path zone has
         * more than 299 tiles, at most 3/4 of the total and is below a map-size threshold (8000/10000/20000/25000),
         * and no other-team player slot that is in use (human or AI) with a campground and without the skip flag
         * shares that path zone.
         */
        BOOLEnum checkKeepEnclosed(int playerID);

        /**
         * Returns TRUE if both players have a keep and units of playerID1 can travel between the two campground
         * entry path zones (same zone, or reachable via calculateCanPlayerUnitsNavigateToAreaFromArea mode 0);
         * FALSE if either zone is 0. Returns TRUE if either keep is missing.
         */
        BOOLEnum canNavigateFromKeepToKeep(int playerID1, int playerID2);

        /**
         * Same as canNavigateFromKeepToKeep but checks reachability with navigation mode 2.
         */
        BOOLEnum canUnitsNavigateFromKeepToKeep(int playerID, int targetPlayerID);

        /**
         * Returns TRUE if the player's units can travel from its campground entry zone to the zone of signpost
         * entry 0 (same zone or reachable via mode 0); FALSE if either zone is 0. NAME? better
         * canReachFirstSignpostFromKeep.
         */
        BOOLEnum unitsCanMoveFromKeepOfPlayerToAnotherArea(int playerID);

        /**
         * Returns TRUE if the signpost chosen for attack wave attackWaveIndex
         * (attackInfo.attackWaveSignpostIndex[wave]) lies in the same path zone as playerID's campground entry,
         * or the attacking player's units can navigate between them (mode 0); FALSE if either zone is 0.
         */
        BOOLEnum canKeepReachSignpostZone(int playerID, int attackerPlayerID, int attackWaveIndex);

        /**
         * Like canKeepReachSignpostZone but always runs the navigation check (mode 2) for the attacking player
         * between playerID's campground zone and the attack wave's signpost zone, even if equal; FALSE if either
         * zone is 0.
         */
        BOOLEnum canKeepReachSignpostZoneViaPathfinder(int playerID, int attackerPlayerID, int attackWaveIndex);

        /**
         * When a building is removed: clears the owner's building-category reference that points to it (20
         * categories), and for stockpile/granary/armory/barracks/merc post re-points the reference to the first
         * remaining building of that type (recomputing barracks/merc post campground positions).
         */
        void updatePrimaryBuildingPlayerDataReferences(uint buildingID);

        /**
         * Transfers everything of fromPlayer to toPlayer: non-court units, player data values, tribes, walls, moat
         * and entities.
         */
        void changePlayerOwnership(int fromPlayer, int toPlayer);

        /**
         * Swaps ownership of everything between two players: units (court members removed), castle buildings,
         * tribes, walls, moat, pitch and entities.
         */
        void swapOwnership(int playerID_1, int playerID_2);

        /**
         * Eliminates a player: kills all its units, destroys its buildings, walls and entities.
         */
        void destroyPlayerCompletely(int playerID);

        /**
         * Returns 1 if playerID can afford the building for commandBuildingType, else 0. Always 1 when all
         * buildings are free, in the editor, for keep command types 0x3C..0x3E in solitary mode, or when
         * hasLessWoodThanTheCostOfAWoodcuttersHutAndNoWoodcutters applies. Checks iron, pitch (building type 0x44
         * passes if pitchDitchCounterTo4 is set), gold, then wood/stone; on a shortage plays the matching missing-
         * resource SFX if playResourceLackMsgUnk is set, and only for AI player slots outside solitary mode raises
         * the per-resource resourcesToAcquireArray amount (iron, pitch, wood, stone; not gold). The local
         * requiredIron is reused to hold the current wood stock.
         */
        undefined4 checkRequiredResourcesForBuildingOrPlanToBuy(
            MappersEnum commandBuildingType, int playerID, BOOLEnum playResourceLackMsgUnk);

        /**
         * Returns how many wall tiles of the given material (2 = wood, 4 = stone) the player can afford: 2 tiles
         * per resource unit, minus 1 if a partial wood/stone counter is set, capped at 250. Returns 100 when all
         * buildings are free or in the editor, the player's start stone (startResources[4]) in Siege-That mode, and
         * 0 for any other material.
         */
        int getWallTilesThatCanBeBuilt(int playerID, int wallMaterial);

        /**
         * Popularity popup, run once per 200-tick load-balancer cycle outside pure single-player: for players 1-8
         * that are alive (lordKilledByPlayerID and playerDeathRelated 0) and human or AI, when popularity/100
         * differs from the last shown value (popularityAtWeekTick100) a counter (counterTrackingPopGoldPopup) is
         * bumped; on the 2nd such tick the new value is stored, the counter reset and a popup shown over the
         * player's CAMPGROUND (not the keep). NAME? handles popularity only.
         */
        void showPopAndGoldPopup();

        /**
         * Gold popup, run once per 200-tick load-balancer cycle outside pure single-player: for alive human/AI
         * players 1-8, when gold (currentResources[15]) differs from currentGoldDelayed a counter
         * (PlayerData+0x450) is bumped; on the 2nd such tick currentGoldDelayed is updated, the counter reset and a
         * popup shown over the player's keep.
         */
        void createStatsPopUpEntities();

        /**
         * Shows the trade popup (amount and resource icon) over a player's marketplace after an AI buy/sell, unless
         * in pure single-player or the player is dead/killed. sellGoods passes isSale=1 and a negative amount,
         * buyGoods passes isSale=0.
         */
        void displayPlayerTradeVisualEffect(int playerID, int isSale, int amount, undefined4 resourceType);

        /**
         * For each player 1-8 with keep and campground (not editor/Siege-That): target chicken count = 0/1/2/3 for
         * totalFood <1/<10/<20/<30, otherwise totalFood/(2*currentPopulation)+3 capped at 10 (100 if debug flag
         * unknownAlwaysZero02). If chickenCount2 is below the target, spawns one chicken at the entrance of a
         * random accessible bakery/mill/granary and plays FX_CHICKEN_START; if above, sets the first matching
         * chicken of the player to US_DISAPPEAR.
         */
        void spawnChicken();

        /**
         * For each player 1-8 with keep and campground (not editor/Siege-That) spawns family units at
         * houses/hovels. Gate: in single-player skirmish a hysteresis on totalEnemyTroopValue (start below 41, stop
         * at 101, flag someCount46); in every other mode only while sumOfTotalEnemyUnitsCount < 1. Budget = 75 -
         * someCount02 - someCount03. Per own, non-burning hovel/house: without unitRef it gets a UT_MOTHER (stored
         * in unitRefID/UID); otherwise, if popularity >= 50 and the house's byte timer runs out and its child count
         * is below the byte limit at +0x2a5, a UT_CHILD is spawned and registered as worker.
         */
        void spawnMotherOrChild();

        /**
         * Returns TRUE if the player's campground building ID is valid, owned by that player and of type
         * BT_CAMPGROUND.
         */
        BOOLEnum playerHasACampground(int playerID);

        /**
         * Assigns a peasant to its owner's campfire: sets workplace to the campground, computes a sitting spot for
         * slot (availablePeasants-1) and stores it as target position/orientation. Returns -1 if no valid
         * campground, 0 if the unit is already at the spot, 1 if it must walk there.
         */
        int moveUnitAroundCampfire(int unitID, int availablePeasants);

        /**
         * Sets the trader state to 2 (trader active) and resets the trader counter.
         */
        void activateTraderState();

        /**
         * Resets the trader state and trader counter to 0.
         */
        void resetTraderState();

        /**
         * Returns the first player ID after the given one (up to 8) that owns a marketplace, or 0 if none.
         */
        int findNextPlayerWithMarketplace(int playerID);

        /**
         * Returns whether the resource type is enabled for trading on this map; pitch is mapped to the partial-
         * pitch slot first.
         */
        BOOLEnum isResourceTypeTradeable(ResourceType resourceType);

        /**
         * Counts the tradeable resources in the -1-terminated market resource cycle list and returns TRUE only if
         * at least two are tradeable.
         */
        BOOLEnum anyGoodsAreAllowedForSale();

        /**
         * Finds the given resource in the market cycle list (pitch mapped to partial pitch) and returns the next
         * tradeable resource after it, wrapping around at the -1 terminator.
         */
        int getNextGoodFilteringUnallowed(ResourceType currentResource);

        /**
         * Finds the given resource in the market cycle list (pitch mapped to partial pitch) and returns the
         * previous tradeable resource, wrapping from index 0 to 19.
         */
        int getPreviousGoodsFilteringUnallowed(ResourceType currentResource);

        /**
         * Returns the stored buy price of a resource, which is the price of a 5-unit batch. playerID is unused.
         */
        int getBatchBuyPrice(undefined4 playerID, int resourceType);

        /**
         * Returns the buy cost of 'amount' units of a resource: (batch buy price / 5) * amount. playerID is unused.
         */
        int getBuyPrice(undefined4 playerID, int resourceType, int amount);

        /**
         * Returns the buy price of one unit of a resource (batch buy price / 5).
         */
        int getBuyPriceForOneUnit(int resourceType);

        /**
         * Returns the sale price of one unit of a resource (batch sales price / 5).
         */
        int getSalePriceOfGood(ResourceType resourceType);

        /**
         * Returns the gold received for selling 'amount' units of a resource: (batch sales price / 5) * amount.
         * playerID is unused.
         */
        int getSellPrice(int playerID, int resourceType, int amount);

        /**
         * Returns how many units one sell click sells, based on the player's stock of the resource: the whole stock
         * if < 5, 5 if < 50, 10 if < 100, 20 if < 200, else 50. Machine code reads the player data through ECX
         * (this, ret 8), so it is effectively __thiscall even though the decompiler shows no this pointer.
         */
        int getSellResourceAmount(int playerID, int resourceType);

        /**
         * Resets several map/time globals to their initial values: tick counter, tree spread counter (interval 5),
         * game-over flag, keep-and-granary flag, event countdowns and the signpost distance (30).
         */
        void setVariousGameStateToInitialValues();

        /**
         * For each player 1-8 with keep and campground (not Siege-That): updates the lord/lady/jester/ghost units;
         * then, outside the editor, if countEconomyBuilding_fixme > 0 and availablePeasantsAtFire > 0, collects
         * buildings that need workers and, if any, sorts that queue and assigns peasants.
         */
        void processPeasantsForBuildings();

        /**
         * For every player with keep and campground, sets foodTypesInStock to how many of the four food stocks
         * (bread, cheese, meat, apples) are positive.
         */
        void updateFoodTypesInStockForAllPlayers();

        /**
         * Per-tick food consumption for players with keep and campground (not editor/Siege-That/siege builder
         * maps). Rate (foodClockSpeed) = currentPopulation*3, or currentPopulation*1.8 for AI players outside pure
         * single-player, scaled by rationsSetting (0 none, 1 half, 3 x1.5, 4 x2); foodStorageLevel = estimated time
         * left. Skips the player if no food type is in stock. On month change shifts the estimate into
         * foodStorageLevelLastMonth/LastLastMonth and, for the local player, plays food_warning4 (no food, every
         * 3rd month) or, when rations are on and the new estimate is below 2 and differs from last month's,
         * food_warning2/3. When foodClock passes 15000 it removes one unit of the next stocked food (cycling bread,
         * cheese, meat, apples).
         */
        void processFoodConsumption();

        /**
         * Sets aleRate to 36 for every player 1-8 who has a keep and a campground (unrolled loop).
         */
        void updateAleRate();

        /**
         * Returns ale coverage in percent: workingInns*3000/population, clamped to 0..100; 0 if no working inns or
         * no population.
         */
        int computeAleCoverage(int playerID);

        /**
         * For all 8 players computes the overcrowding percentage: 0 if population <= housing capacity, 150 if there
         * is no housing, else population*100/capacity.
         */
        void updateCrowding();

        /**
         * For all 8 players maps the fear factor level (-5..+5) to a productivity percentage: -5 = 150, -4 = 140,
         * ... -1 = 110, 0 = 100, 1 = 90 ... 4 = 60, 5 = 50.
         */
        void updateFearFactorProductivity();

        /**
         * Recounts religious buildings: clears per-player chapel/church/cathedral counters, then increments the
         * owner's counter for every live chapel, church and cathedral.
         */
        void recomputeReligionBonuses();

        /**
         * Tax income (x10) = (taxStep-1)*peasants/2. In skirmish/multiplayer it is scaled by the advantage setting:
         * 150% for humans at balance 1 or AIs at balance 4, 120% for humans at balance 2, 250% for AIs at balance
         * 5.
         */
        int calculateTaxIncomeForPlayer(int playerIndex, int taxStep, int currentPeasants);

        /**
         * Bribe expense (x10) at low tax steps = (5-taxStep)*population/2, or 0 if the player has no gold.
         */
        int calculateTaxBribeExpenseForPlayer(int playerIndex, int taxStep, int currentPopulation);

        /**
         * Returns the tax income shown in the keep menu: calculateTaxIncomeForPlayer*4/10 for taxStep > 3, else 0.
         */
        int getNumberToDisplayPlayerTaxIncome(int playerIndex, int taxStep, int currentPopulation);

        /**
         * Returns the bribe amount shown in the keep menu: calculateTaxBribeExpenseForPlayer*4/10 for taxStep < 3,
         * else 0.
         */
        int getNumberToDisplayBribeIncome(int playerIndex, int taxStep, int currentPopulation);

        /**
         * Removes one unit of a player to shrink the population: first the lowest-index ULS_NORMAL, non-dying
         * UT_PEASANT of the player (no idle check); otherwise, among ULS_NORMAL non-dying units with field64_0x90
         * == 0, isSelectable_OR_matchTime == 0 and isStalked == 0, the one whose unit type has the highest despawn
         * priority in a hard-coded table. The chosen unit gets its hidden flag cleared, stops walking, gets
         * US_DISAPPEAR and buildingID/updateTickTracker 0.
         */
        void despawnPeasantOrWorker(int playerID);

        /**
         * Spawns 1-4 drunkards (random, capped by a player counter: <20 -> 1, <50 -> 2, <100 -> 3, else 4) at the
         * inn's entrance if the entry tile is valid, and records the inn ID in the player data. Drunkards start
         * idle with a random substate and need a destination.
         */
        void spawnDrunkard(int innBuildingID);

        /**
         * Keep/granary gate for the local player: returns 0 if no keep, -1 if keep but no granary, else 1 and
         * caches TRUE in singlePlayerHasKeepAndGranary. Returns 1 without checking in editor, Siege-That, outside
         * pure single-player, when the flag is already set, or in builder/Crusader-tutorial mode when the local
         * slot is 2.
         */
        int singlePlayerHasKeepAndGranaryCheck();

        /**
         * Resets player teams so each player is its own team (0-8). Outside skirmish/multiplayer and editor,
         * players 2-5 are put together on team 9.
         */
        void resetTeams();

        /**
         * Returns TRUE if both player IDs are non-zero and on different teams.
         */
        BOOLEnum getTeamsDifferent(int firstPlayerId, int secondPlayerId);

        /**
         * Returns the lowest player ID (0-8) other than playerID1 that is an AI and on the same team as playerID1,
         * or 0 if there is none.
         */
        int findAITeamMate(int playerID1);

        /**
         * Builds an 8-bit mask of players 1-8 (bit p-1 = player p) that are NOT on the team of the unit's owner,
         * starting from 0xFF and clearing the bits of same-team players (including the owner). Returns 0xFF for an
         * unowned unit. Used for melee initiation. NAME? something like getEnemyPlayerMaskForUnit.
         */
        uint getEnemyPlayerMaskForUnit(int unitID);

        /**
         * Checks the active players 1-8 (human or AI, lord not killed): the first one's team becomes the reference
         * and is counted, every later active player on a different team is counted too. Returns TRUE if the count
         * is < 2, i.e. all active players share the first one's team (or none is active). NAME? 'Mostly' is
         * misleading; it means all on the same team.
         */
        BOOLEnum areActivePlayersMostlySameTeam();

        /**
         * Recomputes availableHorses for all players: zeroes them, then adds (horses in stable - horses in use) for
         * every live stables building to its owner.
         */
        void recountStablesAndHorses();

        /**
         * Takes a horse for a recruited knight: finds the player's first live stables whose horses in use
         * (Building+0x2a7) are below numberOfAnimals, decrements availableHorses, validates tethered units and
         * stores the unit ID/UID in the first free insideUnitID1-4/insideUnitUID1-4 slot (the decompiler shows this
         * as quarryLinkedOxTethers[i+0xb]) and increments the horses-in-use byte. Returns that stable's building ID
         * (also when no slot was free, then nothing is stored), or 0 if no stable has a free horse. NAME? e.g.
         * takeHorseFromStableForUnit.
         */
        int takeHorseFromStableForUnit(int playerID, int unitID);

        /**
         * Tries up to 20 random tiles within +-15 of the building for a valid tile whose logic flags are free, then
         * spawns 6-10 ET_DISEASE_CLOUD entities there, plays the flies sound and flags the spot on the minimap.
         */
        void spawnPoisonCloudsAroundBuilding(int buildingID);

        /**
         * For the local player plays 'space_warning5.wav' (no space in the stockpile) and stores the time in
         * lastTimeSFXNoPlaceInStockpile. Original-code bug (verified in machine code): the 10 s cooldown subtracts
         * a second timeGetTime() call from the first instead of using the stored time, which is only tested for 0.
         * After the first play the sound repeats only when the millisecond clock ticks between the two calls (the
         * unsigned difference then wraps), i.e. sporadically.
         */
        void playSFXNoSpaceInTheStockPile(int playerID);

        /**
         * Clears one hotkey group: sets all 2500 unit ID/UID pairs to -1.
         */
        void clearTribeHotKey(int hotkeyID);

        /**
         * Clears all 10 hotkey groups by setting every unit ID/UID pair (10 x 2500) to -1.
         */
        void fillWith0xFF();

        /**
         * Writes the living (ULS_NORMAL, not dying) non-lord units of a tribe into hotkey group 'number' from slot
         * 0. For each unit it searches the other 9 groups and removes it there, shifting later entries down and
         * writing -1 at the end. It does not clear or -1-terminate the target group itself.
         */
        void assignSelectionToKey(int number, int tribeID);

        /**
         * Sets the per-player army size limit: 10000 in pure single-player or when nobody is active, otherwise
         * 2400/activePlayers - 40, counting human or AI players whose lord is not killed.
         */
        void computeArmySizeLimit();

        /**
         * Runs a tactical power if the player's power bar holds (powerType+1)*636: 0 = damage area (radius 6,
         * 6000), 1 = heal own units (radius 6), 2/3/4/6/13/16 = spawn an aggressive group (spear 20, engineer 14,
         * mace 20, knight 10, archer 15, firethrower 12) at the tile, 5 = gold donation of 1000-2499, 7 = big
         * damage area (radius 9, 18000). The cost is always subtracted; a sound plays for the local player only for
         * powers 1, 7 and the unit groups. Other types do nothing.
         */
        void handleActivateTacticalPowers(int playerID, int powerType, int tileIndex);

        /**
         * Debug overlay: renders many counters for the local player and engine (player data words, organisms, CRC,
         * units, popularity, crowding, pathfinding stats, enemy hits, entity/building/unit limits) as text at (x,
         * y).
         */
        void renderDebugDataCurrentPlayerData(int x, int y, int width, int height);

        /**
         * Outside pure single-player, adds a building that is not burning to its owner's list of up to 500
         * buildings (used to choose random attack targets) and increments the counter.
         */
        void addBuildingInRegistry(int buildingID);

        /**
         * Resets the per-player building registry counters (players 0-8) to 0 so the list is rebuilt each tick.
         */
        void resetBuildingsCurrentIndexCounter();

        /**
         * Returns a random building ID from the player's building registry using the sync RNG, or 0 if the registry
         * is empty.
         */
        int selectARandomBuildingOwnedByPlayer(int playerID);

        /**
         * Calls validateBuildingCategoryReference for every player 1-8 and category 0-19. NAME?
         * validateAllBuildingCategoryReferences.
         */
        void resetSomethingBuildingRelatedForAllPlayers();

        /**
         * Per player 1-8: currentPopulation = countEntities - nonInteractiveCitizenCountUnk - (PlayerData+0x2174) -
         * armySize, minus 1 for each live lord/lady/jester; populationRelatedCrowdingCountUnk = currentPopulation_2
         * - availablePeasantsOrHousedPeasants; blessedPeoplePercentage = blessed*100/(blessed+unblessed). At day
         * start stores availablePeasants in the 8-entry populationGrowth ring buffer and its average in
         * averagePopulationGrowthUnk; on month change appends currentPopulation to the 300-entry history (shifting
         * when full). Updates finalMaxPopulation, raises tacticalPowersBarLevel up to 7000 and moves up to 10 gold
         * per tick from goldDonation into gold (refreshing the UI for the local player).
         */
        void computePopulationStatistics();

        /**
         * Resets game state for a new map: sign posts, AI player data, counts/start goods, initial values, building
         * category references, building availability, time-halt flag, several map/time fields, the enemy hit array,
         * and for 9 players playerBuildingInfoIndex, playerEnemyBuildingIDs and playerEnemyBuildingUID (2000 each,
         * cleared together) and the enemy unit UID lists (2500); then clears all hotkey groups.
         */
        void clearEnemyRelatedStructures();

        /**
         * Post map-load setup: resets teams in single-player, resets building countdown and load balancer, sets up
         * sign post data, imports trading costs (not in skirmish/multiplayer), commits building availability and
         * recomputes crowding.
         */
        void initializeGameStateAfterMapLoad();

        /**
         * Gives every other player's (1-8) units and buildings to playerID, then recomputes the AI zoner layer.
         */
        void switchPlayerOwnership(int playerID);

        /**
         * Peasant immigration/emigration (skipped on siege builder maps). Per player whose lord is not killed (in
         * pure single-player also playerDeathRelated == 0): vclockIncrement comes from a popularity/500-indexed
         * table (single-player tables split at population 100, skirmish table otherwise); vclock += it, clamped
         * 0..4000, reset to 2000 if the increment is 0. With keep and campground: at 4000, if currentPopulation <
         * populationCap and availablePeasants < 24, vclock = 2000 and a peasant spawns at the campground; at <= 0
         * with availablePeasants + populationRelatedCrowdingCountUnk > 4, vclock = 2000 and despawnPeasantOrWorker
         * runs. Immigrate/emigrate speech plays for the local player when the direction flag (+0x42) flips.
         */
        void processPeasantSpawnAndDespawnCycle();

        /**
         * Pure single-player trader state machine, called once per week: the counter counts weeks. State 1 keeps
         * the counter at 0. State 2: once aiTroops < 2 and counter >= traderRelated1, goes to state 1 and clears
         * traderVisitsPlayer. State 0: once aiTroops < 2 and counter >= traderRelatedCounter2, if any player after
         * traderVisitsPlayer owns a marketplace and the local slot is non-zero, sets state 1 and spawns a trader
         * and a linked trader horse at the first map-edge sign post. Original-code bug (verified in machine code):
         * traderVisitsPlayer is set to the local player slot; the marketplace owner found is only tested for non-
         * zero and then discarded.
         */
        void updateTrader();

        /**
         * Returns the gold for one sell click: (batch sales price / 5) * getSellResourceAmount(playerID,
         * resourceType). Machine code copies ECX (this) to EDX before the call, which does not change EDX, and
         * reads the price table at EDX+0x51f20+type*8; the price is read from this object, shown by the decompiler
         * as DAT_GameState.
         */
        int getSalesPrice(int playerID, int resourceType);

        /**
         * Weekly popularity update for each player with keep and campground. Siege builder maps set popularity to
         * 10000 (0 if the local slot is 2). If population < 4 and popularity < 5000 it is reset to 7500. Otherwise
         * popularity (0..10000, x100) changes by food (rations -200..+200 plus +25/50/75 for variety; +200 with no
         * population), crowding (0..-250), tax/bribe (+175..-600), fair (+400), religion (blessed % plus
         * church/cathedral), ale coverage, fear factor*25 and timed event modifiers. Stores each delta and the code
         * of the worst factor, clamps 0..10000, and plays falling/rising speech for the local player when it moved
         * more than 500 (5 points) past the last announced value.
         */
        void updatePopularity();

        /**
         * Called on week change: adds the tax income (taxesSetting > 3) or bribe expense (taxesSetting < 3) to per-
         * player monthly accumulators. On month change both are divided by 10, tax is added to gold and finalGold,
         * bribes are subtracted from gold (clamped at 0), the values saved as last month's figures, the
         * accumulators cleared, lastMonthsGold shifted into beforeLastMonthsGold and replaced by gold, and
         * marketGold reset to 0.
         */
        void updateTaxing();

        /**
         * Spawns poison clouds near the player's campground, then 'count' times at a random live storage/military
         * building of the player (stockpile, granary, armory, barracks, mercenary post, engineers or tunnelers
         * guild).
         */
        void spawnPoisonCloudsAtRandomStorageOrArmyBuilding(int playerID, int count);

        /**
         * Upgrades game state loaded from an older map/save version: fixes the trail type, validates lady/jester
         * refs and recounts horses, then for each version threshold below the current one resets or converts fields
         * (building availability, lion spots, unit names, event tables, AI status, per-player cow/siege counters,
         * lady/jester removal, banned food, enemy unit/building lists, tick lengths, skirmish options, assembly
         * points).
         */
        void migrateGameStateForMapVersion(
            PackagedFileMagicNum receivedMapVersion, PackagedFileMagicNum packagerMapVersion);

        /**
         * One game tick of slow simulation: a 0-199 load balancer counter spreads work over ticks (troop value
         * recounts per player, enemy building updates, wildlife grid/attack layers, tree spread, moat timers,
         * chickens, mothers/children, peasant jobs, popups, horses). Also counts down the no-rush timer, checks
         * multiplayer sync (and queues a state-hash check every 200 map ticks), and in normal modes updates
         * date/time, weekly crowding/trader/tax/ale/fear factor, popularity and peasant spawning.
         */
        void processSingleTimeTick();

        /**
         * Main per-frame game update: handles multiplayer save/resync states, quit vote timeout, advances RNG and
         * map time and runs processSingleTimeTick when not halted, updates map orientation and tile layers, and
         * when not paused runs all subsystems (buildings, trees, events, AI, units, entities, food, population,
         * tribes, army limit).
         */
        void processGameTick();
    };

    static_assert_cpp98_obj(sizeof(GameStateStructures) == 605172, GameStateStructures);

#pragma pack(pop)

} // namespace Game
} // namespace OpenSHC
