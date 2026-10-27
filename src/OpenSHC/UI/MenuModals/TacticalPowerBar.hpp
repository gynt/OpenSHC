/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuModals/TacticalPowerBar.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace TacticalPowerBar {

            /**
             * Modal render callback for the tactical powers bar: draws a vertical black-filled, soft-yellow framed
             * bar and a white fill whose height is the current player's tacticalPowersBarLevel*308/7000. If
             * DAT_TacticalPowersHelpTextDisplayBool is set, also draws the 'Click on an Icon to use Tactical
             * Powers' multiline hint left of the bar and GM_INTERFACE_ICONS2 frame 0x1D4.
             */
            void __cdecl MenuModalRenderFunction_TacticalPowerBar(int x, int y, int width, int height);

        } // namespace TacticalPowerBar
    } // namespace MenuModals
} // namespace UI
} // namespace OpenSHC
