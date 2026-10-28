#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00457770
    BOOLEnum GameStateStructures::canUnitsNavigateFromKeepToKeep(int playerID, int targetPlayerID)
    {
        if (this->playerDataArray[playerID].keep.id == 0) {
            return TRUE;
        }
        if (this->playerDataArray[targetPlayerID].keep.id == 0) {
            return TRUE;
        }
        int targetTile = this->playerDataArray[targetPlayerID].campground.tileEntry;
        int tile = this->playerDataArray[playerID].campground.tileEntry;
        if (DAT_TileMapState::instance.PathConnectionLayer[targetTile] == 0) {
            return FALSE;
        }
        if (DAT_TileMapState::instance.PathConnectionLayer[tile] == 0) {
            return FALSE;
        }
        if (DAT_TileMapState::instance.PathConnectionLayer[tile]
            == DAT_TileMapState::instance.PathConnectionLayer[targetTile]) {
            return TRUE;
        }
        return MACRO_CALL_MEMBER(
                   OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                   DAT_PathFindingState::ptr)(playerID,
                   (short)DAT_TileMapState::instance.PathConnectionLayer[targetTile],
                   (short)DAT_TileMapState::instance.PathConnectionLayer[tile], 2)
            != 0;
    }
}
}
