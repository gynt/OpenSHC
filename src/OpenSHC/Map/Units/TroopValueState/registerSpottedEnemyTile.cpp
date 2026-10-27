#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051BE60
        void TroopValueState::registerSpottedEnemyTile(int tile)
        {
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                return;
            }
            if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].keep.id
                > 0) {
                return;
            }
            int const unitID = (short)DAT_TileMapState::instance.UnitLayer[tile];
            if (unitID <= 0) {
                return;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[DAT_UnitsState::instance.units[unitID].owner]
                == -1) {
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime == 0) {
                return;
            }
            int const entityID = DAT_TileMapState::instance.EntityLayer[tile];
            if (entityID != 0
                && DAT_EntityState::instance.entityArray[entityID].entityType == OpenSHC::Map::Entities::ET_FIRE) {
                return;
            }
            int freeSlot = -1;
            for (int i = 0; i < 100; ++i) {
                if (DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[i].tile == tile) {
                    return;
                }
                if (DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[i].tile == 0 && freeSlot == -1) {
                    freeSlot = i;
                }
            }
            if (freeSlot > -1) {
                DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[freeSlot].tile = tile;
                DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[freeSlot].value = 100;
            }
        }

    }
}
}
