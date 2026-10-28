/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Helpers.hpp'
*/

#pragma once

#include "OpenSHC/Map/Buildings/BuildingFailReasonEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/EuroRecruitableState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "WinDef.h"
namespace OpenSHC {
namespace UI {
    namespace Helpers {

        using OpenSHC::Map::Buildings::BuildingFailReasonEnum;
        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::Map::Units::EuroRecruitableState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /**
         * Loads the shc_back.tgx background graphic.
         */
        void __cdecl LoadTGX_shc_back();

        /**
         * Menu prepare callback: marks not in-game, resets loaded gfx, loads frontend_combat3.tgx and shc_back.tgx,
         * positions the current menu at the main-menu border offset and opens modal dialog 0x14.
         */
        void __cdecl MainMenu_Unknown21_Prepare();

        /**
         * Returns TRUE when a modal dialog is active that is not one of the AI-lord selection (basic/extended) or
         * roundtable dialogs. NAME? nothing quit-related is checked.
         */
        BOOLEnum __cdecl AModalDialogIsActiveButIsNotQuitting();

        /**
         * Queues GCT_CHANGE_GAME_INTENSITY_OR_BALANCE, resets two sync fields to -1 and sends the chat message
         * "Game Speed :N" (taunt/chat id 10000) to every player slot except the local one, then clears the user
         * text entry.
         */
        void __cdecl CallbackSetMultiplayerSpeedLevel();

        /**
         * Clears the four per-slot siege remaining-point counters (g_siegeRemainingPointsPerSlot..c4) and the 4 per-slot siege army
         * arrays DAT_SiegeInformationPerDifficulty - but only the first 11 of the 21 counts of each 0x54-byte slot are
         * zeroed (confirmed in machine code); the rest keep old values.
         */
        void __cdecl ClearSiegeInformationArray2();

        /**
         * NAME? Siege army setup across the 4 difficulty slots: computes the point budget of slot 1 from its OLD
         * contents (DAT_SiegeRemainingPoints2 = slot-1 remaining + sum count*cost over 21 entries), scales it into
         * per-slot budgets with siegeArmyPercentDifficulty 167/100/75/50, copies the current army
         * (DAT_SiegeInformationArray) into all 4 slot armies and DAT_SiegeRemainingPoints into all 4 remaining-
         * points entries, then - if editedSlot != 1 - rescales the edited slot to 100% into slot 1 (remaining =
         * budget - cost, >= 0), and finally derives every slot other than 1 and editedSlot as slot1*percent/100
         * with remaining = slotBudget - cost (>= 0). Both callers pass editedSlot = 1, so the rescale branch never
         * runs. Quirk (harmless): the loops cover 21 entries but the cost table at 0x6172F8 has only 20, so entry
         * 20's cost is read from siegeArmyPercentDifficulty[0] (167); entry 20 of the current army is only ever
         * written with 0 or copied back from slot entry 20, which is itself only derived from it, so it is always
         * 0. Better: PropagateSiegeArmyToSlots.
         */
        void __cdecl PropagateSiegeArmyToSlots(int editedSlot);

        /**
         * Loads the siege army of the given slot from DAT_SiegeInformationPerDifficulty into DAT_SiegeInformationArray
         * (21 counts) and its remaining points into DAT_SiegeRemainingPoints. NAME? LoadSiegeSlotArmy.
         */
        void __cdecl LoadSiegeArmyFromSlot(int slot);

        /**
         * Map-editor new-map init: loads frontend_builder2.tgx, clears map/time/player and signpost data, resets
         * tile sections, heights and pathing layers, redraws the minimap, sets the viewport, default starting
         * year/resources, clears animal spawns, sets every barracks recruitability (archers field, 14 bytes before)
         * and SEC_MercRecruitable entry to 1 and all weapon production flags to 1, then loads shc_back.tgx.
         */
        void __cdecl InitializeBasicMap();

        /**
         * If DAT_GameCore.scribeReactionType is 0 (nothing pending), stores the given value, sets the scribe flag,
         * records timeGetTime() and resets scribeAnimationFrame2. Called from the Keep and Granary building menus
         * and from building placement.
         */
        void __cdecl TriggerScribeReaction(int taxesSettingUnk);

