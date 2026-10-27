#include "../TribesState.func.hpp"

#include "OpenSHC/Game/GameModeInt.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // Slots 4..11 are enabled by [i*4 + 0x117F094] = mapAndTime.signpostIDs[i - 4] and read x/y from
        // [0x117E564 + i*0x320] = signpostsMapEdge[i - 4][0] (pointer edx at 0x5262C3, step 0x320 at 0x526334).
        // Slot 11 reads row 7 of the [7][50] array (first entry, lands in padding_0x4038), as in machine code.
        // FUNCTION: STRONGHOLDCRUSADER 0x005262A0
        void TribesState::spawnWildlifeOrMercAtAvailableSlot()
        {
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                || DAT_GameState::instance.mapAndTime.rabbitCount >= 0xa0) {
                return;
            }
            for (int i = 0; i < 12; ++i) {
                uint x;
                uint y;
                if (i < 4) {
                    x = DAT_GameState::instance.mapAndTime.rabbitSpawnXY[i][0];
                    y = DAT_GameState::instance.mapAndTime.rabbitSpawnXY[i][1];
                } else {
                    if (DAT_GameState::instance.mapAndTime.signpostIDs[i - 4] == 0) {
                        continue;
                    }
                    x = DAT_GameState::instance.mapAndTime.signpostsMapEdge[i - 4][0].x;
                    y = DAT_GameState::instance.mapAndTime.signpostsMapEdge[i - 4][0].y;
                }
                if (x <= 399 && y <= 399
                    && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] != 0) {
                    int const tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
                    if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x50501581) == 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::createAnimal, this)(
                            OpenSHC::Commands::M_MAPPER_RABBIT, x, y, DAT_TileMapState::instance.HeightLayer[tile]);
                        this->lastRabbitSpawnX = x;
                        this->lastRabbitSpawnY = y;
                        return;
                    }
                }
            }
        }

    }
}
}
