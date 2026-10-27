/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/Unit.hpp'
*/

#pragma once

#include "OpenSHC/Map/Units/Pathfinding/DestinationNeededEnumShort.hpp"
#include "OpenSHC/Map/Units/States/UnitStateShort.hpp"
#include "OpenSHC/Map/Units/States/UnitStateUnion.hpp"
#include "OpenSHC/Map/Units/UnitInstructionTypeShort.hpp"
#include "OpenSHC/Map/Units/UnitLogicStateShort.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitInstructionTypeShort;
        using OpenSHC::Map::Units::UnitLogicStateShort;
        using OpenSHC::Map::Units::UnitTypeShort;
        using OpenSHC::Map::Units::Pathfinding::DestinationNeededEnumShort;
        using OpenSHC::Map::Units::States::UnitStateShort;
        using OpenSHC::Map::Units::States::UnitStateUnion;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)
        // SIZE: 0x00000490
        typedef struct Unit {

            undefined1 padding_0x0[4]; // 0x00000000 length: 4
            int gfxNumber; // 0x00000004 length: 4
            // Created by retype action
            int animationSheetFrameOffset; // 0x00000008 length: 4
            // Created by retype action
            short spriteID; // 0x0000000C length: 2
            undefined1 padding_0xe[2]; // 0x0000000E length: 2
            // Render colour index: owner for player units, colour variant for neutral units; read as ownerColorUnk.
            // Created by retype action
            int ownerColorIndex; // 0x00000010 length: 4
            short drawX; // 0x00000014 length: 2
            short drawY; // 0x00000016 length: 2
            short drawWidth; // 0x00000018 length: 2
            short drawHeight1; // 0x0000001A length: 2
            undefined1 padding_0x1c[2]; // 0x0000001C length: 2
            // [UNK PASS] was spriteWidthUnk
            short hitboxWidth; // 0x0000001E length: 2
            // [UNK PASS] was spriteHeightUnk
            short hitboxHeight; // 0x00000020 length: 2
            short drawXOffset; // 0x00000022 length: 2
            short someDrawYOffset; // 0x00000024 length: 2
            short orientationRelatedPositionX; // 0x00000026 length: 2
            short orientationRelatedPositionY; // 0x00000028 length: 2
            // GM originX of the unit sprite (set in setUnitValues); used for draw X and markers
            short spriteOriginX; // 0x0000002A length: 2
            // [133 0x00563910] setUnitValues and this function load it from
            // gmFileHeaderColorpaletteArray[spriteID].originY; the unit renderer subtracts it from drawY (vertical
            // draw anchor); laddermen add 0x10/0x20 per state. Only the low word is ever accessed here (asm word
            // writes/adds at unit+0x1388578), so the type should be short
            short spriteOriginY; // 0x0000002C length: 2
            undefined1 padding_0x2e[2]; // 0x0000002E length: 2
            // Created by retype action
            int field_0x30_animRelated; // 0x00000030 length: 4
            // Created by retype action
            short isSelected; // 0x00000034 length: 2
            undefined1 padding_0x36[2]; // 0x00000036 length: 2
            // for display only
            short healthbar; // 0x00000038 length: 2
            undefined1 padding_0x3a[2]; // 0x0000003A length: 2
            int animationLeapTicksTotal; // 0x0000003C length: 4
            int animationTicker; // 0x00000040 length: 4
            // The amount of ticks (+1) per animation frame
            int animationSpeed; // 0x00000044 length: 4
            int animationFrame; // 0x00000048 length: 4
            // Created by Rename Structure Field action
            int woodCutterChopsCount; // 0x0000004C length: 4
            BOOLEnum animationCycleNumberHasJustIncremented; // 0x00000050 length: 4
            short facingDirectionMapOrientationCorrected; // 0x00000054 length: 2
            // Orientation of the assigned campfire sitting spot
            short campfireSitOrientation; // 0x00000056 length: 2
            // When non-zero the unit sprite faces the viewer (TileMapState.viewDirFront) instead of its facing
            // direction
            short faceViewer; // 0x00000058 length: 2
            // Non-zero renders the unit with colour slot 9; cleared in setMoveDelayForUnitsOnSameTiles
            short drawNeutralColor; // 0x0000005A length: 2
            // Horizontal sprite offset while climbing (from climbingState); reset each update
            int climbDrawOffsetX; // 0x0000005C length: 4
            // Tile the unit occupies when leaving a ladder (exitLadder)
            int ladderExitTile; // 0x00000060 length: 4
            // Occlusion override: 1/2 draw in front (climbing/siege tower), -1 ignore tile occlusion, 0 normal;
            // reset each update
            int drawOrderOverride; // 0x00000064 length: 4
            int vanish; // 0x00000068 length: 4
            // Overhead marker: 1 selection arrow, 2 man-this-siege-engine, 3 needs engineers; cleared after drawing
            short overheadMarkerType; // 0x0000006C length: 2
            // Siege engine rotate-direction marker frame (direction+1, 0 = none); cleared after drawing
            short rotateMarkerFrame; // 0x0000006E length: 2
            // Such as when in marsh or ford, this applies movement penalty.
            byte negativeHeight; // 0x00000070 length: 1
            byte antelopeBasedRngValue; // 0x00000071 length: 1
            undefined1 padding_0x72[2]; // 0x00000072 length: 2
            // Second sprite layer (rope, horse archer upper body); reset every tick.
            int overlayImageID; // 0x00000074 length: 4
            int imageID2; // 0x00000078 length: 4
            // [150 0x00523A30] non-zero value selects cursor frame 0x6A-v and alpha (8-v)*4 of the destination
            // marker
            short destinationMarkerTimer; // 0x0000007C length: 2
            // [132 0x00562AA0] fixed to 0x6E for knights each tick (unit+0x13885CA), used by the renderer as the GM
            // file of the imageIDUnk layer; setUnitValues initialises it to the unit's SPRITE_ID
            short secondaryGmID; // 0x0000007E length: 2
            // Cached value
            short displayColorPlayerID; // 0x00000080 length: 2
            // [170 0x00579300] byte at unit+0x82 used as a start value of DAT_UpdateUnitsTracker: (tracker - value)
            // indexes a dword table at 0xB5F970 subtracted from unit+0x83; cleared when tracker >= value+13. Not a
            // height. Static scan of .text found no writer other than this reset (effect appears dormant) Created
            // by retype action
            undefined1 liftEffectStartTick; // 0x00000082 length: 1
            // Placeholder +0x83 is an unsigned byte: renderMap movzx byte, updateUnits sub/cmp 0x64/clear on byte.
            undefined1 fallDrawHeight; // 0x00000083 length: 1
            // Extra Y offset added in renderMap; zeroed in recomputeUnitStandingHeight
            short drawYAdjust; // 0x00000084 length: 2
            // Y offset of the primary sprite (positive also reduces blend strength)
            short mainSpriteYOffset; // 0x00000086 length: 2
            // Y offset of the secondary sprite (imageIDUnk layer)
            short secondSpriteYOffset; // 0x00000088 length: 2
            // [181 0x004E7810] machine code 0x4E7C19 uses word [unit+0x13885D6] as a GM image index for the
            // assassin second layer, while 0x4E7E23 uses it as the Y shift/clip of the imageID2 layer (graphicSize
            // > 2)
            short assassinLayerImageOrYOffset; // 0x0000008A length: 2
            // 1 moves to 2 (appearing), 3 means removal: dying
            UnitLogicStateShort logicalState; // 0x0000008C length: 2
            UnitTypeShort unitType; // 0x0000008E length: 2
            // From UnitProperties table: large unit stamping occupancy on surrounding tiles; also hit by
            // projectiles in neighbour tiles
            short occupiesNeighbourTiles; // 0x00000090 length: 2
            undefined1 padding_0x92[2]; // 0x00000092 length: 2
            short moveRelatedFlag; // 0x00000094 length: 2
            // Real value
            short owner; // 0x00000096 length: 2
            int uid; // 0x00000098 length: 4
            int time; // 0x0000009C length: 4
            int targetUID; // 0x000000A0 length: 4
            undefined1 padding_0xa4[4]; // 0x000000A4 length: 4
            // [120 0x0054F860] stores the targeted deer's uid for the hunter, not a tree
            int workTargetUID; // 0x000000A8 length: 4
            undefined1 padding_0xac[4]; // 0x000000AC length: 4
            // Created by retype action
            short goToRallyPoint; // 0x000000B0 length: 2
            short ifSelectedThenPlayerID; // 0x000000B2 length: 2
            short selectionRelatedFlag; // 0x000000B4 length: 2
            short microXPosition; // 0x000000B6 length: 2
            short microYPosition; // 0x000000B8 length: 2
            short terrainOrClimbHeight; // 0x000000BA length: 2
            // Created by retype action
            short buildingHeight; // 0x000000BC length: 2
            short shootTargetMicroX; // 0x000000BE length: 2
            short shootTargetMicroY; // 0x000000C0 length: 2
            short shootTargetZ; // 0x000000C2 length: 2
            // j
            short x; // 0x000000C4 length: 2
            // i
            short y; // 0x000000C6 length: 2
            // j
            short destinationXPosition; // 0x000000C8 length: 2
            // i
            short destinationYPosition; // 0x000000CA length: 2
            // [162 0x00533A10] set to the unit's position when a path plan is committed; path steps are traced from
            // it also previousLocation j
            short pathStartX; // 0x000000CC length: 2
            // [162 0x00533A10] same as ladderExitXPosition for Y also previousLocation i
            short pathStartY; // 0x000000CE length: 2
            // +200 per hit (cap 1000), decremented each tick; lord retreats while > 10
            short recentDamageTimer; // 0x000000D0 length: 2
            // Projectiles from this unit hitting empty ground; catapult gives up target after 6
            short missedShotCount; // 0x000000D2 length: 2
            int tile; // 0x000000D4 length: 4
            int destinationTilePosition; // 0x000000D8 length: 4
            // also LadderExtTilePosition
            int previousTilePosition; // 0x000000DC length: 4
            short mimicCurrentXPosition; // 0x000000E0 length: 2
            short mimicCurrentYPosition; // 0x000000E2 length: 2
            // tile + directionTranslationMatrix[y][dir] for the step being started
            int moveToTile; // 0x000000E4 length: 4
            // When non-zero commitPendingUnitPosition copies nextTileUnk/mimic position to tile/x/y
            int pendingPositionValid; // 0x000000E8 length: 4
            // [167 0x0053D850] read back here as the destination to resume after an interruption; spawnUnit
            // initialises it to the spawn tile; processUnitMove sets it to the current tile when the path ends
            short savedDestinationX; // 0x000000EC length: 2
            // [167 0x0053D850] same as destinationX_2Unk, Y component
            short savedDestinationY; // 0x000000EE length: 2
            // [168 0x0054A7B0] saved from destinationX_2Unk before chasing an enemy, used as guard-post centre for
            // the defensive range and restored as destination afterwards
            short chaseReturnX; // 0x000000F0 length: 2
            // [168 0x0054A7B0] Y counterpart of _someX_2
            short chaseReturnY; // 0x000000F2 length: 2
            short moveDelay; // 0x000000F4 length: 2
            // Generic per-unit movement status for all unit types: 0 idle/arrived, 1 death/path requested, 2
            // following path, 5 interrupted.
            short movementState; // 0x000000F6 length: 2
            // [169 0x00578C40] incremented per sub-step, 8 = at tile centre/stopped, reset to 0 when the next path
            // step starts
            short subTileStepProgress; // 0x000000F8 length: 2
            short currentIndexInPathPlan; // 0x000000FA length: 2
            short totalSizeOfPathPlan; // 0x000000FC length: 2
            byte pathPlanStart[400]; // 0x000000FE length: 400
            short moveInstructionSpeedDelayTracker; // 0x0000028E length: 2
            short leftover; // 0x00000290 length: 2
            short wallDataID; // 0x00000292 length: 2
            short climbDataID; // 0x00000294 length: 2
            undefined1 padding_0x296[2]; // 0x00000296 length: 2
            int climbDataRelated; // 0x00000298 length: 4
            short climbDirection; // 0x0000029C length: 2
            short usingTeleport; // 0x0000029E length: 2
            short dying; // 0x000002A0 length: 2
            // Number is always higher than the unitID, because the TileMap stores the lowest unitID for a tile.
            ushort nextUnitOnTheSameTile; // 0x000002A2 length: 2
            // Created by retype action
            short isSelectable_OR_matchTime; // 0x000002A4 length: 2
            short closestEnemyMicroDistance; // 0x000002A6 length: 2
            // Path connection area of the destination (or area route result) set in setDestinationForUnit
            short destinationArea; // 0x000002A8 length: 2
            short targetShootRelated; // 0x000002AA length: 2
            // Set by work/freetime/idle states (1; tunneler and crossbowman idle 10) and cleared each updateUnits
            // before processMeleeInitiation; write-only in clean.exe
            short busyThisTick; // 0x000002AC length: 2
            short graphicSize; // 0x000002AE length: 2
            // Created by retype action
            int animationCycleNumber; // 0x000002B0 length: 4
            // Created by retype action
            short facingDirection; // 0x000002B4 length: 2
            short orientation; // 0x000002B6 length: 2
            undefined1 padding_0x2b8[2]; // 0x000002B8 length: 2
            short unitOrderWhenOnSameTile; // 0x000002BA length: 2
            short movementRunUpTime; // 0x000002BC length: 2
            short stateBasedSpeed; // 0x000002BE length: 2
            // Created by retype action
            UnitStateUnion state; // 0x000002C0 length: 2
            // [112 0x005416B0] written before entering state 0x6D and copied into state when the fade finishes
            UnitStateShort stateAfterFade; // 0x000002C2 length: 2
            // Unit state before this tick's state update
            short previousState; // 0x000002C4 length: 2
            UnitStateUnion state_3; // 0x000002C6 length: 2
            short updateTickTracker; // 0x000002C8 length: 2
            UnitTypeShort unitTypeToChangeInto; // 0x000002CA length: 2
            short state_2; // 0x000002CC length: 2
            UnitTypeShort unitType_3; // 0x000002CE length: 2
            // [UNK PASS] was someUnitStat2_meleeDamageUnk
            short canMelee; // 0x000002D0 length: 2
            short unknownMovementRelated_0x2d2; // 0x000002D2 length: 2
            // Display only I believe
            short healthPercentage; // 0x000002D4 length: 2
            short selectionTargetUnitID; // 0x000002D6 length: 2
            short tribeID; // 0x000002D8 length: 2
            short idInTribe; // 0x000002DA length: 2
            short plannedDestinationX; // 0x000002DC length: 2
            short plannedDestinationY; // 0x000002DE length: 2
            short topSpeedDelayIndex; // 0x000002E0 length: 2
            short movementDistance; // 0x000002E2 length: 2
            int tribeUID; // 0x000002E4 length: 4
            int workTimer; // 0x000002E8 length: 4
            // [109 0x00530B40] one of the 4 ring slots averaged into av (likewise workRelatedB/C)
            int workTimerHistory1; // 0x000002EC length: 4
            int workRelatedB; // 0x000002F0 length: 4
            int workRelatedC; // 0x000002F4 length: 4
            // [109 0x00530B40] set to the average of the positive work-timer slots
            int avgWorkCycleTicks; // 0x000002F8 length: 4
            // [109 0x00530B40] 0..3 ring index; slot address = manningEngineerRef(0x314) - 0x2C + working*4 =
            // workTimer(0x2E8) + working*4
            short workTimerSlotIndex; // 0x000002FC length: 2
            // 1 when the worker's production is paused (CheckUnitProductionPaused)
            short productionPaused; // 0x000002FE length: 2
            short unitTypeSpecificRestingState; // 0x00000300 length: 2
            // [151 0x005244D0] assigned the SomeTribeBehaviorType targetType value for every target kind (walls,
            // buildings, lord, moat ...)
            short siegeTargetBehaviorType; // 0x00000302 length: 2
            // Created by retype action
            short productivityMod100; // 0x00000304 length: 2
            // Created by retype action
            short productivityDiv100; // 0x00000306 length: 2
            // 0..3 result of updateUnitFadeAndVisibilityNearStructures (1 near building, 2 near tower, 3 other)
            short structureVisibilityMode; // 0x00000308 length: 2
            // Created by retype action
            short idle; // 0x0000030A length: 2
            short banked; // 0x0000030C length: 2
            // [109 0x00530C40] assigned (100-productivity)*av/100, the break length compared with banked
            short requiredBreakTicks; // 0x0000030E length: 2
            short targetX; // 0x00000310 length: 2
            short targetY; // 0x00000312 length: 2
            short manningEngineerRef[4]; // 0x00000314 length: 8
            int manningEngineerUIDRef[4]; // 0x0000031C length: 16
            // Per-type flag 1 for animals, cow/ox/dogs/chicken and mother/child/juggler/fire eater: no voice,
            // ambient on transfer, animal arrow-hit SFX; not 'stalked'
            byte isAnimalOrAmbient; // 0x0000032C length: 1
            // 1 jester / 2 rabbit: unit only advances during certain animation frames (hopping gait)
            char hopGaitMode; // 0x0000032D length: 1
            // 0 opaque..0x20 invisible; incremented and decremented, not only a countdown. 0 to 0x20, used in 0x6e
            // (disappear) state, determines the alpha and serves as a timer
            byte fadeLevel; // 0x0000032E length: 1
            // signed step added to disappearFadeAlphaCountdown in fade state 109 by all unit types incl. engineers
            // (25+ batches); sign picks in/out 0 if never manned before, 0xFE if was removed from siege, else
            // siegeRef
            byte fadeAlphaStep; // 0x0000032F length: 1
            // [163 0x005345A0] set to mapTimeInTicks when the unit is chosen; age since it drives the selection
            // score Created by retype action
            int lastVisitedTick; // 0x00000330 length: 4
            undefined1 padding_0x334[2]; // 0x00000334 length: 2
            // Created by retype action
            short targetID_OR_targetBuildingID; // 0x00000336 length: 2
            // Workplace for workers, home house for children, kennel for cage dogs. Created by retype action
            short workplaceOrHomeBuildingID; // 0x00000338 length: 2
            short targetX_2; // 0x0000033A length: 2
            short targetY_2; // 0x0000033C length: 2
            // [168 0x00549C70] 0x54A625: set to the unit this unit fights (passed to processUnitAttackOtherUnit);
            // the opponent gets this unit's ID in its own field when it fights back - it is the own melee target,
            // not the attacker
            short meleeOpponentUnitID; // 0x0000033E length: 2
            // Value copied alongside attackedUnitID when melee starts (likely attacker UID); cleared with it
            int attackedUnitUID; // 0x00000340 length: 4
            short shootTargetedUnit; // 0x00000344 length: 2
            // Every use is a unit id (0=none) of the enemy being chased; units[it].huntedBy++; no movementType use
            // found Shared function sets it every X ticks, forcing this to 1 or 2 for the spearman for example will
            // result the spearman to run.
            short chaseTargetUnitID; // 0x00000346 length: 2
            // Woodcutter and apple farmer store tree index here. Created by retype action
            short workplaceTileOrTreeID; // 0x00000348 length: 2
            // Created by retype action
            short calculatedMovementSpeed; // 0x0000034A length: 2
            // Created by retype action
            short movementSpeed; // 0x0000034C length: 2
            undefined1 padding_0x34e[2]; // 0x0000034E length: 2
            // Value of moveTickCounter at the last movement step
            int lastMoveStepTick; // 0x00000350 length: 4
            // Tick counter for movement; a step happens when counter - lastMoveStepTick exceeds speed+delay
            int moveTickCounter; // 0x00000354 length: 4
            // [167 0x0053E820] set to 1 when committing a worker into a building, cleared by
            // clearHiddenFlagAndUpdatePosition; hidden units are skipped by getUnitInHitBox
            short isHiddenInBuilding; // 0x00000358 length: 2
            // [169 0x0054B0D0] stores the return value of EntityState::arrowShootingRelated for the chosen target
            short shotTrajectoryValue; // 0x0000035A length: 2
            // Ticks into current climb step (0..0x5f), reset on exiting ladder
            short climbStepTimer; // 0x0000035C length: 2
            // 0 - up, 1 - down
            short climbingDirection; // 0x0000035E length: 2
            // 1 - yes, 0 - no
            short unitCanClimb; // 0x00000360 length: 2
            // Created by retype action
            short stoneAmmunition; // 0x00000362 length: 2
            // Starts from 0, ticks up to 5. Ticks every time the animation is done playing.
            int climbingState; // 0x00000364 length: 4
            // trader horses store the trader unit uid here (0x541A4F compare verified); other units a building uid;
            // compound like workplaceOrHomeBuildingID
            int workplaceBuildingOrTraderUID; // 0x00000368 length: 4
            short traderHorsesTrader; // 0x0000036C length: 2
            short someUnitStat4; // 0x0000036E length: 2
            short cannotClimb; // 0x00000370 length: 2
            // Gates spawn fade-in and recruitment fade-out; not only disappearing.
            short isFadeActive; // 0x00000372 length: 2
            DestinationNeededEnumShort destinationNeeded; // 0x00000374 length: 2
            short unknownStateCopyClimbRelated; // 0x00000376 length: 2
            // Animation counter 0..15 stepping by 2 per move step
            short animCycle16By2; // 0x00000378 length: 2
            // Animation counter 0..11 stepping by 1 per move step
            short animCycle12; // 0x0000037A length: 2
            // Animation counter 0,2,..,12 (7 frames) advanced by 2 per move step
            short animCycle14By2; // 0x0000037C length: 2
            // Animation counter 0..15 stepping by 1 per move step (also gait window for hopGaitMode)
            short animCycle16; // 0x0000037E length: 2
            short substate; // 0x00000380 length: 2
            undefined1 padding_0x382[2]; // 0x00000382 length: 2
            uint fixedRng; // 0x00000384 length: 4
            // Created by retype action
            short resourceToDeposit; // 0x00000388 length: 2
            // Aim pitch (-1/0/1) for ranged units, lifetime ticks for juggler/fire eater; not juggler count.
            short aimPitchOrLifetimeTicks; // 0x0000038A length: 2
            short tunnelerFrame; // 0x0000038C length: 2
            short peasantAlwaysZero; // 0x0000038E length: 2
            undefined1 padding_0x390[2]; // 0x00000390 length: 2
            short seated; // 0x00000392 length: 2
            short resourcesGatheredCount; // 0x00000394 length: 2
            short workerIndex; // 0x00000396 length: 2
            short buildingID; // 0x00000398 length: 2
            // Set to 1 when the unit is chosen as a shoot target (acquireShootTarget), is the target of an active
            // entity (flagUnitsWithActiveEntity) or of certain attackers; cleared at the start of every updateUnits
            // pass.
            short targetedThisTick; // 0x0000039A length: 2
            // [117 0x00549090] carnival units reuse it as a step counter (0 wander, 1-4 act, 5 wander then reset to
            // 3/4), reset to 0 on fade-in 3 if automatic, 4 if user selected attack (explicit)
            UnitInstructionTypeShort targetingType_OR_performanceStep; // 0x0000039C length: 2
            // [135 0x00566750] the priest stores the unit to bless here (from selectNewBlessingTarget) and walks to
            // it
            short targetUnitId; // 0x0000039E length: 2
            int targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID; // 0x000003A0
                                                                                                      // length: 4
            short unkAttackRelated; // 0x000003A4 length: 2
            undefined1 padding_0x3a6[2]; // 0x000003A6 length: 2
            // Created by retype action
            uint targetedBuildingTile; // 0x000003A8 length: 4
            short lookForEnemy; // 0x000003AC length: 2
            short attackedBy; // 0x000003AE length: 2
            // Catapult/trebuchet: when 1 the next shot is a diseased cow instead of a rock (shootProjectile); set
            // for AI when yieldCowThrow allows it or by the tribe "throw cow" instruction for unit types 0x27/0x28.
            short throwCowNext; // 0x000003B0 length: 2
            short huntedBy; // 0x000003B2 length: 2
            // Created by retype action
            short digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300; // 0x000003B4 length: 2
            // on siege engines a rotating 0..15 index into unitScatterOffsetsXY advanced per probed tile, not an
            // engineer count (review 349); keeps dig-tile role
            short digTileY__OR__crewScatterSlotIndex; // 0x000003B6 length: 2
            int digTileTarget; // 0x000003B8 length: 4
            // Siege/ranged units: negative = retarget cooldown counted up to 0 (-0x28/-0x3c/-0x50 after a failed
            // target search) before acquiring again; positive = AI harass target tile chosen by
            // harassBuildingsWithSiegeAI.
            int retargetDelayOrSiegeTile; // 0x000003BC length: 4
            // Cleared together with retargetDelayOrSiegeTile when engineers are released from a siege tower or the
            // tribe gets a new instruction; no reader found.
            short manningReleaseUnk3c0; // 0x000003C0 length: 2
            // Animal units: 1 while the unit is in its lying/resting pose (rabbit state 0xcb, deer rest, cage dog
            // sleep gfx 0x278); deer play the get-up frame (gfx +0x101) and clear it, cage dogs pick the alternate
            // frame table while set; camel/lion clear it
            char restingPoseFlag; // 0x000003C2 length: 1
            // Created by Rename Structure Field action
            char rabbitMovementSlowdown; // 0x000003C3 length: 1
            // Engineer: 1 while he is operating his assigned building/siege machine (set by UpdateEngineer);
            // getActiveEngineerForBuilding only returns him then; cleared on new move orders.
            byte isManningBuilding; // 0x000003C4 length: 1
            // Queued targeting type copied into targetingType then cleared. Byte copy of the targeting/instruction
            // type given by the last order (3 none, 5 attack land, 9 attack building, 0x16 throw cow, 0x17 attack
            // wall, 0x22 light pitch), written together with targetingType; catapult/trebuchet restore
            // targetingType from it when it is 5 or 0x16 and then clear it
            byte pendingTargetingType; // 0x000003C5 length: 1
            // Animation counter 0..17 advanced by 1 per move step (updateUnits); added as frame*8 to gfxNumber for
            // 18-frame walk sheets
            short animCycle18; // 0x000003C6 length: 2
            int health; // 0x000003C8 length: 4
            int maxHealth; // 0x000003CC length: 4
            // [166 0x0053B8E0] set to 1 << (owner-1), or 0xFF when unowned
            byte ownerBitMask; // 0x000003D0 length: 1
            // ~occupancyOrFlag (complement of the owner's player bit 1<<(owner-1)); 0xff for owner 0 (same as
            // occupancyOrFlag then); set in setUnitValues, write-only in clean.exe
            byte occupancyClearMask; // 0x000003D1 length: 1
            // 0/1 flag set when an opponent is found mid-step; at the next tile boundary switches to
            // US_MELEE_ATTACK; not a step count (also added to step count as 0/1) Extra move steps added to
            // speedCategory in processUnitMove; while non-zero a step switches the unit into US_MELEE_ATTACK;
            // cleared by processMeleeInitiation.
            short pendingMeleeEngage; // 0x000003D2 length: 2
            // Short decremented each tick toward 0 (lion attack cooldown etc.); not a bool.
            short cooldownTicks; // 0x000003D4 length: 2
            // Knight's origin stables; engineer's pitch source building.
            short stablesOrPitchSourceBuildingID; // 0x000003D6 length: 2
            // Catapult shoots this many times before stopping automatically.
            short shootBeforeStop; // 0x000003D8 length: 2
            undefined1 padding_0x3da[2]; // 0x000003DA length: 2
            // Number of ranged units currently targeting this unit (rebuilt every tick from attackers'
            // lastShootTargetID); acquireShootTarget adds 50 per shooter to the target cost to spread fire.
            short shootersTargetingCount; // 0x000003DC length: 2
            // Unit ID last chosen as shoot target by acquireShootTarget; each tick it increments that target's
            // shootersTargetingCount.
            short lastShootTargetID; // 0x000003DE length: 2
            // [134 0x00564250] stores buildings[pitchBuilding].uid, which is passed to
            // getBuildingResourceAmountByUid/addResourceToStockpile(RT_PITCH) Created by retype action width from
            // machine code (int)
            int pitchSourceBuildingUid; // 0x000003E0 length: 4
            // Counts down to 0, if reaches 0, the unit is no longer blessed.
            int blessedAmount; // 0x000003E4 length: 4
            short attackAtTileX; // 0x000003E8 length: 2
            short attackAtTileY; // 0x000003EA length: 2
            byte firstNameIndex; // 0x000003EC length: 1
            // [204 0x0043C1E0] used as index into TEXT_PEASANT_SURNAMES right after firstNameIndex
            byte surnameIndex; // 0x000003ED length: 1
            // 0x55B153 toggles 0/1, pushed as processDamageToBuilding noDamage arg (thunk 0x409300): 1 = no damage;
            // current name inverted
            char wallHitNoDamageToggle; // 0x000003EE length: 1
            // Wood needed per item (fletcher bow/crossbow, poleturner spear/pike). Created by retype action
            undefined1 woodNeededPerProduct; // 0x000003EF length: 1
            // [UNK PASS] was killedFlagUnk
            short isDisbanded; // 0x000003F0 length: 2
            // Small per-unit counter: ox sets it to 1 once a full load (>=8) triggered the next state; deer
            // increment it on each flee start and scatter the herd above 10.
            short behaviourRepeatCounter; // 0x000003F2 length: 2
            // Set to 5 when fire blocks the next tile and 0x28 when re-planning fails; decremented while blocked.
            // Not fire-only Set to 5 when doMoveFromTileToTile refuses a step into fire; decremented on failed
            // steps, path index does not advance while > 0; civilians (healer, lady, mother, child, priest,
            // drunkard, jester, hunter dog) disappear when > 1.
            short blockedWaitCounter; // 0x000003F4 length: 2
            undefined1 padding_0x3f6[2]; // 0x000003F6 length: 2
            // Set when idle anim sees an attack order/enemy so the idle ends once; cleared after firing. Ranged
            // units: set to 1 in the idle/look-around state when an attack order is pending (raises
            // DAT_UnitAnimationFinished once); cleared after each shot and when a new target/order is given.
            // Set when idle anim sees an attack order/enemy so the idle ends once; cleared after firing. Ranged
            // units: set to 1 in the idle/look-around state when an attack order is pending (raises
            // DAT_UnitHasBecomeIdle once); cleared after each shot and when a new target/order is given.
            byte idleInterruptedForAttack; // 0x000003F8 length: 1
            // Created by retype action
            undefined1 laddermanIsInPosition; // 0x000003F9 length: 1
            byte fadeCounter; // 0x000003FA length: 1
            byte fadeType; // 0x000003FB length: 1
            short SA; // 0x000003FC length: 2
            byte unknownSiegeTentRelated02; // 0x000003FE length: 1
            // Recomputed in calculateUnitMovementSpeed: 1 while the unit stands on a keep building (types 41-44);
            // AI shooters treat such targets as 3x closer.
            byte isOnKeep; // 0x000003FF length: 1
            // Used to track stats after the unit dies.
            short lastEncounteredEnemyPlayerID; // 0x00000400 length: 2
            byte unknownCountdown_0x402; // 0x00000402 length: 1
            byte wasOnStoneGate; // 0x00000403 length: 1
            // set to the current tile when the next step tile is chosen (pairs with moveToTile)
            int moveFromTile; // 0x00000404 length: 4
            short counter; // 0x00000408 length: 2
            // When non-zero (fire watch, or once the unit was blocked by fire) doMoveFromTileToTile no longer stops
            // it in front of fire tiles.
            short ignoresFireBlocking; // 0x0000040A length: 2
            bool isMatchingSpeed; // 0x0000040C length: 1
            // Set from EntityState::isBrazierNearby; required to light pitch and switches arrows to fire arrows.
            // Crusader/Arabian archer: set to 1 when a brazier was nearby and a fire arrow (entity 0x5b/0x5c/0x5d)
            // was shot; never cleared or read in clean.exe (write-only)
            bool isNearBrazier; // 0x0000040D length: 1
            // Forces the ranged unit to release its shot this tick regardless of animation frame (set for AI pitch
            // lighting); cleared when the shot is fired.
            bool fireImmediately; // 0x0000040E length: 1
            // caller 0x53D288 pushes it; incremented per failed target search, reset on success, >0xF stops
            // catapults: a retry counter offsetting the facing
            char attackDirectionAttemptCount; // 0x0000040F length: 1
            // Quarry ox/worker: set to 8 when no stone was available, decremented per pickup; while non-zero
            // findQuarryPileThatIsCloseAndHasMostStone favours piles with more stone.
            byte preferFullPileCount; // 0x00000410 length: 1
            // 99 means processed, else 0
            byte lordDeathProcessedStatus; // 0x00000411 length: 1
            byte ownerOfAssassinScaledObject; // 0x00000412 length: 1
            // Assassin: 1 while throwing the hook / scaling a wall (US_ASSASSIN_THROWING_HOOK /
            // US_ASSASSIN_CLIMBING_UP), cleared on idle/move/landing; such units are skipped by tribe move/attack
            // orders and blocking checks
            byte isAssassinHookClimbing; // 0x00000413 length: 1
            short assassinHeightDifference; // 0x00000414 length: 2
            // [145 0x00575820] Horse archer stores the facing toward its shoot target here while facingDirection is
            // restored to the movement direction; used to pick the shooting overlay sprite.
            short shootAimDirection; // 0x00000416 length: 2
            // Assassin: extra height added to buildingHeight in recomputeUnitStandingHeight while climbing; reset
            // to 0 on idle/move.
            short climbHeightOffset; // 0x00000418 length: 2
            // Assassin climbing rope overlay blend/alpha (set to 0x20) passed to renderGMWithBlending in
            // renderAssassinClimbingOverlay.
            undefined2 climbOverlayBlend; // 0x0000041A length: 2
            // Screen X of the assassin climbing overlay, stored by renderMap.
            int climbOverlayScreenX; // 0x0000041C length: 4
            // Screen Y of the assassin climbing overlay, stored by renderMap.
            int climbOverlayScreenY; // 0x00000420 length: 4
            short horseArcherShootingVariation; // 0x00000424 length: 2
            short horseArcherShootCheckInterval; // 0x00000426 length: 2
            // Animation counter 0..23 advanced by 1 per move step (updateUnits); added as frame*8 to gfxNumber for
            // 24-frame walk sheets
            short animCycle24; // 0x00000428 length: 2
            // 0x16 is harrassing siege engine for example.
            short aiUnitBehaviourType; // 0x0000042A length: 2
            short rallyRelatedFlag; // 0x0000042C length: 2
            // [030 0x004D2500] set to 1 here on the engineer recruited for oil smelter duty
            short isOilDutyEngineer; // 0x0000042E length: 2
            // Set to 1 every tick by the ranged unit updates (archers, crossbowmen, slingers, fire throwers, horse
            // archers); computeTribePercentages counts such units in aim/reload/fire state.
            short isRangedUnit; // 0x00000430 length: 2
            short siegeTargetPlayerID; // 0x00000432 length: 2
            // ==1 selects sprite 0xCD (GM_BODY_ARABIC_LORD) and FX_ARAB_LORD_KILL; both uses = Arabian lord flag
            short isArabLord; // 0x00000434 length: 2
            // set to the attacking unit on every enemy hit, cleared for fire damage (3 batches agree) Created by
            // retype action
            short lastAttackerUnitID; // 0x00000436 length: 2
            // [UNK PASS] was assassinsMicroDistanceToEnemyUnk
            int assassinNearestSelectableEnemyDistance; // 0x00000438 length: 4
            // [170 0x00579300] used as bitmask: (totalGameTicks & m) == (fixedRng & m) gates the nearest-enemy
            // search
            int enemyScanIntervalMask; // 0x0000043C length: 4
            // Incremented every calculateUnitMovementSpeed call; (value+unitID) & 7 / & 3 throttles how often the
            // speed is recomputed.
            ushort speedRecalcTick; // 0x00000440 length: 2
            // Set to 1 by processFireDamageToUnit; processUnitLossStatistic then does not add the kill to the
            // killer's finalTroopsKilledWeighted.
            short hitByFire; // 0x00000442 length: 2
            // [UNK PASS] was idleCounterUnk
            short assassinIdleTicks; // 0x00000444 length: 2
            // Created by retype action [UNK PASS] was moveableUnk
            short isMovable; // 0x00000446 length: 2
            // Counts hits on own-team walls/buildings, reset on enemy hit.
            short friendlyStructureHitCount; // 0x00000448 length: 2
            short maxHealthRatingLord; // 0x0000044A length: 2
            short cagedogReleaseCheckMoment; // 0x0000044C length: 2
            undefined1 padding_0x44e[66]; // 0x0000044E length: 66

        } Unit;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(Unit) == 1168, Unit);
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
