/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/ScenarioDescription.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace ScenarioDescription {

            /**
             * Render callback for the scenario-description (mission briefing) screen buttons. In builder mode only
             * buttons 10, 0xc, 0xd, -1, -3, -4 pass, and while the -2 sub-page is open (DAT_ScenarioDescBriefingPageOpen==1) only 0xc.
             * buttonId -1 draws the difficulty button (campaign missions >= 4 or economic campaign, briefing page
             * 0/1, mapU4Int1==0) with label + current difficulty name; -2 (TEXT_MISSION_BUTTONS 10), -3 (builder
             * mode with field22==1, TEXT_MISSION_BUTTONS 11) and -4 (builder mode, >= 2 description pages,
             * TEXT_MAPEDIT 10) draw text buttons. Buttons not applicable to the current mode/page are hidden by
             * leaving DAT_ButtonDisabled=1; the rest go to the generic button renderer.
             */
            void __cdecl MenuItemRenderFunction_ScenarioDescription_Main(int param_1, ...);

            /**
             * Action handler for the scenario-description (briefing) screen, ignored while a modal dialog is open.
             * 6/8/9 (campaign or economic campaign only) select briefing page 0/2/3 (9 opens help section
             * "mission%d.hlp"); 10 starts the mission: closes help, and if GameCore.field22==1 just returns to the
             * build menu, otherwise (non-builder modes) loads the mission map/lord, queues slot assignment, sets AI
             * nicknames, inits final results for missions > 15, then switches to the build menu, clears modals and
             * ends speech. 0xc/0xd in builder mode set DAT_MapMissionType from the map type and return to single-
             * player map choice (field22==0, restoring default player colours) or ask a yes/no dialog (param -7);
             * otherwise they fall through to 0xb, which first closes the -2 sub-page if open, else leaves to
             * MVT_HISTORIC_MISSION_SELECT (campaign) / MVT_ECONOMIC_MISSION_SELECT (economic) or asks
             * yes/no (param 1000) when field22!=0. -4 next description page (wraps), -3 yes/no dialog (param 0x2c),
             * -2 opens sub-page, -1 cycles difficulty 0..3 into missionDifficulty/missionDifficulty2.
             */
            void __cdecl MenuItemActionHandler_ScenarioDescription_Main(int param_1, ...);

        } // namespace ScenarioDescription
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
