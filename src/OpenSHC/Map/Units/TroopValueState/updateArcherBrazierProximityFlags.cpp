#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051C2D0
        void TroopValueState::updateArcherBrazierProximityFlags()
        {
            for (int unitID = 1; unitID < (int)DAT_UnitsState::instance.maxUnitCount; ++unitID) {
                if (DAT_UnitsState::instance.units[unitID].logicalState != ULS_INVISIBLE
                    && MACRO_CALL_MEMBER(TroopValueState_Func::getPlayerNot1AndHasKeep, this)(
                           DAT_UnitsState::instance.units[unitID].owner)
                        != FALSE
                    && (DAT_UnitsState::instance.units[unitID].unitType == UT_E_ARCHER
                        || DAT_UnitsState::instance.units[unitID].unitType == UT_A_ARCHER)
                    && DAT_UnitsState::instance.units[unitID].dying == 0) {
                    DAT_UnitsState::instance.units[unitID].isNearBrazier
                        = MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::isBrazierNearby,
                              DAT_EntityState::ptr)(DAT_UnitsState::instance.units[unitID].x,
                              DAT_UnitsState::instance.units[unitID].y,
                              DAT_UnitsState::instance.units[unitID].buildingHeight
                                  + DAT_UnitsState::instance.units[unitID].terrainOrClimbHeight)
                        != 0;
                }
            }
        }

    }
}
}
