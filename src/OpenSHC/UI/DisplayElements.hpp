/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/DisplayElements.hpp'
*/

#pragma once

#include "OpenSHC/UI/DisplayElement.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "WinDef.h"
namespace OpenSHC {
namespace UI {
    namespace DisplayElements {

        using OpenSHC::UI::DisplayElement;
        using OpenSHC::UI::Enums::DisplayElementID;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /**
         * DisplayElement render callback: draws the debug label 'Connect' (state 1) or 'Path linkage' (state 2)
         * with shadow in color 0x80FF at (posX,posY). The third parameter is the element state passed by the
         * display-element system, not a tile type.
         */
        void __cdecl RenderConnectAndPathLinkageInfoTextDisplayElement(int posX, int posY, DWORD tileType);

        /**
         * DisplayElement render callback: draws the current month name and year at (posX,posY) unless time is
         * halted, the map editor (landscaping) is open, display element 0x14 has a non-zero state, or the
         * barracks/mercenary-post tab of the building menu is shown.
         */
        void __cdecl RenderBottomLeftDateDisplayElement(int posX, int posY, DWORD elementState);

        /**
         * Display-element renderer for the local player's starting goods (pendingResources). Returns early in the
         * landscaping editor, GM_EDITOR, slot 2 of a siege builder map, and in multiplayer when the local lord is
         * dead/has an outcome or the remaining players are mostly one team; posY is moved down 0x32 when a
         * victory/defeat timer is shown (0x46 in King of the Hill). Counts non-zero entries (campaign with none
         * returns); tutorial resets the banner, siege-that sets scroll 2000/offset 30. In banner mode it draws a
         * title and scrolls an animated GM_INTERFACE_ICONS2 sprite 2 px per frame until it passes resolutionX (then
         * banner off except siege-that); otherwise startGoodsListOffsetY counts down. Finally each non-zero good
         * (25 goods, rows 30 px apart) is drawn as icon + amount, plus its name while the banner is active.
         */
        void __cdecl RenderStartingGoodDisplayElement(int posX, int posY, DWORD elementState);

        /**
         * Walks the singly linked display-element list from DAT_PointerToDisplayElementStackTop and returns the
         * element whose elementID matches, or NULL.
         */
        DisplayElement* __cdecl FindDisplayElementWithID(int elementID);

        /**
         * Finds a display element by ID, sets its state and makes it permanent (displayDuration = -1). If the state
         * actually changes, clears placementWarningVoicePlayed so the keep/granary warning voice
         * can play again.
         */
        void __cdecl CheckDisplayElementByIDAndSetForUnlimitedDisplay(
            DisplayElementID displayElementID, dword elementState);

        /**
         * Finds a display element by ID and activates it with the given state for displayDuration milliseconds,
         * stamping activationTime with timeGetTime(). NAME? generic timed activation, not specific to game-
         * speed/resource-lack elements.
         */
        void __cdecl ActivateDisplayElementForDuration(
            DisplayElementID elementId, dword elementState, int displayDuration);

        /**
         * Finds a display element by ID, makes it permanent and toggles it: state becomes 0 if currently non-zero,
         * else toggleValue. NAME? generic toggle, not ping-specific.
         */
        void __cdecl ToggleDisplayElementByID(DisplayElementID displayElementID, uint toggleValue);

        /**
         * Returns true if the display element with the given ID exists and its state is non-zero (i.e. it is
         * currently shown).
         */
        BOOLEnum __cdecl GetIfDisplayElementStateNotZero(DisplayElementID elementId);

        /**
         * Per-frame renderer for all active display elements. Screen position = element x/y + camera offset,
         * adjusted by the anchor flags: Y either unchanged, anchored to the bottom (resolutionY-600, +128 for
         * siege-tower/shield build tabs, -20 in the building/status menu) or offset by mainMenuBorderHeight; X
         * likewise. Calls the element's render callback with its state, then expires timed elements whose
         * displayDuration has elapsed since activation.
         */
        void __cdecl RenderDisplayElements();

        /**
         * Display-element callback: forwards to GameSynchronyState::renderInGameChat with position and state.
         */
        void __cdecl RenderInGameChatDisplayElement(int posX, int posY, DWORD elementState);

        /**
         * Display-element callback: renders missing-resource message variant 1 via
         * MissingResourceState::renderResourceMissingText.
         */
        void __cdecl RenderResourceMissing1DisplayElement(int posX, int posY, DWORD elementState);

        /**
         * Display-element callback: renders missing-resource message variant 2 via
         * MissingResourceState::renderResourceMissingText.
         */
        void __cdecl RenderResourceMissing2DisplayElement(int posX, int posY, DWORD elementState);

