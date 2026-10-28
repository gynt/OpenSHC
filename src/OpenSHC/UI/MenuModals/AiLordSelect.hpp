/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuModals/AiLordSelect.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace AiLordSelect {

            /**
             * Renders the lobby AI-lord selection modal: background gfx 0x13 (or bigger 0x14 for >8 AIs), closes on
             * right-click, and shows the hovered AI's name (TEXT_XPLAY_WAITING_ROOM hovered*9+0xE6) and description
             * (hovered+0x180), or the default hint text 0x191. The locals descTextIndex/lineWidth double as blend
             * (0) and X of the name call.
             */
            void __cdecl MenuModalRenderFunction_AiLordSelect(int x, int y, int width, int height);

        } // namespace AiLordSelect
    } // namespace MenuModals
} // namespace UI
} // namespace OpenSHC
