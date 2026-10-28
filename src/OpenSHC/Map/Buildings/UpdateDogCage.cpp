#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState_DogUnit.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // The building ID is read once after addBuildingInRegistry (0x420A44) and kept for the whole function (also
    // after updateWorkshopProgressSign). A dog slot counts when its ID is nonzero and the stored UID matches the
    // unit's UID; it is waiting when its state is USDU_WAITING_IN_CAGE (0xD2). dogCageFrames entries are signed
    // bytes (movsx, jg at 0x420B9E).
    // FUNCTION: STRONGHOLDCRUSADER 0x00420A30
    void Buildings::UpdateDogCage()
    {
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int buildingID = DAT_CurrentBuildingID::instance;
        DAT_GameState::instance.playerDataArray[DAT_BuildingsState::instance.buildings[buildingID].owner].dogCageCount
            += 1;
        int linked = 0;
        int waiting = 0;
        for (int slot = 0; slot < 4; slot++) {
            int dogID = DAT_BuildingsState::instance.buildings[buildingID].insideUnitIDs[slot];
            if (dogID != 0
                && DAT_BuildingsState::instance.buildings[buildingID].insideUnitUIDs[slot]
                    == DAT_UnitsState::instance.units[dogID].uid) {
                linked = linked + 1;
                if (DAT_UnitsState::instance.units[dogID].state.dog == OpenSHC::Map::Units::States::USDU_WAITING_IN_CAGE) {
                    waiting = waiting + 1;
                }
            }
        }
        if (linked != 0) {
            if (waiting != 0) {
                DAT_BuildingsState::instance.buildings[buildingID].showOverlays = 0;
                DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateWorkshopProgressSign,
                    DAT_BuildingsState::ptr)(buildingID, 1);
                DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 1;
                int frame = (char)DAT_BuildingDefinedData::instance
                                .dogCageFrames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame;
                if (frame <= 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].animationIndex = 0;
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 1;
                }
                return;
            }
            DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 0;
            DAT_BuildingsState::instance.buildings[buildingID].showOverlays = 0;
            return;
        }
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[buildingID].showOverlays = 0;
        DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(
            buildingID);
    }

}
}
