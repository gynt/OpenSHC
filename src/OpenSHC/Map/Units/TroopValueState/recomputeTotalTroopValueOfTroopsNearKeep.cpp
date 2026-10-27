#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051FA70
        void TroopValueState::recomputeTotalTroopValueOfTroopsNearKeep()
        {
            DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueOfTroopsNearKeep[0] = 0;
            DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueOfTroopsNearKeep[1] = 0;
            DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueOfTroopsNearKeep[2] = 0;
            DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueOfTroopsNearKeep[3] = 0;
            DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueOfTroopsNearKeep[4] = 0;
            DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueOfTroopsNearKeep[5] = 0;
            DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueOfTroopsNearKeep[6] = 0;
            DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueOfTroopsNearKeep[7] = 0;
            DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueOfTroopsNearKeep[8] = 0;
            DAT_TroopValueState::instance.attackInfo.field_0x25b50 = 0;
            for (int unitID = 1; unitID < (int)DAT_UnitsState::instance.maxUnitCount; ++unitID) {
                if (DAT_UnitsState::instance.units[unitID].logicalState != ULS_INVISIBLE
                    && DAT_UnitsState::instance.units[unitID].dying == 0
                    && DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime != 0
                    && DAT_UnitsState::instance.units[unitID].unitType != UT_E_ENGINEER
                    && DAT_UnitsState::instance.units[unitID].unitType != UT_TUNNELER
                    && DAT_UnitsState::instance.units[unitID].unitType != UT_E_LADDER) {
                    int const owner = DAT_UnitsState::instance.units[unitID].owner;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                        DAT_DirectionAlgorithmState::ptr)(DAT_GameState::instance.playerDataArray[owner].campground.xEntry,
                        DAT_GameState::instance.playerDataArray[owner].campground.yEntry,
                        DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y);
                    if (DAT_DirectionAlgorithmState::instance.distanceHigh <= 40) {
                        DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueOfTroopsNearKeep[owner]
                            += MACRO_CALL_MEMBER(TroopValueState_Func::getValueOfTroopType, this)(
                                (UnitType)(int)(short)DAT_UnitsState::instance.units[unitID].unitType);
                    }
                }
            }
        }

    }
}
}
