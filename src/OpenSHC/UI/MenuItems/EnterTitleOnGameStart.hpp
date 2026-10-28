/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/EnterTitleOnGameStart.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace EnterTitleOnGameStart {

            /**
             * Button of the 'enter title on game start' modal: closes the modal, resets text input to buffer 9 and
             * switches to the main menu (button id ignored).
             */
            void __cdecl MenuItemActionHandler_EnterTitleOnGameStart_Button(int param_1, ...);

            /**
             * Renders a button of the 'enter title on game start' modal with label TEXT_BUBBLE_HELP_TEXT[id], plain
             * when idle, shadowed highlight when hovered.
             */
            void __cdecl MenuItemRenderFunction_EnterTitleOnGameStart_Button(int param_1, ...);

        } // namespace EnterTitleOnGameStart
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
