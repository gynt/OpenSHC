#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitType;

        // Unit+0x390 is padding_0x390[2] in the header but is a short flag here (0x5222F5, 0x522332).
        // maxUnitCount (uint) is compared signed (jle 0x522299, jl 0x52234C).
        // FUNCTION: STRONGHOLDCRUSADER 0x00522210
        void TribesState::updatePeasantSeatingAtBuilding(int buildingID, int peasantCount, int resetStanding)
        {
            int const owner = DAT_BuildingsState::instance.buildings[buildingID].owner;
            int peasantsSeen = 0;
            if (peasantCount <= 1) {
                peasantCount = 1;
            } else if (peasantCount <= 3) {
                peasantCount = (SEC_RNG::instance.currentNumber2 & 1) + 1;
            } else if (peasantCount <= 7) {
                peasantCount = (SEC_RNG::instance.currentNumber2 & 3) + 1;
            } else if (peasantCount <= 15) {
                peasantCount = (SEC_RNG::instance.currentNumber2 & 7) + 1;
            } else {
                peasantCount = (SEC_RNG::instance.currentNumber2 & 0xf) + 1;
            }
            for (int unitID = 1; unitID < (int)DAT_UnitsState::instance.maxUnitCount; ++unitID) {
                if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                    && DAT_UnitsState::instance.units[unitID].dying == 0
                    && DAT_UnitsState::instance.units[unitID].owner == owner
                    && DAT_UnitsState::instance.units[unitID].unitType == UT_PEASANT
                    && DAT_UnitsState::instance.units[unitID].state.generic == States::US_STAND_UPUnk
                    && DAT_UnitsState::instance.units[unitID].workplaceOrHomeBuildingID == buildingID) {
                    ++peasantsSeen;
                    *(short*)DAT_UnitsState::instance.units[unitID].padding_0x390 = 0;
                    if (resetStanding == 1) {
                        DAT_UnitsState::instance.units[unitID].peasantAlwaysZero = 0;
                    }
                    if (peasantsSeen == peasantCount) {
                        DAT_UnitsState::instance.units[unitID].peasantAlwaysZero = 1;
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::standUpIfSeated, DAT_UnitsState::ptr)(
                            unitID);
                    } else if (DAT_UnitsState::instance.units[unitID].peasantAlwaysZero == 0) {
                        *(short*)DAT_UnitsState::instance.units[unitID].padding_0x390 = 1;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::UnitsState_Func::sitDownIfStanding, DAT_UnitsState::ptr)(unitID);
                    }
                }
            }
        }

    }
}
}
