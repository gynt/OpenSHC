#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // buildingVariation is read before updateGateDrawBridgeOpenCloseLogic; +1 for map orientation 2/6, > 0x51 -> 0x50
    // (signed jle 0x424115). Phase 0 + gateState 10 -> phase 2; phase 2 + gateState 11 -> phase 0 (ID re-read after
    // updatePathLinkageTileMapRelatedToGates, 0x4241D6), and phase 2 always renders the door frame afterwards.
    // FUNCTION: STRONGHOLDCRUSADER 0x004240D0
    void Buildings::UpdateWoodGate1()
    {
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int variant = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingVariation;
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateGateDrawBridgeOpenCloseLogic,
            DAT_BuildingsState::ptr)();
        if (DAT_TileMapState::instance.mapOrientation == 2 || DAT_TileMapState::instance.mapOrientation == 6) {
            variant = variant + 1;
        }
        if (variant > 0x51) {
            variant = 0x50;
        }
        int buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[buildingID].showOverlays = 1;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame3 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame4 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame5 = 0;
        if (variant == 0x50) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0x28;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = 9;
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1 = 0x29;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame3 = 10;
        }
        byte phase = DAT_BuildingsState::instance.buildings[buildingID].gateOpenState;
        if (phase == 0) {
            if (DAT_BuildingsState::instance.buildings[buildingID].gateState == 10) {
                DAT_BuildingsState::instance.buildings[buildingID].gateOpenState = 2;
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToGates,
                    DAT_PathFindingState::ptr)(buildingID);
            }
        } else if (phase == 2) {
            if (DAT_BuildingsState::instance.buildings[buildingID].gateState == 0xb) {
                DAT_BuildingsState::instance.buildings[buildingID].gateOpenState = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToGates,
                    DAT_PathFindingState::ptr)(buildingID);
                buildingID = DAT_CurrentBuildingID::instance;
            }
            DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 1;
            DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 0;
            if (variant == 0x50) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame4 = 6;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame5 = 8;
            }
        }
    }

}
}
