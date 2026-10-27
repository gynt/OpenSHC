#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::GameMode2;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00500BB0
    void TileMapState::setSignpostDistanceForCampaignMission()
    {
        DAT_GameState::instance.mapAndTime.signpostExclusionRadius = 30;
        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION) {
            if (DAT_GameCore::instance.missionNumber <= 2) {
                DAT_GameState::instance.mapAndTime.signpostExclusionRadius = 0;
                return;
            }
            if (DAT_GameCore::instance.missionNumber <= 4) {
                DAT_GameState::instance.mapAndTime.signpostExclusionRadius = 15;
                return;
            }
            if (DAT_GameCore::instance.missionNumber == 6) {
                DAT_GameState::instance.mapAndTime.signpostExclusionRadius = 37;
            }
            return;
        }

        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_ECONOMIC_CAMPAIGN_SH1
            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CUSTOM_MAP
                && (int)DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 >= 2)) {
            DAT_GameState::instance.mapAndTime.signpostExclusionRadius = 7;
        }
    }

}
}
