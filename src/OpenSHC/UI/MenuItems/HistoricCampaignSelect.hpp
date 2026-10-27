/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/HistoricCampaignSelect.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace HistoricCampaignSelect {

            /**
             * Render callback of the historic campaign select screen (does nothing when g_mainMenuBackgroundGfxIndex == 1):
             * draws campaign buttons 1-4 and back button 5 (campaign buttons use gm data 0x161 when
             * TextureRenderCore.gmAllowRelativeAliasing is set), plays SFX 0x92 when a different campaign button
             * becomes hovered, and for campaign buttons draws the TEXT_BUBBLE_HELP_TEXT 0x135+id label with shadow
             * plus, while hovered, a front-end icon.
             */
            void __cdecl MenuItemRenderFunction_HistoricCampaignSelect_Main(int param_1, ...);

            /**
             * Action handler of the historic campaign select screen: buttons 1-4 select campaign 1-4 (first mission
             * 1/6/11/16), copy the chosen difficulty into the map state, reset player colours and open the historic
             * mission select; button 5 returns to the main menu.
             */
            void __cdecl MenuItemActionHandler_HistoricCampaignSelect_Main(int param_1, ...);

        } // namespace HistoricCampaignSelect
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
