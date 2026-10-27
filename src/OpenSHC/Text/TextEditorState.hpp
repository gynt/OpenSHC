/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Text/TextEditorState.hpp'
*/

#pragma once

#include "OpenSHC/Text/Enums/HelpTextToken.hpp"
#include "OpenSHC/Text/ImageHotspot.hpp"
#include "OpenSHC/UI/Enums/MenuViewTypeInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "mbstring.h"
#include "winnt.h"

namespace OpenSHC {
namespace Text {

    struct LineLayout {
        short leftBorder;
        short rightBorder;
        short widthForCentering;
    };

    using OpenSHC::Text::ImageHotspot;
    using OpenSHC::Text::Enums::HelpTextToken;
    using OpenSHC::UI::Enums::MenuViewTypeInt;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x00023974
    class TextEditorState {
    public:
        LPWSTR DAT_PointerToTemporaryTextMemory; // 0x00000000 length: 4
        // [198 0x0045F0D0] this+4 is the current length of the edited token buffer, grown by the inserted token
        // length
        int helpTextLength; // 0x00000004 length: 4
        undefined4 isDialogStateInitialized; // 0x00000008 length: 4
        undefined4 helpDialogVariant; // 0x0000000C length: 4
        int useInGameHelpHandler; // 0x00000010 length: 4
        MenuViewTypeInt savedMenuViewType; // 0x00000014 length: 4
        undefined4 savedActiveMenuTab; // 0x00000018 length: 4
        undefined4 savedMenuFlag; // 0x0000001C length: 4
        BOOLEnum pendingCreditsFadeBorder; // 0x00000020 length: 4
        BOOLEnum helpSectionParseSucceeded; // 0x00000024 length: 4
        int currentHelpSectionID; // 0x00000028 length: 4
        int helpSectionHistoryStack[30]; // 0x0000002C length: 120
        // Number of names in UserHelpDefinedData.HelpSections (max 500)
        int helpSectionCount; // 0x000000A4 length: 4
        int helpContentScrollOffsetY; // 0x000000A8 length: 4
        // Layout sets it to total pixel height; max scroll = it - dialogContentHeight; credits restart when offset
        // exceeds it. Not a line index.
        int totalContentHeight; // 0x000000AC length: 4
        int dialogX; // 0x000000B0 length: 4
        int dialogY; // 0x000000B4 length: 4
        int dialogWidth; // 0x000000B8 length: 4
        int dialogHeight; // 0x000000BC length: 4
        int dialogContentX; // 0x000000C0 length: 4
        int dialogContentY; // 0x000000C4 length: 4
        int dialogContentWidth; // 0x000000C8 length: 4
        int dialogContentHeight; // 0x000000CC length: 4
        undefined4 helpContentScrollX; // 0x000000D0 length: 4
        undefined4 helpContentScrollY; // 0x000000D4 length: 4
        // All 4 uses (insert gap, typed chars stored at it, clamped/moved by arrows, reset on open) show it is the
        // editor caret text position.
        int caretTextPos; // 0x000000D8 length: 4
        // Toggled by the 'Symbols' toolbar button; when 1 tokens are printed as tag text instead of applied.
        undefined4 showTagSymbols; // 0x000000DC length: 4
        // 4 consistent uses: gates caret/editing keys, keeps INCLUDE as token, set only by
        // openMapDescriptionEditorDialog.
        undefined4 isEditorMode; // 0x000000E0 length: 4
        undefined4 isCustomTextMode; // 0x000000E4 length: 4
        undefined4 useWideHelpLayout; // 0x000000E8 length: 4
        undefined4 pendingTokenTypeToSkip; // 0x000000EC length: 4
        undefined4 isTextHelpDialogMode; // 0x000000F0 length: 4
        char* customHelpTextPointer; // 0x000000F4 length: 4
        undefined4 isCustomHelpTextWide; // 0x000000F8 length: 4
        undefined4 customHelpTextBufferSize; // 0x000000FC length: 4
        int customTextMaxLength; // 0x00000100 length: 4
        char soundFileNames[5][1000]; // 0x00000104 length: 5000
        byte soundFilePlayedFlags[5]; // 0x0000148C length: 5
        undefined1 padding_0x1491[3]; // 0x00001491 length: 3
        int soundFileCount; // 0x00001494 length: 4
        char graphicFileNames[20][1000]; // 0x00001498 length: 20000
        int graphicFileCount; // 0x000062B8 length: 4
        LineLayout lineLayoutTable[20000]; // 0x000062BC length: 120000
        int imageHotspotCount; // 0x0002377C length: 4
        ImageHotspot imageHotspotTable[50]; // 0x00023780 length: 400
        // [198 0x0045F130] array of 20 wchar_t* cleared here; parseHlp expands <STRING n> from intArray1[n] when
        // helpDialogVariant != 0
        wchar_t* stringSubstitutions[20]; // 0x00023910 length: 80
        // Set when the help/text dialog opens; bltTextToScreenIfNeedBe then blits map game surface back to menu
        // surface (for map editor/build menus) and clears it
        int restoreScreenBltPending; // 0x00023960 length: 4
        // Text index of the glyph under the mouse (set in processHelpRichTextTokens via isMouseInsideBox per glyph,
        // reset -1 each pass); in editor/alternate-tab mode a click (action -3) moves the caret
        // (activeHelpHotspotIndex) there
        int hoveredCharIndex; // 0x00023964 length: 4
        // Link target under the mouse: set from a hovered link-token glyph in processHelpRichTextTokens or from an
        // image hotspot in renderHelpImageHotspots, -1 none; a click (action -3, normal mode) opens
        // openUnusedHelpTextEditorDialog(target)
        int hoveredLinkTarget; // 0x00023968 length: 4
        // Set -1/+1 by editor keys 0xf4/0xf5 (line up/down); the next processHelpRichTextTokens pass moves
        // activeHelpHotspotIndex to the same column on the previous/next line and clears it; non-zero also sets
        // DAT_HelpEditorCursorMoved
        // Set -1/+1 by editor keys 0xf4/0xf5 (line up/down); the next processHelpRichTextTokens pass moves
        // activeHelpHotspotIndex to the same column on the previous/next line and clears it; non-zero also sets
        // DAT_00df334c
        int pendingCaretLineMove; // 0x0002396C length: 4
        // Control-token code (<0x20) at activeHelpHotspotIndex in the edited help text, 0 if plain text; drives
        // editor buttons (1 = PIC)
        int tokenTypeAtCursor; // 0x00023970 length: 4

