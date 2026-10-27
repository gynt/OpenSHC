/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/NewEvent.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace NewEvent {

            /**
             * Action handler of the scenario editor 'new event' dialog. 0x13 deletes the current event; 0x25 (OK)
             * parses the year from user text slot 0xb into the event header; both then close the dialog, re-sort
             * events by date and reset the text input to slot 0xf. 100 opens the event-condition sub-dialog
             * (selected condition slot reset to 0), 0x65 the event-action sub-dialog (pending overlay-slider delay
             * cleared), -1 cycles the event month 0..11.
             */
            void __cdecl MenuItemActionHandler_NewEvent_Main(int param_1, ...);

        } // namespace NewEvent
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
