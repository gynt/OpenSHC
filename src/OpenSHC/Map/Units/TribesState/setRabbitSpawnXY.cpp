#include "../TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // No break in the loop (as in machine code 0x5233B0..0x5233C5), then slot 0 is always overwritten.
        // FUNCTION: STRONGHOLDCRUSADER 0x005233A0
        void TribesState::setRabbitSpawnXY(undefined4 x, undefined4 y)
        {
            for (int i = 0; i < 4; ++i) {
                if (DAT_GameState::instance.mapAndTime.rabbitSpawnXY[i][0] == 0) {
                    DAT_GameState::instance.mapAndTime.rabbitSpawnXY[i][0] = x;
                    DAT_GameState::instance.mapAndTime.rabbitSpawnXY[i][1] = y;
                }
            }
            DAT_GameState::instance.mapAndTime.rabbitSpawnXY[0][0] = x;
            DAT_GameState::instance.mapAndTime.rabbitSpawnXY[0][1] = y;
        }

    }
}
}
