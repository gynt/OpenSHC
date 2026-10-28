/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Text/TextManager.hpp'
*/

#pragma once

#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTargetInt.hpp"
#include "OpenSHC/Text/FontSizeClass.hpp"
#include "OpenSHC/Text/GameLanguageInt.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/CodePageInt.hpp"

#include "WinDef.h"

namespace OpenSHC {
namespace Text {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Rendering::Enums::RenderTargetInt;
    using OpenSHC::Text::FontSizeClass;
    using OpenSHC::Text::GameLanguageInt;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;
    using OpenSHC::WindowsHelper::Enums::CodePageInt;

#pragma pack(push, 1)

    // SIZE: 0x00057274
    class TextManager {
    public:
        int currentXOffset_0x0; // 0x00000000 length: 4
        // Total height (line heights summed) of the last renderOrMeasureWordWrappedText call; callers add it to y
        dword lastWrappedTextHeight; // 0x00000004 length: 4
        // Left x clip bound for glyph rendering (setTextClipRange param_1, reset 0)
        int textClipMinX; // 0x00000008 length: 4
        // Right x clip bound for glyph rendering (setTextClipRange param_2, reset 10000)
        int textClipMaxX; // 0x0000000C length: 4
        CodePageInt codePage; // 0x00000010 length: 4
        // When 0 renderTextChar draws a white box behind every glyph (debug); loadCRTex sets 1
        dword disableGlyphBackgroundBox; // 0x00000014 length: 4
        // When non-zero glyphs are drawn with an underline (drawLine below baseline); toggled by help rich-text
        // link tokens
        dword underlineText; // 0x00000018 length: 4
        RenderTargetInt textSurfaceTarget; // 0x0000001C length: 4
        // fillIntegerTextBuffer prefixes '+' to positive numbers while set
        dword showPlusSignForPositive; // 0x00000020 length: 4
        // One-shot: next glyph gets a decorative background icon (GID_INTERFACE_ICONS_3) behind it for 0x14/0x1b
        // fonts; cleared by renderTextChar after first char
        int illuminatedInitialPending; // 0x00000024 length: 4
        // Copy of illuminatedInitialPending restored for the shadow/second render pass: applies initial-letter
        // spacing without drawing the icon again
        int illuminatedInitialSpacingPending; // 0x00000028 length: 4
        // Set to 1 around BOTH passes of the two-pass shadowed renders (renderMultilineText6Unk/WideTextUnk,
        // renderNumber2, renderInGameTextWithShadow) and cleared after; while set renderTextChar adds 2 px x offset
        // to the illuminated initial
        dword shadowedTextRenderActive; // 0x0000002C length: 4
        // Word-wrap treats each character as a word (no whitespace width); used for map/player names in narrow
        // table cells; auto-reset after render
        dword wrapPerCharacter; // 0x00000030 length: 4
        // If non-zero replaces font line height in word-wrapped rendering (chat list uses 0x11)
        dword lineHeightOverride; // 0x00000034 length: 4
        dword textColor; // 0x00000038 length: 4
        // This feels like one of the things that might be completely different in the eastern versions.
        int sizeOfOneFontSet_0x3c; // 0x0000003C length: 4
        // [UNK PASS] was alternativeCodePageUsedUnk
        BOOLEnum isCodePage1250; // 0x00000040 length: 4
        GameLanguageInt gameLanguage; // 0x00000044 length: 4
        FontSizeClass fontSizeClassArray[20]; // 0x00000048 length: 720
        // [197 0x00469C40] receives the word-wrapped output lines (32 x 128 chars)
        char wrappedLines[32][128]; // 0x00000318 length: 4096
        // [197 0x00469C40] set to the number of wrapped lines written into stringArray1
        int wrappedLineCount; // 0x00001318 length: 4
        undefined1 padding_0x131c[4]; // 0x0000131C length: 4
        char integerTextBuffer[20]; // 0x00001320 length: 20
        char field26_0x1334[20]; // 0x00001334 length: 20
        // Set 1 after cr.tex was read successfully in loadCRTex
        dword crTexLoaded; // 0x00001348 length: 4
        int textOffsets[260]; // 0x0000134C length: 1040
        char textStart[351000]; // 0x0000175C length: 351000

    private:
        TextManager(TextManager const&);
        void operator=(TextManager const&);

    public:
        TextManager() {};
        ~TextManager() {};

