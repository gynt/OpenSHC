#include "../../Map.func.hpp"

#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Trees/TreeType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Trees::TreeType;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F3560
    void LandscapeState::placeAppleTree(int buildingID, undefined4 treeX, undefined4 treeY)
    {
        int iVar1;
        uint uVar2;
        int _treeID;
        _treeID = MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::createTree, this)(
            treeX, (undefined4)((int)(treeY)), OpenSHC::Map::Trees::TT_APPLEUnk, 1, 0, 0, 0);
        if (_treeID != 0) {
            this->trees[_treeID].appleFarmID = (short)buildingID;
            iVar1 = DAT_BuildingsState::instance.buildings[buildingID].uid;
            this->trees[_treeID].stageTracker = this->trees[_treeID].rng1 & 0x1f;
            uVar2 = this->trees[_treeID].tile;
            DAT_TileMapState::instance.LogicLayer[uVar2] = DAT_TileMapState::instance.LogicLayer[uVar2] | 0x1000;
            DAT_TileMapState::instance.OrganismLayer[uVar2] = (short)_treeID;
            this->trees[_treeID].appleFarmUID = iVar1;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::applyTreeBrushToLogicalLayer, DAT_TileMapState::ptr)(
                _treeID, 0);
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                DAT_PathFindingState::ptr)(
                (int)(short)this->trees[_treeID].yPosition, (int)((int)(this->trees[_treeID].tile)));
            DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
        }
    }

}
}