        /**
         * Debug performance overlay. Records the last game-loop duration and gameTicksThisLoop into 100-entry ring
         * buffers and computes the average loop ms, FPS (1000/avg, always stored in DAT_CurrentFramerate) and ticks
         * per second (1000 / (sum duration / sum ticks)). Unless elementState == -1000 (compute-only mode), it
         * prints the last duration, the average, FPS and ticks/s. It also computes the maximum buffered duration,
         * but never uses it (dead code, confirmed in the disassembly).
         */
        void __cdecl RenderDebugNumbersDisplayElement(int posX, int posY, DWORD elementState);

        /**
         * Debug display-element callback: prints DAT_UnknownStopwatch.duration right-aligned.
         */
        void __cdecl RenderAiRecomputeAttacksTimerDisplayElement(int posX, int posY, DWORD elementState);

        /**
         * Debug display-element callback: prints "Mission : Defaults" when state-1 == 0, otherwise "Mission :"
         * followed by state-1.
         */
        void __cdecl RenderMissionNumberDisplayElement(int posX, int posY, DWORD MissionNumPlus1Unk);

        /**
         * Debug display-element callback: prints the literal "No tree growth".
         */
        void __cdecl RenderNoTreeGrowthTextDisplayElement(int posX, int posY, DWORD elementState);

        /**
         * Game-over window element. 8 s after gameOverTime it switches to MVT_GAME_LOST if the local player has
         * not won, else to MVT_MISSION_FINISHED_TRANSITION. It draws a box sized for the number of winning players
         * (playerHasWon, slots 1-8) and a title (TEXT_MAINOPTIONS 0x10, or 0x11 'Defeat' if the local player has
         * not won), then one 30-px row per winner: the name in its player colour followed by 'Wins', with a
         * separate layout for English/American.
         */
        void __cdecl RenderInGameWinDefeatWindowDisplayElement(int posX, int posY, DWORD elementState);

        /**
         * Draws a bordered banner with TEXT_MAINOPTIONS string 0x10 (victory) when winDefeatState == 1, otherwise
         * 0x11 (Defeat).
         */
        void __cdecl RenderMissionWinDefeatBannerDisplayElement(int posX, int posY, DWORD winDefeatState);

        /**
         * NAME? Multiplayer connection-lost / resync dialog: 'Connection lost', a host (0x32) or client (0x33)
         * status line and a progress bar currentPacketTotalSize/resyncTotalBytes. Autosave line: 'Auto save is off'
         * when skirmishAutoSaveEveryMinutes == 0; otherwise 'Auto save is on', followed by 'Last saved: N minutes.'
         * (N >= 1) when both lastSaveTimeMs and desyncDetectedTimeMs are set and the save is older. Only the host
         * gets an active 'Cancel game' button (others see it grey); clicking sets cancelGameConfirmShown = 1, which
         * enlarges the box and shows Yes (queues GCT_KILL_GAME) / No (resets the flag). Better:
         * RenderConnectionLostDisplayElement. The iVar temporaries are reused argument slots of the text calls.
         */
        void __cdecl RenderConnectionLostDisplayElement(int posX, int posY, DWORD elementState);

        /**
         * Tooltip for the owner of the building or wall under the mouse. In single player it runs only in the
         * editor build menu. Skips pitch ditches, killing pits, signposts and (when mapU4Int0) somePlayerID's own
         * buildings. The hovered owner ID goes into g_hoverPlayerInfoTextId together with a timestamp. After
         * hovering ends the tooltip stays fully visible for 400 ms, fades between 400 and 720 ms, then clears.
         * Editor build menu: draws TEXT_BUBBLE_HELP_TEXT entry id+0xcc. Otherwise: player name, player shield icon
         * (0x222+id), portrait (AI icon 0x20a+aiType, lord icon 0x21b/0x21c or a custom bitmap face) and team icon
         * if playerGroupArray > 0.
         */
        void __cdecl RenderPlayerInfoOnHoverDisplayElement(int posX, int posY, DWORD elementState);

        /**
         * Display-element callback: prints "Game Speed" followed by DAT_GameCore.gameSpeedLevel.
         */
        void __cdecl RenderGameSpeedTextDisplayElement(int posX, int posY, DWORD elementState);

        /**
         * Scoreboard. For each occupied player slot 1-8 (currentPlayerFullIDArray != -1) it draws a 190x55 dark
         * box, boxes 200 px apart. Inside: the player name (newlines turned into spaces, cut at 170 px) in player
         * colour, and below it PlayerData.skirmishPointsLeft as up to 8 digits without leading zeros. The digit block
         * is centred using a width taken from the magnitude of GameSynchronyState.skirmishPoints, not of the
         * printed value. NAME? RenderPlayerScoresDisplayElement.
         */
        void __cdecl RenderKingOfTheHillScoresDisplayElement(int posX, int posY, DWORD elementState);

        /**
         * Map-editor element: prints "People available to place:" and 2499 - DAT_UnitsState.unitCount.
         */
        void __cdecl RenderPeopleLeftToPlaceDisplayElement(int posX, int posY, DWORD elementState);

