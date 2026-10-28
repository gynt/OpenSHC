/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Entities/EntityState.hpp'
*/

#pragma once

#include "OpenSHC/IO/PackagedFileMagicNum.hpp"
#include "OpenSHC/Map/Entities/Entity.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Entities/ExtraEntityInfo.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "WinDef.h"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using OpenSHC::IO::PackagedFileMagicNum;
        using OpenSHC::Map::Entities::Entity;
        using OpenSHC::Map::Entities::EntityType;
        using OpenSHC::Map::Entities::ExtraEntityInfo;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

        // SIZE: 0x000AC5E8
        class EntityState {
        public:
            undefined4 totalEntityCount; // 0x00000000 length: 4
            undefined4 maxEntityCount; // 0x00000004 length: 4
            // [075 0x00404AE0] used as the start index of the free-slot scan and set to the allocated ID
            undefined4 nextFreeEntitySearchStart; // 0x00000008 length: 4
            int lineOfSightClearanceSteps; // 0x0000000C length: 4
            undefined4 fireCount; // 0x00000010 length: 4
            Entity entityArray[3000]; // 0x00000014 length: 696000
            ExtraEntityInfo seagullArray[100]; // 0x000A9ED4 length: 10000
            DWORD classConstructionTime; // 0x000AC5E4 length: 4

        private:
            EntityState(EntityState const&);
            void operator=(EntityState const&);

        public:
            EntityState() {};
            ~EntityState() {};

            // Constructor
            /**
             * EntityState constructor: stores timeGetTime() as construction time, clears the entity and seagull
             * arrays and zeroes fireCount.
             */
            EntityState* Constructor_EntityState();

            /**
             * Zeroes totalEntityCount, clears 3000 entity records (0xe8 bytes each at 0x2350314) and 100 seagull
             * records (100 bytes each at 0x23fa1d4), then sets maxEntityCount = 3000 and every10Ticks = 25.
             */
            void clearEntityArrayAndSeagullArray();

            /**
             * Returns TRUE if the player owns an entity of the given type with nonzero logicalState. For types
             * 0x28/0x29 (popups) it also returns TRUE while playerData.popupEntity40Cooldown/someCount33 (cooldown) is
             * nonzero. NOTE (verified in machine code: cmp edx,0x19 / jl): the scan only covers entity slots 1..24,
             * not the whole 3000-entry array.
             */
            BOOLEnum playerHasEntityOfType(int playerID, EntityType entityType);

            /**
             * Initializes graphic/physics fields of entity entityID for type entityType from the EntityDefinedData
             * per-type tables: gm id, graphic offset, origin (from the GM header), velocity (curve types 0/6/9 ->
             * velocityUnk) or starting angle (other curve types), gravity accumulator, gmLookupValue. Then applies
             * hardcoded origin corrections to types 10-15: FLAG_1/BRAZIER/HEADS_ON_SPIKES (-1,-7), FLAG_4 (-1,-2),
             * FLAG_2 (+8,-8), FLAG_3 (+8,-7) (the switch case labels are mis-rendered enum names of entityType-10).
             */
            void setProjectileEntityValues2(int entityID, EntityType entityType);

            /**
             * Sets type, gmLookupValue, gm id, graphic offset, origin (from GM header) and two animation parameters
             * of entity entityID from the EntityDefinedData tables indexed by gmLookupValue; lookup value 1 gets
             * hardcoded values (unkThree_1=5, unkOne_1=3, unkMinusOne=16).
             */
            void setEntityParameters(int entityID, undefined4 entityType, int gmLookupValue);

            /**
             * NAME? Draws nothing: it only sets entity entityID's graphicType2, type, gm id (=graphicType1) and
             * origin from the GM header, plus two animation parameters (special values for gm 0x87). Better name:
             * setEffectEntityGraphic.
             */
            void drawEntityEffect(int entityID, undefined4 entityType, int graphicType1, int graphicType2);

            /**
             * If entityID > 0, marks the entity for removal (logicalState=3) and sets someCounter_OR_hitGround=10.
             */
            void markEntityDestroyed(int entityID);

            /**
             * Per-tick decay counter: increments entity's unkMinusOne; once it exceeds 30 the entity is marked for
             * removal (logicalState=3).
             */
            void tickEntityDecayCounter(int entityID);

            /**
             * NAME? Unlinks entity entityID from the per-tile entity linked list of its tile (EntityLayerLT25 byte
             * list for IDs < 25, EntityLayer otherwise), walking at most 100 nodes; clears the entity's next link.
             * Better name: unlinkEntityFromTile.
             */
            void unlinkEntityFromTile(uint entityID);

            /**
             * Walks the entity linked list of tile and returns the first entity of type ET_FIRE, or 0 if none.
             */
            int getFireEntityIDAtTile(int tile);

            /**
             * NAME? Walks up to 9 entities on tile's entity list; every ET_FIRE entity gets someTracker=2,
             * fireParameter_0xb6=1 and animation frame reset (put out). Always returns 0. Called only by
             * extinguishBuildingFire; better name: extinguishFiresAtTile.
             */
            int updateAllFireEntitiesAtTile(int tile);

            /**
             * Applies fire damage (processFireDamageToUnit with playerID and intensity flag) to every unit in
             * tile's unit linked list.
             */
            void processFireDamageToUnitsAtTile(int tile, int playerID, int fireLowIntensity);

            /**
             * Recounts active fire entities (logicalState 2, ET_FIRE) into fireCount and sets bit (owner-1) in
             * OccupancyLayer of each fire's tile.
             */
            void recountActiveFires();

            /**
             * For each active entity (logicalState 2) with a positive unitID, sets that unit's field233_0x39a to 1
             * (unit has an attached active entity).
             */
            void flagUnitsWithActiveEntity();

            /**
             * For healer unitID: returns the ID of the nearest active disease cloud (entity type
             * ET_DISEASE_CLOUD, unknownAnimationFrameRelated < 1001, unknownDistanceRelatedValue == 0, i.e. not
             * linked to another cloud) that is not claimed by a healer (claiming id + uid) currently in aim/fire
             * state, and that is reachable (same PathConnectionLayer area or navigable for the healer's owner).
             * Outside GM_SOLITARY, if the healer has a workplace building the cloud must also be closer than 31 to
             * it. Stale claims are cleared; returns 0 if none.
             */
            int findNearestDiseaseCloudForHealer(int unitID);

            /**
             * NAME? Every active poison cloud (frame < 1001) within axis distance < 7 of unit unitID gets its frame
             * counter (unknownAnimationFrameRelated) set to 1016, past the 1001 activity threshold; UpdateHealer
             * calls it after curing a cloud, so it ends the nearby clouds too. Better name:
             * dispelPoisonCloudsNearUnit.
             */
            void refreshPoisonCloudNearUnit(int unitID);

            /**
             * Called by UpdateHealer right after a healer claims cloud claimedCloudID: every other active (frame <
             * 1001) poison cloud that is unclaimed (unitID_healer 0) and not yet linked, within axis distance < 7
             * of the claimed cloud, is linked to it by storing claimedCloudID and its uid in
             * unknownDistanceRelatedValue / uidRef.
             */
            void assignPoisonCloudTargetEntity(int claimedCloudID);

            /**
             * If tile has MiscDisplayLayer bit 0x1000, marks every active flag/brazier/heads-on-spikes entity on
             * that tile for removal (logicalState=3) and clears the bit.
             */
            void destroyEntitiesOnTile(int tile);

            /**
             * Returns 1 if an active brazier entity is within axis distance < 4 of (unitX, unitY) and within 45
             * height units of unitZ, else 0.
             */
            undefined4 isBrazierNearby(int unitX, int unitY, int unitZ);

            /**
             * Changes the owner of every active entity (IDs 1..2999) owned by fromPlayerID to toPlayerID.
             */
            void reassignEntitiesOwner(int fromPlayerID, undefined4 toPlayerID);

            /**
             * Swaps ownership of active entities (IDs 1..2999) between playerA and playerB.
             */
            void swapEntityOwnership(int playerA, int playerB);

            /**
             * Marks every active entity (IDs 1..2999) owned by playerID for removal (logicalState=3); used when a
             * player is destroyed.
             */
            void destroyEntitiesPart2(int playerID);

            /**
             * Advances entity microX/microY by one Bresenham step according to the line mode in field50_0x74 (1 y
             * only, 2 x only, 3 y-major, 4 x-major), using someMicroX/Y as step signs and field49_0x72 as the error
             * term. A seagull already at its target (targetZ 0) doesn't move.
             */
            void updateEntityMicroMovement(int entityID);

            /**
             * Maps a projectile pitch angle in degrees (about -90..90) to one of 9 rotation frame indices (0..8, 4
             * = near horizontal).
             */
            undefined4 angleToRotationFrameIndex(int angleDegrees);

            /**
             * NAME? Solves the ballistic equation for the launch angle: tan = v^2/(g*D) -/+ sqrt(v^4/(g^2*D^2) -
             * 2*v^2*h/(g*D^2) - 1), with g=9.812, D=4*horizontalDistance, h=heightDifference/2; each root is
             * converted to whole degrees (1000 if invalid/NaN). Returns the smaller angle, the larger one if the
             * smaller is below -90, or 45 if neither is within -90..90. entityType is unused. Better name:
             * computeLaunchAngle.
             */
            int computeLaunchAngle(int entityType, double launchSpeed, int horizontalDistance, int heightDifference);

            /**
             * Computes the launch speed needed to hit a target at horizontalDistance (scaled x2) and
             * heightDifference (/4) when firing at angleDegrees, with g = 9.812: sqrt(g*(2d)^2/cos^2 / (2d*tan -
             * h/4)), truncated to int. param_2 (entity type in the sibling computeLaunchAngle) is unused.
             */
            int computeVelocity(int unusedEntityType, double angleDegrees, int horizontalDistance, int heightDifference);

            /**
             * Walks a Bresenham line from (x,y,height) to (targetX,targetY,targetHeight) in 1/8-tile units (start
             * height +10 if the start tile has LogicLayer bit 0x10000000). On every odd step (unless
             * skipObstacleChecks != 0) it compares the obstacle top height of the current tile
             * (getObstacleTopHeightAtTile) with the linearly interpolated line height and returns 0 if blocked. The
             * first clearance/2 checks are skipped (clearance 100 if the shooter is more than 54 above the target,
             * capped to 28 for straight lines or when a tile 1..3 tiles before the target is higher than
             * targetHeight); tiles of the start building are ignored while the line is still on tiles with
             * LogicLayer bits 0x400300. Returns the step count reaching the target (1000 cap; 100000 if start ==
             * target). DAT_EntityState.lineOfSightClearanceSteps is set to the clearance, then overwritten with
             * each checked step whose tile lacks bits 0x400300.
             */
            uint computeLineOfSightDistance(
                int x, int y, int height, int targetX, int targetY, int targetHeight, int param_7);

            /**
             * Computes the entity's screen draw offset (x1, y1) from its sub-tile position (microX/microY & 7) via
             * an 8x8 table of (x,y) short pairs in EntityDefinedData.microPosDrawOffsets; depending on mapOrientation
             * (0/4: sub-X selects the column, Y the row, mirrored for 4; 2/6/other: X selects the row, Y the
             * column, 2 mirrors X, 6 mirrors Y).
             */
            void calculateEntityDrawOffset(int entityID);

            /**
             * Sets up Bresenham line state for seagull seagullID from (startX,startY) to (targetX,targetY): step
             * signs, lineStepMode (0 none, 1 vertical, 2 horizontal, 3 y-major, 4 x-major), lineStepsLeft = major-
             * axis length, and for modes 3/4 lineStepIncMinor/lineStepIncMajor and the initial lineStepError.
             */
            void initializeSeagullMovementVector(int seagullID, int startX, int startY, int targetX, int targetY);

            /**
             * Unlinks entity entityID from the EntityLayer linked list of its tile (nextEntityOnThisTileByID
             * chain), walking at most 100 nodes; same as the >=25 branch of doSomethingWithOtherEntitiesOnTile.
             * Used by save-version upgrade code.
             */
            void removeEntityFromTileLinkedList(int entityID);

            /**
             * Activates a pending projectile entity: logicalState=2, field72_0xa8=1, then initializes its values
             * for its stored type entityType2 via setProjectileEntityValues2.
             */
            int activateProjectileEntity(int entityID);

            /**
             * Deletes entity entityID: unlinks it from its tile list, then zero-fills its 0xE8-byte Entity record.
             */
            void deleteEntity(uint entityID);

            /**
             * Sets up the flight of projectile entityID from (x,y,height) to (targetX,targetY,targetZ): stores
             * |dx|,|dy|,|dz| (dz from the entity's own height/targetZ), the line end, step signs and Bresenham line
             * state (step mode 3/4 with minor/major increments and error), then sets launch angle and speed by the
             * type's curve type: 0/6 keep the launch speed (6 forces 125 when the line length > 150) and solve the
             * angle with computeLaunchAngle; 1 keeps the angle and solves the speed with computeVelocity; 2
             * likewise (angle 3 when the target is below, retried with angle 15 if speed < 1); 3/4/5/8 pick random
             * angle/speed from rng_1 (8 depends on unitID_OR_seaGullID and for IDs other than 0 and 5 scales the
             * gravity accumulator by 0.75); 9 angle 0. Line lengths come from computeLineOfSightDistance with
             * checks disabled. Curve types 4, 5, 7 and 10 return early; all others may set impactEffectDone for
             * arrows/bolts aimed more than 54 above the shooter (rng_1 % 10 == 5), reset
             * flightTime/travelledDistance and precompute vCos/vSin and the pitch frame.
             */
            void initializeProjectileVelocities(
                int entityID, int x, int y, int height, int targetX, int targetY, int targetZ);

            /**
             * Bounces projectile entityID off a wall/tower. From the wall flags of its tile
             * (setBitFlagBasedOnWallTowerGatehouseOrKeep), its sub-tile position and travel orientation it picks a
             * new target: the launch point (x_2,y_2) mirrored across the current position on the X or Y axis, or
             * the launch point itself for straight orientations (0x3C/0x40/0x44/0x48) and corner hits ((0,0) for
             * unknown orientations). It rebuilds orientation and Bresenham line state, sets the pitch from
             * wanderCountdown (clamped to >= -80), divides the speed by 8, restarts from the current height
             * (startingHeight, travelledDistance 0), recomputes vCos/vSin and pitchFrameIndex, clears gmLookupValue
             * and plays FX_ARROW_BOUNCE.
             */
            void handleProjectileWallBounce(int entityID);

            /**
             * NAME? Checks line of sight between two points in both directions: returns
             * computeLineOfSightDistance(src->dest) with obstacle checks, or the reverse direction if the first is
             * blocked; 0 means blocked both ways. Better name: lineOfSightEitherDirection.
             */
            int arrowShootingRelated(
                int microX, int microY, int height, int destMicroX, int destMicroY, int destHeight);

            /**
             * Allocates and initializes an entity slot; returns its ID or 0. Types 0x2C..0x5A and > 0x5E are
             * rejected; type -1 uses scratch slot 0 as type 8 (no hit check/callback). Types 0x28..0x2B use
             * reserved slots 1..24. Others scan from nextFreeEntitySearchStart; when no slot below 2999 is free,
             * projectile-like types evict the first fire/dust/debris (ET_FIRE/ET_DUST_CLOUD/0x1B/0x1E/0x1F) entity
             * from slot 25 up (reusing a free slot if found first), others fail and park the cursor at 2999.
             * Projectile types are rejected unless start and target lie on valid map tiles. Flaming variants are
             * remapped: 0x5B/0x5D -> arrow and 0x5C/0x5E -> type 0x18 with variantOrLifetime 1/2 (then gmID 0x91),
             * fire ballista -> ballista with isFireBallistaBolt; these and firethrowers get gmLookupValue 1. Sets
             * position, target, owner, uid (slots >= 25), flag colour (ET_FLAG_1..4), attachedUnitID (for dust
             * clouds 1 means frame 200) and RNG values (heads-on-spikes: lifetime 300..799 and rng_1 =
             * ownerColorUnk; seagull lifetime 120..219; type 8: rng_1 = the unit's fixedRng), then runs
             * initializeProjectileVelocities, maps helper types 0x18/0x19/0x23/0x24 back, and for ID != 0 runs the
             * first hit check, the draw offset and the type's EntityCallbacks entry with DAT_CurrentEntityID
             * temporarily set.
             */
            uint spawnEntity(int unitID, undefined4 playerID1, uint ownerColorUnk, int microX, int microY,
                int totalHeight, int targetX, int targetY, int targetZUnk, EntityType entityType, int param_11);

            /**
             * Resets projectile entityID's current/start position to (x,y,height) and its target to
             * (targetX,targetY,targetZ), updates heightDifference and orientation, then reinitializes its
             * velocities; used to retarget seagulls.
             */
            void setProjectileTargetPosition(
                int entityID, int x, int y, int height, int targetX, int targetY, int targetZ);

            /**
             * When a projectile hits a wall: depending on its orientation (0x3C..0x4B) and the wall flags of its
             * tile (same logic as handleProjectileWallBounce) picks a debris target = the launch point (x_2,y_2)
             * itself, or that point reflected through the impact point along x (2*microX - x_2) or along y
             * (2*microY - y_2); for orientations outside 0x3C..0x4B the target stays (0,0). Spawns 5 + rng_1 % 8
             * type-0x1B debris entities from the impact point toward that target (target height 8; spawnEntity
             * scatters each target by up to +-160), then one type-0x1E entity at the impact point (target x+1,y+1,
             * same height).
             */
            void spawnProjectileImpactDebris(int entityID);

            /**
             * Allocates a seagull slot (first free of 1..99; occupied slots whose entity uid no longer matches are
             * zeroed but not reused in this call; returns 0 when none is free), sets slotState 2,
             * position/centre/destination (x,y), random angle (rand % 360) and angle_2 (high byte of rand, 0..127),
             * circleRadius 24..39, numberBetween60And100 60..99, circle direction someAngle +-1 and angle2Step +-1,
             * circlePhase -20, rngMax799_countdown 400, an empty movement vector (start == destination) and
             * lineStepDelay 5. Advances angle by 20*someAngle with an inverted wrap (original bug: adds 360 when >=
             * 360, subtracts 360 when < 0), then spawns the ET_SEAGULL entity at (x,y) height 250 aimed at the
             * point circleRadius*(sin,cos)(originalAngle-180) away, links it (entityID/entityUID), stores the
             * current random number and returns the seagull ID.
             */
            int createSeagull(int x, int y);

            /**
             * Per-tick update of one seagull (seagullArray[seagullID], driving entity seagullArray.entityID). Dive
             * countdown someCountDown: while running it returns early; when it hits 0 the gull resurfaces (target =
             * own position, FX_GULL_SURFACE). When the entity is within 3 micro units of its target: if
             * (randomNumber ^ rng_1 ^ rand) % 500 == 123 and both its tile and the tile at +stepX/stepY have
             * LogicLayer bit 0 set (water), it dives (target height 0 at the next position, FX_GULL) for 0xa0 ticks
             * and returns; otherwise it circles - advances angle by someAngle*20 deg, on each lap wrap changes
             * circleRadius by +1 (circlePhase < 0) or -1 (circlePhase > 0), clamped 24..80, with circlePhase
             * cycling -20..19 and a 1/5 FX_GULL chance; moves the orbit centre (x_2,y_2) = (x,y) + angle_2 offset
             * of radius numberBetween60And100 and retargets the entity via setProjectileTargetPosition. The centre
             * (x,y) walks towards (x_3,y_3) one step every 10 ticks (lineStepDelay) while lineStepsLeft > 0, using
             * lineStepMode (1: y only, 2: x only, 3: y-major Bresenham, 4: x-major Bresenham). Apparent original
             * bug: in mode 4 the minor branch (lineStepError <= 0) adds the driving entity's stepX instead of
             * lineStepDirX (machine code 0x406F3C). When the destination is reached or the steps are used up, waits
             * rngMax799_countdown, then resets it to 400..799 and picks a new sea tile 400..599 away with
             * findFurthestSeaTile + initializeSeagullMovementVector.
             */
            void processSeaGulls(int seagullID);

            /**
             * Recomputes an entity's xPosition/yPosition/tile from its micro position, resolves its interaction
             * with the map, then links it into the tile entity list (EntityLayerLT25 for ids 1..24, else
             * EntityLayer; id 0 is never linked). Seagulls are linked only on a valid, non-LogicLayer&0x30 tile
             * with height > 0 (else tile = 0, return 0); off-map -> logicalState 3, LogicLayer&0x30 -> destroyed.
             * Decorations (types 10..15) set MiscDisplayLayer|0x1000 and snap to ground/wall/keep/tower height
             * (braziers/heads on spikes not on a wall, keep, gatehouse or tower are destroyed, refunding the
             * brazier gold cost to the local player's pendingResources[15] in GM_SIEGE_THAT). Projectiles (not
             * flaming arrows) damage the first accepting unit on the tile, siege rocks/fast ones also units on 4
             * neighbour tiles; poison clouds damage units on the 8 neighbour tiles and a second ring (height diff <
             * 120); fire ignites pitch ditches; below ground, type 0x20 ignites fire/pitch, type 0x1B and arrows
             * splash on water, arrows past half their range damage buildings (fire ballista 10 + fire if health <
             * 50, ballista 2, else 1) or bounce off walls/keeps, siege rocks spawn debris (counting a missed shot
             * on the firing unit on open ground) or damage buildings (treb 60/30, catapult 20/10, mangonel 5/0,
             * zero for own team), a landing flying cow splats into 6..10 poison clouds. Returns 1 by default (also
             * for types 0x20/0x1B/8 and arrows before half range or on immune buildings), 0 when removed/off-map,
             * on arrow water splash and after the remaining arrow/siege/cow impact branches.
             */
            undefined4 processEntityHitBuildingOrUnit(int entityID);

            /**
             * Sets projectile height = startingHeight + heightDelta; if the new height is < 3 and skipCollision ==
             * 0, unlinks the entity and runs processEntityHitBuildingOrUnit. Then re-reads the height: destroys the
             * entity and returns when it is > 10000; otherwise stores angleToRotationFrameIndex(pitchAngle) (0..8)
             * in pitchFrameIndex and copies the re-read (post-collision) height into height_2.
             */
            void updateProjectileHeightAndCollision(uint entityID, undefined4 heightDelta, int pitchAngle, int skipCollision);

            /**
             * Allocates a free entity slot by scanning upwards from the hint every10Ticks (no wrap-around; returns
             * 0 if no slot with logicalState 0 is found below 3000), raises maxEntityCount if needed, stores the
             * slot as the new hint, assigns a new uid and spawn time (field21_0x34 = mapTimeInTicks), sets micro
             * position/height, logicalState 5, calls setEntityParameters(entityType, gmLookupValue), registers it
             * on its tile via processEntityHitBuildingOrUnit, computes the draw offset and runs the type's update
             * callback once with DAT_CurrentEntityID temporarily set. Returns the entity id or 0.
             */
            uint spawnEntityEffect2(
                undefined4 microX, undefined4 microY, undefined4 height, undefined4 entityType, int gmLookupValue);

            /**
             * Same allocation as spawnEntityEffect2 but initialises the graphic via drawEntityEffect(entityType,
             * graphicType1, graphicType2). Returns the new entity id or 0 if no free slot.
             */
            uint spawnEntityEffect1(
                short x, short y, undefined4 height, undefined4 entityType, int graphicType1, int graphicType2);

            /**
             * Advances a projectile for one tick (returns FALSE at once if someCounter_OR_hitGround is set, else
             * TRUE). With flight time t = speedUnk (float): target travelledDistance = vCos*t/4 and target height
             * delta = 2*(vSin*t - 4.906*t^2). Pitch angle in degrees = atan(3*dh/dx) between t -
             * _elapsedTimeOrGravityAccumulator and t (or moveDirectionOrStepX when t == 0) is stored in
             * wanderCountdown, then t += _elapsedTimeOrGravityAccumulator. Steps travelledDistance one unit at a
             * time: moves the micro position, interpolates height for normal curves (collision skipped) and runs
             * processEntityHitBuildingOrUnit until it returns 0 or a hit is flagged. Curve type 9 (seagull dive)
             * rises 1/tick to targetZ, then drops 8/tick and below height 1 stops and spawns splash 0x1f +
             * FX_GULL_DIVE; curve type 10 rises 1/tick; other curves finish with a collision-enabled height update.
             * If entity field lineStepMode is 0 the linger countdown is set to 0x28 up front.
             */
            BOOLEnum moveProjectileEntity(int entityID);

            /**
             * Applies entity save-format fixups after loading a map: deletes seagulls in multiplayer, then by
             * receivedMapVersion: ==100 -> UpgradeSetCurrentEntityID3000 first; <=0x90 (incl. 100) ->
             * SetFlagEntityColor; <0xa0 -> UpgradeFirst25Entities. Nothing else if versions already match.
             */
            void handleMapVersionUpgrade(
                PackagedFileMagicNum receivedMapVersion, PackagedFileMagicNum packagerMapVersion);

            /**
             * Per-tick update of all map entities (projectiles, fires, flags, dust/poison clouds, seagulls). Every
             * 10th tick resets nextFreeEntitySearchStart to 25. For each used slot: counts it, advances
             * logicalState (1->2, 5->6, 3 or self-linked next pointer deletes, 4 activates the projectile, 7 ticks
             * decay and skips the rest, 8 ticks decay), advances the animation frame every ticksPerAnimFrame ticks,
             * runs type-specific movement (flags/braziers/heads relink, dust drift on odd frames, poison-cloud
             * random walk every 31 ticks at ground+20, types 0x1A/0x28..0x2B rise, projectiles get
             * screenDirectionIndex, trail effects and flight; skipped in state 6), then calls
             * EntityCallbacks[entityType] (and processSeaGulls for seagulls). Finally sets maxEntityCount to one
             * past the highest slot that was in use at the start of this tick (entities deleted this tick still
             * count; 0 if it was <= 1).
             */
            void updateEntities();
        };

        static_assert_cpp98_obj(sizeof(EntityState) == 706024, EntityState);

#pragma pack(pop)

    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
