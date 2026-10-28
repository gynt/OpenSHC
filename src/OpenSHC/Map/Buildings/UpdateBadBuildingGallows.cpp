#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // The owner is read before the two registration calls. fear < -2: animated, not visually active;
    // -2..-1: visually active; >= 0: neither.
    // FUNCTION: STRONGHOLDCRUSADER 0x00418530
    void Buildings::UpdateBadBuildingGallows()
    {
        int owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0;
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateWorkshopProgressSign,
            DAT_BuildingsState::ptr)(buildingID, 1);
        int fear = DAT_GameState::instance.playerDataArray[owner].fearFactorLevel;
        if (fear <= -3) {
            DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 1;
            DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 0;
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 0;
            if (fear <= -1) {
                DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 1;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 0;
            }
        }
        DAT_BuildingsState::instance.buildings[buildingID].spriteOffetX = -0x23;
        DAT_BuildingsState::instance.buildings[buildingID].spriteOffetY = -0x6d;
        int frame = (char)DAT_BuildingDefinedData::instance
                        .gallowsFrames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
        DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame;
        if (frame <= 0) {
            DAT_BuildingsState::instance.buildings[buildingID].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 1;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive
            != DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                buildingID);
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive;
        }
    }

}
}
