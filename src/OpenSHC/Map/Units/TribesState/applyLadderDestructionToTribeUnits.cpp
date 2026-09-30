#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::States::UnitState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00524E20
        void TribesState::applyLadderDestructionToTribeUnits(int param_1)
        {
            int unitID;
            BOOLEnum BVar1;
            int unitSelectionIndex;
            bool bVar2;
            unitSelectionIndex = 0;
            if (0 < this->tribes[param_1].size) {
                do {
                    unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        param_1, unitSelectionIndex);
                    unitSelectionIndex = unitSelectionIndex + 1;
                    if ((DAT_UnitsState::instance.units[unitID].logicalState == OpenSHC::Map::Units::ULS_NORMAL)
                        && (DAT_UnitsState::instance.units[unitID].dying == 0)) {
                        if (DAT_UnitsState::instance.units[unitID].usingTeleport != 0) {}
                        if (DAT_UnitsState::instance.units[unitID].field303_0x413 != 0) {}
                        if (DAT_UnitsState::instance.units[unitID].tunnelerFinishedDigging == 2) {}
                        if (DAT_UnitsState::instance.units[unitID].state.generic
                            == OpenSHC::Map::Units::States::US_MELEE_ATTACK) {}
                        bVar2 = this->tribes[param_1].unknownBool02 == 0;
                        BVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::computeLadderClimbPath,
                            DAT_UnitsState::ptr)(unitID, (uint)((int)(bVar2)), 0, (int)((int)((uint)bVar2)));
                        if (BVar1 != FALSE) {
                            DAT_UnitsState::instance.units[unitID].state.generic
                                = OpenSHC::Map::Units::States::US_DEATH_02
                                | OpenSHC::Map::Units::States::US_STAND_UPUnk;
                        }
                    }
                } while (unitSelectionIndex < this->tribes[param_1].size);
            }
        }

    }
}
}
