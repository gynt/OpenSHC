#include "../../Map.func.hpp"

#include "OpenSHC/Game/ScenarioEvents/InGameEventUnionVersion.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004BD980
    void MapPropertiesState::createScenarioEventForNextMonth()
    {
        int* piVar1;
        InGameEventUnionVersion* _ptrEvent;
        this->currentEventID = this->eventsCount;
        _ptrEvent = this->scenarioEvents + this->eventsCount;
        this->field50_0x13568 = 3;
        this->eventsCount = this->eventsCount + 1;
        MACRO_CALL_MEMBER(
            OpenSHC::Game::ScenarioEvents::InGameEventUnionVersion_Func::initializeScenarioEvent, _ptrEvent)();
        this->scenarioEvents[this->currentEventID].header.month = DAT_GameState::instance.mapAndTime.month + 1;
        this->scenarioEvents[this->currentEventID].header.year = DAT_GameState::instance.mapAndTime.year;
        if (0xb < this->scenarioEvents[this->currentEventID].header.month) {
            this->scenarioEvents[this->currentEventID].header.month
                = this->scenarioEvents[this->currentEventID].header.month + -0xc;
            piVar1 = &this->scenarioEvents[this->currentEventID].header.year;
            *piVar1 = *piVar1 + 1;
        }
        *(undefined2*)((int)&this->scenarioEvents[this->currentEventID].data + 8) = 0;
        this->scenarioEvents[this->currentEventID].data.scenario.ScenarioEventType = 1;
        *(undefined1*)((int)&this->scenarioEvents[this->currentEventID].data + 0x17) = 1;
        MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::sortEventsByDate, this)();
    }

}
}
