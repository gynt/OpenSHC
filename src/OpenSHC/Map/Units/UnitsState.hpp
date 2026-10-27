/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/UnitsState.hpp'
*/

#pragma once

#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/IO/PackagedFileMagicNum.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Units/Instructions/MatchSpeedInstructionEnum.hpp"
#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "WinDef.h"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Game::Resources::ResourceType;
        using OpenSHC::IO::PackagedFileMagicNum;
        using OpenSHC::IO::Graphics::GmID;
        using OpenSHC::Map::Entities::EntityType;
        using OpenSHC::Map::Units::Unit;
        using OpenSHC::Map::Units::UnitInstructionType;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::Instructions::MatchSpeedInstructionEnum;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

        // SIZE: 0x002CA7E4
        class UnitsState {
        public:
            uint maxUnitCount; // 0x00000000 length: 4
            uint unitCount; // 0x00000004 length: 4
            // global counter bumped each time a blocked unit wait expires, before re-plan/stop/disappear (review
            // 356)
            undefined4 blockedMoveGiveUpCount; // 0x00000008 length: 4
            undefined4 lastSelectedUnitID; // 0x0000000C length: 4
            // Holds the armed unit command mode (1 normal, 4 attack unit, 5 attack ground, 0x14 engineer load, 0x16
            // throw cow).
            undefined4 unitCommandMode; // 0x00000010 length: 4
            // Set together with unitControlsRelated to the current unit command mode (TRUE, 4, 0x14) by unit-action
            // buttons / tribe creation; declared BOOLEnum but holds mode values.
            BOOLEnum pendingControlMode; // 0x00000014 length: 4
            undefined4 lostChimps; // 0x00000018 length: 4
            // [168 0x0054A7B0] reset to 100000 and lowered to the min distance of selectable enemies (assassins
            // only)
            undefined4 nearestSelectableEnemyDistance; // 0x0000001C length: 4
            undefined4 totalUnitsInSelection; // 0x00000020 length: 4
            int unitCountOfSelection[9]; // 0x00000024 length: 36
            byte unusedBytes01[44]; // 0x00000048 length: 44
            // width from machine code (short[200])
            byte selectedUnitsBitFlags[400]; // 0x00000074 length: 400
            byte unusedBytes02[852]; // 0x00000204 length: 852
            BOOLEnum hasEngineerSelected; // 0x00000558 length: 4
            // Holds the owner (units[].owner) of a non-local, non-neutral unit inside the drag box, not a unit id
            // (batch 163 code) Unit ID of a non-selectable (other player's) unit found in the drag box, written by
            // applyDragBoxSelectionByPriority/selectFirstUnitInDragBoxAnyPlayer; no reader in clean.exe
            int boxSelectedForeignOwner; // 0x0000055C length: 4
            // Unit ID of the selected catapult/trebuchet found by countSelectedCatapultsAndTrebuchets; sent as
            // command param by the toolbar button (cow throw).
            int selectedCatapultID; // 0x00000560 length: 4
            int selectionEuropeanArchers; // 0x00000564 length: 4
            undefined4 selectionSpearmen; // 0x00000568 length: 4
            undefined4 selectionMacemen; // 0x0000056C length: 4
            undefined4 selectionCrossbowmen; // 0x00000570 length: 4
            undefined4 selectionPikemen; // 0x00000574 length: 4
            undefined4 selectionSwordsmen; // 0x00000578 length: 4
            undefined4 selectionKnights; // 0x0000057C length: 4
            undefined4 selectionEngineers; // 0x00000580 length: 4
            int selectionLaddermen; // 0x00000584 length: 4
            int selectionTunnelers; // 0x00000588 length: 4
            int selectionMonks; // 0x0000058C length: 4
            int selectionCatapults; // 0x00000590 length: 4
            int selectionTrebuchets; // 0x00000594 length: 4
            int selectionBatteringRam; // 0x00000598 length: 4
            int selectionSiegeTower; // 0x0000059C length: 4
            int selectionShield; // 0x000005A0 length: 4
            int selectionMangonel; // 0x000005A4 length: 4
            int selectionBallista; // 0x000005A8 length: 4
            // [163 0x00535240] counter index 18 is zeroed but never incremented; fire ballistas are counted in
            // selectionFireBallista (index 26)
            int selectionUnusedIndex18; // 0x000005AC length: 4
            int selectionArabArcher; // 0x000005B0 length: 4
            int selectionArabSlave; // 0x000005B4 length: 4
            int selectionArabSlinger; // 0x000005B8 length: 4
            int selectionArabAssassin; // 0x000005BC length: 4
            int selectionArabHorseArchers; // 0x000005C0 length: 4
            int selectionArabSwordsman; // 0x000005C4 length: 4
            int selectionArabFireThrower; // 0x000005C8 length: 4
            int selectionFireBallista; // 0x000005CC length: 4
            int selectionSlots[8]; // 0x000005D0 length: 32
            int nHasOwnedUnitInSelection; // 0x000005F0 length: 4
            undefined4 climbX2; // 0x000005F4 length: 4
            undefined4 climbY2; // 0x000005F8 length: 4
            byte unusedBytes03[8]; // 0x000005FC length: 8
            // timeGetTime() of the first click on a single unit; a second click on the same unit within 500 ms
            // selects all units of that type
            dword doubleClickStartTimeMs; // 0x00000604 length: 4
            // Unit ID returned by selectionContainsCombatUnit for the first single-unit click (0 = armed, -1 =
            // disabled); compared with the clicked unit for the 500 ms double-click 'select all of type'
            uint doubleClickUnitID; // 0x00000608 length: 4
            // [160 0x0052E960] also set by nonEuroRecruit
            undefined4 recruitFailReason; // 0x0000060C length: 4
            undefined4 euroUnitRequiredResource; // 0x00000610 length: 4
            Unit units[2500]; // 0x00000614 length: 2920000
            // [165 0x00537AA0] used as a scratch list: index reset to 0, then every unit passing the prey filter is
            // appended
            short candidateUnitIDs[2500]; // 0x002C9454 length: 5000
            int unusedUnitIDArrayIndex; // 0x002CA7DC length: 4
            DWORD creationTime; // 0x002CA7E0 length: 4

        private:
            UnitsState(UnitsState const&);
            void operator=(UnitsState const&);

        public:
            UnitsState() {};
            ~UnitsState() {};

            // Constructor
            /**
             * UnitsState constructor: records creation time (timeGetTime), clears all units, resets
             * lastSelectedUnitID, unknownInitially0_01 and lostChimps, and sets maxUnitCount to 2500.
             */
            UnitsState* Constructor_UnitsState();

            /**
             * Resets the unit table: zeroes unit counts and the 9 selection-group counters, clears all 2500 unit
             * records (0x490 bytes each, starting at 0x138854C), sets maxUnitCount to 2500 and zeroes the tile
             * UnitLayer (0x27420 bytes = 80400 shorts at 0x1CD09E8).
             */
            void clearAllUnits();

            /**
             * Finds the first idle normal peasant of playerID (not in one of the busy/converting states) and orders
             * it to walk to the entrance of buildingID and turn into unitType (a worker). Stores workplace building
             * ID/UID and the entry tile as target. Returns the unit ID, or 0 if no peasant is available.
             */
            int assignPeasantToBuilding(UnitType unitType, int buildingID, int playerID, int workerIndex);

            /**
             * Recruits a European troop: checks gold cost (free outside single-player unless
             * skirmishTroopsCostGold), then the required weapon, armour and a third equipment resource, and a
             * stable horse when the table entry is -1; then converts the first idle peasant of playerID into
             * unitType, deducts gold and one of each equipment resource, links knights to a stable, counts the
             * troop in final results and assigns it to an AI tribe. If checkOnly is nonzero returns 1 as soon as a
             * suitable peasant is found (after all resource checks passed). Returns unit ID or 0, with the failure
             * reason (1 gold, 2 resource -> euroUnitRequiredResource, 3 no peasant, 4 no horse) in
             * euroUnitAcquisitionFailReason.
             */
            int euroRecruit(int unitType, undefined4 playersBarracksID, int playerID, int checkOnly);

            /**
             * Recruits a non-European unit (engineer 30, tunneler 30, ladderman 4, monk 10, Arabian archer 75,
             * slave 5, slinger 12, assassin 60, horse archer 80, Arabian swordsman 80, fire thrower 100 gold; other
             * types return 0). Checks gold, converts the first idle peasant of playerID into unitType with
             * workplace = recruitmentBuilding and resourceToDeposit cleared, deducts gold, counts the troop and
             * assigns it to an AI tribe. checkOnly != 0 returns 1 on finding a peasant. Returns unit ID or 0 (fail
             * reason 1 gold, 3 no peasant).
             */
            int nonEuroRecruit(UnitType unitType, undefined4 recruitmentBuilding, int playerID, int checkOnly);

            /**
             * Disbands a unit. Knights are untethered from their origin stable (if its UID still matches). In Siege
             * That mode the unit is marked ULS_REMOVE and its price (written by getPriceForDisbandedUnitType into
             * the unitID argument slot) is added to the current player's starting gold; the function then returns
             * the address of that gold field (nonzero garbage, not a status). Otherwise, if the owner has a
             * campground the unit is ordered to turn back into a peasant (returns 1); else it is set to
             * US_DISAPPEAR with killedFlagUnk (returns 0).
             */
            int disbandUnit(int unitID);

            /**
             * Assigns a random first-name index to a unit from the sync RNG: cows 0x49-0x4C, chickens 0x4D-0x50,
             * hunter dogs 0x51-0x54, quarry oxen 0x55-0x58, women (tanner, lady, mother, brewer, girl child sprite
             * 0x81) 0x34-0x47, everyone else 1-50; humans also get rng1_to_70 in 1..70 (animals keep 0). Advances
             * the RNG twice for humans, not at all for animals.
             */
            void assignNameToUnit(int unitID);

            /**
             * If unitID is valid and its UID matches unitUID, marks the unit for removal (ULS_REMOVE) and, when its
             * tribe still matches the stored tribe UID, removes it from that tribe. Used when a building is
             * deleted.
             */
            void removeUnitFromItsTribe(uint unitID, int unitUID);

            /**
             * Stops a unit's walking by clearing its path plan index/size, unknownMovementRelated_0x2d2 and
             * climbDataID. Really __thiscall on DAT_UnitsState (ECX), one stack arg.
             */
            void makeUnitStopWalkingByClearingPathProgressState(int unitID);

            /**
             * Returns UnitClimbStateFlags[property][unitType of unitID], i.e. whether the unit's type has the given
             * climb-related property.
             */
            int checkUnitHasPropertyBasedOnUnitType(int unitID, int property);

            /**
             * Recomputes the unit's buildingHeight offset (and resets drawYAdjust) from the tile's logic flags:
             * wall (0x800) 12; 0x100 (gate passage) 4 without building, 40 on a building, or -90 (0 if
             * terrainOrClimbHeight-90 < 8) while unknownCountdown_0x402 runs, setting wasOnStoneGate; 0x400 -> 2;
             * building top (0x10000000) -> getBuildingHeightForBuildingID (unless the countdown runs or the unit is
             * a siege tower), drawYAdjust from getBuildingHeightForBuildingID2 and terrainOrClimbHeight from the
             * building; drawbridge tile without flags -> 8 - terrainOrClimbHeight; plain tile after a gate restores
             * terrain height. Finally adds climbHeightOffset of unit DAT_CurrentUnitSlotID (the global current
             * unit, not unitID); harmless because all callers (updateUnits, commitMimmicLocation from
             * UpdateAssassin) pass DAT_CurrentUnitSlotID.
             */
            void recomputeUnitStandingHeight(int unitID);

            /**
             * Inserts unitID into the per-tile unit list (UnitLayer head + nextUnitOnTheSameTile) before the first
             * unit with a higher ID (list copied to a stack array of max 2000), rewrites the links and renumbers
             * unitOrderWhenOnSameTile. Then finds the lowest movementSpeed among list units with movementState ==
             * 2; walking the list, the first such unit at that lowest speed moves freely and every other such unit
             * with moveDelay 0 gets moveDelay = order/2+1. Skipped (except resetting unitOrderWhenOnSameTile) when
             * isHiddenInBuilding is set; an empty tile just gets unitID as head.
             */
            void setMoveDelayForUnitsOnSameTiles(int unitID, int unitIDCurrentTilePosition);

            /**
             * Removes unitID from the unit linked list of tile unitCurrentTilePosition (fixes the head or the
             * predecessor's nextUnitOnTheSameTile) and clears the unit's link and order; does nothing for tile 0 or
             * if the unit is not found. If the tile's list is empty it writes the link into dummy unit 0. NAME? it
             * unlinks rather than sets up.
             */
            void setupUnitSharingTileIDs(int unitID, int unitCurrentTilePosition);

            /**
             * Consistency check: returns 1 if unitID appears in the unit linked list of its own tile, or if the
             * unit is not in normal logical state / not tile-linked (unknownTestAgainst0_2 != 0); returns 0
             * otherwise (also for tile 0).
             */
            undefined4 isUnitRegisteredOnItsOwnTile(int unitID);

            /**
             * Returns 1 if any unit on the given tile is a ladderman in state 3 (presumably ladder raised), else 0.
             * Really __thiscall on DAT_UnitsState (ECX), one stack arg.
             */
            BOOLEnum ifAnyUnitOnSameTileIsLadder(int tile);

            /**
             * Checks the 4 neighbours of tile in directions 0, 2, 4, 6 of directionTranslationMatrix row y (despite
             * its name, y is a direction-table row) for a tile without any 0x4A5015B1 logic flags that has units
             * and a ladderman in state 3; returns 1 if found.
             */
            undefined4 ifAnyUnitOnSameTileIsLadderInRightDirection(int tile, int y);

            /**
             * Consistency check called during map rendering (single-player, or synced and not saving, and window
             * not already open): if a tile's unit list head is out of range (>2499) or any listed unit is not
             * actually on that tile (and not teleporting, field303_0x413 == 0), opens
             * multiplayerUnitSameTileLinkageTimeWindow (=1) and queues command 0x4F.
             */
            void triggerDesyncIfTileUnitLinkageInvalid(int tile);

            /**
             * Advances the tile-linkage repair window: values 1..99 are incremented and reset to 0 once above 49;
             * if the value is >=100 it is reset and all 80400 tiles are scanned, clearing out-of-range list heads
             * and, at the first unit not really on the tile, making its successor the new list head.
             */
            void removeUnitsSameTileLinkageIfNoLongerApplicable();

            /**
             * Every 8th tick per unit (4th on building/special tiles, every tick while unknownCountdown_0x402 runs)
             * recomputes calculatedMovementSpeed (higher = slower): unless tile flag 0x800000, steps
             * terrainOrClimbHeight toward the tile height with climb penalties, or matches the tribe's speed for
             * formation units; applies wading/sinking (negativeHeight, flags 0x20000000/0x40000000 and 0x200000)
             * with extra speed penalties; marks a tree/organism under the unit as state 3. Also registers spotted-
             * enemy tiles (flag 8), and sets field289_0x3ff when standing on a keep (building type 41-44); if the
             * keep belongs to another player and the live unit's owner has currentPlayerFullIDArray == -1,
             * increments attackInfo.enemyUnitsOnKeepCount.
             */
            void calculateUnitMovementSpeed(int unitID);

            /**
             * If the unit is seated, starts the stand-up animation (substate 100, animation cycle 0) and returns 1;
             * otherwise returns 0. Really __thiscall on DAT_UnitsState (ECX), one stack arg.
             */
            BOOLEnum standUpIfSeated(int unitID);

            /**
             * If the unit is standing, starts the sit-down animation (substate 101, animation cycle 0) and returns
             * 1; otherwise returns 0. Really __thiscall on DAT_UnitsState (ECX), one stack arg.
             */
            BOOLEnum sitDownIfStanding(int unitID);

            /**
             * Sets unitID's facingDirection to the orientation from it to targetUnitID (tile x/y), unless the
             * orientation is undefined (15).
             */
            void setFacingDirectionTowardUnit(int unitID, int targetUnitID);

            /**
             * Sets unitID's facingDirection to the orientation from its tile position to (targetX, targetY), unless
             * undefined (15).
             */
            void setFacingDirectionTowardCoords(int unitID, int targetX, int targetY);

            /**
             * Turns unitID one step (of 8) toward targetUnitID along the shorter rotation, updating facingDirection
             * and facingDirectionMapOrientationCorrected (= facing - mapOrientation, mod 8). Returns 1 if it
             * turned, 0 if no target, undefined orientation or already facing.
             */
            undefined4 setUnitFacingDirectionTowardsTarget(int unitID, int targetUnitID);

            /**
             * Sets unitID's orientation field toward targetUnitID using micro (sub-tile) positions, unless
             * undefined (15); knights get one step less (mod 8). Used at melee initiation.
             */
            void setFacingDirectionTowardUnitMicro(int unitID, int targetUnitID);

            /**
             * Turns unit unitID one 1/8 step (the shorter way round) toward world point (targetX,targetY) using
             * DirectionAlgorithmState::calculatePreferredRelativeOrientation, wraps facingDirection into 0..7 and
             * recomputes facingDirectionMapOrientationCorrected (facing minus map rotation, wrapped). Returns TRUE
             * only if the facing changed; FALSE if no orientation (15) or already facing the target.
             */
            BOOLEnum setUnitFacingDirectionForTargetXandY(int unitID, int targetX, int targetY);

            /**
             * Same as setUnitFacingDirectionForTargetXandY but the target point is building buildingID's (x,y):
             * rotates the unit's facing one step toward the building and updates the map-orientation-corrected
             * facing. Returns 1 if facing changed, 0 if buildingID==0, no orientation or already facing.
             */
            uint setUnitFacingDirectionBasedOnBuilding(int unitID, int buildingID);

            /**
             * Returns TRUE if the unit is not a peasant and its unit type has the COMPUTER_MANAGED flag in
             * UnitPropertiesDefinedData.
             */
            BOOLEnum isComputerManagedNonPeasant(int unitID);

            /**
             * Plays the 'hurt' sound for a unit at its position: wood-hit for siege engines, girl grunt for female
             * units (brewer, tanner, lady, mother, child with girl sprite 0x81), otherwise one of 8 body-hit sounds
             * chosen by fixedRng&7. Skips unit 0, units with healthPercentage<11, isStalked (animal/ambient) units,
             * mantlets with no operators, and non-positive types.
             */
            void playHurtSFXForUnit(int unitID);

            /**
             * Counts units 1..maxUnitCount-1 with logicalState ULS_NORMAL, not dying, whose unitType equals param_1
             * (machine code compares unit+0x6A2 = unitType, not owner). Used by trySpawnAdditionalWildlifeForTribe
             * to count animals of a species. NAME? counts living units of a given type, not of a player.
             */
            int countLivingUnitsOfType(int unitType);

            /**
             * For every live, non-dying unit owned by param_1 that is a siege tower (UT_S_TOWER) in state 9,
             * switches it to US_STONE_DEATH_01, resets animationCycleNumber and marks it dying (destroys a player's
             * idle siege towers; scenario event).
             */
            void triggerStoneTowerDeathForPlayer(int playerID);

            /**
             * Kills every live, non-dying unit with owner 0 whose isStalked byte (owner+0x296) is set: state
             * US_STONE_DEATH_01, animation reset, dying=1. NAME? only flagged (animal/ambient) unowned units are
             * killed, not all unowned units.
             */
            void killAllUnownedUnits();

            /**
             * Outside skirmish mode, puts every live, non-dying, unowned deer/wolf/bear/rabbit (UT_ANTELOPESHDEER,
             * UT_LIONSHWOLF, UT_CAMELSHBEAR, UT_RABBIT) into US_STONE_DEATH_01, resets its animation and marks it
             * dying.
             */
            void triggerDeathAnimationForAllWildlife();

            /**
             * Kills all live, non-dying, non-isStalked units owned by playerID: sets state US_STONE_DEATH_01,
             * animationCycleNumber=0, dying=1 and the short at isStalked+0xc4 to 1.
             */
            void killUnits(int playerID);

            /**
             * Loops unit slots 1..2499: units of fromPlayer that are lord, lady or jester get US_DISAPPEAR; other
             * units change owner to toPlayer (the int field at unitType-0x7e is also set when not isStalked or
             * already nonzero). isStalked units are skipped except ox, cow, hunter dog, chicken, mother, child,
             * juggler and fire eater.
             */
            void transferNonCourtUnitsToPlayer(int fromPlayer, int toPlayer);

            /**
             * Swaps unit ownership between two players: for each live unit owned by playerA or playerB,
             * lord/lady/jester get US_DISAPPEAR and every other unit is given to the other player (also the int
             * field at unitType-0x7e). Same isStalked type filter as transferNonCourtUnitsToPlayer.
             */
            void makeCourtMemberUnitsDisappearAndSwapAllOtherUnitsOwnership(int playerA, int playerB);

            /**
             * For each live, non-dying, non-isStalked unit of playerID (also requiring the short at
             * logicalState+0x218 to be 0) checks via PathFindingState whether the unit's path-connection area can
             * reach the player's campground area; unreachable units are set to US_DISAPPEAR, animation reset and
             * marked dying.
             */
            void makeUnitsDisappearThatCannotReachTheKeep(int playerID);

            /**
             * For every live, non-dying cow owned by playerID assigns a random value 0..299 (SEC_RNG.currentNumber2
             * % 300) to digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300 and advances the
             * RNG.
             */
            void setRandomNumberOnCows(int playerID);

            /**
             * Mission-specific lord setup: for missions 5, 6, 8 and 15 sets
             * unknownLordTypeBasedMissionSpecificValue_01 (unit+0xA48 = dying+0x194, verified) to 1 on all non-
             * local-player lords; for missions >15 only on those whose getLordTypeForPlayer==1. A killing lord with
             * this flag plays FX_ARAB_LORD_KILL.
             */
            void setMissionNumberSpecificLord(int missionNumber);

            /**
             * Returns 1 if the unit's state is 111..116 (0x6F..0x74, the death-animation states), else 0. NAME? it
             * detects a unit in a death animation, i.e. dying, not alive.
             */
            BOOLEnum isUnitInDeathState(int unitID);

            /**
             * Returns TRUE when attacker and target must NOT fight in melee (caller getEnemyUnitIDNearby accepts
             * the target only on FALSE). TRUE for traders/trader horses/ghosts; a bear only fights woodcutters and
             * wolves (and vice versa); wolves, war dogs and hunter dogs fight their listed prey animals plus non-
             * animal units (war dogs only other-team ones), other animals never initiate; non-animals fight wolves,
             * rabbits, oxen, cows, hunter dogs and other-team war dogs but not other animals; two non-animal units
             * are blocked (TRUE) only during skirmishNoRushTicks outside skirmish-single-player/solitary modes.
             * NAME? inverted: means 'melee is blocked'.
             */
            BOOLEnum isMeleeBetweenUnitsForbidden(int attackerUnitID, int targetUnitID);

            /**
             * Returns damage scaled by the owner's fear factor: damage * 5 * (fearFactorLevel + 20) / 100 (fear
             * level 0 = 100%).
             */
            int computeDamageFearFactorBonus(int damage, int playerID);

            /**
             * Applies one melee hit of unitID on unit2ID: damage from MELEE_DAMAGE[attackerType][victimType], fear-
             * factor scaled (not for lords); records last enemy player/unit on the victim, updates
             * health/percentage/healthbar. Alive victim: 'under attack' sound for the local player, returns 0.
             * Killed: sets dying, tribe flag, death state and plays weapon/death/lord/jester/girl sounds, returns
             * 1. Original-game bug (machine code): for a killed mantlet the crew-count check and for a killed child
             * the girl-sprite 0x81 check read the ATTACKER's fields instead of the victim's.
             */
            undefined4 processUnitAttackOtherUnit(int unitID, int unit2ID);

            /**
             * Applies projectile/entity damage to unitID. Cow poison clouds: 400/200/150 damage by tileDistance
             * 0/1/else, cut to 80/60/40% by the owner's healer count 1/2/3+, skipped on protected tiles, in
             * towers/keeps/gates or for immune types; always returns FALSE. Other projectiles: height-window hit
             * test, same-team rules, damage from siege tables (>20000 = instant splat kill) or
             * ARROW/STONE/BOLT_DAMAGE with fear bonus (halved vs siege units); reduced when launched from more than
             * 30 below the target (shooting upward); records shooter in the victim tribe's 10-slot ring buffer; on
             * death sets death state and plays death sounds. Returns TRUE if the hit applied, FALSE if ignored.
             */
            BOOLEnum processEntityDamageToUnit(int unitID, int entityID, int tileDistance);

            /**
             * Applies one tick of fire damage to unitID (lord 25, firefighter 1, Arabian fire thrower 10, others
             * 100; halved if halfTheDamage), records the attacking player (attacker unit cleared to 0), updates
             * health/percentage/healthbar. On death the lord enters US_STONE_DEATH_01 and is marked dying; other
             * units go ULS_TRANSITIONING and change into UT_BURNINGMAN or a big/small burning animal, with a
             * male/female burn scream for non-isStalked units. Returns 0 if unit invalid or already dying, else 1.
             */
            undefined4 processFireDamageToUnit(int unitID, int playerID, int halfTheDamage);

            /**
             * Spawns a projectile entity from unitID toward (targetX,targetY,targetZUnk) via
             * EntityState::spawnEntity. Launch position/height depend on projectile type (trebuchet +130, catapult
             * +56 with facing offset, mangonel +64 with facing offset, ballista +25, horse archer +45, arrows +30,
             * type 8 / ~ET_UNKNOWN +12 with facing offset); trebuchet/catapult launch ET_COW_FLYING instead when
             * field243_0x3b0 is set. Arrow-type shots pass shootTargetedUnit as target unit. Afterwards sets
             * countdown2=500 on the shooter's tribe (if any).
             */
            void shootProjectile(int unitID, EntityType projectileType, int targetX, int targetY, int targetZUnk);

            /**
             * Per-tick recompute of a player's battlefield view. Clears enemy counters/values; skipped (outside
             * solitary) for player slots that are neither human nor AI. Walks live, non-dying units: own-team
             * selectable units within 60 tiles of the player's campground entry add to totalTeamTroopValue. Other-
             * team units (some ambient types skipped): owned, manned (siege crew>0) selectable ones increment
             * totalEnemyUnitsCount (non-selectable only for lords) and, if within 60 of the campground and owned by
             * a human/non-AI player or targeting this player, add troop value per owner, to totalEnemyTroopValue
             * and - only for NON-ranged types - to totalEnemyRangedTroopValue. Every such unit (incl. owner 0) is
             * stored (index+uid) in the enemy list, reservoir-sampled beyond 2499.
             */
            void recomputeTroopValuesForPlayer(int playerID);

            /**
             * Returns playerDataArray[playerID].armySize.
             */
            int getArmySize(int playerID);

            /**
             * Only in GM_SOLITARY with at most 100 units: returns the smallest Chebyshev micro-position distance
             * from the unit to any still-valid (uid matches) entry in its owner's enemy list; otherwise (or if
             * none) returns 10000. The parameter slot is reused for the running minimum; a second minimum capped at
             * 1000 is computed but never used.
             */
            int computeDistanceToNearestEnemyForLegacyMissions(int unitIDThenMinDist);

            /**
             * Stub that always returns 0.
             */
            BOOLEnum returnFalseStub(int stackArg0);

            /**
             * Computes a scattered aim point for a ranged/siege unit around (microX,microY,z): random depth and
             * lateral offsets plus z jitter whose ranges depend on unit type (trebuchet, catapult, mangonel,
             * ballista attacking land, fire ballista not attacking land = z only, plain ballista = none, default),
             * z clamped to 8..250; if depth exceeds half the shooter-target Chebyshev distance depth and lateral
             * are halved, if it exceeds the distance it is negated; offsets are rotated by the unit's facing.
             * Stores the result in shootTargetMicroX/Y/Z.
             */
            void setRandomShootLocation(int unitID, int microX, int microY, int z);

            /**
             * Returns how many more engineers a siege engine needs: required crew (trebuchet 3, tower 4, ram 4,
             * mantlet 1, catapult/mangonel/ballista/fire ballista 2, siege tent 3 or 2 by fixedRng bit 1) minus
             * countCurrentlyManningEnginers; 0 for other types.
             */
            int getRemainingRequiredEngineers(int unitID);

            /**
             * Returns TRUE if the siege unit's owner currently counts any enemy units (totalEnemyUnitsCount>0);
             * else if targeting a building (UIT_ATTACK_BUILDING), whether the building uid still matches the stored
             * target uid - read from unit DAT_CurrentUnitSlotID, not unitID (machine code 0x5335BF); else whether
             * an enemy building/defensive structure is within 12 tiles of the shoot target tile.
             */
            BOOLEnum checkTargetBuildingPossibilityOrState(int unitID);

            /**
             * If the spearman stands on a wall tile (logic 0x100), scans its owner's enemy list for laddermen in
             * state 3 whose climb is usable from the spearman's path area; picks the nearest climb position
             * (Chebyshev, +10 penalty if already targeted), stores it in climbX2/climbY2, sets
             * shootTargetedUnit/targetUID/distanceToEnemyUnitLadders and marks the ladderman targeted (25). Returns
             * TRUE if a target was chosen.
             */
            BOOLEnum findAndAttackNearbyEnemyLaddermanInPosition(int unitID);

            /**
             * Checks the 8 neighbouring tiles (and every unit stacked on each) for an other-team ladderman in state
             * 3 (only if the unit's owner is nonzero). If found and checkOnly==0, kills it (dying, US_DEATH_02) and
             * returns 1; if checkOnly!=0 returns the direction index 0..7. Returns -1 if none.
             */
            int findAndDestroyAdjacentEnemyLadder(int unitID, int checkOnly);

            /**
             * Returns TRUE if the unit's secondary destination (destinationX_2Unk/Y_2Unk) differs from (x,y), FALSE
             * if equal (verified in machine code). NAME? the result is inverted relative to 'Equals'.
             */
            BOOLEnum destination2DiffersFrom(int unitID, int x, int y);

            /**
             * Returns TRUE if the unit's current (x,y) equals its secondary destination destinationX_2Unk/Y_2Unk.
             */
            BOOLEnum isAtSecondaryDestination(int unitID);

            /**
             * Returns TRUE if the unit's movement state (tunnelerFinishedDigging) is 0 and it either has no
             * climbDataID or stands on its secondary destination.
             */
            BOOLEnum hasUnitReachedDestination(int unitID);

            /**
             * Returns TRUE if the unit's tunnelerFinishedDigging field is 0. NAME? this is a generic 'movement
             * finished' test used by many unit types, not tunneler specific.
             */
            BOOLEnum isUnitMovementIdle(int unitID);

            /**
             * Computes a new RNG-noised walk-layer path for unitID (wandering/fleeing units): clears climb data,
             * copies the unit into slot 0 scratch, resets its 400-byte path plan and runs
             * PathFindingState::commitUnitPathPlanUsingWalkLayer(searchRangeLevel, doReturnPass,
             * excludeSameDistance); searchRangeLevel picks a search range of 80/200/500/1000/2000, doReturnPass !=
             * 0 makes the walker turn back down the distance field after the outbound climb ends,
             * excludeSameDistance != 0 forbids steps to tiles of equal distance. On success stores the plan length,
             * sets path start/previousTilePosition to the current position, clears cannotClimb and sets
             * movementState 2. Returns TRUE if a path was found.
             */
            BOOLEnum computeRandomWanderPath(int unitID, uint searchRangeLevel, int doReturnPass, int excludeSameDistance);

            /**
             * Shortens the unit's path plan by 'leftover' steps and recomputes destinationX/Y, the secondary
             * destination and destination tile by walking the remaining 4-bit direction steps from the path start.
             * If leftover >= plan length the plan is emptied and the destination becomes the path start (tile =
             * previousTilePosition); while climbing it only stores leftover for later.
             */
            void changeDestinationByAmount(int unitID, int leftover);

            /**
             * If the unit has a positive pending 'leftover' step count, calls changeDestinationByAmount with it.
             */
            void changeDestinationByLeftover(int unitID);

            /**
             * Walks the unit's path plan from the path start until reaching a tile with logic flag 0x800, truncates
             * the plan to that step (length = steps taken + 1, also +1 when no such tile is found) and sets
             * destinationX/Y and destination tile to that point (secondary destination untouched).
             */
            void tracePathFromLadderExitSetDestination(int unitID);

            /**
             * Updates a moving unit's fade/vanish state near walls, towers and gatehouses: classifies the current
             * tile (wall, tower level 1-4, gate 10/11), compares with the previous classification in field171_0x308
             * (1 wall, 2 tower, 3 gate) to choose a fadeType on entering, manages the gate countdown
             * unknownCountdown_0x402 and sets 'vanish' from MiscDisplayLayer flag 0x10.
             */
            void updateUnitFadeAndVisibilityNearStructures(int unitID);

            /**
             * Saves the unit's current state into state_3 and sets tunnelerFinishedDigging (movement state) to 5 =
             * interrupted. Really __thiscall (ECX = UnitsState used as base).
             */
            void saveUnitStateBeforeInterruption(int unitID);

            /**
             * If the unit's isSelectable_OR_matchTime is 0, it is not lord/lady/jester (types 55..57), stands on a
             * wall tile and PathFindingState says it is stranded on walls/keep, sets it to US_DISAPPEAR with fade
             * countdown 0.
             */
            void despawnUnreachableUnit(int unitID);

            /**
             * Recomputes orientationRelatedPositionX/Y from the unit's sub-tile micro position (low 3 bits of
             * microX/Y), rotated by map orientation, via a lookup in UnitPropertiesDefinedData.microPosScreenOffsets (x/y
             * pairs on an 8x8 grid).
             */
            void updateMicroPosition(int unitID);

            /**
             * Adds UnitOrientationRelatedOffset[screen facing] to the unit's orientationRelatedPositionX/Y (one
             * movement step in screen space).
             */
            void adjustUnitMapOrientationRelatedPositionBasedOnMapOrientationCorrectedFacingDirection(int unitID);

            /**
             * Walks the tunneler's path plan from its path start; on each tile without logic flags 0x20000081: if
             * no building and height or default height < 16, lowers terrain (brush -2) and zeroes height, otherwise
             * deals 5 damage via processDamageToBuilding; then refreshes walk/path layers at that tile.
             */
            void applyTunnelDamageAlongPathPlan(uint unitID);

            /**
             * Checks whether the unit's targetedBuildingTile (requires field64_0x90 != 0) is one of the 8
             * neighbouring tiles or a neighbour of a neighbour. Returns 0 if no target / not near; -1 if the tested
             * tile is neither wall (logic 0x100) nor building; otherwise stops the unit walking
             * (makeUnitStopWalkingByClearingPathProgressState) and returns 1 if movementRelated >= 8, else 0.
             * Original-game quirk (machine code): in the distance-2 case the outer loop does not stop after a hit,
             * so the wall/building test is made on the unit's 8th (direction 7) neighbour tile, not on the matched
             * one.
             */
            int stopUnitIfNextToTarget(int unitID);

            /**
             * Returns 1 if any of the 8 tiles around the unit belongs to its workplaceBuildingID_1, 0 otherwise or
             * if the unit has no workplace.
             */
            undefined4 isWorkplaceBuildingOnAdjacentTile(int unitID);

            /**
             * If the unit's workplace building still exists (uid matches workplaceBuildingUID) and
             * BuildingsState::buildingIsAccessible(building, entryAngleUnk) succeeds, sets the unit's
             * targetX_2/targetY_2 to the building entry tile and returns 1; else returns 0.
             */
            undefined4 setWorkplaceBuildingEntryAsTarget(int unitID, int entryAngleUnk);

            /**
             * Returns bit 30 of LogicLayer at the unit's tile (moat flag).
             */
            BOOLEnum unitIsInMoat(int unitID);

            /**
             * ORs the unit's occupancyOrFlag byte into the byte OccupancyLayer for the 3x3 tile block centred on
             * the unit's tile (row offsets from ptr_MovementDirectionTranslationMatrix, directions 0 and 4). The
             * code uses 16-bit ORs at byte addresses with a zero high byte, so effectively byte ORs; the
             * PathLinkageLayer+0x13a0f access is a mis-resolved OccupancyLayer[tile-1].
             */
            void stampOccupancyFlagOnSurroundingTiles(int unitID);

            /**
             * Writes the byte 'six' into SEC_TileMap1104 for the 3x3 tile block centred on the unit's tile (the
             * unitDeathHeatMap+0x13a0f access is a mis-resolved SEC_TileMap1104[tile-1]). NAME? the value is a
             * parameter, not fixed to 6.
             */
            void writeSixToTileMap1104InAllDirections(int unitID, undefined4 six);

            /**
             * Among live units of playerID (excluding unitID and types flagged in SomeUnitStatMatrix5; if zero2 is
             * 1 or 10 only units whose short at dying+12 equals zero2) picks the one with highest positive score =
             * (ticks since its someMatchTimeVariable) >> 5, minus distance/4 to (unitXPosition,unitYPosition) if
             * zero1 != 0. Stamps the chosen unit's someMatchTimeVariable with the current tick and returns its ID,
             * or 0. Used by lord/lady/jester to pick whom to visit.
             */
            int findEligibleUnitByTimeAndLocation(
                int unitID, int playerID, int unitXPosition, int unitYPosition, int zero1, int zero2);

            /**
             * Priest target selection: among live units of the priest's owner whose type is blessable and blessed
             * amount (int at dying+0x144) < 4000, within distance 40, returns the one maximizing (4000-blessed)/64
             * - distance/2 (must be > 0); 0 if none.
             */
            int selectNewBlessingTarget(int unitID);

            /**
             * Drag-box selection: first pass counts own units inside the screen box (lord, non-siege troops, each
             * siege type) and records a foreign non-neutral owner in field14_0x55c; second pass marks isSelected.
             * If any own unit is in the box, mode 0 selects all own units (the lord only if no other own unit is in
             * the box); otherwise mode 9 selects every non-own unit (incl. neutral) in the box. The per-siege-type
             * modes 1-8 are dead code: the mode slot (shared with the fire-ballista counter) is only ever set to 0
             * or 9 (machine code 0x534A6E/0x534A78) before the switch at 0x534B93.
             */
            void applyDragBoxSelectionByPriority();

            /**
             * Clears and rebuilds the selection: selects all of the current player's non-lord selectable units that
             * are either inside the mouse drag box (excluding idle siege towers and tunnelers in certain states) or
             * whose ifSelectedThenPlayerID equals the current player. Updates totalUnitsInSelection.
             */
            void selectUnitsInDragBoxForCurrentPlayer();

            /**
             * Selects only the first selectable unit (any owner, excluding idle siege towers and some tunneler
             * states) whose sprite rectangle intersects the drag box; if it belongs to another non-neutral player
             * its owner is stored in field14_0x55c. isSelected is cleared only for slots scanned before the hit
             * (later slots keep their flag); totalUnitsInSelection and field14_0x55c are reset first.
             */
            void selectFirstUnitInDragBoxAnyPlayer();

            /**
             * Selects every live unit with nonzero drawX (currently drawn) of the given type owned by the given
             * player and counts them in totalUnitsInSelection (count reset first; existing isSelected flags of
             * other units are not cleared here).
             */
            void selectAllUnitsOfTypeForPlayer(int playerID, int unitType);

            /**
             * Clears isSelected on all unit slots and sets totalUnitsInSelection to 0.
             */
            void deselectAllUnitsOneByOne();

            /**
             * If the unit is selected, clears isSelected and decrements totalUnitsInSelection; always returns a
             * pointer to the unit's isSelected field (EAX). Really __thiscall (ECX = UnitsState), leaves EDX
             * untouched.
             */
            void deselectUnit(int unitID);

            /**
             * Deselects all selected units whose unitType equals unitType, decrementing totalUnitsInSelection.
             */
            void filterUnitSelectionExcludeUnitType(int unitType);

            /**
             * Keeps only selected units of the given unitType: deselects every other selected unit and decrements
             * totalUnitsInSelection.
             */
            void filterUnitSelectionForUnitType(int unitType);

            /**
             * Recounts the current player's selected live units per troop type into the 27 selectionXxx counters
             * (sets nHasOwnedUnitInSelection when a counted type is found), then fills selectionSlots[0..7] with
             * the indices of the first 8 nonzero counters (-1 for unused) for the selection UI.
             */
            void recountUnitsInSelection();

            /**
             * Returns 1 if the selection contains engineers and no other counted type (counter index 7 only), else
             * 0. Really __thiscall (ECX = UnitsState, counters at this+0x564); does not touch EDX, which
             * getSelectedEngineerCarryingResource relies on.
             */
            BOOLEnum selectionContainsEngineersOnly();

            /**
             * Returns TRUE if selectionEngineers is nonzero.
             */
            BOOLEnum selectionHasEngineers();

            /**
             * Returns TRUE if the selection contains European or Arabian archers.
             */
            BOOLEnum selectionHasArchers();

            /**
             * Returns 1 if the selection contains any knights, laddermen, battering rams, trebuchets, catapults,
             * horse archers, fire ballistas or siege towers, else 0 (an 'any of' test).
             */
            undefined4 selectionHasMobileAssaultUnits();

            /**
             * Returns 1 if the selection contains at least one knight/ladderman/ram/trebuchet/catapult/horse
             * archer/fire ballista/siege tower and no unit of any other counted type, else 0 (verified in machine
             * code). NAME? it tests 'only these types', not a mix with infantry.
             */
            undefined4 selectionContainsOnlyAssaultUnits();

            /**
             * If the selection is engineers only, scans selected live units (using DAT_CurrentUnitSlotID as
             * cursor): returns 0 as soon as one belonging to another player is met; returns the first selected
             * engineer with resourceToDeposit != 0, or 0. selectionContainsEngineersOnly preserves EDX.
             */
            uint getSelectedEngineerCarryingResource();

            /**
             * Returns 1 if the selection contains tunnelers and no other counted type (index 9 only), else 0.
             */
            int selectionContainsTunnelersOnly();

            /**
             * Returns TRUE if the selection contains at least one ranged unit (archer, crossbow, Arab archer,
             * slinger, horse archer, fire thrower, fire ballista, catapult, trebuchet) and nothing outside that
             * set, else FALSE.
             */
            BOOLEnum selectionContainsRangedOnlyUnits();

            /**
             * Returns 1 if the selection contains laddermen and no other counted type (index 8 only), else 0.
             */
            int selectionContainsLaddermenOnly();

            /**
             * Returns TRUE if the selection contains Arabian assassins and no other counted type (index 22 only),
             * else FALSE.
             */
            BOOLEnum selectionContainsOnlyArabAssassins();

            /**
             * Returns 1 if the selection contains mantlets (selectionShield, index 15) and no other counted type,
             * else 0.
             */
            int selectionContainsShieldmenOnly();

            /**
             * Returns 1 if the selection contains mantlets, siege towers or battering rams and nothing else
             * (indices 13, 14, 15 only; verified in machine code), else 0. NAME? it is an 'only these types' test.
             */
            undefined4 selectionContainsOnlyShieldsTowersRams();

            /**
             * Returns 1 if the selection contains mantlets or siege towers and nothing else (indices 14, 15 only),
             * else 0. NAME? it is an 'only these types' test.
             */
            undefined4 selectionContainsOnlyShieldsOrTowers();

            /**
             * Returns 1 if the selection contains no archers, crossbowmen, Arab archers, slingers, catapults,
             * trebuchets, horse archers, fire throwers, fire ballistas, mangonels or ballistas, else 0.
             */
            undefined4 selectionHasNoRangedUnits();

            /**
             * Returns 1 if the selection contains engineers, slaves, spearmen, archers, macemen or pikemen, else 0.
             * NAME? these appear to be the moat-digging unit types (e.g. selectionHasMoatDiggers).
             */
            undefined4 selectionHasFootSoldiers();

            /**
             * Scans selected live units: returns 0 as soon as one belongs to another player; returns the unit slot
             * of the first selected lord owned by the current player, else 0. Leaves DAT_CurrentUnitSlotID at the
             * stop position.
             */
            uint getSelectedLordIDIfOwnedByCurrentPlayer();

            /**
             * Clears the 400-byte selected-unit bitmask at UnitsState+0x74 (one bit per unit slot, set by
             * TribesState::addUnitToSelected), then sets the bit for every live unit of the current player that is
             * selected and either not already marked as selected by this player (ifSelectedThenPlayerID) or the
             * game mode is not GM_SOLITARY. If any were added, allocates a tribe ID for the player and queues
             * GCT_UNITS_SELECT with it; returns the number of units added (0 otherwise).
             */
            int createUnitSelection();

            /**
             * Same as createUnitSelection but without the ifSelectedThenPlayerID/game-mode filter: sets the
             * selected-unit bitmask bit for all selected, alive units of the current player, allocates a tribe ID
             * and queues GCT_UNITS_SELECT. Returns the number of units added. NAME? It does not create the tribe
             * itself, it only queues the synced select command (the executor playerMakeUnitSelection builds the
             * tribe).
             */
            int createTribeFromSelectedUnits();

            /**
             * Executes the synced unit-selection command for playerID: marks all of the player's alive units that
             * TribesState reports as selected (ifSelectedThenPlayerID, selectionRelatedFlag,
             * unitCountOfSelection++), moves them out of their old tribes into a new player tribe (tribeID hint)
             * and copies stance/speed info. For the local player it plays selection feedback based on the tribe's
             * majority unit type: for siege engines still lacking engineers it plays 'need N engineers' effects
             * (0xB-0xD for 1-3, 0xE for more or none manning yet), for a catapult/trebuchet without stone the 'need
             * stones' line, otherwise the unit-type selection speech.
             */
            void playerMakeUnitSelection(int playerID, int tribeID);

            /**
             * Queues synced game command 0x48 with param0 = unitID and param1 = the current tribe ID. Its only
             * caller (InGameMenu_UnitSelectionAndControlsUnk at 0x435449) passes the not-yet-selected unit under
             * the cursor from getUnitInHitBox (already-selected units go to deselectUnit + command 0x4E instead);
             * the executor Commands::SiegeEngineRelated calls selectSiegeEngineAndPlayFeedback(player, param0,
             * param1), adding the unit to the current selection tribe. NAME? Returns nothing and searches nothing;
             * better 'queueAddUnitToSelectionCommand'.
             */
            void queueAddUnitToSelectionCommand(undefined4 unitID);

            /**
             * Executor of synced command 0x48 (add one unit to a selection tribe): removes unitID from its tribe,
             * marks it selected by playerID, increments the player's selection count and adds it to tribeID. If the
             * tribe belongs to the local player and the unit is a siege engine, plays 'need N engineers' (0xB-0xE)
             * or 'need stones' feedback, otherwise the unit-type selection speech; finally sets
             * MenuView_TriggerInitial. NAME? Works for any unit type, only the feedback is siege-specific.
             */
            void addUnitToSelectionTribeAndPlayFeedback(int playerID, int unitID, int tribeID);

            /**
             * Recalls control group section1099ID: deselects all alive units, then walks the group's 2500 (id, uid)
             * entries; entries whose unit still has the same uid and has unknownTestAgainst0_2 == 0 and
             * disappearFadeAlphaCountdown == 0 are re-selected and counted in totalUnitsInSelection, stale entries
             * are set to -1. If anything was selected, queues the selection via createTribeFromSelectedUnits.
             */
            void makeSelectionBasedOnShortcut(int section1099ID);

            /**
             * Returns TRUE only if the build-menu view (MVT_BUILD_MENU) shows tab 0x3D/0x3E and control group
             * unitHotKeyNumber equals the current selection: every alive unselected unit is absent from the group's
             * 2500 entries and every alive selected unit is present. The digit-key handler in
             * WindowMsgProcessingFunc uses TRUE (second press of the same group key) to centre the camera on the
             * group's first unit, FALSE to escape and recall the group. NAME? It checks 'group already selected',
             * not availability.
             */
            BOOLEnum isHotkeyGroupAlreadySelected(int unitHotKeyNumber);

            /**
             * For each unit in tribe tribeID, marks it as selected by playerID (ifSelectedThenPlayerID) and
             * increments that player's unitCountOfSelection.
             */
            void selectTribeUnitsForPlayer(int playerID, int tribeID);

            /**
             * Returns the unit type of the first alive selected unit; returns -1 if that unit is not owned by the
             * current player and 0 if nothing is selected. Leaves DAT_CurrentUnitSlotID at the found slot.
             */
            UnitType getUnitTypeOfFirstSelectedUnit();

            /**
             * Scans selected alive units: returns 0 as soon as a selected unit is not the current player's; returns
             * 1 for the first selected unit that is not a trebuchet (0x28), mangonel (0x29) or ballista (0x3D);
             * returns 0 if none qualifies.
             */
            undefined4 selectionHasMovableNonSiegeUnit();

            /**
             * Returns the slot ID of the first alive selected unit whose type equals either given unit type; 0 if
             * none or if a selected unit belongs to another player.
             */
            uint getFirstSelectedUnitOfEitherType(int unitTypeA, int unitTypeB);

            /**
             * Returns the highest stoneAmmunition among the selected catapults/trebuchets of the current player (0
             * if none or if a selected unit belongs to another player).
             */
            int getMaxStoneAmmoInSelectedSiegeEngines();

            /**
             * If the current player has a keep, counts selected catapults/trebuchets and stores the last one's unit
             * ID in field15_0x560 (reset to 0 first); returns 0 (none / foreign unit selected / no keep), 1
             * (exactly one) or 2 (several).
             */
            undefined4 countSelectedCatapultsAndTrebuchets();

            /**
             * Returns the slot ID of the first selected alive engineer of the current player; 0 if none or if a
             * selected unit belonging to another player is met first.
             */
            uint returnFirstSelectedEngineer();

            /**
             * Returns the slot ID of the first selected alive tunneler of the current player; 0 if none or a
             * foreign selected unit is met first.
             */
            uint getTunnelerIDOnlyIfFirstSelected();

            /**
             * Returns the slot ID of the first selected alive unit of type UT_E_LADDER owned by the current player;
             * 0 if none or a foreign selected unit is met first.
             */
            uint getFirstSelectedLadderUnitID();

            /**
             * Returns 1 if any selected alive unit of the current player has unitCanClimb set, 0 otherwise (also 0
             * if a foreign selected unit is met first).
             */
            undefined4 canAUnitClimb();

            /**
             * Returns the slot ID of the first selected catapult, trebuchet, mangonel, ballista or fire ballista of
             * the current player; 0 if none or a foreign selected unit is met first.
             */
            uint getFirstSelectedSiegeEngineID();

            /**
             * Returns the slot ID of the first selected catapult or trebuchet of the current player; 0 if none or a
             * foreign selected unit is met first.
             */
            uint getFirstSelectedCatapultOrTrebuchetID();

            /**
             * For the given tile: if it holds a tower or keep, counts current-player units standing on the
             * building's tiles. Returns TRUE if that count reaches capacity (size^2, 5 for BT_TOWER1), or if it is
             * at least half capacity and twice the free room is less than the summed selection counts of categories
             * 2-28 except 8, 10 and 13-16; else FALSE.
             */
            BOOLEnum isTowerTileOvercrowdedByCurrentPlayer(int tileOrOwnUnitCount);

            /**
             * Returns 0 if any selected alive unit belongs to another player or lacks unit-type property 1 (table
             * 0xB55E40: only E_ARCHER, E_SPEARMAN, E_MACEMAN, i.e. ladder climbers), otherwise 1 (also 1 when
             * nothing is selected). NAME? Semantics are 'all selected units can climb ladders', the inverse of the
             * name.
             */
            undefined4 allSelectedUnitsCanClimbLadders();

            /**
             * Returns TRUE if unitID is a catapult/trebuchet/siege tower/ram/mantlet with no manning engineers and
             * the current selection contains engineers (selectionEngineers != 0), i.e. the selected engineers can
             * be sent to man it. NAME? It tests one target unit against the selection, not the selection itself.
             */
            BOOLEnum canSelectedEngineersManSiegeEngine(int targetUnitID);

            /**
             * Starting at slot unitID, builds a unitType->first unitID map of the current player's selected alive
             * units, then returns one representative unit by fixed priority (archers/crossbowmen and other ranged
             * first, then siege engines, melee, utility units, lord, towers/rams/shields); -1 if nothing selected.
             * NAME? Returns a representative selected unit ID rather than testing for combat units.
             */
            int getRepresentativeSelectedUnitID(uint unitID);

            /**
             * Queues GCT_ESCAPE with param0 = 0, which the executor (clearOrDeselectUnitFromSelection) treats as
             * 'clear the whole selection'.
             */
            void queueEscapeCommand();

            /**
             * Queues GCT_ESCAPE with param0 = -1 and param1 = unitType; executed as clearTribesOfUnitType, i.e.
             * removes that unit type from the selection.
             */
            void queueDeselectUnitTypeCommand(undefined4 unitType);

            /**
             * Queues GCT_ESCAPE with param0 = -2 and param1 = unitType; executed as clearTribesNotOfUnitType, i.e.
             * keeps only that unit type selected.
             */
            void queueSelectOnlyUnitTypeCommand(undefined4 unitType);

            /**
             * GCT_ESCAPE executor: unitID -1 removes unitType from the player's selection, -2 keeps only unitType,
             * 0 clears the player's selection (count and ifSelectedThenPlayerID of all their units), any other ID
             * removes that unit from its tribe (if any) and, if it was marked selected, clears the mark and
             * decrements the player's selection count.
             */
            void clearOrDeselectUnitFromSelection(int playerID, uint unitID, int unitType);

            /**
             * Resets unitCountOfSelection for players 1-8 and clears ifSelectedThenPlayerID on every unit slot.
             */
            void clearSelectionCountsAndPlayerIDs();

            /**
             * Queues GCT_UNITS_MOVE (tribe, x, y, patrol, matchUnitSpeeds), then local speech feedback unless the
             * representative selected unit's tile has logic flag 0x40000000: reachability = area connection from
             * that unit to the hovered tile; if the selection has assault units, a target tile with flags
             * 0x10000100 or a failed path search also counts as unreachable. Speech is only played for the local
             * player's tribe, never for mangonel/ballista/trebuchet, and for archers/crossbowmen/catapults only
             * when matchUnitSpeeds is set: 9 if unreachable, otherwise selection sound then 10 (far, |dx| or |dy| >
             * 0x48 from the tribe's lead unit) or 6, skipped while a sound is busy or the lead unit is an engineer
             * carrying a resource.
             */
            void giveMoveCommand(int tribeID, int x, int y, int patrol, int matchUnitSpeeds);

            /**
             * Executes a human move order for tribeID: if bit 7 of speedMatching is set, clears it and sets the
             * tribe's freeUnitSpeeds flag (else clears it), then calls TribesState::giveTribeMoveInstruction with
             * the target x/y, rally flag and 1.
             */
            void giveTribeMoveInstructionHumans(
                int tribeID, uint x, uint y, int rallyBool, MatchSpeedInstructionEnum speedMatching);

            /**
             * Queues GCT_UNIT_EXTEND_RALLY_POINT with tribe ID, mouse x/y and rally count.
             */
            void extendRallyPoint(int tribeID, int mouseX, int mouseY, int rallyCount);

            /**
             * Queues synced command GCT_GIVE_UNITS_INSTRUCTION (0x24) with param0 = tribe ID and param1 =
             * instruction type. Command 0x24 is dispatched (handler table 0xB38E10[0x24]) to
             * Commands::ClickGiveUnitsInstruction, which deserialises param0 (2 bytes), param1 (1 byte), param2-4
             * (4 bytes each) and calls relayTribeInstruction(param0..param4), so this is the generic synced 'give
             * tribe an instruction' command.
             */
            void queueDisbandAndAttackCommand2Params(undefined4 tribeID, undefined4 instructionType);

            /**
             * Queues GCT_GIVE_UNITS_INSTRUCTION (generic tribe instruction) with tribe ID, instruction type and
             * first target (unit ID, x or tile).
             */
            void queueDisbandAndAttackCommand3Params(undefined4 tribeID, undefined4 instructionType, undefined4 targetIDOrX);

            /**
             * Queues GCT_GIVE_UNITS_INSTRUCTION (generic tribe instruction) with tribe ID, instruction type,
             * target ID/x/tile and target UID/y.
             */
            void queueGiveUnitsInstructionCommand4Params(
                undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4);

            /**
             * Queues GCT_GIVE_UNITS_INSTRUCTION (generic tribe instruction) with all five params: tribe ID,
             * instruction, target ID/x/tile, target UID/y and the fifth giveTribeAnInstruction argument.
             */
            void queueDisbandAndAttackCommand5Params(undefined4 param_1, UnitInstructionType instruction,
                undefined4 param_3, undefined4 param_4, undefined4 param_5);

            /**
             * Thin wrapper: forwards (tribeID, instructionType, target1, target2, extra) to
             * TribesState::giveTribeAnInstruction. Called by the synced executor
             * Commands::ClickGiveUnitsInstruction (command 0x24) and directly (unsynced) by AI code and
             * setupBuildingData.
             */
            void relayTribeInstruction(
                int tribeID, UnitInstructionType instructionType, int targetID_1, int targetID_2, int param_5);

            /**
             * Picks a free standing tile 2 tiles away from `tile` (typically a wall tile, e.g. for siege-tower
             * docking) for unitID: tests the (x,y-2), (x+2,y), (x,y+2) and (x-2,y) tiles; returns 0 if none is in a
             * path area reachable from the unit's area. Drops the y+-2 pair unless (x-1,y) and (x+1,y) both carry
             * logic flag 0x100, and the x+-2 pair unless (x,y-1) and (x,y+1) do; drops a candidate whose footprint
             * (per-direction XYPair offset lists in UnitPropertiesDefinedData) hits a valid tile with flag 0x100 or
             * 0x4A5014B1 or a building other than a killing pit. Returns the remaining candidate tile nearest to
             * the unit, or 0.
             */
            uint findFreeTileNearby(uint unitID, uint tile);

            /**
             * Tunneler target search from originBuildingID: uses the building's tunnelerCounter (attempt 0-5) to
             * choose search radius 20/20/40/40/80/80, alternates the start tile between (x, y-1) and (x-1, y)
             * stored in someX/someY, increments the counter and runs algTunnelerFindTarget against targetPlayer.
             * Returns TRUE (counter reset to -1) when a target tile was found; FALSE otherwise. A negative counter
             * fails immediately; a call with counter > 5 sets it to -1 and fails.
             */
            BOOLEnum findTunnelTarget(int originBuildingID, int targetPlayer);

            /**
             * Returns the unit ID of playerID's lord if it is in ULS_NORMAL and not dying; 0 if none.
             */
            int getAliveLordForPlayer(int playerID);

            /**
             * Counts unit slots 1..2499 whose unitType is UT_ANTELOPESHDEER (0x2C), regardless of state or owner
             * (unrolled 3 per iteration).
             */
            int getRawDeerCount();

            /**
             * For hunter param unit: finds the nearest alive, unowned deer whose distance is greater than 20
             * (second pass if none: greater than 5) and either at least 54 away or reachable by an arrow from the
             * hunter (arrowShootingRelated result 1..0x1B0). Returns the deer's unit ID or 0.
             */
            int findNearestShootableDeer(int hunterIDOrMinDist);

            /**
             * Returns the ID of the cow owned by playerID nearest to (x, y) that is alive and in state
             * US_DETERMINE_NEXT_STATEUnk, with distance below 10000; 0 if none.
             */
            int findNearestIdleCowForPlayer(int playerID, int x, int y);

            /**
             * Lion prey search: for a valid (x, y) tile, scans alive units not in US_MELEE_ATTACK with a zero short
             * at dying+0xB8 bytes that are in the same path area and within maxDistance; with excludeCows FALSE
             * only deer/rabbits/cows qualify, with TRUE any unit whose byte at dying+0x8C is 0 (so 'excludeCows'
             * really widens the filter to all unit types). Records candidates in unusedUnitIDArray and returns the
             * one with the lowest distance + 3*(short at dying+0x112), or 0. NAME? Returns the closest prey unit,
             * nothing is stored as a 'result'.
             */
            int findClosestPreyInArea(int maxDistance, BOOLEnum excludeCows, uint x, uint y);

            /**
             * Cage-dog target search: for valid tile (x, y) returns the alive enemy unit (team differs from
             * playerID's team, not melee-attacking, short at dying+0xB8 bytes and byte at dying+0x8C both 0) in the
             * same path area within maxDistance with the lowest distance + 3*(short at dying+0x112); 0 if none.
             * Also resets unusedUnitIDArrayIndex to 0 without appending to the array.
             */
            int findClosestEnemyByAreaAndRange(int maxDistance, uint x, uint y, int playerID);

            /**
             * Makes animal unitID_1 attack unitID_2 (> 0) if both are alive and unitID_1 is not already in state
             * 0xCF or US_MELEE_ATTACK: stores the target ID/UID, increments the victim's huntedBy, sets state 0xCF
             * and requests a new destination. Returns 1 on success, 0 otherwise.
             */
            undefined4 tryAttackUnitID(int unitID_1, int unitID_2);

            /**
             * When a tower is deleted: if it holds a mangonel (containsSiegeMangonel1OrBallista2 == 1) or ballista
             * (== 2), finds the first alive unit of that type whose tile belongs to the building (BuildingLayer ==
             * buildingID, scanning from slot 0) and sets its state to US_STAND_UPUnk|US_IDLEUnk.
             */
            void setTowerSiegeEngineToIdle(int buildingID);

            /**
             * For player slots 1-8 whose currentPlayerFullIDArray entry is -1 (empty), sets
             * playerDataArray[i].aiControlStatusRelated = 100000.
             */
            void setAIControlStatusTo100000();

            /**
             * Peasant-menu action text: returns the TEXT_UNIT_ACTIONS index describing what the unit is doing and
             * writes the related goods type to *pResourceType (0 if none). Dying -> 0xC; state 0x79 or production
             * paused -> 'wandering/resting' 0x5F + signed fixedRng%4; state 0x6A -> 'Fighting' 0x73; otherwise a
             * per-unit-type switch over the state (fletcher/smith/armorer stages ask
             * getStorageBuildingForResourceTypeAndAmount whether the raw material is in store).
             */
            int getUnitActionTextIdAndGoods(int unitIndex, ResourceType* pResourceType);

            /**
             * Maps the unit's type to the GID_BODY_* sprite group drawn in the chapel/church menu and the status-
             * menu chimp view (default GID_BODY_PEASANT).
             */
            GmID getPeasantGmID(int unitID);

            /**
             * Church wedding pick: collects up to 100 non-invisible units with a male job (woodcutter..jester list)
             * whose firstNameIndex < 51 as husband candidates and up to 100 brewers/tanners/mothers with
             * firstNameIndex >= 52 as wife candidates, excluding the previous couple (0xEE102C/0xEE1028). Picks one
             * of each with SEC_RNG; if that pair is not among the 8 recent pairs starting at g_recentMarriagePairs
             * it writes them to *husbandID/*wifeID, shifts the pair history by one, stores the new pair at its head
             * and as the previous couple, and returns 1; otherwise (or with no candidates) returns 0.
             */
            undefined4 chooseHusbandAndWife(int* husbandID, int* wifeID);

            /**
             * Returns 1 if the worker unit is in its job-specific 'waiting at workplace' state (e.g.
             * woodcutter/miller/smith US_STAND_UPUnk, fletcher US_LOOK_AROUNDUnk, wheat farmer state 10, baker
             * US_FIRE_WEAPONUnk), else 0. Really __thiscall on UnitsState (uses ECX as the unit array base).
             */
            undefined4 isWorkerAtProductionIdleState(int unitID);

            /**
             * For a non-dying worker in a waiting state, returns the 'blocked' speech/morale ID explaining why it
             * cannot work: 0x32 no tree found, 0x33 no wood in stockpile (fletcher, poleturner), 0x34 no deer, 0x35
             * no wheat, 0x36 no flour in the bakery, 0x37 no hops, 0x38 no iron, 0x39 no cow, 0x3A no ale;
             * 0x2F-0x31 for other waiting states. Returns 0 if not stuck or the needed resource exists. BUG
             * (original game, display only): the baker and brewer branches read workplace/owner of
             * DAT_CurrentUnitSlotID (the global unit-scan cursor) instead of unitID, so their 'no flour'/'no hops'
             * result is computed for an unrelated slot.
             */
            int getWorkerBlockingStateIfStuck(int unitID);

            /**
             * Returns the first unit owned by the given player that is in ULS_NORMAL, not dying, has
             * isSelectable_OR_matchTime set, and is a siege engine (catapult, trebuchet, mangonel, ballista, fire
             * ballista, ram, tower or mantlet); 0 if none. NAME? The parameter is compared with the unit owner and
             * the caller passes a player index, so it searches per player, not per tribe.
             */
            int findActiveSiegeEngineOfPlayer(int playerID);

            /**
             * Returns the first unit of playerID in ULS_NORMAL, not dying and with isSelectable_OR_matchTime set; 0
             * if none.
             */
            int getLivingSelectableUnit(int playerID);

            /**
             * Debug overlay: if no unit is watched (lastSelectedUnitID < 1) prints totals (chimps, flies/entities,
             * climb teleports, greatest loading, zones, lost chimps); otherwise prints many fields of the watched
             * unit (type, owner, status, dying, next on tile, teleport, sloth, enemy distance, facing, height,
             * state, anim/gfx, hp, hunted-by, tribe, ...) at (x, y).
             */
            void renderDebugDataUnitData(int x, int y, int width, int height);

            /**
             * Initialises a unit slot for unitType from UnitPropertiesDefinedData: sprite IDs, origin and draw
             * offsets, movement speed, HP (healthPercentage always ends up 100, healthbar 10),
             * climb/melee/notice/movable stats; assigns a name if it has none or is a
             * brewer/tanner/lady/mother/juggler/fire-eater/priest; sets the owner bit mask and its complement (both
             * 0xFF when unowned); unknownBool01 = 500 except for cage dogs, assassin distance 32000.
             */
            void setUnitValues(int unitID, UnitType unitType);

            /**
             * If the unit has a pending move (field105_0xe8 != 0), commits nextTileUnk and mimic x/y as its tile
             * and position; then updates move delays of units sharing that tile.
             */
            void commitPendingUnitPosition(int unitID);

            /**
             * Wrapper: calls setupUnitSharingTileIDs for the unit's current tile.
             */
            void setupUnitSharingCurrentTilePosition(int unitID);

            /**
             * If the unit's x/y disagree with its tile index, resets x/y, mimic position and micro position
             * (tile*8+4) from the tile and calls updateMicroPosition. NAME? It snaps x/y to the unit's tile rather
             * than teleporting.
             */
            void teleportUnitToUnitXAndY(int unitID);

            /**
             * Walks the unit chain on tileUnk (up to 2000 links) and returns the first unit that is not dying, has
             * unknownTestAgainst0_2 == 0 and moveRelatedFlag != 1, whose height is within +-32 of unitHeight, for
             * which shouldUnitsEngageInMelee returns FALSE (i.e. melee allowed), and that is on another team (or
             * the searcher is unowned); 0 if none.
             */
            int getEnemyUnitIDNearby(int unitID, int tileUnk, int unitHeight);

            /**
             * Sets the shooter's shootTargetMicroX/Y/Z: if targetID == -1 re-randomises around the current shoot
             * target (setRandomShootLocation); else the target's tile centre and height, led ahead along its facing
             * (lead = leadAmount*1.33 scaled by its speed) when the target has an active path
             * (tunnelerFinishedDigging == 2). Then inaccuracy: if the target is below the shooter's buildingHeight
             * only siege engines get an error budget (catapult/ballista 20, trebuchet 50, mangonel 60, fire
             * ballista 10), other units none; otherwise budget = height difference (x1.5 above 75) plus 40/60/70
             * for catapult+ballista/trebuchet/mangonel, none for fire ballista, capped at 280. With probability
             * budget/300 (SEC_RNG) it jitters X/Y or offsets Z. Return value is incidental.
             */
            int prepareProjectileTarget(int shooterID, int targetID, int leadAmount);

            /**
             * Chooses a shooting target for catapult/trebuchet/mangonel/ballista/fire ballista (catapult/treb
             * without stone return 0; in non-GM_SOLITARY games an AI owner tries to restock). If attacking a
             * building: returns 0 and clears targetingType when its uid no longer matches, else aims at its centre.
             * Otherwise reuses the previous target tile if it is still an enemy-team wall at least 31 above its
             * default height (not for fire ballistas), else searches with
             * findBestAttackTargetTileWithHeightAndOwner; on failure it increments attackFacingDirection (idling
             * catapults/fire ballistas after 16 tries under some AI/mode conditions), stores -50 and returns 0. On
             * success calls setRandomShootLocation and returns 1.
             */
            undefined4 harassBuildingsWithSiegeAI(int unitID);

            /**
             * Plans a path for unitID to tile (x, y): fails on an invalid tile, a target with logic flags 0x30, or
             * (for units unable to climb towers) flags 0x10000100; returns TRUE immediately if already there. If
             * the target is in another path area, resolves reachability and a climb point (climbX/Y) via climb data
             * (moat units first get their area from canNavigateFunctionReturnsArea). Then runs doPathfinding (or
             * retraceAndCommitPathPlan when reusePathingInfo) and stores the plan, destination and path state 2. On
             * failure calls despawnUnreachableUnit and returns FALSE.
             */
            BOOLEnum setDestinationForUnit(int unitID, uint x, uint y, int reusePathingInfo);

            /**
             * If the unit is alive and not being removed, restores the state saved before an interruption
             * (state_3), clears tunnelerFinishedDigging (movement mode) and re-sends it to its saved destination
             * (destinationX_2Unk/destinationY_2Unk), then applies the leftover destination offset. For wolves/cage
             * dogs it also sets US_MOVE_TO_DESTINATION and tail-calls
             * makeUnitStopWalkingByClearingPathProgressState, both on DAT_CurrentUnitSlotID rather than unitID;
             * every call path (via resumeMovementIfNoAttackTarget from the per-type Update* routines) passes
             * DAT_CurrentUnitSlotID, so in practice this is the same unit.
             */
            void resumeMovementAfterInterruption(int unitID);

            /**
             * Ends a ladder climb: clears vanish/teleport/climb-step flags, calls setupUnitSharingTileIDs with
             * ladderExitTile and then zeroes it, re-registers the unit on its current tile, snaps it to its mimic
             * tile position (x/y, tile index, tile-centre micro position) and commits the new position.
             */
            void exitLadder(int unitID);

            /**
             * Scans all units (DAT_CurrentUnitSlotID as loop cursor) for one under the mouse selection box: normal,
             * alive, not hidden in a building, not in US_FADE_TRANSITION; hit test is the sprite rectangle, or
             * within 1 tile of the viewport mouse tile when mouseOverMinimap is set. Skips siege towers / tunnelers
             * in certain states, bears, and deer unless the selection contains ranged units. Returns the first unit
             * ID matching filterMode (0 any, 1 enemy team, 2 own siege engine/shield, 3 own unit, 4 selectable non-
             * neutral, 5 own selectable, 6 own ladderman), else 0.
             */
            uint getUnitInHitBox(undefined4 filterMode);

            /**
             * Writes the unit's path-connection area into PathConnectionLayer at its targeted building tile and
             * asks the pathfinder for a free tile next to that enemy defensive structure, passing the facing
             * direction and useShortSearchRange (1 = shorter search distance). On success sends the unit there
             * (US_MOVE_TO_DESTINATION, plannedDestination set, extra changeDestinationByAmount(2) if
             * occupiesNeighbourTiles), resets targetingType and stores the paired structure tile in
             * targetedBuildingTile/attackAtTileX/Y. Returns 1 on success, 0 if no tile found.
             */
            undefined4 setDestinationNearTargetedBuilding(int unitID, int useShortSearchRange);

            /**
             * Chooses the speech/status line ID for the peasant (chimp) status panel. 1) a stuck/blocked worker
             * state if any; 2) among event counters recentEventTimer[i] (i = 5 or 11..22 except 20) with value >=
             * 40, the one with the SMALLEST value, mapped to a fixed line (when the same event is chosen a third
             * consecutive time its counter is zeroed); 3) otherwise a weighted pick between enemy-threat (>= 10
             * enemy units, not skirmish/MP and not campaign mission > 15; weight 80, dropping to 20 after repeated
             * threat speeches), rations, taxes and fear-factor/productivity lines; the rations/taxes/fear speech
             * biases (0/10/25) rotate whenever a different unit is inspected. fixedRng&3 picks the line variant; if
             * only one topic applied, 1/3 of the time (or when nothing applied) returns generic line 1. The final
             * threat-counter reset tests the last computed candidate, not the chosen line.
             */
            int selectWorkerSpeechOrMoraleStateID(int unitID);

            /**
             * Upgrades loaded unit data from an older map/save format: runs three unconditional fix-ups, then, if
             * receivedMapVersion differs from packagerMapVersion, applies every version-specific units upgrade step
             * (100, 112 ... 170) newer than the received version.
             */
            void upgradeMapFormatForUnits(
                PackagedFileMagicNum receivedMapVersion, PackagedFileMagicNum packagerMapVersion);

            /**
             * Allocates the first free unit slot (logicalState ULS_INVISIBLE, slots 1..2499, raising maxUnitCount
             * if needed), assigns uid, owner, display colour (cleared for siege towers; owner colour cleared for
             * caged dogs), spawn time, micro/tile/mimic position, saved destination and fixed RNG, initialises type
             * data via setUnitValues and applies type-specific setup: catapult/trebuchet stone ammo 20 (40 for non-
             * human owners in single-player missions), mangonel/ballista mark the building under them
             * (containsSiegeMangonel1OrBallista2 = 1/2), child sprite variant and name. Commits the position and
             * returns the new unit ID, or 0 if no slot is free.
             */
            int spawnUnit(int playerID, int displayColor, int microXPosition, int microYPosition, int terrainHeight,
                UnitType unitType);

            /**
             * Finishes a unit type change (e.g. peasant becoming a worker/soldier): restores state from state_2,
             * marks the unit normal and to go to the rally point, saves the old type in unitType_3, recomputes
             * calculatedOwnerPlayerIndex (single player: 0 for player 1's non-army types, otherwise the owner;
             * multiplayer: always the owner) and re-initialises the unit as unitTypeToChangeInto. Returns unitID.
             */
            int changeUnitType(int unitID);

            /**
             * Deletes a unit: deselects it, removes it from its owner's selection groups, records a death-heatmap
             * entry around its tile for AI-controlled owners (currentPlayerFullIDArray == -1) unless stalked,
             * releases its shared-tile registration and zero-fills its 0x490-byte unit record. (this_00 is ECX left
             * unchanged by deselectUnit, i.e. DAT_UnitsState.)
             */
            void deleteUnit(uint unitID);

            /**
             * Stops a unit's movement (path index, movement flags reset, movementRelated=8), sets the hidden flag
             * unknownTestAgainst0_2=1 and releases its shared-tile registration; used when a worker goes inside its
             * building.
             */
            void commitUnitLocation(int unitID);

            /**
             * Resets a unit's movement state (path progress, flags, movementRelated=8) and clears the hidden flag;
             * if the unit was hidden it re-commits its tile position.
             */
            void resetUnitMovementState(int unitID);

            /**
             * If the unit's hidden flag (unknownTestAgainst0_2) is set, clears it and re-commits the unit's tile
             * position so it appears on the map again.
             */
            void clearHiddenFlagAndUpdatePosition(int unitID);

            /**
             * Teleports a unit to tile (x, y) at the given height if the tile is inside the 400x400 map and nonzero
             * in the byte map at 0x21AEC98: resets movement, releases shared tile, sets micro/tile/mimic position
             * and tile index, then commits and updates the micro position.
             */
            void setPositionOfUnit(int unitID, uint x, uint y, undefined4 height);

            /**
             * Moves the unit to its mimic tile position (mimicCurrentX/Y): resets movementRelated, releases shared
             * tile, sets x/y, micro position, tile index and terrain height from the height layer, then commits
             * position and recomputes standing height.
             */
            void commitMimmicLocation(int unitID);

            /**
             * If the unit stands on a keep, gatehouse, wooden gate or tower, takes its target tile (pitch ditch for
             * UIT_LIGHT_PITCH, building origin for UIT_ATTACK_BUILDING, shoot-target micro position for
             * UIT_ATTACK_LAND or shootTargetedUnit==-2, else the shootTargetedUnit's tile) and asks the pathfinder
             * for the closest free tile on that building towards it (X written into the reused unitID parameter
             * slot, Y into freeTileY); if that differs from the unit's position, sends it there with state 0x7B and
             * returns TRUE, else FALSE.
             */
            BOOLEnum ifOnADefensiveStructureSetDestinationInDirectionOfTarget(int unitID);

            /**
             * Per-tick melee engagement. Eligible: melee-capable, not hidden, unknownMovementRelated_0x2d2 == 0,
             * normal, alive, moveRelatedFlag != 1, and either closestEnemyMicroDistance <= 50 (150 if selectable,
             * 270 while moving), already engaged (meleeOpponentUnitID != 0), a wolf, or an animal on a 1/16
             * throttle (outside missions or with > 100 units). Builds a 24-bit meleeNeighbourMask of enemy-occupied
             * tiles (team bitmask vs occupancy layer) in the 5x5 area plus an enemy-on-own-tile flag. If the
             * current opponent (uid checked) is still alive and found within that area at height difference < 32 it
             * is kept; otherwise the own tile and the 24 tiles are scanned in facing-dependent order with height
             * checks (outer-ring tiles need reachable 'via' neighbours; wolves and caged dogs take animals only on
             * the inner ring) and the first enemy becomes the opponent (face it). A free melee-capable opponent is
             * made to fight back, then the unit enters state 0x6A if at a tile centre, else pendingMeleeEngage is
             * set; finally processUnitAttackOtherUnit (the substate reset and that call use DAT_CurrentUnitSlotID,
             * which the only caller passes as unitID). Clears opponent fields when none or not eligible. Raw
             * offsets are relative to unitSlotBase = unit record - 0x614.
             */
            void processMeleeInitiation(int unitID);

            /**
             * If the unit has no melee opponent (attackedUnitID == 0), resumes its interrupted movement
             * (resumeMovementAfterInterruption) and clears attackedUnitID/field191_0x340.
             */
            void resumeMovementIfNoAttackTarget(int unitID);

            /**
             * Scans the owner's enemy-unit list and returns the approximate micro distance (max + 0.4*min^2/max) to
             * the closest enemy, capped at 32000; for assassins also stores the nearest selectable enemy distance
             * in nearestSelectableEnemyDistance. Explicit orders first: melee types with UIT_UNIT_ATTACK_UNIT keep
             * it only while their tribe's attack target is valid; melee types with UIT_ATTACK_LAND walk to
             * attackAtTile (or clear the order when there). For tribe units with defensive (range 40, Chebyshev
             * distance measured from the guard post chaseReturnX/Y when not rallying) or aggressive (200) stance
             * that are not busy, scores in-range uid-valid enemies by type, attackers, hunters and a vision-bonus
             * jitter, keeps the best one that has a free adjacent tile at similar height, and if its path area is
             * reachable saves the return position (if none yet), walks to the approach tile next to it
             * (findNearestValidDigTileNearTarget -> approachTileX/Y), sets lookForEnemy = min(-30-distance, -50)
             * and chaseTargetUnitID (incrementing its huntedBy when it changes); otherwise lookForEnemy=-8 and the
             * unit returns to its saved chase-return position.
             */
            dword findNearestEnemyAndHeadTowardsIt(int unitID);

            /**
             * Picks the shoot target for a ranged unit/siege engine; returns TRUE if one was set.
             * Catapult/trebuchet without stones (and no cow order) drop the order. Explicit UIT_UNIT_ATTACK_UNIT:
             * if the target is alive, not in a death state, an enemy and within the squared tile range, it is
             * locked (shootTargetedUnit/targetUID/shot value/micro XYZ, aimPitchOrLifetimeTicks arc class by
             * height, target marked targetedThisTick); with no clear shot, or for mangonel/ballista, the target's
             * position is fired at as ground (-2; hunters give up). Out of range: human owners keep the order and
             * return FALSE, AI owners drop it; an invalid target drops the order and walks back to chaseReturnX/Y
             * if set (TRUE). Pitch ditch (needs a brazier nearby), building centre, wall tile and ground/cow orders
             * set a fixed point (shootTargetedUnit -1). Otherwise (not catapult/trebuchet) scans the owner's enemy
             * list (uid-validated), filters animals/own-team dogs/hidden assassins/out-of-range units, scores by
             * Chebyshev micro distance + 50 per shootersTargetingCount weighted by shooter class and target type,
             * requires a clear shot, and prefers a target not yet targetedThisTick if within 1.5x of the best
             * score; mangonels fire at its position, ballistae lock it without bumping shootersTargetingCount. The
             * unitID stack slot is reused as the enemy-list pointer.
             */
            BOOLEnum acquireShootTarget(int unitIDThenEnemyListPtr);

            /**
             * Called while moving when the unit has a climbDataID: 0 -> TRUE, 200 -> FALSE, stale record
             * (climbDataRelated uid mismatch) -> clears the ID and returns FALSE. Sets climbingState to -1, then
             * for type 1 the climb record's unit must be in the tile list of its bottom tile (else FALSE); the unit
             * copies that unit's facing, sets usingTeleport=1, climbStepTimer=0, climbingState=0,
             * climbingDirection=(climbDirection!=0) and lowers terrainOrClimbHeight by 40 when that is 1, saves its
             * state and enters state 0x68. Types 3-7 exit the ladder and resume to the saved destination; other
             * types do nothing. Finally sets the mimic position to the record's bottom tile if climbDirection != 0,
             * else to its top tile, and returns TRUE.
             */
            BOOLEnum updateClimbing(int unitID);

            /**
             * Per-tick ladder-climb update. If the climb record is unusable or stale: a teleporting unit
             * (usingTeleport==1) goes to US_DETERMINE_NEXT_STATEUnk if climbingState < 0, else dies; others exit
             * the ladder and resume to the saved destination. Types 3-7: in state 0x6C the unit dies (stone death),
             * otherwise exits the ladder and resumes. Type 1: counts climbStepTimer; past 95 it resets it, bumps
             * climbingState and moves height by 15 (direction from climbingDirection), forcing climbingState 5 once
             * the height exceeds the ground height at the mimic tile; sets climbDrawOffsetX, the climb animation
             * frame, gfxNumber by corrected facing and vanish/drawOrderOverride; at climbingState >= 5 exits the
             * ladder, restores the state saved in unknownStateCopyClimbRelated and resumes towards the saved
             * destination.
             */
            void unitClimbing(int unitID);

            /**
             * For a unit with a targetedBuildingTile, checks whether that tile is one of the unit's 8 neighbours
             * (every 2nd direction only if the target is a wall tile, LogicLayer & 0x100). Returns 0 if there is no
             * target or it is not adjacent, -1 if the target tile is not a wall, not flagged 0x40000000 and has no
             * building. Otherwise, if no ladder stands on the unit's tile, it stops walking and, when at a tile
             * centre (subTileStepProgress >= 8), saves its current tile as the resume destination and returns 1; if
             * a ladder is there and the target is a wall, calls setDestinationNearTargetedBuilding(unitID, 0).
             * Returns 0 in the remaining cases.
             */
            int handleUnitMovementWhenTargetingBuildings(int unitID);

            /**
             * Moves a unit off a bad tile: if its tile is impassable (LogicLayer & 0x30) it is teleported to a
             * directly adjacent walkable tile (returns FALSE). Otherwise, if it is not the first unit in its tile's
             * unit chain, finds a tile without units (a free tile on the defensive structure when standing on a
             * wall) and walks there, setting US_MOVE_TO_DESTINATION on DAT_CurrentUnitSlotID (all callers are
             * Update* routines passing that slot). Returns TRUE only when a walk order was issued.
             */
            BOOLEnum moveToFreeTileNearby(int unitID);

            /**
             * Movement step for one unit. Skipped for dying units (except burning men) and climbing assassins.
             * movementState 5 freezes the unit (position re-committed, returns 0); a state other than 2/4 only
             * refreshes the micro position and climbing (re-planning if updateClimbing fails) and returns 0.
             * Otherwise decrements moveInstructionSpeedDelayTracker/moveDelay and runs speedCategory +
             * pendingMeleeEngage + 1 sub-steps (some skipped by the current slot's hopGaitMode/animCycle16
             * throttle): each advances subTileStepProgress; at 8 (tile boundary) it ends the path (saving the tile
             * as resume destination), switches to US_MELEE_ATTACK if a melee engage is pending, or reads the next
             * 4-bit direction from the packed path and (unless moveRelatedFlag == 1) tries doMoveFromTileToTile; on
             * failure it waits (blockedWaitCounter), then re-plans, stops or makes non-selectable units disappear
             * (blockedWaitCounter=40 if re-planning fails); on success it may scare a crow from a nearby tree and
             * sets the from/next tile, mimic position and tile-centre micro position. Then nudges the micro
             * position by facing, commits it and, once the position is committed, handles killing pits / tower
             * occupancy. Returns 1 after all sub-steps, 0 when movement ended early or was not performed.
             */
            undefined4 processUnitMove(int unitID, int speedCategory);

            /**
             * Per-tick main unit update over unit slots 1..2499. Pass 1 (all slots): clears the OccupancyLayer and
             * per-player healer counts, resets per-unit attackedBy/huntedBy counters, removes 'lost' units not
             * registered on their own tile (lostChimps++), sets siegeTargetPlayerID, counts blessed/unblessed
             * units, and for the 1/16 of slots whose (slot & 15) matches an RNG-chosen phase makes units older than
             * 1000 ticks on unconnected tiles disappear (the lord is instead teleported to targetX_2/targetY_2) and
             * removes catapults/fire ballistas on forbidden tiles; any normal unit with x==0, y==0 or tile<0 is
             * made to disappear. Pass 2: accumulates attackedBy/huntedBy/field265 counts (and adds 1 to GameCore
             * battle-activity accumulator per newly melee-engaged unstalked target). Pass 3: rebuilds per-player
             * troop/AI-behaviour counters, occupancy bits, troop value + name assignment every 64 ticks, nearest-
             * enemy scans and the dormant vertical-lift effect. Pass 4: per logicalState deletes/changes type,
             * advances animation, facing, workplace loss, runs the per-unit-type state handler, movement or
             * climbing, sprite frame selection (gfxNumber/imageIDUnk) and fade alpha. Finally increments
             * DAT_UpdateUnitsTracker (or resets it to 0 when refreshRelatedOne is 0).
             */
            void updateUnits();
        };

        static_assert_cpp98_obj(sizeof(UnitsState) == 2926564, UnitsState);

#pragma pack(pop)

    } // namespace Units
} // namespace Map
} // namespace OpenSHC
