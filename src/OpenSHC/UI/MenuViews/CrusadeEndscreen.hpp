/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/CrusadeEndscreen.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace CrusadeEndscreen {

            /**
             * Initial handler of the Crusader Trail end screen: clears the screen, draws the outer menu border,
             * positions the menu origin/current menu and clears the 'easter-egg music started' flag INT_00ed27b8.
             */
            void __cdecl MenuView_CrusadeEndscreen_DoInitial();

            /**
             * Prepare handler of the Crusader Trail victory end screen: loads sktrail_win (gfx 0), endframe1..8
             * (gfx 1..8) and jesterlast (gfx 9), stores the five TEXT_SKTRAIL_WIN strings and builds the credits
             * script: for each of 8 frames an image transition + lord Bink victory video with speech wav, then the
             * text lines (font 0x10, 0x11 for Italian; shadow + foreground; line 4 'Extreme Trail' or line 3
             * depending on trail type), then each lord frame (command 8 with gfx index 1..8) is replaced by the
             * jester image/video, ending with a looping jester sequence; finally starts the tick counter.
             */
            void __cdecl MenuView_CrusadeEndscreen_Prepare();

            /**
             * Per-frame handler of the Crusader Trail end screen: when the tick counter fires, advances the credits
             * script; once the script cursor DAT_CreditsScriptCommandIndex is past command 0x3A it starts the
             * MUSIC_GERMAN_EGG track once (flag INT_00ed27b8); then renders the active credits elements.
             */
            void __cdecl MenuView_CrusadeEndscreen_DoEveryFrame();

        } // namespace CrusadeEndscreen
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
