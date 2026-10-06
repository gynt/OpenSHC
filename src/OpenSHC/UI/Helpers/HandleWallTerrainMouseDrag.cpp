#include "../Helpers.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_ScrollingHandler.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace UI {

    using Commands::GameCommandType;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00437CC0
    void Helpers::HandleWallTerrainMouseDrag()
    {
        int iVar2;
        int iVar3;
        if (!DAT_ViewportRenderState::instance.viewportState.field0_0x0) {}
        if (!DAT_TileMapState::instance.flatViewToggleValue1) {
            MACRO_CALL_MEMBER(
                Rendering::ViewportRenderState_Func::setupMouseTileXY, DAT_ViewportRenderState::ptr)();
        } else {
            MACRO_CALL_MEMBER(
                Rendering::ViewportRenderState_Func::setupMouseTileXY2, DAT_ViewportRenderState::ptr)();
        }
        if (!DAT_MouseState::instance.leftClickStart) {
            if ((DAT_MouseState::instance.draggingStopped != FALSE)
                || (DAT_MouseState::instance.leftClickState != FALSE)) {
                DAT_TileMapState::instance.dragEndX = DAT_ViewportRenderState::instance.viewportState.mouseTileX;
                DAT_TileMapState::instance.dragEndY = DAT_ViewportRenderState::instance.viewportState.mouseTileY;
                goto LAB_00437d7f;
            }
            if (DAT_ScrollingHandler::instance.isScrolling_0x0 != FALSE) {}
            DAT_TileMapState::instance.dragStartX = DAT_ViewportRenderState::instance.viewportState.mouseTileX;
            DAT_TileMapState::instance.dragStartY = DAT_ViewportRenderState::instance.viewportState.mouseTileY;
            DAT_TileMapState::instance.dragEndX = DAT_ViewportRenderState::instance.viewportState.mouseTileX;
            DAT_TileMapState::instance.dragEndY = DAT_ViewportRenderState::instance.viewportState.mouseTileY;
        } else {
            DAT_TileMapState::instance.dragStartX = DAT_ViewportRenderState::instance.viewportState.mouseTileX;
            DAT_TileMapState::instance.dragStartY = DAT_ViewportRenderState::instance.viewportState.mouseTileY;
        LAB_00437d7f:
            if (DAT_MouseState::instance.draggingStopped != FALSE) {
                iVar2 = DAT_ViewportRenderState::instance.translationMatrix[DAT_TileMapState::instance.dragStartY]
                            .addXgetTile
                    + DAT_TileMapState::instance.dragStartX;
                if ((DAT_TileMapState::instance.LogicLayer[iVar2] & 0x100000U)) {
                    MACRO_CALL_MEMBER(
                        Map::Navigation::DirectionAlgorithmState_Func::calculatePreferredRelativeOrientation,
                        DAT_DirectionAlgorithmState::ptr)(DAT_TileMapState::instance.dragStartX,
                        (int)(DAT_TileMapState::instance.dragStartY), (int)(DAT_TileMapState::instance.dragEndX),
                        (int)(DAT_TileMapState::instance.dragEndY));
                    iVar3 = DAT_DirectionAlgorithmState::instance.orientation;
                    if (DAT_DirectionAlgorithmState::instance.orientation == 0xf) {
                        iVar3 = 0;
                    }
                    DAT_TileMapState::instance.WallGFXLayer[iVar2] = (ushort)iVar3;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = DAT_TileMapState::instance.dragStartY;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = DAT_TileMapState::instance.dragStartX;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = 1;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 0x100000;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 0x20;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(Commands::GCT_SET_TERRAIN);
                }
            }
        }
        iVar3 = DAT_ViewportRenderState::instance.translationMatrix[DAT_TileMapState::instance.dragStartY].addXgetTile
            + DAT_TileMapState::instance.dragStartX;
        MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::calculatePreferredRelativeOrientation,
            DAT_DirectionAlgorithmState::ptr)(DAT_TileMapState::instance.dragStartX,
            (int)(DAT_TileMapState::instance.dragStartY), (int)(DAT_TileMapState::instance.dragEndX),
            (int)(DAT_TileMapState::instance.dragEndY));
        iVar2 = DAT_DirectionAlgorithmState::instance.orientation;
        if (DAT_DirectionAlgorithmState::instance.orientation == 0xf) {
            iVar2 = 0;
        }
        ushort uVar1 = (ushort)iVar2;
        if (!DAT_TileMapState::instance.mapOrientation) {
        LAB_00437dcd:
            uVar1 = (short)GMTotalPicturesProcessed::instance[5] + 0x38c + uVar1 * 8;
        } else {
            if (DAT_TileMapState::instance.mapOrientation == 2) {
                uVar1 = uVar1 - 2;
            } else {
                if (DAT_TileMapState::instance.mapOrientation == 4) {
                    uVar1 = uVar1 - 4 & 7;
                    goto LAB_00437dcd;
                }
                uVar1 = uVar1 + 2;
            }
            uVar1 = (short)GMTotalPicturesProcessed::instance[5] + 0x38c + (uVar1 & 7) * 8;
        }
        if (DAT_MouseState::instance.leftClickState != FALSE) {
            if ((DAT_TileMapState::instance.LogicLayer[iVar3] & 0x100000U)) {
                DAT_TileMapState::instance.ConstructionGFXLayer[iVar3] = uVar1;
            }
            DAT_TileMapState::instance.buildingPlacementFail = FALSE;
        }
        DAT_TileMapState::instance.buildingPlacementFail = TRUE;
        MACRO_CALL_MEMBER(Map::TileMapState_Func::renderPreviewMapperWithBrush, DAT_TileMapState::ptr)(
            DAT_ViewportRenderState::instance.viewportState.mouseTileX,
            (uint)(DAT_ViewportRenderState::instance.viewportState.mouseTileY),
            DAT_TileMapState::instance.currentMapperCommand);
    }

}
}