    private:
        TextEditorState(TextEditorState const&);
        void operator=(TextEditorState const&);

    public:
        TextEditorState() {};
        ~TextEditorState() {};

        // Constructor
        /**
         * Initializes the global TextEditorState: clears dialog flags, resets help state, allocates the 40000-byte
         * help text buffer, sets customTextMaxLength=-1, sets 'counter' to the index of the first empty name in
         * DAT_UserHelpDefinedData.HelpSections (500 x 1000-char names; counter is left unchanged if none is empty),
         * and nulls the 20 STRING substitution pointers. Returns the global.
         */
        TextEditorState* Constructor_TextEditorState();

        /**
         * Sets the help dialog content rectangle (dialogContentX/Y/Width/Height). The prototype's 3rd/4th parameter
         * names are swapped: the 3rd argument is stored into dialogContentWidth and the 4th into
         * dialogContentHeight, and the only caller passes dialogWidth-40 and dialogHeight-45 in that order, so the
         * game logic is correct.
         */
        void setHelpWindowBounds(int x, int y, int height, int width);

        /**
         * Clears the 30-entry help section history stack to -1 and sets currentHelpSectionID to -1.
         */
        void resetHelpStateFields();

        /**
         * Case-insensitively searches the first TextEditorState.counter names in
         * DAT_UserHelpDefinedData.HelpSections for sectionName; returns its index or -1.
         */
        int findHelpSectionIndexByName(char* sectionName);

