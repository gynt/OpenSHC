
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00511850
    void TileMapState::updateGameRelatedValue()
    {
        if (DAT_GameState::instance.mapAndTime.invasionNextMonthCountdown == 0) {
            return;
        }

        if (DAT_GameState::instance.mapAndTime.invasionNextMonthCountdown == 0x28) {
            this->currentSignpostDistance = -1;
        }
        DAT_GameState::instance.mapAndTime.invasionNextMonthCountdown
            = DAT_GameState::instance.mapAndTime.invasionNextMonthCountdown - 1;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setSignpostDistanceForCampaignMission, this)();
        int signpostDistance = ((0x28 - DAT_GameState::instance.mapAndTime.invasionNextMonthCountdown)
                                   * DAT_GameState::instance.mapAndTime.signpostExclusionRadius)
            / 0x28;
        if (signpostDistance == this->currentSignpostDistance) {
            return;
        }

        this->currentSignpostDistance = signpostDistance;
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::clearObstaclesAroundSignposts,
            DAT_PathFindingState::ptr)(signpostDistance);
    }

}
}
