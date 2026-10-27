/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/UnusedOldTitleMenu.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace UnusedOldTitleMenu {

            /**
             * Prepare of the unused old title menu: positions the current menu at the border origin, marks not in-
             * game and loads gm_fly.tgx as the only gfx.
             */
            void __cdecl MenuView_UnusedOldTitleMenu_Prepare();

            /**
             * DoInitial of the unused old title menu: black screen, dithered 4x4 overlay, a white 600x400 box
             * centred, gfx 0 at border+100 and the texts "FireFly's" / "Crusader" at border+(400,210)/(400,248).
             */
            void __cdecl MenuView_UnusedOldTitleMenu_DoInitial();

        } // namespace UnusedOldTitleMenu
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
