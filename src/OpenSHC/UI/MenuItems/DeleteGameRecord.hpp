/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/DeleteGameRecord.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace DeleteGameRecord {

            /**
             * Delete game record confirmation: button 0x16 (yes) deletes the selected skirmish leaderboard entry
             * (g_rankingSelectedRecordId) and rebuilds the leaderboard view; any button closes the modal.
             */
            void __cdecl MenuItemActionHandler_DeleteGameRecord_Main(int param_1, ...);

        } // namespace DeleteGameRecord
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
