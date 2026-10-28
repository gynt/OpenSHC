#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {

    // Pending start gold (pendingResources[15]) moves into currentResources[15] every 4th tick in chunks of
    // 1 / 10 / 100 (signed compares against 0, 100 and 1000).
    // FUNCTION: STRONGHOLDCRUSADER 0x004179B0
    void Buildings::UpdateKeepStoneKeep()
    {
        int owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentHealth
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].maxHealth;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].accessTileX
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x + 3;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].accessTileY
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y + 2;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].showOverlays = 1;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame0 = 0x18;
        if (((byte)DAT_GameCore::instance.mapTimeInTicks & 3) == 0 && DAT_GameCore::instance.gameMode_2 != Game::GM_EDITOR
            && DAT_GameCore::instance.gameMode_2 != Game::GM_SIEGE_THAT) {
            int pending = DAT_GameState::instance.playerDataArray[owner].pendingResources[15];
            if (pending > 0) {
                int chunk = 1;
                if (pending > 1000) {
                    chunk = 100;
                } else if (pending > 100) {
                    chunk = 10;
                }
                DAT_GameState::instance.playerDataArray[owner].pendingResources[15] = pending - chunk;
                DAT_GameState::instance.playerDataArray[owner].currentResources[15] += chunk;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].deliveryActivityCountdown = 100;
                DAT_GameState::instance.playerDataArray[owner].beforeLastMonthsGold
                    = (short)DAT_GameState::instance.playerDataArray[owner].currentResources[15];
                DAT_GameState::instance.playerDataArray[owner].lastMonthsGold
                    = (short)DAT_GameState::instance.playerDataArray[owner].currentResources[15];
                DAT_GameCore::instance.countdown = 1;
            }
        }
    }

}
}
