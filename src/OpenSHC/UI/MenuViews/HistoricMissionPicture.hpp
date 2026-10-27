/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/HistoricMissionPicture.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace HistoricMissionPicture {

            /**
             * Prepare handler of the historic mission picture view: loads m<chapter>pic.tgx (chapter =
             * (mission-1)/5+1), prepares the history book, stores the mission's two title strings, resets the fade
             * counter, sets phase 1, starts the tick counter and loads shc_back.
             */
            void __cdecl MenuView_HistoricMissionPicture_Prepare();

            /**
             * Per-frame handler of the historic mission picture view: wind ambience, click skip/fade-out, draws the
             * chapter picture and two title strings at the current fade level; after fade-in stays shown (phase 0)
             * and after fade-out switches to the historic mission intro view.
             */
            void __cdecl MenuView_HistoricMissionPicture_DoEveryFrame();

        } // namespace HistoricMissionPicture
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
