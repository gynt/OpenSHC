/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Entities/Entity.hpp'
*/

#pragma once

#include "OpenSHC/Map/Entities/EntityTypeShort.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using OpenSHC::Map::Entities::EntityTypeShort;

#pragma pack(push, 1)
        // SIZE: 0x000000E8
        typedef struct Entity {

            int graphicType2; // 0x00000000 length: 4
            short graphicType2RelatedOffset; // 0x00000004 length: 2
            short gmID; // 0x00000006 length: 2
            // [UNK PASS] was colorUnk
            int ownerColorIndex; // 0x00000008 length: 4
            short x1; // 0x0000000C length: 2
            short y1; // 0x0000000E length: 2
            // [077 0x004087C0] threshold for field7_0x12 before unknownAnimationFrameRelated advances
            short ticksPerAnimFrame; // 0x00000010 length: 2
            // Ticks spent on current animation frame; when >= frame duration (unkOne_1) the frame advances and this
            // resets
            short animFrameTickCounter; // 0x00000012 length: 2
            // Incremented once per ticksPerFrame; also used as lifetime gauge (<1001) for poison clouds, i.e.
            // elapsed frame count.
            short animFrameCounter; // 0x00000014 length: 2
            // [072 0x00401D20] effect ends when unknownAnimationFrameRelated reaches it; also the divisor of the
            // progress value in UpdateArrowsSecondaryEntity
            short animFrameCount; // 0x00000016 length: 2
            short originX; // 0x00000018 length: 2
            short originY; // 0x0000001A length: 2
            // Direction 0..15 = orientation-0x3c adjusted by map orientation; used to pick rotated sprite frames
            short screenDirectionIndex; // 0x0000001C length: 2
            short nextEntityOnThisTileByID; // 0x0000001E length: 2
            short imageID; // 0x00000020 length: 2
            byte unused_0x22[6]; // 0x00000022 length: 6
            // Created by retype action
            short logicalState; // 0x00000028 length: 2
            // verified
            EntityTypeShort entityType; // 0x0000002A length: 2
            // Created by retype action
            short owner; // 0x0000002C length: 2
            byte unused_0x2e[2]; // 0x0000002E length: 2
            int uid; // 0x00000030 length: 4
            // GameCore.mapTimeInTicks when the entity was spawned
            int spawnTick; // 0x00000034 length: 4
            // Created by retype action
            short microX; // 0x00000038 length: 2
            // Created by retype action
            short microY; // 0x0000003A length: 2
            short height; // 0x0000003C length: 2
            // Created by retype action
            short targetX; // 0x0000003E length: 2
            // Created by retype action
            short targetY; // 0x00000040 length: 2
            // Created by retype action
            short targetZ; // 0x00000042 length: 2
            // Created by retype action
            short xPosition; // 0x00000044 length: 2
            // Created by retype action
            short yPosition; // 0x00000046 length: 2
            byte unused_0x48[4]; // 0x00000048 length: 4
            int tile; // 0x0000004C length: 4
            // Created by retype action
            short x_2; // 0x00000050 length: 2
            // Created by retype action
            short y_2; // 0x00000052 length: 2
            // Created by retype action
            short startingHeight_2; // 0x00000054 length: 2
            // Created by retype action
            short height_2; // 0x00000056 length: 2
            // Created by retype action
            short startingHeight; // 0x00000058 length: 2
            // Per-entity-type value copied from EntityDefinedData table at +0x284 (field6_0x270[type+5]) in
            // setProjectileEntityValues2; values e.g. 350 (types 1,2,7), 480 (3,4), 500, 250, 150, 80; never read
            // back
            short projectileParam5a; // 0x0000005A length: 2
            // Target micro X of the Bresenham flight line (set in initializeProjectileVelocities / wall bounce)
            short lineTargetMicroX; // 0x0000005C length: 2
            // abs(targetX - x) of the projectile flight line (micro units)
            short lineDeltaX; // 0x0000005E length: 2
            // [074 0x00402AE0] per-step +-1 added to microX
            short stepX; // 0x00000060 length: 2
            // Target micro Y of the Bresenham flight line
            short lineTargetMicroY; // 0x00000062 length: 2
            // abs(targetY - y) of the projectile flight line (micro units)
            short lineDeltaY; // 0x00000064 length: 2
            // [074 0x00402AE0] per-step +-1 added to microY
            short stepY; // 0x00000066 length: 2
            // abs(targetZ - height) at launch
            short lineDeltaZ; // 0x00000068 length: 2
            // angleToRotationFrameIndex(startingAngle); vertical-angle sprite row (graphic = idx*16 + direction);
            // <3 = shallow
            short pitchFrameIndex; // 0x0000006A length: 2
            // fire entities: burn cycle counter (+2, ends > 8); projectiles: impact linger countdown (1 on hit,
            // 0x28 on miss), counted down by callbacks Burning?
            short burnCyclesOrImpactCountdown; // 0x0000006C length: 2
            // Bresenham increment 2*minorDelta used by updateEntityMicroMovement
            short lineStepIncMinor; // 0x0000006E length: 2
            // Bresenham increment 2*minorDelta - 2*majorDelta
            short lineStepIncMajor; // 0x00000070 length: 2
            // Bresenham error accumulator (init 2*minor - major)
            short lineStepError; // 0x00000072 length: 2
            // Line type: 0 none (no movement), 1 vertical (dx=0), 2 horizontal (dy=0), 3 Y-major, 4 X-major
            short lineStepMode; // 0x00000074 length: 2
            byte unused_0x76[2]; // 0x00000076 length: 2
            // float flight-time accumulator t (fld/fstp, [esi+0x8C] = +0x78): distance vCos*t/4, height
            // vSin*t-4.906t^2; not a speed
            int flightTime; // 0x00000078 length: 4
            // v_0 * cos( startingAngle )
            float vCos; // 0x0000007C length: 4
            // v_0 * sin( startingAngle )
            float vSin; // 0x00000080 length: 4
            // on x-y plane
            short travelledDistance; // 0x00000084 length: 2
            byte field56_0x86[2]; // 0x00000086 length: 2
            int orientation; // 0x00000088 length: 4
            // Distance from computeLineOfSightDistance; collisions ignored until travelledDistance > half of it
            short lineOfSightDistance; // 0x0000008C length: 2
            undefined1 padding_0x8e[2]; // 0x0000008E length: 2
            // Created by retype action
            int heightDifference; // 0x00000090 length: 4
            // Copy of the initial line-of-sight distance (written only)
            short lineOfSightDistanceInit; // 0x00000094 length: 2
            // projectiles: launch speed (computeVelocity); dust: microY drift period; poison: move timer. Parallels
            // moveDirOrDriftXOrLaunchPitch; replaces Unk
            short launchSpeedOrDriftPeriodY; // 0x00000096 length: 2
            float _elapsedTimeOrGravityAccumulator; // 0x00000098 length: 4
            // projectiles: launch pitch in degrees (t == 0 branch, review 320 x87 check); clouds: move direction /
            // drift period; keeps all roles [077 0x004087C0] poison cloud uses it as 8-way direction index; dust
            // cloud uses it as signed X step divisor projectile motion
            short moveDirOrDriftXOrLaunchPitch; // 0x0000009C length: 2
            // projectiles store current pitch (mov [esi+0xB2],ax at 0x4085BE = +0x9E); poison clouds use it as
            // random-walk countdown [077 0x004087C0] cow poison cloud: decremented, when <1 reloaded with random
            // 0..63 and startingAngle set to random 0..7 direction
            word wanderCountdownOrPitchDegrees; // 0x0000009E length: 2
            short unitID; // 0x000000A0 length: 2
            // Created by retype action
            short unitID_OR_seaGullID; // 0x000000A2 length: 2
            undefined1 padding_0xa4[2]; // 0x000000A4 length: 2
            short gmLookupValue; // 0x000000A6 length: 2
            // Set to 1 in activateProjectileEntity
            short projectileActivated; // 0x000000A8 length: 2
            EntityTypeShort entityType2; // 0x000000AA length: 2
            int rng_1; // 0x000000AC length: 4
            // 0..0x1f fade/shade ramp or -1; removal at >30 is the end of the same ramp.
            short fadeLevel; // 0x000000B0 length: 2
            // [076 0x00407190] set to 1 when the cow splat effect is played (once); nonzero also suppresses the
            // wall bounce of arrows
            short impactEffectDone; // 0x000000B2 length: 2
            // [073 0x00402900] for flags selects which frame table (wave strength 0..3) is used and is set from
            // wind/AI mood; for fire it is the burn phase
            short animState; // 0x000000B4 length: 2
            // [073 0x00405130] fire strength 1..5: raised to the new level when refreshed, decremented by 1 per
            // spread, picks fade level and frame tables in UpdateFireEntity
            short fireLevel; // 0x000000B6 length: 2
            // Fire entity: next neighbour direction (0..3: -x,+x,+y,-y) to try spreading fire to; incremented each
            // attempt
            short fireSpreadDirIndex; // 0x000000B8 length: 2
            // Initialised from lineOfSightClearanceSteps and decremented per step; while >0 the projectile does not
            // bounce off walls
            short losClearanceStepsLeft; // 0x000000BA length: 2
            // [075 0x00404AE0] 1/2 marks fire-arrow/fire-bolt variants (gmID 0x91); seagulls get a random 120..219
            // and heads-on-spikes 300..799 - not an RNG value
            short variantOrLifetime; // 0x000000BC length: 2
            // Popup entity (types 0x28-0x2b): GM sprite sheet of the icon (0x2e)
            short popupIconGmID; // 0x000000BE length: 2
            // Popup icon frame within popupIconGmID; non-zero marks the entity as an icon+number popup in renderMap
            // (types 0x28-0x2b use 0xab/0x82..., gold/popularity popups 0x8d+2*n)
            short popupIconFrame; // 0x000000C0 length: 2
            byte unused_0xc2[2]; // 0x000000C2 length: 2
            int displayValue; // 0x000000C4 length: 4
            // Screen X offset of popup icon
            short popupIconOffsetX; // 0x000000C8 length: 2
            // Screen Y offset of popup icon
            short popupIconOffsetY; // 0x000000CA length: 2
            // Screen X offset of the popup number (displayValue)
            short popupNumberOffsetX; // 0x000000CC length: 2
            // Screen Y offset of the popup number
            short popupNumberOffsetY; // 0x000000CE length: 2
            // 1 when spawned as ET_FIREBALLISTA (converted to ballista type); damage code checks it
            short isFireBallistaBolt; // 0x000000D0 length: 2
            short unitID_healer; // 0x000000D2 length: 2
            int unitUID; // 0x000000D4 length: 4
            short fireIntensity; // 0x000000D8 length: 2
            // Entity index validated with uidRef; poison-cloud link is one instance of the generic link.
            short linkedEntityID; // 0x000000DA length: 2
            // [074 0x00401910] uid of the entity stored in unknownDistanceRelatedValue
            int linkedCloudUID; // 0x000000DC length: 4
            byte unused_0xe0[8]; // 0x000000E0 length: 8

        } Entity;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(Entity) == 232, Entity);
    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
