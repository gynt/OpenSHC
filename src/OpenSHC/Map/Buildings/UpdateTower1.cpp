#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // damageCount = 9 - currentHealth * 9 / maxHealth (signed idiv at 0x418D6D), clamped to 8 (jle at 0x418D7D);
    // 0 skips the overlay copy (je at 0x418D86), negative copies the zeroed slots. Slot seed = randomSeed >> 8
    // (sar). The unit rescan runs when the signed short countdown reaches 0 (jle 0x418E0F, jne 0x418E22) and
    // re-reads DAT_CurrentBuildingID each iteration; the final roof check uses that re-read ID.
    // FUNCTION: STRONGHOLDCRUSADER 0x00418C80
    void Buildings::UpdateTower1()
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
        tower->overlayFrame0 = 0x7d;
        tower->overlayFrame5 = 0x7c;
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
        int damageOverlays[8] = { 0 };
        tower->overlayFrame15 = 0;
        int damageCount = 9
            - (DAT_BuildingsState::instance.buildings[buildingID].currentHealth * 9)
                / DAT_BuildingsState::instance.buildings[buildingID].maxHealth;
        if (damageCount > 8) {
            damageCount = 8;
        } else if (damageCount == 0) {
            goto checkUnitsOnTop;
        }
        for (int i = 0; i < damageCount; i++) {
            damageOverlays[((DAT_BuildingsState::instance.buildings[buildingID].randomSeed >> 8) + i) & 7]
                = ((DAT_BuildingsState::instance.buildings[buildingID].randomSeed + i) & 0xf) + 1;
        }
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame8 = damageOverlays[0];
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame9 = damageOverlays[1];
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame10 = damageOverlays[2];
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame11 = damageOverlays[3];
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame12 = damageOverlays[4];
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 = damageOverlays[5];
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame14 = damageOverlays[6];
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame15 = damageOverlays[7];
    checkUnitsOnTop:
        if (DAT_BuildingsState::instance.buildings[buildingID].unitsOnTopRecheckCountdown > 0) {
            if (--DAT_BuildingsState::instance.buildings[buildingID].unitsOnTopRecheckCountdown == 0) {
                int tileIndex = 0;
                short unitsOnTop = 0;
                do {
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData,
                        DAT_TileMapState::ptr)(tileIndex, 3);
                    buildingID = DAT_CurrentBuildingID::instance;
                    if (DAT_TileMapState::instance.UnitLayer
                            [DAT_ViewportRenderState::instance
                                    .translationMatrix[DAT_BuildingsState::instance.buildings[buildingID].y
                                        + DAT_TileMapState::instance.buildingY]
                                    .addXgetTile
                                + DAT_BuildingsState::instance.buildings[buildingID].x
                                + DAT_TileMapState::instance.buildingX]
                        != 0) {
                        unitsOnTop = 1;
                        break;
                    }
                    tileIndex += 1;
                } while (tileIndex < DAT_TileMapState::instance.constructionTileCount);
                DAT_BuildingsState::instance.buildings[buildingID].hasUnitsOntop = unitsOnTop;
                DAT_BuildingsState::instance.buildings[buildingID].unitsOnTopRecheckCountdown = 100;
            }
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].hasUnitsOntop != 0) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame5 = 0x7e;
        }
    }

}
}
