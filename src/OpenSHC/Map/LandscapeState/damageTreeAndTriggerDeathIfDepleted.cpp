#include "../../Map.func.hpp"
#include "../LandscapeState.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F3010
    undefined4 LandscapeState::damageTreeAndTriggerDeathIfDepleted(int treeID, undefined4 param_2, int param_3)
    {
        undefined2* puVar1;
        if (((this->trees[treeID].uid == param_3) && (this->trees[treeID].zeroUpTo2 == 0))
            && (puVar1 = &this->trees[treeID].stageRelated1, *puVar1 = *puVar1 + (short)param_2,
                (short)this->trees[treeID].stageRelated1 < 1)) {
            this->trees[treeID].stageRelated1 = 0;
            this->trees[treeID].zeroUpTo2 = 1;
            this->trees[treeID].animationFrameIndex = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::applyTreeBrushToLogicalLayer, DAT_TileMapState::ptr)(
                treeID, 1);
            return (undefined4)(1);
        }
        return (undefined4)(0);
    }

}
}
