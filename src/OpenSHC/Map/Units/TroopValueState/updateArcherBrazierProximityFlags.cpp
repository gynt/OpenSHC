#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0051C2D0
        void TroopValueState::updateArcherBrazierProximityFlags()
        {
            BOOLEnum BVar1;
            int iVar2;
            Unit* pUVar2;
            int iVar3;
            iVar3 = 1;
            if (1 < (int)DAT_UnitsState::instance.maxUnitCount) {
                pUVar2 = &DAT_UnitsState::instance.units[1];
                do {
                    if ((((pUVar2->logicalState != OpenSHC::Map::Units::ULS_INVISIBLE)
                             && (BVar1
                                 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::getPlayerNot1AndHasKeep,
                                     this)((int)pUVar2->owner),
                                 BVar1 != FALSE))
                            && ((pUVar2->unitType == OpenSHC::Map::Units::UT_E_ARCHER
                                || (pUVar2->unitType == OpenSHC::Map::Units::UT_A_ARCHER))))
                        && (pUVar2->dying == 0)) {
                        iVar2 = MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::isBrazierNearby,
                            DAT_EntityState::ptr)((int)pUVar2->x, (int)((int)(pUVar2->y)),
                            (int)((int)(pUVar2->buildingHeight + pUVar2->terrainOrClimbHeight)));
                        pUVar2->field297_0x40d = iVar2 != 0;
                    }
                    iVar3 = iVar3 + 1;
                    pUVar2 = pUVar2 + 0x248;
                } while (iVar3 < (int)DAT_UnitsState::instance.maxUnitCount);
            }
        }

    }
}
}
