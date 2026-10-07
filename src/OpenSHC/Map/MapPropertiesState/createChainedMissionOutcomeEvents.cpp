#include "../../Map.func.hpp"

#include "OpenSHC/Game/ScenarioEvents/InGameEventUnionVersion.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004BDA80
    void MapPropertiesState::createChainedMissionOutcomeEvents(int param_1)
    {
        InGameEventUnionVersion* pIVar1;
        int* piVar2;
        if (param_1 == 2) {
            this->currentEventID = this->eventsCount;
            pIVar1 = this->scenarioEvents + this->eventsCount;
            this->editedEventType = 3;
            this->eventsCount = this->eventsCount + 1;
            MACRO_CALL_MEMBER(
                Game::ScenarioEvents::InGameEventUnionVersion_Func::initializeScenarioEvent, pIVar1)();
            this->scenarioEvents[this->currentEventID].header.month = DAT_GameState::instance.mapAndTime.month + 1;
            this->scenarioEvents[this->currentEventID].header.year = DAT_GameState::instance.mapAndTime.year;
            if (0xb < this->scenarioEvents[this->currentEventID].header.month) {
                this->scenarioEvents[this->currentEventID].header.month
                    = this->scenarioEvents[this->currentEventID].header.month + -0xc;
                piVar2 = &this->scenarioEvents[this->currentEventID].header.year;
                *piVar2 = *piVar2 + 1;
            }
            this->scenarioEvents[this->currentEventID].data.scenario.ScenarioEventType = 1;
            *(undefined1*)((int)&this->scenarioEvents[this->currentEventID].data + 0x3f) = 1;
            this->currentEventID = this->eventsCount;
            pIVar1 = this->scenarioEvents + this->eventsCount;
            this->editedEventType = 3;
            this->eventsCount = this->eventsCount + 1;
            MACRO_CALL_MEMBER(
                Game::ScenarioEvents::InGameEventUnionVersion_Func::initializeScenarioEvent, pIVar1)();
            this->scenarioEvents[this->currentEventID].header.month = DAT_GameState::instance.mapAndTime.month + 1;
            this->scenarioEvents[this->currentEventID].header.year = DAT_GameState::instance.mapAndTime.year;
            if (0xb < this->scenarioEvents[this->currentEventID].header.month) {
                this->scenarioEvents[this->currentEventID].header.month
                    = this->scenarioEvents[this->currentEventID].header.month + -0xc;
                piVar2 = &this->scenarioEvents[this->currentEventID].header.year;
                *piVar2 = *piVar2 + 1;
            }
            *(undefined2*)((int)&this->scenarioEvents[this->currentEventID].data + 8) = 0;
            this->scenarioEvents[this->currentEventID].data.scenario.ScenarioEventType = 0;
            *(undefined1*)((int)&this->scenarioEvents[this->currentEventID].data + 0x1b) = 1;
        } else {
            if (param_1 != 1)
                goto LAB_004bde26;
            this->currentEventID = this->eventsCount;
            pIVar1 = this->scenarioEvents + this->eventsCount;
            this->editedEventType = 3;
            this->eventsCount = this->eventsCount + 1;
            MACRO_CALL_MEMBER(
                Game::ScenarioEvents::InGameEventUnionVersion_Func::initializeScenarioEvent, pIVar1)();
            this->scenarioEvents[this->currentEventID].header.month = DAT_GameState::instance.mapAndTime.month + 1;
            this->scenarioEvents[this->currentEventID].header.year = DAT_GameState::instance.mapAndTime.year;
            if (0xb < this->scenarioEvents[this->currentEventID].header.month) {
                this->scenarioEvents[this->currentEventID].header.month
                    = this->scenarioEvents[this->currentEventID].header.month + -0xc;
                piVar2 = &this->scenarioEvents[this->currentEventID].header.year;
                *piVar2 = *piVar2 + 1;
            }
            *(undefined2*)((int)&this->scenarioEvents[this->currentEventID].data + 8) = 0;
            this->scenarioEvents[this->currentEventID].data.scenario.ScenarioEventType = 1;
            *(undefined1*)((int)&this->scenarioEvents[this->currentEventID].data + 0x17) = 1;
            *(undefined1*)((int)&this->scenarioEvents[this->currentEventID].data + 0x3f) = 1;
            this->currentEventID = this->eventsCount;
            pIVar1 = this->scenarioEvents + this->eventsCount;
            this->editedEventType = 3;
            this->eventsCount = this->eventsCount + 1;
            MACRO_CALL_MEMBER(
                Game::ScenarioEvents::InGameEventUnionVersion_Func::initializeScenarioEvent, pIVar1)();
            this->scenarioEvents[this->currentEventID].header.month = DAT_GameState::instance.mapAndTime.month + 1;
            this->scenarioEvents[this->currentEventID].header.year = DAT_GameState::instance.mapAndTime.year;
            if (0xb < this->scenarioEvents[this->currentEventID].header.month) {
                this->scenarioEvents[this->currentEventID].header.month
                    = this->scenarioEvents[this->currentEventID].header.month + -0xc;
                piVar2 = &this->scenarioEvents[this->currentEventID].header.year;
                *piVar2 = *piVar2 + 1;
            }
            *(undefined2*)((int)&this->scenarioEvents[this->currentEventID].data + 8) = 0;
            this->scenarioEvents[this->currentEventID].data.scenario.ScenarioEventType = 0;
        }
        *(undefined1*)((int)&this->scenarioEvents[this->currentEventID].data + 0x4b) = 1;
    LAB_004bde26:
        MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::sortEventsByDate, this)();
    }

}
}
