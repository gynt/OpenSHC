/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Rendering.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Rendering {

    /**
     * Alpha-blends 256 pixels (64 at zoom 2) of the current GM image into the map surface at the current draw
     * position; each pixel's destination offset (and at zoom 2 also its source offset) comes from a
     * DAT_BlendingDefinedData offset table. Per colour component the destination is scaled with
     * DAT_BlendFilterArrays[blendLevel] (0xd7d2d8) and the source with DAT_BlendFilterArrays[32 - blendLevel]
     * (0xd812d8 minus level*0x200), then the two are added. Handles RGB555 and RGB565; nothing is drawn unless the
     * start row lies inside mapGameSurfaceHeightRange. Lazily initialises the filter tables if level 32 is still
     * empty.
     */
    void __cdecl ApplyBlending(int blendLevel);

    /**
     * Copies a GM tile image (rows of 15 dwords, 0x3c bytes) onto the map surface, each source row written as an
     * isometric diagonal stripe (dword k goes to dest row k for k<=7 or 14-k for k>=7, pixel column 2k). Clips
     * vertically against mapGameSurfaceHeightRange and draws in up to two segments (current image for its first
     * height-7 rows, then image g_renderMapCurImageIndex for the remaining g_renderMapBlitY rows);
     * g_renderMapBlitMode selects right half (1, dwords 7-14), left half (2, dwords 0-7), centre column only (3) or
     * the whole tile; the zoom-2 path writes alternating halves per row parity into the half-size surface.
     */
    void __cdecl BlitMapImageWithVerticalClip();

    /**
     * Variant of BlitMapImageWithVerticalClip (same diagonal-stripe blit, modes 1/2/3/full, zoom-2 path, clipping
     * against mapGameSurfaceHeightRange) whose source is shifted down by (0xa0 - DAT_RenderMap_YOffset) rows: that
     * shifted offset is used for the continuation segment from image g_renderMapCurImageIndex, or for the only
     * segment when the image is not split. Mode 3 moves the first segment's source back 8 rows (0x1e0 bytes).
     */
    void __cdecl BlitMapImageWithVerticalClipAndYOffset();

    /**
     * Initialises the global COL_* 16-bit colour constants for the current pixel format (hardcoded values for
     * RGB555 vs RGB565), plus several colours converted from RGB via TransformToCurrentModeColor.
     */
    void __cdecl InitializeColors();

    /**
     * Starts the frame timer: uses QueryPerformanceFrequency/Counter if available (g_frameIntervalTicks = frequency/60,
     * TIME_PreviousQuery = current counter low part), otherwise falls back to timeGetTime with a 16 ms margin.
     * Resets both frame-time scale floats to 1.0.
     */
    void __cdecl TicksStartCounter();

    /**
     * Returns the tile number under the viewport reference point (presumably its centre):
     * screenPointToTileNumber[viewportX/32 + (viewportY/16 + mbr_0xb0/2) * 401 + mbr_0xac + orientationOffset - 8],
     * where the offset selects one of four per-map-orientation tables (8, 0x13a18, 0x27428, 0x3ae38).
     */
    int __cdecl ViewportBasedTileNumber();

    /**
     * Interpreter for the credits / scripted-sequence command list (CreditsRelatedStructure2_ARRAY_00eb9b68, cursor
     * DAT_CreditsScriptCommandIndex), only while no menu switch is pending: executes commands until one blocks (frame wait,
     * wait for an element's fade to finish, sound stream or Bink end, screen fade end, click on a button element).
     * Opcodes add/fade/remove display elements, play/stop Bink videos and sound streams, start screen fades, show
     * full-screen text pages, set the background and loop back to the last opcode-0x1f marker. Opcode 0x16 advances
     * WITHOUT removing buttons: the decompiled fall-through into opcode 0x17 is an artefact (machine code jumps
     * straight to the advance code at 0x4E10B2).
     */
    void __cdecl ProcessCreditsScriptCommands();

    /**
     * Per-frame renderer of the credits/script elements: clears the screen black or draws background gfx
     * DAT_CreditsBackgroundGfx (per DAT_CreditsBackgroundMode = 0/1), applies the mode-5 dim (level falls to 16), then for
     * layers 0..7 draws every active element (type 1 gfx with optional hover image, 2 text, 3 button showing gfx+1
     * when hovered, 4 bordered box) and advances its fade: mode 1 lowers the level and resets the mode to 0 at <1
     * (element kept), mode 2 raises it and frees the element above 31 (type 1 fades twice as fast; type 3 has no
     * fade). Finally draws the text-page progress bar and the full-screen (modes 1/2) or rectangle (3/4, double
     * speed) black fade; modes 1/3 end above 31, modes 2/4 end below 0 and then call AppendCreditsSoundEntry(0,0).
     */
    void __cdecl RenderActiveCreditsElements();

} // namespace Rendering
} // namespace OpenSHC
