/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Global/Init.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Global {
    namespace Init {

        /**
         * Trivial no-op constructor: returns the object pointer passed in ECX unchanged. Shared by several global-
         * object static initializers whose classes have empty constructors.
         */
        void* __cdecl Constructor_Empty();

        /**
         * Static initializer: constructs the global MenuView_00b974bc (0xB974BC) with view type MVT_NO_VIEW via
         * Constructor_MenuView_Reduced, which sets only menuID (no callbacks) and pushes it onto the global
         * DAT_MenuViewStackTop linked list; registers Destructor_0059cd30 with atexit.
         */
        void __cdecl Constructor_MenuView_Reduced();

        /**
         * Static initializer: constructs global MenuView_IntroLogos for view type MVT_INTRO_LOGOS with callbacks
         * Prepare=MenuView_IntroLogos_Prepare, DoInitial=MenuView_IntroLogos_DoInitial,
         * DoEveryFrame=MenuView_IntroLogos_DoEveryFrame. Constructor_MenuView stores these in the object and pushes
         * it onto the global DAT_MenuViewStackTop linked list; Destructor_MenuView_IntroLogos is registered with
         * atexit.
         */
        void __cdecl Constructor_MenuView_IntroLogos();

        /**
         * Static initializer: constructs global MenuView_HistoricMissionSelect for view type
         * MVT_HISTORIC_MISSION_SELECT with callbacks Prepare=MenuView_HistoricMissionSelect_Prepare,
         * DoInitial=MenuView_General_DoInitial_DefaultMainMenuStructure,
         * DoEveryFrame=MenuView_MissionSelect_DoEveryFrame. Constructor_MenuView stores these in the object and
         * pushes it onto the global DAT_MenuViewStackTop linked list; Destructor_MenuView_HistoricMissionSelect is
         * registered with atexit.
         */
        void __cdecl Constructor_MenuView_HistoricMissionSelect();

        /**
         * Static initializer: constructs global MenuView_UnusedEconomicMissionSelect for view type
         * MVT_ECONOMIC_MISSION_SELECT with callbacks
         * Prepare=MenuView_UnusedEconomicMissionSelect_Prepare,
         * DoInitial=MenuView_General_DoInitial_DefaultMainMenuStructure,
         * DoEveryFrame=MenuView_MissionSelect_DoEveryFrame. Constructor_MenuView stores these in the object and
         * pushes it onto the global DAT_MenuViewStackTop linked list;
         * Destructor_MenuView_UnusedEconomicMissionSelect is registered with atexit.
         */
        void __cdecl Constructor_MenuView_UnusedEconomicMissionSelect();

        /**
         * Static initializer: constructs global MenuView_UnusedSomeMissionStartUnk for view type
         * MVT_UNUSED_SOME_MISSION_STARTUnk with callbacks Prepare=MenuView_UnusedSomeMissionStartUnk_Prepare,
         * DoInitial=MenuView_General_DoInitial_DefaultMainMenuStructure,
         * DoEveryFrame=MenuView_General_DoEveryFrame_FirstGfxCentered. Constructor_MenuView stores these in the
         * object and pushes it onto the global DAT_MenuViewStackTop linked list;
         * Destructor_MenuView_UnusedSomeMissionStartUnk is registered with atexit.
         */
        void __cdecl Constructor_MenuView_UnusedSomeMissionStartUnk();

        /**
         * Static initializer: constructs global MenuView_UnusedOldTitleMenu for view type MVT_UNUSED_OLD_TITLE_MENU
         * with callbacks Prepare=MenuView_UnusedOldTitleMenu_Prepare,
         * DoInitial=MenuView_UnusedOldTitleMenu_DoInitial, DoEveryFrame=DoNothing. Constructor_MenuView stores
         * these in the object and pushes it onto the global DAT_MenuViewStackTop linked list;
         * Destructor_MenuView_UnusedOldTitleMenu is registered with atexit.
         */
        void __cdecl Constructor_MenuView_UnusedOldTitleMenu();

        /**
         * Static initializer: constructs global MenuView_MpConnection for view type MVT_MP_CONNECTION with
         * callbacks Prepare=MenuView_MpConnection_Prepare,
         * DoInitial=MenuView_General_DoInitial_DefaultMainMenuStructure,
         * DoEveryFrame=MenuView_General_DoEveryFrame_FirstGfxCentered. Constructor_MenuView stores these in the
         * object and pushes it onto the global DAT_MenuViewStackTop linked list; Destructor_MenuView_MpConnection
         * is registered with atexit.
         */
        void __cdecl Constructor_MenuView_MpConnection();

        /**
         * Static initializer: constructs global MenuView_Unknown21 for view type MVT_UNKNOWN_21 with callbacks
         * Prepare=MainMenu_Unknown21_Prepare, DoInitial=MenuView_General_DoInitial_DefaultMainMenuStructure,
         * DoEveryFrame=MenuView_General_DoEveryFrame_FirstGfxCentered. Constructor_MenuView stores these in the
         * object and pushes it onto the global DAT_MenuViewStackTop linked list; Destructor_MenuView_Unknown21 is
         * registered with atexit.
         */
        void __cdecl Constructor_MenuView_Unknown21();

        /**
         * Static initializer: constructs global MenuView_LobbyMenu for view type MVT_LOBBY_MENU with callbacks
         * Prepare=MenuView_LobbyMenu_Prepare, DoInitial=MenuView_General_DoInitial_DefaultMainMenuStructure,
         * DoEveryFrame=MenuView_LobbyMenu_DoEveryFrame. Constructor_MenuView stores these in the object and pushes
         * it onto the global DAT_MenuViewStackTop linked list; Destructor_MenuView_LobbyMenu is registered with
         * atexit.
         */
        void __cdecl Constructor_MenuView_LobbyMenu();

        /**
         * Static initializer: constructs global MenuView_Unknown33 for view type MVT_UNKNOWN_33 with callbacks
         * Prepare=DoNothing, DoInitial=DoNothing, DoEveryFrame=MenuView_Unknown33_DoEveryFrame.
         * Constructor_MenuView stores these in the object and pushes it onto the global DAT_MenuViewStackTop linked
         * list; Destructor_MenuView_Unknown33 is registered with atexit.
         */
        void __cdecl Constructor_MenuView_MultiplayerWaitForPlayersReady();

        /**
         * Static initializer: constructs global MenuView_Unknown61ReturnToSkrimishMenuUnk for view type
         * MVT_RETURN_TO_SKIRMISH_LOBBY with callbacks
         * Prepare=MenuView_Unknown61ReturnToSkrimishMenuUnk_Prepare,
         * DoInitial=MenuView_Unknown61ReturnToSkrimishMenuUnk_DoInitial,
         * DoEveryFrame=MenuView_Unknown61ReturnToSkrimishMenuUnk_DoEveryFrame. Constructor_MenuView stores these in
         * the object and pushes it onto the global DAT_MenuViewStackTop linked list;
         * Destructor_MenuView_Unknown61ReturnToSkrimishMenuUnk is registered with atexit.
         */
        void __cdecl Constructor_MenuView_ReturnToSkirmishLobby();

        /**
         * Static initializer: constructs global MenuView_SingleplayerMapChoice for view type
         * MVT_SINGLEPLAYER_MAP_CHOICE with callbacks Prepare=MenuView_SingleplayerMapChoice_Prepare,
         * DoInitial=MenuView_General_DoInitial_DefaultMainMenuStructure,
         * DoEveryFrame=MenuView_SingleplayerMapChoice_DoEveryFrame. Constructor_MenuView stores these in the object
         * and pushes it onto the global DAT_MenuViewStackTop linked list; Destructor_MenuView_SingleplayerMapChoice
         * is registered with atexit.
         */
        void __cdecl Constructor_MenuView_SingleplayerMapChoice();

        /**
         * Static initializer: constructs global MenuView_Unknown49DoesNothingUnk for view type
         * MVT_RESTARTING_CUSTOM_MAP with callbacks Prepare=DoNothing, DoInitial=DoNothing,
         * DoEveryFrame=DoNothing. Constructor_MenuView stores these in the object and pushes it onto the global
         * DAT_MenuViewStackTop linked list; Destructor_MenuView_Unknown49DoesNothingUnk is registered with atexit.
         */
        void __cdecl Constructor_MenuView_RestartingCustomMap();

        /**
         * Static initializer: constructs global MenuView_MapEditorLandscaping for view type
         * MVT_MAP_EDITOR_LANDSCAPING with callbacks Prepare=MenuView_MapEditorLandscaping_Prepare,
         * DoInitial=MenuView_MapEditorLandscaping_DoInitial,
         * DoEveryFrame=MenuView_MapEditorLandscaping_DoEveryFrame. Constructor_MenuView stores these in the object
         * and pushes it onto the global DAT_MenuViewStackTop linked list; Destructor_MenuView_MapEditorLandscaping
         * is registered with atexit.
         */
        void __cdecl Constructor_MenuView_MapEditorLandscaping();

        /**
         * Static initializer: constructs global MenuView_BuildMenu for view type MVT_BUILD_MENU with callbacks
         * Prepare=MenuView_BuildMenu_Prepare, DoInitial=MenuView_BuildMenu_DoInitial,
         * DoEveryFrame=MenuView_BuildMenu_DoEveryFrame. Constructor_MenuView stores these in the object and pushes
         * it onto the global DAT_MenuViewStackTop linked list; Destructor_MenuView_BuildMenu is registered with
         * atexit.
         */
        void __cdecl Constructor_MenuView_BuildMenu();

        /**
         * Static initializer: constructs global MenuView_BuildingAndStatusMenu for view type
         * MVT_BUILDING_AND_STATUS_MENU with callbacks Prepare=MenuView_BuildingAndStatusMenu_Prepare,
         * DoInitial=MenuView_BuildingAndStatusMenu_DoInitial,
         * DoEveryFrame=MenuView_BuildingAndStatusMenu_DoEveryFrame. Constructor_MenuView stores these in the object
         * and pushes it onto the global DAT_MenuViewStackTop linked list; Destructor_MenuView_BuildingAndStatusMenu
         * is registered with atexit.
         */
        void __cdecl Constructor_MenuView_BuildingAndStatusMenu();

        /**
         * Static initializer: constructs global MenuView_UnusedHelpTextEditor for view type
         * MVT_UNUSED_HELP_TEXT_EDITOR with callbacks Prepare=MenuView_UnusedHelpTextEditor_Prepare,
         * DoInitial=MenuView_General_DoInitial_OnlySetMenuXY,
         * DoEveryFrame=MenuView_UnusedHelpTextEditor_DoEveryFrame. Constructor_MenuView stores these in the object
         * and pushes it onto the global DAT_MenuViewStackTop linked list; Destructor_MenuView_UnusedHelpTextEditor
         * is registered with atexit.
         */
        void __cdecl Constructor_MenuView_UnusedHelpTextEditor();

        /**
         * Static initializer: constructs global MenuView_MapEditorProperties for view type
         * MVT_MAP_EDITOR_PROPERTIES with callbacks Prepare=MenuView_MapEditorProperties_Prepare,
         * DoInitial=MenuView_General_DoInitial_DefaultMainMenuStructure,
         * DoEveryFrame=MenuView_MapEditorProperties_DoEveryFrame. Constructor_MenuView stores these in the object
         * and pushes it onto the global DAT_MenuViewStackTop linked list; Destructor_MenuView_MapEditorProperties
         * is registered with atexit.
         */
        void __cdecl Constructor_MenuView_MapEditorProperties();

        /**
         * Static initializer: constructs global MenuView_NewMapMaptype for view type MVT_NEW_MAP_MAPTYPE with
         * callbacks Prepare=MenuView_NewMapMaptype_Prepare,
         * DoInitial=MenuView_General_DoInitial_DefaultMainMenuStructure,
         * DoEveryFrame=MenuView_General_DoEveryFrame_FirstGfxCentered. Constructor_MenuView stores these in the
         * object and pushes it onto the global DAT_MenuViewStackTop linked list; Destructor_MenuView_NewMapMaptype
         * is registered with atexit.
         */
        void __cdecl Constructor_MenuView_NewMapMaptype();

        /**
         * Static initializer: constructs global MenuView_NewMapMapsize for view type MVT_NEW_MAP_MAPSIZE with
         * callbacks Prepare=MenuView_NewMapMapsize_Prepare,
         * DoInitial=MenuView_General_DoInitial_DefaultMainMenuStructure,
         * DoEveryFrame=MenuView_NewMapMapsize_DoEveryFrame. Constructor_MenuView stores these in the object and
         * pushes it onto the global DAT_MenuViewStackTop linked list; Destructor_MenuView_NewMapMapsize is
         * registered with atexit.
         */
        void __cdecl Constructor_MenuView_NewMapMapsize();

        /**
         * Static initializer: constructs global MenuView_UnusedChooseAvailableKeeps for view type
         * MVT_UNUSED_CHOOSE_AVAILABLE_KEEPS with callbacks Prepare=MenuView_UnusedChooseAvailableKeeps_Prepare,
         * DoInitial=MenuView_General_DoInitial_ScreenToBlack,
         * DoEveryFrame=MenuView_UnusedChooseAvailableKeeps_DoEveryFrame. Constructor_MenuView stores these in the
         * object and pushes it onto the global DAT_MenuViewStackTop linked list;
         * Destructor_MenuView_UnusedChooseAvailableKeeps is registered with atexit.
         */
        void __cdecl Constructor_MenuView_UnusedChooseAvailableKeeps();

        /**
         * Static initializer: constructs global MenuView_UnusedChooseGameType for view type
         * MVT_UNUSED_CHOOSE_GAME_TYPE with callbacks Prepare=DoNothing,
         * DoInitial=MenuView_General_DoInitial_ScreenToBlack,
         * DoEveryFrame=MenuView_UnusedChooseGameType_DoEveryFrame. Constructor_MenuView stores these in the object
         * and pushes it onto the global DAT_MenuViewStackTop linked list; Destructor_MenuView_UnusedChooseGameType
         * is registered with atexit.
         */
        void __cdecl Constructor_MenuView_UnusedChooseGameType();

        /**
         * Static initializer: constructs global MenuView_UnusedCreateSiege for view type MVT_UNUSED_CREATE_SIEGE
         * with callbacks Prepare=MenuView_UnusedCreateSiege_Prepare,
         * DoInitial=MenuView_General_DoInitial_DefaultMainMenuStructure,
         * DoEveryFrame=MenuView_UnusedCreateSiege_DoEveryFrame. Constructor_MenuView stores these in the object and
         * pushes it onto the global DAT_MenuViewStackTop linked list; Destructor_MenuView_UnusedCreateSiege is
         * registered with atexit.
         */
        void __cdecl Constructor_MenuView_UnusedCreateSiege();

        /**
         * Static initializer: constructs global MenuView_Unknown26_CampaignRelatedUnk for view type
         * MVT_MISSION_INTRO_SEQUENCE with callbacks Prepare=MenuView_Unknown26_CampaignRelatedUnk_Prepare,
         * DoInitial=MenuView_Unknown26_CampaignRelatedUnk_DoInitial,
         * DoEveryFrame=MenuView_MissionIntroSequence_DoEveryFrame. Constructor_MenuView stores these in the object
         * and pushes it onto the global DAT_MenuViewStackTop linked list;
         * Destructor_MenuView_Unknown26_CampaignRelatedUnk is registered with atexit.
         */
        void __cdecl Constructor_MenuView_MissionIntroSequence();

        /**
         * Static initializer: constructs global MenuView_CampaignUnk for view type MVT_CAMPAIGN_MAP with
         * callbacks Prepare=MenuView_CampaignUnk_Prepare, DoInitial=MenuView_CampaignUnk_DoInitial,
         * DoEveryFrame=MenuView_CampaignUnk_DoEveryFrame. Constructor_MenuView stores these in the object and
         * pushes it onto the global DAT_MenuViewStackTop linked list; Destructor_MenuView_CampaignUnk is registered
         * with atexit.
         */
        void __cdecl Constructor_MenuView_CampaignMap();

        /**
         * Static initializer: constructs global MenuView_ScenarioDescription for view type MVT_SCENARIO_DESCRIPTION
         * with callbacks Prepare=MenuView_ScenarioDescription_Prepare,
         * DoInitial=MenuView_ScenarioDescription_DoInitial, DoEveryFrame=MenuView_ScenarioDescription_DoEveryFrame.
         * Constructor_MenuView stores these in the object and pushes it onto the global DAT_MenuViewStackTop linked
         * list; Destructor_MenuView_ScenarioDescription is registered with atexit.
         */
        void __cdecl Constructor_MenuView_ScenarioDescription();

        /**
         * Static initializer: constructs global MenuView_MissionFinishedTransition for view type
         * MVT_MISSION_FINISHED_TRANSITION with callbacks Prepare=MenuView_MissionFinishedTransition_Prepare,
         * DoInitial=MenuView_General_DoInitial_DefaultMainMenuStructure,
         * DoEveryFrame=MenuView_MissionFinishedTransition_DoEveryFrame. Constructor_MenuView stores these in the
         * object and pushes it onto the global DAT_MenuViewStackTop linked list;
         * Destructor_MenuView_MissionFinishedTransition is registered with atexit.
         */
        void __cdecl Constructor_MenuView_MissionFinishedTransition();

        /**
         * Static initializer: constructs global MenuView_GameLost for view type MVT_GAME_LOST with callbacks
         * Prepare=MenuView_GameLost_Prepare, DoInitial=MenuView_General_DoInitial_DefaultMainMenuStructure,
         * DoEveryFrame=MenuView_GameLost_DoEveryFrame. Constructor_MenuView stores these in the object and pushes
         * it onto the global DAT_MenuViewStackTop linked list; Destructor_MenuView_GameLost is registered with
         * atexit.
         */
        void __cdecl Constructor_MenuView_GameLost();

        /**
         * Static initializer: constructs global MenuView_UnusedExtremeAd for view type MVT_UNUSED_EXTREME_AD with
         * callbacks Prepare=MenuView_UnusedExtremeAd_Prepare, DoInitial=MenuView_UnusedExtremeAd_DoInitial,
         * DoEveryFrame=MenuView_UnusedExtremeAd_DoEveryFrame. Constructor_MenuView stores these in the object and
         * pushes it onto the global DAT_MenuViewStackTop linked list; Destructor_MenuView_UnusedExtremeAd is
         * registered with atexit.
         */
        void __cdecl Constructor_MenuView_UnusedExtremeAd();

        /**
         * Static initializer: constructs global MenuView_EditScenario for view type MVT_EDIT_SCENARIO with
         * callbacks Prepare=MenuView_EditScenario_Prepare, DoInitial=MenuView_General_DoInitial_OnlySetMenuXY,
         * DoEveryFrame=MenuView_EditScenario_DoEveryFrame. Constructor_MenuView stores these in the object and
         * pushes it onto the global DAT_MenuViewStackTop linked list; Destructor_MenuView_EditScenario is
         * registered with atexit.
         */
        void __cdecl Constructor_MenuView_EditScenario();

        /**
         * Static initializer: constructs global MenuView_GameStartEnterName for view type MVT_GAME_START_ENTER_NAME
         * with callbacks Prepare=MenuView_GameStartEnterName_Prepare,
         * DoInitial=MenuView_GameStartEnterName_DoInitial, DoEveryFrame=MenuView_GameStartEnterName_DoEveryFrame.
         * Constructor_MenuView stores these in the object and pushes it onto the global DAT_MenuViewStackTop linked
         * list; Destructor_MenuView_GameStartEnterName is registered with atexit.
         */
        void __cdecl Constructor_MenuView_GameStartEnterName();

        /**
         * Static initializer: constructs global MenuView_MainMenu for view type MVT_MAIN_MENU with callbacks
         * Prepare=MenuView_MainMenu_Prepare, DoInitial=MenuView_MainMenu_DoInitial,
         * DoEveryFrame=MenuView_MainMenu_DoEveryFrame. Constructor_MenuView stores these in the object and pushes
         * it onto the global DAT_MenuViewStackTop linked list; Destructor_MenuView_MainMenu is registered with
         * atexit.
         */
        void __cdecl Constructor_MenuView_MainMenu();

        /**
         * Static initializer: constructs global MenuView_HistoricCampaignSelect for view type
         * MVT_HISTORIC_CAMPAIGN_SELECT with callbacks Prepare=MenuView_HistoricCampaignSelect_Prepare,
         * DoInitial=MenuView_General_DoInitial_BlackBoxDefaultBorderAndPicture,
         * DoEveryFrame=MenuView_HistoricCampaignSelect_DoEveryFrame. Constructor_MenuView stores these in the
         * object and pushes it onto the global DAT_MenuViewStackTop linked list;
         * Destructor_MenuView_HistoricCampaignSelect is registered with atexit.
         */
        void __cdecl Constructor_MenuView_HistoricCampaignSelect();

        /**
         * Static initializer: constructs global MenuView_UnusedEconomicGametypeSelect for view type
         * MVT_UNUSED_ECONOMIC_GAMETYPE_SELECT with callbacks Prepare=MenuView_UnusedEconomicGametypeSelect_Prepare,
         * DoInitial=MenuView_UnusedEconomicGametypeSelect_DoInitial,
         * DoEveryFrame=MenuView_General_DoEveryFrame_FirstGfxCentered. Constructor_MenuView stores these in the
         * object and pushes it onto the global DAT_MenuViewStackTop linked list;
         * Destructor_MenuView_UnusedEconomicGametypeSelect is registered with atexit.
         */
        void __cdecl Constructor_MenuView_UnusedEconomicGametypeSelect();

        /**
         * Static initializer: constructs global MenuView_CustomScenarios for view type MVT_CUSTOM_SCENARIOS with
         * callbacks Prepare=MenuView_CustomScenarios_Prepare,
         * DoInitial=MenuView_General_DoInitial_BlackBoxDefaultBorderAndPicture,
         * DoEveryFrame=MenuView_CustomScenarios_DoEveryFrame. Constructor_MenuView stores these in the object and
         * pushes it onto the global DAT_MenuViewStackTop linked list; Destructor_MenuView_CustomScenarios is
         * registered with atexit.
         */
        void __cdecl Constructor_MenuView_CustomScenarios();

        /**
         * Static initializer: constructs global MenuView_Credits for view type MVT_CREDITS with callbacks
         * Prepare=MenuView_Credits_Prepare, DoInitial=MenuView_Credits_DoInitial,
         * DoEveryFrame=MenuView_Credits_DoEveryFrame. Constructor_MenuView stores these in the object and pushes it
         * onto the global DAT_MenuViewStackTop linked list; Destructor_MenuView_Credits is registered with atexit.
         */
        void __cdecl Constructor_MenuView_Credits();

        /**
         * Static initializer: constructs global MenuView_UnusedDemoBuyItScreen for view type
         * MVT_UNUSED_DEMO_BUY_IT_SCREEN with callbacks Prepare=MenuView_UnusedDemoBuyItScreen_Prepare,
         * DoInitial=MenuView_UnusedDemoBuyItScreen_DoInitial,
         * DoEveryFrame=MenuView_UnusedDemoBuyItScreen_DoEveryFrame. Constructor_MenuView stores these in the object
         * and pushes it onto the global DAT_MenuViewStackTop linked list; Destructor_MenuView_UnusedDemoBuyItScreen
         * is registered with atexit.
         */
        void __cdecl Constructor_MenuView_UnusedDemoBuyItScreen();

        /**
         * Static initializer: constructs global MenuView_IntroVideo for view type MVT_INTRO_VIDEO with callbacks
         * Prepare=MenuView_IntroVideo_Prepare, DoInitial=MenuView_General_DoInitial_OnlySetMenuXY,
         * DoEveryFrame=MenuView_IntroVideo_DoEveryFrame. Constructor_MenuView stores these in the object and pushes
         * it onto the global DAT_MenuViewStackTop linked list; Destructor_MenuView_IntroVideo is registered with
         * atexit.
         */
        void __cdecl Constructor_MenuView_IntroVideo();

        /**
         * Static initializer: constructs global MenuView_HistoricMissionPicture for view type
         * MVT_HISTORIC_MISSION_PICTURE with callbacks Prepare=MenuView_HistoricMissionPicture_Prepare,
         * DoInitial=MenuView_General_DoInitial_BlackBorderAndGfx,
         * DoEveryFrame=MenuView_HistoricMissionPicture_DoEveryFrame. Constructor_MenuView stores these in the
         * object and pushes it onto the global DAT_MenuViewStackTop linked list;
         * Destructor_MenuView_HistoricMissionPicture is registered with atexit.
         */
        void __cdecl Constructor_MenuView_HistoricMissionPicture();

        /**
         * Static initializer: constructs global MenuView_HistoricMissionIntro for view type
         * MVT_HISTORIC_MISSION_INTRO with callbacks Prepare=MenuView_HistoricMissionIntro_Prepare,
         * DoInitial=MenuView_General_DoInitial_BlackBorderAndGfx,
         * DoEveryFrame=MenuView_HistoricMissionIntro_DoEveryFrame. Constructor_MenuView stores these in the object
         * and pushes it onto the global DAT_MenuViewStackTop linked list; Destructor_MenuView_HistoricMissionIntro
         * is registered with atexit.
         */
        void __cdecl Constructor_MenuView_HistoricMissionIntro();

        /**
         * Static initializer: constructs global MenuView_HistoricCampaignIntro for view type
         * MVT_HISTORIC_CAMPAIGN_INTRO with callbacks Prepare=MenuView_HistoricCampaignIntro_Prepare,
         * DoInitial=MenuView_General_DoInitial_BlackBorderAndGfx,
         * DoEveryFrame=MenuView_HistoricCampaignIntro_DoEveryFrame. Constructor_MenuView stores these in the object
         * and pushes it onto the global DAT_MenuViewStackTop linked list; Destructor_MenuView_HistoricCampaignIntro
         * is registered with atexit.
         */
        void __cdecl Constructor_MenuView_HistoricCampaignIntro();

        /**
         * Static initializer: constructs global MenuView_HistoricCampaignOutro for view type
         * MVT_HISTORIC_CAMPAIGN_OUTRO with callbacks Prepare=MenuView_HistoricCampaignOutro_Prepare,
         * DoInitial=MenuView_General_DoInitial_BlackBorderAndGfx,
         * DoEveryFrame=MenuView_HistoricCampaignOutro_DoEveryFrame. Constructor_MenuView stores these in the object
         * and pushes it onto the global DAT_MenuViewStackTop linked list; Destructor_MenuView_HistoricCampaignOutro
         * is registered with atexit.
         */
        void __cdecl Constructor_MenuView_HistoricCampaignOutro();

        /**
         * Static initializer: constructs global MenuView_UnusedSelectRandomNumberOfEnemies for view type
         * MVT_UNUSED_SELECT_RANDOM_NUMBER_OF_ENEMIES with callbacks
         * Prepare=MenuView_General_Prepare_SwordShieldAndBorder,
         * DoInitial=MenuView_General_DoInitial_DefaultMainMenuStructure,
         * DoEveryFrame=MenuView_UnusedSelectRandomNumberOfEnemies_DoEveryFrame. Constructor_MenuView stores these
         * in the object and pushes it onto the global DAT_MenuViewStackTop linked list;
         * Destructor_MenuView_UnusedSelectRandomNumberOfEnemies is registered with atexit.
         */
        void __cdecl Constructor_MenuView_UnusedSelectRandomNumberOfEnemies();

        /**
         * Static initializer: constructs global MenuView_SelectCrusade for view type MVT_SELECT_CRUSADE with
         * callbacks Prepare=MenuView_General_Prepare_SwordShieldAndBorder,
         * DoInitial=MenuView_SelectCrusade_DoInitial, DoEveryFrame=MenuView_SelectCrusade_DoEveryFrame.
         * Constructor_MenuView stores these in the object and pushes it onto the global DAT_MenuViewStackTop linked
         * list; Destructor_MenuView_SelectCrusade is registered with atexit.
         */
        void __cdecl Constructor_MenuView_SelectCrusade();

        /**
         * Static initializer: constructs global MenuView_CrusadeMissionIntro for view type
         * MVT_CRUSADE_MISSION_INTRO with callbacks Prepare=MenuView_CrusadeMissionIntro_Prepare,
         * DoInitial=MenuView_General_DoInitial_CrusadeAndRankMenu,
         * DoEveryFrame=MenuView_CrusadeMissionIntro_DoEveryFrame. Constructor_MenuView stores these in the object
         * and pushes it onto the global DAT_MenuViewStackTop linked list; Destructor_MenuView_CrusadeMissionIntro
         * is registered with atexit.
         */
        void __cdecl Constructor_MenuView_CrusadeMissionIntro();

        /**
         * Static initializer: constructs global MenuView_CrusadeMap for view type MVT_CRUSADE_MAP with callbacks
         * Prepare=MenuView_CrusadeMap_Prepare, DoInitial=MenuView_General_DoInitial_CrusadeAndRankMenu,
         * DoEveryFrame=MenuView_CrusadeMap_DoEveryFrame. Constructor_MenuView stores these in the object and pushes
         * it onto the global DAT_MenuViewStackTop linked list; Destructor_MenuView_CrusadeMap is registered with
         * atexit.
         */
        void __cdecl Constructor_MenuView_CrusadeMap();

        /**
         * Static initializer: constructs global MenuView_RankingGames for view type MVT_RANKING_GAMES with
         * callbacks Prepare=MenuView_RankingGames_Prepare, DoInitial=MenuView_General_DoInitial_CrusadeAndRankMenu,
         * DoEveryFrame=MenuView_RankingGames_DoEveryFrame. Constructor_MenuView stores these in the object and
         * pushes it onto the global DAT_MenuViewStackTop linked list; Destructor_MenuView_RankingGames is
         * registered with atexit.
         */
        void __cdecl Constructor_MenuView_RankingGames();

        /**
         * Static initializer: constructs global MenuView_CrusadeEndscreen for view type MVT_CRUSADE_ENDSCREEN with
         * callbacks Prepare=MenuView_CrusadeEndscreen_Prepare, DoInitial=MenuView_CrusadeEndscreen_DoInitial,
         * DoEveryFrame=MenuView_CrusadeEndscreen_DoEveryFrame. Constructor_MenuView stores these in the object and
         * pushes it onto the global DAT_MenuViewStackTop linked list; Destructor_MenuView_CrusadeEndscreen is
         * registered with atexit.
         */
        void __cdecl Constructor_MenuView_CrusadeEndscreen();

        /**
         * Static initializer: constructs global Menu Menu_Unknown_ManyThings from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_EmptyShared.
         */
        void __cdecl Constructor_Menu_EmptyShared();

        /**
         * Static initializer: constructs global Menu Menu_IntroLogos from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_IntroLogos.
         */
        void __cdecl Constructor_Menu_IntroLogos();

        /**
         * Static initializer: constructs global Menu Menu_IntroVideo from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_IntroVideo.
         */
        void __cdecl Constructor_Menu_IntroVideo();

        /**
         * Static initializer: constructs global Menu Menu_StartEnterName from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_StartEnterName.
         */
        void __cdecl Constructor_Menu_StartEnterName();

        /**
         * Static initializer: constructs global Menu Menu_MainMenu from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_MainMenu.
         */
        void __cdecl Constructor_Menu_MainMenu();

        /**
         * Static initializer: constructs global Menu Menu_HistoricCampaignSelect from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_HistoricCampaignSelect.
         */
        void __cdecl Constructor_Menu_HistoricCampaignSelect();

        /**
         * Static initializer: constructs global Menu Menu_UnusedEconomicGametypeSelect from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_UnusedEconomicGametypeSelect.
         */
        void __cdecl Constructor_Menu_UnusedEconomicGametypeSelect();

        /**
         * Static initializer: constructs global Menu Menu_CustomScenarios from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_CustomScenarios.
         */
        void __cdecl Constructor_Menu_CustomScenarios();

        /**
         * Static initializer: constructs global Menu Menu_UnusedSomeMissionStartUnk from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_UnusedSomeMissionStartUnk.
         */
        void __cdecl Constructor_Menu_UnusedSomeMissionStartUnk();

        /**
         * Static initializer: constructs global Menu Menu_HistoricMissionSelect from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_HistoricMissionSelect.
         */
        void __cdecl Constructor_Menu_HistoricMissionSelect();

        /**
         * Static initializer: constructs global Menu Menu_UnusedEconomicMissionSelect from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_UnusedEconomicMissionSelect.
         */
        void __cdecl Constructor_Menu_UnusedEconomicMissionSelect();

        /**
         * Static initializer: constructs global Menu Menu_UnusedSetName from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_UnusedSetName.
         */
        void __cdecl Constructor_Menu_UnusedSetName();

        /**
         * Static initializer: constructs global Menu Menu_UnusedOldTitleMenu from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_UnusedOldTitleMenu.
         */
        void __cdecl Constructor_Menu_UnusedOldTitleMenu();

        /**
         * Static initializer: constructs global Menu Menu_LobbyMenu from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_LobbyMenu.
         */
        void __cdecl Constructor_Menu_LobbyMenu();

        /**
         * Static initializer: constructs global Menu Menu_SkirmishConnectionOptions from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_SkirmishConnectionOptions.
         */
        void __cdecl Constructor_Menu_SkirmishConnectionOptions();

        /**
         * Static initializer: constructs global Menu Menu_SkirmishPlayOptions from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_SkirmishPlayOptions.
         */
        void __cdecl Constructor_Menu_SkirmishPlayOptions();

        /**
         * Static initializer: constructs global Menu Menu_SendMapTo from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_SendMapTo.
         */
        void __cdecl Constructor_Menu_SendMapTo();

        /**
         * Static initializer: constructs global Menu Menu_ReceiveMapFrom from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_ReceiveMapFrom.
         */
        void __cdecl Constructor_Menu_ReceiveMapFrom();

        /**
         * Static initializer: constructs global Menu Menu_UnusedSelectRandomNumberOfEnemies from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_UnusedSelectRandomNumberOfEnemies.
         */
        void __cdecl Constructor_Menu_UnusedSelectRandomNumberOfEnemies();

        /**
         * Static initializer: constructs global Menu Menu_ChooseRandomNumberOfEnemies from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_ChooseRandomNumberOfEnemies.
         */
        void __cdecl Constructor_Menu_ChooseRandomNumberOfEnemies();

        /**
         * Static initializer: constructs global Menu Menu_SelectCrusade from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_SelectCrusade.
         */
        void __cdecl Constructor_Menu_SelectCrusade();

        /**
         * Static initializer: constructs global Menu Menu_BasicAiLordSelect from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_BasicAiLordSelect.
         */
        void __cdecl Constructor_Menu_BasicAiLordSelect();

        /**
         * Static initializer: constructs global Menu Menu_ExtendedAiLordSelect from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_ExtendedAiLordSelect.
         */
        void __cdecl Constructor_Menu_ExtendedAiLordSelect();

        /**
         * Static initializer: constructs global Menu Menu_Roundtable from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_Roundtable.
         */
        void __cdecl Constructor_Menu_Roundtable();

        /**
         * Static initializer: constructs global Menu Menu_OverlaySlider from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_OverlaySlider.
         */
        void __cdecl Constructor_Menu_OverlaySlider();

        /**
         * Static initializer: constructs global Menu Menu_UnusedWinCondition from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_UnusedWinCondition.
         */
        void __cdecl Constructor_Menu_UnusedWinCondition();

        /**
         * Static initializer: constructs global Menu Menu_SingleplayerMapChoice from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_SingleplayerMapChoice.
         */
        void __cdecl Constructor_Menu_SingleplayerMapChoice();

        /**
         * Static initializer: constructs global Menu Menu_MapEditorProperties from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_MapEditorProperties.
         */
        void __cdecl Constructor_Menu_MapEditorProperties();

        /**
         * Static initializer: constructs global Menu Menu_NewMapMaptype from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_NewMapMaptype.
         */
        void __cdecl Constructor_Menu_NewMapMaptype();

        /**
         * Static initializer: constructs global Menu Menu_NewMapMapsize from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_NewMapMapsize.
         */
        void __cdecl Constructor_Menu_NewMapMapsize();

        /**
         * Static initializer: constructs global Menu Menu_UnusedChooseAvailableKeeps from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_UnusedChooseAvailableKeeps.
         */
        void __cdecl Constructor_Menu_UnusedChooseAvailableKeeps();

        /**
         * Static initializer: constructs global Menu Menu_UnusedChooseGameType from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_UnusedChooseGameType.
         */
        void __cdecl Constructor_Menu_UnusedChooseGameType();

        /**
         * Static initializer: constructs global Menu Menu_UnusedCreateSiege from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_UnusedCreateSiege.
         */
        void __cdecl Constructor_Menu_UnusedCreateSiege();

        /**
         * Static initializer: constructs global Menu Menu_Unknown26CampaignRelatedUnk from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_MissionIntroSequence.
         */
        void __cdecl Constructor_Menu_MissionIntroSequence();

        /**
         * Static initializer: constructs global Menu Menu_Unknown27CampaignUnk from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_CampaignMap.
         */
        void __cdecl Constructor_Menu_CampaignMap();

        /**
         * Static initializer: constructs global Menu Menu_UnusedExtremeAd from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_UnusedExtremeAd.
         */
        void __cdecl Constructor_Menu_UnusedExtremeAd();

        /**
         * Static initializer: constructs global Menu Menu_HistoricCampaignIntroAndMissionPicture from menu-item
         * table DAT_TroopValueDefinedData.MenuItems_HistoricCampaignIntroAndMissionPicture.
         */
        void __cdecl Constructor_Menu_HistoricCampaignIntroAndMissionPicture();

        /**
         * Static initializer: constructs global Menu Menu_HistoricCampaignOutroAndMissionIntro from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_HistoricCampaignOutroAndMissionIntro.
         */
        void __cdecl Constructor_Menu_HistoricCampaignOutroAndMissionIntro();

        /**
         * Static initializer: constructs global Menu Menu_ScenarioDescription from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_ScenarioDescription.
         */
        void __cdecl Constructor_Menu_ScenarioDescription();

        /**
         * Static initializer: constructs global Menu Menu_CrusadeMissionIntro from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_CrusadeMissionIntro.
         */
        void __cdecl Constructor_Menu_CrusadeMissionIntro();

        /**
         * Static initializer: constructs global Menu Menu_CrusadeMap from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_CrusadeMap.
         */
        void __cdecl Constructor_Menu_CrusadeMap();

        /**
         * Static initializer: constructs global Menu Menu_RankingGames from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_RankingGames.
         */
        void __cdecl Constructor_Menu_RankingGames();

        /**
         * Static initializer: constructs global Menu Menu_CrusadeEndscreen from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_CrusadeEndscreen.
         */
        void __cdecl Constructor_Menu_CrusadeEndscreen();

        /**
         * Static initializer: constructs global Menu Menu_MissionFinishedTransition from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_MissionFinishedTransition.
         */
        void __cdecl Constructor_Menu_MissionFinishedTransition();

        /**
         * Static initializer: constructs global Menu Menu_GameLostUnk from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_GameLost.
         */
        void __cdecl Constructor_Menu_GameLost();

        /**
         * Static initializer: constructs global Menu Menu_ChooseNetworkServiceProvider from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_ChooseNetworkServiceProvider.
         */
        void __cdecl Constructor_Menu_ChooseNetworkServiceProvider();

        /**
         * Static initializer: constructs global Menu Menu_FindingNetworkSessions from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_FindingNetworkSessions.
         */
        void __cdecl Constructor_Menu_FindingNetworkSessions();

        /**
         * Static initializer: constructs global Menu Menu_WaitingForHost from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_WaitingForHost.
         */
        void __cdecl Constructor_Menu_WaitingForHost();

        /**
         * Static initializer: constructs global Menu Menu_BuildMenu from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_BuildMenu.
         */
        void __cdecl Constructor_Menu_BuildMenu();

        /**
         * Static initializer: constructs global Menu Menu_BuildingAndStatusMenu from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_BuildingAndStatusMenu.
         */
        void __cdecl Constructor_Menu_BuildingAndStatusMenu();

        /**
         * Static initializer: constructs global Menu Menu_PauseMenu from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_PauseMenu.
         */
        void __cdecl Constructor_Menu_PauseMenu();

        /**
         * Static initializer: constructs global Menu Menu_PauseMenuOptions from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_PauseMenuOptions.
         */
        void __cdecl Constructor_Menu_PauseMenuOptions();

        /**
         * Static initializer: constructs global Menu Menu_MainMenuOptions from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_MainMenuOptions.
         */
        void __cdecl Constructor_Menu_MainMenuOptions();

        /**
         * Static initializer: constructs global Menu Menu_GameplayOptions from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_GameplayOptions.
         */
        void __cdecl Constructor_Menu_GameplayOptions();

        /**
         * Static initializer: constructs global Menu Menu_VideoOptions from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_VideoOptions.
         */
        void __cdecl Constructor_Menu_VideoOptions();

        /**
         * Static initializer: constructs global Menu Menu_SoundOptions from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_SoundOptions.
         */
        void __cdecl Constructor_Menu_SoundOptions();

        /**
         * Static initializer: constructs global Menu Menu_IdentityOptions from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_IdentityOptions.
         */
        void __cdecl Constructor_Menu_IdentityOptions();

        /**
         * Static initializer: constructs global Menu Menu_EnterTitleOnGameStart from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_EnterTitleOnGameStart.
         */
        void __cdecl Constructor_Menu_EnterTitleOnGameStart();

        /**
         * Static initializer: constructs global Menu Menu_NetworkOptions from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_NetworkOptions.
         */
        void __cdecl Constructor_Menu_NetworkOptions();

        /**
         * Static initializer: constructs global Menu Menu_LoadMap from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_LoadMap.
         */
        void __cdecl Constructor_Menu_LoadMap();

        /**
         * Static initializer: constructs global Menu Menu_SaveMap from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_SaveMap.
         */
        void __cdecl Constructor_Menu_SaveMap();

        /**
         * Static initializer: constructs global Menu Menu_YesNoDialog from menu-item table
         * DAT_TroopValueDefinedData.MenuItem_YesNoDialog.
         */
        void __cdecl Constructor_Menu_YesNoDialog();

        /**
         * Static initializer: constructs global Menu Menu_QuitDialog from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_QuitDialog.
         */
        void __cdecl Constructor_Menu_QuitDialog();

        /**
         * Static initializer: constructs global Menu Menu_DeleteGameRecord from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_DeleteGameRecord.
         */
        void __cdecl Constructor_Menu_DeleteGameRecord();

        /**
         * Static initializer: constructs global Menu Menu_TacticalPowerBar from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_TacticalPowerBar.
         */
        void __cdecl Constructor_Menu_TacticalPowerBar();

        /**
         * Static initializer: constructs global Menu Menu_ProgressBarBox from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_ProgressBarBox.
         */
        void __cdecl Constructor_Menu_ProgressBarBox();

        /**
         * Static initializer: constructs global Menu Menu_Chat from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_Chat.
         */
        void __cdecl Constructor_Menu_Chat();

        /**
         * Static initializer: constructs global Menu Menu_Allies from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_Allies.
         */
        void __cdecl Constructor_Menu_Allies();

        /**
         * Static initializer: constructs global Menu Menu_AlliesOrder from menu-item table
         * DAT_TroopValueDefinedData.MenuItem_AlliesOrder.
         */
        void __cdecl Constructor_Menu_AlliesOrder();

        /**
         * Static initializer: constructs global Menu Menu_AlliesRequestGoods from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_AlliesRequestGoods.
         */
        void __cdecl Constructor_Menu_AlliesRequestGoods();

        /**
         * Static initializer: constructs global Menu Menu_AlliesSendGoods from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_AlliesSendGoods.
         */
        void __cdecl Constructor_Menu_AlliesSendGoods();

        /**
         * Static initializer: constructs global Menu Menu_GreatestLord from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_GreatestLord.
         */
        void __cdecl Constructor_Menu_GreatestLord();

        /**
         * Static initializer: constructs global Menu Menu_OnlineQuitGame from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_OnlineQuitGame.
         */
        void __cdecl Constructor_Menu_OnlineQuitGame();

        /**
         * Static initializer: constructs global Menu Menu_OnlineVoteQuitGame from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_OnlineVoteQuitGame.
         */
        void __cdecl Constructor_Menu_OnlineVoteQuitGame();

        /**
         * Static initializer: constructs global Menu Menu_DebugModals from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_DebugModals.
         */
        void __cdecl Constructor_Menu_DebugModals();

        /**
         * Static initializer: constructs global Menu Menu_DisplayAiLordMessage from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_DisplayAiLordMessage.
         */
        void __cdecl Constructor_Menu_DisplayAiLordMessage();

        /**
         * Static initializer: constructs global Menu Menu_TutorialBox from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_TutorialBox.
         */
        void __cdecl Constructor_Menu_TutorialBox();

        /**
         * Static initializer: constructs global Menu Menu_TutorialBoxWithLeave from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_TutorialBoxWithLeave.
         */
        void __cdecl Constructor_Menu_TutorialBoxWithLeave();

        /**
         * Static initializer: constructs global Menu Menu_UnusedHelpTextEditor from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_UnusedHelpTextEditor.
         */
        void __cdecl Constructor_Menu_UnusedHelpTextEditor();

        /**
         * Static initializer: constructs global Menu Menu_BuildingHelpText from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_BuildingHelpText.
         */
        void __cdecl Constructor_Menu_BuildingHelpText();

        /**
         * Static initializer: constructs global Menu Menu_InGameHelpText from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_InGameHelpText.
         */
        void __cdecl Constructor_Menu_InGameHelpText();

        /**
         * Static initializer: constructs global Menu Menu_DisplayScenarioHelpText from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_DisplayScenarioHelpText.
         */
        void __cdecl Constructor_Menu_DisplayScenarioHelpText();

        /**
         * Static initializer: constructs global Menu Menu_Credits from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_Credits.
         */
        void __cdecl Constructor_Menu_Credits();

        /**
         * Static initializer: constructs global Menu Menu_MapDescriptionEditor from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_MapDescriptionEditor.
         */
        void __cdecl Constructor_Menu_MapDescriptionEditor();

        /**
         * Static initializer: constructs global Menu Menu_UnusedDemoBuyItScreen from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_UnusedDemoBuyItScreen.
         */
        void __cdecl Constructor_Menu_UnusedDemoBuyItScreen();

        /**
         * Static initializer: constructs global Menu Menu_EditorMapTypeQuickChange from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_EditorMapTypeQuickChange.
         */
        void __cdecl Constructor_Menu_EditorMapTypeQuickChange();

        /**
         * Static initializer: constructs global Menu Menu_Empty10 from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_Empty10.
         */
        void __cdecl Constructor_Menu_Empty10();

        /**
         * Static initializer: constructs global Menu Menu_Empty11 from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_Empty11.
         */
        void __cdecl Constructor_Menu_Empty11();

        /**
         * Static initializer: constructs global Menu Menu_MapEditorLandscaping from menu-item table
         * DAT_TroopValueDefinedData.MenuItems_Menu_MapEditorLandscaping.
         */
        void __cdecl Constructor_Menu_MapEditorLandscaping();

        /**
         * Static initializer: constructs global menu Menu_EditScenario from its item table
         * DAT_TroopValueDefinedData.MenuItems_EditScenario via UI::Menu::Constructor_Menu (no atexit destructor).
         */
        void __cdecl Constructor_Menu_EditScenario();

        /**
         * Static initializer: constructs global menu Menu_UnusedChooseMessageBox from its item table
         * DAT_TroopValueDefinedData.MenuItems_UnusedChooseMessageBox via UI::Menu::Constructor_Menu (no atexit
         * destructor).
         */
        void __cdecl Constructor_Menu_UnusedChooseMessageBox();

        /**
         * Static initializer: constructs global menu Menu_TraderSettings from its item table
         * DAT_TroopValueDefinedData.MenuItems_TraderSettings via UI::Menu::Constructor_Menu (no atexit destructor).
         */
        void __cdecl Constructor_Menu_TraderSettings();

        /**
         * Static initializer: constructs global menu Menu_StartGoods from its item table
         * DAT_TroopValueDefinedData.MenuItems_StartGoods via UI::Menu::Constructor_Menu (no atexit destructor).
         */
        void __cdecl Constructor_Menu_StartGoods();

        /**
         * Static initializer: constructs global menu Menu_UnusedSiegeAttackingForceUnk from its item table
         * DAT_TroopValueDefinedData.MenuItems_SiegeAttackingForce via UI::Menu::Constructor_Menu (no atexit
         * destructor).
         */
        void __cdecl Constructor_Menu_SiegeAttackingForce();

        /**
         * Static initializer: constructs global menu Menu_NewInvasion from its item table
         * DAT_TroopValueDefinedData.MenuItems_NewInvasion via UI::Menu::Constructor_Menu (no atexit destructor).
         */
        void __cdecl Constructor_Menu_NewInvasion();

        /**
         * Static initializer: constructs global menu Menu_UnusedCreateTimedMessageEvent from its item table
         * DAT_TroopValueDefinedData.MenuItems_UnusedCreateTimedMessageEvent via UI::Menu::Constructor_Menu (no
         * atexit destructor).
         */
        void __cdecl Constructor_Menu_UnusedCreateTimedMessageEvent();

        /**
         * Static initializer: constructs global menu Menu_NewEvent from its item table
         * DAT_TroopValueDefinedData.MenuItems_NewEvent via UI::Menu::Constructor_Menu (no atexit destructor).
         */
        void __cdecl Constructor_Menu_NewEvent();

        /**
         * Static initializer: constructs global menu Menu_NewEventCondition from its item table
         * DAT_TroopValueDefinedData.MenuItems_NewEventCondition via UI::Menu::Constructor_Menu (no atexit
         * destructor).
         */
        void __cdecl Constructor_Menu_NewEventCondition();

        /**
         * Static initializer: constructs global menu Menu_NewEventAction from its item table
         * DAT_TroopValueDefinedData.MenuItems_NewEventAction via UI::Menu::Constructor_Menu (no atexit destructor).
         */
        void __cdecl Constructor_Menu_NewEventAction();

        /**
         * Static initializer: constructs global menu Menu_UnusedCreateMessageEvent from its item table
         * DAT_TroopValueDefinedData.MenuItems_UnusedCreateMessageEvent via UI::Menu::Constructor_Menu (no atexit
         * destructor).
         */
        void __cdecl Constructor_Menu_UnusedCreateMessageEvent();

        /**
         * Static initializer: constructs global menu Menu_BuildingAvailability from its item table
         * DAT_TroopValueDefinedData.MenuItems_BuildingAvailability via UI::Menu::Constructor_Menu (no atexit
         * destructor).
         */
        void __cdecl Constructor_Menu_BuildingAvailability();

        /**
         * Static initializer: constructs global menu Menu_DisableEuroTroops from its item table
         * DAT_TroopValueDefinedData.MenuItems_DisableEuroTroops via UI::Menu::Constructor_Menu (no atexit
         * destructor).
         */
        void __cdecl Constructor_Menu_DisableEuroTroops();

        /**
         * Static initializer: constructs global menu Menu_DisableArabTroops from its item table
         * DAT_TroopValueDefinedData.MenuItems_DisableArabTroops via UI::Menu::Constructor_Menu (no atexit
         * destructor).
         */
        void __cdecl Constructor_Menu_DisableArabTroops();

        /**
         * Static initializer: constructs global menu Menu_DisableWeapon from its item table
         * DAT_TroopValueDefinedData.MenuItems_DisableWeapon via UI::Menu::Constructor_Menu (no atexit destructor).
         */
        void __cdecl Constructor_Menu_DisableWeapon();

        /**
         * Static initializer: constructs global menu Menu_TriggerInvasion from its item table
         * DAT_TroopValueDefinedData.MenuItems_TriggerInvasion via UI::Menu::Constructor_Menu (no atexit destructor).
         */
        void __cdecl Constructor_Menu_TriggerInvasion();

        /**
         * Static initializer: constructs global menu Menu_TriggerEventOrInvasion from its item table
         * DAT_TroopValueDefinedData.MenuItems_TriggerEventOrInvasion via UI::Menu::Constructor_Menu (no atexit
         * destructor).
         */
        void __cdecl Constructor_Menu_TriggerEventOrInvasion();

        /**
         * Static initializer: constructs global menu Menu_TriggerEvent from its item table
         * DAT_TroopValueDefinedData.MenuItems_TriggerEvent via UI::Menu::Constructor_Menu (no atexit destructor).
         */
        void __cdecl Constructor_Menu_TriggerEvent();

        /**
         * Static initializer: constructs global menu Menu_TriggerEventSlider from its item table
         * DAT_TroopValueDefinedData.MenuItems_TriggerEventSlider via UI::Menu::Constructor_Menu (no atexit
         * destructor).
         */
        void __cdecl Constructor_Menu_TriggerEventSlider();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_OverlaySlider
         * (MMT_OVERLAY_SLIDER): x=0, y=0, size 204x17, style flags 0, colour field 0, render function
         * MenuModalRenderFunction_OverlaySlider, menu Menu_OverlaySlider; the constructor also pushes it onto the
         * DAT_ModalMenuArrayPointerToStackTop list. Registers Meta::Destructor_MenuModal_OverlaySlider with atexit.
         * Non-centred coordinates are offsets inside the centred 800x600 area.
         */
        void __cdecl Constructor_MenuModal_OverlaySlider();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_SliderHeightHolderUnk
         * (MMT_UNUSED_WIN_CONDITION): x=0, y=0, size 240x0, style flags 0, colour field 0, render function
         * DoNothing, menu Menu_UnusedWinCondition; the constructor also pushes it onto the
         * DAT_ModalMenuArrayPointerToStackTop list. Registers Meta::Destructor_MenuModal_UnusedWinCondition with
         * atexit. Non-centred coordinates are offsets inside the centred 800x600 area.
         */
        void __cdecl Constructor_MenuModal_UnusedWinCondition();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_DebugDataCurrentPlayerData
         * (MMT_DEBUG_DATA_CURRENT_PLAYER_DATA): x=267, y=3, size 400x242, style flags 0xe, colour field COL_WHITE
         * (raw 16-bit colour value), render function MenuModalRenderFunction_DebugDataCurrentPlayerData, menu
         * Menu_DebugModals; the constructor also pushes it onto the DAT_ModalMenuArrayPointerToStackTop list.
         * Registers Meta::Destructor_MenuModal_DebugDataCurrentPlayerData with atexit. Non-centred coordinates are
         * offsets inside the centred 800x600 area.
         */
        void __cdecl Constructor_MenuModal_DebugDataCurrentPlayerData();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_DebugDataAiInfo
         * (MMT_DEBUG_DATA_AI_INFO): x=10, y=3, size 780x240, style flags 0xe, colour field COL_WHITE (raw 16-bit
         * colour value), render function MenuModalRenderFunction_DebugDataAiInfo, menu Menu_DebugModals; the
         * constructor also pushes it onto the DAT_ModalMenuArrayPointerToStackTop list. Registers
         * Meta::Destructor_MenuModal_DebugDataAiInfo with atexit. Non-centred coordinates are offsets inside the
         * centred 800x600 area.
         */
        void __cdecl Constructor_MenuModal_DebugDataAiInfo();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_DebugDataUnitData
         * (MMT_DEBUG_DATA_UNIT_DATA): x=267, y=3, size 400x142, style flags 0xe, colour field COL_WHITE (raw 16-bit
         * colour value), render function MenuModalRenderFunction_DebugDataUnitData, menu Menu_DebugModals; the
         * constructor also pushes it onto the DAT_ModalMenuArrayPointerToStackTop list. Registers
         * Meta::Destructor_MenuModal_DebugDataUnitData with atexit. Non-centred coordinates are offsets inside the
         * centred 800x600 area.
         */
        void __cdecl Constructor_MenuModal_DebugDataUnitData();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_DebugDataZoneDataUnk
         * (MMT_DEBUG_DATA_ATTACK_INFO): x=267, y=3, size 400x200, style flags 0xe, colour field COL_WHITE (raw
         * 16-bit colour value), render function MenuModalRenderFunction_DebugDataZoneDataUnk, menu
         * Menu_DebugModals; the constructor also pushes it onto the DAT_ModalMenuArrayPointerToStackTop list.
         * Registers Meta::Destructor_MenuModal_DebugDataZoneDataUnk with atexit. Non-centred coordinates are
         * offsets inside the centred 800x600 area.
         */
        void __cdecl Constructor_MenuModal_DebugDataAttackInfo();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_DebugDataNetwork
         * (MMT_DEBUG_DATA_NETWORK): x=167, y=3, size 500x200, style flags 0xe, colour field COL_WHITE (raw 16-bit
         * colour value), render function MenuModalRenderFunction_DebugDataNetwork, menu Menu_DebugModals; the
         * constructor also pushes it onto the DAT_ModalMenuArrayPointerToStackTop list. Registers
         * Meta::Destructor_MenuModal_DebugDataNetwork with atexit. Non-centred coordinates are offsets inside the
         * centred 800x600 area.
         */
        void __cdecl Constructor_MenuModal_DebugDataNetwork();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_DebugDataMousePointing
         * (MMT_DEBUG_DATA_MOUSE_POINTING): x=267, y=3, size 400x142, style flags 0xe, colour field COL_WHITE (raw
         * 16-bit colour value), render function MenuModalRenderFunction_DebugDataMousePointing, menu
         * Menu_DebugModals; the constructor also pushes it onto the DAT_ModalMenuArrayPointerToStackTop list.
         * Registers Meta::Destructor_MenuModal_DebugDataMousePointing with atexit. Non-centred coordinates are
         * offsets inside the centred 800x600 area.
         */
        void __cdecl Constructor_MenuModal_DebugDataMousePointing();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_DebugDataSplitInfo
         * (MMT_DEBUG_DATA_SPLIT_INFO): x=267, y=3, size 500x302, style flags 0xe, colour field COL_WHITE (raw
         * 16-bit colour value), render function MenuModalRenderFunction_DebugDataSplitInfo, menu Menu_DebugModals;
         * the constructor also pushes it onto the DAT_ModalMenuArrayPointerToStackTop list. Registers
         * Meta::Destructor_MenuModal_DebugDataSplitInfo with atexit. Non-centred coordinates are offsets inside the
         * centred 800x600 area.
         */
        void __cdecl Constructor_MenuModal_DebugDataSplitInfo();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_DebugDataMapData
         * (MMT_DEBUG_DATA_MAP_DATA): x=4, y=4, size 600x414, style flags 0xe, colour field COL_WHITE (raw 16-bit
         * colour value), render function MenuModalRenderFunction_DebugDataMapData, menu Menu_DebugModals; the
         * constructor also pushes it onto the DAT_ModalMenuArrayPointerToStackTop list. Registers
         * Meta::Destructor_MenuModal_DebugDataMapData with atexit. Non-centred coordinates are offsets inside the
         * centred 800x600 area.
         */
        void __cdecl Constructor_MenuModal_DebugDataMapData();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_PauseMenu (MMT_PAUSE_MENU):
         * centred (x = y = -1), size 500x357 (rounded up to multiples of 24 when activated), style flags 0x200,
         * colour field COL_WHITE (raw 16-bit colour value), render function MenuModalRenderFunction_OptionsMenu,
         * menu Menu_PauseMenu; the constructor also pushes it onto the DAT_ModalMenuArrayPointerToStackTop list.
         * Registers Meta::Destructor_MenuModal_PauseMenu with atexit.
         */
        void __cdecl Constructor_MenuModal_PauseMenu();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_VideoOptions
         * (MMT_VIDEO_OPTIONS): centred (x = y = -1), size 500x357 (rounded up to multiples of 24 when activated),
         * style flags 0x200, colour field COL_WHITE (raw 16-bit colour value), render function
         * MenuModalRenderFunction_VideoOptions, menu Menu_VideoOptions; the constructor also pushes it onto the
         * DAT_ModalMenuArrayPointerToStackTop list. Registers Meta::Destructor_MenuModal_VideoOptions with atexit.
         */
        void __cdecl Constructor_MenuModal_VideoOptions();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_SoundOptions
         * (MMT_SOUND_OPTIONS): centred (x = y = -1), size 500x357 (rounded up to multiples of 24 when activated),
         * style flags 0x200, colour field COL_WHITE (raw 16-bit colour value), render function
         * MenuModalRenderFunction_SoundOptions, menu Menu_SoundOptions; the constructor also pushes it onto the
         * DAT_ModalMenuArrayPointerToStackTop list. Registers Meta::Destructor_MenuModal_SoundOptions with atexit.
         */
        void __cdecl Constructor_MenuModal_SoundOptions();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_NetworkOptions
         * (MMT_NETWORK_OPTIONS): centred (x = y = -1), size 500x357 (rounded up to multiples of 24 when activated),
         * style flags 0x200, colour field COL_WHITE (raw 16-bit colour value), render function
         * MenuModalRenderFunction_NetworkOptions, menu Menu_NetworkOptions; the constructor also pushes it onto the
         * DAT_ModalMenuArrayPointerToStackTop list. Registers Meta::Destructor_MenuModal_NetworkOptions with
         * atexit.
         */
        void __cdecl Constructor_MenuModal_NetworkOptions();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_LoadMap (MMT_LOAD_MAP): centred
         * (x = y = -1), size 700x397 (rounded up to multiples of 24 when activated), style flags 0x200, colour
         * field COL_WHITE (raw 16-bit colour value), render function MenuModalRenderFunction_LoadMap, menu
         * Menu_LoadMap; the constructor also pushes it onto the DAT_ModalMenuArrayPointerToStackTop list. Registers
         * Meta::Destructor_MenuModal_LoadMap with atexit.
         */
        void __cdecl Constructor_MenuModal_LoadMap();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_SaveMap (MMT_SAVE_MAP): centred
         * (x = y = -1), size 700x397 (rounded up to multiples of 24 when activated), style flags 0x200, colour
         * field COL_WHITE (raw 16-bit colour value), render function MenuModalRenderFunction_SaveMap, menu
         * Menu_SaveMap; the constructor also pushes it onto the DAT_ModalMenuArrayPointerToStackTop list. Registers
         * Meta::Destructor_MenuModal_SaveMap with atexit.
         */
        void __cdecl Constructor_MenuModal_SaveMap();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_YesNoDialog (MMT_YES_NO_DIALOG):
         * centred (x = y = -1), size 450x150 (rounded up to multiples of 24 when activated), style flags 0x200,
         * colour field COL_WHITE (raw 16-bit colour value), render function MenuModalRenderFunction_YesNoDialog,
         * menu Menu_YesNoDialog; the constructor also pushes it onto the DAT_ModalMenuArrayPointerToStackTop list.
         * Registers Meta::Destructor_MenuModal_YesNoDialog with atexit.
         */
        void __cdecl Constructor_MenuModal_YesNoDialog();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_QuitDialog (MMT_QUIT_DIALOG):
         * centred (x = y = -1), size 500x150 (rounded up to multiples of 24 when activated), style flags 0x200,
         * colour field COL_WHITE (raw 16-bit colour value), render function MenuModalRenderFunction_YesNoDialog,
         * menu Menu_QuitDialog; the constructor also pushes it onto the DAT_ModalMenuArrayPointerToStackTop list.
         * Registers Meta::Destructor_MenuModal_QuitDialog with atexit.
         */
        void __cdecl Constructor_MenuModal_QuitDialog();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_PauseMenuOptions
         * (MMT_PAUSE_MENU_OPTIONS): centred (x = y = -1), size 500x357 (rounded up to multiples of 24 when
         * activated), style flags 0x200, colour field COL_WHITE (raw 16-bit colour value), render function
         * MenuModalRenderFunction_OptionsMenu, menu Menu_PauseMenuOptions; the constructor also pushes it onto the
         * DAT_ModalMenuArrayPointerToStackTop list. Registers Meta::Destructor_MenuModal_PauseMenuOptions with
         * atexit.
         */
        void __cdecl Constructor_MenuModal_PauseMenuOptions();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_MainMenuOptions
         * (MMT_MAIN_MENU_OPTIONS): centred (x = y = -1), size 500x357 (rounded up to multiples of 24 when
         * activated), style flags 0x200, colour field COL_WHITE (raw 16-bit colour value), render function
         * MenuModalRenderFunction_OptionsMenu, menu Destructor_MenuModal_MainMenuOptions; the constructor also
         * pushes it onto the DAT_ModalMenuArrayPointerToStackTop list. Registers
         * Meta::Destructor_MenuModal_MainMenuOptions with atexit.
         */
        void __cdecl Constructor_MenuModal_MainMenuOptions();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_GameplayOptions
         * (MMT_GAMEPLAY_OPTIONS): centred (x = y = -1), size 500x357 (rounded up to multiples of 24 when
         * activated), style flags 0x200, colour field COL_WHITE (raw 16-bit colour value), render function
         * MenuModalRenderFunction_GameplayOptions, menu Menu_GameplayOptions; the constructor also pushes it onto
         * the DAT_ModalMenuArrayPointerToStackTop list. Registers Meta::Destructor_MenuModal_GameplayOptions with
         * atexit.
         */
        void __cdecl Constructor_MenuModal_GameplayOptions();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_IdentityOptions
         * (MMT_IDENTITY_OPTIONS): centred (x = y = -1), size 500x400 (rounded up to multiples of 24 when
         * activated), style flags 0x200, colour field COL_WHITE (raw 16-bit colour value), render function
         * MenuModalRenderFunction_IdentityOptions, menu Menu_IdentityOptions; the constructor also pushes it onto
         * the DAT_ModalMenuArrayPointerToStackTop list. Registers Meta::Destructor_MenuModal_IdentityOptions with
         * atexit.
         */
        void __cdecl Constructor_MenuModal_IdentityOptions();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_EnterTitleOnGameStart
         * (MMT_ENTER_TITLE_ON_GAME_START): x=-1 (centred), y=100, size 500x200 (rounded up to multiples of 24 when
         * activated), style flags 0x200, colour field COL_WHITE (raw 16-bit colour value), render function
         * MenuModalRenderFunction_EnterTitleOnGameStart, menu Menu_EnterTitleOnGameStart; the constructor also
         * pushes it onto the DAT_ModalMenuArrayPointerToStackTop list. Registers
         * Meta::Destructor_MenuModal_EnterTitleOnGameStart with atexit. Non-centred coordinates are offsets inside
         * the centred 800x600 area.
         */
        void __cdecl Constructor_MenuModal_EnterTitleOnGameStart();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_ProgressBarBox
         * (MMT_PROGRESS_BAR_BOX): x=-1 (centred), y=50, size 400x100 (rounded up to multiples of 24 when
         * activated), style flags 0x200, colour field COL_WHITE (raw 16-bit colour value), render function
         * MenuModalRenderFunction_ProgressBarBox, menu Menu_ProgressBarBox; the constructor also pushes it onto the
         * DAT_ModalMenuArrayPointerToStackTop list. Registers Meta::Destructor_MenuModal_ProgressBarBox with
         * atexit. Non-centred coordinates are offsets inside the centred 800x600 area.
         */
        void __cdecl Constructor_MenuModal_ProgressBarBox();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_BuildingHelpText
         * (MMT_BUILDING_HELP_TEXT): centred (x = y = -1), size 704x336 (rounded up to multiples of 24 when
         * activated), style flags 0x20, colour field COL_BLACK (raw 16-bit colour value), render function
         * MenuModalRenderFunction_TextEditor, menu Menu_BuildingHelpText; the constructor also pushes it onto the
         * DAT_ModalMenuArrayPointerToStackTop list. Registers Meta::Destructor_MenuModal_BuildingHelpText with
         * atexit.
         */
        void __cdecl Constructor_MenuModal_BuildingHelpText();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_InGameHelpText
         * (MMT_IN_GAME_HELP_TEXT): centred (x = y = -1), size 768x432 (rounded up to multiples of 24 when
         * activated), style flags 0x20, colour field COL_BLACK (raw 16-bit colour value), render function
         * MenuModalRenderFunction_TextEditor, menu Menu_InGameHelpText; the constructor also pushes it onto the
         * DAT_ModalMenuArrayPointerToStackTop list. Registers Meta::Destructor_MenuModal_InGameHelpText with
         * atexit.
         */
        void __cdecl Constructor_MenuModal_InGameHelpText();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_MapDescriptionEditor
         * (MMT_MAP_DESCRIPTION_EDITOR): centred (x = y = -1), size 400x230 (rounded up to multiples of 24 when
         * activated), style flags 0x20, colour field COL_BLACK (raw 16-bit colour value), render function
         * MenuModalRenderFunction_TextEditor, menu Menu_MapDescriptionEditor; the constructor also pushes it onto
         * the DAT_ModalMenuArrayPointerToStackTop list. Registers Meta::Destructor_MenuModal_MapDescriptionEditor
         * with atexit.
         */
        void __cdecl Constructor_MenuModal_MapDescriptionEditor();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_ChooseNetworkServiceProvider
         * (MMT_CHOOSE_NETWORK_SERVICE_PROVIDER): x=150, y=80, size 500x408 (rounded up to multiples of 24 when
         * activated), style flags 0x200, colour field COL_WHITE (raw 16-bit colour value), render function
         * MenuModalRenderFunction_ChooseNetworkServiceProvider, menu Menu_ChooseNetworkServiceProvider; the
         * constructor also pushes it onto the DAT_ModalMenuArrayPointerToStackTop list. Registers
         * Meta::Destructor_MenuModal_ChooseNetworkServiceProvider with atexit. Non-centred coordinates are offsets
         * inside the centred 800x600 area.
         */
        void __cdecl Constructor_MenuModal_ChooseNetworkServiceProvider();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_FindingNetworkSessions
         * (MMT_FINDING_NETWORK_SESSIONS): centred (x = y = -1), size 500x360 (rounded up to multiples of 24 when
         * activated), style flags 0x200, colour field COL_WHITE (raw 16-bit colour value), render function
         * MenuModalRenderFunction_FindingNetworkSessions, menu Menu_FindingNetworkSessions; the constructor also
         * pushes it onto the DAT_ModalMenuArrayPointerToStackTop list. Registers
         * Meta::Destructor_MenuModal_FindingNetworkSessions with atexit.
         */
        void __cdecl Constructor_MenuModal_FindingNetworkSessions();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_DisplayAiLordMessage
         * (MMT_DISPLAY_AI_LORD_MESSAGE): x=0, y=0, size 0x0, style flags 0x40, colour field COL_WHITE (raw 16-bit
         * colour value), render function MenuModalRenderFunction_DisplayAiLordMessage, menu
         * Menu_DisplayAiLordMessage; the constructor also pushes it onto the DAT_ModalMenuArrayPointerToStackTop
         * list. Registers Meta::Destructor_MenuModal_DisplayAiLordMessage with atexit. Non-centred coordinates are
         * offsets inside the centred 800x600 area.
         */
        void __cdecl Constructor_MenuModal_DisplayAiLordMessage();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_WaitingForHost
         * (MMT_WAITING_FOR_HOST): centred (x = y = -1), size 500x100 (rounded up to multiples of 24 when
         * activated), style flags 0x200, colour field COL_WHITE (raw 16-bit colour value), render function
         * MenuModalRenderFunction_WaitingForHost, menu Menu_WaitingForHost; the constructor also pushes it onto the
         * DAT_ModalMenuArrayPointerToStackTop list. Registers Meta::Destructor_MenuModal_WaitingForHost with
         * atexit.
         */
        void __cdecl Constructor_MenuModal_WaitingForHost();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_UnusedSetName
         * (MMT_UNUSED_SET_NAME): centred (x = y = -1), size 500x150, style flags 0x10, colour field COL_WHITE (raw
         * 16-bit colour value), render function MenuModalRenderFunction_UnusedSetName, menu Menu_UnusedSetName; the
         * constructor also pushes it onto the DAT_ModalMenuArrayPointerToStackTop list. Registers
         * Meta::Destructor_MenuModal_UnusedSetName with atexit.
         */
        void __cdecl Constructor_MenuModal_UnusedSetName();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_UnusedChooseMessageBox
         * (MMT_UNUSED_CHOOSE_MESSAGE_BOX): centred (x = y = -1), size 663x440 (rounded up to multiples of 24 when
         * activated), style flags 0x200, colour field 6 (palette index -> COL_DARK_CYAN_GREY), render function
         * MenuModalRenderFunction_UnusedChooseMessageBox, menu Menu_UnusedChooseMessageBox; the constructor also
         * pushes it onto the DAT_ModalMenuArrayPointerToStackTop list. Registers
         * Meta::Destructor_MenuModal_UnusedChooseMessageBox with atexit.
         */
        void __cdecl Constructor_MenuModal_UnusedChooseMessageBox();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_TraderSettings
         * (MMT_TRADER_SETTINGS): centred (x = y = -1), size 600x390 (rounded up to multiples of 24 when activated),
         * style flags 0x200, colour field 6 (palette index -> COL_DARK_CYAN_GREY), render function
         * MenuModalRenderFunction_TraderSettings, menu Menu_TraderSettings; the constructor also pushes it onto the
         * DAT_ModalMenuArrayPointerToStackTop list. Registers Meta::Destructor_MenuModal_TraderSettings with
         * atexit.
         */
        void __cdecl Constructor_MenuModal_TraderSettings();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_StartGoods (MMT_START_GOODS):
         * centred (x = y = -1), size 600x390 (rounded up to multiples of 24 when activated), style flags 0x200,
         * colour field 6 (palette index -> COL_DARK_CYAN_GREY), render function MenuModalRenderFunction_StartGoods,
         * menu Menu_StartGoods; the constructor also pushes it onto the DAT_ModalMenuArrayPointerToStackTop list.
         * Registers Meta::Destructor_MenuModal_StartGoods with atexit.
         */
        void __cdecl Constructor_MenuModal_StartGoods();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_UnusedSiegeAttackingForceUnk
         * (MMT_SIEGE_ATTACKING_FORCE): centred (x = y = -1), size 600x440 (rounded up to multiples of 24
         * when activated), style flags 0x200, colour field 6 (palette index -> COL_DARK_CYAN_GREY), render function
         * MenuModalRenderFunction_UnusedSiegeAttackingForceUnk, menu Menu_UnusedSiegeAttackingForceUnk; the
         * constructor also pushes it onto the DAT_ModalMenuArrayPointerToStackTop list. Registers
         * Meta::Destructor_MenuModal_UnusedSiegeAttackingForceUnk with atexit.
         */
        void __cdecl Constructor_MenuModal_SiegeAttackingForce();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_NewInvasion (MMT_NEW_INVASION):
         * centred (x = y = -1), size 700x440 (rounded up to multiples of 24 when activated), style flags 0x200,
         * colour field 6 (palette index -> COL_DARK_CYAN_GREY), render function
         * MenuModalRenderFunction_CreateOrTriggerInvasion, menu Menu_NewInvasion; the constructor also pushes it
         * onto the DAT_ModalMenuArrayPointerToStackTop list. Registers Meta::Destructor_MenuModal_NewInvasion with
         * atexit.
         */
        void __cdecl Constructor_MenuModal_NewInvasion();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_UnusedCreateTimedMessageEvent
         * (MMT_UNUSED_CREATE_TIMED_MESSAGE_EVENT): centred (x = y = -1), size 700x510 (rounded up to multiples of
         * 24 when activated), style flags 0x200, colour field 6 (palette index -> COL_DARK_CYAN_GREY), render
         * function MenuModalRenderFunction_UnusedCreateTimedMessageEvent, menu Menu_UnusedCreateTimedMessageEvent;
         * the constructor also pushes it onto the DAT_ModalMenuArrayPointerToStackTop list. Registers
         * Meta::Destructor_MenuModal_UnusedCreateTimedMessageEvent with atexit.
         */
        void __cdecl Constructor_MenuModal_UnusedCreateTimedMessageEvent();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_NewEvent (MMT_NEW_EVENT):
         * centred (x = y = -1), size 600x470 (rounded up to multiples of 24 when activated), style flags 0x200,
         * colour field 6 (palette index -> COL_DARK_CYAN_GREY), render function MenuModalRenderFunction_NewEvent,
         * menu Menu_NewEvent; the constructor also pushes it onto the DAT_ModalMenuArrayPointerToStackTop list.
         * Registers Meta::Destructor_MenuModal_NewEvent with atexit.
         */
        void __cdecl Constructor_MenuModal_NewEvent();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_NewEventCondition
         * (MMT_NEW_EVENT_CONDITION): centred (x = y = -1), size 700x540 (rounded up to multiples of 24 when
         * activated), style flags 0x200, colour field 6 (palette index -> COL_DARK_CYAN_GREY), render function
         * MenuModalRenderFunction_NewEventCondition, menu Menu_NewEventCondition; the constructor also pushes it
         * onto the DAT_ModalMenuArrayPointerToStackTop list. Registers Meta::Destructor_MenuModal_NewEventCondition
         * with atexit.
         */
        void __cdecl Constructor_MenuModal_NewEventCondition();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_NewEventAction
         * (MMT_NEW_EVENT_ACTION): centred (x = y = -1), size 760x540 (rounded up to multiples of 24 when
         * activated), style flags 0x200, colour field 6 (palette index -> COL_DARK_CYAN_GREY), render function
         * MenuModalRenderFunction_NewEventAction, menu Menu_NewEventAction; the constructor also pushes it onto the
         * DAT_ModalMenuArrayPointerToStackTop list. Registers Meta::Destructor_MenuModal_NewEventAction with
         * atexit.
         */
        void __cdecl Constructor_MenuModal_NewEventAction();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_UnusedCreateMessageEvent
         * (MMT_UNUSED_CREATE_MESSAGE_EVENT): centred (x = y = -1), size 700x460 (rounded up to multiples of 24 when
         * activated), style flags 0x200, colour field 6 (palette index -> COL_DARK_CYAN_GREY), render function
         * MenuModalRenderFunction_UnusedCreateMessageEvent, menu Menu_UnusedCreateMessageEvent; the constructor
         * also pushes it onto the DAT_ModalMenuArrayPointerToStackTop list. Registers
         * Meta::Destructor_MenuModal_UnusedCreateMessageEvent with atexit.
         */
        void __cdecl Constructor_MenuModal_UnusedCreateMessageEvent();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_BuildingAvailability
         * (MMT_BUILDING_AVAILABILITY): centred (x = y = -1), size 700x540 (rounded up to multiples of 24 when
         * activated), style flags 0x200, colour field 6 (palette index -> COL_DARK_CYAN_GREY), render function
         * MenuModalRenderFunction_BuildingAvailability, menu Menu_BuildingAvailability; the constructor also pushes
         * it onto the DAT_ModalMenuArrayPointerToStackTop list. Registers
         * Meta::Destructor_MenuModal_BuildingAvailability with atexit.
         */
        void __cdecl Constructor_MenuModal_BuildingAvailability();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_DisableEuroTroops
         * (MMT_DISABLE_EURO_TROOPS): centred (x = y = -1), size 400x240 (rounded up to multiples of 24 when
         * activated), style flags 0x200, colour field 6 (palette index -> COL_DARK_CYAN_GREY), render function
         * MenuModalRenderFunction_DisableTroops, menu Menu_DisableEuroTroops; the constructor also pushes it onto
         * the DAT_ModalMenuArrayPointerToStackTop list. Registers Meta::Destructor_MenuModal_DisableEuroTroops with
         * atexit.
         */
        void __cdecl Constructor_MenuModal_DisableEuroTroops();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_DisableArabTroops
         * (MMT_DISABLE_ARAB_TROOPS): centred (x = y = -1), size 400x240 (rounded up to multiples of 24 when
         * activated), style flags 0x200, colour field 6 (palette index -> COL_DARK_CYAN_GREY), render function
         * MenuModalRenderFunction_DisableTroops, menu Menu_DisableArabTroops; the constructor also pushes it onto
         * the DAT_ModalMenuArrayPointerToStackTop list. Registers Meta::Destructor_MenuModal_DisableArabTroops with
         * atexit.
         */
        void __cdecl Constructor_MenuModal_DisableArabTroops();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_DisableWeapon
         * (MMT_DISABLE_WEAPON): centred (x = y = -1), size 400x240 (rounded up to multiples of 24 when activated),
         * style flags 0x200, colour field 6 (palette index -> COL_DARK_CYAN_GREY), render function
         * MenuModalRenderFunction_DisableWeapon, menu Menu_DisableWeapon; the constructor also pushes it onto the
         * DAT_ModalMenuArrayPointerToStackTop list. Registers Meta::Destructor_MenuModal_DisableWeapon with atexit.
         */
        void __cdecl Constructor_MenuModal_DisableWeapon();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_TutorialBox (MMT_TUTORIAL_BOX):
         * x=-1 (centred), y=20, size 600x150, style flags 0x840, colour field COL_WHITE (raw 16-bit colour value),
         * render function MenuModalRenderFunction_TutorialBox_Thunk, menu Menu_TutorialBox; the constructor also
         * pushes it onto the DAT_ModalMenuArrayPointerToStackTop list. Registers
         * Meta::Destructor_MenuModal_TutorialBox with atexit. Non-centred coordinates are offsets inside the
         * centred 800x600 area.
         */
        void __cdecl Constructor_MenuModal_TutorialBox();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_TutorialBoxWithLeave
         * (MMT_TUTORIAL_BOX_WITH_LEAVE): x=-1 (centred), y=20, size 600x150, style flags 0x840, colour field
         * COL_WHITE (raw 16-bit colour value), render function MenuModalRenderFunction_TutorialBox_Thunk, menu
         * Menu_TutorialBoxWithLeave; the constructor also pushes it onto the DAT_ModalMenuArrayPointerToStackTop
         * list. Registers Meta::Destructor_MenuModal_TutorialBoxWithLeave with atexit. Non-centred coordinates are
         * offsets inside the centred 800x600 area.
         */
        void __cdecl Constructor_MenuModal_TutorialBoxWithLeave();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_DisplayScenarioHelpText
         * (MMT_DISPLAY_SCENARIO_HELP_TEXT): x=-1 (centred), y=30, size 696x408 (rounded up to multiples of 24 when
         * activated), style flags 0x1200, colour field COL_BLACK (raw 16-bit colour value), render function
         * MenuModalRenderFunction_TextEditor, menu Menu_DisplayScenarioHelpText; the constructor also pushes it
         * onto the DAT_ModalMenuArrayPointerToStackTop list. Registers
         * Meta::Destructor_MenuModal_DisplayScenarioHelpText with atexit. Non-centred coordinates are offsets
         * inside the centred 800x600 area.
         */
        void __cdecl Constructor_MenuModal_DisplayScenarioHelpText();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_Chat (MMT_CHAT): x=16, y=16,
         * size 768x224 (rounded up to multiples of 24 when activated), style flags 0x200, colour field COL_BLACK
         * (raw 16-bit colour value), render function MenuModalRenderFunction_Chat, menu Menu_Chat; the constructor
         * also pushes it onto the DAT_ModalMenuArrayPointerToStackTop list. Registers
         * Meta::Destructor_MenuModal_Chat with atexit. Non-centred coordinates are offsets inside the centred
         * 800x600 area.
         */
        void __cdecl Constructor_MenuModal_Chat();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_CreditsScroll
         * (MMT_CREDITS_SCROLL): x=400, y=0, size 400x600, style flags 0x40, colour field COL_BLACK (raw 16-bit
         * colour value), render function MenuModalRenderFunction_CreditsScroll, menu Menu_Credits; the constructor
         * also pushes it onto the DAT_ModalMenuArrayPointerToStackTop list. Registers
         * Meta::Destructor_MenuModal_CreditsScroll with atexit. Non-centred coordinates are offsets inside the
         * centred 800x600 area.
         */
        void __cdecl Constructor_MenuModal_CreditsScroll();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_EditorMapTypeQuickChange
         * (MMT_EDITOR_MAP_TYPE_QUICK_CHANGE): centred (x = y = -1), size 400x300 (rounded up to multiples of 24
         * when activated), style flags 0x200, colour field COL_BLACK (raw 16-bit colour value), render function
         * DoNothing, menu Menu_EditorMapTypeQuickChange; the constructor also pushes it onto the
         * DAT_ModalMenuArrayPointerToStackTop list. Registers Meta::Destructor_MenuModal_EditorMapTypeQuickChange
         * with atexit.
         */
        void __cdecl Constructor_MenuModal_EditorMapTypeQuickChange();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_SkirmishConnectionOptions
         * (MMT_SKIRMISH_CONNECTION_OPTIONS): centred (x = y = -1), size 408x200 (rounded up to multiples of 24 when
         * activated), style flags 0x200, colour field COL_BLACK (raw 16-bit colour value), render function
         * MenuModalRenderFunction_SkirmishConnectionOptions, menu Menu_SkirmishConnectionOptions; the constructor
         * also pushes it onto the DAT_ModalMenuArrayPointerToStackTop list. Registers
         * Meta::Destructor_MenuModal_SkirmishConnectionOptions with atexit.
         */
        void __cdecl Constructor_MenuModal_SkirmishConnectionOptions();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_SkirmishPlayOptions
         * (MMT_SKIRMISH_PLAY_OPTIONS): centred (x = y = -1), size 408x370 (rounded up to multiples of 24 when
         * activated), style flags 0x200, colour field COL_BLACK (raw 16-bit colour value), render function
         * MenuModalRenderFunction_SkirmishPlayOptions, menu Menu_SkirmishPlayOptions; the constructor also pushes
         * it onto the DAT_ModalMenuArrayPointerToStackTop list. Registers
         * Meta::Destructor_MenuModal_SkirmishPlayOptions with atexit.
         */
        void __cdecl Constructor_MenuModal_SkirmishPlayOptions();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_OnlineQuitGame
         * (MMT_ONLINE_QUIT_GAME): centred (x = y = -1), size 400x235 (rounded up to multiples of 24 when
         * activated), style flags 0x200, colour field COL_WHITE (raw 16-bit colour value), render function
         * MenuModalRenderFunction_OnlineQuitGame, menu Menu_OnlineQuitGame; the constructor also pushes it onto the
         * DAT_ModalMenuArrayPointerToStackTop list. Registers Meta::Destructor_MenuModal_OnlineQuitGame with
         * atexit.
         */
        void __cdecl Constructor_MenuModal_OnlineQuitGame();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_OnlineVoteQuitGame
         * (MMT_ONLINE_VOTE_QUIT_GAME): x=-1 (centred), y=10, size 400x200 (rounded up to multiples of 24 when
         * activated), style flags 0x200, colour field COL_WHITE (raw 16-bit colour value), render function
         * MenuModalRenderFunction_OnlineVoteQuitGame, menu Menu_OnlineVoteQuitGame; the constructor also pushes it
         * onto the DAT_ModalMenuArrayPointerToStackTop list. Registers
         * Meta::Destructor_MenuModal_OnlineVoteQuitGame with atexit. Non-centred coordinates are offsets inside the
         * centred 800x600 area.
         */
        void __cdecl Constructor_MenuModal_OnlineVoteQuitGame();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_TriggerInvasion
         * (MMT_CREATE_OR_TRIGGER_INVASION): centred (x = y = -1), size 700x440 (rounded up to multiples of 24 when
         * activated), style flags 0x200, colour field 6 (palette index -> COL_DARK_CYAN_GREY), render function
         * MenuModalRenderFunction_CreateOrTriggerInvasion, menu Menu_TriggerInvasion; the constructor also pushes
         * it onto the DAT_ModalMenuArrayPointerToStackTop list. Registers
         * Meta::Destructor_MenuModal_TriggerInvasion with atexit.
         */
        void __cdecl Constructor_MenuModal_TriggerInvasion();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_TriggerEvent
         * (MMT_TRIGGER_EVENT): centred (x = y = -1), size 408x442 (rounded up to multiples of 24 when activated),
         * style flags 0x200, colour field 6 (palette index -> COL_DARK_CYAN_GREY), render function
         * MenuModalRenderFunction_TriggerEvent, menu Menu_TriggerEvent; the constructor also pushes it onto the
         * DAT_ModalMenuArrayPointerToStackTop list. Registers Meta::Destructor_MenuModal_TriggerEvent with atexit.
         */
        void __cdecl Constructor_MenuModal_TriggerEvent();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_TriggerEventOrInvasion
         * (MMT_TRIGGER_EVENT_OR_INVASION): centred (x = y = -1), size 408x144 (rounded up to multiples of 24 when
         * activated), style flags 0x200, colour field 6 (palette index -> COL_DARK_CYAN_GREY), render function
         * DoNothing, menu Menu_TriggerEventOrInvasion; the constructor also pushes it onto the
         * DAT_ModalMenuArrayPointerToStackTop list. Registers Meta::Destructor_MenuModal_TriggerEventOrInvasion
         * with atexit.
         */
        void __cdecl Constructor_MenuModal_TriggerEventOrInvasion();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_TriggerEventSlider
         * (MMT_TRIGGER_EVENT_SLIDER): centred (x = y = -1), size 408x168 (rounded up to multiples of 24 when
         * activated), style flags 0x200, colour field 6 (palette index -> COL_DARK_CYAN_GREY), render function
         * MenuModalRenderFunction_TriggerEventSlider, menu Menu_TriggerEventSlider; the constructor also pushes it
         * onto the DAT_ModalMenuArrayPointerToStackTop list. Registers
         * Meta::Destructor_MenuModal_TriggerEventSlider with atexit.
         */
        void __cdecl Constructor_MenuModal_TriggerEventSlider();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_SendMapTo (MMT_SEND_MAP_TO):
         * x=-1 (centred), y=50, size 504x348 (rounded up to multiples of 24 when activated), style flags 0x200,
         * colour field 6 (palette index -> COL_DARK_CYAN_GREY), render function MenuModalRenderFunction_SendMapTo,
         * menu Menu_SendMapTo; the constructor also pushes it onto the DAT_ModalMenuArrayPointerToStackTop list.
         * Registers Meta::Destructor_MenuModal_SendMapTo with atexit. Non-centred coordinates are offsets inside
         * the centred 800x600 area.
         */
        void __cdecl Constructor_MenuModal_SendMapTo();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_ReceiveMapFrom
         * (MMT_RECEIVE_MAP_FROM): centred (x = y = -1), size 408x200 (rounded up to multiples of 24 when
         * activated), style flags 0x200, colour field 6 (palette index -> COL_DARK_CYAN_GREY), render function
         * MenuModalRenderFunction_ReceiveMapFrom, menu Menu_ReceiveMapFrom; the constructor also pushes it onto the
         * DAT_ModalMenuArrayPointerToStackTop list. Registers Meta::Destructor_MenuModal_ReceiveMapFromUnk with
         * atexit.
         */
        void __cdecl Constructor_MenuModal_ReceiveMapFrom();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_BasicAiLordSelect
         * (MMT_BASIC_AI_LORD_SELECT): x=200, y=200, size 648x288, style flags 0x1040, colour field COL_WHITE (raw
         * 16-bit colour value), render function MenuModalRenderFunction_AiLordSelect, menu Menu_BasicAiLordSelect;
         * the constructor also pushes it onto the DAT_ModalMenuArrayPointerToStackTop list. Registers
         * Meta::Destructor_MenuModal_BasicAiLordSelect with atexit. Non-centred coordinates are offsets inside the
         * centred 800x600 area.
         */
        void __cdecl Constructor_MenuModal_BasicAiLordSelect();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_ExtendedAiLordSelect
         * (MMT_EXTENDED_AI_LORD_SELECT): x=200, y=200, size 648x364, style flags 0x1040, colour field COL_WHITE
         * (raw 16-bit colour value), render function MenuModalRenderFunction_AiLordSelect, menu
         * Menu_ExtendedAiLordSelect; the constructor also pushes it onto the DAT_ModalMenuArrayPointerToStackTop
         * list. Registers Meta::Destructor_MenuModal_ExtendedAiLordSelect with atexit. Non-centred coordinates are
         * offsets inside the centred 800x600 area.
         */
        void __cdecl Constructor_MenuModal_ExtendedAiLordSelect();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_Roundtable (MMT_ROUNDTABLE):
         * x=4, y=4, size 792x432 (rounded up to multiples of 24 when activated), style flags 0x1200, colour field
         * COL_WHITE (raw 16-bit colour value), render function MenuModalRenderFunction_Roundtable, menu
         * Menu_Roundtable; the constructor also pushes it onto the DAT_ModalMenuArrayPointerToStackTop list.
         * Registers Meta::Destructor_MenuModal_Roundtable with atexit. Non-centred coordinates are offsets inside
         * the centred 800x600 area.
         */
        void __cdecl Constructor_MenuModal_Roundtable();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_Allies (MMT_ALLIES): centred (x
         * = y = -1), size 696x384 (rounded up to multiples of 24 when activated), style flags 0x200, colour field
         * COL_BLACK (raw 16-bit colour value), render function MenuModalRenderFunction_Allies, menu Menu_Allies;
         * the constructor also pushes it onto the DAT_ModalMenuArrayPointerToStackTop list. Registers
         * Meta::Destructor_MenuModal_Allies with atexit.
         */
        void __cdecl Constructor_MenuModal_Allies();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_AlliesOrder (MMT_ALLIES_ORDER):
         * centred (x = y = -1), size 768x240 (rounded up to multiples of 24 when activated), style flags 0x200,
         * colour field COL_BLACK (raw 16-bit colour value), render function MenuModalRenderFunction_AlliesOrder,
         * menu Menu_AlliesOrder; the constructor also pushes it onto the DAT_ModalMenuArrayPointerToStackTop list.
         * Registers Meta::Destructor_MenuModal_AlliesOrder with atexit.
         */
        void __cdecl Constructor_MenuModal_AlliesOrder();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_AlliesRequestGoods
         * (MMT_ALLIES_REQUEST_GOODS): centred (x = y = -1), size 600x408 (rounded up to multiples of 24 when
         * activated), style flags 0x200, colour field COL_BLACK (raw 16-bit colour value), render function
         * MenuModalRenderFunction_AlliesRequestGoods, menu Menu_AlliesRequestGoods; the constructor also pushes it
         * onto the DAT_ModalMenuArrayPointerToStackTop list. Registers
         * Meta::Destructor_MenuModal_AlliesRequestGoods with atexit.
         */
        void __cdecl Constructor_MenuModal_AlliesRequestGoods();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_GreatestLord
         * (MMT_GREATEST_LORD): centred (x = y = -1), size 600x408 (rounded up to multiples of 24 when activated),
         * style flags 0x200, colour field COL_BLACK (raw 16-bit colour value), render function
         * MenuModalRenderFunction_GreatestLord, menu Menu_GreatestLord; the constructor also pushes it onto the
         * DAT_ModalMenuArrayPointerToStackTop list. Registers Meta::Destructor_MenuModal_GreatestLord with atexit.
         */
        void __cdecl Constructor_MenuModal_GreatestLord();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_AlliesSendGoods
         * (MMT_ALLIES_SEND_GOODS): centred (x = y = -1), size 600x408 (rounded up to multiples of 24 when
         * activated), style flags 0x200, colour field COL_WHITE (raw 16-bit colour value), render function
         * MenuModalRenderFunction_AlliesSendGoods, menu Menu_AlliesSendGoods; the constructor also pushes it onto
         * the DAT_ModalMenuArrayPointerToStackTop list. Registers Meta::Destructor_MenuModal_AlliesSendGoods with
         * atexit.
         */
        void __cdecl Constructor_MenuModal_AlliesSendGoods();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_ChooseRandomNumberOfEnemies
         * (MMT_CHOOSE_RANDOM_NUMBER_OF_ENEMIES): centred (x = y = -1), size 600x400 (rounded up to multiples of 24
         * when activated), style flags 0x200, colour field COL_WHITE (raw 16-bit colour value), render function
         * MenuModalRenderFunction_ChooseRandomNumberOfEnemies, menu Menu_ChooseRandomNumberOfEnemies; the
         * constructor also pushes it onto the DAT_ModalMenuArrayPointerToStackTop list. Registers
         * Meta::Destructor_MenuModal_ChooseRandomNumberOfEnemies with atexit.
         */
        void __cdecl Constructor_MenuModal_ChooseRandomNumberOfEnemies();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_DeleteGameRecord
         * (MMT_DELETE_GAME_RECORD): centred (x = y = -1), size 500x150 (rounded up to multiples of 24 when
         * activated), style flags 0x200, colour field COL_WHITE (raw 16-bit colour value), render function
         * MenuModalRenderFunctionMenuModal_DeleteGameRecord, menu Menu_DeleteGameRecord; the constructor also
         * pushes it onto the DAT_ModalMenuArrayPointerToStackTop list. Registers
         * Meta::Destructor_MenuModal_DeleteGameRecord with atexit.
         */
        void __cdecl Constructor_MenuModal_DeleteGameRecord();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_TacticalPowerBar
         * (MMT_TACTICAL_POWER_BAR): x=745, y=50, size 55x320, style flags 0x1000, colour field COL_WHITE (raw
         * 16-bit colour value), render function MenuModalRenderFunction_TacticalPowerBar, menu
         * Menu_TacticalPowerBar; the constructor also pushes it onto the DAT_ModalMenuArrayPointerToStackTop list.
         * Registers Meta::Destructor_MenuModal_TacticalPowerBar with atexit. Non-centred coordinates are offsets
         * inside the centred 800x600 area.
         */
        void __cdecl Constructor_MenuModal_TacticalPowerBar();

        /**
         * Static initializer: Constructor_MenuModal sets up global modal MenuModal_DebugDataAivStateUnk
         * (MMT_DEBUG_DATA_AIV_PLACEMENT): x=267, y=3, size 400x242, style flags 0xe, colour field COL_WHITE (raw
         * 16-bit colour value), render function MenuModalRenderFunction_DebugDataAivStateUnk, menu
         * Menu_DebugModals; the constructor also pushes it onto the DAT_ModalMenuArrayPointerToStackTop list.
         * Registers Meta::Destructor_MenuModal_DebugDataAivStateUnk with atexit. Non-centred coordinates are
         * offsets inside the centred 800x600 area.
         */
        void __cdecl Constructor_MenuModal_DebugDataAivPlacementSuccess();

        /**
         * Static initializer: constructs on-screen display element UnknownDisplayElement0 (element id OST_CHAT) at
         * (4,408), initial state 1, render function DoNothing, position modifier
         * DEPM_RESOLUTION_X|DEPM_TOWARDS_MID_Y (no atexit destructor).
         */
        void __cdecl CreateUnknownDisplayElement0();

        /**
         * Static initializer: constructs on-screen display element BottomLeftDateDisplayElement (element id
         * OST_DATE) at (4,424), initial state 0, render function RenderBottomLeftDateDisplayElement, position
         * modifier DEPM_RESOLUTION_X|DEPM_TOWARDS_MID_Y (no atexit destructor).
         */
        void __cdecl CreateBottomLeftDateDisplayElement();

        /**
         * Static initializer: constructs on-screen display element UnknownDisplayElement18 (element id 18) at
         * (200,4), initial state 1, render function DoNothing, position modifier
         * DEPM_RESOLUTION_X|DEPM_RESOLUTION_Y (no atexit destructor).
         */
        void __cdecl CreateUnknownDisplayElement18();

        /**
         * Static initializer: constructs on-screen display element InGameStartingGoodsCounterDisplayElement
         * (element id OST_STARTING_GOODS) at (4,4), initial state 1, render function
         * RenderStartingGoodDisplayElement, position modifier DEPM_RESOLUTION_X|DEPM_RESOLUTION_Y (no atexit
         * destructor).
         */
        void __cdecl CreateInGameStartingGoodsCounterDisplayElement();

        /**
         * Static initializer: constructs on-screen display element ConnectAndPathLinkageInfoTextDisplayElement
         * (element id 2) at (630,9), initial state 0, render function
         * RenderConnectAndPathLinkageInfoTextDisplayElement, position modifier DEPM_TOWARDS_MID_X|DEPM_RESOLUTION_Y
         * (no atexit destructor).
         */
        void __cdecl CreateConnectAndPathLinkageInfoTextDisplayElement();

        /**
         * Static initializer: constructs on-screen display element InGameChatDisplayElement (element id
         * OST_MULTI_CHAT) at (4,367), initial state 1, render function RenderInGameChatDisplayElement, position
         * modifier DEPM_RESOLUTION_X|DEPM_TOWARDS_MID_Y (no atexit destructor). The 'Unk' in the function name is
         * unnecessary: element id and render function confirm it is the multiplayer chat display.
         */
        void __cdecl CreateInGameChatDisplayElement();

        /**
         * Static initializer: constructs on-screen display element ResourceMissing1DisplayElement (element id
         * OST_FEEDBACK_1) at (10,403), initial state 0, render function RenderResourceMissing1DisplayElement,
         * position modifier DEPM_RESOLUTION_X|DEPM_TOWARDS_MID_Y (no atexit destructor).
         */
        void __cdecl CreateResourceMissing1DisplayElement();

        /**
         * Static initializer: constructs on-screen display element ResourceMissing2DisplayElement (element id
         * OST_FEEDBACK_2) at (10,367), initial state 0, render function RenderResourceMissing2DisplayElement,
         * position modifier DEPM_RESOLUTION_X|DEPM_TOWARDS_MID_Y (no atexit destructor).
         */
        void __cdecl CreateResourceMissing2DisplayElement();

        /**
         * Static initializer: constructs on-screen display element DebugNumbersDisplayElement (element id
         * OST_FRAMERATE) at (730,9), initial state 0, render function RenderDebugNumbersDisplayElement, position
         * modifier DEPM_TOWARDS_MID_X|DEPM_RESOLUTION_Y (no atexit destructor).
         */
        void __cdecl CreateDebugNumbersDisplayElement();

        /**
         * Static initializer: constructs on-screen display element UnknownDisplayElement7 (element id 7, which
         * Ghidra renders as the bogus flag combination OST_FRAMERATE|OST_DATE) at (700,9), initial state 0, render
         * function RenderUnknownDisplayElement7, position modifier DEPM_TOWARDS_MID_X|DEPM_RESOLUTION_Y (no atexit
         * destructor).
         */
        void __cdecl CreateAiRecomputeAttacksTimerDisplayElement();

        /**
         * Static initializer: constructs on-screen display element SomeMissionNumberUnkDisplayElement9 (element id
         * 9) at (290,225), initial state 0, render function RenderSomeMissionNumberUnkDisplayElement9, position
         * modifier DEPM_MAIN_MENU_X_Y (no atexit destructor).
         */
        void __cdecl CreateMissionNumberDisplayElement();

        /**
         * Static initializer: constructs on-screen display element NoTreeGrowthTextDisplayElement (element id 14)
         * at (200,34), initial state 0, render function RenderNoTreeGrowthTextDisplayElement, position modifier
         * DEPM_RESOLUTION_Y (no atexit destructor).
         */
        void __cdecl CreateNoTreeGrowthTextDisplayElement();

        /**
         * Static initializer: constructs on-screen display element InGameWinDefeatWindowDisplayElement (element id
         * OST_MP_GAME_OVER) at (400,240), initial state 0, render function
         * RenderInGameWinDefeatWindowDisplayElement, position modifier DEPM_MAIN_MENU_X_Y (no atexit destructor).
         */
        void __cdecl CreateInGameWinDefeatWindowDisplayElement();

        /**
         * Static initializer: constructs on-screen display element MissionWinDefeatBannerDisplayElement (element id
         * OST_MISSION_FINISHED) at (400,30), initial state 0, render function
         * RenderMissionWinDefeatBannerDisplayElement, position modifier DEPM_RESOLUTION_Y (no atexit destructor).
         */
        void __cdecl CreateMissionWinDefeatBannerDisplayElement();

        /**
         * Static initializer: constructs on-screen display element SomeMultiplayerInfoUnkDisplayElement19 (element
         * id OST_SPLIT_MESSAGE) at (400,10), initial state 0, render function
         * RenderSomeMultiplayerInfoUnkDisplayElement19, position modifier DEPM_RESOLUTION_Y (no atexit destructor).
         */
        void __cdecl CreateConnectionLostDisplayElement();

        /**
         * Static initializer: constructs on-screen display element KeepAndGranaryPlacementInfoDisplayElement
         * (element id OST_KEEP_MESSAGE) at (725,447), initial state 0, render function
         * RenderAndPlayKeepAndGranaryPlacementInfoDisplayElement, position modifier DEPM_TOWARDS_MID_Y (no atexit
         * destructor).
         */
        void __cdecl CreateKeepAndGranaryPlacementInfoDisplayElement();

        /**
         * Static initializer: constructs on-screen display element PlayerInfoOnHoverDisplayElement (element id
         * OST_WHO_OWNS) at (400,430), initial state 0, render function RenderPlayerInfoOnHoverDisplayElement,
         * position modifier DEPM_TOWARDS_MID_Y (no atexit destructor).
         */
        void __cdecl CreatePlayerInfoOnHoverDisplayElement();

        /**
         * Static initializer: constructs on-screen display element PlayerPingUnkDisplayElement22 (element id
         * OST_PINGS) at (660,40), initial state 0, render function RenderPlayerPingUnkDisplayElement22, position
         * modifier DEPM_TOWARDS_MID_X (no atexit destructor).
         */
        void __cdecl CreatePlayerPingDisplayElement();

        /**
         * Static initializer: constructs on-screen display element GamePausedTextDisplayElement (element id
         * OST_GAME_PAUSED) at (400,230), initial state 0, render function RenderGamePausedTextDisplayElement,
         * position modifier DEPM_MAIN_MENU_X_Y (no atexit destructor).
         */
        void __cdecl CreateGamePausedTextDisplayElement();

        /**
         * Static initializer: constructs on-screen display element GameSpeedTextDisplayElement (element id
         * OST_GAME_SPEED) at (770,9), initial state 0, render function RenderGameSpeedTextDisplayElement, position
         * modifier DEPM_MAIN_MENU_X_Y (no atexit destructor).
         */
        void __cdecl CreateGameSpeedTextDisplayElement();

        /**
         * Static initializer: constructs on-screen display element UnknownDisplayElement25 (element id
         * OST_KING_OF_THE_HILL) at (100,10), initial state 0, render function RenderUnknownDisplayElement25,
         * position modifier DEPM_RESOLUTION_Y (no atexit destructor).
         */
        void __cdecl CreateKingOfTheHillScoresDisplayElement();

        /**
         * Static initializer: constructs on-screen display element TimeUntilVictoryDisplayElement (element id
         * OST_WIN_TIMER) at (0,8), initial state 0, render function RenderTimeUntilVictoryDisplayElement, position
         * modifier DEPM_RESOLUTION_Y (no atexit destructor).
         */
        void __cdecl CreateTimeUntilVictoryDisplayElement();

        /**
         * Static initializer: constructs on-screen display element NoRushCountdownDisplayElement (element id
         * OST_MESSAGE_BAR) at (0,8), initial state 0, render function RenderNoRushCountdownDisplayElement, position
         * modifier DEPM_RESOLUTION_Y (no atexit destructor).
         */
        void __cdecl CreateNoRushCountdownDisplayElement();

        /**
         * Static initializer: constructs on-screen display element TimeUntilDefeatDisplayElement (element id
         * OST_TIMETODEFEAT) at (0,8), initial state 0, render function RenderTimeUntilDefeatDisplayElement,
         * position modifier DEPM_RESOLUTION_Y (no atexit destructor).
         */
        void __cdecl CreateTimeUntilDefeatDisplayElement();

        /**
         * Static initializer: constructs on-screen display element SomeMultiplayerInfoUnkDisplayElement28 (element
         * id OST_PING_ERROR) at (400,10), initial state 0, render function
         * RenderSomeMultiplayerInfoUnkDisplayElement28, position modifier DEPM_RESOLUTION_Y (no atexit destructor).
         */
        void __cdecl CreatePlayerNotRespondingDisplayElement();

        /**
         * Static initializer: constructs on-screen display element PeopleLeftToPlaceDisplayElement (element id
         * OST_PEOPLE_LEFT) at (400,10), initial state 0, render function RenderPeopleLeftToPlaceDisplayElement,
         * position modifier DEPM_RESOLUTION_Y (no atexit destructor).
         */
        void __cdecl CreatePeopleLeftToPlaceDisplayElement();

        /**
         * Static initializer for global UNK_UnknownClassLocation2 (0x024036F8): calls the trivial Constructor_Empty
         * (mov eax,ecx; ret - the decompiler drops the ECX=this load) and registers Meta::Destructor_0059d4d0 with
         * atexit, which only tail-calls DoNothing on the same object.
         */
        void __cdecl Constructor_UnknownClass1();

        /**
         * Static initializer: calls UI::Rendering::WindowAndDirectDraw::Constructor_WindowAndDirectDraw on global
         * DAT_WindowAndDirectDraw and registers Meta::Destructor_WindowAndDirectDraw with atexit.
         */
        void __cdecl Constructor_WindowAndDirectDraw();

        /**
         * Static initializer for global DAT_WindowInformation (0x01A27980): calls the trivial Constructor_Empty
         * (mov eax,ecx; ret - the decompiler drops the ECX=this load) and registers Meta::Destructor_0059d4f0 with
         * atexit, which only tail-calls DoNothing on the same object.
         */
        void __cdecl Constructor_WindowInformation();

        /**
         * Static initializer: calls Input::MouseState::Constructor_MouseState on global DAT_MouseState and
         * registers Meta::Destructor_0059d500 with atexit.
         */
        void __cdecl Constructor_MouseState();

        /**
         * Static initializer: calls Input::ModifierKeyState::Constructor_ModifierKeyState on global
         * DAT_ModifierKeyState and registers Meta::Destructor_0059d510 with atexit.
         */
        void __cdecl Constructor_ModifierKeyState();

        /**
         * Static initializer: calls UI::ScrollingHandler::Constructor_ScrollingHandler on global
         * DAT_ScrollingHandler and registers Meta::Destructor_ScrollingHandler with atexit.
         */
        void __cdecl Constructor_ScrollingHandler();

        /**
         * Static initializer: calls Input::InsertKeyState::Constructor_InsertKeyState on global DAT_InsertKeyState
         * and registers Meta::Destructor_InsertKeyState with atexit.
         */
        void __cdecl Constructor_InsertKeyState();

        /**
         * Static initializer for global DAT_PencilRenderCore (0x0191D720): calls the trivial Constructor_Empty (mov
         * eax,ecx; ret - the decompiler drops the ECX=this load) and registers Meta::Destructor_0059d540 with
         * atexit, which only tail-calls DoNothing on the same object.
         */
        void __cdecl Constructor_PencilRenderCoreObj();

        /**
         * Static initializer: calls Text::UserTextHandler::UserTextHandler on global DAT_UserTextHandlerState and
         * registers Meta::Destructor_0059d550 with atexit.
         */
        void __cdecl Constructor_UserTextHandler();

        /**
         * Static initializer for global DAT_TextManagerObject (0x02157578): calls the trivial Constructor_Empty
         * (mov eax,ecx; ret - the decompiler drops the ECX=this load) and registers Meta::Destructor_0059d560 with
         * atexit, which only tail-calls DoNothing on the same object.
         */
        void __cdecl Constructor_TextManagerObj();

        /**
         * Static initializer for global UNK_UnusedClass1Location (0x0234DBE0): calls the trivial Constructor_Empty
         * (mov eax,ecx; ret - the decompiler drops the ECX=this load) and registers Meta::Destructor_0059d570 with
         * atexit, which only tail-calls DoNothing on the same object.
         */
        void __cdecl Constructor_UnusedClass1Unk();

        /**
         * Static initializer: calls Random::RNG::Constructor_RNG on global SEC_RNG and registers
         * Meta::Destructor_0059d580 with atexit.
         */
        void __cdecl Constructor_RNGState();

        /**
         * Static initializer for global DAT_LowLevelMemory (0x0165272C): calls the trivial Constructor_Empty (mov
         * eax,ecx; ret - the decompiler drops the ECX=this load) and registers Meta::Destructor_0059d590 with
         * atexit, which only tail-calls DoNothing on the same object.
         */
        void __cdecl Constructor_LowLevelMemory();

        /**
         * Static initializer: calls Game::GameCore::Constructor_GameCore on global DAT_GameCore and registers
         * Meta::Destructor_GameCore with atexit.
         */
        void __cdecl Constructor_GameCore();

        /**
         * Static initializer: calls IO::ResourceManager::Constructor_ResourceManager on global DAT_ResourceManager
         * and registers Meta::Destructor_0059d5b0 with atexit.
         */
        void __cdecl Constructor_ResourceManager();

        /**
         * Static initializer: calls IO::BitMapState::Constructor_BitMapState on global DAT_BitMapState and
         * registers Meta::Destructor_0059d5c0 with atexit.
         */
        void __cdecl Constructor_BitMapState();

        /**
         * Static initializer for global DAT_DirectionAlgorithmState (0x00EE23BC): calls the trivial
         * Constructor_Empty (mov eax,ecx; ret - the decompiler drops the ECX=this load) and registers
         * Meta::Destructor_0059d5d0 with atexit, which only tail-calls DoNothing on the same object.
         */
        void __cdecl Constructor_DirectionAlgorithmState();

        /**
         * Static initializer: calls Util::Timing::Stopwatch::Constructor_Stopwatch on global DAT_GameLoopStopwatch
         * and registers Meta::Destructor_Stopwatch_Gameloop with atexit.
         */
        void __cdecl Constructor_Stopwatch_Gameloop();

        /**
         * Static initializer: calls Util::Timing::Stopwatch::Constructor_Stopwatch on global DAT_UnknownStopwatch
         * and registers Meta::Destructor_Stopwatch_Unknown with atexit.
         */
        void __cdecl Constructor_Stopwatch_AiRecomputeAttacks();

        /**
         * Static initializer: calls IO::FilePackager::Constructor_FilePackager on global FilePackagerObj and
         * registers Meta::Destructor_0059d600 with atexit.
         */
        void __cdecl Constructor_FilePackager();

        /**
         * Static initializer: calls IO::DecoderState::Constructor_DecoderState on global DAT_DecoderState and
         * registers Meta::Destructor_Decoder with atexit.
         */
        void __cdecl Constructor_DecoderState();

        /**
         * Static initializer: calls UI::Rendering::TextureRenderCore::Constructor_TextureRenderCore on
         * DAT_TextureRenderCoreObject with processedImageDataBufferSize = 68100000, gmAndGfxImageDataBufferSize =
         * 0x1167910 (18250000) and unknownMemSize = 0, then registers Meta::Destructor_TextureRenderingCore with
         * atexit.
         */
        void __cdecl Constructor_TextureRenderingCore();

        /**
         * Static initializer: calls Audio::SFX::SFXState::Constructor_SFXState on global DAT_SFXState and registers
         * Meta::Destructor_SFXState with atexit.
         */
        void __cdecl Constructor_SFXState();

        /**
         * Static initializer: calls UI::Rendering::AlphaAndButtonSurface::Constructor_AlphaAndButtonSurface on
         * global AlphaAndButtonSurfaceObj and registers Meta::Destructor_AlphaAndButtonSurface with atexit.
         */
        void __cdecl Constructor_AlphaAndButtonSurface();

        /**
         * Static initializer with no constructor call: only registers Meta::Destructor_0059d650 with atexit, which
         * tail-calls DoNothing on DAT_MenuHandlerState (0x00F2B390) - a trivially destructible global.
         */
        void __cdecl Constructor_Empty1();

        /**
         * Static initializer: calls Rendering::ViewportRenderState::Constructor_ViewportRenderState on global
         * DAT_ViewportRenderState and registers Meta::Destructor_0059d660 with atexit.
         */
        void __cdecl Constructor_ViewportRenderState();

        /**
         * Static initializer: calls UI::MinimapViewState::Constructor_MinimapViewState on global
         * DAT_MinimapViewState and registers Meta::Destructor_0059d670 with atexit.
         */
        void __cdecl Constructor_MiniMapView();

        /**
         * Static initializer: calls UI::MenuModalComposition::Constructor_MenuModalComposition on
         * DAT_MenuModalComposition1 with slot = 0 (sets slot, activeModalDialogID = MMT_NONE) and registers
         * Meta::Destructor_0059d680 with atexit.
         */
        void __cdecl Constructor_MenuModalComposition1();

        /**
         * Static initializer: calls UI::MenuModalComposition::Constructor_MenuModalComposition on
         * DAT_MenuModalComposition2 with slot = 1 and registers Meta::Destructor_0059d690 with atexit.
         */
        void __cdecl Constructor_MenuModalComposition2();

        /**
         * Static initializer: calls UI::MenuModalComposition::Constructor_MenuModalComposition on
         * DAT_MenuModalComposition3 with slot = 2 and registers Meta::Destructor_0059d6a0 with atexit.
         */
        void __cdecl Constructor_MenuModalComposition3();

        /**
         * Static initializer: calls Map::TileMapState::Constructor_TileMapState on global DAT_TileMapState and
         * registers Meta::Destructor_0059d6b0 with atexit.
         */
        void __cdecl Constructor_TileMapState();

        /**
         * Static initializer: calls Map::WildlifeState::Constructor_WildlifeState on global DAT_WildlifeState and
         * registers Meta::Destructor_0059d6c0 with atexit.
         */
        void __cdecl Constructor_WildlifeState();

        /**
         * Static initializer: calls Map::Navigation::PathFindingState::Constructor_PathFindingState on global
         * DAT_PathFindingState and registers Meta::Destructor_0059d6d0 with atexit.
         */
        void __cdecl Constructor_PathFindingState();

        /**
         * Static initializer: calls Map::Units::UnitsState::Constructor_UnitsState on global DAT_UnitsState and
         * registers Meta::Destructor_0059d6e0 with atexit.
         */
        void __cdecl Constructor_UnitsState();

        /**
         * Static initializer: calls Map::Entities::EntityState::Constructor_EntityState on global DAT_EntityState
         * and registers Meta::Destructor_0059d6f0 with atexit.
         */
        void __cdecl Constructor_EntityState();

        /**
         * Static initializer: calls Map::Units::TribesState::Constructor_TribesState on global DAT_TribesState and
         * registers Meta::Destructor_0059d700 with atexit.
         */
        void __cdecl Constructor_TribesState();

        /**
         * Static initializer: calls Map::Units::TroopValueState::Constructor_TroopValueState on global
         * DAT_TroopValueState and registers Meta::Destructor_0059d710 with atexit.
         */
        void __cdecl Constructor_TroopValueState();

        /**
         * Static initializer: calls Map::Buildings::BuildingsState::Constructor_BuildingsState on global
         * DAT_BuildingsState and registers Meta::Destructor_BuildingsState with atexit.
         */
        void __cdecl Constructor_BuildingsState();

        /**
         * Static initializer: calls AI::AIVState::Constructor_AIVState on global DAT_AIVState and registers
         * Meta::Destructor_0059d730 with atexit.
         */
        void __cdecl Constructor_AIVState();

        /**
         * Static initializer: calls AI::AICState::Constructor_AICState on global DAT_AICState and registers
         * Meta::Destructor_0059d740 with atexit.
         */
        void __cdecl Constructor_AICState();

        /**
         * Static initializer: calls Map::LandscapeState::Construct_LandscapeState on global DAT_LandscapeState and
         * registers Meta::Destructor_0059d750 with atexit.
         */
        void __cdecl Constructor_LandscapeState();

        /**
         * Static initializer for global DAT_GameState (0x0112B0B8): calls the trivial Constructor_Empty (mov
         * eax,ecx; ret - the decompiler drops the ECX=this load) and registers Meta::Destructor_0059d760 with
         * atexit, which only tail-calls DoNothing on the same object.
         */
        void __cdecl Constructor_GameState();

        /**
         * Static initializer: calls UI::MenuTextInputState::Constructor_MenuTextInputState on global
         * DAT_MenuTextInputState and registers Meta::Destructor_0059d770 with atexit.
         */
        void __cdecl Constructor_MenuTextInputState();

        /**
         * Static initializer: calls Text::TextEditorState::Constructor_TextEditorState on global
         * DAT_TextEditorState and registers Meta::Destructor_TextEditorState with atexit.
         */
        void __cdecl Constructor_TextEditorState();

        /**
         * Static initializer with no constructor call: registers Meta::Destructor_BinkControlClass with atexit;
         * that destructor loads ECX=&DAT_BinkControlState (0x02157518) and tail-calls stopAllBinkPlaybackThunk, so
         * Bink playback is stopped at process exit.
         */
        void __cdecl Constructor_BinkControlClass();

        /**
         * Static initializer with no constructor call: only registers Meta::Destructor_0059d7a0 with atexit, which
         * tail-calls DoNothing on DAT_SoundSystemState (0x01127DD0).
         */
        void __cdecl Constructor_Empty2();

        /**
         * Static initializer: loads ECX=&DAT_HoveredState and tail-jumps to
         * UI::HoveredState::Constructor_HoveredState. Unlike its neighbours it registers no atexit destructor.
         */
        void __cdecl Constructor_HoveredState();

        /**
         * Static initializer for global DAT_MapPropertiesState (0x01653858): calls the trivial Constructor_Empty
         * (mov eax,ecx; ret - the decompiler drops the ECX=this load) and registers Meta::Destructor_0059d7b0 with
         * atexit, which only tail-calls DoNothing on the same object.
         */
        void __cdecl Constructor_MapPropertiesState();

        /**
         * Static initializer: calls Synchrony::GameSynchronyState::Constructor_GameSynchronyState on global
         * DAT_GameSynchronyState and registers Meta::Destructor_0059d7c0 with atexit.
         */
        void __cdecl Constructor_GameSynchronyState();

        /**
         * MSVC CRT static initializer: constructs std::_Init_locks object DAT_Locks and registers
         * Meta::Destructor_StdInitLocks with atexit.
         */
        void __cdecl Constructor_Locks();

        /**
         * MSVC CRT/STL static initializer with no constructor call: only registers Meta::Destructor_0059d7d4 with
         * atexit, which tail-calls meth_0x467730 on INTERNAL_LocaleState (0x02427504) - locale-state cleanup,
         * consistent with the function name.
         */
        void __cdecl Constructor_CreateLocaleMemoryRelated();

        /**
         * MSVC CRT static initializer: constructs std::_Init_locks object INTERNAL_Locks2 and registers
         * Meta::Destructor_StdInitLocks2 with atexit.
         */
        void __cdecl Constructor_Locks2();

        /**
         * MSVC CRT/STL static initializer with no constructor call: only registers Meta::Destructor_StdInitAtexit
         * with atexit, which tail-calls 0x0057EC4D (thunk to 0x0057EC67) with ECX=0x02427599 (std::_Init_atexit-
         * style object).
         */
        void __cdecl Constructor_CRelated();

        /**
         * atexit destructor stub (registered by the static initializer at 0x0059A640, which builds
         * MenuView_MissionFinishedTransition via Constructor_MenuView): loads
         * ECX=&MenuView_MissionFinishedTransition (0x00B966F4) and tail-jumps to DoNothing (the MenuView destructor
         * is empty). The decompiler hides the ECX load; the name is correct.
         */
        void __cdecl Destructor_MenuView_MissionFinishedTransition();

    } // namespace Init
} // namespace Global
} // namespace OpenSHC
