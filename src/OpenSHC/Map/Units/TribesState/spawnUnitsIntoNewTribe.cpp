#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00523030
        dword TribesState::spawnUnitsIntoNewTribe(undefined4 counter, int tribeType, int x, int y, int playerID,
            UnitType unitType, UnitType unitType2, int unitType1Count, int unitType2Count)
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
            this->tribes[tribeID].nearbyTileOffsetStartIndex = (short)counter;
            this->tribes[tribeID].attackWave = (short)DAT_TroopValueState::instance.attackInfo.currentAttackWaveSlot;
            for (int i = 0; i < unitType1Count; ++i) {
                int const unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit,
                    DAT_UnitsState::ptr)(playerID, playerID, x * 8, y * 8, 8, unitType);
                if (unitID != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToTribe, this)(
                        unitID, tribeID);
                    DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType = 0;
                }
            }
            for (int i = 0; i < unitType2Count; ++i) {
                int const unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit,
                    DAT_UnitsState::ptr)(playerID, playerID, x * 8, y * 8, 8, unitType2);
                if (unitID != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToTribe, this)(
                        unitID, tribeID);
                    DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType = 0;
                }
            }
            this->tribes[tribeID].spreadOnSpawnPending = 1;
            return tribeID;
        }

    }
}
}
