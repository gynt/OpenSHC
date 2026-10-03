#include "../../Map.func.hpp"
#include "../MapPropertiesState.func.hpp"

#include "OpenSHC/Game/GameMode2.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::GameMode2;

    // FUNCTION: STRONGHOLDCRUSADER 0x004B7AB0
    int MapPropertiesState::getDifficultyMultipliedValue(int param_1)
    {
        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION)
            && (DAT_GameCore::instance.missionNumber1to20 == 8)) {
            return param_1;
        }
        return (DAT_MissionAestheticsDefinedData::instance
                       .DifficultyEventMultipliers[DAT_GameState::instance.mapAndTime.difficulty]
                   * param_1)
            / 100;
    }

}
}
