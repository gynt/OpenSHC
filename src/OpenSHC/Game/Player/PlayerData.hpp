/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/Player/PlayerData.hpp'
*/

#pragma once

#include "OpenSHC/AI/AIRecruitUnitChoiceInt.hpp"
#include "OpenSHC/AI/AISiegeUnitCreation.hpp"
#include "OpenSHC/AI/AIStrengthTypeInt.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"
#include "OpenSHC/Coordinates/XYPairShort.hpp"
#include "OpenSHC/Game/Player/BuildingEntryInfo.hpp"
#include "OpenSHC/Game/Player/UnknownPlayerDataStructure.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Game {
    namespace Player {

        using OpenSHC::AI::AIRecruitUnitChoiceInt;
        using OpenSHC::AI::AISiegeUnitCreation;
        using OpenSHC::AI::AIStrengthTypeInt;
        using OpenSHC::AI::AITypeInt;
        using OpenSHC::Coordinates::XYPairShort;
        using OpenSHC::Game::Player::BuildingEntryInfo;
        using OpenSHC::Game::Player::UnknownPlayerDataStructure;
        using OpenSHC::Game::Resources::ResourceTypeInt;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)
        // SIZE: 0x000039F4
        typedef struct PlayerData {

            undefined1 padding_0x0[4]; // 0x00000000 length: 4
            int openOrCloseGateClick; // 0x00000004 length: 4
            undefined1 padding_0x8[8]; // 0x00000008 length: 8
            // 3 uses: copied from fletcher/blacksmith/poleturner producedItemType on menu open, set by action
            // handler, highlights selected weapon.
            ResourceTypeInt workshopMenuSelectedWeapon; // 0x00000010 length: 4
            int taxesSliderUI; // 0x00000014 length: 4
            // 0..4 none/half/normal/extra/double selects speech, icon and popularity; 3 suffix meaningless (review
            // 367)
            int rationsLevel; // 0x00000018 length: 4
            // [214 0x004652D0] used only by the drawbridge buttons (command 0x25); the gatehouse uses
            // openOrCloseGateClick
            int lastDrawbridgeChoice; // 0x0000001C length: 4
            int taxesSetting2; // 0x00000020 length: 4
            int rationsSetting2; // 0x00000024 length: 4
            ResourceTypeInt marketSelectedResourceType; // 0x00000028 length: 4
            int storageMarketFailState; // 0x0000002C length: 4
            int timeStorageMarketFailState; // 0x00000030 length: 4
            // [207 0x00433DA0] +2 per frame; x = value-40+posX of a scrolling animated GM_INTERFACE_ICONS2 sprite
            // (frame from value>>2) until it passes resolutionX; set to 2000 for siege-that
            int startGoodsBannerScrollX; // 0x00000034 length: 4
            // [207 0x00433DA0] 0 = banner off; 1/2 select TEXT_STARTUP title 0/2; cleared when the scroll animation
            // finishes; gates drawing of goods names
            int startGoodsBannerMode; // 0x00000038 length: 4
            // [207 0x00433DA0] set to 30 in siege-that, decremented to 0 while banner is off and added to every
            // goods row Y Created by retype action
            int startGoodsListOffsetY; // 0x0000003C length: 4
            // 1 after "popularity falling" speech was played, 0 after "rising"; hysteresis flag for popularity
            // trend speech (short)
            short popularityFallingAnnounced; // 0x00000040 length: 2
            // [043 0x0045B4A0] set to 1 with SEID_POP_EMIGRATE and back to 0 with SEID_POP_IMMIGRATE
            short lastMigrationWasEmigration; // 0x00000042 length: 2
            int timeTaxesOrRationsChange; // 0x00000044 length: 4
            short releaseDogsFlag; // 0x00000048 length: 2
            // [073 0x00402660] set to 0x46 when the type-40 popup entity expires; playerHasEntityOfType(0x28)
            // returns TRUE while it is nonzero
            undefined2 popupEntity40Cooldown; // 0x0000004A length: 2
            // [073 0x00402730] set to 0x46 when the type-41 popup entity expires; playerHasEntityOfType(0x29)
            // returns TRUE while it is nonzero
            undefined2 popupEntity41Cooldown; // 0x0000004C length: 2
            undefined1 padding_0x4e[2]; // 0x0000004E length: 2
            dword lastTimeSFXNoPlaceInStockpile; // 0x00000050 length: 4
            // Created by retype action
            int marketGold; // 0x00000054 length: 4
            undefined1 padding_0x58[8]; // 0x00000058 length: 8
            // expressed in 100's
            int popularity; // 0x00000060 length: 4
            undefined1 padding_0x64[4]; // 0x00000064 length: 4
            // [069 0x0040F620] accumulates each building's currentlyNeededEmployeeCount (missing workers) for the
            // owner confirm all buildings counted
            int totalNeededWorkers; // 0x00000068 length: 4
            // peasantSpawnClock
            int vclock; // 0x0000006C length: 4
            int vclockIncrement; // 0x00000070 length: 4
            int populationCap; // 0x00000074 length: 4
            int currentPopulation_2; // 0x00000078 length: 4
            undefined1 padding_0x7c[4]; // 0x0000007C length: 4
            // if population cap is 0: 150, else (population*100)/cap
            int crowding; // 0x00000080 length: 4
            // [170 0x00579300] incremented once per live (non-removed) unit of the owner in the final pass
            int liveUnitCount; // 0x00000084 length: 4
            int availablePeasantsAtFire; // 0x00000088 length: 4
            int availablePeasantsOrHousedPeasants; // 0x0000008C length: 4
            // [110 0x0053EAA0] incremented for peasants fading in, walking to the campfire (state 4) or playing the
            // arrival animation (state 5)
            int peasantsArrivingAtCampfire; // 0x00000090 length: 4
            BuildingEntryInfo keep; // 0x00000094 length: 40
            BuildingEntryInfo stockpile; // 0x000000BC length: 40
            BuildingEntryInfo granary; // 0x000000E4 length: 40
            BuildingEntryInfo armory; // 0x0000010C length: 40
            BuildingEntryInfo unknown4; // 0x00000134 length: 40
            BuildingEntryInfo barracks; // 0x0000015C length: 40
            BuildingEntryInfo unknown6; // 0x00000184 length: 40
            BuildingEntryInfo marketplace; // 0x000001AC length: 40
            BuildingEntryInfo campground; // 0x000001D4 length: 40
            BuildingEntryInfo engineersGuild; // 0x000001FC length: 40
            BuildingEntryInfo tunnelersGuild; // 0x00000224 length: 40
            BuildingEntryInfo mercenaryPost; // 0x0000024C length: 40
            BuildingEntryInfo oilSmelter; // 0x00000274 length: 40
            undefined1 padding_0x29c[280]; // 0x0000029C length: 280
            // [044 0x0045B830] copy of popularity (x100 scale, not percent) before the weekly change popularity as
            // percent * 100 to two decimals. increments of 25 possible
            int previousWeekPopularity; // 0x000003B4 length: 4
            int previousArmySize; // 0x000003B8 length: 4
            // most likely int. is likely used as accumulator - can oscillate 0 to x
            int currentSiegeWeaponCount; // 0x000003BC length: 4
            // most likely int. is stable total
            int previousSiegeWeaponsCount; // 0x000003C0 length: 4
            undefined1 padding_0x3c4[128]; // 0x000003C4 length: 128
            // [042 0x00457F20] stores popularity/100 whenever the popularity popup is shown here (not tied to a
            // week tick) range 0 - 100, delayed update potentially month end only
            int lastShownPopularityDiv100; // 0x00000444 length: 4
            int currentGoldDelayed; // 0x00000448 length: 4
            int counterTrackingPopGoldPopup; // 0x0000044C length: 4
            int field490_0x450; // 0x00000450 length: 4
            int hasInitialResourceRecievingStarted; // 0x00000454 length: 4
            undefined1 padding_0x458[4]; // 0x00000458 length: 4
            // [107 0x00514F30] indexes WheatFarmTiles and is incremented and wrapped to 0 above 1 after each wheat
            // farm placement
            int wheatFarmLayoutToggle; // 0x0000045C length: 4
            // toggled 0/1 after each hop farm, indexes hopFarmFieldTiles; named like sibling wheatFarmLayoutToggle
            // Created by retype action width from machine code (int)
            int hopFarmLayoutToggle; // 0x00000460 length: 4
            undefined1 padding_0x464[4]; // 0x00000464 length: 4
            int dairyFarmVariationMod4; // 0x00000468 length: 4
            // goods queued for the stockpile/granary (start goods, lord loot, refunds), moved gradually into
            // currentResources; HUD 'Available Goods'
            int pendingResources[25]; // 0x0000046C length: 100
            int currentResources[25]; // 0x000004D0 length: 100
            undefined1 padding_0x534[4]; // 0x00000534 length: 4
            // [056 0x00411480] barracks and outposts add 10 and mercenary posts add 5 per tick (weighted military-
            // building tally)
            int militaryBuildingScore; // 0x00000538 length: 4
            int armySize; // 0x0000053C length: 4
            undefined1 padding_0x540[24]; // 0x00000540 length: 24
            XYPairShort barracksParadegroundLocations[6][72]; // 0x00000558 length: 1728
            int barracksParadegroundLocationsTotal; // 0x00000C18 length: 4
            undefined1 padding_0xc1c[4]; // 0x00000C1C length: 4
            // Created by retype action
            XYPairShort engineersParadegroundLocations[25]; // 0x00000C20 length: 100
            int engineersParadegroundLocationsTotal; // 0x00000C84 length: 4
            undefined1 padding_0xc88[4]; // 0x00000C88 length: 4
            // Incremented by engineers and laddermen at assembly; engineer slot = this - laddermanAssemblyCount.
            undefined4 engineerGuildAssemblyCount; // 0x00000C8C length: 4
            XYPairShort tunnelersGuildParadegroundLocations[25]; // 0x00000C90 length: 100
            int tunnelersGuildParadegroundLocationsTotal; // 0x00000CF4 length: 4
            undefined1 padding_0xcf8[4]; // 0x00000CF8 length: 4
            // Incremented per tunneler in state 0x69 each tick; used as start index into tunneler assembly tiles.
            undefined4 tunnelerAssemblyCount; // 0x00000CFC length: 4
            // Created by retype action
            short enemyIDArray[2500]; // 0x00000D00 length: 5000
            // [162 0x00532BA0] number of entries written into enemyIDArray / playerEnemenyUnitUIDShortList, capped
            // at 2499
            int enemyListCount; // 0x00002088 length: 4
            int breadCount; // 0x0000208C length: 4
            int cheeseCount; // 0x00002090 length: 4
            int meatCount; // 0x00002094 length: 4
            int appleCount; // 0x00002098 length: 4
            // Created by retype action
            int totalFood; // 0x0000209C length: 4
            // Created by retype action
            int foodTypesInStock; // 0x000020A0 length: 4
            // Created by retype action
            int weeksWithoutFood; // 0x000020A4 length: 4
            // Created by retype action
            int foodTypesCurrentlyEaten; // 0x000020A8 length: 4
            int foodTypeToBeEatenNext; // 0x000020AC length: 4
            int foodClockSpeed; // 0x000020B0 length: 4
            int foodClock; // 0x000020B4 length: 4
            int currentArchers; // 0x000020B8 length: 4
            int currentCrossbowmen; // 0x000020BC length: 4
            int currentSpearmen; // 0x000020C0 length: 4
            int currentPikemen; // 0x000020C4 length: 4
            int currentMacemen; // 0x000020C8 length: 4
            int currentSwordsmen; // 0x000020CC length: 4
            int currentKnights; // 0x000020D0 length: 4
            int currentLaddermen; // 0x000020D4 length: 4
            int currentEngineers; // 0x000020D8 length: 4
            int currentTunnelers; // 0x000020DC length: 4
            int countArabianArcher; // 0x000020E0 length: 4
            int countSlaves2; // 0x000020E4 length: 4
            // [144 0x00572E80] Incremented unconditionally for every slinger each tick alongside armySize
            // (0x572EAD).
            int countSlingers; // 0x000020E8 length: 4
            // Created by retype action
            int countAssassins; // 0x000020EC length: 4
            // Created by retype action
            int countHorseArchers; // 0x000020F0 length: 4
            int countArabSwordsman; // 0x000020F4 length: 4
            // Created by retype action
            int countFirethrowers; // 0x000020F8 length: 4
            undefined1 padding_0x20fc[20]; // 0x000020FC length: 20
            // Created by retype action
            int popularityChangeAleBased; // 0x00002110 length: 4
            // Created by retype action
            int popularityChangeBasedOnReligion; // 0x00002114 length: 4
            // Created by retype action
            int popularityChangeFearFactorBased; // 0x00002118 length: 4
            // 50..150 percent from the fear factor level, printed after 'Efficiency %:' Created by retype action
            int fearFactorEfficiencyPercent; // 0x0000211C length: 4
            undefined1 padding_0x2120[4]; // 0x00002120 length: 4
            // Created by retype action
            int workingInnsCount; // 0x00002124 length: 4
            // Created by retype action
            int aleRate; // 0x00002128 length: 4
            int badStuffCount; // 0x0000212C length: 4
            int goodStuffCount; // 0x00002130 length: 4
            // positive values are +1 bonuses, negative values are caused by bad things
            int fearFactorLevel; // 0x00002134 length: 4
            int objectsLeftUntilNextLevel; // 0x00002138 length: 4
            undefined1 padding_0x213c[4]; // 0x0000213C length: 4
            int lastMonthsBribeTax; // 0x00002140 length: 4
            int taxBribeMonthlyAccumulator; // 0x00002144 length: 4
            int totalEnemyUnitsCount; // 0x00002148 length: 4
            int partialWoodCounter; // 0x0000214C length: 4
            // Created by retype action
            int partialStoneCounter; // 0x00002150 length: 4
            int lastMonthsIncomeTax; // 0x00002154 length: 4
            int taxIncomeMonthlyAccumulator; // 0x00002158 length: 4
            // Created by retype action
            int popularityChangeBasedOnTax; // 0x0000215C length: 4
            uint popularityChangeBasedOnFood; // 0x00002160 length: 4
            // Created by retype action
            int popularityChangeBasedOnCrowding; // 0x00002164 length: 4
            // zeroed each updatePopularity pass next to tax popularity; no reader seen
            int popularityFactor2168; // 0x00002168 length: 4
            // [044 0x0045B830] set to the code of the most negative factor (1 food, 2 crowding, 4 tax, 5 fair, 6
            // religion, 7 ale, 8 fear)
            uint worstPopularityFactor; // 0x0000216C length: 4
            int someCount43; // 0x00002170 length: 4
            // incremented on every UpdateDrunkard call for the drunkard's owner (census of active drunkards); no
            // reset/reader visible in the decompiled code
            int drunkardUpdateCount; // 0x00002174 length: 4
            // building id of the inn that last spawned a drunkard (spawnDrunkard)
            int lastDrunkardInnBuildingId; // 0x00002178 length: 4
            // [115 0x005464F0] incremented every tick by chicken/mother/child/juggler/fire-eater updates; zeroed
            // for players 1-8 each tick in resetCountsAndStatistics (0x4560F0)
            int nonInteractiveUnitCountThisTick; // 0x0000217C length: 4
            int currentPopulation; // 0x00002180 length: 4
            int populationRelatedCrowdingCountUnk; // 0x00002184 length: 4
            int taxesSetting; // 0x00002188 length: 4
            // range (0 = no rations to 4 = double rations)
            int rationsSetting; // 0x0000218C length: 4
            // How many months of food are in the supply
            int foodStorageLevel; // 0x00002190 length: 4
            bool snoozedBuildings[100]; // 0x00002194 length: 100
            int lordID; // 0x000021F8 length: 4
            int lordUID; // 0x000021FC length: 4
            // [069 0x0040FC40] receives the unit spawned as UT_LADY
            int ladyUnitID; // 0x00002200 length: 4
            // uid of units[ladyID] stored to validate the lady reference (3 batches agree)
            int ladyUnitUID; // 0x00002204 length: 4
            // [069 0x0040FC40] receives the unit spawned as UT_JESTER
            int jesterUnitID; // 0x00002208 length: 4
            // uid of units[jesterID] stored to validate the jester reference (3 batches agree)
            int jesterUnitUID; // 0x0000220C length: 4
            // [139 0x0056C560] SP: 10, or the killer id when the killer is nonzero and not the local player. MP
            // body removal: always 1. Not always a player id
            int lordDeathStatusOrKiller; // 0x00002210 length: 4
            int playerRelatedFlag; // 0x00002214 length: 4
            short stoneGainedFraction; // 0x00002218 length: 2
            short woodGainedFraction; // 0x0000221A length: 2
            int chickenCount2; // 0x0000221C length: 4
            // [116 0x005477C0] PlayerData+0x2220: set to the child that recruited followers in state 16 (with
            // childUID +0x2224); other children entering state 16 join it as followers while units[id].uid matches;
            // cleared when the leader's walk ends, enemies appear or the uid no longer matches
            int childLeaderUnitId; // 0x00002220 length: 4
            // [116 0x005477C0] uid check paired with childTargetIDUnk
            int childLeaderUid; // 0x00002224 length: 4
            BOOLEnum areCarnivalUnitsPresent; // 0x00002228 length: 4
            int popularityChangeBasedOnFair; // 0x0000222C length: 4
            int troopsLost; // 0x00002230 length: 4
            int troopsKilled; // 0x00002234 length: 4
            // [170 0x00579300] incremented per unit with blessedAmount>0 each tick (blessedAmount is decremented at
            // the same time)
            int blessedUnitCount; // 0x00002238 length: 4
            // [170 0x00579300] incremented per unit with blessedAmount==0 whose type is not in NotBlessableUnits
            int unblessedBlessableUnitCount; // 0x0000223C length: 4
            int blessedPeoplePercentage; // 0x00002240 length: 4
            // 0 ongoing, 1 won/ended, 2 lost; game-over sets 1 for all slots; not death-specific.
            int gameOutcome; // 0x00002244 length: 4
            short lastMonthsGold; // 0x00002248 length: 2
            short beforeLastMonthsGold; // 0x0000224A length: 2
            short foodStorageLevelLastMonth; // 0x0000224C length: 2
            short foodStorageLevelLastLastMonth; // 0x0000224E length: 2
            // [044 0x0045B830] compared with popularity +-500 and updated when falling/rising speech is played
            short lastAnnouncedPopularity; // 0x00002250 length: 2
            short availableHorses; // 0x00002252 length: 2
            // [115 0x00546BC0] PlayerData+0x2254 incremented once per mother update and zeroed for players 1-8 each
            // tick in resetCountsAndStatistics; mother+child sum > 75 makes the unit disappear
            int motherCountThisTick; // 0x00002254 length: 4
            // [115 0x00546BC0] PlayerData+0x2258 is the term added to the mother count in the 75 cap; it is
            // incremented by UpdateChild
            int childCountThisTick; // 0x00002258 length: 4
            short freshUnitTribeIDs[4]; // 0x0000225C length: 8
            int freshUnitTribeUIDs[4]; // 0x00002264 length: 16
            int aiControlStatusRelated; // 0x00002274 length: 4
            // Player's cow count: decremented when cows disappear or are thrown; shown on cow-throw button.
            int cowCount; // 0x00002278 length: 4
            short pitchDitchCounterTo4; // 0x0000227C length: 2
            short previousBlessedPeoplePercentage; // 0x0000227E length: 2
            // 0 -> bread, 1 -> cheese, 2 -> meat, 3 -> apple; used as boolean, 0 = not banned
            short isFoodTypeBanned[4]; // 0x00002280 length: 8
            // [042 0x00458F70] incremented once per BT_CHAPEL owned
            int chapelCount; // 0x00002288 length: 4
            // incremented per BT_CHURCH; elsewhere tested nonzero, so a count covers both uses
            int churchCount; // 0x0000228C length: 4
            // incremented per BT_CATHEDRAL; elsewhere tested nonzero, so a count covers both uses
            int cathedralCount; // 0x00002290 length: 4
            // Created by retype action
            int popularityReligionBasedDiv25; // 0x00002294 length: 4
            // [135 0x00566750] incremented once per tick for every priest unit of that owner
            int priestCount; // 0x00002298 length: 4
            // real per-player value (other players reached with stride 0xE7D ints = sizeof(PlayerData)):
            // RenderUnknownDisplayElement25 prints it (up to 8 digits) under each player name,
            // checkSkirmishGameDefeat (when GameCore.isKingOfTheHill != 0) picks the winning team from a present player
            // whose value is 0 - likely remaining skirmish points; writer not visible
            // real per-player value (other players reached with stride 0xE7D ints = sizeof(PlayerData)):
            // RenderUnknownDisplayElement25 prints it (up to 8 digits) under each player name,
            // checkSkirmishGameDefeat (when GameCore.mapU4Int0 != 0) picks the winning team from a present player
            // whose value is 0 - likely remaining skirmish points; writer not visible
            int skirmishPointsLeft; // 0x0000229C length: 4
            // sum of (losses per unit type * unit weight)
            int weightedLosses; // 0x000022A0 length: 4
            uint beerPercentage; // 0x000022A4 length: 4
            short pitchDitchTileCount; // 0x000022A8 length: 2
            short moatTileCount; // 0x000022AA length: 2
            // [044 0x0045B830] decremented weekly while applying a -150..0 popularity modifier stored in
            // someCount54; someCount49-53 / someCount55-59 are the same pattern with fixed -75, -125, -50, +200,
            // +50
            short popularityEventWeeksLeft; // 0x000022AC length: 2
            // set to 0xC by lions event (Random_Events8), decremented weekly with -75 popularity while nonzero
            // (review 371 verified)
            short lionsEventCountdown; // 0x000022AE length: 2
            // set to 0x10 by bandits event (Random_Events9); weekly decrement with -125 popularity (review 371
            // verified)
            short banditsEventCountdown; // 0x000022B0 length: 2
            // set to 8 by the fire event; weekly countdown like the other event countdowns (review 371)
            short fireEventCountdown; // 0x000022B2 length: 2
            // set to 0xC by the marriage event (Random_Events12); weekly countdown (review 371)
            short marriageEventCountdown; // 0x000022B4 length: 2
            // set to 0x30 by the jester event (Random_Events13); weekly countdown (review 371)
            short jesterEventCountdown; // 0x000022B6 length: 2
            // [256 0x0043E6C0] shown next to TEXT_SCENARIO 0x8b 'Plague' and summed into popularity
            short plaguePopularityEffect; // 0x000022B8 length: 2
            // [256 0x0043E6C0] shown next to TEXT_SCENARIO 0x91 'Lion Attack' and summed into popularity
            short lionAttackPopularityEffect; // 0x000022BA length: 2
            // [256 0x0043E6C0] shown next to TEXT_SCENARIO 0x92 'Bandits' and summed into popularity
            short banditsPopularityEffect; // 0x000022BC length: 2
            // [256 0x0043E6C0] shown next to TEXT_SCENARIO 0xb3 'Fire!' and summed into popularity
            short firePopularityEffect; // 0x000022BE length: 2
            // [256 0x0043E6C0] shown next to TEXT_SCENARIO 0x95 'Marriage' and summed into the monthly popularity
            // total
            short marriagePopularityEffect; // 0x000022C0 length: 2
            // [256 0x0043E6C0] shown next to TEXT_SCENARIO 0x96 'Jester' and summed into popularity
            short jesterPopularityEffect; // 0x000022C2 length: 2
            // [111 0x00540440] incremented by 2 each time a healer finishes curing a disease cloud (only use seen
            // here) [UNK PASS] was healerCureScoreUnk
            int plagueCureProgress; // 0x000022C4 length: 4
            // [069 0x0040FC40] receives the unit spawned as UT_GHOST at the shrine
            int ghostUnitID; // 0x000022C8 length: 4
            // uid of the ghost unit spawned for the player (paired with someUnitID01); reset if the unit uid no
            // longer matches
            int ghostUnitUid; // 0x000022CC length: 4
            int countInns; // 0x000022D0 length: 4
            int lastlastEncounteredEnemyPlayerID; // 0x000022D4 length: 4
            byte lostUnitToEnemyPlayerFlags[4]; // 0x000022D8 length: 4
            int sumOfTotalEnemyUnitsCount; // 0x000022DC length: 4
            XYPairShort barracksAssemblyPoints[7]; // 0x000022E0 length: 28
            int aivID; // 0x000022FC length: 4
            // rat = 2, human = 0, ? = 1
            AITypeInt aiType; // 0x00002300 length: 4
            undefined1 padding_0x2304[52]; // 0x00002304 length: 52
            // Mercenary parade-ground table, same shape as barracksParadegroundLocations XYPairShort[6][72]
            // (+0x558): setupMercenaryPostCampgroundPositions memsets 0x6C0 bytes at player+0x115E130 (+0x2338),
            // fills 3 groups of 24 XYPairShort per row (ecx -0x60/+0x60) and steps rows by 0x120, sets the total
            // (+0x29F8) to 0x48; getKeepLocationForAIUnit reads row (class-10) entry idx<0x48 as [(player*0xE7D +
            // class*0x48 + idx)*4 + 0x115D5F2] (= +0x17F8 + class*0x120 + idx*4, class 10..15). The +0x17F8 base is
            // why Ghidra showed this access inside enemyIDArray.
            UnknownPlayerDataStructure mercenaryParadegroundLocations; // 0x00002338 length: 1728
            // [067 0x0040D400] zeroed then set to 0x48 exactly like barracksParadegroundLocationsTotal for the
            // barracks
            int mercenaryParadeLocationsTotal; // 0x000029F8 length: 4
            undefined1 padding_0x29fc[4]; // 0x000029FC length: 4
            // Per-unit-class rally waiting counter indexed by class 0..16: isSpaceAvailableAtUnitRallyPoint reads
            // [(player*0xE7D + class)*4 + 0x115E7F8] for European classes 0..5 (6->5), getKeepLocationForAIUnit for
            // mercenary classes 10..15 (16->13); class 6 (knight, +0x2A18) and 16 (+0x2A40) are also read directly;
            // each Update<Unit> increments its own element.
            int rallyWaitingCountPerClass[17]; // 0x00002A00 length: 68
            undefined4 someCount24; // 0x00002A44 length: 4
            undefined4 someCount25; // 0x00002A48 length: 4
            undefined4 someCount26; // 0x00002A4C length: 4
            // [102 0x00506BD0] copied into the new building's hovelVisualStyle and advanced as (n+1)%7 after a
            // hovel is placed; also picks the hovel ghost sprite in setConstructionGFXLayerBasedOnPlacementChecks
            int nextHovelVisualStyle; // 0x00002A50 length: 4
            // Created by retype action
            int aiFarmIndex; // 0x00002A54 length: 4
            undefined1 padding_0x2a58[16]; // 0x00002A58 length: 16
            // [031 0x004D48F0] set to 1 iff marketplace.id != 0
            int hasMarketplace; // 0x00002A68 length: 4
            BOOLEnum willBuy; // 0x00002A6C length: 4
            // actually this index is -1 if you compare it to ResourceType enum. So it should maybe start +4 later
            // in the struct?
            int resourcesToAcquireArray[24]; // 0x00002A70 length: 96
            undefined1 padding_0x2ad0[4]; // 0x00002AD0 length: 4
            // [025 0x004CB3A0] set to the quarry with no linked ox tether or the highest stone-per-tether ratio
            // (>20) when an extra ox tether is required Created by retype action
            int quarryNeedingOxTether; // 0x00002AD4 length: 4
            BOOLEnum granaryIsAlmostFilledUp; // 0x00002AD8 length: 4
            undefined4 isArmouryAlmostFilledUp; // 0x00002ADC length: 4
            // Set to 1 if a building was destroyed for this player
            int resourceRebuildDelay; // 0x00002AE0 length: 4
            int populationGrowthStatisticCounter; // 0x00002AE4 length: 4
            int populationGrowth[8]; // 0x00002AE8 length: 32
            // [UNK PASS] was averagePopulationGrowthUnk
            int averageAvailablePeasants; // 0x00002B08 length: 4
            int previousAvailablePeasants; // 0x00002B0C length: 4
            undefined1 padding_0x2b10[4]; // 0x00002B10 length: 4
            int farmsWithoutWorkers; // 0x00002B14 length: 4
            int countWoodcutters; // 0x00002B18 length: 4
            int noLabourerBuildingCount; // 0x00002B1C length: 4
            int someCount10; // 0x00002B20 length: 4
            // [026 0x004CB890] used directly as a building ID that is passed to
            // giveBackResourceForDestroyedBuilding/destroyBuilding; nothing here shows it is always a woodcutter
            int aiBuildingToDemolishID; // 0x00002B24 length: 4
            // Created by retype action
            int noWoodTracker; // 0x00002B28 length: 4
            // Created by retype action
            int noIronTracker; // 0x00002B2C length: 4
            // Created by retype action
            int noFlourTracker; // 0x00002B30 length: 4
            // Created by retype action
            int noHopsTracker; // 0x00002B34 length: 4
            // [026 0x004CBA50] incremented unconditionally on every call and never reset here; > 36 snoozes the
            // tanner like an input-missing tracker
            int aiEconomyTickCounter; // 0x00002B38 length: 4
            // [026 0x004CBA50] incremented while currentResources[0xE] (ale) < 1, reset otherwise, same pattern as
            // noWoodTracker/noHopsTracker; > 72 snoozes the inn Created by retype action
            int noAleTracker; // 0x00002B3C length: 4
            undefined4 someCount12; // 0x00002B40 length: 4
            undefined4 someCount13; // 0x00002B44 length: 4
            int aivNegativeFearFactorDelay; // 0x00002B48 length: 4
            int aivPositiveFearFactorDelay; // 0x00002B4C length: 4
            int defWallPatrolRallyTimeWaitCounter; // 0x00002B50 length: 4
            int defWallPatrolRallyTimeHits; // 0x00002B54 length: 4
            // incremented per non-dying engineer in UpdateEngineer (engineer census)
            int livingEngineerCount; // 0x00002B58 length: 4
            // [030 0x004D2000] compared against required engineer count before
            // assignRequiredIdleEngineersToNewTribe; else isEngineerRequired = TRUE
            int availableEngineerCount; // 0x00002B5C length: 4
            BOOLEnum isEngineerRequired; // 0x00002B60 length: 4
            int closestEnemyDistanceToTheLord; // 0x00002B64 length: 4
            undefined1 padding_0x2b68[4]; // 0x00002B68 length: 4
            int idlePeasantsCount; // 0x00002B6C length: 4
            int outerPatrolRallyDelayTracker; // 0x00002B70 length: 4
            // [031 0x004D3320] additive score 0..10 from gold/population/food/troops, thresholded into
            // aiStrengthFeeling source: np123
            int aiStrengthScore; // 0x00002B74 length: 4
            // Created by retype action
            int raidRetargetDelayCounter; // 0x00002B78 length: 4
            // [028 0x004CE930] result of tracePathToFriendlyDefenses from the attack army position; someX/someY are
            // its coordinates and become the defensive move target in makeUnitsGoDefensiveAndBackToSomeLocation
            int regroupTile; // 0x00002B7C length: 4
            // Created by retype action
            int someX; // 0x00002B80 length: 4
            // Created by retype action
            int someY; // 0x00002B84 length: 4
            // Created by retype action
            int countFletchersPoleturners; // 0x00002B88 length: 4
            // Created by retype action
            int countArmorersAndBlacksmiths; // 0x00002B8C length: 4
            // Created by retype action
            int countBakers; // 0x00002B90 length: 4
            // Created by retype action
            int countBrewers; // 0x00002B94 length: 4
            int shortestDistanceTile; // 0x00002B98 length: 4
            int shortestDistanceY; // 0x00002B9C length: 4
            int shortestDistanceX; // 0x00002BA0 length: 4
            // Created by retype action
            int aiPlayerState; // 0x00002BA4 length: 4
            int totalAttackingEngineerTroops; // 0x00002BA8 length: 4
            // Created by retype action
            int totalDiggingUnitTroops; // 0x00002BAC length: 4
            // Created by retype action
            int totalAssassinTroops; // 0x00002BB0 length: 4
            // Created by retype action
            int totalUnit2Troops; // 0x00002BB4 length: 4
            // Created by retype action
            int totalLaddermenTroops; // 0x00002BB8 length: 4
            // Created by retype action
            int totalTunnelerTroops; // 0x00002BBC length: 4
            // Created by retype action
            int totalUnitPatrolTroops; // 0x00002BC0 length: 4
            // Created by retype action
            int totalUnitBackupTroops; // 0x00002BC4 length: 4
            // Created by retype action
            int totalUnitEngageTroops; // 0x00002BC8 length: 4
            // Created by retype action
            int totalUnitSiegeDefTroops; // 0x00002BCC length: 4
            // Created by retype action
            int totalMaxDefaultTroops; // 0x00002BD0 length: 4
            // [027 0x004CDF10] its gold decides the raid size modifier in the raid parameter calculation
            int raidTargetPlayerID; // 0x00002BD4 length: 4
            int attackedPlayerID; // 0x00002BD8 length: 4
            int attackedByPlayerArrayUnk; // 0x00002BDC length: 4
            int field889_0x2be0; // 0x00002BE0 length: 4
            // accessed by 0x456537
            // int[9][8] per player from +0x2BE4: [p][0] written by processUnitLossStatistic 0x456537, [p][1] by
            // setLastEncounteredTroopUnit 0x456654
            int unusedEnemyAttackTracker[9][8]; // 0x00002BE4 length: 288
            undefined1 padding_0x2d04[24]; // 0x00002D04 length: 24
            int aivUnitLocationSlots[22][10]; // 0x00002D1C length: 880
            int aivUnitLocationSlotLocationCount[22]; // 0x0000308C length: 88
            // Created by retype action
            int totalTroopsType0; // 0x000030E4 length: 4
            // Created by retype action [UNK PASS] was totalDefensiveTroopsUnk
            int totalDefensiveTroops; // 0x000030E8 length: 4
            // Created by retype action [UNK PASS] was totalRaidingTroopsUnk
            int totalRaidingTroops; // 0x000030EC length: 4
            // Created by retype action
            int totalAttackTroops; // 0x000030F0 length: 4
            // Created by retype action
            AIStrengthTypeInt aiStrengthFeeling; // 0x000030F4 length: 4
            AIRecruitUnitChoiceInt aiRecruitUnitChoiceState; // 0x000030F8 length: 4
            int aiRecruitIntervalTracker; // 0x000030FC length: 4
            int aiDefUnitChoiceIndex; // 0x00003100 length: 4
            int aiRaidUnitChoiceIndex; // 0x00003104 length: 4
            int aiAttUnitMainChoiceIndex; // 0x00003108 length: 4
            short aiTribeIDs[200]; // 0x0000310C length: 400
            int aiTribeUIDs[200]; // 0x0000329C length: 800
            // [030 0x004D2A70] filled on the building owner's record; here the own list is used for gathering and
            // the enemy's list (attackedPlayerID_2Unk) for raiding
            short ownTargetableBuildings[100]; // 0x000035BC length: 200
            // Created by retype action
            int top100TargetableBuildingsTracker; // 0x00003684 length: 4
            // [027 0x004CDBC0] incremented each call, wraps at targetable building count, used as rotating start
            // offset of the scan
            int targetBuildingScanRotation; // 0x00003688 length: 4
            AISiegeUnitCreation aiSiegeCreationInformation[4][5]; // 0x0000368C length: 400
            // [032 0x004D49E0] reset entering state 4, incremented each state-4 call and compared to AIC
            // AttAssaultDelay (+0x208); forced to 100 when no siege engines remain
            int attAssaultDelayCounter; // 0x0000381C length: 4
            // current name is inverted: set to 1 when own troop value <= enemy + margin; UI shows 'Help Needed!'
            // when set
            int helpNeeded; // 0x00003820 length: 4
            // indexed by requesting player; stores the requested ResourceType, amount kept 10 shorts later (3 uses
            // agree)
            short requestedGoodsTypeByPlayer[10]; // 0x00003824 length: 20
            // Requested goods amount indexed by requesting player; shown as 'Requests'
            short requestedGoodsAmountByPlayer[10]; // 0x00003838 length: 20
            // order this player received from an ally: 0 none, 1 attack (+target), 2 defend; Allies UI shows it as
            // 'Orders'
            int allyOrderState; // 0x0000384C length: 4
            // Target player of the ally attack request, drawn next to the Attack order
            int allyRequestAttackTarget; // 0x00003850 length: 4
            int unitPatrolRecommandRelatedDelayValue; // 0x00003854 length: 4
            // Created by retype action
            int aiCowThrowCounter; // 0x00003858 length: 4
            int aiPopularityDecisionValue; // 0x0000385C length: 4
            int aiResourceBuildingFocusIndicator; // 0x00003860 length: 4
            // Created by retype action
            int aivCurrentPauseIndex; // 0x00003864 length: 4
            int aivCurrentPause; // 0x00003868 length: 4
            short aivPauses[20]; // 0x0000386C length: 40
            int aivPauseDelay; // 0x00003894 length: 4
            int aiRequestDelay; // 0x00003898 length: 4
            int nervousBikCountdown; // 0x0000389C length: 4
            // Created by retype action
            int currentWaveRandomAttackingStrength; // 0x000038A0 length: 4
            // [029 0x004D0C00] gate and 0x60 reload for the anger2 video
            int anger2BikCooldown; // 0x000038A4 length: 4
            // [029 0x004D0C70] gate and 0x30 reload for the victory2 video
            int victory2BikCooldown; // 0x000038A8 length: 4
            // [029 0x004D0CF0] gate and 0x30 reload for the nervous1 video
            int nervous1BikCooldown; // 0x000038AC length: 4
            // [029 0x004D0D40] gate and 0x30 reload for the request-help video
            int requestHelpBikCooldown; // 0x000038B0 length: 4
            undefined1 padding_0x38b4[4]; // 0x000038B4 length: 4
            int totalEnemyTroopValueByPlayerID[9]; // 0x000038B8 length: 36
            undefined1 padding_0x38dc[4]; // 0x000038DC length: 4
            int totalEnemyTroopValue; // 0x000038E0 length: 4
            // Set to requestedByPlayerID whenever an ally attack/defence request is stored; shown as order issuer
            // Created by retype action
            int allyRequestByPlayerID; // 0x000038E4 length: 4
            int totalTroopValue; // 0x000038E8 length: 4
            int aiBuildingDestroyChoiceTracker; // 0x000038EC length: 4
            int aiNervousActionsTracker; // 0x000038F0 length: 4
            // Created by retype action
            int currentAttackRaidParameter; // 0x000038F4 length: 4
            // [150 0x005237F0] holds the tribe ID new monks are added to, validated with monkTribeUIDUnk
            int monkTribeID; // 0x000038F8 length: 4
            // [150 0x005237F0] uid of monkTribeIDUnk's tribe for staleness check
            int monkTribeUID; // 0x000038FC length: 4
            int healerCount; // 0x00003900 length: 4
            // [110 0x0053EAA0] incremented for fading-out peasants whose unitTypeToChangeInto is a military/siege
            // type
            int peasantsBeingRecruitedAsTroops; // 0x00003904 length: 4
            // Represents the number of prepared AI team members the AI is willing to wait for until attacking
            int aiAttackCoordinationLevel; // 0x00003908 length: 4
            // [030 0x004D2A70] set to 100 when a raid tribe is ordered to attack a building, decremented each call
            // while raiding troops exist; while > 0 the gather-at-home branch is skipped Created by retype action
            int raidAttackCountdown; // 0x0000390C length: 4
            // [162 0x00532BA0] machine code at 0x532E1A..0x532E4F adds the value only when the type is NOT
            // 22/23/70/72/74/76 (archer, crossbow, Arab archer, slinger, horse archer, fire thrower)
            int totalEnemyNonRangedTroopValue; // 0x00003910 length: 4
            // Created by retype action
            int harrassingSiegeEnginesIndex; // 0x00003914 length: 4
            int harrasingEngineRecruitTimeout; // 0x00003918 length: 4
            // [027 0x004CD2A0] compared against AIC HarassingSiegeEnginesMax (+0x1EC) before building more
            // harassing engines
            int harassingSiegeEnginesCount; // 0x0000391C length: 4
            int totalTeamTroopValue; // 0x00003920 length: 4
            // Created by retype action
            int currentAttackWave; // 0x00003924 length: 4
            int countFarms; // 0x00003928 length: 4
            // [139 0x0056C560] set to 0xA0 when loot is queued; UpdateStockpile delivers pending goods only while
            // it is 0
            int goodsDeliveryDelay; // 0x0000392C length: 4
            int aiCoordinatedAttackPatience; // 0x00003930 length: 4
            int someXPosition; // 0x00003934 length: 4
            int someYPosition; // 0x00003938 length: 4
            int totalTroopsType6; // 0x0000393C length: 4
            int unknownCounter_01; // 0x00003940 length: 4
            int totalTroopsType7; // 0x00003944 length: 4
            int lastEncounteredTroopUnitID; // 0x00003948 length: 4
            int lastEncounteredTroopUnitUID; // 0x0000394C length: 4
            short mercenaryAssemblyPoints[7][2]; // 0x00003950 length: 28
            int moatsOwned; // 0x0000396C length: 4
            int attackTicker; // 0x00003970 length: 4
            int canStartSpending; // 0x00003974 length: 4
            // [033 0x004EE140] same decrement/reset-to-5 cooldown pattern as algoIronCooldown for the woodcutter
            // search
            short algoTreeCooldown; // 0x00003978 length: 2
            // [033 0x004EDDF0] decremented while >0, set to 5 after a failed search, exactly like
            // algoIronCooldown/algoOilCooldown
            short algoOasisCooldown; // 0x0000397A length: 2
            short algoBoulderCooldown; // 0x0000397C length: 2
            short algoIronCooldown; // 0x0000397E length: 2
            short algoOilCooldown; // 0x00003980 length: 2
            short availableTreeGridTiles; // 0x00003982 length: 2
            short availableOasisGridTiles; // 0x00003984 length: 2
            short availableBoulderGridTiles; // 0x00003986 length: 2
            short availableIronGridTiles; // 0x00003988 length: 2
            short availableOilGridTiles; // 0x0000398A length: 2
            int countIronMines; // 0x0000398C length: 4
            int countPitchRigs; // 0x00003990 length: 4
            int countStoneQuarries; // 0x00003994 length: 4
            int unknownPathBorderDistanceRelated; // 0x00003998 length: 4
            // [115 0x00546BC0] in GM_SKIRMISH_SINGLE_PLAYER a non-zero value counts as no enemies present,
            // mirroring sumOfTotalEnemyUnitsCount == 0 in other modes
            int noEnemyThreatSkirmish; // 0x0000399C length: 4
            short keepEnclosementRelatedCountdown; // 0x000039A0 length: 2
            short defensesDamagedByPlayer; // 0x000039A2 length: 2
            XYPairShort engineersAssemblyPoints[2]; // 0x000039A4 length: 8
            short tunnelersGuildAssemblyPointX; // 0x000039AC length: 2
            short tunnelersGuildAssemblyPointY; // 0x000039AE length: 2
            short cathedralAssemblyPointX; // 0x000039B0 length: 2
            short cathedralAssemblyPointY; // 0x000039B2 length: 2
            undefined1 padding_0x39b4[4]; // 0x000039B4 length: 4
            // Incremented per ladderman in rally state 0x69; used as laddermen's slot index; engineers start at
            // someCount27-this.
            undefined2 laddermanAssemblyCount; // 0x000039B8 length: 2
            // Incremented per monk heading to cathedral assembly (state 0x69); start index of the assembly tile
            // search.
            undefined2 monkAssemblyCount; // 0x000039BA length: 2
            // [032 0x004D49E0] incremented each call in state 5; wall-assault commands are issued and it is reset
            // when it exceeds 3; reset on entering state 5
            short wallAssaultTickCounter; // 0x000039BC length: 2
            // [061 0x00417B90] incremented for each drawbridge that is raising, raised or lowering this tick (and
            // when a raise starts)
            undefined2 notLoweredDrawbridgeCount; // 0x000039BE length: 2
            short relativeStrengthOfTeamComparedToEnemy; // 0x000039C0 length: 2
            short aiStateCounter; // 0x000039C2 length: 2
            short commemorationShrinePlacementCountdown; // 0x000039C4 length: 2
            short someKeepRelatedX2; // 0x000039C6 length: 2
            short someKeepRelatedY2; // 0x000039C8 length: 2
            short dogCageCount; // 0x000039CA length: 2
            int unknownHarrassingSiegeRelated; // 0x000039CC length: 4
            int ignitionTime; // 0x000039D0 length: 4
            int tacticalPowersBarLevel; // 0x000039D4 length: 4
            int goldDonation; // 0x000039D8 length: 4
            undefined1 padding_0x39dc[24]; // 0x000039DC length: 24

        } PlayerData;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(PlayerData) == 14836, PlayerData);
    } // namespace Player
} // namespace Game
} // namespace OpenSHC
