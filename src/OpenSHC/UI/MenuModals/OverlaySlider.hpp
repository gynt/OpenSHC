/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuModals/OverlaySlider.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace OverlaySlider {

            /**
             * Modal render callback for the overlay slider: draws GM_INTERFACE_ICONS2 frame 0x10E at (x,y). When
             * not inside an in-game menu it temporarily targets the menu screen buffer (RT_SCREEN_MENU); afterwards
             * always sets the draw buffer to RT_MAP_GAME.
             */
            void __cdecl MenuModalRenderFunction_OverlaySlider(int x, int y, int width, int height);

        } // namespace OverlaySlider
    } // namespace MenuModals
} // namespace UI
} // namespace OpenSHC
