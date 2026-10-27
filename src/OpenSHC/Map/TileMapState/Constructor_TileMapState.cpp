
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00515F40
    TileMapState* TileMapState::Constructor_TileMapState()
    {
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setupMovementDirectionTranslationMatrix, this)();
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setupBuildingSizeIndexMapping, this)();
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setupTileMapSections, this)();
        this->editorActiveBrush = 7;
        this->heightOffsetAnimMode = 2;
        this->heightAnimFrame = 0;
        this->mapperMax = FALSE;
        this->mapperSnapMode = 0;
        this->mapperAffectType = 0;
        this->unknownZero_0x554900 = 0;
        this->currentMapperCommand = OpenSHC::Commands::M_MAPPER_NULL;
        this->fullHeightViewActive = 1;
        this->flatViewMode = 0;
        this->refreshRelatedTwo = 0;
        this->forceUpdateLogicalAndMiscDisplayLayers = 1;
        this->forceUpdateTextureTilemap = 1;
        this->forceUpdateGFXLayers = 1;
        this->refreshCertainTileMap_old = 4;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setChangedLayerToThreeAndMapping0x40x40, this)();
        this->moatTileCount = 0;
        this->forcePlaceBuilding = 0;
        this->gatePreviewOrientation = 0x50;
        this->lastTime = timeGetTime();
        this->rockOrientation = 0;
        this->editorBigRockType = 0;
        this->floatAnimLastTickMs = timeGetTime();
        this->floatAnimFrame = 1;
        this->dustCloudSourceCount = 0;
        this->previewSkipChecks = 0;
        DAT_GameCore::instance.isTimeHalted = FALSE;
        DAT_GameState::instance.mapAndTime.skirmishFogOfWar = 0;
        this->ptr_LogicLayer = this->LogicLayer;
        this->ptr_ChangedLayer = this->ChangedLayer;
        this->ptr_TerrainTypeTileMap = this->Logic2Layer;
        this->ptr_TerrainHeightTileMap = this->HeightLayer;
        this->ptr_PathConnectionLayer = this->PathConnectionLayer;
        this->ptr_OccupancyLayer = this->OccupancyLayer;
        this->ptr_DamageLayer = this->DamageOrCropStageLayer;
        this->ptr_MiscDisplayLayer = this->MiscDisplayLayer;
        this->ptr_MovementDirectionTranslationMatrix = this;
        this->ptr_SpecialAreasArray = this->specialAreasArray;
        this->ptr_AIZoneLayer = this->AIZoneLayer;
        this->maxMoatCount = 16000;
        this->maxPitchDitchCount = 4000;
        return this;
    }

}
}
