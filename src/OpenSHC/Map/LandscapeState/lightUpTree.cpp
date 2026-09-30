#include "../../Map.func.hpp"
#include "../LandscapeState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F2280
    BOOLEnum LandscapeState::lightUpTree(int tile, int playerID)
    {
        int _treeID;
        int iVar1;
        int _spread;
        _treeID = (int)DAT_TileMapState::instance.OrganismLayer[tile];
        if ((1999 < _treeID) || (this->trees[_treeID].field92_0x98 != 0)) {
            return FALSE;
        }
        iVar1 = (int)(short)this->trees[_treeID].treeType;
        switch (iVar1) {
        case 1:
        case 2:
        case 3:
        case 4:
            if (0x13 < DAT_GameState::instance.mapAndTime.field3176_0x27c8) {
                return FALSE;
            }
            if (this->trees[_treeID].stage < 3) {
                return FALSE;
            }
            this->trees[_treeID].stage = 6;
            this->trees[_treeID].stageTracker
                = *(int*)((int)DAT_OrganismDefinedData::instance.TreeStageLevels + iVar1 * 0x20);
            this->trees[_treeID].field92_0x98 = 0x14;
            _spread = 2;
            break;
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 0xb:
        case 0xc:
        case 0xd:
        case 0xe:
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
            this->trees[_treeID].state = 3;
            return TRUE;
        case 0xf:
            this->trees[_treeID].stageTracker = 0;
            this->trees[_treeID].stage = 6;
            this->trees[_treeID].field92_0x98 = 0x14;
            _spread = 1;
            break;
        default:
            return FALSE;
        }
        this->trees[_treeID].igniterPlayer = (short)playerID;
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::igniteFireAtTilesDistanceAway,
            DAT_PathFindingState::ptr)(tile, _spread, playerID);
        return TRUE;
    }

}
}
