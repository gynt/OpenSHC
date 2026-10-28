#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // hovelVisualStyle (int in the header) is read as a sign-extended word (movsx at 0x410CB7). The building ID is
    // re-read from DAT_CurrentBuildingID after updateBuildingGraphicsLayer (0x410CE0) and for addBuildingInRegistry.
    // FUNCTION: STRONGHOLDCRUSADER 0x00410CA0
    void Buildings::UpdateHovel()
    {
        int buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[buildingID].spriteID = DAT_BuildingDefinedData::instance
            .SomeSpriteArray1[(short)DAT_BuildingsState::instance.buildings[buildingID].hovelVisualStyle];
        if (DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState == -1) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                buildingID);
            buildingID = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState = 0;
        }
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
    }

}
}