        /**
         * Wrapper: renders a string with a drop shadow (color1 foreground, color2 shadow) via
         * renderInGameTextWithShadow with blendStrength 0.
         */
        void renderInGameText(char* textAddress, int xParam, int yParam, TextAlignment alignment, uint color1,
            uint color2, int fontSize, BOOLEnum keepOffsetX);

        /**
         * Wrapper: renders a plain (unshadowed) string via renderTextToScreen with blendStrength 0.
         */
        void renderTextToScreen2(char* textAddress, int xParam, int yParam, TextAlignment alignment, BGR24 color,
            int fontSize, BOOLEnum keepOffsetX);

        /**
         * Looks up string textNumInGroup of text group textGroupIndex in cr.tex and renders it with a drop shadow
         * (color = foreground, param_7 = shadow colour drawn first at x,y), blendStrength 0.
         */
        void renderText(eTextSections textGroupIndex, int textNumInGroup, int xPosition, int yPosition,
            TextAlignment textShift, uint color, uint param_7, int fontSize, BOOLEnum param_9);

        /**
         * Looks up a cr.tex string by group/index and renders it unshadowed via renderTextToScreen (blendStrength
         * 0).
         */
        void renderText2(eTextSections textOffsetIndex, int textNumInGroup, int xParam, int yParam,
            TextAlignment alignment, uint color, int fontSize, BOOLEnum keepOffsetX);

        /**
         * Looks up a cr.tex string by group/index and renders it with a drop shadow (color1 foreground, color2
         * shadow) and the given blend strength.
         */
        void renderInGameText2(eTextSections textOffsetIndex, int textNumInGroup, int xParam, int yParam,
            TextAlignment alignment, uint color1, uint color2, int fontSize, BOOLEnum keepOffsetX, int blendStrength);

        /**
         * Looks up a cr.tex string by group/index and renders it unshadowed with the given blend strength.
         */
        void renderTextFromTextGroup(eTextSections offsetIndex, int numInGroup, int xParam, int yParam,
            TextAlignment alignment, uint color, int fontSize, BOOLEnum keepOffsetX, int blendStrength);

        /**
         * NAME? Draws nothing: looks up a cr.tex string and calls renderOrMeasureWordWrappedText in mode 1 (measure
         * only, x=y=0, colour 0) with the given wrap width and font, returning the pixel height of the word-wrapped
         * text (mode 1 returns the accumulated line-step total, see 0x4732CF). Callers use it to place text above
         * an anchor or stack two help texts.
         */
        int measureWrappedTextHeight(eTextSections textGroup, int textNumInGroup, int maxWidth, int fontSize);

        /**
         * Looks up a cr.tex string by group/index and renders it word-wrapped to maxWidth (renderMultilineText5Unk)
         * with colour, font and blend strength.
         */
        void renderWrappedTextById(eTextSections textOffsetIndex, int textNumInGroup, int xPos, int yPos, int maxWidth,
            uint color, int fontSize, int blendStrength);

        /**
         * Same as renderMultilineTextUnk with blendStrength 0: renders a cr.tex string word-wrapped to maxWidth.
         */
        void renderWrappedTextByIdNoBlend(eTextSections textOffsetIndex, int textNumInGroup, int xPos, int yPos,
            int maxWidth, uint color, int fontSize);

        /**
         * Looks up a cr.tex string by group/index and renders it word-wrapped with a drop shadow
         * (renderMultilineText6Unk: color2 shadow pass, then color1 foreground).
         */
        void renderWrappedTextWithShadowById(eTextSections textOffsetIndex, int textNumInGroup, int xPos, int yPos,
            int maxWidth, uint color1, uint color2, int fontSize, int blendStrength);

        /**
         * Sets TextManager.field12_0x30=1 (one-shot per-character wrap flag, cleared again by
         * renderMultilineText5Unk) and renders a cr.tex string word-wrapped to maxWidth.
         */
        void renderTextByIdTruncatedToWidth(eTextSections textOffsetIndex, int textNumInGroup, int xPos, int yPos,
            int maxWidth, uint color, int fontSize, int blendStrength);

        /**
         * Renders an integer left-aligned with a drop shadow (color1 foreground, color2 shadow) via renderNumber2,
         * blendStrength 0.
         */
        void renderNumber(
            int number, int xPosition, int yPosition, uint color1, uint color2, int fontSize, BOOLEnum keepOffsetX);

