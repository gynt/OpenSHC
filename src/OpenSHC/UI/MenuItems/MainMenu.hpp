/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/MainMenu.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace MainMenu {

            /**
             * Main menu button render: plays hover sounds (on hover-enter for the quit button and the 4 main
             * entries/custom scenarios), renders the button graphic, then draws the label text from
             * TEXT_MAINOPTIONS (multiplayer greyed out when GameCore.directDrawStatus < 0x700) and a highlight icon
             * when hovered. Does nothing when g_mainMenuBackgroundGfxIndex == 1.
             */
            void __cdecl MenuItemRenderFunction_MainMenu_Main(int param_1, ...);

            /**
             * Main menu click handler: 1 historical campaigns, 2 crusader trail, 3 castle builder (all troop types
             * producible, reset teams), 4 multiplayer connection, 5 quit confirmation, 6 tutorial (load
             * Crusader_tutorial.map, init tutorial step tables), 7 credits, 8 options (also queues
             * GCT_ASK_FOR_SLOT_ASSIGNMENT), 9 custom scenarios. Also resets player unit colors to defaults for
             * 1/3/4.
             */
            void __cdecl MenuItemActionHandler_MainMenu_Main(int param_1, ...);

        } // namespace MainMenu
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