        /**
         * Setter for DAT_TribesState.patrolButtonPressed.
         */
        void __cdecl SetTribesPatrolButtonPressed(BOOLEnum pressed);

        /**
         * Returns 0 when the minimap flag field15_0x3c is 0, the floor tile under the mouse has logic bits
         * 0x10000300, and that tile's view-rotated x+y (rotation by mapOrientation 2/4/6 on the 400-tile grid) is
         * greater than the unit's rotated x+y; otherwise 1. Likely decides whether the hovered tile is in front of
         * the unit.
         */
        undefined4 __cdecl SomeUnitAndViewportCheck(int unitID);

        /**
         * Map-editor drag tool for tiles with logic flag 0x100000: tracks drag start/end tiles. On release, if the
         * start tile has the flag, writes the start->end orientation (0xF -> 0) to WallGFXLayer and queues
         * GCT_SET_TERRAIN (x, y, 1, 0x100000, 0x20). Otherwise converts the orientation into a sprite index
         * (GMFirstPictureIndex[5] + 0x38C + dir*8, dir rotated for mapOrientation); while the button is held it
         * writes that into ConstructionGFXLayer of the start tile (if flagged) and clears buildingPlacementResult,
         * else sets it and draws the brush preview.
         */
        void __cdecl HandleWallTerrainMouseDrag();

        /**
         * Plays the advisor voice line (placement_warningN.wav) matching a building placement failure reason;
         * default "Can't place that there my lord" (placement_warning16.wav).
         */
        void __cdecl PlayPlacementWarning(BuildingFailReasonEnum failReason);

        /**
         * When the local player selects an own building, plays an advisor line: not enough gold for
         * engineer/tunneler guild; then (for the guilds or building types <= 0x27) work halted (sleeping), no
         * labour, needs 1 / 2+ more people, or "a peasant is on its way" when one of the first 4 assigned workers
         * is still a peasant (not for the oil smelter).
         */
        void __cdecl HandleBuildingSelectionSpeech(int buildingIndexUnk);

        /**
         * Maps the local player's popularity (stored x100) to a TEXT_PLAYER_DESC index: 2 for <= 0, 12 for >= 100,
         * otherwise tens+3 below 50 and tens+2 from 50.
         */
        int __cdecl getPopularityDescriptionTextIndex();

        /**
         * Maps the local player's fearFactorLevel to a status-overview description text index: < -4 -> 0xE, -4..-3
         * -> 0xF, -2..-1 -> 0x10, 0..2 -> 0x11, 3..4 -> 0x12, > 4 -> 0x13. NAME? getFearFactorDescriptionTextIndex.
         */
        undefined4 __cdecl getFearFactorDescriptionTextIndex();

        /**
         * Picks a status-overview advice text index for the local player by priority: no gold 0x1D, gold >= 1000
         * 0x20, blessed >= 80% 0x17, > 2 working inns 0x1B, blessed >= 40% 0x16, 2 inns 0x1A, gold >= 5000 0x1F
         * (dead code: already caught by the >= 1000 test, confirmed at 0x43E609/0x43E652), blessed >= 20% 0x15, 1
         * inn 0x19, gold < 500 0x1E, > 4 enemy units 0x24, then population 0 -> 0x22, 1-4 -> 0x23, > 4 -> 0x27.
         * NAME? not just gold-related (getOverviewAdviceTextIndex).
         */
        int __cdecl getPlayerTraitDescriptionTextIndex();

        /**
         * Clears g_playerUnitCountByType (80 ints) and counts the local player's active units (logicalState !=
         * ULS_INVISIBLE, i.e. slot in use) per unitType, starting at unit 1, skipping units whose byte at
         * owner+0x296 is set and unit types <= 0 or 0x43..0x45.
         */
        void __cdecl CountPlayerUnitsByType();

