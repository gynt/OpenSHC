/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuModals/TutorialBox.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace TutorialBox {

            void __cdecl MenuModalRenderFunction_TutorialBox_Thunk(int x, int y, int width, int height);

            /**
             * Modal render callback for the tutorial box (steps 0..31 only): tiles the box from 24-px
             * GID_INTERFACE_ICONS_3 pieces with alpha masks (mask = frame+3; transition counter used as fade while
             * g_tutorialTransitionState), plays an alternating fx\speech prompt on the rising edge of
             * g_tutorialHintActive when no speech stream is playing, prints the step title
             * TEXT_TUTORIAL[g_tutorialStepStartIndices[step]], then either the body text
             * TEXT_TUTORIAL[title+1+g_tutorialSubStep] (no hint) or the hint text TEXT_TUTORIAL_BUTTONS[3+toggle]
             * (single centred line if its measured height < 0x24, else wrapped), and finally the tutorial float
             * pointer for the step. BUG (confirmed in machine code): the single-centred-line hint call passes the
             * fade value in the keepOffsetX slot and 0 as blend, so that hint line is not faded during transitions
             * (the wrapped variant passes the fade correctly).
             */
            void __cdecl MenuModalRenderFunction_TutorialBox(int x, int y, int width, int height);

        } // namespace TutorialBox
    } // namespace MenuModals
} // namespace UI
} // namespace OpenSHC
