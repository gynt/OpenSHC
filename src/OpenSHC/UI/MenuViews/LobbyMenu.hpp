/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/LobbyMenu.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace LobbyMenu {

            /**
             * Prepare handler of the skirmish/multiplayer lobby view: closes modal dialog 3, sets skirmish game
             * mode and first-edition trail type, loads the lobby graphics (table slices, opponent pickers,
             * fireflies), positions the current menu, resets text input slot 4 and initializes lobby timers.
             */
            void __cdecl MenuView_LobbyMenu_Prepare();

            /**
             * Per-frame handler of the multiplayer lobby: draws the background and blended panels (fading
             * DAT_ButtonBackgroundBlendStrength in/out per DAT_MenuFadeState); while a map file is being
             * transferred (DAT_MapFileReceivingState == 1) queues GCT_SHARE_MAP_PART (param0 = per-slot next part
             * index, param1 = slot) for every slot 1..8 with an open send handle that has the map pending and is
             * not mid-part, and once no handle is open and no slot is still transferring closes the modal, clears
             * the state and sets reparseMaps. Every 250 ms (375 ms with >4 active humans) queues the next lobby
             * face-bitmap chunk (0..65); every 30 s the host queues a player-info refresh (clients redraw the map
             * description). When reparseMaps is set it rebuilds the list of multiplayer maps with >1 player, fills
             * the per-map player-count/balance arrays, marks whether each map fits the occupied-slot count (host
             * queues GCT_LOAD_MAP_HEADER per map) and re-selects a map that fits; finally draws the 8 slot face/AI
             * icons in rows of four.
             */
            void __cdecl MenuView_LobbyMenu_DoEveryFrame();

        } // namespace LobbyMenu
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