        /**
         * Chooses and sets the mouse cursor: 3 (wait) when waitCursorToggle; if no modal/help dialog is open: 1
         * when MouseState.cursorOverlayMode < 1000 or in the intro logos, 2/5 for the build-menu delete mapper (by
         * TileMapState.deleteBlockedByEnemy), 4 in the editor; then 6 for campaign missions 6-10 (in the historic
         * intro/outro/description/picture menus when not in an in-game menu, or in-game) or for skirmish/MP when
         * the local selectedLordType is 1; otherwise 0.
         */
        HCURSOR __cdecl SetCursorDependingOnProgramState();

        /**
         * Barracks recruit check for the local player and European unit type barrackUnitIdUnk (0x16..0x1C): gold
         * cost = TroopDefinedData.BarracksUnitCost[type-0x16] (0 when not solitary and skirmishTroopsCostGold ==
         * 0). Returns ERS_NOT_ALLOWED_TO_RECRUIT if euroRecruitable[type-0x16] is 0, ERS_UNABLE_BECAUSE_MAX_ARMY if
         * count_2 + armySize >= armySizeLimit, ERS_CAN_NOT_RECRUIT if gold is short or one of the 4 required goods
         * in UnitPropertiesDefinedData.EuroUnitResourceCosts[type-0x16] is missing (-1 = horse); otherwise
         * ERS_CAN_RECRUIT when availablePeasantsOrHousedPeasants > count, else ERS_CAN_RECRUIT + 3.
         */
        EuroRecruitableState __cdecl GetEuroUnitRecruitState(int barrackUnitIdUnk);

        /**
         * Mercenary recruit check for Arabian unit type mercUnitType (0x46..0x4C): returns 2 if the mercRecruitable
         * flag for the type is 0 (decompiled as a cast off mapAndTime.playerHasWon), 3 if
         * peasantsBeingRecruitedAsTroops + armySize >= armySizeLimit, 0 if gold is below unitRecruitGoldCost, 1 if
         * availablePeasantsOrHousedPeasants > peasantsArrivingAtCampfire, otherwise 4 (no free peasant).
         */
        int __cdecl GetUnitRecruitPermission(int mercUnitType);

        /**
         * Returns whether the local player's gold covers the cost for unit type 0x1E (engineer, 30), 0x1D
         * (ladderman, 4) or 0x25 (monk, 10); 0 cost (always TRUE) for any other value.
         */
        BOOLEnum __cdecl HasEnoughGold(int unitType);

        /**
         * Sets DAT_EnoughGoldForRequestedUnit = local player gold >= 4 (ladderman cost).
         */
        void __cdecl CheckIfEnoughGoldForLadderman();

        /**
         * Sets DAT_EnoughGoldForRequestedUnit = local player gold >= 10 (monk cost).
         */
        void __cdecl CheckIfEnoughGoldForMonk();

        /**
         * Returns whether the local player has enough gold for the tunneler portrait: cost 30 when the argument is
         * 5, otherwise 0 (always TRUE).
         */
        BOOLEnum __cdecl CheckGoldResource(int portraitIndex);

        /**
         * Sets DAT_EnoughGoldForRequestedUnit = local player gold >= 30 (tunneler cost).
         */
        void __cdecl CheckIfEnoughGoldForTunneler();

        /**
         * Sets DAT_EnoughGoldForRequestedUnit to TRUE.
         */
        void __cdecl SetEnoughGoldForRequestedUnitToTrue();

        /**
         * Sets g_mercPostPortraitsEnabled to 1.
         */
        void __cdecl EnableMercPostPortraits();

        /**
         * 60 fps frame limiter: busy-waits until g_frameIntervalTicks (performance frequency/60 set by the init at
         * 0x46CF10, or 16 ms with the timeGetTime fallback) has elapsed since TIME_PreviousQuery, stores the new
         * time, then sets FLOAT_Between1and0dot2 = margin/elapsed (forced to 1.0 above 0.95, minimum 0.2) and
         * frameTimeScale to its inverse. Always returns 1. NAME? WaitFrameAndComputeTimeScale.
         */
        undefined4 __cdecl TicksSinceCounterStart();

