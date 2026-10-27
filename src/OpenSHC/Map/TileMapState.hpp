/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/TileMapState.hpp'
*/

#pragma once

#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Commands/MappersEnumShort.hpp"
#include "OpenSHC/Game/Player/PlayerID.hpp"
#include "OpenSHC/IO/PackagedFileMagicNum.hpp"
#include "OpenSHC/Map/Buildings/BuildingFailReasonEnumInt.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic2.hpp"
#include "OpenSHC/Map/Moat.hpp"
#include "OpenSHC/Map/PitchDitch.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::Game::Player::PlayerID;
    using OpenSHC::IO::PackagedFileMagicNum;
    using OpenSHC::Map::Moat;
    using OpenSHC::Map::PitchDitch;
    using OpenSHC::Map::Buildings::BuildingFailReasonEnumInt;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::LogicHelpers::Logic1;
    using OpenSHC::Map::LogicHelpers::Logic2;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x00554A88
    class TileMapState {
    public:
        int directionTranslationMatrix[400][8]; // 0x00000000 length: 12800
        // [094 0x004F6B20] yArray1[row] receives the tile count of each map row (2..400..2);
        // updateLogicalTileMapRelatedSections uses it as the per-row loop bound
        int rowTileCount[400]; // 0x00003200 length: 1600
        int heightBasedScreenYOffset[256]; // 0x00003840 length: 1024
        int unusedTileMap[80400]; // 0x00003C40 length: 321600
        ushort GfxLayer[80400]; // 0x00052480 length: 160800
        // read as GM overlay/wall-connection image (review 360) and written with stockpile building id by
        // placeStockpile: multi-use layer [096 0x004FAF70] used as index into DAT_BuildingsState.buildings for
        // stockpile pathable tiles and zeroed on removal
        ushort overlayImageOrStockpileIdLayer[80400]; // 0x000798A0 length: 160800
        ushort ConstructionGFXLayer[80400]; // 0x000A0CC0 length: 160800
        ushort PillarGFXLayer[80400]; // 0x000C80E0 length: 160800
        // wall image on wall tiles but per-tile animation counter on sea/animated tiles (review 360); PascalCase as
        // other TileMapState layers
        ushort WallGfxOrAnimCounterLayer[80400]; // 0x000EF500 length: 160800
        ushort FloatingLayer[80400]; // 0x00116920 length: 160800
        ushort RandomLayer[80400]; // 0x0013DD40 length: 160800
        int LogicLayer[80400]; // 0x00165160 length: 321600
        byte unknownData1[1600]; // 0x001B39A0 length: 1600
        char Logic2Layer[80400]; // 0x001B3FE0 length: 80400
        byte unknownData2[400]; // 0x001C79F0 length: 400
        char ChangedLayer[80400]; // 0x001C7B80 length: 80400
        short OrganismLayer[80400]; // 0x001DB590 length: 160800
        short BuildingLayer[80400]; // 0x002029B0 length: 160800
        uchar BuildingWasLayer[80400]; // 0x00229DD0 length: 80400
        ushort UnitLayer[80400]; // 0x0023D7E0 length: 160800
        short EntityLayer[80400]; // 0x00264C00 length: 160800
        byte EntityLayerLT25[80400]; // 0x0028C020 length: 80400
        byte HeightLayer[80400]; // 0x0029FA30 length: 80400
        byte DefaultHeightLayer[80400]; // 0x002B3440 length: 80400
        byte WallOwnerLayer[80400]; // 0x002C6E50 length: 80400
        uchar LuminesenceLayer[80400]; // 0x002DA860 length: 80400
        uchar ShowHiLayer[80400]; // 0x002EE270 length: 80400
        short MiscDisplayLayer[80400]; // 0x00301C80 length: 160800
        // Wall damage counter elsewhere, crop stage marks on farm tiles; shared layer. PascalCase kept like sibling
        // *Layer fields.
        byte DamageOrCropStageLayer[80400]; // 0x003290A0 length: 80400
        ushort MacroLayer[80400]; // 0x0033CAB0 length: 160800
        ushort PathConnectionLayer[80400]; // 0x00363ED0 length: 160800
        uchar PathLinkageLayer[80400]; // 0x0038B2F0 length: 80400
        uchar OccupancyLayer[80400]; // 0x0039ED00 length: 80400
        // BFS distance from start (3 uses); gfx pass reuse as scratch noted. PascalCase like sibling layers.
        short SearchDistanceLayer[80400]; // 0x003B2710 length: 160800
        // Decomp shows writes/compares with searchGeneration (BFS visited stamp) only; not walkability. PascalCase
        // like sibling layers.
        short SearchGenerationLayer[80400]; // 0x003D9B30 length: 160800
        byte AIZoneLayer[80400]; // 0x00400F50 length: 80400
        uchar AIInfoLayer[80400]; // 0x00414960 length: 80400
        uchar unitDeathHeatMap[80400]; // 0x00428370 length: 80400
        uchar SEC_TileMap1104[80400]; // 0x0043BD80 length: 80400
        // [092 0x004A7090] byte[9][80400] at 0x1EE2998 filled with BFS distance from AIZoneLayer==1 tiles
        uchar aiZoneDistanceLayers[9][80400]; // 0x0044F790 length: 723600
        // Start of section row (Y) loop; min of y/10 of reached tiles.
        int dirtySectionRowMin; // 0x00500220 length: 4
        // Inclusive end of section row (Y) loop.
        int dirtySectionRowMax; // 0x00500224 length: 4
        // Section column start (tileX = col*10), verified in machine code 0x4FF0E0; X, not Y.
        int dirtySectionColMin; // 0x00500228 length: 4
        // Inclusive end of section column (X) loop.
        int dirtySectionColMax; // 0x0050022C length: 4
        char mapping40x40[40][40]; // 0x00500230 length: 1600
        Moat moats[16000]; // 0x00500870 length: 256000
        // Upper bound of used moat slots (highest index+1), reset with maxEntityCount etc.; not a live count.
        int maxMoatCount; // 0x0053F070 length: 4
        undefined4 moatTileCount; // 0x0053F074 length: 4
        undefined4 ALG_MoatXResult; // 0x0053F078 length: 4
        undefined4 ALG_MoatYResult; // 0x0053F07C length: 4
        int someMoatTile; // 0x0053F080 length: 4
        PitchDitch pitchDitches[4000]; // 0x0053F084 length: 80000
        int maxPitchDitchCount; // 0x00552904 length: 4
        undefined1 padding_0x552908[4]; // 0x00552908 length: 4
        short specialAreasArray[8]; // 0x0055290C length: 16
        // [097 0x004FC340] count of entries, capped at 1000
        int dustCloudSourceCount; // 0x0055291C length: 4
        // [097 0x004FC490] incremented every call, compared mod 500/1200/64 for dust cloud timing
        int dustCloudTick; // 0x00552920 length: 4
        // [097 0x004FC490] random countdown; variant-1 sources spawn only when it is 0
        int dustCloudVariant1PauseCountdown; // 0x00552924 length: 4
        // [097 0x004FC490] random countdown; variant-0 sources spawn only when it is 0
        int dustCloudVariant0PauseCountdown; // 0x00552928 length: 4
        // [097 0x004FC340] filled with tile indices here and iterated only by generateDustClouds to spawn
        // ET_DUST_CLOUD
        int dustCloudSourceTiles[1000]; // 0x0055292C length: 4000
        // [097 0x004FC340] 0/1 per source tile, read as piVar4[1000] in generateDustClouds and passed to
        // spawnEntity
        int dustCloudSourceVariant[1000]; // 0x005538CC length: 4000
        undefined4 forceUpdateLogicalAndMiscDisplayLayers; // 0x0055486C length: 4
        int forceUpdateTextureTilemap; // 0x00554870 length: 4
        int forceUpdateGFXLayers; // 0x00554874 length: 4
        int forceUpdateMacroLayerFlag; // 0x00554878 length: 4
        // Set to 500 after map setup/prepareMap and 200 after edits/placement, always together with
        // forceUpdateMacroLayerFlag; write-only in this build (no reader in clean.exe)
        undefined4 macroLayerUpdateDelay; // 0x0055487C length: 4
        undefined1 padding_0x554880[8]; // 0x00554880 length: 8
        undefined4 placedBuildingID; // 0x00554888 length: 4
        // Gate orientation code 0x50/0x51: auto-toggled every second by rotateFearFactorBuildingVariations, forced
        // to 0x51 for gate types A/C and 0x50 for B/D in setConstructionGFXLayerBasedOnPlacementChecks, selects
        // buildingSpriteID1/2 for the preview and is sent as GameCommandParam4 (building orientation) when placing
        // main/inner gates
        undefined4 gatePreviewOrientation; // 0x0055488C length: 4
        undefined4 rockOrientation; // 0x00554890 length: 4
        // Selected big-rock brush in map editor landscaping (1..5, 0 = none); type 5 cycles rockOrientation
        undefined4 editorBigRockType; // 0x00554894 length: 4
        undefined4 lastTime; // 0x00554898 length: 4
        int mapOrientation; // 0x0055489C length: 4
        undefined4 DAT_FutureMapOrientation; // 0x005548A0 length: 4
        // Direction index (mapOrientation+3) of the tile toward the viewer; used for occlusion and 'face camera'
        // units
        int viewDirFront; // 0x005548A4 length: 4
        // Direction index mapOrientation+2 (neighbour next to the front direction), used in occlusion checks
        int viewDirFrontLeft; // 0x005548A8 length: 4
        // Direction index mapOrientation+4 (other neighbour of the front direction)
        int viewDirFrontRight; // 0x005548AC length: 4
        // Direction index front+2 (mapOrientation 0/2/4/6 -> 5/7/1/3), set in changeMapOrientation; write-only in
        // clean.exe
        int viewDirFrontPlus2; // 0x005548B0 length: 4
        // +1 or -1 row step toward the viewer depending on map orientation
        int viewRowStep; // 0x005548B4 length: 4
        // [099 0x00501A20] values 1-4 select how heightBasedScreenYOffset is set/animated; reset to 0 when finished
        undefined4 heightOffsetAnimMode; // 0x005548B8 length: 4
        undefined4 refreshCertainTileMap_old; // 0x005548BC length: 4
        // [099 0x00501A20] incremented each animation step, cleared when animation ends
        undefined4 heightAnimFrame; // 0x005548C0 length: 4
        // set 1 when height transition reaches the full-height table (modes 2/4), 0 when flattened; gates height Y
        // offsets (review 360)
        undefined4 fullHeightViewActive; // 0x005548C4 length: 4
        // When non-zero, height/occlusion handling would be disabled like flatViewToggleValue2 (no ShowHi layer,
        // flat mouse picking, plain rock gfx); only ever zeroed (constructor) in clean.exe, i.e. a dead debug
        // toggle
        undefined4 flatViewMode; // 0x005548C8 length: 4
        undefined4 flatViewToggleValue1; // 0x005548CC length: 4
        // accessed by 0x512313, 0x512580
        undefined4 field_0x5548d0; // 0x005548D0 length: 4
        undefined4 flatViewToggleValue2; // 0x005548D4 length: 4
        undefined4 refreshRelatedTwo; // 0x005548D8 length: 4
        // editorActiveBrush saved when switching to editor test mode, restored on return
        undefined4 savedEditorBrush; // 0x005548DC length: 4
        undefined4 editorActiveBrush; // 0x005548E0 length: 4
        MappersEnum currentMapperCommand; // 0x005548E4 length: 4
        undefined4 DAT_BuildingSize; // 0x005548E8 length: 4
        // Number of units spawned per editor/placement click (PlaceUnit); reset to 1
        undefined4 placeUnitCount; // 0x005548EC length: 4
        BOOLEnum mapperMax; // 0x005548F0 length: 4
        undefined4 rockFlagStartNumber; // 0x005548F4 length: 4
        // [226 0x004314E0] always editorActiveBrush >> 1
        undefined4 editorBrushRadius; // 0x005548F8 length: 4
        // [226 0x004314E0] cycled 0->1->2->0 by M_MAPPER_SNAP_TO
        undefined4 mapperSnapMode; // 0x005548FC length: 4
        undefined4 unknownZero_0x554900; // 0x00554900 length: 4
        // Toggled by M_MAPPER_AFFECT_TYPE; selects water/land tiles affected by terrain edit.
        undefined4 mapperAffectType; // 0x00554904 length: 4
        // Scratch variant/rotation index used while computing wall/pillar/ramp tile graphics
        undefined4 tmpGfxVariant; // 0x00554908 length: 4
        undefined4 dragStartX; // 0x0055490C length: 4
        undefined4 dragStartY; // 0x00554910 length: 4
        undefined4 dragEndX; // 0x00554914 length: 4
        undefined4 dragEndY; // 0x00554918 length: 4
        BOOLEnum illegalBuild; // 0x0055491C length: 4
        // Cleared at the start of validateWallBuildPath, set to 1 once the start tile passed its checks and the
        // drag path is traced; renderWallDragPreview draws only the single 'invalid' start marker for stairs while
        // it is 0
        undefined4 wallPathStartValid; // 0x00554920 length: 4
        // Max wall height in the brush area at the stair start; stair placement steps down from it
        undefined4 stairStartHeight; // 0x00554924 length: 4
        undefined4 DAT_ClickedTileX; // 0x00554928 length: 4
        undefined4 DAT_ClickedTileY; // 0x0055492C length: 4
        // When 1 placeBuilding skips placement checks (skirmish start, statues, version upgrade); cleared after use
        undefined4 forcePlaceBuilding; // 0x00554930 length: 4
        // [101 0x005037B0] typed BOOLEnum but set to 2 for off-map / LogicLayer&0x30 tiles, distinct from TRUE
        BOOLEnum buildingPlacementResult; // 0x00554934 length: 4
        BuildingFailReasonEnumInt buildingPlacementFailReason; // 0x00554938 length: 4
        undefined4 placementWarning; // 0x0055493C length: 4
        undefined4 uiBuildingRotation; // 0x00554940 length: 4
        // rotation*16 or drawbridge side*50: frame offset for placement preview, not just a rotation code.
        // Placement rotation relative to the view: ((uiBuildingRotation - mapOrientation) mod 8) * 16 (0x80 =
        // none/failed), rotation*0x32 for drawbridges, 0 reset; write-only in clean.exe
        undefined4 placementPreviewGfxOffset; // 0x00554944 length: 4
        undefined4 buildingSpriteSheetID_1; // 0x00554948 length: 4
        undefined4 buildingSpriteID1; // 0x0055494C length: 4
        undefined4 buildingSpriteID2; // 0x00554950 length: 4
        // Holds building id or -pitchDitchID (or -1); not building-only. delete prefix kept like sibling fields.
        // Building under the delete cursor (negative = pitch ditch ID); sent as command param 0 for destroy
        undefined4 deleteTargetID; // 0x00554954 length: 4
        undefined4 buildingHeightLimit; // 0x00554958 length: 4
        int buildingMinHeight; // 0x0055495C length: 4
        int buildingMaxHeight; // 0x00554960 length: 4
        undefined4 buildingMaxHeightDifference; // 0x00554964 length: 4
        undefined4 buildingPlacementProperty_3; // 0x00554968 length: 4
        undefined4 buildingPlacementProperty_4; // 0x0055496C length: 4
        undefined4 buildingPlacementProperty_5; // 0x00554970 length: 4
        undefined4 buildingPlacementProperty_6; // 0x00554974 length: 4
        undefined4 buildingPlacementProperty_7; // 0x00554978 length: 4
        undefined1 padding_0x55497c[4]; // 0x0055497C length: 4
        // 1 when the left button was not held when the wall command was triggered; 0 shows wall-loss preview
        undefined4 wallPreviewButtonUp; // 0x00554980 length: 4
        int constructionTileCount; // 0x00554984 length: 4
        int DAT_WallTileCountCurrentDrag; // 0x00554988 length: 4
        undefined4 buildingX; // 0x0055498C length: 4
        undefined4 buildingY; // 0x00554990 length: 4
        // [095 0x004F9880] selected from DAT_BuildingSizeIndexMapping columns 2..5 by mapOrientation; added to
        // rock/building gfx base to pick the image piece for each footprint tile
        undefined4 rotatedFootprintPieceIndex; // 0x00554994 length: 4
        // Set when delete target is an own wall tile; read by DeleteAction. Delete tool currently dragging over own
        // wall tiles
        undefined4 deleteTargetIsWall; // 0x00554998 length: 4
        // Set when delete target is own-team moat tile; read by DeleteAction. Delete tool currently dragging over
        // moat tiles (filling moat)
        undefined4 deleteTargetIsMoat; // 0x0055499C length: 4
        // Moat tile under the delete cursor; sent as command param 0 for moat removal
        undefined4 deleteTargetMoatTile; // 0x005549A0 length: 4
        int showNoRubbleWhenDestroyingBuilding; // 0x005549A4 length: 4
        // X result of findNearestValidDigTileNearTarget: tile 2 away from the target enemy (or the target X itself)
        // that findNearestEnemyAndHeadTowardsIt sends the unit to
        undefined4 approachTileX; // 0x005549A8 length: 4
        // Y result of findNearestValidDigTileNearTarget: tile 2 away from the target enemy (or the target Y itself)
        // that findNearestEnemyAndHeadTowardsIt sends the unit to
        undefined4 approachTileY; // 0x005549AC length: 4
        int wallPlacementCost; // 0x005549B0 length: 4
        int DAT_TempBuildingRotation; // 0x005549B4 length: 4
        // Set during unit control / size query; renderMap then highlights moat-marked tiles; cleared at end of
        // renderMap
        int showMoatDigHighlight; // 0x005549B8 length: 4
        // timeGetTime of last step of floatAnimFrame (decided_2 renamed cursorAnimFrame -> floatAnimFrame); steps
        // every 70 ms
        undefined4 floatAnimLastTickMs; // 0x005549BC length: 4
        // Added to GID_FLOATS_NEW base ids for all overhead floats/markers in ViewportRenderState, not just the
        // cursor Cursor/marker animation frame 1..16, advanced every ~70 ms
        undefined4 floatAnimFrame; // 0x005549C0 length: 4
        // Base frame of the mouse action icon in cursorIconGmID
        undefined4 cursorIconFrameBase; // 0x005549C4 length: 4
        // GM sprite sheet of the mouse action icon (0x6b default, 0xac no-entry/move, 0x10 siege)
        undefined4 cursorIconGmID; // 0x005549C8 length: 4
        // Frame count used for animated cursor icons (cursorAnimTick % count)
        undefined4 cursorIconFrameCount; // 0x005549CC length: 4
        // Free-running counter incremented every ~70 ms; drives animated cursor icons and assembly markers
        undefined4 cursorAnimTick; // 0x005549D0 length: 4
        undefined4 DAT_SelectionIconType; // 0x005549D4 length: 4
        // Pending click action under cursor: -10 unreachable, -1 invalid, 0 none, 1 attack, 2 man building, 3 man
        // siege, 4 engineer, 5 attack wall, 6 attack unit, 10/11 engineer ops, 12 pitch
        undefined4 cursorActionType; // 0x005549D8 length: 4
        undefined1 padding_0x5549dc[8]; // 0x005549DC length: 8
        // Values 0 none, 1 units selected, 2/3 drag-select (3 shift-add), 4/5 tactical-power targeting; not only
        // shift.
        int mapInteractionMode; // 0x005549E4 length: 4
        // Unit ID targeted by the pending cursor action (siege engine to man, etc.)
        undefined4 cursorTargetUnitID; // 0x005549E8 length: 4
        // Selected tactical power bar action (param of TacticalPowerBar handler, e.g. 2,3,4,6)
        undefined4 tacticalPowerType; // 0x005549EC length: 4
        // Mouse X captured at click for attack-ground / throw-cow commands
        undefined4 actionTargetX; // 0x005549F0 length: 4
        // Mouse Y captured at click for attack-ground / throw-cow commands
        undefined4 actionTargetY; // 0x005549F4 length: 4
        // [222 0x004348D0] unit under the cursor in weapon range; passed with DAT_SomeUNitUIDUIRelated (its uid) to
        // UIT_UNIT_ATTACK_UNIT on click
        undefined4 hoverAttackTargetUnitID; // 0x005549F8 length: 4
        // always units[hoverAttackTargetUnitID].uid, checked before UIT_UNIT_ATTACK_UNIT
        undefined4 hoverAttackTargetUnitUID; // 0x005549FC length: 4
        // Mouse X stored together with actionTargetX when the left click starts; write-only in clean.exe
        undefined4 clickStartMouseX; // 0x00554A00 length: 4
        // Mouse Y stored together with actionTargetY when the left click starts; write-only in clean.exe
        undefined4 clickStartMouseY; // 0x00554A04 length: 4
        // Extra parameter (set 0xf) sent with attack-ground / throw-cow commands
        undefined4 groundAttackParam; // 0x00554A08 length: 4
        int mapSize; // 0x00554A0C length: 4
        // Value interpolated toward signpost distance over 40 ticks; passed to pathfinding. Cached (40 -
        // gameEventRelatedCountdown) * unk_signpostDistance / 40 last passed to pathfindingUpdate_0x4a8ab0; set to
        // -1 when the countdown starts (40) to force the first update
        undefined4 currentSignpostDistance; // 0x00554A10 length: 4
        // Set by calculateHoveredTile; setConstructionGFXLayerBasedOnPlacementChecks then draws without failure
        // checks and clears it
        undefined4 previewSkipChecks; // 0x00554A14 length: 4
        undefined1 padding_0x554a18[4]; // 0x00554A18 length: 4
        // Random variant 0..6 chosen when selecting the heads-on-spikes decoration (+1 sent on placement)
        undefined4 headsOnSpikesVariant; // 0x00554A1C length: 4
        // Set when deletion is blocked (enemy too close); cursor shows the blocked icon
        undefined4 deleteBlockedByEnemy; // 0x00554A20 length: 4
        // Skirmish launch flag: placeKeep demolishes buildings in the keep footprint once
        undefined4 clearKeepFootprintOnPlace; // 0x00554A24 length: 4
        undefined1 padding_0x554a28[8]; // 0x00554A28 length: 8
        // Set to 1 whenever buildings/walls/terrain change (placement, erase, damage, tunneling, resync); no reader
        // found in clean.exe
        int terrainChangedDirty; // 0x00554A30 length: 4
        // [105 0x00509180] column of the tile currently being processed; reset to sectionCol*10 per row,
        // incremented per inner-loop step, passed to xyAreValid/translateXYToTile
        int curTileX; // 0x00554A34 length: 4
        // [105 0x00509180] row = sectionRow*10 + rowInSection, passed to translateXYToTile and used as
        // directionTranslationMatrix row
        int curTileY; // 0x00554A38 length: 4
        // Current tile index of the scan loop, index into every layer.
        int curTileIndex; // 0x00554A3C length: 4
        // Scratch 8-bit mask of neighbours matching a flag (4 uses); British spelling as sibling fields.
        undefined1 neighbourMask; // 0x00554A40 length: 1
        undefined1 padding_0x554a41[3]; // 0x00554A41 length: 3
        undefined4 DAT_CardinalTilesAroundTile; // 0x00554A44 length: 4
        // 24-bit mask of enemy-occupied tiles in the 5x5 neighbourhood computed by processMeleeInitiation
        undefined4 meleeNeighbourMask; // 0x00554A48 length: 4
        undefined1 padding_0x554a4c[4]; // 0x00554A4C length: 4
        // Height of the neighbour tile in the view direction (0 if water, 0x14 if flagged) used for cliff gfx; read
        // with movsx (signed)
        undefined2 tmpNeighbourHeight; // 0x00554A50 length: 2
        undefined1 padding_0x554a52[6]; // 0x00554A52 length: 6
        pointer ptr_LogicLayer; // 0x00554A58 length: 4
        pointer ptr_TerrainTypeTileMap; // 0x00554A5C length: 4
        pointer ptr_TerrainHeightTileMap; // 0x00554A60 length: 4
        pointer ptr_ChangedLayer; // 0x00554A64 length: 4
        pointer ptr_MovementDirectionTranslationMatrix; // 0x00554A68 length: 4
        pointer ptr_OccupancyLayer; // 0x00554A6C length: 4
        pointer ptr_DamageLayer; // 0x00554A70 length: 4
        pointer ptr_PathConnectionLayer; // 0x00554A74 length: 4
        pointer ptr_AIZoneLayer; // 0x00554A78 length: 4
        pointer ptr_SpecialAreasArray; // 0x00554A7C length: 4
        pointer ptr_MiscDisplayLayer; // 0x00554A80 length: 4
        undefined1 padding_0x554a84[4]; // 0x00554A84 length: 4

    private:
        TileMapState(TileMapState const&);
        void operator=(TileMapState const&);

    public:
        TileMapState() {};
        ~TileMapState() {};

        // Constructor
        /**
         * Static constructor of the global TileMapState: builds direction/size lookup tables, clears all tile
         * layers, initialises editor/refresh flags and timers, sets the layer shortcut pointers (logic, changed,
         * terrain type, height, path, occupancy, damage, misc display, AI zone) and the moat/pitch-ditch array
         * limits (16000/4000).
         */
        TileMapState* Constructor_TileMapState();

        /**
         * Thunk: calls processEntityDamageToBuildingCollateral on DAT_TileMapState with the same arguments plus a
         * trailing 0.
         */
        void processEntityDamageToBuildingCollateralThunk(
            int tile, uint x_2, uint y_2, int damage, int playerID, undefined4 unused);

        /**
         * Thunk used by unit update routines: calls processDamageToBuilding on DAT_TileMapState with the same
         * arguments plus unitID = 0 and returns its BOOL result. The pass-through 5th argument, when nonzero, makes
         * processDamageToBuilding zero the damage to wall tiles and skip the wall height reduction.
         */
        BOOLEnum processDamageToBuildingThunk(int targetedTile, uint targetedTileX, uint targetedTileY, int damage,
            int param_5, int playerID, BOOLEnum aiBuildDelayRelated);

        /**
         * Forces a full map redraw: fills all 80400 bytes of TileMapState.ChangedLayer (0x1C5AD88) and the 40x40
         * section map (mapping40x40, 1600 bytes) with 3, then calls setChangedLayerZeroBasedOn40x40Layer(1).
         */
        void setChangedLayerToThreeAndMapping0x40x40();

        /**
         * Builds TileMapState.directionTranslationMatrix: for each of the 400 rows of the diamond-shaped map, the 8
         * tile-index offsets to the neighbouring tiles (which depend on the lengths of the rows above/below), and
         * yArray1[row] = number of tiles in the row (2,4,...,398 for rows 0-198, 400 for rows 199/200, 398,...,2
         * for rows 201-399). Rows 199 and 200 (the two middle rows) are filled explicitly after the first loop. The
         * writes to cells [199][4]/[200][5] inside the first loop are a decompiler artefact: the row length is kept
         * in a register (eax) and only stored at the end.
         */
        void setupMovementDirectionTranslationMatrix();

        /**
         * Initialises the map edge in LogicLayer for the full 400-wide diamond by plain assignment (other flags of
         * those tiles are overwritten): in every row the first and last tile get 0x10 (outer border) and the second
         * and second-to-last tile get 0x20 (inner border); other tiles are not touched. Upper half rows widen by 2,
         * lower half narrow by 2.
         */
        void setupLogicalMapBorders();

        /**
         * Sets DAT_TileMapState.mapSize, removes all existing border flags (0x30) from LogicLayer (restoring those
         * tiles' height from DefaultHeightLayer), re-marks the full-map diamond edge (0x10 outer, 0x20 inner) and
         * then the edge of the inset playable diamond for mapSize (margin (400-mapSize)/2). For smaller maps calls
         * setWalkabilityBorderLogicLayerForSmallerMapSizes; finally sets the height of every border tile to 8.
         */
        void resetHeightAndMapBorders(int mapSize);

        /**
         * Map editor: steps to the next map size: picks the first entry of DAT_TerrainDefinedData.MapSizes that is
         * smaller than `size` and stores it in DAT_TileMapState.mapSize; if the list's -1 terminator is reached,
         * wraps around to MapSizes[0].
         */
        void setMapSize(int size);

        /**
         * Chooses the terrain view mode: 2 while flat view (flatViewToggleValue2) is on, else viewMode. If it
         * differs from refreshCertainTileMap_old, resets counter1 and stores it in refreshCertainTileMap; when that
         * new mode is 3 and the game is not paused, updates two byte fields of every non-invisible wandering
         * civilian unit (drunk, rabbit, hunter dog, jester, chicken, child, juggler, fire eater): one to (sum of
         * two short fields)/10 capped at 14, the other to 0.
         */
        void triggerLoweredView(int viewMode);

        /**
         * Sets flatViewToggleValue1 and flatViewToggleValue2 to the new flat-view value when it differs from the
         * current one.
         */
        void toggleFlatView(int flatView);

        /**
         * Empty function (single ret 4); its argument is ignored.
         */
        void noop1(undefined4 unused1);

        /**
         * Stores newRotation in DAT_TileMapState.DAT_FutureMapOrientation (applied later).
         */
        void setMapRotation(undefined4 newRotation);

        /**
         * If forceUpdateLogicalAndMiscDisplayLayers is set (cleared here), walks rows mappingYRelated..dirtyMaxY and
         * for every changed (ChangedLayer != 0), non-border tile recomputes display data: LogicLayer bit 0x8000
         * (set for height 1-8, for height 0 from Logic2Layer 0x20 / flag 0x40000000, above 8 from Logic2Layer bits;
         * cleared at a height step to a neighbour without 0x40100000), ShowHiLayer (0xff when terrain up to 8 tiles
         * toward the camera hides the tile, 8 when field93_0x5548c8 is set, else tileScreenY minus the lowest of
         * three neighbours' screen Y) and MiscDisplayLayer bits 0x10/1/2 (edge/side flags from neighbour heights,
         * walls, stockpiles, drawbridges and building flags).
         */
        void updateLogicalTileMapRelatedSections();

        /**
         * Sets ShowHiLayer[t] = heightBasedScreenYOffset[height[t]] for all 80400 tiles (the height byte layer lies
         * 0x4e840 bytes before ShowHiLayer), 8 tiles per iteration.
         */
        void rebuildShowHiLayerFromHeights();

        /**
         * Computes the shading value 0..7 of `tile` (row tileY) into LuminesenceLayer; skips border/structure tiles
         * (LogicLayer 0x10000430). Base shade 2 (tree tiles: growth stage if > 2; flag 0x2000 tiles: 5). Casts a
         * 5-tile ray in the orientation-dependent light direction and two parallel 5-tile side rays, comparing each
         * tile's effective height (terrain, + max(16, building height) unless getBuildingFlag3, + tree growth
         * stage*7, + 40 for flag 0x2000) with the tile's own height to raise the shade. If the side rays dominate,
         * shade = sideA + sideB - 2 capped at 7; else if the shade is still 2, a slope check of the neighbours in
         * and against the light direction gives 1 or 0 (skipped on LogicLayer 0x40000000 tiles).
         */
        void computeTileLuminescence(int tile, int tileY);

        /**
         * Tunneler digging: if the tile has none of the LogicLayer flags 0x70300500/0xb1 and no building, changes
         * its height by `increment` (only when current or default height is below 16 and the result stays >= 0),
         * then always updates walk/path layers (mode 4) and path linkages around it.
         */
        void increaseHeightForTunnelSingleTile(int tile, uint x, uint y, int increment);

        /**
         * Returns currentHealth of the building on `tile` if BuildingLayer > 0, its logicalState is neither 0 nor
         * BLS_REMOVE, currentHealth != 0, its type has health and the tile has none of the LogicLayer flags
         * 0xf000000; otherwise returns 1000.
         */
        int getNonFarmFieldBuildingHealthAtTileOr1000(int tile);

        /**
         * Clears LogicLayer flags 0x410B00 on the tile (mask 0xffbef4ff, same mask used when walls are removed),
         * restores its height from DefaultHeightLayer, destroys entities on it and updates walk/path layers (mode
         * 5) at (x,y).
         */
        void resetTileToDefaultState(int tile, uint x, uint y);

        /**
         * Picks the hit-sound category for a tile (the parameter named buildingID is really a tile index). With no
         * building on the tile it returns 2 if the LogicLayer wall bit 0x100 is set, else 0. For a building whose
         * logicalState is neither 0 nor BLS_REMOVE and whose health is > 0 it returns 2 for stone/large structures
         * (keeps, towers, gatehouses, churches, barracks, stockpile, armory, guilds, outpost) and 1 for all other
         * types; otherwise 0.
         */
        uint getBuildingHurtSFXID(int buildingID);

        /**
         * Called from processGameTick to animate the build-cursor previews. When field80_0x554894 == 5,
         * rockOrientation steps 0->2->4->6->0 on every call. Once per second (timeGetTime vs lastTime) it toggles
         * field78_0x55488c between 0x50 and 0x51, steps rockOrientation the same way if field80 == 0, and advances
         * currentMapperCommand to the next variant of the decorative (fear-factor) building being placed: gardens,
         * cess pits, statues, shrines, ponds, wrapping back to the first variant.
         */
        void rotateFearFactorBuildingVariations();

        /**
         * Counts how many of the 4 cardinal neighbours (direction indices 0,2,4,6 of directionTranslationMatrix[y])
         * of `tile` have any of the `logic1` LogicLayer bits, and stores the count (0..4) in
         * DAT_CardinalTilesAroundTile. Returns nothing.
         */
        void countLogicPropertyInSurroundingTiles(int tile, int y, uint logic1);

        /**
         * NAME? Returns 1 as soon as ANY cardinal neighbour (checked in order 0,4,2,6) is a plain wall tile:
         * LogicLayer 0x100 (L_WALL_OR_GATEHOUSE) set and neither 0x2 nor 0x200 (L_CRENEL) set. Returns 0 if none
         * is. It is not an enclosure test (confirmed in machine code: early 'mov eax,1' exit on the first match).
         */
        BOOLEnum hasCardinalPlainWallNeighbourNoCrenel(int tile, int y);

        /**
         * NAME? Returns 1 as soon as ANY of the 4 cardinal neighbours (order 0,4,2,6) has LogicLayer 0x100
         * (L_WALL_OR_GATEHOUSE) without bit 0x2; otherwise 0. One such neighbour is enough, so this is not an
         * enclosure test (confirmed in machine code). Used by validateWallBuildPath.
         */
        undefined4 hasCardinalWallNeighbour(int tile, int y);

        /**
         * For direction 0/4 it requires neighbours 0 and 4 to have LogicLayer bit 0x200 (L_CRENEL) and neighbours 2
         * and 6 not to; for 2/6 the roles are swapped. Returns TRUE when that pattern matches, else FALSE; any
         * other direction value uses index 0 for all four checks and always returns FALSE. NAME? This detects a
         * straight run of crenel tiles through the tile, not a corner. Used by updateGfxLayer.
         */
        BOOLEnum isWallCornerForCardinalDirection(int tile, int y, int direction);

        /**
         * Maps a diagonal direction to an L-shaped pattern: 1 -> neighbours 4,6 set and 0,2 clear; 3 -> 0,6 set,
         * 4,2 clear; 5 -> 0,2 set, 4,6 clear; 7 -> 4,2 set, 0,6 clear, where set/clear refers to LogicLayer bit
         * 0x200 (L_CRENEL). Returns 1 when the pattern matches, else 0 (other direction values always give 0). Used
         * by updateGfxLayer to pick crenel corner gfx.
         */
        uint isWallCornerForDiagonalDirection(int tile, int y, int direction);

        /**
         * Checks the two opposite neighbours on the axis of `direction` (0/4 -> dirs 0,4; 2/6 -> dirs 2,6; other
         * values check dir 0 twice). Returns 1 only if both are wall tiles (0x100 set, 0x2 clear) and each one is
         * either damaged (DamageLayer != 0) or at least as high as the tile's own height - 16. Otherwise returns 0.
         * __thiscall on DAT_TileMapState (ret 0xC).
         */
        BOOLEnum isWallConnectionHeightValid(int tileOrSecondNeighbour, int y, int direction);

        /**
         * Counts cardinal neighbours that have LogicLayer bit 0x10000 (L_UNKNOWN_WALL_RELATED, a tower bit
         * according to the function name) and, separately, neighbours that are walls (0x100) without that bit.
         * Returns TRUE if at least one 0x10000 neighbour exists and no plain wall neighbour does. Used by
         * placeWalls.
         */
        BOOLEnum hasOnlyTowerNeighborsNoWalls(int tile, int y);

        /**
         * Accepts screen direction 2 or 4 and returns 0 for anything else. It rotates the direction by
         * mapOrientation into a world neighbour index (dir 2: orientation 0/2/4/6 -> 2/4/6/0; dir 4: -> 4/6/0/2;
         * unknown orientation -> 0) and returns that neighbour's wall bit (LogicLayer 0x100) as 0/1. __thiscall on
         * DAT_TileMapState (ret 0xC).
         */
        uint getWallFlagForOrientedDirection(int tile, int y, int screenDirection);

        /**
         * Rotates `direction` by mapOrientation (mod 8) and finds that neighbour (an unknown orientation uses
         * direction 0). Returns TRUE if the neighbour is higher than the tile (HeightLayer) and has the stairs bit
         * (LogicLayer 0x800, L_STAIRS).
         */
        BOOLEnum hasHigherNeighborWithStairs(int tile, int y, int direction);

        /**
         * Rotates `direction` by mapOrientation (mod 8) and finds that neighbour. Returns TRUE if the neighbour is
         * higher than the tile and is a wall/gatehouse tile (0x100) without bits 0x200 (L_CRENEL) and 0x2.
         */
        BOOLEnum hasHigherPlainNeighborWithWallOrGatehouse(int tile, int y, int direction);

        /**
         * For an on-map (x,y), walks DAT_TerrainDefinedData.SomeOrientationOrderArray (end hardcoded at 0xB4ADA0).
         * Returns the first direction whose neighbour is a wall/gatehouse tile (0x100) without bits 0x400002 (0x2
         * and 0x400000 L_CRENEL_MERLON). Returns 15 if none is found or the coordinates are invalid. Used by
         * the ladderman to find a wall to climb.
         */
        int getOrientationThatIsWallTowerOrGatehouse(uint x, uint y);

        /**
         * Walks from (x1,y1) to (x2,y2) and writes the drag preview into ConstructionGFXLayer, counting placeable
         * tiles in DAT_WallTileCountCurrentDrag (stops at constructionTileCount). Commands: 0x19 M_MAPPER_WALL,
         * 0x1A M_MAPPER_CRENAL, 0x1B M_MAPPER_STAIR, 0x2E M_MAPPER_WOODWALL. Wall/woodwall/crenel step diagonally;
         * stairs step one axis at a time, start at field119_0x554924 height, lose 16 per step and stop on wall
         * tiles or below 0x18 (if field118 == 0 the start tile is just marked red). Wall drawn over a crenel
         * (0x200) tile is not counted. Red gfx (+0x13/+0x14) is used when illegalBuild. Finally, if field145 == 0,
         * calls processWallBuildingLoss with the count as stone (or as wood for 0x2E).
         */
        void renderWallDragPreview(int playerID, uint x1, uint y1, uint x2, uint y2, undefined4 command);

        /**
         * Scans every tile (loop unrolled by 6) and gives wall tiles (LogicLayer 0x100) to toPlayer by writing
         * WallOwnerLayer low 3 bits = toPlayer-1. A tile without a building changes owner when its old owner was
         * fromPlayer; a tile with a building changes owner when that building's owner already equals toPlayer
         * (presumably buildings were transferred earlier in changePlayerOwnership).
         */
        void reassignWallOwnershipForPlayer(int fromPlayer, int toPlayer);

        /**
         * Scans every tile (loop unrolled by 6, 0x13A10 tiles) and swaps the owners of wall tiles (LogicLayer
         * 0x100) between playerA and playerB in WallOwnerLayer (low 3 bits = owner-1): a tile owned by A becomes
         * B's and one owned by B becomes A's; other owners are untouched.
         */
        void swapWallOwnership(int playerA, int playerB);

        /**
         * For every wall tile (0x100) owned by playerID: destroys the entities on it and clears LogicLayer bits
         * 0x100, 0x200, 0x800, 0x10000 and 0x400000 (mask 0xFFBEF4FF). It also resets HeightLayer to
         * DefaultHeightLayer, clears DamageLayer, sets the area/section refresh flags and updates path linkages and
         * the walk layer.
         */
        void destroyWallsOfPlayer(int playerID);

        /**
         * Checks whether a wall/crenel/defensive piece can go at (x,y). Sets illegalBuild = TRUE and clears it only
         * if: the tile is not a wall (or its DamageLayer > 11), has no 0x400 (L_BUILDING), no building, none of
         * 0x14 (farm/border) and none of 0x60300081 (sea, rocky, river, ford, marsh, moat);
         * isEnemyTooCloseUnk(...,5) is FALSE; and findSomeSuitableLocationUnk(...,2) returns 0. When placing a
         * crenel (M_MAPPER_CRENAL/CRENAL2) on a non-wall tile with a unit on it, that unit is set to ULS_REMOVE.
         */
        void validateWallPlacementAtTile(int playerID, uint x, uint y, OpenSHC::Commands::MappersEnumShort mapperCommand);

        /**
         * Clears DAT_BuildingSizeIndexMapping[buildingSize] (169 entries x 6 ints) and, for sizes > 1, fills it:
         * [0],[1] = (x, y) of each footprint index, then 4 passes walk the footprint's 2*size-1 diagonals and write
         * a descending index (from size*size-1) into [2..5], one column per mapOrientation 0/2/4/6 (the rotated
         * footprint piece order). Entry index = (size*169 + row*size + col); the buildingSize parameter is reused
         * as a diagonal start offset in pass 4, hence the saved copy.
         */
        void setupBuildingSizeIndexMappingForBuildingWithSize(int buildingSizeThenDiagOffset);

        /**
         * Loads footprint entry footprintIndex of a buildingSize x buildingSize footprint: constructionTileCount =
         * size*size, buildingX/buildingY = the tile offsets, rotatedFootprintPieceIndex = the entry's piece index
         * for the current mapOrientation (columns 2..5 for 0/2/4/6). __thiscall on DAT_TileMapState (ret 8), ECX
         * preserved. The EAX return value is inconsistent (piece index for orientations 0/4, the entry's byte
         * offset otherwise) and is evidently not meaningful.
         */
        void getBuildingSizeIndexMappingData(int footprintIndex, int buildingSize);

        /**
         * Returns TRUE if footprint index `counter` lies on the border of a size x size footprint (first/last row
         * or first/last column). Footprints smaller than 3 count as all edge.
         */
        BOOLEnum isFootprintIndexOnEdge(int counter, int size);

        /**
         * Scans every footprint tile of a size buildingWidthAndHeight footprint at (x,y) and records the lowest and
         * highest HeightLayer values in buildingMinHeight/buildingMaxHeight (initialised to 1000 and 0).
         * extraout_ECX is DAT_TileMapState (getBuildingSizeIndexMappingData preserves ECX): 0x55498C buildingX,
         * 0x554990 buildingY, 0x554984 constructionTileCount, 0x55495C/0x554960 min/max, 0x29FA30 HeightLayer.
         */
        void storeMinAndMaxHeightOfArea(uint x, uint y, int buildingWidthAndHeight);

        /**
         * Checks one footprint tile for building `commandBuildingType`. Returns 0 if allowed, 1 if blocked, 2 if
         * another building is there. Checks in order: height limit (placementWarning 1..4 for farms), max height
         * difference, pitch ditch on 0x8, building, units, sea (0x1), border (0x30), river (0x100000), own-wall
         * rule (only gates/towers on the player's own walls), 0x4 farm footprint and 0x10000400 keep/building,
         * trees (0x3000; most tree types block unless the player is AI outside GM_SOLITARY), farm fields 0xF000000
         * and ford 0x200000. Last, bare rock (0x80), moat 0x40000000 and marsh 0x20000000 are allowed only via
         * buildingPlacementProperty_4/7/6. relaxedCheck != 0 skips the 0x4 and farm-field checks.
         */
        int isBuildingPlacementBlockedAtTile(int tile, int playerID, MappersEnum commandBuildingType, int relaxedCheck);

        /**
         * Eraser/demolish target check (callers: clearBuildingFromTerrain, eraseAreaWithBrush, useEraserBrush).
         * buildingPlacementResult (TRUE = not erasable) starts TRUE if the tile has no building or the building
         * belongs to someone else (playerID 0 = any owner). On a bare wall tile it returns early (result unchanged)
         * unless the player owns the wall, in which case it is cleared. It is then set TRUE again unless the tile
         * has LogicLayer 0x10000400 or the building is a gate, keep door, drawbridge, campground, parade ground,
         * campfire or killing pit. On the normal path the building id is stored in deleteTargetID. Returns the tile
         * index or building type (not meaningful). __thiscall (ret 0xC), ECX preserved.
         */
        void validateEraseTargetAtTile(int playerID, int x, int y);

        /**
         * NAME? Removes wall/stair structure from a tile rather than only spawning an effect. It always clears
         * MiscDisplayLayer bit 0x400; then, only if no unit stands on the tile, it resets height to default,
         * destroys entities, clears LogicLayer bits 0x100/0x200/0x800/0x10000/0x400000, spawns effect entity type
         * 0x1E at the tile, clears BuildingWasLayer and DamageLayer, updates pathfinding and requests a minimap
         * redraw. The first parameter is unused (confirmed: never read in machine code).
         */
        void eraseWallTile(undefined4 unusedArg, int tile);

        /**
         * Picks a placement rotation from nearby walls. The machine code first sets uiBuildingRotation = 8 and
         * field127_0x554944 = 0x80 and returns if buildingPlacementFail. Otherwise it probes 4 (dx,dy) offsets per
         * side (DAT_TerrainDefinedData.rotationProbeOffsets) on 4 sides around (x,y) and counts tiles with wall bit
         * 0x100 but without 0x802. Two adjacent fully walled sides give a corner rotation (1/3/5/7), one fully
         * walled side gives 0/2/4/6, none gives 8. field127_0x554944 = ((rotation - mapOrientation) mod 8) * 16, or
         * 128 for 8. __thiscall on DAT_TileMapState (ret 8).
         */
        void determineBuildingPlacementRotation(int x, int y);

        /**
         * Validates a drawbridge at (x,y); returns at once if placement already failed, else sets
         * buildingPlacementFail = TRUE. For each of the 4 sides it reads up to 9 BuildingLayer ids from
         * drawBridgeOffsets[side], stopping at an off-map or border (0x30) tile. The first tile must hold a
         * BLS_NORMAL large (7 tiles) or small (5 tiles) gatehouse; variation 0x51 is accepted only on sides 0/2,
         * 0x50 only on sides 1/3, any other variation on every side. If the first 7/5 ids all equal that gatehouse,
         * it clears buildingPlacementFail, sets uiBuildingRotation = side*2 and field127_0x554944 = side*50 and
         * returns.
         */
        void checkDrawbridgePlacement(int x, int y);

        /**
         * NAME? Nothing here is about damage or rubble. It maps a piece code (0x50/0x51 = the two straight
         * orientations, 1/3/5/7 = the four corners) to a screen-relative gfx index 0..5 for the current
         * mapOrientation; unknown codes give 0. Both callers use it for the 23 dairy-farm (cattle farm) fence
         * tiles: the code comes from DamageLayer (repurposed) or the dairy farm layout table, and the result is
         * added to GM[0xE] + 0x37. __thiscall on DAT_TileMapState (ret 4).
         */
        undefined4 getViewRelativeDirectionFrame(int pieceCode);

        /**
         * Looks up a building's footprint size for a mapper command through a byte jump table. Returns 0..13, or -1
         * when the command is outside the table range. One case (size 2) also sets field159_0x5549b8 = 1.
         */
        int getBuildingSizeForCommandBuildingType(MappersEnum commandBuildingType);

        /**
         * Before placing a keep, destroys every building in its keepSize footprint at (x,y) with
         * showNoRubbleWhenDestroyingBuilding set. It also clears three single tiles and a 7x7 and a 5x5 area at
         * offsets from DAT_TerrainDefinedData tables indexed by keepBuildingType - BT_MANORHOUSE (0x60-byte and
         * 0x20-byte records; probably the spots of the keep's auto-placed companion buildings). Finally deletes all
         * buildings left in BLS_REMOVE state. playerID, orientation and xyValue are never read (ret 0x1C).
         */
        void demolishBuildingsInKeepsConstructionFootprint(
            undefined4 param_1, int param_2, int param_3, undefined4 param_4, int param_5, int param_6, int param_7);

        /**
         * For every tile of a size x size footprint at (x,y), sets LogicLayer bit 0x4 (farm footprint;
         * L_PLAIN1_AND_FARM) and clears MiscDisplayLayer bits 0xC. Used by the four farm placers and the dairy-farm
         * upgrade code. extraout_ECX is DAT_TileMapState (ECX preserved by getBuildingSizeIndexMappingData).
         */
        void markBuildingFootprintFlag(int x, int y, int size);

        /**
         * Gets the accessible path area id next to a building location via findAccessibleAreaNearBuildingLocation
         * and writes it into PathConnectionLayer for every footprint tile that currently has 0. Called from
         * clearBuildingFromTerrain so the freed tiles join the surrounding area.
         */
        void updateAreaBasedOnSurrounding(int x, int y, int buildingSize);

        /**
         * Walks the building's tileRef list (surfaceArea entries). For each tile it removes the tree there if bit
         * 0x4000000 (L_FARM_FIELD_APPLE, orchard trees) is set, clears logic bits 0x400 and 0xF000000 (mask
         * 0xF0FFFBFF), DamageLayer and BuildingLayer, and clears BuildingWasLayer when noRubble == 0. It then sets
         * ChangedLayer = 2 and updates path linkages.
         */
        void clearBuildingTilesAndTrees(int buildingID, int surfaceArea);

        /**
         * For each footprint tile: clears building logic bits (mask 0xEFBFF0FF: 0x100-0x800, 0x400000, 0x10000000),
         * restores DefaultHeight if MiscDisplayLayer bit 0x20 was set, and clears BuildingLayer. If the old
         * building's noRubble is 0 it clears BuildingWasLayer, otherwise it sets MiscDisplayLayer bit 0x2000 on
         * edge tiles and 0x4000 on inner tiles. It resets vanish and unknownCountdown_0x402 of every unit in the
         * tile's unit list and sets ChangedLayer = 2.
         */
        void clearBuildingFootprintAndResetUnits(int x, int y, int size);

        /**
         * For each footprint tile: clears building logic bits (mask 0xEFBFF0FF) and BuildingLayer, resets height to
         * default and updates path linkages. A siege tower (UT_S_TOWER) standing on the tile is set to
         * US_DISAPPEAR.
         */
        void clearBuildingFootprintAndRemoveSiegeTower(int x, int y, int size);

        /**
         * Clears LogicLayer bit 0x4 (farm footprint) on all tiles of a size x size footprint at (x,y); the inverse
         * of markBuildingFootprintFlag. Returns the last tile processed. __thiscall on DAT_TileMapState (ret 0xC),
         * ECX preserved.
         */
        void unmarkBuildingFootprintFlag(int x, int y, int size);

        /**
         * Same as clearBuildingFootprintAndResetUnits but leaves units alone. Per footprint tile it clears building
         * logic bits, restores height if MiscDisplayLayer bit 0x20 was set and clears BuildingLayer. It then clears
         * BuildingWasLayer (noRubble == 0) or sets MiscDisplayLayer bit 0x2000 (edge) / 0x4000 (inner), and sets
         * ChangedLayer = 2.
         */
        void clearBuildingFootprintWithEdgeRubble(int x, int y, int size);

        /**
         * For the 2x2 footprint at (x,y) it clears logic bits (mask 0xEFBFF0FD, also bit 0x2) and BuildingLayer. It
         * clears BuildingWasLayer (noRubble == 0) or sets MiscDisplayLayer bit 0x4000, and copies
         * DefaultHeightLayer into HeightLayer. __thiscall on DAT_TileMapState (ret 8); raw extraout_ECX offsets:
         * 0x165160 Logic, 0x2029B0 Building, 0x229DD0 BuildingWas, 0x301C80 MiscDisplay, 0x29FA30/0x2B3440
         * Height/DefaultHeight.
         */
        void clearFixedSizeTwoBuildingFootprint(int x, int y);

        /**
         * For a drawbridge building, walks its 5x5 footprint with the per-variation mask
         * field2469_0x21ec[variation/2]. Returns TRUE if any tile whose mask entry is 0 has a unit on it (UnitLayer
         * at ECX+0x23D7E0), otherwise FALSE. Probably keeps the drawbridge from closing on units (caller
         * UpdateDrawBridge).
         */
        BOOLEnum isUnitBlockingSizeFiveFootprint(int buildingID);

        /**
         * For every (dx,dy) in DAT_TerrainDefinedData.StockpilePathableOffsets (unrolled by 3) around (x,y): clears
         * LogicLayer bits 0x100 and 0x2, resets height to default, then clears BuildingWasLayer or sets
         * MiscDisplayLayer bit 0x4000 depending on the noRubble flag of the building whose id is stored in
         * AlphaGFXLayer, and finally zeroes AlphaGFXLayer. Here AlphaGFXLayer holds a building id for stockpile
         * tiles. __thiscall on DAT_TileMapState (ret 8).
         */
        void clearStockpileFootprintTiles(int x, int y);

        /**
         * Only for buildings with unknownStockpileOrSignpostRelated set. Buildings smaller than 3 (except
         * gibbet/gallows) just get MiscDisplayLayer bit 0x4 at their origin. Others: bits 0xC are cleared over the
         * footprint, then bit 0x8 goes on every tile for types 0x0B/0x13, else on the footprint index from
         * orientationRelativeBuildingTileOffset1 (offset2 for the listed swap types, none for 0x3E/0x5D) and that
         * tile is stored in flag8DisplayTile. Bit 0x4 goes on the offset2 index (offset1 for swap types; fixed per
         * orientation for type 0x31) and that tile goes to miscDisplayLayerTile; type 0x31 also gets bits 0xC on a
         * second fixed index. Note: locals are misnamed by the decompiler: 'buildingType' = orientation/2 then loop
         * index/tile, 'buildingX' = y, 'buildingY' = type, 'offset1OrTile' = x. __thiscall on DAT_TileMapState (ret
         * 4).
         */
        void setMiscDisplayLayer(int buildingIdOrFlag8Index);

        /**
         * Clears MiscDisplayLayer bits 0xC on every tile of the building's footprint. When destroyEntities == 1 it
         * also destroys the entities on those tiles.
         */
        void clearBuildingDisplayFlagsAndEntities(int buildingID, int destroyEntities);

        /**
         * NAME? Draws an animated ring marker, probably not a number (callers draw flags and unit destinations). It
         * walks the offset list field2474_0x2764[type/2] (60 pairs, terminated by x == -1), positioned at (x -
         * type/2, y - type/2). For every even-indexed entry on a tile without bits 0x10000500 it creates a
         * GID_FLOATS_NEW floating element with frame 0xE5 + ((field161_0x5549c0 + offsets + entry index + corner x
         * + corner y - 1) mod 16).
         */
        void spawnFloatingNumberAroundTile(int x, int y, int type);

        /**
         * Map editor: places rock variant 0..15 at (x,y) as rock type 1..16 with size 1 (0-3), 2 (4-7), 3 (8-11) or
         * 4 (12-15). It aborts if any footprint tile has border bits 0x30, bit 0x400 or an organism. Otherwise it
         * creates the rock (createRock with rockOrientation), sets HeightLayer and DefaultHeightLayer to min +
         * (max-min)/2, clears logic bits (mask 0x1FC1FFB6) and Logic2Layer, sets bit 0x80 (L_ROCKY) and writes
         * OrganismLayer = rockId + 2000, then triggers path and macro-layer updates. The parameter slot is reused
         * for the min height and the organism id.
         */
        void placeRock(uint x, uint y, uint variantMinHeightOrOrganism);

        /**
         * Writes GfxLayer images for every non-wall tile of a rock's footprint: GM[rock.unknownGMID] + rock.gfx +
         * rotation block ((orientation + mapOrientation)/2 * size^2) + buildingRotationRelatedValue - 1. When
         * field93_0x5548c8 is set, size-1 rocks use the same formula and bigger rocks use GM base +
         * getRandomRockImageOffset + rotation block - 1. The rockID parameter is reused as the footprint counter.
         */
        void applyRockGraphicsToFootprint(int rockID);

        /**
         * Clears the tree's OrganismLayer entry and LogicLayer bit 0x1000 (L_TREE) at its root tile, then clears
         * bit 0x2000 (L_TREE_VARIATION, tree footprint) on every tile of its size x size footprint.
         */
        void clearTreeFootprintFlags(int treeID);

        /**
         * For every tile of a rock's footprint, clears LogicLayer bit 0x80 (L_ROCKY) and zeroes OrganismLayer
         * (ECX+0x1DB590).
         */
        void clearRockFootprintFlags(int rockID);

        /**
         * NAME? Map-editor rock placement preview, not a wall preview. It sets buildingPlacementFail = FALSE, maps
         * rockVariant 0..15 to size 1..4 and a gfx base (same size table as placeRock), and returns without drawing
         * if any footprint tile has border bits 0x30, 0x400 or an organism. Otherwise it writes GM[0x38] + rotation
         * block + buildingRotationRelatedValue + gfxBase - 1 into ConstructionGFXLayer (ECX+0xA0CC0). The rotation
         * is rockOrientation + mapOrientation, or mapOrientation alone when field80 == 5.
         */
        void renderBigRockPlacementPreview(uint x, uint y, short rockVariant);

        /**
         * Returns the castle build range for the current mapSize: 160 -> 45, 200 -> 50, 300 -> 60, anything else
         * (400) -> 70.
         */
        undefined4 getCastleBuildRangeForMapSize();

        /**
         * Advances to brush tile `index`. For a square brush it asks PathFindingState.getTileInSquareBrush and
         * writes the absolute result. Otherwise it reads a step code from field12_0xc[index] (index > 36 becomes 0)
         * and moves *tilePointer/*yPointer relative to their current values: codes 0..7 one step, 20..27 two steps,
         * 40..47 three steps in direction code mod 20; code 15 and codes above 47 mean no move.
         */
        void getTileForBrush(int square, int index, int* tilePointer, int* yPointer, int baseTile, uint y);

        /**
         * NAME? Checks the 8 neighbours of (x,y), starting north and going clockwise, and returns TRUE as soon as a
         * valid neighbour is strictly lower (HeightLayer) than `tile`; FALSE if none is. The x-1 neighbours are
         * read through EntityLayerLT25[...+0x13A0F], which is the same address as HeightLayer[tile-1] (the layers
         * are adjacent). So this is really 'is the tile higher than any neighbour'.
         */
        BOOLEnum isTileHigherThanAnyNeighbour(int tile, uint x, uint y);

        /**
         * Single-player only (returns in GM_MULTIPLAYER). Reads the heights of the neighbour offsets in
         * field2476_0x372c around (x,y); a slot keeps the tile's own height unless that neighbour has LogicLayer
         * 0x100000 (L_RIVER), and min/max are tracked over the slots. Logic2Layer keeps only bits 0x38. If no river
         * neighbour is lower: no flag when none is higher, 0x80 when the highest is at most 16 above, else 0x40.
         * Otherwise sets a directional drop bit 1/2/4 from specific lower slots, chosen by mapOrientation.
         */
        void computeTileCliffEdgeFlags(int tile, int x, int y);

        /**
         * If the tile's Logic2Layer is 0, scans the neighbour offsets in field2476_0x372c around (x,y). If any
         * valid neighbour has LogicLayer 0x100000 (L_RIVER), Logic2 bits 0x50 and is at least as high as the tile,
         * the tile's Logic2Layer is set to 0x80.
         */
        void propagateCliffEdgeFlagFromNeighbor(int tile, int x, int y);

        /**
         * NAME? Builds the source-tile list (max 1000) that only generateDustClouds consumes; nothing climb-
         * related. temporaryTerrainTypeArray gets the tile and temporaryTerrainTypeBinaryArray (array +1000) a
         * variant flag. Non-border river tiles (0x100000) with Logic2 0x40 get flag 1, or 0 if a neighbour in
         * ClimbLogicDefinedData.directionScanOrder directions is a river tile more than 0x50 higher. River tiles with
         * Logic2 0x10 and sea tiles (0x1) with Logic2 0x8 get flag 1. Since all sources are river/sea tiles, the
         * ET_DUST_CLOUD entities are probably water spray.
         */
        void collectDustCloudSourceTiles();

        /**
         * Per game tick: advances SEC_Section1052 (tick counter) and, on random matches, sets SEC_Section1053/1054
         * to rng % 180; both count down to 0 each tick. For each listed source tile whose (RandomLayer ^ rng) mod
         * 64 equals tick mod 64, spawns ET_DUST_CLOUD at the tile centre (x*8+4, y*8+4, tile height): variant-0
         * tiles only while 1054 == 0 (variant arg 0), other tiles only while 1053 == 0 (variant arg 1, or 2 for any
         * other stored value).
         */
        void generateDustClouds();

        /**
         * Picks a wall frame for the current tile (DAT_SomeTile/DAT_SomeY); the caller stores it in
         * field112_0x554908. If the wall connects along direction 2 (isWallConnectionHeightValid), the result is
         * derived from mapOrientation and x & 0xF; else if it connects along direction 0, from mapOrientation and y
         * & 0xF (frames 1..0x20). Otherwise it returns 0x30 if getWallFlagForOrientedDirection(2), else 0x3F if
         * (4), else 0x21. An unknown mapOrientation gives 0. The decompiler's unaff_ESI is really param_1 (x).
         */
        int computeWallCornerRenderRotation(uint x);

        /**
         * Returns TRUE if the neighbour in the direction opposite field84_0x5548a4 ((dir + 4) mod 8) is more than
         * 20 height units below the tile. The x parameter is never read (checked in machine code, ret 0xC).
         */
        BOOLEnum isCliffDropInDirection(int tile, undefined4 unusedX, int y);

        /**
         * Compares the tile height (default height for wall tiles) with the neighbours in directions field86 (A),
         * field85 (B) and field84 (C). A neighbour counts as a drop when it is more than 20 lower and below 0x88.
         * Returns 0 none, 1 A only, 2 B only, 3 A and B, 5 A, B and C or only C lower by > 20, 4 when A and B are
         * both >= 0x88. It also sets field112_0x554908 to a texture phase 1..31 from x or y (& 0x1F), depending on
         * mapOrientation and the shape.
         */
        int computeClimbRampRotation(int tile, uint x, uint y);

        /**
         * Incremental terrain-gfx refresh while forceUpdateGFXLayers > 0. Walks flagged 10x10 sections (rows
         * someIndex..dirtySectionRowMax, columns someYLike..dirtySectionColMax). For tiles with LogicLayer 0x8000 and no
         * GfxLayer, it picks a gfx offset set from marsh (0x20000000) or Logic2Layer bits and builds a neighbour
         * mask (tile+1, tile-1, directions 0 and 4) in bitFlag. GfxLayer is computed from
         * GMFirstPictureIndex[0x37], luminance (min 2), MacroLayer type/index/variant and RandomLayer;
         * PillarGFXLayer = GM[9]. local_10 is only ever 0 or 2, so the local_10 == 1 branch looks unreachable.
         */
        void updateGFXLayers();

        /**
         * Recomputes TileMapState.MacroLayer (big-tile terrain sprite selection) for tiles inside dirty 10x10
         * chunks (byte grid, 40 per row, at 0x1f93438) of the chunk range someIndex..dirtySectionRowMax (rows/Y) x
         * someYLike..dirtySectionColMax (columns/X). The first dirty chunk starts at sub-row
         * PathFindingState.dirtyMinY % 10, later ones at 0. Phase 1: for each tile with ChangedLayer!=0
         * (MacroLayer cleared first when clearMacroFirst), if LogicLayer&logicMask or Logic2Layer&terrainMask
         * matches and the tile has no 0x30 logic bits, builds an 8-neighbour mask (bitFlag) of neighbours with the
         * same flag (logic 0x8000 / 0x20000000 from LogicLayer, terrain bits from ptr_TerrainTypeTileMap; terrain
         * 0x20 also ORs neighbours with logic bit 1). Tiles with 0x20000000 that also have 0x80000000 are skipped
         * entirely. Fully surrounded (0xff) tiles become 0x800 (merge candidate) or 2 when RandomLayer&0xf==0, all
         * others 1; PathFindingState::updateWalkAndPathLayer(1,x,y) is called when the value changed. Phases 2-4
         * stamp 4x4 (16 offsets, base 0x10), 3x3 (9, base 8) and 2x2 (4, base 4) macro tiles wherever all offset
         * tiles are 0x800, value = base + index<<6 + RandomLayer*0x1000; phase 5 turns leftover 0x800 tiles into
         * single tiles (2).
         */
        void updateMacroLayerRelated(uint logicMask, uint terrainMask, int clearMacroFirst);

        /**
         * Specialised MacroLayer rebuild for tiles with LogicLayer bit 1 inside the dirty 10x10 chunks (same chunk
         * ranges as updateMacroLayerRelated; inline bounds check x,y<400 plus validity byte map at 0x21aec98). Pass
         * 1 (rows unrolled 2x5) marks changed tiles with logic bit 1 as 0x800; pass 2 (starting at sub-row
         * mappingYRelated%10) stamps a 4x4 macro pattern (0x10 + index<<6 + (byte)RandomLayer*0x1000) wherever the
         * anchor tile is 0x800 with logic bit 1 and all 16 offset tiles are 0x800; pass 3 (unrolled 2x5) turns
         * leftover 0x800 tiles into single tiles (2). Unlike updateMacroLayerRelated there is no neighbour-mask
         * computation, no 3x3/2x2 pass and no pathfinding update.
         */
        void updateMacroLayerRelated2();

        /**
         * Builds the 8-neighbour mask (TileMapState.neighbourMask) for tile (x,y): sets one bit per neighbour whose
         * LogicLayer has any of 0x10000100 (wall 0x100 or keep/tower structure 0x10000000), using the direction
         * translation matrix for the rows above/below. Returns the mask; used by projectile wall-bounce/debris
         * code.
         */
        byte setBitFlagBasedOnWallTowerGatehouseOrKeep(int x, int y);

        /**
         * NAME? (suggest getObstacleTopHeightAtTile) Returns HeightLayer[tile] plus the height of whatever stands
         * on it: keep/tower structures (logic 0x10000000) and manor/keeps (types 40-44) add
         * getBuildingHeightForBuildingID, gatehouses/towers (45,46,61,74-78) add that +10, other buildings (logic
         * 0x400) add BuildingHeights[type] except the hunter's hut (type 7) which adds 0 when ignoreHuntersHut != 0
         * (line-of-sight callers pass 1, projectile-hit callers 0); rocky tiles (logic bit 0x80, no wall 0x100,
         * OrganismLayer>=2000) add 70 or 50 depending on the rock type value (>12 / 9..12). Walls need no extra
         * term because their height is already in HeightLayer.
         */
        uint getObstacleTopHeightAtTile(int tile, int ignoreHuntersHut);

        /**
         * Returns the total height at tile: HeightLayer if no building; otherwise building height
         * (getBuildingHeightForBuildingID) added to DefaultHeightLayer for large/small gatehouses or to HeightLayer
         * for all other buildings.
         */
        uint getTotalHeightAtTile(int tile);

        /**
         * Computes the top-surface height at tile = HeightLayer + structure height: keep/tower structures (logic
         * 0x10000000) and manor/keeps (40-44) building height, gatehouses (45/46) building height, towers
         * (61,74-78) building height +20, other 0x400 buildings BuildingHeights[type], rocks +50/+70, logic
         * 0x400000 +20, logic 0x200 +10, any other building tile (no 0x400 flag) +30. Returns the height if the
         * tile is a standable top/edge for playerID (0 = any owner; owner from building or WallOwnerLayer),
         * otherwise -1-height. Standable = edge tile of a keep/tower structure (some of the 8 neighbours is another
         * building; manor house never), any gatehouse/tower tile, 0x400000 and 0x200 tiles, and gatehouse tiles
         * without 0x400 whose neighbour in direction dirA or dirB (2/6 or 0/4 by buildingVariation) is not the
         * gatehouse. Rocks and plain buildings always give -1-height.
         */
        int getTotalHeightAt(int tile, int playerID);

        /**
         * Returns the height a unit of playerID could stand on at tile, or 0: requires PathConnectionLayer!=0 and
         * MiscDisplayLayer bit 0x1000 clear; walls (logic 0x100) owned by playerID (or playerID 0) return
         * HeightLayer; interior tiles (all 8 neighbours same building) of the player's keeps/towers, and gatehouse
         * tiles whose both axis neighbours are the gatehouse, return getTotalHeightAtTile. Everything else returns
         * 0.
         */
        uint getWalkableStructureHeightAtTileForPlayer(int tile, int playerID);

        /**
         * Scans moats[1..15999] and sets TileMapState.maxMoatCount to one past the highest index with a non-
         * zero owner (0 if none) - an iteration bound, not a count. __thiscall on ECX=this; leaves ECX unchanged.
         */
        void recountTotalOwnedMoats();

        /**
         * Zeroes playerDataArray[1..8].moatsOwned, then counts moat entries 1..15999 per owner (loop unrolled 3x,
         * 5333 iterations) into playerDataArray[owner].moatsOwned.
         */
        void countMoatsOwnedByEachPlayer();

        /**
         * Counts moat entries 1..15999 owned by playerID whose tile is not yet dug (LogicLayer bit 0x40000000
         * clear). Loop unrolled 3x.
         */
        int countUnfinishedMoatTilesForPlayer(int playerID);

        /**
         * Returns the number of free moat slots (owner == 0) among entries 1..15999. Loop unrolled 3x.
         */
        int getUnownedMoatCount();

        /**
         * Returns the ID (1..maxMoatCount-1) of the owned moat entry whose tile equals targetedTile, or 0 if
         * none.
         */
        int returnOwnedMoatAtTile(int targetedTile);

        /**
         * NAME? Returns the first moat ID (1..maxMoatCount-1) whose tile field (Moat offset 0, read as
         * owner-0xc) equals the first argument and whose owner equals the second, else 0. Despite the name/param
         * names the first argument is a tile index (the only caller, pathFindingToAttackCastleIncludingMoat at
         * 0x4A433F, passes the tile it also uses to index BuildingLayer), not a player ID (suggest
         * findMoatIdByTileAndOwner).
         */
        int findMoatIdByTileAndOwner(int playerID, int playerID2);

        /**
         * Zeroes the 16-byte moat entry moatID (if < 16000) and decrements TileMapState.moatTileCount.
         */
        void clearMoatData(uint moatID);

        /**
         * Clears every moat entry (index 0..maxMoatCount-1, owner not checked) whose x/y match the given tile
         * coordinates, decrementing moatTileCount for each.
         */
        void clearMoatDataAtTile(int x, int y);

        /**
         * Returns TRUE if any of the 8 neighbours of tile (direction row yUnk = tile's Y) belongs to
         * PathConnectionLayer area `area` and is at most 16 height units higher than tile, else FALSE.
         */
        BOOLEnum hasNeighborTileInSameAreaWithinHeightLimit(int area, int tile, int yUnk);

        /**
         * Moat dig target for a unit standing at (x,y). The first parameter (named tile) is actually a moat ID
         * (indexes moats[] with <<4). Returns 0 if (x,y) is invalid. Mode 1: stores the moat's x/y in
         * ALG_MoatXResult/ALG_MoatYResult and returns the moat tile itself. Mode 2: finds the first of the moat
         * tile's 8 neighbours that is in the same PathConnectionLayer area as (x,y) and at most 16 height above
         * (x,y)'s tile, stores someMoatTile = the moat's own tile and ALG_MoatX/YResult = moat x/y +
         * clockwiseCardinalTranslationMatrix[dir], and returns that neighbour tile (0 if none). Other modes return
         * 0.
         */
        int computeMoatDigTarget(int tile, int mode, uint x, uint y);

        /**
         * One dig step on moat moatID: increments fillProgress; when it exceeds 3 the tile is finished (countdown
         * 0, progress 4, stage 2, height 0, LogicLayer clear 0x4000 and 0x8, set 0x40000000, Logic2Layer cleared),
         * updateWalkAndPathLayer(2,x,y) and path linkages are updated, the separate-area map and minimap refresh
         * are requested, and it returns 1. Otherwise returns 0.
         */
        undefined4 advanceMoatDigProgress(int moatID);

        /**
         * If tile has the moat-planned logic bit 0x4000, removes the matching moat entries (clearMoatDataAtTile
         * with tile's x/y) and clears that bit.
         */
        void clearMoat(int tile);

        /**
         * Per-tick: calls recountTotalOwnedMoats, then decrements the positive countdown byte (+0xf, someCountDown)
         * of every owned moat entry 0..maxMoatCount-1. The raw offsets are relative to ECX = this
         * (recountTotalOwnedMoats is __thiscall and leaves ECX intact): this+0x53f070 = currentMoatCount,
         * this+0x50087f = moats[0].someCountDown, -3 = owner.
         */
        void updateMoatCountdownTimers();

        /**
         * Zeroes all 16000 moat entries (16 bytes each, starting 0x1f93a78) and resets moatTileCount to 0.
         */
        void resetMoatArray();

        /**
         * On map preparation, clears owned moat entries (1..maxMoatCount-1) whose tile is neither planned
         * (0x4000) nor dug (0x40000000) and has no building.
         */
        void clearInvalidMoatEntries();

        /**
         * Finds the owned moat entry at tile and stores zeroOrTwo into its zeroOrTwo field (drawbridge water visual
         * state).
         */
        void setMoatVisualStateAtTile(int tile, undefined4 zeroOrTwo);

        /**
         * Reassigns every moat entry 1..15999 owned by fromPlayerID to toPlayerID (ownership change).
         */
        void setMoatOwnerForAllMatching(int fromPlayerID, undefined4 toPlayerID);

        /**
         * Swaps moat ownership between two players over entries 1..15999.
         */
        void swapMoatOwnership(int playerA, int playerB);

        /**
         * Sets maxPitchDitchCount = 4000 and zeroes all 4000 pitch-ditch entries (20 bytes each, starting
         * 0x1fd228c).
         */
        void resetPitchDitchArray();

        /**
         * Counts free pitch-ditch slots (owner == 0) over entries 0..3999 (loop unrolled 5x, 800 iterations; unlike
         * the other ditch loops it includes entry 0).
         */
        int countUnownedPitchDitches();

        /**
         * Returns the ID of the owned pitch ditch on tile (1..maxPitchDitchCount-1), or 0.
         */
        int getPitchDitchIDForTile(int tile);

        /**
         * Removes pitch ditch pitchDitchID: clears LogicLayer bit 0x8 and MiscDisplayLayer bits 0x2000/0x4000 on
         * its tile, restores HeightLayer from DefaultHeightLayer if the tile has no wall (0x100) and no building,
         * updates pathfinding (updateWalkAndPathLayer type 4) and zeroes the 20-byte entry.
         */
        void destroyPitchDitch(int pitchDitchID);

        /**
         * Swaps pitch-ditch ownership between two players over entries 1..3999.
         */
        void swapPitchOwnership(int playerA, int playerB);

        /**
         * NAME? (not dig-specific; caller is findNearestEnemyAndHeadTowardsIt) Among the 4 offsets field2478_0x378c
         * around target (x2,y2), picks the one in the same path-connection area as (x1,y1) whose height (incl.
         * building height) is strictly within +-16 of the target's height and that is closest to (x1,y1)
         * (setAxisBasedDistanceResult). Stores it in field155/156 and returns 1; if none qualifies stores (x2,y2)
         * and returns 0. Returns 0 without storing when either coordinate pair is invalid.
         */
        undefined4 findApproachTileNextToTarget(uint x1, uint y1, uint x2, uint y2);

        /**
         * Walks |steps| tiles from startTile along direction 4 (steps>0) or direction 0 (steps<0), adding
         * directionTranslationMatrix[row][dir] each step and moving the matrix row by +-1 per step, then returns
         * the resulting tile + extraOffset.
         */
        int computeTileAlongAxisOffset(int startTile, int extraOffset, uint steps);

        /**
         * Sets mapAndTime.signpostExclusionRadius by game mode: default 30; campaign missions <3 -> 0, 3-4 -> 15, 6 ->
         * 37 (others keep 30); economic campaign, or builder maps with MapType2_1 > 1 -> 7.
         */
        void setSignpostDistanceForCampaignMission();

        /**
         * Wrapper: runs PathFindingState::spreadAlgorithmForFlagsAndBraziersUnk(playerID, x, y, 4, 0) (flag
         * variant) and returns its result.
         */
        int spreadFlagPlacementAlgorithm(int playerID, uint x, uint y);

        /**
         * Wrapper: runs PathFindingState::spreadAlgorithmForFlagsAndBraziersUnk(playerID, x, y, 4, 1) (brazier
         * variant).
         */
        void spreadBrazierPlacementAlgorithm(int playerID, uint x, uint y);

        /**
         * Sets the force-update flags for logic/misc display, texture tilemap and GFX layers and marks the whole
         * ChangedLayer/chunk mapping dirty.
         */
        void forceFullTileMapRedraw();

        /**
         * Map-editor eraser centred on (x,y) with BrushSizeArray[brushSize] tiles (getTileForBrush mode 1, which
         * yields only each brush tile's index and y): first destroys entities on the centre tile; pass 1 removes
         * trees (<2000) / rocks (>=2000) on each brush tile and updates pathfinding (type 3/8); pass 2 runs
         * validateBuildingPlacementAtTile and destroys the blocking building without rubble (for a keep also its
         * stockpile, for a stockpile also the keep) or spawns an eraser effect for other obstacles; pass 3 marks
         * all units on each brush tile ULS_REMOVE. BUG (original game, confirmed in machine code): passes 1-2 use
         * the centre x (EBP = arg x, never updated) with the brush tile's y for updateWalkAndPathLayer,
         * validateBuildingPlacementAtTile and spawnEraserTileEffect, so only the centre column is tested for
         * buildings.
         */
        void useEraserBrush(uint xOrBrushTile, uint yOrBrushY, int brushSizeOrCount);

        /**
         * One animation step of heightBasedScreenYOffset[256] (terrain raise/pull-down effect) selected by
         * refreshCertainTileMap: mode 1 sets entry i to (i>>2)+1 and mode 2 to i directly (finish in one step);
         * mode 3 moves each entry down toward (i>>2)+1 and mode 4 up toward i by a stepped amount
         * (30/20/14/8/4/3/2/1 by distance). While still animating rebuilds ShowHi from heights and returns; when
         * done sets refreshRelatedOne/Two (1/1 for modes 2,4, 0/2 otherwise), resets the mode, forces logic-layer
         * redraw, marks ChangedLayer, clears counter1 and sets DAT_RotateMapOrPullDownTerrain.
         */
        void stepHeightOffsetAnimationAndRefreshShowHi();

        /**
         * Sets mapOrientation (0/2/4/6) keeping the viewport focus tile, forces a full tilemap and building display
         * refresh, and sets orientation-dependent direction indices field84..field87 plus a +-1 sign in field88.
         */
        void changeMapOrientation(int mapOrientation);

        /**
         * Tunneler terrain effect: for the 9 tiles of brush type 0 around tile, skips tiles with
         * walls/keeps/buildings (0x10000500, BuildingLayer) or flags 0xb1/0x60300000; on the remaining tiles adds
         * increment to HeightLayer when HeightLayer or DefaultHeightLayer is below 16 and the result stays non-
         * negative, and updates path linkages (also when the height was not changed). Finally calls
         * updateWalkAndPathLayer(5, x, y) where y has been overwritten by the last brush tile's y (getTileForBrush
         * writes into the y argument slot), so the update is centred on (x, y of brush tile 8).
         */
        void increaseHeightForTunnelWithBrush(int tile, uint x, uint y, int increment);

        /**
         * Map-editor raise/lower land brush: for BrushSizeArray[brush] tiles around tile, skipping tiles with 0x30
         * flags, walls/keeps/buildings/moats (0x50004500, BuildingLayer) and filtered by unknownZero_0x554904
         * (water-flag mode), clears the rock bit 0x80, marks ChangedLayer=2, and adds change to HeightLayer (only
         * if height != 0 or change >= 0; then also clears Logic2Layer), clamped to [minHeight,maxHeight] (8..0x80
         * on land, 0..0x14 for tiles with 0x60000000, fixed 0 for water bit 1). Height is handled +8 for logic bit
         * 0x100000 tiles, copied to DefaultHeightLayer, then -8 again; path linkages updated. Forces texture/logic
         * redraw.
         */
        void raiseLand(int tile, uint y, uint brush, int change);

        /**
         * Map-editor plateau brush: a first pass over the BrushSizeArray[brushSize] tiles computes the maximum
         * height but the result is discarded (dead code in the original binary; the pass still runs
         * getTileForBrush). Second pass: for each free tile (no 0x30, wall/keep/building/water/moat flags
         * 0x70000401|0x50004500, no BuildingLayer) clears the rock bit, sets HeightLayer to 0x50 (setting 4) or
         * 0x82 (setting 8; other settings keep the height), copies it to DefaultHeightLayer (HeightLayer -8 for bit
         * 0x100000 tiles), stores the setting in Logic2Layer, marks the 3x3 ChangedLayer neighbourhood and updates
         * path linkages.
         */
        void createPlateau(int tile, uint the_y, int brushSize, int plateauHeightSetting);

        /**
         * Map-editor level/equalize brush: finds min and max height over BrushSizeArray[brushSize] tiles (ignoring
         * 0x30 tiles), target = (min+max)/2, then for each editable tile (mapperAffectType water filter, excluding
         * water bit 1, walls/keeps/buildings/moats) clears bit 0x80 and moves the height toward the target by 1 +
         * distance/10 (clearing Logic2Layer when it moves), clamps to 8..0x9c, updates DefaultHeightLayer (with the
         * +-8 handling of bit 0x100000), marks the 3x3 ChangedLayer neighbourhood and updates path linkages.
         * param_4 is a real stack arg (ret 0x10) but never read.
         */
        void useLevelBrush(int brushTile, uint brushY, uint brushSizeMinOrIndex, int unused4);

        /**
         * Map-editor set-land brush: for each brush tile without 0x30, wall/keep/building (0x10000500,
         * BuildingLayer) or 0x1000 flags (and no rock organism on a 0x80 tile), restores HeightLayer from
         * DefaultHeightLayer (min 8), clears MiscDisplay bit 0x20, removes moat data and moat bits (0x40004000),
         * clears most logic bits (mask 0x5f81c436) and MiscDisplay bits (mask 0xf83f), resets Logic2Layer (4/8 when
         * height is a plateau level 0x50/0x82) and WallOwnerLayer, and updates path linkages.
         */
        void setLand(int tile, uint y, uint brushType_y);

        /**
         * NAME? Checks the 9 tiles of brush type 0 around (x,y) for placing build type cbt: a tile counts if it is
         * free (no organism, keep/building 0x10000400, BuildingLayer, 0x203a0100 or 0x85 flags), no enemy is within
         * range (30 single player / 15, skipped in editor and Siege That) and, outside single player, no opponent
         * building within castle range+5. For cbt 0x6a (M_MAPPER_MOAT) the tile must also not be planned/dug moat
         * (0x40004000), for 0x6b (M_MAPPER_ANTIMOAT) it must be planned moat (0x4000); any other cbt accepts every
         * free tile. Returns TRUE if at least one tile qualifies (the x parameter is reused as the counter). The
         * only caller (0x44626A) invokes it only when the current build type is 0x6a or 0x6b.
         */
        BOOLEnum isMoatBrushPlacementValid(int x, uint y, int cbt);

        /**
         * Map-editor terrain min/max brush: over BrushSizeArray[brushSize] tiles computes the average of min and
         * max height, then for each editable tile (no 0x30 or 0x70000501 flags, no building) first adds 1 to
         * HeightLayer and then applies heightMode: 0 = 8 (minimum, clears Logic2 bits 0x0c), 1 = 0x9c (max, sets
         * logic 0x8000), 5 = 100, 2 = height*((height*100/avg)/8+100)/100 capped at 0x9c, other modes keep the +1;
         * removes rocks (bit 0x80, organism >= 2000) and clears the rock bit, clamps to 8..0x9c, updates
         * DefaultHeightLayer (-8 for bit 0x100000), ChangedLayer 3x3 and path linkages; finally forces the
         * logic/misc layer redraw.
         */
        void useTerrainHeightBrush(int brushTile, uint brushY, uint brushSizeMinOrIndex, undefined4 heightMode);

        /**
         * Returns the maximum HeightLayer among brush tiles 1..4 (the first four neighbours from getTileForBrush
         * mode 1) around the given tile that are walls (logic 0x100) without bit 0x2 or crenel bit 0x200; 0 if
         * none. Used by validateWallBuildPath for stair placement. brushTile/brushY are reused as getTileForBrush
         * output slots.
         */
        int getMaxWallHeightInBrushArea(int brushTile, uint brushY);

        /**
         * Validates a wall/crenel/stair drag from (x1,y1) to (x2,y2) for playerID; sets illegalBuild TRUE first and
         * FALSE only on success. Stairs (command 0x1b) need a start enclosed by walls/gates and adjacent walls
         * higher than 16 (stored in field119_0x554924); crenels (0x1a) need every tile enclosed by walls (else
         * reason 0x13). Walks the line (stairs: one axis per step, walls: diagonal steps) rejecting tiles with 0x14
         * or 0x70000401 flags, buildings, 0x300000, rocks (0x80), trees other than types 5-14/16-19, units other
         * than chickens on non-wall tiles, enemy too close (0x11), opponent building or keep range in multiplayer
         * (0x13 unless already 0x12), opponent building within 7 in the editor (0x11), findSomeSuitableLocationUnk
         * (0x11) and signposts (0x15). Stair height drops by 16 per tile and a stair path succeeds early once it is
         * <= 16 or a wall tile is reached.
         */
        void validateWallBuildPath(int playerID, uint x1, uint y1, uint x2, uint y2, undefined4 command);

        /**
         * Places walls along the validated line (x1,y1)-(x2,y2) for playerID, stopping after tileCountUnk tiles or
         * when more normal tiles were placed than constructionTileCount allows (stairs abort if the stair height is
         * below 0x18 or a wall tile is reached). Per tile: stone wall +0x5a, wood wall +0x3c, crenel (sets 0x200,
         * +0x62 or +0x44 next to towers, parity-based 0x400000), stairs (0x800, height up to stairHeight-16); a
         * wall placed on a crenel tile converts it back to a wall without charging; otherwise sets wall bit 0x100
         * and owner, hides chickens, clears pitch bit 8 (+4 height), fells trees of types 5-14/16-19, sets 0x10000
         * for wood walls and tower-adjacent crenels; then path linkages, clearMoat and updateWalkAndPathLayer(7).
         * Finally charges via processWallBuildingLoss(player, stoneCount, woodCount, 0) and requests area/minimap
         * refresh.
         */
        void placeWalls(int playerID, uint x1, uint y1, uint x2, uint y2, MappersEnum wallType, int tileCountUnk);

        /**
         * AI placement of a single defensive tile at (x,y) after validateWallPlacementAtTile: resets DamageLayer
         * and height to DefaultHeightLayer, then by wallType adds +0x5a (0x19 wall), +0x3c (0x2e wood wall, also
         * sets 0x10000), crenel +0x62 (0x1a) or +0x44 (0x23) with 0x200 and the parity-based 0x400000, or stairs
         * 0xb5-0xb9 (+0x50..+0x10, flag 0x800); sets wall bit 0x100 and owner, clears pitch bit 8 (+4 height),
         * fells any tree on the tile, updates pathing/moat, and charges processWallBuildingLoss(player,1,0,0) for
         * every type except 0xb5-0xba (so wood walls are charged in the stone slot here, unlike placeWalls).
         */
        void placeDefensiveStructureTile(int playerID, uint x, uint y, MappersEnum wallType);

        /**
         * Calls setupBuildingSizeIndexMappingForBuildingWithSize for size indices 0..13 to build the per-size
         * footprint index tables.
         */
        void setupBuildingSizeIndexMapping();

        /**
         * Validates placing commandBuildingType for playerID at tile (x,y): loads sprite and placement limits from
         * BuildingDefinedData into DAT_TileMapState (returns early for siege-tower base), then (unless buildingSize
         * < 0, which means size 2 without any distance checks - statue placement passes -2) runs per-type distance
         * checks: enemy units within 30 (single player) / 15 tiles or opponent buildings in range -> reason 0x11,
         * outside castle build range (+5 for killing pit/pitch ditch/drawbridge) -> 0x12, signpost within
         * unk_signpostDistance+5 -> 0x15, dog-cage limit 10 -> 1000, and finally enemy building/wall within 2 ->
         * 0x11. It scans every footprint tile (off-map or LogicLayer&0x30 -> result 2;
         * isBuildingPlacementBlockedAtTile -> TRUE) while counting boulder (0x20000), iron (0x80000), marsh (bit31)
         * and Logic2Layer grass/thick-scrub/scrub tiles, then applies type rules: farms need grass+scrub >= tile
         * count (0x16) and grass+thick-scrub >= 50 (0x17), quarry >= 8 boulder tiles, iron mine >= 4 iron tiles,
         * pitch rig >= 1 marsh tile, stockpile/granary/armoury must touch an existing one (limit 32/8/8), keeps,
         * wooden gates 1A-1D, barracks, guilds and oil smelter check their extra part areas, tunnel construction
         * needs a tunneler target. Result in buildingPlacementResult (FALSE ok, TRUE invalid, 2 off-map/blocked)
         * and buildingPlacementFailReason. Stack-slot reuse: the skip flag lives in the x argument slot, x is then
         * the footprint loop counter, y_fertileLandCount (y slot) the fertile tile count; local 'noEnemyTooClose'
         * holds the tile's Logic2Layer flags.
         */
        void checkBuildingCanBePlacedHere(
            int playerID, uint x, uint y__fertileLandCount, MappersEnum commandBuildingType, int buildingSize);

        /**
         * NAME? Demolish-target check, not a placement check: its only caller (BuildMenu DeleteAction 0x438A5B)
         * reads buildingPlacementFail/FailReason afterwards and issues command 0x1D with field131_0x554954. Finds
         * the target under the cursor (building id via mouseRayBuildingID or BuildingLayer in flat view, wall tile,
         * moat tile, own pitch ditch), refuses off-map tiles, enemy-nearby targets (reason 0x14, or reason 0 for
         * foreign targets), foreign buildings (unless playerID 0), keeps/signpost/campground/keep doors/pond, wall
         * tiles with units, and buildings without LogicLayer 0x10000400 that are not gates/drawbridge/killing pit;
         * sets field151 (own wall) or field152 (own-team moat) and stores the target in field131 (building id or
         * -pitchDitchID). Param x is reused for the building id (its stack slot is overwritten).
         */
        void evaluateDemolishTargetAtCursor(int playerID, uint x, uint y);

        /**
         * Called by the workshop/bakery/brewery update functions with the building's x,y: clears
         * buildingPlacementFail (determineBuildingPlacementRotation does nothing while it is set), lets that
         * function pick uiBuildingRotation from adjacent wall tiles, then restores the saved flag. extraout_ECX is
         * just this (the callee preserves ECX).
         */
        void computeWallFacingRotationAt(int x, int y);

        /**
         * Draws the placement preview of command building `type` at (x,y) into ConstructionGFXLayer. The one-shot
         * flag previewSkipChecks is read and cleared: if it was clear and the last check result is 2 it returns 2;
         * if it was clear and the check failed, every footprint/extra-part tile gets a marker frame from
         * isBuildingPlacementBlockedAtTile (0x3E when it returns 0, 0x37 when nonzero = blocked; tiles with
         * LogicLayer & 0x10000500 skipped except wood-gate parts). Otherwise (check passed, or flag set - then
         * sprite sheet/IDs are reloaded first) it draws the ghost sprites: generic footprint (rotation relative to
         * mapOrientation, drawbridge rotation remap, gate variation 0x50/0x51 with the map orientation picks
         * buildingSpriteID1/2, type 0x27 offset, hovel style), then special layouts for wood gates, farms,
         * barracks, guilds, oil smelter and keeps; when the flag was set it ORs 0x8000 into MiscDisplayLayer of
         * each ghost tile. Apart from the early 2 the return value is garbage (ignored by both callers). The x
         * argument slot is genuinely reused by the compiler to hold the chosen sprite ID in the ghost loop (x
         * itself was copied to originX), the flag is kept in the y slot.
         */
        int setConstructionGFXLayerBasedOnPlacementChecks(int x, int y, MappersEnum type, int size);

        /**
         * Writes GfxLayer (and the secondary layer stockpileBuildingIdLayer for generic buildings) for every
         * footprint tile of buildingID. First sets usesGfxOffsetLayer = (refreshRelatedOne == 0 && gfxOffset != 0).
         * If flatViewMode is set, draws a brush-size placeholder sprite and clears the secondary layer. Otherwise:
         * stockpiles draw the pile frame for the stored amount (minus pendingResourceLossPreview) by resource type
         * and pile style, mercenary post/barracks/outpost the plain sprite, keep doors pick spriteID+keepDoorValue
         * or gfxOffset by map orientation (+2 for door orientation 2/6), gatehouses/wood gate and manor house
         * choose by orientation and variation 0x50/0x51, drawbridge tiles use a per-part frame table or the
         * moat/ground texture, killing pits with state <= 0 are not drawn for other teams (outside editor), placed
         * siege towers are skipped. Other buildings with variation 0xF use spriteID+keepDoorValue (inactive),
         * visuallyActiveSpriteID or gfxOffset; otherwise spriteID/visuallyActiveSpriteID + rotation*size*size with
         * rotation = variation - mapOrientation (mod 8), except variation 8 which uses the fixed offset
         * 8*size*size.
         */
        void updateBuildingGraphicsLayer(int buildingID);

        /**
         * For every footprint tile of buildingID: recomputes path linkages in all eight directions
         * (updatePathLinkagesInAllEightDirections with the tile row y and tile) and calls clearMoat on the tile;
         * then runs the gate-, keep- or placed-siege-tower-specific path linkage update for those building types.
         */
        void updatePathLinkagesForBuilding(int buildingID);

        /**
         * Places a workshop or hovel for playerID at (x,y): creates it with setupBuildingData, copies the player's
         * hovel style into hovelVisualStyle (and advances it mod 7 when the type is BT_HOVEL), sets
         * placedBuildingID, and for every footprint tile stores the tile in tileRef1..36 (first 36 tiles), sets
         * HeightLayer = averageHeight, LogicLayer |= 0x400, BuildingLayer, BuildingWasLayer = type, ChangedLayer =
         * 2; then setMiscDisplayLayer and updatePathLinkagesForBuilding. For the local player, if the building's
         * buildingTypeBasedEmployeeCount (+0x198) exceeds availablePeasantsAtFire and population is at the cap or
         * popularity < 5000, shows bottom-left message 0x4D. unaff_retaddr is playerID and the odd
         * 'buildings[0].workerID + (size - 6)' is buildings[buildingID].buildingTypeBasedEmployeeCount (decompiler
         * stack drift).
         */
        void placeWorkshopOrHovel(
            int playerID, uint x, uint y, BuildingType type, uint size, int orientation, undefined4 averageHeight);

        /**
         * Places a placed siege tower for playerID at (x,y): creates it via setupBuildingData(playerID, x, y,
         * height, type, size, playerID, orientation), then for every footprint tile stores the tile ref (first 36),
         * sets HeightLayer = height, LogicLayer |= 0x10000000, BuildingLayer, BuildingWasLayer = type and
         * ChangedLayer = 2, and updates misc display and path linkages. this_00 is just this (ECX preserved through
         * setMiscDisplayLayer).
         */
        void placeSiegetowerPlaced(
            int param_1, uint param_2, uint param_3, short param_4, uint param_5, int param_6, undefined4 param_7);

        /**
         * Places a siege tent for playerID at (x,y): setupBuildingData, then marks every footprint tile (tile ref
         * for the first 36, height, LogicLayer 0x400, BuildingLayer, BuildingWasLayer, ChangedLayer), updates misc
         * display/path linkages, and for the local player shows bottom-left message 0x4D when the building's
         * buildingTypeBasedEmployeeCount exceeds availablePeasantsAtFire and population is at the cap or popularity
         * < 5000. unaff_retaddr is playerID (decompiler stack drift after setMiscDisplayLayer).
         */
        void placeSiegeTent(
            int param_1, uint param_2, uint param_3, short param_4, uint param_5, int param_6, undefined4 param_7);

        /**
         * Places a positive fear-factor (decoration) building for playerID at (x,y): setupBuildingData with type,
         * size, height and variation, sets placedBuildingID, marks footprint tiles (tile ref for the first 36,
         * height, LogicLayer 0x400, BuildingLayer, ChangedLayer; BuildingWasLayer not set), updates misc
         * display/path linkages and shows message 0x4D for the local player when workers are short (same test as
         * placeSiegeTent). The 7th stack parameter is never read (ret 0x20).
         */
        void placePositiveFearfactor(int playerID, uint x, uint y, undefined4 buildingType, undefined4 variation,
            uint buildingSize, undefined4 param_7, undefined4 height);

        /**
         * Generic building placement: setupBuildingData for playerID at (x,y) with type, size, height and
         * variation, sets placedBuildingID, then marks every footprint tile (tile ref for the first 36, height,
         * LogicLayer 0x400, BuildingLayer, ChangedLayer; BuildingWasLayer not set) and updates misc display and
         * path linkages. The 7th stack parameter is never read (ret 0x20).
         */
        void stampBuildingOntoTileMap(int param_1, uint param_2, uint param_3, undefined4 param_4, undefined4 param_5,
            uint param_6, undefined4 param_7, undefined4 param_8);

        /**
         * Places a tower for playerID at (x,y): setupBuildingData, sets uidWhenPlaced = uniqueGameObjectTracker,
         * and for each footprint tile stores the tile ref, height, BuildingLayer, BuildingWasLayer, ChangedLayer;
         * the 4 footprint indices listed in TowerTileOffsetsBySize[size] get LogicLayer 0x400, all others
         * 0x10000000. Then updates misc display and path linkages.
         */
        void placeTower(
            int param_1, uint param_2, uint param_3, undefined4 param_4, uint size, int param_6, undefined4 param_7);

        /**
         * Save-version upgrade (called by Version::UpgradeTowerLogicLayer): rewrites the LogicLayer flags of an
         * existing tower's footprint (clears 0x400, then sets 0x400 on the TowerTileOffsetsBySize tiles and
         * 0x10000000 on the rest) and updates its path linkages. this_00 is this (ECX preserved by
         * getBuildingSizeIndexMappingData).
         */
        void upgradeTowerLogicLayer(int buildingID);

        /**
         * Resets a tile before a building part is stamped on it: clears LogicLayer bits 0x410B08, restores
         * DefaultHeightLayer, zeroes DamageLayer, sets state 3 on a tree of type 5-14 or 16-19 standing there
         * (LogicLayer 0x1000, OrganismLayer id < 2000), clears moat data (clearMoatDataAtTile with x,y) and bits
         * 0x40004000 if either is set, and clears MiscDisplayLayer bits 0x3C0.
         */
        void resetTileAndClearMoat(int tile);

        /**
         * Places a small gatehouse for playerID at (x,y): setupBuildingData, records uidWhenPlaced, and for each
         * footprint tile stores the tile ref, sets height to height+0x5A, LogicLayer wall flag 0x100, wall owner
         * bits (playerID-1), MiscDisplayLayer 0x20, BuildingLayer/BuildingWasLayer/ChangedLayer; then
         * createClimbData(4, buildingID, 0, 2 if variation 0x50 else 0, 0) and updates misc display and path
         * linkages.
         */
        void placeGatehouseSmall(
            int param_1, uint param_2, uint param_3, undefined4 param_4, uint param_5, int param_6, undefined4 param_7);

        /**
         * Places a large gatehouse; identical to placeGatehouseSmall except createClimbData type 3: marks footprint
         * tiles as owned wall (height+0x5A, LogicLayer 0x100, wall owner, MiscDisplayLayer 0x20, tile refs,
         * BuildingLayer/BuildingWasLayer/ChangedLayer) and updates misc display and path linkages.
         */
        void placeGatehouseLarge(
            int param_1, uint param_2, uint param_3, undefined4 param_4, uint param_5, int param_6, undefined4 param_7);

        /**
         * Places a barracks or mercenary post: rotationIndex = orientation/2 (0 for 0xF). Creates the main building
         * (variation 0xF, uidWhenPlaced = uniqueGameObjectTracker), stamps its footprint (tileRefs, HeightLayer,
         * LogicLayer 0x400, BuildingLayer, BuildingWasLayer = type, ChangedLayer). Then three 5x5 parts at (x,y) +
         * BuildingPartsOffsets[rotationIndex][0/1/2] with types PARADEGROUND3/4/2, each with the main height and
         * uid and linkedBuildingID = main id; each part tile is reset by resetTileAndClearMoat, gets the height,
         * LogicLayer 0x400 only on the centre tile (2,2), BuildingLayer = part id, BuildingWasLayer = main type;
         * after each part setMiscDisplayLayer, updatePathLinkagesForBuilding, updateWalkAndPathLayer(8, partX,
         * partY). Finally sets up mercenary-post (type 8) or barracks campground positions and shows worker message
         * 0x4D for the local player, tested against the LAST part's employee count.
         */
        void placeBarracks(int playerID, uint xPosition, int* yPosition_param, undefined4 buildingType,
            uint buildingSize, int buildingOrientation, undefined4 param_7);

        /**
         * Places an engineers' guild (machine-code reading): rotationIndex = orientation/2 (0 for 0xF); creates the
         * main building with orientation 0xF and uidWhenPlaced = uniqueGameObjectTracker, stamps its footprint
         * (tileRef1.., height, LogicLayer 0x400, BuildingLayer, BuildingWasLayer = type, ChangedLayer),
         * setMiscDisplayLayer + updatePathLinkagesForBuilding; then creates the 5x5 BT_PARADEGROUND (0x35) part at
         * (x,y) + BuildingPartsOffsets[rotationIndex][1] with the main height and uid, quarryStockpileID = main id,
         * resets each part tile (resetTileAndClearMoat) and sets height, BuildingLayer = part id, BuildingWasLayer
         * = main type; then setMiscDisplayLayer, path linkages, updateWalkAndPathLayer(8, partX, partY) and
         * setupEngineersGuildParagroundPositions(playerID). Artefacts (stack drift 4 per setMiscDisplayLayer):
         * unaff_retaddr = playerID, unaff_EBX = rotationIndex, the local 'playerID' passed at the end is the real
         * playerID (it is not the uid), part uidWhenPlaced = the uid (not local_8), the part's height argument is
         * height (not uVar2), and param_2/param_4/param_6 reuse in the second half are other slots (tileRef
         * pointer, loop index, height).
         */
        void placeEngineersguild(
            int param_1, int* param_2, uint param_3, undefined4 param_4, uint param_5, int param_6, undefined4 param_7);

        /**
         * Places a tunnelers' guild: creates the main building (variation 0xF, uidWhenPlaced =
         * uniqueGameObjectTracker) and stamps its footprint (tileRefs, height, LogicLayer 0x400, BuildingLayer,
         * BuildingWasLayer, ChangedLayer); then the 5x5 BT_PARADEGROUND5 part at (x,y) +
         * BuildingPartsOffsets[rotationIndex][1] with the main height and uid and linkedBuildingID = main id,
         * resets and stamps its tiles (no LogicLayer bit, BuildingWasLayer = main type), updates misc display, path
         * linkages, updateWalkAndPathLayer(8, partX, partY) and setupTunnelersGuildCampgroundPositions(playerID).
         */
        void placeTunnelersguild(
            int param_1, int* param_2, uint param_3, undefined4 param_4, uint param_5, int param_6, undefined4 param_7);

        /**
         * Places an oil smelter: creates the main building (variation 0xF, uidWhenPlaced = uniqueGameObjectTracker)
         * and stamps its footprint without tile refs (height, LogicLayer 0x400, BuildingLayer, BuildingWasLayer,
         * ChangedLayer), setMiscDisplayLayer + path linkages; then creates the 4x4 part of type 0x33 (enum
         * BT_OILSMELTER_PART) at (x,y) + oilSmelterPartOffsetByRot[rotationIndex] with the main height and uid, cross-
         * links main and part via linkedBuildingID, resets and stamps the part tiles (BuildingWasLayer = main
         * type), calls setTileRefsForOilSmelter(part), setMiscDisplayLayer, path linkages and
         * updateWalkAndPathLayer(8, partX, partY).
         */
        void placeOilsmelter(
            int param_1, uint param_2, uint param_3, undefined4 param_4, uint param_5, int param_6, undefined4 param_7);

        /**
         * Places a quarry: creates it (uidWhenPlaced = uniqueGameObjectTracker), stamps the footprint without tile
         * refs (height, LogicLayer 0x400, BuildingLayer, BuildingWasLayer, ChangedLayer), setMiscDisplayLayer +
         * path linkages, then calls findQuarryPileLocation(..., attempt, M_MAPPER_QUARRYPILE) for attempt 1..9
         * until buildingPlacementResult is FALSE; if none succeeds it returns. Otherwise it takes the 2x2 spot at
         * (x,y) + TempX/YOffset, uses the midpoint of min/max tile heights, creates BT_QUARRYSTOCKPILE there with
         * the quarry's orientation, increments the AIV structure heat map, gives it the same uid, stores the pile
         * id in the quarry's linkedBuildingID, stamps the pile tiles (resetTileAndClearMoat, mid height, LogicLayer
         * 0x400, BuildingWasLayer = quarry type) and shows worker message 0x4D for the local player tested against
         * the pile's employee count. Locals uidOrPlayerID (footprint tile, then pile id) and tileHeight (saved y,
         * then pile y) are misnamed; heightUnk is the height arg reused as min height.
         */
        void placeQuarry(int playerID, uint x, uint y, undefined4 buildingType, uint buildingSize,
            int buildingOrientation, uint heightUnk);

        /**
         * Places a stockpile: for each of the 4 Stockpile_BuildingPartsOffsets entries creates a 2x2 stockpile
         * building (height+10, same uid, stockpilePartNumber = 1..4) and marks its tiles (height+10, LogicLayer |=
         * 0x502, wall owner bits playerID-1, BuildingLayer, BuildingWasLayer = type, ChangedLayer) and updates its
         * path linkages; then the 9 StockpilePathableOffsets tiles get LogicLayer |= 0x102, height+10,
         * stockpileBuildingIdLayer = last part id, BuildingWasLayer and wall owner bits. placedBuildingID = last
         * part; worker message 0x4D for the local player uses the last part's employee count. The 5th stack
         * parameter is never read (ret 0x1C).
         */
        void placeStockpile(
            int playerID, int x, int y, undefined4 buildingType, undefined4 param_5, int variation, int averageHeight);

        /**
         * NAME? Drawbridge-only: its caller clearBuildingFromTerrain calls it only for building type 0x31
         * (drawbridge, 0x515B95), and it indexes DrawbridgeOrientationMapping by the building's variation. For each
         * tile of the 5x5 area at (x,y): clears LogicLayer 0x400; on bridge tiles over an owned moat it either
         * removes the moat (clearMoatData, clear water flag, Logic2Layer |= 2, BuildingWasLayer = 0, height 8) or,
         * if noRubble is set on the building, keeps the tile as water (LogicLayer |= 0x40000000); tiles without the
         * water flag get Logic2Layer |= 2 and BuildingWasLayer = 0; BuildingLayer = 0 and ChangedLayer = 2
         * everywhere.
         */
        void clearDrawbridgeFootprintAndMoat(int x, int y);

        /**
         * Save-version fixup (Version::UpgradeDestroyDrawbridgesInFirst10Buildings): for each tile of a 5x5 area at
         * (x,y) clears the water flag 0x40000000, sets height 8, clears any owned moat data there, and resets
         * BuildingLayer/BuildingWasLayer and sets ChangedLayer.
         */
        void clearDrawBridgeWater(int x, int y);

        /**
         * For drawbridge buildingID (called by UpdateDrawBridge when the bridge starts raising), re-marks every
         * bridge tile (per DrawbridgeOrientationMapping[variation/2]) that lies on an owned moat as water
         * (LogicLayer 0x40000000, moat visual state 2), then refreshes the building graphics, path linkages,
         * updateWalkAndPathLayer(size+6, x, y) and flags the separate-area map for update.
         */
        void floodMoatUnderRaisingDrawbridge(int buildingID);

        /**
         * Draws the brush preview of a terrain/mapper tool at tile (x,y) into ConstructionGFXLayer. Off-map tiles
         * return. buildingPlacementFail is set FALSE for the four pond mappers (return), otherwise TRUE; the
         * signpost mapper returns there. The marker frame is chosen by mapper category (water 0x39, beach/ford
         * 0x3A, rocks/iron 0x3B, undug moat/oil 0x3D, dunes/scrub/dirt 0x3C, height tools/delete/trees/animals 0x3E
         * with a 1-tile brush for trees and animals, default 0x38). For the moat mappers outside editor/Siege That
         * the frame becomes 0x3E when an enemy is within 0x1E (single player) / 0xF, a signpost is within
         * unk_signpostDistance+5, or (multiplayer) isOpponentBuildingInRange(range 7, castle build range+5) hits;
         * moat mappers paint a fixed 9-tile brush (getTileForBrush mode 0), others paint
         * BrushSizeArray[editorActiveBrush] tiles. The y and mapper-type arg slots are reused (brush tile count,
         * opponent range, brush row output).
         */
        void renderPreviewMapperWithBrush(uint x, uint y, MappersEnum mapperTypeOrTemp);

        /**
         * Applies a tree's footprint to LogicLayer: brush size =
         * BrushSizeArray[getValueFrom0UpTo3ForTreeTypeAndTreeStage(type, stage)]; for each brush tile around the
         * tree (stopping the whole loop at the first tile with LogicLayer 0x10) and skipping tiles with 0x60000001,
         * sets the tree-variation bit 0x2000, or clears it when noVariation != 0; then updateWalkAndPathLayer(7,
         * tree x, tree y). The treeID parameter slot is reused as the brush tile output.
         */
        void applyTreeBrushToLogicalLayer(int treeID, int noVariation);

        /**
         * Erase command (Commands::ClickErase): over BrushSizeArray[brushSizeIndex] brush tiles around (x,y), each
         * pass stopping at the first tile with LogicLayer 0x30: (1) removes trees (OrganismLayer id < 2000) or
         * rocks (id-2000), then updateWalkAndPathLayer(3 or 8, centre x, tile row y),
         * toggleUpdateSeparateAreaTileMap and field204 = 1; (2) clears field151, calls
         * validateBuildingPlacementAtTile(0, centre x, tile row y) and, if it succeeds, either spawns an eraser
         * effect (wall target) or destroys building field131 without rubble, first destroying the owner's stockpile
         * when the target is the keep and the keep when the target is a stockpile (type 0xA); (3) sets ULS_REMOVE
         * on every unit chained on each tile. Passes 1 and 2 use the centre x with each brush tile's row (x is
         * never taken from the brush tile). The x/y/brushSizeIndex slots are reused as getTileForBrush outputs and
         * saved y.
         */
        void eraseAreaWithBrush(uint xOrTile, uint yOrTileY, uint brushIndexOrY);

        /**
         * If forceUpdateTextureTilemap > 0, decrements it and makes four passes over the tiles of every flagged
         * 10x10 section (byte grid at 0x1f93438, 0x28 bytes per section row) inside the dirty section row/column
         * range; the first flagged section starts at row DAT_PathFindingState.dirtyMinY%10. Each pass handles only
         * valid tiles whose ChangedLayer is non-zero. Pass 1 (tiles with no building; drawbridge tiles only get
         * their luminescence recomputed) recomputes luminescence and sets rubble, brush (LogicLayer
         * 0x100000/0x200000), farm-field (0x1000000 wheat / 0x2000000 hops, setting
         * DAT_BuildingsState.farmFieldGfxFullRefresh = 1), climb-ramp and wall-corner/stair graphics plus the
         * inner-wall-corner fill (WallGFXLayer = lowest adjacent wall height, AlphaGFXLayer 0x2e-0x31,
         * WallOwnerLayer|8 if one of those walls is damaged). Pass 2 (LogicLayer&0x100201): water tiles get a shore
         * sprite from the neighbour they face and store the low-land neighbour mask in MiscDisplayLayer 0x100 /
         * CertainPathLayer; other 0x100000 tiles get computeTileCliffEdgeFlags; 0x200 tiles get diagonal-pair
         * sprites. Pass 3: a water tile without MiscDisplay 0x40 gets MiscDisplay 0x80 and an edge sprite when some
         * neighbour has 0x40 but not 0x80. Pass 4 decrements ChangedLayer and picks the final
         * GfxLayer/PillarGFXLayer/WallGFXLayer/AlphaGFXLayer (buildings via updateBuildingGraphicsLayer,
         * stockpile/ballista/killing pit, pitch ditches, moat, rocks via applyRockGraphicsToFootprint, cliffs,
         * terrain transitions, water edges) from neighbour masks, height, luminescence, RandomLayer and
         * mapOrientation. The 'call' through PTR_ARRAY_00510d94 followed by 'return' is a mis-decompiled 4-way jump
         * table (0x50AB3A jmp [edx*4+0x510d94], index wallCornerKind-1): it does not return, each target stores the
         * two cardinal wall neighbours and the diagonal between them (cornerWallNbrA/B, cornerDiagonalNbr) and
         * jumps to the height comparison at 0x50AD2B.
         */
        void updateGfxLayer();

        /**
         * Per-tick: if forceUpdateMacroLayerFlag > 0, clears it and rebuilds the macro (coarse) map layer by
         * calling updateMacroLayerRelated for several masks (0x8000 with mode 1, 0x20000000 with mode 0, then modes
         * 2/0x10/0x20/4/8 with mask 0), then updateMacroLayerRelated2, and requests a texture tilemap refresh.
         */
        void updateMacroLayer();

        /**
         * Registers a moat tile for playerID at (x,y): returns 0 if out of 400x400 bounds or the tile is not valid
         * (byte map at 0x21aec98); returns the existing moat ID on that tile if returnOwnedMoatAtTile finds one; in
         * Siege That mode requires enough gold. Otherwise takes the first free slot in moats[1..15999] (raising
         * currentMoatCount), stores owner/x/y/tile, zeroOrTwo=2, and either stage 1 with dig depth 0 (filled==0:
         * planned, still to be dug) or stage 2 with dig depth 4 (already dug), increments moatTileCount and returns
         * the new moat ID (0 if no free slot). Note: the 'filled' parameter actually means 'already dug'.
         */
        int createMoatData(undefined4 playerID, uint x, uint y, int filled);

        /**
         * Picks the best moat job for unit unitID of playerID; number selects the job and must equal the moat
         * stage: 1 = dig a planned moat (stage 1) owned by the player's own team, 2 = fill a dug moat (stage 2)
         * owned by an enemy team (also requires hasNeighborTileInSameAreaWithinHeightLimit), other values = any
         * owner. Tile must have no building (or zeroOrTwo != 0), logic bits 0x40004000, worker-reservation counter
         * < 100 and no unit (or one with someUnitStat4 set). Score = distance unit->moat + half distance unit
         * target->moat + reservation counter (+10 * moat owner's per-player tile byte at 0x1ee2998 when
         * currentPlayerFullIDArray[playerID] == -1). Returns the lowest-score moat ID and adds 20 to its
         * reservation counter; if nothing qualifies it returns -1 (callers test < 0) and, as a quirk, still adds 20
         * to the byte just before moats[0] (moats[-1].someCountDown). The unitID parameter is reused as the moat
         * loop index (loop starts at slot 0). NAME? also finds enemy moats to fill when number==2, not only
         * friendly moats to dig.
         */
        BOOLEnum findBestMoatTileForWork(int playerID, int unitID, int number);

        /**
         * One fill-in work step by a unit on a dug moat: decrements its dig depth; when it drops to <= 0 the moat
         * is filled in: tile height reset to 8, logic bit 0x40000000 cleared, walk/path layers and path linkages
         * updated, the moat slot cleared, building graphics refreshed if a building stands on the tile, minimap
         * redrawn; returns TRUE. Otherwise FALSE. The second stack parameter is never read (ret 8). NAME? it fills
         * in a moat gradually (counterpart of advanceMoatDigProgress) rather than removing it at once.
         */
        BOOLEnum removeMoat(uint moatID, int unused);

        /**
         * Per-tick pitch ditch state machine. When gameTicksLoadBalancer%10==3 recomputes maxPitchDitchCount as
         * highest used slot+1. For each used ditch: destroyed (destroyPitchDitch) when its tile lost logic bit 8 or
         * state is -1; state 0 -> 1 (ready/ignitable) with timer 0; state 2 (burning) counts its timer to 20, then
         * switches to state 3 and ignites each of the 4 neighbour tiles (offset table at 0xb4c6c0) that hold a
         * state-1 ditch whose height differs by < 25 (SetPlaceOnFire at the neighbour, state 2); state 3 counts to
         * 200, then restores the tile height from DefaultHeightLayer and sets state -1 so the next tick removes it.
         * State 1 is left unchanged here (ignition happens elsewhere).
         */
        void updatePitchDitches();

        /**
         * Creates a pitch ditch for playerID at (x,y) if in bounds, valid and not already a ditch: takes the first
         * free slot of pitchDitches[1..3999] (raising maxPitchDitchCount), stores owner, unique object ID,
         * x/y/tile, state 0, timer 0 and an RNG value; lowers the tile height by 4 (to 0 if < 5), sets logic bit 8,
         * clears MiscDisplay bits 0x4000/0x2000 and marks the tile changed. Returns the new ditch ID, the existing
         * ditch ID on the tile, or 0 (invalid tile / no free slot).
         */
        int placePitchDitch(undefined4 playerID, uint x, uint y);

        /**
         * Per-tick 40-step ramp: while gameEventRelatedCountdown is non-zero, decrements it (forcing
         * field187_0x554a10 to -1 on the first step), lets setSignpostDistanceForCampaignMission set
         * unk_signpostDistance for the current mode/mission, computes value =
         * (40-countdown)*unk_signpostDistance/40 and, when it differs from the stored one, stores it and calls
         * pathfindingUpdate_0x4a8ab0 with it. extraout_ECX is just this (the callee never touches ECX). NAME?
         * vague; it ramps a signpost/distance value over 40 ticks.
         */
        void updateGameRelatedValue();

        /**
         * Map load: runs the three unconditional logic-layer fixups, defaults mapSize to 400, and if the loaded map
         * version differs from the current one applies each logic-layer upgrade step for versions below
         * 102/120/125/128/145/147 in order.
         */
        void upgradeMapFormatLogicLayer(
            PackagedFileMagicNum receivedMapVersion, PackagedFileMagicNum packagerMapVersion);

        /**
         * Zero-fills all per-tile map layers (fixed BSS addresses, 400x400 tiles at 1/2/4 bytes per tile, plus a 9x
         * per-player byte map at 0x1ee2998), fills RandomLayer with fresh SEC_RNG values, resets map orientation to
         * 0 and clears the pending orientation change (8 = none).
         */
        void setupTileMapSections();

        /**
         * Full reset to an empty map: clears tile sections, rebuilds viewport lookups and borders, sets GfxLayer
         * per tile to base graphic GMFirstPictureIndex[2] +0/+1/+2 for LogicLayer 0x10/0x20/other (unrolled 6
         * tiles per iteration), sets PillarGFXLayer to 1 and Height/DefaultHeight layers to 8, then clears
         * buildings, landscape, units, tribes, game state, the AI tribe ID/UID arrays and entities, flags all
         * layers for refresh, rebuilds path linkage/areas and minimap, and resets transient state.
         */
        void setupAllMapSections();

        /**
         * Post-load map preparation: saves viewportX/Y; for single-player skirmish sets mode/host, copies the local
         * player name into slot 1 and syncs AI names; campaign missions < 16 and builder mode switch to solitary
         * mode. Re-applies the map orientation, resets the search-generation layer, restores the saved viewport,
         * sets the object pool limits, resets heights/borders and flat view, runs all per-subsystem map-version
         * upgrades, rebuilds pathfinding/climb data, buildings, landscape, the 40 wildlife grids, runs one game
         * tick and redraws the minimap.
         */
        void prepareMap();

        /**
         * Unreferenced (no direct callers): for every tile whose LogicLayer has bit 0x10 or 0x20 set, erases it
         * with the eraser brush and resets all per-tile layers (graphics, logic, height/default height to 8,
         * damage, ownership, AI, pathfinding cost maps) to defaults.
         */
        void resetAreaBasedOnLogicalLayer();

        /**
         * Per-tick: applies a pending map orientation change (DAT_FutureMapOrientation < 8) via
         * changeMapOrientation and resets the pending value to 8 (none).
         */
        void processMapOrientationChange();

        /**
         * Applies a terrain brush (BrushSizeArray[brushType] tiles, 9 for moat) around tile/yParam: for each brush
         * tile from getTileForBrush (yParam is overwritten with the tile's y) that is not a border tile (logic
         * 0x10), sets the terrain selected by flags1 (sea, river/ford, rocky, iron, pebbles, marsh, oil only on
         * marsh, boulders, moat) or the flags2 ground texture (earth, grass, beach, scrub...), clearing conflicting
         * LogicLayer bits and adjusting height, then updates path linkages (unless flags1 is L_NONE). Moat (flags1
         * L_MOAT): flags2 NONE plans a moat (createMoatData undug, bit 0x4000), SCRUB removes a planned one,
         * EARTH_AND_STONES creates a dug moat (bit 0x40000000, height 0), MOAT_UNDUG fills it in (height 8);
         * outside editor/Siege That it requires no enemy within 30 (solitary) / 15 tiles and, outside solitary
         * mode, no opponent building within radius 7 / castle build range + 5. In the editor, ground textures are
         * additionally passed to setLand.
         */
        void setTerrain(int playerID, int tile, uint yParam, uint brushType, Logic1 flags1, Logic2 flags2);

        /**
         * AI moat planning for one tile: if the tile is free (no border, organism, building, wall/gatehouse,
         * water/marsh/rock/iron etc., not already a planned or dug moat (0x40004000), height < 13) creates a
         * planned (undug) moat entry for playerID and sets LogicLayer bit 0x4000, then updates path linkages around
         * the tile.
         */
        void planMoat(undefined4 playerID, int tile, uint tileY);

        /**
         * Places a killing pit (placeBuilding routes only BT_KILLINGPIT 0x43 here): creates the building via
         * setupBuildingData, records the first 36 footprint tiles in its tileRef array and writes height =
         * averageHeight, BuildingLayer and BuildingWasLayer per tile. The branch for any other type (height lowered
         * by 4, ground repainted as earth or thick scrub if the origin tile had grass/scrub) is unreachable from
         * placeBuilding. Afterwards, for the local player, shows bottom-left message 0x4d when free peasants < the
         * building's employee count and (housing full or popularity < 5000). unaff_retaddr in that check is really
         * playerID: the decompiler loses 4 bytes of stack after setMiscDisplayLayer (callee pops its argument, see
         * review SIGNATURE note).
         */
        void placeKillingPit(
            int param_1, uint param_2, uint param_3, short param_4, uint param_5, int param_6, int param_7);

        /**
         * Places a keep or manor house for playerID: optionally demolishes buildings in the footprint, creates the
         * keep (uidWhenPlaced = uniqueGameObjectTracker read at entry) and its footprint tiles (logic 0x10000000,
         * or 0x400 for the manor house; earth or thick scrub ground depending on the origin tile's Logic2 bits
         * 0x90). Then creates the left (0x47), centre (0x49, MiscDisplay bit 4) and right (0x48) doors, each linked
         * to the keep with the original orientation, from the DAT_TerrainDefinedData table (+0x264..+0x278) indexed
         * by (type-0x28)*4 + orientation/2 (orientation 0xF treated as 0); the 7x7 campground (+0x384/+0x388) with
         * a blocked plus-shaped centre; and a 5x5 stockpile (+0x3e4/+0x3e8). Door keepDoorValue is 2 for manor
         * house/stone keep (centre door gets half), else 0.
         */
        void placeKeep(int playerID, uint x, uint y, BuildingType type, uint size, int orientation, int xyValue);

        /**
         * Places a drawbridge: creates the building, then for each footprint tile stores it in the building's tile
         * refs, writes BuildingLayer/BuildingWasLayer, makes tiles flagged in DrawbridgeTileMoatProperty impassable
         * (0x400), and for tiles whose DrawbridgeOrientationMapping[orientation/2] entry is non-zero creates a dug
         * moat entry (createMoatData filled=1) with moat visual and height 0; logic bit 0x40000000 is cleared on
         * every tile. The orientation parameter is reused as a pointer into the mapping row and averageHeight to
         * hold the building ID.
         */
        void placeDrawbridge(int playerID, uint x, uint y, undefined4 buildingType, uint width, int* orientation,
            undefined4 averageHeight);

        /**
         * Places a wheat farm: creates the 3x3 farmhouse, marks the footprint flag area (9), stores the 36 field
         * tiles from WheatFarmTiles[player layout] into tileRef1..36, toggles the player's layout (0/1), sets
         * farmhouse tiles (height, 0x400, thick scrub) and field tiles (moat cleared, logic 0x1000000), updates
         * path linkages and, for the local player, may show message 0x4d (free peasants < employee count and
         * housing full or popularity < 5000). The size parameter is unused (fixed 3). Tail artefacts (4-byte stack
         * misread after setMiscDisplayLayer): unaff_retaddr = playerID, unaff_EBX = buildingID*0x32c, and the 'x'
         * in the player-field expressions is playerID*0x39f4.
         */
        void placeWheatfarm(int playerID, uint x, uint y, undefined4 buildingType, undefined4 param_5, int variation,
            undefined4 averageHeight);

        /**
         * Places a hop farm: creates the 3x3 farmhouse, marks the footprint flag area (9), stores 24 field tiles
         * from hopFarmFieldTiles[player variation] into the tile refs, sets hopFarmLayoutCode to 0x51 (variation 0)
         * or 7, sets farmhouse tiles (height, logic 0x400, thick scrub) and field tiles (moat cleared, logic
         * 0x2000000, path linkages), then toggles the player's hop farm variation (0/1). For the local player shows
         * message 0x4d when free peasants at the fire are fewer than the farm's workers and population is at the
         * cap or popularity < 5000 (50.00).
         */
        void placeHopfarm(
            int param_1, uint param_2, uint param_3, undefined4 param_4, undefined4 param_5, int param_6, int param_7);

        /**
         * Places a dairy farm: creates the 3x3 farmhouse, marks the footprint flag area (10), writes the 27 tiles
         * of the player's current dairy layout (field1009_0xf5c[dairyFarmVariationMod4], cycling 0..3) into
         * tileRef1..27 (clearing moats; tiles from index 4 get the layout's property byte in DamageLayer), sets
         * farmhouse tiles (height, 0x400, thick scrub), flags the 23 pasture tiles (tileRef5..27) with logic
         * 0x8000000 and updates their path linkages, then may show message 0x4d for the local player (free peasants
         * < employee count and housing full or popularity < 5000). Tail artefacts (4-byte stack misread after
         * setMiscDisplayLayer): unaff_retaddr = playerID, unaff_EBX = playerID*0x39f4, and 'buildings +
         * param_1*0x39f4 + 0x198' is really the farm's employee count (buildingID*0x32c + 0xf986cc).
         */
        void placeDairyfarm(int param_1, uint param_2, uint param_3, undefined4 param_4, undefined4 param_5,
            int* param_6, undefined4 param_7);

        /**
         * Places an apple farm: creates the 3x3 farmhouse, marks the footprint flag area (10), stores the 8 orchard
         * tiles from AppleFarmOffsets in tileRef1..8, sets farmhouse tiles (height, 0x400, thick scrub), then for
         * each orchard tile clears moats, sets logic 0x4000000 and places an apple tree; finally updates path
         * linkages and may show message 0x4d for the local player. buildingType is reused as a pointer into the
         * tile refs (the '+BT_OXTETHER' step is +4 bytes) and param_7 as a pointer into AppleFarmOffsets. Tail
         * artefacts (4-byte stack misread after setMiscDisplayLayer): unaff_retaddr = playerID, and 'workerID + (x
         * - 6)' is the farm's employee count (the y slot then holds buildingID*0x32c).
         */
        void placeApplefarm(
            int playerID, uint x, uint y, BuildingType buildingType, undefined4 param_5, int param_6, int* param_7);

        /**
         * Removes a building's footprint from the terrain (on delete or when clearing space): unless it is a
         * killing pit, returns early when validateBuildingPlacementAtTile(owner,x,y) sets buildingPlacementFail;
         * then per type clears the stockpile, the farm fields and trees (wheat 36, hop 24, dairy 27, apple 8 tiles)
         * and their footprint flag area, drawbridge moats, siege-tent rubble or a placed siege tower, otherwise the
         * plain footprint; finally updates path linkages (except for a placed siege tower), the walk layer (size+6,
         * 12 for farms), separate areas and the minimap (tail call). this_00..03/extraout_ECX are all this: the
         * callees preserve ECX.
         */
        void clearBuildingFromTerrain(int buildingID);

        /**
         * When a drawbridge is lowered (called from UpdateDrawBridge): for each of its 5x5 footprint tiles whose
         * DrawbridgeOrientationMapping entry (row buildingVariation/2) is non-zero, creates a dug moat entry for
         * the owner, clears logic bit 0x40000000, sets the moat visual and height 0; then refreshes building
         * graphics, path linkages and the walk layer (size+6).
         */
        void createWaterForDrawBridge(int buildingID);

        /**
         * Places a tree at (x,y) for the ClickPlaceRockOrTree command: maps the UI tree type to a logical type,
         * gets its size class (0..3) and brush size, and if the base tile has none of the logic bits 0x703e25b5
         * scans the brush tiles: a wall/building/0x400/0x100000 tile, a rock (bit 0x80) or an organism aborts; a
         * border tile (0x10) just ends the scan. Then creates the tree, marks its tile as tree (0x1000, clears
         * 0x80), stores it in OrganismLayer, applies the tree brush to the logic layer and updates path linkages.
         * The y parameter is reused as the brush tile output.
         */
        void placeTree(uint x, uint y, undefined4 treeType);

        /**
         * AI helper before placing a building of size buildingWidthOrHeight at (x,y): stores the area's min/max
         * height, returns FALSE if any footprint tile is off-map/invalid/border or isBuildingPlacementAllowedAtTile
         * returns 1. Otherwise, with no owner check, removes every woodcutter, ox tether, quarry, iron mine or farm
         * on the footprint (or the farm owning an orchard tile, logic 0x4000000): refunds 50% to playerID, clears
         * it from the terrain, updates player building references and zeroes its 0x32c-byte record; returns TRUE if
         * anything was removed. commandBuildingType is reused as the second loop counter.
         */
        BOOLEnum prepareAreaForBuildingPlacement(
            int playerID, uint x, uint y, MappersEnum commandBuildingType, int buildingWidthOrHeight);

        /**
         * Places a building of mapper command type cbt for playerID at (x,y): checks placement (unless
         * forcePlaceBuilding) and tutorial restrictions, converts cbt to a BuildingType, clears every footprint
         * tile (rocks, trees, units unless the building type tolerates them, moats, logic bits, height reset to
         * default, damage 0; in Siege That counts tiles with logic bit 0x100 into a player counter), takes the
         * midpoint of min/max ground height and dispatches to the type-specific place* function (placing a
         * BT_TUNNEL (0x32) also plays the tunneler command speech for the local player). For the local player
         * records the pitch ditch or starts the placement undo window; then applies resource cost, the low-wood no-
         * refund flag, minimap and walk-layer refresh (radius 9, or size+5 for size > 5).
         */
        void placeBuilding(PlayerID playerID, int x, int y, MappersEnum cbt, int buildingSize, int buildingOrientation);

        /**
         * Applies damage at a tile. A negative playerID means attacker -playerID with friendly protection when
         * currentPlayerFullIDArray[-playerID] == -1. Wall tiles (logic 0x100): returns FALSE for logic bit 2 and
         * protected same-team walls, records defensesDamagedByPlayer and the unit's friendlyStructureHitCount
         * (incremented on same team, else reset), scales damage by neighbouring wall count (x1.5 / x0.5), noDamage
         * zeroes it, drops a tall undamaged wall by 20 first, then lowers it one height step per damage point
         * (DamageLayer up to 200) and clears it at ground level. Building tiles: returns TRUE for
         * inactive/healthless buildings and farmland, subtracts health (same-team protected); with
         * aiBuildDelayRelated it destroys drawbridges attached to a damaged gatehouse and sets the owner's
         * resourceRebuildDelay on destruction. On destruction records statistics (except types 0x4f, 0x56..0x59),
         * plays AI anger/victory videos and Genie voices, and handles oil smelter fire, gatehouses, tunnels, placed
         * siege towers and towers (replaced by ruins via placeBuilding). Every hit adds damage*10 to the battle-
         * intensity accumulator. Returns TRUE when destroyed or nothing damageable, FALSE when only damaged,
         * protected, or a ruin was placed.
         */
        BOOLEnum processDamageToBuilding(int tile, uint xPosition, uint yPosition, int damageUnk, int param_5,
            int playerID, BOOLEnum aiBuildDelayRelated, int unitID);

        /**
         * Collateral damage from an entity/projectile hit to the target tile and its 8 neighbours (9 steps of
         * getTileForBrush brush 0). A negative playerID is negated; if that attacker is AI-controlled
         * (currentPlayerFullIDArray == -1) same-team walls/buildings are spared. Wall tiles lose 1 height per
         * damage point (DamageLayer up to 200) and are flattened (entities destroyed, flags cleared, path linkages
         * rebuilt) once at default height; buildings with health lose `damage` HP and at <=0 are destroyed with
         * type-specific handling (oil smelter fire, gatehouse + drawbridges, tunnel collapse via its tunneler,
         * siege tower, towers replaced by ruined mappers), plus destroy stats, AI anger/victory videos and Genie
         * lines. Each hit sets defensesDamagedByPlayer (walls, gatehouse/tower types), updates the attacking unit's
         * friendlyFireCounterUnk and adds damage*10 to GameCore.battleLevelAccumulator; finally refreshes walk/path
         * layers around (x_2, y_2).
         */
        void processEntityDamageToBuildingCollateral(
            int tile, uint x_2, uint y_2, int damage, int playerID, undefined4 unused, int unitID);
    };

    static_assert_cpp98_obj(sizeof(TileMapState) == 5589640, TileMapState);

#pragma pack(pop)

} // namespace Map
} // namespace OpenSHC
