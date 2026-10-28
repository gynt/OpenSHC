/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Entities.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Entities {

        /**
         * Per-tick update of an arrow entity (DAT_CurrentEntityID): graphicType2 = field45_0x6a*16 + field12_0x1c +
         * graphicType2RelatedOffset; if someCounter_OR_hitGround is non-zero it is decremented (forced to 0 when
         * rng_2 is set) and at <= 0 the entity is removed (logicalState 7); orientation 0x4C is reset to 0x3C and
         * also removes it.
         */
        void __cdecl UpdateArrowEntity();

        /**
         * Per-tick update of a catapult projectile entity: while someCounter_OR_hitGround is 0 the frame index
         * wraps to 0 above 7 and graphicType2 = base offset + frame; otherwise the counter is decremented, the
         * entity removed (logicalState 7) at <= 0 and the base sprite shown. Orientation 0x4C is reset to 0x3C and
         * also removes it.
         */
        void __cdecl UpdateCatapultProjectileEntity();

        /**
         * Per-tick update of a pebble (slinger) projectile entity: fixed sprite (base offset); counts down a non-
         * zero someCounter_OR_hitGround and removes the entity (logicalState 7) at <= 0; orientation 0x4C is reset
         * to 0x3C and also removes it.
         */
        void __cdecl UpdatePebbleEntity();

        /**
         * Per-tick update of a fire-thrower secondary effect entity: shows base offset + animation frame until the
         * frame reaches unkThree_1, then sets logicalState 3 (finished); sets unkMinusOne = 0x10 when gmLookupValue
         * is 1.
         */
        void __cdecl UpdateFirethrowSecondaryEntity();

        /**
         * Per-tick update of an arrows secondary effect entity: finishes (logicalState 3) when the animation frame
         * reaches unkThree_1, otherwise sets unkMinusOne = frame*32/unkThree_1 (progress 0..31).
         */
        void __cdecl UpdateArrowsSecondaryEntity();

        /**
         * Per-tick update of a crossbow bolt entity: same as UpdateArrowEntity without the rng_2 shortcut
         * (graphicType2 from field45_0x6a*16 + field12_0x1c + base offset, counter countdown to removal,
         * orientation 0x4C removal).
         */
        void __cdecl UpdateCrossbowArrowEntity();

        /**
         * Per-tick update for entity types 20/37 (directional projectile). Sets graphicType2 = ((field12_0x1c+8)
         * mod 16) + field45_0x6a*16 + graphicType2RelatedOffset (16-direction sprite), counts down
         * someCounter_OR_hitGround and sets logicalState 7 when it reaches 0, and also switches to state 7 when
         * orientation hits 0x4c (resetting it to 0x3c).
         */
        void __cdecl UpdateEntity_20_37();

        /**
         * Per-tick update for entity type 21: a fading effect whose lifetime is unknownAnimationFrameRelated.
         * unitID==2 selects the 200-tick variant, otherwise the 400-tick variant; computes unkMinusOne (0..0x1f
         * fade level) and graphicType2 frame from elapsed ticks, and sets logicalState 3 (remove) when the lifetime
         * is exceeded.
         */
        void __cdecl UpdateEntity_21();

        /**
         * Per-tick update of a poison/disease cloud entity. rng_2 is a lifetime counter (after 800 ticks the cloud
         * jumps to its fade-out frames 0x3f8..0x400), frames 0..7 fade in, then loops 8 frames offset by rng_1; at
         * 0x400 sets logicalState 3. imageID = graphicType2+0x10. If linked to another entity
         * (unknownDistanceRelatedValue, validated via uidRef==uid), drops the link when that entity is more than 6
         * tiles away.
         */
        void __cdecl UpdateEntity_PoisonCloud();

        /**
         * Per-tick update of a catapulted cow in flight. While someCounter_OR_hitGround == 0 it loops a 12-frame
         * flying animation (imageID = frame+0x11); once nonzero it plays landing frames (anim tick clamped
         * 100..0x77), counts the counter down and sets logicalState 7 at 0. Orientation 0x4c also ends the flight
         * (state 7).
         */
        void __cdecl UpdateEntity_CowFlying();

        /**
         * Per-tick update of effect entity type 26: 0x48-tick animation whose fade level (unkMinusOne) goes 20->0,
         * stays 0, then rises to 0x1f; graphicType2 = tick+1, imageID = frame+0x50; sets logicalState 3 when the
         * animation ends. Stores fade as -1-level.
         */
        void __cdecl UpdateEntity_26();

        /**
         * Per-tick update of entity type 27: random frame (rng_1&7)+1 within one of 3 sprite sets
         * (unitID_OR_seaGullID % 3); rng_2 counts ticks and after 10 sets logicalState 8; sets logicalState 3 if
         * someCounter_OR_hitGround is nonzero.
         */
        void __cdecl UpdateEntity_27();

        /**
         * Per-tick update of entity type 28: loops a 12-frame animation per direction (field12_0x1c*12 + tick + 1)
         * and writes it to graphicType2 and imageID.
         */
        void __cdecl UpdateEntity_28();

        /**
         * Per-tick update of entity type 29 (animated ambient creature). If targetZ == 0 shows a static per-
         * direction frame (0x91+dir, image 0xa1+dir). Otherwise loops an 8-frame per-direction animation; rng_2
         * alternates between a positive active countdown (170..369 ticks) and a negative idle countdown (-10..-59
         * ticks, during which the frame is held at 3), re-seeded from SEC_RNG. Returns a junk value.
         */
        uint __cdecl UpdateEntity_29();

        /**
         * Per-tick update of entity type 30. While unitID (used as a delay counter) is nonzero it increments it and
         * keeps frame 0 with someCounter_OR_hitGround=1; once it is 0, plays an 8-frame animation (graphicType2
         * tick+1, imageID tick+9) and sets logicalState 3 at the end.
         */
        void __cdecl UpdateEntity_30();

        /**
         * Per-tick update of entity type 31 with two variants by unitID_OR_seaGullID: variant 0 plays 16 frames
         * with fade level tick*2, variant 1 plays 8 frames (offset 0x11) with fade tick*3; sets logicalState 3 when
         * the animation ends.
         */
        void __cdecl UpdateEntity_31();

        /**
         * Per-tick update of entity type 32: random frame (rng_1&7)+offset, fade level 0, sets logicalState 3 once
         * someCounter_OR_hitGround becomes nonzero.
         */
        void __cdecl UpdateEntity_32();

        /**
         * Per-tick update of popup entity type 40 (owner icon, gm 0x2e frame 0xab; see playerHasEntityOfType). Sets
         * fadeLevel = popupFadeLevels[animFrameCounter]-1 (graphicType2 = 1); when the table entry is <1 sets
         * logicalState 3 and the owner's popupEntity40Cooldown = 0x46. Writes popup icon gm/frame and icon/number
         * offsets, popupIconOffsetX shrinking and popupNumberOffsetX growing after tick 16.
         */
        void __cdecl UpdateEntity_40();

        /**
         * Per-tick update of popup entity type 41 (same as type 40; playerHasEntityOfType(0x29) in
         * displayPopularityAndGoldPopups checks for it). fadeLevel = popupFadeLevels[animFrameCounter]-1; when the
         * table ends sets logicalState 3 and the owner's popupEntity41Cooldown = 0x46. popupIconFrame chosen by
         * displayValue (<40 -> 0x82, 40..59 -> 0x81, >=60 -> 0x80), gm 0x2e; icon/number offsets animate after tick
         * 16.
         */
        void __cdecl UpdateEntity_41();

        /**
         * Per-tick update of popup entity types 42/43: fade level from the field60_0x107c table (logicalState 3
         * when it ends), overlay gm 0x2e with the frame already in field83_0xc0, layout fields 0xc8..0xce;
         * field87_0xca = 0x2d - spriteHeight/2 using PTR_ARRAY_GmRunCopyJumpTable for that gm/frame (vertical
         * centring).
         */
        void __cdecl UpdateEntity_42_43();

        /**
         * Per-tick update of flag entities (types 1,2,4). Frame table chosen by someTracker (0..3 = flag wave
         * strength) indexed by animation tick; at the end of the cycle switches someTracker to the next state,
         * taken from wind (DAT_LandscapeState.wind) or, for AI players in non-solitary games, from the AI mood
         * (destroy/nervous -> 3, defensive -> 0, raiding -> 1, else 2). State 3 also sets unkOne_1 = 1.
         */
        void __cdecl UpdateFlag_1_2_4_Entity();

        /**
         * Per-tick update of flag entity type 3. Latches wind value into rng_2 when the wind countdown passes this
         * entity's row, picks a frame table by someTracker (0 or 1/2) and at end of cycle resets the tick and
         * adopts the latched wind state.
         */
        void __cdecl UpdateFlag3Entity();

        /**
         * Per-tick update of a brazier entity: graphicType2 = offset + (animation tick & 7), an 8-frame flame loop.
         */
        void __cdecl UpdateBrazierEntity();

        /**
         * Fire spread step used by incendiary projectiles (UpdateEntityType8): picks a random micro-offset from
         * XYOffsetsInAllDirections, converts to tile, rejects off-map/invalid tiles and LogicLayer mask 0x10300131.
         * A building (except tunnel/killing pit/BT_TUNNEL_CONSTRUCTION) is lit via lightUpBuilding and no fire entity is
         * spawned; else an existing fire is refreshed (fireLevel raised, animState/animFrameCounter reset) or a new
         * ET_FIRE entity is spawned (plus a 0x1a entity for level>2 on 1/4 of tiles), lighting trees. Returns the
         * new fire entity id or 0.
         */
        uint __cdecl SomeFireSpreadFunction(int playerID, int x, int y, int height, int fireLevel);

        /**
         * Ignites fire near a micro-tile: random micro-offset from XYOffsetsInAllDirections, off-map/LogicLayer-
         * mask 0x10300131 check, gatehouses/towers are immune. If no fire exists on the tile, lights the building
         * there (lightUpBuilding with fireIntensity passed as its spareGrounds flag) and a tree (LogicLayer
         * 0x1000), spawns ET_FIRE (and a 0x1a smoke-like entity for level>2 on 1/4 of tiles) with fireLevel = param
         * 'two' (really the fire level) and fireIntensity; otherwise refreshes the existing fire
         * (animState/animFrameCounter = 0, fireLevel raised). Returns the new fire entity id or 0.
         */
        uint __cdecl IgniteFireAtMiniTile(
            int playerID, int miniTileX, int miniTileY, int tileHeightMin8, int two, int fireIntensity);

        /**
         * Fire spread step used by fire throwers and SetPlaceOnFire: random micro-offset, refreshes an existing
         * fire on the tile, otherwise spawns ET_FIRE only if the tile passes LogicLayer mask 0x1a7001b1 and
         * lightUpBuilding (fireIntensity passed as spareGrounds) / lightUpTree (when present) succeed; sets
         * fireLevel and fireIntensity and may add a 0x1a entity for level>2 on 1/4 of tiles.
         */
        void __cdecl AFireSpreadFunction(int playerID, int x, int y, int height, int fireLevel, int fireIntensity);

        /**
         * Per-tick update of a fire entity (gmID 0x76/0x90). fadeLevel from fireLevel (5..1 -> 8,9,12,14,16).
         * animState phase: <0 = delay (fade 0x20, counts up), 0 = start, 1 = burning, 2 = dying; frame tables
         * chosen by phase, level (<3 -> small tables) and rng_1 bit 7. At the end of each animation cycle: phase 0
         * -> 1; phase 1 adds 2 to someCounter_OR_hitGround and goes to phase 2 once it exceeds 8, unless the
         * building under it is flammable (then phase 2 if its fireDuration is 0, else fireLevel raised to >=3 and
         * counter reset); phase 2 -> logicalState 3. The 'counter == 6 -> level capped at 2' check sits between the
         * two +1 increments, so it never fires while the counter is even. In phase 0 at tick 1 (level >= 2) it
         * tries to spread to neighbour fireSpreadDirIndex (0:x-1, 1:x+1, 2:y+1, 3:y-1) via IgniteFireAtMiniTile
         * with level-1 if |height difference| <= 24, then increments fireSpreadDirIndex. Finally damages units on
         * its tile (processFireDamageToUnitsAtTile) unless LogicLayer mask 0xba7001b1.
         */
        void __cdecl UpdateFireEntity();

        /**
         * Per-tick update of a fire-thrower flame projectile: when someCounter_OR_hitGround is set it calls
         * AFireSpreadFunction(owner, microX, microY, tile height, level 2, intensity 1) and sets logicalState 7;
         * orientation 0x4c also ends it.
         */
        void __cdecl UpdateFirethrowEntity();

        /**
         * Per-tick update of a heads-on-spikes decoration: frame rng_1+1; rng_2 is a countdown which, on reaching
         * 0, is reset to 300..799 and spawns entity type 0x1c (probably a crow/fly) above the spikes flying towards
         * a random point within +-50 tiles.
         */
        void __cdecl UpdateHeadsOnSpikesEntity();

        /**
         * Per-tick update of entity type 8 (incendiary projectile): frame 8..16 by travelledDistance (+16 on 1/4 of
         * rng_1). On ground hit sets logicalState 3, calls SomeFireSpreadFunction with fire level 5 at tile
         * height+8 and plays FX_FIRE_START; orientation 0x4c also ends it.
         */
        void __cdecl UpdateEntityType8();

        /**
         * Wrapper: IgniteFireAtMiniTile(playerID, x, y, height, level, intensity 0). Returns the spawned fire
         * entity id or 0.
         */
        uint __cdecl IgniteFireAtMiniTile_Convenience(
            int playerID, int miniTileX, int miniTileY, int tileHeightMin8, int two);

        /**
         * Wrapper: AFireSpreadFunction(playerID, x, y, height, level, intensity 0).
         */
        void __cdecl SetPlaceOnFire(int playerID, int x, int y, int height, int fireLevel);

    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