        /**
         * Keep/granary placement hint. Outside in-game menus or in the Crusader tutorial it hides itself (state 0).
         * Otherwise it measures TEXT_FEEDBACK string 9+whichBuildingIsMissing, draws it word-wrapped (max width
         * 580) and centred on posX/posY. For state 1 (keep) / 2 (granary) it plays other_warning1.wav /
         * other_warning2.wav, but only if placementWarningVoicePlayed is still FALSE, then sets
         * that flag.
         */
        void __cdecl RenderAndPlayKeepAndGranaryPlacementInfoDisplayElement(
            int posX, int posY, DWORD whichBuildingIsMissing);

        /**
         * Multiplayer ping overlay: outside solitary/single-player skirmish it draws a blended box and, for every
         * occupied player slot 1..8, the slot number in the player's colour and, for other players,
         * connectionLagInfoArray[slot].avgHalfRttMs*2 followed by "ms". In single-player it ends its own display
         * element (DEID_PLAYER_PING, state 0). The timeGetTime() result is unused. NAME? the 'Unk22' is
         * unnecessary (RenderPlayerPingDisplayElement).
         */
        void __cdecl RenderPlayerPingDisplayElement(int posX, int posY, DWORD elementState);

        /**
         * Shows the centred "Game Paused" text (TEXT_FEEDBACK 0x16) with shadow while
         * DAT_GameCore.gamePausedLogical is set; otherwise ends the DEID_GAME_PAUSED_TEXT element.
         */
        void __cdecl RenderGamePausedTextDisplayElement(int posX, int posY, DWORD elementState);

        /**
         * "Time Until Victory" box (display element 0x1A): hidden/ended when DAT_GameCore.section1095 == 2. Shifts
         * posX left by a per-resolution amount, stores textWidth + 16 in g_victoryTimerDisplayBottomY (the Time
         * Until Defeat box adds it to its X so it sits to the right of this box), then draws a blended black box,
         * the title and a progress bar whose fill is (SEC_Section1090 - SEC_Section1080) / SEC_Section1090 of the
         * text width. textWidth first holds the font size 0x12 passed to computeTextWidth.
         */
        void __cdecl RenderTimeUntilVictoryDisplayElement(int posX, int posY, DWORD elementState);

        /**
         * Skirmish "No Rush" countdown: when skirmishNoRushTicks (the decrementing counter) is 0 plays
         * battlehorn.wav and ends DEID_NO_RUSH; otherwise draws the label (TEXT_SKIRMISH_MISC 7) at a per-
         * resolution x position with a bar of width textWidth+50 whose fill is skirmishNoRushTicks /
         * skirmishNoRushTicksLeft (shrinks as the counter runs down). textWidth first holds the font size 0x12.
         */
        void __cdecl RenderNoRushCountdownDisplayElement(int posX, int posY, DWORD elementState);

        /**
         * 'Time Until Defeat' box (element 0x1B; hidden when section1095 == 2): per-resolution X shift, moved right
         * by g_victoryTimerBoxWidth when element 0x1A (Time Until Victory) is shown. deadline = (months from map
         * start to the time-until-defeat event) * 800 ticks; remaining = deadline - monthsElapsed*800, minus
         * week*200 and gameTicksLoadBalancer when time runs and element 0x14 is not shown; clamped >= 0; bar fill =
         * (deadline - remaining)/deadline of the text width. Existing local names are misleading: halfWidth holds
         * the 0x1A flag, text X, start month index, then deadline ticks; centerX holds the font size, then months
         * elapsed; textWidth is the font size then the title width.
         */
        void __cdecl RenderTimeUntilDefeatDisplayElement(int posX, int posY, DWORD elementState);

        /**
         * NAME? Multiplayer '<name>: Not Responding' box for laggingPlayerSlot. While no result is pending
         * (notRespondingResultTimeMs == 0) the host checks the player: slot now empty -> laggingPlayerMessageID
         * 0x41 'Timed Out'; last message within 10 s -> 0x43 'Back in the Game!'; in both cases it stores the time
         * and queues GCT_NOT_RESPONDING_RESULT. Otherwise the host sees a countdown clamp(60 - lag seconds, 0, 50)
         * and an 'Eject' button (sets 0x42 'Ejected' and queues the command); non-hosts see a grey 'Eject' label.
         * Once a result is pending the box shows that TEXT_MULTIPLAYER_CONNECTION text and closes after 2 s
         * (resetting laggingPlayerSlot and hiding the element). Nothing is ejected automatically here. Better:
         * RenderPlayerNotRespondingDisplayElement.
         */
        void __cdecl RenderPlayerNotRespondingDisplayElement(int posX, int posY, DWORD elementState);

    } // namespace DisplayElements
} // namespace UI
} // namespace OpenSHC
