#include "OpenSHC/Synchrony/Actions.func.hpp"

#include "OpenSHC/Audio/MissingResourceState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Audio/SFX/ResourceLackSFX.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MissingResourceState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // wood < requiredWood and stone < requiredStone are signed (jle 0x46629F, jle 0x4662C5). The return value
    // of updateRepairCostAndReturnIfDamaged is not used (0x466284).
    // FUNCTION: STRONGHOLDCRUSADER 0x00466260
    void Actions::ProcessTowerRepair(int playerID, int buildingID, int requiredWood, int requiredStone, int gameObjectID)
    {
        if (DAT_BuildingsState::instance.buildings[buildingID].uid == gameObjectID) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateRepairCostAndReturnIfDamaged,
                DAT_BuildingsState::ptr)(buildingID);
            if (requiredWood > DAT_GameState::instance.playerDataArray[playerID].currentResources[OpenSHC::Game::Resources::RT_WOOD]) {
                if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::MissingResourceState_Func::playResourceLackSFX,
                        DAT_MissingResourceState::ptr)(1, OpenSHC::Audio::SFX::RLSFX_WOOD);
                }
            } else if (requiredStone > DAT_GameState::instance.playerDataArray[playerID].currentResources[OpenSHC::Game::Resources::RT_STONE]) {
                if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::MissingResourceState_Func::playResourceLackSFX,
                        DAT_MissingResourceState::ptr)(1, OpenSHC::Audio::SFX::RLSFX_STONE);
                }
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].currentHealth
                    = DAT_BuildingsState::instance.buildings[buildingID].maxHealth;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss,
                    DAT_BuildingsState::ptr)(playerID, OpenSHC::Game::Resources::RT_WOOD, requiredWood, 0);
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss,
                    DAT_BuildingsState::ptr)(playerID, OpenSHC::Game::Resources::RT_STONE, requiredStone, 0);
            }
        }
    }

}
}
