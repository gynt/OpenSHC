
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_RotateMapOrPullDownTerrain.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00501A20
    void TileMapState::stepHeightOffsetAnimationAndRefreshShowHi()
    {
        int importHeight = 0;
        this->refreshRelatedTwo = 0;
        if (this->heightOffsetAnimMode == 0) {
            return;
        }

        this->heightAnimFrame = this->heightAnimFrame + 1;
        this->refreshCertainTileMap_old = this->heightOffsetAnimMode;
        this->fullHeightViewActive = 0;
        for (int row = 0; row < 256; row++) {
            int target = ((uint)row >> 2) + 1;
            /* the pull-down eases towards the target in steps that shrink as it gets closer */
            int step;
            if (this->heightOffsetAnimMode == 3) {
                step = this->heightBasedScreenYOffset[row] - target;
            } else if (this->heightOffsetAnimMode == 4) {
                step = row - this->heightBasedScreenYOffset[row];
            } else {
                step = 0;
            }
            if (step > 60) {
                step = 30;
            } else if (step > 40) {
                step = 20;
            } else if (step > 30) {
                step = 14;
            } else if (step > 20) {
                step = 8;
            } else if (step > 10) {
                step = 4;
            } else if (step > 6) {
                step = 3;
            } else if (step > 2) {
                step = 2;
            } else if (step > 0) {
                step = 1;
            } else {
                step = 0;
            }

            if (this->heightOffsetAnimMode == 1) {
                this->heightBasedScreenYOffset[row] = target;
            } else if (this->heightOffsetAnimMode == 2) {
                this->heightBasedScreenYOffset[row] = row;
            } else if (this->heightOffsetAnimMode == 3) {
                this->heightBasedScreenYOffset[row] = this->heightBasedScreenYOffset[row] - step;
                if (this->heightBasedScreenYOffset[row] > target) {
                    importHeight = 1;
                }
            } else if (this->heightOffsetAnimMode == 4) {
                this->heightBasedScreenYOffset[row] = this->heightBasedScreenYOffset[row] + step;
                if (this->heightBasedScreenYOffset[row] != row) {
                    importHeight = 1;
                }
            }
        }

        this->refreshRelatedTwo = 1;
        if (importHeight == 0) {
            if (this->heightOffsetAnimMode == 4 || this->heightOffsetAnimMode == 2) {
                this->fullHeightViewActive = 1;
            } else {
                this->fullHeightViewActive = 0;
                this->refreshRelatedTwo = 2;
            }
            this->heightOffsetAnimMode = 0;
            this->forceUpdateLogicalAndMiscDisplayLayers = 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setChangedLayerToThreeAndMapping0x40x40, this)();
            this->heightAnimFrame = 0;
            DAT_RotateMapOrPullDownTerrain::instance = 1;
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::rebuildShowHiLayerFromHeights, this)();
    }

}
}
