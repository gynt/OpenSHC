#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

#include "OpenSHC/Globals/DAT_UnitSelectionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

// The original has no return value on the not-found path (see below).
#pragma warning(disable : 4715)

namespace OpenSHC {
namespace Map {
    namespace Units {

        // Start index = nearbyTileOffsetStartIndex % 40 (cdq; idiv at 0x52A73C), <= 0 -> 0. Destination bounds are
        // unsigned (ja at 0x52A767 / 0x52A76F). When no tile is found the original returns whatever is left in eax
        // (no explicit return value, 0x52A7A4); the only caller ignores the result.
        // FUNCTION: STRONGHOLDCRUSADER 0x0052A700
        int TribesState::moveTribeToIndexedNearbyTile(int tribeID)
        {
            int const leaderUnitID = this->tribes[tribeID].leaderUnitID;
            int const fromX = DAT_UnitsState::instance.units[leaderUnitID].x;
            int const fromY = DAT_UnitsState::instance.units[leaderUnitID].y;
            int startIndex = this->tribes[tribeID].nearbyTileOffsetStartIndex % 40;
            if (startIndex <= 0) {
                startIndex = 0;
            }
            if (startIndex < 40) {
                for (int i = startIndex; i < 40; ++i) {
                    uint const destX = DAT_UnitSelectionDefinedData::instance.nearbyTileOffsets[i].x + fromX;
                    uint const destY = DAT_UnitSelectionDefinedData::instance.nearbyTileOffsets[i].y + fromY;
                    if (destX <= 399 && destY <= 399
                        && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[destY * 400 + destX] != 0
                        && MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::isTribePathToDestinationClear,
                               this)(tribeID, fromX, fromY, destX, destY)
                            != 0) {
                        return MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction,
                            this)(tribeID, destX, destY, 0, 0, Instructions::UMSE_0);
                    }
                }
            }
        }
    }
}
}
