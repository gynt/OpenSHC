/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Buildings.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        /**
         * Per-tick update of the current hovel (DAT_CurrentBuildingID): disables animation, sets spriteID from its
         * hovelVisualStyle, refreshes the graphics layer once (oldVisualActiveState -1 -> 0), and registers the
         * building as AI-targetable and in the building registry.
         */
        void __cdecl UpdateHovel();

        /**
         * Per-tick update of the current woodcutter's hut: animates while workers[0] is set; increments the owner's
         * noLabourerBuildingCount when currentlyNeededEmployeeCount == 0, else countWoodcutters; stops if
         * destroyBuildingIfNoWorker returns non-zero. Otherwise zeroes field246_0x2d4 when field242_0x2c8 is set
         * and records the player's maximum field246 (someCount10) with its building id (someCount11), registers the
         * building, advances the work animation from field54_0x4bac (wrap -> field13_0x28++, field14_0x2c = 1;
         * FX_SAW at frame 16), sets wood-pile overlay sprites field20/field21 from resources[1]/[2] and animates
         * the owner flag outside GM_SOLITARY.
         */
        void __cdecl UpdateWoodcuttersHut();

        /**
         * Per-tick update of the current pitch rig: increments the owner's countPitchRigs, animates while staffed,
         * registers as targetable; per work phase (building.state 0 / 1-3 / 4) plays pitch SFX
         * (scoop/pour/waterlap/mudbub) on specific animation indices and takes frames from three
         * BuildingDefinedData tables; at the end of each animation cycle advances state 0->1->2->3->4 and from 4
         * back to 0 completing a work cycle (field13_0x28++, field14_0x2c = 1). field66_0xbe: 31 at index 0 of
         * phase 0 then decremented (0 after index 29), 0 in phases 1-3, animationIndex-0x28 late in phase 4, forced
         * to 0 when animationIncrement is 0 and otherwise clamped 0..31 (Ghidra shows it as resources-0x62 and
         * state as resources-8; verified: same offsets 0xBE/0x118). Clears field20_0x38 and animates the owner flag
         * outside GM_SOLITARY.
         */
        void __cdecl UpdatePitchRig();

        /**
         * Per-tick update of the current mercenary post: adds 5 to the owner's someCount04, registers the building
         * as AI-targetable and in the registry, and animates the owner flag outside GM_SOLITARY (else clears
         * field39_0x84).
         */
        void __cdecl UpdateMercenaryPost();

        /**
         * Per-tick update of the current barracks: adds 10 to the owner's someCount04, registers the building as
         * AI-targetable and in the registry, and animates the owner flag outside GM_SOLITARY (else clears
         * field39_0x84).
         */
        void __cdecl UpdateBarracks();

        /**
         * Per-tick update of an outpost (European/Arabian bandit camp): adds 10 to the owner's someCount04,
         * registers the building and animates the owner flag (field39_0x84; 0 in GM_SOLITARY). Stops here in the
         * editor and, outside solitary/skirmish-SP, while skirmishNoRushTicks runs. First run (field_0x314) tags
         * owner units in the 16x16 tiles around the centre with aiUnitBehaviourType 0x32. Garrison:
         * randomOutpostField is rolled to 6-7; every 1200 ticks (outpostRelatedUnk4) it counts live units in
         * insideUnitID1-4/workerID[0-3] and, if below that target, spawns an E/A archer at the entrance, sends it
         * to one of 15 random tiles within -7..+6 of the centre (the first one whose LogicLayer has 0x10000000,
         * else the first reachable one) and stores it in the first dead inside/worker slot. Raids: without a live
         * tribe it waits 2000 - outpostRelatedUnk06 ticks (min 100 in solitary/skirmish-SP, else min 400), picks a
         * random enabled troop table (bits of outpostRelatedUnk1 -> field270_0x30c, +8 for Arabian), creates an
         * aggressive tribe with target size (rand % tbl[3] + tbl[2]) * (outpostRelatedUnk2+1); afterwards every
         * max(tbl[0]-incByFourUnk, tbl[1]) ticks (min 50 in MP, scaled by 100-15*outpostRelatedUnk2 %) spawns
         * troops from tbl[4..11] (siege engines get 1-4 engineers; MP respects the army size limit), moves the
         * tribe to the entrance, and once it is full and outpostRelatedUnk3 has expired hands it to
         * aiRegisterTribeAndAssignTarget and shortens future intervals (+100 / +4).
         */
        void __cdecl UpdateOutpostBuilding();

        /**
         * Per-tick stockpile update: clears renderAnimation; every 4th tick (solitary mode or owner !=
         * mapAndTime.somePlayerID, not editor/Siege That, owner's someCountdown01 == 0 and
         * hasInitialResourceRecievingStarted == 0) moves one unit each of wood, hops, stone, iron, pitch, wheat,
         * ale and flour from the owner's startResources pool into this stockpile (if it has room) and
         * currentResources, setting hasInitialResourceRecievingStarted = 1 and refreshing the building graphics per
         * transfer; recounts the player's resources if anything moved. The flag is never cleared in this function.
         */
        void __cdecl UpdateStockpile();

        /**
         * Per-tick armory update: registers it; every 4th tick (not editor/Siege That, someCountdown01 == 0) moves
         * one of each starting weapon/armour (resources 0x11-0x18: bows .. metal armour) from startResources into
         * the armory and currentResources, setting resourceRelatedCountDown = 100, then calls countPlayerResources.
         * For metal armour (0x18) the original stores currentResources[0x18] = 1 instead of += 1 (machine-code
         * confirmed), but countPlayerResources recomputes that counter immediately, so it has no lasting effect.
         * Clears isArmouryAlmostFilledUp below 10 items; for allied/AI owners keeps buildingIsVisuallyActive while
         * the countdown runs; animates the flag into field36_0x78 and, only while buildingIsVisuallyActive, fills
         * up to four pile-overlay sprite slots (0x20+n bows, 0x30 crossbows, ... 0x70 swords, 0x80 leather, 0x00
         * metal armour; max 16 per slot) from the largest remaining stocks.
         */
        void __cdecl UpdateArmory();

        /**
         * Per-tick fletcher's workshop update: counts it in countFletchersPoleturners, animates while staffed,
         * refreshes buildingVariation from the placement-rotation preview every 256 ticks, and advances the work
         * animation from BuildingDefinedData frame tables chosen by producedItemTypeNext (bow vs crossbow, crossbow
         * frames +0x24), state and solitary mode, playing FX_FLETCH_LONG for bows at animation indices 8/0x3a.
         * Phase 1 has frame tables only in GM_SOLITARY; in other modes it ends at once. At the end of an animation
         * cycle building.state goes 0->1, and 1->0 completes a product (field13_0x28++, field14_0x2c = 1). Steps
         * field66_0xbe (31 down to 0 in phase 0, = animationIndex in phase 1; Ghidra shows it as resources-0x62 and
         * state as resources-8) and clamps it to 0..31, marks the building visually active while the worker's state
         * is US_AIM/RELOAD_WEAPON and animates the owner flag outside GM_SOLITARY.
         */
        void __cdecl UpdateFletchersWorkshop();

        /**
         * Per-tick blacksmith update: counts it in countArmorersAndBlacksmiths, animates while staffed, refreshes
         * buildingVariation every 256 ticks. Swords: work phases building.state 0..7 with per-phase frame tables
         * (+0x18) and FX_BS_ANVIL (phases 1/3/5/6) / FX_BS_COOL (phase 7); at the end of phase 1 GM_SOLITARY goes
         * to phase 2, other modes skip to phase 6. Maces: 3 phases (+0x6e, phase 2 +0xaf) with FX_BS_POUR/OPEN
         * (phase 1) and FX_BS_FILE (phase 2). Finishing the last phase completes a product (field13_0x28++,
         * field14_0x2c = 1, state 0). Visually active while the worker is in state US_FIRE/AIM_WEAPON; only while
         * active it animates the forge overlay into field20_0x38 (campgroundVclock steps through the bellows table
         * field63_0x5010 with FX_BS_BELLOW when field27_0x54 is set, else the idle table field62_0x4ffc;
         * field27_0x54 is recomputed from state when a cycle ends), otherwise field20_0x38 = 0. A second overlay
         * field21_0x3c (field81_0x55c0 + 0x10) advances every 4th tick while staffed; the owner flag is animated
         * outside GM_SOLITARY.
         */
        void __cdecl UpdateBlacksmithsWorkshop();

        /**
         * Per-tick poleturner update: counts it in countFletchersPoleturners, animates while staffed, refreshes
         * buildingVariation every 256 ticks. Spears: 2 work phases (frames +0x5e; phase 0 plays FX_POLE_TURN and
         * uses field78_0x54cc in GM_SOLITARY / field79_0x555c otherwise, phase 1 uses field80_0x55a4). Pikes: 4
         * phases (phase 0 field74_0x5364 frames +0; phases 1-2 play FX_POLE_GRIND with field75_0x53bc /
         * field76_0x5484, phase 3 field77_0x54a8, frames +0x3d). At the end of each animation cycle building.state
         * advances; the last phase completes a product (field13_0x28++, field14_0x2c = 1, state 0). Steps
         * field66_0xbe and clamps it to 0..31, sets visually active while the worker is in US_FIRE/AIM_WEAPON and
         * animates the owner flag outside GM_SOLITARY.
         */
        void __cdecl UpdatePoleturnersWorkshop();

        /**
         * Per-tick armorer update: counts it in countArmorersAndBlacksmiths, animates while staffed, refreshes
         * buildingVariation every 256 ticks; phase 0 takes frames from field48_0x490c (GM_SOLITARY) /
         * field49_0x4acc, plays FX_ARMOUR_HIT when field48_0x490c[animationIndex] == 5 and steps field66_0xbe down
         * from 31; phase 1 uses field50_0x4b3c and sets field66_0xbe = 2*animationIndex. At the end of a cycle
         * state 0 -> 1, any other state completes a product (field13_0x28++, field14_0x2c = 1, state 0). Clamps
         * field66_0xbe to 0..31, sets visually active while the worker is in state US_FIRE_WEAPON / US_AIM_WEAPON /
         * US_FADE_TRANSITION (enum value apparently reused for a work state) and animates the owner flag outside
         * GM_SOLITARY.
         */
        void __cdecl UpdateArmorersWorkshop();

        /**
         * Per-tick tanner update: animates while staffed, refreshes buildingVariation every 256 ticks, offsets the
         * sprite by +1 while state < 7. Runs 11 work phases (building.state 0..10) with per-phase frame tables
         * (AnimTanner*, solitary variants; phase 10 animates only in GM_SOLITARY), FX_TANNER_BRUSH1/2 in phases
         * 1/3/5 and FX_TANNER_CUT in phase 7, stepping field66_0xbe; at the end of each animation cycle state
         * advances and phase 10 completes a product (field13_0x28++, field14_0x2c = 1). Clamps field66_0xbe to
         * 0..31, sets visually active while the worker is in US_FIRE/AIM_WEAPON and animates the owner flag outside
         * GM_SOLITARY. Unlike the other workshops it does not update a player workshop counter.
         */
        void __cdecl UpdateTannersWorkshop();

        /**
         * Per-tick update of the bakery DAT_CurrentBuildingID: registers it as AI-targetable and in the registry,
         * bumps the owner's countBakers (and someCount13 when currentlyNeededEmployeeCount == 0), and once every
         * 256 ticks (staggered by uid) recomputes buildingVariation via updateBuildingPlacementRotationPreview.
         * Runs a two-phase animation in Building.state: when the phase's table (field55_0x4c14 for state 0,
         * field56_0x4da0 for state 1) hits a non-positive entry the index resets and state 0 -> 1, or state 1 -> 0
         * with field13_0x28++ and field14_0x2c = 1 (one batch done); plays FX_BAKE/FX_BAKE2 on specific animation
         * indices; sets the intensity field66_0xbe (state 0: 31 then -2 per frame up to index 15, else 0; state 1:
         * index*2; clamped 0..31). Then sets visual-active if the worker's unit state is US_RELOAD_WEAPONUnk or 3,
         * overlay field20_0x38 (0 without worker, 0x44 in state 1, else 0/0x41..0x44 by animation index), overlay
         * field21_0x3c from the field81_0x55c0 table (advanced every 4th tick via field28_0x58/field25_0x4c) while
         * a worker exists, and the multiplayer owner flag (field39_0x84).
         */
        void __cdecl UpdateBakery();

        /**
         * Per-tick update of the brewery DAT_CurrentBuildingID: registers it, marks it visually active while the
         * brewer (workerID[0]) is in unit state US_FIRE_WEAPONUnk or US_AIM_WEAPONUnk, bumps countBrewers
         * (someCount12 when no employee is needed), and every 256 ticks recomputes buildingVariation. Runs an
         * 8-phase brewing animation in Building.state (0..7, each phase advancing when its table entry is non-
         * positive; phase 7 increments field13_0x28, sets field14_0x2c = 1 and restarts at phase 4 when
         * currentGameMode != GM_SOLITARY, phase 0 otherwise), plays FX_STIR on specific frames, sets overlay
         * field20_0x38 from the field82_0x55d4 table (+0x30) while active, overlay field21_0x3c from field81_0x55c0
         * while a worker exists, and the multiplayer owner flag.
         */
        void __cdecl UpdateBrewery();

        /**
         * Per-tick update of the granary DAT_CurrentBuildingID: every 4th tick (not in GM_EDITOR/GM_SIEGE_THAT, and
         * only while the owner's goodsDeliveryDelay == 0) moves one unit each of the owner's
         * pendingResources[10..13] (bread, cheese, meat, apples) into currentResources and the granary while
         * computeResourceSumForBuilding < 250, setting deliveryActivityCountdown = 100 and calling
         * countPlayerResources if anything moved. Clears granaryIsAlmostFilledUp when the granary holds < 230; for
         * the local team or AI owners keeps it visually active while the countdown runs. Adds non-banned food to
         * the owner's bread/cheese/meat/apple counts and totalFood, then, if active and non-empty, fills the 16
         * overlay frames with food-pile frames by repeatedly taking a chunk (bread 32, cheese/meat 16, apples 8) of
         * the largest remaining stock.
         */
        void __cdecl UpdateGranary();

        /**
         * Per-tick update of the inn DAT_CurrentBuildingID: visually active while an innkeeper exists and the inn
         * has ale (flagonsOfAleOrCheeseOrReleaseDogs) or a running field204_0x28a timer. While active it steps
         * overlay counters campgroundVclock (field20_0x38, which is then overwritten with 0), field25_0x4c
         * (field21_0x3c from field173 or, while the timer runs, field174), field26_0x50 (field22_0x40, only while
         * the innkeeper is in US_AIM_WEAPONUnk) and field27_0x54 (field23_0x44, while the timer runs), and
         * decrements field204_0x28a, calling spawnDrunkard when it reaches 0. If ale > 0: with an innkeeper the
         * short at +0x2b2 counts up and at >= owner's aleRate resets and consumes one flagon; workingInnsCount++ if
         * ale remains and a worker exists. Always countInns++, refreshes the graphics layer on visual change and
         * the multiplayer owner flag.
         */
        void __cdecl UpdateInn();

        /**
         * Per-tick update of the apothecary DAT_CurrentBuildingID: visually active and animating only while its
         * worker is in unit state 2 (otherwise animationIndex reset to 0); steps the field171_0x7bd4 animation
         * table (negative entry wraps to index 0, field13_0x28++ and field14_0x2c = 1, else field14_0x2c = 0),
         * refreshes graphics layer on visual change and updates the multiplayer owner flag.
         */
        void __cdecl UpdateApothecary();

        /**
         * Per-tick update of the tunnelers guild DAT_CurrentBuildingID: registers it as AI-targetable and in the
         * registry, disables animation and updates the owner flag animation (only when currentGameMode !=
         * GM_SOLITARY, otherwise flag frame 0).
         */
        void __cdecl UpdateTunnelersGuild();

        /**
         * Per-tick update of the marketplace DAT_CurrentBuildingID: in GM_SKIRMISH_AND_MULTIPLAYER always active
         * and animated; otherwise active while mapAndTime.traderState == 2. On becoming active field66_0xbe = 31
         * and field13_0x28 = 0, on becoming inactive field66_0xbe = 1 (still animated while 1..31). Steps the
         * AnimMarketPlace table (wrap -> field13_0x28++, field14_0x2c = 1), then moves field66_0xbe down (no cycle
         * completed yet) or up, clamping to 0 and stopping animation at 32; updates the multiplayer owner flag.
         */
        void __cdecl UpdateMarketplace();

        /**
         * Per-tick update of the current oil smelter (DAT_CurrentBuildingID): registers it as targetable/in
         * registry, then runs a 9-state animation machine on state (0->2, 1 idle; 2-5 boiling cycle where state 4
         * at frame 0x1C adds one pot to resources[7] and arms the flare-up effect via field117_0x11a; 6-8 pot hand-
         * over where the end of state 7 removes one pot from resources[7] and, if the unit in field_0x2a0 is a
         * UT_E_ENGINEER waiting in state US_STAND_UPUnk|US_IDLEUnk, sets its resourceToDeposit=1). Then picks the
         * fire/flare overlay frame (field21_0x3c) by the pot count resources[7] (FX_POT_FLARE_UP, FX_POT_OPEN,
         * FX_OIL_REFILL sounds), refreshes graphics when needed and animates the multiplayer owner flag
         * (field39_0x84, 0 in solitary mode).
         */
        void __cdecl UpdateOilSmelter();

        /**
         * Per-tick update of the current wheat farm: counts it in the owner's countFarms (and farmsWithoutWorkers
         * when workers[0]==0), registers it as targetable/in registry, clears renderAnimation, every 151 ticks
         * (growCounter > 150) calls growWheat, refreshes the wheat field tile graphics and animates the multiplayer
         * owner flag (field39_0x84, 0 in solitary mode).
         */
        void __cdecl UpdateWheatFarm();

        /**
         * Per-tick update of the current hops farm: counts it in the owner's countFarms (and farmsWithoutWorkers
         * when workers[0]==0), registers it as targetable/in registry, clears renderAnimation, every 401 ticks
         * (growCounter > 400) calls growHops, refreshes the hops field tile graphics and animates the multiplayer
         * owner flag.
         */
        void __cdecl UpdateHopsFarm();

        /**
         * Per-tick update of the current apple farm: counts it in the owner's countFarms (and farmsWithoutWorkers
         * when workers[0]==0), registers it as targetable/in registry, clears renderAnimation and animates the
         * multiplayer owner flag (no growth logic here).
         */
        void __cdecl UpdateAppleFarm();

        /**
         * Per-tick update of the current dairy farm: updates owner farm stats and registers it; with no farmer
         * (workers[0]==0) it resets all animation state. Otherwise a state machine in field214_0x298 runs: with <3
         * cows and no cooldown (flagonsOfAleOrCheeseOrReleaseDogs==0) a 400-tick timer leads to states 1-2 that
         * spawn a UT_COW into the first free/invalid cow slot (workerID[1..3]/workerUID[1..3], fading in);
         * otherwise, while resources[11]==0, the timer picks the next cow slot (field215_0x299), sends that cow
         * into fade state US_FADE_TRANSITION and plays the milking animation (states 3-6, FX_COW_MILK/FX_MILK_POUR)
         * ending with resources[11]=1. Afterwards it drops cow slots whose uid no longer matches, resets
         * numberOfAnimals and animates the multiplayer owner flag.
         */
        void __cdecl UpdateDairyFarm();

        /**
         * Per-tick update (only every other tick, via field28_0x58 parity) of the current mill: counts
         * workers[0..2], validates the miller in unitID (must be ULS_NORMAL, UT_MILLER, state US_AIM_WEAPONUnk) and
         * sets visual-active state accordingly, then animates: sails (field23_0x44 via field134 table) whose frame
         * advance slows as the grind timer outpostRelatedUnk4 runs down (every tick >=51, then every 2/4/8 ticks),
         * the inactive/active grinding layers (field20_0x38 / field21_0x3c; note field21_0x3c is written twice, the
         * second write wins) and the miller sub-animation (field22_0x40) driven by killingPitField 0-3, plus the
         * multiplayer owner flag.
         */
        void __cdecl UpdateMill();

        /**
         * Per-tick update of the current stables: validates tethered units, breeds a new horse when
         * outpostRelatedUnk4 exceeds 550 (every 551 ticks) while numberOfAnimals < 4 (then recounts
         * stables/horses), and every 6th tick animates the four horse sprite layers field20..23 (0 when that horse
         * does not exist, a fixed frame 0x2A..0x27 when randomOutpostField >= its index, otherwise the field147
         * idle animation) and then the multiplayer owner flag.
         */
        void __cdecl UpdateStables();

        /**
         * Generic per-tick building update shared by several building types: registers the current building as
         * targetable and in the registry, clears renderAnimation and animates the multiplayer owner flag
         * (field39_0x84 = 0 in solitary mode).
         */
        void __cdecl UpdateBuildingShared2();

        /**
         * Per-tick update of the current cathedral: registers it, clears renderAnimation, animates the multiplayer
         * owner flag, and in campaign mission 7 swaps its sprite to the damaged version (spriteID 0x11F, then
         * updateBuildingGraphicsLayer) once currentHealth <= 30% of maxHealth (field249_0x2da is the damaged flag,
         * cleared again above 30%).
         */
        void __cdecl UpdateCathedral();

        /**
         * Per-tick update of a manor-house keep DAT_CurrentBuildingID: no animation, keeps currentHealth at
         * maxHealth, sets someX/someY = (x+3, y+9). Every 4th tick (not in GM_EDITOR/GM_SIEGE_THAT) moves the
         * owner's pending startResources[15] (gold) into currentResources[15] in a chunk of 1 (<= 100 left), 10
         * (101..1000 left) or 100 (> 1000 left), sets the keep's resourceRelatedCountDown = 100, writes the new
         * gold total (as short) into lastMonthsGold and beforeLastMonthsGold and sets DAT_GameCore.countdown = 1.
         */
        void __cdecl UpdateKeepManorHouse();

        /**
         * Per-tick update of a stone keep: same as UpdateKeepManorHouse (health kept at max, pending start gold
         * moved into currentResources every 4th tick in chunks of 1/10/100) but with someX/someY = (x+3, y+2),
         * displayOwnerFlag = 1 and overlay field20_0x38 = 0x18.
         */
        void __cdecl UpdateKeepStoneKeep();

        /**
         * Per-tick update of a stronghold keep: same as UpdateKeepManorHouse (health kept at max, pending start
         * gold moved into currentResources every 4th tick in chunks of 1/10/100) but with someX/someY = (x+5, y+4),
         * displayOwnerFlag = 1 and overlay field20_0x38 = 0x1b.
         */
        void __cdecl UpdateKeepStronghold();

        /**
         * Per-tick update of a drawbridge: state machine on drawBridgeState1 (0 lowered, 1 raising via table
         * field139_0x6ae4 with FX_DRAWBRIDGE_RAISING/RAISED, 2 raised, 3 lowering via table field140_0x6b04 with
         * FX_DRAWBRIDGE_CONTROL/LOWERING/LOWERED) driven by drawbridgeState2 (10 in state 0 = raise, only if
         * isUnitBlockingSizeFiveFootprint is FALSE; 11 in state 2 = lower; set to 12 when accepted). Starting to
         * raise calls floodMoatUnderRaisingDrawbridge (sets LogicLayer bit 0x40000000 / moat visual state 2 on the
         * bridge's moat tiles); finishing lowering calls createWaterForDrawBridge (clears that bit, visual state
         * 0). Increments the owner's someCount31 for every bridge not in state 0 (and on the raise transition),
         * sets frames from field414_0xa38c[relativeRotation/2], per-rotation overlays (state 0 only) and sprite
         * offsets.
         */
        void __cdecl UpdateDrawBridge();

        /**
         * Per-tick update of a tunnel entrance linked to its tunneler unit (unitRefID): hidden (index 0, no
         * animation) while the tunneler is in unit state 3 or 4 (US_RELOAD_WEAPONUnk) or dying; in unit state 9
         * (decompiled as US_STAND_UPUnk|US_IDLEUnk) it plays the field95_0x5a18 dig animation (FX_DIG2 when the
         * frame value is 10 or 25) and when the table entry is 0xff sets the unit to state 3 with
         * tunnelerFinishedDigging = 2; in any other state it shows the first table frame.
         */
        void __cdecl UpdateTunnel();

        /**
         * Shared trivial building update: just disables animation rendering for DAT_CurrentBuildingID.
         */
        void __cdecl UpdateBuildingShared1();

        /**
         * Per-tick update of the campground: loops the field96_0x5a4c fire animation (field13_0x28++ and
         * FX_CAMPFIRE via DAT_SFX_Interval_Campfire on each wrap), shows overlays only while the mouse tile belongs
         * to it, maps the owner's vclock (clamped 0..4000, /40 - 50) to overlay frame field20_0x38. field40_0x88
         * acts as a start/stop delay: while field192_0x270 or field193_0x272 is non-zero it counts up to 40 before
         * the fire animates, otherwise it counts down while animating until the animation stops. Activity state
         * field194_0x274 (previous in field195_0x276): 1 if field192 < 2, 3 if < 5, else cycles 2->4->3->5->6->2 on
         * timeAlive thresholds (200/600/1000, state 5 = 6 x 300 ticks, state 6 = 13 x 80 ticks counted in
         * buildingProgress), calling updatePeasantSeatingAtBuilding(building, field192, 1 or 100) when timeAlive ==
         * 1 in states 5/6. Clears field192/field193 at the end.
         */
        void __cdecl UpdateCampGround();

        /**
         * Per-tick update of parade ground variant 2: animation on, static animation frame 0x20.
         */
        void __cdecl UpdateParadeGround2();

        /**
         * Per-tick update of parade ground variant 3: animation on, static animation frame 0x1f.
         */
        void __cdecl UpdateParadeGround3();

        /**
         * Per-tick update of parade ground variant 4: animation on, static animation frame 0x21.
         */
        void __cdecl UpdateParadeGround4();

        /**
         * Per-tick update of the gallows: registers it, updates the signpost counter, animates (visually inactive)
         * when the owner's fearFactorLevel < -2, otherwise shows the 'active' graphic for fear -2..-1 and inactive
         * for >= 0; steps the field158_0x75fc animation and refreshes the graphics layer on visual change.
         */
        void __cdecl UpdateBadBuildingGallows();

        /**
         * Per-tick update of the stocks: animates while the owner's fearFactorLevel < -1, steps the field159_0x7624
         * table, and plays FX_STOCKS at animation index 5 only while this building is selected with the stocks
         * status tab open.
         */
        void __cdecl UpdateBadBuildingStocks();

        /**
         * Per-tick update of the maypole: playerColorUnk = fireRelatedRNG1 % 9, animates while fearFactorLevel > 0;
         * if popularity is below 5000 + (rng & 0xff) plays the idle table field168_0x79c4 (+0x20), else the dance
         * table field167_0x7974, counting dance cycles in field13_0x28 and playing FX_MAYPOLE every 8th cycle.
         */
        void __cdecl UpdateGoodBuildingMaypole();

        /**
         * Per-tick update of a garden: disables animation and registers the building as AI-targetable and in the
         * registry.
         */
        void __cdecl UpdateGoodBuildingGarden();

        /**
         * Per-tick update of a placed siege tower building: marks it BLS_REMOVE when its linked unit is gone
         * (unitRefID == 0 or unitRefUID no longer matches the unit's uid).
         */
        void __cdecl UpdatePlacedSiegeTower();

        /**
         * Per-tick update of a well/water pot: registers it, disables animation (animationIncrement = 0) and runs
         * the owner flag animation when currentGameMode != GM_SOLITARY (flag frame 0 otherwise).
         */
        void __cdecl UpdateWellOrWaterpot();

        /**
         * Per-tick update of the left keep door piece: copies orientation from its parent keep (quarryStockpileID),
         * picks spriteID/gfxOffset for manor house (0x524/0x531) vs stone keep/stronghold (0x522/0x52c), and
         * refreshes the graphics layer when spriteID changed (oldVisualActiveState caches it).
         */
        void __cdecl UpdateKeepDoorLeft();

        /**
         * Per-tick update of the right keep door piece: like UpdateKeepDoorLeft but with the right-side sprite IDs
         * (0x528 manor / 0x526 keep).
         */
        void __cdecl UpdateKeepDoorRight();

        /**
         * Per-tick update of the keep door: copies the parent keep's orientation, animates while field62_0xb0 == 0,
         * selects sprite/gfxOffset and the map-orientation-dependent sprite offset and frame (mapOrientation 0/4 vs
         * others) for manor house or stone keep/stronghold, refreshing the graphics layer when the sprite changes.
         */
        void __cdecl UpdateKeepDoor();

        /**
         * Per-tick update of a small tower: sets fixed overlays (field20_0x38 = 0x7d, shouldRenderRoof = 0x7c),
         * fills min(9 - 9*health/maxHealth, 8) consecutive slots of the 8 overlay slots field33_0x6c..overlayFrame15
         * (start slot and sprite values 1..16 derived from fireRelatedRNG1) as damage overlays; while
         * field261_0x2fa runs it counts down and at 0 rescans the size-3 footprint's UnitLayer to set hasUnitsOntop
         * and restarts at 100; uses roof sprite 0x7e when units are on top.
         */
        void __cdecl UpdateTower1();

        /**
         * Trivial per-tick update (cess pit / dancing bear?): disables animation and overlays. NAME? the code is
         * generic and gives no evidence for either building type.
         */
        void __cdecl UpdateCessPitBeehivePondBearCave();

        /**
         * Per-tick update of the burning stake: registers it, updates the signpost counter, animates
         * (field163_0x778c table) while fearFactorLevel < -4, and plays FX_WITCH_BURN / FX_WITCH_SCREAM at
         * animation indices 0x2f/0x31 only while it is selected with its status tab open.
         */
        void __cdecl UpdateBadBuildingBurningStake();

        /**
         * Per-tick update of the gibbet: playerColorUnk = fireRelatedRNG1 % 9, registers it, updates the signpost
         * counter, animates (field162_0x7768) while fearFactorLevel < -3.
         */
        void __cdecl UpdateBadBuildingGibbet();

        /**
         * Per-tick update of the dungeon: adds it to the registry (not AI-targetable), updates the signpost
         * counter; animates and shows active graphic when fearFactorLevel < -3, active graphic without animation
         * for -3..-2, inactive otherwise; steps field160_0x766c and refreshes the graphics layer on visual change.
         */
        void __cdecl UpdateBadBuildingDungeon();

        /**
         * Per-tick update of the stretching rack: registers it, updates the signpost counter and animates
         * (field164_0x77e4) while fearFactorLevel < -2.
         */
        void __cdecl UpdateBadBuildingStretchingRack();

        /**
         * Trivial per-tick update of the flogging rack: disables animation and overlays and adds the building to
         * the registry.
         */
        void __cdecl UpdateBadBuildingRackFlogging();

        /**
         * Per-tick update of the chopping block: every 2nd tick (field28_0x58 throttle) sets displayOwnerFlag
         * (overlay visible) to fearFactorLevel < -3 and advances the overlay counter campgroundVclock through
         * field165_0x7884 into overlay field20_0x38 (wrapping to frame 1).
         */
        void __cdecl UpdateBadBuildingChoppingBlock();

        /**
         * Per-tick update of the dunking stool: registers it (AI-targetable + registry), clears overlays, updates
         * the signpost counter, sets renderAnimation/buildingIsVisuallyActive only while the owner's
         * fearFactorLevel < -4, sets animationFrame from table field161_0x76bc[animationIndex] (index wraps to 0
         * when the entry is < 1), plays FX_WH_DUNK/BREATH1/BREATH2/LIFT at animationIndex 4/0x22/0x48/0x68 only
         * while animating, selected and its status tab is open, and refreshes the graphics layer when the visual-
         * active state changed.
         */
        void __cdecl UpdateBadBuildingDunkingStool();

        /**
         * Per-tick update of a statue: registers it as AI-targetable and in the building registry, and clears
         * renderAnimation and the owner flag. Nothing else.
         */
        void __cdecl UpdateGoodBuildingStatue();

        /**
         * Per-tick update of a shrine: registers it as AI-targetable and in the registry, clears renderAnimation
         * and the owner flag, and copies buildingEntryX/Y into someX/someY.
         */
        void __cdecl UpdateGoodBuildingShrine();

        /**
         * Per-tick update of the dancing bear: registers it, clears overlays, updates the signpost counter, sets
         * renderAnimation = (owner's fearFactorLevel > 2) and sets animationFrame from table
         * field169_0x7a14[animationIndex] (index wraps to 0 when the entry is < 1).
         */
        void __cdecl UpdateGoodBuildingDancingBear();

        /**
         * Per-tick update of an ox tether: sprite = base sprite + 4*resources[RT_STONE] (stone carried), registers
         * it, runs the multiplayer owner-flag animation. While outpostRelatedUnk4 > 0 it only counts that cooldown
         * down. Otherwise, with a linked ox it clears the link if the unit's uid no longer matches, or starts a
         * 300-tick cooldown (link kept) if that unit is now UT_BURNING_ANIMAL_BIG; with no ox but a worker it
         * counts field28_0x58 and every 100th tick spawns a UT_QUARRYOX at the entrance tile and links it both
         * ways.
         */
        void __cdecl UpdateOxTether();

        /**
         * Per-tick update of the iron mine: increments the owner's countIronMines, registers it, then (every 2nd
         * tick via field28_0x58) runs four chained animation state machines while staffed, all reset when
         * unstaffed: `state` 0..6 (overlay field20_0x38, FX_IRON_PULL in state 3; states 5/6 go to idle state 6
         * while the mine's own store holds >= 7 iron, else to 0), killingPitField 0..3 (overlay field22_0x40,
         * starts at state 3 frame 0x50), field117_0x11a 0..2 (overlay field21_0x3c, FX_IRON_STRAIN/DUMP/LDUMP/BOIL,
         * starts when state == 4 and lets state 4 advance; sets byte field208_0x292 to 0x0c..0x18 from the frame)
         * and field119_0x11e 0..1 (overlay field23_0x44, FX_IRON_POUR, starts when field117 == 2; on completion
         * adds 1 RT_IRON to the mine's own resources, cap 8). Also an iron-pile overlay from resources[RT_IRON] and
         * the multiplayer owner flag.
         */
        void __cdecl UpdateIronMine();

        /**
         * Per-tick update of the current stone quarry: increments the owner's countStoneQuarries, registers it,
         * then (every 2nd tick in single-player, every tick otherwise) drives four animation layers: puller
         * (workers[1]; state/campgroundVclock/field20_0x38, states 0..6 advancing when the pryer reaches 7/9 and
         * the mason is idle), block/rope (field117_0x11a/field25_0x4c/field21_0x3c, same 0..6 sequence, not worker-
         * gated), pryer (workers[0]; killingPitField 0..11 /field26_0x50/field22_0x40) and mason (workers[2];
         * field119_0x11e/field27_0x54/field23_0x44, starts when field117 == 6). Worker-gated layers show idle
         * frames when fewer than 3 workers are present. Each completed mason cycle adds 1 RT_STONE (cap 48) to the
         * linked quarry pile (quarryStockpileID); the pryer leaves its last state 11 for a random 0..2 only while
         * that pile holds < 47 stone. Finally animates the multiplayer owner flag.
         */
        void __cdecl UpdateQuarry();

        /**
         * Per-tick update of a fire-ballista siege tent: in single-player marks it BLS_REMOVE if its attack wave
         * has no tribes left; on the first tick picks the tent sprite variant (1 for human owners, else 2/3 by lord
         * type) and refreshes graphics. Adds currentEmployeeCount to buildingProgress; once > 320 it spawns
         * UT_S_FBALLISTA at the tent (undoing this tick's progress on failure). With exactly 2 engineers both are
         * put straight into the aim state and their IDs/UIDs copied into the unit's manningEngineer arrays;
         * otherwise each engineer is sent to man it (UIT_MAN_SIEGE_EQUIPMENT) and the copied crew count is 0. Faces
         * scenario attackers (neither human nor AI) toward the local player's campground, adds the unit to a new
         * tribe of the attack wave, updates the open building menu and destroys the tent without rubble.
         */
        void __cdecl UpdateFireBallistaBuilding();

        /**
         * Per-tick update of a killing pit trap: destroys itself (no rubble) if the BuildingLayer tile no longer
         * points at it. State 0 = hidden/armed (sprite variant 9..16, on first tick refreshes graphics and sets
         * killingPitField=1); 1 = trigger animation from table field418_0xa5a4, then state 2; 2 = spent,
         * field117_0x11a counts up and at 2000 the pit is destroyed; -1 starts a reset animation (state -2, table
         * field417_0xa53c) that returns to state 0. The sprite/frame variant comes from fireRelatedRNG1 & 7.
         */
        void __cdecl UpdateKillingPit();

        /**
         * Per-tick update of a tower using building size index 4 (Tower2): registers it, resets overlay/decal
         * fields, sets someX/someY = x+1,y+1; every 40 ticks (buildingProgress) recomputes entrance flags; shows
         * door overlays when exit (field21 = 0x51) or entrance (field23 = 0x5a) flags are set. Damage stage = 9 -
         * 9*health/maxHealth (capped at 8) fills that many damage-decal slots (field33_0x6c..overlayFrame15) pseudo-
         * randomly from fireRelatedRNG1. If DAT_BuildingsState.towerTilesRefreshPending is set, clears MiscDisplayLayer bit
         * 0x10 on all its tiles and sets it on the tiles listed for the current orientation in table
         * field419_0xa73c.
         */
        void __cdecl UpdateTower2();

        /**
         * Per-tick update of a tower using building size index 5 (Tower3): same as UpdateTower2 but someX/someY =
         * x+2,y+2, field20_0x38 = 4 and the highlighted-tile table is field420_0xa77c (6 entries per orientation).
         * Recomputes entrance flags every 40 ticks, door overlays, and up to 8 damage decals from the health ratio.
         */
        void __cdecl UpdateTower3();

        /**
         * Per-tick update of a tower using building size index 6 (Tower4): like UpdateTower2/3 (field20 = 2,
         * entrance flags, door overlays, 8 damage decals, MiscDisplayLayer bit 0x10 from table field421_0xa7dc, 8
         * entries per orientation) and sets the roof frame shouldRenderRoof = 0x7a. While field261_0x2fa > 0 it
         * counts down; on reaching 0 it scans the tower's tiles in UnitLayer, stores hasUnitsOntop and restarts at
         * 100. When hasUnitsOntop is set, the roof is hidden (shouldRenderRoof = 0) and overlay frame 0x7b is shown
         * instead.
         */
        void __cdecl UpdateTower4();

        /**
         * Per-tick update of a tower using building size index 6 (Tower5): like UpdateTower4 without the roof /
         * units-on-top logic - field20_0x38 = 3, someX/someY = x+2,y+2; recomputes entrance flags every 40 ticks,
         * sets door overlays (exit 0x51 / entrance 0x5a), fills up to 8 damage-decal slots
         * (field33_0x6c..overlayFrame15) from the health ratio and fireRelatedRNG1, and marks MiscDisplayLayer bit
         * 0x10 on the tiles listed in field421_0xa7dc when DAT_BuildingsState.towerTilesRefreshPending is set.
         */
        void __cdecl UpdateTower5();

        /**
         * Per-tick update of a catapult siege tent (building type 80): marks it BLS_REMOVE in single-player when
         * its attack wave has no tribes left, initialises the tent sprite on the first tick, adds
         * currentEmployeeCount to buildingProgress and once > 320 spawns UT_S_CATAPULT (undoing this tick's
         * progress on failure). With exactly 2 engineers both go straight to aiming and are copied into the unit's
         * manningEngineer arrays; otherwise each is sent to man it (UIT_MAN_SIEGE_EQUIPMENT) and the stored crew
         * count becomes 0. Sets facing, adds the unit to a new tribe of the attack wave (type 0x16), sets
         * siegeTargetPlayerID in skirmish, updates the open building menu and destroys the tent without rubble.
         * Unlike the ballista/trebuchet tents it does not call generateSiegeCreationInformation.
         */
        void __cdecl UpdateCatapultBuilding();

        /**
         * Per-tick update of a trebuchet siege tent (building type 81): same flow as the catapult tent but needs
         * progress > 640, spawns UT_S_TREBUCHET, calls generateSiegeCreationInformation and uses tribe type 0x17.
         * With exactly 3 engineers they start aiming; otherwise each engineer is teleported to a rally point near
         * the tent (tent x/y plus a (dx,dy) pair from DAT_AttackInfoDefinedData.unitScatterOffsetsXY starting at a random
         * index 0..15, resolved by computeNextRallyPointDestination; tile/x/y/height set directly) and assigned to
         * man the trebuchet, and the stored crew count becomes 0. Then copies engineers into the unit, updates the
         * menu and destroys the tent without rubble.
         */
        void __cdecl UpdateTrebutchetBuilding();

        /**
         * Per-tick update of a siege-tower tent (dispatched for building type 82): marks it BLS_REMOVE in single-
         * player when its attack wave has no tribes left, initialises the sprite on the first tick; progress
         * (+currentEmployeeCount per tick) > 1280 spawns UT_S_TOWER. With exactly 4 engineers they start operating
         * immediately; otherwise each engineer is teleported to a rally point offset (field10_0xec table) near the
         * tent and sent to man it, and the stored crew count becomes 0. Sets facing, adds the unit to a new tribe
         * of the attack wave (type 0x14), copies engineer IDs/UIDs into the unit, updates the open building menu
         * and destroys the tent without rubble.
         */
        void __cdecl UpdateSiegeTowerBuilding();

        /**
         * Per-tick update of a battering-ram tent (dispatched for building type 83): marks it BLS_REMOVE in single-
         * player when its attack wave has no tribes left, initialises the sprite on the first tick; progress
         * (+currentEmployeeCount per tick) > 640 spawns UT_S_BATTERINGRAM. With exactly 4 engineers they start
         * operating immediately; otherwise each is teleported to a rally point offset near the tent and sent to man
         * it, and the stored crew count becomes 0. Sets facing, adds the unit to a new tribe of the attack wave
         * (type 0x13), copies engineer IDs/UIDs into the unit, updates the open building menu and destroys the tent
         * without rubble.
         */
        void __cdecl UpdateBatteringRamBuilding();

        /**
         * Per-tick update of a portable-shield (mantlet) tent (building type 84): marks it BLS_REMOVE in single-
         * player when its attack wave has no tribes left, initialises the sprite on the first tick; progress
         * (+currentEmployeeCount per tick) > 120 spawns UT_S_SHIELD. With exactly 1 engineer he starts operating
         * immediately; otherwise each is teleported to a rally point offset near the tent and sent to man it, and
         * the stored crew count becomes 0. Sets facing, adds the unit to a new tribe of the attack wave (type
         * 0x15), copies engineer IDs/UIDs into the unit, updates the open building menu and destroys the tent
         * without rubble.
         */
        void __cdecl UpdateShieldBuilding();

        /**
         * Per-tick update of a dog cage: registers it and increments the owner's dogCageCount. Counts the up-to-4
         * dogs still validly linked (insideUnitID/UID pairs match) and how many of them are in state 0xd2 (waiting
         * in the cage). No linked dogs -> destroy the cage without rubble; none waiting -> static sprite; otherwise
         * animates the cage from frame table field166_0x794c and bumps the signpost counter.
         */
        void __cdecl UpdateDogCage();

        /**
         * Per-tick update of a hunter's post: registers it as AI-targetable and in the building registry. If the
         * unit in worker slot 1 is a burning man/animal, arms a 400-tick cooldown (field185_0x264, decremented each
         * tick). When worker slot 0 is valid, numberOfAnimals == 0 and the cooldown is 0, spawns a UT_HUNTERDOG at
         * the building entry and binds it as worker slot 1. While the hunter is inside (renderAnimation) it steps
         * an 8-state animation cycle in `state`: state 0 (frames field51_0x4b50, field66_0xbe fades from 0x20),
         * states 1..6 butchering (frames field52_0x4b68, FX_HUNTER_CUT at frame 4; each finished state adds 1
         * RT_MEAT via addResourceToStockpile), state 7 (frames field53_0x4b90, field66_0xbe grows to 0x20) which on
         * completion increments field13_0x28, sets field14_0x2c = 1 and returns to state 0. Finally picks the meat-
         * display sprite field20_0x38 = 0x13 + meat (meat 1..6, else 0) and animates the owner flag unless in
         * GM_SOLITARY mode.
         */
        void __cdecl UpdateHuntersPost();

        /**
         * Per-tick update of a large gatehouse: runs updateGateDrawBridgeOpenCloseLogic, sets someX/someY =
         * x+4,y+2, derives the facing variant (buildingVariation, +1 for map orientations 2/6, clamped) and sets
         * static sub-sprites accordingly; scatters up to 4 damage decals (count 5 - 5*health/maxHealth, max 4)
         * using fireRelatedRNG1. Gate phase (pathLinkageRelated2): 0 open -> on gateState 10 phase 1 closing
         * (FX_PC_DROP/FX_PC_SLAM, frames field142_0x6b44) -> 2 closed (path linkage updated) -> on gateState 11
         * phase 3 opening (FX_PC_LIFT, frames field141_0x6b28) -> 0 open (path linkage updated). The door frame
         * goes to field29_0x5c (+6) for facing 0x50, else to shouldRenderRoof.
         */
        void __cdecl UpdateGateHouseLarge();

        /**
         * Per-tick update of a small gatehouse: same as UpdateGateHouseLarge except someX = x+3 and only the
         * field22_0x40/field23_0x44 sub-sprites are set (0xb / 0xc by facing); damage decals from health and the
         * same open/close phase machine with drop/slam/lift SFX and path-linkage updates when fully closed or
         * opened.
         */
        void __cdecl UpdateGateHouseSmall();

        /**
         * Per-tick update of a wooden gate: runs updateGateDrawBridgeOpenCloseLogic and sets static sub-sprites by
         * facing; no animation: phase 0 (open) + gateState 10 -> phase 2 (closed), phase 2 + gateState 11 -> phase
         * 0, updating path linkage on each switch. While in phase 2 (including the tick it reopens) it renders the
         * door frame (field29_0x5c = 6 for facing 0x50, else shouldRenderRoof = 8).
         */
        void __cdecl UpdateWoodGate1();

    } // namespace Buildings
} // namespace Map
} // namespace OpenSHC
