#include "../TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005232E0
        void TribesState::clearAnimalSpawnLocations()
        {
            for (int i = 0; i < 4; ++i) {
                DAT_GameState::instance.mapAndTime.deerSpawnLocationsXY[i].x = 0;
                DAT_GameState::instance.mapAndTime.deerSpawnLocationsXY[i].y = 0;
                DAT_GameState::instance.mapAndTime.lionLocationsXY[i].x = 0;
                DAT_GameState::instance.mapAndTime.lionLocationsXY[i].y = 0;
                DAT_GameState::instance.mapAndTime.rabbitSpawnXY[i][0] = 0;
                DAT_GameState::instance.mapAndTime.rabbitSpawnXY[i][1] = 0;
                DAT_GameState::instance.mapAndTime.camelSpawnXY[i].x = 0;
                DAT_GameState::instance.mapAndTime.camelSpawnXY[i].y = 0;
            }
            DAT_GameState::instance.mapAndTime.animalSpawnLocationRotation = 0;
        }

    }
}
}
