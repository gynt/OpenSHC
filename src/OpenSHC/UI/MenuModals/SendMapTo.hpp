/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuModals/SendMapTo.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace SendMapTo {

            /**
             * Modal render callback for the 'Send Map To' dialog: draws the header, then for player slots 1..8
             * whose field282_0x109d98 entry equals 1 prints the player name in its slot colour (rows 0x1E px apart)
             * and, while DAT_MapFileReceivingState != 0, a per-player progress bar of bytes sent
             * (mapSendingByteBufferAddress[slot]) / mapSendingFileSize.
             */
            void __cdecl MenuModalRenderFunction_SendMapTo(int x, int y, int width, int height);

        } // namespace SendMapTo
    } // namespace MenuModals
} // namespace UI
} // namespace OpenSHC
