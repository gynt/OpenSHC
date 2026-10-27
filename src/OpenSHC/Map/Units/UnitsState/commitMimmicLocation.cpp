#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0053E9F0
        void UnitsState::commitMimmicLocation(int unitID)
        {
            this->units[unitID].subTileStepProgress = 8;
            this->units[unitID].pendingPositionValid = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setupUnitSharingCurrentTilePosition, this)(unitID);
            short mimicX = this->units[unitID].mimicCurrentXPosition;
            short mimicY = this->units[unitID].mimicCurrentYPosition;
            this->units[unitID].microXPosition = mimicX * 8 + 4;
            this->units[unitID].y = mimicY;
            this->units[unitID].x = mimicX;
            this->units[unitID].microYPosition = mimicY * 8 + 4;
            this->units[unitID].tile = DAT_ViewportRenderState::instance.translationMatrix[mimicY].addXgetTile + mimicX;
            this->units[unitID].terrainOrClimbHeight = DAT_TileMapState::instance.HeightLayer[this->units[unitID].tile];
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitPendingUnitPosition, this)(unitID);
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::updateMicroPosition, this)(unitID);
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::recomputeUnitStandingHeight, this)(unitID);
        }

    }
}
}