        /**
         * Load dialog preview: when the selected list entry (selection index + offset) changes, copies its map
         * name, appends .tmp (create-siege view, FRT_MAPS), .map (custom scenarios, FRT_MAPS), .sav (single-player)
         * or .msv (multiplayer), resolves the path and reads only the map header for the preview.
         * local_3f4/local_3f0 are one 1008-byte name buffer; stack0xfffffc0b is fileName-1 used for the strlen
         * scan.
         */
        void __cdecl LoadSelectedMapHeaderForPreview();

        /**
         * Opens the save progress dialog for an executed multiplayer GCT_SAVE: sets DAT_MenuOptionsActionParameter
         * to 0x2E if isAutoSave (title TEXT_GAME_OPTIONS 0x2E 'Auto-Saving') else 0x20 ('Saving'), opens the
         * MMT_PROGRESS_BAR_BOX modal (also forcing activeModalDialogID) and immediately runs
         * LoadAndSaveGameButtonLogic, which treats 0x20 and 0x2E identically (writes the .msv). isAutoSave =
         * GCT_SAVE param2: 1 from the autosave timer, 0 from the manual save menu/dialog.
         */
        void __cdecl ShowProgressBarSaveLoadDialog(int isAutoSave);

        /**
         * Fills DAT_AllyMenuSelectionArray[1..6] with occupied (human or AI) player slots 1..8 other than the
         * local player that are on a different team and whose lord is alive (or at most 400 ticks have passed since
         * section1127, i.e. game start), and sets DAT_EnemyArrayIndex to the count (stops at 6).
         */
        void __cdecl BuildEnemyPlayerList();

        /**
         * Clears DAT_LobbyAddAICurrentlyHoveredAI.
         */
        void __cdecl ClearLobbyHoveredAI();

        /**
         * Plays the AI lord voice clip [messageIndex][aiType] from the MissionAestheticsDefinedData file-name table
         * (aiType < 17, messageIndex 1..33).
         */
        void __cdecl PlayAMessageFromAI(uint aiType, int messageIndex);

        /**
         * Wrapper: calls MapPropertiesState::sumUnitPoints.
         */
        void __cdecl SumUnitPoints();

        /**
         * Copies DAT_CopyOfScenarioGold back into mapAndTime.scenarioGold (as short).
         */
        void __cdecl RestoreScenarioGold();

        /**
         * Stores timeGetTime() in DAT_LastSliderChangeTime.
         */
        void __cdecl CaptureCurrentTimeToLastSliderChangeTime();

        /**
         * Starts a tutorial box transition: records the start time and the transition type; the counter starts at
         * 31 for type 1 (fade in) and at 1 otherwise (type 2 = fade out, after which UpdateTutorialStepAndProgress
         * advances the step).
         */
        void __cdecl InitTutorialStepTransition(int transitionType);

        /**
         * Returns DAT_TutorialCurrentStep.
         */
        undefined4 __cdecl GetCurrentTutorialStep();

        /**
         * Records a tutorial player action: 1 sets INT_00df5574, 2 increments TUT_RotateMapHappened, 3 increments
         * INT_00df557c, 4 sets INT_00df5580 = 1, 5 advances it 1 -> 2, 0x11 increments INT_00df5584. These are
         * tested by the per-step completion checks.
         */
        void __cdecl RecordTutorialPlayerAction(int actionId);

        /**
         * Records the last tutorial-relevant action type and building type, except that action 0xB does not
         * overwrite a pending action 7.
         */
        void __cdecl SetTutorialBuildingActionState(int actionType, BuildingType buildingType);

        /**
         * Zeroes all tutorial action trackers (action flags/counters, last action type/building, action counter) at
         * the start of a tutorial step.
         */
        void __cdecl ResetTutorialActionTrackers();

        /**
         * Sets g_tutorialHintActive and stores timeGetTime() in DWORD_00df5568; the tutorial update clears the hint
         * after 1000 ms.
         */
        void __cdecl SetTutorialHintActiveWithTimestamp();

