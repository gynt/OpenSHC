#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051AFF0
        int TroopValueState::claimArcherAttackPoint(int tribeID)
        {
            // archer point record: {x, y, tile, counterStamp, tribeID, tribeUID, reservationTimer, 0}
            int const unitID = DAT_TribesState::instance.tribes[tribeID].leaderUnitID;
            if (MACRO_CALL_MEMBER(TribesState_Func::tribeHasActiveLaddermanUnit, DAT_TribesState::ptr)(tribeID) == 0) {
                int const newSlot = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::findArcherRelatedAttackInfoIndex,
                    DAT_PathFindingState::ptr)(
                    200, DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y, tribeID);
                if (newSlot != 0) {
                    short const oldSlot = DAT_TribesState::instance.tribes[tribeID].archerPointIndex;
                    DAT_TribesState::instance.tribes[tribeID].previousArcherPointIndex = oldSlot;
                    DAT_TroopValueState::instance.attackInfo.archerPointRecords[oldSlot][4] = 0;
                    DAT_TroopValueState::instance.attackInfo.archerPointRecords[oldSlot][5] = 0;
                    DAT_TroopValueState::instance.attackInfo.archerPointRecords[newSlot][5]
                        = DAT_TribesState::instance.tribes[tribeID].uid;
                    DAT_TribesState::instance.tribes[tribeID].archerPointIndex = newSlot;
                    DAT_TroopValueState::instance.attackInfo.archerPointRecords[newSlot][4] = tribeID;
                    DAT_TroopValueState::instance.attackInfo.archerPointRecords[newSlot][6] = 3;
                    MACRO_CALL_MEMBER(TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(tribeID,
                        DAT_TroopValueState::instance.attackInfo.archerPointRecords[newSlot][0],
                        DAT_TroopValueState::instance.attackInfo.archerPointRecords[newSlot][1], 0, 0,
                        Instructions::UMSE_0);
                    return newSlot;
                }
            }
            return 0;
        }

    }
}
}
