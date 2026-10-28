#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051B190
        int TroopValueState::assignTribeToSupportPoint(uint x, uint y, int tribeID)
        {
            int const newSlot = MACRO_CALL_MEMBER(
                OpenSHC::Map::Navigation::PathFindingState_Func::findSupportPointIndex, DAT_PathFindingState::ptr)(
                200, x, y, tribeID);
            if (newSlot != 0) {
                DAT_TribesState::instance.tribes[tribeID].oldSupportPointIndex
                    = DAT_TribesState::instance.tribes[tribeID].supportPointIndex;
                DAT_TroopValueState::instance.attackInfo
                    .supportPointsArray[DAT_TribesState::instance.tribes[tribeID].oldSupportPointIndex]
                    .tribeID
                    = 0;
                DAT_TroopValueState::instance.attackInfo
                    .supportPointsArray[DAT_TribesState::instance.tribes[tribeID].oldSupportPointIndex]
                    .tribeUID
                    = 0;
                DAT_TribesState::instance.tribes[tribeID].supportPointIndex = newSlot;
                DAT_TroopValueState::instance.attackInfo.supportPointsArray[newSlot].tribeUID
                    = DAT_TribesState::instance.tribes[tribeID].uid;
                DAT_TroopValueState::instance.attackInfo.supportPointsArray[newSlot].tribeID = tribeID;
                DAT_TroopValueState::instance.attackInfo.supportPointsArray[newSlot].reservationTimer = 3;
                MACRO_CALL_MEMBER(TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(tribeID,
                    DAT_TroopValueState::instance.attackInfo.supportPointsArray[newSlot].x,
                    DAT_TroopValueState::instance.attackInfo.supportPointsArray[newSlot].y, 0, 0,
                    Instructions::UMSE_0);
                return newSlot;
            }
            return 0;
        }

    }
}
}
