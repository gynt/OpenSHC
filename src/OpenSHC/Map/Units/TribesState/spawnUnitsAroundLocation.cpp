#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00523240
        dword TribesState::spawnUnitsAroundLocation(
            undefined4 tribeType, int aroundX, int aroundY, int playerID, UnitType unitType, int count)
        {
            if (aroundX <= 0 && aroundY <= 0) {
                return 0;
            }
            int const tribeID
                = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::createTribe, this)(playerID, 0);
            if (tribeID <= 0) {
                return 0;
            }
            this->tribes[tribeID].nearbyTileOffsetStartIndex = 0;
            this->tribes[tribeID].attackWave = 0;
            this->tribes[tribeID].tribeType = (OpenSHC::AI::Tribes::AITribeTypeShort)tribeType;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findPathWithBudget,
                DAT_PathFindingState::ptr)(aroundX, aroundY, -1, -1, 2000, 0);
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::spawnUnitAndAddToTribe,
                DAT_PathFindingState::ptr)(playerID, playerID, count, unitType, tribeID);
            this->tribes[tribeID].spreadOnSpawnPending = 1;
            return tribeID;
        }

    }
}
}
