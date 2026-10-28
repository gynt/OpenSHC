#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00533A10
        BOOLEnum UnitsState::computeRandomWanderPath(int unitID, uint param_2, int param_3, int param_4)
        {
            this->units[unitID].climbDataID = 0;
            DAT_PathFindingState::instance.climbIsIllegal = 0;
            DAT_PathFindingState::instance.pathForAssassins = 0;
            this->units[unitID].blockedWaitCounter = 0;
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
                0x490, &this->units[unitID], this->units);
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                400, '\0', DAT_UnitsState::instance.units[unitID].pathPlanStart);
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::bindPathPlanToAlgorithmStateAndReset,
                DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[unitID].pathPlanStart);
            DAT_PathFindingState::instance.unitX = this->units[unitID].x;
            DAT_PathFindingState::instance.unitY = this->units[unitID].y;
            int _pathPlanSize
                = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::commitUnitPathPlanUsingWalkLayer,
                    DAT_PathFindingState::ptr)(param_2, param_3, param_4);
            if (_pathPlanSize > 0) {
                this->units[unitID].pathStartY = this->units[unitID].y;
                this->units[unitID].totalSizeOfPathPlan = (short)_pathPlanSize;
                this->units[unitID].currentIndexInPathPlan = 0;
                this->units[unitID].pathStartX = this->units[unitID].x;
                this->units[unitID].movementState = 2;
                this->units[unitID].previousTilePosition = this->units[unitID].x
                    + DAT_ViewportRenderState::instance.translationMatrix[this->units[unitID].y].addXgetTile;
                this->units[unitID].cannotClimb = 0;
                return TRUE;
            }
            return FALSE;
        }

    }
}
}
