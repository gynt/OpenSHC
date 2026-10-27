/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/ScenarioDescription.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace ScenarioDescription {

            /**
             * Prepare handler of the scenario description (briefing) view: loads the briefing background TGX files,
             * sets DAT_ScenarioDescPageMode for non-campaign modes, closes the AI-lord message modal, clamps missionNumber to
             * >= 1; for a fresh mission start (field22_0x64 == 0) loads the mission's siege header (except in
             * editor mode), zeroes the whole 8000-dword SEC_EventsExtra block and two mapAndTime fields, and in the
             * historic campaign sets difficulty 1 for missions < 4 else missionDifficulty; then resets event
             * status, briefing page state and start time and loads shc_back.
             */
            void __cdecl MenuView_ScenarioDescription_Prepare();

            /**
             * Initial-draw handler of the scenario description view: positions the menu at the border origin,
             * clears the screen black, draws the outer menu border and renders the background gfx.
             */
            void __cdecl MenuView_ScenarioDescription_DoInitial();

            /**
             * Per-frame handler of the scenario description (briefing) screen: redraws border and background, plays
             * the mission's briefing speech 1.5 s after g_scenarioDescStartTime (missions 1-20), and animates the
             * background via a per-250 ms frame table (frames drawn for the first 26 steps of each 15 s cycle). If
             * DAT_ScenarioDescBriefingPageOpen == 1 it shows the 'Briefing' header plus briefing text; otherwise
             * DAT_ScenarioDescPageMode selects 0 = objectives + briefing text (if the wrapped text would end below
             * y 0x1a4 it instead sets g_scenarioDescNeedsSecondPage (0xED26D4) and returns), 1 = objectives only,
             * or 2 = hints page (intro line, hints header (TEXT_HINTS 3 for one hint, 2 for several), revealed hint
             * lines, and a 'Click to reveal a hint' line for the first unrevealed one, revealed by clicking its
             * icon). Hint counts are two adjacent dword tables in MissionDefinedData: economic campaign missions
             * 33-37 (gameMode_2 5) read [missionNumber*4+0xB435B4] = ecoMissionHintCounts[missionNumber-33] at
             * 0xB43638..0xB43648 (exe init 0,1,2,1,2), other missions read [missionNumber*4+0xB4364C] = the
             * 21-entry table at 0xB43650 (+0xAFC, field28_0xafc/field29_0xb00, index missionNumber-1); 0xB4364C
             * itself is the byte flag crusadeMissionIntroActive, so Ghidra's ecoMissionHintCounts[missionNumber+5]
             * is only a folded-offset rendering. Revealed flags are mapAndTime.hintRevealed[hintIndex].
             */
            void __cdecl MenuView_ScenarioDescription_DoEveryFrame();

        } // namespace ScenarioDescription
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
