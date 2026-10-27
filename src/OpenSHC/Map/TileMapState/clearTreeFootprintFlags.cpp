
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_TREE;
    using OpenSHC::Map::LogicHelpers::L_TREE_VARIATION;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FB8E0
    void TileMapState::clearTreeFootprintFlags(int treeID)
    {
        // the original sign-extends both (0x4FB8F3/0x4FB8FA movsx)
        int treeX = (short)DAT_LandscapeState::instance.trees[treeID].xPosition;
        int treeY = (short)DAT_LandscapeState::instance.trees[treeID].yPosition;
        this->OrganismLayer[DAT_LandscapeState::instance.trees[treeID].tile] = 0;
        this->LogicLayer[DAT_LandscapeState::instance.trees[treeID].tile]
            = this->LogicLayer[DAT_LandscapeState::instance.trees[treeID].tile] & ~L_TREE;
        int index = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                index, DAT_LandscapeState::instance.trees[treeID].size);
            index++;
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + treeY].addXgetTile + treeX
                + this->buildingX;
            this->LogicLayer[tile] = this->LogicLayer[tile] & ~L_TREE_VARIATION;
        } while (index < this->constructionTileCount);
    }

}
}
