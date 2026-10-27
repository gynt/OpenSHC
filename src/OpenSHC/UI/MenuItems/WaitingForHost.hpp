/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/WaitingForHost.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace WaitingForHost {

            /**
             * Waiting-for-host dialog action handler: button 3 (cancel) disconnects DirectPlay, closes the modal,
             * returns to the main menu and resets mouse state.
             */
            void __cdecl MenuItemActionHandler_WaitingForHost_Button(int param_1, ...);

            /**
             * Renders a waiting-for-host dialog button: basic button with centered TEXT_MULTIPLAYER_CONNECTION
             * string buttonId.
             */
            void __cdecl MenuItemRenderFunction_WaitingForHost_Button(int param_1, ...);

            /**
             * Waiting-for-host poll (lobby-launch join): step 0 initialises DirectPlay and starts session
             * enumeration (step 1); step 1 re-enumerates and, for each session named 'Crusader', copies its GUID
             * and joins it; on success stops the async session enumeration (EnumSessions with the game's
             * application GUID and DPENUMSESSIONS_STOPASYNC 0x20), opens the lobby menu, waits for the host, queues
             * GCT_ASK_FOR_SLOT_ASSIGNMENT, sets step 2 and closes the modal. The loop does not break after a
             * successful join. The local 'result' is reused as the session loop index.
             */
            void __cdecl MenuItemActionHandler_WaitingForHost_ConnectToLobby();

        } // namespace WaitingForHost
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
