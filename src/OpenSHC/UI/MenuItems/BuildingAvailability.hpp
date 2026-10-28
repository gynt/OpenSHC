/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/BuildingAvailability.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace BuildingAvailability {

            /**
             * Render callback for the editor building-availability table. Ids 1000+row draw the toggle button for
             * visible row (scroll offset + row) with label TEXT_SCENARIO 0xac (available) / 0xad (disabled); ids
             * 2000+row draw a '!' button only when the row's building identifier is 0x32/0x52/0x53/0x56/0x57
             * (weapons / Arab troops / Euro troops sub-dialogs), otherwise hide it; -2/-1 draw the down/up scroll
             * arrows; anything else is a normal scenario button with text.
             */
            void __cdecl MenuItemRenderFunction_BuildingAvailability_Buttons(int param_1, ...);

            /**
             * Action handler for the editor building-availability table: 1000+row toggles
             * MapPropertiesState.buildingAvailability (XOR 1) of the visible row's building; 2000+row opens the
             * disable-weapons (0x32/0x52/0x53), disable-Arab-troops (0x56) or disable-Euro-troops (0x57) dialog; -2
             * scrolls down, -1 scrolls up (clamped to 0..entryCount-19); 0x25 closes the dialog.
             */
            void __cdecl MenuItemActionHandler_BuildingAvailability_Buttons(int param_1, ...);

            /**
             * Render callback for a row of the building-availability table: looks up the building entry for scroll
             * offset + row, draws the cell background and the building name (TEXT_BUBBLE_HELP_TEXT) at x+20, grey
             * when the building is disabled, normal colour when enabled, highlight colour when hovered.
             */
            void __cdecl MenuItemRenderFunction_BuildingAvailability_TableRows(int param_1, ...);

            /**
             * Scrollbar callback for the building-availability table: range 0..entryCount-19 over
             * DAT_BuildingAvailabilityScrollbarOffset (event 1 init min/max/current, 2/3 set from current, 4 get
             * current+max, 5 step up, 6 step down).
             */
            void __cdecl MenuItemActionHandler_BuildingAvailability_Scrollbar(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

        } // namespace BuildingAvailability
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
