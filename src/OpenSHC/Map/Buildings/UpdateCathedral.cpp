#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
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

    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::GameMode2;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004177E0
    void Buildings::UpdateCathedral()
    {
        int* piVar1;
        int buildingID;
        bool bVar2;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        buildingID = DAT_CurrentBuildingID::instance;
        bVar2 = DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        if (bVar2) {
            DAT_BuildingsState::instance.buildings[buildingID].field39_0x84 = 0;
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag = 1;
            piVar1 = &DAT_BuildingsState::instance.buildings[buildingID].ownerFlagFrame;
            *piVar1 = *piVar1 + 1;
            if ((char)DAT_BuildingDefinedData::instance
                    .field177_0x7e1c[DAT_BuildingsState::instance.buildings[buildingID].ownerFlagFrame / 2]
                < '\x01') {
                DAT_BuildingsState::instance.buildings[buildingID].ownerFlagFrame = 0;
            }
            DAT_BuildingsState::instance.buildings[buildingID].field39_0x84
                = (int)(char)DAT_BuildingDefinedData::instance
                      .field177_0x7e1c[DAT_BuildingsState::instance.buildings[buildingID].ownerFlagFrame / 2];
        }
        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION)
            && (DAT_GameCore::instance.missionNumber1to20 == 7)) {
            if ((DAT_BuildingsState::instance.buildings[buildingID].maxHealth * 3) / 10
                < (int)DAT_BuildingsState::instance.buildings[buildingID].currentHealth) {
                DAT_BuildingsState::instance.buildings[buildingID].field249_0x2da = 0;
            } else if ((DAT_BuildingsState::instance.buildings[buildingID].field249_0x2da == 0)
                || (DAT_BuildingsState::instance.buildings[buildingID].spriteID != 0x11f)) {
                DAT_BuildingsState::instance.buildings[buildingID].field249_0x2da = 1;
                DAT_BuildingsState::instance.buildings[buildingID].spriteID = 0x11f;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                    buildingID);
            }
        }
    }

}
}
