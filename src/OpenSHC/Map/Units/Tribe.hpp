/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/Tribe.hpp'
*/

#pragma once

#include "OpenSHC/AI/Tribes/AITribeTypeShort.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnumShort.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorTypeShort.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::AI::Tribes::AITribeTypeShort;
        using OpenSHC::Map::Units::SomeTribeBehaviorTypeShort;
        using OpenSHC::Map::Units::UnitTypeShort;
        using OpenSHC::Map::Units::Behavior::UnitStanceEnumShort;

#pragma pack(push, 1)
        // SIZE: 0x00000334
        typedef struct Tribe {

            undefined1 padding_0x0[2]; // 0x00000000 length: 2
            // [152 0x00527330] empty tribe is kept while mapTimeInTicks <= time
            short emptyKeepAliveUntilTick; // 0x00000002 length: 2
            // Created by retype action
            int owner; // 0x00000004 length: 4
            undefined1 padding_0x8[4]; // 0x00000008 length: 4
            int uid; // 0x0000000C length: 4
            undefined1 padding_0x10[8]; // 0x00000010 length: 8
            short tribeState; // 0x00000018 length: 2
            AITribeTypeShort tribeType; // 0x0000001A length: 2
            // Zeroed on tribe creation; no reader seen
            short initZero1c; // 0x0000001C length: 2
            // Zeroed on tribe creation; no reader seen
            short initZero1e; // 0x0000001E length: 2
            short facingDirection_1; // 0x00000020 length: 2
            short facingDirection_2; // 0x00000022 length: 2
            short facingDirection_3; // 0x00000024 length: 2
            // Copy of the lead unit's movementRunUpTime when units are added
            short movementRunUpTime; // 0x00000026 length: 2
            SomeTribeBehaviorTypeShort tribeBehaviorType; // 0x00000028 length: 2
            undefined1 padding_0x2a[2]; // 0x0000002A length: 2
            // [158 0x0051D7F0] threshold the per-tribe tick counter must reach before the behaviour action fires; 0
            // disables it in most cases
            short behaviorDelayTicks; // 0x0000002C length: 2
            // [154 0x0052A7D0] generic per-tribe tick counter, also used by animal tribes as wander/rest timer
            short behaviorTickCounter; // 0x0000002E length: 2
            // Zeroed on tribe creation; no reader seen
            short initZero30; // 0x00000030 length: 2
            // [027 0x004CD160] used as the tribe's representative unit whose tile/position is used for moat search
            // and pathing Created by retype action
            short leaderUnitID; // 0x00000032 length: 2
            // Created by retype action
            short size; // 0x00000034 length: 2
            short size2Unk; // 0x00000036 length: 2
            short unitSelectionBitMasked[200]; // 0x00000038 length: 400
            // Start of the 0x16c-byte block moved by upgradeTribeArrayLayoutForMapVersion
            byte relocatedBlock1c8; // 0x000001C8 length: 1
            undefined1 padding_0x1c9[11]; // 0x000001C9 length: 11
            // 10-entry ring of unit ids written when a member is hit, later checked for team/area/distance
            short recentAttackerUnitIDs[10]; // 0x000001D4 length: 20
            short countdown2; // 0x000001E8 length: 2
            undefined1 padding_0x1ea[6]; // 0x000001EA length: 6
            short freeUnitSpeeds; // 0x000001F0 length: 2
            // shield tribe stores the tribe it protects (0x4CFCD0) and attacker stores its support tribe
            // (0x518A10): generic link, 'support' fits only one use Linked support/escort tribe ID (validated with
            // uid2) for siege/AI behaviour
            short linkedTribeID; // 0x000001F2 length: 2
            // uid of the tribe in linkedTribeID, used to detect stale links (both uses agree)
            int linkedTribeUID; // 0x000001F4 length: 4
            // not the own index: back-link set on the linked tribe to the linking tribe's index (shield/attacker),
            // 0 = free, cleared per owner (0x518A10)
            short linkedByTribeID; // 0x000001F8 length: 2
            short minimumMovementSpeed; // 0x000001FA length: 2
            short movementSpeed; // 0x000001FC length: 2
            short maximumMovementSpeed; // 0x000001FE length: 2
            // Zeroed in addUnitsToTribeAndComputeMovementSpeed
            short resetOnAdd200; // 0x00000200 length: 2
            // Zeroed in addUnitsToTribeAndComputeMovementSpeed
            short resetOnAdd202; // 0x00000202 length: 2
            // Animal tribe movement state: 0 initial move pending, 1 moving/placed, 2 lion/wolf roaming
            short wildlifeMoveState; // 0x00000204 length: 2
            // [152 0x005263A0] stored from rallyBool together with a 2-point rallyPointArray route
            short rallyMode; // 0x00000206 length: 2
            // Zeroed in addUnitsToTribeAndComputeMovementSpeed
            short resetOnAdd208; // 0x00000208 length: 2
            short unitsHealthPercentage; // 0x0000020A length: 2
            // Zeroed in addUnitsToTribeAndComputeMovementSpeed
            short resetOnAdd20c; // 0x0000020C length: 2
            short targetX; // 0x0000020E length: 2
            short targetY; // 0x00000210 length: 2
            // Set to 1 by giveTribeAnInstruction when the tribe is ordered to attack a rabbit, cleared on every new
            // instruction/move; acquireShootTarget lets non-hunter units target rabbits only while set
            short rabbitAttackOrdered; // 0x00000212 length: 2
            undefined1 padding_0x214[20]; // 0x00000214 length: 20
            // Created by retype action
            UnitTypeShort unitType; // 0x00000228 length: 2
            // Aggressive-stance tick counter 0..0x3b; at 0x3c the tribe rescans for enemies
            short aggressiveScanTimer; // 0x0000022A length: 2
            undefined1 padding_0x22c[12]; // 0x0000022C length: 12
            // [150 0x00522DD0] type should be short[10][2]: copy loop writes indices 0..9 (pasVar3 = array+1,
            // pasVar3[-1]..pasVar3[8]); index 9 lands on the undefined bytes 0x25C-0x25F right before
            // currentRallyPointIndex, so the array has 10 entries, not 9
            short rallyPointArray[9][2]; // 0x00000238 length: 36
            undefined1 padding_0x25c[4]; // 0x0000025C length: 4
            short currentRallyPointIndex; // 0x00000260 length: 2
            // Created by retype action
            short rallyPointCount; // 0x00000262 length: 2
            undefined1 padding_0x264[20]; // 0x00000264 length: 20
            // Animal tribe alarm counter: set to 1 when attacked, counts up (to 800/3000) then resets; blocks
            // spawning
            short wildlifeAlarmTimer; // 0x00000278 length: 2
            // Set when units are spawned into the tribe; tribe moves to an indexed nearby tile once then clears
            short spreadOnSpawnPending; // 0x0000027A length: 2
            short unkIsAnimalTribe; // 0x0000027C length: 2
            // Ticks between wildlife wander moves (200/400/20, randomised)
            short wildlifeWanderInterval; // 0x0000027E length: 2
            // Tribe size threshold (initial size/2) below which wildlife breeds faster
            short wildlifeMinSize; // 0x00000280 length: 2
            // Maximum tribe size for wildlife breeding (initial size*2)
            short wildlifeMaxSize; // 0x00000282 length: 2
            // Ticks since last wildlife spawn; spawn when >= interval
            short wildlifeSpawnTimer; // 0x00000284 length: 2
            // Deer/rabbit tribes: +1 every tick, 7999->4000 cap, reset only in editor (age); lion: reset after
            // melee. Neutral tick counter covering both
            short elapsedTicks; // 0x00000286 length: 2
            // Placeholder +0x288 is a word counter: add word 1, movzx word, reset to 0 (esi = TribesState+id*0x334,
            // tribe offset = disp-0x28).
            undefined1 extraSpawnTimer[2]; // 0x00000288 length: 2
            // [150 0x00523790] set by flagTribesOfType(tribeType) and consumed here (cleared, unknownBool01 set) by
            // processSingleplayerEvents
            short pendingEventFlag; // 0x0000028A length: 2
            // [138 0x0056B0E0] while set: lion cooldown and tribe.pendingEventFlag cleared every tick, and idle lions
            // search prey in radius 200 with flag TRUE
            // [138 0x0056B0E0] while set: lion cooldown and tribe.unknownBool02 cleared every tick, and idle lions
            // search prey in radius 200 with flag TRUE
            short isProvoked; // 0x0000028C length: 2
            short countdown; // 0x0000028E length: 2
            // Head index (mod 10) of recentAttackerUnitIDs ring
            short recentAttackerIndex; // 0x00000290 length: 2
            // [154 0x0052A700] used modulo 40 as start index into the nearby-tile offset table
            short nearbyTileOffsetStartIndex; // 0x00000292 length: 2
            short attackWave; // 0x00000294 length: 2
            // [152 0x005270F0] computed as dying members *100 / size
            short percentageDying; // 0x00000296 length: 2
            // percentage of living members mid-step (subTileStepProgress != 8); meaning known, drop Unk
            short percentageMoving; // 0x00000298 length: 2
            // [152 0x005270F0] counts US_MELEE_ATTACK and US_MELEE_ATTACK_WALL members
            short percentageMeleeAttacking; // 0x0000029A length: 2
            // Percentage counter reset with the other percentage fields in computeTribePercentages
            short percentageUnk29c; // 0x0000029C length: 2
            // percentage of ranged members in reload/aim/fire states; meaning confirmed, drop Unk
            short percentageShooting; // 0x0000029E length: 2
            // Percentage counter reset with the other percentage fields in computeTribePercentages
            short percentageUnk2a0; // 0x000002A0 length: 2
            short percentageSomething; // 0x000002A2 length: 2
            short attackInfo_someCounter1; // 0x000002A4 length: 2
            // [087 0x0049F040] compared to the candidate archer-point index so the tribe's current point is skipped
            short archerPointIndex; // 0x000002A6 length: 2
            // Receives the old archer point before re-reservation; hence also excluded from candidates.
            short previousArcherPointIndex; // 0x000002A8 length: 2
            short supportPointIndex; // 0x000002AA length: 2
            short oldSupportPointIndex; // 0x000002AC length: 2
            // Zeroed each updateTribeBehaviorBasedOnBehaviorType
            short behaviorResetFlag2ae; // 0x000002AE length: 2
            // Holds the reserved tent-point slot of the tribe.
            short tentPointIndex; // 0x000002B0 length: 2
            // Receives old siegeIndexValue1 before re-reservation; also excluded from candidates.
            short previousTentPointIndex; // 0x000002B2 length: 2
            int someTile2; // 0x000002B4 length: 4
            UnitStanceEnumShort unitStance; // 0x000002B8 length: 2
            short orientation; // 0x000002BA length: 2
            // set to running attackInfo assigned-tribe counter (0..4) per tribe assigned to the wave (checked
            // decomp 0x518930 and preceding function)
            short waveAssignmentSlot; // 0x000002BC length: 2
            // Set to path-length*8 after ordering pursuit, decremented while target stays put; delays re-issuing
            // attack. Covers both uses Wait counter (instructionType*8, min 8) decremented while units reach
            // someTile2
            short attackRetargetDelay; // 0x000002BE length: 2
            // Set to attacked unit id in attack/shoot cases and re-issued via UIT_UNIT_ATTACK_UNIT; someUnitID is a
            // placeholder
            short attackTargetUnitID; // 0x000002C0 length: 2
            undefined1 padding_0x2c2[2]; // 0x000002C2 length: 2
            // UID partner of attackTargetUnitID, validated against units[id].uid before re-issuing attack
            int attackTargetUnitUID; // 0x000002C4 length: 4
            // [153 0x00527C80] set to the attacked unit's current tile
            int targetUnitTile; // 0x000002C8 length: 4
            // [149 0x005224E0] set to the lowest non-zero word index of unitSelectionBitMasked
            short firstOccupiedMaskWord; // 0x000002CC length: 2
            // values 1 to 8
            short targetPlayer_outpost; // 0x000002CE length: 2
            short targetBuildingID; // 0x000002D0 length: 2
            undefined1 padding_0x2d2[2]; // 0x000002D2 length: 2
            int targetBuildingUID; // 0x000002D4 length: 4
            // [161 0x00531920] parallel ring buffer of shooter uids
            int recentAttackerUIDs[10]; // 0x000002D8 length: 40
            short tribeSubtype1; // 0x00000300 length: 2
            short counter; // 0x00000302 length: 2
            int randomNumber; // 0x00000304 length: 4
            undefined1 padding_0x308[44]; // 0x00000308 length: 44

        } Tribe;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(Tribe) == 820, Tribe);
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
