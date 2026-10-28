/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuModals/Allies.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace Allies {

            /**
             * Renders the Allies modal: recalculates allies, toggles the allies icon animation frame (0/1) every
             * 500 ms, draws the 'Allies' title (font 0xF) and, when DAT_AlliesCount < 1, 'You have no Allies!'
             * (font 0x11).
             */
            void __cdecl MenuModalRenderFunction_Allies(int x, int y, int width, int height);

        } // namespace Allies
    } // namespace MenuModals
} // namespace UI
} // namespace OpenSHC
