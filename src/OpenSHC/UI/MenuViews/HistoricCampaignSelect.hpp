/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/HistoricCampaignSelect.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace HistoricCampaignSelect {

            /**
             * Prepare handler of the historic campaign select view: loads frontend_combat/frontend_combat2 and
             * shc_back, staggers the four campaign button animation start times, sets DAT_LastHoveredMenuButtonId to -1, selects
             * background 0 and closes modal dialog 3.
             */
            void __cdecl MenuView_HistoricCampaignSelect_Prepare();

            /**
             * Per-frame handler of the historic campaign select view: draws background image 0, or 1 while a modal
             * dialog is open, centred.
             */
            void __cdecl MenuView_HistoricCampaignSelect_DoEveryFrame();

        } // namespace HistoricCampaignSelect
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
