/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units.hpp'
*/

#pragma once

#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::States::UnitState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /**
         * Returns the lowest player slot >= 2 whose keep building id is > 0 (scans playerDataArray from index 2 to
         * the end of the array); returns 1 when gameMode_2 is GM_CUSTOM_MAP on an MT_SIEGE map, 0 if no such
         * player.
         */
        int __cdecl FindFirstOpponentWithKeep();

        /**
         * Detaches a ladderman from the wall: clears the ladder bit 0x800000 in the LogicLayer at the unit's tile,
         * resets wallDataID and laddermanIsInPosition, and rebuilds path linkages around that tile.
         */
        void __cdecl DetachLadderman(int unitID);

        /**
         * Per-tick update of a siege tent (DAT_CurrentUnitSlotID): sets a static sprite variant gfxNumber =
         * (fixedRng+1)&3 and counts animationCycleNumber up each tick; after 500 ticks it becomes ULS_TRANSITIONING
         * into a catapult (fixedRng bit 1 clear) or trebuchet, sets state_2=6 and faces toward player 1's keep
         * entry.
         */
        void __cdecl UpdateSiegeTent();

        /**
         * Per-tick update of a burning animal (variant 1) for DAT_CurrentUnitSlotID: makes it
         * ownerless/dying/unselectable; from state 1 starts the death animation (gfx 1, state 2), then sets
         * gfxNumber = animationCycleNumber+1 and removes the unit once the cycle exceeds 20 or
         * DAT_UnitAnimationFinished is set.
         */
        void __cdecl UpdateBurningAnimal1();

        /**
         * Per-tick update of a burning animal (variant 2): identical to UpdateBurningAnimal1 but the unit is
         * removed once the cycle exceeds 16.
         */
        void __cdecl UpdateBurningAnimal2();

        /**
         * Increments the worker's current work-timer slot (4-int ring workTimer/workRelatedA/B/C indexed by
         * `working`). If updateAV, sets av to the sum of the 4 slots divided by the number of positive slots,
         * advances the ring index (0..3) and zeroes the new slot.
         */
        void __cdecl IncrementAndOptionalUpdateAVValueRelated(int unitID, BOOLEnum updateAV);

        /**
         * Decides whether a worker takes a break: only if destinationNeeded == DNE_DESTINATION_NEEDED, the owner's
         * fearFactorProductivity < 100 and av > 100. Required break = (100-productivity)*av/100 (stored in target);
         * if banked < that, saves nextUnitState in cachedState, idle=banked, field166_0x2fe=0, switches to state
         * 0x79 (free time) and returns TRUE; otherwise subtracts it from banked. Returns FALSE in all other cases.
         */
        BOOLEnum __cdecl ConsiderTakingFearFactorBreak(int unitID, UnitState nextUnitState);

        /**
         * While the worker is in break phase 1 (field166_0x2fe==1) increments idle; if additionally
         * shouldFindNewGoodThing, advances substate (wrapping to 0 at param_3), resets the animation cycle, sets
         * the free-time state 0x79 and returns 1. Otherwise returns 0.
         */
        undefined4 __cdecl SetStateToFreetimeWalking(int unitID, int shouldFindNewGoodThing, int substateCount);

        /**
         * Returns true if the worker unit is in break phase 1 (field166_0x2fe == 1), i.e. production is paused.
         */
        BOOLEnum __cdecl CheckUnitProductionPaused(int unitID);

        /**
         * Computes goods produced in a work cycle: productivity = max(100, owner's fearFactorProductivity) (+50 in
         * non-solitary modes if boost); the excess over 100% times goodsCount plus the carried remainder
         * productivityMod100 yields extra whole goods (stored in productivityDiv100) and a new remainder. Returns
         * goodsCount + extra goods.
         */
        int __cdecl ComputeGoodsProduced(int unitID, int goodsCount, BOOLEnum boost);

        /**
         * Plays 'The granary is full my lord' (placement_warning10.wav) at most once per ~60 s (next allowed time
         * randomised by up to 5 s) if the local player owns a normal-state granary. Does not itself check fullness;
         * callers do.
         */
        void __cdecl WarnIfPlayersGranaryIsFull();

        /**
         * Plays 'The stockpile is full my lord' (placement_warning11.wav) at most once per ~60 s (cooldown
         * randomised by up to 5 s); unlike the granary/armory variants it does not check that the player owns a
         * stockpile. Returns the elapsed time or a throwaway RNG quotient.
         */
        uint __cdecl PlayStockpileIsFullWarning();

        /**
         * Plays 'The armory is full my lord' (placement_warning12.wav) at most once per ~60 s (randomised by up to
         * 5 s) if the local player owns a normal-state armory.
         */
        void __cdecl PlayArmoryIsFullWarning();

        /**
         * NAME? Returns TRUE if the local player (currentPlayerSlotID) owns any unit of type UT_HEALER whose
         * logicalState is not ULS_INVISIBLE; not specific to the current unit.
         */
        BOOLEnum __cdecl LocalPlayerHasHealer();

        /**
         * Per-tick update of a burning man (DAT_CurrentUnitSlotID): makes him ownerless, dying and unselectable.
         * State 0: picks a short random wander path (computeRandomWanderPath), trims it by 4 steps and runs (state
         * 0x78); with no path he dies at once (US_STONE_DEATH_03, stop walking). State 0x78: when movement is idle
         * he enters US_STONE_DEATH_03. Death states play animBurningManDeath, then US_DISAPPEAR fades him out over
         * 32 ticks and removes him; any other state resets to 0.
         */
        void __cdecl UpdateBurningMan();

        /**
         * Per-tick update of a camel (DAT_CurrentUnitSlotID; herd = tribe): increments mapAndTime.camelCount,
         * counts down the fade-in alpha (unless US_DISAPPEAR) and cooldownTicks. State 0: waits updateTickTracker,
         * faces the tribe leader and enters idle state 0xcd (first the lie-down animation, then seated idle
         * animations chosen by substate 0..3; next wait = (fixedRng+mapTime)%20). States 2/0x78: if substate==100
         * plays the get-up animation first, else walks (movementSpeed 1/stateBasedSpeed 1 while the tribe's
         * wildlifeAlarmTimer is set, else 3/0) and on arrival returns to state 0 with a random substate 0/1. Death:
         * US_DEATH_01 or the other death states (FX_CAMEL_DIE, FX_HORSE_FALL), then corpse state 0x75 for 51 ticks,
         * US_DISAPPEAR fade-out and removal.
         */
        void __cdecl UpdateCamel();

        /**
         * Per-tick update of a portable shield (DAT_CurrentUnitSlotID): counts it in the owner's
         * armySize/currentSiegeWeaponCount. State 0 goes to state 6 when not manned (count != 1). State 6: for an
         * AI owner with one assigned engineer it absorbs him once he arrived within 30 micro-units/16 height; every
         * 16 ticks it scans for live engineers ordered (UIT_MAN_SIEGE_EQUIPMENT) to man this shield within range
         * (one per player), preferring the owner's, otherwise transferring the shield to the first player 1..8 with
         * one (deselect, owner/colour change, new tribe). The engineer fades into the shield (US_FADE_TRANSITION,
         * stateAfterFade 5) and is stored in manningEngineerRef[0]. Also handles walking, death (FX_DEATH_SHIELD,
         * removes manning engineers with loss/hit stats, removal after 200 ticks) and fade-out removal with loss
         * statistics. BUG (original game): on transfer createTribe receives units[scanIndex].owner, where scanIndex
         * is the finished scan loop index (= maxUnitCount), not the new owner.
         */
        void __cdecl UpdateShield();

        /**
         * Wrapper: calls ConsiderHavingABreakNowUnk(unitID, current state) so the worker resumes its current state
         * after the break; returns its BOOLEnum result.
         */
        BOOLEnum __cdecl UpdateWorker_ConsiderTakingFearFactorBreak(int unitID);

        /**
         * Per-tick update of a peasant (DAT_CurrentUnitSlotID) at its owner's campground: counts available/at-
         * fire/idle peasants and sets calculatedOwnerPlayerIndex = fixedRng&7. In state 0 a peasant with
         * isDisappearingUnk fades in (US_FADE_TRANSITION, step -1) and walks to the campfire (state 4) where it
         * plays an arrival animation (state 5); otherwise moveUnitAroundCampfire assigns a spot (-1 = remove),
         * walking there in state 7 and idling in state 8 with animations chosen by substate 0x64..0x78 and the
         * campground's field194_0x274. A positive fade step with isDisappearingUnk (recruitment) counts count_2 for
         * military/siege target types and ends in ULS_TRANSITIONING. Handles death animations, US_DISAPPEAR
         * removal, and disappears if its tile has no path connection.
         */
        void __cdecl UpdatePeasant();

        /**
         * Per-tick update of an ox tether (DAT_CurrentUnitSlotID): goes US_DISAPPEAR if its quarry
         * (workplaceBuildingID_1, uid-checked) is gone; counts the owner's nonInteractiveCitizenCountUnk. At the
         * quarry it plays the loading animation (state 4, facing the quarry) until resourceToDeposit >= 8, then
         * walks (state 1, after an 80-tick start delay in moveInstructionSpeedDelayTracker) to an accessible
         * stockpile, where state 2 unloads 1 stone per tick (addResourceToStockpile, finalStoneProduced,
         * FX_STOCK_STONE), re-targets another stockpile when this one is full (dropping the load if none is
         * reachable) and, once empty, returns to the quarry (state 3; on path failure retries after
         * DNE_OX_SPECIFIC_COUNTDOWN ticks). Handles death (FX_OX_DIE, loaded sprite +12) and fade-out removal.
         */
        void __cdecl UpdateOx();

        /**
         * Per-tick update of a miner-type worker (DAT_CurrentUnitSlotID): fades in after spawning
         * (isDisappearingUnk); on goToRallyPoint walks to targetX_2/targetY_2 (state 2), on arrival commits its
         * location and idles in state 1, where it registers itself every tick in its workplace's
         * workers[workerIndex]. Death: US_DEATH_01 and the other death states play ANIM_Frames_UnitDeath, then
         * US_DISAPPEAR; the fade-out removal records setLastEncounteredTroopUnit unless killedFlagUnk; any other
         * state resets to 0 and stops walking.
         */
        void __cdecl UpdateMiner();

        /**
         * Per-tick update of a healer (DAT_CurrentUnitSlotID): counts healerCount; goes US_DISAPPEAR if
         * field280_0x3f4 > 1. State 1: walks home (targetX_2/Y_2) and fades into the building (state 2), rests up
         * to 300 ticks (checking for disease clouds every 10), then fades out and, by RNG, wanders with
         * computeLadderClimbPath(2,0,1) (state 4) or visits gardens (state 3) for 1..8 stops (resourceToDeposit).
         * Whenever somethingWithSeparateAreas1 returns a reachable unclaimed disease cloud (ET_DISEASE_CLOUD
         * entity) the healer claims it (velocityUnk=-10000; unitUID/unitID_healer + assignPoisonCloudTargetEntity
         * on the garden path), walks to it (state 5), plays the cure animation (state 6), then calls
         * refreshPoisonCloudNearUnit and adds 2 to the owner's someCount60. Also handles death animations and fade-
         * out removal.
         */
        void __cdecl UpdateHealer();

        /**
         * Per-tick update of an innkeeper (DAT_CurrentUnitSlotID): in state 0 finishes the spawn fade-in, then when
         * goToRallyPoint is set walks to targetX_2/Y_2 (US_RELOAD_WEAPONUnk) and becomes state 1 on arrival. State
         * 1 plays serving animations (substate 0..3) and after each cycle heads for an accessible storage with ale
         * (state 2). At the storage it takes 1 ale (addResourceToStockpile -1; tries another storage, else goes
         * home or is removed if there is none) and carries it to the inn (state 3), adding 0xa0 to the inn's ale
         * level flagonsOfAleOrCheeseOrReleaseDogs; it hurries (movementSpeed 1 instead of 3) when that level is <
         * 201 on the way out / < 151 on the way back. At the inn (state 5, drunkardSpawnCountdown=300 each tick) it
         * waits while the level >= 400, fetches more when lower, and returns to state 1 when the inn is empty.
         * Handles death animations and fade-out removal.
         */
        void __cdecl UpdateInnkeeper();

        /**
         * Per-tick state machine of the merchant (trader) unit DAT_CurrentUnitSlotID (colour index 1). State 0:
         * walk to the entry of the visited player's (traderVisitsPlayer) marketplace (state 1), or ULS_REMOVE if it
         * is not accessible; state 1: on arrival call activateTraderState and fade out (US_FADE_TRANSITION, step
         * +2, then state 2); state 2: wait until mapAndTime.traderState == 1, then fade back in (fadeLevel 0x20,
         * step -2) into state 3; state 3: walk to the first map-edge signpost and remove itself on arrival. Dying
         * states switch to US_DISAPPEAR (removed after 33 ticks); US_FADE_TRANSITION adds fadeAlphaStep (clamped
         * 0..31) for 17 ticks, then switches to stateAfterFade (commitUnitLocation after a fade-out); unknown
         * states reset to 0.
         */
        void __cdecl UpdateMerchant();

        /**
         * Per-tick state machine of the merchant's pack horse: marks itself ULS_REMOVE if
         * units[traderHorsesTrader].uid no longer equals the trader UID it stored in workplaceBuildingUID
         * (processing continues). State 0 polls the trader: trader in state 1 -> walk to the trader's saved
         * destination (state 1, moveInstructionSpeedDelayTracker 20); trader in state 3 -> fade in (step -2) into
         * state 3. State 1: on arrival fade out (step +2) into state 2; state 2: back to state 0 when traderState
         * == 1; state 3: walk to the first map-edge signpost, then resetTraderState and remove itself. Movement
         * holds (stateBasedSpeed -1) while moveInstructionSpeedDelayTracker != 0; dying states -> US_DISAPPEAR
         * fade-out; US_FADE_TRANSITION handled like the merchant.
         */
        void __cdecl UpdateMerchantHorse();

        /**
         * Per-tick update of a deer: increments mapAndTime.deerCount, sets movementSpeed 1..3 from
         * antelopeBasedRngValue and decays the fade level (fade-in) unless disappearing. State 0: if
         * closestEnemyMicroDistance > 200 face the tribe's selectionTargetUnitID and play idle animation 0xCD
         * (tribeBehaviorType STBT_1) or 0xCB, else alert animation 0xCC and count it in field279_0x3f2 (> 10 in a
         * row -> scatterTribeUnitsRandomly). Move state: lie-down/stand-up sub-animations, tribe-dependent speed,
         * back to 0 on arrival; 0xCB/0xCC: 4-substate idle animations; 0xCD: sit/rest; death animations
         * (FX_DEER_FALL), corpse kept 500 ticks, then US_DISAPPEAR fade-out; 0xD1: occasionally walk to targetX/Y.
         */
        void __cdecl UpdateDeer();

        /**
         * Per-tick update of a rabbit: increments mapAndTime.rabbitCount (rabbit count), sets
         * calculatedOwnerPlayerIndex from fixedRng&0xF (0..8 kept, 9..15 remapped to 2/3/4/6/8), decays the fade
         * level and clears DamageLayer on its tile and its 4 direct neighbours when they carry LogicLayer flags
         * 0x3000000. State 0: alert animation 0xCC if closestEnemyMicroDistance < 1, else idle 0xCB (odd unit IDs
         * face the tribe target); move states with hop slow-down (substate 100); 0xCB idle animation chosen by
         * unitID&3; death animations (FX_RABBIT_DIE), corpse kept 5 ticks, then US_DISAPPEAR fade-out; 0xD1:
         * occasionally walk to targetX/Y.
         */
        void __cdecl UpdateRabbit();

        /**
         * Per-tick update of a dairy-farm cow: counts itself in playerData.nonInteractiveUnitCountThisTick;
         * ULS_REMOVE if its farm is gone (UID mismatch), sleeping or has no worker; otherwise either counts in
         * farm.numberOfAnimals or (in the walk/wait/slaughter/disappear states) frees its workerID slot. Counts
         * down the lifetime timer in digTileX__OR__..._forCowsRandomBelow300 (at 0: playerData.counter--,
         * US_DISAPPEAR). State 3: hidden at the farm while farm field214_0x298 is 3..4, else fade in (0x6D, step
         * -1, 33 ticks) into state 0; US_RELOAD_WEAPONUnk: walk to the targeted unit (if it vanished/dies:
         * counter--, disappear), on arrival US_AIM_WEAPONUnk waits 1001 ticks, then US_FIRE_WEAPONUnk plays the
         * death animation silently; death states play it with FX_COW_MOO/FX_HORSE_FALL; all end in counter-- and
         * US_DISAPPEAR fade-out. State 0: grazing animations cycling substates 100->102->103->101->106 with a moo
         * at cycle 8.
         */
        void __cdecl UpdateCow();

        /**
         * Per-tick state machine of the fire-watch unit (fire fighter from a well / water pot): writes its ID into
         * its workplace's workers[workerIndex]. State 0: fade in while isDisappearingUnk, or start (state 1) when
         * goToRallyPoint is set; state 1: walk to its post (targetX_2/Y_2, US_DISAPPEAR if unreachable), then take
         * a target from findClosestReachableAlliedBuilding (state 3) or idle (state 2); state 2: 4 idle animations,
         * re-searching after each; state 3: walk to the target's entry while it is the same building (uid) and
         * still burning (fireDuration), retarget otherwise; on arrival state 4 (US_RELOAD_WEAPONUnk): throw
         * animation with FX_THROW_WATER at cycle 5, then extinguishBuildingFire + FX_FIRE_OUT on the target and
         * extinguishBuildingFire on every other active building with the same non-zero uidWhenPlaced, back to state
         * 1. 0x6C frozen, 0x6D fade step; death states play the death animation then ULS_REMOVE; US_DISAPPEAR fades
         * out and removes.
         */
        void __cdecl UpdateFireWatch();

        /**
         * Per-tick update of the ghost unit: counts itself in owner's nonInteractiveCitizenCountUnk, makes itself
         * unselectable (colour index 0); state 0 fades in (fade level -1 per tick) until < 0x16, state 1 wanders
         * between the owner's reachable defensive buildings (findNextReachableDefensiveBuildingForPlayer),
         * flickering its fade level from a 100-entry table (+0x16) and playing FX_GHOST when picking a new target
         * at most every 30 s (timeGetTime); US_MELEE_ATTACK switches to 2, which fades out and removes the unit;
         * 0x6C frozen, other states reset to 0.
         */
        void __cdecl UpdateGhost();

        /**
         * Per-tick state machine of the lady (lord's wife); field280_0x3f4 > 1 forces US_DISAPPEAR. State 0: fade
         * in while isDisappearingUnk or start (state 1) on goToRallyPoint; state 1: walk to targetX_2/Y_2 and fade
         * out (0x6D) into hidden state 2; state 2: every 200 ticks picks by SEC_RNG&7 a next own building of type
         * 0x24/0x25/0x26 (cachedState US_LOOK_AROUNDUnk), of type 0x42 (cachedState 3) or a unit from
         * findEligibleUnitByTimeAndLocation (cachedState US_AIM_WEAPONUnk) and fades back in. State 3 tours up to 8
         * type-0x42 buildings, then state 1; US_LOOK_AROUNDUnk walks to the building and fades out into
         * US_STAND_UPUnk, which waits 500 ticks and fades in to state 1; US_AIM_WEAPONUnk walks to the partner
         * until axis distance < 3, then US_FIRE_WEAPONUnk faces it and plays one talk animation (4 variants by
         * substate); afterwards resourceToDeposit++ and she either chats with another eligible unit or (counter > 1
         * / no partner) returns to state 1. Death animation -> US_DISAPPEAR fade-out and removal.
         */
        void __cdecl UpdateLady();

        /**
         * Per-tick state machine of a siege tower: counts it in the owner's armySize/currentSiegeWeaponCount and
         * sets its two-part sprite by facing. State 0 (crewed) -> US_FIRE_WEAPONUnk (awaiting crew) when the crew
         * count != 4. Awaiting crew: for AI owners (currentPlayerFullIDArray == -1) whose 4 assigned engineers have
         * all arrived (uid valid, destination reached, height diff <= 16, Chebyshev micro distance < 30) the crew
         * fades in (0x6D fade -> US_AIM_WEAPONUnk) and the tower returns to state 0; otherwise every 16 ticks
         * (fixedRng^ticks) it scans all live engineers ordered UIT_MAN_SIEGE_EQUIPMENT on this tower within the
         * same limits, bucketed per player (max 4): if the owner has 4 they board, else the first player 1..8 with
         * 4 captures the tower (deselect, owner/colour change, new tribe) and boards; crew refs/UIDs are stored,
         * count = 4, state 0. Moving: on arrival at a UIT_ATTACK_WALL target it docks (US_STAND_UPUnk) or re-paths
         * / picks another wall (findAccessibleWallAndNearbyFreeTile), else gives up. Docking: turns to
         * attackAtTileX/Y, then docked (US_STAND_UPUnk|US_IDLEUnk); if the wall belongs to the local player plays
         * General_Warning5.wav (solo or enemy team, 60 s cooldown); AI towers leave their tribe, human-owned towers
         * eject the 4 engineers onto free tiles (16-entry scatter table, fade-in) and reset the count; then places
         * an M_MAPPER_SIEGE_TOWER_BASE building linked to the unit. Docked: undoes its army count, unselectable,
         * copies its health ratio to the base building. Death: removes the crew once (loss/hit statistics), removed
         * after ~20 ticks with its base building; US_DISAPPEAR/0x6D: removed at once (loss statistic if crewed and
         * not killed). BUG (original game): on capture createTribe gets units[scanUnitIndex].owner, where
         * scanUnitIndex is the finished engineer-scan loop index (= maxUnitCount), not the new owner.
         */
        void __cdecl UpdateSiegeTower();

        /**
         * Per-tick state machine of a battering ram: counts it in owner's armySize/currentSiegeWeaponCount, colour
         * = owner. State 0 -> US_FIRE_WEAPONUnk when crew count != 4; US_FIRE_WEAPONUnk uses the same AI-crew check
         * and 16-tick engineer scan / capture / boarding as UpdateSiegeTower (including createTribe with the owner
         * of units[maxUnitCount]). Moving: on arrival -> state 0; stopUnitIfNextToTarget -> US_MELEE_ATTACK_WALL.
         * Attack: turns to attackAtTileX/Y, swing animation (FX_RAM_SWING at cycle 2); at frame 10 plays FX_RAM_HIT
         * if the tile has a hurt sound, toggles nextAttackHurtsWall, warns the local player with
         * General_Warning6.wav when an enemy ram hits his live large/small gatehouse or wooden gate (180 s
         * cooldown, TIME_LastRamGateWarningMoment updated only when played), deals 50 damage via processDamageToBuildingThunk and,
         * if that returns TRUE and the ram cannot re-target near the building (LogicLayer bit 0x100 +
         * setDestinationNearTargetedBuilding), clears the target and asks the tribe for a new one (state 0 if
         * none). Death: removes the crew once (emenyHitArray), removed after 200 ticks. US_DISAPPEAR/0x6D: fade-
         * out, removed after 33 ticks; processUnitLossStatistic is called on every such tick while killedFlagUnk ==
         * 0 and crew == 4.
         */
        void __cdecl UpdateBatteringRam();

        /**
         * Per-tick AI for a chicken (current unit DAT_CurrentUnitSlotID): bumps owner's
         * nonInteractiveCitizenCountUnk and chickenCount2 (both reset every tick by resetCountsAndStatistics),
         * gives 1/4 of chickens sprite 0x9a. State 0: fade-in (state 109, step -1) if isDisappearingUnk, else by
         * RNG&15 walk to a random bakery (0), mill (1) or granary (2-4, FX_CHICKEN_CLUCK) as state 101, take a
         * random wander path via computeLadderClimbPath (5-7, state 120), or peck idly with random facing (8-15,
         * state 1). While pecking, a wolf/caged dog/hunter dog on one of the 8 adjacent tiles makes it flap (state
         * 2, FX_CHICKEN_FLAP); any other non-chicken neighbour does so with 1/16 chance. Death state 111 and the
         * other death states play two different death animations ending in ULS_REMOVE; US_DISAPPEAR fades out with
         * alpha and tick tracker each incremented twice per tick (machine-code confirmed), so it is removed after
         * about 17 ticks. State values are reused with chicken-specific meanings.
         */
        void __cdecl UpdateChicken();

        /**
         * Per-tick AI for a mother (UT_MOTHER, current unit): bumps owner's someCount02 (mothers) and
         * nonInteractive counters (reset every tick), switches to US_DISAPPEAR if field280_0x3f4 > 1 or if the
         * owner's mothers+children counted so far this tick exceed 75 (cmp 0x4b / jle), pins health at 60000 and
         * turns any death state into US_DISAPPEAR, so she cannot die. State 0 (unless fading in): go idle; vanish
         * if the home building is gone; scream if enemies are present (skirmish: someCount46 == 0, otherwise
         * sumOfTotalEnemyUnitsCount != 0); otherwise by RNG%22 walk home, visit 2-5 gardens in a row (state 6,
         * count kept in resourceToDeposit), visit a chapel/church/cathedral or maypole/stocks/gallows, take a
         * random wander path, or (state 8) pick another idle mother of the same owner, who walks over (state 7),
         * and chat for 500 ticks (state 4). Idle state 1 plays the baby animation (FX_BABY at 50%, at most once per
         * 8 s of real time). Scream state 2 plays FX_GIRL_SCREAM (at most once per 5 s of real time, timeGetTime)
         * and then she runs home (state 5) and enters US_DISAPPEAR, which fades her out, sets ULS_REMOVE and clears
         * the home building's unitRefID. Raw offsets from units[0].manningEngineerRef/UIDRef/pathPlanStart are the
         * current unit's own fields (iVar11 = unitId*0x490).
         */
        void __cdecl UpdateMother();

        /**
         * Per-tick AI for a child (UT_CHILD, current unit): bumps owner's someCount03 (children) and nonInteractive
         * counters (reset every tick), switches to US_DISAPPEAR if field280_0x3f4 > 1 or if mothers+children
         * counted so far this tick exceed 75, pins health at 60000 and turns death states into US_DISAPPEAR. State
         * 0 (unless fading in): vanish at once if the home building (workplaceBuildingID_1) is gone, walk home and
         * vanish (state 5) if popularity < 50, run home and vanish (state 4) if enemies are present, otherwise by
         * RNG%25 visit home (101), take a random wander path (120), or start a game. Pair games: state 8 recruits
         * an idle child of the same owner (state 7) and they alternate states 6/9 for 1-5 rounds; state 12 recruits
         * a child with spriteID 0x81 or fixedRng&3==1 (state 11) and they alternate 10/13. The partner walks to a
         * tile next to the initiator using the 8-entry neighbour offset table. In the state 11 retry loop the index
         * (fixedRng&3)+i+4 can reach 8..10 and read past that table (original-game bug, minor). Follow-the-leader
         * (state 16): join a valid leader stored in PlayerData.childLeaderUnitId/childUID, or recruit (rng%8)+4 idle
         * children as followers (state 15), wait 300 ticks, then run 3-7 random wander legs (state 14). Followers
         * chase the leader's position +-3 tiles until the leader leaves states 14/16. State 17 walks to a nearby
         * (<21 tiles) selectable unit of the owner and watches it for 25-74 ticks; state 18 follows the lord +-3
         * tiles. Final fade-out sets ULS_REMOVE and removes the child from its home building's workerID/workerUID
         * list. Raw offsets from units[0].manningEngineerRef/UIDRef/pathPlanStart are the current unit's (or the
         * partner's) own fields.
         */
        void __cdecl UpdateChild();

        /**
         * Per-tick AI for a juggler (carnival unit): counts it in the owner's nonInteractiveCitizenCountUnk, sets
         * areCarnivalUnitsPresent (both reset every tick), and increments its lifetime counter jugglerCount; once
         * that exceeds 1999 the next decision switches to US_DISAPPEAR. targetingType is reused as a step counter:
         * step 0 starts a random wander path (computeLadderClimbPath(2,0,1) + changeDestinationByAmount 8, state
         * 120); steps 1-4 each pick one of four juggling acts by RNG&3 (states 2, 3, 4, or 5 followed by 6); step 5
         * starts another wander path and resets the step to 3 or 4, so later paths are followed by 1-2 acts. Also
         * handles fade-in (state 109, resets the step), US_DISAPPEAR fade-out and two death animations ending in
         * ULS_REMOVE.
         */
        void __cdecl UpdateJuggler();

        /**
         * Per-tick AI for a fire eater (carnival unit), same structure as UpdateJuggler: counts it as non-
         * interactive, sets areCarnivalUnitsPresent, disappears after jugglerCount > 1999, and uses targetingType
         * as a step counter (step 0 wander path; steps 1-4 one of three fire acts chosen by RNG%3: states 2, 3, 4;
         * step 5 another wander path with the step reset to 3 or 4). Also handles fade-in, US_DISAPPEAR fade-out
         * and two death animations ending in ULS_REMOVE.
         */
        void __cdecl UpdateFireEater();

        /**
         * Worker break helper (cdecl, unitID): increments unit.idle on every call. Whenever destinationNeeded is
         * set it clears it and walks the unit to a random positive-fear-factor building of its owner; if there is
         * none, it restores cachedState and sets destinationNeeded=2. Once the destination is reached: if idle (at
         * entry) exceeded target, it stores the excess idle-target in banked, restores cachedState, clears
         * field166_0x2fe and returns TRUE. Otherwise, the first time it enters the unit-type resting animation
         * state (unitTypeSpecificRestingState, if > 0) and returns FALSE; the next time it requests a new
         * destination. Returns TRUE in all other cases.
         */
        BOOLEnum __cdecl SetRestingForUnit(int unitID);

        /**
         * Per-tick AI for a woodcutter. State 0 at the hut: finishes the fade-in, goes home (state 9) if
         * goToRallyPoint is set, then waits until animationCycleNumber reaches 10; if the hut holds >2 logs he saws
         * (US_FIRE_WEAPONUnk/US_AIM_WEAPONUnk: every 48 ticks one RT_LOGS consumed and one plank added to the hut
         * via the workshop progress sign); when logs run out he takes 3 RT_WOOD out of the hut and carries
         * ComputeGoodsProduced units to a stockpile (US_LOOK_AROUNDUnk/US_STAND_UPUnk), depositing one every 5
         * ticks at the target, crediting finalWoodProduced and playing FX_STOCK_WOOD (rest discarded if no
         * stockpile can take it). Otherwise findTree (none -> freetime state 10), walk to it (state 1, records
         * woodcutterTreePathLength; re-picks an adjacent tile if shared, else goes home), fell it (state 2,
         * FX_CHOP, FX_LILTREE_FALL/FX_TREE_FALL by tree stage), cut the trunk 4 times (state 3), advance tree decay
         * and carry a log home (US_RELOAD_WEAPONUnk, FX_DROP_LOG). Also handles walk home with break check (arrival
         * -> state 10, substate 2/3), resting, freetime animations (state 10, substates 0-6), melee swing, death
         * animations and fade-out: every fade tick sets the hut's aiRestaffCountdown to 4000, and on removal adds
         * 10 to its aiAbandonCounter.
         */
        void __cdecl UpdateWoodcutter();

        /**
         * Per-tick state machine of the fletcher (unit DAT_CurrentUnitSlotID), reusing troop state values as work
         * phases: 0 = pick a stockpile with wood (none reachable -> free-time state 8); 1 = walk there and take 1
         * wood (stockpile empty -> try another); 2 = carry it into the workshop, then if workshop wood >= 2 (bow) /
         * 3 (crossbow) go to state 5, else back to 0 for another trip; 3 = walk back to the workshop empty-handed;
         * 5 = 30 ticks of work, then the workshop wood is zeroed; 4 = run the signpost counter until done, then
         * ComputeGoodsProduced sets the carried weapon count; 6 = find an armory with space (warns the local player
         * if all are full); 7 = once at the armory, deposit 1 weapon every 5 ticks (finalWeaponsProduced++,
         * FX_STOCK_WEAPON; full armory -> next one, none -> weapons are dropped). After delivery it may take a
         * break; otherwise the stockpile trip it sets up (state 1) is immediately overwritten by state 3 (return to
         * workshop), or the unit is removed if the workshop is unreachable. Also handles state 121 (resting), 8
         * (free-time animations), death animations, and fading out in US_DISAPPEAR followed by ULS_REMOVE.
         */
        void __cdecl UpdateFletcher();

        /**
         * Per-tick state machine of the tunneler (unit DAT_CurrentUnitSlotID). Every tick it first adds 1 to the
         * owner's armySize and currentTunnelers and registers the unit in a tribe. States: 0 picks an idle
         * animation (6 if the closest enemy is 97..400 away, else 5) or, on goToRallyPoint, walks to a free
         * tunneler assembly tile (0x69, counting PlayerData.tunnelerAssemblyCount every tick); 101 = ordinary walking (on
         * arrival a targeted building/wall -> US_MELEE_ATTACK_WALL, or US_FILL_MOAT on an owned moat if the order flag is
         * 0x3f7); 122 walks to a stored tile, then is placed there and continues to its planned destination in 101;
         * 7 walks to its workplace marker, 8 plays the dig-in animation (FX_DIG1), then destroys the marker and in
         * 109 fades into the ground, placing an M_MAPPER_TUNNEL entrance at the same tile as its new workplace,
         * then returns to cachedState 9; 9 calls findTunnelTarget, moves the unit to the entrance and requests a
         * path (path status 1); 3 digs along the path (raising tunnel height at frames 6/12/18 and with a brush at
         * frame 24), but removes the unit and the entrance at once if the path status is still 1; 4 waits 60
         * frames, deals 10 collateral + 10 building damage with FX_WALLDROP for 5 ticks, then destroys the building
         * on its tile (or resets the tile), applies applyTunnelDamageAlongPathPlan, destroys the entrance and
         * removes itself. It also handles wall attacks (damage 6 on wall tiles, 4 on gates/towers, 20 on other
         * buildings; AI owners may retarget), melee, and death/fade-out (removes its entrance and records loss
         * statistics).
         */
        void __cdecl UpdateTunneler();

        /**
         * Per-tick state machine for the hunter DAT_CurrentUnitSlotID (workplace = hunter's hut). With no meat in
         * the hut (resources[12]==0) and a valid worker in hut slot 1 it picks the nearest shootable deer, walks
         * into bow range (movementSpeed/anim chosen by tile distance: 1 when far, up to 10 when close), aims
         * (US_STAND_UPUnk|US_IDLEUnk) and shoots in state 10 (shootProjectile ET_ARROW_AND_DEFAULT + FX_ARROW_FIRE
         * at frame 0x16); once the deer is dying it walks to the carcass (US_SIT_DOWNUnk), then heads home (state
         * 2) and, if the carcass UID still matches, sets the deer's updateTickTracker to 1000; at the hut it fades
         * in, registers in the hut's workers[] (state 3, workshop progress sign) and fades out again. With meat in
         * the hut it takes 6 RT_MEAT, after 21 ticks picks a granary (warns if the local player's is full),
         * deposits ComputeGoodsProduced units one every 5 ticks (finalFoodProduced++, FX_STOCK_FOOD) and walks back
         * (removed if unreachable). With no deer it shows alert idles when an enemy is within 400 micro-units
         * (shooting it in solitary mode) or freetime animations. Also rally point, fade in/out, rest, melee and
         * death animations; generic weapon-named states are reused with hunter-specific meanings.
         */
        void __cdecl UpdateHunter();

        /**
         * Per-tick state machine for the quarry mason unit DAT_CurrentUnitSlotID (the stone work itself is driven
         * by the quarry building): in determine-next-state it finishes a fade-in (decrements
         * disappearFadeAlphaCountdown, clears isDisappearingUnk) or heads to the rally point (state 2, then
         * US_IDLEUnk + commitUnitLocation on arrival); US_IDLEUnk registers it in its workplace's
         * workers[workerIndex]; also handles state 0x6C, the melee-interrupt animation, death animations (then
         * US_DISAPPEAR) and the fade-out path (state 0x6E) which sets the workplace's idleTimerUnk to 4000 every
         * tick and after 32 ticks sets ULS_REMOVE (setLastEncounteredTroopUnit unless killedFlagUnk). In non-
         * solitary game modes it forces movementSpeed to 1.
         */
        void __cdecl UpdateQuarryMason();

        /**
         * Per-tick state machine of UT_QUARRYWORKER (unit-type handler table 0xB4DF60, index 8), the ox-tether
         * worker, not the stonemason (UT_QUARRYMASON, 0x550A50) or the ox (UT_QUARRYOX, 0x53F940). Its workplace is
         * the ox tether; oxTetherRelatedUnitID is the ox that UpdateOxTether spawns. States: 1 = at the tether,
         * after 20 cycles go to the quarry pile with the most stone (findQuarryPileThatIsCloseAndHasMostStone) via
         * 101, or, once the tether holds 8 stone (resources[4]), zero it, give the ox ComputeGoodsProduced(ox, 8)
         * as its load and walk to a stone stockpile itself (3); 101 = walk to the pile (then 2) or back with 1
         * stone (tether resources[4]++, then 1); 2 = after 20 cycles take 1 stone from the pile and carry it to the
         * tether (the pile was replaced -> return via 4); 3 = reach the stockpile, then 4 = walk back to the tether
         * (may take a break; unreachable -> free-time state 7). States 6/0x66 take one stone from the ox's
         * resourceToDeposit and carry it to a stockpile (FX_DROP_PLANK). Also handles rally point, resting (121),
         * melee, death animations and fade-out with ULS_REMOVE.
         */
        void __cdecl UpdateOxTetherWorker();

        /**
         * Per-tick state machine of the pitchman (UT_PITCHMAN). 0: after 10 cycles target the pitch rig entrance
         * (or ULS_REMOVE if none) and go to state 4; 4: walk to the rig (may take a break; unreachable ->
         * US_DISAPPEAR), then disappear into it via the fade state 109 (fade step +2, then state 1); 1: run the
         * rig's signpost counter until done, then reappear via 109 (countdown 0x20, step -2, then state 2) carrying
         * pitch; 2: every 21 ticks look for a pitch storage and, once one is reachable, set the load with
         * ComputeGoodsProduced(unit, 1) and walk there (state 3); 3: once there, deposit 1 pitch every 5 ticks
         * (finalPitchProduced++, FX_STOCK_PITCH), switch storage if full or drop the load if none is reachable,
         * then return to the rig (state 4; ULS_REMOVE if the rig is unreachable). State 109 ends after 17 ticks by
         * restoring cachedState, calling commitUnitLocation for a positive step and signpost counter mode 2. Also
         * handles free-time animation (state 5), resting (121), the death animation and fade-out removal.
         */
        void __cdecl UpdatePitchman();

        /**
         * Per-tick state machine of the wheat farmer (farm = workplaceBuildingID_1). 1 = idle animation at the
         * farm; when it ends, isFarmTileReadyForWheatStageChange picks DAT_BuildingsState.farmerDestinationTile and
         * the farm's wheatGrowStateRelated becomes the unit state. 3/4 = walk to a tile and hoe it (FX_HOE,
         * DamageLayer[tile] = 1 at animation cycle 8), repeating while the farm stage stays 3; 5 = walk tile to
         * tile setting DamageLayer = 2 while the stage stays 5; 6/7 = walk to a tile and harvest it (FX_HARVEST;
         * while DamageLayer < 0x78 it marks 0x78, every 3rd tile 0x79), continuing with stage 6 or 8; 8 = walk to
         * the last tile and mark it 0x78, then 9 = after 11 ticks find a wheat store (warning to the local player
         * if none), load = ComputeGoodsProduced(unit, 2, FALSE), walk there (10) and deposit 1 wheat every 5 ticks
         * (FX_STOCK_WHEAT; full store -> another, none -> load dropped), then go back to the field (stage 6/8) or
         * to the farm (2). Failing checks send the farmer back to the farm in state 2 (a break may be taken;
         * unreachable -> US_DISAPPEAR). Also handles rally point, resting (121), death animations and fade-out
         * removal.
         */
        void __cdecl UpdateWheatFarmer();

        /**
         * Per-tick state machine of the hops farmer, structured like UpdateWheatFarmer but using
         * setNewOnFarmDestination and target tile + hopFarmerDestinationOffsetX/Y. 1 = idle animation, then the
         * farm stage becomes the unit state; 3/4 = walk to a tile and plant (DamageLayer[targetedBuildingTile] =
         * 2), repeating while the stage is 3 (resourceToDeposit reset to 0); 5/6 = walk to a tile and harvest
         * (DamageLayer = 0x50, resourceToDeposit++), repeating while the stage is 5 until more than 5 harvests; 7 =
         * every 11 ticks look for a hops store (warning to the local player if none) and, once reachable, replace
         * the harvest count with the load ComputeGoodsProduced(unit, 1 in GM_SOLITARY else 2, TRUE) and walk there
         * (8); 8 = deposit 1 hops every 5 ticks (FX_STOCK_HOPS; full store -> another, none -> load dropped), then
         * harvest more (stage 5) or return to the farm (2). Also handles rally point, break, resting, death
         * animations and fade-out removal.
         */
        void __cdecl UpdateHopsFarmer();

        /**
         * Per-tick state machine of the apple farmer. 0 = (registering in the farm's workers[]) pick the closest
         * apple tree (LandscapeState::selectClosestAppleTree; tree index kept in workplaceBuildingTilePosition) and
         * walk to it (2), or idle (1) if none; 2 = on arrival pick (3) if the tree stage is 3, else go back to the
         * farm (5); 3 = picking animation, then resourcesGatheredCount++: below 4 walk to the next closest tree (8,
         * which again checks stage 3), at 4 find an apple store (granary-full warning to the local player if none)
         * and walk there (7) with load ComputeGoodsProduced(unit, 3, TRUE); if any of this fails, carry the apples
         * to the farm (4) and from there look for a store every 11 ticks (6); 7 = deposit 1 apple every 5 ticks
         * (finalFoodProduced[owner]++, FX_STOCK_FOOD; full store -> another, none -> load dropped), then return to
         * the farm (5, may take a break; unreachable -> US_DISAPPEAR) and start over in 0. States 4/5 write
         * animationCycleNumber and state through raw offsets from manningEngineerRef (decompiler aliasing). Also
         * handles rally point, resting, death animations and fade-out.
         */
        void __cdecl UpdateAppleFarmer();

        /**
         * Per-tick state machine of the dairy farmer (registers itself in the farm's workers[]). 1 = idle animation
         * at the farm; unless production is paused (CheckUnitProductionPaused): if the farm's resources[RT_CHEESE]
         * is set, clear it (and field23_0x44) and go to 4; while the farm's field214_0x298 is 3..4, fade out
         * (disappearFadeAlphaCountdown counts up past 32) into state 3, where it stays hidden until that value
         * leaves 3..4 and then fades back into state 1. 2 = walk to the farm (may take a break; unreachable -> back
         * to 1). 4 = every 11 ticks look for a cheese store (granary-full warning to the local player if none) and
         * walk there (5) with load ComputeGoodsProduced(unit, 3, TRUE); 5 = deposit 1 cheese every 5 ticks
         * (finalFoodProduced[owner]++, FX_STOCK_FOOD; full store -> another, none -> load dropped), then return to
         * the farm (2). Also handles rally point, resting, death animations and fade-out.
         */
        void __cdecl UpdateDairyFarmer();

        /**
         * Per-tick state machine of the miller (registers itself in the mill's workers[] every tick). 1 = sit/idle
         * at the mill (substates 100/0x65/0x6a/0x6b pick the animation), then find a wheat store and, once
         * standUpIfSeated reports no stand-up animation is needed, walk there (3); 3 = take 1 wheat (load =
         * ComputeGoodsProduced(unit, 1, FALSE)) and walk back to the mill (4), or try another store, else return to
         * the mill (2) or ULS_REMOVE; 4 = at the mill wait (6) while another miller occupies it (unitID) or it is
         * still grinding (killingPitField != 0), else claim it (unitID = self, outpostRelatedUnk4 = 300) and stay
         * inside (5) until killingPitField == 3; 7 = after the flour animation find a flour store (stockpile-full
         * warning) and walk there (8); 8 = deposit exactly 1 flour (FX_STOCK_HOPS) and go for wheat again. BUG
         * (confirmed): the flour load is ComputeGoodsProduced(unit, 0, TRUE), which is always 0, so when the first
         * store cannot take the flour the miller retargets another store but then immediately leaves for wheat, and
         * the flour is lost. Also handles the 109 fade transition (restores cachedState, signpost counter mode 2),
         * resting, death animations and fade-out.
         */
        void __cdecl UpdateMiller();

        /**
         * Per-tick state machine of the baker. 1 = sit/idle in the bakery (substates 100/0x65/0x6a..0x6d; field265
         * animation while production is paused), then find a flour store and, once standUpIfSeated needs no stand-
         * up animation, walk there (7); 7 = take 1 flour and walk back to the bakery (8), or, if the store is
         * empty, look for another one: BUG (confirmed) a successful path to the new store sets logicalState =
         * ULS_REMOVE, so the baker is removed, while a failed path sends him back to the bakery (2); 8 = on arrival
         * disappear into the bakery (fade state 109, step +2, then 4); 4 = register as workers[0], signpost counter
         * mode 2, then 3 = run the signpost counter until the batch is done, then reappear (fade 109, step -2, then
         * 5) carrying ComputeGoodsProduced(unit, 8, FALSE) bread; 5 = every 11 ticks look for a bread store
         * (granary-full warning) and walk there (6); 6 = deposit 1 bread every 5 ticks (finalFoodProduced[owner]++,
         * FX_STOCK_FOOD; full store -> another, with a 35-tick wait; none -> load dropped), then fetch flour again
         * (7) or return to the bakery (2). States 2 and 8 write animationCycleNumber, state, substate, fade fields
         * and cachedState through raw offsets (decompiler aliasing). Also handles rally point, resting,
         * US_DISAPPEAR fade-out (ULS_REMOVE after 32 ticks) and death animations.
         */
        void __cdecl UpdateBaker();

        /**
         * Per-tick state machine of the brewer. Every tick it registers as the brewery's workers[0] and, outside
         * GM_SOLITARY, sets movementSpeed = 1. 1 = sweeping idle animation (FX_BROOM, substates 0x66..0x69), then
         * walk to a hops store (2); 2 = take 1 hops and carry it to the brewery (3), or try another store, else
         * return to the brewery (4) or ULS_REMOVE; 3 = put the hops into the brewery and disappear into it (fade
         * 109, step +2, then 6); 6 = 30 ticks of brewing (signpost counter mode 3), then if the brewery has hops
         * take 1 and go to 5, else take 1 ale back out of the brewery and reappear (fade 109, step -2, then 7)
         * carrying ComputeGoodsProduced(unit, 1, TRUE) ale; 5 = run the signpost counter until done, add 1 ale to
         * the brewery, back to 6; 7 = every 11 ticks look for an ale store (stockpile-full warning) and walk there
         * (8); 8 = deposit 1 ale every 5 ticks (FX_STOCK_ALE; full store -> another, none -> load dropped), then
         * possibly take a break (ConsiderHavingABreakNowUnk) and fetch hops again, or return to the brewery (4; may
         * take a break, unreachable -> US_DISAPPEAR). Also handles rally point, resting, US_DISAPPEAR fade-out and
         * death animations.
         */
        void __cdecl UpdateBrewer();

        /**
         * Per-tick update of the current pole turner (DAT_CurrentUnitSlotID). State 1 plays an idle animation
         * (substates 0x66-0x69), then targets a wood stockpile (state 2); state 2 takes 1 wood and carries it to
         * the workshop (state 3), which adds it there and, once the workshop holds poleturner_spearOrPike wood (1
         * spear / 2 pike), fades into the building (state 109: alpha +2/tick for 17 ticks, then commitUnitLocation)
         * into US_FIRE_WEAPONUnk, else goes back to state 1 for more wood. US_FIRE_WEAPONUnk works 30 ticks, then
         * zeroes the workshop wood (resources[2]) and enters US_AIM_WEAPONUnk, which waits for the building
         * signpost counter, sets resourceToDeposit = ComputeGoodsProduced and fades back out (alpha -2/tick) into
         * US_LOOK_AROUNDUnk: after 11 ticks it targets an armory with space (armory-full warning for the local
         * player); US_STAND_UPUnk deposits the weapons one at a time (finalWeaponsProduced++, FX_STOCK_WEAPON),
         * retargeting another armory when full, then may take a break or immediately fetches wood again
         * (US_RELOAD_WEAPONUnk = walk back to workplace when no stockpile is reachable). Also handles rally point /
         * fade-in after appearing, resting (state 121), state 108, US_DISAPPEAR fade (sets workplace
         * idleTimerUnk=4000) and death animations that end in ULS_REMOVE.
         */
        void __cdecl UpdatePoleTurner();

        /**
         * Per-tick update of the current blacksmith. State 1 targets an iron stockpile and walks there (state 2);
         * if none is reachable it goes to state 9 (two alternating idle animations, may start free-time walking)
         * and then retries. State 2 takes 1 iron and carries it to the workshop (state 3), which adds it to the
         * workshop, commits the unit location and starts US_FIRE_WEAPONUnk: 30 ticks of work, then removes 1 iron
         * and goes to US_AIM_WEAPONUnk (waits for the signpost counter, then resourceToDeposit =
         * ComputeGoodsProduced, US_LOOK_AROUNDUnk); if the workshop has no iron at that point it instead removes 1
         * of the weapon type from the workshop and goes straight to US_LOOK_AROUNDUnk. US_LOOK_AROUNDUnk waits 11
         * ticks, targets an armory with space (armory-full warning for the local player); US_STAND_UPUnk deposits
         * weapons one at a time (finalWeaponsProduced++, FX_STOCK_WEAPON; sword vs mace animation by
         * producedItemTypeNext), then may take a break or fetches iron again. Also handles rally/fade-in, melee
         * attack, resting (121), state 108, US_DISAPPEAR fade-out (workplace idleTimerUnk=4000, then ULS_REMOVE)
         * and death animations that lead to US_DISAPPEAR.
         */
        void __cdecl UpdateBlacksmith();

        /**
         * Per-tick update of the current armourer. State 1 waits 20 ticks, then targets an iron stockpile (state
         * 2); if none is reachable it goes to state 9 (two alternating idle animations, may start free-time
         * walking) and back to 1. State 2 takes 1 iron and carries it to the workshop (state 3), which adds it
         * there and fades into the building (state 109, +2 alpha/tick, commitUnitLocation) into US_FIRE_WEAPONUnk.
         * US_FIRE_WEAPONUnk works 30 ticks; if the workshop still has iron it removes 1 iron and goes to
         * US_AIM_WEAPONUnk, which waits for the signpost counter, adds 1 RT_IRONARMOR (work in progress) to the
         * workshop and returns to US_FIRE_WEAPONUnk; when no iron is left it removes that 1 RT_IRONARMOR from the
         * workshop, sets resourceToDeposit = ComputeGoodsProduced and fades out of the building (-2 alpha) into
         * US_LOOK_AROUNDUnk. That state waits 11 ticks and targets an armory with space for item 0x18
         * (RT_IRONARMOR; armory-full warning for the local player); US_STAND_UPUnk deposits RT_IRONARMOR one at a
         * time (finalWeaponsProduced++, FX_STOCK_WEAPON), then may take a break or fetches iron again. Also handles
         * rally/fade-in, resting (121), state 108, US_DISAPPEAR fade (workplace idleTimerUnk=4000) and death
         * animations ending in ULS_REMOVE.
         */
        void __cdecl UpdateArmorer();

        /**
         * Per-tick update of the current tanner. State 1 plays an idle/sharpening animation (substates 0x66-0x69,
         * 0x7A; FX_SHARPEN on frames 3 and 11); when it ends, if the tannery holds hides (resources[5], enum
         * RT_PARTIALSTONE) it fades into the building to US_FIRE_WEAPONUnk, otherwise it picks the nearest idle cow
         * (findNearestIdleCowForPlayer), stores it as target and goes to state 2. State 2 follows the cow; on
         * arrival, if the cow is still valid and in state 0 it sends the cow (target = tanner, state 4) and itself
         * (state 3) to the workplace entry, else re-paths if any idle cow exists or resets to state 0. State 3
         * walks to the workplace, then switches to state 9 and faces the cow; state 9 is the slaughter animation
         * (cow set to state 6 and FX_COW_SLAUGHTER at frame 8) and at its end adds 3 hides to resource slot 5 of
         * the workplace and fades into the building. US_FIRE_WEAPONUnk works 30 ticks, removes 1 hide and goes to
         * US_AIM_WEAPONUnk (if no hide is left it only resets the timer and cachedState and stays in state 6);
         * US_AIM_WEAPONUnk waits for the signpost counter, sets resourceToDeposit = ComputeGoodsProduced and fades
         * out to US_LOOK_AROUNDUnk (11 ticks, then armory with space for item 0x17 = RT_LEATHERARMOR);
         * US_STAND_UPUnk deposits leather armour one at a time (finalWeaponsProduced++, FX_STOCK_WEAPON), then may
         * take a break or walks back to the workplace (state 4 -> state 1). State 0 without rally also sends it to
         * the workplace. Also handles melee attack, resting (121), state 108, US_DISAPPEAR fade and death
         * animations ending in ULS_REMOVE.
         */
        void __cdecl UpdateTanner();

        /**
         * Per-tick update of the current European (crusader) archer (DAT_CurrentUnitSlotID, re-cached after every
         * call). Counts it in the owner's armySize/currentArchers, stamps isSelectable_OR_matchTime with the map
         * time if 0, marks it ranged, calls addUnitToNewTribe and drops a light-pitch order once the ditch state is
         * >1. State machine: idle decision (fade-in, rally point 0x69, UIT_DIG_MOAT -> state 124 dig via
         * advanceMoatDigProgress, UIT_FILL_MOAT -> US_FILL_MOAT fill via removeMoat, attack order/acquireShootTarget ->
         * reload, else look-around (AI, far or 100000) / sit (enemy > 400) / stand), walking (the tribe's
         * selection-target unit issues UIT_RANGED_ATTACK_UNIT every 32 ticks for rallying or AI tribes not on stand-
         * ground; arrival handles tribe behaviour 0x400 -> US_DISAPPEAR and wall/moat targets), reload -> aim
         * (three aim-pitch animations, target re-validation and position cache) -> fire at frame 6 or
         * fireImmediately (entity 0x18 for ground/pitch shots, ET_ARROW_AND_DEFAULT at units, flaming
         * 0x5B/0x5C/0x5D near a brazier, FX_ARROW_FIRE/FX_FLAME_ARROW), look-around/stand/sit idle animations (cut
         * short once via idleInterruptedForAttack), melee and wall attacks (processDamageToBuildingThunk: 2 per hit
         * on wall tiles with every second hit dealing none, 1 on gates/towers, 4 on other buildings; AI retreat
         * checks), rally waiting (re-check every 40 ticks), US_FADE_TRANSITION (33 ticks, then campground walk or
         * ULS_TRANSITIONING), death animations, US_DISAPPEAR loss statistics and US_APPEAR placement.
         */
        void __cdecl UpdateCrusaderArcher();

        /**
         * Per-tick state machine (__cdecl, no args, no return) for the crossbowman in slot DAT_CurrentUnitSlotID:
         * bumps owner's armySize/currentCrossbowmen, joins a tribe, then by state: 0 chooses next state (rally
         * order -> 0x69; attack order or enemy within 0x1B0 with a target -> RELOAD 4; enemy > 400 -> idle 1; else
         * alert idle 2); 1/2 idle animations; 3/101/123 moving (every 32 ticks may acquire a target and give the
         * tribe UIT_SHOOT_TARGET; on arrival may switch to MELEE_ATTACK_WALL); 4 reload (FX_XBOW_WIND at frame 6)
         * -> 5 aim (face building/land/unit; frame table chosen by jugglerCount aim pitch 0/1/-1, refreshes target
         * position) -> 6 fire (at frame 2 shoots ET_CROSSBOWARROW at a unit or projectile 0x19 at land,
         * FX_XBOW_FIRE; then back to state 0); 0x69 rally waiting (rallySearchOffsetsUnk[1]++ each tick, rechecks
         * every 40 ticks); 106 melee; 107 wall melee (damage 2 to wall tiles and gates/towers, 4 to other
         * buildings; AI may retarget via TroopValueState); 109 fade; 110 disappear (kill/loss statistics); 111-116
         * deaths; 122 appear.
         */
        void __cdecl UpdateCrossbowman();

        /**
         * Per-tick state machine (__cdecl, no args, no return) for the spearman in slot DAT_CurrentUnitSlotID:
         * bumps owner's armySize/currentSpearmen, joins a tribe, then by state: 0 chooses next state (UIT_DIG_MOAT
         * -> dig state 124, UIT_FILL_MOAT -> state 125 = US_FILL_MOAT, on failure releases the moat reservation and
         * clears the order; AI player with no enemy within 400 -> 6 guard idle; enemy > 400 -> idle 1; enemy < 0x61
         * and an enemy ladderman found -> walk to climbX2/Y2 and state 3, else alert idle 2; rally -> 0x69); 3
         * pushes down the adjacent enemy ladder (findAndDestroyAdjacentEnemyLadder, speech UT_E_SPEAR 0x21 for the
         * local player at most every 4 s); 124 (and alias 4) digs: FX_MOAT_DIG, advanceMoatDigProgress per cycle,
         * stops when the tile has LogicLayer bit 0x40000000 or is occupied; 125 (and alias 5) fills: removeMoat per
         * cycle, 'General_Warning11.wav' at most every 180 s when a non-local spearman fills the local player's
         * moat; 6 guard idle facing signpost 0 outside skirmish; 101 moving (enemy-moat target 0x3f7 -> fill state,
         * else wall attack); 0x69 rally (rallySearchOffsetsUnk[2]); 106 melee; 107 wall melee (damage 4 to wall
         * tiles, 3 to gates/towers, 8 to other buildings; AI retargets via TroopValueState); 109 fade; 110
         * disappear; deaths (DEATH_02 lowers terrainOrClimbHeight to ground); 122 appear.
         */
        void __cdecl UpdateSpearman();

        /**
         * Per-tick state machine (__cdecl, no args, no return) for the pikeman in slot DAT_CurrentUnitSlotID: bumps
         * owner's armySize/currentPikemen, joins a tribe, then by state: 0 chooses next state (UIT_DIG_MOAT -> dig
         * state 124, UIT_FILL_MOAT -> state 125 = US_FILL_MOAT; AI player with no enemy within 400 -> 3 guard idle;
         * enemies alive -> 2 if one within 400 else 1; rally -> 0x69); 1 idle with seat substates (0x65 sit down ->
         * 0x6a/0x6b seated loops, 100 stand up, 0x66 standing; stands up when selected in GM_SOLITARY, never sits
         * on tiles with LogicLayer 0x10000100); 2 alert idle; 3 guard idle facing signpost 0 outside skirmish; 124
         * (alias 4) digs (advanceMoatDigProgress, stops if tile already has bit 0x40000000 or is occupied); 125
         * (alias 5) fills (removeMoat); 101 moving (enemy-moat target 0x3f7 -> fill, else wall attack); 0x69 rally
         * (rally class 4, rallySearchOffsetsUnk[4]); 106 melee (sprite base 0x123 when target stands >15 higher,
         * 0x1A3 when >=16 lower, else 0x163; substate cycles 0-3); 107 wall melee (damage 6 to wall tiles, 4 to
         * gates/towers, 20 to other buildings; AI retargets via TroopValueState); 109 fade; 110 disappear; 111-116
         * deaths; 122 appear.
         */
        void __cdecl UpdatePikeman();

        /**
         * Per-tick update of a maceman (DAT_CurrentUnitSlotID): counts it in owner's armySize/currentMacemen, puts
         * it in a new tribe, then runs its state machine. State 0 decides the next state: UIT_DIG_MOAT -> walk to a
         * friendly moat tile and enter dig state 0x7C, UIT_FILL_MOAT -> walk to it and enter fill state 0x7D
         * (US_FILL_MOAT), rally point -> 0x69, else AI-idle 3 / idle 1 / alert idle 2 (enemy within 400). State 0x7C
         * (also entered from 4) digs: FX_MOAT_DIG at cycle 5, advanceMoatDigProgress at cycle end, back to state 0
         * when done or the tile is already moat (0x40000000) or occupied. State 0x7D (also from 5) fills:
         * removeMoat at cycle end, leaves via moveUnitToBehaviorTarget when filled or no moat left. Walking checks
         * handleUnitMovementWhenTargetingBuildings every tick and switches to wall attack or (target flag 0x3F7)
         * moat filling; melee cycles 4 swing substates (FX_SWISH, hurt SFX); wall/building attack deals 6 to walls,
         * 4 to gates/towers, else 35 (FX_ATTACK_WOOD/STONE); an AI owner gives up on the target once its damage map
         * value exceeds the scale value +10 (gate/tower) or +15 (wall). Also fade transition (109), fade-out
         * removal with loss/kill statistics, three death animations and the appear-from-tile state.
         */
        void __cdecl UpdateMaceman();

        /**
         * Per-tick update of a swordsman (DAT_CurrentUnitSlotID): counts it in owner's armySize/currentSwordsmen,
         * puts it in a new tribe, then runs its state machine. State 0: rally point -> state 0x69
         * (isSpaceAvailableAtUnitRallyPoint group 5), AI owner -> combat-ready idle 3, else idle 1. Idle uses one
         * of four animations chosen by unitID&3 (variant 3 randomly plays FX_SHEATH_OUT/IN at cycles 11/80) and
         * ends immediately for AI owners. Walking never runs; only after arriving does it call
         * handleUnitMovementWhenTargetingBuildings and switch to wall attack. Rally state counts the unit in
         * rallySearchOffsetsUnk[5]. Melee alternates two swing animations via substate (FX_STEEL1/FX_STEEL2 against
         * armoured unit types, FX_SWISH, hurt SFX). Wall/building attack deals 10 to walls, 6 to gates/towers, else
         * 70 (FX_ATTACK_WOOD/STONE); an AI owner gives up on the target once its damage-map value exceeds the scale
         * value +10/+15. Also fade transition (109), fade-out removal with loss/kill statistics, death animations
         * and appear-from-tile.
         */
        void __cdecl UpdateSwordsman();

        /**
         * Per-tick update of a knight (DAT_CurrentUnitSlotID): counts it in owner's armySize/currentKnights, forces
         * imageIDUnk>=1, sets gmIDUnk=0x6E and displayColorPlayerID, puts it in a new tribe, then runs its state
         * machine. The knight is drawn as two sprites: gfxNumber from its own sheet and imageIDUnk, an image of GM
         * file gmIDUnk (0x6E) drawn as a second layer (variant chosen by unitID&1 in idle and melee). State 0:
         * rally -> 0x69 (group 6), AI -> combat-ready idle 3, else idle 1. Walking uses stateBasedSpeed 2 with
         * sheet offset 0x81 (gallop) unless run-up time or speed matching applies; only on arrival does it check
         * handleUnitMovementWhenTargetingBuildings. Rally counts the unit in rallySearchOffsetsUnk[5] and
         * rallySearchOffset. Melee strikes twice per cycle (FX_SWISH at 4/13, FX_STEEL1 vs armoured types at 5/14,
         * hurt SFX at 7/16). Wall/building attack updates only the second layer, plays the hit SFX at cycle 15 and
         * deals 10 to walls, 6 to gates/towers, else 70. Removal also untethers the knight from its origin stables;
         * deaths play FX_HORSE_DIE/FX_HORSE_FALL; plus fade transition and appear-from-tile.
         */
        void __cdecl UpdateKnight();

        /**
         * Per-tick update of a ladderman (DAT_CurrentUnitSlotID): resets the low word of unknownV to the sprite's
         * GM originY (states then add 0x10 when standing/idle or 0x20 when moving, raising the sprite's draw
         * anchor), counts it in owner's armySize/currentLaddermen, stores the first-seen map tick in
         * isSelectable_OR_matchTime, puts it in a new tribe and calls DetachLadderman if it is marked in position
         * but no longer in state 3. States: 0 decides rally (0x69 via findFreeEngineerAssemblyTile), idle 1, or
         * idle 2 when an enemy is 97..400 away, or disappear for STBT_0x400 tribes; 1 and 2 are idle animations
         * (two variants each by unitID&1); 3 = ladder placed against a wall (bumps a global TroopValueState
         * counter, fixed gfx by facing); walking (disappears on arrival for STBT_0x400 tribes); 0x67 walks to the
         * wall and on arrival faces it (getOrientationThatIsWallTowerOrGatehouse, idle if none), calls
         * UpdateLadderman_SetClimbData and plays FX_LADDER_PLACE; 0x69 rally waiting (bumps
         * someCount27/someCount28); fade transition (109); fade-out removal without loss statistics; deaths, where
         * US_DEATH_02 is the placed ladder being knocked down (directional frames, FX_LADDER_BREAK); appear-from-
         * tile.
         */
        void __cdecl UpdateLadderman();

        /**
         * Per-tick state machine for the engineer in slot DAT_CurrentUnitSlotID. Always re-adds it to a tribe and
         * bumps the owner's armySize/currentEngineers (livingEngineerCount only while not dying; AI behaviour 0x16
         * engineers also bump unknownHarrassingSiegeRelated and are removed once it exceeds 20), then switches on
         * the state: idle (1) / alert idle (2) animations, after which AI engineers (and any engineer with
         * goToRallyPoint in state 0) are sent to a free engineer assembly tile (state 0x69); moat digging (state
         * 0x7C, advanceMoatDigProgress) and filling (US_FILL_MOAT 0x7D, removeMoat); manning a siege building (state 8:
         * registers as worker when within 1 tile of the entry and under getRequiredEngineerCountForSiegeBuilding,
         * then fades out via US_FADE_TRANSITION into state 7, which fades it back in towards assembly when the
         * building uid changes); oil duty (12: fetch 1 RT_PITCH from a stockpile, 13: carry it to the work tile and
         * fade into the building, 14/15: workshop progress sign, 9: work/wait at the smelter, 11 US_SIT_DOWNUnk:
         * carrying a pot with auto-throw check, 10: throw via shootProjectile type 8 + FX_OIL_DUMP); death
         * animations -> US_DISAPPEAR, which records loss statistics. No return value.
         */
        void __cdecl UpdateEngineer();

        /**
         * Per-tick state machine for the iron-mine worker who carries iron from his mine
         * (workplaceOrHomeBuildingID, stock in resources[6]) to a stockpile. In non-solitary game modes
         * movementSpeed is forced to 1. US_IDLE re-registers him in the mine's workers[] slot every tick and after
         * 20 ticks goes to state 3 (load) if the mine has iron, state 5 (free-time animation) if it is empty, or,
         * when not next to the mine, state 2 (walk back to the mine entry; removed if that cannot be targeted).
         * State 3 retries every 11 ticks to pick an accessible stockpile (getBuildingThatCanStoreThisResource
         * RT_IRON), then takes 1 iron from the mine and sets resourceToDeposit = ComputeGoodsProduced(slot,1,TRUE);
         * state 4 walks there and unloads 1 iron per tick (addResourceToStockpile, finalIronProduced++,
         * FX_STOCK_IRON), re-targeting another stockpile when full or dropping the load when none is accessible,
         * then returns to the mine (state 2, may take a break, US_DISAPPEAR if no path). Also handles the rally
         * order, resting, fade, disappear (setLastEncounteredTroopUnit) and death animations; in the free-time
         * state the computed gfxNumber is immediately overwritten with facing+1 (dead store in the original,
         * 0x56656D).
         */
        void __cdecl UpdateMinerIronFetcher();

        /**
         * Per-tick state machine for the priest. Increments the owner's priestCount and forces US_DISAPPEAR when
         * blockedWaitCounter > 1. US_IDLE walks back to his church (targetX_2/Y_2); on arrival he fades out into it
         * (US_FADE_TRANSITION, stateAfterFade 2) and the chapel/church/cathedral bell rings. State 2 prays inside
         * for 301 ticks, then fades back in and picks the next outing from RNG(&7), selectNewBlessingTarget and
         * findClosestInnBuildingID: bless the target unit (US_STAND_UP), visit the closest inn (US_AIM_WEAPON walk,
         * US_FIRE_WEAPON 501 ticks inside, then an outdoor prayer animation in US_LOOK_AROUND), go to the owner's
         * campground entry (state 3, US_RELOAD_WEAPON 201 ticks inside) or play an outdoor prayer animation
         * (US_SIT_DOWN) and re-enter the church. Blessing walks toward the target; within axis distance < 5 it
         * stops, sets the target's blessedAmount = 8000 and plays a bless animation; up to 4 people are blessed per
         * outing (counted in resourceToDeposit), then he returns. Building enter/exit uses the 17-tick
         * US_FADE_TRANSITION with stateAfterFade, followed by updateWorkshopProgressSign(workplace,2). Also handles
         * resting, disappear and death animations.
         */
        void __cdecl UpdatePriest();

        /**
         * Per-tick state machine for the drunkard. Increments the owner's playerData.drunkardUpdateCount, sets
         * ownerColorIndex to 0 and forces US_DISAPPEAR when blockedWaitCounter > 1. US_IDLE requests a random
         * wander path via computeRandomWanderPath(slot,0,0,0) (US_DISAPPEAR if that fails) with a random speed of
         * 6-9; when movement is idle it goes to state 3, which plays one of three staggering animations (substate
         * 0..2) and returns to US_IDLE. After 6 staggers (counted in resourceToDeposit) it switches to US_DISAPPEAR
         * (0x6e) and is removed after a 33-tick fade. State 2 turns him back into a UT_PEASANT (ULS_TRANSITIONING);
         * US_MELEE_ATTACK plays the drunkard animation then resumeMovementIfNoAttackTarget. A unit in a death state
         * goes straight to US_DISAPPEAR without a death animation; any other state resets to
         * US_DETERMINE_NEXT_STATE.
         */
        void __cdecl UpdateDrunkard();

        /**
         * Per-tick state machine for the (black) monk military unit. Counts the monk into the owner's armySize,
         * marks it selectable and calls addUnitToNewTribe, then switches on the state. US_DETERMINE_NEXT_STATE: a
         * rally order whose workplace is a cathedral walks to findFreeCathedralAssemblyTile (falling back to the
         * cathedral entry; state 0x69, counted in monkAssemblyCount); otherwise idle state 1, or alert-idle state 2
         * when enemies exist and the closest is within 0x190 micro units. States 1/2 play idle animations (state 1
         * is cut short when an enemy is closer than 0xC0), then return to US_DETERMINE_NEXT_STATE via
         * moveToFreeTileNearby; state 0x69 counts into monkAssemblyCount every tick and, once arrived, re-checks
         * for a free assembly tile every 40 ticks. Also handles moving, melee attack (FX_SWISH) and attacking
         * walls/buildings via processDamageToBuildingThunk (damage 4 on wall tiles with LogicLayer bit 0x100, 3 on
         * gates/towers, 20 on other buildings, with AI-only retarget logic), US_FADE_TRANSITION (to the campground
         * or ULS_TRANSITIONING when isFadeActive), US_DISAPPEAR (removed once fadeLevel exceeds 32, with loss
         * statistics), death and appear animations.
         */
        void __cdecl UpdateMonk();

        /**
         * Per-tick state machine for the catapult. Counts armySize and currentSiegeWeaponCount. Idle
         * (US_DETERMINE_NEXT_STATE) needs exactly 2 manning engineers (else switches to the unmanned state
         * US_FIRE_WEAPONUnk); after the negative retargetDelayOrSiegeTile cooldown it acquires a target (AI:
         * harassBuildingsWithSiegeAI; human: acquireShootTarget plus a queued pendingTargetingType 5/0x16,
         * shootBeforeStop retries). State 8 turns toward targets within squared tile distance 0x15FA, state 2 loads
         * (FX_CA_LOAD), state 4 fires (FX_CA_FIRE) a stone using stoneAmmunition; an out-of-stones AI catapult
         * calls TryAcquireAmmunitionOrPlanToBuyStone. It can throw a cow instead (UIT_THROW_COW or AI
         * yieldCowThrow); a human player then needs playerData.cowCount >= 1, which is decremented and the nearest
         * idle cow removed. Unmanned state: an AI catapult re-mans when both recorded engineers have arrived within
         * |height diff| <= 16 and Chebyshev micro distance < 30; every 16 ticks (phase from fixedRng ^
         * totalGameTicks) it scans all units for live UT_E_ENGINEERs targeting it with UIT_MAN_SIEGE_EQUIPMENT (or,
         * for an AI catapult, with aiUnitBehaviourType 0x16) within the same range, buckets up to 2 per engineer
         * owner, and lets its own owner or else the lowest player 1..8 with 2 engineers capture it (owner/colour
         * change, new tribe); the two engineers fade out into the engine (US_FADE_TRANSITION, stateAfterFade
         * US_AIM_WEAPONUnk). Also handles moving, AI relocation (state 9) via
         * findReachableTileWithLowestZoneDistance with growing radius (5,10,20,60,120) after 6 missed or 5
         * friendly-structure shots, death (removes the manning engineers, loss/hit stats, removed after 201 ticks)
         * and fade-out removal. BUG (original game): after a capture createTribe gets units[counter].owner, where
         * counter is the finished engineer-scan index (= maxUnitCount), not the new owner, so the captured catapult
         * joins a tribe created for the wrong owner. BUG (original game): in the US_DISAPPEAR/0x6D branch
         * processUnitLossStatistic runs on every fade tick while killedFlagUnk == 0 and the crew is 2.
         */
        void __cdecl UpdateCatapult();

        /**
         * Per-tick state machine of the trebuchet (DAT_CurrentUnitSlotID); adds it to the owner's
         * armySize/currentSiegeWeaponCount. Idle needs 3 crew (else unmanned state US_FIRE_WEAPONUnk); AI targets
         * via harassBuildingsWithSiegeAI, humans via acquireShootTarget with retarget cooldown and shootBeforeStop
         * retries. Unmanned: an AI trebuchet waits for its 3 assigned engineers to arrive; every 16 ticks it scans
         * live engineers of ANY player ordered UIT_MAN_SIEGE_EQUIPMENT onto this unit (height diff <= 16, Chebyshev
         * micro distance < 30), the owner keeps priority, else the lowest player 1..8 with 3 such engineers
         * captures it; the crew fades out into the engine (US_FADE_TRANSITION, stateAfterFade US_AIM_WEAPONUnk).
         * State 8 aims (dist^2 < 0x1C3A), state 2 loads (FX_TR_LOAD, FX_TR_FIRE), state 4 fires when overlay frame
         * 0x1B is reached (stone, or cow: humans spend playerData.cowCount and remove the nearest idle cow, AI asks
         * yieldCowThrow). US_MOVE_TO_DESTINATION just resets to idle (it cannot move). Death removes live crew,
         * updates hit stats and removes the unit after ~200 ticks; US_DISAPPEAR/0x6D fade out. BUG (original game):
         * after a capture createTribe gets units[counter].owner, where counter is the finished engineer-scan index
         * (= maxUnitCount), not the new owner, so the captured trebuchet joins a tribe created for the wrong owner.
         * BUG (original game): in the US_DISAPPEAR/0x6D branch processUnitLossStatistic runs on every fade tick
         * while killedFlagUnk == 0 and the crew is 3.
         */
        void __cdecl UpdateTrebuchet();

        /**
         * Per-tick state machine of the mangonel (DAT_CurrentUnitSlotID); adds it to the owner's
         * armySize/currentSiegeWeaponCount. Idle needs 2 crew (else unmanned state US_FIRE_WEAPONUnk); it only
         * acquires a target if an enemy is within micro distance 0x2A8 or it has an attack-land/attack-building
         * order, and an AI mangonel falls back to findClosestEnemyBuildingWithinRadius(0x44) as attack-building
         * target. Unmanned: an AI mangonel waits for its 2 assigned engineers; every 16 ticks it takes the first 2
         * live engineers of the OWNER ordered UIT_MAN_SIEGE_EQUIPMENT onto it (height diff <= 16, micro distance <
         * 30) - no capture; the crew fades out into it (US_FADE_TRANSITION, stateAfterFade US_AIM_WEAPONUnk).
         * US_LOOK_AROUNDUnk counts down the cooldown, retries acquireShootTarget (fail: cooldown -200) and on
         * success sets state US_FIRE_WEAPONUnk unless moving. State 8 aims at shootTarget micro/8 (or the target
         * building centre), turning if dist^2 <= 0x1324; state 2 loads (FX_MA_LOAD); state 4 fires (FX_MA_FIRE, on
         * frame 0x16 seven prepareProjectileTarget+shootProjectile ET_MANGONEL shots). Death removes live crew,
         * updates hit stats and after 200 ticks removes the unit and clears containsSiegeMangonel1OrBallista2 of
         * the building under it (also at the end of the fade-out); state 9 (US_STAND_UPUnk|US_IDLEUnk) removes the
         * unit and its live crew at once. BUG (original game): in the US_DISAPPEAR/0x6D branch
         * processUnitLossStatistic runs on every fade tick while killedFlagUnk == 0 and the crew is 2.
         */
        void __cdecl UpdateMangonel();

        /**
         * Per-tick state machine for a lion (DAT_CurrentUnitSlotID). Increments mapAndTime.lionCount, fades the
         * unit in (fadeLevel--), counts down cooldownTicks and, while its tribe isProvoked, clears the cooldown and
         * the tribe's pendingEventFlag. In state 0 it faces the tribe leaderUnitID and, when off cooldown and
         * pendingEventFlag is 0, picks prey via findClosestPreyInArea: radius 200 (flag TRUE) if provoked, else by
         * the tribe elapsedTicks calm counter (<10: no target, <3000: radius 0x19 FALSE, else 0x32 TRUE); then
         * tryAttackUnitID(prey or 0), or rest state 0xCD if that fails. Other states: get-up (substate 100) / walk
         * (0x65/0x78, speed by tribe wildlifeAlarmTimer), chase targetUnitId (0xCF), melee (FX_LION_ATTACK; then
         * cooldown 1000, calm counter reset, 'Lions are attacking' warning when the melee opponent belongs to the
         * local player, at most every ~90 s), standing idle 0xCC / lie-down-rest 0xCD, stop 0xD0, death animations
         * (FX_LION_DIE) into corpse state 0x75 (51 ticks), then US_DISAPPEAR fade-out and ULS_REMOVE.
         */
        void __cdecl UpdateLion();

        /**
         * Per-tick state machine for a hunter's dog. Each tick it increments the owner's
         * nonInteractiveCitizenCountUnk and goes to US_DISAPPEAR if field280_0x3f4 > 1. It is flagged ULS_REMOVE if
         * its hut (workplaceBuildingID_1/UID) is invalid, sleeping or has no worker, or if the master (hut
         * workerID[0]) UID no longer matches; that last case returns at once. Otherwise it increments the hut's
         * numberOfAnimals. In state 0 it starts a random walk (computeLadderClimbPath(3,1,1)) 25% of the time,
         * otherwise goes to alert-animation state 2 if an enemy is 1..200 away, else to idle animations (state 1).
         * The other states follow the master: walk/run to him when he is in state 1 (bark when the path is long),
         * idle animations by substate (3), go to the dying animal he shot (7), then a random run (8) with
         * FX_DOG_BARK and whimper/return (10/9; FX_DOG_WHIMPER, FX_DOG_PANT). It also handles melee and death
         * (FX_DOG_DIE, removed at the end of the animation) and the US_DISAPPEAR fade-out.
         */
        void __cdecl UpdateHunterDog();

        /**
         * Per-tick state machine for a lord (DAT_CurrentUnitSlotID). Copies closestEnemyMicroDistance into
         * PlayerData.closestEnemyDistanceToTheLord and, outside GM_SOLITARY (multiplayer/skirmish) while alive,
         * updates finalTimeAlive. An Arab lord (isArabLord==1) uses sprite 0xCD and most gfx numbers are lowered by
         * altSpriteGfxOffset=0x80. US_IDLE walks to the keep (targetX_2/Y_2, teleports if no path) and enters it
         * (state 2). State 2 picks an action every 11 ticks: in GM_SOLITARY with no enemy units, no
         * invasionImminent and cageDogCount+lionCount < 3 he visits the lady (if she is in state 3), walks to a
         * defensive building near the campground (US_LOOK_AROUNDUnk, then the at-building animation), walks to and
         * talks to a unit from findEligibleUnitByTimeAndLocation (US_AIM_WEAPONUnk / US_FIRE_WEAPONUnk) or wanders
         * (US_SIT_DOWNUnk); otherwise he goes to the keep (state 12; AI lords with recentDamageTimer > 10 go to the
         * campground entry, or to their last attacker within 30 tiles of it, when the keep is enclosed or the enemy
         * troop value is low) and looks around there (state 13). Talks and building visits are limited by
         * resourceToDeposit. For the lord the US_FADE_TRANSITION state switches to stateAfterFade immediately. Also
         * handles moving, wall/building melee (processDamageToBuildingThunk damage 10 for wall tiles, 6 for
         * gates/towers, 70 otherwise; FX_ATTACK_WOOD/STONE) and unit melee with the 'lord under attack' warning
         * (local owner, >120 s apart). Non-solitary death, processed once (lordDeathProcessedStatus=99): killer =
         * lastEncounteredEnemyPlayerID gets 25% of the victim's gold clamped 500..100000 into currentResources[15]
         * and 25% of each goods type in lordKillLootResources into pendingResources (victim's stock not reduced),
         * plus kill stats, finalGold, chat 'X has killed Y' / 'receives N gold' and the death Bink (chat and Bink
         * skipped for the scripted victim in campaign missions 0x11/0x13). Solitary death sets playerRelatedFlag=1
         * for all other players and lordDeathStatusOrKiller=10 (or the killer if not the local player). After the
         * death animation (lord-killed/victory voice at frame 16) and a 33-tick US_DISAPPEAR fade the unit is
         * removed: loss statistics, then outside GM_SOLITARY lordDeathStatusOrKiller=1, commemoration shrine
         * countdown at the keep, destroyPlayerCompletely(owner) and, for the local player, the build menu.
         */
        void __cdecl UpdateLord();

        /**
         * Per-tick state machine of the current jester (DAT_CurrentUnitSlotID). blockedWaitCounter > 1 forces
         * US_DISAPPEAR. US_IDLEUnk walks to targetX_2/targetY_2 and fades out into the hidden wait state 2, which
         * counts 400 ticks and then, by RNG&7, picks: 3-4 with an inn -> walk to the owner's inn entry
         * (US_AIM_WEAPONUnk), fade out, stay hidden 500 ticks (US_FIRE_WEAPONUnk) and reappear to US_IDLE;
         * otherwise, if findEligibleUnitByTimeAndLocation found a unit -> walk to it (state 3) and within axis
         * distance 5 perform (US_RELOAD_WEAPONUnk, cycling 4 animations by substate, at most 5 acts counted in
         * resourceToDeposit, looking for a new audience after each act); else wander with computeRandomWanderPath
         * legs (US_LOOK_AROUNDUnk, hopping gait) each ending with the arrival animation (US_STAND_UPUnk), 11 legs
         * then US_IDLE. Leaving the hidden state reappears via US_FADE_TRANSITION (fadeLevel 0x20, step -2) and
         * resets substate/resourceToDeposit. The fade state adds fadeAlphaStep to fadeLevel (clamped 0..31), after
         * 17 ticks sets state = stateAfterFade, calls commitUnitLocation when fading out and
         * updateWorkshopProgressSign(workplace, 2). Also: melee plays animJesterPerform0 then
         * resumeMovementIfNoAttackTarget, death animations -> US_DISAPPEAR, which fades and sets ULS_REMOVE after
         * 33 ticks.
         */
        void __cdecl UpdateJester();

        /**
         * Per-tick state machine of the current ballista; each tick also adds it to the owner's
         * currentSiegeWeaponCount/armySize. State 0: crew count != 2 -> US_FIRE_WEAPONUnk (wait for crew); else
         * counts the negative retry cooldown field248_0x3bc up to 0, then acquireShootTarget (human owners
         * additionally require closestEnemyMicroDistance <= 0x2A8 or an attack-land/building order and use
         * checkTargetBuildingPossibilityOrState/shootBeforeStop); failure sets cooldown -40 (or -80), success ->
         * US_STAND_UPUnk. US_FIRE_WEAPONUnk: for AI owners with 2 crew it re-hides both crew engineers once they
         * are back within 30 micro / 16 height and returns to state 0; every 16 ticks it looks for two own
         * engineers with UIT_MAN_SIEGE_EQUIPMENT aimed at this ballista within 30 micro / 16 height, fades them out
         * (US_FADE_TRANSITION, cachedState US_AIM_WEAPONUnk), deselects them, stores them in manningEngineerRef/UID
         * and sets crew count 2. US_LOOK_AROUNDUnk: cooldown/acquire (failure -200) -> US_FIRE_WEAPONUnk.
         * US_STAND_UPUnk: target tile (building centre for UIT_ATTACK_BUILDING); dist^2 > 0x1C39 -> cooldown -40
         * and state 0; turns until setUnitFacingDirectionForTargetXandY returns FALSE, then state 2 (load
         * animation, FX_BALLISTA_LOAD) -> US_RELOAD_WEAPONUnk (FX_BALLISTA_FIRE, ET_BALLISTA projectile on frame
         * 12, z +0x1A for unit targets) -> state 0. Death states: on the first tick remove the crew engineers and
         * update the local player's kill/loss counters; the wreck is removed after 900 ticks (clears the tile
         * building's containsSiegeMangonel1OrBallista2). US_DISAPPEAR/0x6D fade and remove after 32 ticks, calling
         * processUnitLossStatistic every tick while killedFlagUnk == 0 and crew == 2; state 9 removes the crew and
         * the ballista at once.
         */
        void __cdecl UpdateBallista();

        /**
         * Per-tick state machine for the current caged war dog (DAT_CurrentUnitSlotID); also increments
         * mapAndTime.cageDogCount, fades the dog in and counts down cooldownTicks. Marks the dog dying/US_DISAPPEAR
         * when its kennel (workplaceOrHomeBuildingID, checked by UID) is gone. Caged state 0xD2: every 33 ticks
         * (staggered by cagedogReleaseCheckMoment*8) it runs computeTotalUnitsWithinDistance(kennel owner, mode 0 =
         * enemies, radius 16) around the dog and, if the enemy troop value > 24 or count > 5, releases the dog
         * (US_FADE_TRANSITION from fadeLevel 0x1F with step -2, then US_DETERMINE_NEXT_STATEUnk). Free dog (state
         * 0) faces its tribe's leaderUnitID and attacks the closest enemy (range 15) around the kennel entry; with
         * none it walks back (0xD3) and fades into the cage (step +2, then 0xD2 with commitUnitLocation). This fade
         * variant ends when fadeLevel reaches 0 or 31 instead of after a fixed time. Also handles stop (0xD0), get-
         * up/walk (0x65/0x78), chase (0xCF), melee with FX_WOLF_ATTACK (resets the tribe's elapsedTicks), lie-
         * down/rest (0xCE), death animations with FX_WOLF_DIE, corpse state 0x75 (51 ticks) and removal after
         * US_DISAPPEAR.
         */
        void __cdecl UpdateCageDog();

        /**
         * Per-tick state machine for the current Arabian archer. Counts it in the owner's
         * armySize/countArabianArcher, ensures it has a tribe, and drops a light-pitch order if the ditch is
         * already burning (state > 1). Idle: AI rally order -> state 0x69 (walk to keep defence spot, re-checked
         * every 40 ticks, shooting enemies within 0x1B0; counted in countArabianArchersRelated each tick there);
         * otherwise acquires a shoot target or, by closest-enemy distance/AI status, goes to look-around, sit-down
         * or stand-up idles. Walking: periodic tribe shoot orders, wall attack or moat digging via
         * handleUnitMovementWhenTargetingBuildings. Reload -> aim (face target, snapshot target x/y/z) -> fire at
         * frame 0x16 (arrow 0x18, or flaming arrow 0x5b/0x5c/0x5d when a brazier is nearby, which can also light a
         * pitch ditch); sprite base chosen by jugglerCount (aim pitch). Also melee/wall attacks (wall tile damage
         * 2, gate/tower 1, other buildings 4), fade transition, appear, death animations, and US_DISAPPEAR removal
         * with loss/hit statistics.
         */
        void __cdecl UpdateArabianArcher();

        /**
         * Per-tick state machine for the current slave (DAT_CurrentUnitSlotID, re-cached after every call; its low
         * bits also pick idle-animation variants). Counts it in the owner's armySize/countSlaves2, marks it
         * selectable and ensures it has a tribe. Idle (state 0): a rally order (goToRallyPoint) -> state 0x69 (walk
         * to the keep spot from getKeepLocationForAIUnit(owner,12), re-checked every 40 ticks once arrived, counted
         * in countSlavesRallying every tick); UIT_DIG_MOAT -> findBestMoatTileForWork mode 1 and dig state 124
         * (advanceMoatDigProgress, FX_MOAT_DIG; stops when the tile already has the moat bit or is occupied);
         * UIT_FILL_MOAT -> mode 2 and US_FILL_MOAT (125), which fills via removeMoat and, when a slave of another player
         * fills a moat owned by the local player, plays General_Warning11.wav at most once per 180 s
         * (lastMoatFillWarningTime). If no path, the moat's workerReservation is reduced by 20. Otherwise
         * idle/alert animations by enemy distance (< 0x191). States 4/5 are normalised to 124/125. Also walking
         * (STBT_0x400 tribes disappear on arrival; wall targets -> US_MELEE_ATTACK_WALL, moat target 0x3F7 ->
         * US_FILL_MOAT), torch melee (FX_SLAVE_FIRE), building attack with FX_FIRE_POP (wallHitNoDamageToggle alternates
         * 0/1 per hit; damage 8 to buildings with flammability factor 0; a flammable building that is not burning
         * is lit via lightUpBuilding on hits where the toggle is 1, which is then reset to 0, plus the victory Bink
         * when lighting succeeds; burning or missing target -> retarget (AI) or idle), US_FADE_TRANSITION (33
         * ticks; to the campground or ULS_TRANSITIONING when isFadeActive), US_APPEAR, death animations and
         * US_DISAPPEAR removal (fadeLevel > 32) with loss/hit statistics.
         */
        void __cdecl UpdateSlave();

        /**
         * Per-tick state machine for the current slinger. Counts it in the owner's armySize/countSlingers2 (per-
         * tick total) and ensures it has a tribe. Idle: AI rally order -> state 0x69 (walk to keep defence spot,
         * re-checked every 40 ticks, shooting enemies within 0x1B0; counted in countSlingers each tick there);
         * otherwise acquires a shoot target or goes to sit-down (> 400) / stand-up idles. Walking: periodic tribe
         * shoot orders and wall attack via handleUnitMovementWhenTargetingBuildings. Reload: when finished, aborts
         * with field248_0x3bc = -40 if the unit/building target is at squared distance >= 0x1E5, else aim (face
         * target, FX_SLING_THROW, snapshot target x/y/z) -> fire at frame 12 (ET_SLINGER 0x21 at a unit, type 0x23
         * at ground/area, re-targets if the unit target became invalid); reload/aim/fire sprite base chosen by
         * jugglerCount (aim pitch: -1 0x161, 0 0x1c1, 1 0x221). Also melee/wall attack (wall tile damage 2,
         * gate/tower 1, other buildings 4), state 0x68/0x6c stand-still frames, fade transition, appear, death
         * animations and US_DISAPPEAR removal with loss/hit statistics.
         */
        void __cdecl UpdateSlinger();

        /**
         * Per-tick state machine for the Arabian assassin in slot DAT_CurrentUnitSlotID: first counts it into the
         * owner's armySize/countAssassins and puts it in its own tribe, then runs the state: idle animation
         * (variant = slot & 3), movement (on arrival may switch to wall attack or moat digging), rally state 0x69
         * (every 40 ticks at the rally point walks toward getKeepLocationForAIUnit and counts it in
         * countAssassinsAndArabianSwordsman), melee and wall attacks (wall damage 10 on wall tiles, 6 on
         * gates/towers, 70 on other buildings; AI owners may retarget), fade/disappear/death animations, appear,
         * and the hook-throw / climb-up / climb-down wall-scaling sequence. When the hook catches on a wall owned
         * by the local player (enemy assassin) and more than 30000 ms (timeGetTime, unsigned compare) passed since
         * lastAssassinWarningTime, plays 'General_Warning18.wav' (in single-player or for an enemy team) and restamps the
         * time.
         */
        void __cdecl UpdateAssassin();

        /**
         * Horse-archer shooting overlay animation for the unit slot unitID (really an int slot index; all callers
         * pass DAT_CurrentUnitSlotID). horseArcherShootingVariation 4 = aim (turns toward the building/land/unit
         * target, stores that direction, restores the body facing), 5 = draw (at its end refreshes the target
         * unit's position, or reacquires a target, else stops), 6 = release (at frame 0x1B fires: ground-targeted
         * arrow entity 0x18 when no target unit, otherwise ET_ARROW_AND_DEFAULT if the target is still valid and in
         * range, else reacquire/stop; plays FX_ARROW_FIRE). The upper-body sprite goes into imageIDUnk; variation 0
         * = not shooting.
         */
        void __cdecl UpdateHorseArcher_DoShooting(int unitID);

        /**
         * Per-tick state machine for the Arabian swordsman in slot DAT_CurrentUnitSlotID: counts it into the
         * owner's armySize/countArabSwordsman, puts it in its own tribe, then by state: 0 chooses next (fade-out
         * countdown, rally -> 0x69, owner aiControlStatusRelated > 0 with no enemy within 400 (or value 100000) ->
         * 3 guard idle, else idle); idle animation (variant = slot & 3; variant 3 plays sheath out/in SFX with 50%
         * chance at cycles 11/80); 3 guard idle facing signpost 0 outside skirmish/MP; movement (arrival may switch
         * to wall attack); 0x69 rally (every 40 ticks at the rally point walks to
         * getKeepLocationForAIUnit(owner,0x10), counts someCount23 and countAssassinsAndArabianSwordsman); melee
         * with hit SFX; wall melee (damage 10 on wall tiles, 6 on gates/towers, 70 on other buildings; AI owners
         * may retarget); fade transition, disappear, deaths and appear.
         */
        void __cdecl UpdateArabianSwordsman();

        /**
         * Per-tick state machine for the Arabian fire thrower in slot DAT_CurrentUnitSlotID: counts it into the
         * owner's armySize/countFirethrowers, puts it in its own tribe, then by state: 0 chooses next (shoot order
         * with a target -> reload state; else enemy > 400 -> sit-down idle, otherwise acquire target or stand-up
         * idle; the extra > 432 test is unreachable); moving (unit whose selectionTargetUnitID is itself, in a
         * rallying or AI-owned tribe not on stand-ground, every 32 ticks issues UIT_SHOOT_TARGET to its tribe when
         * a target unit is found); reload (target more than 11 tiles away -> field248_0x3bc = -40 and back to state
         * 0, else aim); aim (re-validates target) and fire (at frame 0x14 spawns ET_FIRETHROWER at a valid target
         * unit or ET_FIRETHROWER_UNTARGETED at a ground spot, plays FX_FIRE_THROW); sit/stand idles; 0x68 stand
         * still; 0x69 rally (every 40 ticks at the rally point shoots if an enemy is within 160, else walks to
         * getKeepLocationForAIUnit(owner,0xf); always counts countFireThrowers); melee, wall melee (damage 2 on
         * wall tiles, 1 on gates/towers, 4 on other buildings; AI owners may retarget), fade, disappear, deaths,
         * appear.
         */
        void __cdecl UpdateFireThrower();

        /**
         * Per-tick state machine for the fire ballista in slot DAT_CurrentUnitSlotID: counts it into
         * armySize/currentSiegeWeaponCount, then by state: US_DETERMINE_NEXT_STATEUnk needs a full crew (crew count
         * 2, else -> US_FIRE_WEAPONUnk = uncrewed); a negative retargetDelayOrSiegeTile makes it wait; AI owners
         * pick a unit target within 0x2A8 or a building via aiFindBuildingToAttack/harassBuildingsWithSiegeAI,
         * humans need a target (shootBeforeStop budget), then -> turn state; the turn state rotates toward the
         * target (building centre for building targets) if dist^2 < 0xB65 (else delay -60) and goes to load state 2
         * (FX_BALLISTA_LOAD) -> fire state (FX_ARAB_BALLISTA_FIRE at frame 12, ET_FIREBALLISTA projectile at frame
         * 13). The uncrewed state boards an AI crew that has arrived within 30 micro units/16 height, and every 16
         * ticks scans for 2 nearby engineers per player ordered to man it (or with AI behaviour 0x16 when the owner
         * is AI); if the owner lacks 2 but another player has 2 the ballista changes owner (deselect, owner/colour
         * fields, new tribe), then the 2 engineers fade into it as crew (US_FADE_TRANSITION) and it returns to the
         * determine state. Also AI siege-target path-finding with growing radii 5..120, and death/disappear
         * removing the crew and counting losses/hits. BUG (confirmed at instruction level): on capture the new
         * tribe is created for units[maxUnitCount].owner (the leftover scan counter), not for the new owner.
         */
        void __cdecl UpdateFireBallista();

        /**
         * Per-tick state machine for the horse archer in slot DAT_CurrentUnitSlotID: counts
         * armySize/countHorseArchers, own tribe, sets displayColorPlayerID = owner and calculatedOwnerPlayerIndex =
         * slot & 7, then by state: 0 chooses next (target -> shooting state with variation 4, else idle); idle
         * (rider and horse sprites); shooting state delegates to UpdateHorseArcher_DoShooting; moving (every 100
         * ticks, if not shooting and an enemy is within 432, acquires a target and starts shooting on the move;
         * arrival may switch to wall attack); 0x69 rally (every 40 ticks at the rally point shoots if an enemy is
         * within 432, else walks to getKeepLocationForAIUnit(owner,0xb); counts countRelatedToHorseArchers); melee
         * (two-part sprites, hit SFX); wall melee (damage 2 on wall tiles, 1 on gates/towers, 4 on other buildings;
         * AI owners may retarget); fade transition; disappear (loss statistics, decrements numberOfAnimals and
         * randomOutpostField of the origin stable); deaths with FX_HORSE_DIE/FX_HORSE_FALL; appear.
         */
        void __cdecl UpdateHorseArcher();

    } // namespace Units
} // namespace Map
} // namespace OpenSHC
