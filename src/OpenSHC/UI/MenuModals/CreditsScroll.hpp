/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuModals/CreditsScroll.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace CreditsScroll {

            /**
             * Credits scroll modal: once per request (pendingCreditsFadeBorder) renders the help/credits text and
             * draws a fading black gradient along the top edge (rows going down from y) and the bottom edge (rows
             * going up from y+height): 30 rows of 4 px; per row 20 one-pixel columns at the left with individual
             * alpha ramps (column c alpha = 0x20 + ramp/20, ramp starting at -30*(c+1) and growing by c+1 per row,
             * column 0 = 0x20 - countdown/20) plus a strip from x+20 to the right edge with alpha rowIndex+2. Each
             * ramp local is reused for a different column in the bottom loop.
             */
            void __cdecl MenuModalRenderFunction_CreditsScroll(int x, int y, int width, int height);

        } // namespace CreditsScroll
    } // namespace MenuModals
} // namespace UI
} // namespace OpenSHC
