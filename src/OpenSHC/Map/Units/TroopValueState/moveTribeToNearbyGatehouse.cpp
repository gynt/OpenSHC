#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051D450
        undefined4 TroopValueState::moveTribeToNearbyGatehouse(int tribeID)
        {
            int const leaderUnitID = DAT_TribesState::instance.tribes[tribeID].leaderUnitID;
            int gatehouseID = MACRO_CALL_MEMBER(
                Map::Navigation::PathFindingState_Func::findNearestEnemyGatehouseWithinDistance,
                DAT_PathFindingState::ptr)(DAT_TribesState::instance.tribes[tribeID].owner,
                DAT_UnitsState::instance.units[leaderUnitID].x, DAT_UnitsState::instance.units[leaderUnitID].y, 80);
            if (gatehouseID == 0) {
                gatehouseID = MACRO_CALL_MEMBER(
                    Map::Navigation::PathFindingState_Func::findNearestEnemyGatehouseWithinDistance,
                    DAT_PathFindingState::ptr)(DAT_TribesState::instance.tribes[tribeID].owner,
                    DAT_UnitsState::instance.units[leaderUnitID].x, DAT_UnitsState::instance.units[leaderUnitID].y,
                    200);
                if (gatehouseID == 0) {
                    return 0;
                }
            }
            MACRO_CALL_MEMBER(TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(
                tribeID, UIT_NO_INSTRUCTION_OR_MOVE, 0, 0, 0);
            MACRO_CALL_MEMBER(TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(tribeID,
                DAT_BuildingsState::instance.buildings[gatehouseID].accessTileX,
                DAT_BuildingsState::instance.buildings[gatehouseID].accessTileY, 0, 0, Instructions::UMSE_0);
            return 1;
        }

    }
}
}
