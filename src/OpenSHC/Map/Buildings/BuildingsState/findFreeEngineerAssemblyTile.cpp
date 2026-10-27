#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040E120
        int BuildingsState::findFreeEngineerAssemblyTile(int playerIndex, int param_2)
        {
            // Matching note: The remaining differences are register and stack slot allocation.
            // param_2 is the unit. Engineers and laddermen use their own assembly point.
            int laddermenCount = (short)DAT_GameState::instance.playerDataArray[playerIndex].laddermanAssemblyCount;
            int i = DAT_GameState::instance.playerDataArray[playerIndex].engineerGuildAssemblyCount - laddermenCount;
            int isLadderman = 0;
            if (DAT_UnitsState::instance.units[param_2].unitType == OpenSHC::Map::Units::UT_E_LADDER) {
                isLadderman = 1;
                i = laddermenCount;
            }
            short assemblyX
                = DAT_GameState::instance.playerDataArray[playerIndex].engineersAssemblyPoints[isLadderman].x;
            if (assemblyX != 0) {
                // Search around the assembly point
                int pointY
                    = (short)DAT_GameState::instance.playerDataArray[playerIndex].engineersAssemblyPoints[isLadderman].y;
                int pointX = assemblyX;
                for (; i < 49; ++i) {
                    int x = DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[i].x + pointX;
                    int y = DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[i].y + pointY;
                    int tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
                    int unitOnTile = (short)DAT_TileMapState::instance.UnitLayer[tile];
                    if ((unitOnTile == 0 || unitOnTile == param_2
                            || DAT_UnitsState::instance.units[param_2].subTileStepProgress != 8)
                        && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                 calculateCanPlayerUnitsNavigateToAreaFromArea,
                               DAT_PathFindingState::ptr)(playerIndex,
                               (short)DAT_TileMapState::instance
                                   .PathConnectionLayer[DAT_UnitsState::instance.units[param_2].tile],
                               (short)DAT_TileMapState::instance.PathConnectionLayer[tile], 0)
                            != 0) {
                        this->DAT_TempXOffset = x;
                        this->DAT_TempYOffset = y;
                        if (x == DAT_UnitsState::instance.units[param_2].x
                            && y == DAT_UnitsState::instance.units[param_2].y) {
                            return 0;
                        }
                        return 1;
                    }
                }
                return 0;
            }

            // No assembly point, use the parade ground. Laddermen fill it up from the back.
            uint x;
            uint y;
            for (int slot = i;; ++slot) {
                if (slot >= 25) {
                    return 0;
                }
                if (isLadderman != 0) {
                    x = DAT_GameState::instance.playerDataArray[playerIndex].engineersParadegroundLocations[24 - slot].x;
                    y = DAT_GameState::instance.playerDataArray[playerIndex].engineersParadegroundLocations[24 - slot].y;
                } else {
                    x = DAT_GameState::instance.playerDataArray[playerIndex].engineersParadegroundLocations[slot].x;
                    y = DAT_GameState::instance.playerDataArray[playerIndex].engineersParadegroundLocations[slot].y;
                }
                if (x <= 399 && y <= 399
                    && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] != 0) {
                    int unitOnTile = (short)DAT_TileMapState::instance
                                         .UnitLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x];
                    if (unitOnTile == 0 || unitOnTile == param_2
                        || DAT_UnitsState::instance.units[param_2].subTileStepProgress != 8) {
                        break;
                    }
                }
            }
            this->DAT_TempXOffset = x;
            this->DAT_TempYOffset = y;
            if (x == DAT_UnitsState::instance.units[param_2].x && y == DAT_UnitsState::instance.units[param_2].y) {
                return 0;
            }
            return 1;
        }

    }
}
}
