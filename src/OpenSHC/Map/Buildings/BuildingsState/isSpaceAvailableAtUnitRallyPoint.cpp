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

        // FUNCTION: STRONGHOLDCRUSADER 0x0040D6E0
        undefined4 BuildingsState::isSpaceAvailableAtUnitRallyPoint(int playerID, int value0to6, int unitID)
        {
            // Matching note: The remaining differences are register allocation; the original also does not
            // constant propagate group = 6 in the rally branch.
            int type = value0to6;
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

            if (value0to6 == 6) {
                value0to6 = 5;
            }
            int searchOffset = DAT_GameState::instance.playerDataArray[playerID].rallyWaitingCountPerClass[value0to6];
            if (DAT_GameState::instance.playerDataArray[playerID].barracksAssemblyPoints[type].x != 0) {
                // Search around the rally point
                if (type == 6) {
                    searchOffset = DAT_GameState::instance.playerDataArray[playerID].rallyWaitingCountPerClass[6];
                    value0to6 = type;
                } else if (type == 5) {
                    searchOffset -= DAT_GameState::instance.playerDataArray[playerID].rallyWaitingCountPerClass[6];
                }
                int pointX
                    = (short)DAT_GameState::instance.playerDataArray[playerID].barracksAssemblyPoints[value0to6].x;
                int pointY
                    = (short)DAT_GameState::instance.playerDataArray[playerID].barracksAssemblyPoints[value0to6].y;
                for (; searchOffset < 49; ++searchOffset) {
                    uint x = DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[searchOffset].x + pointX;
                    uint y = DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[searchOffset].y + pointY;
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
            // No rally point, use the parade ground of the barracks
            if (DAT_GameState::instance.playerDataArray[playerID].barracks.id <= 0) {
                return 0;
            }
            if (type == 6) {
                if (DAT_GameState::instance.playerDataArray[playerID].barracksAssemblyPoints[5].x != 0) {
                    searchOffset = DAT_GameState::instance.playerDataArray[playerID].rallyWaitingCountPerClass[6];
                }
            } else if (type == 5 && DAT_GameState::instance.playerDataArray[playerID].barracksAssemblyPoints[6].x != 0) {
                searchOffset -= DAT_GameState::instance.playerDataArray[playerID].rallyWaitingCountPerClass[6];
            }
            uint x;
            uint y;
            for (int slot = searchOffset;; ++slot) {
                if (slot >= 72) {
                    return 0;
                }
                x = DAT_GameState::instance.playerDataArray[playerID].barracksParadegroundLocations[value0to6][slot].x;
                y = DAT_GameState::instance.playerDataArray[playerID].barracksParadegroundLocations[value0to6][slot].y;
                if (x <= 399 && y <= 399 && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] != 0) {
                    int unitOnTile = (short)DAT_TileMapState::instance
                                         .UnitLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x];
                    if (unitOnTile == 0 || unitOnTile == unitID
                        || DAT_UnitsState::instance.units[unitID].subTileStepProgress != 8) {
                        break;
                    }
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
