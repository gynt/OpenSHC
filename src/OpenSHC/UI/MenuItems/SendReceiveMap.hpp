/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/SendReceiveMap.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace SendReceiveMap {

            /**
             * Render callback of the send/receive-map dialog buttons: draws a basic button with centered text
             * TEXT_MULTIPLAYER_CONNECTION[buttonId]; the 'send' button (0x44) is hidden while a map transfer is
             * running (DAT_MapFileReceivingState != 0).
             */
            void __cdecl MenuItemRenderFunction_SendReceiveMap_Main(int param_1, ...);

            /**
             * Action handler of the multiplayer send/receive-map dialog. Button 0x44 (when idle) starts sending the
             * selected map: DAT_MapFileReceivingState = 1, builds '<name>.map', resolves it in FRT_MAPS, stores
             * mapSendingFileSize, then for each player slot 1..8 clears the transfer counters and, if the slot
             * lacks the map (mapPossessionStatePerPlayer == 1), opens its own FILE handle and queues
             * GCT_START_MAP_TRANSFER (map index, slot, size). Button 3 cancels: state 1 closes all send
             * handles, state 2 closes the partially received file and queues command 0x6B (param 1), both reset
             * state to 0; in state 0 it closes the modal.
             */
            void __cdecl MenuItemActionHandler_SendReceiveMap_Main(int param_1, ...);

        } // namespace SendReceiveMap
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
