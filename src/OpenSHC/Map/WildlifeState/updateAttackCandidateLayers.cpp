#include "OpenSHC/Map/WildlifeState.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0052E020
    void WildlifeState::updateAttackCandidateLayers()
    {
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
            return;
        }
        // the castle zone grows by one cell per pass through contiguous castle-building cells
        for (int pass = 0; pass < 20; pass++) {
            for (int y = 0; y < 40; y++) {
                for (int x = 0; x < 40; x++) {
                    this->grid[x][y].zoneProximity = 0;
                    this->grid[x][y].siegeCampSuitable = 0;
                    if (this->grid[x][y].castlebuildings != 0
                        && MACRO_CALL_MEMBER(WildlifeState_Func::hasAdjacentCellWithField24Or25, this)(x, y)) {
                        this->grid[x][y].castleZoneSpread += 1;
                    }
                }
            }
        }
        for (int y = 0; y < 40; y++) {
            for (int x = 0; x < 40; x++) {
                if (this->grid[x][y].castleCoreScore != 0 || this->grid[x][y].castleZoneSpread != 0) {
                    MACRO_CALL_MEMBER(WildlifeState_Func::floodFillZoneProximityFromCell, this)(x, y, 6);
                }
            }
        }
        for (int y = 0; y < 40; y++) {
            for (int x = 0; x < 40; x++) {
                if (this->grid[x][y].zoneProximity == 0
                    && MACRO_CALL_MEMBER(WildlifeState_Func::isAttackStagingCandidateCell, this)(x, y)) {
                    this->grid[x][y].siegeCampSuitable += 1;
                }
            }
        }
    }

}
}
