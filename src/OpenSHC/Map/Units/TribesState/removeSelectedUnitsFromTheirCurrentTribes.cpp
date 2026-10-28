#include "../TribesState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // The touched-tribe array is written (0x525804) but never read. maxUnitCount is compared signed (jl at
        // 0x525818).
        // FUNCTION: STRONGHOLDCRUSADER 0x00525790
        void TribesState::removeSelectedUnitsFromTheirCurrentTribes(int playerID)
        {
            bool touchedTribes[1250];
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(touchedTribes), 0, touchedTribes);
            for (int unitID = 1; unitID < (int)DAT_UnitsState::instance.maxUnitCount; ++unitID) {
                if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                    && DAT_UnitsState::instance.units[unitID].dying == 0
                    && DAT_UnitsState::instance.units[unitID].ifSelectedThenPlayerID == playerID) {
                    int const tribeID = DAT_UnitsState::instance.units[unitID].tribeID;
                    if (tribeID > 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::removeUnitFromThisTribeIfInTribe,
                            this)(unitID, tribeID);
                        touchedTribes[tribeID] = true;
                    }
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