        /**
         * Returns the index of sectionName in the help section name table, appending it at HelpSections[counter] if
         * not yet present (returns the old counter; counter capped at 500). BUG: the copy is done before the cap
         * check, so with 500 names a new name is written one entry past the array, over the help font table
         * field5_0x7a124, and index 500 is returned.
         */
        int findOrAddHelpSectionName(char* sectionName);

        /**
         * Reads the next token of a wide-char .hlp file into HLP_WCHAR_Buffer and returns it, or NULL at EOF (also
         * when EOF follows a partial token). Outside double quotes a token ends at tab, space, ',' or '=' (further
         * separators are skipped, a following '>' is consumed, any other char is pushed back with fseek -2) or at
         * '>'; inside quotes these chars are stored. Quotes toggle quoting and are not stored; CR/LF are dropped.
         */
        LPWSTR parseHLPPart(FILE* filePointer);

        /**
         * Resets the back-loaded gfx slot index of TextureRenderCore to 99 (and slot 99's buffer offset to 0) and
         * loads every help graphic file (graphicFileNames[0..graphicFileCount)) at the end of the gfx buffer.
         */
        void loadHelpSectionGraphics();

        /**
         * Tokenizer over DAT_PointerToTemporaryTextMemory at *textPos: returns a control char (<0x20) as its value,
         * otherwise copies the next word (up to and including a trailing space, stopping before a control char)
         * into a static wide buffer (no length check) and returns its pointer. Advances *textPos.
         */
        uint readNextControlCharOrWord(int* textPosPtr);

        /**
         * For each image hotspot of the help page: in in-game help or dialog variant 1, images whose gfx does not
         * start with transparent pixels get a 2-px greyish-yellow frame, top-clipped to the content area (BUG: when
         * the frame passes the content bottom its bottom edge is set to y = 2*dialogContentHeight instead of
         * dialogContentY+dialogContentHeight); then draws the gfx (slot 99 - gfx index) at its scrolled position
         * and, if the mouse is over it, stores the hotspot's link value in field50_0x23968.
         */
        void renderHelpImageHotspots();

        /**
         * If field48_0x23960 is set and the saved menu view is map-editor landscaping, build menu or
         * building/status menu, blits the map game surface to the screen menu surface; then clears the flag.
         */
        void bltTextToScreenIfNeedBe();

        /**
         * NAME? (draws nothing) Called from renderMenuModal: stores the dialog rectangle (x,y,width,height),
         * derives the content rectangle by applying the global text-dialog paddings (x+padX, y+padY, width-padW,
         * height-padH), and copies the current camera offset into helpContentScrollX/Y.
         */
        void setDialogRectAndContentArea(int x, int y, int width, int height);

        /**
         * Draws the help window background: a rounded box in custom-text mode; otherwise a black box, or (alternate
         * help tab, not variant 2) a very-dark-grey frame with a black content area plus a 60-px dark cyan-grey
         * strip below (nothing for alternate tab + variant 2). Before drawing, variant 1 points text/pencil output
         * at RT_MAP_GAME, other variants point the texture draw buffer at RT_SCREEN_MENU; afterwards they are set
         * to RT_SCREEN_MENU / RT_MAP_GAME respectively.
         */
        void drawHelpWindowBackground();

        /**
         * Case-insensitively searches graphicFileNames[0..graphicFileCount) for graphicName; returns its index or
         * -1.
         */
        int findHelpGraphicIndexByName(char* graphicName);

        /**
         * Returns the index of graphicName in the help graphic file table, appending it at
         * graphicFileNames[graphicFileCount] if not present (returns the old count; count capped at 20). BUG: the
         * copy happens before the cap check, so with 20 names a new name overwrites graphicFileCount itself and the
         * following lineLayoutTable.
         */
        int findOrAddHelpGraphicName(char* graphicName);

