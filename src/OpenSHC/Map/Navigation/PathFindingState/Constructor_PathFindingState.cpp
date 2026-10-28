#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A9760
        PathFindingState* PathFindingState::Constructor_PathFindingState()
        {
            this->unkInit70 = 0;
            this->separateAreaUpdateCount = 0;
            this->linkageRebuildCount = 0;
            this->skipLocalPathSearch = 0;
            this->DAT_Easy = 0;
            this->DAT_Hard = 0;
            this->areaRouteSearchCount = 0;
            this->nonLadderAreaRouteSearchCount = 0;
            this->searchNonmatchCount = 0;
            this->searchMatchCounter = 0;
            this->wallScalingSearchCount = 0;
            this->calculations = 0;
            this->DAT_Mini_spreads = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::clearPathFindingTileMaps, this)();
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::clearAllClimbData, this)();
            this->searchGeneration = 1;
            return this;
        }

    }
}
}
