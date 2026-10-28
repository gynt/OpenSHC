#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Navigation/Algorithms/XYPair.hpp"

#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {
        using OpenSHC::Map::Navigation::Algorithms::XYPair;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A8780
        int PathFindingState::findUnitPreferredOrientationBasedConnectedTile(int unitID, int tile)
        {
            XYPair* pXVar1;
            int _y;
            int _candidate;
            int _area;
            int _toArea;
            _y = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
            int _x = tile - DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile;
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::calculatePreferredRelativeOrientation,
                DAT_DirectionAlgorithmState::ptr)(_x, _y, (int)(DAT_UnitsState::instance.units[unitID].x),
                (int)(DAT_UnitsState::instance.units[unitID].y));
            pXVar1
                = DAT_ClimbLogicDefinedData::instance
                      .OrderedOrientationBasedCardinalDirectionList[DAT_DirectionAlgorithmState::instance.orientation];
            _area = (int)(short)DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[unitID].tile];
            for (tile = 0; tile < 4; tile++) {
                _candidate
                    = DAT_ViewportRenderState::instance.translationMatrix[pXVar1->y + _y].addXgetTile + pXVar1->x + _x;
                _toArea = (int)(short)DAT_TileMapState::instance.PathConnectionLayer[_candidate];
                if (_area == _toArea
                    || MACRO_CALL_MEMBER(
                           OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                           DAT_PathFindingState::ptr)((int)DAT_UnitsState::instance.units[unitID].owner, (dword)_area,
                           (dword)_toArea, 0)
                        != 0)
                    return _candidate;
                pXVar1 = pXVar1 + 1;
            }
            return 0;
        }

    }
}
}
