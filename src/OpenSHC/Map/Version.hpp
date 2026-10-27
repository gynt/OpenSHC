/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Version.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Version {

        /**
         * Map-version upgrade step: sets DAT_CurrentEntityID to 3000 (the entity-slot loop end value).
         */
        void __cdecl UpgradeSetCurrentEntityID3000();

        /**
         * Map-version upgrade step: for every live entity (logicalState 2) of type ET_FLAG_1..4, copies the short
         * field following entityType into an int field 0x22 bytes before entityType (flag color). Also sets
         * DAT_CurrentEntityID = 3000.
         */
        void __cdecl SetFlagEntityColor();

        /**
         * Map-version upgrade step: deletes all live seagull entities (slots 1..2999), then zeroes the 10000-byte
         * global block 0x23FA1D4..0x23FC8E3 in 100-byte chunks.
         */
        void __cdecl DeleteSeagull();

        /**
         * Map-version upgrade step: for live entities in slots 1..24, unlinks the entity from its tile linked list
         * and re-runs processEntityHitBuildingOrUnit on it.
         */
        void __cdecl UpgradeFirst25Entities();

        /**
         * Map-version upgrade step: for every existing building at full health (currentHealth == maxHealth), sets
         * both currentHealth and maxHealth to the default BuildingHP of its type.
         */
        void __cdecl SetUndamagedBuildingHealthToValue();

        /**
         * Map-version upgrade step: for building IDs 1..8 recomputes barracks and mercenary-post campground
         * positions.
         */
        void __cdecl UpgradeFirst9Buildings();

        /**
         * Map-version upgrade step: for every existing building widens the short uidPlaced into the int field
         * uidWhenPlaced (+0x2A8).
         */
        void __cdecl UpgradeBuildingField1();

        /**
         * Map-version upgrade step: for every existing building re-initialises flag1 (+0x108) from
         * BuildingDefinedData.buildingFlag1PerType[type] and flag2 (+0x28C) from field24_0x237c[type].
         */
        void __cdecl UpgradeBuildingFlag1();

        /**
         * Map-version upgrade step (stack arg = map version): for every existing building reloads spriteSheetID,
         * visuallyActiveSpriteID, gfxOffset/2/3, unknownFlag4, spriteOffsetX/Y, animAdvanceThrottle and spriteID2
         * from per-type BuildingDefinedData tables. spriteID is also reset except for types
         * 0x27,0x42,0x5B,0x64,0x65,0x68, and for type 1 only when version < 0x8C. If at full health, resets
         * current/max health to the type's default HP; sets oldVisualActiveState (+0xCE) to -1.
         */
        void __cdecl UpgradeBuildingProperties1(int version);

        /**
         * Map-version upgrade step: zeroes flagonsOfAleOrCheeseOrReleaseDogs (+0x2B0, the cheese counter) of every
         * existing dairy farm.
         */
        void __cdecl SetDairyCheeseToZero();

        /**
         * Map-version upgrade step: for every existing tower building (BT_TOWER2..BT_TOWER5) calls
         * TileMapState::upgradeTowerLogicLayer with its building ID.
         */
        void __cdecl UpgradeTowerLogicLayer();

        /**
         * Map-version upgrade step: numbers all existing hovels sequentially (0,1,2,...) in buildMonthOrBuildOrder
         * (+0x2BA) and zeroes hovelVisualStyle (+0x284, written as two shorts).
         */
        void __cdecl SetHovelBuildOrder();

        /**
         * Map-version upgrade step: sets each existing building's buildingTypeBasedEmployeeCount to
         * EmployeeCountPerBuildingType[type].
         */
        void __cdecl SetBuildingsEmployeeCountToValue();

        /**
         * Map-version upgrade step: for every existing building zeroes field203_0x288 and field185_0x264.
         */
        void __cdecl UpgradeBuildingField2();

        /**
         * Map-version upgrade step: in solitary (single-player) game mode, zeroes playerColorUnk of every existing
         * building.
         */
        void __cdecl UpgradeSolitaryMapBuildingField3();

        /**
         * Map-version upgrade step: for every existing dairy farm calls TileMapState::markBuildingFootprintFlag(x,
         * y, 10).
         */
        void __cdecl UpgradeLogicAndDisplayLayerForDairyFarms();

        /**
         * NAME? Iterates ALL building slots (loop bound 0x1124DE2, same as the other full-array loops), not the
         * first 10, and rebuilds rather than destroys: for each existing drawbridge clears its drawbridge water and
         * display flags/entities, saves owner, x, y and buildingVariation, wipes the 0x32C-byte building record and
         * places a new drawbridge (mapper 0x69 M_MAPPER_DRAWBRIDGE, arg 5, saved variation) at the same position.
         */
        void __cdecl UpgradeDestroyDrawbridgesInFirst10Buildings();

        /**
         * Map-version upgrade step: converts every existing pitch-ditch building into a pitch-ditch tile object:
         * clears building/logic-bit 0x400/building-was layers at its tile, restores HeightLayer from
         * DefaultHeightLayer, calls placePitchDitch(owner, x, y), updateWalkAndPathLayer(4, x, y) and wipes the
         * 0x32C-byte building record.
         */
        void __cdecl UpgradePitchDitchBuildingIntoPitchDitchObject();

        /**
         * Map-version upgrade step: for every existing killing-pit building zeroes killingPitField (+0x11C).
         */
        void __cdecl UpgradeKillingPitField();

        /**
         * Map-version upgrade step: zeroes field241_0x2c6 of every existing building.
         */
        void __cdecl UpgradeBuildingField4();

        /**
         * Map-version upgrade step: zeroes the 0x32C-byte building records of slots 1000..1999 (0x105E914 up to the
         * end of the buildings array).
         */
        void __cdecl UpgradeClearBuildings1000AndHigher();

        /**
         * Map-version upgrade step: for each stables building (type 0x23) resets its linked-knight count byte
         * (+0x2A7, typed randomOutpostField), then scans unit slots 0..2499 for European knights whose origin-
         * stables index equals this building's index and whose stored stables UID (unit+0x3E0) equals the building
         * uid; stores each knight's slot index in insideUnitID[n] and its uid in insideUnitUID[n], incrementing the
         * count and stopping at 4.
         */
        void __cdecl UpgradeKnightsAndStables();

        /**
         * Map-version upgrade step: for every existing European or Arabian outpost zeroes randomOutpostField
         * (+0x2A7).
         */
        void __cdecl UpgradeOutpostField();

        /**
         * If lossValue is negative, adds its magnitude to currentPlayerUnitValueLostToPlayer[playerID]; non-negative
         * values are ignored.
         */
        void __cdecl UpdateUnitLossData(int lossValue, int playerID);

        /**
         * Adds the given count to DAT_DestroyedBuildingsCountHistory[0] (current destroyed-building tally).
         */
        void __cdecl UpdateDestroyedBuildingCountData(int destroyedCount);

        /**
         * For players 1..8 validates two (unitID, unitUID) reference pairs in player data (lady and jester per the
         * existing name): if the stored UID no longer matches DAT_UnitsState.units[id].uid, clears both id and uid.
         */
        void __cdecl ValidateLadyAndJesterUnitRefs();

        /**
         * Map-version upgrade step: copies each player's storedPopularityPercent into someCount44 and sets all
         * euro/merc recruitable flags (and the euroRecruitableCopy fields) to 1.
         */
        void __cdecl InitPopularityAndRecruitableDefaults();

        /**
         * Map-version upgrade step: wrapper calling GameStateStructures::resetTeams on DAT_GameState.
         */
        void __cdecl ResetTeams();

        /**
         * Map-version upgrade step: copies the skirmish lobby setup from DAT_SkirmishLobbySetupStructureLongMapName
         * into SEC_SkirmishLobbySetupStructure (map name string, per-slot group/round-table order/AI/AI variation
         * arrays for 9 slots, slot positions, advantage settings, lord types, popularity, map selection).
         */
        void __cdecl UpgradeOldSection1124();

        /**
         * Map-version upgrade step: for every tree slot of type 1..4 reloads gmOriginX/gmOriginY from the GM file
         * header of its sprite, then removes the tree when PathFindingState::findNoTreeInRange(2, x, y) returns
         * FALSE.
         */
        void __cdecl UpdateFixTrees2();

        /**
         * NAME? No rock-type test: for rock slots 1..3999 with a nonzero existence short (+0xC), removes the rock
         * when OrganismLayer at its tile is not (rockID + 2000) or the tile lacks logic flag 0x80, i.e. it purges
         * orphaned/inconsistent rocks.
         */
        void __cdecl UpgradeRemoveOrphanedRocks();

        /**
         * Map-version upgrade step: for every tree with state 2 and type 0x10..0x13, sets its state to 4, sets
         * DAT_CurrentTreeID and runs the per-type UpdateTree callback.
         */
        void __cdecl UpdateTreesOfCertainTypes();

        /**
         * NAME? Zeroes the 32-byte rock records 0xF88930..0xF9832F, which are rock slots 2000..3999 of the
         * 4000-entry rocks array (rocks[0] = 0xF78F30), not slots beyond 1000.
         */
        void __cdecl UpgradeClearRockSlots2000Plus();

        /**
         * Map logic upgrade: for every tile, sets Logic2Layer to 4 where height is 0x50 and to 8 where height is
         * 0x82.
         */
        void __cdecl UpgradeMapLogicToVersion_125();

        /**
         * Map logic upgrade: for every tile with MiscDisplayLayer flag 0x20, clears the flag unless BuildingLayer
         * at that tile (read via fixed offset -0xFF2D0 bytes) refers to a large/small gatehouse or wood gate type
         * (0x2D..0x2F). Loop unrolled 6x.
         */
        void __cdecl UpgradeMapLogic_ClearStaleGatehouseFlags();

        /**
         * Map logic upgrade: for every tile with logic flag 0x800 whose height is not above its default height,
         * resets height to the default and clears logic bits 0x410B00. Loop unrolled 5x.
         */
        void __cdecl UpgradeMapLogicToVersion_Unknown2();

        /**
         * Map logic upgrade: for every moat-flagged tile (logic 0x40000000) whose owned moat is at stage 2 with
         * fillProgress 4, sets tile height to 0.
         */
        void __cdecl UpgradeMapLogicToVersion_128();

        /**
         * Map logic upgrade to version 102: the first 0x27420 bytes of LogicLayer still hold the old 16-bit logic
         * values; copies them to a 160800-byte stack buffer with LowLevelMemory::copyData(size, src, dst), then
         * widens each ushort into the 32-bit LogicLayer entry (80400 tiles).
         */
        void __cdecl UpgradeMapLogicToVersion_102();

        /**
         * Map logic upgrade: builds DefaultHeightLayer from HeightLayer; tiles with logic 0x200 or 0x100 get
         * height-0x62 / height-0x5A. For tiles with 0x800 it intends to average the adjusted heights of 8
         * neighbours lacking 0x800, but (confirmed in machine code, original bug) the sample index is
         * directionTranslationMatrix[row][dir] + dirIndex instead of + tile, and the result (8 if no samples) is
         * written to DefaultHeightLayer[8] instead of the current tile, so such tiles keep DefaultHeight = Height.
         */
        void __cdecl UpgradeMapLogicToVersion_120();

        /**
         * Map logic upgrade: zeroes height and default height of tiles with logic flag 1, and of tiles lacking
         * logic 0x100000 but having Logic2 flag 0x20; clears logic bits 0x4C on all tiles.
         */
        void __cdecl UpgradeMapLogicToVersion_145();

        /**
         * Map logic upgrade: caps DefaultHeightLayer at 0x9C; for tiles whose default height exceeded 0x9C, lowers
         * HeightLayer by the same excess (adds 0x9C - default, byte arithmetic) and sets the default to 0x9C.
         */
        void __cdecl UpgradeMapLogicToVersion_147();

        /**
         * Map logic upgrade: for every owned moat at stage 1 whose tile has logic flag 0x40000000, sets stage to 2
         * and fillProgress to 4.
         */
        void __cdecl UpgradeMapLogicToVersion_Unknown3();

        /**
         * Tribes-state upgrade to v142: for each active tribe (tribeState != 0) with attackWave < 1, sets
         * tribeBehaviorType (+0x28) to 0.
         */
        void __cdecl UpgradeMapTribesStateVersionTo_142();

        /**
         * Tribes-state upgrade: for each active tribe, sets the shorts at +0x280/+0x282 to size/2 and size*2 (if
         * size >= 31 it first trims the tribe to 30 units and uses 15/60) and zeroes the short at +0x284.
         */
        void __cdecl UpgradeMapTribesStateVersionTo_Unknown1();

        /**
         * Tribes-state upgrade: for each tribe with nonzero tribeState, recomputes whether it contains any units.
         */
        void __cdecl UpgradeMapTribesState_RecomputeContainsAnyUnits();

        /**
         * Units upgrade to v117: for every normal unit sets the speed short at +0x34C from
         * UNIT_MOVEMENT_SPEED_ARRAY[type], maps facingDirection 0xF to 4, and zeroes the short at +0x418 for non-
         * assassins. Sets DAT_CurrentUnitSlotID = 2500.
         */
        void __cdecl UpgradeMapUnitsTo_117();

        /**
         * Units upgrade: for every normal unit sets the short before unknownMovementRelated_0x2d2 from
         * UNIT_CAN_MELEE[type], clamps unknownMovementRelated_0x2d2 > 1 to 0, and if health >= maxHealth resets
         * both to BASE_HP[type], stores the health percent (+0x2D4) and percent/10 into healthbar.
         */
        void __cdecl UpgradeMapUnitsTo_UnknownVersion2();

        /**
         * Units upgrade to v114: zeroes calculatedOwnerPlayerIndex of every normal unit.
         */
        void __cdecl UpgradeMapUnitsTo_114();

        /**
         * Units upgrade to v112: for every normal unit copies workplaceBuildingID_1 into the short 0x60 bytes later
         * (+0x398).
         */
        void __cdecl UpgradeMapUnitsTo_112();

        /**
         * Units upgrade to v100: for every normal unit with a workplace, writes the unit's slot ID and uid into
         * that building's unitRefID/unitRefUID.
         */
        void __cdecl UpgradeMapUnitsTo_100();

        /**
         * Units upgrade: for every normal unit reloads per-type defaults: spriteID (except children), climb
         * ability, SomeUnitStatMatrix4 value, sprite origin X/Y from the GM header and derived draw offsets,
         * graphic size, enemy notice range and movable flag.
         */
        void __cdecl UpgradeMapUnits_ReloadUnitTypeDefaults();

        /**
         * Units upgrade to v122: for every normal unit copies targetedUnitID__OR__engineerMannedSiegeEngineRef and
         * the low short of the following int into the two shorts 0x4A/0x4C bytes later.
         */
        void __cdecl UpgradeMapUnitsAttackTileLogicTo_122();

        /**
         * Units upgrade to v130: for every normal cow zeroes the short at unit+0x3B4 (the field that holds the
         * operator count for siege engines).
         */
        void __cdecl UpgradeMapUnitsTo_130();

        /**
         * Units upgrade to v149: zeroes shootBeforeStop of every normal unit.
         */
        void __cdecl UpgradeMapUnitsTo_149();

        /**
         * Units upgrade to v154: sets the short at unit+0x362 to 20 for every normal catapult and trebuchet.
         */
        void __cdecl UpgradeMapUnitsTo_154();

        /**
         * Units upgrade to v155: zeroes killedFlagUnk of every non-invisible unit.
         */
        void __cdecl UpgradeMapUnitsTo_155();

        /**
         * Units upgrade to v169 (non-solitary games only): for every lord owned by an AI player (no human ID,
         * currentAIArray != 0) sets the short at unit+0x44A from MaxLordHealthMapping[aiType-1].aiTypeA and, if
         * health == maxHealth, scales both by maxHealthMultiplier percent. Loop unrolled 3 units per iteration
         * (0x37 = UT_LORD).
         */
        void __cdecl UpgradeMapUnitsLordHealthTo_169();

        /**
         * Units upgrade to v170: for every unit slot of a siege-engine type (no logicalState check), walks its
         * operator list (unit IDs at +0x314, uids at +0x31C, count at +0x3B4) and switches operators whose uid
         * still matches and that are in US_LOOK_AROUNDUnk to US_AIM_WEAPONUnk.
         */
        void __cdecl UpgradeMapUnitsTo_170();

    } // namespace Version
} // namespace Map
} // namespace OpenSHC
