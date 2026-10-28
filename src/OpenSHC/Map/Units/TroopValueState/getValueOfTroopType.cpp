#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_TroopValueDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051C360
        int TroopValueState::getValueOfTroopType(UnitType unitType)
        {
            switch (unitType) {
            case UT_E_MONK:
                return DAT_TroopValueDefinedData::instance.MONK;
            case UT_TUNNELER:
                return DAT_TroopValueDefinedData::instance.TUNNELER;
            case UT_A_ARCHER:
                return DAT_TroopValueDefinedData::instance.A_ARCHER;
            case UT_A_SLAVE:
                return DAT_TroopValueDefinedData::instance.SLAVE;
            case UT_A_SLINGER:
                return DAT_TroopValueDefinedData::instance.SLINGER;
            case UT_A_ASSASSIN:
                return DAT_TroopValueDefinedData::instance.ASSASSIN;
            case UT_A_HARCHER:
                return DAT_TroopValueDefinedData::instance.HARCHER;
            case UT_A_SWORDSMAN:
                return DAT_TroopValueDefinedData::instance.A_SWORDSMAN;
            case UT_A_FIRETHROWER:
                return DAT_TroopValueDefinedData::instance.FIRETHROWER;
            case UT_S_FBALLISTA:
                return DAT_TroopValueDefinedData::instance.S_FBALLISTA;
            case UT_S_CATAPULT:
                return DAT_TroopValueDefinedData::instance.CATAPULT;
            default:
                if (unitType < UT_E_ARCHER) {
                    return 0;
                }
                if (unitType <= UT_E_ENGINEER) {
                    // ARCHER..ENGINEER are consecutive fields in unit type order
                    return (&DAT_TroopValueDefinedData::instance.ARCHER)[unitType - UT_E_ARCHER];
                }
                return 0;
            }
        }

    }
}
}
