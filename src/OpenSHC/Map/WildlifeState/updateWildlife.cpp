#include "OpenSHC/Map/WildlifeState.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0052DF30
    void WildlifeState::updateWildlife()
    {
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
            return;
        }
        for (int y = 0; y < 40; y++) {
            for (int x = 0; x < 40; x++) {
                this->grid[x][y].dangerInfluence = 0;
                this->grid[x][y].farmlandInfluence = 0;
                this->grid[x][y].castleCoreScore = 0;
                this->grid[x][y].castleZoneSpread = 0;
                this->grid[x][y].heightSum = this->grid[x][y].heightSum / 100;
                if (this->grid[x][y].humanPlayerAreaTileCount != 0) {
                    if (this->grid[x][y].keeps != 0) {
                        this->grid[x][y].castleCoreScore = 1;
                    }
                    if (this->grid[x][y].castlebuildings != 0) {
                        this->grid[x][y].castleCoreScore += 1;
                    }
                }
            }
        }
        for (int y = 0; y < 40; y++) {
            for (int x = 0; x < 40; x++) {
                if (this->grid[x][y].humanCount != 0) {
                    MACRO_CALL_MEMBER(WildlifeState_Func::floodFillField13FromCell, this)(x, y, 2);
                } else if (this->grid[x][y].buildingTileCount != 0) {
                    MACRO_CALL_MEMBER(WildlifeState_Func::floodFillField13FromCell, this)(x, y, 2);
                } else if (this->grid[x][y].lionCount != 0) {
                    MACRO_CALL_MEMBER(WildlifeState_Func::floodFillField13FromCell, this)(x, y, 3);
                }
                if (this->grid[x][y].farmlandTileCount != 0) {
                    MACRO_CALL_MEMBER(WildlifeState_Func::floodFillField20FromCell, this)(x, y, 6);
                }
            }
        }
    }

}
}
