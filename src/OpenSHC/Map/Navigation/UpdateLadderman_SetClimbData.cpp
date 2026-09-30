#include "../../Map.func.hpp"
#include "../Navigation.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00530720
    void Navigation::UpdateLadderman_SetClimbData(int unitID)
    {
        DAT_TileMapState::instance.LogicLayer[DAT_UnitsState::instance.units[unitID].tile]
            = DAT_TileMapState::instance.LogicLayer[DAT_UnitsState::instance.units[unitID].tile] | 8388608;
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::createClimbData, DAT_PathFindingState::ptr)(
            1, 0, unitID, 0, 0);
        DAT_UnitsState::instance.units[unitID].laddermanIsInPosition = 1;
    }

}
}
