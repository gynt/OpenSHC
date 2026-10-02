#include "../../Map.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Commands::MappersEnum;
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
      whenever terrain is selected and you try to place it   decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00508A00
    void TileMapState::renderPreviewMapperWithBrush(uint x, uint y, MappersEnum param_3)
    {
        uint uVar1;
        uint y_00;
        MappersEnum MVar2;
        int baseTile;
        BOOLEnum BVar3;
        ushort _gfx;
        int iVar4;
        MVar2 = param_3;
        y_00 = y;
        if (399 < x) {}
        if (399 < y) {}
        if (*(char*)(y * 400 + 0x21aec98 + x) == '\0') {}
        uVar1 = DAT_TerrainDefinedData::instance.BrushSizeArray[this->editorActiveBrush];
        baseTile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
        if (param_3 == OpenSHC::Commands::M_MAPPER_POND1) {
            this->buildingPlacementFail = FALSE;
        }
        if (param_3 == OpenSHC::Commands::M_MAPPER_POND2_SMALL) {
            this->buildingPlacementFail = FALSE;
        }
        if (param_3 == OpenSHC::Commands::M_MAPPER_POND3_LARGE1) {
            this->buildingPlacementFail = FALSE;
        }
        if (param_3 == OpenSHC::Commands::M_MAPPER_POND4_LARGE2) {
            this->buildingPlacementFail = FALSE;
        }
        this->buildingPlacementFail = TRUE;
        if (param_3 == OpenSHC::Commands::M_MAPPER_SIGNPOST) {
            this->buildingPlacementFail = TRUE;
        }
        y = uVar1;
        if (0x154 < (int)param_3) {
        switchD_00508acb_caseD_5:
            _gfx = 0x38;
            goto LAB_00508b05;
        }
        if (param_3 == OpenSHC::Commands::M_MAPPER_DUNES) {
        switchD_00508acb_caseD_7:
            _gfx = 0x3c;
        } else {
            switch (param_3) {
            case OpenSHC::Commands::M_MAPPER_SEA:
            case OpenSHC::Commands::M_MAPPER_SHALLOWS:
            case OpenSHC::Commands::M_MAPPER_RIVER:
            case OpenSHC::Commands::M_MAPPER_MARSH:
            case OpenSHC::Commands::M_MAPPER_DUGMOAT:
            case OpenSHC::Commands::M_MAPPER_MOAT:
                _gfx = 0x39;
                break;
                default:
                    goto switchD_00508acb_caseD_5;
            case OpenSHC::Commands::M_MAPPER_SCRUB:
            case OpenSHC::Commands::M_MAPPER_DIRT:
                goto switchD_00508acb_caseD_7;
            case OpenSHC::Commands::M_MAPPER_BEACH:
            case OpenSHC::Commands::M_MAPPER_FORD:
                _gfx = 0x3a;
                break;
            case OpenSHC::Commands::M_MAPPER_ROCKY:
            case OpenSHC::Commands::M_MAPPER_STONES:
            case OpenSHC::Commands::M_MAPPER_BOULDERS:
            case OpenSHC::Commands::M_MAPPER_PEBBLES:
            case OpenSHC::Commands::M_MAPPER_IRON:
                _gfx = 0x3b;
                break;
            case OpenSHC::Commands::M_MAPPER_CHESTNUT:
            case OpenSHC::Commands::M_MAPPER_OAK:
            case OpenSHC::Commands::M_MAPPER_PINE:
            case OpenSHC::Commands::M_MAPPER_BIRCH:
            case OpenSHC::Commands::M_MAPPER_SHRUB1A:
            case OpenSHC::Commands::M_MAPPER_SHRUB1B:
            case OpenSHC::Commands::M_MAPPER_SHRUB1C:
            case OpenSHC::Commands::M_MAPPER_SHRUB1D:
            case OpenSHC::Commands::M_MAPPER_SHRUB1E:
            case OpenSHC::Commands::M_MAPPER_SHRUB2A:
            case OpenSHC::Commands::M_MAPPER_SHRUB2B:
            case OpenSHC::Commands::M_MAPPER_SHRUB2C:
            case OpenSHC::Commands::M_MAPPER_SHRUB2D:
            case OpenSHC::Commands::M_MAPPER_SHRUB2E:
            case OpenSHC::Commands::M_MAPPER_SHRUB3A:
            case OpenSHC::Commands::M_MAPPER_SHRUB3B:
            case OpenSHC::Commands::M_MAPPER_SHRUB3C:
            case OpenSHC::Commands::M_MAPPER_SHRUB3D:
            case OpenSHC::Commands::M_MAPPER_DEER:
            case OpenSHC::Commands::M_MAPPER_LION:
            case OpenSHC::Commands::M_MAPPER_RABBIT:
            case OpenSHC::Commands::M_MAPPER_CAMEL:
            case OpenSHC::Commands::M_MAPPER_CROW_SEAGULL:
            case OpenSHC::Commands::M_MAPPER_SEAGULL:
                y = 1;
            case OpenSHC::Commands::M_MAPPER_RAISE:
            case OpenSHC::Commands::M_MAPPER_LOWER:
            case OpenSHC::Commands::M_MAPPER_EQUALISE:
            case OpenSHC::Commands::M_MAPPER_MOUNTAIN:
            case OpenSHC::Commands::M_MAPPER_HILL:
            case OpenSHC::Commands::M_MAPPER_DELETE:
                _gfx = 0x3e;
                break;
            case OpenSHC::Commands::M_MAPPER_UNDUGMOAT:
            case OpenSHC::Commands::M_MAPPER_OIL:
                _gfx = 0x3d;
            }
        }
    LAB_00508b05:
        switch (param_3) {
        case OpenSHC::Commands::M_MAPPER_UNDUGMOAT:
        case OpenSHC::Commands::M_MAPPER_DUGMOAT:
        case OpenSHC::Commands::M_MAPPER_MOAT:
        case OpenSHC::Commands::M_MAPPER_ANTIMOAT:
            if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR)
                && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT)) {
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                    iVar4 = 0x1e;
                    param_3 = (OpenSHC::Commands::MappersEnum)(OpenSHC::Commands::M_MAPPER_TOWER | OpenSHC::Commands::M_MAPPER_RAISE);
                } else {
                    iVar4 = 0xf;
                    param_3 = OpenSHC::Commands::M_MAPPER_SCRUB;
                }
                BVar3 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyTooCloseUnk,
                    DAT_PathFindingState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, x, y_00, iVar4);
                if (BVar3 != FALSE) {
                    _gfx = 0x3e;
                }
                BVar3 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isSignPostWithinDistance,
                    DAT_PathFindingState::ptr)(x, y_00, DAT_GameState::instance.mapAndTime.unk_signpostDistance + 5);
                if (BVar3 != FALSE) {
                    _gfx = 0x3e;
                }
                if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                    iVar4 = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getCastleBuildRangeForMapSize, this)();
                    iVar4
                        = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isOpponentBuildingInRange,
                            DAT_PathFindingState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                            (int)((int)(x)), (int)((int)(y_00)), (int)((int)(param_3)), -1, -1, iVar4 + 5);
                    if (iVar4 != 0) {
                        _gfx = 0x3e;
                    }
                }
            }
        }
        x = DAT_ViewportRenderState::instance.translationMatrix[y_00].addXgetTile + x;
        if ((((MVar2 == OpenSHC::Commands::M_MAPPER_DUGMOAT) || (MVar2 == OpenSHC::Commands::M_MAPPER_UNDUGMOAT))
                || (MVar2 == OpenSHC::Commands::M_MAPPER_MOAT))
            || (MVar2 == OpenSHC::Commands::M_MAPPER_ANTIMOAT)) {
            iVar4 = 0;
            param_3 = (OpenSHC::Commands::MappersEnum)(y_00);
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(
                    0, iVar4, (int*)&x, (int*)&param_3, baseTile, y_00);
                iVar4 = iVar4 + 1;
                this->ConstructionGFXLayer[x] = _gfx;
            } while (iVar4 < 9);
        } else {
            iVar4 = 0;
            param_3 = (OpenSHC::Commands::MappersEnum)(y_00);
            if (0 < (int)y) {
                do {
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(
                        1, iVar4, (int*)&x, (int*)&param_3, baseTile, y_00);
                    iVar4 = iVar4 + 1;
                    this->ConstructionGFXLayer[x] = _gfx;
                } while (iVar4 < (int)y);
            }
        }
    }

}
}
