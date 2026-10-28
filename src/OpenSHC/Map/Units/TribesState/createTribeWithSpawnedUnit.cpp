#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00523190
        dword TribesState::createTribeWithSpawnedUnit(
            short someIndex, undefined4 tribeType, int x, int y, int playerID, UnitType unitType, int count)
        {
            if (x <= 0 && y <= 0) {
                return 0;
            }
            int const tribeID
                = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::createTribe, this)(playerID, 0);
            if (tribeID <= 0) {
                return 0;
            }
            this->tribes[tribeID].tribeType = (OpenSHC::AI::Tribes::AITribeTypeShort)tribeType;
            this->tribes[tribeID].nearbyTileOffsetStartIndex = someIndex;
            this->tribes[tribeID].attackWave = (short)DAT_TroopValueState::instance.attackInfo.currentAttackWaveSlot;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findPathWithBudget,
                DAT_PathFindingState::ptr)(x, y, -1, -1, 2000, 0);
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::spawnUnitAndAddToTribe,
                DAT_PathFindingState::ptr)(playerID, playerID, count, unitType, tribeID);
            this->tribes[tribeID].spreadOnSpawnPending = 1;
            return tribeID;
        }

    }
}
}
