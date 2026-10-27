#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // buildingProgress recomputes the entrance flags at >= 40 (jl 0x41E92E). damageCount = 9 - currentHealth * 9 /
    // maxHealth (signed idiv 0x41E9AF), clamped to 8 (jle 0x41E9BF); 0 skips the copy (je 0x41E9CA). Slot seed =
    // randomSeed >> 8 (sar). The tile refresh loop is a do-while (first tile handled even when
    // constructionTileCount <= 0, jl at 0x41EAE8 only at the bottom); mapOrientation / 2 is signed (cdq; sar).
    // FUNCTION: STRONGHOLDCRUSADER 0x0041E870
    void Buildings::UpdateTower2()
    {
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int buildingID = DAT_CurrentBuildingID::instance;
        OpenSHC::Map::Buildings::Building* tower = &DAT_BuildingsState::instance.buildings[buildingID];
        tower->renderAnimation = 1;
        tower->showOverlays = 1;
        tower->animationFrame = 0;
        tower->accessTileX
            = DAT_BuildingsState::instance.buildings[buildingID].x + 1;
        tower->accessTileY
            = DAT_BuildingsState::instance.buildings[buildingID].y + 1;
        tower->overlayFrame0 = 1;
        tower->overlayFrame1 = 0;
        tower->overlayFrame2 = 0;
        tower->overlayFrame3 = 0;
        tower->overlayFrame4 = 0;
        tower->overlayFrame8 = 0;
        tower->overlayFrame9 = 0;
        tower->overlayFrame10 = 0;
        tower->overlayFrame11 = 0;
        tower->overlayFrame12 = 0;
        tower->overlayFrame13 = 0;
        tower->overlayFrame14 = 0;
        tower->overlayFrame15 = 0;
        int* progressPtr = &DAT_BuildingsState::instance.buildings[buildingID].buildingProgress;
        *progressPtr = *progressPtr + 1;
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingProgress >= 40) {
            DAT_BuildingsState::instance.buildings[buildingID].buildingProgress = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeBuildingEntranceFlagsForOrientations,
                DAT_BuildingsState::ptr)(buildingID);
        }
        if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasBuildingExitFlagForOrientation,
                DAT_BuildingsState::ptr)(buildingID)
            != 0) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1 = 0x51;
            DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 1;
        }
        if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasBuildingEntranceFlagForOrientation,
                DAT_BuildingsState::ptr)(buildingID)
            != 0) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame3 = 0x5a;
            DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 1;
        }
        int damageDecals[8] = { 0 };
        int damageCount = 9
            - (DAT_BuildingsState::instance.buildings[buildingID].currentHealth * 9)
                / DAT_BuildingsState::instance.buildings[buildingID].maxHealth;
        if (damageCount > 8) {
            damageCount = 8;
        } else if (damageCount == 0) {
            goto refreshTiles;
        }
        for (int i = 0; i < damageCount; i++) {
            damageDecals[((DAT_BuildingsState::instance.buildings[buildingID].randomSeed >> 8) + i) & 7]
                = ((DAT_BuildingsState::instance.buildings[buildingID].randomSeed + i) & 0xf) + 1;
        }
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame8 = damageDecals[0];
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame9 = damageDecals[1];
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame10 = damageDecals[2];
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame11 = damageDecals[3];
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame12 = damageDecals[4];
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 = damageDecals[5];
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame14 = damageDecals[6];
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame15 = damageDecals[7];
    refreshTiles:
        if (DAT_BuildingsState::instance.towerTilesRefreshPending != 0) {
            int tileIndex = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData,
                    DAT_TileMapState::ptr)(tileIndex, 4);
                int tile = DAT_ViewportRenderState::instance
                               .translationMatrix[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y
                                   + DAT_TileMapState::instance.buildingY]
                               .addXgetTile
                    + DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x
                    + DAT_TileMapState::instance.buildingX;
                DAT_TileMapState::instance.MiscDisplayLayer[tile] &= 0xffef;
                int* vanishTile = DAT_BuildingDefinedData::instance.tower2VanishTilesByOrientation
                    + (DAT_TileMapState::instance.mapOrientation / 2) * 4;
                for (int j = 0; j < 4; j++) {
                    if (*vanishTile == tileIndex) {
                        DAT_TileMapState::instance.MiscDisplayLayer[tile] |= 0x10;
                        break;
                    }
                    vanishTile++;
                }
                tileIndex += 1;
            } while (tileIndex < DAT_TileMapState::instance.constructionTileCount);
        }
    }

}
}
