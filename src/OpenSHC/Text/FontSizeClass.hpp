/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Text/FontSizeClass.hpp'
*/

#pragma once

#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/IO/Graphics/GmIDInt.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/FontRenderType.hpp"
#include "OpenSHC/Text/FontRenderTypeInt.hpp"

#include "WinDef.h"

namespace OpenSHC {
namespace Text {

    using OpenSHC::IO::Graphics::GmID;
    using OpenSHC::IO::Graphics::GmIDInt;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Text::FontRenderType;
    using OpenSHC::Text::FontRenderTypeInt;

#pragma pack(push, 1)

    // SIZE: 0x00000024
    class FontSizeClass {
    public:
        // Unsigned Double-Word (ddw, 4-bytes)
        GmIDInt fontGmID_0x0; // 0x00000000 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        dword numberOfFontStartInGm_0x4; // 0x00000004 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        int fontStartImageId_0x8; // 0x00000008 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        FontRenderTypeInt renderType_0xc; // 0x0000000C length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        int baselineOffset_0x10; // 0x00000010 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        int lineHeight_0x14; // 0x00000014 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        int letterSpacing_0x18; // 0x00000018 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        int whiteSpaceWidth_0x1c; // 0x0000001C length: 4
        HGDIOBJ hgdiobj; // 0x00000020 length: 4

    private:
        FontSizeClass(FontSizeClass const&);
        void operator=(FontSizeClass const&);

    public:
        FontSizeClass() {};
        ~FontSizeClass() {};

        /**
         * Initialises a FontSizeClass: stores the font GM id, first-glyph index in the GM, render type, baseline
         * offset, line height, letter spacing and whitespace width; sets fontStartImageId to -1 (resolved lazily by
         * the width/render functions).
         */
        void setupFontSizeClassObject(GmID fontGmID, int numberOfFontStartInGm, FontRenderType renderType,
            int baselineOffset, int lineHeight, int letterSpacing, int whiteSpaceWidth);

        /**
         * Returns the pixel width of the first `length` chars of text in this font: mapped glyphs add glyph width +
         * letterSpacing, unmapped printable chars add whiteSpaceWidth, other control chars add 0; result is
         * max(running width, widest line seen). On '\n' the running width is reset only if it exceeds the widest
         * line so far (BUG: after a line not wider than an earlier one the next line is added on top,
         * overestimating multi-line text). Lazily resolves fontStartImageId. If TextManager field9_0x24 or
         * field10_0x28 is set, the first glyph counts as the decorative initial's width + 3 (image 19 or 20 of GM
         * 0x9c for lineHeight 27 / 20) instead of its own.
         */
        int getWidthOfText(char* text, int length);

        /**
         * Extracts the next space-delimited word from text starting at startAndRunIndex into wordReceiver (at most
         * maxWordBufferSize chars, NUL-terminated); stores the number of skipped leading spaces in
         * *wordStartIndexOutPtr and returns the word length (0 for NULL pointers or end of text). Only ' '
         * separates words (not '\n'). In per-character mode (TextManager field12_0x30) returns just the single next
         * char with skip count 0.
         */
        int getWordStartingFromPos(
            char* text, int startAndRunIndex, char* wordReceiver, int maxWordBufferSize, int* wordStartIndexOutPtr);

        /**
         * Word-wraps text to allowedWidth into TextManager.wrappedLines (128-char rows, at most 32 lines; each word
         * is appended with sprintf "%s ", breaking before a word that would exceed the pixel width) and sets count1
         * to the line count. If the whole text fits it is copied as a single line only when shorter than 128 chars
         * (otherwise count1 stays 0); if any single word is wider than allowedWidth count1 is set to 0. Row length
         * in chars is not checked, only pixel width.
         */
        void wrapTextIntoLines(char* text, int allowedWidth);

        /**
         * Returns the advance width of a single char: glyph width + letterSpacing if the char maps to a glyph,
         * whiteSpaceWidth for unmapped printable chars, 0 for unmapped control chars. Lazily resolves
         * fontStartImageId.
         */
        int getCharWidth(byte charUnk);

