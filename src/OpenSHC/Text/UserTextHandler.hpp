/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Text/UserTextHandler.hpp'
*/

#pragma once

#include "OpenSHC/Text/TextArrayIndexTypeInt.hpp"

namespace OpenSHC {
namespace Text {

    using OpenSHC::Text::TextArrayIndexTypeInt;

#pragma pack(push, 1)

    // SIZE: 0x00001114
    class UserTextHandler {
    public:
        TextArrayIndexTypeInt textArrayIndex; // 0x00000000 length: 4
        // [201 0x00469790] set to 1 when a slot is activated/cleared/filled; getCurrentText returns NULL and
        // handleCharacterCode ignores typed characters while it is 0 Unsigned Double-Word (ddw, 4-bytes)
        dword textInputActive; // 0x00000004 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        dword returnPressed; // 0x00000008 length: 4
        // [201 0x00469790] resetToTextIndex only switches/activates a slot while this is 0, i.e. a non-zero value
        // blocks it - the opposite of what 'allow' suggests Unsigned Double-Word (ddw, 4-bytes)
        dword textSlotSwitchLocked; // 0x0000000C length: 4
        int textArrayFontSizes[16]; // 0x00000010 length: 64
        int textBoxMaxCharactersArray[16]; // 0x00000050 length: 64
        int textContentLengthArray[16]; // 0x00000090 length: 64
        int textCursorIndexArray[16]; // 0x000000D0 length: 64
        int textBoxMaxTextWidthDimensionArray[16]; // 0x00000110 length: 64
        // Created by retype action
        char textArray[16][250]; // 0x00000150 length: 4000
        char inputBuffer[30]; // 0x000010F0 length: 30
        undefined1 padding_0x110e[2]; // 0x0000110E length: 2
        int inputBufferIndex; // 0x00001110 length: 4

    private:
        UserTextHandler(UserTextHandler const&);
        void operator=(UserTextHandler const&);

    public:
        UserTextHandler() {};
        ~UserTextHandler() {};

        /**
         * Constructor of the global UserTextHandler: sets per-slot font sizes, max character counts and max pixel
         * widths for the text input slots, default strings ('Campaign name string' slot 1, 'Game load string' slot
         * 3, three spaces slot 4, '1181' slots 10/11; slots 2/12-15 empty) with their lengths, selects slot
         * TAIT_NINE__FILTER_B, clears returnPressed and disables text input.
         */
        void Constructor_UserTextHandler();

        /**
         * Activates text slot textIndex (<16) for user text input: makes it the current slot, resets its cursor to
         * 0, marks text input active (unknown01=1) and clears returnPressed. Does nothing while
         * DAT_UserTextHandlerState.textSlotSwitchLocked is non-zero.
         */
        void resetToTextIndex(int textIndex);

        /**
         * Returns the text buffer of the currently active text slot, or NULL if text input is not active (unknown01
         * == 0).
         */
        char* getCurrentText();

        /**
         * Returns a pointer to the 250-byte text buffer of text slot textSlotIndex.
         */
        char* getTextArrayPointer(int textSlotIndex);

        /**
         * Copies string srcText into text slot textSlotIndex (buffers at 0x1652890, stride 250) and sets that
         * slot's content length and cursor position to strlen(srcText). Does not change the active slot or the
         * input flags.
         */
        void setTextEntryAndUpdateCursor(int textSlotIndex, char* srcText);

        /**
         * Returns the font size configured for the currently active text slot.
         */
        int getCurrentFontSize();

        /**
         * Records that Return was pressed in the text input (returnPressed = 1).
         */
        void handleReturnKey();

        /**
         * Right-arrow in text input: advances the active slot's cursor by one if it is before the end of the text.
         */
        void handleRightKey();

        /**
         * Left-arrow in text input: moves the active slot's cursor back by one if it is above 0.
         */
        void handleLeftKey();

