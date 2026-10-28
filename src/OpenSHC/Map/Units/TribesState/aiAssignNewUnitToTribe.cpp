#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // Role slot 0 generic, 1 engineer, 2 tunneler, 3 ladderman (freshUnitTribeIDs is short, movsx at 0x52381D);
        // monks use the int monkTribeID/monkTribeUID pair (0x5238B8..0x5238F9).
        // FUNCTION: STRONGHOLDCRUSADER 0x005237F0
        void TribesState::aiAssignNewUnitToTribe(int playerID, int unitType, int unitID)
        {
            int roleSlot = 0;
            if (unitType == UT_E_ENGINEER) {
                roleSlot = 1;
            } else if (unitType == UT_TUNNELER) {
                roleSlot = 2;
            } else if (unitType == UT_E_LADDER) {
                roleSlot = 3;
            } else if (unitType == UT_E_MONK) {
                int tribeID = DAT_GameState::instance.playerDataArray[playerID].monkTribeID;
                if (tribeID == 0 || this->tribes[tribeID].tribeState == 0
                    || this->tribes[tribeID].uid != DAT_GameState::instance.playerDataArray[playerID].monkTribeUID) {
                    tribeID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::createTribe, this)(playerID, 0);
                    DAT_GameState::instance.playerDataArray[playerID].monkTribeID = tribeID;
                    DAT_GameState::instance.playerDataArray[playerID].monkTribeUID = this->tribes[tribeID].uid;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToTribe, this)(unitID, tribeID);
                return;
            }
            short* freshTribeIDPtr = &DAT_GameState::instance.playerDataArray[playerID].freshUnitTribeIDs[roleSlot];
            int tribeID = *freshTribeIDPtr;
            if (tribeID == 0 || this->tribes[tribeID].tribeState == 0
                || this->tribes[tribeID].uid
                    != DAT_GameState::instance.playerDataArray[playerID].freshUnitTribeUIDs[roleSlot]) {
                tribeID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::createTribe, this)(playerID, 0);
                *freshTribeIDPtr = (short)tribeID;
                DAT_GameState::instance.playerDataArray[playerID].freshUnitTribeUIDs[roleSlot]
                    = this->tribes[tribeID].uid;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToTribe, this)(unitID, tribeID);
        }

    }
}
}
