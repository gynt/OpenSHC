#include "../../Map.func.hpp"

#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/Game/ScenarioEvents/InGameEventUnionVersion.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace Map {

    using Game::ScenarioEvents::InGameEventUnionVersion;

    // FUNCTION: STRONGHOLDCRUSADER 0x004BEB20
    void MapPropertiesState::updateEventYearsAndCommitBuildingAvailability()
    {
        char local_10[12];
        uint local_4;
        local_4 = MSVC_SecurityCookie::instance ^ (uint)local_10;
        if (this->SEC_StartingYear < 1000) {
            this->SEC_StartingYear = 1181;
        }
        MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(10);
        MACRO_CALL(OS_Func::_sprintf)(local_10, "%d", this->SEC_StartingYear);
        MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(
            local_10);
        this->field48_0x13560 = -1;
        this->field47_0x1355c = 0;
        this->year_copy = this->SEC_StartingYear;
        for (int eventIndex = 0; eventIndex < this->eventsCount; ++eventIndex) {
            InGameEventUnionVersion& event = this->scenarioEvents[eventIndex];
            int const eventYear = event.header.year;
            if ((eventYear <= DAT_GameState::instance.mapAndTime.year)
                && ((DAT_GameState::instance.mapAndTime.year != eventYear)
                    || (DAT_GameState::instance.mapAndTime.month < event.header.month))
                && (event.header.tl_type == 1) && (event.data.invasion.messageYear)) {
                if (!event.data.invasion.messageMonth) {
                    event.data.invasion.messageMonth = eventYear;
                } else {
                    event.header.year = event.data.invasion.messageMonth;
                }
            }
        }
        MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::commitBuildingAvailability, this)();
        ;
    }

}
}
