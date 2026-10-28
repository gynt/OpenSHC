/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Rendering/PencilRenderCore.hpp'
*/

#pragma once

#include "OpenSHC/Rendering/Enums/RenderTargetInt.hpp"
#include "OpenSHC/UI/Enums/RoundedBoxEdgeRoundingLevel.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::Enums::RenderTargetInt;
        using OpenSHC::UI::Enums::RoundedBoxEdgeRoundingLevel;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

        // SIZE: 0x00000042
        class PencilRenderCore {
        public:
            // [232 0x0045DE40] set to white/black per hover state and passed as the fill color to drawColorBox
            ushort currentFillColor; // 0x00000000 length: 2
            undefined1 padding_0x2[2]; // 0x00000002 length: 2
            ushort* surfacePtr; // 0x00000004 length: 4
            dword horizontalByteSize; // 0x00000008 length: 4
            RenderTargetInt surfaceTarget; // 0x0000000C length: 4
            dword currentX; // 0x00000010 length: 4
            dword currentY; // 0x00000014 length: 4
            dword field8_0x18; // 0x00000018 length: 4
            dword field9_0x1c; // 0x0000001C length: 4
            // [250 0x00468C80] set to +1 if left<=right else -1; added to currentX by the line drawers
            dword stepX; // 0x00000020 length: 4
            // [250 0x00468C80] set to +1 if top<=bottom else -1; added to currentY by the line drawers
            dword stepY; // 0x00000024 length: 4
            // [250 0x00468C80] |right-left|, used as Bresenham dx and loop counter
            int deltaX; // 0x00000028 length: 4
            // [250 0x00468C80] |bottom-top|, decremented as remaining-rows counter
            int deltaY; // 0x0000002C length: 4
            // Also used as state.
            dword drawStartX; // 0x00000030 length: 4
            // Also used as state.
            dword drawStartY; // 0x00000034 length: 4
            // Also used as state.
            dword drawEndX; // 0x00000038 length: 4
            // Also used as state.
            dword drawEndY; // 0x0000003C length: 4
            ushort drawColor; // 0x00000040 length: 2

        private:
            PencilRenderCore(PencilRenderCore const&);
            void operator=(PencilRenderCore const&);

        public:
            PencilRenderCore() {};
            ~PencilRenderCore() {};

            /**
             * Selects the pencil's target surface: the screen-menu surface with its real line pitch when
             * surfaceTarget is RT_SCREEN_MENU, otherwise the off-screen map-game surface with a fixed pitch of
             * 0x1FB0 bytes (4056 pixels).
             */
            void setupPencilSurface();

            /**
             * Stores the draw colour and clips the rectangle (inclusive right/bottom) to the target surface: x to
             * 0..resolutionX-1 (menu surface) or 0..0xFD7 (map surface), y to that surface's configured height
             * range [start, end). Returns FALSE if fully outside; otherwise sets currentX/Y = left/top, the
             * absolute width/height deltas, the x/y step directions (+1/-1) and the normalised drawStart/drawEnd
             * X/Y.
             */
            BOOLEnum setupPencil(int left, int top, int right, int bottom, ushort color);

            /**
             * Fills row drawStartY from drawStartX to drawEndX (inclusive) with drawColor on the pencil surface.
             */
            void drawHorizontalLine();

            /**
             * Fills column drawStartX from drawStartY to drawEndY (inclusive) with drawColor on the pencil surface.
             */
            void drawVerticalLine();

            /**
             * Halves the brightness of every pixel of row drawStartY from drawStartX to drawEndX by masking off
             * each channel's low bit (0x7BDE for RGB555, 0xF7DE otherwise/RGB565) and shifting right.
             */
            void dimHorizontalLine();

            /**
             * Writes drawColor at (currentX, currentY) on the pencil surface.
             */
            void drawCurrentPixel();

            /**
             * Writes a fixed 4x4 block of 16-bit pixels at (drawX, drawY): rows 0x7BCF,0xFFFF,0,0x39C7 /
             * 0x7BCF,0x7BCF,0,0x39C7 / 0x39C7,0x39C7,0,0x39C7 / all 0 (a bevel-like light/white/dark/black pattern,
             * colour values not adapted to RGB565).
             */
            void drawPixelPattern4x4(int drawX, int drawY);

            /**
             * Draws a 64-px-high header banner from 8x8 alpha-masked tiles of GID_INTERFACE_ICONS_3 (top row
             * pictures 0x30.., middle 0x36.., bottom row 0x3C.., each with left/middle/right variants, mask =
             * picture+3) at y = yPos+8.., between xPos+8 and xPos+width-8, then ornament picture 0x5B (mask 0x5C)
             * near both ends. The xPos parameter is reused as the row offset; unusedUnk is ignored.
             */
            void drawHeaderBanner(int xPos, int yPos, int width, int unusedUnk);

            /**
             * Draws a vertical scrollbar at xPos: track tiled with 20-px pictures 0x4F then 1-px pictures 0x5F down
             * to yPos+height, then the thumb at yPos+thumbYPos (single picture 0x59 when thumbHeight <= 20, else
             * top 0x64 / 1-px middle 0x65 / bottom 0x66). A dragged thumb is drawn opaque with renderGM, otherwise
             * alpha-masked with blendStrength like the track.
             */
            void drawScrollbar(
                uint xPos, int yPos, int height, int thumbYPos, BOOLEnum isDragged, int thumbHeight, int blendStrength);

            /**
             * Draws a small arrow button at DAT_ButtonX/Y: picture 0x51 when isDownButtonUnk is non-zero, otherwise
             * 0x55, +1 when DAT_ButtonCurrentlyInteracting; alpha mask is picture+2, blended with blendStrengthUnk.
             */
            void renderUpDownButtonUnk(int isDownButtonUnk, int blendStrengthUnk);

            /**
             * Draws a table-row background across DAT_ButtonW in 20-px tiles. Unselected and not hovered: stripe
             * picture 0x45 or 0x47 by row-index parity. Selected or hovered: left cap 0x49, middle 0x4A, right cap
             * 0x4B (masks 0x4C/0x4D/0x4D). For widths < 21 it increments the global DAT_ButtonW by one and skips
             * the left cap; the right cap is skipped when DAT_ButtonW < 22.
             */
            void drawTableCellBackground(BOOLEnum isSelected, int indexToGetStripes, int blendStrength);

            /**
             * Fills a clipped rectangle (inclusive edges) with a solid colour line by line.
             */
            void drawColorBox(int left, int top, int right, int bottom, ushort color);

            /**
             * Fills a clipped rectangle with a solid colour and rounded corners: the first and last roundingLevel
             * rows are shortened on both sides by per-row dword insets (RBERL_SLIGHT = 5 rows, table at 0xB37CBC =
             * 5,3,2,1,1; RBERL_STRONG = 22 rows, table at 0xB37CE8), the bottom rows using the table in reverse.
             * Does nothing for other levels or when the clipped height is < 2*roundingLevel.
             */
            void drawBoxWithRoundedEdgesAndColor(
                int left, int top, int right, int bottom, ushort color, RoundedBoxEdgeRoundingLevel roundingLevel);

            /**
             * Clips the rectangle and draws a black box blended with the background at blendStrengh via
             * TextureRenderCore::renderBlendedBlackBox.
             */
            void drawBlendedBlackBox(int left, int top, int right, int bottom, int blendStrengh);

            /**
             * Clips the rectangle and halves the brightness of every pixel in it (dimHorizontalLine per row).
             */
            void dimBox(int left, int top, int right, int bottom);

            /**
             * Same rounded-corner rectangle logic as drawBoxWithRoundedEdgesAndColor (inset tables at 0xB37CBC /
             * 0xB37CE8), but halves the brightness of the covered pixels via dimHorizontalLine instead of filling a
             * colour. NAME? dimBoxWithRoundedEdges.
             */
            void drawBoxWithRoundedEdges(
                int left, int top, int right, int bottom, RoundedBoxEdgeRoundingLevel roundingLevel);

            /**
             * Draws a 1-px rectangle outline in the given colour (top, bottom, left and right lines) on the clipped
             * rectangle.
             */
            void drawBorderBox(int left, int top, int right, int bottom, ushort color);

            /**
             * Bresenham line for steep lines (dy > dx): plots at (currentX, currentY), steps currentY every pixel
             * and currentX when the error term is positive, plotting deltaY+1 pixels.
             */
            void drawSteepLine();

            /**
             * Bresenham line for shallow lines (dx >= dy): plots at (currentX, currentY), steps currentX every
             * pixel and currentY when the error term is positive, plotting deltaX+1 pixels.
             */
            void drawShallowLine();

            /**
             * Covers the whole screen (resolutionX x resolutionY) with the fixed 4x4 pixel pattern of
             * drawPixelPattern4x4, using currentX/currentY as loop counters (step 4).
             */
            void drawPixelPattern4x4OverWholeScreen();

            /**
             * Draws a frame of 24x24 alpha-masked border tiles (GID_INTERFACE_ICONS_3 pictures 1-3 top, 7/9 sides,
             * 13-15 bottom, mask = picture+3; interior tiles skipped) with width/height rounded up to multiples of
             * 24, then fills the interior (inset 24 px) with a black box at blend 16.
             */
            void drawBorderedBoxWithBlendedBackground(int xPos, int yPos, int width, int height);

            /**
             * Same 24-px tiled frame as drawBorderedBoxWithBlendedBackground but the tiles use blendStrength and
             * the interior black box uses blend 32+(blendStrength-32)/2.
             */
            void drawBorderedBoxWithCustomBlendedBackground(
                int xPos, int yPos, int width, int height, int blendStrength);

            /**
             * Draws a 1-px line from (x1,y1) to (x2,y2) in the given colour on the current pencil surface: after
             * clipping (setupPencil) picks the vertical (deltaX 0), horizontal (deltaY 0), steep (deltaX < deltaY)
             * or shallow Bresenham routine.
             */
            void drawLine(int x1, int y1, int x2, int y2, ushort color);

            /**
             * Draws the same 64-px tiled header banner as drawHeaderBanner (8x8 alpha-masked tiles plus two 0x5B
             * ornaments) and then the text textGroupIndex/textNumInGroup centred over the inner width at yPos+0x16
             * (font size 0xF, colour 0xC2F0EB, blend 0). The 6th stack parameter is never read (verified in machine
             * code; ret 0x18).
             */
            void drawHeaderTextBanner(
                int textGroupIndex, int textNumInGroup, int xPos, int yPos, int width, int height);
        };

        static_assert_cpp98_obj(sizeof(PencilRenderCore) == 66, PencilRenderCore);

#pragma pack(pop)

    } // namespace Rendering
} // namespace UI
} // namespace OpenSHC
