/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/Credits.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace Credits {

            /**
             * Prepare handler of the credits view: loads credits_1..4.tgx (or only end_credit.tgx when DAT_CreditsAfterCampaignEnd
             * is set), opens credits.hlp as the scrolling credits dialog with scroll offset -600 (text starts below
             * the screen), resets the background image fade animation (frame 0, fading in) and its timers, loads
             * shc_back and clears the screen to black.
             */
            void __cdecl MenuView_Credits_Prepare();

            /**
             * Initial handler of the credits view: clears the screen, draws the menu border and the first credits
             * image centred, positions the menu origin/current menu and sets pendingCreditsFadeBorder so the next
             * frame redraws.
             */
            void __cdecl MenuView_Credits_DoInitial();

            /**
             * Per-frame handler of the credits view: drives the background image cycle (fade in over 32 steps of 50
             * ms, hold 20 s, fade out, next of 4 images; no hold->fade-out when DAT_CreditsAfterCampaignEnd is
             * set), scrolls the credits text by time at 1 px per 30 ms starting at -600 (VK_DOWN held speeds it up,
             * more with Shift) into TextEditorState.helpContentScrollOffsetY and restarts it once the offset
             * exceeds TextEditorState.totalContentHeight, redraws the centred image when something changed with a
             * blended black box over the menu area (left half of the screen after the campaign end) while fading,
             * and on left click closes the dialog and returns to the main menu.
             */
            void __cdecl MenuView_Credits_DoEveryFrame();

        } // namespace Credits
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
