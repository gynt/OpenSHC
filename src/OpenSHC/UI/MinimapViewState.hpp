/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MinimapViewState.hpp'
*/

#pragma once

#include "OpenSHC/Map/MapHeaderSection4IntStruct.hpp"

#include "WinDef.h"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Map::MapHeaderSection4IntStruct;

#pragma pack(push, 1)

    // SIZE: 0x00061BF8
    class MinimapViewState {
    public:
        // Set by menu views every frame (or when map changes) to force minimap re-render; cleared by render
        // functions
        undefined4 forceRedraw; // 0x00000000 length: 4
        // Viewport-center x (tiles) of last minimap render; change triggers redraw
        undefined4 lastRenderedViewX; // 0x00000004 length: 4
        // Viewport-center y of last minimap render; change triggers redraw
        undefined4 lastRenderedViewY; // 0x00000008 length: 4
        // Cleared by every minimap render; build/landscaping DoEveryFrame force a menu redraw
        // (unk_resetViewportRelated=2) while it is 0; no non-zero writer seen
        undefined4 skipMenuRedrawFlag; // 0x0000000C length: 4
        // Top row of the visible minimap window for large maps (tile rows); used to convert minimap clicks to
        // viewport/tile y
        undefined4 scrollOriginY; // 0x00000010 length: 4
        // Left column of the visible minimap window; used to convert minimap clicks to viewport/tile x
        undefined4 scrollOriginX; // 0x00000014 length: 4
        undefined4 width; // 0x00000018 length: 4
        undefined4 height; // 0x0000001C length: 4
        undefined4 widthFactor; // 0x00000020 length: 4
        undefined4 heightFactor; // 0x00000024 length: 4
        undefined4 x; // 0x00000028 length: 4
        undefined4 y; // 0x0000002C length: 4
        undefined4 oneOrTwo; // 0x00000030 length: 4
        // Advanced by 2 and passed as start percent to row renderers until >99; a percentage, not a row. Row cursor
        // (0..100 step 2, percent) of the incremental tile-color rebuild done in drawMinimap
        undefined4 incrementalRedrawPercent; // 0x00000034 length: 4
        // Incremental minimap rebuild passes remaining: triggerMinimapRedraw sets 2 (or 1 if already running);
        // decremented after each full sweep
        undefined4 pendingRedrawPasses; // 0x00000038 length: 4
        // Set by BuildMenu_MiniMapInteraction render when cursor is over the minimap; disables unit hit-testing and
        // enables click-to-tile conversion
        undefined4 mouseOverMinimap; // 0x0000003C length: 4
        undefined4 DAT_SomeMiniMapCounterTill4; // 0x00000040 length: 4
        // [246 0x004B5330] machine code takes this+0x44 as the output buffer (0x1A31654) written by this renderer
        ushort compositedPixelBuffer[80000]; // 0x00000044 length: 160000
        // 400x400/2 cached base minimap colors per tile pair, used when the per-flag color resolves to 0
        ushort baseTileColorCache[80000]; // 0x00027144 length: 160000
        short loadedMiniMap[200][200]; // 0x0004E244 length: 80000
        MapHeaderSection4IntStruct DAT_MapU4B64; // 0x00061AC4 length: 64
        int spawnMomentX[20]; // 0x00061B04 length: 80
        int spawnMomentY[20]; // 0x00061B54 length: 80
        DWORD spawnMoment[20]; // 0x00061BA4 length: 80
        int spawnMomentCount; // 0x00061BF4 length: 4

    private:
        MinimapViewState(MinimapViewState const&);
        void operator=(MinimapViewState const&);

    public:
        MinimapViewState() {};
        ~MinimapViewState() {};

        // Constructor
        /**
         * Static constructor of the global MinimapViewState: clears the redraw-state field field14_0x38 (+0x38) and
         * DAT_SomeMiniMapCounterTill4 (+0x40); returns the object.
         */
        MinimapViewState* Constructor_MinimapViewState();

        /**
         * Scrolls the main view so the minimap point under the mouse becomes the view centre: converts mouse pos to
         * minimap tile coords (via x/y, width/heightFactor, oneOrTwo and the field5_0x14/field4_0x10 tile offsets),
         * subtracts half of (viewportHeight-5) from the column and half of viewportWidth from the row, stores
         * viewportX (*32) / viewportY (*8) and calls setViewportBasedOnMapSize. Skipped when in the build menu with
         * tab 0x3d (BASMTT_SIEGETENT_RAM_OR_BM_TROOP_PANEL) or shiftRelated0or3==1 AND rightClickState is 0 (the old header
         * saying 'right button held' is inverted).
         */
        void scrollViewportToMinimapClick();

        /**
         * Converts the mouse position over the minimap into map tile coordinates (used for building preview
         * placement). If field15_0x3c is 0 returns (-1,-1); else computes a viewport-pixel point (x*32, y*8), looks
         * it up in screenPointToTileNumber (offset by map orientation) and splits the tile number into Y
         * (tileTranslationMatrix_YComponent) and X (tile - translationMatrix[y].addXgetTile).
         */
        void convertMinimapClickToTileXY(int* outTileX, int* outTileY);

        /**
         * Draws the 200x200 RGB16 loadedMiniMap image (hard-coded 0x1A7F854 = DAT_MinimapViewState+0x4E244) onto
         * the pencil surface at (screenX, screenY), skipping 0-valued (transparent) pixels.
         */
        void renderMinimapPreview(int screenX, int screenY);

        /**
         * Requests a minimap redraw: if no redraw is pending (field14_0x38==0) resets field13_0x34 and sets state
         * 2, otherwise sets state 1. The stack argument is unused (ret 4).
         */
        void triggerMinimapRedraw(int unused);

        /**
         * Renders the composited minimap pixel buffer (hard-coded 0x1A31654, i.e. this+0x44 of
         * DAT_MinimapViewState; `this` itself is not used) for rows startPercent..startPercent+percentCount percent
         * of the 400 rows: walks the diamond map via screenPointToTileNumber (table base chosen by mapOrientation)
         * and picks a colour from DAT_MiniMapDefinedData: LogicLayer bit 0x40000000 -> moatColors, bits 0x3000 ->
         * treeColors (variant RandomLayer&3), bit 8 -> plain2PitchColor if MiscDisplayLayer&0x2000 else 0,
         * otherwise the first entry of the 0-terminated logicFlagColorTable whose mask matches (else 0). Non-zero
         * colours (unless LuminesenceLayer==2 or flag 2) are scaled per channel by luminescenceBrightnessPct
         * (RGB555/565). Where the colour is 0 it falls back to baseTileColorCache (the first fallback pixel is then
         * reused for the rest of that tile). 1x or half-res (scaleFlags&4) output; maps <= 200 skip 100 rows.
         */
        void renderMinimapTileStripWithLuminescence(uint scaleFlags, int tilePixelWidth, int tilePixelHeight, uint startPercentOrColor, int percentCountOrPixelRow);

        /**
         * Renders the terrain colour layer of the minimap (baseTileColorCache, hard-coded 0x1A58754; `this` unused)
         * for rows startPercent..startPercent+percentCount percent of 400: for each tile (via
         * screenPointToTileNumber, table base by mapOrientation) picks a colour from DAT_MiniMapDefinedData by a
         * priority chain: LogicLayer&0x30 -> 0, bit 1 sea, 0x200000 ford, 0x100000 river, 0x20000 boulder, 0x80
         * MinimapColorArray, 0x40000 pebble, Logic2 0x40 stones/high ground, Logic2 0x20 beach, Logic2 0x10+0x8000
         * oasis grass, Logic2 0x80+0x8000 thick scrub, Logic2 1+0x8000 scrub, 0x80000 iron, 0xA0000000 marsh/oil,
         * HeightLayer>16 stones/high ground, Logic2 2 or bit 8 earth, else default ground (variant RandomLayer&3,
         * or &7 for sea/ford/boulder/earth/default). Applies the luminescenceBrightnessPct factor (unless
         * LuminesenceLayer==2) per channel in RGB555/565 and writes tilePixelWidth x tilePixelHeight pixels (half-
         * res when flags&4). Maps <= 200 skip the first 100 rows. Parameters are reused as row index / colour /
         * pixel x.
         */
        void renderMinimapTileColors(uint flagsOrRow, int tilePixelWidth, int tilePixelHeight, int startPercentOrColor, uint percentCountOrPixelX);

        /**
         * Scans the minimap tile grid (same walk as the minimap renderers) and for every keep building
         * (buildingType 40..44) records the first minimap pixel position per owner in
         * DAT_MapU4B64.keepPositions[owner-1] (all reset to -1 first). Used when rendering the minimap for saving.
         */
        void locatePlayerKeepPositionsOnMinimap(uint flagsOrPixelRow, int tilePixelWidth, int tilePixelHeight);

        /**
         * Palettises the 200x200 loadedMiniMap for saving: masks off each channel's low bit(s), builds up to 256
         * unique colours (extra colours map to index 0) into a 40000-byte index array, converts the palette to
         * RGB555 if in 565 mode, then stores the 256-entry palette at the start of loadedMiniMap and the index
         * bytes right after (byte offset 512).
         */
        int generateMinimapImage();

        /**
         * Inverse of generateMinimapImage after reading a map header: takes the 256-colour palette and 40000 index
         * bytes stored in loadedMiniMap, converts the palette from RGB555 to 565 if needed and expands it back into
         * 200x200 16-bit pixels.
         */
        void convertLoadedMinimapColors();

        /**
         * Appends a minimap event marker (x, y, timeGetTime) to the spawnMoment arrays if fewer than 20 are stored
         * (callers: fire spread, poison clouds, scripted events).
         */
        void setSpawnMoment(int x, int y);

        /**
         * Called each game tick: finds the first spawn-moment marker older than 20 s (age > 20000 ms), removes it
         * by shifting the following X/Y/time entries down one slot, and decrements the count (at most one removal
         * per call).
         */
        void clearOldSpawnMoment();

        /**
         * Redraws the composited minimap for a row range: calls renderMinimapTileStripWithLuminescence(flags 4, 2x1
         * px per tile for maps > 200, else 4x2) with the given start percentage and percentage count (callers pass
         * 0,100 for full redraw).
         */
        void redrawMinimapRowsForMapSize(uint startPercent, int percentCount);

        /**
         * Re-renders the minimap terrain colour layer for a row range: calls renderMinimapTileColors(flags 4, 2x1
         * px per tile for maps > 200, else 4x2) with start percentage and percentage count.
         */
        void setTileColorsDependingOnMapSize(int startPercent, uint percentCount);

        /**
         * Core minimap renderer. First re-renders the minimap pixel buffers if the map orientation changed (rows
         * 0..100) or redraw passes are pending (pendingRedrawPasses, 2% of rows per call via
         * incrementalRedrawPercent; the first slice also calls collectDustCloudSourceTiles). Then clamps the view
         * so it stays inside the map, stores the minimap origin tile (scrollOriginX / scrollOriginY) and copies the
         * composite buffer (0x1A31654) to the screen surface, or into loadedMiniMap when modeOrRowStride > 0 (save
         * thumbnail). Next it plots units as player-coloured dots (colour slot: owner, or displayColorPlayerID for
         * selectable E_KNIGHT/A_HARCHER, ownerColorIndex for other selectable units): siege engines cycle shades
         * via DAT_SomeMiniMapCounterTill4, unowned units and cows/dogs/chickens use the neutral colour, enemy
         * assassins are hidden unless within 0xA0, melee-attacking, or (single-player only) idleCounterUnk > 0x960.
         * In ally/enemy colour mode (minimapAllyEnemyColorMode) units on the local player's team use the local
         * player's colour and all others the colour of the first slot on another team; unowned units and animals
         * are skipped. Finally, when flags&2 is set and the view rectangle is not clamped, draws the white view
         * rectangle clipped to the minimap. flags: 1 = offsets are the view centre, 2 = draw view rect, 4 = half-
         * size plotting (oneOrTwo=2).
         */
        void drawMinimap(int xPos, int yPos, int width, int height, uint flags, int xOffset, int yOffset,
            int widthFactor, int heightFactor, int param_10);

        /**
         * Renders the in-game minimap in the bottom panel (menu origin +0x23B,+0x1D1, 126x126, flags 7, mode 0)
         * when forced (field0_0x0) or the view-centre tile changed. It advances the 0..3 shade counter, stores the
         * centre and clears field0_0x0/field3_0xc. When a selection icon is active, field15_0x3c is set and the
         * mouse is over the minimap, it also draws the GM_MINI_CURSORS icon at the mouse.
         */
        void renderMinimapMain();

        /**
         * Map-editor landscaping variant of renderMinimapMain: draws the minimap at the given rect (flags 7) when
         * forced or the view centre moved, advances the shade counter, stores the centre and clears
         * field0_0x0/field3_0xc.
         */
        void renderMinimapLandscaping(int xPos, int yPos, int width, int heigth);

        /**
         * Editor/setup-menu minimap: resets the shade counter. When forced or the view moved, draws the minimap at
         * the given rect with flags 5 (centre on view, half-size plotting, no view rectangle) and mode -1, then
         * sets unk_resetViewportRelated = 2. Always stores the centre and clears field0_0x0/field3_0xc.
         */
        void renderMinimapEditor(int xPos, int yPos, int width, int height);

        /**
         * Renders the minimap thumbnail stored in map/save files. Clears loadedMiniMap (80000 bytes), then draws
         * the minimap into it (flags 5, mode 1) with 4x2 (maps <= 200) or 2x1 pixels per tile. The view centre
         * comes from the map margin (top-left of the playable area) and is then clamped by drawMinimap. Records
         * keep positions via locatePlayerKeepPositionsOnMinimap and sets field0_0x0 so the live minimap is redrawn
         * next frame.
         */
        void renderMiniMapForSaving(int xPos, int yPos, int width, int height);
    };

    static_assert_cpp98_obj(sizeof(MinimapViewState) == 400376, MinimapViewState);

#pragma pack(pop)

} // namespace UI
} // namespace OpenSHC
