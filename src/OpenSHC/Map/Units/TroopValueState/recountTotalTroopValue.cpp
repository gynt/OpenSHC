#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051F9C0
        void TroopValueState::recountTotalTroopValue()
        {
            DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[0] = 0;
            DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[1] = 0;
            DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[2] = 0;
            DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[3] = 0;
            DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[4] = 0;
            DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[5] = 0;
            DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[6] = 0;
            DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[7] = 0;
            DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[8] = 0;
            DAT_TroopValueState::instance.attackInfo.troopValueUnk25b28 = 0;
            int const maxUnitCount = DAT_UnitsState::instance.maxUnitCount;
            for (int unitID = 1; unitID < maxUnitCount; ++unitID) {
                if (DAT_UnitsState::instance.units[unitID].logicalState != ULS_INVISIBLE
                    && DAT_UnitsState::instance.units[unitID].dying == 0
                    && DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime != 0
                    && DAT_UnitsState::instance.units[unitID].unitType != UT_E_ENGINEER
                    && DAT_UnitsState::instance.units[unitID].unitType != UT_TUNNELER
                    && DAT_UnitsState::instance.units[unitID].unitType != UT_E_LADDER) {
                    DAT_TroopValueState::instance.attackInfo
                        .playerTotalTroopValueArray[DAT_UnitsState::instance.units[unitID].owner]
                        += MACRO_CALL_MEMBER(TroopValueState_Func::getValueOfTroopType, this)(
                            (UnitType)(int)(short)DAT_UnitsState::instance.units[unitID].unitType);
                }
            }
        }

    }
}
}
