#include "../Helpers.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Game/Scenario/BarracksRecruitabilityShort.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Game::Scenario::BarracksRecruitabilityShort;

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0042F010
    void Helpers::InitializeBasicMap()
    {
        short* psVar1;
        DAT_GameCore::instance.currentlyInGameUnk_0xa4 = FALSE;
        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
            DAT_TextureRenderCoreObject::ptr)("frontend_builder2.tgx");
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::clearMapAndTimeAndPlayerData, DAT_GameState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::clearSignpostData, DAT_GameState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setupAllMapSections, DAT_TileMapState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetHeightAndMapBorders, DAT_TileMapState::ptr)(
            DAT_TileMapState::instance.mapSize);
        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
        MACRO_CALL_MEMBER(
            OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageLayerForEachBuildingAtEachTile,
            DAT_PathFindingState::ptr)();
        MACRO_CALL_MEMBER(
            OpenSHC::Map::Navigation::PathFindingState_Func::updateSeparateAreaTileMap, DAT_PathFindingState::ptr)(1);
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updatePathLinkageLayerForAllBuildings,
            DAT_BuildingsState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::forceFullTileMapRedraw, DAT_TileMapState::ptr)();
        MACRO_CALL_MEMBER(
            OpenSHC::UI::MinimapViewState_Func::setTileColorsDependingOnMapSize, DAT_MinimapViewState::ptr)(0, 100);
        MACRO_CALL_MEMBER(
            OpenSHC::UI::MinimapViewState_Func::setMapPropertyDependingOnMapSize, DAT_MinimapViewState::ptr)(0, 100);
        DAT_GameState::instance.mapAndTime.editScenarioExtraOptions = 0;
        MACRO_CALL_MEMBER(
            OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, DAT_ViewportRenderState::ptr)();
        DAT_GameCore::instance.descriptionUseStringTable = 0;
        DAT_GameCore::instance.temporaryTextBufferOfSize1000[0] = '\0';
        DAT_TileMapState::instance.unitPlacementCount = 1;
        MACRO_CALL_MEMBER(
            OpenSHC::Map::MapPropertiesState_Func::setStartingYearAndStartingResources, DAT_MapPropertiesState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::clearAnimalSpawnLocationsUnk, DAT_TribesState::ptr)();
        DAT_GameCore::instance.mapU4Int3_balanced = 0;
        psVar1 = DAT_MapPropertiesState::instance.SEC_MercRecruitable;
        do {
            (((BarracksRecruitabilityShort*)(psVar1 + -7))->recruitability).archers = 1;
            *psVar1 = 1;
            psVar1 = psVar1 + 1;
        } while ((int)psVar1 < 0x1653df6);
        DAT_MapPropertiesState::instance.SEC_XbowProducible_save = 1;
        DAT_MapPropertiesState::instance.SEC_BowProducible_save = 1;
        DAT_MapPropertiesState::instance.SEC_PikeProducible_save = 1;
        DAT_MapPropertiesState::instance.SEC_SpearProducible_save = 1;
        DAT_MapPropertiesState::instance.SEC_SwordProducible_save = 1;
        DAT_MapPropertiesState::instance.SEC_MaceProducible_save = 1;
        DAT_GameCore::instance.mapU4Int1 = 0;
        MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadTGX_shc_back)();
    }

}
}
