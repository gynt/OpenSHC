/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Buildings/Building.hpp'
*/

#pragma once

#include "OpenSHC/Game/Resources/ResourceTypeShort.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalStateShort.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Game::Resources::ResourceTypeShort;
        using OpenSHC::Map::Buildings::BuildingLogicalStateShort;
        using OpenSHC::Map::Buildings::BuildingTypeShort;

#pragma pack(push, 1)
        // SIZE: 0x0000032C
        typedef struct Building {

            int spriteID; // 0x00000000 length: 4
            int spriteSheetID; // 0x00000004 length: 4
            // Player index used as render colour (DAT_RenderedUnitOwner); rewritten with new owner on transfer.
            // Same pattern as Unit+0x10.
            int ownerColorIndex; // 0x00000008 length: 4
            short spriteOffetX; // 0x0000000C length: 2
            short spriteOffetY; // 0x0000000E length: 2
            int animAdvanceThrottle; // 0x00000010 length: 4
            int animStateCounterTracker; // 0x00000014 length: 4
            int animStateCounter; // 0x00000018 length: 4
            int animationFrame; // 0x0000001C length: 4
            short animationIndex; // 0x00000020 length: 2
            short spriteID2; // 0x00000022 length: 2
            short unknownStockpileOrSignpostRelated; // 0x00000024 length: 2
            short renderAnimation; // 0x00000026 length: 2
            // Incremented each time the building work animation completes a cycle (table wrap / last work phase),
            // cleared by updateBuildingSignpostCounter.
            int workCycleCount; // 0x00000028 length: 4
            // Set to 1 together with workCycleCount++ (some buildings clear it on other ticks); read and cleared by
            // updateBuildingSignpostCounter.
            short workCycleJustEnded; // 0x0000002C length: 2
            short animationIncrement; // 0x0000002E length: 2
            short animationActive; // 0x00000030 length: 2
            undefined1 padding_0x32[2]; // 0x00000032 length: 2
            // [061 0x00419370] chopping block sets it from fear < -3 to show its overlay animation, campground sets
            // it on mouse hover; it enables the overlay layer generally, not only the owner flag
            int showOverlays; // 0x00000034 length: 4
            // Building overlay sprite frame (0 = not drawn), drawn by
            // renderGmOverlayBuilding/renderGmOverlayBuilding2 per building type. Overlay slots are field20..23
            // (0x38-0x44, frames of the 4 animated layers whose counters are campgroundVclock/field25/26/27) and
            // 0x5C-0x88 (slots 4-15; shouldRenderRoof=slot 5, shouldRenderSomeOverlay=slot 6, ownerFlagFrame=slot
            // 13 are existing misleading names). Slot 0: frame of animated layer 0 (counter campgroundVclock), e.g.
            // woodcutter/farmer worker, keep overlay 0x18/0x1B, tower fixed overlay 0x7D, granary pile.
            int overlayFrame0; // 0x00000038 length: 4
            // Building overlay sprite frame (0 = not drawn), drawn by
            // renderGmOverlayBuilding/renderGmOverlayBuilding2 per building type. Overlay slots are field20..23
            // (0x38-0x44, frames of the 4 animated layers whose counters are campgroundVclock/field25/26/27) and
            // 0x5C-0x88 (slots 4-15; shouldRenderRoof=slot 5, shouldRenderSomeOverlay=slot 6, ownerFlagFrame=slot
            // 13 are existing misleading names). Slot 1: frame of animated layer 1 (counter field25), e.g. smoke of
            // blacksmith/bakery/brewery, oil flare.
            int overlayFrame1; // 0x0000003C length: 4
            // Building overlay sprite frame (0 = not drawn), drawn by
            // renderGmOverlayBuilding/renderGmOverlayBuilding2 per building type. Overlay slots are field20..23
            // (0x38-0x44, frames of the 4 animated layers whose counters are campgroundVclock/field25/26/27) and
            // 0x5C-0x88 (slots 4-15; shouldRenderRoof=slot 5, shouldRenderSomeOverlay=slot 6, ownerFlagFrame=slot
            // 13 are existing misleading names). Slot 2: frame of animated layer 2 (counter field26), e.g.
            // mill/iron mine/stables layers.
            int overlayFrame2; // 0x00000040 length: 4
            // Building overlay sprite frame (0 = not drawn), drawn by
            // renderGmOverlayBuilding/renderGmOverlayBuilding2 per building type. Overlay slots are field20..23
            // (0x38-0x44, frames of the 4 animated layers whose counters are campgroundVclock/field25/26/27) and
            // 0x5C-0x88 (slots 4-15; shouldRenderRoof=slot 5, shouldRenderSomeOverlay=slot 6, ownerFlagFrame=slot
            // 13 are existing misleading names). Slot 3: frame of animated layer 3 (counter field27), e.g. mill
            // sails.
            int overlayFrame3; // 0x00000044 length: 4
            // frame counter for overlay layer 0 in many buildings, not campground-specific; +0x48 precedes
            // overlayAnimIndex1..3 (+0x4C..+0x54)
            int overlayAnimIndex0; // 0x00000048 length: 4
            // Frame counter (index into a BuildingDefinedData frame table) of animated overlay layer 1; the looked-
            // up frame goes to overlayFrame1 (field21_0x3c). Advanced when the tick divider field28_0x58 is 0.
            int overlayAnimIndex1; // 0x0000004C length: 4
            // Frame counter of animated overlay layer 2 (result into overlayFrame2 / field22_0x40); dairy farm,
            // mill, stables, iron mine, quarry, inn.
            int overlayAnimIndex2; // 0x00000050 length: 4
            // Frame counter of animated overlay layer 3 (result into overlayFrame3 / field23_0x44); dairy, mill,
            // stables, iron mine, quarry. The blacksmith reuses it as a 0/1 'bellows active' selector between two
            // forge tables.
            int overlayAnimIndex3; // 0x00000054 length: 4
            // Per-building tick divider: incremented every tick and wrapped (>3 in workshops for overlay animation,
            // >1 mill/iron mine/quarry logic, >5 stables, every 100 ticks ox tether spawn); logic or overlay
            // counters advance only when it is 0.
            int tickDivider; // 0x00000058 length: 4
            // Building overlay sprite frame (0 = not drawn), drawn by
            // renderGmOverlayBuilding/renderGmOverlayBuilding2 per building type. Overlay slots are field20..23
            // (0x38-0x44, frames of the 4 animated layers whose counters are campgroundVclock/field25/26/27) and
            // 0x5C-0x88 (slots 4-15; shouldRenderRoof=slot 5, shouldRenderSomeOverlay=slot 6, ownerFlagFrame=slot
            // 13 are existing misleading names). Slot 4: armory weapon pile 0, granary pile, tower/gatehouse/iron-
            // mine overlays.
            int overlayFrame4; // 0x0000005C length: 4
            // sprite frame number, not a flag; +0x60 sits in the overlayFrame0..15 block (overlayFrame4=+0x5C,
            // overlayFrame7=+0x68)
            int overlayFrame5; // 0x00000060 length: 4
            // sprite frame number, not a flag; +0x64 sits in the overlayFrame0..15 block (overlayFrame4=+0x5C,
            // overlayFrame7=+0x68)
            int overlayFrame6; // 0x00000064 length: 4
            // Building overlay sprite frame (0 = not drawn), drawn by
            // renderGmOverlayBuilding/renderGmOverlayBuilding2 per building type. Overlay slots are field20..23
            // (0x38-0x44, frames of the 4 animated layers whose counters are campgroundVclock/field25/26/27) and
            // 0x5C-0x88 (slots 4-15; shouldRenderRoof=slot 5, shouldRenderSomeOverlay=slot 6, ownerFlagFrame=slot
            // 13 are existing misleading names). Slot 7: granary goods pile (only the granary writes it).
            int overlayFrame7; // 0x00000068 length: 4
            // Building overlay sprite frame (0 = not drawn), drawn by
            // renderGmOverlayBuilding/renderGmOverlayBuilding2 per building type. Overlay slots are field20..23
            // (0x38-0x44, frames of the 4 animated layers whose counters are campgroundVclock/field25/26/27) and
            // 0x5C-0x88 (slots 4-15; shouldRenderRoof=slot 5, shouldRenderSomeOverlay=slot 6, ownerFlagFrame=slot
            // 13 are existing misleading names). Slot 8: first of the 8 tower/gatehouse damage overlay slots
            // (0x6C..0x88), granary pile.
            int overlayFrame8; // 0x0000006C length: 4
            // Building overlay sprite frame (0 = not drawn), drawn by
            // renderGmOverlayBuilding/renderGmOverlayBuilding2 per building type. Overlay slots are field20..23
            // (0x38-0x44, frames of the 4 animated layers whose counters are campgroundVclock/field25/26/27) and
            // 0x5C-0x88 (slots 4-15; shouldRenderRoof=slot 5, shouldRenderSomeOverlay=slot 6, ownerFlagFrame=slot
            // 13 are existing misleading names). Slot 9: tower/gatehouse damage overlay, granary pile.
            int overlayFrame9; // 0x00000070 length: 4
            // Building overlay sprite frame (0 = not drawn), drawn by
            // renderGmOverlayBuilding/renderGmOverlayBuilding2 per building type. Overlay slots are field20..23
            // (0x38-0x44, frames of the 4 animated layers whose counters are campgroundVclock/field25/26/27) and
            // 0x5C-0x88 (slots 4-15; shouldRenderRoof=slot 5, shouldRenderSomeOverlay=slot 6, ownerFlagFrame=slot
            // 13 are existing misleading names). Slot 10: tower/gatehouse damage overlay, granary pile.
            int overlayFrame10; // 0x00000074 length: 4
            // Building overlay sprite frame (0 = not drawn), drawn by
            // renderGmOverlayBuilding/renderGmOverlayBuilding2 per building type. Overlay slots are field20..23
            // (0x38-0x44, frames of the 4 animated layers whose counters are campgroundVclock/field25/26/27) and
            // 0x5C-0x88 (slots 4-15; shouldRenderRoof=slot 5, shouldRenderSomeOverlay=slot 6, ownerFlagFrame=slot
            // 13 are existing misleading names). Slot 11: tower/gatehouse damage overlay, granary pile; the armory
            // puts its owner flag here.
            int overlayFrame11; // 0x00000078 length: 4
            // Building overlay sprite frame (0 = not drawn), drawn by
            // renderGmOverlayBuilding/renderGmOverlayBuilding2 per building type. Overlay slots are field20..23
            // (0x38-0x44, frames of the 4 animated layers whose counters are campgroundVclock/field25/26/27) and
            // 0x5C-0x88 (slots 4-15; shouldRenderRoof=slot 5, shouldRenderSomeOverlay=slot 6, ownerFlagFrame=slot
            // 13 are existing misleading names). Slot 12: armory weapon pile 2, granary pile, tower/gatehouse
            // damage overlay.
            int overlayFrame12; // 0x0000007C length: 4
            // sits between overlayFrame12/14, zeroed with them; per-type slot 13 (granary food pile, GM_CRACKS,
            // goods pile, flag tick). Machine-checked; supersedes decided_1 keep
            int overlayFrame13; // 0x00000080 length: 4
            // Building overlay sprite frame (0 = not drawn), drawn by
            // renderGmOverlayBuilding/renderGmOverlayBuilding2 per building type. Overlay slots are field20..23
            // (0x38-0x44, frames of the 4 animated layers whose counters are campgroundVclock/field25/26/27) and
            // 0x5C-0x88 (slots 4-15; shouldRenderRoof=slot 5, shouldRenderSomeOverlay=slot 6, ownerFlagFrame=slot
            // 13 are existing misleading names). Slot 14: in most buildings the multiplayer owner-flag frame
            // (field177_0x7e1c[ownerFlagFrame/2], 0 in GM_SOLITARY), but the armory stores its 4th weapon-pile
            // sprite here, so it is a generic slot.
            int overlayFrame14; // 0x00000084 length: 4
            // Building overlay sprite frame (0 = not drawn), drawn by
            // renderGmOverlayBuilding/renderGmOverlayBuilding2 per building type. Overlay slots are field20..23
            // (0x38-0x44, frames of the 4 animated layers whose counters are campgroundVclock/field25/26/27) and
            // 0x5C-0x88 (slots 4-15; shouldRenderRoof=slot 5, shouldRenderSomeOverlay=slot 6, ownerFlagFrame=slot
            // 13 are existing misleading names). Slot 15: granary pile, tower/gatehouse damage overlay; the
            // campground reuses it as a 0..40 start/stop delay for the campfire animation.
            int overlayFrame15; // 0x00000088 length: 4
            // [096 0x004FB0C0] written as an int tile index (marked 'fixme') for the MiscDisplayLayer bit-8 tile,
            // not an x coordinate
            byte flag8DisplayTile; // 0x0000008C length: 1
            byte yPosition; // 0x0000008D length: 1
            undefined1 padding_0x8e[2]; // 0x0000008E length: 2
            // [182 0x004E8CF0] zeroed for all buildings at frame start and incremented in the building pass for
            // each of its tiles that is in a visible row, an inner column and column > 4
            short visibleTileCount; // 0x00000090 length: 2
            // Created by retype action
            short orientation; // 0x00000092 length: 2
            undefined1 padding_0x94[6]; // 0x00000094 length: 6
            short unknownFlag3; // 0x0000009A length: 2
            // [071 0x0041BD70] set to the amount that would be removed when previewOnly is set, zeroed on a real
            // deduction
            short pendingResourceLossPreview; // 0x0000009C length: 2
            short buildingIsVisuallyActive; // 0x0000009E length: 2
            int visuallyActiveSpriteID; // 0x000000A0 length: 4
            // set to 100 on each delivery, decremented; nonzero keeps the building visually active
            short deliveryActivityCountdown; // 0x000000A4 length: 2
            undefined1 padding_0xa6[2]; // 0x000000A6 length: 2
            // added to spriteID for keep doors AND every generic variation-0xF building (final_329/331); keep-door-
            // only name too narrow [107 0x005146D0] set on the keep doors to 2 (manor house / stone keep) or 0, the
            // centre door gets half
            uint spriteFrameOffset; // 0x000000A8 length: 4
            int gfxOffset; // 0x000000AC length: 4
            // Set by updateBuildingGraphicsLayer to 1 when gfxOffset != 0 and TileMapState.fullHeightViewActive == 0
            // (else 0); while set keeps/gatehouses use the gfxOffset tile graphics, overlays and the keep-door
            // animation are skipped and getBuildingHeightForBuildingID2 returns type-specific heights.
            // Set by updateBuildingGraphicsLayer to 1 when gfxOffset != 0 and TileMapState.refreshRelatedOne == 0
            // (else 0); while set keeps/gatehouses use the gfxOffset tile graphics, overlays and the keep-door
            // animation are skipped and getBuildingHeightForBuildingID2 returns type-specific heights.
            int usesGfxOffsetLayer; // 0x000000B0 length: 4
            int gfxOffset2; // 0x000000B4 length: 4
            int gfxOffset3; // 0x000000B8 length: 4
            // [179 0x004E3980] value 1..4 converted to blend alpha 0x20 - v*32/5 for the pile/mill overlays
            short overlayFadeStep; // 0x000000BC length: 2
            // Blend level of the building's worker/overlay animation: 0 = normal renderGM, 1..32 =
            // renderGMWithBlending with this level (renderBuildingAnimation, renderGmOverlayBuilding farmer
            // layers). Workshops/bakery/marketplace/dairy step it between 0x1F/0x20 and 0 to fade the worker in or
            // out; setBuildingToAppleFarm sets 0x20.
            short animFadeAlpha; // 0x000000BE length: 2
            short recruitTimer; // 0x000000C0 length: 2
            // One-frame marker request drawn by renderGmOverlayBuilding(2) as GID_FLOATS_NEW above the building,
            // then cleared: 1 = attack target of a selected unit (drawFlagsAndUnitDestinations), 2 = mannable siege
            // engine / oil smelter under the cursor while selecting units.
            short floatMarkerMode; // 0x000000C2 length: 2
            // [070 0x0041A7A0] inverted name: set to 1 when showNoRubbleWhenDestroyingBuilding == 0
            // (destroyBuildings 0x41A894: global = BuildingShowRubbleWhenDestroyed[type] == 0); the TileMapState
            // footprint-clearing functions clear BuildingWasLayer when noRubble == 0 and sets MiscDisplayLayer bit
            // 0x4000 (rubble) when it is non-zero. The global and the table names are consistent; only
            // Building.leavesRubble is inve
            // [070 0x0041A7A0] inverted name: set to 1 when showNoRubbleWhenDestroyingBuilding == 0
            // (destroyBuildings 0x41A894: global = BuildingShowRubbleWhenDestroyed[type] == 0); the TileMapState
            // footprint-clearing functions clear BuildingWasLayer when noRubble == 0 and sets MiscDisplayLayer bit
            // 0x4000 (rubble) when it is non-zero. The global and the table names are consistent; only
            // Building.noRubble is inve
            short leavesRubble; // 0x000000C4 length: 2
            undefined1 padding_0xc6[2]; // 0x000000C6 length: 2
            int miscDisplayLayerTile; // 0x000000C8 length: 4
            // [070 0x00419960] stores the gate-state byte before an override and is copied back to restore it
            short savedGateState; // 0x000000CC length: 2
            short oldVisualActiveState; // 0x000000CE length: 2
            BuildingLogicalStateShort logicalState; // 0x000000D0 length: 2
            BuildingTypeShort buildingType; // 0x000000D2 length: 2
            undefined1 padding_0xd4[2]; // 0x000000D4 length: 2
            // Created by retype action
            short owner; // 0x000000D6 length: 2
            int uid; // 0x000000D8 length: 4
            undefined1 padding_0xdc[12]; // 0x000000DC length: 12
            ushort microX; // 0x000000E8 length: 2
            ushort microY; // 0x000000EA length: 2
            // [071 0x00420D20] initialised from the averageHeight argument and used as the z coordinate when
            // spawning cage dogs Created by retype action
            short terrainHeight; // 0x000000EC length: 2
            // most north-west tile
            short x; // 0x000000EE length: 2
            short y; // 0x000000F0 length: 2
            undefined1 padding_0xf2[2]; // 0x000000F2 length: 2
            uint currentTilePositionAdjusted; // 0x000000F4 length: 4
            uint widthOrHeight; // 0x000000F8 length: 4
            ushort entranceAttemptTileIndex; // 0x000000FC length: 2
            short buildingEntryX; // 0x000000FE length: 2
            short buildingEntryY; // 0x00000100 length: 2
            short buildingVariation; // 0x00000102 length: 2
            // per-building random value set from SEC_RNG at placement; used for sprite variants, thresholds and
            // decals, not fire-specific
            int randomSeed; // 0x00000104 length: 4
            short flag1; // 0x00000108 length: 2
            undefined1 padding_0x10a[2]; // 0x0000010A length: 2
            short currentHealth; // 0x0000010C length: 2
            short maxHealth; // 0x0000010E length: 2
            // Used by siege tower that is placed to refer to unit
            short unitRefID; // 0x00000110 length: 2
            undefined1 padding_0x112[2]; // 0x00000112 length: 2
            int unitRefUID; // 0x00000114 length: 4
            short state; // 0x00000118 length: 2
            // Secondary animation/work state used per building type: oil smelter flare-up flag (1 when a pot is
            // produced, 0 when the flare table ends), quarry block/rope state 0..6, iron mine sub-state 0..2, reset
            // by the killing pit; read by the renderer.
            short subAnimState1; // 0x0000011A length: 2
            // generic per-building sub-state (miller, iron mine, quarry pryer, killing pit flag); between
            // subAnimState1 (+0x11A) and subAnimState3 (+0x11E)
            short subAnimState2; // 0x0000011C length: 2
            // Third animation/work state (after killingPitField): iron mine pouring state 0/1 (completion adds 1
            // iron to the mine), quarry mason state (finishing 1 adds 1 RT_STONE to the pile).
            short subAnimState3; // 0x0000011E length: 2
            int resources[25]; // 0x00000120 length: 100
            // a building can only hold 1 type of resource
            int currentNumberOfResource; // 0x00000184 length: 4
            uint currentLimitOfResource; // 0x00000188 length: 4
            short currentStoredResourceType; // 0x0000018C length: 2
            short uidPlaced; // 0x0000018E length: 2
            // Part number 1..4 of a stockpile: placeStockpile creates 4 2x2 stockpile buildings (one per
            // Stockpile_BuildingPartsOffsets entry) and numbers them; clearBuildingFromTerrain clears the stockpile
            // footprint only for part 1.
            short stockpilePartNumber; // 0x00000190 length: 2
            // part-to-parent link (keep doors, parade grounds, guild/oil smelter parts, quarry pile), not quarry-
            // specific Created by retype action
            undefined2 linkedBuildingID; // 0x00000192 length: 2
            // Decremented once per updateBuildings tick while > 0; no writer found in the analysed code, purpose
            // unknown.
            short countdown194; // 0x00000194 length: 2
            short numberOfPopulationProvided; // 0x00000196 length: 2
            short buildingTypeBasedEmployeeCount; // 0x00000198 length: 2
            short currentEmployeeCount; // 0x0000019A length: 2
            short currentlyNeededEmployeeCount; // 0x0000019C length: 2
            short workerID[4]; // 0x0000019E length: 8
            undefined1 padding_0x1a6[2]; // 0x000001A6 length: 2
            int workerUID[4]; // 0x000001A8 length: 16
            short workers[4]; // 0x000001B8 length: 8
            // [123 0x00554CC0] set to the miller slot while grinding and cleared when done; other millers wait
            // while it is nonzero
            short occupyingWorkerId; // 0x000001C0 length: 2
            // Set to 1 every tick by the fletcher, blacksmith, poleturner, armorer, tanner, bakery and brewery
            // updates (goods workshops only); no reader found in the analysed code.
            short isProductionWorkshop; // 0x000001C2 length: 2
            // Created by retype action
            short growCounter; // 0x000001C4 length: 2
            undefined1 padding_0x1c6[2]; // 0x000001C6 length: 2
            // Building.tileRef1..36 are one int[36] footprint tile list: placeWheatfarm loops 0x24 times over
            // [id*0x32C+0xF986FC] with stride 4; determinePeasantSitPosition indexes [(id*0xCB+k)*4+0xF986FC].
            // Requested by manual_changes.json / decided_1.
            int tileRefs[36]; // 0x000001C8 length: 144
            // Declared 1-byte undefined1 but every access is a word (movzx/mov/cmp word) - found while verifying
            // the Building placeholders; +0x259 is undefined.
            short farmerNextWorkState; // 0x00000258 length: 2
            undefined1 padding_0x25a[2]; // 0x0000025A length: 2
            int tunnelerCounter; // 0x0000025C length: 4
            // Set at building creation to x+offset / buildingEntryX; used as reachability target tile. Tunneler
            // reuse is also an adjacent start tile. Created by retype action
            short accessTileX; // 0x00000260 length: 2
            // Pair of accessTileX: set to y+offset / buildingEntryY at creation, used as reachability target row.
            // Created by retype action
            short accessTileY; // 0x00000262 length: 2
            // Hunter's post: set to 400 when the hunter dog (worker slot 1) is burning, decremented each tick; a
            // new UT_HUNTERDOG is spawned only when it is 0.
            short dogRespawnCooldown; // 0x00000264 length: 2
            undefined1 padding_0x266[2]; // 0x00000266 length: 2
            // [062 0x0041CA00] uid of the spawned UT_QUARRYOX, compared to units[oxUnitID].uid
            int oxUnitUID; // 0x00000268 length: 4
            // the UT_QUARRYOX unit spawned by the ox tether (validated with oxTetherRelatedUnitUID)
            short oxUnitID; // 0x0000026C length: 2
            // Placeholder +0x26E is a word: placeHopfarm writes it with a word store, setNewOnFarmDestination
            // compares word ==0x51.
            undefined1 hopFarmLayoutCode[2]; // 0x0000026E length: 2
            // Campground: number of peasants idling at their campfire spot (UpdatePeasant state 8) counted this
            // tick (cleared by UpdateCampGround every tick); < 2 / < 5 select the fixed activity states 1 / 3 and
            // it keeps the campfire animation running.
            short campIdlePeasantCount; // 0x00000270 length: 2
            // Campground: number of peasants walking to their campfire spot (UpdatePeasant state 7) counted this
            // tick; keeps the campfire animation running; cleared every tick.
            short campArrivingPeasantCount; // 0x00000272 length: 2
            // Campground peasant activity state (1,3 fixed; else cycles 2->4->3->5->6->2 on timeAlive thresholds);
            // UpdatePeasant maps it to peasant idle/sit/dance substates.
            short campActivityState; // 0x00000274 length: 2
            // Campground: previous value of campActivityState, saved on each state change.
            short campPrevActivityState; // 0x00000276 length: 2
            // Created by retype action
            int buildingProgress; // 0x00000278 length: 4
            // [061 0x00418100] compared against 200/600/1000/300/80 and reset to 0 on each campground state change
            // (other building types may use it differently)
            uint stateTimer; // 0x0000027C length: 4
            // The four bytes +0x280..+0x283 are one per-side byte array:
            // computeBuildingEntranceFlagsForOrientations clears all four with one dword store and then sets byte
            // [building+0x280 + perimeterIndex/tilesPerSide]=1; readers test single bytes per orientation.
            undefined1 wallOnSide[4]; // 0x00000280 length: 4
            // used for hovels
            int hovelVisualStyle; // 0x00000284 length: 4
            // Set to 1 by placeBuilding when hasLessWoodThanTheCostOfAWoodcuttersHutAndNoWoodcutters is true for
            // the placed type (out-of-wood rescue placement); ClickDestroyBuilding gives back no resources for such
            // a building; cleared for all buildings by the map-version upgrade UpgradeBuildingField2.
            short noRefundOnDestroy; // 0x00000288 length: 2
            // Inn: set to 300 by the innkeeper when serving/fetching ale; decremented by UpdateInn, spawnDrunkard
            // at 0; while non-zero keeps the inn active and selects the busy overlay table.
            short drunkardSpawnCountdown; // 0x0000028A length: 2
            short flag2; // 0x0000028C length: 2
            // [203 0x00439440] drawn after 'Producing:' (asm 0x4395C2); elsewhere workers copy producedItemType
            // into it when a cycle starts and deliver it as output
            ResourceTypeShort currentProducedItemType; // 0x0000028E length: 2
            // [203 0x00439440] drawn after 'Next:' (asm 0x43967B); the player command handler (Synchrony::Actions)
            // writes the chosen weapon into it
            ResourceTypeShort selectedNextItemType; // 0x00000290 length: 2
            // Iron mine: blend level 0x0C..0x18 (set from the smelting sub-animation frame) passed to
            // renderGMWithBlending when GID_ANIM_IRON_MINER is drawn blended.
            byte ironMinerBlendLevel; // 0x00000292 length: 1
            // [061 0x00417B90] 10 requests raise (state 0), 11 requests lower (state 2), set to 12 once the request
            // is accepted
            byte drawbridgeCommand; // 0x00000293 length: 1
            // [061 0x00417B90] 0 lowered, 1 raising (anim field139, raise SFX), 2 raised, 3 lowering (anim
            // field140, lower SFX)
            byte drawbridgePhase; // 0x00000294 length: 1
            byte containsSiegeMangonel1OrBallista2; // 0x00000295 length: 1
            bool sleeping; // 0x00000296 length: 1
            // Such are horses and cows.
            byte numberOfAnimals; // 0x00000297 length: 1
            // Dairy farm state machine 0..6: 0 timers (new cow after 400 ticks if < 3 cows, else milking), 1 fade
            // (overlay 0x46), 2 new-cow animation and spawn, 3 fade before milking, 4 milking
            // (FX_COW_MILK/FX_MILK_POUR), 5 cheese making, 6 cheese ready (resources[11] = 1).
            // UpdateCow/UpdateDairyFarmer hide while it is 3..4.
            byte dairyState; // 0x00000298 length: 1
            // Dairy farm: cow slot 1..3 (index into workerID[]) chosen for the next milking, cycled round-robin.
            byte dairyMilkCowSlot; // 0x00000299 length: 1
            // per-type timer: outpost archer respawn, dairy/stables production, mill grind, ox tether cooldown
            short typeSpecificTimer; // 0x0000029A length: 2
            int ffBuildingVariation; // 0x0000029C length: 4
            // Placeholder +0x2A0 is a signed word (movsx in UpdateOilSmelter, word stores/compares in
            // UpdateEngineer).
            short oilWaitingEngineerID; // 0x000002A0 length: 2
            // gate door state 0 open, 1 closing, 2 closed, 3 opening; drives path linkage through the gate
            // (majority of batches)
            byte gateOpenState; // 0x000002A2 length: 1
            byte gateState; // 0x000002A3 length: 1
            // [090 0x004A4470] tiles whose building has unknownFlag4 != 0 are skipped by the phase-2 AI zone
            // marking Created by retype action
            undefined1 blocksAIZoneSpread; // 0x000002A4 length: 1
            // Placeholder +0x2A5: only access is a byte store from a byte table in setupBuildingData.
            char houseVariant; // 0x000002A5 length: 1
            char childSpawnCountdown; // 0x000002A6 length: 1
            // per-type byte: stables horses taken (UI 'Horse(s) In Use'), outpost garrison archer target 6+rand%2
            char horsesInUseOrOutpostArcherCap; // 0x000002A7 length: 1
            int uidWhenPlaced; // 0x000002A8 length: 4
            int attackWave; // 0x000002AC length: 4
            short flagonsOfAleOrCheeseOrReleaseDogs; // 0x000002B0 length: 2
            // accessed by 0x41597d, 0x415984, 0x41599e
            undefined1 field_0x2b2[2]; // 0x000002B2 length: 2
            // [158 0x0051E300] set to the last non-zero value among the 4 orthogonal neighbour words copied from
            // AIZoneLayer (16-bit reads from a byte layer at 0x51EB5E) before the building is added to the
            // high/arch list
            short adjacentAIZoneValue; // 0x000002B4 length: 2
            // Gatehouse: set to 10 together with gateState = 10 when the open gate of an AI-controlled owner closes
            // because an enemy is within 200 sub-tiles; no reader found.
            short gateAutoCloseState; // 0x000002B6 length: 2
            short gateCloseOpenTimer; // 0x000002B8 length: 2
            short buildMonthOrBuildOrder; // 0x000002BA length: 2
            short hasAccessToKeep; // 0x000002BC length: 2
            // goes up until overflows
            short fireDuration; // 0x000002BE length: 2
            // [072 0x004224F0] set to 1200 when an enemy unit is within 200 micro units, decremented each tick,
            // gate reopens when it is 0
            short enemyNearbyHoldTimer; // 0x000002C0 length: 2
            // Placeholder +0x2C2 is written as a word (keep flag entity id).
            undefined1 keepFlagEntityID[2]; // 0x000002C2 length: 2
            short cooldownTimer; // 0x000002C4 length: 2
            // Gatehouse/wood gate: player ID of the enemy currently holding the gate (troop value majority on the
            // footprint), 0 = not captured; triggers "lost control of a gatehouse" warning, blocks the status menu
            // and makes the gate passable for that player in pathfinding.
            short capturedByPlayerID; // 0x000002C6 length: 2
            // Set to 1 when the building was placed by an AI castle (AIV) build step; woodcutter huts with it set
            // report path length 0 (not relocated by AI).
            short placedByAIV; // 0x000002C8 length: 2
            short quarryLinkedOxTethers[3]; // 0x000002CA length: 6
            // Created by retype action
            short oxtetherLinkedQuarryID; // 0x000002D0 length: 2
            short laddermanDataID; // 0x000002D2 length: 2
            // Woodcutter's hut: path length (totalSizeOfPathPlan) of the woodcutter's last walk to a tree; the
            // player's maximum and its building are tracked in someCount10/someCount11.
            short woodcutterTreePathLength; // 0x000002D4 length: 2
            // Set to 4000 while workplace's worker disappears; decremented only for AI buildings (cleared for
            // humans); sort key of needs-peasants queue.
            short aiRestaffCountdown; // 0x000002D6 length: 2
            short unknownSiegeTentRelated01; // 0x000002D8 length: 2
            // Cathedral, campaign mission 7: 1 once the sprite was switched to the damaged version (0x11F) at <=30%
            // health, 0 above.
            short damagedSpriteShown; // 0x000002DA length: 2
            // [026 0x004CB940] AI demolishes the woodcutter hut when it has no worker and this counter >= 20;
            // decremented while a worker is present
            short aiAbandonCounter; // 0x000002DC length: 2
            ushort ifFireThenResponsiblePlayer; // 0x000002DE length: 2
            // [057 0x00411540] insideUnitID1-4 (and insideUnitUID1-4) are contiguous and indexed as arrays by the
            // slot loop at 0x00411B00 (shown by Ghidra as out-of-bounds quarryLinkedOxTethers[i+0xb]/[i*2+0xf])
            // Created by retype action
            short insideUnitIDs[4]; // 0x000002E0 length: 8
            // [057 0x00411540] insideUnitUID1-4: UIDs of the units in insideUnitIDs, indexed by the same slot loop
            int insideUnitUIDs[4]; // 0x000002E8 length: 16
            short hasUnitsOntop; // 0x000002F8 length: 2
            // Tower1/Tower4: countdown (reset to 100 when units move onto it or a siege tent is placed); at 0 the
            // footprint is rescanned to update hasUnitsOntop.
            short unitsOnTopRecheckCountdown; // 0x000002FA length: 2
            // Placeholder +0x2FC is a signed word cursor (movsx read, word store) in the wheat/hops field graphics
            // updaters.
            undefined1 farmGfxUpdateCursor[2]; // 0x000002FC length: 2
            short statueCommemoratingPlayerID; // 0x000002FE length: 2
            // bit i enables outpost raid troop table i; toggled by outpost unit buttons, init 0xFF; outpost only
            short outpostTroopTableMask; // 0x00000300 length: 2
            short tribeID; // 0x00000302 length: 2
            int tribeUID; // 0x00000304 length: 4
            // Outpost/campground raid: incremented each tick and compared to the spawn interval; reset to 2000 or
            // rand%40.
            short raidTimer; // 0x00000308 length: 2
            // [057 0x00411540] = (rand % tbl[3] + tbl[2]) * (level+1); tribe released when its size reaches it
            short raidTargetSize; // 0x0000030A length: 2
            // Outpost: row index into BuildingDefinedData.outpostSpawnConfig (field413_0xa04c), 0-7 (+8 Arabian).
            short raidTroopTableIndex; // 0x0000030C length: 2
            // slider 0..5: raid size * (lvl+1) and spawn interval (100-15*lvl)%; outpost only
            short outpostStrengthLevel; // 0x0000030E length: 2
            // [057 0x00411540] decremented each tick while >0; tribe is only released to the AI when it is <1
            short outpostAttackDelay; // 0x00000310 length: 2
            // Outpost: 1 after a raid tribe was created until its catapult is spawned; tables 6/7 then always pick
            // their first unit entry.
            short raidCatapultPending; // 0x00000312 length: 2
            // Placeholder +0x314: byte compare and byte store 1 in UpdateOutpostBuilding.
            byte outpostInitDone; // 0x00000314 length: 1
            undefined1 padding_0x315[1]; // 0x00000315 length: 1
            // [057 0x00411540] +100 after each released raid; raid interval = 2000 - value
            short raidIntervalReduction; // 0x00000316 length: 2
            // [057 0x00411540] +4 after each released raid; subtracted from the per-troop spawn period tbl[0]
            short troopSpawnIntervalReduction; // 0x00000318 length: 2
            undefined1 padding_0x31a[18]; // 0x0000031A length: 18

        } Building;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(Building) == 812, Building);
    } // namespace Buildings
} // namespace Map
} // namespace OpenSHC
