#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Game::GameMode;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040D9C0
        undefined4 BuildingsState::getKeepLocationForAIUnit(int playerID, int param_2, int unitID)
        {
            // Matching note: The remaining differences are register allocation; the original also does not
            // constant propagate group = 16 in the rally branch.
            int type = param_2;
            // AI units in multiplayer gather at the keep
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                && DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1
                && DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0
                && DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType != 2) {
                int keepID = DAT_GameState::instance.playerDataArray[playerID].keep.id;
                if (keepID == 0) {
                    return 0;
                }
                this->DAT_TempXOffset = DAT_BuildingsState::instance.buildings[keepID].accessTileX;
                this->DAT_TempYOffset = DAT_BuildingsState::instance.buildings[keepID].accessTileY;
                return 1;
            }

            // param_2 is the mercenary group (10 to 16)
            if (param_2 == 16) {
                param_2 = 13;
            }
            // Note: indexes past the declared size of rallySearchOffsetsUnk
            int searchOffset = DAT_GameState::instance.playerDataArray[playerID].rallyWaitingCountPerClass[param_2];
            if (DAT_GameState::instance.playerDataArray[playerID].mercenaryAssemblyPoints[type - 10][0] != 0) {
                // Search around the rally point
                if (type == 16) {
                    searchOffset = DAT_GameState::instance.playerDataArray[playerID].rallyWaitingCountPerClass[16];
                    param_2 = type;
                } else if (type == 13) {
                    searchOffset -= DAT_GameState::instance.playerDataArray[playerID].rallyWaitingCountPerClass[16];
                }
                int pointX
                    = (short)DAT_GameState::instance.playerDataArray[playerID].mercenaryAssemblyPoints[param_2 - 10][0];
                int pointY
                    = (short)DAT_GameState::instance.playerDataArray[playerID].mercenaryAssemblyPoints[param_2 - 10][1];
                for (; searchOffset < 49; ++searchOffset) {
                    int x = DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[searchOffset].x + pointX;
                    int y = DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[searchOffset].y + pointY;
                    int tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
                    int unitOnTile = (short)DAT_TileMapState::instance.UnitLayer[tile];
                    if ((unitOnTile == 0 || unitOnTile == unitID
                            || DAT_UnitsState::instance.units[unitID].subTileStepProgress != 8)
                        && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                 calculateCanPlayerUnitsNavigateToAreaFromArea,
                               DAT_PathFindingState::ptr)(playerID,
                               (short)DAT_TileMapState::instance
                                   .PathConnectionLayer[DAT_UnitsState::instance.units[unitID].tile],
                               (short)DAT_TileMapState::instance.PathConnectionLayer[tile], 0)
                            != 0) {
                        this->DAT_TempXOffset = x;
                        this->DAT_TempYOffset = y;
                        if (x == DAT_UnitsState::instance.units[unitID].x
                            && y == DAT_UnitsState::instance.units[unitID].y) {
                            return 0;
                        }
                        return 1;
                    }
                }
                return 0;
            }
            // No rally point, use the parade ground of the mercenary post
            if (DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.id <= 0) {
                return 0;
            }
            if (type == 16) {
                if (DAT_GameState::instance.playerDataArray[playerID].mercenaryAssemblyPoints[3][0] != 0) {
                    searchOffset = DAT_GameState::instance.playerDataArray[playerID].rallyWaitingCountPerClass[16];
                }
            } else if (type == 13
                // Note: the original reads index 16 instead of 16 - 10
                && DAT_GameState::instance.playerDataArray[playerID].mercenaryAssemblyPoints[16][0] != 0) {
                searchOffset -= DAT_GameState::instance.playerDataArray[playerID].rallyWaitingCountPerClass[16];
            }
            int x;
            int y;
            for (int slot = searchOffset;; ++slot) {
                if (slot >= 72) {
                    return 0;
                }
                x = DAT_GameState::instance.playerDataArray[playerID]
                        .mercenaryParadegroundLocations.mercenaryOutpostCampgroundLocations[(param_2 - 10) * 72 + slot]
                        .x;
                y = DAT_GameState::instance.playerDataArray[playerID]
                        .mercenaryParadegroundLocations.mercenaryOutpostCampgroundLocations[(param_2 - 10) * 72 + slot]
                        .y;
                int unitOnTile = (short)DAT_TileMapState::instance
                                     .UnitLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x];
                if (unitOnTile == 0 || unitOnTile == unitID
                    || DAT_UnitsState::instance.units[unitID].subTileStepProgress != 8) {
                    break;
                }
            }
            this->DAT_TempXOffset = x;
            this->DAT_TempYOffset = y;
            if (x == DAT_UnitsState::instance.units[unitID].x && y == DAT_UnitsState::instance.units[unitID].y) {
                return 0;
            }
            return 1;
        }

    }
}
}
