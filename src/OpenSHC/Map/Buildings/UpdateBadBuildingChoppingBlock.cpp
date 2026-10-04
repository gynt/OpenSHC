#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00419370
    void Buildings::UpdateBadBuildingChoppingBlock()
    {
        int* piVar1;
        byte bVar2;
        short sVar3;
        int iVar4;
        int iVar5;
        iVar5 = DAT_CurrentBuildingID::instance;
        sVar3 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].playerColorUnk = 0;
        MACRO_CALL_MEMBER(AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(iVar5);
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        iVar5 = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[iVar5].field66_0xbe = 0;
        piVar1 = &DAT_BuildingsState::instance.buildings[iVar5].field28_0x58;
        *piVar1 = *piVar1 + 1;
        if (1 < DAT_BuildingsState::instance.buildings[iVar5].field28_0x58) {
            iVar4 = DAT_GameState::instance.playerDataArray[sVar3].fearFactorLevel;
            DAT_BuildingsState::instance.buildings[iVar5].field28_0x58 = 0;
            DAT_BuildingsState::instance.buildings[iVar5].displayOwnerFlag = (uint)(iVar4 < -3);
            piVar1 = &DAT_BuildingsState::instance.buildings[iVar5].campgroundVclock;
            *piVar1 = *piVar1 + 1;
            bVar2 = DAT_BuildingDefinedData::instance
                        .field165_0x7884[DAT_BuildingsState::instance.buildings[iVar5].campgroundVclock];
            DAT_BuildingsState::instance.buildings[iVar5].field20_0x38 = (int)(char)bVar2;
            if ((char)bVar2 < 1) {
                DAT_BuildingsState::instance.buildings[iVar5].campgroundVclock = 0;
                DAT_BuildingsState::instance.buildings[iVar5].field20_0x38 = 1;
            }
        }
    }

}
}
