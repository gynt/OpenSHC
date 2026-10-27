#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // Campaign mission 7: the damaged sprite 0x11F is applied once health <= maxHealth * 3 / 10 (signed idiv).
    // FUNCTION: STRONGHOLDCRUSADER 0x004177E0
    void Buildings::UpdateCathedral()
    {
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int buildingID = DAT_CurrentBuildingID::instance;
        bool isNotSolitary = DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY;
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 0;
        if (isNotSolitary) {
            int* showOverlaysPtr = &DAT_BuildingsState::instance.buildings[buildingID].showOverlays;
            *showOverlaysPtr = 1;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 += 1;
            if ((char)DAT_BuildingDefinedData::instance
                    .ownerFlagFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 / 2]
                <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 = 0;
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame14 = (char)DAT_BuildingDefinedData::instance
                .ownerFlagFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 / 2];
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame14 = 0;
        }
        if (DAT_GameCore::instance.gameMode_2 == Game::GM_CAMPAIGN_MISSION && DAT_GameCore::instance.missionNumber == 7) {
            if (DAT_BuildingsState::instance.buildings[buildingID].currentHealth
                <= DAT_BuildingsState::instance.buildings[buildingID].maxHealth * 3 / 10) {
                if (DAT_BuildingsState::instance.buildings[buildingID].damagedSpriteShown == 0
                    || DAT_BuildingsState::instance.buildings[buildingID].spriteID != 0x11f) {
                    DAT_BuildingsState::instance.buildings[buildingID].damagedSpriteShown = 1;
                    DAT_BuildingsState::instance.buildings[buildingID].spriteID = 0x11f;
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer,
                        DAT_TileMapState::ptr)(buildingID);
                    return;
                }
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].damagedSpriteShown = 0;
            }
        }
    }

}
}
