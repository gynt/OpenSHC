#include "../NewEvent.func.hpp"

#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

#include "stdlib.h"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using UI::Enums::MenuModalType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004C0040
        void NewEvent::MenuItemActionHandler_NewEvent_Main(int param_1, ...)
        {
            char* _Str;
            long lVar1;
            switch (param_1) {
            case 0x13:
                MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::removeEventAtIndex,
                    DAT_MapPropertiesState::ptr)(DAT_MapPropertiesState::instance.currentEventID);
                goto LAB_004c006f;
            case 0x25:
                _Str = MACRO_CALL_MEMBER(
                    Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(0xb);
                lVar1 = atol(_Str);
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .header.year = lVar1;
            LAB_004c006f:
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NONE, FALSE);
                MACRO_CALL_MEMBER(
                    Map::MapPropertiesState_Func::sortEventsByDate, DAT_MapPropertiesState::ptr)();
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    0xf);
                return;
            case 100:
                DAT_MapPropertiesState::instance.invasionTroopIndex = 0;
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NEW_EVENT_CONDITION, FALSE);
                return;
            case 0x65:
                DAT_MapPropertiesState::instance.field127_0x145cc = 0;
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NEW_EVENT_ACTION, FALSE);
                break;
            case -1:
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .header.month
                    = DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                          .header.month
                    + 1;
                if (0xb
                    < DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .header.month) {
                    DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .header.month = 0;
                    return;
                }
            }
            return;
        }

    }
}
}
