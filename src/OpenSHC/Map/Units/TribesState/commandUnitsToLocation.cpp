#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/g_tribeScanIndex.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // The countdown2 test reads the tribe g_tribeScanIndex, not tribeID (0x526FEB), and freeUnitSpeeds is
        // cleared through the global DAT_TribesState (absolute 0x1668190 at 0x5270B2), as in machine code.
        // matchUnitSpeeds is tested as a byte (0x52702C, 0x5270A9).
        // FUNCTION: STRONGHOLDCRUSADER 0x00526F00
        undefined4 TribesState::commandUnitsToLocation(
            int tribeID, uint destinationX, uint destinationY, undefined4 matchUnitSpeeds)
        {
            int unitSelectionIndex = 0;
            int noUnitEligible = 1;
            if (this->tribes[tribeID].size > 0) {
                do {
                    int const unitID = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        tribeID, unitSelectionIndex);
                    ++unitSelectionIndex;
                    if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                        && DAT_UnitsState::instance.units[unitID].dying == 0) {
                        short const goToRallyPoint = DAT_UnitsState::instance.units[unitID].goToRallyPoint;
                        DAT_UnitsState::instance.units[unitID].rallyRelatedFlag = 0;
                        if (goToRallyPoint == 0 && DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime != 0
                            && (MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                                    DAT_DirectionAlgorithmState::ptr)(destinationX, destinationY,
                                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y),
                                DAT_DirectionAlgorithmState::instance.distanceHigh > 4)
                            && (DAT_UnitsState::instance.units[unitID].chaseTargetUnitID == 0
                                || DAT_UnitsState::instance.units[DAT_UnitsState::instance.units[unitID].targetUnitId]
                                        .logicalState
                                    != ULS_NORMAL)
                            && (DAT_UnitsState::instance.units[unitID].shootTargetedUnit == 0
                                || this->tribes[g_tribeScanIndex::instance].countdown2 <= 0
                                || DAT_UnitsState::instance.units[unitID].unitType == UT_A_HARCHER
                                || DAT_UnitsState::instance.units[unitID].targetUID
                                    != DAT_UnitsState::instance
                                           .units[DAT_UnitsState::instance.units[unitID].shootTargetedUnit]
                                           .uid)
                            && DAT_UnitsState::instance.units[unitID].state.generic != States::US_MELEE_ATTACK
                            && ((char)matchUnitSpeeds != 0
                                || (DAT_UnitsState::instance.units[unitID].unitType != UT_S_FBALLISTA
                                    && DAT_UnitsState::instance.units[unitID].unitType != UT_S_CATAPULT
                                    && DAT_UnitsState::instance.units[unitID].unitType != UT_S_SHIELD
                                    && DAT_UnitsState::instance.units[unitID].unitType != UT_S_TOWER
                                    && DAT_UnitsState::instance.units[unitID].unitType != UT_S_BATTERINGRAM))
                            && (DAT_UnitsState::instance.units[unitID].isOilDutyEngineer == 0
                                || (DAT_UnitsState::instance.units[unitID].resourceToDeposit != 0
                                    && DAT_UnitsState::instance.units[unitID].isManningBuilding == 0))) {
                            DAT_UnitsState::instance.units[unitID].rallyRelatedFlag = 0;
                            noUnitEligible = 0;
                        } else {
                            DAT_UnitsState::instance.units[unitID].rallyRelatedFlag = 1;
                        }
                    }
                } while (unitSelectionIndex < this->tribes[tribeID].size);
            }
            if (noUnitEligible != 0) {
                return 0;
            }
            if ((char)matchUnitSpeeds != 0) {
                DAT_TribesState::instance.tribes[tribeID].freeUnitSpeeds = 0;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction, this)(
                tribeID, destinationX, destinationY, 0, 0, OpenSHC::Map::Units::Instructions::UMSE_0);
            return 1;
        }

    }
}
}
