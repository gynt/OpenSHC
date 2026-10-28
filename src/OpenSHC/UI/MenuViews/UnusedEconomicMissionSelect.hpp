/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/UnusedEconomicMissionSelect.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace UnusedEconomicMissionSelect {

            /**
             * Prepare of the unused economic mission select menu: marks not in-game, loads frontend_economics2.tgx
             * and shc_back, resets section1066 and two text-input state fields (0x90 = 0, 0x8c = -1), and sets
             * missionNumber1to20 = 0x21 (33).
             */
            void __cdecl MenuView_UnusedEconomicMissionSelect_Prepare();

        } // namespace UnusedEconomicMissionSelect
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
