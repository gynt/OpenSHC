/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuModals/ReceiveMapFrom.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace ReceiveMapFrom {

            /**
             * Modal render callback for the 'Receiving Map' dialog: draws the header banner, a black frame spanning
             * the middle half of the dialog (x+w/4-1 .. x+3w/4+1), and a lime fill of width (width/2) *
             * mapSendingByteBufferAddress[0] / mapSendingFileSize, i.e. bytes received so far.
             */
            void __cdecl MenuModalRenderFunction_ReceiveMapFrom(int x, int y, int width, int height);

        } // namespace ReceiveMapFrom
    } // namespace MenuModals
} // namespace UI
} // namespace OpenSHC
