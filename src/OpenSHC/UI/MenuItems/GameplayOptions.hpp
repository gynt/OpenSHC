/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/GameplayOptions.hpp'
*/

#pragma once

#include "WinDef.h"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace GameplayOptions {

            /**
             * Renders Gameplay Options buttons with TEXT_GAME_OPTIONS labels: 15 is a static non-interactive title;
             * -1 draws the state label of the pending bubble-help value (0 -> text 0xe, 1 -> text 0xd, other values
             * nothing) and -2 that of the pending unusedOption1 (set -> 0xd, clear -> 0xe), both without a button
             * background; other ids are buttons whose label index equals the id, drawn with shadow and highlighted
             * on hover.
             */
            void __cdecl MenuItemRenderFunction_GameplayOptions_Buttons(int param_1, ...);

            /**
             * Game speed slider callback (range 20..90). In multiplayer modes (not GM_SOLITARY /
             * GM_SKIRMISH_SINGLE_PLAYER) every event just reports skirmishGameSpeedLevel (read-only); in single-
             * player event 1 inits, 2/3 store the dragged value, 5/6 decrement/increment it, all into the pending
             * speed MenuTextInputState.field12_0x30.
             */
            void __cdecl MenuItemActionHandler_GameplayOptions_SpeedSlider(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            /**
             * Renders the game speed slider: track (basic button), thumb box (dark lime while dragged, greyish
             * yellow otherwise) and the numeric value to the right of the track. The parameters named
             * thumbYPos/thumbHeight are actually the thumb's X offset and width (horizontal slider).
             */
            void __cdecl MenuItemRenderFunction_GameplayOptions_SpeedSlider(
                int param_1, int thumbYPos, int param_3, int thumbHeight, BOOL isDragged);

            /**
             * Gameplay Options buttons: 0x12 (OK) commits pending speed, bubble help and unusedOption1 into
             * GameCore and pops the modal; 0x11 (cancel) just pops; 0x21 toggles pending bubble help; 0x34 toggles
             * pending unusedOption1.
             */
            void __cdecl MenuItemActionHandler_GameplayOptions_Buttons(int param_1, ...);

        } // namespace GameplayOptions
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
