#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051D0D0
        void TroopValueState::sendAttackingPatrolTribeToComputedDestination(int tribeID)
        {
            int const leaderUnitID = DAT_TribesState::instance.tribes[tribeID].leaderUnitID;
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updatePathLinkageTileMap, DAT_BuildingsState::ptr)(
                1);
            int tile = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findTileAtZoneDistanceByPathCost,
                DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[leaderUnitID].x,
                DAT_UnitsState::instance.units[leaderUnitID].y, DAT_UnitsState::instance.units[leaderUnitID].owner, 12,
                1);
            if (tile <= 0) {
                tile = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findTileAtZoneDistanceByPathCost,
                    DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[leaderUnitID].x,
                    DAT_UnitsState::instance.units[leaderUnitID].y, DAT_UnitsState::instance.units[leaderUnitID].owner,
                    30, 1);
                if (tile <= 0) {
                    tile = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findTileAtZoneDistanceByPathCost,
                        DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[leaderUnitID].x,
                        DAT_UnitsState::instance.units[leaderUnitID].y,
                        DAT_UnitsState::instance.units[leaderUnitID].owner, 50, 1);
                }
            }
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updatePathLinkageTileMap, DAT_BuildingsState::ptr)(
                0);
            if (tile > 0) {
                MACRO_CALL_MEMBER(TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(tribeID,
                    tile
                        - DAT_ViewportRenderState::instance
                            .translationMatrix[DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile]]
                            .addXgetTile,
                    DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile], 0, 0,
                    Instructions::UMSE_0);
            }
        }

    }
}
}
