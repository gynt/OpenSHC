#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

#include "OpenSHC/Globals/DAT_UnitSelectionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // Destination bounds are unsigned compares (ja at 0x52A686 / 0x52A68E): offset + leader position.
        // FUNCTION: STRONGHOLDCRUSADER 0x0052A640
        void TribesState::moveTribeToNearbyClearTile(int tribeID)
        {
            int const leaderUnitID = this->tribes[tribeID].leaderUnitID;
            int const fromX = DAT_UnitsState::instance.units[leaderUnitID].x;
            int const fromY = DAT_UnitsState::instance.units[leaderUnitID].y;
            for (int i = 0; i < 40; ++i) {
                uint const destX = DAT_UnitSelectionDefinedData::instance.nearbyTileOffsets[i].x + fromX;
                uint const destY = DAT_UnitSelectionDefinedData::instance.nearbyTileOffsets[i].y + fromY;
                if (destX <= 399 && destY <= 399
                    && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[destY * 400 + destX] != 0
                    && MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::isTribePathToDestinationClear, this)(
                           tribeID, fromX, fromY, destX, destY)
                        != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction, this)(
                        tribeID, destX, destY, 0, 0, Instructions::UMSE_0);
                    return;
                }
            }
        }

    }
}
}
