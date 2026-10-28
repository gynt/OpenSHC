/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuModals/YesNoDialog.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace YesNoDialog {

            /**
             * Modal render callback for the yes/no dialog: clears UI_MissionModeIntent and picks the header text id
             * (group 0x4A) from DAT_MenuOptionsActionParameter: 7/9/0x1E/0x2B/0x2C/0x2F/0x31 are used directly, -7
             * -> 7, 1000 -> 7 and sets UI_MissionModeIntent, anything else -> none. Parameter 2000 instead draws a
             * plain banner with 'Receiving Map' and DAT_GameSynchronyState.sharedMapName. Draws the text banner
             * when an id was chosen; always clears currentMenu->zero.
             */
            void __cdecl MenuModalRenderFunction_YesNoDialog(int x, int y, int width, int height);

        } // namespace YesNoDialog
    } // namespace MenuModals
} // namespace UI
} // namespace OpenSHC
