#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051CBD0
        void TroopValueState::redeployArchersToDefensivePositions()
        {
            if (DAT_TroopValueState::instance.attackInfo.unitsSentToKeep != 0
                || DAT_TroopValueState::instance.attackInfo.reserveArcherCount <= 0) {
                return;
            }
            // the reserve count is only checked before the loop: more vacant posts than reserve archers read
            // before reserveArcherUnitIDs (original behaviour)
            for (int postIdx = 0; postIdx < DAT_TroopValueState::instance.attackInfo.wallArcherPostCount; ++postIdx) {
                int const postUnitID = DAT_TroopValueState::instance.attackInfo.wallArcherPostUnitIDs[postIdx];
                if (postUnitID != 0
                    && DAT_UnitsState::instance.units[postUnitID].uid
                        == DAT_TroopValueState::instance.attackInfo.wallArcherPostUnitUIDs[postIdx]) {
                    continue;
                }
                int const tile = DAT_TroopValueState::instance.attackInfo.wallArcherPostTiles[postIdx];
                if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x10000100) == 0) {
                    continue;
                }
                int const y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                --DAT_TroopValueState::instance.attackInfo.reserveArcherCount;
                int const unitID
                    = DAT_TroopValueState::instance.attackInfo
                          .reserveArcherUnitIDs[DAT_TroopValueState::instance.attackInfo.reserveArcherCount];
                DAT_TroopValueState::instance.attackInfo.wallArcherPostUnitUIDs[postIdx]
                    = DAT_UnitsState::instance.units[unitID].uid;
                DAT_TroopValueState::instance.attackInfo.wallArcherPostUnitIDs[postIdx] = unitID;
                DAT_UnitsState::instance.units[unitID].state.generic = States::US_MOVE_TO_DESTINATION;
                MACRO_CALL_MEMBER(UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    unitID, tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile, y, 0);
            }
        }

    }
}
}
