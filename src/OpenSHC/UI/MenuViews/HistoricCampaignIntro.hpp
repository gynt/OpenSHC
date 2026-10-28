/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/HistoricCampaignIntro.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace HistoricCampaignIntro {

            /**
             * Prepare handler of the historic campaign intro: prepares the history book, loads c<N>pic.tgx (N =
             * historicCampaignNumber 1..4), stores the campaign title and intro text (TEXT_CAMPAIGN_INFO N*6-5,
             * N*6-4), loads shc_back, resets the fade counter, sets phase 1 (fade in) and starts the tick counter.
             */
            void __cdecl MenuView_HistoricCampaignIntro_Prepare();

            /**
             * Per-frame handler of the historic campaign intro: keeps the wind ambience playing; a click during
             * fade-in reverses into fade-out, a click while fully shown starts fade-out. Each tick draws the
             * history book, the title and intro text and the campaign picture blended by the phase (phase 1:
             * 31-counter, phase 2: counter). Phase 1 ends at counter > 32 -> phase 0 with the counter reset to 60
             * as a delay, after which intro_0N.wav is played; when fade-out (phase 2) completes it stops the speech
             * streams and switches to the historic mission picture view.
             */
            void __cdecl MenuView_HistoricCampaignIntro_DoEveryFrame();

        } // namespace HistoricCampaignIntro
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
