#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::GameMode;
    using OpenSHC::Map::Units::States::UnitState;

    // FUNCTION: STRONGHOLDCRUSADER 0x00415A80
    void Buildings::UpdateApothecary()
    {
        int* piVar1;
        int iVar2;
        int iVar3;
        iVar2 = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(iVar2);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        iVar2 = DAT_CurrentBuildingID::instance;
        iVar3 = (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[0];
        if ((iVar3 == 0) || (DAT_UnitsState::instance.units[iVar3].state.generic != ((UnitState)2))) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive = 0;
            DAT_BuildingsState::instance.buildings[iVar2].renderAnimation = 0;
            DAT_BuildingsState::instance.buildings[iVar2].animationIndex = 0;
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive = 1;
            DAT_BuildingsState::instance.buildings[iVar2].renderAnimation = 1;
        }
        MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::updateVisuallyActiveState, DAT_BuildingsState::ptr)(iVar2);
        DAT_BuildingsState::instance.buildings[iVar2].animationIncrement = 1;
        if ((char)DAT_BuildingDefinedData::instance
                .field171_0x7bd4[DAT_BuildingsState::instance.buildings[iVar2].animationIndex]
            < '\0') {
            DAT_BuildingsState::instance.buildings[iVar2].animationIndex = 0;
            piVar1 = &DAT_BuildingsState::instance.buildings[iVar2].field13_0x28;
            *piVar1 = *piVar1 + 1;
            DAT_BuildingsState::instance.buildings[iVar2].field14_0x2c = 1;
        } else {
            DAT_BuildingsState::instance.buildings[iVar2].field14_0x2c = 0;
        }
        DAT_BuildingsState::instance.buildings[iVar2].animationFrame
            = (int)(char)DAT_BuildingDefinedData::instance
                  .field171_0x7bd4[DAT_BuildingsState::instance.buildings[iVar2].animationIndex];
        if (DAT_BuildingsState::instance.buildings[iVar2].buildingIsVisuallyActive
            != DAT_BuildingsState::instance.buildings[iVar2].oldVisualActiveState) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                iVar2);
            iVar2 = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
            DAT_BuildingsState::instance.buildings[iVar2].displayOwnerFlag = 1;
            piVar1 = &DAT_BuildingsState::instance.buildings[iVar2].ownerFlagFrame;
            *piVar1 = *piVar1 + 1;
            if ((char)DAT_BuildingDefinedData::instance
                    .field177_0x7e1c[DAT_BuildingsState::instance.buildings[iVar2].ownerFlagFrame / 2]
                < '\x01') {
                DAT_BuildingsState::instance.buildings[iVar2].ownerFlagFrame = 0;
            }
            DAT_BuildingsState::instance.buildings[iVar2].field39_0x84
                = (int)(char)DAT_BuildingDefinedData::instance
                      .field177_0x7e1c[DAT_BuildingsState::instance.buildings[iVar2].ownerFlagFrame / 2];
        }
        DAT_BuildingsState::instance.buildings[iVar2].field39_0x84 = 0;
    }

}
}
