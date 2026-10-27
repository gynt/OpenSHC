/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/AttackInfo.hpp'
*/

#pragma once

#include "OpenSHC/AI/Siege/EngineerBuildingAndCountPair.hpp"
#include "OpenSHC/Map/AttackInfoPitchRelated.hpp"
#include "OpenSHC/Map/AttackInfoSubArrayElement1.hpp"
#include "OpenSHC/Map/AttackInfoSubArrayElement2.hpp"
#include "OpenSHC/Map/AttackInfoSubArrayElement3.hpp"
#include "OpenSHC/Map/AttackInfoSubElement.hpp"
#include "OpenSHC/Map/Units/Attack/TribeSizesPerTribeType.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::AI::Siege::EngineerBuildingAndCountPair;
    using OpenSHC::Map::AttackInfoPitchRelated;
    using OpenSHC::Map::AttackInfoSubArrayElement1;
    using OpenSHC::Map::AttackInfoSubArrayElement2;
    using OpenSHC::Map::AttackInfoSubArrayElement3;
    using OpenSHC::Map::AttackInfoSubElement;
    using OpenSHC::Map::Units::Attack::TribeSizesPerTribeType;

#pragma pack(push, 1)
    // SIZE: 0x0010375C
    typedef struct AttackInfo {

        undefined1 padding_0x0[80144]; // 0x00000000 length: 80144
        int high1; // 0x00013910 length: 4
        int high2; // 0x00013914 length: 4
        int high3; // 0x00013918 length: 4
        AttackInfoSubArrayElement1 high2ValuesArray[1000]; // 0x0001391C length: 16000
        undefined1 padding_0x1779c[16]; // 0x0001779C length: 16
        int arch1; // 0x000177AC length: 4
        int arch2; // 0x000177B0 length: 4
        int arch3; // 0x000177B4 length: 4
        AttackInfoSubArrayElement1 arch2ValuesArray[1000]; // 0x000177B8 length: 16000
        undefined1 padding_0x1b638[16]; // 0x0001B638 length: 16
        int archerPoints; // 0x0001B648 length: 4
        int archerPointsNext; // 0x0001B64C length: 4
        // Archer-point records after archerPoints/archerPointsNext: 200 x 32-byte {x, y, tile, lastTick, tribeID,
        // tribeUID, holdCounter, pad}, slot 0 unused; loops run slot 1..199 (end pointers 0x17802AC/0x17802B4),
        // memset 0x20 per record, writes via shl 5 at 0x177E9A4+slot*32. Range ends at +0x1CF50 (<
        // targetedBuildingTilesArray +0x1CF70).
        int archerPointRecords[200][8]; // 0x0001B650 length: 6400
        undefined1 padding_0x1cf50[32]; // 0x0001CF50 length: 32
        int targetedBuildingTilesArray[4000]; // 0x0001CF70 length: 16000
        int targetedBuildingTilesArraySize; // 0x00020DF0 length: 4
        int startCon; // 0x00020DF4 length: 4
        int keepCon; // 0x00020DF8 length: 4
        int counter; // 0x00020DFC length: 4
        // accessed by 0x5181cb, 0x51f343, 0x51f49b
        undefined1 field_0x20e00[4]; // 0x00020E00 length: 4
        // Number of AI tribes of type 0x1A (UT_A_SLAVE tribes) counted by recountAttackTroopValue (+1 per tribe);
        // computeAttackWaveTroopComposition uses it as a lower bound for the _134984 group count.
        int slaveTribeCount; // 0x00020E04 length: 4
        int index; // 0x00020E08 length: 4
        undefined1 padding_0x20e0c[304]; // 0x00020E0C length: 304
        // accessed by 0x51967c, 0x5207f4, 0x5207fc, 0x520802
        int field_0x20f3c; // 0x00020F3C length: 4
        // accessed by 0x51935d, 0x5194c1, 0x519593, 0x519661
        int field_0x20f40; // 0x00020F40 length: 4
        // accessed by 0x51933a, 0x519389, 0x519395, 0x5193a1
        int field_0x20f44; // 0x00020F44 length: 4
        // accessed by 0x51933f, 0x5193cb, 0x519480, 0x51952e
        int field_0x20f48; // 0x00020F48 length: 4
        // accessed by 0x519345, 0x5193d5, 0x519491, 0x519544
        int field_0x20f4c; // 0x00020F4C length: 4
        // accessed by 0x519363, 0x5194c7, 0x519599, 0x51966b
        int field_0x20f50; // 0x00020F50 length: 4
        // accessed by 0x51934b, 0x5193df, 0x519413, 0x5194a4
        int field_0x20f54; // 0x00020F54 length: 4
        // accessed by 0x519351, 0x5193e5, 0x5193ed, 0x5194af
        int field_0x20f58; // 0x00020F58 length: 4
        // accessed by 0x519357, 0x5193fa, 0x519402, 0x519468
        int field_0x20f5c; // 0x00020F5C length: 4
        int catapults; // 0x00020F60 length: 4
        int engineers; // 0x00020F64 length: 4
        int pikemenSwordsmenAndMore; // 0x00020F68 length: 4
        int laddermen; // 0x00020F6C length: 4
        int spearmenAndMacemen; // 0x00020F70 length: 4
        // Number of non-siege fighting AI tribes counted by recountAttackTroopValue (+1 per tribe, aiTroops gets
        // the sizes); <6 / 10..19 / 20..29 select the attack-wave composition; >9 enables the STBT_0x3FB group in
        // delayed target assignment.
        int fightingTribeCount; // 0x00020F74 length: 4
        int attacker; // 0x00020F78 length: 4
        undefined1 padding_0x20f7c[4]; // 0x00020F7C length: 4
        int aiTroops; // 0x00020F80 length: 4
        // Toggles 0/1 on each aiRecomputeAttacks / aiRecomputeAttacks2 call; while < 1
        // calculateAttackVectorsToCampFireOfPlayer is run first, so attack vectors are recomputed every second
        // time; reset to 0 when aiTroops == 0.
        int attackVectorRecalcToggle; // 0x00020F84 length: 4
        int biggestZone; // 0x00020F88 length: 4
        int startZone; // 0x00020F8C length: 4
        int unknownOne_0x20f90; // 0x00020F90 length: 4
        int scaleZone; // 0x00020F94 length: 4
        // Global counter incremented every tick by each ladderman in state 3 (ladder placed against a wall), reset
        // to 0 in aiControlNonSkirmishUnitMovement.
        int placedLaddersCount; // 0x00020F98 length: 4
        // Set to 1 by playAttackAlarmSound; cleared when a wave is initialised or advanced to staging;
        // updateInProgressAttackWave plays the alarm once and does nothing further until it is set.
        int attackAlarmPlayed; // 0x00020F9C length: 4
        int someCounter1; // 0x00020FA0 length: 4
        undefined1 padding_0x20fa4[4]; // 0x00020FA4 length: 4
        // Array has 100 16-byte entries, not 50: clear loop runs 0x1784300..0x1784940 stride 16, sort pushes entry
        // 99 (0x178493C), swap temp nof_fpointsArrayCopy sits at +0x640 = 100*16.
        short nof_fpointsArray[100][8]; // 0x00020FA8 length: 1600
        short nof_fpointsArrayCopy[8]; // 0x000215E8 length: 16
        undefined1 padding_0x215f8[1600]; // 0x000215F8 length: 1600
        int nof_fpoints; // 0x00021C38 length: 4
        // [159 0x0051FB90] set to 1 when the AI has no combat troops, or is outnumbered 3:1 with few troops and low
        // enemy troop value
        int attackForceTooWeak; // 0x00021C3C length: 4
        int size; // 0x00021C40 length: 4
        // [159 0x005205A0] incremented on each recompute, reset when the wave ends; value10 - field89399_0x21c48
        // gates which target types are unlocked
        int targetRecomputeCount; // 0x00021C44 length: 4
        // Number of target-assignment rounds reserved for catapults: AttackInfoDefinedData.catapultHoldbackRoundsPerAttacker[attacker]
        // (+10 when zoneSize < 3000) if the wave has catapults, else 0; the other attack groups are released only
        // when value10 - this > 2.
        // Number of target-assignment rounds reserved for catapults: AttackInfoDefinedData.field4_0xa0[attacker]
        // (+10 when zoneSize < 3000) if the wave has catapults, else 0; the other attack groups are released only
        // when value10 - this > 2.
        int catapultLeadRounds; // 0x00021C48 length: 4
        // Copy of unknownTribeCounterRelated right after the moat group (STBT_0x3F7) was sorted/assigned in
        // executeAttackWaveTargetAssignment; later, if nonzero, that many tribes are sorted for STBT_0x3F4 and
        // switched to STBT_0x3FC.
        int moatTribesAssignedCount; // 0x00021C4C length: 4
        int casDis; // 0x00021C50 length: 4
        // accessed by 0x51e003, 0x51ffc4, 0x5209f2
        int field_0x21c54; // 0x00021C54 length: 4
        undefined1 padding_0x21c58[16032]; // 0x00021C58 length: 16032
        int zoneSize; // 0x00025AF8 length: 4
        int someDistanceLimit; // 0x00025AFC length: 4
        // Incremented when an attack wave starts (initializeOrAdvanceAttackWave); playRandomAmbientMusic plays
        // battle music while it is non-zero and enemies exist, then clears it; playRandomMusic02 recounts the troop
        // value when it is 0. Cleared by clearAttackInfo.
        int attackWaveMusicPending; // 0x00025B00 length: 4
        int playerTotalTroopValueArray[9]; // 0x00025B04 length: 36
        // Only reset to 0 in recountTotalTroopValue together with playerTotalTroopValueArray[0..8] (the int right
        // after that 9-entry array; possibly a 10th entry).
        int troopValueUnk25b28; // 0x00025B28 length: 4
        int playerTotalTroopValueOfTroopsNearKeep[9]; // 0x00025B2C length: 36
        // accessed by 0x51faba
        int field_0x25b50; // 0x00025B50 length: 4
        undefined1 padding_0x25b54[20472]; // 0x00025B54 length: 20472
        // accessed by 0x5181aa, 0x5210a0, 0x5210aa
        int field_0x2ab4c; // 0x0002AB4C length: 4
        // [160 0x00520F70] someIntArray2[wave-1] incremented each tick while the wave has tribes; >10 with
        // lowTroopValueRelated switches the wave to state 6
        int attackWaveAgeTicks[50]; // 0x0002AB50 length: 200
        undefined1 padding_0x2ac18[1596]; // 0x0002AC18 length: 1596
        // Up to 100 {tile, value} entries: registerSpottedEnemyTile (called from calculateUnitMovementSpeed for
        // tiles with LogicLayer bit 8) adds a tile with value 100, processSpottedEnemyTiles processes them (entries
        // with an invalid tile > 0x13A0F are cleared).
        AttackInfoPitchRelated spottedEnemyTiles[100]; // 0x0002B254 length: 800
        // Tick counter of the non-skirmish AI defence schedule in updateAttackInfoTick: 0 collect archers + assign
        // macemen/knights, 1 brazier flags, 0x3C knights, 0x46 macemen, every 16th tick oil, tick&15==8 archer
        // redeploy; incremented each tick and wraps from >100 back to 2; reset on wave-slot init and
        // clearAttackInfo.
        int defenseScheduleTick; // 0x0002B574 length: 4
        // Set to 1 once commandUnitsToMoveToKeep was issued (player 1 units can leave the keep area); reset at
        // schedule tick 0; redeployArchersToDefensivePositions only runs while it is 0.
        int unitsSentToKeep; // 0x0002B578 length: 4
        // [157 0x0051CA50] archers not on walls, popped later to refill wall posts
        short reserveArcherUnitIDs[1000]; // 0x0002B57C length: 2000
        // [157 0x0051CA50] count of reserveArcherUnitIDs
        int reserveArcherCount; // 0x0002BD4C length: 4
        // [157 0x0051CA50] tile of each archer standing on a wall (max 200)
        int wallArcherPostTiles[200]; // 0x0002BD50 length: 800
        // parallel to wallArcherPostTiles: unit ID per wall archer post (200 shorts)
        short wallArcherPostUnitIDs[200]; // 0x0002C070 length: 400
        // parallel to wallArcherPostTiles: unit uid per wall archer post (200 ints)
        int wallArcherPostUnitUIDs[200]; // 0x0002C200 length: 800
        // [157 0x0051CA50] count of recorded wall archer posts (capped at 200)
        int wallArcherPostCount; // 0x0002C520 length: 4
        int macemenTribeCount; // 0x0002C524 length: 4
        int knightTribeCount; // 0x0002C528 length: 4
        int macemenTribeArray[100]; // 0x0002C52C length: 400
        int knightTribeArray[100]; // 0x0002C6BC length: 400
        int pitchRelatedPlayerID; // 0x0002C84C length: 4
        int playerID_0x2c850; // 0x0002C850 length: 4
        // accessed by 0x51cf9f, 0x51d033, 0x51fecf, 0x51ff4c
        undefined1 field_0x2c854[4]; // 0x0002C854 length: 4
        // [158 0x0051E300] set to PathConnectionLayer of the tile holding an enemy UT_LORD (0x37) and compared to
        // startCon
        int lordConnectionArea; // 0x0002C858 length: 4
        // Only reset to 0 in recomputeAttackInfo together with scaleZone/someArea.
        int recomputeResetUnk2c85c; // 0x0002C85C length: 4
        // [158 0x0051E300] incremented for every tile holding an enemy unit of type 0x37 (UT_LORD)
        int enemyLordTileCount; // 0x0002C860 length: 4
        // [155 0x0051A100] used as number of valid lordValuesArray entries
        int lordTargetCount; // 0x0002C864 length: 4
        // [155 0x0051A100] set to count of unassigned lordValuesArray entries
        int lordTargetsAvailable; // 0x0002C868 length: 4
        AttackInfoSubArrayElement1 lordValuesArray[917]; // 0x0002C86C length: 14672
        undefined1 padding_0x301bc[4]; // 0x000301BC length: 4
        // Phantom record-0 image part A (+0x301C0..+0x306FC = record +0x0..+0x53C: attackedPlayerID, hack1-3, start
        // of the hack list). playerInfo is 1-based: record p lives at 0x1793514 + p*0x177BC = AttackInfo+0x301C0 +
        // p*0x177BC (p>=1, i.e. playerInfo[p-1] at +0x4797C). Every access to the replaced fields uses a base
        // register = p*0x177BC (REC), i.e. they are fields of AttackInfoSubElement seen through the non-existent
        // record 0; none is accessed absolutely or by a wave/tribe index. The real globals around them
        // (currentAttackWaveSlot, attackWave*, support/tent points, createTribeAmount, people*, tribeIDArray...)
        // are accessed absolutely/indexed and stay. Struct size is preserved; the record meanings remain in
        // AttackInfoSubElement (offset = AttackInfo offset - 0x301C0).
        byte record0ImageUnused_0x301c0[1340]; // 0x000301C0 length: 1340
        // [201 0x0042C620] incremented and wrapped to 1 after 49, then used as the attack-wave slot index for
        // initializeAttackWaveSlot and attackWavePlayerIDArray
        int currentAttackWaveSlot; // 0x000306FC length: 4
        // [154 0x00518350] per-wave state; 6 = finished, set to 3 when attacker assigned
        int attackWaveState[50]; // 0x00030700 length: 200
        int attackWaveTicker[50]; // 0x000307C8 length: 200
        // [160 0x00520F70] read as wave liveness then cleared to 0 after each wave is processed
        byte waveTribeCountThisTick[50]; // 0x00030890 length: 50
        // [158 0x0051D7F0] incremented per wave for tribes whose percentageMovingUnk < 1;
        // initializeOrAdvanceAttackWave compares it against nof_tribes-5 to advance the wave
        byte nofStationaryTribesPerWave[50]; // 0x000308C2 length: 50
        byte attackWavePlayerIDArray[50]; // 0x000308F4 length: 50
        // byte[wave][10]; indices 0-4,8 count catapult/trebuchet/ram/tower/shield/fire ballista (verified base in
        // 227); not a score.
        byte waveSiegeEngineCounts[50][10]; // 0x00030926 length: 500
        // Per attack-wave counter (index = wave slot 0..49): incremented on each delayed target assignment and
        // passed as first argument to aiRecomputeAttacks; reset to 0 when the wave becomes state 4 via
        // canKeepReachSignpostZone. (The recountAttackTroopValue usage is an alias for aiTribeSizesPerTribeType at
        // 0x30B80, not this array.)
        short attackWaveRecomputeStep[50]; // 0x00030B1A length: 100
        undefined1 padding_0x30b7e[2]; // 0x00030B7E length: 2
        TribeSizesPerTribeType aiTribeSizesPerTribeType; // 0x00030B80 length: 160
        int supportPoints; // 0x00030C20 length: 4
        int supportPointsNext; // 0x00030C24 length: 4
        AttackInfoSubArrayElement3 supportPointsArray[201]; // 0x00030C28 length: 6432
        int tentPoints; // 0x00032548 length: 4
        int tentPointsNext; // 0x0003254C length: 4
        AttackInfoSubArrayElement3 tentPointsValues[216]; // 0x00032550 length: 6912
        undefined1 padding_0x34050[16]; // 0x00034050 length: 16
        // Phantom record-0 image part B (+0x34060..+0x41F70 = record +0x3EA0..+0x11DB0: min layer values,
        // stone/scale/town/gate/moat counters and lists). playerInfo is 1-based: record p lives at 0x1793514 +
        // p*0x177BC = AttackInfo+0x301C0 + p*0x177BC (p>=1, i.e. playerInfo[p-1] at +0x4797C). Every access to the
        // replaced fields uses a base register = p*0x177BC (REC), i.e. they are fields of AttackInfoSubElement seen
        // through the non-existent record 0; none is accessed absolutely or by a wave/tribe index. The real globals
        // around them (currentAttackWaveSlot, attackWave*, support/tent points, createTribeAmount, people*,
        // tribeIDArray...) are accessed absolutely/indexed and stay. Struct size is preserved; the record meanings
        // remain in AttackInfoSubElement (offset = AttackInfo offset - 0x301C0).
        byte record0ImageUnused_0x34060[57104]; // 0x00034060 length: 57104
        int createTribeAmount; // 0x00041F70 length: 4
        // 250 {engineerBuildingType, engineerCount} entries filled by placeSiegeTentsAndAssignEngineers (count in
        // createTribeAmount); each entry creates an AITT_ENGINEERS tribe and places that siege tent/tunnel.
        EngineerBuildingAndCountPair siegeTentPlan[250]; // 0x00041F74 length: 2000
        // Tribe ID found by findTribeWithMoatAttackBehavior (AI tribe with behaviour STBT_0x3F7; also sets
        // TroopValueState.x/y to its target); reset in aiRecomputeAttacks2.
        int moatAttackTribeId; // 0x00042744 length: 4
        int people1; // 0x00042748 length: 4
        // [155 0x0051A0C0] used as number of valid peopleValuesArray entries max 999
        int peopleTargetCount; // 0x0004274C length: 4
        // [155 0x0051A0C0] set to count of unassigned peopleValuesArray entries
        int peopleTargetsAvailable; // 0x00042750 length: 4
        AttackInfoSubArrayElement1 peopleValuesArray[312]; // 0x00042754 length: 4992
        undefined1 padding_0x43ad4[12]; // 0x00043AD4 length: 12
        // Phantom record-0 image part C (+0x43AE0..+0x465E4 = record +0x13920..+0x16424: wide1-3 and the wide
        // list). playerInfo is 1-based: record p lives at 0x1793514 + p*0x177BC = AttackInfo+0x301C0 + p*0x177BC
        // (p>=1, i.e. playerInfo[p-1] at +0x4797C). Every access to the replaced fields uses a base register =
        // p*0x177BC (REC), i.e. they are fields of AttackInfoSubElement seen through the non-existent record 0;
        // none is accessed absolutely or by a wave/tribe index. The real globals around them
        // (currentAttackWaveSlot, attackWave*, support/tent points, createTribeAmount, people*, tribeIDArray...)
        // are accessed absolutely/indexed and stay. Struct size is preserved; the record meanings remain in
        // AttackInfoSubElement (offset = AttackInfo offset - 0x301C0).
        byte record0ImageUnused_0x43ae0[11012]; // 0x00043AE0 length: 11012
        int tribeIDArraySize; // 0x000465E4 length: 4
        // [154 0x00518870] counts tribes that received the behaviour type
        int assignedTribeCount; // 0x000465E8 length: 4
        int tribeIDArray[50]; // 0x000465EC length: 200
        int field127657_0x466b4[50]; // 0x000466B4 length: 200
        // [154 0x00518380] rank of tribeType in the selected priority table; 12 = excluded
        int tribeTypePriorityRank[50]; // 0x0004677C length: 200
        undefined1 padding_0x46844[200]; // 0x00046844 length: 200
        // per attack wave index into signpost/map-edge spawn entries (2 batches agree)
        int attackWaveSignpostIndex; // 0x0004690C length: 4
        undefined1 padding_0x46910[196]; // 0x00046910 length: 196
        // Signpost index chosen for the current attack wave by initializeAttackWaveSlot; WildlifeState flood fills
        // / updateNofFpoints start from signpostEntryData[this].
        int activeAttackSignpostIndex; // 0x000469D4 length: 4
        // Incremented every tick a wave is in delayed target assignment (executeDelayedAttackWaveTargetAssignment),
        // reset on wave-slot init and map load; playRandomAmbientMusic plays 'the enemy has breached the walls'
        // (General_Warning15) only while it equals 1 and buildingDamageEventCount > 0, then sets it to 2.
        int breachWarningGate; // 0x000469D8 length: 4
        // Incremented by calculateUnitMovementSpeed for each live AI-player unit standing on another owner's keep
        // (building types 0x29..0x2C); playRandomAmbientMusic clears it and plays 'the enemy are inside the castle'
        // (General_Warning4, 90 s cooldown) when non-zero.
        int enemyUnitsOnKeepCount; // 0x000469DC length: 4
        // Incremented in TileMapState::processDamageToBuilding for each damage application; > 0 enables the wall-
        // breach warning; reset on wave-slot init and map load.
        int buildingDamageEventCount; // 0x000469E0 length: 4
        int knights; // 0x000469E4 length: 4
        int ranged; // 0x000469E8 length: 4
        undefined1 padding_0x469ec[8]; // 0x000469EC length: 8
        int tilemapOffset; // 0x000469F4 length: 4
        undefined1 padding_0x469f8[3972]; // 0x000469F8 length: 3972
        // 1-based array (playerID is always 1 to 8)
        AttackInfoSubElement playerInfo[8]; // 0x0004797C length: 769504

    } AttackInfo;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(AttackInfo) == 1062748, AttackInfo);
} // namespace Map
} // namespace OpenSHC
