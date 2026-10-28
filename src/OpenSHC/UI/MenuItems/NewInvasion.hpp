/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/NewInvasion.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace NewInvasion {

            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            /**
             * Action handler for an invasion-event unit-type button: recomputes the unit sum, opens an overlay
             * slider on the count of unit type unitTypeMenuID (0..min(InvasionUnitLimits[type], count + 500 -
             * current total)) at the button, labelled with a TEXT_SCENARIO (group 199) entry mapped from the unit
             * type.
             */
            void __cdecl MenuItemActionHandler_NewInvasion_UnitButtons(int unitTypeMenuID, ...);

            /**
             * Render callback for an invasion-event unit-type button: draws the button, the unit count (if non-
             * zero) right-aligned, and the unit portrait from GM_ARMY_UNITS (image id mapped from the unit type,
             * vertically centred using the GM height table).
             */
            void __cdecl MenuItemRenderFunction_NewInvasion_UnitButtons(int param_1, ...);

            /**
             * Slider callback for the invasion 'repeat' slider: event 1 initialises min 0 / max 120 / current =
             * invasion repeatMonths (read through the union as scenario.conditions[0x19], same dword), 2/3 store
             * the slider value there, 4 refreshes current and max. The item parameter is unused.
             */
            void __cdecl MenuItemActionHandler_NewInvasion_RepeatSlider(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            /**
             * Render callback for the invasion 'repeat' slider: draws the track, the thumb (lime while dragged),
             * the numeric value to the right and the 'Repeat' label (TEXT_SCENARIO 0xA3) to the left. The item
             * parameter is unused.
             */
            void __cdecl MenuItemRenderFunction_NewInvasion_RepeatSlider(
                int param_1, int thumbXPos, int sliderValue, int thumbWidth, BOOLEnum isDragged);

            /**
             * Action handler of the 'new invasion' dialog. 0x13 deletes the event; 0x25 (OK) stores the typed year
             * into the header and a copy at data+0x6C, sums the 25 unit-count slots (data+4..data+0x64) into
             * actionData, then closes the dialog, re-sorts events and resets the text input. 0xDD/0xDE/0x57 set the
             * invading side (crusaderArabian = 0/1/4), -1 cycles the month.
             */
            void __cdecl MenuItemActionHandler_NewInvasion_Buttons(int param_1, ...);

            /**
             * Render callback of the 'new invasion' dialog: side buttons (9-0xC, 0x57, 0xDD, 0xDE) are drawn
             * highlighted with their TEXT_SCENARIO label when their value matches invasion.crusaderArabian, -1
             * shows the month name, everything else goes to RenderScenarioButtonWithText.
             */
            void __cdecl MenuItemRenderFunction_NewInvasion_Buttons(int param_1, ...);

        } // namespace NewInvasion
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
