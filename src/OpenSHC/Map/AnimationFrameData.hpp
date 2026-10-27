/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/AnimationFrameData.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {

#pragma pack(push, 1)
    // SIZE: 0x000083D4
    typedef struct AnimationFrameData {

        byte ANIM_Frames_Shared_UnitClimbingUp[20]; // 0x00000000 length: 20
        // US_DEATH_02 fall death (speed 1; terrainOrClimbHeight lowered to ground level from frame 4, gfx by
        // opposite facing) shared by crusader archer, spearman and maceman; exe data 1..8 then hold 8 (128 entries)
        byte animDeath02FallShared[276]; // 0x00000014 length: 276
        byte drunkard[1172]; // 0x00000128 length: 1172
        byte useWeapon[124]; // 0x000005BC length: 124
        byte ANIM_Frames_UnitDeath[52]; // 0x00000638 length: 52
        // US_DEATH_03 and US_STONE_DEATH_03 frames (speed 1) of spearman and engineer; exe data 1..24 each doubled,
        // then hold
        byte animDeath3SpearmanEngineer[104]; // 0x0000066C length: 104
        // death frames (US_DEATH_01, US_DEATH_03 and the generic citizen death states) of pole turner and armourer,
        // speed 2
        byte animDeathWorkerPoleArmorer[144]; // 0x000006D4 length: 144
        // slave US_DEATH_01 frames (exe data 1..13 then hold)
        byte animDeathSlave[96]; // 0x00000764 length: 96
        // slave US_STONE_DEATH_03 frames (exe data 1..15 then hold)
        byte animStoneDeathSlave[96]; // 0x000007C4 length: 96
        // slave US_DEATH_03 and slinger US_STONE_DEATH_03 frames (exe data 1..16 then hold)
        byte animDeath3SlaveSlinger[104]; // 0x00000824 length: 104
        // camel death frames for the non-DEATH_01 death states (FX_HORSE_FALL at frame 17, FX_CAMEL_DIE at cycle 2)
        // and fire thrower US_STONE_DEATH_03 frames (exe data 1..20 then hold)
        byte animDeathCamelFireThrower[88]; // 0x0000088C length: 88
        // assassin US_STONE_DEATH_03 frames (exe data 1..22 then hold)
        byte animStoneDeathAssassin[88]; // 0x000008E4 length: 88
        // assassin US_DEATH_01 and US_DEATH_03 frames (exe data 1..24 then hold)
        byte animDeathAssassin[96]; // 0x0000093C length: 96
        // camel US_DEATH_01 frames (FX_CAMEL_DIE) and arabian swordsman US_STONE_DEATH_03 frames (exe data 1..25
        // then hold)
        byte animDeathCamelArabSword[96]; // 0x0000099C length: 96
        // arabian swordsman US_DEATH_03 and horse archer US_DEATH_01 frames (exe data 1..26 then hold)
        byte animDeathArabSwordHorseArcher[96]; // 0x000009FC length: 96
        // [146 0x00575C40] Used as the US_DEATH_01 frame table for the Arabian swordsman, not worker-specific.
        byte ANIM_UnitDeath1[104]; // 0x00000A5C length: 104
        // pitchman US_DEATH_01 and generic death-state frames (exe data 1..16 then hold)
        byte animDeathPitchman[104]; // 0x00000AC4 length: 104
        // burning man death animation played in death states 111..116 before US_DISAPPEAR (exe data 1..23 then
        // hold)
        byte animBurningManDeath[88]; // 0x00000B2C length: 88
        // lord killed animation (UpdateLord after the kill bookkeeping; at cycle 0x10 plays 'the lord has been
        // killed' speech); exe data 1..28 then hold
        byte animLordDeath[112]; // 0x00000B84 length: 112
        // crusader archer US_RELOAD_WEAPONUnk (state 4) frames, then US_AIM_WEAPONUnk
        byte animArcherReload[40]; // 0x00000BF4 length: 40
        // crusader archer aim frames for aim pitch jugglerCount == 0 (level target, gfx base 0x139); single frame
        byte animArcherAimLevel[24]; // 0x00000C1C length: 24
        // crusader archer aim frames for jugglerCount == 1 (shooter > 70 above target, gfx base 0x1B9)
        byte animArcherAimDown[32]; // 0x00000C34 length: 32
        // crusader archer aim frames for jugglerCount == -1 (target > 70 above shooter or tile target, gfx base
        // 0x219)
        byte animArcherAimUp[32]; // 0x00000C54 length: 32
        // crusader archer US_FIRE_WEAPONUnk frames, shared by all three aim pitches (different gfx bases)
        byte animArcherFire[44]; // 0x00000C74 length: 44
        // crusader archer standing idle in state US_STAND_UPUnk while not seated, used for odd unit slots (gfx
        // 0x2B0 + frame)
        byte animArcherStandIdleOdd[64]; // 0x00000CA0 length: 64
        // crusader archer standing idle in state US_STAND_UPUnk while not seated, used for even unit slots
        byte animArcherStandIdleEven[56]; // 0x00000CE0 length: 56
        // crusader archer sit-down transition (US_SIT_DOWNUnk substate 0x65 -> seated 0x6A); exe data 1..11
        byte animArcherSitDown[40]; // 0x00000D18 length: 40
        // crusader archer seated idle loop (substate 0x6A, alternates with 0x6B); exe data frames 12..15
        byte animArcherSeatedIdleA[60]; // 0x00000D40 length: 60
        // crusader archer seated idle hold (substate 0x6B, back to 0x6A); exe data frame 12 repeated 192 times
        byte animArcherSeatedIdleB[216]; // 0x00000D7C length: 216
        byte ANIM_Archer_CrusaderAndArabian1[32]; // 0x00000E54 length: 32
        // crusader archer US_LOOK_AROUNDUnk idle frames (AI-owned, far from enemies)
        byte animArcherLookAround[272]; // 0x00000E74 length: 272
        // crusader archer melee frames for substates 0 and 2, also US_MELEE_ATTACK_WALL
        byte animArcherMeleeA[68]; // 0x00000F84 length: 68
        // crusader archer melee frames for substate 1
        byte animArcherMeleeB[28]; // 0x00000FC8 length: 28
        // pikeman standing idle for odd fixedRng: state 1 standing substate and state 2 (alert idle)
        byte animPikemanStandIdleOdd[48]; // 0x00000FE4 length: 48
        // pikeman standing idle for even fixedRng: state 1 standing substate and state 2 (alert idle)
        byte animPikemanStandIdleEven[104]; // 0x00001014 length: 104
        // pikeman state 3 guard idle (AI, facing signpost 0) for odd fixedRng
        byte animPikemanGuardIdleOdd[36]; // 0x0000107C length: 36
        // pikeman state 3 guard idle (AI, facing signpost 0) for even fixedRng
        byte animPikemanGuardIdleEven[40]; // 0x000010A0 length: 40
        // pikeman sit-down transition (state 1 substate 0x65 -> seated 0x6A); exe data 1..12
        byte animPikemanSitDown[44]; // 0x000010C8 length: 44
        // pikeman seated idle loop (substate 0x6A, alternates with 0x6B); exe data frames 13..15
        byte animPikemanSeatedIdleA[88]; // 0x000010F4 length: 88
        // pikeman seated idle loop (substate 0x6B); exe data frames 15..18
        byte animPikemanSeatedIdleB[100]; // 0x0000114C length: 100
        // pikeman stand-up transition (substate 100 -> standing 0x66); exe data 12..1 (sit-down reversed)
        byte animPikemanStandUp[36]; // 0x000011B0 length: 36
        // pikeman melee frames for substate 1
        byte animPikemanMeleeB[36]; // 0x000011D4 length: 36
        // pikeman melee frames for substates 0 and 2, also US_MELEE_ATTACK_WALL
        byte animPikemanMeleeA[28]; // 0x000011F8 length: 28
        // pikeman melee frames for substate 3
        byte animPikemanMeleeC[36]; // 0x00001214 length: 36
        // pikeman moat digging, state 124 (alias 4, decompiled US_RELOAD_WEAPONUnk /
        // US_DEATH_02|US_STAND_UPUnk|US_RELOAD_WEAPONUnk): FX_MOAT_DIG, advanceMoatDigProgress; exe data 1..15
        byte animPikemanDigMoat[36]; // 0x00001238 length: 36
        // pikeman moat filling, state 125 (alias 5, decompiled US_FILL_MOAT / US_AIM_WEAPONUnk): removeMoat; exe data
        // 15..1 (dig reversed)
        // pikeman moat filling, state 125 (alias 5, decompiled US_DIG / US_AIM_WEAPONUnk): removeMoat; exe data
        // 15..1 (dig reversed)
        byte animPikemanFillMoat[36]; // 0x0000125C length: 36
        // maceman state 2 (alert idle, enemy within 400) for odd fixedRng
        byte animMacemanAlertIdleOdd[36]; // 0x00001280 length: 36
        // maceman state 2 (alert idle) for even fixedRng
        byte animMacemanAlertIdleEven[96]; // 0x000012A4 length: 96
        // maceman state 1 (US_IDLEUnk) idle frames
        byte animMacemanIdle[40]; // 0x00001304 length: 40
        // maceman state 3 guard idle (AI, facing signpost 0); both fixedRng branches use this table
        byte animMacemanGuardIdle[92]; // 0x0000132C length: 92
        // maceman melee frames for substates 0 and 2 (gfx 0x209), also US_MELEE_ATTACK_WALL
        byte animMacemanMeleeA[36]; // 0x00001388 length: 36
        // maceman melee frames for substate 1 (gfx 0x269)
        byte animMacemanMeleeB[36]; // 0x000013AC length: 36
        // maceman melee frames for substate 3 (gfx 0x2C9)
        byte animMacemanMeleeC[32]; // 0x000013D0 length: 32
        // crossbowman state 2 (alert idle) for odd fixedRng
        byte animCrossbowAlertIdleOdd[52]; // 0x000013F0 length: 52
        // crossbowman state 2 (alert idle) for even fixedRng
        byte animCrossbowAlertIdleEven[48]; // 0x00001424 length: 48
        // crossbowman state 1 (US_IDLEUnk) idle for odd fixedRng
        byte animCrossbowIdleOdd[80]; // 0x00001454 length: 80
        // crossbowman state 1 (US_IDLEUnk) idle for even fixedRng
        byte animCrossbowIdleEven[104]; // 0x000014A4 length: 104
        // crossbowman melee frames for odd fixedRng (exe data 1..8)
        byte animCrossbowMeleeOdd[32]; // 0x0000150C length: 32
        // crossbowman melee frames for even fixedRng (exe data 9..16), also US_MELEE_ATTACK_WALL
        byte animCrossbowMeleeEven[32]; // 0x0000152C length: 32
        // crossbowman US_RELOAD_WEAPONUnk (state 4) frames, FX_XBOW_WIND
        byte animCrossbowReload[68]; // 0x0000154C length: 68
        // crossbowman aim frames for aim pitch jugglerCount == 0 (gfx base 0xE1)
        byte animCrossbowAimLevel[28]; // 0x00001590 length: 28
        // crossbowman aim frames for jugglerCount == 1 (shooter above target); exe data 1,2,3,15,16,17
        byte animCrossbowAimDown[28]; // 0x000015AC length: 28
        // crossbowman aim frames for jugglerCount == -1 (target above shooter); exe data 1,2,3,8,9,10
        byte animCrossbowAimUp[28]; // 0x000015C8 length: 28
        // crossbowman US_FIRE_WEAPONUnk frames for jugglerCount == 0 (bolt released at cycle 2)
        byte animCrossbowFireLevel[48]; // 0x000015E4 length: 48
        // crossbowman fire frames for jugglerCount == 1 (exe data 18..21)
        byte animCrossbowFireDown[44]; // 0x00001614 length: 44
        // crossbowman fire frames for jugglerCount == -1 (exe data 11..14)
        byte animCrossbowFireUp[44]; // 0x00001640 length: 44
        // monk state 2 (alert idle) for odd fixedRng
        byte animMonkAlertIdleOdd[56]; // 0x0000166C length: 56
        // monk state 2 (alert idle) for even fixedRng
        byte animMonkAlertIdleEven[40]; // 0x000016A4 length: 40
        // monk state 1 (US_IDLEUnk) idle for odd fixedRng
        byte animMonkIdleOdd[56]; // 0x000016CC length: 56
        // monk state 1 (US_IDLEUnk) idle for even fixedRng
        byte animMonkIdleEven[40]; // 0x00001704 length: 40
        // monk melee frames: substates 0/2 for even fixedRng, all substates except 1 for odd, also
        // US_MELEE_ATTACK_WALL
        byte animMonkMeleeA[28]; // 0x0000172C length: 28
        // monk melee frames for substate 1
        byte animMonkMeleeB[32]; // 0x00001748 length: 32
        // monk melee frames for substate 3 (even fixedRng only)
        byte animMonkMeleeC[28]; // 0x00001768 length: 28
        // catapult state 2 'preparing to shoot' (FX_CA_LOAD) machine frames (gfxNumber), then state 4; exe data
        // 1..13
        byte animCatapultLoad[40]; // 0x00001784 length: 40
        // catapult loading: second sprite (imageIDUnk, crew) frames parallel to animCatapultLoad; exe data 29..41
        byte animCatapultLoadOverlay[40]; // 0x000017AC length: 40
        // catapult state 4 (decompiled US_RELOAD_WEAPONUnk) firing machine frames: FX_CA_FIRE at cycle 2,
        // projectile/cow released when the frame is 0x17; exe data 14..28
        byte animCatapultFire[40]; // 0x000017D4 length: 40
        // catapult firing: second sprite (imageIDUnk, crew) frames parallel to animCatapultFire; exe data 42..56
        byte animCatapultFireOverlay[40]; // 0x000017FC length: 40
        char field77_0x1824[24]; // 0x00001824 length: 24
        // trebuchet state 2 loading (FX_TR_LOAD at cycle 1, FX_TR_FIRE at cycle 0x21) machine frames (gfxNumber;
        // exe data frame 1 x36), then state 4
        byte animTrebuchetLoad[100]; // 0x0000183C length: 100
        // trebuchet loading: imageIDUnk overlay frames (exe data 2..23)
        byte animTrebuchetLoadOverlay1[100]; // 0x000018A0 length: 100
        // trebuchet loading: imageID2 overlay frames (exe data 37..58)
        byte animTrebuchetLoadOverlay2[104]; // 0x00001904 length: 104
        // trebuchet state 4 (decompiled US_RELOAD_WEAPONUnk) firing machine frames (exe data frame 1 x25)
        byte animTrebuchetFire[60]; // 0x0000196C length: 60
        // trebuchet firing: imageIDUnk overlay frames; the projectile/cow is released when this table yields 0x1B;
        // exe data 24..36 then 2
        byte animTrebuchetFireOverlay1[60]; // 0x000019A8 length: 60
        // trebuchet firing: imageID2 overlay frames (exe data 59..71)
        byte animTrebuchetFireOverlay2[64]; // 0x000019E4 length: 64
        // mangonel state 2 loading (FX_MA_LOAD) machine frames, then state 4; exe data 1..14
        byte animMangonelLoad[60]; // 0x00001A24 length: 60
        // mangonel loading: imageIDUnk overlay frames (exe data 31..44)
        byte animMangonelLoadOverlay[60]; // 0x00001A60 length: 60
        // mangonel state 4 (decompiled US_RELOAD_WEAPONUnk) firing machine frames, FX_MA_FIRE; exe data 15..30
        byte animMangonelFire[60]; // 0x00001A9C length: 60
        // mangonel firing: imageIDUnk overlay frames (exe data 45..60)
        byte animMangonelFireOverlay[60]; // 0x00001AD8 length: 60
        // ballista state 2 loading (FX_BALLISTA_LOAD) machine frames, then state 4; exe data 1..7
        byte animBallistaLoad[60]; // 0x00001B14 length: 60
        // ballista loading: imageIDUnk overlay frames (exe data 22..28)
        byte animBallistaLoadOverlay[60]; // 0x00001B50 length: 60
        // ballista state 4 (decompiled US_RELOAD_WEAPONUnk) firing machine frames, FX_BALLISTA_FIRE; exe data 8..21
        byte animBallistaFire[60]; // 0x00001B8C length: 60
        // ballista firing: imageIDUnk overlay frames (exe data 29..42)
        byte animBallistaFireOverlay[60]; // 0x00001BC8 length: 60
        // spearman US_MELEE_ATTACK and US_MELEE_ATTACK_WALL frames (exe data 1..12)
        byte animSpearmanMelee[36]; // 0x00001C04 length: 36
        // spearman state 3: pushing down an adjacent enemy ladder (findAndDestroyAdjacentEnemyLadder at cycle 10,
        // speech UT_E_SPEAR 0x21; gfx 0x411 + facing)
        byte animSpearmanPushLadder[44]; // 0x00001C28 length: 44
        // spearman state 1 (US_IDLEUnk) idle for unit slot & 3 == 0
        byte animSpearmanIdleA[68]; // 0x00001C54 length: 68
        // spearman state 1 idle for unit slot & 3 == 1
        byte animSpearmanIdleB[64]; // 0x00001C98 length: 64
        // spearman state 1 idle for unit slot & 3 == 2
        byte animSpearmanIdleC[44]; // 0x00001CD8 length: 44
        // spearman state 1 idle for unit slot & 3 == 3
        byte animSpearmanIdleD[68]; // 0x00001D04 length: 68
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateSpearman
        // state 2 (alert idle: enemy within 400 but no adjacent enemy ladder to push), odd unit slot IDs (even IDs
        // use field99); gfx 0x220+frame, then state 0 and moveToFreeTileNearby.
        byte animSpearmanAlertIdleOdd[52]; // 0x00001D48 length: 52
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateSpearman
        // state 2 (alert idle), even unit slot IDs (odd IDs use field98); gfx 0x220+frame.
        byte animSpearmanAlertIdleEven[84]; // 0x00001D7C length: 84
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). Moat-digging
        // animation (state 124, UIT_DIG_MOAT) shared by crusader archer, spearman, maceman, engineer and slave:
        // FX_MOAT_DIG on cycle 5, TileMapState::advanceMoatDigProgress each finished cycle.
        byte animSharedMoatDig[40]; // 0x00001DD0 length: 40
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). Moat-filling
        // animation (state 125 = US_FILL_MOAT, UIT_FILL_MOAT / enemy moat) shared by crusader archer, spearman, maceman,
        // engineer and slave: FX_MOAT_DIG on cycle 5, TileMapState::removeMoat when a cycle finishes.
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). Moat-filling
        // animation (state 125 = US_DIG, UIT_FILL_MOAT / enemy moat) shared by crusader archer, spearman, maceman,
        // engineer and slave: FX_MOAT_DIG on cycle 5, TileMapState::removeMoat when a cycle finishes.
        byte animSharedMoatFill[40]; // 0x00001DF8 length: 40
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateSpearman
        // state 6 (AI-owned unit with no enemy within 400: faces signpostIDs[0] outside skirmish), units with odd
        // fixedRng (even use field103).
        byte animSpearmanAiStandbyOdd[40]; // 0x00001E20 length: 40
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateSpearman
        // state 6 (AI-owned unit, no enemy within 400, faces signpost 0 outside skirmish), units with even fixedRng
        // (odd use field102).
        byte animSpearmanAiStandbyEven[52]; // 0x00001E48 length: 52
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateSwordsman
        // melee swing used when substate == 0 (substate alternates swings) and the wall/building attack
        // (US_MELEE_ATTACK_WALL).
        byte animSwordsmanMeleeA[36]; // 0x00001E7C length: 36
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateSwordsman
        // alternate melee swing (substate != 0); FX_SWISH on cycle 4.
        byte animSwordsmanMeleeB[36]; // 0x00001EA0 length: 36
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateSwordsman
        // idle (state 1) variant for unit slot ID & 3 == 0; gfx 0x141+frame.
        byte animSwordsmanIdle0[120]; // 0x00001EC4 length: 120
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateSwordsman
        // idle (state 1) variant for unit slot ID & 3 == 1; gfx 0x141+frame.
        byte animSwordsmanIdle1[72]; // 0x00001F3C length: 72
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateSwordsman
        // idle (state 1) variant for unit slot ID & 3 == 2; gfx 0x141+frame.
        byte animSwordsmanIdle2[104]; // 0x00001F84 length: 104
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateSwordsman
        // idle (state 1) variant for unit slot ID & 3 == 3; the only variant with random FX_SHEATH_OUT (cycle 11) /
        // FX_SHEATH_IN (cycle 80); gfx 0x141+frame.
        byte animSwordsmanIdle3[108]; // 0x00001FEC length: 108
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateSwordsman
        // state 3 (AI-owned unit, no enemy within 400, faces signpost 0 outside skirmish); both fixedRng branches
        // read this same table.
        byte animSwordsmanAiStandby[44]; // 0x00002058 length: 44
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateKnight
        // idle (state 1), even unit slot IDs: drives the second sprite layer imageIDUnk (GM 0x6E), base
        // 0x179+facing+frame*8. Main sprite uses field113.
        byte animKnightIdleOverlayEven[128]; // 0x00002084 length: 128
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateKnight
        // idle (state 1), odd unit slot IDs: second sprite layer imageIDUnk (GM 0x6E), base 0x369+facing+frame*8.
        // Main sprite uses field113.
        byte animKnightIdleOverlayOdd[128]; // 0x00002104 length: 128
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateKnight
        // idle (state 1): main sprite gfxNumber 0xF9+facing+frame*8, played together with the overlay table
        // field111/field112.
        byte animKnightIdleMain[140]; // 0x00002184 length: 140
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateKnight
        // state 3 (AI-owned, no enemy within 400, faces signpost 0 outside skirmish): second sprite layer
        // imageIDUnk base 0x1D9.
        byte animKnightAiStandbyOverlay[44]; // 0x00002210 length: 44
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateKnight
        // state 3 (AI standby): main sprite gfxNumber 0xF9+facing+frame*8, paired with overlay table field114.
        byte animKnightAiStandbyMain[40]; // 0x0000223C length: 40
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateKnight
        // melee (US_MELEE_ATTACK), odd unit slot IDs: second sprite layer imageIDUnk base 0x371.
        byte animKnightMeleeOverlayOdd[44]; // 0x00002264 length: 44
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateKnight
        // melee, even unit slot IDs: second sprite layer imageIDUnk base 0x1D9; also the only table of the
        // wall/building attack (US_MELEE_ATTACK_WALL).
        byte animKnightMeleeOverlayEven[76]; // 0x00002290 length: 76
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateKnight
        // melee: main sprite gfxNumber 0xF9+facing+frame*8 (two strikes per cycle: FX_SWISH 4/13, FX_STEEL1 5/14,
        // hurt SFX 7/16), paired with overlay field116/field117.
        byte animKnightMeleeMain[272]; // 0x000022DC length: 272
        byte fixme_integerArrayLadderMan[88]; // 0x000023EC length: 88
        byte fixme_integerArrayLadderMan2[96]; // 0x00002444 length: 96
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateLadderman
        // state 2 (alert idle: closest enemy 97..400 away), even unit slot IDs (odd use
        // fixme_integerArrayLadderMan3); gfx 0x90+frame.
        byte animLaddermanAlertIdleEven[40]; // 0x000024A4 length: 40
        byte fixme_integerArrayLadderMan3[56]; // 0x000024CC length: 56
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateLadderman
        // US_DEATH_02: the placed ladder being knocked down (directional frames, FX_LADDER_BREAK).
        byte animLaddermanLadderBreak[52]; // 0x00002504 length: 52
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateSlave
        // torch attack: melee (US_MELEE_ATTACK, FX_SLAVE_FIRE, hurt SFX on cycle 6) and wall/building attack
        // (FX_SLAVE_FIRE on cycles 5/18).
        byte animSlaveMelee[52]; // 0x00002538 length: 52
        byte ANIM_Slave_Idle1[32]; // 0x0000256C length: 32
        byte ANIM_Slave_Idle2[96]; // 0x0000258C length: 96
        byte ANIM_Slave_Idle3[144]; // 0x000025EC length: 144
        byte ANIM_Slave_Idle4[152]; // 0x0000267C length: 152
        byte fixme_integerArraySlave5[60]; // 0x00002714 length: 60
        byte fixme_integerArraySlave6[60]; // 0x00002750 length: 60
        // [142 0x00570400] frame table of US_RELOAD_WEAPONUnk; when exhausted goes to aim state
        byte ANIM_ArabianArcher_Reload[32]; // 0x0000278C length: 32
        // [142 0x00570400] frame table of US_AIM_WEAPONUnk; at end snapshots target position and goes to fire state
        byte ANIM_ArabianArcher_Aim[24]; // 0x000027AC length: 24
        // [142 0x00570400] frame table of US_FIRE_WEAPONUnk; projectile spawned at frame 0x16
        byte ANIM_ArabianArcher_Fire[40]; // 0x000027C4 length: 40
        byte ANIM_ArabianArcher_Melee[48]; // 0x000027EC length: 48
        // [142 0x00570400] frame table of US_LOOK_AROUNDUnk
        byte ANIM_ArabianArcher_LookAround[28]; // 0x0000281C length: 28
        byte ANIM_ArabianArcher_Idle_SitDown[36]; // 0x00002838 length: 36
        byte ANIM_ArabianArcher_Idle1[128]; // 0x0000285C length: 128
        byte ANIM_ArabianArcher_Idle2[96]; // 0x000028DC length: 96
        byte ANIM_ArabianArcher_Idle3[124]; // 0x0000293C length: 124
        byte ANIM_ArabianArcher_Idle4[108]; // 0x000029B8 length: 108
        byte ANIM_Slinger_Melee[84]; // 0x00002A24 length: 84
        byte ANIM_Slinger_Idle_101_sit_down[36]; // 0x00002A78 length: 36
        byte ANIM_Slinger_Idle_1_0x6a_0x6b[96]; // 0x00002A9C length: 96
        byte ANIM_Slinger_Idle_2_0x6a_0x6b[132]; // 0x00002AFC length: 132
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateSlinger
        // getting up from sitting: state 8 when seated and idle substate 100 of state 11 (US_SIT_DOWNUnk); at the
        // end substate=0x66, seated=0; gfx 0x298+frame (same sheet range as the sit-down).
        byte animSlingerStandUp[32]; // 0x00002B80 length: 32
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateSlinger
        // state 8 (alert idle: enemy 0x1B0..400 away or no shoot target) while standing, odd unit slot IDs (even
        // use ANIM_Slinger_8); gfx 0x288+frame.
        byte animSlingerAlertIdleOdd[52]; // 0x00002BA0 length: 52
        byte ANIM_Slinger_8[84]; // 0x00002BD4 length: 84
        byte ANIM_Slinger_4[28]; // 0x00002C28 length: 28
        byte ANIM_Slinger_Throwing[56]; // 0x00002C44 length: 56
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateSlinger
        // US_FIRE_WEAPONUnk (state 6): release throw, projectile shot when animationFrame == 12; same table for all
        // aim pitches (jugglerCount 0/-1/1 -> gfx bases 0x1C1/0x161/0x221). The preceding aim state uses
        // ANIM_Slinger_Throwing.
        byte animSlingerFire[24]; // 0x00002C7C length: 24
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateAssassin
        // melee (FX_STEEL1, FX_ASS_SWISH on cycle 4) and wall/building attack; gfx 0x101+facing at end.
        byte animAssassinMelee[52]; // 0x00002C94 length: 52
        byte DAT_AssassinAnimationFrames0[52]; // 0x00002CC8 length: 52
        byte DAT_AssassinAnimationFrames1[64]; // 0x00002CFC length: 64
        byte DAT_AssassinAnimationFrames2[48]; // 0x00002D3C length: 48
        byte DAT_AssassinAnimationFrames4[64]; // 0x00002D6C length: 64
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateAssassin
        // US_ASSASSIN_THROWING_HOOK when assassinHeightDifference < 0x46 (low wall).
        byte animAssassinHookThrowLow[72]; // 0x00002DAC length: 72
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateAssassin
        // US_ASSASSIN_THROWING_HOOK when assassinHeightDifference is 0x46..0x9F.
        byte animAssassinHookThrowMid[88]; // 0x00002DF4 length: 88
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateAssassin
        // US_ASSASSIN_THROWING_HOOK when assassinHeightDifference >= 0xA0 (tall wall).
        byte animAssassinHookThrowHigh[100]; // 0x00002E4C length: 100
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateAssassin
        // US_ASSASSIN_START_CLIMBING_DOWN; gfx 0x1C1+facing at end.
        byte animAssassinClimbDownStart[40]; // 0x00002EB0 length: 40
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateAssassin
        // US_ASSASSIN_CLIMBING_UP (imageIDUnk picked from assassinHeightDifference); gfx 0x271+facing at end.
        byte animAssassinClimbUp[44]; // 0x00002ED8 length: 44
        byte ANIM_HorseArcher_Idle_part1[96]; // 0x00002F04 length: 96
        byte ANIM_HorseArcher_Idle_part2[92]; // 0x00002F64 length: 92
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation).
        // UpdateHorseArcher melee and wall/building attack: second sprite layer imageIDUnk base
        // 0x79+facing+frame*8; main sprite uses field164.
        byte animHorseArcherMeleeOverlay[76]; // 0x00002FC0 length: 76
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation).
        // UpdateHorseArcher melee and wall/building attack: main sprite gfxNumber, paired with overlay table
        // field163 (FX_SWISH on cycles 4/13).
        byte animHorseArcherMeleeMain[216]; // 0x0000300C length: 216
        byte ANIM_Frames_HorseArcher_Shooting_1[104]; // 0x000030E4 length: 104
        byte ANIM_Frames_HorseArcher_Shooting_2[88]; // 0x0000314C length: 88
        byte ANIM_Frames_HorseArcher_Shooting_3[104]; // 0x000031A4 length: 104
        // arab swordsman melee animation array
        byte ANIM_ArabianSwordsman_Melee[64]; // 0x0000320C length: 64
        byte DAT_ANI_ASWORD_UNKNOWN_1[88]; // 0x0000324C length: 88
        byte ANIM_ArabianSwordsman_Idle1[104]; // 0x000032A4 length: 104
        byte ANIM_ArabianSwordsman_Idle2[48]; // 0x0000330C length: 48
        byte ANIM_ArabianSwordsman_Idle3[80]; // 0x0000333C length: 80
        byte ANIM_ArabianSwordsman_Idle4[104]; // 0x0000338C length: 104
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation).
        // UpdateFireThrower melee (hurt SFX on cycle 4) and wall/building attack; gfx 0x81+facing at end.
        byte animFireThrowerMelee[76]; // 0x000033F4 length: 76
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation).
        // UpdateFireThrower state 8 (alert idle: enemy 0x1B0..400 away or no shoot target), odd unit slot IDs; gfx
        // 0x220+frame. Not a stand-up animation despite the enum name.
        byte animFireThrowerAlertIdleOdd[52]; // 0x00003440 length: 52
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation).
        // UpdateFireThrower state 8 (alert idle), even unit slot IDs; gfx 0x220+frame.
        byte animFireThrowerAlertIdleEven[96]; // 0x00003474 length: 96
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation).
        // UpdateFireThrower state 4 (US_RELOAD_WEAPONUnk): gfx 0x139+facing+frame*8; at the end checks target
        // distance and goes to aim (state 5).
        byte animFireThrowerReload[24]; // 0x000034D4 length: 24
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation).
        // UpdateFireThrower state 5 (US_AIM_WEAPONUnk, faces the target): gfx 0x139+facing+frame*8, then state 6.
        byte animFireThrowerAim[36]; // 0x000034EC length: 36
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation).
        // UpdateFireThrower state 6 (US_FIRE_WEAPONUnk): projectile (ET_FIRETHROWER...) launched when
        // animationFrame == 0x14; gfx 0x139+facing+frame*8.
        byte animFireThrowerFire[60]; // 0x00003510 length: 60
        byte ANIM_FireThrower_Idle1[72]; // 0x0000354C length: 72
        byte ANIM_FireThrower_Idle2[72]; // 0x00003594 length: 72
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation).
        // UpdateFireBallista state 2: loading (FX_BALLISTA_LOAD on cycle 1), drives gfxNumber and overlay
        // imageIDUnk (0xA1 base); at the end goes to state 4.
        byte animFireBallistaLoad[120]; // 0x000035DC length: 120
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation).
        // UpdateFireBallista state 4 (US_RELOAD_WEAPONUnk enum name, but it fires): FX_ARAB_BALLISTA_FIRE at frame
        // 12, projectile at frame 13; drives gfxNumber and overlay imageIDUnk.
        byte animFireBallistaFire[120]; // 0x00003654 length: 120
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateEngineer
        // state 2 (alert idle: closest enemy within 400), odd unit slot IDs; gfx 0x178+frame.
        byte animEngineerAlertIdleOdd[136]; // 0x000036CC length: 136
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateEngineer
        // state 2 (alert idle), even unit slot IDs; gfx 0x178+frame.
        byte animEngineerAlertIdleEven[92]; // 0x00003754 length: 92
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateEngineer
        // idle (state 1) substate 0x65: sitting down; afterwards substate = 0x6A + (slot & 3) and the seated flag
        // is set.
        byte animEngineerIdleSitDown[36]; // 0x000037B0 length: 36
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateEngineer
        // idle (state 1) substate 100: standing up; afterwards substate 0x6A and the seated flag is cleared.
        byte animEngineerIdleStandUp[36]; // 0x000037D4 length: 36
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateEngineer
        // idle (state 1) substate 0x6A (idle cycle 0x6A..0x71, advances by 1 or 2); gfx 0x188+frame.
        byte animEngineerIdleSub6a[36]; // 0x000037F8 length: 36
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateEngineer
        // idle (state 1) substate 0x6E.
        byte animEngineerIdleSub6e[32]; // 0x0000381C length: 32
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateEngineer
        // idle (state 1) substates 0x6B and 0x6D (shared table).
        byte animEngineerIdleSub6b6d[28]; // 0x0000383C length: 28
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateEngineer
        // idle (state 1) substate 0x6F.
        byte animEngineerIdleSub6f[36]; // 0x00003858 length: 36
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateEngineer
        // idle (state 1) substate 0x71 (last of the idle cycle).
        byte animEngineerIdleSub71[44]; // 0x0000387C length: 44
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateEngineer
        // idle (state 1) substate 0x70.
        byte animEngineerIdleSub70[56]; // 0x000038A8 length: 56
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateEngineer
        // idle (state 1) substate 0x6C.
        byte animEngineerIdleSub6c[64]; // 0x000038E0 length: 64
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateEngineer
        // state 9: the active engineer at the oil smelter (registered as workerID[0]); gfx 0x178+frame; when it
        // ends he fetches pitch or fades into the building.
        byte animEngineerOilSmelterWork[32]; // 0x00003920 length: 32
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateEngineer
        // waiting timer: non-active engineers queued at the oil smelter (state 9) and an engineer holding an oil
        // pot (state 11 US_SIT_DOWNUnk, auto-throw check); only the >0 test is used, the sprite is a fixed pose by
        // facing (0x2A5/0x1F5/0x275).
        byte animEngineerOilWait[28]; // 0x00003940 length: 28
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateEngineer
        // state 10: throwing the oil pot (shootProjectile type 8 + FX_OIL_DUMP at frame 7); gfx
        // 0x26D+facing+frame*8.
        byte animEngineerThrowOil[40]; // 0x0000395C length: 40
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateHunter
        // free-time animation (US_LOOK_AROUNDUnk: no deer target), substate 0; gfx 0x290+frame; may switch to free-
        // time walking.
        byte animHunterFreetime0[152]; // 0x00003984 length: 152
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateHunter
        // free-time animation (US_LOOK_AROUNDUnk), substate 1.
        byte animHunterFreetime1[128]; // 0x00003A1C length: 128
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateHunter
        // free-time animation (US_LOOK_AROUNDUnk), substate 2.
        byte animHunterFreetime2[192]; // 0x00003A9C length: 192
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateHunter
        // free-time animation (US_LOOK_AROUNDUnk), substate >= 3.
        byte animHunterFreetime3[272]; // 0x00003B5C length: 272
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateHunter
        // state 8 (no deer, enemy within 400 but not shootable), substate 0 (alternates 0/1); gfx 0x280+frame.
        byte animHunterAlertIdleA[40]; // 0x00003C6C length: 40
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateHunter
        // state 8 (alert idle), substate 1; gfx 0x2B1+frame.
        byte animHunterAlertIdleB[116]; // 0x00003C94 length: 116
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateHunter
        // melee attack (US_MELEE_ATTACK).
        byte animHunterMelee[36]; // 0x00003D08 length: 36
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateHunter
        // state 10: shooting the bow (arrow + FX_ARROW_FIRE at frame 0x16); gfx 0x301+facing+frame*8.
        byte animHunterShootBow[68]; // 0x00003D2C length: 68
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateWoodcutter
        // free-time animation ('Freetime at good things', state 10), substate 0.
        byte animWoodcutterFreetime0[52]; // 0x00003D70 length: 52
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateWoodcutter
        // free-time animation (state 10), substate 1.
        byte animWoodcutterFreetime1[124]; // 0x00003DA4 length: 124
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateWoodcutter
        // free-time animation (state 10), substate 2 (also played on arrival at the hut).
        byte animWoodcutterFreetime2[52]; // 0x00003E20 length: 52
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateWoodcutter
        // free-time animation (state 10), substate 3 (also played on arrival at the hut).
        byte animWoodcutterFreetime3[48]; // 0x00003E54 length: 48
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateWoodcutter
        // free-time animation (state 10), substate 4.
        byte animWoodcutterFreetime4[128]; // 0x00003E84 length: 128
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateWoodcutter
        // free-time animation (state 10), substate 5.
        byte animWoodcutterFreetime5[88]; // 0x00003F04 length: 88
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateWoodcutter
        // free-time animation (state 10), substate 6.
        byte animWoodcutterFreetime6[152]; // 0x00003F5C length: 152
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateWoodcutter
        // state 2: chopping the standing tree (FX_CHOP at frame 12, damages the tree, tree-fall SFX by stage).
        byte animWoodcutterFellTree[44]; // 0x00003FF4 length: 44
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateWoodcutter
        // state 3: cutting the felled trunk, first cut (woodCutterChopsCount == 0); FX_CHOP at frame 7.
        byte animWoodcutterCutTrunkFirst[44]; // 0x00004020 length: 44
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateWoodcutter
        // state 3: cutting the felled trunk, later cuts (woodCutterChopsCount != 0); FX_CHOP at frame 7.
        byte animWoodcutterCutTrunk[36]; // 0x0000404C length: 36
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateWoodcutter
        // attack swing (state 106 US_MELEE_ATTACK); gfx 0x361+facing at end.
        byte animWoodcutterMelee[68]; // 0x00004070 length: 68
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateBlacksmith
        // state 9 (no reachable iron stockpile: waits, then retries), substate 0 (alternates 0/1); gfx 0x2A0+frame;
        // may start free-time walking.
        byte animBlacksmithNoIronIdleA[144]; // 0x000040B4 length: 144
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateBlacksmith
        // state 9 (no reachable iron), substate 1; gfx 0x2A0+frame.
        byte animBlacksmithNoIronIdleB[88]; // 0x00004144 length: 88
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateBlacksmith
        // melee attack (US_MELEE_ATTACK); gfx 0x241+facing at end.
        byte animBlacksmithMelee[32]; // 0x0000419C length: 32
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). Melee attack
        // (US_MELEE_ATTACK) shared by UpdateQuarryMason and UpdateQuarryWorker; gfx 0x131+facing at end.
        byte animQuarryMelee[40]; // 0x000041BC length: 40
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateFletcher
        // free-time animation (state 8), substate 0 (substate = random 0..7 after each); gfx 0x200+frame.
        byte animFletcherFreetime0[36]; // 0x000041E4 length: 36
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateFletcher
        // free-time animation (state 8), substates 1, 4 and 6.
        byte animFletcherFreetime1[44]; // 0x00004208 length: 44
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateFletcher
        // free-time animation (state 8), substates 2 and 5.
        byte animFletcherFreetime2[44]; // 0x00004234 length: 44
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateFletcher
        // free-time animation (state 8), substates 3 and 7.
        byte animFletcherFreetime3[100]; // 0x00004260 length: 100
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateTunneler
        // state 5 idle (closest enemy > 400 or < 97), substate 0 (random 0..3 after each); gfx 400+frame.
        byte animTunnelerIdle0[80]; // 0x000042C4 length: 80
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateTunneler
        // state 5 idle, substate 1.
        byte animTunnelerIdle1[80]; // 0x00004314 length: 80
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateTunneler
        // state 5 idle, substate 2.
        byte animTunnelerIdle2[80]; // 0x00004364 length: 80
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateTunneler
        // state 5 idle, substate 3.
        byte animTunnelerIdle3[104]; // 0x000043B4 length: 104
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateTunneler
        // state 6 (alert idle: closest enemy 97..400 away), even unit slot IDs; gfx 0x180+frame.
        byte animTunnelerAlertIdleEven[40]; // 0x0000441C length: 40
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateTunneler
        // state 6 (alert idle), odd unit slot IDs; gfx 0x180+frame.
        byte animTunnelerAlertIdleOdd[56]; // 0x00004444 length: 56
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateTunneler
        // melee and wall/building attack; gfx 0x1E9+facing at end.
        byte animTunnelerMelee[40]; // 0x0000447C length: 40
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateTunneler
        // state 8: digging in at the workplace marker (FX_DIG1 at frame 10) before fading into the ground and
        // placing the tunnel entrance.
        byte animTunnelerDigIn[120]; // 0x000044A4 length: 120
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdatePeasant
        // campfire idle (state 8) substate 0x66, standing (seated=0); gfx 0x7D+facing/2+frame*4.
        byte animPeasantCampfire66[144]; // 0x0000451C length: 144
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdatePeasant
        // campfire idle (state 8) substate 0x67, standing (seated=0).
        byte animPeasantCampfire67[100]; // 0x000045AC length: 100
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdatePeasant
        // campfire idle (state 8) substate 0x65: sitting down; at the end seated=1.
        byte animPeasantSitDown[40]; // 0x00004610 length: 40
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdatePeasant
        // campfire idle (state 8) substate 100: getting up; at the end seated=0.
        byte animPeasantStandUp[52]; // 0x00004638 length: 52
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdatePeasant
        // campfire idle (state 8) substate 0x6A, seated.
        byte animPeasantCampfireSeated6a[88]; // 0x0000466C length: 88
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdatePeasant
        // campfire idle (state 8) substate 0x6B, seated.
        byte animPeasantCampfireSeated6b[96]; // 0x000046C4 length: 96
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdatePeasant
        // campfire idle (state 8) substate 0x6E, seated.
        byte animPeasantCampfireSeated6e[112]; // 0x00004724 length: 112
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdatePeasant
        // campfire idle (state 8) substate 0x6F, seated.
        byte animPeasantCampfireSeated6f[112]; // 0x00004794 length: 112
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdatePeasant
        // campfire idle (state 8) substate 0x72, standing; gfx 0xB1+facing/2+frame*4.
        byte animPeasantCampfire72[88]; // 0x00004804 length: 88
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdatePeasant
        // campfire idle (state 8) substate 0x73, standing.
        byte animPeasantCampfire73[64]; // 0x0000485C length: 64
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdatePeasant
        // campfire idle (state 8) substate 0x74, standing.
        byte animPeasantCampfire74[104]; // 0x0000489C length: 104
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdatePeasant
        // campfire idle (state 8) substate 0x75, standing.
        byte animPeasantCampfire75[136]; // 0x00004904 length: 136
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdatePeasant
        // campfire idle (state 8) substate 0x76, standing; facing variant +1 for odd fixedRng; gfx
        // 0x13D+dir+frame*4.
        byte animPeasantCampfire76[56]; // 0x0000498C length: 56
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdatePeasant
        // campfire idle (state 8) substate 0x78, standing; gfx 0xED+facing/2+frame*4.
        byte animPeasantCampfire78[112]; // 0x000049C4 length: 112
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdatePitchman
        // free-time animation (state 5); gfx 0x120+frame; may switch to free-time walking, then state 4 (walk to
        // the rig). Not pitch-ditch work.
        byte animPitchmanFreetime[124]; // 0x00004A34 length: 124
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). Death animation
        // shared by UpdateQuarryMason and UpdateQuarryWorker (US_DEATH_01 with gfx base 0x118, the other death
        // states with base 0x130 in the mason); ends in US_DISAPPEAR.
        byte animQuarryDeath[36]; // 0x00004AB0 length: 36
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation).
        // UpdateQuarryWorker (ox-tether worker) free-time animation (state 7); the entry is used directly as
        // gfxNumber (0x18 at the end); substate counts 0..6.
        byte animQuarryWorkerFreetime[72]; // 0x00004AD4 length: 72
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateOx state
        // 4: waiting/loading at the quarry facing it while resourceToDeposit < 8; gfx 0xF9+facing+frame*8.
        byte animOxLoadingAtQuarry[168]; // 0x00004B1C length: 168
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateOx death
        // animation (FX_OX_DIE on cycle 1).
        byte animOxDeath[48]; // 0x00004BC4 length: 48
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation).
        // UpdateWheatFarmer idle at the farm (state 1), substate 0; gfx 0x300 base.
        byte animWheatFarmerIdleA[168]; // 0x00004BF4 length: 168
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation).
        // UpdateWheatFarmer idle at the farm (state 1), substate != 0.
        byte animWheatFarmerIdleB[76]; // 0x00004C9C length: 76
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation).
        // UpdateWheatFarmer state 4: hoeing a field tile (FX_HOE, DamageLayer[tile] = 1 at cycle 8).
        byte animWheatFarmerHoe[40]; // 0x00004CE8 length: 40
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation).
        // UpdateWheatFarmer state 7 (US_LOOK_AROUNDUnk): harvesting a tile (entered with FX_HARVEST); gfx
        // 0x201+facing at end.
        byte animWheatFarmerHarvest[44]; // 0x00004D10 length: 44
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateHopsFarmer
        // idle at the farm (state 1), substate 0.
        byte animHopsFarmerIdleA[168]; // 0x00004D3C length: 168
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateHopsFarmer
        // idle at the farm (state 1), substate != 0; gfx 0x301 at end.
        byte animHopsFarmerIdleB[76]; // 0x00004DE4 length: 76
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateHopsFarmer
        // state 4: planting a tile (DamageLayer = 2); gfx base 0x350 by facing/2.
        byte animHopsFarmerPlant[56]; // 0x00004E30 length: 56
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateHopsFarmer
        // state 6: harvesting a tile (DamageLayer = 0x50, resourceToDeposit++); gfx base 0x310 by facing/2.
        byte animHopsFarmerHarvest[60]; // 0x00004E68 length: 60
        byte DAT_AnimationAppleFarm[156]; // 0x00004EA4 length: 156
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation).
        // UpdateAppleFarmer state 3: picking apples at the tree (resourcesGatheredCount++ afterwards); gfx
        // 0x491+facing at end.
        byte animAppleFarmerPick[52]; // 0x00004F40 length: 52
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation).
        // UpdateDairyFarmer state 1: idle animation at the dairy farm (476 entries); gfx 0x301 at end.
        byte animDairyFarmerIdle[476]; // 0x00004F74 length: 476
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateBaker idle
        // (state 1) substate 100: standing up; afterwards substate 0x6A, seated=0.
        byte animBakerStandUp[16]; // 0x00005150 length: 16
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateBaker idle
        // (state 1) substate 0x65: sitting down; afterwards substate 0x6A, seated=1.
        byte animBakerSitDown[20]; // 0x00005160 length: 20
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateBaker idle
        // (state 1) animation used while CheckUnitProductionPaused is nonzero (other substates without a table get
        // frame 0); gfx 0x100+frame.
        byte animBakerProductionPaused[120]; // 0x00005174 length: 120
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateBaker idle
        // (state 1) substate 0x6A (cycle 0x6A..0x6D).
        byte animBakerIdleSub6a[200]; // 0x000051EC length: 200
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateBaker idle
        // (state 1) substate 0x6B.
        byte animBakerIdleSub6b[112]; // 0x000052B4 length: 112
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateBaker idle
        // (state 1) substate 0x6C.
        byte animBakerIdleSub6c[184]; // 0x00005324 length: 184
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateBaker idle
        // (state 1) substate 0x6D.
        byte animBakerIdleSub6d[164]; // 0x000053DC length: 164
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateTanner
        // idle/sharpening at the tannery (state 1) substate 0x66 (cycle 0x66->0x67->0x68->0x69->0x7A); FX_SHARPEN
        // at frames 3/11 for all substates; gfx 0x160+frame.
        byte animTannerIdleSub66[40]; // 0x00005480 length: 40
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateTanner
        // idle/sharpening (state 1) substate 0x67.
        byte animTannerIdleSub67[56]; // 0x000054A8 length: 56
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateTanner
        // idle/sharpening (state 1) substate 0x68.
        byte animTannerIdleSub68[44]; // 0x000054E0 length: 44
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateTanner
        // idle/sharpening (state 1) substate 0x69.
        byte animTannerIdleSub69[56]; // 0x0000550C length: 56
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateTanner
        // idle/sharpening (state 1) default branch = substate 0x7A.
        byte animTannerIdleSub7a[72]; // 0x00005544 length: 72
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateTanner
        // state 9: slaughtering the cow (at frame 8 the cow is set to state 6 and FX_COW_SLAUGHTER plays; at the
        // end 3 hides are added to the tannery).
        byte animTannerSlaughterCow[56]; // 0x0000558C length: 56
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateArmorer
        // state 9 (no reachable iron stockpile), substate 0 (alternates 0/1); gfx 0x180+frame; may start free-time
        // walking.
        byte animArmorerNoIronIdleA[176]; // 0x000055C4 length: 176
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateArmorer
        // state 9 (no reachable iron), substate 1.
        byte animArmorerNoIronIdleB[136]; // 0x00005674 length: 136
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdatePoleTurner
        // idle at the workshop (state 1) substate 0x66 (cycle 0x66->0x67->0x68->0x69); gfx 0x280+frame.
        byte animPoleTurnerIdleSub66[76]; // 0x000056FC length: 76
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdatePoleTurner
        // idle (state 1) substate 0x67.
        byte animPoleTurnerIdleSub67[52]; // 0x00005748 length: 52
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdatePoleTurner
        // idle (state 1) substate 0x68.
        byte animPoleTurnerIdleSub68[128]; // 0x0000577C length: 128
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdatePoleTurner
        // idle (state 1) default branch = substate 0x69.
        byte animPoleTurnerIdleSub69[184]; // 0x000057FC length: 184
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateBrewer
        // sweeping idle (state 1, FX_BROOM at frame 2) substate 0x66 (cycle 0x66->0x67->0x68->0x69); gfx
        // 0x180+frame.
        byte animBrewerSweepSub66[88]; // 0x000058B4 length: 88
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateBrewer
        // sweeping idle (state 1) substate 0x67.
        byte animBrewerSweepSub67[72]; // 0x0000590C length: 72
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateBrewer
        // sweeping idle (state 1) substate 0x68.
        byte animBrewerSweepSub68[112]; // 0x00005954 length: 112
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateBrewer
        // sweeping idle (state 1) default branch = substate 0x69.
        byte animBrewerSweepSub69[172]; // 0x000059C4 length: 172
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateInnkeeper
        // serving animation (state 1) substate 0 (substates 0..3; 3 uses DAT_InnKeeperAnimationIndices).
        byte animInnkeeperServe0[52]; // 0x00005A70 length: 52
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateInnkeeper
        // serving animation (state 1) substate 1.
        byte animInnkeeperServe1[108]; // 0x00005AA4 length: 108
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateInnkeeper
        // serving animation (state 1) substate 2.
        byte animInnkeeperServe2[44]; // 0x00005B10 length: 44
        byte DAT_InnKeeperAnimationIndices[100]; // 0x00005B3C length: 100
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateMiller
        // idle (state 1) substate 100: standing up; afterwards substate 0x6A, seated=0.
        byte animMillerStandUp[32]; // 0x00005BA0 length: 32
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateMiller
        // idle (state 1) substate 0x65: sitting down; afterwards substate 0x6A, seated=1.
        byte animMillerSitDown[32]; // 0x00005BC0 length: 32
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateMiller
        // idle (state 1) substate 0x6A (and any substate other than 100/0x65/0x6B); gfx 0x180+frame.
        byte animMillerIdleSub6a[68]; // 0x00005BE0 length: 68
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateMiller
        // idle (state 1) substate 0x6B.
        byte animMillerIdleSub6b[112]; // 0x00005C24 length: 112
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation).
        // UpdateMinerIronFetcher free-time animation (state 5, mine empty), odd unit slot IDs (the computed
        // gfxNumber is overwritten, dead store).
        byte animIronMinerFreetimeOdd[80]; // 0x00005C94 length: 80
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation).
        // UpdateMinerIronFetcher free-time animation (state 5, mine empty), even unit slot IDs.
        byte animIronMinerFreetimeEven[68]; // 0x00005CE4 length: 68
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdatePriest
        // state 9: blessing the target unit (faces it), substate 0 (substate advances 0..3 per blessed person).
        byte animPriestBless0[40]; // 0x00005D28 length: 40
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdatePriest
        // state 9 (blessing), substate 1.
        byte animPriestBless1[40]; // 0x00005D50 length: 40
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdatePriest
        // state 9 (blessing), substate 2.
        byte animPriestBless2[56]; // 0x00005D78 length: 56
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdatePriest
        // state 9 (blessing), substate >= 3.
        byte animPriestBless3[56]; // 0x00005DB0 length: 56
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdatePriest
        // state 11 (US_SIT_DOWNUnk: outing without target, the animation played outside before re-entering; prayer
        // per the function annotation), substate 0; gfx 0x100+frame.
        byte animPriestOutdoor0[36]; // 0x00005DE8 length: 36
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdatePriest
        // state 11 (outdoor animation), substate 1.
        byte animPriestOutdoor1[44]; // 0x00005E0C length: 44
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdatePriest
        // state 11 (outdoor animation), substate 2.
        byte animPriestOutdoor2[52]; // 0x00005E38 length: 52
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdatePriest
        // state 11 (outdoor animation) substate 3; also played once in state 7 after leaving the inn (then state
        // 1).
        byte animPriestOutdoor3[84]; // 0x00005E6C length: 84
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateJester
        // state 8: animation on arrival at a wander waypoint (gfx 0x81 base); also the performance act for substate
        // 2 of state 4.
        byte animJesterArrival[36]; // 0x00005EC0 length: 36
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateJester
        // performance (state 4, US_RELOAD_WEAPONUnk) act substate 0, gfx base 0x1B1; also the jester's melee
        // (US_MELEE_ATTACK) animation.
        byte animJesterPerform0[36]; // 0x00005EE4 length: 36
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateJester
        // performance (state 4) act substate 1, gfx base 0x1B1.
        byte animJesterPerform1[44]; // 0x00005F08 length: 44
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateJester
        // performance (state 4) act substate 3, gfx base 0x1B1 (substate 2 uses field304).
        byte animJesterPerform3[56]; // 0x00005F34 length: 56
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateLord state
        // 8: animation after arriving at a defensive building (idle visit from state 7), then state 1.
        byte animLordAtBuilding[52]; // 0x00005F6C length: 52
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateLord state
        // 13: standing at the keep facing its entry; entries 1..5 are mapped to facing offsets 0/+1/+2/-1/-2 (head
        // turns) rather than frame indices; gfx 0xA9+facing+offset.
        byte animLordLookAroundAtKeep[28]; // 0x00005FA0 length: 28
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateLord state
        // 6: talking to a nearby unit (faces targetedUnitID), substate 0 (substate cycles 0..4).
        byte animLordTalk0[56]; // 0x00005FBC length: 56
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateLord state
        // 6 (talking), substate 1.
        byte animLordTalk1[72]; // 0x00005FF4 length: 72
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateLord state
        // 6 (talking), substate 2.
        byte animLordTalk2[72]; // 0x0000603C length: 72
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateLord state
        // 6 (talking), substate 3.
        byte animLordTalk3[88]; // 0x00006084 length: 88
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateLord state
        // 6 (talking), substate 4.
        byte animLordTalk4[72]; // 0x000060DC length: 72
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateLord melee
        // and wall/building attack, substate 0 (substate cycles 0..3).
        byte animLordMelee0[40]; // 0x00006124 length: 40
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateLord melee
        // and wall/building attack, substates 1 and 3.
        byte animLordMelee1[36]; // 0x0000614C length: 36
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateLord melee
        // and wall/building attack, substate 2.
        byte animLordMelee2[36]; // 0x00006170 length: 36
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateLady state
        // 6: talking to a nearby unit (faces it), substate 0 (4 variants by substate).
        byte animLadyTalk0[120]; // 0x00006194 length: 120
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateLady state
        // 6 (talking), substate 1.
        byte animLadyTalk1[96]; // 0x0000620C length: 96
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateLady state
        // 6 (talking), substate 2.
        byte animLadyTalk2[136]; // 0x0000626C length: 136
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateLady state
        // 6 (talking), substate >= 3; gfx 0x101+facing at end.
        byte animLadyTalk3[88]; // 0x000062F4 length: 88
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateDrunkard
        // state 3: staggering animation, substate 0 (of 0..2); gfx 0x100+frame.
        byte animDrunkardStagger0[84]; // 0x0000634C length: 84
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateDrunkard
        // state 3: staggering animation, substate 1.
        byte animDrunkardStagger1[52]; // 0x000063A0 length: 52
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateDrunkard
        // state 3: staggering animation, substate 2.
        byte animDrunkardStagger2[72]; // 0x000063D4 length: 72
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateCow
        // grazing state 0, substate 100: getting up (FX_COW_MOO at cycle 8); then substate 0x66 and the seated word
        // (raw offset) cleared. Cycle: 0x65 -> 0x6A -> 100 -> 0x66 -> 0x67 -> 0x65.
        byte animCowStandUp[36]; // 0x0000641C length: 36
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateCow
        // grazing state 0, substate 0x65: lying down; then substate 0x6A and the seated word set to 1.
        byte animCowLieDown[44]; // 0x00006440 length: 44
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateCow
        // grazing state 0, substate 0x6A (lying), then substate 100.
        byte animCowLyingIdle[144]; // 0x0000646C length: 144
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateCow
        // grazing state 0, substate 0x66 (standing), then 0x67.
        byte animCowStandingIdleA[128]; // 0x000064FC length: 128
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateCow
        // grazing state 0, substate 0x67 (standing, 336 entries), then 0x65.
        byte animCowStandingIdleB[336]; // 0x0000657C length: 336
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateCow death
        // animation: state 6 (slaughtered by the tanner, silent), US_DEATH_01, US_DEATH_03 and US_STONE_DEATH_01;
        // gfx 0x180+frame.
        byte animCowDeath[80]; // 0x000066CC length: 80
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateDeer state
        // 0xCB (relaxed idle, no enemy within 200), substate 0; gfx 0xF9+facing+frame*8.
        byte animDeerIdle0[104]; // 0x0000671C length: 104
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateDeer state
        // 0xCB (relaxed idle), substate 2.
        byte animDeerIdle2[128]; // 0x00006784 length: 128
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateDeer state
        // 0xCB (relaxed idle), substates 1 and 3.
        byte animDeerIdle13[160]; // 0x00006804 length: 160
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateDeer state
        // 0xCC (alert idle: enemy within 200), substates 0 and 2.
        byte animDeerAlert02[80]; // 0x000068A4 length: 80
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateDeer state
        // 0xCC (alert idle), substates 1 and 3.
        byte animDeerAlert13[144]; // 0x000068F4 length: 144
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateDeer state
        // 0xCD (rest) while not seated: lying down; at the end seated=1.
        byte animDeerLieDown[36]; // 0x00006984 length: 36
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateDeer
        // US_MOVE_TO_DESTINATION with substate 100: getting up before running (random animationSpeed 1..8); at the
        // end substate=0, seated=0.
        byte animDeerGetUp[36]; // 0x000069A8 length: 36
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateDeer state
        // 0xCD (rest) while seated: lying/resting loop (256 entries).
        byte animDeerResting[256]; // 0x000069CC length: 256
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateDeer
        // US_DEATH_01 (FX_DEER_FALL at cycle 15).
        byte animDeerDeath1[64]; // 0x00006ACC length: 64
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateDeer
        // US_DEATH_02/03 and US_STONE_DEATH_01/02/03; ends in the corpse state 0x75.
        byte animDeerDeathOther[344]; // 0x00006B0C length: 344
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateCageDog
        // death animation for death states other than US_DEATH_01 (FX_WOLF_DIE at cycle 1); gfx 0x338+frame, then
        // corpse state 0x75.
        byte animCageDogDeathOther[64]; // 0x00006C64 length: 64
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateLion rest
        // state 0xCD while not seated (lying down; afterwards seated=1); field343 is used once seated; gfx
        // 0x170+frame.
        byte animLionLieDown[72]; // 0x00006CA4 length: 72
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateLion rest
        // state 0xCD while seated (after animLionLieDown); gfx 0x170+frame; substate toggles 0/1 afterwards.
        byte animLionResting[40]; // 0x00006CEC length: 40
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateLion move
        // states (101 / 0x78) with substate 100: getting up before walking (random animationSpeed 1..8,
        // movementSpeed 0x14); at the end seated=0 and substate = fixedRng&1. Not the walk cycle.
        byte animLionGetUp[104]; // 0x00006D14 length: 104
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateCageDog
        // rest state 0xCE while not seated: lying down (gfx 0x278 base, sets field250_0x3c2=1); at the end
        // seated=1.
        byte animCageDogLieDown[28]; // 0x00006D7C length: 28
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateCageDog
        // move states with substate 100: getting up before moving when Unit.restingPoseFlag == 0 (gfx
        // 0x2B0+facing+frame*8); at the end seated=0.
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateCageDog
        // move states with substate 100: getting up before moving when Unit.field250_0x3c2 == 0 (gfx
        // 0x2B0+facing+frame*8); at the end seated=0.
        byte animCageDogGetUp[32]; // 0x00006D98 length: 32
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateCageDog
        // move states with substate 100 when Unit.restingPoseFlag != 0 (set by the 0xCE rest state): getting up from
        // lying (gfx 0x270+facing+frame*8).
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateCageDog
        // move states with substate 100 when Unit.field250_0x3c2 != 0 (set by the 0xCE rest state): getting up from
        // lying (gfx 0x270+facing+frame*8).
        byte animCageDogGetUpFromRest[268]; // 0x00006DB8 length: 268
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateLion idle
        // state 0xCC (directional, gfx 0x2B8 base, 376 entries), then state 0. Not related to the 'lions are
        // attacking' warning (that is in the melee state).
        byte animLionStandingIdle[376]; // 0x00006EC4 length: 376
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateLion
        // US_MELEE_ATTACK (FX_LION_ATTACK at cycle 1); afterwards 1000-tick attack cooldown.
        byte animLionMelee[36]; // 0x0000703C length: 36
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateCageDog
        // US_MELEE_ATTACK, substate 0 (substate cycles 1..4 afterwards); FX_WOLF_ATTACK at cycle 1 for every
        // variant.
        byte animCageDogMelee0[24]; // 0x00007060 length: 24
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateCageDog
        // US_MELEE_ATTACK, substate 1.
        byte animCageDogMelee1[32]; // 0x00007078 length: 32
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateCageDog
        // US_MELEE_ATTACK, substate 2.
        byte animCageDogMelee2[40]; // 0x00007098 length: 40
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateCageDog
        // US_MELEE_ATTACK, substate 3.
        byte animCageDogMelee3[32]; // 0x000070C0 length: 32
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateCageDog
        // US_MELEE_ATTACK, substate >= 4; gfx 0x179+facing+frame*8.
        byte animCageDogMelee4[84]; // 0x000070E0 length: 84
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateCageDog
        // rest state 0xCE while seated (after animCageDogLieDown).
        byte animCageDogResting[68]; // 0x00007134 length: 68
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateRabbit
        // relaxed idle state 0xCB (seated=1), variant unit slot ID & 3 == 0.
        byte animRabbitIdle0[40]; // 0x00007178 length: 40
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateRabbit
        // relaxed idle state 0xCB, variant slot & 3 == 1.
        byte animRabbitIdle1[52]; // 0x000071A0 length: 52
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateRabbit
        // relaxed idle state 0xCB, variant slot & 3 == 2.
        byte animRabbitIdle2[56]; // 0x000071D4 length: 56
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateRabbit
        // move states (101 / 0x78) with substate 100: start-of-move hop (movementSpeed 0x28, ends early after
        // (fixedRng&15) slowdown ticks); at the end seated=0, substate 0.
        byte animRabbitMoveStart[92]; // 0x0000720C length: 92
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateRabbit:
        // relaxed idle 0xCB variant slot & 3 == 3 (gfx base 0xF9) and alert idle 0xCC substate 0 (shared table).
        byte animRabbitIdle3Alert0[56]; // 0x00007268 length: 56
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateRabbit
        // alert idle state 0xCC, substate 1.
        byte animRabbitAlert1[64]; // 0x000072A0 length: 64
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateRabbit
        // US_DEATH_01; gfx 0x180+frame.
        byte animRabbitDeath1[48]; // 0x000072E0 length: 48
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateRabbit
        // US_DEATH_02/03 and US_STONE_DEATH_01/02/03; gfx 0x198+frame.
        byte animRabbitDeathOther[136]; // 0x00007310 length: 136
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateCamel idle
        // state 0xCD while not seated: lying down; afterwards seated=1; gfx 0xC0+frame.
        byte animCamelLieDown[44]; // 0x00007398 length: 44
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateCamel move
        // states (2 / 0x78) with substate 100: standing up before walking; at the end substate 0, seated 0.
        byte animCamelGetUp[48]; // 0x000073C4 length: 48
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateCamel idle
        // state 0xCD while seated, substate 0 (substates 0..3).
        byte animCamelSeatedIdle0[112]; // 0x000073F4 length: 112
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateCamel
        // seated idle, substate 1.
        byte animCamelSeatedIdle1[80]; // 0x00007464 length: 80
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateCamel
        // seated idle, substate 2.
        byte animCamelSeatedIdle2[112]; // 0x000074B4 length: 112
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateCamel
        // seated idle, substate 3 (any other).
        byte animCamelSeatedIdle3[192]; // 0x00007524 length: 192
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateHunterDog
        // idle state 1, substate 0 (substate cycles 0..4); gfx 0x198+frame.
        byte animHunterDogIdle0[240]; // 0x000075E4 length: 240
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateHunterDog
        // idle state 1, substate 1.
        byte animHunterDogIdle1[120]; // 0x000076D4 length: 120
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateHunterDog
        // idle state 1, substate 2.
        byte animHunterDogIdle2[112]; // 0x0000774C length: 112
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateHunterDog
        // idle state 1, substate 3.
        byte animHunterDogIdle3[120]; // 0x000077BC length: 120
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateHunterDog
        // idle state 1, substate 4.
        byte animHunterDogIdle4[184]; // 0x00007834 length: 184
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateHunterDog
        // state 3 (idle next to the hunter after following him), substates 0 and 4; directional gfx
        // 0xE9+facing+frame*8.
        byte animHunterDogNearMasterA[64]; // 0x000078EC length: 64
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateHunterDog
        // state 3 (idle next to the hunter), substates 1 and 3.
        byte animHunterDogNearMasterB[88]; // 0x0000792C length: 88
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateHunterDog
        // state 3 (idle next to the hunter), substate 2.
        byte animHunterDogNearMasterC[68]; // 0x00007984 length: 68
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateHunterDog
        // alert animation: state 2 (enemy 1..200 away) and state 6 (watching while the hunter aims/shoots, master
        // in state 9/10); directional gfx 0x169+facing+frame*8.
        byte animHunterDogAlert[28]; // 0x000079C8 length: 28
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateHunterDog
        // state 10 (entered with FX_DOG_WHIMPER after the random run), then walks back (state 9); gfx 0x1CD+frame.
        // Not US_SIT_DOWNUnk (11).
        byte animHunterDogWhimper[72]; // 0x000079E4 length: 72
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateHunterDog
        // US_MELEE_ATTACK; gfx 0xF1+facing+frame*8.
        byte animHunterDogMelee[40]; // 0x00007A2C length: 40
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateHunterDog
        // US_DEATH_01 (FX_DOG_DIE at cycle 1), then ULS_REMOVE.
        byte animHunterDogDeath1[88]; // 0x00007A54 length: 88
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateHunterDog
        // other death states (0x6F..0x74 except US_DEATH_01), then ULS_REMOVE.
        byte animHunterDogDeathOther[80]; // 0x00007AAC length: 80
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateChicken
        // US_DEATH_01 (FX_CHICKEN_FLAP at cycle 1); gfx 0x136+frame.
        byte animChickenDeath1[88]; // 0x00007AFC length: 88
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateChicken
        // other death states; gfx 0x11E+frame.
        byte animChickenDeathOther[88]; // 0x00007B54 length: 88
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateChicken
        // state 1: idle pecking (random facing).
        byte animChickenPeck[108]; // 0x00007BAC length: 108
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateChicken
        // state 2: flapping when a wolf/dog (or 1/16 any non-chicken) is adjacent (FX_CHICKEN_FLAP at cycle 1).
        byte animChickenFlap[52]; // 0x00007C18 length: 52
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateMother
        // idle state 1: baby animation (FX_BABY with 50% at frame 2, at most once per 8 s).
        byte animMotherWithBaby[72]; // 0x00007C4C length: 72
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateMother
        // state 2 (enemies present): scream animation (FX_GIRL_SCREAM), then she runs home (state 5); gfx
        // 0x110+frame.
        byte animMotherScream[40]; // 0x00007C94 length: 40
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateChild idle
        // state 1 (gfx 0x280+frame) and the looping wait animation of a follow-the-leader leader (restarts at entry
        // 0).
        byte animChildIdle[52]; // 0x00007CBC length: 52
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateChild pair
        // game A, state 6 (alternates with state 9 for 1-5 rounds), faces the partner.
        byte animChildPairGameA1[44]; // 0x00007CF0 length: 44
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateChild pair
        // game A, state 9 (US_STAND_UPUnk|US_IDLEUnk), faces the partner.
        byte animChildPairGameA2[44]; // 0x00007D1C length: 44
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateChild pair
        // game B, state 10 (alternates with state 13), faces the partner. Not US_SIT_DOWNUnk (11).
        byte animChildPairGameB1[40]; // 0x00007D48 length: 40
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateChild pair
        // game B, state 13 (US_STAND_UPUnk|US_AIM_WEAPONUnk), faces the partner.
        byte animChildPairGameB2[44]; // 0x00007D70 length: 44
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateJuggler
        // juggling act state 2 (one of four acts picked by RNG&3).
        byte animJugglerAct2[96]; // 0x00007D9C length: 96
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateJuggler
        // juggling act state 3.
        byte animJugglerAct3[96]; // 0x00007DFC length: 96
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateJuggler
        // juggling act state 4 (US_RELOAD_WEAPONUnk); gfx 0xA2+frame.
        byte animJugglerAct4[96]; // 0x00007E5C length: 96
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateJuggler
        // state 5 (US_AIM_WEAPONUnk): first part of the fourth act, then state 6.
        byte animJugglerAct5Start[76]; // 0x00007EBC length: 76
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateJuggler
        // state 6 (US_FIRE_WEAPONUnk): second part of the act started in state 5; gfx 0xB4+frame.
        byte animJugglerAct5End[52]; // 0x00007F08 length: 52
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateJuggler
        // US_DEATH_01, then ULS_REMOVE; gfx 0xC4+frame.
        byte animJugglerDeath1[80]; // 0x00007F3C length: 80
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateJuggler
        // other death states, then ULS_REMOVE; gfx 0xDC+frame.
        byte animJugglerDeathOther[80]; // 0x00007F8C length: 80
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateFireEater
        // fire act state 2 (one of three acts picked by RNG%3).
        byte animFireEaterAct2[72]; // 0x00007FDC length: 72
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateFireEater
        // fire act state 3; gfx 0x91+frame.
        byte animFireEaterAct3[88]; // 0x00008024 length: 88
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateFireEater
        // fire act state 4 (US_RELOAD_WEAPONUnk); gfx 0xA1+frame.
        byte animFireEaterAct4[88]; // 0x0000807C length: 88
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateFireEater
        // US_DEATH_01, then ULS_REMOVE.
        byte animFireEaterDeath1[72]; // 0x000080D4 length: 72
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateFireEater
        // other death states, then ULS_REMOVE.
        byte animFireEaterDeathOther[80]; // 0x0000811C length: 80
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateHealer
        // US_DEATH_01, then ULS_REMOVE.
        byte animHealerDeath1[80]; // 0x0000816C length: 80
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateHealer
        // other death states, then ULS_REMOVE.
        byte animHealerDeathOther[76]; // 0x000081BC length: 76
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateHealer
        // state 6: cure animation at a claimed disease cloud (afterwards refreshPoisonCloudNearUnit and owner
        // someCount60 += 2).
        byte animHealerCure[44]; // 0x00008208 length: 44
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateFireWatch
        // US_DEATH_01 (gfx 0x194 base) and US_DEATH_03 (gfx 0x1AC base), then ULS_REMOVE.
        byte animFireWatchDeath13[80]; // 0x00008234 length: 80
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateFireWatch
        // remaining death states (checkIfCitizenUnitIsAliveBasedOnState branch), then ULS_REMOVE.
        byte animFireWatchDeathOther[76]; // 0x00008284 length: 76
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateFireWatch
        // state 4 (US_RELOAD_WEAPONUnk): throwing water at the burning building (FX_THROW_WATER at cycle 5, then
        // extinguishBuildingFire + FX_FIRE_OUT).
        byte animFireWatchThrowWater[40]; // 0x000082D0 length: 40
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateFireWatch
        // idle state 2, substate 0 (4 idle animations).
        byte animFireWatchIdle0[40]; // 0x000082F8 length: 40
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateFireWatch
        // idle state 2, substate 1.
        byte animFireWatchIdle1[44]; // 0x00008320 length: 44
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateFireWatch
        // idle state 2, substate 2.
        byte animFireWatchIdle2[48]; // 0x0000834C length: 48
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation). UpdateFireWatch
        // idle state 2, substate 3 (any other); gfx 0x18B at end.
        byte animFireWatchIdle3[44]; // 0x0000837C length: 44
        // Signed-byte frame table indexed by animationCycleNumber (entry <= 0 ends the animation).
        // UpdateBatteringRam swing loop in US_MELEE_ATTACK_WALL (FX_RAM_SWING at cycle 2, hit handling at frame
        // 10); a 0 entry restarts at entry 0.
        byte animBatteringRamSwing[44]; // 0x000083A8 length: 44

    } AnimationFrameData;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(AnimationFrameData) == 33748, AnimationFrameData);
} // namespace Map
} // namespace OpenSHC
