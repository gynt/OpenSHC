/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/UnusedHelpTextEditor.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace UnusedHelpTextEditor {

            /**
             * Prepare of the unused help-text editor: positions the current menu at the main-menu border origin and
             * blits the text editor surface to screen if needed.
             */
            void __cdecl MenuView_UnusedHelpTextEditor_Prepare();

            /**
             * Per-frame handler of the unused help-text editor: renders the help dialog if it is open.
             */
            void __cdecl MenuView_UnusedHelpTextEditor_DoEveryFrame();

        } // namespace UnusedHelpTextEditor
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
