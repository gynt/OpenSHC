/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/General.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace General {

            /**
             * Generic menu-view initial handler: clears the screen, draws the outer border and the loaded image
             * g_mainMenuBackgroundGfxIndex centred, and positions the current menu.
             */
            void __cdecl MenuView_General_DoInitial_BlackBoxDefaultBorderAndPicture();

            /**
             * Generic menu-view per-frame handler: draws loaded image 0 centred on screen.
             */
            void __cdecl MenuView_General_DoEveryFrame_FirstGfxCentered();

            /**
             * Generic menu-view initial handler: clears the screen, draws the outer menu border and positions the
             * current menu at the main-menu border offset.
             */
            void __cdecl MenuView_General_DoInitial_DefaultMainMenuStructure();

            /**
             * Generic menu-view prepare handler: clears GameSynchronyState.enteringLobbyPending and loads
             * frontend_combat3.tgx (sword and shield background) plus shc_back.
             */
            void __cdecl MenuView_General_Prepare_SwordShieldAndBorder();

            /**
             * Generic menu-view initial handler: clears the screen to black and positions the current menu at the
             * main-menu border offset (no border drawn).
             */
            void __cdecl MenuView_General_DoInitial_ScreenToBlack();

            /**
             * Generic menu-view initial handler: only positions the current menu at the main-menu border offset.
             */
            void __cdecl MenuView_General_DoInitial_OnlySetMenuXY();

            /**
             * Generic menu-view initial handler: clears the screen, draws the outer border and loaded gfx 0 via
             * RenderGfxHelperUnk(0,0,0).
             */
            void __cdecl MenuView_General_DoInitial_BlackBorderAndGfx();

            /**
             * Initial handler shared by crusade and ranking menus: clears the screen, draws the outer border,
             * positions the current menu and draws loaded gfx 0 via RenderGfxHelperUnk(0,0,0).
             */
            void __cdecl MenuView_General_DoInitial_CrusadeAndRankMenu();

        } // namespace General
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
