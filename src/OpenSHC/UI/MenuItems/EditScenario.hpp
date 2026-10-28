/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/EditScenario.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace EditScenario {

            /**
             * Scenario editor base-menu button handler (does nothing while a modal is open). 3: parses the year
             * text box (buffer 10) into SEC_StartingYear and returns to map-editor properties; 0x26 trader settings
             * (non-siege); 0x29 start goods dialog, or in siege maps the attacking-force troop dialog
             * (indexStored=20; the decompiled SEC_StartingResources[idx+5] is the SEC_SiegeInformation troop-count
             * array that follows the 25-int resources array); 0x2a new invasion event (invasion maps only), 0x2b
             * new scenario event (not in just-build maps), both appended to scenarioEvents dated at the start date;
             * 0x3d/0x4f/0xa8/0xa9 open overlay sliders for scenario gold (extra options), popularity (non-siege),
             * siege starting gold and pitch; 0xa6/0xa7 cycle rations (0..4) and taxes (0..9) when extra options are
             * on; 0xab building availability; -1 cycles the start month. 0x26/0x4f in siege maps only clear
             * DAT_StopHandlingMenuItems.
             */
            void __cdecl MenuItemActionHandler_EditScenario_BaseMenuButtons(int param_1, ...);

            /**
             * Scenario editor text-box click handler: focuses the UserTextHandler buffer belonging to the clicked
             * box (box 0->15, 1->10 start year, 2->11 event year, 3/4/7->12 numeric value, 5->13, 6->14) unless
             * that buffer is already active.
             */
            void __cdecl MenuItemActionHandler_EditScenario_TextInputBoxes(int param_1, ...);

            /**
             * Scrollbar callback for the scenario event list: action 1 initialises range [0, eventsCount-20] with
             * value 0, 2/3 store the dragged position (clamped >= 0), 4 refreshes value and max, 5/6 step up/down;
             * position kept in MapPropertiesState.eventListScrollOffset and returned via currentValue.
             */
            void __cdecl MenuItemActionHandler_EditScenario_Scrollbar(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            /**
             * Click on a row of the scenario event/invasion list (no modal open): if offset+row is an existing
             * event, selects it (row, kind from header.tl_type, currentEventID), puts its year into text buffer 11
             * and opens the invasion (kind 1) or event (kind 3) editor modal.
             */
            void __cdecl MenuItemActionHandler_EditScenario_EventAndInvasionList(int param_1, ...);

            /**
             * Renders one row of the scenario event list: cell background (highlighted if selected), month and
             * year, then for invasions 'Invasion' + a number (data.scenario.actionData via the union) + '(x N
             * Month(s))' if invasion.repeatMonths != 0; for scenario events the event-type label (TEXT_SCENARIO
             * 0x80+type, 0x95+type when 0x80+type > 0x9b) and, if scenario.repeat != 0 and scenario.repeatMonths !=
             * 1, '(<repeatMonths> x <repeat> Month(s))' with the first number omitted when it is 10.
             */
            void __cdecl MenuItemRenderFunction_EditScenario_EventAndInvasionList(int param_1, ...);

            /**
             * Event list up/down arrow handler (no modal open): -2 scrolls down while offset < eventsCount-20, -1
             * scrolls up while offset > 0.
             */
            void __cdecl MenuItemActionHandler_EditScenario_UpDownButtons(int param_1, ...);

            /**
             * Render for event list arrow buttons: non-negative ids are text buttons labelled with
             * TEXT_SCENARIO[id] (shadowed text, white on hover); -1 draws the up arrow, other negatives the down
             * arrow.
             */
            void __cdecl MenuItemRenderFunction_EditScenario_UpDownButtons(int param_1, ...);

            /**
             * Renders the start-month button of the scenario editor: basic button with the month name
             * TEXT_MONTHS[SEC_StartingMonth+12] centered, highlighted on hover.
             */
            void __cdecl MenuItemRenderFunction_EditScenario_StartDateMonth(int param_1, ...);

            /**
             * Renders static labels of the scenario editor start-date panel: -5 -> TEXT_SCENARIO 0x27, -1 -> 0x20
             * ('Start Date'), both centered; id 0 draws nothing; other ids render TEXT_SCENARIO[id] centered if the
             * button has width, else left-aligned at ButtonX.
             */
            void __cdecl MenuItemRenderFunction_EditScenario_StartDate(int param_1, ...);

            /**
             * Renders the scenario editor base-menu buttons: 3 plain; with extra options enabled 0x3d gold value,
             * 0xa6 rations label, 0xa7 tax label; siege-only 0xa8 'Starting Gold' (SEC_StartingResources[15]) and
             * 0xa9 'Starting Pitch' ([8]) with icons; 0x4f popularity with value; 0x29 relabelled 0xa4 in siege
             * maps. Hidden: 0x2a unless invasion map, 0x26/0x4f in siege maps, 0x11/0x2a/0x2b in just-build maps;
             * the rest via RenderScenarioButtonWithText.
             */
            void __cdecl MenuItemRenderFunction_EditScenario_BaseMenuButtons(int param_1, ...);

            /**
             * Renders scenario editor text-input boxes with a cursor bar when focused, and live-parses the focused
             * numeric box (buffer 12) back into data: start goods (indexStored<20), siege attacking troop counts
             * (20..29; decompiled SEC_StartingResources[idx+5] = SEC_SiegeInformation[idx-20], reduced so
             * sumUnitPoints<=500), popularity (30), or invasion troop count (box 7, stored as short = value / per-
             * troop divisor). Box 7 is skipped when the troop slot is disabled. Ids 100/0x65/0x66 draw 'Total
             * Troops' sums (sumUnitPoints, sumUnitCounts, sumInvasionEventUnitCount); in 0x65 the uninitialised
             * 'number' is really sumUnitCounts' EAX return.
             */
            void __cdecl MenuItemRenderFunction_EditScenario_TextInputBoxes(int param_1, ...);

        } // namespace EditScenario
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
