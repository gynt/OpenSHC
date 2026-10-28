/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Rendering/ViewportState.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Rendering {

#pragma pack(push, 1)
    // SIZE: 0x000000B4
    typedef struct ViewportState {

        // 1 when the cursor is inside the map view and not over a menu rectangle (updateBuildingPreviewPosition);
        // gates map clicks/drags in many UI handlers.
        undefined4 mouseOverMap; // 0x00000000 length: 4
        int mouseTileX; // 0x00000004 length: 4
        int mouseTileY; // 0x00000008 length: 4
        int mouseTile; // 0x0000000C length: 4
        // Mouse tile at which the map editor/peasant mapper tool was last applied (-1 initially); prevents re-
        // applying on the same tile while dragging.
        int lastMapperTile; // 0x00000010 length: 4
        // LogicLayer value of the tile under the cursor.
        undefined4 mouseTileLogicFlags; // 0x00000014 length: 4
        // BuildingLayer value (building ID) of the tile under the cursor.
        undefined4 mouseTileBuildingID; // 0x00000018 length: 4
        int mouseRayBuildingID; // 0x0000001C length: 4
        // UnitLayer value (first unit ID) of the tile under the cursor.
        undefined4 mouseTileUnitID; // 0x00000020 length: 4
        int mouseRayEntityID; // 0x00000024 length: 4
        int mouseRayUnitID; // 0x00000028 length: 4
        undefined4 field11_0x2c; // 0x0000002C length: 4
        int mouseRayLastUnitID; // 0x00000030 length: 4
        // timeGetTime() when a unit was last hit by the mouse ray; used for a 200 ms grace period in the
        // peasant/right-click handler.
        undefined4 mouseRayUnitTimeMs; // 0x00000034 length: 4
        // LogicLayer 0x40000000 (moat) flag of the target tile when the moat belongs to another team, else 0.
        undefined4 mouseOnEnemyMoat; // 0x00000038 length: 4
        // Moat flag (0x40000000) of the target tile when the moat belongs to the player's team;
        // evaluateBuildingPlacementAtCursor then uses the walk target tile.
        undefined4 mouseOnOwnMoat; // 0x0000003C length: 4
        // LogicLayer bit 0x4000 of the target tile when it is an own-team moat, else 0.
        undefined4 mouseOwnMoatFlag4000; // 0x00000040 length: 4
        // pitch ditch under the mouse, target of the ignite order; hover* like hoverAttackTargetUnitID
        int hoverPitchDitchID; // 0x00000044 length: 4
        // BuildingWasLayer type of a ruin under the cursor; shown as "This was a ..." tooltip.
        undefined4 mouseRuinBuildingType; // 0x00000048 length: 4
        // Sub-tile X index of the cursor (MapRenderDefinedData.screenCellSubTileX).
        undefined4 mouseSubTileX; // 0x0000004C length: 4
        // Sub-tile Y index of the cursor (MapRenderDefinedData.screenCellSubTileY).
        undefined4 mouseSubTileY; // 0x00000050 length: 4
        // Wall tile hit by the mouse ray (0 if none); used by delete action, hover info and building placement.
        undefined4 mouseWallTile; // 0x00000054 length: 4
        // Micro X offset for the cursor sub-tile (UnitProperties microPosScreenOffsets).
        undefined4 mouseMicroOffsetX; // 0x00000058 length: 4
        // Micro Y offset for the cursor sub-tile.
        undefined4 mouseMicroOffsetY; // 0x0000005C length: 4
        // Standable target tile under the cursor (walls/tower tops resolved), 0 if none; used for move commands and
        // building placement.
        undefined4 mouseTargetTile; // 0x00000060 length: 4
        int mouseX; // 0x00000064 length: 4
        int mouseY; // 0x00000068 length: 4
        // 1 when mouseTargetTile is a wall/raised tile (LogicLayer 0x10000300 without bit 2).
        undefined4 mouseTargetRaised; // 0x0000006C length: 4
        int mouseAtomRefFloorTile; // 0x00000070 length: 4
        // [182 0x004E8CF0] points to the map-surface pixel under the mouse (camera+mouse, pitch 0xfd8); COL_MAGENTA
        // is written there and checked after drawing to set mouseRayUnitID/mouseRayBuildingID
        ushort* mousePickPixelPtr; // 0x00000074 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        int viewportX; // 0x00000078 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        int viewportY; // 0x0000007C length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        int currentCameraOffsetX; // 0x00000080 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        int currentCameraOffsetY; // 0x00000084 length: 4
        // 0x4E5C41: (..-[this+0x88]+4)<<5 = X limit in 32-px columns; 30 at 800x600. Horizontal count, not height
        // Unsigned Double-Word (ddw, 4-bytes)
        int viewportTileColumns; // 0x00000088 length: 4
        // 0x4E5C38: (0x191-[this+0x8C]-..)*8 = Y limit in 8-px rows (~height/8). Vertical count, not width Unsigned
        // Double-Word (ddw, 4-bytes)
        int viewportTileRows; // 0x0000008C length: 4
        // [047 0x004B2AE0] Z and Ctrl+Up toggle zoom via resetupViewport(isZoomedOutUnk == 0); it is the current
        // zoom-state boolean Unsigned Double-Word (ddw, 4-bytes)
        int isZoomedOut; // 0x00000090 length: 4
        // When non-zero renderMap starts drawing 64 (128 zoomed out) pixels higher; only zeroed by the constructor.
        undefined4 extraTopRenderMargin; // 0x00000094 length: 4
        // [182 0x004E8CF0] set to zoomOffset*0x20+0x46 and used as the tile screen X at the start of every row
        // (+0x10 on shifted rows)
        undefined4 rowStartScreenX; // 0x00000098 length: 4
        int tileCenterX; // 0x0000009C length: 4
        int tileCenterY; // 0x000000A0 length: 4
        undefined4 someYOffset; // 0x000000A4 length: 4
        undefined4 someXOffset; // 0x000000A8 length: 4
        // [180 0x004E5E20] viewportX = (column - mbr_0xac)*32 centres the view on the column; resetupViewport
        // converts origin<->centre with it (value ~half the screen width in 32-px columns) Unsigned Double-Word
        // (ddw, 4-bytes)
        dword centerColumnOffset; // 0x000000AC length: 4
        // [180 0x004E5E20] viewportY = (row - mbr_0xb0)*8 centres the view on the row; resetupViewport uses it the
        // same way (not exactly half of viewportWidth, so not a plain half size) Unsigned Double-Word (ddw,
        // 4-bytes)
        dword centerRowOffset; // 0x000000B0 length: 4

    } ViewportState;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(ViewportState) == 180, ViewportState);
} // namespace Rendering
} // namespace OpenSHC
