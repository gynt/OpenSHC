#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
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

    // FUNCTION: STRONGHOLDCRUSADER 0x004113C0
    void Buildings::UpdateMercenaryPost()
    {
        int* piVar1;
        int iVar2;
        iVar2 = DAT_CurrentBuildingID::instance;
        piVar1 = &DAT_GameState::instance
                      .playerDataArray[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner]
                      .someCount04;
        *piVar1 = *piVar1 + 5;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(iVar2);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        iVar2 = DAT_CurrentBuildingID::instance;
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 1;
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
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field39_0x84 = 0;
    }

}
}
