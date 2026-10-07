#include "../../Map.func.hpp"
#include "../MapPropertiesState.func.hpp"

#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/ScenarioEvents/IngameScenarioEventItemContent.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Map {

    using Game::GameMode2;
    using Game::ScenarioEvents::IngameScenarioEventItemContent;

    // FUNCTION: STRONGHOLDCRUSADER 0x004B78D0
    int MapPropertiesState::getEventIDForTimeUntilDefeatEventType()
    {
        if (((DAT_GameCore::instance.gameMode_2 != Game::GM_CAMPAIGN_MISSION)
                && (DAT_GameCore::instance.gameMode_2 != Game::GM_ECONOMIC_CAMPAIGN_SH1))
            && (DAT_GameCore::instance.gameMode_2 != Game::GM_BUILDERUnk)) {
            return -1;
        }
        for (int _eventID = 0; _eventID < this->eventsCount; _eventID++) {
            if ((this->scenarioEvents[_eventID].header.tl_type == 3)
                && ((this->scenarioEvents[_eventID].data.scenario.ScenarioEventType == 1)
                    || (this->scenarioEvents[_eventID].data.scenario.ScenarioEventType == 0x1b))
                && (this->scenarioEvents[_eventID].data.scenario.conditions[0].enabled != 0)) {
                return _eventID;
            }
        }
        return -1;
    }

}
}