        /**
         * Per-frame tutorial driver: keeps the tutorial box modal open (with Leave button on step 0x1F), plays each
         * sub-step's speech 1 s after the sub-step starts, and on a non-last sub-step whose speech has finished (no
         * speech stream playing, sound enabled) calls MenuItemActionHandler_TutorialBox_Main(1). Runs the fade-
         * in/fade-out transition in 32 ms units (fade-in end plays the step speech; fade-out end advances
         * DAT_TutorialCurrentStep, resets trackers and sub-step state), evaluates the current step's completion
         * condition from recorded actions/menu state, plays a rotating completion clip (index 0x24..0x27) when the
         * condition first becomes true (if the step's tutorialStepSpeechMode entry is 2) and calls
         * TutorialBox_Main(1) on the last sub-step when tutorialStepAutoContinue is set.
         */
        void __cdecl UpdateTutorialStepAndProgress();

        /**
         * Loads gfx8\campaign_map_england_hotspots.bmp (must be 800x600, top-down or bottom-up; 8 bits per pixel
         * assumed, not checked) into the gfx buffer and converts each of the 600 rows into up to 12 runs in
         * g_campaignHotspotRows: a run starts at a pixel of region colour 0x15..0x28 and continues over pixels of
         * that colour or of marker colours 1..0x14 until a 0 pixel, a different region colour (that pixel is
         * skipped, it does not start a new run) or x = 800; it stores start x, length (= run pixels + 1) and region
         * id 0x28 - colour. Marker pixels (colour 1..0x14, never 0) inside a run store their x/row in
         * g_campaignMapMarkerPos[colour-1] (20 XYPairs at 0xED26D8, all reset to 64,64 first); the decompiler shows
         * this as (&g_textPageStartTime)[colour*2] / (&g_scenarioDescNeedsSecondPage)[colour*2] because 0xED26D0 +
         * colour*8 = 0xED26D8 + (colour-1)*8, but those two globals are never written here. Also sets INT_00ed3110
         * = 1. heightOrPos holds the image height, then a file offset, then the run count of the current row; DVar3
         * is the scan x; dstOffsetOrRunCount is only the destination offset of the bottom-up copy.
         */
        void __cdecl ParseCampaignMapHotspotBitmap();

        /**
         * Zeroes the four 40-entry scenario-condition arrays (subType 0xEB1238, enabled 0xED2630, value 0xED2FC8,
         * isTrue 0xED3070) and sets INT_00ec02e8 if any kind-3 event of type 1/0x1B has its flag byte set. Then
         * selects the first kind-3 event of type 0/0x1A; if GameCore.briefingOpenedFromInGame==1 it advances to the last later
         * such event dated (year, month) not after the current game date, stopping at the first future-dated one.
         * Copies that event's 40 conditions into the arrays, scaling values of conditions 1,4,5,6,7,17 by
         * difficulty; if no such event exists the arrays stay zero. NAME? loads the current scenario event's
         * conditions rather than resetting a status.
         */
        void __cdecl LoadCurrentScenarioEventConditions();

        /**
         * Copies the given map name into a local buffer, appends '.map', resolves it inside the maps resource
         * folder (FRT_MAPS) and reads only the map header via FilePackager::readMapHeader(TRUE); then sets
         * INT_00eb9ae8 = 1 (likely a 'header loaded' flag).
         */
        void __cdecl ReadMapHeaderFromFile(char* mapName);

        /**
         * Per-frame countdown: while the tactical-powers help text is shown, decrements
         * MissionDefinedData.tacticalPowersHelpTextTimer and hides the help text when it reaches 0. NAME? it is a help-text
         * timer tick, nothing is 'filled'.
         */
        void __cdecl TacticalPowersFill();

        /**
         * Fills the whole screen with a solid colour: draws a color box from (0,0) to (width-1,height-1) for the
         * current game resolution.
         */
        void __cdecl ColorEntireScreen(ushort color);

        /**
         * Appends a copy of a string to the global menu string array (1024-byte slots) if fewer than 33 strings are
         * stored and the text is shorter than 1024 chars; increments DAT_NumberOfStoredMenuStrings.
         */
        void __cdecl StoreStringInMenuStringArray(char* textToStore);