        /**
         * Converts numberOfChars wide chars to the multibyte code page in a 3000-byte stack buffer and returns
         * getWidthOfText of the result.
         */
        int getWidthOfWideText(LPWSTR wideText, int numberOfChars);

        /**
         * Converts one wide char to the multibyte code page and returns getCharWidth for it.
         */
        dword getWideCharWidth(WCHAR wChar);

        /**
         * Draws textLength chars at (xPos,yPos) in color/blendStrength onto TextManager.textSurfaceTarget and
         * returns the end x. Glyphs are drawn only while x is inside the TextManager clip range (field2_0x8 < x +
         * 5*spaceWidth, x < field3_0xc), otherwise x just advances; unmapped printable chars advance by
         * whiteSpaceWidth and are underlined if field6_0x18 is set; '\n' moves down by baselineOffset +
         * baselineOffset/3 and returns to xPos. Restores the previous draw buffer.
         */
        int renderText(char* text, int textLength, int xPos, int yPos, BGR24 color, int blendStrength);

        /**
         * Word-wraps text to maxWidth starting at (xPos,yPos); words wider than maxWidth are split across lines
         * with a '-' hyphen. Draws only when modeUnk==0. Returns the total height (lineHeight*38/32 for the first
         * line plus one line step per further line) when modeUnk==1, otherwise the widest line width (0 for empty
         * text; a text that fits on one line returns its full width in modes 0/2). Line step is lineHeight*38/32
         * unless TextManager.lineHeightOverride is set; TextManager.lastWrappedTextHeight accumulates the height.
         * wrapPerCharacter mode uses space width 0 and stops at the first wrap.
         */
        int renderOrMeasureWordWrappedText(
            char* text, int xPos, int yPos, int maxWidth, BGR24 color, int blendStrength, int modeUnk);

        /**
         * NAME? (better: renderOrMeasureWrappedWideText) Converts a NUL-terminated wide string to multibyte
         * (3000-byte buffer) and forwards to renderOrMeasureWordWrappedText with the same position, width, color,
         * blend and mode; returns its result (width or height).
         */
        int renderOrMeasureWordWrappedWideText(
            LPWSTR _wideText, int xPos, int yPos, int maxWidth, uint color, int blendStrength, int modeUnk);

        /**
         * Typewriter-style reveal of the wrapped lines in TextManager.wrappedLines (wrappedLineCount must be
         * 1..32): shows the first lengthUnk chars. Fully revealed lines are drawn opaque (blend 0) one below
         * another (step lineHeight*38/32); in the line containing the reveal point the first lengthUnk-1 chars are
         * drawn opaque and the newest char with blend otherBlendValueUnk*32/100 (a transparency percent: 100 =
         * invisible, 0 = opaque). If lengthUnk exceeds the text, everything is drawn opaque.
         */
        void renderWrappedTextTypewriter(int lengthUnk, int otherBlendValueUnk, int xPos, int yPos, BGR24 color);

        /**
         * Draws a single char at (xPos,yPosUnk) in color bgr24 with blend onto the text surface and returns the
         * advanced x (glyph width + letterSpacing + extra initial spacing, or whiteSpaceWidth with optional
         * underline for unmapped printable chars, unchanged for unmapped control chars); outside the clip range it
         * only advances x. Single-char counterpart of renderText.
         */
        int renderChar(byte charId, int xPos, int yPosUnk, int bgr24, int blendStrengthUnk);

        /**
         * Converts textLength wide chars to multibyte (3000-byte buffer) and calls renderText; returns renderText's
         * end x.
         */
        int renderWideText(LPWSTR wideText, int textLength, int xPos, int yPos, BGR24 color, int blendStrength);

        /**
         * Converts one wide char to multibyte and draws it via renderCharUnk; returns the advanced x.
         */
        int renderWideChar(WCHAR wideChar, int xPos, int yPos, int bgr24, int blendStrengthUnk);
    };

    static_assert_cpp98_obj(sizeof(FontSizeClass) == 36, FontSizeClass);

#pragma pack(pop)

} // namespace Text
} // namespace OpenSHC
