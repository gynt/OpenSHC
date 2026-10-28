/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/NetworkSessions.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace NetworkSessions {

            /**
             * Render callback for the multiplayer connection/session list buttons. 10000 = Join button (greyed when
             * no session is selected, scrollBarIndex == -1, otherwise drawn as button 8); ids 7/8 (Host/Join) are
             * greyed and flagged disabled on the modem tab when the modem list is empty; other ids >= 0 (9/10 with
             * hover cleared) draw TEXT_MULTIPLAYER_CONNECTION[id] in normal/hover colour; -1 draws the scroll-up
             * arrow and other negative ids the scroll-down arrow, -1000 a plain button, -10000 (and -10 when
             * field32_0x510 != 0) the generic alpha-texture button.
             */
            void __cdecl MenuItemRenderFunction_NetworkSessions_Buttons(int param_1, ...);

        } // namespace NetworkSessions
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
