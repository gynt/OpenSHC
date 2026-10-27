#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // The tribe size is re-read every iteration (0x5244A8); the destination is passed sign-extended from
        // its low 16 bits (0x524492 / 0x524495).
        // FUNCTION: STRONGHOLDCRUSADER 0x00524340
        undefined4 TribesState::applyMoveCommandOrRallyCommandToTribe(
            int tribeID, undefined4 x1, undefined4 y1, undefined4 isRallying, int storeAsRallyPoint)
        {
            int unitSelectionIndex = 0;
            BOOLEnum const allAssassins
                = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::isTribeAllAssassins, this)(tribeID);
            this->tribes[tribeID].attackTargetUnitID = 0;
            if (storeAsRallyPoint != 0) {
                int const leaderUnitID = this->tribes[tribeID].leaderUnitID;
                this->tribes[tribeID].rallyMode = (short)isRallying;
                this->tribes[tribeID].rallyPointArray[0][0] = DAT_UnitsState::instance.units[leaderUnitID].x;
                this->tribes[tribeID].rallyPointArray[0][1] = DAT_UnitsState::instance.units[leaderUnitID].y;
                this->tribes[tribeID].rallyPointArray[1][0] = (short)x1;
                this->tribes[tribeID].rallyPointArray[1][1] = (short)y1;
                this->tribes[tribeID].currentRallyPointIndex = 1;
                this->tribes[tribeID].rallyPointCount = 2;
            }
            while (unitSelectionIndex < this->tribes[tribeID].size) {
                int const unitID = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(tribeID, unitSelectionIndex);
                ++unitSelectionIndex;
                if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                    && DAT_UnitsState::instance.units[unitID].dying == 0
                    && DAT_UnitsState::instance.units[unitID].usingTeleport == 0
                    && DAT_UnitsState::instance.units[unitID].isAssassinHookClimbing == 0
                    && DAT_UnitsState::instance.units[unitID].state.generic != States::US_MELEE_ATTACK
                    && DAT_UnitsState::instance.units[unitID].isMovable != 0
                    && DAT_UnitsState::instance.units[unitID].moveRelatedFlag != 1) {
                    DAT_UnitsState::instance.units[unitID].plannedDestinationX = (short)x1;
                    DAT_UnitsState::instance.units[unitID].state.generic = States::US_MOVE_TO_DESTINATION;
                    DAT_UnitsState::instance.units[unitID].targetingType_OR_performanceStep
                        = UIT_NO_INSTRUCTION_OR_MOVE;
                    DAT_UnitsState::instance.units[unitID].chaseReturnX = 0;
                    DAT_UnitsState::instance.units[unitID].chaseReturnY = 0;
                    DAT_UnitsState::instance.units[unitID].plannedDestinationY = (short)y1;
                    DAT_UnitsState::instance.units[unitID].moveDelay = 0;
                    DAT_UnitsState::instance.units[unitID].moveInstructionSpeedDelayTracker = 0;
                    if (allAssassins != FALSE) {
                        DAT_PathFindingState::instance.pathForAssassins = 1;
                    }
                    MACRO_CALL_MEMBER(UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        unitID, (short)x1, (short)y1, 0);
                }
            }
            return 1;
        }

    }
}
}
