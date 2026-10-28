/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/TextEditor.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace TextEditor {

            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            /**
             * Render callback of the help/text editor buttons: toolbar buttons 1..15 and 20 (Symbols, New Page,
             * Load, Save, Pic, Link, \Link, Font, Centre, \Centre, Colour, LinkClr, Sound, String, Include,
             * ScrSize), Exit (-5) / Back (-4, only with history) help buttons, the type label of the token under
             * the cursor (0x1f), its argument (0x20: picture file, font name, colour name, link/include section,
             * sound file or string number), Left/Centre/Right/Here picture alignment or PREV/NEXT value buttons
             * (0x21-0x24) and scroll arrows (-1/-2).
             */
            void __cdecl MenuItemRenderFunction_TextEditor_Buttons(int param_1, ...);

            /**
             * Scrollbar callback of the help/text editor: scroll range is content height minus dialog height
             * (clamped >= 0), step is range/20 (min 1). Event 1 init, 2/3 set offset, 4 sync, 5/6 scroll up/down by
             * a step with clamping, 7 returns page size (dialog height - 20).
             */
            void __cdecl MenuItemActionHandler_TextEditor_Scrollbar(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            /**
             * Render callback of the help/text editor scrollbar: draws the scrollbar and a yellow frame around it
             * including the 21 px arrow-button areas above and below. The slider value parameter is unused.
             */
            void __cdecl MenuItemRenderFunction_TextEditor_Scrollbar(
                int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged);

            /**
             * Keyboard handler of the help viewer/editor. In view mode it dequeues a key and scrolls the help
             * content (0xF4/0xF5 up/down 18 px, 0xFA/0xFB by one dialog height, 0xF6/0xF7 home/end, clamped to
             * content height - dialog height). In edit mode it first skips a pending freshly inserted token, then
             * inserts printable chars at the caret (and, outside custom-text mode, a tab char 9 / paragraph token 6
             * for keys 0xF0/0xF1; custom-text mode enforces customTextMaxLength), moves the caret over whole
             * control tokens (left/right, home/end, up/down via pendingCaretLineMove), deletes the char/token
             * before (0xF8) or at (0xF9) the caret, relayouts, and finally records the control-token code under the
             * caret (0 for normal text).
             */
            void __cdecl MenuItemActionHandler_TextEditor_HandleKeyboardInput();

            /**
             * Action handler of the help/text editor buttons: Symbols (1, toggles helpDialogSubMode), New Page (2),
             * Load (3, open dialog -> open section) and Save (4, pre-fills both file-dialog buffers with the
             * current section name, then saves); insert control tokens at the cursor (after skipping a pending
             * token): Pic 5 -> PIC 1 (file dialog), Link 6 -> LINK 4, \Link 7 -> code 5, Font 8 -> FONT 2 (default
             * font 17), Centre 9 -> 7, \Centre 10 -> 8, Colour 11 -> COLOUR 3, LinkClr 12 -> 10, Sound 13 -> 11
             * (sound file dialog), String 14 -> 12, Include 15 -> 14 (help file dialog); ScrSize (0x14) toggles the
             * wide layout. For the token under the cursor: 0x20 re-picks its file/section, 0x21/0x22 set PIC
             * alignment Left/Centre or step the font / colour / string-number argument to the previous/next value,
             * 0x23/0x24 set PIC alignment Right/Here. -5 exit, -4 back (history), -3 opens section field50 (view
             * mode) or moves the cursor to field49 (edit mode), -1/-2 scroll 18 px.
             */
            void __cdecl MenuItemActionHandler_TextEditor_Buttons(int param_1, ...);

        } // namespace TextEditor
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