        /**
         * NAME? (fonts, not help sections) Finds fontID in the -1-terminated help font table
         * UserHelpDefinedData.helpFontTable ({font name, font id}: 'Stronghold 14 aa' = 19 ... 'Stronghold 44 aa'
         * = 15) and returns the id of the following entry, wrapping to the first entry; returns -1 if not found.
         */
        int getNextHelpFontId(int fontID);

        /**
         * NAME? (fonts) Finds fontID in the -1-terminated help font table and returns the id of the preceding
         * entry, wrapping to the last entry; returns -1 if not found or the table is empty.
         */
        int getPrevHelpFontId(int fontID);

        /**
         * NAME? (fonts) Returns the font name (text_0x0) of the help font table entry whose id equals fontID, or
         * NULL if not found.
         */
        char* getHelpFontName(int fontID);

        /**
         * Circular next index in the help colour table (UserHelpDefinedData.helpColorTable, {name, r, g, b}
         * entries): entryIndex+1, or 0 if that entry has no name.
         */
        int getNextHelpColorEntryIndex(int entryIndex);

        /**
         * Circular previous index in the help colour table: entryIndex-1, or the index of the last named entry when
         * that would be negative.
         */
        int getPrevHelpColorEntryIndex(int entryIndex);

        /**
         * Case-insensitively searches soundFileNames[0..soundFileCount) for soundName; returns its index or -1.
         */
        int findSoundIndexByName(char* soundName);

        /**
         * Returns the index of soundName in the help sound file table, appending it at
         * soundFileNames[soundFileCount] and clearing its soundFilePlayedFlags entry if not present (returns the
         * old count; count capped at 5). BUG: the copy happens before the cap check, so with 5 names a new name
         * overwrites soundFilePlayedFlags, soundFileCount and the start of graphicFileNames.
         */
        int findOrAddSoundName(char* soundName);

        /**
         * Saves the in-memory help token stream (DAT_PointerToTemporaryTextMemory) to the FRT_HELP file named after
         * the current help section (HelpSections[currentHelpSectionID], not crusader_help.hlp): UTF-16 BOM,
         * <HEADER> with one <LOADPIC="name"> per loaded graphic (graphicFileNames, 1000-byte stride), then <BODY>
         * where each token code (1 PIC [4 wchars: id, alignment LEFT/CENTRE/RIGHT/HERE], 2 FONT/3 COLOUR/4 LINK/10
         * LINKCOLOUR/11 SOUND/12 STRING/14 INCLUDE [3 wchars], 5-8 single-wchar tags) is printed as its tag and
         * every other wchar verbatim. No <SECTION> wrapper is written.
         */
        void saveHelpFileToResource();

        /**
         * Returns the length in wchars of a help text token of the given type: 4 for PIC (1), 3 for the value-
         * carrying tokens FONT/COLOUR/LINK/LINKCOLOUR/SOUND/STRING/INCLUDE (2,3,4,10,11,12,14), 1 for everything
         * else (single tags and plain characters).
         */
        int helpToken_getHelpTokenAdvanceLength(HelpTextToken tokenType);

        /**
         * Makes room for a token in the editor text buffer: shifts every wchar from the caret position
         * (activeHelpHotspotIndex, this+0xD8) up to and including the terminator at the text length (this+4) right
         * by the token's length, then grows the text length by that amount. extraout_ECX is just `this` (ECX
         * survives the callee).
         */
        void helpToken_insertSpaceForHelpTextToken(HelpTextToken token);

        /**
         * If a help dialog is open: resets help state and then either (custom text mode) closes the modal, clears
         * the STRING substitutions and copies the edited text back to the caller's buffer (wcsncpy if wide, else
         * converted to multibyte) and sets DAT_MenuView_TriggerPrepare; or (helpDialogVariant==0) returns to the
         * saved menu view/tab (build menu, landscaping, building/status menu or generic); or (modal help variant)
         * closes the modal and clears the substitutions. Resets helpDialogVariant to 0 in every path.
         */
        void closeHelpDialogAndReturnToMenu();

