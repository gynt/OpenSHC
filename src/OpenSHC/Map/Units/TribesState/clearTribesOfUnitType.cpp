#include "../TribesState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // No alive check. The touched-tribe array is marked for every selected unit of the player, also those of
        // another type (0x5258F8), and never read. maxUnitCount is compared signed (jl at 0x525913).
        // FUNCTION: STRONGHOLDCRUSADER 0x00525870
        void TribesState::clearTribesOfUnitType(int playerID, int unitType)
        {
            bool touchedTribes[1250];
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(touchedTribes), 0, touchedTribes);
            for (int unitID = 1; unitID < (int)DAT_UnitsState::instance.maxUnitCount; ++unitID) {
                if (DAT_UnitsState::instance.units[unitID].owner == playerID
                    && DAT_UnitsState::instance.units[unitID].ifSelectedThenPlayerID != 0) {
                    if (DAT_UnitsState::instance.units[unitID].unitType == unitType) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::removeUnitFromThisTribeIfInTribe,
                            this)(unitID, DAT_UnitsState::instance.units[unitID].tribeID);
                        DAT_UnitsState::instance.units[unitID].ifSelectedThenPlayerID = 0;
                        DAT_UnitsState::instance.unitCountOfSelection[playerID]--;
                    }
                    touchedTribes[DAT_UnitsState::instance.units[unitID].tribeID] = true;
                }
            }
            for (int tribeID = 1; tribeID < 1250; ++tribeID) {
                if (this->tribes[tribeID].tribeState == 2) {
                    if (this->tribes[tribeID].leaderUnitID == -1) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::electTribeLeader, this)(tribeID);
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::setWhetherTribeContainsAnyUnits, this)(
                        tribeID);
                }
            }
        }

    }
}
}