        /**
         * Home key: sets the active text slot's cursor to position 0.
         */
        void resetCursorToStart();

        /**
         * End key: sets the active text slot's cursor to the slot's content length.
         */
        void moveCursorToEnd();

        /**
         * Deletes a character in the active text slot by shifting charCount characters starting at startIndex one
         * position to the left (each text[i] = text[i+1]); the shifted-in NUL terminates the string. Used by
         * backspace and delete.
         */
        void shiftTextLeftAtCursor(int startIndex, int charCount);

        /**
         * Opens a gap at cursorIndex in the active text slot for insert mode: writes a NUL at
         * cursorIndex+charsAfterCursor+1, then copies characters backwards one position to the right
         * (text[cursor+k] = text[cursor+k-1] for k = charsAfterCursor..1; the body runs once even when
         * charsAfterCursor is 0). The odd textArray[idx - TAIT_ONE][...+0xf9] expression is the decompiler's view
         * of text[cursor+k-1].
         */
        void shiftTextRightAtCursor(int cursorIndex, int charsAfterCursor);

        /**
         * Queues a typed character into the 30-byte keyboard input FIFO if character filter B allows it (or code >
         * 0xEF). When the FIFO is full the oldest character is dropped (29 bytes shifted left) and the new one is
         * written at index 29.
         */
        void handleCharacterIntoInputBuffer(int characterCode);

        /**
         * Pops the oldest byte from the keyboard input FIFO, shifting the remaining bytes left and decrementing
         * inputBufferIndex. Returns the byte (zero-extended), or 0xFFFFFFFF if the FIFO is empty.
         */
        uint dequeueInputBufferChar();

        /**
         * Returns the pixel width of the active slot's text up to the cursor position (in the slot's font size);
         * render functions use it to place the text caret.
         */
        int getTextWidthUntilCurrentCursor();

        /**
         * Backspace in text input: if the cursor is above 0, moves it left, deletes the character there by shifting
         * the tail left, and recomputes the slot's content length with strlen.
         */
        void handleBackspace();

        /**
         * Zero-fills the active text slot's 250-byte buffer, resets its length and cursor to 0, marks text input
         * active (unknown01=1) and clears returnPressed.
         */
        void clearTextAndCursor();

        /**
         * Zero-fills the 250-byte buffer of text slot textSlotIndex and resets its length and cursor to 0. Unlike
         * clearTextAndCursor it does not change the active slot or the input-active/returnPressed flags.
         */
        void clearEntry(int textSlotIndex);

        /**
         * Clears the active text slot, copies srcText into it, sets its length and cursor to strlen(srcText), marks
         * text input active and clears returnPressed.
         */
        void copyIntoTextArray(char* srcText);

        /**
         * Returns 2 if the active text slot is full, else 0. Full means the rendered text width is >= the slot's
         * max pixel width, or the cursor is at/after the slot's max character count.
         */
        int isTextInputAtCapacity();

        /**
         * Delete key in text input: unless isTextInputAtCapacity returns 2, deletes the character at the cursor by
         * shifting the tail left, then recomputes the content length. Original-game quirk (verified in machine
         * code): when the box is full (pixel width reached) Delete does nothing, unlike Backspace.
         */
        void handleDeleteKey();

        /**
         * Inserts typed characterCode at the cursor of the active text slot; ignored while text input is inactive
         * (unknown01 == 0). Slots 2/3 use character filter A, slots 5/6/7 accept digits only (slot 5 also '.'), the
         * rest use filter B. If the slot is not full: in insert mode (and length < max) it first opens a gap, then
         * (if length < max chars) writes the char, advances and clamps the cursor to [0, maxChars], and recomputes
         * the length with strlen.
         */
        void handleCharacterCode(byte characterCode);
    };

    static_assert_cpp98_obj(sizeof(UserTextHandler) == 4372, UserTextHandler);

#pragma pack(pop)

} // namespace Text
} // namespace OpenSHC