        /**
         * Renders an integer left-aligned without shadow via renderNumberToScreen2, blendStrength 0.
         */
        void renderLeftAlignedNumberToScreen(
            int number, int xParam, int yParam, uint color, int fontSize, BOOL keepOffsetX);

        /**
         * Renders an integer with the given alignment without shadow via renderNumberToScreen2, blendStrength 0.
         */
        void renderNumberToScreen(int number, int xParam, int yParam, TextAlignment alignment, uint color, int fontSize,
            BOOLEnum keepOffsetX);

        /**
         * Returns the pixel width of cr.tex string (group, index) in the given font size.
         */
        int computeTextWidthForTextGroup(eTextSections textOffsetIndex, int textNumInGroup, int fontSize);

        /**
         * Initializes the five anti-aliased Stronghold font objects fontSizeClassArray[15..19] from
         * GID_FONT_STRONGHOLD_AA, each starting at the next font-set offset (sizeOfOneFontSet_0x3c * n), with
         * decreasing size parameters (0x20/0x2E for the largest down to 10/16 for the smallest).
         */
        void setupFontSizeClassObjects();

        /**
         * Sets the horizontal text clipping range (TextManager +0x8 = min x, +0xC = max x) used when rendering
         * text, e.g. for the scrolling crowding ticker.
         */
        void setTextClipRange(dword clipMinX, dword clipMaxX);

        /**
         * Resets the horizontal text clipping range to 0..10000 (effectively unclipped).
         */
        void resetTextClipRange();

        /**
         * Wraps/trims text in place to allowedWidth pixels using the given font (FontSizeClass::wrapTextIntoLines).
         */
        void trimText(char* text, int allowedWidth, int fontSize);

        /**
         * Returns the pixel width of the first cursorIndex characters of text in the given font (0 for NULL text).
         */
        int getTextWidthOfPrefix(char* text, int cursorIndex, int fontSize);

        /**
         * Formats numberInt into TextManager.integerTextBuffer (20 bytes, this+0x1320): optional '-' (or '+' for
         * positives when field8_0x20 is set), then the decimal digits written right to left. The digit count comes
         * from the table at 0xB38340 ({9,1},{99,2}..{99999999,8}; 9 digits if larger).
         */
        void fillIntegerTextBuffer(int numberInt);

        /**
         * Returns a pointer to string numInGroup of cr.tex text group offsetIndex (from
         * textStart+textOffsets[group], skips that many strings, treating runs of NULs as one separator). Some IDs
         * are first remapped to TEXT_SKIRMISH_CHOOSE2 entries: MAINOPTIONS 26-28, BUBBLE_HELP 227/260/268,
         * MAP_TITLES 2, XPLAY_WAITING_ROOM 413, SKIRMISH_CHOOSE 0/1/2/4.
         */
        char* getTextStringInGroupAtOffset(eTextSections offsetIndex, int numInGroup);

        /**
         * NAME? Draws one digit glyph of numberToRenderUnk (used for the gold display): integerPartToRenderUnk
         * selects the decimal position (0=units .. 5=hundred-thousands); positions above the number's length are
         * skipped (early return, eax then holds the low half of the division multiply - garbage); -1 draws special
         * glyph 10 at the same position but advances currentXOffset 2px less; out-of-range positions draw '0'.
         * digitSet 1-3 adds 11/22/33 to the glyph index (y offset 12 for sets 1 and 3, else 17) in GM block 0x92.
         * Draws at currentXOffset+x on textSurfaceTarget, advances currentXOffset by glyph width-2 and returns that
         * advance.
         */
        int renderNumberDigitGlyph(int numberToRenderUnk, int xPosUnk, int yPosUnk, int integerPartToRenderUnk,
            int bgr24, int digitSet, BOOL useCurrentXOffsetUnk);

        /**
         * Returns the pixel width of an integer drawn with digit glyph set digitSet (0-3, glyph offsets 0/11/22/33
         * in GM image block 0x92): sums glyph width-2 for each digit from hundred-thousands down to units, skipping
         * leading zeros. number == -1 returns width-2 of the set's special glyph (index 10/21/32/43; any digitSet
         * other than 0-2 gives 43).
         */
        int calcRenderedNumberWidth(int number, int digitSet);

        /**
         * Returns the pixel width of a single character in the given font size.
         */
        int getCharWidth(char character, int fontSize);

        /**
         * Returns the pixel width of a NUL-terminated string in the given font size (0 for NULL).
         */
        int computeTextWidth(char* text, int fontSize);

