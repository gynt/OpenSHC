/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuModals/NewEvent.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace NewEvent {

            /**
             * Renders the scenario 'Event' summary modal: for up to 7 enabled conditions (of 40) of the current
             * event prints the condition name (TEXT_SCENARIO[cond+0x6A], or cond+0xAA past 0x7D; ids 0x6F/0x70/0x7B
             * collapse to 0x71), an optional bracketed sub-type name (eventConditionSubTypeTextIds for kind 1,
             * eventOptionTextIds for kind 2) and the amount times eventConditionValueScale; then prints the event
             * action type name (type+0x80, or type+0x95 past 0x9B). The x parameter is reused as the shown-
             * condition counter.
             */
            void __cdecl MenuModalRenderFunction_NewEvent(int xThenShownCondCount, int y, int width, int height);

        } // namespace NewEvent
    } // namespace MenuModals
} // namespace UI
} // namespace OpenSHC
