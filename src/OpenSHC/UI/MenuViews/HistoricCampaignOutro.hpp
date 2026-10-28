/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/HistoricCampaignOutro.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace HistoricCampaignOutro {

            /**
             * Prepare handler of the historic campaign outro: prepares the history book, loads c<N>pic.tgx, loads
             * shc_back, stores the outro title/text (TEXT_CAMPAIGN_INFO N*6-2, N*6-1), resets the fade counter,
             * sets phase 1 and starts the tick counter.
             */
            void __cdecl MenuView_HistoricCampaignOutro_Prepare();

            /**
             * Per-frame handler of the historic campaign outro: same fade/click state machine as the intro; when
             * fade-in completes it plays after_0N.wav immediately (no delay); when fade-out completes it stops the
             * wind and speech streams and returns to the main menu.
             */
            void __cdecl MenuView_HistoricCampaignOutro_DoEveryFrame();

        } // namespace HistoricCampaignOutro
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