        /**
         * Opens crusader_help.hlp (FRT_HELP) for binary read, skips the BOM and scans '<' tags until it finds
         * <SECTION name> matching searchedPart (case-insensitive), then skips to the closing '>' and sets
         * helpSectionParseSucceeded. Returns the FILE* (ESI) positioned at the section body, or at EOF if not found
         * (caller must fclose); NULL if the file cannot be opened. Decompiler shows the return through
         * __security_check_cookie.
         */
        FILE* readCrusaderHelpHlp(LPCSTR searchedPart);

        /**
         * Checks whether a help section named searchedPart exists in crusader_help.hlp: opens/seeks it via
         * readCrusaderHelpHlp, closes the file and returns TRUE if the section header was found.
         */
        BOOLEnum loadAndParseHelpFile(char const* searchedPart);

        /**
         * Parses the current help section (HelpSections[currentHelpSectionID]) of crusader_help.hlp into the
         * 40000-byte token buffer: plain chars copied only inside <BODY> (curly double quotes -> '"', U+2019 ->
         * '`', CR/LF dropped), tags converted to token codes (PIC 1 with LOADPIC graphic id + alignment, FONT 2,
         * COLOUR 3, LINK 4, \LINK 5, NEWPARAGRAPH 6, CENTRE 7/8, LINKCOLOUR 10, SOUND 11, STRING 12 or inline-
         * expanded substitution text, INCLUDE 14 in editor mode, else the included section is parsed inline via a
         * 4-entry file stack without bounds check). Missing graphics and st99_dog_cage.tgx get id -1 and their PICs
         * are dropped; \SECTION or EOF closes the current file and resumes the parent. Stores the length in
         * helpTextLength. Note: locals parseError / loadPicCounts are really the inside-<BODY> / inside-<HEADER>
         * flags.
         */
        void parseHlp();

        /**
         * Core help rich-text engine. Walks the token buffer word by word (readNextControlCharOrWord) over the per-
         * pixel-row lineLayoutTable (left margin, right margin, centre slack; rows with left margin -1 are
         * skipped). isRenderPass=0 is the incremental layout pass: on reaching the next not-yet-placed
         * LEFT/CENTRE/RIGHT picture it records it in imageHotspotTable, carves the picture (+25 gap, +50 rows) out
         * of the row margins, increments imageHotspotCount and returns 0 so the caller restarts; HERE pictures are
         * placed inline. At end of text it scans forward to the first row with default margins (25 / width-25),
         * stores that +6 in totalContentHeight, in editor mode scrolls helpContentScrollOffsetY to keep the caret
         * rows visible, and returns 1. isRenderPass=1 skips floating pictures, draws words/chars with the current
         * font and text/link colour (TAB token advances 30 px), records the hovered text position and link
         * (hoveredCharIndex/hoveredLinkTarget), marks a SOUND as triggered when its row is visible, and in editor
         * mode draws the caret as two COL_DARK_LIME lines and applies pending caret up/down moves.
         * showTagSymbols==1 renders tokens as raw tag text in colour 0xff. Returns 1 (also immediately when
         * isTextHelpDialogMode==0) except the layout-pass picture restart (0).
         */
        int processHelpRichTextTokens(int isRenderPass);

        /**
         * Renders the help text: sets the clip rect to the dialog content area (map/game surface for the in-game
         * variant 1, screen-menu surface otherwise), runs processHelpRichTextTokens in render mode and draws the
         * image hotspots, then restores full-resolution clipping and the default surfaces.
         */
        void renderHelpTextContent();

        /**
         * Resets the 20000-row line layout table (left margin 25, right margin contentWidth-25, centre slack 0;
         * left margin of the first 4 rows set to -1 = blocked), clears the image hotspot count and calls the layout
         * pass processHelpRichTextTokens(0) repeatedly until it returns nonzero (each 0 means a floating picture
         * was placed and layout must restart).
         */
        void initializeAndLayoutHelpText();

