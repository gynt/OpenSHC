/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/GameCore.hpp'
*/

#pragma once

#include "OpenSHC/Game/GameMode2Int.hpp"
#include "OpenSHC/Game/ScenarioProgress.hpp"
#include "OpenSHC/Game/TrailTypeInt.hpp"
#include "OpenSHC/Map/MapLockStateInt.hpp"
#include "OpenSHC/Map/Navigation/Algorithms/XYPair.hpp"
#include "OpenSHC/Rendering/Enums/DirectDrawStatusInt.hpp"
#include "OpenSHC/UI/ActiveMenuTab.hpp"
#include "OpenSHC/UI/Enums/BuildMenuTabTypeShort.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/UI/Enums/MenuViewTypeInt.hpp"
#include "OpenSHC/UI/MenuItemActionHandler.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "WinDef.h"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::GameMode2Int;
    using OpenSHC::Game::ScenarioProgress;
    using OpenSHC::Game::TrailTypeInt;
    using OpenSHC::Map::MapLockStateInt;
    using OpenSHC::Map::Navigation::Algorithms::XYPair;
    using OpenSHC::Rendering::Enums::DirectDrawStatusInt;
    using OpenSHC::UI::ActiveMenuTab;
    using OpenSHC::UI::MenuItemActionHandler;
    using OpenSHC::UI::Enums::BuildMenuTabTypeShort;
    using OpenSHC::UI::Enums::MenuViewType;
    using OpenSHC::UI::Enums::MenuViewTypeInt;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x00002380
    class GameCore {
    public:
        DirectDrawStatusInt directDrawStatus; // 0x00000000 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        int menuSwitchDelay; // 0x00000004 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        dword menuRenderMoment; // 0x00000008 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        MenuViewTypeInt currentMenuViewType; // 0x0000000C length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        ActiveMenuTab activeMenuTab; // 0x00000010 length: 4
        dword unknownAlwaysZero01; // 0x00000014 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        MenuViewTypeInt menuViewToSwitchTo; // 0x00000018 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        ActiveMenuTab menuTabToSwitchTo; // 0x0000001C length: 4
        dword field8_0x20; // 0x00000020 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        ActiveMenuTab buildmenuMenuTabToSwitchTo; // 0x00000024 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        dword buildingandstatusmenuMenuTabToSwitchTo; // 0x00000028 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        dword landscapingmenuMenuTabToSwitchTo; // 0x0000002C length: 4
        // build-menu tab requested by a toolbar button (MenuItemActionHandler_General_Unknown2); copied to
        // buildmenuMenuTabToSwitchTo when it differs from the active tab
        dword toolbarRequestedBuildTab; // 0x00000030 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        ActiveMenuTab secondaryActiveMenuTabToSwitchTo; // 0x00000034 length: 4
        // saves the build-menu tab before switching to soldier tab 61; restored when selection cleared (review 312
        // cross-checked restore sites)
        BuildMenuTabTypeShort buildMenuTabBeforeSoldiers; // 0x00000038 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        dword historicCampaignNumber; // 0x0000003C length: 4
        // [201 0x0042C620] set to 0x1C (28) here, outside the 1..20 range in the name Unsigned Double-Word (ddw,
        // 4-bytes)
        int missionNumber; // 0x00000040 length: 4
        ScenarioProgress scenarioProgress; // 0x00000044 length: 16
        // Unsigned Double-Word (ddw, 4-bytes)
        dword furthestMission; // 0x00000054 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        dword unlockAllHistoricalCampaigns; // 0x00000058 length: 4
        dword unused1; // 0x0000005C length: 4
        dword section1066; // 0x00000060 length: 4
        // 1 when the scenario description/briefing was opened from the in-game menu (Resume Game label, return to
        // build menu, battle music kept); 0 when entered from campaign/main menus
        dword briefingOpenedFromInGame; // 0x00000064 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        GameMode2Int gameMode_2; // 0x00000068 length: 4
        // 1 while play-testing a map launched from the map editor properties (gameMode BUILDER); disables
        // save/load, on quit reloads map and returns to MVT_MAP_EDITOR_PROPERTIES
        int isTestPlayingEditorMap; // 0x0000006C length: 4
        dword specialMultiplayerState; // 0x00000070 length: 4
        // 1 when a mission was chosen from the historic mission select screen; prevents mission progress increment
        dword isReplayingSelectedMission; // 0x00000074 length: 4
        int mapU4Int1; // 0x00000078 length: 4
        int mapU4Int1_2; // 0x0000007C length: 4
        // next 'view to keeps' target: 0 = own keep, n = n-th valid (>= 0) tile of mapAndTime.field22_0x58;
        // incremented per jump and wrapped at the number of targets, reset on map load (distinct from the scroll-
        // gesture counter g_viewToKeepsCycleIndex)
        dword viewToKeepsTargetIndex; // 0x00000080 length: 4
        int battleLevel; // 0x00000084 length: 4
        // same field (+0x88) decided in decided_0 as battleLevelAccumulator; damage*10 accumulator copied to
        // battleLevel every 200 ticks (machine-checked 0x516CB6) [076 0x00407190] increased by 500 each time a
        // flying cow lands and spawns poison clouds
        dword battleLevelAccumulator; // 0x00000088 length: 4
        int someSoundMatchTime_1; // 0x0000008C length: 4
        // times the jester's status panel was opened (BuildingAndStatusMenu prepare, BASMTT_PEASANT with
        // UT_JESTER), capped at 3; reset in mapLoadingAndLaunchGameRelated1; no reader seen
        dword jesterClickCount; // 0x00000090 length: 4
        int battleLevel2; // 0x00000094 length: 4
        dword mapTimeInTicks; // 0x00000098 length: 4
        // written as 1 with mapTimeInTicks = 1 at map start; only read as baseline (mapTimeInTicks - it > 200/400)
        dword mapStartTick; // 0x0000009C length: 4
        // mapTimeInTicks snapshot taken when a map/sav file is read
        dword mapTimeAtLoad; // 0x000000A0 length: 4
        // [UNK PASS] was currentlyInGameUnk_0xa4
        BOOLEnum inGameViewActive_0xa4; // 0x000000A4 length: 4
        dword gameSpeedMultiplicator; // 0x000000A8 length: 4
        dword performedGameTicksThisLoop; // 0x000000AC length: 4
        dword gameTicksThisLoop; // 0x000000B0 length: 4
        dword gameTicksLastLoop; // 0x000000B4 length: 4
        dword averageTimePerGameTick; // 0x000000B8 length: 4
        dword timeBeforeRunningGameTicksThisLoop; // 0x000000BC length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        int countdown; // 0x000000C0 length: 4
        int uniqueGameObjectTracker; // 0x000000C4 length: 4
        dword gameSpeedLevel; // 0x000000C8 length: 4
        dword settingBubbleHelp; // 0x000000CC length: 4
        BOOLEnum isTimeHalted; // 0x000000D0 length: 4
        // [081 0x004C31A0] Event types 0x18/0x19 set it 0/1; when non-zero the invasion announcement videos, siege-
        // tab switch and sands-of-time warnings are skipped.
        dword suppressInvasionWarnings; // 0x000000D4 length: 4
        dword isTimeHalted2; // 0x000000D8 length: 4
        // initialised to 1 in GameCore constructor; no other observed use
        dword ctorDefaultOne_0xdc; // 0x000000DC length: 4
        int missionDifficulty; // 0x000000E0 length: 4
        int missionDifficulty2; // 0x000000E4 length: 4
        int missionDifficulty_2; // 0x000000E8 length: 4
        int missionDifficulty_3; // 0x000000EC length: 4
        int missionDifficulty_1; // 0x000000F0 length: 4
        int missionDifficulty_0; // 0x000000F4 length: 4
        // initialised to 0 in GameCore constructor; no other observed use
        dword ctorDefaultZero_0xf8; // 0x000000F8 length: 4
        BOOLEnum solitaryAllBuildingsAreFree; // 0x000000FC length: 4
        // market sub-menu tab chosen via MarketMenuChangeButtons (mirror of buildingandstatusmenuMenuTabToSwitchTo)
        int lastMarketMenuTab; // 0x00000100 length: 4
        // initialised to 1 in GameCore constructor next to option flags; no other observed use
        dword ctorDefaultOne_0x104; // 0x00000104 length: 4
        // default 1; when 0 the floating 'building needs workers' overlay above buildings is not rendered
        dword showNeedsWorkersOverlay; // 0x00000108 length: 4
        // When non-zero the game ends immediately with the local player as winner; cleared afterwards; not always
        // zero.
        dword forceLocalPlayerVictory; // 0x0000010C length: 4
        dword unknownAlwaysZero02; // 0x00000110 length: 4
        // [227 0x0042E900] when non-zero, description button shows text 0x20 and 0x42EDF0 does not open the editor;
        // only two reads (0x42E97E, 0x42EE18), no direct writer found, so whether it is ever non-zero is unproven
        int mapDescriptionLocked; // 0x00000114 length: 4
        // [242 0x00440560] set TRUE when the stored player name is non-empty (prompt skipped), FALSE before opening
        // the enter-title dialog; other menu code skips name editing when TRUE
        BOOLEnum playerNameAlreadySet; // 0x00000118 length: 4
        // [242 0x00440560] timeGetTime() stored when the prompt is skipped; only read by the dead 1000 ms check in
        // the enter-name frame handler
        DWORD nameGreetingStartTime; // 0x0000011C length: 4
        byte unused_0x120[8]; // 0x00000120 length: 8
        int scribeAnimationFrameCopy; // 0x00000128 length: 4
        // 0 = none, 1..3 select scribe animation table; set only when 0 by TriggerScribeReaction, reset when
        // sequence ends. Not a tax setting.
        int scribeReactionType; // 0x0000012C length: 4
        // [221 0x00433370] 0 = moving to frame 6, 1 = playing sequence via scribeAnimationFrame2, 2 = returning to
        // popularity frame; tested against TRUE and 2
        BOOLEnum scribeAnimationPhase; // 0x00000130 length: 4
        int scribeAnimationFrame; // 0x00000134 length: 4
        int scribeAnimationFrame2; // 0x00000138 length: 4
        // [221 0x00433370] timeGetTime() throttle: animation steps at most every 60 ms
        int scribeAnimLastTickMs; // 0x0000013C length: 4
        byte unused_0x140[4]; // 0x00000140 length: 4
        // page of the popularity status report (0/1), toggled by the switch button, reset if >= page count
        int popularityReportPage; // 0x00000144 length: 4
        // 1 or 2 pages depending on the number of active popularity factors (>2 => 2)
        int popularityReportPageCount; // 0x00000148 length: 4
        dword isBinkVideoPlaying; // 0x0000014C length: 4
        dword section1095; // 0x00000150 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        dword newPlayerID; // 0x00000154 length: 4
        // [UNK PASS] was hasMenuRenderedUnk
        dword menuFadeInProgress; // 0x00000158 length: 4
        // set 1 when a camera gesture (lowered view, rotation, zoom toggle, flat view) is performed while right-
        // button input is handled; while set, releasing the right button does not cancel the moat-digging mapper;
        // reset to 0 on the next right-click start
        dword cameraGestureDuringRightClick; // 0x0000015C length: 4
        // Triggers UI element visibility
        int xbowProducible_logic; // 0x00000160 length: 4
        // Triggers UI element visibility
        int pikeProducible_logic; // 0x00000164 length: 4
        // Triggers UI element visibility
        int swordProducible_logic; // 0x00000168 length: 4
        // Triggers UI element visibility
        int bowProducible_logic; // 0x0000016C length: 4
        // Triggers UI element visibility
        int spearProducible_logic; // 0x00000170 length: 4
        // Triggers UI element visibility
        int maceProducible_logic; // 0x00000174 length: 4
        byte unused_0x178[2024]; // 0x00000178 length: 2024
        BOOLEnum cheatModeFlag; // 0x00000960 length: 4
        BOOLEnum solitaryAltUDungeon; // 0x00000964 length: 4
        dword descriptionUseStringTable; // 0x00000968 length: 4
        dword descriptionStringTableIndex; // 0x0000096C length: 4
        char temporaryTextBufferOfSize1000[1000]; // 0x00000970 length: 1000
        char standaloneFilename[1001]; // 0x00000D58 length: 1001
        byte unused_0x1141[1003]; // 0x00001141 length: 1003
        // [217 0x004AC040] 'King of the Hill' button (0xc) is drawn pressed only for multiplayer maps when
        // mapU4Int0 != 0
        int isKingOfTheHill; // 0x0000152C length: 4
        int mapU4Int0_2; // 0x00001530 length: 4
        dword U2_mapType_singleOrMulti; // 0x00001534 length: 4
        // [234 0x0042FEC0] five dword flags toggled by keep buttons -1..-5 (0x1fe9248..0x1fe9258 in machine code);
        // continue requires at least one set
        dword availableKeepFlags[5]; // 0x00001538 length: 20
        int mapU2PlayersCount; // 0x0000154C length: 4
        int mapU4Int3_balanced; // 0x00001550 length: 4
        int mapDescUseStringTable; // 0x00001554 length: 4
        int mapDescUseStringTableIndex; // 0x00001558 length: 4
        char mapDescription[1000]; // 0x0000155C length: 1000
        byte unused_0x1944[1004]; // 0x00001944 length: 1004
        int mapType; // 0x00001D30 length: 4
        int sh1MapKeeps[5]; // 0x00001D34 length: 20
        int mapPlayerCount; // 0x00001D48 length: 4
        XYPair keepPositions[8]; // 0x00001D4C length: 64
        int savedMapBalance; // 0x00001D8C length: 4
        MapLockStateInt U3_mapLockedState; // 0x00001D90 length: 4
        MapLockStateInt savedMapLocked; // 0x00001D94 length: 4
        // Checked: set 1 on new map creation and on map load, 0 on entering editor; gates editing buttons. Not 'new
        // map'. 1 when the map editor was entered to create/edit a map (new map size chosen, keeps chosen), 0 when
        // coming from custom scenarios; gates editable fields in MapEditorProperties
        dword editorMapLoaded; // 0x00001D98 length: 4
        int mapU3EndInt; // 0x00001D9C length: 4
        int savedMapEndInt2; // 0x00001DA0 length: 4
        int canBeginMainLoop; // 0x00001DA4 length: 4
        int twohundred; // 0x00001DA8 length: 4
        byte unused_0x1dac[4]; // 0x00001DAC length: 4
        // Unsigned Double-Word (ddw, 4-bytes) [UNK PASS] was menuType7_MenuItemClickHandlerUnk
        MenuItemActionHandler* onViewOrTabSwitchHandler; // 0x00001DB0 length: 4
        // [032 0x004ECAD0] set to numberOfAIsWithAIV, the length of arrayOfLordIdsWithAIVsUnk
        int numAILordsWithAIV; // 0x00001DB4 length: 4
        // [032 0x004ECAD0] filled with (aiIndex+1) for each AI that has at least one AIV file
        int aiLordIDsWithAIV[16]; // 0x00001DB8 length: 64
        int furthestSkirmishTrailMission; // 0x00001DF8 length: 4
        int skirmishTrailMonthsTakenOrChicken[50]; // 0x00001DFC length: 200
        // Unsigned Double-Word (ddw, 4-bytes)
        int skirmishTrailStartDateInMonths[50]; // 0x00001EC4 length: 200
        // [040 0x0046BD50] initialized to 13200 (1100*12) and accumulates month counts Unsigned Double-Word (ddw,
        // 4-bytes)
        dword skirmishTrailCurrentDateInMonths; // 0x00001F8C length: 4
        dword skirmishTrailStartDateMonths; // 0x00001F90 length: 4
        BOOLEnum isSkirmishTrail; // 0x00001F94 length: 4
        dword skirmishTrailProgress; // 0x00001F98 length: 4
        TrailTypeInt currentTrailType; // 0x00001F9C length: 4
        int furthestWarchestTrailMission; // 0x00001FA0 length: 4
        int warchestTrailMonthsTakenOrChicken[50]; // 0x00001FA4 length: 200
        int warchestTrailStartDatesInMonths[50]; // 0x0000206C length: 200
        // [040 0x0046BD50] initialized to 13560 (1130*12) and accumulates month counts Unsigned Double-Word (ddw,
        // 4-bytes)
        dword warchestTrailCurrentDateInMonths; // 0x00002134 length: 4
        dword warchestTrailStartDateMonths; // 0x00002138 length: 4
        dword field137_0x213c; // 0x0000213C length: 4
        dword warchestTrailProgress; // 0x00002140 length: 4
        int furthestExtremeTrailMission; // 0x00002144 length: 4
        int extremeTrailMonthsTakenOrChicken[50]; // 0x00002148 length: 200
        int extremeTrailStartDatesInMonths[50]; // 0x00002210 length: 200
        // [040 0x0046BD50] initialized to 13560 (1130*12) and accumulates month counts Unsigned Double-Word (ddw,
        // 4-bytes)
        dword extremeTrailCurrentDateInMonths; // 0x000022D8 length: 4
        dword extremeTrailStartDateMonths; // 0x000022DC length: 4
        dword field144_0x22e0; // 0x000022E0 length: 4
        int extremeTrailProgress; // 0x000022E4 length: 4
        // Local player's lord face index (2..0x15), saved in user config, sent as lordIcons[slot]
        int localLordIcon; // 0x000022E8 length: 4
        int lordIcons[9]; // 0x000022EC length: 36
        byte unused_0x2310[4]; // 0x00002310 length: 4
        // Local player's lord type (0 European, else Arabian), saved in config, sent as selectedLordTypes[slot]
        int localSelectedLordType; // 0x00002314 length: 4
        // [UNK PASS] was selectedLordType_2Unk
        int singlePlayerMapLordType; // 0x00002318 length: 4
        int selectedLordTypes[9]; // 0x0000231C length: 36
        // skirmish lobby value saved/restored with SkirmishLobbySetupStructure.mbr_0xf0
        dword skirmishLobbySettingF0; // 0x00002340 length: 4
        dword gamePausedLogical; // 0x00002344 length: 4
        int viewportFocusBeforeBarracksHotkey; // 0x00002348 length: 4
        int viewportFocusBeforeMercenaryHotkey; // 0x0000234C length: 4
        int viewportFocusBeforeGranaryHotkey; // 0x00002350 length: 4
        int viewportFocusBeforeMarketHotkey; // 0x00002354 length: 4
        int viewportFocusBeforeKeepHotkey; // 0x00002358 length: 4
        int viewportFocusBeforeArmoryHotkey; // 0x0000235C length: 4
        int viewportFocusBeforeEngineersGuildHotkey; // 0x00002360 length: 4
        // viewport tile saved before the T hotkey jumps to the tunnelers guild; Shift+T returns to it, -1 = none
        int viewportFocusBeforeTunnelerHotkey; // 0x00002364 length: 4
        BOOLEnum genieVoiceActive; // 0x00002368 length: 4
        // checked decomp: set to timeGetTime() at start, += paused span on resume, gameDuration = now - it,
        // restored as now - gameDuration on load: pause-adjusted start time, not paused total
        uint gameStartTimeMs; // 0x0000236C length: 4
        dword gameDuration; // 0x00002370 length: 4
        byte tacticalPowersDisplayFlag; // 0x00002374 length: 1
        byte unusedOption1; // 0x00002375 length: 1
        // [UNK PASS] was isVictoryOrDefeatUnk
        byte pendingForcedVictory; // 0x00002376 length: 1
        byte skipStoreSKMasters; // 0x00002377 length: 1
        // [247 0x004B66C0] when set, units are drawn only in own-team / first-enemy colour; unowned units and
        // animals are skipped, so it does more than hide wildlife
        byte minimapAllyEnemyColorMode; // 0x00002378 length: 1
        byte unused_0x2379[3]; // 0x00002379 length: 3
        // Unsigned Double-Word (ddw, 4-bytes)
        dword forty; // 0x0000237C length: 4

    private:
        GameCore(GameCore const&);
        void operator=(GameCore const&);

    public:
        GameCore() {};
        ~GameCore() {};

        // Constructor
        /**
         * GameCore constructor: initializes DAT_GameCore fields to defaults (no menu view, speed 40, bubble help
         * on, campaign progress starts, furthest mission 0x21, hotkey viewport focus memories -1) and returns
         * &DAT_GameCore.
         */
        GameCore* Constructor_GameCore();

        /**
         * Sets DAT_GameCore.currentMenuViewType to 2 (called from the GameCore destructor on exit).
         */
        void setViewOnExitUnk();

        /**
         * Copies the remembered tab of the current menu view (build menu or map-editor landscaping) into
         * secondaryActiveMenuTabToSwitchTo.
         */
        void setTabToSwitchTo();

        /**
         * Restores buildmenuMenuTabToSwitchTo from secondaryActiveMenuTabToSwitchTo, except that a siege-tent
         * shield tab is replaced by the battering-ram tab.
         */
        void swapBuildMenuTab();

        /**
         * Schedules a switch to menu view menuID after delay ms (target, delay and timeGetTime stored in GameCore;
         * an invalid combined view ID is mapped to the main menu) and picks the tab to show:
         * landscaping/build/building-status remembered tabs. For the build menu it forces the stocks tab in certain
         * single-player modes or when display element 0x11 is set, otherwise forces the keep resp. granary
         * placement tab while singlePlayerHasKeepAndGranaryCheck reports no keep (0) / no granary (-1), starting
         * the build-menu slide transition when already in the build menu; other views stop both Bink players. When
         * the view actually changes it selects background music per target view (intro, tutorial, credits, campaign
         * intro/outro, narration, etc.).
         */
        void switchToMenuView(MenuViewType menuID, int delay);

        /**
         * Applies a pending menu view switch once its delay has elapsed: commits the selected building/unit; if
         * view and tab are unchanged it only re-triggers the view's initial/prepare handlers. Otherwise invokes and
         * clears the pending menuType7 click handler, sets currentMenuViewType/activeMenuTab (main menu from
         * skirmish switches the mode to solitary), resets viewport, mouse cursor, menu position and bottom-left
         * text, and flags the view for initial/prepare. Also handles a pending newPlayerID: makes that slot the
         * local player (transferring ownership from the current slot if Shift is held).
         */
        void processMenuViewSwitch();

        /**
         * Decrements DAT_GameCore.countdown while positive; if the viewport state is 0 and no scrolling is in
         * progress resets countdown to 1 and forty to 0.
         */
        void viewportAndScrollingRelated();

        /**
         * Returns TRUE if the current menu view is an in-game view (map editor landscaping, build menu, or
         * building/status menu), else FALSE.
         */
        BOOLEnum isInGameView();

        /**
         * Returns TRUE if in the building/status menu with one of the granary, siege tent (catapult, fire ballista,
         * trebuchet, siege tower, battering ram, shield) or keep tabs active.
         */
        BOOLEnum isInBuildingTab();

        /**
         * Sets mapAndTime jester/lady availability flags by campaign mission number (jester from mission 7, lady
         * from mission 11); for earlier missions removes the current player's jester/lady unit (logicalState =
         * ULS_REMOVE) if its stored uid still matches and clears the references.
         */
        void removeJesterAndLadyUnitsInCertainMissions();

        /**
         * Clears mapAndTime jester/lady flags and removes the current player's lady and jester units (logicalState
         * = ULS_REMOVE) when their stored uid still matches, clearing the references.
         */
        void removeLadyAndJester();

        /**
         * In single-player modes (solitary, skirmish single player) returns TRUE if a modal dialog or the in-game
         * help text is open (game should halt); always FALSE in multiplayer.
         */
        BOOLEnum isGameHaltingMenuOpen();

        /**
         * Recomputes campaign trail mission start dates (in months): for trail 1 (skirmish, 50 missions, start 1100
         * AD), 2 (warchest, 30, 1130 AD), 3 (extreme, 20, 1130 AD) or all when 0, walks the months-taken array
         * (-1200 = skipped/chicken adds 100 years, other negative = unplayed stops) writing each mission's start
         * date and the first unplayed mission's start date. NAME? better recomputeTrailStartDates.
         */
        void recomputeTrailMissionStartDates(int trailType);

        /**
         * Advances to the next historical campaign mission: raises the matching campaign's progress (unless all
         * campaigns are unlocked or field26_0x74 is set), saves user config. If the mission number is valid it
         * removes early-mission jester/lady, sets player slot 1 and switches to the campaign intro when the mission
         * is the campaign's first (campaign*5-4); otherwise to the mission picture view only when field26_0x74 is
         * set. In all other cases (invalid mission, or field26_0x74 clear) it switches to the mission-finished
         * transition.
         */
        void incrementMissionProgress();

        /**
         * Removes early-mission jester/lady, switches to the scenario description menu view and clears
         * GameCore.briefingOpenedFromInGame.
         */
        void switchToScenarioDescriptionMenuView();

        /**
         * Advances the mission number, removes lady and jester, updates furthestMission, saves user config, and
         * switches to the scenario description view (valid mission that is 0x21 or field26_0x74 set) or the
         * mission-finished transition.
         */
        void incrementMission();

        /**
         * Removes lady and jester, clears GameCore.briefingOpenedFromInGame and switches to the scenario description menu view.
         */
        void exitToScenarioDescriptionMenu();

        /**
         * UI hide toggle hotkey: in build menu or landscaping (no selection box) toggles between the normal tab and
         * a hidden/minimized tab (siege tower / shield placeholder tabs, landscaping tab 0x3c/0xe7) and re-enters
         * the view; from the building/status menu switches to the build menu with the hidden tab.
         */
        void hideOrUnhideUI();
    };

    static_assert_cpp98_obj(sizeof(GameCore) == 9088, GameCore);

#pragma pack(pop)

} // namespace Game
} // namespace OpenSHC
