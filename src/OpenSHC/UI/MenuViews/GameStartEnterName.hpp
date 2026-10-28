/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/GameStartEnterName.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace GameStartEnterName {

            /**
             * Per-frame handler of the game-start enter-name view: does nothing if the name was already known
             * (unknownFlag_0x118 == TRUE); otherwise draws the background and, when Return was pressed in the name
             * field, closes the modal dialog, resets text input to slot 9 and switches to the main menu. The inner
             * flag==TRUE branch (1 s greeting window / right-click skip) is dead code: asm re-tests the same flag
             * at 0x424B4B after only a draw call.
             */
            void __cdecl MenuView_GameStartEnterName_DoEveryFrame();

            /**
             * Prepare handler of the game-start enter-name view: copies the stored player name, plays the matching
             * lord-name speech if the name is in the callable-names table (else the generic start-game speech); if
             * the stored name is non-empty it sets unknownFlag_0x118 and the time, switches to the main menu and
             * immediately runs its prepare/initial/frame handlers; otherwise loads frontend_combat3 + shc_back,
             * clears the flag, prefills 'Lord Crusader' and opens the enter-title modal dialog. The
             * _time64/localtime results are unused.
             */
            void __cdecl MenuView_GameStartEnterName_Prepare(void* unusedArg);

            /**
             * Initial handler of the enter-name view: clears the screen, draws the outer border and the centred
             * background image, and positions the current menu at the main-menu border offset.
             */
            void __cdecl MenuView_GameStartEnterName_DoInitial();

        } // namespace GameStartEnterName
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
