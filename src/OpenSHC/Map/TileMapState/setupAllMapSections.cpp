#include "../../Map.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WallAndPitchState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00512100
    void TileMapState::setupAllMapSections()
    {
        ushort* puVar1;
        short* psVar2;
        ushort uVar3;
        int* piVar4;
        int iVar5;
        DAT_TileMapState::instance.temporaryTerrainTypeIndex = 0;
        DAT_TileMapState::instance.SEC_Section1052 = 0;
        DAT_TileMapState::instance.SEC_Section1053 = 0;
        DAT_TileMapState::instance.SEC_Section1054 = 0;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setupTileMapSections, this)();
        DAT_WallAndPitchState::instance.countdown = 0;
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setTileSystemMemoryLookupArrays,
            DAT_ViewportRenderState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::tweakValidTilesToExcludeMapBorders,
            DAT_ViewportRenderState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setupViewport, DAT_ViewportRenderState::ptr)(0,
            0, (undefined4)((int)(DAT_WindowAndDirectDraw::instance.resolutionX)),
            (undefined4)((int)(DAT_WindowAndDirectDraw::instance.resolutionY + -128)));
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setupLogicalMapBorders, this)();
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateShowHiLayerOrResetChangedLayer, this)();
        puVar1 = DAT_TileMapState::instance.GfxLayer + 1;
        piVar4 = DAT_TileMapState::instance.LogicLayer + 1;
        iVar5 = 13400;
        do {
            uVar3 = (ushort)GMTotalPicturesProcessed::instance[2];
            if (piVar4[-1] != 0x10) {
                if (piVar4[-1] == 0x20) {
                    uVar3 = (ushort)GMTotalPicturesProcessed::instance[2] + 1;
                } else {
                    uVar3 = (ushort)GMTotalPicturesProcessed::instance[2] + 2;
                }
            }
            puVar1[-1] = uVar3;
            uVar3 = (ushort)GMTotalPicturesProcessed::instance[2];
            if (*piVar4 != 0x10) {
                if (*piVar4 == 0x20) {
                    uVar3 = (ushort)GMTotalPicturesProcessed::instance[2] + 1;
                } else {
                    uVar3 = (ushort)GMTotalPicturesProcessed::instance[2] + 2;
                }
            }
            *puVar1 = uVar3;
            uVar3 = (ushort)GMTotalPicturesProcessed::instance[2];
            if (piVar4[1] != 0x10) {
                if (piVar4[1] == 0x20) {
                    uVar3 = (ushort)GMTotalPicturesProcessed::instance[2] + 1;
                } else {
                    uVar3 = (ushort)GMTotalPicturesProcessed::instance[2] + 2;
                }
            }
            puVar1[1] = uVar3;
            uVar3 = (ushort)GMTotalPicturesProcessed::instance[2];
            if (piVar4[2] != 0x10) {
                if (piVar4[2] == 0x20) {
                    uVar3 = (ushort)GMTotalPicturesProcessed::instance[2] + 1;
                } else {
                    uVar3 = (ushort)GMTotalPicturesProcessed::instance[2] + 2;
                }
            }
            puVar1[2] = uVar3;
            uVar3 = (ushort)GMTotalPicturesProcessed::instance[2];
            if (piVar4[3] != 0x10) {
                if (piVar4[3] == 0x20) {
                    uVar3 = (ushort)GMTotalPicturesProcessed::instance[2] + 1;
                } else {
                    uVar3 = (ushort)GMTotalPicturesProcessed::instance[2] + 2;
                }
            }
            puVar1[3] = uVar3;
            uVar3 = (ushort)GMTotalPicturesProcessed::instance[2];
            if (piVar4[4] != 0x10) {
                if (piVar4[4] == 0x20) {
                    uVar3 = (ushort)GMTotalPicturesProcessed::instance[2] + 1;
                } else {
                    uVar3 = (ushort)GMTotalPicturesProcessed::instance[2] + 2;
                }
            }
            puVar1[4] = uVar3;
            piVar4 = piVar4 + 6;
            puVar1 = puVar1 + 6;
            iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ShortValue, DAT_LowLevelMemory::ptr)(
            80400, 1, (void*)((int)(DAT_TileMapState::instance.PillarGFXLayer)));
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            80400, '\b', (void*)((int)(DAT_TileMapState::instance.HeightLayer)));
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            80400, '\b', (void*)((int)(DAT_TileMapState::instance.DefaultHeightLayer)));
        DAT_PathFindingState::instance.searchGeneration = 1;
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            160800, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::setChangedLayerZeroBasedOn40x40Layer,
            DAT_PathFindingState::ptr)(0);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateLogicalTileMapRelatedSections, this)();
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateGfxLayer, this)();
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateGFXLayers, this)();
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetMoatArray, this)();
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetPitchDitchArray, this)();
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::toggleFlatView, this)(0);
        (*(int*)&DAT_TileMapState::instance.padding_0x5548d0[0]) = 0;
        DAT_TileMapState::instance.flatViewToggleValue2 = 0;
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::clearBuildings, DAT_BuildingsState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::clearRocksAndTrees, DAT_LandscapeState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::resetWind, DAT_LandscapeState::ptr)();
        MACRO_CALL(OpenSHC::Global_Func::DoNothing)();
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::clearAllUnits, DAT_UnitsState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::clearAllTribes, DAT_TribesState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::clearMapAndTimeAndPlayerData, DAT_GameState::ptr)();
        MACRO_CALL_MEMBER(
            OpenSHC::Game::GameStateStructures_Func::resetVariousCountsAndStatisticsAndStartGoodsAndResources,
            DAT_GameState::ptr)();
        MACRO_CALL_MEMBER(
            OpenSHC::Game::GameStateStructures_Func::clearCurrentResourcesAndStrongWalls, DAT_GameState::ptr)();
        MACRO_CALL_MEMBER(
            OpenSHC::Game::GameStateStructures_Func::initializeGameStateAfterMapLoad, DAT_GameState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::fillWith0xFF, DAT_GameState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::clearAnimalSpawnLocationsUnk, DAT_TribesState::ptr)();
        piVar4 = DAT_AICState::instance.tribeUIDArray;
        psVar2 = DAT_AICState::instance.tribeIDArray;
        do {
            *psVar2 = 0;
            *piVar4 = 0;
            psVar2 = psVar2 + 1;
            piVar4 = piVar4 + 1;
        } while ((int)psVar2 < 0x24026cc);
        MACRO_CALL(OpenSHC::Global_Func::DoNothing)();
        MACRO_CALL(OpenSHC::Global_Func::DoNothing)();
        MACRO_CALL_MEMBER(
            OpenSHC::Map::Entities::EntityState_Func::clearEntityArrayAndSeagullArray, DAT_EntityState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setChangedLayerToThreeAndMapping0x40x40, this)();
        DAT_TileMapState::instance.forceUpdateLogicalAndMiscDisplayLayers = 1;
        DAT_TileMapState::instance.forceUpdateTextureTilemap = 1;
        DAT_TileMapState::instance.forceUpdateGFXLayers = 1;
        DAT_TileMapState::instance.forceUpdateMacroLayerFlag = 1;
        DAT_TileMapState::instance.field68_0x55487c = 200;
        MACRO_CALL_MEMBER(
            OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageLayerForEachBuildingAtEachTile,
            DAT_PathFindingState::ptr)();
        MACRO_CALL_MEMBER(
            OpenSHC::Map::Navigation::PathFindingState_Func::updateSeparateAreaTileMap, DAT_PathFindingState::ptr)(1);
        DAT_TileMapState::instance.forceUpdateMacroLayerFlag = 1;
        DAT_TileMapState::instance.field68_0x55487c = 500;
        MACRO_CALL_MEMBER(
            OpenSHC::UI::MinimapViewState_Func::setTileColorsDependingOnMapSize, DAT_MinimapViewState::ptr)(0, 100);
        MACRO_CALL_MEMBER(
            OpenSHC::UI::MinimapViewState_Func::setMapPropertyDependingOnMapSize, DAT_MinimapViewState::ptr)(0, 100);
        DAT_GameCore::instance.currentlyInGameUnk_0xa4 = FALSE;
        MACRO_CALL(OpenSHC::Map_Func::ResetSomeValuesFunctionUnk)();
    }

}
}