        /**
         * If a help dialog is open, draws its background window and then its text content.
         */
        void renderHelpDialogIfOpen();

        /**
         * Resets graphic/sound counts and scroll, parses the current help section and loads its graphics (unless in
         * custom text mode, where the buffer was filled by the caller), resets the caret position and lays out the
         * text.
         */
        void loadAndLayoutHelpContent();

        /**
         * Opens (or navigates) the building help modal (MMT_BUILDING_HELP_TEXT, variant 1) for help section
         * param_1: returns early if already showing that section, closes the dialog if param_1==-1, otherwise sets
         * dialog/content rectangles (padding 15/13, margins 60/65), pushes the current section onto the 30-entry
         * history and loads/lays out the new section.
         */
        void openBuildingHelpDialog(int helpSectionId);

        /**
         * Opens the in-game help modal (MMT_IN_GAME_HELP_TEXT, variant 1, in-game handler) for help section param_1
         * (-1 closes it): sets dialog/content rectangles (padding 15/13, margins 60/65), pushes the previous
         * section onto the history and loads/lays out the section.
         */
        void openInGameHelpDialog(int helpSectionId);

        /**
         * Opens the scenario description help modal (MMT_DISPLAY_SCENARIO_HELP_TEXT, variant 2) for help section
         * param_1 (-1 closes): padding 10/10, margins 45/20, pushes history and loads/lays out the section.
         */
        void openScenarioHelpDialog(int helpSectionId);

        /**
         * Opens the credits scroll modal (MMT_CREDITS_SCROLL, variant 2) showing help section param_1 (-1 closes)
         * with zero padding (content = whole modal), pushes history and loads/lays out the section.
         */
        void openCreditsScrollDialog(int helpSectionId);

        /**
         * Opens the map description editor modal (MMT_MAP_DESCRIPTION_EDITOR) in editable custom-text mode (variant
         * 0, useAlternateHelpTab=1 editor flag); param_1==-1 closes it instead, otherwise param_1 is only a flag
         * and its stack slot is reused as the modalX output. Clears customHelpTextPointer and isTextHelpDialogMode
         * (so layout is a no-op until setCustomHelpText), sets rectangles (padding 10/10, margins 45/53), pushes
         * the current section on the history, sets current section -1 and calls loadAndLayoutHelpContent.
         */
        void openMapDescriptionEditorDialog(int openFlagThenModalX);

        /**
         * Sets a caller-owned multibyte text (e.g. map description) as the editable help text: remembers the
         * pointer and buffer size (non-wide), converts it to wide into the text buffer, stores its length, enables
         * text dialog mode and lays it out.
         */
        void setCustomHelpText(char* text, int bufferSize);

        /**
         * Help 'back' navigation: pops the previous section id from the 30-entry history stack (shifting the rest
         * down, filling the last slot with -1); closes the dialog if the history was empty (-1), otherwise reloads
         * and lays out that section.
         */
        void popHelpDialogStack();

        /**
         * NAME? Generic 'open help section' dispatcher (window messages, text-editor buttons), not only the unused
         * editor dialog: helpDialogVariant 2 forwards to openScenarioHelpDialog, a nonzero useInGameHelpHandler to
         * openInGameHelpDialog, other nonzero variants to openBuildingHelpDialog. For variant 0 it saves the
         * current menu view/tab on first open, resets the caret (activeHelpHotspotIndex) to 0, closes on
         * helpSectionId -1, else switches to MVT_UNUSED_HELP_TEXT_EDITOR (tab chosen by useAlternateHelpTab) with a
         * 640x480 dialog (content 600x435, or 664x291 in wide layout), pushes the current section onto the 30-entry
         * history stack, sets the new section, resets scroll and calls loadAndLayoutHelpContent.
         */
        void openHelpSection(int helpSectionId);
    };

    static_assert_cpp98_obj(sizeof(TextEditorState) == 145780, TextEditorState);

#pragma pack(pop)

} // namespace Text
} // namespace OpenSHC
