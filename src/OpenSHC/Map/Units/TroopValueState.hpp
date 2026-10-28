/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/TroopValueState.hpp'
*/

#pragma once

#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/IO/PackagedFileMagicNum.hpp"
#include "OpenSHC/Map/AttackInfo.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::AI::Tribes::AITribeType;
        using OpenSHC::Commands::MappersEnum;
        using OpenSHC::IO::PackagedFileMagicNum;
        using OpenSHC::Map::AttackInfo;
        using OpenSHC::Map::Units::SomeTribeBehaviorType;
        using OpenSHC::Map::Units::UnitInstructionType;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

        // SIZE: 0x00103768
        class TroopValueState {
        public:
            undefined4 x; // 0x00000000 length: 4
            undefined4 y; // 0x00000004 length: 4
            undefined4 tile; // 0x00000008 length: 4
            AttackInfo attackInfo; // 0x0000000C length: 1062748

        private:
            TroopValueState(TroopValueState const&);
            void operator=(TroopValueState const&);

        public:
            TroopValueState() {};
            ~TroopValueState() {};

            // Constructor
            /**
             * Constructor of the global TroopValueState: calls clearAttackInfo and returns &DAT_TroopValueState.
             */
            TroopValueState* Constructor_TroopValueState();

            /**
             * Zero-fills the whole TroopValueState.attackInfo block (0x10375C bytes) and resets a few fields
             * explicitly; sets inv_count=1 and aiTroops=-1.
             */
            void clearAttackInfo();

            /**
             * Resets attack-wave slot param_1: clears value3Array01/attackWaveTicker[slot], someIntArray2[slot-1]
             * and its 10-byte block at 0x1793C7A+slot*10, resets wave counters and the per-player playerInfo
             * fields, then stores the entry signpost (unknownSignpostRelatedArray[slot] and field128056_0x469d4):
             * param_2-1 if param_2 is a 1-based signpost number <= countActiveSignposts, otherwise a random
             * accessible signpost. The decompiler's unaff_EBX is really param_2 ([esp+0x14] in machine code); EBX
             * holds the random pick.
             */
            void initializeAttackWaveSlot(int waveSlot, int signpostNumber);

            /**
             * For wave slot param_1 with tribes: finds the first tribe in state 2 owned by a non-zero player other
             * than the local player and makes that owner the wave's attacker (attackWavePlayerIDArray, attacker,
             * ticker=10000, state=3, value10=10), returning TRUE. If none (or the wave has no tribes) clears
             * nof_tribes/unknownByteArray02 for the slot and returns FALSE.
             */
            BOOLEnum searchTribeWithProperties(int waveSlot);

            /**
             * Returns TRUE if all 50 attack-wave slots are either empty (nof_tribes==0) or in state 6 (finished),
             * FALSE otherwise. Matches OpenSHC exactly.
             */
            BOOLEnum isAttackWaveComplete();

            /**
             * Picks a 12-entry tribe-type priority table (.data 0xB4C830..0xB4D0A0) from the behaviour type, resets
             * all ranks to 12, and collects non-human live tribes (state not 0/3) of attackWave not yet tagged with
             * attackInfo.someCounter1 and not in siege-construction behaviours (0x410/0x415) into
             * attackInfo.tribeIDArray. Only if shrinkSize > 0 and tribeSizeSumLimit > 0: bubble-sorts them by the
             * rank of their tribeType in the table, stores each rank (12 = not listed) in
             * tribeRelatedArrayValue0UpTo12, re-marks as 12 every tribe after the cumulative member count has
             * exceeded tribeSizeSumLimit, and truncates the list to shrinkSize.
             */
            void collectWaveTribesSortedByTypePriority(
                int attackWave, int shrinkSize, int tribeSizeSumLimit, SomeTribeBehaviorType someTribeTypeIdentifier);

            /**
             * For every collected wave tribe whose priority rank is < 11, assigns tribeBehaviorType, a sequential
             * someCounter1, attackInfo_someCounter1 and a staggered someUpdateUpperLimit = (listIndex+1)*off2 +
             * off1; excluded tribes get tribeBehaviorType2 if non-zero. Resets each tribe's tick counter and stores
             * the number of assigned tribes in unknownTribeCounterRelated.
             */
            void applyTribeBehaviorTypes(
                SomeTribeBehaviorType tribeBehaviorType, SomeTribeBehaviorType tribeBehaviorType2, int off1, int off2);

            /**
             * Assigns behaviour type behaviorType to at most 5 collected wave tribes (priority rank < 11) whose
             * leader's path-connection area can reach attackInfo.lordConnectionArea, giving each the wave's
             * someCounter1 (attackInfo_someCounter1), a sequential someCounter1 slot (0..4) and a staggered
             * behaviorDelayTicks = (listIndex+1)*delayStep + delayBase; resets behaviorTickCounter of every visited
             * tribe except the 5th assigned one (returns right after it). param_2 is never read (machine code reads
             * only args 1, 3 and 4). NAME? 'Nearby' is really 'reachable'.
             */
            void assignBehaviorTypeToNearbyTribes(
                SomeTribeBehaviorType param_1, undefined4 param_2, short param_3, short param_4);

            /**
             * Clears Tribe.tribeID (link to an attack tribe) on every tribe owned by playerID (<1 -> 2), then walks
             * attackInfo.tribeIDArray for wave attackID and returns early as soon as an entry has
             * tribeRelatedArrayValue0UpTo12 > 10 or already has a valid support link (field56_0x1f2 != 0 and uid2
             * == that tribe's uid). For each processed tribe it sets tribeBehaviorType, someUpdateUpperLimit =
             * (i+1)*step + base, copies attackInfo.someCounter1 and resets unknownAttackRelatedUpdateCounter, then
             * links it to the first active, unlinked (tribeID == 0) tribe of the same owner with tribe type
             * 0x16/0x17 (stone-throwing siege engines, not in AITribeType), or else - unless
             * value3Array01[attackID] == 4 - to the first unlinked archer/crossbow tribe: stores the support tribe
             * index in field56_0x1f2, its uid in uid2, and the attack tribe index in the support tribe's tribeID.
             */
            void assignBehaviorTypeAndLinkSupportTribe(
                int param_1, int param_2, SomeTribeBehaviorType param_3, undefined4 param_4, undefined4 param_5);

            /**
             * Counts active tribes (tribeState not 0/3) of non-human owners (currentPlayerFullIDArray[owner] == -1)
             * assigned to attackID, split by getTribeAliveStatus >= 50 (healthy) or < 50 (dying). Returns TRUE if
             * healthy*100/total >= leDyingPerc; with no such tribes returns TRUE iff leDyingPerc <= 100.
             */
            BOOLEnum isLessThanPercentageOfTribesInAttackDying(int attackID, int leDyingPerc);

            /**
             * Debug overlay: prints the AI attack-planning state as text rows from (x+2, y): zones/connections,
             * keep position, fpoints/inv count, the attacker's per-player hack/scale/town/gate/moat/wide list
             * header values (and the Stone counter), lord/high/arch/people stats, archer/support/tent points, AI
             * troop counts by tribe type, player 1's kills/losses and the total troop value of players 0..8.
             */
            void renderAttackInfoDebugOverlay(int x, int y, int width, int height);

            /**
             * Computes the per-type troop counts of the next AI attack wave (attackInfo._134972_4_.._135004_4_)
             * from a strength tier field86974_0x20f74 (bands <6, 6-9, 10-19, 20-29, >=30) and the available
             * spearmen/macemen, pikemen/swordsmen, laddermen and engineers counts; _134972_4_ is always 3,
             * _134992_4_ = engineers, and _134984_4_ is finally raised to at least field86627_0x20e04.
             */
            void computeAttackWaveTroopComposition();

            /**
             * Rebuilds tribes[tribeID].rallyPointArray: for every active tribe of a non-human owner with tribe type
             * 0x16/0x17 whose selectionTargetUnitID unit still has stoneAmmunition > 0, appends the
             * computeNextRallyPointDestination-adjusted position of that unit. Then clamps currentRallyPointIndex
             * into [0, rallyPointCount) (0 when out of range).
             */
            void buildRallyPointsFromSiegeUnits(int tribeID);

            /**
             * Finds the (tribes[tribeID].someCounter1 + 1)-th active laddermen tribe of a non-human owner and sets
             * rally point 0 of tribe tribeID to the computeNextRallyPointDestination-adjusted position of that
             * laddermen tribe's selectionTargetUnitID unit; does nothing if there are not enough such tribes.
             */
            void setRallyPointForLaddermenTribe(int tribeID);

            /**
             * Initializes attack zone data from the signpost assigned to attack wave attackID
             * (attackInfo.attackWaveSignpostIndex[attackID]): stores the path-connection id (startCon), AI zone
             * (startZone) and zone size of its tile, resets biggestZone, sets unknownOne_0x20f90 = 1 and stores the
             * connection id of the current player's campground tile in keepCon.
             */
            void initializeAttackZoneSearch(int attackID);

            /**
             * Zeroes attackInfo.targetedBuildingTilesArray (16000 bytes) and fills it with the targetBuildingTile
             * of every unit with state ULS_NORMAL, isSelectable_OR_matchTime != 0, owner == playerID, a non-zero
             * target tile and type other than UT_A_SLAVE, stopping at 4000 entries. The decompiled owner comparison
             * against unaff_EDI is an artefact: the code compares with the playerID stack argument.
             */
            void recomputeTargetedBuildingTilesArray(int playerID);

            /**
             * Returns TRUE if tile is contained in attackInfo.targetedBuildingTilesArray (first
             * targetedBuildingTilesArraySize entries), else FALSE.
             */
            BOOLEnum getTileInTargetedBuildingTiles(int tile);

            /**
             * If attackedPlayerID has a campground, scores the 16-byte entries {tile, ..., score, ...} of
             * attackingPlayerID's per-player siege target lists from a per-player byte tile layer at 0x1EE2998 +
             * player*0x13A10 (hack list: attackedPlayerID's layer; other lists: the player stored at hack header
             * -0x10). Hack: tracks the minimum value, score = value only if no correctly-oriented ladder is on the
             * tile, value > 0, min < 50 and value < min+15 (counted as free in the record's +0xC counter), else
             * 9999; scale/wide: 0 if value <= 5 else 9999; town: value (100 if 0); gate: tracks the minimum, then 0
             * if value <= 10 (when min <= 10) or <= 20 (otherwise), else 9999; moat: value x1 (<=10), x2 (<=15), x3
             * (<=20), x4 (<=25), x5 (<=50), x6 (<=70), 9999 if 0 or > 70.
             */
            void computeSiegeSpotScores(int attackedPlayerID, int attackingPlayerID);

            /**
             * For the unit's owner, picks the unassigned (unitID == 0) hack (wall-breaching) entry with score <
             * 9999 minimizing distance(unit, tile2) + score*8; stores its tile and tile2's x/y in
             * DAT_TroopValueState.tile/x/y, marks the entry as taken by unitID and returns its tile2 (0 if none).
             */
            undefined4 findEnemyWalls(int unitID);

            /**
             * Counts the player's scale (ladder) entries with score < 5999 that are unassigned (or all of them when
             * one != 0) and stores the count in the scale list's free-slot field (block+0x3EB8, printed as the
             * third Scale value in the debug overlay).
             */
            void setScale3(int one, int playerID);

            /**
             * For the unit's owner, picks the nearest (distance to tile2) unassigned scale (ladder) entry with
             * score < 5999; stores its tile and x/y in DAT_TroopValueState.tile/x/y, assigns the entry to unitID
             * and returns its tile2 (0 if none).
             */
            undefined4 findNearestAvailableScalePoint(int unitID);

            /**
             * Counts the player's town (building) entries that are unassigned (or all when includeAssigned != 0)
             * and stores the count in the town list's free-slot field (no score filter).
             */
            void setTown2(int includeAssigned, int playerID);

            /**
             * For the unit's owner, picks the unassigned town (building) entry minimizing distance(unit, tile2) +
             * (100 - score)*2 (higher layer value preferred); stores its tile and x/y in
             * DAT_TroopValueState.tile/x/y, assigns the entry to unitID and returns its tile2 (0 if none).
             */
            undefined4 findEnemyBuildingsClosestToUnit(int unitID);

            /**
             * Sets attackInfo.peopleTargetsAvailable to the number of peopleValuesArray entries (of people2) that are unassigned,
             * or to all of them when includeAssigned != 0.
             */
            void countAvailablePeopleValueSlots(int includeAssigned);

            /**
             * Sets attackInfo.lordTargetsAvailable to the number of lordValuesArray entries (of lord3) that are unassigned, or to
             * all of them when includeAssigned != 0.
             */
            void countAvailableLordValueSlots(int includeAssigned);

            /**
             * Picks the unassigned peopleValuesArray entry whose tile2 is nearest to the unit; stores its tile and
             * x/y in DAT_TroopValueState.tile/x/y, assigns the entry to unitID and returns its tile2 (0 if none).
             */
            undefined4 calculateTile2PeoplValueClosestToUnit(int unitID);

            /**
             * Assigns unitID to the first unassigned lordValuesArray entry and returns its tile2 (also writing
             * tile2's x/y and the entry tile into DAT_TroopValueState); if all are taken, returns entry 0's
             * tile2/position without assigning. Returns 0 if there are no lord entries.
             */
            int findEnemyLord(undefined4 unitID);

            /**
             * Counts the player's gate entries with score < 5999 that are unassigned (or all when includeAssigned
             * != 0) and stores the count in the gate list's free-slot field.
             */
            void setGate2(int includeAssigned, int playerID);

            /**
             * For the unit's owner, picks the nearest unassigned gate entry (score < 5999, distance to tile2),
             * stores its tile and x/y in DAT_TroopValueState.tile/x/y, assigns it to unitID and returns its tile2.
             * If none is free, clears the unitID of all gate entries and searches again, returning the nearest gate
             * entry's tile2 (and setting tile/x/y) without assigning it; 0 if the list is empty or all scores are
             * >= 5999.
             */
            undefined4 findEnemyTowersOrGates(int unitID);

            /**
             * Counts the player's 'wide' entries with score < 5999 that are unassigned (or all when includeAssigned
             * != 0) and stores the count in the wide list's free-slot field.
             */
            void setWide3(int includeAssigned, int playerID);

            /**
             * The parameter named playerID is actually a unit ID (indexes units[] with stride 0x490, callers pass
             * unitID, stored as the entry's unitID). Picks the unassigned 'wide' entry (score < 5999) minimizing
             * distance(unit, tile2) + distance(tile2, campground of the player stored in the owner's hack-list
             * header); stores its tile and x/y in DAT_TroopValueState, assigns it to the unit and returns its tile2
             * (0 if none).
             */
            undefined4 findWideTargetClosestToUnitAndCamp(int playerID);

            /**
             * Counts the player's moat entries with score < 5999 that are unassigned (or all when
             * checkAgainstNonZero != 0) and stores the count in the moat list's free-slot field.
             */
            void setMoat3(int checkAgainstNonZero, int playerID);

            /**
             * For the unit's owner, picks the unassigned moat entry (score < 5999) minimizing distance(unit, tile2)
             * + score*8 (initial limit 100000); stores its tile and x/y in DAT_TroopValueState.tile/x/y, assigns it
             * to unitID and returns its tile2 (0 if none).
             */
            undefined4 calculateTile2MoatValueClosestToUnit(int unitID);

            /**
             * Calls findNearestFriendlyMoatTileForDigging(owner of unit, unitID, 2); if it returns a non-negative
             * tile, calls setXYBasedOnMoatID(tile, 2, unit x, unit y) and, when that returns > 0, copies
             * ALG_MoatXResult/ALG_MoatYResult/someMoatTile into DAT_TroopValueState.x/y/tile and returns that
             * value; otherwise returns 0.
             */
            int findNearestDiggableMoatPoint(int unitID);

            /**
             * Finds the first active tribe (tribeState != 0) of a non-human owner whose tribeBehaviorType is
             * STBT_0x3f7; copies its targetX/targetY into DAT_TroopValueState.x/y, stores the tribe index in
             * attackInfo.moatAttackTribeId and returns 1, else 0.
             */
            undefined4 findTribeWithMoatAttackBehavior();

            /**
             * Sets attackInfo.high3 to the number of high2ValuesArray entries (of high2) whose building has
             * unknownCounterTo10000_0x2b4 < 9999 and that are unassigned (or regardless of assignment when
             * includeAssigned != 0).
             */
            void countAvailableHighValueSlots(int includeAssigned);

            /**
             * Picks the unassigned high2ValuesArray entry (building counter < 9999) whose tile2 is nearest to the
             * tribe's selectionTargetUnitID unit; stores its tile and x/y in DAT_TroopValueState, writes that unit
             * ID into the entry's unitID and returns its tile2 (0 if none). The tribeID parameter is reused as the
             * loop index.
             */
            int calculateHigh2ClostestToTribeTargetUnit(int tribeID);

            /**
             * Sets attackInfo.arch3 to the number of arch2ValuesArray entries (of arch2) whose building has
             * unknownCounterTo10000_0x2b4 < 9999 and that are unassigned (or regardless of assignment when
             * includeAssigned != 0).
             */
            void countAvailableArcherValueSlots(int includeAssigned);

            /**
             * Picks the unassigned arch2ValuesArray entry (building counter < 9999) whose tile2 is nearest to the
             * tribe's selectionTargetUnitID unit; stores its tile and x/y in DAT_TroopValueState, writes that unit
             * ID into the entry's unitID and returns its tile2 (0 if none). The tribeID parameter is reused as the
             * loop index.
             */
            int calculateArch2ClosestToTribeTargetUnit(int tribeID);

            /**
             * Returns TRUE if buildingID appears in any of the 1000 high2ValuesArray entries (all, not only the
             * first high2), else FALSE.
             */
            BOOLEnum attackInfoHasHigh2Building(int buildingID);

            /**
             * Returns TRUE if buildingID appears in any of the 1000 arch2ValuesArray entries (all, not only the
             * first arch2), else FALSE.
             */
            BOOLEnum attackInfoHasArch2Building(int buildingID);

            /**
             * Grows the AIInfoLayer marking (AIInfoLayer is the byte array at 0x1EA7B68): for each tile marked 1
             * that has an unmarked cardinal neighbour (AIInfoLayer & 0xF == 0), calls
             * recomputeALGPathFindingTileMapUnk(6, nx, ny, 2) from the first such neighbour; then turns all 2-marks
             * into 1 and repeats the pass with range 10 (mark 2).
             */
            void expandAIZoneLayerStage1();

            /**
             * AIInfoLayer expansion stage 2: for each tile marked 2 that has an unmarked cardinal neighbour
             * (AIInfoLayer & 0xF == 0), calls recomputeALGPathFindingTileMapUnk(15, nx, ny, 4) from the first such
             * neighbour.
             */
            void expandAIZoneLayerStage2();

            /**
             * AIInfoLayer expansion stage 3: for each tile marked 4 that has an unmarked cardinal neighbour
             * (AIInfoLayer & 0xF == 0), calls recomputeALGPathFindingTileMapUnk(15, nx, ny, 8) from the first such
             * neighbour.
             */
            void expandAIZoneLayerStage3();

            /**
             * Searches the archer point slots (32-byte {x, y, tile, counterStamp, tribeID, tribeUID, timer, 0}
             * records, 1-based, tile field of slot 1 at attackInfo.field_0x1b678) for tile; returns the slot index
             * if found, else 0. Also records the first empty slot in attackInfo.archerPointsNext (0 if full).
             */
            int findOrReserveArcherPointSlot(int tile);

            /**
             * Maintains archer point slots: slots whose counter stamp differs from attackInfo.someCounter1 are
             * zeroed; current slots whose reserving tribe no longer matches its UID are zeroed, and their
             * reservation timer is decremented toward 0.
             */
            void pruneStaleArcherPoints();

            /**
             * If the tribe has no active ladderman, finds an archer point within 200 of its selectionTargetUnitID
             * unit (findArcherRelatedAttackInfoIndex); saves the previous slot in archerRelated2 and releases it,
             * reserves the new one (tribe id, uid, timer 3), stores it in Tribe.archerPointIndex and orders the tribe
             * to move to the slot's x/y. Returns the new slot or 0. The decompiler shows the 32-byte archer slots
             * as pairs of arch2ValuesArray elements past index 1000.
             */
            int claimArcherAttackPoint(int tribeID);

            /**
             * Searches supportPointsArray (1-based, 32-byte entries) for tile; returns the slot index if found,
             * else 0. Records the first empty slot in attackInfo.supportPointsNext (0 if full).
             */
            int getSupportPointIndex(int tile);

            /**
             * Maintains supportPointsArray: entries whose someCounter stamp differs from attackInfo.someCounter1
             * are zeroed; current entries whose tribe no longer matches its UID are zeroed, and their 'three'
             * reservation timer is decremented toward 0.
             */
            void pruneStaleSupportPoints();

            /**
             * Finds a support point within 200 of (x, y) for the tribe (findSupportPointIndex); saves the tribe's
             * previous support point in oldSupportPointIndex and releases it, reserves the new one (tribe id, uid,
             * timer 3), stores it in supportPointIndex and orders the tribe to move there. Returns the new index or
             * 0.
             */
            int assignTribeToSupportPoint(uint x, uint y, int tribeID);

            /**
             * Searches tentPointsValues (1-based, 32-byte entries) for tile; returns the slot index if found, else
             * 0. Records the first empty slot in attackInfo.tentPointsNext (0 if full).
             */
            int getSiegeIndexForTile(int tile);

            /**
             * Maintains tentPointsValues: entries whose counter stamp differs from attackInfo.someCounter1 are
             * zeroed; current entries whose tribe no longer matches its UID are zeroed, and their reservation timer
             * is decremented toward 0.
             */
            void pruneStaleTentPoints();

            /**
             * Finds a free attack-angle tent point within 200 of the tribe leader (findFreeSiegeTentPointIndex),
             * saves/releases the tribe's previous tent point, reserves the new one (tribe id/uid, reservationTimer
             * 3), places a commandBuildingType building at (x-1, y-1) for the tribe's owner (no placement-failure
             * check), tags placedBuildingID with the tribe's attackWave and gives the tribe
             * UIT_CONSTRUCT_SIEGE_EQUIPMENTOIL_DUTYENGINEERRELATED on it. Returns the tent point index or 0.
             */
            int placeSiegeTentAtAttackAngle(int tribeID, MappersEnum commandBuildingType);

            /**
             * Finds a site for a siege tent/tunnel near the tribe leader (findAppropriateLocationForSiegeTent with
             * range 100, then 200), checks the tile at (x-1, y-1) is in-map, non-zero in the byte map at 0x21AEC98
             * and free of tile flags 0x4A5014B1, then places commandBuildingType for the tribe's owner; if
             * placement succeeded, tags the building with the tribe's attackWave and unknownSiegeTentRelated01 = 2
             * and gives the tribe the given instruction on it. Returns TRUE on success; an invalid site sets
             * buildingPlacementResult = TRUE (fail) and returns FALSE.
             */
            BOOLEnum placeSiegeTentOrTunnelAtSuitableLocationAndAssignEngineers(
                int tribeID, MappersEnum commandBuildingType, uint strategicDistance, UnitInstructionType instruction);

            /**
             * Like placeSiegeTentAtAttackAngle but for tunnels: reserves a free attack-angle tent point for the
             * tribe, places M_MAPPER_TUNNEL_CONSTRUCTION at (x-1, y-1), and if placedBuildingID > 0 tags it with
             * the tribe's attackWave and gives the tribe instruction 0x15 on it. Returns the point index, or 0 if
             * no point or the placement failed (the point stays reserved).
             */
            int placeTunnelEntrances(int tribeID);

            /**
             * Clears every non-zero AIInfoLayer tile whose PathConnectionLayer id differs from attackInfo.startCon.
             */
            void clearAIInfoLayerOutsideStartZone();

            /**
             * Triggers battle music if conditions allow, plays battlehorn.wav (attacker 2-4) or drumhorn.wav
             * (attacker 5) on the speech SFX stream (nothing for other attackers), and sets
             * attackInfo.attackAlarmPlayed = 1.
             */
            void playAttackAlarmSound();

            /**
             * For attack wave attackWave of its attacking player (attackWavePlayerIDArray, 0 -> 2; forced 2 in
             * Siege-type builder maps): builds up to 250 siegeTentPlan orders from the wave's per-type siege counts
             * (types 0..4 and 8; building type and engineers per type from DAT_AttackInfoDefinedData) and, only if
             * the wave has engineer tribes, pops up to the total needed engineers out of them. Then for each order
             * creates an engineer tribe (owner, wave and counter copied from the last old engineer tribe;
             * STBT_0x410_SIEGE_EQUIPMENT_CONSTRUCTION), fills it with the player's normal, non-dying, tribeless
             * engineers (scan continues from the last unit index) and places its tent (attack angle if
             * useAttackAngle != 0, else a suitable location); stops as soon as the unit list is exhausted, leaving
             * the current tribe without a tent.
             */
            void placeSiegeTentsAndAssignEngineers(int attackWave, int useAttackAngle);

            /**
             * For attack wave attackWave of its attacking player (0 -> 2; forced 2 in Siege-type builder maps):
             * counts the player's normal, non-dying tunnelers, collects the wave's tunneler tribes and, only if
             * there are any, empties them; then for each counted tunneler creates a one-unit tunneler tribe
             * (STBT_0x415, wave/counter copied from the last old tribe), adds the next normal non-dying tribeless
             * tunneler and calls placeTunnelEntrances for it (stops when the unit list is exhausted). attackWave is
             * reused as the loop counter.
             */
            void placeTunnelForEveryTunneler(int attackWaveThenLoopIdx);

            /**
             * Creates a new tribe for a freshly built siege unit (called from the siege-equipment building updates)
             * and adds unitID to it. If currentGameMode == GM_SOLITARY the tribe is created for the wave's
             * attacking player (attackWavePlayerIDArray[attackWave], 0 -> 2, forced 2 on Siege-type builder maps)
             * with behavior STBT_6; otherwise createTribeForPlayer(playerID). Sets tribeType, attackWave and resets
             * attackInfo_someCounter1.
             */
            void addUnitToNewTribe(undefined4 unitID, int attackWave, AITribeType tribeType, undefined4 playerID);

            /**
             * For every active tribe (tribeState != 0) of the given attack wave whose tribe type is 0x13-0x18
             * (siege-equipment crews), gives each member unit that is ULS_NORMAL and not dying the
             * UIT_EXIT_SIEGE_EQUIPMENT instruction (via its tribe) and sets its state to US_DISAPPEAR.
             */
            void exitSiegeEquipmentForWave(int wave);

            /**
             * Returns 1 if playerID is a player whose units the castle-defence helpers act on: on Siege-type
             * builder maps only player 1, otherwise any player other than 1 whose keep.id > 0; else 0. __stdcall,
             * only EAX is modified, so callers keep live values in ECX/EDX across the call (the decompiler shows
             * them as the high half of a 64-bit return).
             */
            BOOLEnum getPlayerNot1AndHasKeep(int playerID);

            /**
             * If currentGameMode == GM_SOLITARY and the current player has no keep: if tile holds a selectable unit
             * whose owner is a human player (currentPlayerFullIDArray != -1) and the tile has no ET_FIRE entity,
             * records the tile in the first free slot of the 100-entry list attackInfo.spottedEnemyTiles with
             * value 100, unless already present.
             */
            void registerSpottedEnemyTile(int tile);

            /**
             * Returns TRUE if the troop value from computeTotalUnitsWithinDistance(playerID, 0, 1, tile, 6) is more
             * than twice the value from computeTotalUnitsWithinDistance(playerID, 1, 1, tile, 10) (by its other
             * callers' use, mode 0 = enemies of playerID, mode 1 = own troops). The third stack argument (enemy
             * owner) is never read (ret 0xC).
             */
            BOOLEnum shouldLightPitchBasedOnTroopValue(int tile, int playerID, int enemyPlayerID);

            /**
             * Gets the pitch ditch at tile and finds the closest archer (UT_E_ARCHER or UT_A_ARCHER, not invisible,
             * owner accepted by getPlayerNot1AndHasKeep, not dying, brazier flag at unit+0x40D set, targeting type
             * not already UIT_LIGHT_PITCH) within squared tile distance <= 2500 that has a valid
             * arrowShootingRelated trajectory to the ditch centre; gives it a UIT_LIGHT_PITCH shot at the ditch,
             * stops its walking and sets state US_FIRE_WEAPONUnk with fireImmediately. Returns 1 if an archer was
             * assigned, else 0. (The local named distanceSq actually holds dx.)
             */
            undefined4 giveLightPitchInstructionToUnitClosestToPitch(int tile);

            /**
             * If currentGameMode != GM_SOLITARY and unitID's owner is an AI player (no human full ID,
             * currentAIArray set): if unit unitID2 stands on a LogicLayer bit-8 tile that has a pitch ditch and
             * shouldLightPitchBasedOnTroopValue(tile, owner, unit2 owner) agrees, sets unitID's shoot target to the
             * ditch centre/height with targeting type UIT_LIGHT_PITCH and fireImmediately (does not change the unit
             * state or stop its walking).
             */
            void lightPitchIfNecessary(int unitID, int unitID2);

            /**
             * For every visible European/Arabian archer whose owner is accepted by getPlayerNot1AndHasKeep and
             * which is not dying, stores whether a brazier is nearby (EntityState::isBrazierNearby at its
             * position/height) in Unit.isNearBrazier.
             */
            void updateArcherBrazierProximityFlags();

            /**
             * Returns the troop value of a unit type from DAT_TroopValueDefinedData: the per-type fields TUNNELER,
             * MONK, CATAPULT and the Arabian units (A_ARCHER..S_FBALLISTA) for their types, the consecutive fields
             * ARCHER..ENGINEER for European types 0x16-0x1E (the decompiler shows these as the out-of-bounds
             * NoRushTicks[unitType+5]), 0 for other types. __stdcall, clobbers only EAX/ECX.
             */
            int getValueOfTroopType(UnitType unitType);

            /**
             * NAME? Operates only on engineers, not archers: for every visible UT_E_ENGINEER whose owner is
             * accepted by getPlayerNot1AndHasKeep, not dying and in state US_SIT_DOWNUnk, queries enemies of
             * attackInfo.pitchRelatedPlayerID within 3 tiles (5 if terrain height > 110) of it; if their troop
             * value >= 10, their count >= 2 and an enemy unit was found (PathFindingState.firstMatchingUnitID), sets
             * targetingType UIT_THROW_OIL, attackAtTileX/Y = that unit's position and animationFrame 4.
             */
            void queueOilThrowForIdleEngineers();

            /**
             * Auto oil-throw for an engineer: requires a tribe, closestEnemyMicroDistance <= 80 and, for human
             * owners, a stance other than stand-ground; every 8th call counts enemies within 4 tiles (5 if terrain
             * height > 110): aggressive stance needs >= 1 enemy, otherwise >= 4 enemies or value >= 20. If the
             * first found enemy stands on a campfire/parade ground/campground, sums the troop values of selectable
             * units on that building's footprint by team and returns 0 if the engineer's team outweighs the others;
             * otherwise sets UIT_THROW_OIL at the enemy's position (animationFrame 4) and returns 1.
             */
            undefined4 ifNecessaryThrowOilAutomatically(int unitIDThenFootprintSize);

            /**
             * Computes an entrance position for attackInfo.pitchRelatedPlayerID's keep (offset by keep type;
             * returns for unknown types), creates a swordsmen and an archer tribe for that player, moves every
             * visible unit accepted by getPlayerNot1AndHasKeep that is a European mace/sword/spear, or
             * archer/crossbow not on a LogicLayer 0x10000100 tile, and is within distance 30 of that position from
             * its old tribe into them (swordsmen into the sword tribe, the rest into the archer tribe), then orders
             * the sword tribe to (x, y+1) and the archer tribe to (x, y); empty tribes get tribeState 3.
             */
            void commandUnitsToMoveToKeep();

            /**
             * Clears the defender archer lists, then for visible European archers/crossbowmen accepted by
             * getPlayerNot1AndHasKeep: those not on a LogicLayer 0x10000100 (wall/tower) tile are removed from
             * their tribe and pushed to reserveArcherUnitIDs (max 1000); those on such tiles whose tribe is 0 or
             * not rallying are recorded as wall posts (tile, uid, unitID) while fewer than 200 posts exist.
             */
            void collectArcherUnitsByLocation();

            /**
             * If field127523_0x2b578 is 0 and reserve archers exist: for every post whose recorded archer is gone
             * (id 0 or uid mismatch) and whose tile still has LogicLayer 0x10000100 set, pops the last reserve
             * archer, records it for the post and sends it (state US_MOVE_TO_DESTINATION, setDestinationForUnit) to
             * the post tile. The reserve count is only checked before the loop, so more vacant posts than reserves
             * underflow it (reads before unitIDArray_0x2b57c).
             */
            void redeployArchersToDefensivePositions();

            /**
             * Removes all visible European macemen and knights of players accepted by getPlayerNot1AndHasKeep from
             * their tribes, then regroups them into new tribes of attackInfo.pitchRelatedPlayerID: macemen tribes
             * of 5/8/10 (count <= 20 / <= 40 / more) and knight tribes of 2/4/6 (count <= 12 / <= 18 / more), at
             * most 100 each, storing ids in macemenTribeArray/knightTribeArray and counts in
             * macemenTribeCount/knightTribeCount. The knight count is kept in EDX across getPlayerNot1AndHasKeep
             * (high half of uVar7 in the decompile).
             */
            void assignMacemenAndKnightsNotFromPlayer1ToTribes();

            /**
             * If macemen tribes are queued, attackInfo._182356_4_ > 3 and (SEC_RNG.currentNumber2 & 7) == 0: pops
             * the last macemen tribe, sets it aggressive and, unless in a campaign mission with missionNumber1to20
             * <= 14, sends it to a living selectable unit of player playerID_0x2c850.
             */
            void trySendMacemenTribeToAttack();

            /**
             * If knight tribes are queued, attackInfo._182356_4_ > 9 (and either > 99 or the target player has
             * previousSiegeWeaponsCount > 0) and (SEC_RNG.currentNumber2 & 7) == 0: pops the last knight tribe
             * (knightTribeArray, shown as macemenTribeArray[count+99]), sets it aggressive and sends it to an
             * active siege engine of player playerID_0x2c850, or to a living selectable unit if that player has no
             * siege weapons.
             */
            void trySendKnightTribeToAttack();

            /**
             * With updatePathLinkageTileMap(1) active, searches a destination tile from the tribe's
             * selectionTargetUnitID unit with pathfindingRelated49ff20 (radius 12, then 30, then 50, last argument
             * 1), restores the linkage map and moves the tribe there if a tile was found.
             */
            void sendAttackingPatrolTribeToComputedDestination(int tribeID);

            /**
             * Same as sendAttackingPatrolTribeToComputedDestination but with last argument 0: searches a tile from
             * the tribe's selectionTargetUnitID unit (radius 12, 30, 50) with path linkage enabled and moves the
             * tribe there if found.
             */
            void moveTribeToReachableNearbyTile(int tribeID);

            /**
             * Around the tribe's selectionTargetUnitID unit looks for an enemy building within 15 and an enemy unit
             * within 10. If bit 0 of SEC_RNG.currentNumber2 is set, attacks the building if any, else the unit if
             * any (the same RNG bit gates both). Otherwise clears the tribe instruction and moves the tribe to
             * findBestAttackTileByPathCost (radius 6, then 30, then 50) with path linkage enabled.
             */
            void decideAndExecuteTribeAttackAction(int tribeID);

            /**
             * Looks for a gatehouse via getGatehouseNearSomethingUnk from the tribe's selectionTargetUnitID unit
             * (range 80, then 200); if found clears the tribe's instruction, moves it to the building's someX/someY
             * and returns 1, else 0.
             */
            undefined4 moveTribeToNearbyGatehouse(int tribeID);

            /**
             * Looks for a target unit via findDistanceOrThreatLevelToUnitUnk from the tribe's selectionTargetUnitID
             * unit (range 80, then 200); if found clears the tribe's instruction and moves it to that unit's
             * position.
             */
            void moveTowardsParticularUnits(int tribeID);

            /**
             * Amortized decay of the byte tile map at 0x1ECEF88: decrements every non-zero byte in a 200-tile
             * window starting at attackInfo.tilemapOffset, then advances the window by 200 (wrapping to 0 after the
             * window ending at tile 80400).
             */
            void decrementTileMap1104();

            /**
             * Moves attack wave attackWave into staging: clears field86987_0x20f9c (set by playAttackAlarmSound),
             * sets value3Array01[wave] = 2 and its ticker to 0, calls collectReachableLocationsFromFirstNofFPoint,
             * increments someCounter1, then sortAttackInfoTribeIDArrayBasedOn(wave, 2, 100000, STBT_0x3fb) +
             * applyTribeBehaviorTypes(STBT_0x3fe, STBT_5, 0, 50); if casDis >=
             * AttackInfoDefinedData.field0_0x0[attacker] also sort(wave, 1000, 10000, STBT_5) + apply(STBT_5,
             * STBT_1, 0, 40).
             */
            void advanceAttackWaveStaging(int attackWave);

            /**
             * Ticks an active attack wave: when the ticker was < 1 increments someCounter1, removes the wave's
             * siege buildings, makes siege-equipment crews exit (exitSiegeEquipmentForWave) and runs
             * sort/applyTribeBehaviorTypes with STBT_0x3ff -> STBT_1; otherwise applies STBT_0x400 to the wave on
             * every tick once the ticker exceeds 100, and resets the ticker to 0 after 1000, so the first-tick
             * actions repeat.
             */
            void updateActiveAttackWaveState(int attackWave);

            /**
             * Per-tick attack-behaviour state machine for one tribe. Raises a non-zero attackWave to at least
             * attackInfo.index, bumps the per-wave counters waveTribeCountThisTick (and nofStationaryTribesPerWave
             * when percentageMovingUnk < 1), increments behaviorTickCounter and dispatches on tribeBehaviorType.
             * Most cases wait until the counter reaches behaviorDelayTicks, then do one action: move to a signpost,
             * region seed point, attack vector, rally point or the local player's keep; assign attack targets;
             * claim an archer or support point; or set the stance. Several cases advance tribeBehaviorType (3->4,
             * 5->6, 7->8, 0x3ff->0x400, invalid link in 0x411 -> 1). Case 0x3fc sets unitStance =
             * (archerAssignRounds > 2) i.e. USE_DEFENSIVE vs USE_STAND_GROUND and claims an archer attack point
             * only while countdown2 < 1; case 0x412 assigns a support point next to a moat-attack tribe, else an
             * archer point; case 7 takes the first free attackVectors slot in the row of currentPlayerSlotID;
             * unknown types fall back to updateTribeCombatStanceBehavior.
             */
            void updateTribeBehaviorBasedOnBehaviorType(int tribeID);

            /**
             * Rebuilds the attack-target lists of attacking player playerID against attackedPlayerID. Clears
             * playerID's per-player record (hack/scale/town/gate/wide/moat counters and 1000-entry lists, stride
             * 0x177BC) and the global people/lord/high2/arch2 lists, then scans all 0x13A10 tiles; each list entry
             * is a (tile, adjacent reachable tile at similar height) pair, capped at 1000. People: enemy-team
             * selectable non-animal units in area startCon on tiles marked in attackedPlayer's 0x1EE2998 map; lord:
             * enemy UT_LORD (sets lordConnectionArea) paired with any connected neighbour; buildings of the
             * attacked player: gate/tower -> gate points, other buildings with health -> town points, health-less
             * buildings on 0x10000000 tiles with a non-zero adjacent AI zone -> high2 (human units on it) or arch2.
             * Other tiles: the attacked player's wall tiles (WallOwnerLayer, > 20 above default height, no
             * building) give a wide point when three consecutive neighbours are reachable, otherwise hack and
             * (unless LogicLayer 0x400000) scale points; marked moat tiles (LogicLayer 0x40000000) give moat
             * points. Some hits flood-fill or mark the AI zone around them.
             */
            void recomputeAttackInfo(int playerID, int attackedPlayerID);

            /**
             * Collects AI archer points. A tile qualifies when AIInfoLayer == 2, an orthogonal neighbour has
             * AIInfoLayer & 0xF == 4 and RandomLayer & 3 == 0, and findAIZoneWithFlags finds no 0x10-flagged tile
             * within the spacing radius (5..10 from the previous full scan's point count, 8 if that count is
             * negative i.e. no scan yet). A qualifying tile gets AIInfoLayer |= 0x10 and a new (x, y, tile,
             * someCounter1) or refreshed (someCounter1) archer-point record via findOrReserveArcherPointSlot. The
             * scan stops at 200 points; only a full scan stores the count for the next radius choice.
             */
            void scanForArcherPoints();

            /**
             * Collects AI support points. A tile qualifies when AIInfoLayer == 1, an orthogonal neighbour has
             * AIInfoLayer & 0xF == 2 and RandomLayer & 3 == 0, and findAIZoneWithFlags finds no 0x40-flagged tile
             * within radius 8. A qualifying tile gets |0x40 and a new or refreshed supportPointsArray entry (x, y,
             * tile, someCounter1); the slot comes from getSupportPointIndex, or supportPointsNext when that returns
             * 0. Stops after 200 points.
             */
            void scanForSupportPoints();

            /**
             * Collects siege-tent points. Candidates are unit-free tiles with AIInfoLayer == 8. Each of the 8
             * neighbours (ring 1) must be within +-6 of the tile's HeightLayer value, unit-free, in
             * attackInfo.startCon and free of LogicLayer flags 0xA0002400; one failure rejects the tile. Then the 8
             * neighbours of each ring-1 tile (ring 2) are checked the same way with +-8, counting passes until the
             * first failure. Only all 64 passes (count > 0x3F) qualify. If no 0x80-flagged tile lies within radius
             * 6, the tile gets |0x80 and a new or refreshed tentPointsValues entry (new: x, y, tile, someCounter1,
             * tribe fields 0). Stops after 2000 points.
             */
            void scanForSiegeTentPoints();

            /**
             * Walks the 100 {tile,value} entries of field127521_0x2b254. Tile 0 means an unused slot. A tile >=
             * 0x13A10 has its slot zeroed, but the old value is still used for the rest of this pass (machine code
             * keeps it in EDI). Value 100 marks a new entry: if shouldLightPitchBasedOnTroopValue(tile,
             * pitchRelatedPlayerID, playerID_0x2c850) agrees, the unit closest to the pitch is ordered to light it,
             * and the value drops to 99. Other values count down by 1, and the slot is cleared when the value
             * reaches 0.
             */
            void processSpottedEnemyTiles();

            /**
             * Zeroes playerTotalTroopValueArray[0..8] and troopValueUnk25b28, then for every unit slot
             * 1..maxUnitCount-1 whose logicalState is not ULS_INVISIBLE, not dying, has the short flag 0x216 bytes
             * after unitType set and is not an engineer, tunneler or ladderman, adds getValueOfTroopType(unitType)
             * to its owner's total.
             */
            void recountTotalTroopValue();

            /**
             * Zeroes playerTotalTroopValueOfTroopsNearKeep[0..8] and _154448_4_. Then, for every in-use, non-dying
             * unit that is not an engineer, tunneler or ladderman, adds its troop value to its owner's slot if
             * setAxisBasedDistanceResult between the unit and the owner's campground entry point gives distanceHigh
             * <= 40.
             */
            void recomputeTotalTroopValueOfTroopsNearKeep();

            /**
             * Empty stub: ignores its two map-version magics (just ret 8).
             */
            void uselessFunction(PackagedFileMagicNum receivedMapVersion, PackagedFileMagicNum packagerMapVersion);

            /**
             * Every 16th call, or at once when forceRecount != 0, recounts attack-troop statistics over all tribes.
             * Tribes for which isFullIDEqualsToMinus1(owner) is true are counted as AI: their sizes are summed per
             * tribe type into aiTribeSizesPerTribeType (cleared with a 0xA0-byte fill), engineer and ladderman
             * tribes and type 0x16/0x17 tribes with stone ammunition are counted, and combat tribes are counted by
             * kind. Other tribes owned by the current player add their size to attackInfo.size. Knights are zeroed
             * if any spearmen/macemen or pikemen/swordsmen exist. lowTroopValueRelated is set when there are no AI
             * combat troops, or when size > 3*aiTroops, aiTroops < 3 (difficulty 0) or 6, and players 2-5 have a
             * total troop value below 30.
             */
            void recountAttackTroopValue(int forceRecount);

            /**
             * Per-tick defence helper for non-skirmish AI. Picks the pitch players: 1 and 2 on siege maps in
             * builder mode, otherwise FindFirstOpponentWithKeep() and 1. Then runs a schedule on a tick counter
             * that wraps 100 -> 2: at 0, collect archers and assign macemen/knights (also resetting the moved-to-
             * keep flag and the cycle count); at 1, brazier proximity flags; at 0x46, send a macemen tribe; at
             * 0x3C, send a knight tribe; every 16 ticks, queue oil throws; at tick & 15 == 8, redeploy archers.
             * Once player 1's units can leave the keep area, it orders units to the keep (one time only). Finally
             * processes the pitch tile list.
             */
            void updateAttackInfoTick();

            /**
             * Wave state 0 (preparation) for attackID. On the first call (ticker 0) it sets the ticker to 1, resets
             * the wave counters, recounts troops, computes the composition, initialises the zone search, sorts
             * tribes, gives the initial behaviours (STBT_3 to the wave) and stores casDis. Afterwards, once at most
             * 5 of the wave's tribes are still moving, it advances the ticker. When the ticker reaches
             * field1_0x28[attacker] it switches to state 1 (staging) with ticker 0. Attacker 8 instead sounds the
             * alarm and jumps straight to state 3 (target assignment) with ticker 10000, so the first assignment
             * fires at once.
             */
            void initializeOrAdvanceAttackWave(int attackID);

            /**
             * Full target recomputation for wave attackID, whose attacking player is
             * attackWavePlayerIDArray[attackID] (playerID). Writes the current player slot (the attacked player)
             * into that player's record field 0 and clears AIZoneLayer and AIInfoLayer (0x13A10 bytes each).
             * Recounts troops, then computes AI zones from the wave's signpost; that signpost falls back to
             * signpost 0 and resets the index if its tile is < 1, and the flag passed to computeAIZoneLayer is
             * canKeepReachSignpostZone(...) != 0. Then rebuilds targeted-building tiles and
             * recomputeAttackInfo(attacker, attackedPlayer), scores siege spots and fills the slot counts. It
             * recomputes attack vectors whenever field86981_0x20f84 <= 0, which in practice is every call because
             * the counter always ends at 0. Finally it expands the AI zones and rescans archer and support points,
             * plus siege-tent points when scanTentPoints != 0. Timed with DAT_UnknownStopwatch. Artefacts:
             * unaff_EDI is really the canKeepReachSignpostZone result (saved in param_2's stack slot), and
             * tentScanFlag = 0x1E94158 is really param_1.
             */
            void aiRecomputeAttacks2(int scanTentPoints, int attackID);

            /**
             * Lighter target recomputation used by wave state 4. Like aiRecomputeAttacks2 it writes the current
             * player slot into the wave player's record (hack header -0x10), clears AIZoneLayer and AIInfoLayer,
             * recounts troops, recomputes AI zones from the wave's signpost tile (signpost 0's tile, and the wave's
             * signpost index reset to 0, if that tile is < 1; flag fixed at 1, path-cost parameter 0x3C instead of
             * 0x5A), rebuilds targeted tiles and recomputeAttackInfo, scores siege spots and fills slot counts, all
             * timed by DAT_UnknownStopwatch. Recomputes attack vectors when attackVectorRecalcToggle <= 0; the
             * toggle code always leaves it 0 (from 0 or 1), so unless other code sets it to 1 this happens on every
             * call. unusedRecomputeCount is never read.
             */
            void aiRecomputeAttacks(undefined4 unusedRecomputeCount, int attackID);

            /**
             * Wave state 2 (in progress). If isLessThanPercentageOfTribesInAttackDying(attackID, 50) is true and
             * field86987_0x20f9c is still 0, plays the attack alarm. While field86987_0x20f9c stays 0 it then
             * returns. When the ticker is 0 it increments someCounter1 and calls aiRecomputeAttacks2(1, attackID).
             * It then places siege tents; if tent points exist it does so in mode 1 and also places tunnels. Tribes
             * are then assigned to town targets (STBT_0x3f5) and people targets (STBT_0x3fb). Finally it advances
             * the ticker. After AttackWaveDurationPerAttacker[attacker] ticks it switches to state 3 with ticker
             * 10000, playing Mace_s4.wav for attacker 4 in mission 39.
             */
            void updateInProgressAttackWave(int attackID);

            /**
             * Wave state 3 (main target assignment). Advances the ticker; every field3_0x78[attacker] ticks it
             * resets the ticker and increments value10. If the attacked keep can reach the signpost zone and
             * attacker != 8, it switches to state 4 with ticker 10000 and resets field127574_0x30b1a[attackID].
             * Otherwise it increments someCounter1, calls aiRecomputeAttacks2(0, attackID) and assigns tribe
             * behaviour types in priority order: siege engines, lord, town, attack vectors, moat, patrols, gates,
             * archer points, people, walls, scale and hack points, knights. Most steps unlock as value10 -
             * field89399_0x21c48 grows. Attacker 8 uses a short fixed plan and switches to state 6 (with battle-end
             * music) once someCounter1 > 9. Siege maps in builder mode force wave player 2 and the round offsets
             * local_8=5, local_4=-1. Two pairs use different tags in the machine code itself: a sort with
             * STBT_0x3f4 followed by apply STBT_0x3fc (0x520B9C/0x520BB5), and sort 0x417 followed by apply 0x3f6
             * (0x520C65/0x520C82).
             */
            void executeAttackWaveTargetAssignment(int attackID);

            /**
             * Wave state 4 (keep reachable). If the attacked keep can no longer reach the signpost zone, returns to
             * state 3 with ticker 0. Otherwise, every 400 ticks it resets the ticker, increments someCounter1 and
             * the per-wave field127574_0x30b1a counter, and calls aiRecomputeAttacks (passing the old count, which
             * is unused). It then assigns STBT behaviour types: 0x41b and 0x418, people 0x3fb (if > 9 combat
             * tribes), lord 0x3fd, high 0x3f8 and arch 0x3f9, people again, town 0x3f5, support 0x411, attack
             * vectors (STBT_7) and keep approach 0x416.
             */
            void executeDelayedAttackWaveTargetAssignment(int attackID);

            /**
             * Per-tick controller of AI attack waves outside editor, skirmish/MP and Siege That (i.e. campaign).
             * Calls decrementTileMap1104; if the current player has no keep only updateAttackInfoTick runs.
             * Otherwise recounts/composes attack troops and steps the current player's aiControlStatusRelated:
             * -1000 = idle/done; 0 -> set to 600 when no wave has tribes outside state 6; >0 counts down and
             * becomes -1000 on reaching 0; other negatives count up. Then for wave slots 1..49 whose attacker is
             * not player 1 (attacker > 0 or found via searchTribeWithProperties) it marks the attacker's
             * attackedPlayerID = 1 and, if the wave has tribes this tick, increments its age, forces state 6 (with
             * battle-end music) when lowTroopValueRelated is set and age > 10, and dispatches on the wave state (0
             * init, 1 staging, 2 in progress, 3 target assignment, 4 delayed target assignment, 6 active); a wave
             * without tribes is reset to state 0. NAME? it drives attack-wave state machines rather than unit
             * movement.
             */
            void aiControlNonSkirmishUnitMovement();
        };

        static_assert_cpp98_obj(sizeof(TroopValueState) == 1062760, TroopValueState);

#pragma pack(pop)

    } // namespace Units
} // namespace Map
} // namespace OpenSHC
