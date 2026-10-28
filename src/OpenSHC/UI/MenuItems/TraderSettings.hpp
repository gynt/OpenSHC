/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/TraderSettings.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace TraderSettings {

            /**
             * Action handler of the map-editor trader settings panel: negative button ids toggle tradeability of
             * the goods type mapped from the button slot (-id-1); 0x457 toggles the goods of
             * MapPropertiesState.indexStored; 0x25 closes the dialog.
             */
            void __cdecl MenuItemActionHandler_TraderSettings(int param_1, ...);

            /**
             * Render callback of the trader settings panel: goods buttons are highlighted when tradeable and draw
             * the goods icon (faded if not tradeable) plus an On/Off label (TEXT_SCENARIO 0xac/0xad); ids 0..999
             * render a scenario text button; 0x44c draws the 'Trader 1' header box; others draw a rounded box (blue
             * when hovered).
             */
            void __cdecl MenuItemRenderFunction_TraderSettings(int param_1, ...);

        } // namespace TraderSettings
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
