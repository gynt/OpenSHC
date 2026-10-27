/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/Unused.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace Unused {

            /**
             * Render callback of the (unused) economic game-type select menu: non-hovered buttons (except 5) show
             * an animated GM frame ((now - stateTransitionTime)/100 mod 64, frames above 15 shown as 0) and drop
             * the remembered hover id; hovered buttons (and 5) get small per-button offsets, are drawn by the
             * generic renderer and play a hover SFX when the hovered button (< 5) changes.
             */
            void __cdecl MenuItemRenderFunction_UnusedEconomicGametypeSelect_Main(int param_1, ...);

            /**
             * Unused economic game-type menu action handler. Button 1 clears GameCore.briefingOpenedFromInGame, takes
             * difficulty from missionDifficulty2 and opens the unused economic mission select; buttons 2/3 set up a
             * builder-mode standalone map choice (mission 0, all troop types producible, teams reset,
             * DAT_MapMissionType 1 or 0 with difficulty missionDifficulty_1/_0, standalone filename cleared);
             * button 5 returns to the main menu, 4 does nothing. Cases 1-3 also restore the default player slot
             * unit colours.
             */
            void __cdecl MenuItemActionHandler_UnusedEconomicGametypeSelect_Main(int param_1, ...);

            /**
             * Unused set-name screen button renderer. Hides the button (DAT_ButtonDisabled=1) when it is button
             * 8 while unknownFlag_0x118 is TRUE or button 0x19 while it is FALSE; otherwise draws a basic button
             * with centered TEXT_MAINOPTIONS string buttonId, highlighted when hovered.
             */
            void __cdecl MenuItemRenderFunction_UnusedSetName_OkAndChangeTitleButtons(int param_1, ...);

            /**
             * Unused set-name screen action handler. Button 8 resets the user text input to slot 9 and returns to
             * the main menu; button 0x19 clears unknownFlag_0x118 and resets user text input to slot 0.
             */
            void __cdecl MenuItemActionHandler_UnusedSetName_OkAndChangeTitleButtons(int param_1, ...);

            /**
             * Renders one row of the unused economic mission list (row ids are negative mission numbers, -id ==
             * missionNumber1to20 when selected). Missions beyond furthestMission (unless all campaigns unlocked)
             * get a disabled table cell and are hidden; otherwise draws a cell (selected style for the current
             * mission), the number -id-0x20 and the mission name TEXT_MISSION_NAMES[-id-0xb], highlighted when
             * selected or hovered. Only when no modal dialog is open.
             */
            void __cdecl MenuItemRenderFunction_UnusedEconomicMissionSelect_MissionSelect(int param_1, ...);

            /**
             * Unused economic mission select action handler. Button 0xd (or a double-click within 500 ms on the
             * same mission row) starts the selected mission as an SH1 economic campaign (decrements
             * missionNumber1to20 then incrementMission); 0x12 returns to main menu; 0x14 cycles difficulty 0..3;
             * negative ids select mission -buttonId and record click mission/time for double-click detection.
             */
            void __cdecl MenuItemActionHandler_UnusedEconomicMissionSelect_General(int param_1, ...);

            /**
             * Renders a button of an unused mission-start screen: rounded box (blue-filled when hovered) with
             * centered shadowed TEXT_MAINOPTIONS string buttonId. Only when no modal dialog is open.
             */
            void __cdecl MenuItemRenderFunction_UnusedSomeMissionStartUnk_General(int param_1, ...);

            /**
             * Unused mission-start screen action handler. Button 0xd switches to the build menu (hunter's hut tab),
             * loads the mission map for missionNumber1to20 and its lord, clears modal dialogs 2-6 and queues
             * GCT_ASK_FOR_SLOT_ASSIGNMENT; button 0xe returns to the main menu. Only when no modal dialog is open.
             */
            void __cdecl MenuItemActionHandler_UnusedSomeMissionStartUnk_General(int param_1, ...);

            /**
             * Unused handler that sets up a single-player skirmish lobby with numEnemies random AI opponents: opens
             * the lobby menu, makes the local machine host (DPLAYX player ID 1, currentPlayerSlotID 0), copies the
             * user name (text slot 0) into player name 1, marks all 9 slot entries, then for players
             * 2..numEnemies+1 picks a random AI personality (1..numAILordsWithAIV) and resets its variation.
             */
            void __cdecl MenuItemActionHandler_UnusedSelectRandomNumberOfEnemies_Main(int param_1, ...);

            /**
             * Unused old title menu: renders the 'Exit' debug button (colour box white/black with inverted text
             * colour when hovered).
             */
            void __cdecl MenuItemRenderFunction_UnusedOldTitleMenu_ExitButton(int param_1, ...);

            /**
             * Unused old title menu: renders the 'Continue' debug button (colour box white/black with inverted text
             * colour when hovered).
             */
            void __cdecl MenuItemRenderFunction_UnusedOldTitleMenu_ContinueButton(int param_1, ...);

            /**
             * Unused old title menu: renders the 'Test map' debug button (colour box white/black with inverted text
             * colour when hovered).
             */
            void __cdecl MenuItemRenderFunction_UnusedOldTitleMenu_TestMapButton(int param_1, ...);

            /**
             * Renders buttons of the unused 'choose available keeps' map-editor screen. Button 7 uses the generic
             * button renderer; negative ids -1..-5 are toggles for GameCore.availableKeepFlags[-id-1] (shown as
             * GameCore+0x1534-4*id) and are drawn with GM index 0x70 when that flag is 0; ids 0xe..0x12 are drawn
             * as non-interactive highlighted labels; button 0xb (continue) is greyed when all five flags are 0;
             * others are normal TEXT_MAPEDIT buttons.
             */
            void __cdecl MenuItemRenderFunction_UnusedChooseAvailableKeeps_Main(int param_1, ...);

            /**
             * Action handler of the unused 'choose available keeps' screen. 7 goes back to the map-size menu; 0xb
             * opens map editor properties (and sets GameCore.editorMapLoaded) if at least one keep flag is set;
             * -1..-5 XOR-toggle GameCore.availableKeepFlags[-id-1].
             */
            void __cdecl MenuItemActionHandler_UnusedChooseAvailableKeeps_Main(int param_1, ...);

            /**
             * Renders buttons of the unused 'choose game type' map-editor screen: button 7 via the generic
             * renderer, others as basic buttons with centered TEXT_MAPEDIT string buttonId, highlighted when
             * hovered.
             */
            void __cdecl MenuItemRenderFunction_UnusedChooseGameType_Main(int param_1, ...);

            /**
             * Action handler of the unused 'choose game type' screen: 7 goes back to map size; 0x1c/0x1d/0x1e/0x21
             * set the new map type to siege/invasion/economic/just-build and open the map editor properties menu
             * (setting GameCore.editorMapLoaded).
             */
            void __cdecl MenuItemActionHandler_UnusedChooseGameType_Main(int param_1, ...);

            /**
             * Renders buttons of the unused 'Siege That' creation screen (id -1 is skipped). Button 5 uses the
             * generic renderer; save buttons 0x23/0x24 are greyed out while siegeThatMapReady is 0 (no map
             * loaded/created yet); others are normal TEXT_MAPEDIT buttons.
             */
            void __cdecl MenuItemRenderFunction_UnusedCreateSiege_SiegeThat(int param_1, ...);

            /**
             * Unused old title menu action handler: any button requests the game window to close
             * (postWindowCloseMessage = 1), i.e. quits.
             */
            void __cdecl MenuItemActionHandler_UnusedOldTitleMenu_General(int param_1, ...);

            /**
             * Action handler of the unused 'Siege That' creation screen. 2 opens the load-map dialog; 4 loads
             * mission22.map as a siege template (1500 gold / 1000 of resource 4 start resources for the local
             * player, clears moat/pitch counts, imports trading costs, clears attack info, recomputes AI zoner
             * layer) then falls through to 6 which enters siege-that editing mode (gameMode GM_SIEGE_THAT, mission
             * 0x1f, player slot 1, mapper to main); 5 returns to custom scenarios, or asks to quit if editing is
             * active; 0x23/0x24 save the map as editable/playable siege when a map is ready.
             */
            void __cdecl MenuItemActionHandler_UnusedCreateSiege_SiegeThat(int param_1, ...);

            /**
             * Renders an option row of the drop-down/list modal held in DAT_MenuModalComposition1 (set up by
             * setModalSliderParameters): rows below mbr_0x64 get a blended black box (greyish-yellow fill when
             * hovered) and centered text from the modal's textGroup at textIndex+row; other rows are not drawn.
             */
            void __cdecl MenuItemRenderFunction_UnusedWinCondition_Options(int param_1, ...);

            /**
             * Closes the slot-0 modal (DAT_MenuModalComposition1) on a right-click, or on a left-click outside the
             * box of the slot-1 composition DAT_MenuModalComposition2 (machine code tests 0x2403680..); after
             * closing, if sliderCallbackFunction is set it is called and minus1 is set to -1 (suppress mouse
             * capture for this frame). NAME? acts as 'close on click outside' rather than deselect.
             */
            void __cdecl MenuItemActionHandler_UnusedWinCondition_CloseOnClickOutside(int param_1, ...);

            /**
             * Selects option rowIndex of the drop-down modal: stores it in sliderValue and *destination, closes the
             * modal and tail-calls sliderCallbackFunction if set. Ignored if rowIndex >= option count (mbr_0x64).
             */
            void __cdecl MenuItemActionHandler_UnusedWinCondition_Options(int param_1, ...);

            /**
             * Selects list entry index (offset by scroll offset) in the scenario event editor list if within total
             * and index != -1: stores the index and the entry value, and writes the value as actionData of the
             * current scenario event (both flag branches do the same).
             */
            void __cdecl MenuItemActionHandler_UnusedCreateMessageEvent_SelectListEntry(int index, ...);

            /**
             * Renders buttons of the unused create-message-event screen (TEXT_SCENARIO labels). Page
             * field69_0x13590: on page 4 buttons 9..0xc are hidden, otherwise 0x3f1..0x3f4 are hidden. Buttons 4..8
             * are page tabs, the one with id-4 == page is drawn highlighted. Page 4: option 0x3f1+_79252_4_ or
             * 0xd+_79256_4_ is highlighted, ids 0x3f1..0x3f4 draw an enemy-lord face (GM_ENEMY_FACES id-0x3f0)
             * above label id-1000. Page 3: option 8+_79252_4_ highlighted, ids 9/10 remapped to texts 0x18/0x19 and
             * 0xb/0xc hidden. Pages <3 draw nothing for ids > 8.
             */
            void __cdecl MenuItemRenderFunction_UnusedCreateMessageEvent_Buttons(int param_1, ...);

            /**
             * Selects list row rowIndex (plus scroll offset) of a message-box list in the scenario editor if within
             * total: stores row index, entry value, absolute index and click time (likely for double-click
             * detection).
             */
            void __cdecl MenuItemActionHandler_UnusedChooseMessageBox_SelectListEntry(int param_1, ...);

            /**
             * Scenario event editor (message event) action handler: -1 cycles the current event's month 0..11; 0x13
             * (only when flag==0) deletes the current event, closes the dialog and re-sorts events. 0x25 (OK): flag
             * 0 -> deletes the event if no value was chosen (value -1) else sets its year from text slot 0xb, then
             * closes and re-sorts; flag 1 -> sets actionData=-1 if no value, opens the new-event-action dialog;
             * other flag -> stores value as GameCore.descriptionStringTableIndex and closes. NAME? handles
             * date/OK/delete rather than text.
             */
            void __cdecl MenuItemActionHandler_UnusedCreateMessageEvent_SetTextUnk(int param_1, ...);

        } // namespace Unused
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
