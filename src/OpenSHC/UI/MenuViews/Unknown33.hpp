/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/Unknown33.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace Unknown33 {

            /**
             * Per-frame handler that waits until checkAllPlayersReadyAndCleanupSlots succeeds; then the host shares
             * lobby state and requests a player-info refresh, slots 1-8 with no human, no AI and (in King of the
             * Hill) not the map's reserved player slot are destroyed, AI nicknames set, the autosave interval start
             * time recorded, and the game switches to the build menu (hunter's hut tab) with per-slot sync values
             * and lobby face-bitmap counters reset. NAME? Unknown33 is the game-start wait view after the lobby.
             */
            void __cdecl MenuView_MultiplayerWaitForPlayersReady_DoEveryFrame();

        } // namespace Unknown33
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
