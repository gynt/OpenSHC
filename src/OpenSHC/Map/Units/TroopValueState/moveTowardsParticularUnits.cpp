#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitInstructionType;
        using OpenSHC::Map::Units::Instructions::UnitMatchSpeedEnum;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0051D510
        void TroopValueState::moveTowardsParticularUnits(int param_1)
        {
            short sVar1;
            int iVar2;
            sVar1 = DAT_TribesState::instance.tribes[param_1].selectionTargetUnitID;
            iVar2
                = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findDistanceOrThreatLevelToUnitUnk,
                    DAT_PathFindingState::ptr)(DAT_TribesState::instance.tribes[param_1].owner,
                    (int)((int)(DAT_UnitsState::instance.units[sVar1].x)),
                    (int)((int)(DAT_UnitsState::instance.units[sVar1].y)), 0x50);
            if ((iVar2 == 0)
                && (iVar2 = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::findDistanceOrThreatLevelToUnitUnk,
                        DAT_PathFindingState::ptr)(DAT_TribesState::instance.tribes[param_1].owner,
                        (int)((int)(DAT_UnitsState::instance.units[sVar1].x)),
                        (int)((int)(DAT_UnitsState::instance.units[sVar1].y)), 200),
                    iVar2 == 0)) {}
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(
                param_1, OpenSHC::Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk, 0, 0, 0);
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                param_1, (uint)((int)((int)DAT_UnitsState::instance.units[iVar2].x)),
                (uint)((int)((int)DAT_UnitsState::instance.units[iVar2].y)), 0, 0,
                OpenSHC::Map::Units::Instructions::UMSE_0);
        }

    }
}
}
