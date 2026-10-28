/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuModals/Roundtable.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace Roundtable {

            /**
             * Modal render callback for the round-table (team setup) view: right-click closes the modal; draws
             * loaded gfx 2 as the table, then for seats 1..8 (stopping at the first seat whose
             * DAT_RoundTableOrderArray entry or player group is < 1) draws the seat graphic at a fixed per-seat
             * offset. The graphic alternates between set A (gfx seat+2, blend 0x10) and set B (gfx seat+10, blend
             * 0x14) each time the player group number increases, so adjacent teams are distinguished. Sets the
             * button rect and redraws the bottom-left text if g_roundtableNeedsRedraw.
             */
            void __cdecl MenuModalRenderFunction_Roundtable(int x, int y, int width, int height);

        } // namespace Roundtable
    } // namespace MenuModals
} // namespace UI
} // namespace OpenSHC
