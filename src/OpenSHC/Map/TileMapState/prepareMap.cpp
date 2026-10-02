#include "../../Map.func.hpp"

#include "OpenSHC/AI/AIVState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/WildlifeState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/HoveredState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_HoveredState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WallAndPitchState.hpp"
#include "OpenSHC/Globals/DAT_WildlifeState.hpp"
#include "OpenSHC/Globals/FilePackagerObj.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "MappersEnumShort": Some values do not have unique names
     */
    /*
      WARNING: Enum "MappersEnumInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00512450
    void TileMapState::prepareMap()
    {
        char cVar1;
        char* pcVar2;
        char (*pacVar3)[250];
        int _viewportY;
        int _viewportX;
        _viewportX = DAT_ViewportRenderState::instance.viewportState.viewportY;
        _viewportY = DAT_ViewportRenderState::instance.viewportState.viewportX;
        if (DAT_GameSynchronyState::instance.currentGameModeCopy_SEC_Section1106
            == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
            DAT_GameSynchronyState::instance.currentGameMode = OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER;
            DAT_GameSynchronyState::instance.isHost = TRUE;
            pcVar2 = MACRO_CALL_MEMBER(
                OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(0);
            pacVar3 = DAT_GameSynchronyState::instance.DAT_PlayerNames + 1;
            do {
                cVar1 = *pcVar2;
                (*pacVar3)[0] = cVar1;
                pcVar2 = pcVar2 + 1;
                pacVar3 = (char (*)[250])(*pacVar3 + 1);
            } while (cVar1 != '\0');
            MACRO_CALL_MEMBER(OpenSHC::AI::AIVState_Func::syncAIPlayerNamesAndBuildIntervals, DAT_AIVState::ptr)();
            DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
        } else {
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION) {
                if (0xf < DAT_GameCore::instance.missionNumber1to20)
                    goto LAB_005124d2;
            } else if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_BUILDERUnk)
                goto LAB_005124d2;
            DAT_GameSynchronyState::instance.currentGameMode = OpenSHC::Game::GM_SOLITARY;
        }
    LAB_005124d2:
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::changeMapOrientation, this)(DAT_TileMapState::instance.mapOrientation);
        DAT_PathFindingState::instance.searchGeneration = 1;
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
        DAT_ViewportRenderState::instance.viewportState.viewportX = _viewportY;
        DAT_ViewportRenderState::instance.viewportState.viewportY = _viewportX;
        MACRO_CALL_MEMBER(
            OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, DAT_ViewportRenderState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setTileSystemMemoryLookupArrays,
            DAT_ViewportRenderState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::tweakValidTilesToExcludeMapBorders,
            DAT_ViewportRenderState::ptr)();
        DAT_BuildingsState::instance.maxBuildingsCount = 2000;
        DAT_UnitsState::instance.maxUnitCount = 2500;
        DAT_PathFindingState::instance.maxClimbDataCount = 200;
        DAT_EntityState::instance.maxEntityCount = 3000;
        DAT_TileMapState::instance.currentMoatCount = 16000;
        DAT_LandscapeState::instance.maxTreeCount = 2000;
        DAT_TileMapState::instance.maxPitchDitchCount = 4000;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetHeightAndMapBorders, this)(DAT_TileMapState::instance.mapSize);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::toggleFlatView, this)(0);
        (*(int*)&DAT_TileMapState::instance.padding_0x5548d0[0]) = 0;
        DAT_TileMapState::instance.flatViewToggleValue2 = 0;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setChangedLayerToThreeAndMapping0x40x40, this)();
        DAT_TileMapState::instance.forceUpdateLogicalAndMiscDisplayLayers = 1;
        DAT_TileMapState::instance.forceUpdateTextureTilemap = 1;
        DAT_TileMapState::instance.forceUpdateGFXLayers = 1;
        DAT_TileMapState::instance.forceUpdateMacroLayerFlag = 1;
        DAT_TileMapState::instance.field68_0x55487c = 500;
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::upgradeTribeArrayLayoutForMapVersion,
            DAT_TribesState::ptr)(
            (OpenSHC::IO::PackagedFileMagicNum)FilePackagerObj::instance.versionNumOfCurrentFileTypeUnk,
            (OpenSHC::IO::PackagedFileMagicNum)(FilePackagerObj::instance.packagerMapVersionNumUnk));
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::uselessFunction, DAT_TroopValueState::ptr)(
            (OpenSHC::IO::PackagedFileMagicNum)FilePackagerObj::instance.versionNumOfCurrentFileTypeUnk,
            (OpenSHC::IO::PackagedFileMagicNum)(FilePackagerObj::instance.packagerMapVersionNumUnk));
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::upgradeMapFormatForUnits, DAT_UnitsState::ptr)(
            (OpenSHC::IO::PackagedFileMagicNum)FilePackagerObj::instance.versionNumOfCurrentFileTypeUnk,
            (OpenSHC::IO::PackagedFileMagicNum)(FilePackagerObj::instance.packagerMapVersionNumUnk));
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::upgradeMapFormatLogicLayer, this)(
            (OpenSHC::IO::PackagedFileMagicNum)FilePackagerObj::instance.versionNumOfCurrentFileTypeUnk,
            (OpenSHC::IO::PackagedFileMagicNum)(FilePackagerObj::instance.packagerMapVersionNumUnk));
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::upgradeBuildingsForMapVersion,
            DAT_BuildingsState::ptr)((OpenSHC::IO::PackagedFileMagicNum)FilePackagerObj::instance.versionNumOfCurrentFileTypeUnk,
            (OpenSHC::IO::PackagedFileMagicNum)(FilePackagerObj::instance.packagerMapVersionNumUnk));
        MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::upgradeTreesAndRocksForMapVersion,
            DAT_LandscapeState::ptr)((OpenSHC::IO::PackagedFileMagicNum)FilePackagerObj::instance.versionNumOfCurrentFileTypeUnk,
            (OpenSHC::IO::PackagedFileMagicNum)(FilePackagerObj::instance.packagerMapVersionNumUnk));
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::upgradeMapTribesState, DAT_TribesState::ptr)(
            (OpenSHC::IO::PackagedFileMagicNum)FilePackagerObj::instance.versionNumOfCurrentFileTypeUnk,
            (OpenSHC::IO::PackagedFileMagicNum)(FilePackagerObj::instance.packagerMapVersionNumUnk));
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::migrateGameStateForMapVersion, DAT_GameState::ptr)(
            (OpenSHC::IO::PackagedFileMagicNum)FilePackagerObj::instance.versionNumOfCurrentFileTypeUnk,
            (OpenSHC::IO::PackagedFileMagicNum)(FilePackagerObj::instance.packagerMapVersionNumUnk));
        MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::handleMapVersionUpgrade, DAT_EntityState::ptr)(
            (OpenSHC::IO::PackagedFileMagicNum)FilePackagerObj::instance.versionNumOfCurrentFileTypeUnk,
            (OpenSHC::IO::PackagedFileMagicNum)(FilePackagerObj::instance.packagerMapVersionNumUnk));
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::recountTotalOwnedMoats, this)();
        MACRO_CALL_MEMBER(
            OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageLayerForEachBuildingAtEachTile,
            DAT_PathFindingState::ptr)();
        MACRO_CALL_MEMBER(
            OpenSHC::Map::Navigation::PathFindingState_Func::updateSeparateAreaTileMap, DAT_PathFindingState::ptr)(1);
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updatePathLinkageLayerForAllBuildings,
            DAT_BuildingsState::ptr)();
        MACRO_CALL_MEMBER(
            OpenSHC::Map::Navigation::PathFindingState_Func::updateClimbData, DAT_PathFindingState::ptr)();
        MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::clearBuildingValueWhenStateIsTwo, DAT_BuildingsState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::setCurrentTimeOnSomeTrees, DAT_LandscapeState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::resetWind, DAT_LandscapeState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::collectCliffEdgeTilesForClimbData, this)();
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearInvalidMoatEntries, this)();
        MACRO_CALL_MEMBER(
            OpenSHC::Game::GameStateStructures_Func::initializeGameStateAfterMapLoad, DAT_GameState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::sortEventsByDate, DAT_MapPropertiesState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::applyVersionUpgradeAccessibilityRecompute,
            DAT_BuildingsState::ptr)((OpenSHC::IO::PackagedFileMagicNum)FilePackagerObj::instance.versionNumOfCurrentFileTypeUnk,
            (OpenSHC::IO::PackagedFileMagicNum)(FilePackagerObj::instance.packagerMapVersionNumUnk));
        MACRO_CALL_MEMBER(
            OpenSHC::Map::Navigation::PathFindingState_Func::updateSeparateAreaTileMap, DAT_PathFindingState::ptr)(1);
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updatePathLinkageLayerForAllBuildings,
            DAT_BuildingsState::ptr)();
        _viewportX = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::updateWildlifeGrid, DAT_WildlifeState::ptr)(_viewportX);
            _viewportX = _viewportX + 1;
        } while (_viewportX < 40);
        MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::updateWildlife, DAT_WildlifeState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::updateSection1034Info, DAT_WildlifeState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::updateNofFpoints, DAT_WildlifeState::ptr)();
        MACRO_CALL(OpenSHC::Map_Func::ResetSomeValuesFunctionUnk)();
        DAT_WallAndPitchState::instance.countdown = 0;
        MACRO_CALL_MEMBER(OpenSHC::UI::HoveredState_Func::clearHoveredState, DAT_HoveredState::ptr)();
        DAT_GameCore::instance.gamePausedLogical = 0xffffffff;
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::processGameTick, DAT_GameState::ptr)();
        MACRO_CALL_MEMBER(
            OpenSHC::Map::Navigation::PathFindingState_Func::updateSeparateAreaTileMap, DAT_PathFindingState::ptr)(1);
        MACRO_CALL_MEMBER(
            OpenSHC::UI::MinimapViewState_Func::setTileColorsDependingOnMapSize, DAT_MinimapViewState::ptr)(0, 100);
        MACRO_CALL_MEMBER(
            OpenSHC::UI::MinimapViewState_Func::setMapPropertyDependingOnMapSize, DAT_MinimapViewState::ptr)(0, 100);
    }

}
}
