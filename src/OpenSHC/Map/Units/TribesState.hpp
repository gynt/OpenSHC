/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/TribesState.hpp'
*/

#pragma once

#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/IO/PackagedFileMagicNum.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/Tribe.hpp"
#include "OpenSHC/Map/Units/UnitIDMovementDistancePair.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "WinDef.h"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Commands::MappersEnum;
        using OpenSHC::IO::PackagedFileMagicNum;
        using OpenSHC::Map::Units::SomeTribeBehaviorType;
        using OpenSHC::Map::Units::Tribe;
        using OpenSHC::Map::Units::UnitIDMovementDistancePair;
        using OpenSHC::Map::Units::UnitInstructionType;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::Behavior::UnitStanceEnum;
        using OpenSHC::Map::Units::Instructions::UnitMatchSpeedEnum;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

        // SIZE: 0x000FB3D0
        class TribesState {
        public:
            undefined4 DAT_CurrentTribeID; // 0x00000000 length: 4
            // [152 0x00527330] reset to 0 and incremented once per tribe with valid members
            int activeTribeCount; // 0x00000004 length: 4
            // Highest tribe ID that currently has units (1 when none)
            undefined4 highestActiveTribeID; // 0x00000008 length: 4
            undefined4 ALG_ResultX; // 0x0000000C length: 4
            undefined4 ALG_ResultY; // 0x00000010 length: 4
            undefined4 ALG_ResultTileIndex; // 0x00000014 length: 4
            // +1 per hard pathfind, -1 per direct path in a move order; >=0 doubles move delay, <0 clears it
            undefined4 pathEaseBalance; // 0x00000018 length: 4
            BOOLEnum patrolButtonPressed; // 0x0000001C length: 4
            undefined4 rallyCount; // 0x00000020 length: 4
            // Zeroed in clearAllTribes
            undefined4 clearedOnReset24; // 0x00000024 length: 4
            Tribe tribes[1250]; // 0x00000028 length: 1025000
            UnitIDMovementDistancePair someUnitIDMovementDistancePair[1001]; // 0x000FA410 length: 4004
            int someUnitIDArrayCount; // 0x000FB3B4 length: 4
            int fcn_mtribe; // 0x000FB3B8 length: 4
            int tribeCopiedToSlot0; // 0x000FB3BC length: 4
            // [152 0x005262A0] set to the x where the rabbit was just created
            int lastRabbitSpawnX; // 0x000FB3C0 length: 4
            // [152 0x005262A0] set to the y where the rabbit was just created
            int lastRabbitSpawnY; // 0x000FB3C4 length: 4
            DWORD constructorTime; // 0x000FB3C8 length: 4
            undefined1 padding_0xfb3cc[4]; // 0x000FB3CC length: 4

        private:
            TribesState(TribesState const&);
            void operator=(TribesState const&);

        public:
            TribesState() {};
            ~TribesState() {};

            // Constructor
            /**
             * Constructor of the global TribesState: stores timeGetTime() as construction time, zeroes clans and
             * fcn_mtribe, sets field2_0x8 = 1 and returns &DAT_TribesState.
             */
            TribesState* Constructor_TribesState();

            /**
             * Thin wrapper: forwards (tribeID, x, y, rallyBool, doRally) to giveTribeMoveInstruction on the global
             * TribesState with speed-matching mode UMSE_0 (no speed matching, per the function name).
             */
            void giveUnitSelectionMoveInstructionNoMatchedSpeed(
                int tribeID, uint x, uint y, int rallyBool, int doRally);

            /**
             * Resets the tribe table: clears clans/field9_0x24, sets field2_0x8 = 1 and zero-fills every tribe
             * record 1..0x4E1 (0x334 bytes each), using the global g_tribeScanIndex (0xEE0FB0) as the loop
             * counter (leaves it at 0x4E2).
             */
            void clearAllTribes();

            /**
             * Walks tribes 1..0x4E1 and, for every active tribe (Tribe.tribeState == 2, read via owner+0x14) owned
             * by fromPlayerID, changes its owner to toPlayerID. Called by changePlayerOwnership. NAME? the '2' is
             * tribeState == 2 (active), not a behavior type.
             */
            void reassignOwnerForTribesOfBehaviorType2(int fromPlayerID, int toPlayerID);

            /**
             * Swaps ownership of active tribes (tribeState == 2) between two players: tribes owned by playerA
             * become playerB's and vice versa.
             */
            void swapTribeOwnership(int playerA, int playerB);

            /**
             * For a normal, alive, non-teleporting unit whose owner has no human player ID
             * (currentPlayerFullIDArray[owner] == -1, i.e. AI-owned), looks up a target via TroopValueState
             * according to behaviorType (0x3F2 enemy walls, 0x3F5 enemy buildings, 0x3FB tile value with enemy-
             * walls fallback that also switches the unit (and the tribe, if it is the leader) to 0x3F2, 0x3FD enemy
             * lord, 0x3F6 towers/gates, 0x413/0x414 closest wide value, 0x3F7 diggable moat). Always clears
             * targetedBuildingTile; on success stores the target tile in targetedBuildingTile/attackAtTileX/Y (and
             * the tribe target if the unit is the tribe leader), sets US_MOVE_TO_DESTINATION and a destination
             * unless stopUnitIfNextToTarget succeeds; returns 1, else 0.
             */
            undefined4 moveUnitToBehaviorTarget(int unitID, int behaviorType);

            /**
             * Predicts where unitID will be when targetUnitID can reach it. Writes unitID's current x/y to
             * *unitCurrentX/*unitCurrentY; if unitID's tunnelerFinishedDigging field == 2 it then steps along
             * unitID's remaining 4-bit path plan, after each step comparing (Chebyshev distance to the target - 2)
             * * targetFactor against an accumulating cost (unitID's tribe min speed * 4 per step) and stops when
             * the former drops below. targetFactor = target tribe min speed * 4, halved for stateBasedSpeed > 0 or
             * swordsmen and divided by 3 for non-speed-matched knights; the same modifiers are then applied again
             * using unitID's own state (machine code confirms both adjust the target factor).
             */
            void predictUnitInterceptPosition(int targetUnitID, int unitID, int* unitCurrentX, int* unitCurrentY);

            /**
             * Counts, per unit type (< 0x50), the normal, alive units with isSelected set that are owned by the
             * local player (currentPlayerSlotID) and returns the most frequent type (lowest type wins ties),
             * writing its count to *maximumCount if non-null. The tribeID argument is unused. Because the max
             * starts at -1 with a signed compare, an empty selection returns UT_PEASANT (1) with count 0; the
             * 'return 0' path is unreachable.
             */
            UnitType getMajoritySelectedUnitType(undefined4 tribeID, int* maximumCount);

            /**
             * Plays the selection acknowledgement SFX/speech for the current selection based on its majority unit
             * type and count (param_1 is overwritten with the count), positioned at the first selected combat unit:
             * European swordsmen SFX 0xAD/0xAE/0xAF for 1/2/3+ units; knights 0x56 (1), 0x57 (2-3) or 0x58 (>3)
             * followed by 0x59; engineers carrying a resource speech 0x24; catapult/tower/ram SFX 0x68 when no
             * engineers are missing, otherwise speech 0xE (unmanned or >3 missing) or 0xB/0xC/0xD for 1/2/3
             * missing; horse archers 0xEA/0xEB/0xEC (1 / <5 / more) plus 0x59.
             */
            void playUnitSelectionSound(int selectionIdOrCount);

            /**
             * Plays the attack-order speech/SFX for the selection's majority unit type against target unitID:
             * ranged types use speech 0x1E if the target is beyond the squared projectile range else 0x19 (horse
             * archers add count-based 0xEA/0xEB/0xEC + 0x59); spear/pike/mace/monk use speech 0x11 against
             * knights/swordsmen/lord (spear always 0x15) else 0x15; swordsmen and knights add count-based
             * armour/horse SFX; groups of size >= 15 add SFX 0x14 (0xFA for knights); Arabian swordsmen only the
             * group SFX; engineers nothing.
             */
            void playUnitCombatSpeechForTarget(int selectionID, int unitID);

            /**
             * Plays the 'unit selected' speech (action 0xB) for the majority unit type of the current selection
             * (the argument is ignored by getMajoritySelectedUnitType and reused as its count output).
             */
            void playUnitSelectSpeech(undefined4 selectionIdOrCount);

            /**
             * Plays the move-order speech for the selection's majority unit type: ranged units action 0x1D; manned
             * siege engines their own line (catapult 0x10, trebuchet 0x11, mangonel 0xF, ram 0x13, ballistae 0x12),
             * with catapult/trebuchet playing speech SEID_RESOURCE_NEED25 instead when stoneAmmunition < 1; other
             * types nothing.
             */
            void playUnitMoveSpeech(undefined4 selectionIdOrCount);

            /**
             * Feedback for an attack order: if the majority selected type is a siege engine (ram, catapult,
             * trebuchet, mangonel, ballista, fire ballista) plays the move speech for
             * TribesState.g_tribeScanIndex and the selection sound; otherwise plays attack speech 0x15 and,
             * except for engineers, the selection sound. The argument's input value is effectively unused: it is
             * only forwarded to getMajoritySelectedUnitType/playUnitSelectionSound, which ignore it, and its stack
             * slot is overwritten with the majority count.
             */
            void playAttackCommandFeedback(int unusedOrMajorityTypeCount);

            /**
             * Plays the patrol-order speech (action 0x29) for the majority unit type of the selection.
             */
            void playPatrolCommandSpeech(undefined4 selectionIdOrCount);

            /**
             * Plays the tunneler's dig-order speech (action 0x27).
             */
            void playTunnelerCommandSpeech();

            /**
             * Plays the work-order speech (action 0x24) for the majority unit type of the selection.
             */
            void playWorkCommandSpeech(undefined4 selectionIdOrCount);

            /**
             * For every tribe with tribeState != 0 belonging to the given AI attackWave whose tribeBehaviorType
             * differs and whose Tribe.attackInfo_someCounter1 differs from TroopValueState.attackInfo.someCounter1,
             * sets the new tribeBehaviorType and resets unknownAttackRelatedUpdateCounter to 0.
             */
            void applyTribeBehaviorType(int attackWave, SomeTribeBehaviorType tribeBehaviorType);

            /**
             * Campfire peasant animation: picks a random 1-based index (range 1, 1-2, 1-4, 1-8 or 1-16 depending on
             * peasantCount) and walks all normal, alive peasants of the building's owner in state US_STAND_UPUnk
             * assigned to this building; for each it clears one flag (and, when resetStanding == 1, the 'stood'
             * flag), the picked one gets the 'stood' flag and stands up, others whose 'stood' flag is clear sit
             * down.
             */
            void updatePeasantSeatingAtBuilding(int buildingID, int peasantCount, int resetStanding);

            /**
             * Returns TRUE if tribeUID is non-zero and equals the uid of the given tribe slot (stale-reference
             * check).
             */
            BOOLEnum tribeCorrespondsWithUID(int tribeID, uint tribeUID);

            /**
             * For an active tribe (tribeState 2) with unitSelectionIndex < size, scans its 200x16-bit unit
             * membership bitmask and returns the unit ID (word*16 + bit) of the N-th member, or 0 if not found.
             */
            int getUnitIDForIndexInTribe(int tribeID, int unitSelectionIndex);

            /**
             * Stateful iterator over a tribe's member bitmask: when iterationStep == 0 restarts from
             * tribe.firstOccupiedMaskWord (first occupied mask word); each call returns the next member unit ID (word*16 + bit)
             * and advances the global cursor (g_tribeUnitSearchWord word / g_tribeUnitSearchIndex bit); returns 0 at
             * the end.
             */
            int getSpecificUnitFromTribe(int tribeID, int iterationStep);

            /**
             * Finds the first non-zero 16-bit word of the tribe's member bitmask, stores its index in
             * tribe.firstOccupiedMaskWord and returns it; returns 200 (highestID untouched) if the tribe has no members. NAME?
             * it computes the first occupied mask word rather than setting a boolean.
             */
            int setWhetherTribeContainsAnyUnits(int tribeID);

            /**
             * Sets the unit's bit (word unitID/16, bit unitID%16) in UnitsState.selectedUnitsBitFlags.
             */
            void addUnitToSelected(int unitID);

            /**
             * Returns TRUE if the unit's bit is set in UnitsState.selectedUnitsBitFlags. NAME? the parameter named
             * tribeID is actually a unit ID.
             */
            BOOLEnum unitIsSelectedByPlayer(uint tribeID);

            /**
             * Adds a unit to a tribe: increments size, sets the unit's membership bit, makes it the tribe leader
             * (selectionTargetUnitID) if none, copies leader/tribeID/tribeUID/idInTribe (= new size) into the unit
             * and refreshes tribe.firstOccupiedMaskWord via setWhetherTribeContainsAnyUnits.
             */
            void addUnitToTribe(uint unitID, int tribeID);

            /**
             * Removes a unit from the given tribe. Proceeds if the unit has any non-zero tribeID (not necessarily
             * this tribe; machine code skips the bit test then) or its membership bit is set in this tribe:
             * decrements size (tribeState 3 when it reaches 0), clears the bit, clears the unit's tribe fields only
             * if unit.tribeID == tribeID, and sets the tribe leader to -1 if it was this unit.
             */
            void removeUnitFromThisTribeIfInTribe(uint unitID, int tribeID);

            /**
             * Finds a free tribe slot (tribeState 0 and time 0): in single-player scans down from 0x4E1 and marks
             * time = 1; in multiplayer scans from 0x4E2-playerID downward in steps of 8 (per-player interleaving)
             * and reserves it with time = mapTimeInTicks+400. Mirrors the scan position in the global
             * g_tribeScanIndex; returns the slot or 0 if none.
             */
            int getAvailableTribeID(int playerID);

            /**
             * Finds a slot with tribeState 0 in the player's interleaved range (0x4E2-playerID, step -8), wipes it
             * and initialises it as an active tribe (tribeState 2) owned by playerID with a fresh uid; returns its
             * ID or 0.
             */
            int createTribeForPlayer(int playerID);

            /**
             * Finds the first tribe slot with tribeState 0 (scanning from 1 with the global g_tribeScanIndex as
             * cursor), wipes and initialises it as an active tribe of playerID with a fresh uid, and stores it in
             * TribesState.g_tribeScanIndex (the selected tribe, offset 0) if playerID is the local player and
             * setAsCurrentTribeID != 0. Returns the tribe ID or 0. unaff_EBP/unaff_EBX are decompiler artefacts:
             * they are really the stack args playerID/setAsCurrentTribeID (see SIGNATURE note).
             */
            int createTribe(int playerID, int setAsCurrentTribeID);

            /**
             * Wipes the given tribe slot and initialises it as an active tribe (tribeState 2) owned by playerID
             * with a fresh uid; the second argument is unused. Returns tribeID. unaff_ESI is a decompiler artefact
             * for the playerID stack argument (see SIGNATURE note).
             */
            int createPlayerTribe(int playerID, undefined4 one, int tribeID);

            /**
             * Adds every normal, alive unit with ifSelectedThenPlayerID == playerID to the tribe, then sets tribe
             * size2Unk, the three facing directions and field24_0x26 (run-up time) from the leader, min/max
             * movement speed of the added units (movementSpeed = slowest) and the average of their health-related
             * field into unitsHealthPercentage.
             */
            void addUnitsToTribeAndComputeMovementSpeed(int playerID, int tribeID);

            /**
             * Adds one unit to the tribe, then recomputes over all normal, alive units with ifSelectedThenPlayerID
             * == playerID (not over the tribe members) the min/max movement speed and average health and stores
             * them in the tribe (if non-empty).
             */
            void addUnitToTribeAndUpdateTribeMovementSpeed(int playerID, uint unitID, int tribeID);

            /**
             * Zero-fills the 0x334-byte record of the given tribe.
             */
            void clearTribe(int tribeID);

            /**
             * Queues a GCT_UNIT_STANCE synchronized command with Param0 = first argument and Param1 = unitStance;
             * ClickUnitStance later calls setUnitStance(Param0, Param1). NAME? the first parameter 'stanceID' is
             * really the tribe ID (callers pass TribesState.g_tribeScanIndex) and the second is the stance (0
             * stand, 1 defensive, 2 aggressive).
             */
            void queueUnitStance(undefined4 stanceID, undefined4 unitStance);

            /**
             * Sets the tribe's unitStance and sets DAT_GameCore.countdown = 1.
             */
            void setUnitStance(int tribeID, UnitStanceEnum unitStance);

            /**
             * Stores (destinationX, destinationY) as rally/waypoint number 'step' of the tribe and sets
             * rallyPointCount = step + 1.
             */
            void addRallyPoint(int section1016ID, int destinationX, int destinationY, int step);

            /**
             * Scans all normal, alive units with ifSelectedThenPlayerID == playerID. If every such unit that has a
             * tribe (tribeID > 0) belongs to the same tribe, copies that whole 0x334-byte tribe record into
             * tribes[0] and sets tribeCopiedToSlot0 = 1. Otherwise sets tribes[0].unitStance from the per-stance
             * counts of the units' tribes: no counts -> stand ground, stance-2 count >= both others -> aggressive,
             * else 1 (defensive) if count1 >= count0 else 0.
             */
            void snapshotSelectionTribeAndComputeStance(int playerID);

            /**
             * Restores per-tribe settings for a freshly created selection tribe from the snapshot in tribes[0]: if
             * a whole tribe was copied there (tribeCopiedToSlot0), copies attackRetargetDelay,
             * attackTargetUnitID/UID, targetUnitTile, someTile2, currentRallyPointIndex, rallyPointCount,
             * rallyMode, unitStance and the 10 rally points (x pass then y pass); otherwise only the stance. The
             * first argument is unused.
             */
            void importStoredInfoFromSlot0(undefined4 unused1, int tribeID);

            /**
             * Intended to shrink a tribe to smallerSize by setting ULS_REMOVE on every member (logicalState 1,
             * normal or transitioning) whose index is >= smallerSize. BUG (confirmed in machine code): the tribeID
             * argument is never read; the tribe index is taken from the global scan cursor g_tribeScanIndex
             * (0xEE0FB0), so both callers (oversized deer tribes > 30) trim whichever tribe that cursor happens to
             * point at instead.
             */
            void trimTribeToSize(undefined4 tribeID, int smallerSize);

            /**
             * If (tileX > 0 or tileY > 0) and count > 0, spawns count units of unitType for playerID at tile
             * (tileX, tileY) (micro coords *8), sets each spawned unit's ownerColorIndex to calcOwnerIndex and adds
             * it to an AI tribe via AICState::addUnitToItsTribe with behaviour 0x11 for ranged types (archers,
             * crossbows, slingers, horse archers, fire throwers) or 0x14 otherwise. tileX is reused as the loop
             * counter. The first argument is unused.
             */
            void spawnUnitsForAITribe(
                undefined4 param_1, int param_2, int param_3, int param_4, UnitType param_5, int param_6, int param_7);

            /**
             * Creates a new tribe for playerID (tribeType, someIndex = counter, attackWave =
             * TroopValueState.attackInfo.currentAttackWaveSlot) and spawns unitType1Count units of unitType and unitType2Count
             * of unitType2 at tile (x,y), adding them to the tribe with aiUnitBehaviourType 0; sets field134_0x27a
             * = 1 and returns the tribe ID (0 if x<1 and y<1 or no slot).
             */
            dword spawnUnitsIntoNewTribe(undefined4 counter, int tribeType, int x, int y, int playerID,
                UnitType unitType, UnitType unitType2, int unitType1Count, int unitType2Count);

            /**
             * Creates a tribe for playerID with given tribeType/someIndex and the current attack wave (inv_count),
             * searches spawn tiles around (x,y) via findSuitableSpawnLocationUnk (limit 2000) and spawns count
             * units of unitType into it; sets field134_0x27a = 1 and returns the tribe ID or 0.
             */
            dword createTribeWithSpawnedUnit(
                short someIndex, undefined4 tribeType, int x, int y, int playerID, UnitType unitType, int count);

            /**
             * Creates a tribe of the given type (someIndex/attackWave 0) for playerID, searches spawn tiles around
             * (aroundX, aroundY) and spawns count units of unitType into it; sets field134_0x27a = 1 and returns
             * the tribe ID or 0.
             */
            dword spawnUnitsAroundLocation(
                undefined4 param_1, int aroundX, int aroundY, int playerID, UnitType unitType, int count);

            /**
             * Clears the 4-slot spawn coordinate arrays for deer, lions, rabbits and camels in GameState.mapAndTime
             * (offsets verified: +0x3B0 lion, +0x1D40 rabbit, +0x1D54 camel from deerSpawnLocationsXY) and resets
             * the round-robin index field2269_0xdee.
             */
            void clearAnimalSpawnLocations();

            /**
             * Stores (x,y) into the 4 deerSpawnLocationsXY slots. The loop has no break (confirmed in machine
             * code), so it writes every slot whose x is 0: the first deer herd fills all 4 slots and later calls
             * are no-ops until the slots are cleared - probably a missing break in the original source.
             */
            void storeDeerXAndYinMapInfo(undefined4 x, undefined4 y);

            /**
             * Stores (x,y) into every empty (x == 0) slot of the 4 lionLocationsXY slots (no break, confirmed in
             * machine code): the first lion fills all slots, which makes the round-robin in
             * findRecentOrSignpostSpawnLocation return the same point.
             */
            void storeLionXAndYInMapInfo(undefined4 x, undefined4 y);

            /**
             * Stores (x,y) into every empty slot of the 4 rabbitSpawnXY slots (no break) and then unconditionally
             * overwrites slot 0 with (x,y); net effect: slot 0 = latest rabbit position, slots 1-3 = the first one.
             */
            void setRabbitSpawnXY(undefined4 x, undefined4 y);

            /**
             * Stores (x,y) into every empty slot of the 4 camelSpawnXY slots (no break, confirmed in machine code;
             * the first camel fills all slots).
             */
            void setCamelSpawnXY(undefined4 x, undefined4 y);

            /**
             * Picks a spawn location: tries the 4 lionLocationsXY slots round-robin starting at field2269_0xdee,
             * accepting one inside the 400x400 map with a non-zero byte in the map mask at 0x21AEC98 and none of
             * LogicLayer flags 0x4A5014B1 (then sets the round-robin index to the next slot); otherwise falls back
             * to the map-edge point of the first existing signpost. Writes *outX/*outY, returns 1, or 0 if nothing
             * found.
             */
            undefined4 findRecentOrSignpostSpawnLocation(uint* outX, uint* outY);

            /**
             * Single-player only and while mapAndTime.rabbitCount < 0xA0: returns 1 if any of the 4
             * rabbitSpawnXY points is inside the map with a non-zero mask byte (0x21AEC98), or any of
             * mercRecruitable[8..15] is set; else 0.
             */
            undefined4 hasAvailableSpawnSlotForWildlifeOrMercs();

            /**
             * For an animal tribe with field133_0x278 == 0, re-rolls the antelopeBasedRngValue of each normal,
             * alive member currently at 2 using its fixedRng & 7: 0-1 -> 0, 2-5 -> 1, 6-7 -> 2.
             */
            void updateAnimalHerdBehaviorState(int tribeID);

            /**
             * Returns the first tribe member that is normal, not dying and has antelopeBasedRngValue == 1, else 0.
             * NAME? more specific than 'non-dying unit'.
             */
            int getNonDyingUnit(int tribeID);

            /**
             * Recounts mapAndTime.aliveDeerCount over all unit slots from 1 (loop unrolled 3 units per iteration)
             * counting normal, non-dying units of type UT_ANTELOPESHDEER (0x2C).
             */
            void countDeerEfficiently();

            /**
             * Sets tribes[tribeID].unkIsAnimalTribe = 1.
             */
            void markTribeAsAnimalTribe(int tribeID);

            /**
             * Sets unknownBool02 = 1 on every used tribe 1..0x4E1 (tribeState != 0) whose tribeType equals the
             * given type.
             */
            void flagTribesOfType(int tribeType);

            /**
             * For up to maxCount used tribes of the given type that have unknownBool02 set (scanning tribes
             * 1..0x4E1), clears unknownBool02 and sets unknownBool01 = 1, decrementing maxCount; stops when
             * maxCount reaches 0.
             */
            void consumeFlaggedTribesOfType(int tribeType, int maxCount);

            /**
             * Puts a newly recruited unit into the player's per-role 'fresh unit' tribe (slot 0 generic, 1 engineer
             * 0x1E, 2 tunneler 5, 3 ladderman 0x1D) or, for monks (0x25), into the player's monk tribe; (re)creates
             * the tribe via createTribe when the stored ID is 0, its tribeState is 0 or its uid no longer matches
             * the stored UID.
             */
            void aiAssignNewUnitToTribe(int playerID, int unitType, int unitID);

            /**
             * Scatters an (animal) tribe: runs findSuitableSpawnLocationUnk around the leader (limit 5000) and, if
             * at least size*16+200 tiles were found, gives each normal, alive member a target tile taken from the
             * search queue at a pseudo-random increasing index (100 + sum of 1 + fixedRng&15) and puts it in state
             * 0xD1. Returns 1 on success, 0 otherwise (also 0 for tribeID 0).
             */
            int scatterTribeUnitsRandomly(int tribeID);

            /**
             * UI overlay for a selected tribe: if it is rallying and owned by the local player draws its rally-
             * point flags (starting at index 1 when isRallyingUnk < 0); then for each normal, alive, local-player
             * member draws destination cursor markers (fading by unitSpeedMatchingRelatedUnk), floating marks for
             * attack-land/throw-cow and fill/dig-moat targets, and sets highlight flags on the targeted unit,
             * building, pitch ditch tile or building on targetedBuildingTile.
             */
            void drawFlagsAndUnitDestinations(int tribeID);

            /**
             * Map-load upgrade for map versions < 0xA9 (when they differ from the packager version): converts the
             * tribe array in place, from tribe 0x4E1 down to 0, from the old 0x26C-byte record layout (100-word
             * member bitmask) to the current 0x334-byte layout: copies the old record, moves its tail (0x16C bytes
             * from old offset 0x100) to field35_0x1c8 and zeroes the new second half of the member bitmask.
             */
            void upgradeTribeArrayLayoutForMapVersion(
                PackagedFileMagicNum receivedMapVersion, PackagedFileMagicNum packagerMapVersion);

            /**
             * For each normal, alive tribe member resets rallyRelatedFlag to 0, then sets it to 1 if goToRallyPoint
             * != 0 or isSelectable_OR_matchTime == 0; returns 1 if any member was flagged, else 0.
             */
            undefined4 updateTribeRallyFlags(int tribeID);

            /**
             * Clears rallyRelatedFlag on all normal, alive members of the tribe.
             */
            void unsetRallyRelatedFlagOnUnits(int tribeID);

            /**
             * Returns TRUE if every normal, alive member of the tribe is an Arabian assassin (also TRUE for an
             * empty tribe).
             */
            BOOLEnum isTribeAllAssassins(int tribeID);

            /**
             * Returns the first normal, alive tribe member standing on a tile with LogicLayer flag 0x40000000, else
             * 0.
             */
            int getFirstUnitInTribeThatIsOnXTerrain(int selectionID);

            /**
             * Returns 1 if the tribe has a normal, alive ladderman (UT_E_LADDER) in state 3, else 0.
             */
            undefined4 tribeHasActiveLaddermanUnit(int tribeID);

            /**
             * Returns 1 if any normal, alive tribe member has unitCanClimb set, else 0.
             */
            undefined4 tribeContainsUnitThatCanClimb(int tribeID);

            /**
             * Returns TRUE if the tribe contains a normal, alive mounted unit (horse archer or knight).
             */
            BOOLEnum selectionContainsHorses(int tribeID);

            /**
             * Counts normal, alive European vs Arabian archers in the tribe and returns UT_A_ARCHER if Arabian ones
             * are strictly more numerous, else UT_E_ARCHER.
             */
            UnitType getMajorityArcherTypeEuropeanOrArabian(int selectionID);

            /**
             * Clears tribe.attackTargetUnitID; if storeAsRallyPoint, sets isRallyingUnk and stores a two-point rally path
             * (leader position -> (x1,y1), index 1, count 2). Then gives every normal, alive, non-teleporting,
             * movable member not in melee (and moveRelatedFlag != 1) a move order: planned destination (x1,y1),
             * US_MOVE_TO_DESTINATION, targetingType UIT_NO_INSTRUCTION_OR_MOVE, cleared move delays, and
             * setDestinationForUnit; sets PathFindingState.pathForAssassins when the tribe is all assassins. Returns
             * 1.
             */
            undefined4 applyMoveCommandOrRallyCommandToTribe(
                int tribeID, undefined4 x1, undefined4 y1, undefined4 isRallying, int storeAsRallyPoint);

            /**
             * AI tribes only (returns 0 if the tribe owner has a human player ID, else 1). For every normal, alive,
             * non-teleporting, movable member: unless targetType is 0x3FD (enemy lord), members already busy
             * (attacking a wall, moving to destination, state 0x67, or a type-specific work state for
             * spearmen/engineers/laddermen/tunnelers) are skipped. Otherwise a target of kind targetType is looked
             * up via TroopValueState (walls, scale points, enemy buildings, tile value, lord, towers/gates, wide
             * value, moat value); on success the member gets attackAtTileX/Y, targetedBuildingTile and
             * unknownDigMoatOrWallAttackFlag1015 = targetType and is sent there (state 0x67 for 0x3F4 scale points,
             * else US_MOVE_TO_DESTINATION); if setDestinationForUnit fails the unit is set to ULS_REMOVE (machine
             * code 0x52478A). For 0x414 it instead walks to a free tile next to the target and gets
             * UIT_ATTACK_WALL. The tribe target is updated when the member is the leader.
             */
            undefined4 assignAttackTargetsForTribe(int tribeID, SomeTribeBehaviorType targetType);

            /**
             * For every normal, alive tribe member: teleporting/flagged (field303_0x413) members are counted as
             * busy; members in US_MOVE_TO_DESTINATION are stopped (path progress cleared) and counted. Returns 1 if
             * no member was counted (tribe idle) or the tribe is empty, else 0.
             */
            undefined4 stopTribeMovementAndCheckIdle(int tribeID);

            /**
             * Runs a path search from the tribe leader (calculatePathKeepAndWallsGatesNotAllowed if
             * horseAndRamCount != 0, pathFindingWithBuildingsIncluded if the tribe is all assassins, else
             * findLinkageBasedPathOrWalkRadius; limit 100000), assigns each queued destination a cost from
             * SearchDistanceLayer (10000000 if SearchGenerationLayer != searchGeneration, i.e. not reached),
             * bubble-sorts the searchQueue destinations by ascending cost (a pass stops at the first entry pair
             * with a zero tile), compacts out unreached entries and zero-terminates the list. The climbData+200
             * casts are decompiler aliases of DAT_PathFindingState.searchQueue; tribeID is reused as the bubble-
             * sort index.
             */
            void sortTribePathDestinationsByCost(int tribeIDThenSortIdx, int horseAndRamCount);

            /**
             * Walks the normal, alive members of a tribe; returns 0 as soon as one is teleporting/flagged, has
             * tunnelerFinishedDigging == 2 (following a path), is in melee attack or is a positioned ladderman.
             * Returns 1 if a member's tile (UnitLayer) holds a different unit that is not following a path
             * (blocked), 0 if none found.
             */
            undefined4 isTribeUnitBlockedByOtherUnit(int tribeID);

            /**
             * Counts normal, alive members with tunnelerFinishedDigging == 2 (following a path) versus other
             * normal, alive members. Returns 100 if none are at 2 (or the tribe is empty), 50 if they are not the
             * majority, 1 if they are the majority but others exist, 0 if all are at 2 (verified in machine code).
             * The header doc's 'alive/dead' wording describes the caller's interpretation; the counted condition is
             * the ==2 movement state.
             */
            int getTribeAliveStatus(int tribeID);

            /**
             * Checks that (fromX,fromY) and (destX,destY) are valid on-map tiles (mask 0x21AEC98) in the same
             * PathConnectionLayer region, then searches outward from the destination (radius 500) and, for each
             * normal, alive tribe member, takes the next closest tile (mode depends on LogicLayer flag 0x100 at the
             * destination); returns 0 if such a tile is occupied by a unit of another tribe that is not following a
             * path, or after 500 tiles, else 1 when every member got a tile. ALG_ResultTileIndex counts the tiles
             * taken.
             */
            undefined4 isTribePathToDestinationClear(
                int param_1, uint param_2, uint param_3, uint param_4, uint param_5);

            /**
             * For each normal, alive tribe member: returns immediately if one is teleporting/flagged, following a
             * path (tunnelerFinishedDigging == 2) or in melee attack; otherwise calls computeLadderClimbPath(unit,
             * b, 0, b) with b = (tribe.pendingEventFlag == 0) and on success sets the unit's state to the value shown
             * as US_DEATH_02|US_STAND_UPUnk. NAME? nothing is destroyed here and the callers are lion/wolf and
             * rabbit behavior updates; it looks like 'compute climb/flee path for tribe units'.
             */
            void applyLadderDestructionToTribeUnits(int tribeID);

            /**
             * Assigns topSpeedDelayIndex to tribe members. Tribes with size < 40: clears
             * someUnitIDMovementDistancePair, stores each normal, alive member's unitID (and, if skipDistanceSort
             * is FALSE, its movementDistance) at the member's index, bubble-sorts the first someUnitIDArrayCount
             * pairs by ascending distance (only when skipDistanceSort is FALSE) and gives each listed unit its
             * position as topSpeedDelayIndex. Larger tribes: member i gets min(i, 199). The pair slot advances for
             * every member while the count only grows for living ones, so dead members leave zero holes and
             * trailing living members are not re-indexed.
             */
            void applyUnitTopSpeedDelayBasedOnTribeSize(int tribeID, BOOLEnum skipDistanceSort);

            /**
             * Plays the unit speech with action ID 0x1F for the majority archer type (European or Arabian) of the
             * given tribe.
             */
            void playArcherCommandSpeech(int selectionID);

            /**
             * Returns FALSE if any normal, alive tribe member stands on a tile whose WalkLayer value differs from
             * algTileFlag (the current path-search generation), TRUE if all are covered. NAME? return values are
             * inverted relative to the name: TRUE means all units are inside the search coverage.
             */
            BOOLEnum areAllTribeUnitsCoveredBySearch(int tribeID, int algTileFlag);

            /**
             * Sets each normal, alive tribe member's movementDistance to the CertainPathLayer value of its current
             * tile (from the last path search).
             */
            void applyMovementDistanceToUnitsInTribe(int tribeID);

            /**
             * Sets each normal, alive tribe member's movementDistance to its idInTribe (join order) instead of a
             * path distance.
             */
            void applyMovementDistanceToUnitsInTribeBasedOnUnitNumberInTribe(int tribeID);

            /**
             * Returns FALSE if any normal, alive tribe member has movementState == 2, else TRUE. NAME? Only called
             * for camel/lion-wolf/rabbit tribes and only tests the generic movementState, so it is not about
             * tunnelling. The second parameter is unused (only [esp+8] is read; ret 8 confirms two stack args).
             */
            BOOLEnum isTribeFreeOfMovementState2Units(int tribeID, int unused2);

            /**
             * Re-elects the tribe leader: clears tribe.selectionTargetUnitID, makes the first normal, alive member
             * the leader and writes the leader ID into every such member's selectionTargetUnitID.
             */
            void electTribeLeader(int tribeID);

            /**
             * Sets the state of every normal, alive tribe member to newState and resets its animationCycleNumber
             * and seated flag.
             */
            void setStateForAllTribeUnits(int tribeID, undefined4 newState);

            /**
             * Makes every normal, alive tribe member stand up if seated, resets its animationCycleNumber and clears
             * rabbitMovementSlowdown (callers are the deer/camel/lion/rabbit behavior updates).
             */
            void standUpAllTribeUnits(int tribeID);

            /**
             * Returns TRUE if every normal, alive tribe member has reached its destination
             * (hasUnitReachedDestination), FALSE otherwise.
             */
            BOOLEnum allUnitsReachedTheirDestination(int tribeID);

            /**
             * Sets logicalState = ULS_REMOVE on every unit of the tribe (no alive check).
             */
            void removeAllTribeUnits(int tribeID);

            /**
             * Single-player only: if the unit's owner has no human player ID (AI) and the unit is not in a valid
             * live tribe (tribeID < 1, uid mismatch or tribeState 0), creates a new tribe for the owner, sets
             * tribeType from the unit type (European troops AITT_*, Arabian troops 0x18-0x1F), someIndex = 1,
             * attackWave = current inv_count, behavior 0x410 for engineers in US_STAND_UPUnk or 0x415 for tunnelers
             * in US_LOOK_AROUNDUnk, and adds the unit. Returns TRUE if a tribe was created, else FALSE.
             */
            BOOLEnum addUnitToNewTribe(uint unitID);

            /**
             * Removes every normal, alive unit with ifSelectedThenPlayerID == playerID from its current tribe
             * (records the touched tribe IDs in a 1250-byte local array that is never read), then for every active
             * tribe (tribeState 2) re-elects the leader via setTargetUnitForTribe if leaderUnitID is -1 and
             * refreshes the tribe's contains-units state. Stack-cookie protected.
             */
            void removeSelectedUnitsFromTheirCurrentTribes(int playerID);

            /**
             * For every unit owned by playerID that is currently selected (ifSelectedThenPlayerID != 0, no alive
             * check): if its type equals unitType it is removed from its tribe, deselected and
             * unitCountOfSelection[playerID] is decremented; every such unit's tribe is marked in a local array
             * that is never read. Then active tribes get leader re-election / highestID refresh. iStack_8/local_4
             * are decompiler artefacts for the playerID/unitType stack arguments (local_4 is really the security-
             * cookie slot).
             */
            void clearTribesOfUnitType(int playerID, int unitType);

            /**
             * For every unit owned by playerID that is currently selected and whose type differs from unitType:
             * removes it from its tribe, deselects it, decrements unitCountOfSelection[playerID] and marks its
             * tribe in a never-read local array. Then active tribes get leader re-election / highestID refresh.
             * iStack_8/local_4 are decompiler artefacts for the playerID/unitType stack arguments.
             */
            void clearTribesNotOfUnitType(int playerID, int unitType);

            /**
             * Removes unitID from tribeID. Proceeds if the unit has any non-zero tribeID (not necessarily this
             * tribe) or its membership bit is set in this tribe: decrements size (tribeState 3 when it reaches 0),
             * clears the membership bit, resets the unit's tribe fields only if unit.tribeID == tribeID and re-
             * elects the leader (setTargetUnitForTribe) if it was the leader. Always refreshes tribe.firstOccupiedMaskWord.
             */
            void removeUnitFromTribe(uint unitID, int tribeID);

            /**
             * Takes the first member (index 0) of the tribe, removes it from the tribe and returns its unit ID (0
             * if the tribe is empty).
             */
            int popUnitFromTribe(int tribeID);

            /**
             * Creates a new animal tribe (owner 0) at (x,y): deer, lion, rabbit or camel herds of random size (deer
             * 9-12, lion 3-4, rabbit 14-21, camel 2-5) if the tile is on-map and free of LogicLayer flags
             * 0x4A5014B1; crows mark nearby trees and seagulls spawn an entity instead (return 0). Sets
             * field137_0x280 = size/2 and field138_0x282 = size (lion) or 2*size, records the spawn point via the
             * per-species store function and returns the tribe ID. Machine code creates the tribe before validating
             * the tile, so the early 'return 0' paths (invalid tile, blocked tile, crow, seagull) leave an empty
             * active tribe behind. The 'tile' parameter is passed to spawnUnit in the height slot.
             */
            dword createAnimal(MappersEnum animalType, uint x, uint y, int tile);

            /**
             * Herd regrowth tick (not in the landscaping editor, tribeID > 0, field133_0x278 == 0): increments the
             * tribe respawn timer; when it reaches spawnInterval (quartered while size <= herdMinSize) it resets,
             * and if the herd is below herdMaxSize spawns one animal of unitType at the leader's position (deer: at
             * a member with antelopeBasedRngValue 1 if any) when (rng & 0x7F) >= threshold (25 while below min
             * size, 100 otherwise, 110 for rabbits during the rabbit-infestation event). Returns TRUE if an animal
             * was spawned.
             */
            BOOLEnum spawnDeerLionOrRabbit(int tribeID, int spawnInterval, UnitType unitType);

            /**
             * Wildlife spawn tick (skipped in the landscaping editor, for tribeID < 1, when field133_0x278 is set,
             * or for camels in mission 0x26): increments tribe.field_0x288; when it reaches spawnInterval it resets
             * and with ~22% chance (rng & 0x7F > 99) counts living units of unitType; if fewer than maxAnimalCount
             * it returns 1, creating a new camel herd at the leader's position only when unitType is camel (0x2F).
             * Returns 0 otherwise.
             */
            undefined4 trySpawnAdditionalWildlifeForTribe(int tribeID, int spawnInterval, int maxAnimalCount, int unitType);

            /**
             * Deer respawn tick (not editor / Siege That / builder-on-siege-map; currentGameMode GM_SOLITARY only):
             * if mapAndTime.aliveDeerCount != 0 and deerCount < 6, tries candidates 0..3 = deerSpawnLocationsXY[i]
             * and candidate 4 = signpostsMapEdge[0][0]; takes the first xyAreValid one whose tile is not blocked by
             * LogicLayer mask 0x50501581 (sea/rocky/wall/building/tree/river/keep/moat...), or is blocked but holds
             * an organism (tree), which is removed first. Then createAnimal(M_MAPPER_DEER) there with the tile
             * height. Blocked tiles without an organism are skipped.
             */
            void respawnDeer();

            /**
             * Single-player only, while mapAndTime.rabbitCount < 0xA0: scans 12 spawn slots (0..3 =
             * rabbitSpawnXY, 4..11 = int x/y pairs at 0x117E564+i*0x320 enabled by mercRecruitable[i+4]; the
             * decompiler mis-types this array) and creates a rabbit (createAnimal M_MAPPER_RABBIT) at the first
             * slot that is inside 400x400, flagged in the byte map 0x21AEC98 and free of LogicLayer mask
             * 0x50501581; remembers it in unknownX_01/unknownY_01. NAME? only rabbits are ever created; nothing
             * merc-related is spawned.
             */
            void spawnWildlifeOrMercAtAvailableSlot();

            /**
             * Map-load version upgrade for the tribes state: always runs the two Unknown upgrade steps, and the 142
             * upgrade when the map file version differs from the packager version and is below 0x8e.
             */
            void upgradeMapTribesState(
                PackagedFileMagicNum receivedMapVersion, PackagedFileMagicNum packagerMapVersion);

            /**
             * Moves a tribe to (x1,y1): rejects off-map / border (LogicLayer 0x30) / area-0 targets, checks area
             * connectivity from the leader (assassin-only, climbing, or cross-area bridge variants; falls back to
             * applyMoveCommandOrRallyCommandToTribe when the leader's area is 0 or canNavigate fails), optionally
             * stores a 2-point rally route, then path-searches around the destination with a radius growing by 500
             * until every living tribe unit stands on a reached tile (cap 0x13A0F, or 7999 for climbing / wall-or-
             * keep targets, then a full search toward the leader). Each eligible unit (alive, not held back, siege
             * engines only when fully crewed, never trebuchet/mangonel/ballista) gets a planned formation tile
             * (modulo step 1-4), is set US_MOVE_TO_DESTINATION and setDestinationForUnit is called; stranded
             * wall/keep units get an US_APPEAR teleport via the bridge tile. Move delays are computed but then
             * overwritten with 0. Returns 1 on success, 0 if invalid/unreachable; rallyBool is reused to hold the
             * previous search distance.
             */
            undefined4 giveTribeMoveInstruction(
                int tribeID, uint x1, uint y1, int rallyBool, int storeAsRallyPoint, UnitMatchSpeedEnum speedMatching);

            /**
             * Marks each living tribe unit as held back (rallyRelatedFlag=1) or eligible (0). Eligible:
             * goToRallyPoint==0, isSelectable_OR_matchTime!=0, more than 4 tiles from the destination, no live
             * melee target, not shooting a still-valid target (horse archers exempt; the countdown2 test indexes
             * the tribe g_tribeScanIndex, not tribeID), not in US_MELEE_ATTACK, not a slow siege engine unless
             * matchUnitSpeeds, not a busy oil engineer. If any unit is eligible, clears freeUnitSpeeds when
             * matching speeds and calls giveTribeMoveInstruction(rally 0, no store, UMSE_0); returns 1, else 0.
             */
            undefined4 commandUnitsToLocation(
                int tribeID, uint destinationX, uint destinationY, undefined4 matchUnitSpeeds);

            /**
             * Recomputes tribe statistics: unitType (0 if mixed), max movementSpeed (seeded from the leader), and
             * percentages (of the size after removals) of dying, moving (subTileStepProgress != 8), melee/wall-
             * attacking, ranged units in reload/aim/fire states and one other unit state (-> percentageSomething);
             * empty tribes get 100. percentageUnk29c/percentageUnk2a0 are only cleared. Members for which
             * isComputerManagedNonPeasant is TRUE are removed from the tribe.
             */
            void computeTribePercentages(int tribeID);

            /**
             * Per-tick tribe maintenance over tribes 1..0x4e1 (via g_tribeScanIndex): removes members that are
             * invalid (bad logical state, dying, or tribeID mismatch), counts tribes with valid members into
             * activeTribeCount and records the last such tribe in highestActiveTribeID. Clears tribes in state 3,
             * tribes whose members were all invalid, and empty tribes unless emptyKeepAliveUntilTick is non-zero
             * and not yet passed by mapTimeInTicks.
             */
            void updateTribeUnitAssignments();

            /**
             * Spawns queued troops as new tribes (batches of at most 9, behaviorTickCounter=0x32). The queue is the
             * 20-dword block startGoods[0x19..0x2c], which is the same memory as mapAndTime.siegeInformation
             * (0x117CE50). Builder/tutorial maps: scales every queued count by a difficulty/player-slot percentage
             * (50..167%), spawns all 20 queued kinds (kinds 18/19 have no case and reuse the previous type) and
             * SEC_Section1067.tunnelersCount tunnelers at unitMoveDestinationXYPairs (index wraps to 0 above 39),
             * then disables itself (reinforcementSpawnTimer=-1). Single-player missions: each time the timer
             * exceeds 200, takes one European (kinds 0..9 except ladder) and one Arabian (10..19) batch from the
             * queue and spawns a copy of it at every active player's campground. Skirmish: same timer (50 on
             * extreme trail), one batch per active player from that player's playerQueuedTroops. Disables itself
             * when nothing was spawned.
             */
            void spawnQueuedReinforcementWaves();

            /**
             * Dispatches a UnitInstructionType to all living units of a tribe; id_x_tile/unitUID_Y are the target
             * (unit ID+UID, building ID+UID, pitch-ditch ID+UID, tile, or x/y) and extraArg is an instruction-
             * specific extra argument. Handles move/clear, stop, attack unit (ranged/siege target directly,
             * catapult/trebuchet attack the target's tile, melee get intercept formation tiles via
             * pathPlanningForTribe and attackRetargetDelay = max(8, 8*longest half path)), attack land / throw cow
             * (catapult/trebuchet only with crew), fill/dig moat (fill falls through to dig), attack building/wall
             * (melee and fully crewed rams get cost-sorted access tiles), construct siege equipment / oil duty
             * (sends the required number of engineers to the building entry) and man siege equipment (engineers
             * sent to scatter tiles around the engine), exit siege equipment (crew fade back in on free tiles
             * around the engine, which becomes uncrewed), throw oil, 0x15 (sends one tunneler to the building
             * entry; if none can go the building is destroyed without rubble), set ladder, 0x1A (sets throwCowNext
             * on catapults/trebuchets), disband (siege engines are exited and refunded to the local player in Siege
             * That), 0x20/shoot target and light pitch. Returns 0 only when the target unit UID no longer matches
             * (attack/shoot) or the building entry is off-map (construct, 0x15); otherwise 1. Note: the man-siege
             * case clears chaseReturnX/Y of the siege engine, not of the engineer (as in machine code).
             */
            undefined4 giveTribeAnInstruction(
                int tribeID, UnitInstructionType unitInstructionType, int id__x__tile, int unitUID__Y, int param_5);

            /**
             * Scans the 40-entry nearby-tile offset table (DAT_UnitSelectionDefinedData.nearbyTileOffsets, XYPair
             * list at 0xB4DE00..0xB4DF44) around the tribe leader's tile and moves the tribe
             * (giveTribeMoveInstruction) to the first in-map (<400) tile that is flagged in the byte map at
             * 0x21AEC98 and reachable via isTribePathToDestinationClear. Does nothing if no candidate is found.
             */
            void moveTribeToNearbyClearTile(int tribeID);

            /**
             * Like moveTribeToNearbyClearTile but starts the scan of the 40-entry nearby-tile offset table at index
             * tribe.someIndex % 40 (negative -> 0), moving the tribe to the first in-map, flagged (byte map
             * 0x21AEC98) and path-clear tile and returning giveTribeMoveInstruction's result. If nothing is found
             * the machine code returns whatever is left in EAX (0 or the leader's y) - the source was probably
             * void; the 'return someIndex/40' branch is unreachable.
             */
            int moveTribeToIndexedNearbyTile(int tribeID);

            /**
             * Per-tick combat behaviour of a military tribe (human tribes and all tribes outside GM_SOLITARY via
             * updateTribes, plus AI tribes via TroopValueState). With a target (someUnitID/UID still valid) it re-
             * issues UIT_UNIT_ATTACK_UNIT when the target's destination tile changed, or when field168_0x2be has
             * run out and the target left someTile; an invalid target is cleared. Without a target and in
             * aggressive stance it walks the 10-slot ring of recent units, dropping invalid/same-team/other-area
             * entries; for the first enemy within 500 micro units it issues instruction 0x20 only when
             * unknownAttackRelatedUpdateCounter==0 and field93_0x22a==0x3B and no non-fighting melee-type member
             * has SA==0. Once the counter exceeds 50: rallying tribes advance along rally points after all units
             * arrived (ranged only if no enemy within 0x1B0, horse archers always, others if no enemy within 0x60
             * or not aggressive); non-rallying aggressive tribes every 60 ticks target a building (0x26) or wall
             * tile (0x25) within 15 via aggressiveStanceTargetBuildingAtRange; then a pending field134_0x27a
             * triggers moveTribeToIndexedNearbyTile.
             */
            void updateTribeCombatStanceBehavior(int tribeID);

            /**
             * Per-tick deer herd AI. Reads the leader's wildlife grid cell (10x10 tiles), marks the tribe as
             * animal, trims the herd to 30 and sets field137/field138 to size/2 and size*2, and starts panic
             * (field133_0x278=1) when lionCount+field18_0x48 != 0. If spawnDeerLionOrRabbit(100) returns TRUE the
             * herd picks a new rally point (radius 2) and moves there. Otherwise: initial positioning
             * (field64_0x204==0), editor reset, wandering along rally points on a timer (random 200-800 ticks, 200
             * when cell field16_0x40 != 0 or field17_0x44 > 20), resting (STBT_1, 800 ticks), or panic flight with
             * FX_DEER_RUN (scatter if no rally point) lasting 800 ticks.
             */
            void processDeerMoving(int tribeID);

            /**
             * Per-tick lion/wolf pack AI. Increments the tribe age counter (8000 -> 4000), marks it animal; while
             * countdown==0: if isTribeFreeOfTunnelingUnits and spawnDeerLionOrRabbit(500) succeed it just resets;
             * otherwise handles initial positioning (field64_0x204 0/1), editor reset, then alternates between
             * roaming (behaviour 0: new rally point at tick 0, move to its end at tick 150) and resting (STBT_1,
             * 300 ticks). When countdown is exactly 100 it sets all units to state 0xD0 and sets unknownBool01.
             */
            void updateLionWolfTribeBehavior(int tribeID);

            /**
             * Per-tick rabbit group AI. Reads the leader's wildlife grid cell, marks the tribe animal, calls
             * spawnDeerLionOrRabbit with rate parameter 80 (3 during a rabbit-infestation event; result ignored),
             * handles initial positioning, roaming via buildRallyPointPathForTribe /
             * findAndSetNewRallyPointForDeerAndLions (move at tick 150), resting STBT_1 for 400 ticks (20 if cell
             * field16_0x40 != 0 or field17_0x44 > 20), and panic scattering (field133_0x278) lasting 3000 ticks.
             */
            void updateRabbitTribeBehavior(int tribeID);

            /**
             * Per-tick camel herd AI. Increments age counter (8000 -> 4000), marks animal; tries
             * trySpawnAdditionalWildlifeForTribe(1000,10,0x2F) when isTribeFreeOfTunnelingUnits, handles initial
             * positioning (field64_0x204 0/1), roams to the last rally point found (behaviour 0) and rests (STBT_1)
             * for 800 ticks, or only 10 ticks while the herd is younger than 101 ticks. Resets the age counter in
             * the map editor landscaping view.
             */
            void updateCamelTribeBehavior(int tribeID);

            /**
             * Game-tick driver for all tribes: decrements the rabbit-infestation event countdown, then for tribes
             * 1..1249 with tribeState 2 decrements countdown2, recomputes percentages every 32 ticks (staggered by
             * tribe ID), and dispatches by tribeType: 0xD deer, 0xE lion, 0xF rabbit, 0x10 camel always go to their
             * animal handlers; for human-owned tribes, or any tribe when not GM_SOLITARY, everything else uses
             * updateTribeCombatStanceBehavior; for AI tribes in GM_SOLITARY the military types go to
             * TroopValueState::updateTribeBehaviorBasedOnBehaviorType, 0x11/0x12 are just marked animal, other
             * types use updateTribeCombatStanceBehavior. Finally decrements the tribe countdown.
             */
            void updateTribes();
        };

        static_assert_cpp98_obj(sizeof(TribesState) == 1029072, TribesState);

#pragma pack(pop)

    } // namespace Units
} // namespace Map
} // namespace OpenSHC