        /**
         * Formats an integer into integerTextBuffer and returns its pixel width in the given font size.
         */
        int computeNumberTextWidth(int number, int fontSize);

        /**
         * Loads cr.tex: reads the 0x410-byte group offset table and 0xAB630 bytes (0x55B18 wchars) of UTF-16 text,
         * converts it to code page 1252 into textStart, then detects the language from TEXT_LANGUAGE[0] (polish re-
         * converts with code page 1250 and sets alternativeCodePageUsedUnk;
         * english/american/german/french/italian/spanish set gameLanguage, default English). Then marks text loaded
         * (field27_0x1348), clears a 20-byte buffer and resets the clip range. The malloc'd wide buffer is never
         * freed (one-time leak).
         */
        void loadCRTex();

        /**
         * Renders text word-wrapped to maxWidth with the given font, colour and blend strength
         * (renderOrMeasureWordWrappedText mode 0), then clears TextManager.field12_0x30.
         */
        void renderWrappedText(
            char* text, int xPos, int yPos, int maxWidth, uint color, int fontSize, int blendStrength);

        /**
         * Renders word-wrapped text with a drop shadow: first in color2 at (x,y), then sets field10_0x28 to the
         * value field9_0x24 had on entry and draws in color1 at (x-2,y-1); field11_0x2c is 1 during both passes.
         * NULL text only clears field12_0x30.
         */
        void renderWrappedTextWithShadow(
            char* text, int xPos, int yPos, int maxWidth, uint color1, uint color2, int fontSize, int blendStrength);

        /**
         * Wide-string version of renderMultilineText6Unk: renders word-wrapped UTF-16 text in color2 at (x,y) then
         * color1 at (x-2,y-1) as a drop shadow.
         */
        void renderWrappedWideTextWithShadow(LPWSTR _wideText, int xPos, int yPos, int maxWidth, uint color1, uint color2,
            int fontSize, int blendStrength);

        /**
         * Forwards to FontSizeClass::renderSomeSpecificTextUnk of the given font (only caller: the scrolling
         * credits frame).
         */
        void renderWrappedTextTypewriter(
            int lengthUnk, int otherBlendValueUnk, int xPos, int yPos, uint color, int fontSize);

        /**
         * Renders a string in one colour: resets currentXOffset unless keepOffsetX, measures the width; alignment >
         * 0 centres it in a box of that many pixels starting at x, < 0 right-aligns it ending at x, 0 places it at
         * x + currentXOffset. Advances currentXOffset by the width, then draws. NULL text draws nothing.
         */
        void renderTextToScreen(char* textAddress, int xParam, int yParam, TextAlignment alignment, BGR24 color,
            int fontSize, BOOLEnum keepOffsetX, int blendStrength);

        /**
         * UTF-16 version of renderTextToScreen: measures, aligns (positive alignment = centring box width, negative
         * = right-align, 0 = current x offset), advances currentXOffset and renders.
         */
        void renderWideText(LPWSTR wideText, int xPos, int yPos, TextAlignment alignment, uint color, int fontSize,
            BOOL keepXOffset, int blendStrength);

        /**
         * Formats an integer and renders it with a drop shadow: shadow colour param_6 at (x,y), then foreground
         * color at (x-1,y-1), restoring currentXOffset between passes.
         */
        void renderNumber2(int integer, int xPosition, int yPosition, TextAlignment textShift, uint color, uint param_6,
            int fontSize, BOOLEnum param_8, int param_9);

        /**
         * Formats an integer and renders it in one colour via renderTextToScreen.
         */
        void renderNumberToScreen2(int number, int xParam, int yParam, TextAlignment alignment, uint color,
            int fontSize, BOOLEnum keepOffsetX, int blendStrength);

        /**
         * Renders a string with a drop shadow: backgroundColor at (x,y), then foregroundColor at (x-2,y-1); between
         * the passes restores currentXOffset and sets field10_0x28 to the entry value of field9_0x24.
         */
        void renderInGameTextWithShadow(char const* textAddress, int xParam, int yParam, TextAlignment alignment,
            uint foregroundColor, uint backgroundColor, int fontSize, BOOLEnum keepOffsetX, int blendStrength);
    };

    static_assert_cpp98_obj(sizeof(TextManager) == 356980, TextManager);

#pragma pack(pop)

} // namespace Text
} // namespace OpenSHC
