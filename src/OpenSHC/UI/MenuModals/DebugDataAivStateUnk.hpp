/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuModals/DebugDataAivStateUnk.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace DebugDataAivStateUnk {

            /**
             * Debug modal 'Village Placement Success': for players 1..8 lists the AIV castle placement result from
             * DAT_AIVPlacementFit: skips -10, shows 'File missing' (-3), 'Can't place keep' (-2), 'Total Success'
             * (100) or 'N% Success'; rows with values other than 100 are drawn in red (colour 0xff). NAME? shows
             * AIV placement success, not a generic AIV state.
             */
            void __cdecl MenuModalRenderFunction_DebugDataAivPlacementSuccess(int x, int y, int width, int height);

        } // namespace DebugDataAivStateUnk
    } // namespace MenuModals
} // namespace UI
} // namespace OpenSHC
