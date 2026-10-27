#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/Pathfinding/DestinationNeededEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00530C40
    BOOLEnum Units::ConsiderTakingFearFactorBreak(int unitID, UnitState nextUnitState)
    {
        int owner = DAT_UnitsState::instance.units[unitID].owner;
        if (DAT_UnitsState::instance.units[unitID].destinationNeeded
            != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED) {
            return FALSE;
        }
        if (DAT_GameState::instance.playerDataArray[owner].fearFactorEfficiencyPercent < 100
            && DAT_UnitsState::instance.units[unitID].avgWorkCycleTicks > 100) {
            DAT_UnitsState::instance.units[unitID].requiredBreakTicks
                = (short)((100 - DAT_GameState::instance.playerDataArray[owner].fearFactorEfficiencyPercent)
                    * DAT_UnitsState::instance.units[unitID].avgWorkCycleTicks / 100);
            if (DAT_UnitsState::instance.units[unitID].banked
                >= DAT_UnitsState::instance.units[unitID].requiredBreakTicks) {
                DAT_UnitsState::instance.units[unitID].banked
                    -= DAT_UnitsState::instance.units[unitID].requiredBreakTicks;
                return FALSE;
            }
            DAT_UnitsState::instance.units[unitID].stateAfterFade = (short)nextUnitState;
            DAT_UnitsState::instance.units[unitID].idle = DAT_UnitsState::instance.units[unitID].banked;
            DAT_UnitsState::instance.units[unitID].productionPaused = 0;
            // resting
            DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)121;
            return TRUE;
        }
        return FALSE;
    }

}
}
