/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuModals/FindingNetworkSessions.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace FindingNetworkSessions {

            /**
             * Renders the 'Finding Sessions' modal: header, dimmed session list frame, an animated spinner icon
             * (counter UI_NetworkSessionsShadeLogic/2 mod 32 indexes a frame table, so it advances every second
             * call), and selects the first session once any are found.
             */
            void __cdecl MenuModalRenderFunction_FindingNetworkSessions(int x, int y, int width, int height);

        } // namespace FindingNetworkSessions
    } // namespace MenuModals
} // namespace UI
} // namespace OpenSHC
