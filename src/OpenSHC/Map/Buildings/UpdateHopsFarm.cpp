#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::GameMode;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00416630
    void Buildings::UpdateHopsFarm()
    {
        int* piVar1;
        short* psVar2;
        short sVar3;
        int iVar4;
        iVar4 = DAT_CurrentBuildingID::instance;
        sVar3 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        piVar1 = &DAT_GameState::instance.playerDataArray[sVar3].countFarms;
        *piVar1 = *piVar1 + 1;
        if (DAT_BuildingsState::instance.buildings[iVar4].workers[0] == 0) {
            piVar1 = &DAT_GameState::instance.playerDataArray[sVar3].farmsWithoutWorkers;
            *piVar1 = *piVar1 + 1;
        }
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(iVar4);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        iVar4 = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        psVar2 = &DAT_BuildingsState::instance.buildings[iVar4].growCounter;
        *psVar2 = *psVar2 + 1;
        if (400 < DAT_BuildingsState::instance.buildings[iVar4].growCounter) {
            DAT_BuildingsState::instance.buildings[iVar4].growCounter = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::growHops, DAT_BuildingsState::ptr)(iVar4);
        }
        MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::updateHopsFieldTileGraphics, DAT_BuildingsState::ptr)(iVar4);
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
            DAT_BuildingsState::instance.buildings[iVar4].displayOwnerFlag = 1;
            piVar1 = &DAT_BuildingsState::instance.buildings[iVar4].ownerFlagFrame;
            *piVar1 = *piVar1 + 1;
            if ((char)DAT_BuildingDefinedData::instance
                    .field177_0x7e1c[DAT_BuildingsState::instance.buildings[iVar4].ownerFlagFrame / 2]
                < '\x01') {
                DAT_BuildingsState::instance.buildings[iVar4].ownerFlagFrame = 0;
            }
            DAT_BuildingsState::instance.buildings[iVar4].field39_0x84
                = (int)(char)DAT_BuildingDefinedData::instance
                      .field177_0x7e1c[DAT_BuildingsState::instance.buildings[iVar4].ownerFlagFrame / 2];
        }
        DAT_BuildingsState::instance.buildings[iVar4].field39_0x84 = 0;
    }

}
}
