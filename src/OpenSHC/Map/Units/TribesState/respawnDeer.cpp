#include "../TribesState.func.hpp"

#include "OpenSHC/Game/GameModeInt.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"

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

        // Candidates 0..3 = deerSpawnLocationsXY (movsx, 0x526215), candidate 4 = signpostsMapEdge[0][0]. A blocked
        // tile with an organism has the tree removed (0x52627C) and is used; one without an organism is skipped.
        // FUNCTION: STRONGHOLDCRUSADER 0x005261B0
        void TribesState::respawnDeer()
        {
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT
                || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CUSTOM_MAP
                    && DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE)) {
                return;
            }
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                || DAT_GameState::instance.mapAndTime.aliveDeerCount == 0
                || DAT_GameState::instance.mapAndTime.deerCount >= 6) {
                return;
            }
            for (int spawnSlot = 0; spawnSlot < 5; ++spawnSlot) {
                int x;
                int y;
                if (spawnSlot < 4) {
                    x = DAT_GameState::instance.mapAndTime.deerSpawnLocationsXY[spawnSlot].x;
                    y = DAT_GameState::instance.mapAndTime.deerSpawnLocationsXY[spawnSlot].y;
                } else {
                    x = DAT_GameState::instance.mapAndTime.signpostsMapEdge[0][0].x;
                    y = DAT_GameState::instance.mapAndTime.signpostsMapEdge[0][0].y;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(x, y)
                    == FALSE) {
                    continue;
                }
                int const tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
                if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x50501581) != 0) {
                    int const organismID = DAT_TileMapState::instance.OrganismLayer[tile];
                    if (organismID == 0) {
                        continue;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::removeTree, DAT_LandscapeState::ptr)(
                        organismID);
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::createAnimal, this)(
                    OpenSHC::Commands::M_MAPPER_DEER, x, y, DAT_TileMapState::instance.HeightLayer[tile]);
                return;
            }
        }

    }
}
}
