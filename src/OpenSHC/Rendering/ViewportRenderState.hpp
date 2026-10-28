/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Rendering/ViewportRenderState.hpp'
*/

#pragma once

#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Map/Floaters/Floater.hpp"
#include "OpenSHC/Map/Matrices/TranslationMatrixTriplet.hpp"
#include "OpenSHC/Rendering/UnitRenderHelpStructure.hpp"
#include "OpenSHC/Rendering/ViewportState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Rendering {

    using OpenSHC::IO::Graphics::GmID;
    using OpenSHC::Map::Floaters::Floater;
    using OpenSHC::Map::Matrices::TranslationMatrixTriplet;
    using OpenSHC::Rendering::UnitRenderHelpStructure;
    using OpenSHC::Rendering::ViewportState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x0019F008
    class ViewportRenderState {
    public:
        // imported
        ViewportState viewportState; // 0x00000000 length: 180
        undefined4 DAT_skipped_isos; // 0x000000B4 length: 4
        undefined1 padding_0xb8[4]; // 0x000000B8 length: 4
        undefined4 DAT_MapEditorDisplayLayer; // 0x000000BC length: 4
        uchar DAT_BinaryTileMap400x400[160000]; // 0x000000C0 length: 160000
        short tileTranslationMatrix_YComponent[80400]; // 0x000271C0 length: 160800
        // Zeroed by setTileSystemMemoryLookupArrays together with the following 7 ints; no reader found.
        int tileLookupState0; // 0x0004E5E0 length: 4
        // Zeroed by setTileSystemMemoryLookupArrays; no reader found.
        undefined4 tileLookupState1; // 0x0004E5E4 length: 4
        // Zeroed by setTileSystemMemoryLookupArrays; no reader found.
        undefined4 tileLookupState2; // 0x0004E5E8 length: 4
        // Zeroed by setTileSystemMemoryLookupArrays; no reader found.
        undefined4 tileLookupState3; // 0x0004E5EC length: 4
        // Zeroed by setTileSystemMemoryLookupArrays; no reader found.
        undefined4 tileLookupState4; // 0x0004E5F0 length: 4
        // Zeroed by setTileSystemMemoryLookupArrays; no reader found.
        undefined4 tileLookupState5; // 0x0004E5F4 length: 4
        // Zeroed by setTileSystemMemoryLookupArrays; no reader found.
        undefined4 tileLookupState6; // 0x0004E5F8 length: 4
        // Zeroed by setTileSystemMemoryLookupArrays; no reader found.
        undefined4 tileLookupState7; // 0x0004E5FC length: 4
        int screenPointToTileNumber[321602]; // 0x0004E600 length: 1286408
        undefined1 padding_0x188708[8]; // 0x00188708 length: 8
        int DAT_TileTranslationMatrix_X_offset_min_24; // 0x00188710 length: 4
        int field27_0x188714; // 0x00188714 length: 4
        int field28_0x188718; // 0x00188718 length: 4
        int DAT_TileTranslationMatrix_X_offset_min_12; // 0x0018871C length: 4
        TranslationMatrixTriplet translationMatrix[400]; // 0x00188720 length: 4800
        undefined4 translationResult1; // 0x001899E0 length: 4
        undefined4 translationTracker1; // 0x001899E4 length: 4
        undefined4 translationResult2; // 0x001899E8 length: 4
        Floater floatersArray[250]; // 0x001899EC length: 7000
        int availableFloaterIndex; // 0x0018B544 length: 4
        // [180 0x004E5B80] slot i's frame counter is landscapeSeaWhiteCapsAnimationFrames[i] (piVar4[0x3C]);
        // int[45] + the following byte[60] landscapeAnimationValueArray = 240 bytes, i.e. really an int[60] array
        // of which 45 are used
        int whiteCapTiles[45]; // 0x0018B548 length: 180
        byte landscapeAnimationValueArray[60]; // 0x0018B5FC length: 60
        int landscapeSeaWhiteCapsAnimationFrames[45]; // 0x0018B638 length: 180
        byte unused02[60]; // 0x0018B6EC length: 60
        undefined4 windowX; // 0x0018B728 length: 4
        undefined4 windowY; // 0x0018B72C length: 4
        undefined4 screenPixelWidth; // 0x0018B730 length: 4
        undefined4 screenPixelHeight; // 0x0018B734 length: 4
        // Mouse tile saved by saveFocusTileAndCenterPreview and re-focused by restoreFocusTile.
        undefined4 savedFocusTile; // 0x0018B738 length: 4
        undefined4 interval_03_160; // 0x0018B73C length: 4
        undefined4 previousIntervalTime_03; // 0x0018B740 length: 4
        undefined4 interval_04_180; // 0x0018B744 length: 4
        undefined4 previousIntervalTime_04; // 0x0018B748 length: 4
        undefined4 interval_01_80; // 0x0018B74C length: 4
        undefined4 previousIntervalTime_01; // 0x0018B750 length: 4
        undefined4 interval_02_100; // 0x0018B754 length: 4
        undefined4 previousIntervalTime_02; // 0x0018B758 length: 4
        int unknownCounterUntil_0x20; // 0x0018B75C length: 4
        int unknownCounterUntil_0x24; // 0x0018B760 length: 4
        // Set to 1 by updateWaterAnimationFrames when the whitecaps interval elapsed this frame; renderMap then
        // advances each sea tile's animation counter.
        int seaAnimStepThisFrame; // 0x0018B764 length: 4
        // 0..15 cycle added to per-tile counters (mod 16 or /2 mod 8) to pick animated tile/pillar frames
        int tileAnimFrame16; // 0x0018B768 length: 4
        int unknownCounterUntil_0x200; // 0x0018B76C length: 4
        int unitBatchedRenderCounterUntil6; // 0x0018B770 length: 4
        UnitRenderHelpStructure unitBatch1[500]; // 0x0018B774 length: 16000
        UnitRenderHelpStructure unitBatch2[500]; // 0x0018F5F4 length: 16000
        UnitRenderHelpStructure unitBatch3[500]; // 0x00193474 length: 16000
        UnitRenderHelpStructure unitBatch4[500]; // 0x001972F4 length: 16000
        UnitRenderHelpStructure unitBatch5[500]; // 0x0019B174 length: 16000
        int unitRender1; // 0x0019EFF4 length: 4
        int unitRender2; // 0x0019EFF8 length: 4
        int unitRender3; // 0x0019EFFC length: 4
        int unitRender4; // 0x0019F000 length: 4
        int unitRender5; // 0x0019F004 length: 4

    private:
        ViewportRenderState(ViewportRenderState const&);
        void operator=(ViewportRenderState const&);

    public:
        ViewportRenderState() {};
        ~ViewportRenderState() {};

        // Constructor
        /**
         * Constructor of DAT_ViewportRenderState: sets initial viewport position (0x20, 8), animation interval
         * lengths (80/100/160/180 ms) and their start times, clears counters and the 45-entry landscape animation
         * tile array. Returns the global.
         */
        ViewportRenderState* Constructor_ViewportRenderState();

        /**
         * Returns TRUE if (x, y) is inside the 400x400 grid and marked as a valid map tile in
         * DAT_BinaryTileMap400x400.
         */
        BOOLEnum xyAreValid(uint x, uint y);

        /**
         * Converts grid coordinates (x, y) to a linear tile number using the per-row
         * translationMatrix[y].addXgetTile offset.
         */
        int translateXYToTile(int x, int y);

        /**
         * Inverse of translateXYToTile: returns the x coordinate of a tile number in row y (tile -
         * translationMatrix[y].addXgetTile).
         */
        int computeTileXOffset(int tileNumber, int y);

        /**
         * Builds the diamond-shaped tile layout tables: for each of the 400 rows computes translationMatrix
         * (distanceToCenter, firstTileOfRow, addXgetTile) with row widths 2..400..2, numbers the tiles in a
         * temporary 400x400 grid on the stack, fills screenPointToTileNumber (stride 401) for all four map
         * orientations by reading the grid rotated, and finally sets DAT_BinaryTileMap400x400 (0x21aec98) to 1
         * where the grid value is > 0 (so tile 0 itself is marked 0). The iVar locals are heavily reused register
         * temporaries (counters, row offsets, source indices).
         */
        void setTileSystemMemoryLookupArrays();

        /**
         * For every valid tile of the 400x400 grid stores its row y into tileTranslationMatrix_YComponent[tile] and
         * clears its validity byte in DAT_BinaryTileMap400x400 if the tile's LogicLayer has flags 0x30 (map
         * border).
         */
        void tweakValidTilesToExcludeMapBorders();

        /**
         * Resets the five unit render batches: counters unitRender1..5 to 0 and the rotating batch index
         * unitBatchedRenderCounterUntil6 to 1.
         */
        int resetBatchedRender();

        /**
         * Draws the climbing overlay of an assassin unit: if assassinHeightDifference > 0, imageIDUnk > 0 and the
         * orientation-corrected facing is 1/5 or one of the side-specific directions (2/3/4 when
         * assassinClimbingUpUnk_OR_previousFacingDirection is 0, else 0/6/7), renders its current image with
         * blending at (field308_0x41c, field309_0x420 - heightDifference).
         */
        void renderAssassinClimbingOverlay(int unitIndex);

        /**
         * Appends a unit draw request (unit id/status, owner colour, sprite, position, image, blend strength, gm)
         * to one of five render batches (max 500 each, silently dropped when full). The batch is the current
         * rotating batch index, or 4/3 batches ahead (mod 5) when the layer argument is 1/2.
         */
        void scheduleUnitForBatchedRendering(undefined4 unitIDOrStatus, undefined4 drawX, undefined4 drawY,
            undefined4 imageID, undefined4 blendStrength, undefined4 gmID, int param_7);

        /**
         * Draws per-building overlays at screen position (screenX, screenY): for small buildings (size < 3) the
         * health float when selected/highlighted (lifted 0x50 for gallows/gibbet, 0x1e for tower 1), the sleeping
         * (pop-circle) or needs-workers float (not in builder-mode siege maps), and a one-shot status float
         * (floatMarkerMode 1/2, then cleared); for gatehouses and towers 1-5 below full health (health*5/max != 5,
         * usesGfxOffsetLayer == 0) up to 8 GM_CRACKS images from overlay slots overlayFrame8..15 at type-specific
         * offsets; the owner flag (overlayFrame14, GM_ANIM_FLAG_SMALL) of an ox tether; and finally the building
         * animation (castle anims overlayFrame1/3 for towers 2-5, otherwise spriteID2/animationFrame with optional
         * blending), hiding unsprung enemy killing pits and clipping drawbridges. The status floats (not the health
         * float) are lifted by width*32 for buildings with zero defined height. The 4th stack parameter is never
         * read (ret 0x10).
         */
        void renderGmOverlayBuilding2(int buildingIndexOrFloatLift, int screenX, int screenY, int unused4);

        /**
         * Draws a building's animation sprite (spriteID2 / animationFrame at spriteOffset + screen position,
         * blended with animFadeAlpha if non-zero) in the owner colour, when renderAnimation and animationFrame are
         * set, flatViewMode is 0 and drawbridgePhase is 0; if clipTop is set, temporarily clips the map surface top
         * to max(screenY-0x27, 0) while drawing. The 4th parameter is unused.
         */
        void renderBuildingAnimation(int buildingIndex, int screenX, int screenY, undefined4 unused4, int clipTop);

        /**
         * Draws the animated overlays of one building at screen position (xUnk,yUnk); the parameter Ghidra calls
         * 'tileIndex' is really the building index (machine code: imul by 0x32C into DAT_BuildingsState.buildings)
         * and param_4 is the map tile currently being drawn. If displayOwnerFlag is set: a campground draws its
         * population circle (owner only); every other type returns immediately when
         * DAT_TileMapState.flatViewMode is set, otherwise draws its per-type overlays (small flag from
         * field39_0x84, worker/production animations of woodcutter, iron mine, hunter, quarry, farms, mill,
         * stables, inn, oil smelter, workshops with smoke, keep/gate/tower parts, chopping block) and the granary
         * goods / armory goods-or-shield piles, each pile only on its own footprint tile (armory slots depend on
         * map orientation), blended with an alpha derived from tickRelatedVisuallyActiveIndicator (1..4).
         * Afterwards: the health float (GM_FLOATS frame pct/10+0x11) if the building is the one selected in the
         * building menu or matches BuildingsState.clickedNoMenuBuildingID/field29_0x18e060 (index+uid), except
         * keeps/manor/campground and for granary/armory only on one orientation-dependent footprint tile; the
         * sleeping (zzz) or needs-workers float (skipped in builder-mode siege maps); and a one-shot status float
         * chosen by field68_0xc2 (1 or 2) which is then cleared. xUnk/yUnk are reused as height offsets for flat
         * buildings (size*32 and size*16 + tower adjustment); note the final status float subtracts the size*32 one
         * while the health/sleep floats use size*16 (machine-confirmed, intent unknown).
         */
        void renderGmOverlayBuilding(int tileIndex, int xUnk, int yUnk, int renderedTileIndex);

        /**
         * Per-frame animation clock tick based on timeGetTime(): when interval_04 elapses sets field55_0x18b764=1
         * (else 0) and increments all 45 sea white-cap animation frames; on their own intervals advances the wrap-
         * around counters unknownCounterUntil_0x10/0x20/0x24/0x200 (mod 16, 32, 36 and 512) used by other landscape
         * animations. NAME? updates more than water frames (generic landscape animation clocks).
         */
        void updateWaterAnimationFrames();

        /**
         * Maintains the 45 sea white-cap slots: an empty slot gets a random tile (0..0x13A0F) if that tile has
         * LogicLayer bit0 set, no MiscDisplayLayer 0x3C0 bits and no Logic2Layer bit3, and its animation frame
         * landscapeSeaWhiteCapsAnimationFrames[i] (shown by Ghidra as slotPtr[0x3C], 240 bytes further) is reset to
         * 0; a slot whose frame exceeds 7 (advanced by updateWaterAnimationFrames) is freed.
         */
        void assignRandomTiles();

        /**
         * Clamps the camera position (viewportX/viewportY, pixels) to the playable map area derived from the map
         * size (border = (400-mapSize)/2 tiles) using viewportHeight (visible 32-px columns) for X and
         * viewportWidth (visible 8-px rows) for Y, with extra per-orientation limits; if the allowed range is empty
         * it centres the view (for a 160 map at 1024x768 zoomed out the Y range used for that test is widened).
         * Then recomputes currentCameraOffsetX/Y = sub-tile scroll remainder + 0x96/0x10 (halved coordinates when
         * zoomed out).
         */
        void setViewportBasedOnMapSize();

        /**
         * Converts viewportState.mouseTile (linear tile index) to mouseTileX/mouseTileY by scanning
         * translationMatrix rows for the row containing the tile and adding the row's distanceToCenter.
         */
        void setupMouseTileXY2();

        /**
         * Same as setupMouseTileXY2 but converts viewportState.mouseAtomRefFloorTile (the floor tile under the
         * cursor) into mouseTileX/mouseTileY via translationMatrix row lookup.
         */
        void setupMouseTileXY();

        /**
         * Centres the camera on a map tile: scans the screen-position-to-tile table (orientation-dependent base,
         * 400 rows alternating 200/201 entries starting with 200) for 'tile', then sets viewportX = (column -
         * mbr_0xac)*32 and viewportY = (row - mbr_0xb0)*8 and re-clamps via setViewportBasedOnMapSize. If the tile
         * is not found the loop ends with row 400 and still applies.
         */
        void focusOnTile(int tile);

        /**
         * Picks the map tile under screen point (screenX,screenY) (does nothing but clear the results if
         * viewportState.field0_0x0 says the mouse is outside the map view): scans pixel rows downward from
         * screenY-8, converts each to a tile via screenPointToTileNumber and the sub-tile diamond table, stops at
         * LogicLayer 0x30 tiles, and keeps the last tile whose terrain height (+building height) reaches the cursor
         * (only the first row in flat view). If that tile has no path connection or is a wall (0x200), it redirects
         * to the neighbour in the current view direction when that neighbour is a wall top (0x100, for wall tiles)
         * or a building tile (for keep/tower 0x400 tiles); a tile that is none of moat (0x40000000), wall or
         * keep/tower gets the target cleared. Stores target in field24_0x60, raw tile in mouseAtomRefFloorTile,
         * mouseX/mouseY from the target, field27_0x6c (structure under cursor), moat flags field14/15/16 by moat
         * owner's team, and somePitchDitchID.
         */
        void computeMouseTileFromScreenPosition(int screenX, int screenY);

        /**
         * Clears all floater entries created this frame: for each used floater index >= 1 zeroes its tile's
         * FloatingLayer cell and its chain link, then resets availableFloaterIndex to 1.
         */
        void clearAllFloatingLayerElements();

        /**
         * Adds a floating sprite (gmID/imageID at imageX/imageY minus the GM origin, with variation) attached to
         * 'tile' (>= 0) into floatersArray (max 250). Floaters on a tile form a push-front linked list headed by
         * FloatingLayer[tile]; returns without adding if the same gmID+imageID already exists on that tile or the
         * head index is invalid (>249).
         */
        void createFloatingLayerElement(GmID gmID, int imageID, int imageX, int imageY, int tile, int variation);

        /**
         * Debug overlay at (x,y): prints mouse atom/floor tile, mouse x/y/tile, tile centre, ray-picked unit
         * ('Chimp')/building ('Struct')/entity ('Fly') IDs, and LogicLayer/Logic2Layer/DamageLayer values of the
         * floor tile and of the mouse tile.
         */
        void renderDebugDataMousePointing(int x, int y, int width, int height);

        /**
         * Configures the map viewport for the current resolution and zoom (really __thiscall on
         * DAT_ViewportRenderState; Ghidra lost ECX). Stores windowX into BOTH windowX and windowY and never reads
         * the second parameter (machine-confirmed source slip, latent: both callers pass 0,0), stores the pixel
         * width/height, then sets viewportHeight (visible 32-px columns), viewportWidth (visible 8-px rows), the
         * centre offsets mbr_0xac/mbr_0xb0, ScrollingHandler edge parameters and someX/YOffset from per-resolution
         * constants (separate sets when zoomed out and when the siege-tower/shield siege-tent tab of the build menu
         * or map editor is active), then clamps via setViewportBasedOnMapSize; unknown resolutions only re-clamp.
         */
        void setupViewport(
            undefined4 windowX, undefined4 windowY, undefined4 screenPixelWidth, undefined4 screenPixelHeight);

        /**
         * Changes zoom level (zoomUnk -> isZoomedOutUnk) while keeping the view centre: remembers the centre pixel
         * (viewportX/Y + mbr_0xac*32 / mbr_0xb0*8), re-runs setupViewport(0,0,resolutionX,height) where height is
         * resolutionY minus 128 px for the bottom menu unless the siege-tower/shield siege-tent tab of the build
         * menu/map editor is active, then restores the origin from the saved centre with the new offsets and re-
         * clamps. 'this_00' in the decompilation is simply this: setupViewport is __thiscall and preserves ECX.
         */
        void resetupViewport(int zoomUnk);

        /**
         * Re-applies the viewport setup for the current zoom level (resetupViewport with the existing
         * isZoomedOutUnk); called from processMenuViewSwitch.
         */
        void resetupViewportThunk();

        /**
         * Draws one of five round-robin unit render batches per call (counter 1..5; that batch's count is taken and
         * zeroed). Entry unitID -1: plain GM sprite (blendStrength < 0 alpha-masked with mask frame taken from the
         * gmID field and strength -1-blend, 0 normal, > 0 blended). unitID 0: sprite with packed flags in
         * blendStrength (bit 0x4 sets owner/sprite id, 0x10 owner 0, 0x20 alpha mask with frame imageID+high word,
         * else high word = blend). unitID > 0: a unit, where the entry's imageID/blendStrength/gmID hold sprite
         * width/height/pixel pointer; it saves the back-buffer pixel under the mouse (viewportState.mousePickPixelPtr),
         * paints it magenta, draws the unit (assassin fade layers, base layer and extra layers shifted down/clipped
         * by per-layer offsets, siege tower/ram flag when currentGameMode != GM_SOLITARY) and, if the pixel is no
         * longer magenta, sets mouseRayUnitID to the unit and clears mouseRayBuildingID (last drawn wins), else
         * restores the pixel. Selected units get a health bar (lord rating or owner fear-factor variant, centred on
         * sprite width) and own-team assassins an icon; pending floats field46_0x6e / field45_0x6c are drawn once
         * and cleared.
         */
        void renderUnits();

        /**
         * NAME? Per-frame mouse hover/picking update, not building-preview specific: WinMain's in-game loop calls
         * it every frame right after renderMap with the mouse screen position (saveFocusTileAndCenterPreview calls
         * it with the view centre). Sets field0_0x0 = cursor inside the map view rectangle and not over an active
         * menu-tab hit rectangle (returns at once if over one). Inside the view: resolves mouseTile via the screen-
         * to-tile and sub-tile diamond tables, caches its LogicLayer/BuildingLayer/UnitLayer values and sub-tile
         * direction data, records the last ray-picked unit and the time (a siege tower in a certain idle state is
         * turned into its building), sets mouseTileX/Y, then scans pixel rows from the cursor downward (height
         * aware) for a wall tile (-> field21_0x54, clears mouseRayBuildingID) or a building, which only overrides
         * mouseRayBuildingID when it is an active granary/armory; shows the 'This was a ...' ruins text from
         * BuildingWasLayer and finally calls computeMouseTileFromScreenPosition. Outside the view, in the build
         * menu with the battering-ram tab or shiftRelated0or3 == 1, it takes the tile from the minimap under the
         * cursor and fills the same fields.
         */
        void updateMouseHoverState(int mouseXScreenSpace, int mouseYScreenSpace);

        /**
         * Runs the mouse hover/tile resolution (updateBuildingPreviewPosition) for the centre of the viewport and
         * saves the resulting mouseTile in field44_0x18b738, so changeMapOrientation can re-centre on it after
         * rotating (overwrites the current hover state as a side effect).
         */
        void saveFocusTileAndCenterPreview();

        /**
         * Re-centres the camera on the tile saved by saveFocusTileAndCenterPreview (field44_0x18b738) via
         * focusOnTile.
         */
        void restoreFocusTile();

        /**
         * Centres the camera on map coordinate (x,y) by converting it to a tile index
         * (translationMatrix[y].addXgetTile + x) and calling focusOnTile.
         */
        void focusOnCoordinate(int x, int y);

        /**
         * Wrapper: creates a floater from the GID_FLOATS sprite set (imageID at imageX/imageY attached to tile,
         * with variation) via createFloatingLayerElement.
         */
        void createFloatingTextElement(int imageID, int imageX, int imageY, int tile, int variation);

        /**
         * Main per-frame map renderer (called from WinMain): zeroes the draw rect of every unit that is not
         * ULS_INVISIBLE and Building.visibleTileCount, sets viewportState.tileCenterX/Y and the mouse-pick pixel
         * pointer, then walks screen rows top-down (Y +8 per row; rows alternate viewportTileColumns+1 and
         * viewportTileColumns tiles, the latter shifted +0x10 in X; tile ids from screenPointToTileNumber, row base
         * += 201/200), continuing past viewportTileRows up to +0x2a rows while the probe tile 8 slots into the row
         * is on-map (LogicLayer & 0x30 == 0), calling renderUnits once per row to flush batched sprites. Each row
         * runs three column passes: (1) terrain / animated sea / animated tiles (or flat-view icons), construction-
         * placement and moat-dig GID_FLOATS overlays, wall connections (GM_CASTLE_ANIMS / TGX), floaters with
         * variation&2, birds/flying cows, units (direct or batched; health bars, assassin translucency, multiplayer
         * siege-tower/ram flags, rotate/overhead GID_FLOATS_NEW markers), ground entities, EntityLayerLT25 entities
         * with popup icon + number, trees and pillar/wall blits; (2) building sprites (counting visibleTileCount),
         * drawbridge/building overlays, the MiscDisplay 0x4000 float marker (bit then cleared), floaters with
         * variation&1, then clears ConstructionGFXLayer and MiscDisplay bit 0x8000; (3, not in flat view) alpha-
         * faded overlay images from stockpileBuildingIdLayer on LogicLayer-0x400 tiles, faded by the building's
         * overlayFadeStep 1..4 (level step*32/5). Mouse picking: before each building tile or directly drawn unit
         * it saves the pixel under the cursor, writes COL_MAGENTA, and if that pixel was overdrawn afterwards sets
         * mouseRayBuildingID or mouseRayUnitID (zeroing the other; last drawn wins), else restores it (batched
         * units are not picked here). After the rows it calls renderUnits 5 more times, draws a black band for
         * 160-size maps at 1024x768 zoomed-out with a siege-tent tab, and if viewportState.mouseOverMap draws the
         * cursor overlay for MouseState.cursorOverlayMode 1-5 or, for 1000/1001, an icon plus '(stock -
         * wallPlacementCost)' of resource 4 (pendingResources in GM_SIEGE_THAT, else currentResources) / resource
         * 2; then resets the mode to -1, clears floaters and the surface height range, isZoom2 and
         * showMoatDigHighlight. Note: the existing local 'tileIndex' actually holds the OrganismLayer value (tree
         * index) and later random-rock offsets, building heights and floater Y offsets.
         */
        void renderMap();
    };

    static_assert_cpp98_obj(sizeof(ViewportRenderState) == 1699848, ViewportRenderState);

#pragma pack(pop)

} // namespace Rendering
} // namespace OpenSHC
