/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/NewEventCondition.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace NewEventCondition {

            /**
             * Action handler of the 'new event condition' dialog (40 condition slots, each 4 bytes at
             * data+0xC+slot*4: short value, option byte +0xE, enabled flag +0xF). Buttons 0x6A-0x7D select slots
             * 0-19 and 0xBE-0xD1 slots 20-39: the slot is enabled, its value raised to the per-condition minimum
             * and, when a maximum exists, an overlay slider (min..max) is opened. 1000/1001 decrement/increment the
             * value within min/max; 2000 cycles the option backward, 2001 and 2002 forward (kind 1 = -1-terminated
             * value list with wrap, option 0 treated as 10 going forward; kind 2 = 0..4 wrap). 0x13 disables the
             * selected slot, 0x68 toggles the word at data+8, 0x25 (OK) clears slot 0 if any of slots 1-39 is
             * enabled and returns to the new-event dialog. Right-click ids (button+5000) disable a slot, but only
             * when no overlay slider is open and the slider was not changed within the last second.
             */
            void __cdecl MenuItemActionHandler_NewEventCondition_Main(int param_1, ...);

            /**
             * Render callback of the 'new event condition' dialog. Condition buttons 0x6A-0x7D / 0xBE-0xD0 (slots
             * 0-39) are highlighted when selected; enabled conditions show their name, the option text (kind 1:
             * field1235 name of the option value, kind 2: field92 name 0..4) when the condition has a maximum, and
             * value*field1229 right-aligned; disabled ones show only a grey name. 0xD1 (slot 39) is flagged
             * disabled unless one of slots 1,4,5,6,7,17,20,21,22,23 is enabled. 0x68 shows text 0x68/0x69 by the
             * flag word, 0x7E/0x7F enable/disable text for the selected slot, -1 the month name. 1000/1001 (value
             * arrows) and 2000/2001/2002 (option controls) are simply not drawn when the selected condition has no
             * maximum / no option kind; ids > 5000 are not drawn.
             */
            void __cdecl MenuItemRenderFunction_NewEventCondition_Main(int param_1, ...);

        } // namespace NewEventCondition
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
