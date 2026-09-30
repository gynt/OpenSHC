#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::DE::SHCDE::eSFX;
    using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
    using OpenSHC::UI::Enums::MenuViewType;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00418640
    void Buildings::UpdateBadBuildingStocks()
    {
        byte bVar1;
        short sVar2;
        int iVar3;
        sVar2 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        iVar3 = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].playerColorUnk = 0;
        DAT_BuildingsState::instance.buildings[iVar3].field66_0xbe = 0;
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateBuildingSignpostCounter,
            DAT_BuildingsState::ptr)(iVar3, 1);
        DAT_BuildingsState::instance.buildings[iVar3].renderAnimation
            = (ushort)(DAT_GameState::instance.playerDataArray[sVar2].fearFactorLevel < -1);
        bVar1 = DAT_BuildingDefinedData::instance
                    .field159_0x7624[DAT_BuildingsState::instance.buildings[iVar3].animationIndex];
        DAT_BuildingsState::instance.buildings[iVar3].animationFrame = (int)(char)bVar1;
        if ((char)bVar1 < 1) {
            DAT_BuildingsState::instance.buildings[iVar3].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[iVar3].animationFrame = 1;
        }
        if ((((DAT_BuildingsState::instance.buildings[iVar3].animationActive != 0)
                 && (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU))
                && (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_STOCKS))
            && ((iVar3 == DAT_BuildingsState::instance.menuSelectedBuildingID
                && (DAT_BuildingsState::instance.buildings[iVar3].animationIndex == 5)))) {
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                (int)(short)DAT_BuildingsState::instance.buildings[iVar3].x,
                (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar3].y)), OpenSHC::DE::SHCDE::FX_STOCKS);
        }
    }

}
}
