/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/GameLost.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace GameLost {

            /**
             * Prepare handler of the game lost view: records game duration, resets result sorting and all modal
             * dialogs, sets the bottom tab per resolution, stores local time, starts loss music, positions the menu
             * and clears the screen; unless in skirmish end-of-game mode it plays arabian_lose.bik (campaign
             * missions 6-10, or non-campaign when the player's lord type is 1) else crusader_lose.bik; then loads
             * shc_back and clears other modal dialogs.
             */
            void __cdecl MenuView_GameLost_Prepare();

            /**
             * Per-frame handler of the game lost view: in skirmish/MP renders the greatest-lord screen and proceeds
             * only when INT_00ed279c is set (a click does not count); otherwise a click proceeds, the end of the
             * loss video counts as a click, and in campaign missions a 5 s timeout (BinkControl.lastFrameReached[0]
             * set) also proceeds. On proceeding it stops speech streams and all Bink playback and navigates:
             * skirmish trail -> store result in SKMasters (unless skipStoreSKMasters) and return to the matching
             * crusade trail menu; plain skirmish -> store, SelectCrusade(2), restore lobby; skirmish end-of-game ->
             * ranking view; MP -> leave game (host restores and re-shares the lobby); campaign -> scenario
             * description; economic campaign/builder -> respective menus; else main menu. Always clears
             * skipStoreSKMasters.
             */
            void __cdecl MenuView_GameLost_DoEveryFrame();

        } // namespace GameLost
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
