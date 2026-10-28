/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/HistoricMissionSelect.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace HistoricMissionSelect {

            /**
             * Prepare handler of the historic mission select view: clears currentlyInGameUnk_0xa4, loads
             * frontend_combat2.tgx and shc_back, resets selection state, and computes the page (0-3) and first
             * mission of the page from the current mission number (5 missions per page).
             */
            void __cdecl MenuView_HistoricMissionSelect_Prepare();

        } // namespace HistoricMissionSelect
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
