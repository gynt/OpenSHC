/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuModals/Chat.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace Chat {

            /**
             * Renders the multiplayer Chat modal: 'Chat' title, rounded input box with a caret at the current
             * cursor width (only when no insult is selected), forces user text slot 4, then draws either the
             * current chat input text or the selected insult text (TEXT_INSULTS[DAT_InsultTextIndex], in the
             * current input font size) and clears the insult index.
             */
            void __cdecl MenuModalRenderFunction_Chat(int x, int y, int width, int height);

        } // namespace Chat
    } // namespace MenuModals
} // namespace UI
} // namespace OpenSHC
