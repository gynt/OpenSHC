/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuModals/TriggerEventSlider.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace TriggerEventSlider {

            /**
             * Modal render callback for the trigger-event slider: draws a header banner using
             * invasionEventContent.triggerEventActionId as text index in group 199 (0x94 is shown as 0x92); for 0x92/0x94
             * also draws GM_INTERFACE_ICONS2 frame 0x82 to the right of the centred title.
             */
            void __cdecl MenuModalRenderFunction_TriggerEventSlider(int x, int y, int width, int height);

        } // namespace TriggerEventSlider
    } // namespace MenuModals
} // namespace UI
} // namespace OpenSHC
