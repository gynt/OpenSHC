#include "../TribesState.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00522F70
        void TribesState::spawnUnitsForAITribe(undefined4 unused1, int tileX, int tileY, int playerID,
            UnitType unitType, int count, int calcOwnerIndex)
        {
            if ((tileX > 0 || tileY > 0) && count > 0) {
                for (int i = 0; i < count; ++i) {
                    int const unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit,
                        DAT_UnitsState::ptr)(playerID, playerID, tileX * 8, tileY * 8, 8, unitType);
                    if (unitID != 0) {
                        DAT_UnitsState::instance.units[unitID].ownerColorIndex = calcOwnerIndex;
                        UnitTypeShort const spawnedType = DAT_UnitsState::instance.units[unitID].unitType;
                        if (spawnedType == UT_E_ARCHER || spawnedType == UT_E_XBOW || spawnedType == UT_A_ARCHER
                            || spawnedType == UT_A_SLINGER || spawnedType == UT_A_HARCHER
                            || spawnedType == UT_A_FIRETHROWER) {
                            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addUnitToItsTribe, DAT_AICState::ptr)(
                                unitID, 0x11);
                        } else {
                            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addUnitToItsTribe, DAT_AICState::ptr)(
                                unitID, 0x14);
                        }
                    }
                }
            }
        }

    }
}
}
