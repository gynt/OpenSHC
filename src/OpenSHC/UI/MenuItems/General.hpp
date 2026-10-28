/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/General.hpp'
*/

#pragma once

#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "WinDef.h"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace General {

            using OpenSHC::Commands::MappersEnum;
            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            /**
             * Renders the lobby mini-map (only when no modal is active and a map is selected): bordered box, map
             * preview (when not fading), then for each of the 8 keep start positions with x >= 0 a marker, skipping
             * the player currently being dragged: free positions (-10) as free-slot icons, occupied ones with a
             * team icon (team > 0) plus either a colour flag (ICONS2 0x1d6+player) or, when INT_00b95f6c is set,
             * the player's face / AI lord portrait; the hovered position (DAT_LobbyMinimapHoveredKeepIndex) uses highlighted icons. The
             * dragged player's flag is drawn at the mouse and the drag is cleared once the button is released; the
             * hover index is reset to -1 each frame.
             */
            void __cdecl MenuItemRenderFunction_General_MenuMiniMap(int param_1, ...);

            /**
             * Renders the advanced skirmish/lobby option rows: tech level (0x1f), win condition (0x24), troops
             * free/cost gold (0x53), fog of war (0x6d), start gold (0xe), popularity (0xf), game speed (0x52),
             * autosave (0x5e), alliances (100), strong walls (99), no cow throwing (-10), no dogs (-11), no-rush
             * timer (-12), extreme mode (-13), extreme-mode-2 flag (-14, on only if both extreme flags set), title
             * (-1000) and a plain button (0x67); label left, value text or check icon (0xce on / 0xd0 off) right.
             * Rows are hidden in map-transfer / AI-select / roundtable modals, restricted in the skirmish play
             * options modal, and partly hidden in single-player or for non-hosts; non-hosts never get the hover
             * colour. The blend expression ((b-32)*32)/32+32 equals DAT_ButtonBackgroundBlendStrength.
             */
            void __cdecl MenuItemRenderFunction_General_AdvancedGameOptions(int param_1, ...);

            /**
             * Host-only action handler for the skirmish/multiplayer advanced game options buttons (param = button
             * action id): opens sliders for start gold (0xE), popularity (0xF), game speed (0x52), points (-1) and
             * win condition (0x24); cycles tech level, fog of war, auto-save interval (0/5/10/20) and no-rush
             * setting (0..5); toggles troops-cost-gold, strong walls, alliances, no cow throwing, no dogs, Extreme
             * mode and Extreme powers; 0x5D/0x67 open the connection/play-options modals and -1000 closes the
             * modal. Changes are queued as GCT_CHANGE_GAME_INTENSITY_OR_BALANCE; for auto-save, no-rush and most
             * toggles an 'Option :Value' chat line is also sent to all other players via GCT_TAUNT_OR_CHAT. Ignored
             * for non-hosts, while a send/receive-map, roundtable or AI-lord-select modal is open, and (in the
             * skirmish play-options modal) for ids outside a whitelist. Original-game display bug: the 'Extreme
             * Powers around Lord' (-0xE) announcement reports the state of skirmishExtremeMode instead of the
             * toggled field.
             */
            void __cdecl MenuItemActionHandler_General_AdvancedGameOptions(int param_1, ...);

            /**
             * Menu item action handler: stores its parameter (a build-menu tab type) in DAT_GameCore.field12_0x30,
             * which ToolbarButtonPressed later uses as the build-menu tab to switch back to after selecting a
             * placement command.
             */
            void __cdecl MenuItemActionHandler_General_SetToolbarRequestedBuildTab(int param_1, ...);

            /**
             * Menu item function that just clears DAT_StopHandlingMenuItems (re-enables processing of further menu
             * items); its parameter is unused.
             */
            void __cdecl MenuItemFunction_General_ClearStopHandlingMenuItems(int param_1, ...);

            /**
             * Handles a toolbar/build-menu button press (MappersEnum command id): aborts while syncing, saving,
             * paused, after the local lord was killed, when the player is dead (unless non-solitary and gameOver ==
             * own slot) or when the tutorial forbids it. Dispatches unit stances, engineer build mode, a siege-
             * engine command (GCT 86) when catapults/trebuchets are selected (one variant needs 10 stone), patrol
             * toggle, camera focus on the player's stockpile/market/granary/armoury/barracks/mercenary post/guilds,
             * wall stone check, editor moat/anti-moat variants, random gibbet-heads variant and gate variant by map
             * rotation. Then for building commands checks the required resources, sets
             * TileMapState.placeUnitCount=1 and currentMapperCommand to the (adjusted) command, plays SFX 0x87
             * and, for non-siege, non-tunnel, non-assembly-point commands, switches the build menu back to the
             * stored tab (GameCore.field12_0x30).
             */
            void __cdecl MenuItemActionHandler_General_ToolbarButtonPressed(MappersEnum buttonID);

            void __cdecl MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface();

            /**
             * Action handler for text input fields: selects the UserTextHandler text slot belonging to the clicked
             * field (0 -> slot 5 numeric+dot / IP, 1 -> slot 6, 2 -> slot 7 numeric, 3 -> slot 0 unless
             * GameCore.playerNameAlreadySet) if it is not already active.
             */
            void __cdecl MenuItemActionHandler_General_TextInputDisplay(int param_1, ...);

            /**
             * Render function for text input fields: draws the button background, a cursor bar at the current text
             * width (fields 0 and 1 only when their slot is active, fields 2..4 always) and the text of the
             * matching UserTextHandler slot (field 0..3 -> slots 5,6,7,0). Field 4 draws slot 0 onto the map
             * surface when not in the main menu, then resets the pencil/text targets to RT_SCREEN_MENU; field 3 is
             * skipped entirely when GameCore.playerNameAlreadySet is TRUE.
             */
            void __cdecl MenuItemRenderFunction_General_TextInputDisplay(int param_1, ...);

            /**
             * Renders a game-options menu text button: basic button background plus centered text
             * TEXT_GAME_OPTIONS[param], brighter when hovered/interacting.
             */
            void __cdecl MenuItemRenderFunction_General_GameOptionsTextButton(int param_1, ...);

            /**
             * NAME? Generic Yes/No confirmation-dialog handler. 0x17 (No): for pending action 2000 queues 'stop
             * sending map' (GCT_REPORT_MAP_TRANSFER_NEED, param0=1); for 0x2F (mission finished) revives the
             * local player, re-activates scenario events, schedules the next-month event and sets
             * GameCore.section1095=2; then pops the dialog. 0x16 (Yes) executes
             * DAT_MenuTextInputState.DAT_MenuOptionsActionParameter: 9 quit to Windows, 0x1E save (multiplayer:
             * GCT_SAVE with tick+unit hash; else opens the save progress box), 0x2B custom scenarios, 0x2C restart
             * mission/skirmish/trail, 0x2F mission-finished transition, 0x31 spawn invasion wave, 2000 append
             * '.map' to the map name and start sending the map file, 7/1000 quit the current game (multiplayer: re-
             * init lobby; otherwise disconnect, stop sounds, restore the editor auto_backup_map.map if pending, and
             * switch to the matching menu), and -7 resets the player colours to defaults and then quits exactly
             * like 7. Not specific to multiplayer launch/quit.
             */
            void __cdecl MenuItemActionHandler_General_ConfirmDialogYesNo(int param_1, ...);

            /**
             * Slider callback for the scenario-event editor and trigger-event dialog. param_1 selects the slider:
             * 5/0xC/0x12/0x13/0x15 edit the current event's actionData (only if its type == id-1; max
             * 10/5/5/20/20), -10 edits the trigger-event amount (max = invasionEventContent._164_4_), -2 repeat-
             * every-N-months (1..10) and -1 repeat count (0..60), the last two only for event types 5, 0xB-0x14,
             * 0x1D, 0x1E. param_2 is the slider operation: 1 init min/max/value, 2/3 store dragged value, 4 refresh
             * and clamp, 5 increment up to max, 6 decrement while > 0 (can reach 0 below the min of 1) - 5/6 only
             * for the actionData and amount sliders; 7 sets the value to 1 (repeat sliders only).
             */
            void __cdecl MenuItemActionHandler_General_EventSlider(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            /**
             * Render callback for the event-editor sliders: hidden unless the slider applies to the current event
             * type (same rules as the EventSlider action handler); draws the track, the thumb box (lime while
             * dragged, greyish yellow otherwise) and the current value number to the right, or '-' for the repeat-
             * months slider (-2) at value 10.
             */
            void __cdecl MenuItemRenderFunction_General_EventSlider(
                int param_1, int thumbYPos, int param_3, int thumbHeight, BOOL isDragged);

            /**
             * Slider callback for the message-list scrollbar: range 0..(MapPropertiesState.total - _79184_4_),
             * operations 1 init (value 0), 2/3 set offset from drag, 4 refresh, 5 scroll up (offset-1 while > 0), 6
             * scroll down (offset+1 while below max); writes the resulting offset back to *currentValue.
             */
            void __cdecl MenuItemActionHandler_General_MessageScrollbar(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            /**
             * Generic vertical scrollbar render callback: draws the scrollbar (track + thumb at
             * thumbYPos/thumbHeight, highlighted when dragged) at the current button rect on the screen-menu
             * surface, then restores the draw target to RT_MAP_GAME.
             */
            void __cdecl MenuItemRenderFunction_General_Scrollbar(
                int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged);

            /**
             * Renders one arrow button of the message scrollbar on the screen-menu surface: arrow variant 0 for
             * button id -1 (presumably up), variant 1 for any other id (down).
             */
            void __cdecl MenuItemRenderFunction_General_MessageScrollbarUpDown(int param_1, ...);

            /**
             * NAME? Render callback for buttons of the trigger-event / invasion dialogs (not an event-creation
             * callback). Maps button ids to an option index; for 0x92/0x94 draws the TEXT_SCENARIO 0x92 label plus
             * ' - ' and an INTERFACE_ICONS2 icon (0x82 for 0x92, 0x80 for 0x94); for 0xDD/0xDE draws the button
             * highlighted when its index matches invasionEventContent.crusaderArabian; otherwise delegates to
             * RenderScenarioButtonWithText.
             */
            void __cdecl MenuItemRenderFunction_General_CreateEventCallbackFunction(int param_1, ...);

            /**
             * Render callback for event-editor buttons: button -1 shows the current scenario event's month as
             * centered text (TEXT_MONTHS month+12); any other id delegates to RenderScenarioButtonWithText.
             */
            void __cdecl MenuItemRenderFunction_General_EventButtonAndData(int param_1, ...);

            /**
             * Action handler of the trigger-event / trigger-invasion dialogs: buttons 9/10/0xB/0xC/0x57/0xDD/0xDE
             * set invasionEventContent.crusaderArabian (0..4), 0x17/0x2E open the trigger-event / invasion dialogs,
             * 0x24 closes. Choosing 0x8B poison clouds, 0x91 lions, 0x92 bandit maces at a signpost, 0x94
             * archers+monk marching to the keep or 0xB3 fire stores the event, resets the amount to 1 and opens the
             * amount slider (max 10 or 50); confirm (0x25) executes the stored event and starts its per-player
             * popularity countdown (popularityEventWeeksLeft / someCount49..51). Immediate events: 0x85 travelling
             * fair (jugglers/fire-eaters at the campground), 0x8F tree die-off, 0x90 rabbits (only with a free
             * spawn slot and a hop or wheat farm), 0x95 marriage, 0x96 jester (both cap popularity at 10000 and
             * start countdowns someCount52/53), 0xD4 invasion wave (no message). Events play their
             * Random_EventsN.wav (fire: general_message3.wav) message video with a TEXT_ACTION line and close the
             * dialog. actionId and spawnXOrTribe2 are stack slots reused as spawn y/x (lions) and as the
             * archer/monk tribe ids (0x94); the decompiler's in_ECX is only the stale value of the slot reserved by
             * the prologue 'push ecx' (no register parameter).
             */
            void __cdecl MenuItemActionHandler_General_TriggerEventMenu(int param_1, ...);

            /**
             * Render callback for crusade-map / end-screen buttons: button 1000 draws its picture plus the
             * DAT_TrailMissionSkipsLeft counter and, while hovered, a centered TEXT_CHEATS line (offset 0 if the
             * counter >= 1, else 1, e.g. 'Skip Current Mission'); buttons 10/11/99 just draw their picture.
             */
            void __cdecl MenuItemRenderFunction_General_CrusadeMapAndEndscreen(int param_1, ...);

            /**
             * Menu item action wrapper that forwards its parameter to
             * BottomLeftTextDisplayState::renderCurrentlyDisplayedText.
             */
            void __cdecl MenuItemActionHandler_General_DisplayConditionalText(int param_1, ...);

            /**
             * Menu item action wrapper that calls BottomLeftTextDisplayState::hasPassedCountdownOrDuration, which
             * expires the bottom-left text once its duration has passed; parameter unused.
             */
            void __cdecl MenuItemActionHandler_General_TickBottomLeftTextExpiry(int param_1, ...);

        } // namespace General
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
