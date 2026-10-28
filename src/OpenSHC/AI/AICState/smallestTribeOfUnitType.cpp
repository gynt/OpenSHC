#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CC990
    int AICState::smallestTribeOfUnitType(int playerID, AIVUnitType unitType)
    {
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == AITA_NULL) {
            return 0;
        }

        int aicIndex = aiType - 1;
        int maxGroups = this->aics[aicIndex].defWallPatrolGroups;
        int count = DAT_GameState::instance.playerDataArray[playerID].aivUnitLocationSlotLocationCount[unitType];
        int smallestTribeID = 0;
        int smallestIndex = 0;
        int smallestSize = 1000;
        if (count > maxGroups && (unitType == 8 || unitType == 10 || unitType == 17)) {
            count = maxGroups;
        }

        int offset = DAT_SkirmishDefinedData::instance.AITribeIDOffsetForAIVUnitType[unitType];
        if (count <= 0) {
            return 0;
        }
        for (int i = 0; i < count; i++) {
            int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[offset + i];
            if (tribeID == 0
                || DAT_TribesState::instance.tribes[tribeID].uid
                    != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[offset + i]) {
                smallestTribeID = MACRO_CALL_MEMBER(
                    Map::Units::TribesState_Func::createTribeForPlayer, DAT_TribesState::ptr)(playerID);
                smallestIndex = i;
                goto store;
            }
            if (DAT_TribesState::instance.tribes[tribeID].size < smallestSize) {
                smallestSize = DAT_TribesState::instance.tribes[tribeID].size;
                smallestTribeID = tribeID;
                smallestIndex = i;
            }
        }
        if (smallestTribeID == 0) {
            return 0;
        }

    store:
        DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[offset + smallestIndex] = (short)smallestTribeID;
        DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[offset + smallestIndex]
            = DAT_TribesState::instance.tribes[smallestTribeID].uid;
        return smallestTribeID;
    }
}
}
