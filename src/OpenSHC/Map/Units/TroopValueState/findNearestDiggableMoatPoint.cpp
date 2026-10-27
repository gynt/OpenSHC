#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A8A0
        int TroopValueState::findNearestDiggableMoatPoint(int unitID)
        {
            // findBestMoatTileForWork returns a moat tile (declared as BOOLEnum), -1 if none
            int const moatTile = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::findBestMoatTileForWork,
                DAT_TileMapState::ptr)(DAT_UnitsState::instance.units[unitID].owner, unitID, 2);
            if (moatTile <= -1) {
                return 0;
            }
            int const result = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::computeMoatDigTarget,
                DAT_TileMapState::ptr)(
                moatTile, 2, DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y);
            if (result <= 0) {
                return 0;
            }
            this->x = DAT_TileMapState::instance.ALG_MoatXResult;
            this->y = DAT_TileMapState::instance.ALG_MoatYResult;
            this->tile = DAT_TileMapState::instance.someMoatTile;
            return result;
        }

    }
}
}
