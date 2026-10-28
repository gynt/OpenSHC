#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051BF20
        BOOLEnum TroopValueState::shouldLightPitchBasedOnTroopValue(int tile, int playerID, int enemyPlayerID)
        {
            // enemyPlayerID is never read
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::computeTotalUnitsWithinDistance,
                DAT_PathFindingState::ptr)(playerID, 1, 1, tile, 10);
            int const ownTroopValue = DAT_PathFindingState::instance.ALGO_TotalTroopValue;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::computeTotalUnitsWithinDistance,
                DAT_PathFindingState::ptr)(playerID, 0, 1, tile, 6);
            return (BOOLEnum)(DAT_PathFindingState::instance.ALGO_TotalTroopValue > ownTroopValue * 2);
        }

    }
}
}
