#include "OpenSHC/Map/LandscapeState.func.hpp"

#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F2020
    void LandscapeState::setTreeStageRelatedValues(int treeID, int stage)
    {
        int const treeType = this->trees[treeID].treeType;
        undefined2 const woodChunks = (undefined2)DAT_OrganismDefinedData::instance.TreeRelated1[treeType][stage];
        this->trees[treeID].stageRelated4 = woodChunks;
        this->trees[treeID].woodChunksRemaining = woodChunks;
        undefined2 const hitPoints = (undefined2)DAT_OrganismDefinedData::instance.TreeRelated2[treeType][stage];
        this->trees[treeID].maxHitPoints = hitPoints;
        this->trees[treeID].hitPoints = hitPoints;
    }

}
}
