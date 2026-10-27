/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/FindingNetworkSessions.hpp'
*/

#pragma once

#include "OpenSHC/UI/Multiplayer/FindingNetworkSessions_ButtonParameters.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace FindingNetworkSessions {

            using OpenSHC::UI::Multiplayer::FindingNetworkSessions_ButtonParameters;

            /**
             * Scrollbar callback for the network session list: range [0, DPLAY_SessionsCount-10]; actions 1 init
             * (value = current offset), 2/3 set from drag, 4 refresh, 5/6 step up/down; position in
             * scrollBarItemOffset.
             */
            void __cdecl MenuItemActionHandler_FindingNetworkSessions_Scrollbar(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            /**
             * Click on a network session table row: selects it (scrollBarIndex = row) if offset+row is a valid
             * session.
             */
            void __cdecl MenuItemActionHandler_FindingNetworkSessions_TableRows(int param_1, ...);

            void __cdecl MenuItemRenderFunction_FindingNetworkSessions_TableRows(int param_1, ...);

            void __cdecl MenuItemActionHandler_FindingNetworkSessions_EnumerateDPlaySessions(int param_1, ...);

            /**
             * Buttons of the 'finding network sessions' modal. FNSBP_JOIN (10000) with a selected row: fetches the
             * session GUID and joins it; on success stops the async EnumSessions (app GUID
             * {1D5E2F48-E8C0-49E5-AED8-B124DA9E3059}), closes the modal, switches to the lobby view, waits for the
             * host and queues GCT_ASK_FOR_SLOT_ASSIGNMENT. On join failure, and for cancel (3 or -10000): stops
             * enumeration (if DirectPlay exists), disconnects, reinitialises the multiplayer lobby and reopens the
             * choose-service-provider modal. -1/-2 scroll the 10-row list up/down.
             */
            void __cdecl MenuItemActionHandler_FindingNetworkSessions_Buttons(
                FindingNetworkSessions_ButtonParameters param_1, ...);

        } // namespace FindingNetworkSessions
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
