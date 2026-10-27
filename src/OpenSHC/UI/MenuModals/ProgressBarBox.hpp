/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuModals/ProgressBarBox.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace ProgressBarBox {

            /**
             * Modal render callback for the progress-bar box: prints the TEXT_GAME_OPTIONS string selected by
             * DAT_MenuOptionsActionParameter centred near the top (font 16 for English/American, else 18), then
             * draws a 300-px wide bar area at y+0x41..y+0x50 - a filled soft-yellow box in multiplayer when
             * saveRelated != 0, otherwise a dimmed box - and stores the bar's left x / top y in MenuTextInputState
             * field40_0x94 / field41_0x98.
             */
            void __cdecl MenuModalRenderFunction_ProgressBarBox(int x, int y, int width, int height);

        } // namespace ProgressBarBox
    } // namespace MenuModals
} // namespace UI
} // namespace OpenSHC
