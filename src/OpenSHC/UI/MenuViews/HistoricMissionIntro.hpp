/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/HistoricMissionIntro.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace HistoricMissionIntro {

            /**
             * Prepare handler of the historic mission intro: prepares the history book, loads m<N>map.tgx, stores
             * the mission's three text strings (group TEXT_TUTORIAL + N*4, entries 0-2), resets the fade counter,
             * sets phase 1, pre-wraps string 2 into the scrolling text frame (x 0x1E, y 0x17C, width 0x2E4, font
             * 0x11), starts the tick counter and loads shc_back.
             */
            void __cdecl MenuView_HistoricMissionIntro_Prepare();

            /**
             * Per-frame handler of the historic mission intro: wind ambience; the first click only sets
             * DAT_ScrollingTextFrameDone, later clicks start/reverse the fade-out. Draws the mission map blended by phase, the
             * briefing text (scrolling frame while shown, static blended during fade-out) and the title strings;
             * when fade-in completes it plays fx\speech\m<N>_hist.wav from
             * MissionDefinedData.historicMissionIntroSpeechFiles[mission-1] (missions 1-20), and when fade-out completes it stops
             * the wind stream and switches to the scenario description.
             */
            void __cdecl MenuView_HistoricMissionIntro_DoEveryFrame();

        } // namespace HistoricMissionIntro
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
