#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::States::UnitState;

        // getComputationalTileIndex returns undefined4 but the tile count is compared signed (jge at 0x52398F).
        // targetX is a 16-bit subtraction (sub ax at 0x5239F4).
        // FUNCTION: STRONGHOLDCRUSADER 0x00523920
        int TribesState::scatterTribeUnitsRandomly(int tribeID)
        {
            if (tribeID == 0) {
                return 0;
            }
            int unitSelectionIndex = 0;
            int queueIndex = 100;
            int const leaderUnitID = this->tribes[tribeID].leaderUnitID;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findPathWithBudget,
                DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[leaderUnitID].x,
                DAT_UnitsState::instance.units[leaderUnitID].y, -1, -1, 5000, 0);
            int const tileCount = (int)MACRO_CALL_MEMBER(
                OpenSHC::Map::Navigation::PathFindingState_Func::getComputationalTileIndex, DAT_PathFindingState::ptr)();
            if (tileCount < this->tribes[tribeID].size * 16 + 200) {
                return 0;
            }
            for (; unitSelectionIndex < this->tribes[tribeID].size;) {
                int const unitID = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(tribeID, unitSelectionIndex);
                ++unitSelectionIndex;
                if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                    && DAT_UnitsState::instance.units[unitID].dying == 0) {
                    queueIndex += (DAT_UnitsState::instance.units[unitID].fixedRng & 0xf) + 1;
                    int const destTile = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::getTileInSearchQueue, DAT_PathFindingState::ptr)(
                        queueIndex);
                    int const destY = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[destTile];
                    DAT_UnitsState::instance.units[unitID].targetY = (short)destY;
                    DAT_UnitsState::instance.units[unitID].targetX
                        = (short)destTile - (short)DAT_ViewportRenderState::instance.translationMatrix[destY].addXgetTile;
                    DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)0xd1;
                }
            }
            return 1;
        }

    }
}
}
