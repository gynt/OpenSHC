#include "../../Map.func.hpp"
#include "../LandscapeState.func.hpp"

#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"
#include "OpenSHC/Map/Trees/TreeTypeShort.hpp"

namespace OpenSHC {
namespace Map {
    using OpenSHC::Map::Trees::TreeTypeShort;


    // FUNCTION: STRONGHOLDCRUSADER 0x004F2020
    void LandscapeState::setTreeStageRelatedValues(int treeID, int stage)
    {
        TreeTypeShort TVar1;
        undefined2 uVar2;
        TVar1 = this->trees[treeID].treeType;
        uVar2 = (undefined2)DAT_OrganismDefinedData::instance.TreeRelated1[(short)TVar1][stage];
        this->trees[treeID].stageRelated4 = uVar2;
        this->trees[treeID].treeAdultHoodStageRelatedVisual3 = uVar2;
        uVar2 = (undefined2)DAT_OrganismDefinedData::instance.TreeRelated2[(short)TVar1][stage];
        this->trees[treeID].stageRelated2 = uVar2;
        this->trees[treeID].stageRelated1 = uVar2;
    }

}
}
