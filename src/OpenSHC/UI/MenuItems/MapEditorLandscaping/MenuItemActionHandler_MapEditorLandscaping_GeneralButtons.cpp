#include "../MapEditorLandscaping.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_StopHandlingMenuItems.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Commands::MappersEnum;
        using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
        using OpenSHC::UI::Enums::MenuViewType;
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
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // Rewritten from the original machine code (regress_fix2): every case leaves with ret / tail jmp; the
        // Ghidra-derived version jumped from the M_MAPPER_AREA case back into the M_MAPPER_AREA_BACK block and then
        // re-entered the switch (endless loop, game hang), ran the big-rock brush fix-up for every case and did not
        // set editorPlacementPlayerID = 1 for the default case.
        // FUNCTION: STRONGHOLDCRUSADER 0x004314E0
        void MapEditorLandscaping::MenuItemActionHandler_MapEditorLandscaping_GeneralButtons(MappersEnum param_1, ...)
        {
            int brush;
            if (0x14b < (int)param_1) { // 0x4314e9 jg 0x43183c
                goto LAB_0043183c;
            }
            if (param_1 == OpenSHC::Commands::M_MAPPER_AREA_BACK) {
                // 0x4317c3
                brush = (int)DAT_TileMapState::instance.editorActiveBrush - 1;
                DAT_TileMapState::instance.editorActiveBrush = brush;
                if (brush < 1) { // 0x4317d3 jge: signed
                    brush = 7;
                    DAT_TileMapState::instance.editorActiveBrush = 7;
                }
                if ((DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_BIGROCK1)
                    || (DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_BIGROCK2)
                    || (DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_BIGROCK3)
                    || (DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_BIGROCK4)
                    || (DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_BIGROCK5)) {
                    if (brush == 2) {
                        brush = 1;
                        DAT_TileMapState::instance.editorActiveBrush = 1;
                    } else if (brush == 4) {
                        brush = 3;
                        DAT_TileMapState::instance.editorActiveBrush = 3;
                    } else if (brush == 6) {
                        brush = 5;
                        DAT_TileMapState::instance.editorActiveBrush = 5;
                    }
                }
                // 0x4315c1
                DAT_TileMapState::instance.editorBrushRadius = brush >> 1;
                DAT_StopHandlingMenuItems::instance = 0;
                return; // 0x4315d2 ret
            }
            switch (param_1) {
            case OpenSHC::Commands::M_MAPPER_AREA:
                // 0x431553
                brush = (int)DAT_TileMapState::instance.editorActiveBrush + 1;
                DAT_TileMapState::instance.editorActiveBrush = brush;
                if (7 < brush) { // 0x431563 jle: signed
                    brush = 1;
                    DAT_TileMapState::instance.editorActiveBrush = 1;
                }
                if ((DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_BIGROCK1)
                    || (DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_BIGROCK2)
                    || (DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_BIGROCK3)
                    || (DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_BIGROCK4)
                    || (DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_BIGROCK5)) {
                    if (brush == 2) {
                        brush = 3;
                        DAT_TileMapState::instance.editorActiveBrush = 3;
                    } else if (brush == 4) {
                        brush = 5;
                        DAT_TileMapState::instance.editorActiveBrush = 5;
                    } else if (brush == 6) {
                        brush = 7;
                        DAT_TileMapState::instance.editorActiveBrush = 7;
                    }
                }
                // 0x4315c1
                DAT_TileMapState::instance.editorBrushRadius = brush >> 1;
                DAT_StopHandlingMenuItems::instance = 0;
                return; // 0x4315d2 ret
            case OpenSHC::Commands::M_MAPPER_MIN:
                DAT_TileMapState::instance.mapperMax = FALSE;
                DAT_TileMapState::instance.currentMapperCommand = param_1;
                return;
            case OpenSHC::Commands::M_MAPPER_MAX:
                DAT_TileMapState::instance.mapperMax = TRUE;
                DAT_TileMapState::instance.currentMapperCommand = param_1;
                return;
            case OpenSHC::Commands::M_MAPPER_EXIT:
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_UNUSED_OLD_TITLE_MENU, 0);
                return;
            case OpenSHC::Commands::M_MAPPER_TOMAIN:
                DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType = OpenSHC::UI::Enums::BASMTT_HUNTERSHUT;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
                return;
            case OpenSHC::Commands::M_MAPPER_AFFECT_TYPE:
                // 0x4315d3: ++mapperAffectType, wraps to 0 above 1 (jle: signed)
                DAT_TileMapState::instance.mapperAffectType = DAT_TileMapState::instance.mapperAffectType + 1;
                if (1 < (int)DAT_TileMapState::instance.mapperAffectType) {
                    DAT_TileMapState::instance.mapperAffectType = 0;
                }
                return;
            case OpenSHC::Commands::M_MAPPER_TO_MAP_EDIT:
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_MAP_EDITOR_PROPERTIES, 0);
                return;
            case OpenSHC::Commands::M_MAPPER_TEST:
                return; // 0x43184b ret
            case OpenSHC::Commands::M_MAPPER_REBUILD:
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::forceFullTileMapRedraw, DAT_TileMapState::ptr)();
                return;
            case OpenSHC::Commands::M_MAPPER_SNAP_TO:
                // 0x431701: 0 -> 1, 1 -> 2, otherwise -> 0
                if (DAT_TileMapState::instance.mapperSnapMode == 0) {
                    DAT_TileMapState::instance.mapperSnapMode = 1;
                    return;
                }
                DAT_TileMapState::instance.mapperSnapMode
                    = (-(uint)(DAT_TileMapState::instance.mapperSnapMode != 1) & 0xfffffffe) + 2;
                return;
            case OpenSHC::Commands::M_MAPPER_BIGROCK1:
                DAT_TileMapState::instance.editorBigRockType = 1;
                DAT_TileMapState::instance.rockOrientation = 0;
                break;
            case OpenSHC::Commands::M_MAPPER_BIGROCK2:
                DAT_TileMapState::instance.editorBigRockType = 2;
                DAT_TileMapState::instance.rockOrientation = 2;
                break;
            case OpenSHC::Commands::M_MAPPER_BIGROCK3:
                DAT_TileMapState::instance.editorBigRockType = 3;
                DAT_TileMapState::instance.rockOrientation = 4;
                break;
            case OpenSHC::Commands::M_MAPPER_BIGROCK4:
                DAT_TileMapState::instance.editorBigRockType = 4;
                DAT_TileMapState::instance.rockOrientation = 6;
                break;
            case OpenSHC::Commands::M_MAPPER_BIGROCK5:
                DAT_TileMapState::instance.editorBigRockType = 5;
                DAT_TileMapState::instance.rockOrientation = 0;
                break;
            case OpenSHC::Commands::M_MAPPER_MAP_SIZE:
                if (DAT_TileMapState::instance.mapSize == 0) {
                    DAT_TileMapState::instance.mapSize = 400;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMapSize, DAT_TileMapState::ptr)(
                    DAT_TileMapState::instance.mapSize);
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetHeightAndMapBorders, DAT_TileMapState::ptr)(
                    DAT_TileMapState::instance.mapSize);
                DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::forceFullTileMapRedraw, DAT_TileMapState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::setTileColorsDependingOnMapSize,
                    DAT_MinimapViewState::ptr)(0, 100);
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::redrawMinimapRowsForMapSize,
                    DAT_MinimapViewState::ptr)(0, 100);
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize,
                    DAT_ViewportRenderState::ptr)();
                return;
            case OpenSHC::Commands::M_MAPPER_MP_KEEP1:
            case OpenSHC::Commands::M_MAPPER_MP_KEEP2:
            case OpenSHC::Commands::M_MAPPER_MP_KEEP3:
            case OpenSHC::Commands::M_MAPPER_MP_KEEP4:
            case OpenSHC::Commands::M_MAPPER_MP_KEEP5:
            case OpenSHC::Commands::M_MAPPER_MP_KEEP6:
            case OpenSHC::Commands::M_MAPPER_MP_KEEP7:
            case OpenSHC::Commands::M_MAPPER_MP_KEEP8:
                // 0x431791
                DAT_GameSynchronyState::instance.editorPlacementPlayerID
                    = param_1 - OpenSHC::Commands::M_MAPPER_SUB_MODE_FEATURE_MP;
                if (DAT_GameCore::instance.availableKeepFlags[2] != 0) {
                    DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_KEEP3;
                    return; // 0x4317ae ret
                }
                DAT_TileMapState::instance.currentMapperCommand
                    = (OpenSHC::Commands::MappersEnum)((DAT_GameCore::instance.availableKeepFlags[1] != 0)
                        + OpenSHC::Commands::M_MAPPER_KEEP1);
                return;
            default:
                goto LAB_0043183c;
            }
            // big rocks (0x431628 / 0x43162d): select the rock and step an even brush size up to the next odd one
            DAT_TileMapState::instance.currentMapperCommand = param_1;
            if (DAT_TileMapState::instance.editorActiveBrush == 2) {
                DAT_TileMapState::instance.editorActiveBrush = 3;
            } else if (DAT_TileMapState::instance.editorActiveBrush == 4) {
                DAT_TileMapState::instance.editorActiveBrush = 5;
            } else if (DAT_TileMapState::instance.editorActiveBrush == 6) {
                DAT_TileMapState::instance.editorActiveBrush = 7;
            }
            return;
        LAB_0043183c:
            DAT_GameSynchronyState::instance.editorPlacementPlayerID = 1;
            DAT_TileMapState::instance.currentMapperCommand = param_1;
        }

    }
}
}
