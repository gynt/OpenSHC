/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Rendering/TextureRenderCore.hpp'
*/

#pragma once

#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/IO/Graphics/GMFileHeaderColorpalette.hpp"
#include "OpenSHC/IO/Graphics/GfxRef.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Colors/RGB15.hpp"
#include "OpenSHC/Rendering/Enums/RenderTargetInt.hpp"
#include "OpenSHC/Text/FontRenderType.hpp"
#include "OpenSHC/UI/Rendering/Range.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "WinDef.h"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::DE::SHCDE::eGM;
        using OpenSHC::IO::Graphics::GfxRef;
        using OpenSHC::IO::Graphics::GMFileHeaderColorpalette;
        using OpenSHC::IO::Graphics::GmID;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Rendering::Colors::RGB15;
        using OpenSHC::Rendering::Enums::RenderTargetInt;
        using OpenSHC::Text::FontRenderType;
        using OpenSHC::UI::Rendering::Range;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

        // SIZE: 0x0016D484
        class TextureRenderCore {
        public:
            // [253 0x00455050] 0 = all allocations ok, 1 = gmProcessedImageData or gmAndGfxImageDataBuffer malloc
            // failed, 2 = unknownMemPtr_1_0x80 failed, 3 = address2 failed
            dword allocErrorCode; // 0x00000000 length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            RenderTargetInt drawBufferChoiceValue; // 0x00000004 length: 4
            // Unsigned Double-Word (ddw, 4-bytes) [UNK PASS] was currentRenderSurfaceIdentifierUnk_0x8
            RenderTargetInt flaggedSurfaceTarget; // 0x00000008 length: 4
            ushort* currentRenderSurface; // 0x0000000C length: 4
            // [252 0x0044FBF0] 0 -> palette slot from PlayerSlotUnitColor[owner], else owner index used directly
            // Unsigned Double-Word (ddw, 4-bytes)
            dword useRawOwnerPaletteIndex; // 0x00000010 length: 4
            undefined1 padding_0x14[24]; // 0x00000014 length: 24
            // Set to 1 in TextureRenderCore constructor only
            int ctorFlag2c; // 0x0000002C length: 4
            undefined1 padding_0x30[20]; // 0x00000030 length: 20
            // Unsigned Double-Word (ddw, 4-bytes)
            int gmSizeOfProcessedPictures_0x44; // 0x00000044 length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            int gmNumberOfProcessedPictures; // 0x00000048 length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            int gmFileID; // 0x0000004C length: 4
            // [254 0x004559B0] loadGMFile: when non-zero, pictures with a non-zero header flag byte (without bit 2)
            // reuse the data of picture i+delta instead of being copied If set to 1, only one variation of the big
            // menu buttons is used.
            BOOLEnum gmAllowRelativeAliasing; // 0x00000050 length: 4
            int isZoom2; // 0x00000054 length: 4
            Range mapGameSurfaceHeightRange; // 0x00000058 length: 8
            Range screenMenuSurfaceHeightRange; // 0x00000060 length: 8
            // Unsigned Double-Word (ddw, 4-bytes)
            dword activeMenuTabIndex; // 0x00000068 length: 4
            // [254 0x00455540] set to (iconWidth - glyphWidth) + 3 for glyphs centred on an icon, else 0 Unsigned
            // Double-Word (ddw, 4-bytes)
            dword extraGlyphAdvance; // 0x0000006C length: 4
            // [252 0x0044FBF0] if non-zero it replaces the computed palette pointer used for 8-bit index lookup
            // Unsigned Double-Word (ddw, 4-bytes)
            dword paletteOverridePtr; // 0x00000070 length: 4
            int gmProcessedImageDataBufferSize_0x74; // 0x00000074 length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            void* gmProcessedImageData; // 0x00000078 length: 4
            int unknownMemSize_1_0x7c; // 0x0000007C length: 4
            void* unknownMemPtr_1_0x80; // 0x00000080 length: 4
            int unknownMemSize_2_0x84; // 0x00000084 length: 4
            void* address2; // 0x00000088 length: 4
            int gmAndGfxImageDataBufferSize_0x8c; // 0x0000008C length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            void* gmAndGfxImageDataBuffer; // 0x00000090 length: 4
            // Unsigned Double-Word (ddw, 4-bytes)
            void* bitmapsFaces_0x94; // 0x00000094 length: 4
            // Face-size table has 28 slots: readBitmapFace indexes [i*4+0x1FEA128] (+0x98), lobby code indexes
            // [slot*4+0x1FEA174] = index 19+slot with slot 1..8 (setupSkirmishLobby zeroes +0xE8..+0x104), so
            // unknownPlayerDependentRenderValue is entries 20..27.
            int faceBitmapByteSize[28]; // 0x00000098 length: 112
            // Zeroed in TextureRenderCore constructor only
            int ctorZeroed108; // 0x00000108 length: 4
            // Zeroed in TextureRenderCore constructor only
            int ctorZeroed10c; // 0x0000010C length: 4
            // Zeroed in TextureRenderCore constructor only
            int ctorZeroed110; // 0x00000110 length: 4
            // Zeroed in TextureRenderCore constructor only
            int ctorZeroed114; // 0x00000114 length: 4
            // Zeroed in TextureRenderCore constructor only
            int ctorZeroed118; // 0x00000118 length: 4
            // Zeroed in TextureRenderCore constructor only
            int ctorZeroed11c; // 0x0000011C length: 4
            // Zeroed in TextureRenderCore constructor only
            int ctorZeroed120; // 0x00000120 length: 4
            // Zeroed in TextureRenderCore constructor only
            int ctorZeroed124; // 0x00000124 length: 4
            // Zeroed in TextureRenderCore constructor only
            int ctorZeroed128; // 0x00000128 length: 4
            // Zeroed in TextureRenderCore constructor only
            int ctorZeroed12c; // 0x0000012C length: 4
            undefined1 padding_0x130[1004]; // 0x00000130 length: 1004
            GMFileHeaderColorpalette gmFileHeaderColorpaletteArray[240]; // 0x0000051C length: 1249920
            // loadGMFile writes the name into slot gmID and passes it to resolveResourceFileName: used, not UNUSED
            char gmFileNameArray[240][1001]; // 0x0013179C length: 240240
            GfxRef loadedGfxArray[100]; // 0x0016C20C length: 1600
            int totalLoadedGfx; // 0x0016C84C length: 4
            int backwardsLoadedGfxIndex_0x16C850; // 0x0016C850 length: 4
            RECT renderingRect_16c854; // 0x0016C854 length: 16
            // [251 0x0044CCD0] backup of mapGameSurfaceHeightRange written here and restored by
            // restoreMapSurfaceHeightRangeFromTemporaryUnk
            Range savedMapGameSurfaceHeightRange; // 0x0016C864 length: 8
            undefined1 padding_0x16c86c[24]; // 0x0016C86C length: 24
            // [253 0x00454CB0] receives the 256-entry 16-bit palettes converted from each campaign map's .act data
            // There should actually be place for 6, if I understand the code right, but the space is not provided.
            ushort campaignMapPalettes16[6][256]; // 0x0016C884 length: 3072

        private:
            TextureRenderCore(TextureRenderCore const&);
            void operator=(TextureRenderCore const&);

        public:
            TextureRenderCore() {};
            ~TextureRenderCore() {};

            // Constructor
            /**
             * Initialises the global TextureRenderCore: stores buffer sizes, sets render targets (draw=RT_MAP_GAME,
             * secondary=RT_SCREEN_MENU), clears flags and memory, mallocs the processed GM image buffer, the two
             * optional unknown buffers (size and size/2), the gm/gfx image buffer and an unchecked 0x4a400-byte
             * face bitmap buffer. bufferAllocStateUnk_0x0 = 0 on success, 1/2/3 identify which allocation failed.
             */
            TextureRenderCore* Constructor_TextureRenderCore(
                int processedImageDataBufferSize, int gmAndGfxImageDataBufferSize, int unknownMemSize);

            /**
             * Destructor: frees (if non-null) gmProcessedImageData, unknownMemPtr_1_0x80, address2, the bitmap
             * faces buffer bitmapsFaces_0x94 and gmAndGfxImageDataBuffer.
             */
            void Destructor_TextureRenderCore();

            /**
             * Loading-screen progress bar: if more than 30 ms passed since the last update, draws a dark-red bar
             * from menu offset (0xEC, 0x23B) of length currentGmId*328/barLengthUnk (8 px high) and blits that
             * strip of the menu surface to the screen. Used while loading GM files, WAV sounds and map headers.
             */
            void drawLoadingProgressBar(GmID currentGmId, int barLengthUnk);

            /**
             * If the display is RGB565, converts the colour palette block of GM gmID (0xA00 entries = 10 palettes x
             * 256) in place from RGB555 to RGB565 by shifting red/green up one bit.
             */
            void transformGmColorTableFromRGB555To565IfRequired(int gmID);

            /**
             * Converts imageSize bytes of an uncompressed GM image at gmProcessedImageData+imageOffset in place
             * from RGB555 to RGB565, leaving the transparency marker 0xF81F untouched.
             */
            void transformRawSkippingMagentaRGB555To565(int imageOffset, int imageSize);

            /**
             * Walks a TGX RLE stream of tgxByteSize bytes and converts its pixel data in place from RGB555 to
             * RGB565: token high bits 0x40 = one repeated pixel (converted unconditionally), 0x20 = transparent run
             * and 0x80 = line end carry no pixels, every other token (normally 0x00) is a stream of (n+1) pixels
             * (0xF81F left untouched).
             */
            void transformTgxFromRGB555ToRGB565(ushort* tgxDataPtr, int tgxByteSize);

            /**
             * Converts one 256-pixel (0x200-byte) tile object at gmProcessedImageData+imageOffset in place from
             * RGB555 to RGB565 (no transparency check). Really __thiscall on TextureRenderCore (reads
             * gmProcessedImageData via ECX+0x78, ret 4); the returned value is only the leftover EAX (low word =
             * last converted pixel) and carries no meaning.
             */
            void transformTileObjectToRGB565(int imageOffset);

            /**
             * Converts imageSize bytes of an uncompressed GM image at gmProcessedImageData+imageOffset in place
             * from RGB555 to RGB565 (no transparency marker check).
             */
            void transformRawToRGB555To565(int imageOffset, int imageSize);

            /**
             * Converts a 24-bit colour laid out 0x00BBGGRR (COLORREF order: low byte = red) to the screen's 16-bit
             * format: RGB555 or RGB565 with red (bits 3..7) in the high bits, green in the middle and blue (bits
             * 19..23) in the low 5 bits.
             */
            RGB15 transformBGR24ToScreenColor(BGR24 color);

            /**
             * Zeroes 0x80 bytes of each of the two TGX run-length jump tables (tgxRepeatPixelRunJumpTable,
             * tgxPixelStreamRunJumpTable; refilled lazily by renderFunctionResponsibleForManyGameObjects when entry 0 is
             * null), two other 0x80-byte tables (gmRepeatRunFillJumpTable, PTR_ARRAY_GmRunCopyJumpTable) and the
             * 0x4200-byte DAT_BlendFilterArrays.
             */
            void clearSomeMemory();

            /**
             * Sets the vertical clip range (start, end) of the off-screen map-game surface.
             */
            void setMapSurfaceHeightRange(int start, int end);

            /**
             * Resets the map-game surface vertical clip range to its full height 0..0x81B. NAME?
             * resetMapSurfaceHeightRange.
             */
            void resetMapSurfaceHeightRange();

            /**
             * Saves the current map-game surface clip range into the temporary backup field.
             */
            void saveMapSurfaceHeightRange();

            /**
             * Restores the map-game surface clip range from the temporary backup field.
             */
            void restoreMapSurfaceHeightRange();

            /**
             * Sets the vertical clip range (start, end) of the screen/menu surface.
             */
            void setScreenMenuSurfaceHeightRange(int start, int end);

            /**
             * Resets the screen/menu surface vertical clip range to 0..resolutionY.
             */
            void setScreenMenuSurfaceHeightRangeToResolution();

            /**
             * Copies a 64x66 bitmap face (stride 0x2100 bytes in bitmapsFaces_0x94) to (xPos, yPos) on the surface
             * selected by drawBufferChoiceValue (map-game, button/alpha or screen-menu), skipping magenta pixels.
             * No clipping.
             */
            void drawBitmapFace(int bitmapFaceIndex, int xPos, int yPos);

            /**
             * Draws a bitmap face downscaled by 2 (32x33: every second pixel of every second row of the 64x66 face)
             * at (drawX, drawY) on the map-game, button/alpha or screen-menu surface, skipping magenta. No
             * clipping. NAME? renderBitmapFaceHalfSize.
             */
            void drawBitmapFaceHalfSize(int facesIndex, int drawX, int drawY);

            /**
             * Draws a 64x66 bitmap face with a 0..32 blend value b: 0 = plain drawBitmapFace, 32 = nothing. In
             * RGB565 mode each non-magenta pixel becomes src*(32-b)/32 + dst*b/32 per channel (fade into
             * background); in RGB555 mode it writes only src*b/32 without reading the background, i.e. inverted
             * weighting - inconsistent with the RGB565 path (likely original bug, confirmed in machine code).
             */
            void drawBitmapFaceWithBlend(int bitmapFaceIndex, int xPos, int yPos, int colorOrBlendOrGammaUnk);

            /**
             * Core TGX (RLE) sprite blitter: selects the target surface and its vertical clip range (button/alpha
             * surface: 0..imageHeight), clips the bottom, lazily fills the two 32-entry run-length jump tables,
             * skips rows above the clip start, then dispatches pixel-stream (0x00) and repeat-pixel (0x40) runs to
             * unrolled copy routines via 'jmp [table+n*4]' (decompiled as calls); 0x20 skips transparent pixels,
             * 0x80 ends a row. No horizontal clipping: drawX < 0 draws nothing. In zoomed-out mode (isZoom2) it
             * draws onto the map surface at half resolution, keeping every second pixel of every second row. NAME?
             * renderTgxImage.
             */
            void renderTgxImage(
                int drawX, int drawY, int imageWidth, int imageHeight, ushort* imageAddress);

            /**
             * Draws a TGX run-length-encoded 16-bit image (tokens: 0x00 pixel stream, 0x20 transparent skip, 0x40
             * repeated pixel, 0x80 end of line) at (x,y), alpha-blending each pixel with the surface: result =
             * src*(32-s)/32 + dst*s/32 via the DAT_BlendFilterArrays lookup tables (s = blendStrengthUnk, 0..32,
             * weight of the existing pixel; in the non-zoom path the parameter is then reused as the line byte
             * size). Picks screen-menu or map surface from drawBufferChoiceValue, skips source rows above the
             * surface height range and clips at its end, draws nothing when x < 0, has separate RGB555/RGB565
             * paths, and when isZoom2 is set draws at half scale onto the map surface (every other pixel and row).
             * Generic blended-TGX renderer used by renderGMWithBlending, renderGfxTgxWithBlending,
             * renderGMWithAlphaMask (zoom) and renderMap.
             */
            void renderTgxWithBlending(
                int x, int y, int width, int height, ushort* imageDataPtr, int blendStrengthUnk);

            /**
             * Darkens every non-zero (non-black) pixel in the inclusive rectangle (drawX,drawY)-(drawXEnd,drawYEnd)
             * of the PencilRenderCore surface by scaling its colour channels with DAT_BlendFilterArrays[strength]
             * (factor strength/32). blendStrengthUnk > 64 becomes 0 (black), values 33..64 are mirrored to 64-s;
             * RGB555 and RGB565 paths.
             */
            void renderBlendedBlackBox(int drawX, int drawY, int drawXEnd, int drawYEnd, int blendStrengthUnk);

            /**
             * Draws a TGX RLE 16-bit image at (x,y) using a per-pixel alpha mask held in AlphaAndButtonSurfaceObj
             * (low 5 bits, advanced in lockstep with the image, width per skipped row): alpha = mask -
             * blendStrength; alpha<=0 skips, 31 copies the source pixel, otherwise blends src*alpha/32 +
             * dst*(32-alpha)/32 via DAT_BlendFilterArrays. Clips vertically to the selected surface's height range,
             * draws nothing when x < 0; RGB555 and RGB565 paths.
             */
            void renderGmWithPreparedAlphaMask(
                int x, int y, int width, int height, ushort* imageDataPtr, int blendStrength);

            /**
             * Draws the shape of a TGX RLE image at (xPos,yPos) with every opaque pixel replaced by the solid
             * colour fillColorUnk (source colours ignored); used for text glyphs. Selects screen-menu or map
             * surface, clips vertically, draws nothing when xPos < 0; the width parameter is reused as the per-row
             * byte skip.
             */
            void renderTgxWithSolidColor(
                int xPos, int yPos, int width, int height, ushort* imageSource, ushort fillColorUnk);

            /**
             * Anti-aliased text-glyph renderer: for each opaque TGX pixel computes coverage = (32-blendStrengthUnk)
             * * (top 5 green bits of the source pixel) / 32; coverage 31 writes fillColorUnk, otherwise each RGB
             * channel of the destination is moved towards fillColorUnk by coverage/32. For repeat runs coverage is
             * computed once. Channel shifts depend on RGB555/565 (width parameter reused as red shift). Clips
             * vertically to the selected surface.
             */
            void renderTgxWithColorAndBlending(int xPos, int yPos, int width, int height, ushort* imageSource,
                ushort fillColorUnk, int blendStrengthUnk);

            /**
             * Draws an 8-bit palette-indexed TGX sprite (GM file, e.g. units) at (xPosition,yPosition): palette =
             * GM header palette of currentlyRenderedGmID for the owner's colour slot (the global
             * DAT_RenderedUnitOwner is swapped 1<->4 in place first; mbr_0x10 selects raw owner index instead of
             * PlayerSlotUnitColor; mbr_0x70 overrides the palette pointer). Normal path is inline assembly:
             * unrolled copy/fill blocks reached through two 32-entry jump tables indexed by run length (0xB98710
             * for 0x00 stream runs, 0xC9A490 for 0x40 repeat runs, filled lazily on first use) that the decompiler
             * cannot follow; isZoom2 path draws at half scale onto the map surface.
             */
            void renderPalettedTgx(int xPosition, int yPosition, int width, int height, byte* imageAddress);

            /**
             * Blended renderer for an 8-bit palette-indexed (GIT_Animation) TGX picture at (xPosition,yPosition):
             * palette = PlayerSlotUnitColor[owner] 0x200-byte colour table of GM header currentlyRenderedGmID (or
             * paletteOverridePtr if set); owner 1/4 are swapped by rewriting DAT_RenderedUnitOwner (persistent side
             * effect, done even when nothing is drawn). Each pixel = src*(32-s)/32 + dst*s/32 via
             * DAT_BlendFilterArrays (s = blendStrengthUnk = weight of the existing pixel; s >= 32 draws nothing).
             * Clips vertically only (x < 0 draws nothing); RGB555/565 paths; each row restarts from the saved row-
             * start pointer + lineByteStride; isZoom2 path draws every second column/row at half scale onto the map
             * surface.
             */
            void renderPalettedTgxWithBlending(
                int xPosition, int yPosition, int width, int height, byte* imageAddress, int blendStrengthUnk);

            /**
             * Loads a .gfx (16-bit TGX) resource into gmAndGfxImageDataBuffer at the next forward slot
             * (loadedGfxArray[totalLoadedGfx].offsetInBuffer), failing with -1 if offset+size would exceed
             * 0x1167910 bytes or the read fails. Converts to RGB565 if needed, records width/height from the 8-byte
             * header and the next slot's offset, and returns the new gfx index (totalLoadedGfx is incremented).
             */
            int loadGfxFile(char const* tgxFileName);

            /**
             * Same as loadGfxFile but for an 8-bit .gfx8 resource (FRT_GFX8): reads it into the next forward slot
             * of gmAndGfxImageDataBuffer without colour conversion, records width/height and returns the new gfx
             * index or -1.
             */
            int loadGFX8(char* gfx8Filename);

            /**
             * Loads a .gfx resource into the END of gmAndGfxImageDataBuffer, growing downwards: destination =
             * buffer + 0x1167910 - loadedGfxArray[idx].backwardsOffsetInBuffer - size (Ghidra prints the constant
             * 0x1167910 as &DAT_GameState+0x3c858; confirmed in machine code). No overlap check against the
             * forward-loaded data. Converts to RGB565 if needed, stores offset/width/height in loadedGfxArray[idx]
             * (idx = backwardsLoadedGfxIndex_0x16C850), writes the new cumulative backwards offset into slot idx-1
             * and also into slot idx, decrements the index and returns the used gfx index (-1 on read failure).
             */
            int loadGfxAtBufferEnd(char* fileName);

            /**
             * Returns true if a .gfx resource with the given file name exists (non-zero resource size after
             * resolving it via the resource manager).
             */
            BOOLEnum checkGfxResourceExists(char* gfxFileName);

            /**
             * Draws loaded gfx #loadedGfxIndex (TGX data after its 8-byte header) at (xPos,yPos) via
             * renderFunctionResponsibleForManyGameObjects, temporarily switching drawBufferChoiceValue to
             * currentRenderSurfaceIdentifierUnk_0x8.
             */
            void renderLoadedGfx(int loadedGfxIndex, int xPos, int yPos);

            /**
             * Resets the clipping rectangle renderingRect_16c854 to (0,0)-(resolutionX,resolutionY).
             */
            void setRenderingRectToGameResolution();

            /**
             * Sets the clipping rectangle renderingRect_16c854 to left=xPos, top=yPos, right=width, bottom=heigth.
             * The last two are used as exclusive right/bottom bounds by drawTgxOnFlaggedSurface, so they are end
             * coordinates rather than sizes.
             */
            void setRenderingRect(int xPos, int yPos, int width, int heigth);

            /**
             * Returns TRUE if the first TGX token of loaded gfx #gfxIndex is a transparent-skip token (0x20), i.e.
             * the image starts with transparent pixels.
             */
            BOOLEnum checkIfGfxTgxStartsWithTransparentPixels(int gfxIndex);

            /**
             * Draws loaded gfx #gfxIndex at (x,y) blended with the background via
             * renderInterfaceOrBuildingOccupationArea (blendStrengthUnk = weight of the existing pixel; only if
             * 0..31, unsigned compare), temporarily switching drawBufferChoiceValue to
             * currentRenderSurfaceIdentifierUnk_0x8.
             */
            void renderGfxTgxWithBlending(int gfxIndex, int x, int y, int blendStrengthUnk);

            /**
             * Copies a 16-bit TGX RLE image opaquely onto the surface named by
             * currentRenderSurfaceIdentifierUnk_0x8 (screen menu or map), clipped to renderingRect_16c854 both
             * vertically (top/bottom) and horizontally (left/right) per run. Stream and repeat runs are partially
             * drawn when they straddle the clip edges. The gfxWidth parameter is reused as the destination row-skip
             * in bytes.
             */
            void drawTgxOnFlaggedSurface(int xPos, int yPos, int gfxWidth, int gfxHeight, ushort* tgxSourcePtr);

            /**
             * For each campaign map palette file in DAT_BlendingDefinedData.campaign_map_england.. (pointer list
             * ending at 0xab8730; campaign_map_england_{black,yellow,orange,red,blue,basic}.act in the GFX8 folder)
             * reads the first 0x300 bytes (256-entry RGB .act palette) and converts each entry to a 16-bit RGB565
             * or RGB555|0x8000 colour, storing the palettes consecutively (256 entries each) from
             * campaignMapPalettes16[0]; 0xfc1f is remapped to 0xf81f. The inner loop converts 4 entries per
             * iteration (0x40 iterations).
             */
            void loadCampaignMapPalettes();

            /**
             * Sets activeMenuTabIndex to the argument + 1 (so 0 means no active tab).
             */
            void setActiveMenuTabIndex(int indexToSetToMinusOne);

            /**
             * Clears activeMenuTabIndex (no active menu tab).
             */
            void setActiveMenuTabIndexToZero();

            /**
             * For the active menu tab, walks a list of rectangles (x,y,w,h, 4 ints each; up to 10 per tab at
             * 0xab8730 + (activeMenuTabIndex-1)*0xa0, shown by Ghidra as field166_0x2dfc[tab*0x28+0x5e]); -1 ends
             * the list, a -2 entry is a separator after which the remaining rects are used only at resolutions
             * other than 800x600. Copies every non-magenta pixel of each rect from the screen-menu surface (offset
             * by the menu position) into the map surface at the camera offset, so menu parts overlapping the map
             * get baked into it.
             */
            void moveOverlappingMenuPartsToMapSurface();

            /**
             * Converts GM image #imageIndex (uncompressed with marker format) from RGB555 to RGB565 via
             * transformRawWithMarkerUnkToRGB555To565 using DAT_GMImageOffsets/DAT_GMImageSizes.
             */
            void transformUncompressedImageWithMarkerUnkToRGB565(int imageIndex);

            /**
             * Converts TGX-compressed GM image #imageIndex inside gmProcessedImageData from RGB555 to RGB565 via
             * transformTgxFromRGB555ToRGB565.
             */
            void transformTgxCompressedImageToRGB565(int imageIndex);

            /**
             * Converts tileset GM image #imageIndex to RGB565: the 0x200-byte diamond tile via
             * transformTileObjectToRGB565, then, if the image header's direction field is non-zero (tile has a TGX
             * upper part), the remaining TGX data after the tile. this_00 is the TextureRenderCore still live in
             * ECX (transformTileObjectToRGB565 is __thiscall and does not modify ECX).
             */
            void transformTilesetToRGB565(int imageIndex);

            /**
             * Converts uncompressed GM image #imageIndex from RGB555 to RGB565 via transformRawToRGB555To565.
             */
            void transformUncompressedImageToRGB565(int imageIndex);

            /**
             * Draws image imageID (1-based within the GM file) of GM file gmID at (drawX,drawY): global picture
             * index = GMFirstPictureIndex[gmID] + imageID - 1. Interface-element and compressed images (16-bit
             * TGX) go to renderFunctionResponsibleForManyGameObjects, animation (8-bit palettized) images to
             * renderUnitAnimationUnk; other GM types are ignored.
             */
            void renderGM(eGM gmID, int imageID, int drawX, int drawY);

            /**
             * Blended variant of renderGM: blendStrengthUnk = weight of the existing surface pixel (0..32). 32
             * draws nothing, 0 draws opaquely (as renderGM), otherwise TGX images go to
             * renderInterfaceOrBuildingOccupationArea and animation images to renderUnitAnimationWithBlendingUnk.
             */
            void renderGMWithBlending(GmID GmID, int imageID, int drawX, int drawY, int blendStrengthUnk);

            /**
             * Draws a TGX image (only for GM files of type interface element or compressed image) opaquely at
             * (xPos,yPos) via drawTgxOnFlaggedSurface, i.e. onto the surface named by
             * currentRenderSurfaceIdentifierUnk_0x8 and clipped to renderingRect_16c854.
             */
            void drawTgxGmOnFlaggedSurface(GmID gmId, int imageIndexInGm, int xPos, int yPos);

            /**
             * Renders one font glyph (global GM picture imageId) at (xPos, yPos - glyph tileOffset) using
             * renderType: solid colour (renderTgxWithColorUnk), colour with blending by blendStrength
             * (renderTgxWithColorAndBlendingUnk) or raw TGX. When TextManager field9_0x24 or field10_0x28 is set
             * and lineHeight is 27 or 20, the glyph is centred on interface_icons3 icon 0x13/0x14 (icon drawn
             * blended only if field9 is set), +2 x shift if field11_0x2c, and mbr_0x6c = iconWidth - glyphWidth +
             * 3; both flags are then cleared. Also draws a white box behind the glyph when field5_0x14 is 0 and an
             * underline when field6_0x18 is set; nothing is drawn when blendStrength is 32. The yPos/imageId
             * parameter slots are reused for the x shift and the icon id. sVar1 is read via
             * PTR_ARRAY_GmRunCopyJumpTable only because Ghidra folded DAT_GMImageHeaders.imh[first+icon-1].width
             * (machine: 0xb98780+n*16).
             */
            void renderTextChar(int xPos, int yPos, int imageId, FontRenderType renderType, int lineHeight,
                ushort fillColor, int blendStrength);

            /**
             * Draws GM image imageID of gmID at (xPos,yPos) with a per-pixel alpha mask: fills
             * AlphaAndButtonSurfaceObj with magenta, renders mask image alphaImageID of maskGmID into it
             * (RT_BUTTON_AND_ALPHA), then calls renderGmWithPreparedAlphaMask with blendStrength. In isZoom2 (half-
             * scale) mode the mask is skipped and the image is drawn uniformly blended with blendStrength via
             * renderInterfaceOrBuildingOccupationArea.
             */
            void renderGMWithAlphaMask(
                GmID gmID, int imageID, int xPos, int yPos, GmID maskGmID, int alphaImageID, int blendStrength);

            /**
             * Draws loaded gfx #gfxIndex (TGX after its 8-byte header) opaquely at (xPos,yPos) via
             * drawTgxOnFlaggedSurface (surface currentRenderSurfaceIdentifierUnk_0x8, clipped to
             * renderingRect_16c854).
             */
            void drawGfxOnFlaggedSurface(int gfxIndex, int xPos, int yPos);

            /**
             * In RGB565 display mode converts freshly loaded GM picture imageIndex from RGB555 according to the GM
             * file's image type: TGX conversion for interface/font/compressed images, raw conversion for
             * uncompressed images (with or without marker), tile+TGX conversion for tilesets. Does nothing in
             * RGB555 mode or for animations (their palette is converted separately).
             */
            void adaptGmColorsToRGB565IfRequired(int gmID, int imageIndex);

            /**
             * Loads one .gm1 file as GM gmID: pumps one pending window message, copies the file name into
             * gmFileNameArray[gmID] (then used to resolve the resource), reads the 0x1458-byte header+palettes, the
             * per-picture offset, size and 16-byte image-header tables (appended at gmNumberOfProcessedPictures)
             * and the raw image data; converts animation palettes to 565 if needed. Then for every picture i
             * records gmID in DAT_PictureNumToGmIDArray_UNUSED[i] and either aliases data (header byte +0xf bit 2:
             * offset of picture i-1 (DAT_GMImageSizes[i+0x1c51f] == DAT_GMImageOffsets[i-1]); else, only when
             * gmAllowRelativeAliasing and that byte is non-zero: offset of picture i+delta, delta = short
             * relativeDataPos; size always from i+delta) or copies its data into gmProcessedImageData at
             * gmSizeOfProcessedPictures_0x44 + running write offset (new offset, colour conversion). Finally grows
             * gmSizeOfProcessedPictures_0x44 and advances the loading bar.
             */
            void loadGMFile(GmID gmID, char* gmFileName);

            /**
             * Loads all GM files from fileNameArray (1000-byte name slots, terminated by "null", at most 240):
             * first sets DAT_LoadingBarProgress to the number of slots up to and including the "null" one (241 if
             * no "null" within 240 slots), then for each file stores the first global picture index in
             * GMFirstPictureIndex[gmFileID] and calls loadGMFile, numbering GM files and pictures from 1.
             * Afterwards loads the campaign map palettes and sets the font set size to the picture count of GM 0x57
             * divided by 5.
             */
            void loadGmFiles(char* fileNameArray);
        };

        static_assert_cpp98_obj(sizeof(TextureRenderCore) == 1496196, TextureRenderCore);

#pragma pack(pop)

    } // namespace Rendering
} // namespace UI
} // namespace OpenSHC
