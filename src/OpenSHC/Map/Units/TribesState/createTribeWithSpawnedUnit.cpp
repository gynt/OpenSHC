#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00523190
        dword TribesState::createTribeWithSpawnedUnit(
            short someIndex, undefined4 tribeType, int x, int y, int playerID, UnitType unitType, int count)
        {
            dword _tribeID;
            if ((x < 1) && (y < 1)) {
                return (dword)(0);
            }
            _tribeID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::createTribe, this)(playerID, 0);
            if ((int)_tribeID < 1) {
                return (dword)(0);
            }
            this->tribes[_tribeID].tribeType = (AITribeTypeShort)tribeType;
            this->tribes[_tribeID].someIndex = someIndex;
            this->tribes[_tribeID].attackWave = (short)DAT_TroopValueState::instance.attackInfo.inv_count;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findSuitableSpawnLocationUnk,
                DAT_PathFindingState::ptr)(x, y, -1, -1, 2000, 0);
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::spawnUnitAndAddToTribe,
                DAT_PathFindingState::ptr)(playerID, playerID, count, unitType, (undefined4)((int)(_tribeID)));
            this->tribes[_tribeID].field134_0x27a = 1;
            return (dword)(_tribeID);
        }

    }
}
}
