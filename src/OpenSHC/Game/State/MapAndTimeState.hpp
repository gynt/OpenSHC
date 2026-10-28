/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/State/MapAndTimeState.hpp'
*/

#pragma once

#include "OpenSHC/AI/Siege/SiegeUnitCounts.hpp"
#include "OpenSHC/Game/Market/BuySellPair.hpp"
#include "OpenSHC/Game/Signpost/SignpostLocation.hpp"
#include "OpenSHC/Game/Skirmish/AttackVector.hpp"
#include "OpenSHC/Map/Location/Point4ShortXY.hpp"
#include "OpenSHC/Map/Location/Point8IntXY.hpp"
#include "OpenSHC/Map/Navigation/Algorithms/XYPair.hpp"
#include "OpenSHC/Map/Navigation/Algorithms/XYTileObject.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "WinDef.h"

namespace OpenSHC {
namespace Game {
    namespace State {

        using OpenSHC::AI::Siege::SiegeUnitCounts;
        using OpenSHC::Game::Market::BuySellPair;
        using OpenSHC::Game::Signpost::SignpostLocation;
        using OpenSHC::Game::Skirmish::AttackVector;
        using OpenSHC::Map::Location::Point4ShortXY;
        using OpenSHC::Map::Location::Point8IntXY;
        using OpenSHC::Map::Navigation::Algorithms::XYPair;
        using OpenSHC::Map::Navigation::Algorithms::XYTileObject;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)
        // SIZE: 0x000401D0
        typedef struct MapAndTimeState {

            int field0_0x0; // 0x00000000 length: 4
            BOOLEnum singlePlayerHasKeepAndGranary; // 0x00000004 length: 4
            // per player slot array A[0] (10 ints at +0x8), zeroed in clearEnemyRelatedStructures/migrate; no
            // reader seen
            int playerSlotArrA0; // 0x00000008 length: 4
            // per player slot array A[1] (10 ints at +0x8), zeroed in clearEnemyRelatedStructures/migrate; no
            // reader seen
            int playerSlotArrA1; // 0x0000000C length: 4
            // per player slot array A[2] (10 ints at +0x8), zeroed in clearEnemyRelatedStructures/migrate; no
            // reader seen
            int playerSlotArrA2; // 0x00000010 length: 4
            // per player slot array A[3] (10 ints at +0x8), zeroed in clearEnemyRelatedStructures/migrate; no
            // reader seen
            int playerSlotArrA3; // 0x00000014 length: 4
            // per player slot array A[4] (10 ints at +0x8), zeroed in clearEnemyRelatedStructures/migrate; no
            // reader seen
            int playerSlotArrA4; // 0x00000018 length: 4
            // per player slot array A[5] (10 ints at +0x8), zeroed in clearEnemyRelatedStructures/migrate; no
            // reader seen
            int playerSlotArrA5; // 0x0000001C length: 4
            // per player slot array A[6] (10 ints at +0x8), zeroed in clearEnemyRelatedStructures/migrate; no
            // reader seen
            int playerSlotArrA6; // 0x00000020 length: 4
            // per player slot array A[7] (10 ints at +0x8), zeroed in clearEnemyRelatedStructures/migrate; no
            // reader seen
            int playerSlotArrA7; // 0x00000024 length: 4
            // per player slot array A[8] (10 ints at +0x8), zeroed in clearEnemyRelatedStructures/migrate; no
            // reader seen
            int playerSlotArrA8; // 0x00000028 length: 4
            // per player slot array A[9] (10 ints at +0x8), zeroed in clearEnemyRelatedStructures/migrate; no
            // reader seen
            int playerSlotArrA9; // 0x0000002C length: 4
            // per player slot array B[0] (10 ints at +0x30), zeroed in clearEnemyRelatedStructures/migrate; no
            // reader seen
            int playerSlotArrB0; // 0x00000030 length: 4
            // per player slot array B[1] (10 ints at +0x30), zeroed in clearEnemyRelatedStructures/migrate; no
            // reader seen
            int playerSlotArrB1; // 0x00000034 length: 4
            // per player slot array B[2] (10 ints at +0x30), zeroed in clearEnemyRelatedStructures/migrate; no
            // reader seen
            int playerSlotArrB2; // 0x00000038 length: 4
            // per player slot array B[3] (10 ints at +0x30), zeroed in clearEnemyRelatedStructures/migrate; no
            // reader seen
            int playerSlotArrB3; // 0x0000003C length: 4
            // per player slot array B[4] (10 ints at +0x30), zeroed in clearEnemyRelatedStructures/migrate; no
            // reader seen
            int playerSlotArrB4; // 0x00000040 length: 4
            // per player slot array B[5] (10 ints at +0x30), zeroed in clearEnemyRelatedStructures/migrate; no
            // reader seen
            int playerSlotArrB5; // 0x00000044 length: 4
            // per player slot array B[6] (10 ints at +0x30), zeroed in clearEnemyRelatedStructures/migrate; no
            // reader seen
            int playerSlotArrB6; // 0x00000048 length: 4
            // per player slot array B[7] (10 ints at +0x30), zeroed in clearEnemyRelatedStructures/migrate; no
            // reader seen
            int playerSlotArrB7; // 0x0000004C length: 4
            // per player slot array B[8] (10 ints at +0x30), zeroed in clearEnemyRelatedStructures/migrate; no
            // reader seen
            int playerSlotArrB8; // 0x00000050 length: 4
            // per player slot array B[9] (10 ints at +0x30), zeroed in clearEnemyRelatedStructures/migrate; no
            // reader seen
            int playerSlotArrB9; // 0x00000054 length: 4
            // Alt+digit writes [VK*4+0x117C724] = mapAndTime+0x58 (asm 0x4B4B76); data pass: preset to each
            // player's keep tile keep tile (currentTilePositionAdjusted) per player slot 0..9 (index = player id),
            // -1 = none; filled in LaunchSkirmishGame for present players, cycled by 'view to keeps'; migrated from
            // +0x2724 for old map versions
            int keepOrBookmarkTiles[2][5]; // 0x00000058 length: 40
            // per player slot array C[0] (10 ints at +0x80, after keepTilePerPlayer), initialised to -1 (id/tile)
            // in clearEnemyRelatedStructures/migrate
            int playerSlotIdArrC0; // 0x00000080 length: 4
            // per player slot array C[1] (10 ints at +0x80, after keepTilePerPlayer), initialised to -1 (id/tile)
            // in clearEnemyRelatedStructures/migrate
            int playerSlotIdArrC1; // 0x00000084 length: 4
            // per player slot array C[2] (10 ints at +0x80, after keepTilePerPlayer), initialised to -1 (id/tile)
            // in clearEnemyRelatedStructures/migrate
            int playerSlotIdArrC2; // 0x00000088 length: 4
            // per player slot array C[3] (10 ints at +0x80, after keepTilePerPlayer), initialised to -1 (id/tile)
            // in clearEnemyRelatedStructures/migrate
            int playerSlotIdArrC3; // 0x0000008C length: 4
            // per player slot array C[4] (10 ints at +0x80, after keepTilePerPlayer), initialised to -1 (id/tile)
            // in clearEnemyRelatedStructures/migrate
            int playerSlotIdArrC4; // 0x00000090 length: 4
            // per player slot array C[5] (10 ints at +0x80, after keepTilePerPlayer), initialised to -1 (id/tile)
            // in clearEnemyRelatedStructures/migrate
            int playerSlotIdArrC5; // 0x00000094 length: 4
            // per player slot array C[6] (10 ints at +0x80, after keepTilePerPlayer), initialised to -1 (id/tile)
            // in clearEnemyRelatedStructures/migrate
            int playerSlotIdArrC6; // 0x00000098 length: 4
            // per player slot array C[7] (10 ints at +0x80, after keepTilePerPlayer), initialised to -1 (id/tile)
            // in clearEnemyRelatedStructures/migrate
            int playerSlotIdArrC7; // 0x0000009C length: 4
            // per player slot array C[8] (10 ints at +0x80, after keepTilePerPlayer), initialised to -1 (id/tile)
            // in clearEnemyRelatedStructures/migrate
            int playerSlotIdArrC8; // 0x000000A0 length: 4
            // per player slot array C[9] (10 ints at +0x80, after keepTilePerPlayer), initialised to -1 (id/tile)
            // in clearEnemyRelatedStructures/migrate
            int playerSlotIdArrC9; // 0x000000A4 length: 4
            // One int[9] indexed by killer player id: every unit update does add [killer*4+0x117C834];
            // processSingleplayerEvents sums/clears all 9.
            int unitsLostToPlayer[9]; // 0x000000A8 length: 36
            // [080 0x004C2280] Per-player counters summed and compared with thresholds (>7, >0xe) to advance
            // stages; typo 'emeny'. Code does not show whether they count kills or hits, so only the typo is fixed.
            int enemyHitCountByPlayer[9]; // 0x000000CC length: 36
            // Per-hint "revealed" byte flags of the scenario description (residual review 380/381):
            // MenuView_ScenarioDescription_DoEveryFrame tests/sets byte [hint+0x117C87C] (MapAndTime 0x117C78C +
            // 0xF0) with hint index edi = 0..peasantsArrivingAtCampfire-1 (count from the per-mission hint tables, max 4 in the table);
            // loadMap saves/restores and ScenarioDescription_Prepare zeroes exactly these 8 bytes as two dwords
            // (0x117C87C/0x117C880).
            // Per-hint "revealed" byte flags of the scenario description (residual review 380/381):
            // MenuView_ScenarioDescription_DoEveryFrame tests/sets byte [hint+0x117C87C] (MapAndTime 0x117C78C +
            // 0xF0) with hint index edi = 0..count-1 (count from the per-mission hint tables, max 4 in the table);
            // loadMap saves/restores and ScenarioDescription_Prepare zeroes exactly these 8 bytes as two dwords
            // (0x117C87C/0x117C880).
            byte hintRevealed[8]; // 0x000000F0 length: 8
            int multiplayerUnitSameTileLinkageTimeWindow; // 0x000000F8 length: 4
            DWORD gameOverTime; // 0x000000FC length: 4
            int drunkenManStatus; // 0x00000100 length: 4
            undefined1 padding_0x104[144]; // 0x00000104 length: 144
            // start of the game-state region hashed and resent in 18 chunks of 0x38E6 bytes for multiplayer resync
            int syncedStateRegionStart; // 0x00000194 length: 4
            // zeroed in resetCountsAndStatistics; no other use seen
            int statCounter198; // 0x00000198 length: 4
            undefined1 padding_0x19c[380]; // 0x0000019C length: 380
            int cathedralRelated1; // 0x00000318 length: 4
            undefined1 padding_0x31c[8]; // 0x0000031C length: 8
            int week; // 0x00000324 length: 4
            int month; // 0x00000328 length: 4
            int year; // 0x0000032C length: 4
            undefined1 padding_0x330[8]; // 0x00000330 length: 8
            int monthChanged; // 0x00000338 length: 4
            int yearChanged; // 0x0000033C length: 4
            int weekChanged; // 0x00000340 length: 4
            int skirmishStrongWalls; // 0x00000344 length: 4
            int skirmishAlliances; // 0x00000348 length: 4
            int counterForUpdatingSeparateAreaTileMaps; // 0x0000034C length: 4
            // [UNK PASS] was totalGameTicksUnk
            int totalGameTicks; // 0x00000350 length: 4
            // [043 0x0045A060] printed under the debug label 'lightning count' (debug label only;
            // setVariousGameStateToInitialValues initialises it like a tree-spread value, label may be a leftover)
            int lightningCounter; // 0x00000354 length: 4
            int newOrganisms; // 0x00000358 length: 4
            // [043 0x0045A060] printed under the debug label 'power' (debug label only;
            // setVariousGameStateToInitialValues initialises it like a tree-spread value, label may be a leftover)
            int lightningPower; // 0x0000035C length: 4
            int newOrganismsValue2; // 0x00000360 length: 4
            BOOLEnum startOfDay; // 0x00000364 length: 4
            int skirmishFogOfWar; // 0x00000368 length: 4
            undefined1 padding_0x36c[436]; // 0x0000036C length: 436
            // [000 0x004A6940] filled with one (x,y) per flood-filled region found from the BFS queue
            // [000 0x004A6940] filled with one (x,y) per flood-filled region found from the BFS queue (max 40)
            XYPair regionSeedPoints[40]; // 0x00000520 length: 320
            int startGoods[25]; // 0x00000660 length: 100
            SiegeUnitCounts siegeInformation; // 0x000006C4 length: 80
            int startingPopularity; // 0x00000714 length: 4
            undefined1 padding_0x718[4]; // 0x00000718 length: 4
            // trader-related setting next to traderRelated1: 1 at skirmish launch, 0 when importing trading costs
            int traderFlag71c; // 0x0000071C length: 4
            // trader-related value zeroed at skirmish launch and when importing trading costs
            int traderValue720; // 0x00000720 length: 4
            // [043 0x0045B6B0] threshold for the week counter in state 2
            int traderReturnDelayWeeks; // 0x00000724 length: 4
            // [043 0x0045B6B0] threshold for the week counter before a trader spawns in state 0
            int traderSpawnIntervalWeeks; // 0x00000728 length: 4
            // [043 0x0045B6B0] incremented on each call (updateTrader runs only on weekChanged), reset on state
            // changes
            int traderWeekCounter; // 0x0000072C length: 4
            // [043 0x0045B6B0] state 0/1/2 switched here, set to 2 by activateTraderState and 0 by resetTraderState
            int traderState; // 0x00000730 length: 4
            int traderVisitsPlayer; // 0x00000734 length: 4
            undefined1 padding_0x738[72]; // 0x00000738 length: 72
            BuySellPair copyOfBuyAndSalesPrice[25]; // 0x00000780 length: 200
            BuySellPair buyAndSalesPriceArray[25]; // 0x00000848 length: 200
            int unknownResouceFlagArray1[25]; // 0x00000910 length: 100
            int unknownResourceFlagArray2[25]; // 0x00000974 length: 100
            int isResourceTradeable[25]; // 0x000009D8 length: 100
            int deerCount; // 0x00000A3C length: 4
            Point4ShortXY deerSpawnLocationsXY[4]; // 0x00000A40 length: 16
            // [152 0x00527440] tick counter reset after >200 (or >50) ticks; -1 disables reinforcement spawning
            int reinforcementSpawnTimer; // 0x00000A50 length: 4
            undefined1 padding_0xa54[720]; // 0x00000A54 length: 720
            // accessed by 0x464dc2
            int field_0xd24; // 0x00000D24 length: 4
            undefined1 padding_0xd28[44]; // 0x00000D28 length: 44
            // accessed by 0x464bcd, 0x4f5105
            int field_0xd54; // 0x00000D54 length: 4
            undefined1 padding_0xd58[28]; // 0x00000D58 length: 28
            BOOLEnum gameOver; // 0x00000D74 length: 4
            // [080 0x004C2280] Set to 0xf0/0x280 on win/loss, decremented when no video plays; at 0 the mission end
            // is processed.
            int missionEndCountdown; // 0x00000D78 length: 4
            // [213 0x004649D0] read here as euroRecruitable[resourceType-10] for weapon/armour buttons (runs into
            // the euroRecruitableCopy_* fields) and euroRecruitableCopy_index_6_c for horses; the declared int[7]
            // plus the 'Copy' fields look like one per-resource availability table
            int itemAvailableByResource[7]; // 0x00000D7C length: 28
            int euroRecruitableCopy_index_0; // 0x00000D98 length: 4
            int euroRecruitableCopy_index_1_b; // 0x00000D9C length: 4
            int euroRecruitableCopy_index_2; // 0x00000DA0 length: 4
            int euroRecruitableCopy_index_3_b; // 0x00000DA4 length: 4
            // copy of euroRecruitable[4] != 0 (macemen recruitable), like the sibling euroRecruitableCopy_* flags
            int euroRecruitableCopy_index_4; // 0x00000DA8 length: 4
            int euroRecruitableCopy_index_6_a; // 0x00000DAC length: 4
            int euroRecruitableCopy_index_1_a; // 0x00000DB0 length: 4
            int euroRecruitableCopy_index_3_a_and_6_b; // 0x00000DB4 length: 4
            int euroRecruitableCopy_index_6_c; // 0x00000DB8 length: 4
            int playerTeams[9]; // 0x00000DBC length: 36
            int difficulty; // 0x00000DE0 length: 4
            short scenarioRationsSetting; // 0x00000DE4 length: 2
            short scenarioTaxesSetting; // 0x00000DE6 length: 2
            short scenarioGold; // 0x00000DE8 length: 2
            short editScenarioExtraOptions; // 0x00000DEA length: 2
            short eventCountdownRabbitInfestation; // 0x00000DEC length: 2
            // rotating index (mod 4) into recent/signpost spawn locations in findRecentOrSignpostSpawnLocation
            // (short)
            short animalSpawnLocationRotation; // 0x00000DEE length: 2
            Point4ShortXY lionLocationsXY[4]; // 0x00000DF0 length: 16
            // [040 0x0046BBD0] 0 for missions < 11, 1 otherwise
            short ladyEnabled; // 0x00000E00 length: 2
            // [040 0x0046BBD0] 0 for missions < 7, 1 otherwise
            short jesterEnabled; // 0x00000E02 length: 2
            short playerPopulationStatistics[9][300]; // 0x00000E04 length: 5400
            int populationIndex; // 0x0000231C length: 4
            undefined1 padding_0x2320[816]; // 0x00002320 length: 816
            int signpostsMapEdgeDataCounter; // 0x00002650 length: 4
            // One int[32] indexed by scenario event type: [ecx*4+0x117EDE0] in processSingleplayerEvents and
            // selectWorkerSpeechOrMoraleStateID; migrate writes all 32.
            int recentEventTimer[32]; // 0x00002654 length: 128
            // old save-version location of playerSlotArrA[0]; copied to it by migrateGameStateForMapVersion
            int legacyPlayerSlotArrA0; // 0x000026D4 length: 4
            // old save-version location of playerSlotArrA[1]; copied to it by migrateGameStateForMapVersion
            int legacyPlayerSlotArrA1; // 0x000026D8 length: 4
            // old save-version location of playerSlotArrA[2]; copied to it by migrateGameStateForMapVersion
            int legacyPlayerSlotArrA2; // 0x000026DC length: 4
            // old save-version location of playerSlotArrA[3]; copied to it by migrateGameStateForMapVersion
            int legacyPlayerSlotArrA3; // 0x000026E0 length: 4
            // old save-version location of playerSlotArrA[4]; copied to it by migrateGameStateForMapVersion
            int legacyPlayerSlotArrA4; // 0x000026E4 length: 4
            // old save-version location of playerSlotArrA[5]; copied to it by migrateGameStateForMapVersion
            int legacyPlayerSlotArrA5; // 0x000026E8 length: 4
            // old save-version location of playerSlotArrA[6]; copied to it by migrateGameStateForMapVersion
            int legacyPlayerSlotArrA6; // 0x000026EC length: 4
            // old save-version location of playerSlotArrA[7]; copied to it by migrateGameStateForMapVersion
            int legacyPlayerSlotArrA7; // 0x000026F0 length: 4
            // old save-version location of playerSlotArrA[8]; copied to it by migrateGameStateForMapVersion
            int legacyPlayerSlotArrA8; // 0x000026F4 length: 4
            // old save-version location of playerSlotArrA[9]; copied to it by migrateGameStateForMapVersion
            int legacyPlayerSlotArrA9; // 0x000026F8 length: 4
            // old save-version location of playerSlotArrB[0]; copied to it by migrateGameStateForMapVersion
            int legacyPlayerSlotArrB0; // 0x000026FC length: 4
            // old save-version location of playerSlotArrB[1]; copied to it by migrateGameStateForMapVersion
            int legacyPlayerSlotArrB1; // 0x00002700 length: 4
            // old save-version location of playerSlotArrB[2]; copied to it by migrateGameStateForMapVersion
            int legacyPlayerSlotArrB2; // 0x00002704 length: 4
            // old save-version location of playerSlotArrB[3]; copied to it by migrateGameStateForMapVersion
            int legacyPlayerSlotArrB3; // 0x00002708 length: 4
            // old save-version location of playerSlotArrB[4]; copied to it by migrateGameStateForMapVersion
            int legacyPlayerSlotArrB4; // 0x0000270C length: 4
            // old save-version location of playerSlotArrB[5]; copied to it by migrateGameStateForMapVersion
            int legacyPlayerSlotArrB5; // 0x00002710 length: 4
            // old save-version location of playerSlotArrB[6]; copied to it by migrateGameStateForMapVersion
            int legacyPlayerSlotArrB6; // 0x00002714 length: 4
            // old save-version location of playerSlotArrB[7]; copied to it by migrateGameStateForMapVersion
            int legacyPlayerSlotArrB7; // 0x00002718 length: 4
            // old save-version location of playerSlotArrB[8]; copied to it by migrateGameStateForMapVersion
            int legacyPlayerSlotArrB8; // 0x0000271C length: 4
            // old save-version location of playerSlotArrB[9]; copied to it by migrateGameStateForMapVersion
            int legacyPlayerSlotArrB9; // 0x00002720 length: 4
            // old save-version location of keepTilePerPlayer[0]; copied to it by migrateGameStateForMapVersion
            int legacyKeepTilePerPlayer0; // 0x00002724 length: 4
            // old save-version location of keepTilePerPlayer[1]; copied to it by migrateGameStateForMapVersion
            int legacyKeepTilePerPlayer1; // 0x00002728 length: 4
            // old save-version location of keepTilePerPlayer[2]; copied to it by migrateGameStateForMapVersion
            int legacyKeepTilePerPlayer2; // 0x0000272C length: 4
            // old save-version location of keepTilePerPlayer[3]; copied to it by migrateGameStateForMapVersion
            int legacyKeepTilePerPlayer3; // 0x00002730 length: 4
            // old save-version location of keepTilePerPlayer[4]; copied to it by migrateGameStateForMapVersion
            int legacyKeepTilePerPlayer4; // 0x00002734 length: 4
            // old save-version location of keepTilePerPlayer[5]; copied to it by migrateGameStateForMapVersion
            int legacyKeepTilePerPlayer5; // 0x00002738 length: 4
            // old save-version location of keepTilePerPlayer[6]; copied to it by migrateGameStateForMapVersion
            int legacyKeepTilePerPlayer6; // 0x0000273C length: 4
            // old save-version location of keepTilePerPlayer[7]; copied to it by migrateGameStateForMapVersion
            int legacyKeepTilePerPlayer7; // 0x00002740 length: 4
            // old save-version location of keepTilePerPlayer[8]; copied to it by migrateGameStateForMapVersion
            int legacyKeepTilePerPlayer8; // 0x00002744 length: 4
            // old save-version location of keepTilePerPlayer[9]; copied to it by migrateGameStateForMapVersion
            int legacyKeepTilePerPlayer9; // 0x00002748 length: 4
            // old save-version location of playerSlotIdArrC[0]; copied to it by migrateGameStateForMapVersion
            int legacyPlayerSlotIdArrC0; // 0x0000274C length: 4
            // old save-version location of playerSlotIdArrC[1]; copied to it by migrateGameStateForMapVersion
            int legacyPlayerSlotIdArrC1; // 0x00002750 length: 4
            // old save-version location of playerSlotIdArrC[2]; copied to it by migrateGameStateForMapVersion
            int legacyPlayerSlotIdArrC2; // 0x00002754 length: 4
            // old save-version location of playerSlotIdArrC[3]; copied to it by migrateGameStateForMapVersion
            int legacyPlayerSlotIdArrC3; // 0x00002758 length: 4
            // old save-version location of playerSlotIdArrC[4]; copied to it by migrateGameStateForMapVersion
            int legacyPlayerSlotIdArrC4; // 0x0000275C length: 4
            // old save-version location of playerSlotIdArrC[5]; copied to it by migrateGameStateForMapVersion
            int legacyPlayerSlotIdArrC5; // 0x00002760 length: 4
            // old save-version location of playerSlotIdArrC[6]; copied to it by migrateGameStateForMapVersion
            int legacyPlayerSlotIdArrC6; // 0x00002764 length: 4
            // old save-version location of playerSlotIdArrC[7]; copied to it by migrateGameStateForMapVersion
            int legacyPlayerSlotIdArrC7; // 0x00002768 length: 4
            // old save-version location of playerSlotIdArrC[8]; copied to it by migrateGameStateForMapVersion
            int legacyPlayerSlotIdArrC8; // 0x0000276C length: 4
            // old save-version location of playerSlotIdArrC[9]; copied to it by migrateGameStateForMapVersion
            int legacyPlayerSlotIdArrC9; // 0x00002770 length: 4
            // [081 0x004C31A0] Set to 0x28 at start of day in week 3 (tick 0x97) when an invasion (tl_type 1) is
            // scheduled for next month.
            int invasionNextMonthCountdown; // 0x00002774 length: 4
            // radius (+5) passed to isSignPostWithinDistance, set per campaign mission (0/7/0xF/0x1E/0x25); same
            // name as other entry for this field
            int signpostExclusionRadius; // 0x00002778 length: 4
            // number of rabbits counted this tick (UpdateRabbit increments, reset each pass); wildlife/merc spawn
            // slots refused when >= 160
            int rabbitCount; // 0x0000277C length: 4
            short rabbitSpawnXY[4][2]; // 0x00002780 length: 16
            // number of camels counted this tick (UpdateCamel increments; reset in resetCountsAndStatistics)
            int camelCount; // 0x00002790 length: 4
            Point4ShortXY camelSpawnXY[4]; // 0x00002794 length: 16
            // number of lions counted this tick (UpdateLion increments); UpdateLord checks lions + cage dogs < 3
            int lionCount; // 0x000027A4 length: 4
            // Set when invasion is 3 months ahead even if warnings are suppressed, cleared on spawn; not a warning
            // flag. set 1 in processSingleplayerEvents when the one-month-ahead warning of a scheduled invasion
            // (event type 1) fires, cleared to 0 when the invasion itself is processed; UpdateLord only roams/plays
            // idle variations while it is 0, no enemies are present and lions + cage dogs < 3
            int invasionImminent; // 0x000027A8 length: 4
            // number of released cage dogs counted this tick (UpdateCageDog increments)
            int cageDogCount; // 0x000027AC length: 4
            int somePlayerID; // 0x000027B0 length: 4
            // Zeroed at start; at game over set to 1 only for winners (all cleared, local set on forced win); 0 ->
            // game-lost screen
            short playerHasWon[9]; // 0x000027B4 length: 18
            short field3175_0x27c6; // 0x000027C6 length: 2
            // number of trees set on fire in the current tree update (max 20, reset in updateTrees)
            int treesLitThisPass; // 0x000027C8 length: 4
            int aliveDeerCount; // 0x000027CC length: 4
            int armySizeLimit; // 0x000027D0 length: 4
            // stage of the scripted dialogue/attack sequence in military campaign missions 16..20 (0..7), advanced
            // by updateMilitaryCampaignMissionState (short)
            short militaryMissionScriptStage; // 0x000027D4 length: 2
            // bit flags (bit0 tested) of the military campaign mission script (short)
            short militaryMissionScriptFlags; // 0x000027D6 length: 2
            // [080 0x004C2280] Year half of the scheduled script trigger date paired with monthCopy.
            short scriptTriggerYear; // 0x000027D8 length: 2
            // [080 0x004C2280] Set to current month + N; stages fire when month == monthCopy && year == yearCopy (a
            // scheduled trigger date, not a copy). Not wrapped (see bug), so may hold 12-14.
            short scriptTriggerMonth; // 0x000027DA length: 2
            // secondary stage of the military campaign mission script, must be 0 for some steps (short)
            short militaryMissionScriptStage2; // 0x000027DC length: 2
            // military campaign script value zeroed at skirmish launch (short)
            short militaryMissionScriptValue; // 0x000027DE length: 2
            int skirmishNoDogs; // 0x000027E0 length: 4
            int skirmishExtremeMode; // 0x000027E4 length: 4
            int skirmishExtremeMode2; // 0x000027E8 length: 4
            int skirmishNoCowThrowing; // 0x000027EC length: 4
            // [208 0x004B20B0] 0x117EF7C is decremented at 0x45CBFA and tested for 0 (horn) - it is the remaining
            // countdown
            int skirmishNoRushTicksLeft; // 0x000027F0 length: 4
            // [000 0x004B20D7] denominator of the remaining-time bar (ticks * width / ticksLeft); UI/Actions.cpp
            // sets it once from skirmishNoRushTicks while only skirmishNoRushTicks is decremented
            // (GameStateStructures.cpp)
            int skirmishNoRushTicksTotal; // 0x000027F4 length: 4
            int rawDeerCount; // 0x000027F8 length: 4
            undefined1 padding_0x27fc[252]; // 0x000027FC length: 252
            int mercRecruitable[7]; // 0x000028F8 length: 28
            undefined1 padding_0x2914[4]; // 0x00002914 length: 4
            int signpostIDs[8]; // 0x00002918 length: 32
            undefined1 padding_0x2938[16]; // 0x00002938 length: 16
            // accessed by 0x4ce330, 0x4ce375
            int field_0x2948; // 0x00002948 length: 4
            // accessed by 0x4ce33c, 0x4ce36f
            int field_0x294c; // 0x0000294C length: 4
            undefined1 padding_0x2950[8]; // 0x00002950 length: 8
            SignpostLocation signpostEntryData[8]; // 0x00002958 length: 128
            undefined1 padding_0x29d8[124]; // 0x000029D8 length: 124
            int strongWalls; // 0x00002A54 length: 4
            XYTileObject signpostsMapEdge[7][50]; // 0x00002A58 length: 5600
            undefined1 padding_0x4038[480]; // 0x00004038 length: 480
            Point8IntXY aiTribeMoveDestinationXYPairArray1[5][8]; // 0x00004218 length: 320
            XYPair unitMoveDestinationXYPairs[8][40]; // 0x00004358 length: 2560
            AttackVector attackVectors[9][50]; // 0x00004D58 length: 7200
            undefined1 padding_0x6978[800]; // 0x00006978 length: 800
            int playerGroupArray[9]; // 0x00006C98 length: 36
            undefined1 padding_0x6cbc[4]; // 0x00006CBC length: 4
            // [070 0x00419D70] number of entries written to playerEnemyBuildingIDs/UID for that player
            int playerEnemyBuildingCount[9]; // 0x00006CC0 length: 36
            int playerEnemyBuildingIDs[9][2000]; // 0x00006CE4 length: 72000
            int playerEnemyBuildingUID[9][2000]; // 0x00018624 length: 72000
            int playerEnemenyUnitUIDShortList[9][2500]; // 0x00029F64 length: 90000
            int dayTicks; // 0x0003FEF4 length: 4
            int weekTicks; // 0x0003FEF8 length: 4
            int monthTicks; // 0x0003FEFC length: 4
            // [152 0x00527440] read as int[player*0x14 + troopKind] queue and decremented when skirmish
            // reinforcements spawn width from machine code (int[20])
            byte playerQueuedTroops[80]; // 0x0003FF00 length: 80
            int startingTroops[8][20]; // 0x0003FF50 length: 640

        } MapAndTimeState;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(MapAndTimeState) == 262608, MapAndTimeState);
    } // namespace State
} // namespace Game
} // namespace OpenSHC
