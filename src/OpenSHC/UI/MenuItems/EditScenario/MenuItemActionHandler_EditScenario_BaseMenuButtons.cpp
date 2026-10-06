#include "../EditScenario.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/ScenarioEvents/InGameEventUnionVersion.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CopyOfScenarioGold.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_StopHandlingMenuItems.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "stdlib.h"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using Map::MapType2;
        using UI::Enums::MenuModalType;
        using UI::Enums::MenuViewType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004B8220
        void EditScenario::MenuItemActionHandler_EditScenario_BaseMenuButtons(int param_1, ...)
        {
            char* pcVar1;
            InGameEventUnionVersion* pIVar2;
            char local_10[12];
            uint local_4;
            local_4 = MSVC_SecurityCookie::instance ^ (uint)local_10;
            if (DAT_MenuModalComposition1::instance.activeModalDialogID != UI::Enums::MMT_NONE)
                goto switchD_004b8254_caseD_0;
            switch (param_1) {
            case 3:
                pcVar1 = MACRO_CALL_MEMBER(
                    Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(10);
                DAT_MapPropertiesState::instance.SEC_StartingYear = atol(pcVar1);
                if (DAT_MapPropertiesState::instance.year_copy != DAT_MapPropertiesState::instance.SEC_StartingYear) {
                    DAT_GameState::instance.mapAndTime.month = DAT_MapPropertiesState::instance.SEC_StartingMonth;
                    DAT_GameState::instance.mapAndTime.year = DAT_MapPropertiesState::instance.SEC_StartingYear;
                }
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_MAP_EDITOR_PROPERTIES, 0);
                ;
                return;
            case 0x26:
                if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 != Map::MT_SIEGE) {
                    DAT_MapPropertiesState::instance.indexStored = 0;
                    MACRO_CALL_MEMBER(
                        Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(9);
                    MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_TRADER_SETTINGS, FALSE);
                    ;
                    return;
                }
                goto LAB_004b82b4;
            case 0x29:
                if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == Map::MT_SIEGE) {
                    DAT_MapPropertiesState::instance.indexStored = 0x14;
                    MACRO_CALL_MEMBER(
                        Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(0xc);
                    MACRO_CALL(OS_Func::_sprintf)(local_10, "%d",
                        DAT_MapPropertiesState::instance
                            .SEC_StartingResources[DAT_MapPropertiesState::instance.indexStored + 5]);
                    MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray,
                        DAT_UserTextHandlerState::ptr)(local_10);
                    MACRO_CALL_MEMBER(
                        Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(9);
                    DAT_MapPropertiesState::instance.DAT_MapEditorUnitPointsSum = MACRO_CALL_MEMBER(
                        Map::MapPropertiesState_Func::sumUnitPoints, DAT_MapPropertiesState::ptr)();
                    MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_UNUSED_SIEGE_ATTACKING_FORCEUnk, FALSE);
                    ;
                    return;
                }
                DAT_MapPropertiesState::instance.indexStored = 0;
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    0xc);
                MACRO_CALL(OS_Func::_sprintf)(local_10, "%d",
                    DAT_MapPropertiesState::instance.SEC_StartingResources[DAT_MissionAestheticsDefinedData::instance
                            .field1237_0x345c[DAT_MapPropertiesState::instance.indexStored]]);
                MACRO_CALL_MEMBER(
                    Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(local_10);
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    9);
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_START_GOODS, FALSE);
                ;
                return;
            case 0x2a:
                if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == Map::MT_INVASION) {
                    DAT_MapPropertiesState::instance.currentEventID = DAT_MapPropertiesState::instance.eventsCount;
                    pIVar2 = DAT_MapPropertiesState::instance.scenarioEvents
                        + DAT_MapPropertiesState::instance.eventsCount;
                    DAT_MapPropertiesState::instance.field50_0x13568 = 1;
                    DAT_MapPropertiesState::instance.eventsCount = DAT_MapPropertiesState::instance.eventsCount + 1;
                    MACRO_CALL_MEMBER(
                        Game::ScenarioEvents::InGameEventUnionVersion_Func::resetEvent, pIVar2)();
                    pcVar1 = MACRO_CALL_MEMBER(
                        Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(10);
                    DAT_MapPropertiesState::instance.SEC_StartingYear = atol(pcVar1);
                    DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .header.year = DAT_MapPropertiesState::instance.SEC_StartingYear;
                    DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .header.month = DAT_MapPropertiesState::instance.SEC_StartingMonth;
                    MACRO_CALL_MEMBER(
                        Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(0xe);
                    MACRO_CALL_MEMBER(
                        Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)("");
                    MACRO_CALL_MEMBER(
                        Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(0xb);
                    MACRO_CALL(OS_Func::_sprintf)(local_10, "%d",
                        DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                            .header.year);
                    MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray,
                        DAT_UserTextHandlerState::ptr)(local_10);
                    DAT_MapPropertiesState::instance.field_0x1356c = 0;
                    DAT_MapPropertiesState::instance.offset = 0;
                    DAT_MapPropertiesState::instance.indexStored = 0;
                    MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NEW_INVASION, FALSE);
                    ;
                    return;
                }
                break;
            case 0x2b:
                if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 != Map::MT_JUST_BUILD) {
                    DAT_MapPropertiesState::instance.currentEventID = DAT_MapPropertiesState::instance.eventsCount;
                    pIVar2 = DAT_MapPropertiesState::instance.scenarioEvents
                        + DAT_MapPropertiesState::instance.eventsCount;
                    DAT_MapPropertiesState::instance.field50_0x13568 = 3;
                    DAT_MapPropertiesState::instance.eventsCount = DAT_MapPropertiesState::instance.eventsCount + 1;
                    MACRO_CALL_MEMBER(
                        Game::ScenarioEvents::InGameEventUnionVersion_Func::initializeScenarioEvent, pIVar2)();
                    *(undefined1*)((int)&DAT_MapPropertiesState::instance
                                       .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                       .data
                        + 0xf) = 1;
                    *(undefined1*)((int)&DAT_MapPropertiesState::instance
                                       .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                       .data
                        + 0x22) = 10;
                    *(undefined1*)((int)&DAT_MapPropertiesState::instance
                                       .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                       .data
                        + 0x26) = 10;
                    *(undefined1*)((int)&DAT_MapPropertiesState::instance
                                       .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                       .data
                        + 0x2a) = 10;
                    *(undefined1*)((int)&DAT_MapPropertiesState::instance
                                       .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                       .data
                        + 0x52) = 10;
                    DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.conditions[0x16]
                        .value = 5;
                    DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.conditions[0x17]
                        .value = 5;
                    pcVar1 = MACRO_CALL_MEMBER(
                        Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(10);
                    DAT_MapPropertiesState::instance.SEC_StartingYear = atol(pcVar1);
                    DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .header.year = DAT_MapPropertiesState::instance.SEC_StartingYear;
                    DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .header.month = DAT_MapPropertiesState::instance.SEC_StartingMonth;
                    DAT_MapPropertiesState::instance.invasionTroopIndex = 0;
                    DAT_MapPropertiesState::instance.flag = 1;
                    MACRO_CALL(OS_Func::_sprintf)(local_10, "%d",
                        DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                            .header.year);
                    MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NEW_EVENT, FALSE);
                    ;
                    return;
                }
                break;
            case 0x3d:
                if (DAT_GameState::instance.mapAndTime.editScenarioExtraOptions) {
                    DAT_CopyOfScenarioGold::instance = (int)DAT_GameState::instance.mapAndTime.scenarioGold;
                    MACRO_CALL_MEMBER(
                        UI::MenuModalComposition_Func::setSliderParameters, DAT_MenuModalComposition2::ptr)(0,
                        10000, DAT_CopyOfScenarioGold::instance, (undefined*)DAT_CopyOfScenarioGold::ptr,
                        (void*)MACRO_CALL(UI::Helpers_Func::RestoreScenarioGold));
                    DAT_MenuModalComposition2::instance.textIndex = 0x3d;
                LAB_004b8756:
                    DAT_MenuModalComposition2::instance.textGroup = 199;
                    MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                        DAT_MenuModalComposition2::ptr)(UI::Enums::MMT_OVERLAY_SLIDER,
                        (int)((int)(DAT_ButtonX::instance + -2)), (int)((int)(DAT_ButtonY::instance + 0x19)));
                    ;
                    return;
                }
                break;
            case 0x4f:
                if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 != Map::MT_SIEGE) {
                    MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setSliderParameters,
                        DAT_MenuModalComposition2::ptr)(0, 100, DAT_MapPropertiesState::instance.SEC_StartingPopularity,
                        (undefined*)((int)(&DAT_MapPropertiesState::instance.SEC_StartingPopularity)),
                        (void*)MACRO_CALL(UI::Helpers_Func::SumUnitPoints));
                    DAT_MenuModalComposition2::instance.textGroup = 199;
                    DAT_MenuModalComposition2::instance.textIndex = 0x4f;
                    MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                        DAT_MenuModalComposition2::ptr)(UI::Enums::MMT_OVERLAY_SLIDER,
                        (int)((int)(DAT_ButtonX::instance + -2)), (int)((int)(DAT_ButtonY::instance + 0x19)));
                    ;
                    return;
                }
            LAB_004b82b4:
                DAT_StopHandlingMenuItems::instance = 0;
                ;
                return;
            case 0xa6:
                if ((DAT_GameState::instance.mapAndTime.editScenarioExtraOptions)
                    && (DAT_GameState::instance.mapAndTime.scenarioRationsSetting
                        = DAT_GameState::instance.mapAndTime.scenarioRationsSetting + 1,
                        4 < DAT_GameState::instance.mapAndTime.scenarioRationsSetting)) {
                    DAT_GameState::instance.mapAndTime.scenarioRationsSetting = 0;
                    ;
                    return;
                }
                break;
            case 0xa7:
                if ((DAT_GameState::instance.mapAndTime.editScenarioExtraOptions)
                    && (DAT_GameState::instance.mapAndTime.scenarioTaxesSetting
                        = DAT_GameState::instance.mapAndTime.scenarioTaxesSetting + 1,
                        9 < DAT_GameState::instance.mapAndTime.scenarioTaxesSetting)) {
                    DAT_GameState::instance.mapAndTime.scenarioTaxesSetting = 0;
                }
                break;
            case 0xa8:
                if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == Map::MT_SIEGE) {
                    MACRO_CALL_MEMBER(
                        UI::MenuModalComposition_Func::setSliderParameters, DAT_MenuModalComposition2::ptr)(0,
                        10000, (int)((int)(DAT_MapPropertiesState::instance.SEC_StartingResources[0xf])),
                        (undefined*)((int)((DAT_MapPropertiesState::instance.SEC_StartingResources + 0xf))),
                        (void*)MACRO_CALL(UI::Helpers_Func::SumUnitPoints));
                    DAT_MenuModalComposition2::instance.textIndex = 0xa8;
                    goto LAB_004b8756;
                }
                break;
            case 0xa9:
                if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == Map::MT_SIEGE) {
                    MACRO_CALL_MEMBER(
                        UI::MenuModalComposition_Func::setSliderParameters, DAT_MenuModalComposition2::ptr)(0,
                        100, (int)((int)(DAT_MapPropertiesState::instance.SEC_StartingResources[8])),
                        (undefined*)((int)((DAT_MapPropertiesState::instance.SEC_StartingResources + 8))),
                        (void*)MACRO_CALL(UI::Helpers_Func::SumUnitPoints));
                    DAT_MenuModalComposition2::instance.textIndex = 0xa9;
                    goto LAB_004b8756;
                }
                break;
            case 0xab:
                DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset = 0;
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_BUILDING_AVAILABILITY, FALSE);
                ;
                return;
            case -1:
                DAT_MapPropertiesState::instance.SEC_StartingMonth
                    = DAT_MapPropertiesState::instance.SEC_StartingMonth + 1;
                if (0xb < DAT_MapPropertiesState::instance.SEC_StartingMonth) {
                    DAT_MapPropertiesState::instance.SEC_StartingMonth = 0;
                }
                DAT_GameState::instance.mapAndTime.year = DAT_MapPropertiesState::instance.SEC_StartingYear;
                DAT_GameState::instance.mapAndTime.month = DAT_MapPropertiesState::instance.SEC_StartingMonth;
                ;
                return;
            }
        switchD_004b8254_caseD_0:;
            return;
        }

    }
}
}
