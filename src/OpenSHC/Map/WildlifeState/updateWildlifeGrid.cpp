#include "OpenSHC/Map/WildlifeState.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Trees/TreeType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // Camp areas: PathConnectionLayer (movsx) of each slot's campground entry, -1 for slots without a player ID
    // (computed before the mode test, 0x52BA28..0x52BB1A). Only in GM_SOLITARY (jne 0x52BF2F) row _y10 is
    // rebuilt: per cell the counters are cleared, every valid tile (unsigned bounds, ja 0x18F) of the 10x10 block
    // is tallied, and the most frequent path area (ties keep the first, signed jle) becomes dominantPathAreaId.
    // FUNCTION: STRONGHOLDCRUSADER 0x0052BA10
    void WildlifeState::updateWildlifeGrid(int _y10)
    {
        struct AreaCount {
            int area;
            int count;
        } areaHistogram[100];

        int const tileYBase = _y10 * 10;
        int campArea1 = -1;
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[1] != -1) {
            campArea1 = (short)DAT_TileMapState::instance
                            .PathConnectionLayer[DAT_GameState::instance.playerDataArray[1].campground.tileEntry];
        }
        int campArea2 = -1;
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[2] != -1) {
            campArea2 = (short)DAT_TileMapState::instance
                            .PathConnectionLayer[DAT_GameState::instance.playerDataArray[2].campground.tileEntry];
        }
        int campArea3 = -1;
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[3] != -1) {
            campArea3 = (short)DAT_TileMapState::instance
                            .PathConnectionLayer[DAT_GameState::instance.playerDataArray[3].campground.tileEntry];
        }
        int campArea4 = -1;
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[4] != -1) {
            campArea4 = (short)DAT_TileMapState::instance
                            .PathConnectionLayer[DAT_GameState::instance.playerDataArray[4].campground.tileEntry];
        }
        int campArea5 = -1;
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[5] != -1) {
            campArea5 = (short)DAT_TileMapState::instance
                            .PathConnectionLayer[DAT_GameState::instance.playerDataArray[5].campground.tileEntry];
        }
        int campArea6 = -1;
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[6] != -1) {
            campArea6 = (short)DAT_TileMapState::instance
                            .PathConnectionLayer[DAT_GameState::instance.playerDataArray[6].campground.tileEntry];
        }
        int campArea7 = -1;
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[7] != -1) {
            campArea7 = (short)DAT_TileMapState::instance
                            .PathConnectionLayer[DAT_GameState::instance.playerDataArray[7].campground.tileEntry];
        }
        int campArea8 = -1;
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[8] != -1) {
            campArea8 = (short)DAT_TileMapState::instance
                            .PathConnectionLayer[DAT_GameState::instance.playerDataArray[8].campground.tileEntry];
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
            return;
        }
        for (int tileX = 0; tileX < 400; tileX += 10) {
            int const gridX = tileX / 10;
            WildlifeGridElement* const cell = &this->grid[gridX][_y10];
            cell->validTileCount = 0;
            cell->dominantPathAreaId = 0;
            cell->unclaimedArea = 0;
            cell->buildingTileCount = 0;
            cell->keeps = 0;
            cell->wallTileCount = 0;
            cell->trees = 0;
            cell->unitCount = 0;
            cell->humanCount = 0;
            cell->animalCount = 0;
            cell->camelCount = 0;
            cell->lionCount = 0;
            cell->deerCount = 0;
            cell->rabbitCount = 0;
            cell->flag20000000TileCount = 0;
            cell->disturbedTileCount = 0;
            cell->panicSourceCount = 0;
            cell->farmlandTileCount = 0;
            cell->humanPlayerAreaTileCount = 0;
            cell->castlebuildings = 0;
            cell->heightSum = 0;
            for (int i = 0; i < 100; i++) {
                areaHistogram[i].area = -1;
                areaHistogram[i].count = 0;
            }
            for (int dy = 0; dy < 10; dy++) {
                unsigned int const tileY = dy + tileYBase;
                for (int dx = 0; dx < 10; dx++) {
                    unsigned int const x = dx + tileX;
                    if (x > 399 || tileY > 399
                        || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[tileY * 400 + x] == 0) {
                        continue;
                    }
                    cell->validTileCount++;
                    int const tile = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + dx + tileX;
                    int const area = (short)DAT_TileMapState::instance.PathConnectionLayer[tile];
                    if (area == 0) {
                        cell->unclaimedArea++;
                    }
                    for (int j = 0; j < 100; j++) {
                        if (areaHistogram[j].area == area) {
                            areaHistogram[j].count++;
                            break;
                        }
                        if (areaHistogram[j].area == -1) {
                            areaHistogram[j].area = area;
                            areaHistogram[j].count = 1;
                            break;
                        }
                    }
                    if (area != 0) {
                        if (area == campArea1) {
                            cell->humanPlayerAreaTileCount++;
                        }
                        if (area == campArea2) {
                            cell->humanPlayerAreaTileCount++;
                        }
                        if (area == campArea3) {
                            cell->humanPlayerAreaTileCount++;
                        }
                        if (area == campArea4) {
                            cell->humanPlayerAreaTileCount++;
                        }
                        if (area == campArea5) {
                            cell->humanPlayerAreaTileCount++;
                        }
                        if (area == campArea6) {
                            cell->humanPlayerAreaTileCount++;
                        }
                        if (area == campArea7) {
                            cell->humanPlayerAreaTileCount++;
                        }
                        if (area == campArea8) {
                            cell->humanPlayerAreaTileCount++;
                        }
                    }
                    cell->heightSum += DAT_TileMapState::instance.HeightLayer[tile];
                    int const logicFlags = DAT_TileMapState::instance.LogicLayer[tile];
                    if (logicFlags & 0x100) {
                        cell->wallTileCount++;
                        cell->castlebuildings++;
                    }
                    if (logicFlags & 0x20000000) {
                        cell->flag20000000TileCount++;
                    }
                    if (logicFlags & 0x20000) {
                        cell->disturbedTileCount++;
                    }
                    if (logicFlags & 0x80) {
                        cell->disturbedTileCount++;
                    }
                    if (logicFlags & 0x40000) {
                        cell->disturbedTileCount++;
                    }
                    if (logicFlags & 0x1000000) {
                        cell->farmlandTileCount++;
                    }
                    if (logicFlags & 0x2000000) {
                        cell->farmlandTileCount++;
                    }
                    int const treeID = DAT_TileMapState::instance.OrganismLayer[tile];
                    if (treeID > 0 && treeID < 2000) {
                        short const treeType = DAT_LandscapeState::instance.trees[treeID].treeType;
                        if (treeType == OpenSHC::Map::Trees::TT_CHESTNUT || treeType == OpenSHC::Map::Trees::TT_OAK
                            || treeType == OpenSHC::Map::Trees::TT_PINE || treeType == OpenSHC::Map::Trees::TT_BIRCH) {
                            cell->trees++;
                        }
                    }
                    int const buildingID = DAT_TileMapState::instance.BuildingLayer[tile];
                    if (buildingID != 0) {
                        short const buildingType = DAT_BuildingsState::instance.buildings[buildingID].buildingType;
                        if (buildingType == OpenSHC::Map::Buildings::BT_MANORHOUSE) {
                            cell->keeps++;
                        } else if (buildingType == OpenSHC::Map::Buildings::BT_STONEKEEP) {
                            cell->keeps++;
                        } else if (buildingType == OpenSHC::Map::Buildings::BT_STRONGHOLD) {
                            cell->keeps++;
                        } else if (buildingType == OpenSHC::Map::Buildings::BT_KEEPFOUR) {
                            cell->keeps++;
                        } else if (buildingType == OpenSHC::Map::Buildings::BT_KEEPFIVE) {
                            cell->keeps++;
                        } else if (buildingType == OpenSHC::Map::Buildings::BT_CAMPGROUND) {
                            cell->keeps++;
                        } else if (buildingType == OpenSHC::Map::Buildings::BT_GATEHOUSELARGE
                            || buildingType == OpenSHC::Map::Buildings::BT_GATEHOUSESMALL
                            || buildingType == OpenSHC::Map::Buildings::BT_WOODGATE1
                            || buildingType == OpenSHC::Map::Buildings::BT_WOODGATE2
                            || buildingType == OpenSHC::Map::Buildings::BT_DRAWBRIDGE
                            || buildingType == OpenSHC::Map::Buildings::BT_TOWER1
                            || buildingType == OpenSHC::Map::Buildings::BT_TOWER2
                            || buildingType == OpenSHC::Map::Buildings::BT_TOWER3
                            || buildingType == OpenSHC::Map::Buildings::BT_TOWER4
                            || buildingType == OpenSHC::Map::Buildings::BT_TOWER5) {
                            cell->castlebuildings++;
                        }
                        if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                            != OpenSHC::Map::Buildings::BT_SIGNPOST) {
                            cell->buildingTileCount++;
                        }
                    }
                    int const unitID = (short)DAT_TileMapState::instance.UnitLayer[tile];
                    if (unitID != 0) {
                        cell->unitCount++;
                        if (DAT_UnitsState::instance.units[unitID].isAnimalOrAmbient == 0) {
                            cell->humanCount++;
                            cell->panicSourceCount++;
                        } else {
                            cell->animalCount++;
                            short const unitType = DAT_UnitsState::instance.units[unitID].unitType;
                            if (unitType == OpenSHC::Map::Units::UT_ANTELOPESHDEER) {
                                cell->deerCount++;
                                if (DAT_TribesState::instance.tribes[DAT_UnitsState::instance.units[unitID].tribeID]
                                        .wildlifeAlarmTimer
                                    != 0) {
                                    cell->panicSourceCount++;
                                }
                            } else if (unitType == OpenSHC::Map::Units::UT_RABBIT) {
                                cell->rabbitCount++;
                            } else if (unitType == OpenSHC::Map::Units::UT_CAMELSHBEAR) {
                                cell->camelCount++;
                            } else if (unitType == OpenSHC::Map::Units::UT_LIONSHWOLF) {
                                cell->lionCount++;
                            }
                        }
                    }
                }
            }
            int bestArea = 0;
            int bestCount = 0;
            for (int j = 0; j < 100; j++) {
                if (areaHistogram[j].area == -1) {
                    break;
                }
                if (areaHistogram[j].count > bestCount) {
                    bestArea = areaHistogram[j].area;
                    bestCount = areaHistogram[j].count;
                }
            }
            cell->dominantPathAreaId = bestArea;
        }
    }

}
}
