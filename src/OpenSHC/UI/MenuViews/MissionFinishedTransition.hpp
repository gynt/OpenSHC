/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/MissionFinishedTransition.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace MissionFinishedTransition {

            /**
             * Per-frame handler of the mission-finished transition: in skirmish/MP draws the greatest-lord screen;
             * otherwise waits for the win video to end or a click (campaign missions whose Bink reached its last
             * frame proceed automatically ~5 s later). Then stops speech streams and Bink and routes on: historic
             * campaign -> next mission picture or campaign outro, economic campaign -> next scenario description or
             * main menu (missionNumber >= 38), map-editor games -> main menu (economic map) or custom-scenario
             * menu, other modes -> main menu, MP -> relaunch lobby (host restores and shares lobby state), single-
             * player end-of-game -> ranking games. A non-trail single-player skirmish is stored into SK masters
             * with index 0 (unless skipStoreSKMasters) and returns to SelectCrusade_Main(2) with the lobby setup
             * restored. On a trail it stores the game with the combined trail mission index (progress+1 / +0x33 /
             * +0x51); if the local player won it records a better months-taken value (recomputing trail start dates
             * for trail 1/2/3), raises the furthest-mission mark, advances progress and opens the select-crusade
             * menu, or the crusade end screen after winning the final mission. Every routed exit clears
             * skipStoreSKMasters.
             */
            void __cdecl MenuView_MissionFinishedTransition_DoEveryFrame();

            /**
             * Prepare handler of the mission-finished transition: records game duration, resets result sort
             * columns, menu tab / endscreen stats page (per resolution) and the three modal compositions, stores
             * local time and clears the screen to black. In single-player end-of-game mode only loads the end-of-
             * game background (no video, speech or music); otherwise plays arabian_win.bik (campaign missions 7-11,
             * or Arabian lord type in skirmish) or crusader_win.bik, then a random victory speech (1/3 'We are
             * victorious sire!', else 'Victory!') if any player 1..8 has won (or single-player skirmish) and the
             * win music. For non-skirmish games computes the mission completion score and writes it to the map's
             * .sco file; finally loads shc_back.
             */
            void __cdecl MenuView_MissionFinishedTransition_Prepare();

        } // namespace MissionFinishedTransition
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
