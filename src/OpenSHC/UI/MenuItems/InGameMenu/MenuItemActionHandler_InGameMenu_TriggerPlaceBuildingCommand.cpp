#include "../InGameMenu.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/WallAndPitchState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Actions.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/HoveredState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Map/Buildings/BuildingFailReasonEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00b96110.hpp"
#include "OpenSHC/Globals/DAT_00b98450.hpp"
#include "OpenSHC/Globals/DAT_00b98454.hpp"
#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_HoveredState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_ScrollingHandler.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WallAndPitchState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"
#include "OpenSHC/Globals/UNK_UnusedTextLocation1.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using Commands::GameCommandType;
        using Commands::MappersEnum;
        using DE::SHCDE::eSFX;
        using Game::GameMode;
        using Game::GameMode2;
        using IO::Graphics::GmID;
        using Map::Buildings::BuildingFailReasonEnum;
        using Map::Buildings::BuildingType;
        using UI::Enums::MenuViewType;
        using WindowsHelper::Enums::BOOLEnum;
        using Map::Buildings::BuildingTypeShort;

        // FUNCTION: STRONGHOLDCRUSADER 0x004451C0
        void InGameMenu::MenuItemActionHandler_InGameMenu_TriggerPlaceBuildingCommand(int param_1, ...)
        {
            BuildingTypeShort BVar1;
            short sVar2;
            char cVar3;
            int iVar4;
            int iVar6;
            uint _height;
            uint uVar7;
            int _pitchDitchCount;
            DWORD DVar8;
            BOOLEnum BVar9;
            GmID GVar10;
            uint uVar11;
            int uVar16;
            GmID imageY;
            int iVar12;
            MappersEnum MVar13;
            int _clickedTile;
            GmID imageX;
            bool bVar14;
            int local_8;
            GmID local_4;
            int _barracksID;
            MappersEnumInt unionfacet2_445a55;
            int uVar17;
            int _mercBuildingID;
            int _engineersGuildBuildingID;
            int _tunnelersGuildBuildingID;
            char* pcVar5;
            if (DAT_GameSynchronyState::instance.syncStatus != 0) {}
            if (DAT_GameSynchronyState::instance.saveRelated != 0) {}
            if (DAT_GameCore::instance.gamePausedLogical != 0) {}
            DAT_TileMapState::instance.DAT_BuildingSize
                = MACRO_CALL_MEMBER(Map::TileMapState_Func::getBuildingSizeForCommandBuildingType,
                    DAT_TileMapState::ptr)(DAT_TileMapState::instance.currentMapperCommand);
            if (DAT_TileMapState::instance.DAT_BuildingSize < 0) {
                DAT_TileMapState::instance.DAT_BuildingSize = 0;
            }
            MACRO_CALL_MEMBER(UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                DAT_BottomLeftTextDisplayState::ptr)(2, -1, 0,
                (TextMessageBLLookupStructUnion)((int)(DAT_TileMapState::instance.currentMapperCommand)), 0x32, -1);
            if (DAT_ViewportRenderState::instance.viewportState.field0_0x0 == 0) {}
            DAT_TileMapState::instance.buildingPlacementFailReason
                = Map::Buildings::BFRE_DEFAULT_CANT_PLACE_THAT_THERE;
            if (DAT_TileMapState::instance.flatViewToggleValue1 == 0) {
                MACRO_CALL_MEMBER(
                    Rendering::ViewportRenderState_Func::setupMouseTileXY, DAT_ViewportRenderState::ptr)();
            } else {
                MACRO_CALL_MEMBER(
                    Rendering::ViewportRenderState_Func::setupMouseTileXY2, DAT_ViewportRenderState::ptr)();
            }
            if ((DAT_MouseState::instance.leftClickStart == 0)
                && (DAT_ScrollingHandler::instance.isScrolling_0x0 != FALSE)) {}
            DAT_TileMapState::instance.DAT_ClickedTileY = DAT_ViewportRenderState::instance.viewportState.mouseTileY;
            DAT_TileMapState::instance.DAT_ClickedTileX = DAT_ViewportRenderState::instance.viewportState.mouseTileX;
            if (DAT_TileMapState::instance.currentMapperCommand == Commands::M_MAPPER_MANGONEL) {
                iVar6 = DAT_ViewportRenderState::instance.viewportState.mouseTileY * 3;
                iVar4 = DAT_ViewportRenderState::instance
                            .translationMatrix[DAT_ViewportRenderState::instance.viewportState.mouseTileY]
                            .addXgetTile
                    + DAT_ViewportRenderState::instance.viewportState.mouseTileX;
                iVar12 = (int)DAT_TileMapState::instance.BuildingLayer[iVar4];
                if (DAT_MouseState::instance.draggingStopped == FALSE) {
                    if ((((iVar12 != 0)
                             && (DAT_BuildingsState::instance.buildings[iVar12].owner
                                 == DAT_GameSynchronyState::instance.currentPlayerSlotID))
                            && ((BVar1 = DAT_BuildingsState::instance.buildings[iVar12].buildingType,
                                BVar1 == Map::Buildings::BT_TOWER4
                                    || (BVar1 == Map::Buildings::BT_TOWER5))))
                        && ((((DAT_TileMapState::instance.LogicLayer[iVar4] & 0x10000000U) != 0
                                 && (DAT_TileMapState::instance.UnitLayer[iVar4] == 0))
                            && (DAT_BuildingsState::instance.buildings[iVar12].containsSiegeMangonel1OrBallista2
                                == 0)))) {
                        MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                            DAT_ViewportRenderState::ptr)(IO::Graphics::GID_BODY_MANGONEL, 1, 0, 0, iVar4, 5);
                    }
                    MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                        DAT_ViewportRenderState::ptr)(
                        IO::Graphics::GID_BODY_MANGONEL, 1, 0, 0, iVar4, 0x100005);
                }
                if (iVar12 == 0) {}
                (*(int*)((char*)&UNK_UnusedTextLocation1::instance + 994)) = (*(int*)((char*)&UNK_UnusedTextLocation1::instance + 994))
                    + DAT_ViewportRenderState::instance.viewportState.mouseTileX;
                cVar3 = (char)iVar4 + -3;
                pcVar5 = (char*)((((uint)((int3)((uint)iVar4 >> 8)) & 0xffffff) << 8) | (uint)(byte)(cVar3));
                *pcVar5 = *pcVar5 + cVar3;
                if (*(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar12 + -0x4a) != iVar6) {}
                sVar2 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar12 + -0x4e);
                if ((sVar2 != 0x4d) && (sVar2 != 0x4e)) {}
                if ((DAT_TileMapState::instance.LogicLayer[(int)pcVar5] & 0x10000000U) == 0) {}
                if (DAT_TileMapState::instance.UnitLayer[(int)pcVar5] != 0) {}
                if (*(char*)((int)DAT_BuildingsState::instance.buildings[0].quarryLinkedOxTethers + iVar12 + -0x35)
                    != '\0') {}
                iVar6 = MACRO_CALL_MEMBER(
                    Game::GameStateStructures_Func::checkRequiredResourcesForBuildingOrPlanToBuy,
                    DAT_GameState::ptr)(Commands::M_MAPPER_MANGONEL, iVar6, TRUE);
                if (iVar6 == 0) {}
                MACRO_CALL_MEMBER(UI::HoveredState_Func::createHoverStateElement, DAT_HoveredState::ptr)(
                    DAT_TileMapState::instance.DAT_ClickedTileX,
                    (int)((int)(DAT_TileMapState::instance.DAT_ClickedTileY)),
                    DAT_TileMapState::instance.currentMapperCommand,
                    (int)((int)(DAT_TileMapState::instance.DAT_BuildingSize)), 0);
                iVar6 = (int)*(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar12 + -0x30);
                DAT_TileMapState::instance.DAT_ClickedTileX
                    = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar12 + -0x32) + 2;
                DAT_TileMapState::instance.DAT_ClickedTileY = iVar6 + 2;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                    = DAT_TileMapState::instance.DAT_ClickedTileX * 8 + 4;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                    = DAT_TileMapState::instance.DAT_ClickedTileY * 8 + 4;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = (GmID)
                    * (byte*)(DAT_ViewportRenderState::instance.translationMatrix[iVar6 + 2].addXgetTile + 0x1d32c38
                        + DAT_TileMapState::instance.DAT_ClickedTileX);
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 0x29;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(Commands::GCT_SIEGE_TENT);
            }
            if (DAT_TileMapState::instance.currentMapperCommand == Commands::M_MAPPER_BALLISTA) {
                iVar6 = DAT_ViewportRenderState::instance
                            .translationMatrix[DAT_ViewportRenderState::instance.viewportState.mouseTileY]
                            .addXgetTile
                    + DAT_ViewportRenderState::instance.viewportState.mouseTileX;
                iVar4 = (int)DAT_TileMapState::instance.BuildingLayer[iVar6];
                if (DAT_MouseState::instance.draggingStopped == FALSE) {
                    if ((((iVar4 != 0)
                             && (DAT_BuildingsState::instance.buildings[iVar4].owner
                                 == DAT_GameSynchronyState::instance.currentPlayerSlotID))
                            && ((BVar1 = DAT_BuildingsState::instance.buildings[iVar4].buildingType,
                                BVar1 == Map::Buildings::BT_TOWER4
                                    || (BVar1 == Map::Buildings::BT_TOWER5))))
                        && ((((DAT_TileMapState::instance.LogicLayer[iVar6] & 0x10000000U) != 0
                                 && (DAT_TileMapState::instance.UnitLayer[iVar6] == 0))
                            && (DAT_BuildingsState::instance.buildings[iVar4].containsSiegeMangonel1OrBallista2
                                == 0)))) {
                        MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                            DAT_ViewportRenderState::ptr)(IO::Graphics::GID_BODY_BALLISTA, 1, 0, 0, iVar6, 5);
                    }
                    MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                        DAT_ViewportRenderState::ptr)(
                        IO::Graphics::GID_BODY_BALLISTA, 1, 0, 0, iVar6, 0x100005);
                }
                if (iVar4 == 0) {}
                if (DAT_BuildingsState::instance.buildings[iVar4].owner
                    != DAT_GameSynchronyState::instance.currentPlayerSlotID) {}
                BVar1 = DAT_BuildingsState::instance.buildings[iVar4].buildingType;
                if ((BVar1 != Map::Buildings::BT_TOWER4) && (BVar1 != Map::Buildings::BT_TOWER5)) {}
                if ((DAT_TileMapState::instance.LogicLayer[iVar6] & 0x10000000U) == 0) {}
                if (DAT_TileMapState::instance.UnitLayer[iVar6] != 0) {}
                if (DAT_BuildingsState::instance.buildings[iVar4].containsSiegeMangonel1OrBallista2 != 0) {}
                iVar6 = MACRO_CALL_MEMBER(
                    Game::GameStateStructures_Func::checkRequiredResourcesForBuildingOrPlanToBuy,
                    DAT_GameState::ptr)(Commands::M_MAPPER_BALLISTA,
                    (int)((int)(DAT_GameSynchronyState::instance.currentPlayerSlotID)), TRUE);
                if (iVar6 == 0) {}
                MACRO_CALL_MEMBER(UI::HoveredState_Func::createHoverStateElement, DAT_HoveredState::ptr)(
                    DAT_TileMapState::instance.DAT_ClickedTileX,
                    (int)((int)(DAT_TileMapState::instance.DAT_ClickedTileY)),
                    DAT_TileMapState::instance.currentMapperCommand,
                    (int)((int)(DAT_TileMapState::instance.DAT_BuildingSize)), 0);
                iVar6 = (int)(short)DAT_BuildingsState::instance.buildings[iVar4].y;
                DAT_TileMapState::instance.DAT_ClickedTileX
                    = (short)DAT_BuildingsState::instance.buildings[iVar4].x + 2;
                DAT_TileMapState::instance.DAT_ClickedTileY = iVar6 + 2;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                    = DAT_TileMapState::instance.DAT_ClickedTileX * 8 + 4;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                    = DAT_TileMapState::instance.DAT_ClickedTileY * 8 + 4;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = (GmID)
                    * (byte*)(DAT_ViewportRenderState::instance.translationMatrix[iVar6 + 2].addXgetTile + 0x1d32c38
                        + DAT_TileMapState::instance.DAT_ClickedTileX);
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 0x3d;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(Commands::GCT_SIEGE_TENT);
            }
            if (((DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_FLAG_TYPE0)
                    && (DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_FLAG_TYPE1))
                && ((DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_FLAG_TYPE2
                    && (DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_FLAG_TYPE3)))) {
                if (DAT_TileMapState::instance.currentMapperCommand == Commands::M_MAPPER_HEADS) {
                    iVar6 = DAT_ViewportRenderState::instance
                                .translationMatrix[DAT_ViewportRenderState::instance.viewportState.mouseTileY]
                                .addXgetTile
                        + DAT_ViewportRenderState::instance.viewportState.mouseTileX;
                    iVar4 = DAT_TileMapState::instance.field193_0x554a1c + 1;
                    if (DAT_MouseState::instance.draggingStopped == FALSE) {
                        iVar12 = MACRO_CALL_MEMBER(
                            Map::TileMapState_Func::getTotalHeightAt, DAT_TileMapState::ptr)(
                            iVar6, (int)((int)(DAT_GameSynchronyState::instance.currentPlayerSlotID)));
                        if ((-1 < iVar12) && ((DAT_TileMapState::instance.MiscDisplayLayer[iVar6] & 0x1000) == 0)) {
                            MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                                DAT_ViewportRenderState::ptr)(
                                IO::Graphics::GID_ANIM_HEADS, iVar4, 0xf, 7, iVar6, 0x1d);
                        }
                        MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                            DAT_ViewportRenderState::ptr)(
                            IO::Graphics::GID_ANIM_HEADS, iVar4, 0xf, 7, iVar6, 0x18001d);
                    }
                    iVar4 = MACRO_CALL_MEMBER(Map::TileMapState_Func::getTotalHeightAt, DAT_TileMapState::ptr)(
                        iVar6, (int)((int)(DAT_GameSynchronyState::instance.currentPlayerSlotID)));
                    if (iVar4 < 0) {}
                    if ((DAT_TileMapState::instance.MiscDisplayLayer[iVar6] & 0x1000) != 0) {}
                    iVar6 = DAT_TileMapState::instance.DAT_ClickedTileY * 8;
                    iVar12 = DAT_TileMapState::instance.DAT_ClickedTileX * 8;
                    MACRO_CALL_MEMBER(UI::HoveredState_Func::createHoverStateElement, DAT_HoveredState::ptr)(
                        DAT_TileMapState::instance.DAT_ClickedTileX,
                        (int)((int)(DAT_TileMapState::instance.DAT_ClickedTileY)),
                        DAT_TileMapState::instance.currentMapperCommand,
                        (int)((int)(DAT_TileMapState::instance.field193_0x554a1c)), 0);
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam5
                        = DAT_TileMapState::instance.field193_0x554a1c;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                        = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 0xf;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = iVar12;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = iVar6;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = iVar4;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(Commands::GCT_SPAWN_ENTITY);
                    DAT_TileMapState::instance.field193_0x554a1c = (int)SEC_RNG::instance.currentNumber1 % 7;
                    MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                }
                if (DAT_TileMapState::instance.currentMapperCommand == Commands::M_MAPPER_BRAZIER) {
                    iVar6 = DAT_ViewportRenderState::instance
                                .translationMatrix[DAT_ViewportRenderState::instance.viewportState.mouseTileY]
                                .addXgetTile
                        + DAT_ViewportRenderState::instance.viewportState.mouseTileX;
                    bVar14 = true;
                    if ((DAT_GameCore::instance.gameMode_2 == Game::GM_SIEGE_THAT)
                        && (MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::getBuildingCost,
                                DAT_BuildingsState::ptr)(Commands::M_MAPPER_BRAZIER, &local_8, (int*)&local_4),
                            DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .startResources[0xf]
                                < (int)local_4)) {
                        bVar14 = false;
                    }
                    if (DAT_MouseState::instance.draggingStopped == FALSE) {
                        _height = MACRO_CALL_MEMBER(
                            Map::TileMapState_Func::getHeightAtTileIncludingOwnersBuildings,
                            DAT_TileMapState::ptr)(
                            iVar6, (int)((int)(DAT_GameSynchronyState::instance.currentPlayerSlotID)));
                        if ((_height == 0) || (!bVar14)) {
                            iVar4 = 0x10001d;
                        } else {
                            iVar4 = 0x1d;
                        }
                        MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                            DAT_ViewportRenderState::ptr)(
                            IO::Graphics::GID_BODY_BRAZIER, 1, 0xf, 7, iVar6, iVar4);
                    }
                    uVar7 = MACRO_CALL_MEMBER(Map::TileMapState_Func::getHeightAtTileIncludingOwnersBuildings,
                        DAT_TileMapState::ptr)(
                        iVar6, (int)((int)(DAT_GameSynchronyState::instance.currentPlayerSlotID)));
                    if (uVar7 == 0) {}
                    if (!bVar14) {}
                    MACRO_CALL_MEMBER(UI::HoveredState_Func::createHoverStateElement, DAT_HoveredState::ptr)(
                        DAT_TileMapState::instance.DAT_ClickedTileX,
                        (int)((int)(DAT_TileMapState::instance.DAT_ClickedTileY)),
                        DAT_TileMapState::instance.currentMapperCommand,
                        (int)((int)(DAT_TileMapState::instance.DAT_BuildingSize)), 0);
                    imageX = (IO::Graphics::GmID)(DAT_TileMapState::instance.DAT_ClickedTileX * 8);
                    imageY = (IO::Graphics::GmID)(DAT_TileMapState::instance.DAT_ClickedTileY * 8);
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = MACRO_CALL_MEMBER(
                        Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(iVar6);
                    if (DAT_TileMapState::instance.mapOrientation == 2) {
                        imageX = (IO::Graphics::GmID)(imageX + IO::Graphics::GID_TILE_BUILDINGS_2);
                    } else if (DAT_TileMapState::instance.mapOrientation == 4) {
                        imageX = (IO::Graphics::GmID)(imageX + IO::Graphics::GID_TILE_BUILDINGS_2);
                        imageY = (IO::Graphics::GmID)(imageY + IO::Graphics::GID_TILE_BUILDINGS_2);
                    } else if (DAT_TileMapState::instance.mapOrientation == 6) {
                        imageY = (IO::Graphics::GmID)(imageY + IO::Graphics::GID_TILE_BUILDINGS_2);
                    }
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = IO::Graphics::GID_TILE_FARMLAND;
                    goto LAB_004467a9;
                }
                if ((((((DAT_TileMapState::instance.currentMapperCommand
                            == Commands::M_MAPPER_PLACE_ASSEMBLY_POINT1)
                           || (DAT_TileMapState::instance.currentMapperCommand
                               == Commands::M_MAPPER_PLACE_ASSEMBLY_POINT2))
                          || (DAT_TileMapState::instance.currentMapperCommand
                              == Commands::M_MAPPER_PLACE_ASSEMBLY_POINT3))
                         || ((DAT_TileMapState::instance.currentMapperCommand
                                 == Commands::M_MAPPER_PLACE_ASSEMBLY_POINT4
                             || (DAT_TileMapState::instance.currentMapperCommand
                                 == Commands::M_MAPPER_PLACE_ASSEMBLY_POINT5))))
                        || (DAT_TileMapState::instance.currentMapperCommand
                            == Commands::M_MAPPER_PLACE_ASSEMBLY_POINT6))
                    || (DAT_TileMapState::instance.currentMapperCommand
                        == Commands::M_MAPPER_PLACE_ASSEMBLY_POINT7)) {
                    MACRO_CALL_MEMBER(
                        Map::Buildings::BuildingsState_Func::createEntityForAssemblyPointsForActiveTabType,
                        DAT_BuildingsState::ptr)();
                    _clickedTile = DAT_ViewportRenderState::instance
                                       .translationMatrix[DAT_TileMapState::instance.DAT_ClickedTileY]
                                       .addXgetTile
                        + DAT_TileMapState::instance.DAT_ClickedTileX;
                    _barracksID
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .barracks.id;
                    if (_barracksID < 1) {
                        bVar14 = false;
                    } else {
                        iVar6 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                      calculateCanPlayerUnitsNavigateToAreaFromArea,
                            DAT_PathFindingState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                            (dword)((int)((int)(short)DAT_TileMapState::instance.PathConnectionLayer
                                    [(int)DAT_GameState::instance
                                            .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                            .barracksParadegroundLocations[0][0]
                                            .x
                                        + DAT_ViewportRenderState::instance
                                            .translationMatrix[DAT_GameState::instance
                                                    .playerDataArray[DAT_GameSynchronyState::instance
                                                            .currentPlayerSlotID]
                                                    .barracksParadegroundLocations[0][0]
                                                    .y]
                                            .addXgetTile])),
                            (dword)((int)((int)(short)DAT_TileMapState::instance.PathConnectionLayer[_clickedTile])),
                            0);
                        bVar14 = iVar6 != 0;
                        if (DAT_TileMapState::instance.BuildingLayer[_clickedTile] == _barracksID) {
                            bVar14 = true;
                        }
                    }
                    if (DAT_MouseState::instance.draggingStopped != FALSE) {
                        if (!bVar14) {}
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                            = DAT_TileMapState::instance.currentMapperCommand
                            - Commands::M_MAPPER_PLACE_ASSEMBLY_POINT1;
                    LAB_004465a6:
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                            = DAT_TileMapState::instance.DAT_ClickedTileX;
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                            = DAT_TileMapState::instance.DAT_ClickedTileY;
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)((Commands::GameCommandType)(Commands::GCT_SHARE_GAME_STATE_PARTIAL_HASHES
                            | Commands::GCT_MULTIPLAYER_INITIATE_ANNOUNCE_HOST));
                        DAT_TileMapState::instance.currentMapperCommand = Commands::M_MAPPER_NULL;
                    }
                LAB_0044654b:
                    if (bVar14) {
                        iVar6 = 0xd;
                        goto LAB_0044655d;
                    }
                LAB_00446558:
                    iVar6 = 0x18000d;
                LAB_0044655d:
                    MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                        DAT_ViewportRenderState::ptr)(
                        IO::Graphics::GID_FLOATS_NEW, 0x61, 0xf, 7, _clickedTile, iVar6);
                }
                /*
                  These mappers are likely wrong in SHC
                 */
                if ((((DAT_TileMapState::instance.currentMapperCommand
                          == Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM1)
                         || (DAT_TileMapState::instance.currentMapperCommand
                             == Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM2))
                        || ((DAT_TileMapState::instance.currentMapperCommand
                                == Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM3
                            || (((DAT_TileMapState::instance.currentMapperCommand
                                         == Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM4
                                     || (DAT_TileMapState::instance.currentMapperCommand
                                         == Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM5))
                                || (DAT_TileMapState::instance.currentMapperCommand
                                    == Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM6))))))
                    || (DAT_TileMapState::instance.currentMapperCommand
                        == Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM7)) {
                    MACRO_CALL_MEMBER(
                        Map::Buildings::BuildingsState_Func::createEntityForAssemblyPointsForActiveTabType,
                        DAT_BuildingsState::ptr)();
                    _clickedTile = DAT_ViewportRenderState::instance
                                       .translationMatrix[DAT_TileMapState::instance.DAT_ClickedTileY]
                                       .addXgetTile
                        + DAT_TileMapState::instance.DAT_ClickedTileX;
                    _mercBuildingID
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .mercenaryPost.id;
                    if (_mercBuildingID < 1) {
                        bVar14 = false;
                    } else {
                        iVar6 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                      calculateCanPlayerUnitsNavigateToAreaFromArea,
                            DAT_PathFindingState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                            (dword)((int)((int)(short)DAT_TileMapState::instance.PathConnectionLayer
                                    [(int)DAT_GameState::instance
                                            .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                            .structure.mercenaryOutpostCampgroundLocations[0]
                                            .x
                                        + DAT_ViewportRenderState::instance
                                            .translationMatrix[DAT_GameState::instance
                                                    .playerDataArray[DAT_GameSynchronyState::instance
                                                            .currentPlayerSlotID]
                                                    .structure.mercenaryOutpostCampgroundLocations[0]
                                                    .y]
                                            .addXgetTile])),
                            (dword)((int)((int)(short)DAT_TileMapState::instance.PathConnectionLayer[_clickedTile])),
                            0);
                        bVar14 = iVar6 != 0;
                        if (DAT_TileMapState::instance.BuildingLayer[_clickedTile] == _mercBuildingID) {
                            bVar14 = true;
                        }
                    }
                    if (DAT_MouseState::instance.draggingStopped != FALSE) {
                        if (!bVar14) {}
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                            = DAT_TileMapState::instance.currentMapperCommand
                            - Commands::M_MAPPER_PEOPLE_ARAB_BOW;
                        goto LAB_004465a6;
                    }
                    goto LAB_0044654b;
                }
                if ((DAT_TileMapState::instance.currentMapperCommand
                        == Commands::M_MAPPER_PLACE_ASSEMBLY_POINTE1)
                    || (DAT_TileMapState::instance.currentMapperCommand
                        == Commands::M_MAPPER_PLACE_ASSEMBLY_POINTE2)) {
                    MACRO_CALL_MEMBER(
                        Map::Buildings::BuildingsState_Func::createEntityForAssemblyPointsForActiveTabType,
                        DAT_BuildingsState::ptr)();
                    _clickedTile = DAT_ViewportRenderState::instance
                                       .translationMatrix[DAT_TileMapState::instance.DAT_ClickedTileY]
                                       .addXgetTile
                        + DAT_TileMapState::instance.DAT_ClickedTileX;
                    _engineersGuildBuildingID
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .engineersGuild.id;
                    if (_engineersGuildBuildingID < 1) {
                        bVar14 = false;
                    } else {
                        iVar6 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                      calculateCanPlayerUnitsNavigateToAreaFromArea,
                            DAT_PathFindingState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                            (dword)((int)((int)(short)DAT_TileMapState::instance.PathConnectionLayer
                                    [(int)DAT_GameState::instance
                                            .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                            .engineersParadegroundLocations[0]
                                            .x
                                        + DAT_ViewportRenderState::instance
                                            .translationMatrix[DAT_GameState::instance
                                                    .playerDataArray[DAT_GameSynchronyState::instance
                                                            .currentPlayerSlotID]
                                                    .engineersParadegroundLocations[0]
                                                    .y]
                                            .addXgetTile])),
                            (dword)((int)((int)(short)DAT_TileMapState::instance.PathConnectionLayer[_clickedTile])),
                            0);
                        bVar14 = iVar6 != 0;
                        if (DAT_TileMapState::instance.BuildingLayer[_clickedTile] == _engineersGuildBuildingID) {
                            bVar14 = true;
                        }
                    }
                    if (DAT_MouseState::instance.draggingStopped != FALSE) {
                        if (!bVar14) {}
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                            = DAT_TileMapState::instance.currentMapperCommand
                            - Commands::M_MAPPER_SUB_MENU_GOOD;
                        goto LAB_004465a6;
                    }
                    goto LAB_0044654b;
                }
                if (DAT_TileMapState::instance.currentMapperCommand
                    == Commands::M_MAPPER_PLACE_ASSEMBLY_POINTT1) {
                    MACRO_CALL_MEMBER(
                        Map::Buildings::BuildingsState_Func::createEntityForAssemblyPointsForActiveTabType,
                        DAT_BuildingsState::ptr)();
                    _clickedTile = DAT_ViewportRenderState::instance
                                       .translationMatrix[DAT_TileMapState::instance.DAT_ClickedTileY]
                                       .addXgetTile
                        + DAT_TileMapState::instance.DAT_ClickedTileX;
                    _tunnelersGuildBuildingID
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .tunnelersGuild.id;
                    if (_tunnelersGuildBuildingID < 1) {
                        bVar14 = false;
                    } else {
                        iVar6 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                      calculateCanPlayerUnitsNavigateToAreaFromArea,
                            DAT_PathFindingState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                            (dword)((int)((int)(short)DAT_TileMapState::instance.PathConnectionLayer
                                    [(int)DAT_GameState::instance
                                            .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                            .tunnelersGuildParadegroundLocations[0]
                                            .x
                                        + DAT_ViewportRenderState::instance
                                            .translationMatrix[DAT_GameState::instance
                                                    .playerDataArray[DAT_GameSynchronyState::instance
                                                            .currentPlayerSlotID]
                                                    .tunnelersGuildParadegroundLocations[0]
                                                    .y]
                                            .addXgetTile])),
                            (dword)((int)((int)(short)DAT_TileMapState::instance.PathConnectionLayer[_clickedTile])),
                            0);
                        bVar14 = iVar6 != 0;
                        if (DAT_TileMapState::instance.BuildingLayer[_clickedTile] == _tunnelersGuildBuildingID) {
                            bVar14 = true;
                        }
                    }
                    if (DAT_MouseState::instance.draggingStopped != FALSE) {
                        if (!bVar14) {}
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 0x1e;
                        goto LAB_004465a6;
                    }
                    goto LAB_0044654b;
                }
                if (DAT_TileMapState::instance.currentMapperCommand
                    == Commands::M_MAPPER_PLACE_ASSEMBLY_POINTK1) {
                    MACRO_CALL_MEMBER(
                        Map::Buildings::BuildingsState_Func::createEntityForAssemblyPointsForActiveTabType,
                        DAT_BuildingsState::ptr)();
                    _clickedTile = DAT_ViewportRenderState::instance
                                       .translationMatrix[DAT_TileMapState::instance.DAT_ClickedTileY]
                                       .addXgetTile
                        + DAT_TileMapState::instance.DAT_ClickedTileX;
                    iVar6 = MACRO_CALL_MEMBER(
                        Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                        DAT_PathFindingState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                        (dword)((int)((int)(short)DAT_TileMapState::instance.PathConnectionLayer
                                [DAT_ViewportRenderState::instance
                                        .translationMatrix[DAT_GameState::instance
                                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                                .campground.yEntry]
                                        .addXgetTile
                                    + DAT_GameState::instance
                                        .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                        .campground.xEntry])),
                        (dword)((int)((int)(short)DAT_TileMapState::instance.PathConnectionLayer[_clickedTile])), 0);
                    bVar14
                        = DAT_BuildingsState::instance.buildings[DAT_TileMapState::instance.BuildingLayer[_clickedTile]]
                              .buildingType
                        == Map::Buildings::BT_CATHEDRAL;
                    if (DAT_MouseState::instance.draggingStopped != FALSE) {
                        if (!bVar14 && iVar6 == 0) {}
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 0x28;
                        goto LAB_004465a6;
                    }
                    if (bVar14 || iVar6 != 0) {
                        iVar6 = 0xd;
                        goto LAB_0044655d;
                    }
                    goto LAB_00446558;
                }
                if (DAT_TileMapState::instance.currentMapperCommand - Commands::M_MAPPER_PEOPLE_ARCHERS
                    < 0x11) {
                    MACRO_CALL(UI::Actions_Func::PlaceUnit)();
                }
                if (DAT_TileMapState::instance.currentMapperCommand - Commands::M_MAPPER_PEOPLE_ARAB_BOW < 8) {
                    MACRO_CALL(UI::Actions_Func::PlaceUnit)();
                }
                DAT_TileMapState::instance.DAT_ClickedTileX = DAT_ViewportRenderState::instance.viewportState.mouseTileX
                    - DAT_TileMapState::instance.DAT_BuildingSize / 2;
                DAT_TileMapState::instance.DAT_ClickedTileY = DAT_ViewportRenderState::instance.viewportState.mouseTileY
                    - DAT_TileMapState::instance.DAT_BuildingSize / 2;
                DAT_TileMapState::instance.DAT_TempBuildingRotation = 0;
                MVar13 = DAT_TileMapState::instance.currentMapperCommand;
                if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
                    if (DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_KEEP1) {
                        if (DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_KEEP2) {
                            if (DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_KEEP3)
                                goto LAB_00445c46;
                            if (DAT_GameCore::instance.mapU2MiddleBytes[2] != 0) {
                                MACRO_CALL_MEMBER(Map::TileMapState_Func::checkBuildingCanBePlacedHere,
                                    DAT_TileMapState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                                    (uint)((int)(DAT_TileMapState::instance.DAT_ClickedTileX)),
                                    (uint)((int)(DAT_TileMapState::instance.DAT_ClickedTileY)),
                                    Commands::M_MAPPER_KEEP3,
                                    (int)((int)(DAT_TileMapState::instance.DAT_BuildingSize)));
                            }
                        }
                        if (DAT_GameCore::instance.mapU2MiddleBytes[1] != 0) {
                            MACRO_CALL_MEMBER(Map::TileMapState_Func::checkBuildingCanBePlacedHere,
                                DAT_TileMapState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                                (uint)((int)(DAT_TileMapState::instance.DAT_ClickedTileX)),
                                (uint)((int)(DAT_TileMapState::instance.DAT_ClickedTileY)),
                                Commands::M_MAPPER_KEEP2,
                                (int)((int)(DAT_TileMapState::instance.DAT_BuildingSize)));
                        }
                    }
                    if (DAT_GameCore::instance.mapU2MiddleBytes[0] != 0) {
                        MVar13 = Commands::M_MAPPER_KEEP1;
                        goto LAB_00445c46;
                    }
                } else {
                LAB_00445c46:
                    MACRO_CALL_MEMBER(Map::TileMapState_Func::checkBuildingCanBePlacedHere,
                        DAT_TileMapState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                        (uint)((int)(DAT_TileMapState::instance.DAT_ClickedTileX)),
                        (uint)((int)(DAT_TileMapState::instance.DAT_ClickedTileY)), MVar13,
                        (int)((int)(DAT_TileMapState::instance.DAT_BuildingSize)));
                }
                switch (DAT_TileMapState::instance.currentMapperCommand) {
                case Commands::M_MAPPER_FLETCHER:
                case Commands::M_MAPPER_BAKER:
                case Commands::M_MAPPER_BREWER:
                case Commands::M_MAPPER_POLETURNER:
                case Commands::M_MAPPER_BLACKSMITH:
                case Commands::M_MAPPER_ARMOURER:
                case Commands::M_MAPPER_TANNER:
                    MACRO_CALL_MEMBER(Map::TileMapState_Func::determineBuildingPlacementRotation,
                        DAT_TileMapState::ptr)(DAT_TileMapState::instance.DAT_ClickedTileX,
                        (int)((int)(DAT_TileMapState::instance.DAT_ClickedTileY)));
                    break;
                case Commands::M_MAPPER_DRAWBRIDGE:
                    MACRO_CALL_MEMBER(Map::TileMapState_Func::checkDrawbridgePlacement, DAT_TileMapState::ptr)(
                        DAT_TileMapState::instance.DAT_ClickedTileX,
                        (int)((int)(DAT_TileMapState::instance.DAT_ClickedTileY)));
                }
                uVar11 = DAT_ViewportRenderState::instance.viewportState.mouseTileY;
                uVar7 = DAT_ViewportRenderState::instance.viewportState.mouseTileX;
                MVar13 = DAT_TileMapState::instance.currentMapperCommand;
                if (((DAT_TileMapState::instance.currentMapperCommand == Commands::M_MAPPER_MOAT)
                        || (DAT_TileMapState::instance.currentMapperCommand == Commands::M_MAPPER_ANTIMOAT))
                    || ((DAT_TileMapState::instance.currentMapperCommand == Commands::M_MAPPER_DUGMOAT
                        || (DAT_TileMapState::instance.currentMapperCommand
                            == Commands::M_MAPPER_UNDUGMOAT)))) {
                    DAT_TileMapState::instance.editorActiveBrush = 2;
                    BVar9 = MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(DAT_ViewportRenderState::instance.viewportState.mouseTileX,
                        (uint)((int)(DAT_ViewportRenderState::instance.viewportState.mouseTileY)));
                    if (BVar9 == FALSE) {}
                    iVar6 = DAT_ViewportRenderState::instance.translationMatrix[uVar11].addXgetTile + uVar7;
                    if (((MVar13 == Commands::M_MAPPER_MOAT)
                            || (MVar13 == Commands::M_MAPPER_DUGMOAT))
                        && (iVar4 = MACRO_CALL_MEMBER(
                                Map::TileMapState_Func::getUnownedMoatCount, DAT_TileMapState::ptr)(),
                            uVar7 = DAT_ViewportRenderState::instance.viewportState.mouseTileX,
                            MVar13 = DAT_TileMapState::instance.currentMapperCommand,
                            uVar11 = DAT_ViewportRenderState::instance.viewportState.mouseTileY, iVar4 < 0xf)) {
                        DAT_TileMapState::instance.buildingPlacementFail = TRUE;
                        MACRO_CALL_MEMBER(Map::TileMapState_Func::renderPreviewMapperWithBrush,
                            DAT_TileMapState::ptr)(DAT_ViewportRenderState::instance.viewportState.mouseTileX,
                            (uint)((int)(DAT_ViewportRenderState::instance.viewportState.mouseTileY)),
                            DAT_TileMapState::instance.currentMapperCommand);
                        MACRO_CALL_MEMBER(UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                            DAT_BottomLeftTextDisplayState::ptr)(
                            1, 8, 0x14d, (TextMessageBLLookupStructUnion)0x0, 100, 6000);
                    }
                    if (((DAT_MouseState::instance.leftClickState == FALSE) || (iVar6 == DAT_00b96110::instance))
                        && (iVar6 = DAT_00b96110::instance, DAT_MouseState::instance.draggingStopped == FALSE)) {
                        MACRO_CALL_MEMBER(Map::TileMapState_Func::renderPreviewMapperWithBrush,
                            DAT_TileMapState::ptr)(uVar7, uVar11, MVar13);
                    }
                    DAT_00b96110::instance = iVar6;
                    BVar9 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::isSignPostWithinDistance,
                        DAT_PathFindingState::ptr)(
                        uVar7, uVar11, DAT_GameState::instance.mapAndTime.unk_signpostDistance + 5);
                    if (BVar9 != FALSE) {
                        MACRO_CALL_MEMBER(UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                            DAT_BottomLeftTextDisplayState::ptr)(
                            1, 0x4d, 0x15, (TextMessageBLLookupStructUnion)0x0, 100, 6000);
                    }
                    if (((DAT_TileMapState::instance.currentMapperCommand == Commands::M_MAPPER_MOAT)
                            || (DAT_TileMapState::instance.currentMapperCommand
                                == Commands::M_MAPPER_ANTIMOAT))
                        && (BVar9 = MACRO_CALL_MEMBER(Map::TileMapState_Func::isValidCastleSiteLocation,
                                DAT_TileMapState::ptr)(DAT_ViewportRenderState::instance.viewportState.mouseTileX,
                                (uint)((int)(DAT_ViewportRenderState::instance.viewportState.mouseTileY)),
                                (int)((int)(DAT_TileMapState::instance.currentMapperCommand))),
                            BVar9 == FALSE)) {}
                    DVar8 = DAT_00b98450::instance;
                    if ((DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY)
                        && (DAT_GameSynchronyState::instance.currentGameMode
                            != Game::GM_SKIRMISH_SINGLE_PLAYER)) {
                        DVar8 = timeGetTime();
                        if (DAT_00b98450::instance == 0) {
                            DVar8 = timeGetTime();
                        } else if (DVar8 - DAT_00b98450::instance < 0xc9) {
                        }
                    }
                    DAT_00b98450::instance = DVar8;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                        = DAT_ViewportRenderState::instance.viewportState.mouseTileX;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                        = DAT_ViewportRenderState::instance.viewportState.mouseTileY;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = 2;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 0x40000000;
                    if (DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_MOAT) {
                        if (DAT_TileMapState::instance.currentMapperCommand == Commands::M_MAPPER_ANTIMOAT) {
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 1;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                                DAT_GameSynchronyState::ptr)(Commands::GCT_SET_TERRAIN);
                        }
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam4
                            = (DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_DUGMOAT)
                            + 2;
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(Commands::GCT_SET_TERRAIN);
                    }
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 0;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(Commands::GCT_SET_TERRAIN);
                }
                if (DAT_TileMapState::instance.currentMapperCommand == Commands::M_MAPPER_PITCH_DITCH) {
                    _pitchDitchCount = MACRO_CALL_MEMBER(
                        Map::TileMapState_Func::countUnownedPitchDitches, DAT_TileMapState::ptr)();
                    if (_pitchDitchCount < 0xf) {
                    LAB_00445d3d:
                        DAT_TileMapState::instance.buildingPlacementFail = TRUE;
                        MACRO_CALL_MEMBER(UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                            DAT_BottomLeftTextDisplayState::ptr)(
                            1, 8, 0x14d, (TextMessageBLLookupStructUnion)0x0, 100, 6000);
                    }
                } else if ((DAT_BuildingsState::instance.unknownCountdown01 < 3)
                    || (((DAT_BuildingsState::instance.unknownCountdown01 < 0xb
                             || (((((DAT_TileMapState::instance.currentMapperCommand
                                            != Commands::M_MAPPER_CATAPULT
                                        && (DAT_TileMapState::instance.currentMapperCommand
                                            != Commands::M_MAPPER_TREBUCHET))
                                       && (DAT_TileMapState::instance.currentMapperCommand
                                           != Commands::M_MAPPER_SIEGE_TOWER))
                                      && ((DAT_TileMapState::instance.currentMapperCommand
                                              != Commands::M_MAPPER_BATTERING_RAM
                                          && (DAT_TileMapState::instance.currentMapperCommand
                                              != Commands::M_MAPPER_PORTABLE_SHIELD))))
                                 && (DAT_TileMapState::instance.currentMapperCommand
                                     != Commands::M_MAPPER_ARAB_BALLISTA))))
                        && ((DAT_TileMapState::instance.currentMapperCommand
                                != Commands::M_MAPPER_TUNNEL_CONSTRUCTION
                            && (DAT_BuildingsState::instance.unknownCountdown01 < 0x14))))))
                    goto LAB_00445d3d;
                if (DAT_MouseState::instance.leftClickStart != 0) {
                    DAT_00b96110::instance = 0;
                }
                if (((DAT_MouseState::instance.leftClickState != FALSE)
                        && (DAT_TileMapState::instance.buildingPlacementFail == FALSE))
                    && (DAT_TileMapState::instance.currentMapperCommand == Commands::M_MAPPER_PITCH_DITCH)) {
                    DVar8 = DAT_00b98454::instance;
                    if ((DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY)
                        && (DAT_GameSynchronyState::instance.currentGameMode
                            != Game::GM_SKIRMISH_SINGLE_PLAYER)) {
                        DVar8 = timeGetTime();
                        if (DAT_00b98454::instance == 0) {
                            DVar8 = timeGetTime();
                        } else if (DVar8 - DAT_00b98454::instance < 0xc9) {
                        }
                    }
                    DAT_00b98454::instance = DVar8;
                    iVar6 = DAT_ViewportRenderState::instance
                                .translationMatrix[DAT_TileMapState::instance.DAT_ClickedTileY]
                                .addXgetTile
                        + DAT_TileMapState::instance.DAT_ClickedTileX;
                    if (DAT_00b96110::instance == iVar6)
                        goto LAB_00445e6f;
                    if (DAT_00b96110::instance == 0) {
                        MACRO_CALL_MEMBER(
                            Map::WallAndPitchState_Func::resetWallAndPitchState, DAT_WallAndPitchState::ptr)();
                    }
                LAB_00445e0c:
                    DAT_00b96110::instance = iVar6;
                    iVar6 = MACRO_CALL_MEMBER(
                        Game::GameStateStructures_Func::checkRequiredResourcesForBuildingOrPlanToBuy,
                        DAT_GameState::ptr)(DAT_TileMapState::instance.currentMapperCommand,
                        (int)((int)(DAT_GameSynchronyState::instance.currentPlayerSlotID)), TRUE);
                    if (iVar6 == 0) {}
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                        = DAT_TileMapState::instance.DAT_ClickedTileX;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                        = DAT_TileMapState::instance.DAT_ClickedTileY;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                        = DAT_TileMapState::instance.currentMapperCommand;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam3
                        = DAT_TileMapState::instance.DAT_BuildingSize;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam4
                        = DAT_TileMapState::instance.field78_0x55488c;
                    if ((DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_GATE_MAIN)
                        && (DAT_TileMapState::instance.currentMapperCommand
                            != Commands::M_MAPPER_GATE_INNER)) {
                        if (DAT_TileMapState::instance.currentMapperCommand
                            == Commands::M_MAPPER_GATE_WOOD1A) {
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 0;
                        } else if (DAT_TileMapState::instance.currentMapperCommand
                            == Commands::M_MAPPER_GATE_WOOD1B) {
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 2;
                        } else if (DAT_TileMapState::instance.currentMapperCommand
                            == Commands::M_MAPPER_GATE_WOOD1C) {
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 4;
                        } else if (DAT_TileMapState::instance.currentMapperCommand
                            == Commands::M_MAPPER_GATE_WOOD1D) {
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 6;
                        } else if (DAT_TileMapState::instance.currentMapperCommand
                            == Commands::M_MAPPER_GATE_STONE1B) {
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 0x50;
                        } else if (DAT_TileMapState::instance.currentMapperCommand
                            == Commands::M_MAPPER_GATE_STONE1A) {
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 0x51;
                        } else if (DAT_TileMapState::instance.currentMapperCommand
                            == Commands::M_MAPPER_GATE_STONE2B) {
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 0x50;
                        } else {
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 0x51;
                            if (DAT_TileMapState::instance.currentMapperCommand
                                != Commands::M_MAPPER_GATE_STONE2A) {
                                DAT_GameSynchronyState::instance.DAT_GameCommandParam4
                                    = DAT_TileMapState::instance.uiBuildingRotation;
                            }
                        }
                    }
                    MACRO_CALL_MEMBER(UI::HoveredState_Func::createHoverStateElement, DAT_HoveredState::ptr)(
                        DAT_TileMapState::instance.DAT_ClickedTileX,
                        (int)((int)(DAT_TileMapState::instance.DAT_ClickedTileY)),
                        DAT_TileMapState::instance.currentMapperCommand,
                        (int)((int)(DAT_TileMapState::instance.DAT_BuildingSize)),
                        (int)((int)(DAT_GameSynchronyState::instance.DAT_GameCommandParam4)));
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam5
                        = DAT_TribesState::instance.DAT_CurrentTribeID;
                    /*
                      called when placing a woodcutter
                     */
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(Commands::GCT_PLACE_BUILDING);
                    if (0x144 < (int)DAT_TileMapState::instance.currentMapperCommand) {
                        switch (DAT_TileMapState::instance.currentMapperCommand) {
                        case Commands::M_MAPPER_POND1:
                        case Commands::M_MAPPER_POND2_SMALL:
                        case Commands::M_MAPPER_POND3_LARGE1:
                        case Commands::M_MAPPER_POND4_LARGE2:
                        case Commands::M_MAPPER_WELL:
                            goto switchD_00446116_caseD_145;
                        default:
                            return;
                        case Commands::M_MAPPER_ARAB_BALLISTA:
                            goto switchD_00446116_caseD_166;
                        }
                    }
                    if (DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_DANCING_BEAR) {
                        if (0xc2 < (int)DAT_TileMapState::instance.currentMapperCommand) {
                            switch (DAT_TileMapState::instance.currentMapperCommand) {
                            case Commands::M_MAPPER_CESS_PIT1:
                            case Commands::M_MAPPER_CESS_PIT2:
                            case Commands::M_MAPPER_CESS_PIT3:
                            case Commands::M_MAPPER_CESS_PIT4:
                            case Commands::M_MAPPER_BURNING_STAKE:
                            case Commands::M_MAPPER_GIBBET:
                            case Commands::M_MAPPER_DUNGEON:
                            case Commands::M_MAPPER_RACK_STRETCHING:
                            case Commands::M_MAPPER_CHOPPING_BLOCK:
                            case Commands::M_MAPPER_DUNKING_STOOL:
                            switchD_004460d6_caseD_12d:
                                MACRO_CALL(UI::Helpers_Func::SetTaxesSetting_unknown)(3);
                                return;
                            default:
                                return;
                            case Commands::M_MAPPER_STATUE1:
                            case Commands::M_MAPPER_STATUE2:
                            case Commands::M_MAPPER_STATUE3:
                            case Commands::M_MAPPER_STATUE4:
                            case Commands::M_MAPPER_STATUE5:
                            case Commands::M_MAPPER_SHRINE1:
                            case Commands::M_MAPPER_SHRINE2:
                            case Commands::M_MAPPER_SHRINE3:
                            case Commands::M_MAPPER_SHRINE4:
                            case Commands::M_MAPPER_SHRINE5:
                                goto switchD_00446116_caseD_145;
                            }
                        }
                        if ((int)DAT_TileMapState::instance.currentMapperCommand < 0xbe) {
                            switch (DAT_TileMapState::instance.currentMapperCommand) {
                            case Commands::M_MAPPER_TUNNEL_CONSTRUCTION:
                                goto switchD_004460ba_caseD_42;
                            default:
                                return;
                            case Commands::M_MAPPER_GARDEN1:
                            case Commands::M_MAPPER_GARDEN2:
                            case Commands::M_MAPPER_GARDEN3:
                            case Commands::M_MAPPER_GARDEN4:
                            case Commands::M_MAPPER_GARDEN5:
                            case Commands::M_MAPPER_GARDEN6:
                            case Commands::M_MAPPER_GARDEN7:
                            case Commands::M_MAPPER_GARDEN8:
                            case Commands::M_MAPPER_GARDEN9:
                            case Commands::M_MAPPER_GARDEN10:
                            case Commands::M_MAPPER_GARDEN11:
                            case Commands::M_MAPPER_GARDEN12:
                            case Commands::M_MAPPER_MAYPOLE:
                                goto switchD_00446116_caseD_145;
                            case Commands::M_MAPPER_GALLOWS:
                            case Commands::M_MAPPER_STOCKS:
                                goto switchD_004460d6_caseD_12d;
                            }
                        }
                    switchD_00446116_caseD_166:
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(
                            0x15);
                    switchD_004460ba_caseD_42:
                        DAT_TileMapState::instance.currentMapperCommand = Commands::M_MAPPER_NULL;
                    }
                switchD_00446116_caseD_145:
                    MACRO_CALL(UI::Helpers_Func::SetTaxesSetting_unknown)(2);
                }
            LAB_00445e6f:
                if (DAT_MouseState::instance.draggingStopped != FALSE) {
                    iVar6 = DAT_00b96110::instance;
                    if (DAT_TileMapState::instance.buildingPlacementFail != FALSE) {
                        if (DAT_TileMapState::instance.buildingPlacementFailReason == ((BuildingFailReasonEnum)1000)) {
                            /*
                              added by script: "Too many dog cages"
                             */
                            MACRO_CALL_MEMBER(
                                UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                                DAT_BottomLeftTextDisplayState::ptr)(
                                1, 0x101, 2, (TextMessageBLLookupStructUnion)0x0, 100, 6000);
                        }
                        if (DAT_TileMapState::instance.buildingPlacementFailReason
                            != Map::Buildings::BFRE_DEFAULT_CANT_PLACE_THAT_THERE) {
                            MACRO_CALL_MEMBER(
                                UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                                DAT_BottomLeftTextDisplayState::ptr)(1, 0x4d,
                                (int)((int)(DAT_TileMapState::instance.buildingPlacementFailReason)),
                                (TextMessageBLLookupStructUnion)0x0, 100, 6000);
                            MACRO_CALL(UI::Helpers_Func::PlayPlacementWarning)(DAT_TileMapState::instance.buildingPlacementFailReason);
                        }
                        if (DAT_TileMapState::instance.placementWarning != 0) {
                            MACRO_CALL(UI::Helpers_Func::PlayPlacementWarning)(
                                Map::Buildings::BFRE_DEFAULT_CANT_PLACE_THAT_THERE1
                                - DAT_TileMapState::instance.placementWarning);
                        }
                        if ((DAT_TileMapState::instance.currentMapperCommand == Commands::M_MAPPER_PITCH_DITCH)
                            && (DAT_00b96110::instance != 0)) {}
                        MACRO_CALL(UI::Helpers_Func::PlayPlacementWarning)(Map::Buildings::BFRE_DEFAULT_CANT_PLACE_THAT_THERE1);
                    }
                    goto LAB_00445e0c;
                }
                if (((int)DAT_TileMapState::instance.currentMapperCommand < 0xbe)
                    || (((0xc2 < (int)DAT_TileMapState::instance.currentMapperCommand
                             && (DAT_TileMapState::instance.currentMapperCommand
                                 != Commands::M_MAPPER_ARAB_BALLISTA))
                        || (DAT_TileMapState::instance.buildingPlacementFail != FALSE)))) {
                    /*
                      special check for some types?
                     */
                    MACRO_CALL_MEMBER(Map::TileMapState_Func::setConstructionGFXLayerBasedOnPlacementChecks,
                        DAT_TileMapState::ptr)(DAT_TileMapState::instance.DAT_ClickedTileX,
                        (int)((int)(DAT_TileMapState::instance.DAT_ClickedTileY)),
                        DAT_TileMapState::instance.currentMapperCommand,
                        (int)((int)(DAT_TileMapState::instance.DAT_BuildingSize)));
                }
                /*
                  Do for the 5 siege engines
                 */
                uVar16 = 0;
                uVar17 = 0;
                uVar7 = DAT_TileMapState::instance.DAT_ClickedTileY;
                uVar11 = DAT_TileMapState::instance.DAT_ClickedTileX;
                switch (DAT_TileMapState::instance.mapOrientation) {
                case 0:
                    uVar16 = 0xd;
                    uVar11 = DAT_TileMapState::instance.DAT_ClickedTileX + 1;
                    uVar7 = DAT_TileMapState::instance.DAT_ClickedTileY + 1;
                    uVar17 = 2;
                    break;
                case 2:
                    uVar16 = 0x2d;
                    uVar11 = DAT_TileMapState::instance.DAT_ClickedTileX - 1;
                    uVar7 = DAT_TileMapState::instance.DAT_ClickedTileY + 1;
                    uVar17 = -0xe;
                    break;
                case 4:
                    uVar16 = 0xd;
                    uVar11 = DAT_TileMapState::instance.DAT_ClickedTileX - 1;
                    uVar17 = -0x1e;
                    goto LAB_00445eed;
                case 6:
                    uVar16 = -0x13;
                    uVar11 = DAT_TileMapState::instance.DAT_ClickedTileX + 1;
                    uVar17 = -0xc;
                LAB_00445eed:
                    uVar7 = DAT_TileMapState::instance.DAT_ClickedTileY - 1;
                }
                MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                    DAT_ViewportRenderState::ptr)((IO::Graphics::GmID)(82), 1, uVar16, uVar17,
                    (int)((int)(DAT_ViewportRenderState::instance.translationMatrix[uVar7].addXgetTile + uVar11)), 5);
            }
            iVar6 = DAT_ViewportRenderState::instance
                        .translationMatrix[DAT_ViewportRenderState::instance.viewportState.mouseTileY]
                        .addXgetTile
                + DAT_ViewportRenderState::instance.viewportState.mouseTileX;
            imageY = local_4;
            imageX = local_4;
            switch (DAT_TileMapState::instance.currentMapperCommand) {
            case Commands::M_MAPPER_FLAG_TYPE0:
                local_8 = 9;
                imageY = IO::Graphics::GID_TILE_BUILDINGS_2;
                imageX = IO::Graphics::GID_TILE_GOODS;
                break;
            case Commands::M_MAPPER_FLAG_TYPE1:
                local_8 = 0x29;
                imageY = ~IO::Graphics::GID_TILE_NULL_1;
                imageX = IO::Graphics::GID_TILE_GOODS;
                break;
            case Commands::M_MAPPER_FLAG_TYPE2:
                local_8 = 0x49;
                imageY = IO::Graphics::GID_TILE_BUILDINGS_1;
                imageX = IO::Graphics::GID_TILE_BUILDINGS_1;
                break;
            case Commands::M_MAPPER_FLAG_TYPE3:
                local_8 = 1;
                imageY = IO::Graphics::GID_TILE_BUILDINGS_2;
                imageX = IO::Graphics::GID_TILE_BUILDINGS_1;
            }
            if (DAT_MouseState::instance.draggingStopped == FALSE) {
                local_4 = IO::Graphics::GID_ANIM_FLAGS;
                if (DAT_TileMapState::instance.currentMapperCommand == Commands::M_MAPPER_FLAG_TYPE3) {
                    local_4 = IO::Graphics::GID_ANIM_CRUSADER_FLAG;
                }
                iVar4 = MACRO_CALL_MEMBER(Map::TileMapState_Func::getTotalHeightAt, DAT_TileMapState::ptr)(
                    iVar6, (int)((int)(DAT_GameSynchronyState::instance.currentPlayerSlotID)));
                if ((-1 < iVar4) && ((DAT_TileMapState::instance.MiscDisplayLayer[iVar6] & 0x1000) == 0)) {
                    MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                        DAT_ViewportRenderState::ptr)(
                        local_4, local_8, (int)((int)(imageX)), (int)((int)(imageY)), iVar6, 0xd);
                }
                MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                    DAT_ViewportRenderState::ptr)(
                    local_4, local_8, (int)((int)(imageX)), (int)((int)(imageY)), iVar6, 0x18000d);
            }
            GVar10 = MACRO_CALL_MEMBER(Map::TileMapState_Func::getTotalHeightAt, DAT_TileMapState::ptr)(
                iVar6, (int)((int)(DAT_GameSynchronyState::instance.currentPlayerSlotID)));
            if ((int)GVar10 < 0) {}
            if ((DAT_TileMapState::instance.MiscDisplayLayer[iVar6] & 0x1000) != 0) {}
            local_4 = GVar10;
            switch (DAT_TileMapState::instance.currentMapperCommand) {
            case Commands::M_MAPPER_FLAG_TYPE0:
                GVar10 = IO::Graphics::GID_TILE_WALLS;
                break;
            case Commands::M_MAPPER_FLAG_TYPE1:
                imageY = DAT_TileMapState::instance.DAT_ClickedTileY * 8;
                imageX = DAT_TileMapState::instance.DAT_ClickedTileX * 8;
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_TileMapState::instance.DAT_ClickedTileX,
                    (int)((int)(DAT_TileMapState::instance.DAT_ClickedTileY)), DE::SHCDE::FX_LARGE_FLAG);
                GVar10 = IO::Graphics::GID_TILE_NULL_11;
                goto switchD_004466e9_caseD_4;
            case Commands::M_MAPPER_FLAG_TYPE2:
                GVar10 = IO::Graphics::GID_TILE_LAND_3;
                break;
            case Commands::M_MAPPER_FLAG_TYPE3:
                GVar10 = IO::Graphics::GID_TILE_NULL_13;
                break;
            default:
                goto switchD_004466e9_caseD_4;
            }
            imageY = DAT_TileMapState::instance.DAT_ClickedTileY * 8;
            imageX = DAT_TileMapState::instance.DAT_ClickedTileX * 8;
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                DAT_TileMapState::instance.DAT_ClickedTileX, (int)((int)(DAT_TileMapState::instance.DAT_ClickedTileY)),
                DE::SHCDE::FX_SMALL_FLAG);
        switchD_004466e9_caseD_4:
            MACRO_CALL_MEMBER(UI::HoveredState_Func::createHoverStateElement, DAT_HoveredState::ptr)(
                DAT_TileMapState::instance.DAT_ClickedTileX, (int)((int)(DAT_TileMapState::instance.DAT_ClickedTileY)),
                DAT_TileMapState::instance.currentMapperCommand,
                (int)((int)(DAT_TileMapState::instance.DAT_BuildingSize)), 0);
            DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = local_4;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam5
                = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = GVar10;
        LAB_004467a9:
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = imageX;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = imageY;
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                Commands::GCT_SPAWN_ENTITY);
        }

    }
}
}