        /**
         * Opens a scores file and reads the 10 int scores following the 4-byte version header into
         * DAT_MissionScores.
         */
        void __cdecl LoadScoresFileToMemory(char* filename);

        /**
         * Loads logo1.tgx (gfx 0) and logo2.tgx (gfx 1, not referenced by this script) and builds a credits-engine
         * script: segment start (0x1F), background mode 1 = full-screen gfx 0, opcode 0x20, fade in from black
         * (0x12), wait for the fade (0x14), wait 60 ticks (opcode 1), fade to black (0x13), wait for the fade,
         * opcode 0x1C, then opcode 8 (remove image element 0). No music is started - the SND_STR_MUSIC arguments
         * are just the value 0 shown with a wrong enum type. Both parameters (mission number, section1066 from the
         * caller) are unused.
         */
        void __cdecl BuildIntroLogoSequence(undefined4 unusedMissionNumber, undefined4 unusedSection1066);

        /**
         * Loads the history-book graphics (sand.tgx, pc0-pc7.tgx) and initialises 48 four-int sprite entries at
         * 0xEB0B28 with random fixed-point X (0..899)<<8, Y (0..599)<<8, image index 0..7 and speed 10..19. The
         * returned int is leftover EAX (last rand()/10 from the idiv), callers should ignore it.
         */
        int __cdecl PrepareHistoryBook();

        /**
         * Sets up the stored-text frame globals (string index, x, y, width, colour, font size, string length as
         * float, 100.0 scale, g_textRevealLineCount=1, DAT_ScrollingTextFrameDone=0) for a stored menu string and word-wraps/trims it to
         * the allowed width via TextManager::trimText.
         */
        void __cdecl TrimStoredMenuString(int storedMenuStringIndex, undefined4 param_2, undefined4 param_3,
            int allowedWidth, undefined4 param_5, int fontSize);

        /**
         * Hit-tests the mouse (minus main-menu border) against the rectangles of the credits-engine elements in
         * CreditsRelatedStructure_ARRAY_00ec0348 whose state is 1 or 3; returns the hit entry's id (xSpace field)
         * or -1. NAME? its only caller is the unused Extreme ad screen, so 'CampaignMap' is doubtful.
         */
        undefined4 __cdecl FindCampaignMapHotspotAtMouse();

        /**
         * Builds the (unused) Extreme demo/advert screen: loads its tgx images, stores the five TEXT_EXTREME_DEMO
         * bullet strings (offsets 8..12) in the menu string array, and appends the credits-engine commands that
         * show images, bullet texts and sounds.
         */
        void __cdecl BuildExtremeDemoIntroScript();

        /**
         * High-score table update. Clears DAT_MissionScores, then reads the scores file (int version 1 + 10
         * descending scores). If missing/invalid: writes a new file (version, max(newScore,0), 9 zeros), rank 0 if
         * newScore>=0, previous best 0, reloads scores. Otherwise INT_00ec0828 = previous best; if newScore beats
         * none of the 10 entries it returns at once (DAT_MissionScores stays zeroed, rank -1); else inserts it at
         * its rank, shifting lower ones down, sets INT_00ed2790 = rank, rewrites the file and reloads
         * DAT_MissionScores.
         */
        void __cdecl WriteMissionToScoresFile(char* scoresFileName, int newScore);

        /**
         * Every 10 s while an in-game screen is active in a multiplayer game (not GM_SOLITARY) and no message is
         * being received: plays one-time joke Bink messages from AI lords to the local player. On Christmas day
         * (Dec 25) the highest present AI type among 4..1 speaks; other AI types speak after given play times (now
         * - TIME_ActivePlayStartAdjusted), some only at an exact local hour (0:00-5:00) and some only if that AI is the greatest
         * lord.
         */
        void __cdecl PlayJokeVideoBasedOnCurrentTimeAndPlayTime();

    } // namespace Helpers
} // namespace UI
} // namespace OpenSHC
