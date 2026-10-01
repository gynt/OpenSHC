#include "../../../Map.func.hpp"

#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Commands::MappersEnum;
        using OpenSHC::Game::GameMode;
        using OpenSHC::Game::GameMode2;
        using OpenSHC::Map::MapType2;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x005261B0
        void TribesState::respawnDeer()
        {
            BOOLEnum BVar1;
            uint _x;
            int _counter;
            int _tile;
            uint _y;
            if ((((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR)
                     && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT))
                    && ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_BUILDERUnk
                        || (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 != OpenSHC::Map::MT_SIEGE))))
                && (((DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY
                         && (DAT_GameState::instance.mapAndTime.aliveDeerCount != 0))
                    && (DAT_GameState::instance.mapAndTime.deerCount < 6)))) {
                _counter = 0;
                while (true) {
                    _x = DAT_GameState::instance.mapAndTime.signpostsMapEdge[0][0].x;
                    _y = DAT_GameState::instance.mapAndTime.signpostsMapEdge[0][0].y;
                    if (_counter < 4) {
                        _x = (int)DAT_GameState::instance.mapAndTime.deerSpawnLocationsXY[_counter].x;
                        _y = (int)DAT_GameState::instance.mapAndTime.deerSpawnLocationsXY[_counter].y;
                    }
                    BVar1 = MACRO_CALL_MEMBER(
                        OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid, DAT_ViewportRenderState::ptr)(_x, _y);
                    if (BVar1 != FALSE)
                        break;
                LAB_00526268:
                    _counter = _counter + 1;
                    if (4 < _counter) {}
                }
                _tile = DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile + _x;
                if ((DAT_TileMapState::instance.LogicLayer[_tile] & 0x50501581U) != 0) {
                    if (DAT_TileMapState::instance.OrganismLayer[_tile] == 0)
                        goto LAB_00526268;
                    MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::removeTree, DAT_LandscapeState::ptr)(
                        (int)DAT_TileMapState::instance.OrganismLayer[_tile]);
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::createAnimal, this)(
                    OpenSHC::Commands::M_MAPPER_DEER, _x, _y,
                    (int)((int)((uint)DAT_TileMapState::instance.HeightLayer[_tile])));
            }
        }

    }
}
}
