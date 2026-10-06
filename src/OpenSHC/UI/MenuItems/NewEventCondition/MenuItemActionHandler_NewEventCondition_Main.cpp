#include "../NewEventCondition.func.hpp"

#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_UnknownTime_01.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using UI::Enums::MenuModalType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004B9620
        void NewEventCondition::MenuItemActionHandler_NewEventCondition_Main(int param_1, ...)
        {
            ushort* puVar1;
            short* destination;
            byte* pbVar2;
            short sVar3;
            byte(*pabVar4)[100];
            DWORD DVar5;
            char* pcVar6;
            int iVar7;
            int iVar8;
            if (param_1 < 0x3e9) {
                if (param_1 == 1000) {
                    sVar3 = *(short*)((int)&DAT_MapPropertiesState::instance
                                          .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                          .data
                        + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 0xc);
                    if (DAT_MissionAestheticsDefinedData::instance
                            .field1227_0x21c4[DAT_MapPropertiesState::instance.invasionTroopIndex]
                        < (int)sVar3) {
                        *(short*)((int)&DAT_MapPropertiesState::instance
                                      .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                      .data
                            + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 0xc) = sVar3 + -1;
                        return;
                    }
                } else {
                    switch (param_1) {
                    case 0x13:
                        *(undefined1*)((int)&DAT_MapPropertiesState::instance
                                           .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                           .data
                            + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 0xf) = 0;
                        return;
                    case 0x25:
                        if (*(char*)((int)&DAT_MapPropertiesState::instance
                                         .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                         .data
                                + 0xf)
                            != '\0') {
                            iVar8 = 1;
                            pcVar6 = (char*)((int)&DAT_MapPropertiesState::instance
                                                 .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                                 .data
                                + 0x13);
                            while (*pcVar6 == '\0') {
                                iVar8 = iVar8 + 1;
                                pcVar6 = pcVar6 + 4;
                                if (0x27 < iVar8) {
                                    MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                                        DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NEW_EVENT, FALSE);
                                    return;
                                }
                            }
                            *(undefined1*)((int)&DAT_MapPropertiesState::instance
                                               .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                               .data
                                + 0xf) = 0;
                        }
                        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NEW_EVENT, FALSE);
                        return;
                    case 0x68:
                        puVar1 = (ushort*)((int)&DAT_MapPropertiesState::instance
                                               .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                               .data
                            + 8);
                        *puVar1 = *puVar1 ^ 1;
                        return;
                    case 0xbe:
                    case 0xbf:
                    case 0xc0:
                    case 0xc1:
                    case 0xc2:
                    case 0xc3:
                    case 0xc4:
                    case 0xc5:
                    case 0xc6:
                    case 199:
                    case 200:
                    case 0xc9:
                    case 0xca:
                    case 0xcb:
                    case 0xcc:
                    case 0xcd:
                    case 0xce:
                    case 0xcf:
                    case 0xd0:
                    case 0xd1:
                        param_1 = param_1 + -0x40;
                    case 0x6a:
                    case 0x6b:
                    case 0x6c:
                    case 0x6d:
                    case 0x6e:
                    case 0x6f:
                    case 0x70:
                    case 0x71:
                    case 0x72:
                    case 0x73:
                    case 0x74:
                    case 0x75:
                    case 0x76:
                    case 0x77:
                    case 0x78:
                    case 0x79:
                    case 0x7a:
                    case 0x7b:
                    case 0x7c:
                    case 0x7d:
                        DAT_MapPropertiesState::instance.invasionTroopIndex = param_1 + -0x6a;
                        *(undefined1*)((int)DAT_MapPropertiesState::instance.buildingAvailabilityRelatedFlags
                            + DAT_MapPropertiesState::instance.currentEventID * 0xe4 + param_1 * 4 + 0x1ff) = 1;
                        DAT_UnknownTime_01::instance = 0;
                        if ((int)*(short*)((int)&DAT_MapPropertiesState::instance
                                               .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                               .data
                                + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 0xc)
                            < DAT_MissionAestheticsDefinedData::instance
                                .field1227_0x21c4[DAT_MapPropertiesState::instance.invasionTroopIndex]) {
                            *(short*)((int)&DAT_MapPropertiesState::instance
                                          .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                          .data
                                + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 0xc)
                                = (short)DAT_MissionAestheticsDefinedData::instance
                                      .field1227_0x21c4[DAT_MapPropertiesState::instance.invasionTroopIndex];
                        }
                        if (DAT_MissionAestheticsDefinedData::instance
                                .field1228_0x2264[DAT_MapPropertiesState::instance.invasionTroopIndex]
                            != 0) {
                            destination = (short*)((int)&DAT_MapPropertiesState::instance
                                                       .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                                       .data
                                + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 0xc);
                            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setSliderParameters2,
                                DAT_MenuModalComposition2::ptr)(
                                DAT_MissionAestheticsDefinedData::instance
                                    .field1227_0x21c4[DAT_MapPropertiesState::instance.invasionTroopIndex],
                                (dword)((int)(DAT_MissionAestheticsDefinedData::instance
                                        .field1228_0x2264[DAT_MapPropertiesState::instance.invasionTroopIndex])),
                                (dword)((int)((int)*destination)), (dword)((int)(destination)),
                                (undefined*)MACRO_CALL(UI::Helpers_Func::CaptureCurrentTimeToUnknownTime01));
                            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                                DAT_MenuModalComposition2::ptr)(UI::Enums::MMT_OVERLAY_SLIDER,
                                (int)((int)(DAT_ButtonX::instance + 0x3a)), (int)((int)(DAT_ButtonY::instance + 0x1c)));
                            return;
                        }
                    }
                }
            } else if (param_1 < 0x7d3) {
                if (param_1 < 0x7d1) {
                    if (param_1 == 0x3e9) {
                        sVar3 = *(short*)((int)&DAT_MapPropertiesState::instance
                                              .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                              .data
                            + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 0xc);
                        if ((int)sVar3 < DAT_MissionAestheticsDefinedData::instance
                                .field1228_0x2264[DAT_MapPropertiesState::instance.invasionTroopIndex]) {
                            *(short*)((int)&DAT_MapPropertiesState::instance
                                          .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                          .data
                                + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 0xc) = sVar3 + 1;
                            return;
                        }
                    } else if (param_1 == 2000) {
                        iVar8 = 0;
                        if (DAT_MissionAestheticsDefinedData::instance
                                .field1230_0x23a4[DAT_MapPropertiesState::instance.invasionTroopIndex]
                            != 0) {
                            if (DAT_MissionAestheticsDefinedData::instance
                                    .field1230_0x23a4[DAT_MapPropertiesState::instance.invasionTroopIndex]
                                == 1) {
                                iVar7
                                    = (int)*(char*)((int)&DAT_MapPropertiesState::instance
                                                        .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                                        .data
                                        + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 0xe);
                                pbVar2 = (byte*)((int)&DAT_MapPropertiesState::instance
                                                     .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                                     .data
                                    + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 0xe);
                                if (*(int*)DAT_MissionAestheticsDefinedData::instance
                                        .field1231_0x2444[DAT_MapPropertiesState::instance.invasionTroopIndex]
                                    != iVar7) {
                                    pabVar4 = DAT_MissionAestheticsDefinedData::instance.field1231_0x2444
                                        + DAT_MapPropertiesState::instance.invasionTroopIndex;
                                    do {
                                        pabVar4 = (byte(*)[100])(*pabVar4 + 4);
                                        iVar8 = iVar8 + 1;
                                    } while (*(int*)*pabVar4 != iVar7);
                                }
                                if (iVar8 + -1 < 0) {
                                    pabVar4 = DAT_MissionAestheticsDefinedData::instance.field1231_0x2444
                                        + DAT_MapPropertiesState::instance.invasionTroopIndex;
                                    iVar8 = 0;
                                    do {
                                        iVar7 = iVar8;
                                        if (*(int*)*pabVar4 == -1) {
                                            *pbVar2 = DAT_MissionAestheticsDefinedData::instance.field1231_0x2444
                                                          [DAT_MapPropertiesState::instance.invasionTroopIndex + -1]
                                                          [iVar7 * 4 + 0x60];
                                            goto LAB_004b98bd;
                                        }
                                        pabVar4 = (byte(*)[100])(*pabVar4 + 4);
                                        iVar8 = iVar7 + 1;
                                    } while (iVar7 + 1 < 100);
                                    *pbVar2 = DAT_MissionAestheticsDefinedData::instance
                                                  .field1231_0x2444[DAT_MapPropertiesState::instance.invasionTroopIndex]
                                                                   [iVar7 * 4 + 4];
                                } else {
                                    *pbVar2 = DAT_MissionAestheticsDefinedData::instance
                                                  .field1231_0x2444[DAT_MapPropertiesState::instance.invasionTroopIndex
                                                      + -1][iVar8 * 4 + 0x60];
                                }
                            }
                        LAB_004b98bd:
                            if (DAT_MissionAestheticsDefinedData::instance
                                    .field1230_0x23a4[DAT_MapPropertiesState::instance.invasionTroopIndex]
                                == 2) {
                                pcVar6 = (char*)((int)&DAT_MapPropertiesState::instance
                                                     .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                                     .data
                                    + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 0xe);
                                *pcVar6 = *pcVar6 + -1;
                                if (*(char*)((int)&DAT_MapPropertiesState::instance
                                                 .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                                 .data
                                        + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 0xe)
                                    < '\0') {
                                    *(undefined1*)((int)&DAT_MapPropertiesState::instance
                                                       .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                                       .data
                                        + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 0xe) = 4;
                                }
                            }
                        }
                    }
                } else {
                    iVar8 = 0;
                    if (DAT_MissionAestheticsDefinedData::instance
                            .field1230_0x23a4[DAT_MapPropertiesState::instance.invasionTroopIndex]
                        != 0) {
                        if (DAT_MissionAestheticsDefinedData::instance
                                .field1230_0x23a4[DAT_MapPropertiesState::instance.invasionTroopIndex]
                            == 1) {
                            iVar7 = (int)*(char*)((int)&DAT_MapPropertiesState::instance
                                                      .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                                      .data
                                + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 0xe);
                            if (!iVar7) {
                                *(undefined1*)((int)&DAT_MapPropertiesState::instance
                                                   .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                                   .data
                                    + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 0xe) = 10;
                                iVar7 = 10;
                            }
                            if (*(int*)DAT_MissionAestheticsDefinedData::instance
                                    .field1231_0x2444[DAT_MapPropertiesState::instance.invasionTroopIndex]
                                != iVar7) {
                                pabVar4 = DAT_MissionAestheticsDefinedData::instance.field1231_0x2444
                                    + DAT_MapPropertiesState::instance.invasionTroopIndex;
                                do {
                                    pabVar4 = (byte(*)[100])(*pabVar4 + 4);
                                    iVar8 = iVar8 + 1;
                                } while (*(int*)*pabVar4 != iVar7);
                            }
                            if (*(int*)(DAT_MissionAestheticsDefinedData::instance
                                            .field1231_0x2444[DAT_MapPropertiesState::instance.invasionTroopIndex]
                                    + iVar8 * 4 + 4)
                                == -1) {
                                *(byte*)((int)&DAT_MapPropertiesState::instance
                                             .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                             .data
                                    + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 0xe)
                                    = DAT_MissionAestheticsDefinedData::instance
                                          .field1231_0x2444[DAT_MapPropertiesState::instance.invasionTroopIndex][0];
                            } else {
                                *(byte*)((int)&DAT_MapPropertiesState::instance
                                             .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                             .data
                                    + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 0xe)
                                    = DAT_MissionAestheticsDefinedData::instance
                                          .field1231_0x2444[DAT_MapPropertiesState::instance.invasionTroopIndex]
                                                           [iVar8 * 4 + 4];
                            }
                        }
                        if (DAT_MissionAestheticsDefinedData::instance
                                .field1230_0x23a4[DAT_MapPropertiesState::instance.invasionTroopIndex]
                            == 2) {
                            pcVar6 = (char*)((int)&DAT_MapPropertiesState::instance
                                                 .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                                 .data
                                + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 0xe);
                            *pcVar6 = *pcVar6 + '\x01';
                            if ('\x04' < *(char*)((int)&DAT_MapPropertiesState::instance
                                                      .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                                      .data
                                    + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 0xe)) {
                                *(undefined1*)((int)&DAT_MapPropertiesState::instance
                                                   .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                                   .data
                                    + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 0xe) = 0;
                                return;
                            }
                        }
                    }
                }
            } else {
                switch (param_1) {
                case 0x1446:
                case 0x1447:
                case 0x1448:
                case 0x1449:
                case 0x144a:
                case 0x144b:
                case 0x144c:
                case 0x144d:
                case 0x144e:
                case 0x144f:
                case 0x1450:
                case 0x1451:
                case 0x1452:
                case 0x1453:
                case 0x1454:
                case 0x1455:
                case 0x1456:
                case 0x1457:
                case 0x1458:
                case 0x1459:
                    param_1 = param_1 + -0x40;
                case 0x13f2:
                case 0x13f3:
                case 0x13f4:
                case 0x13f5:
                case 0x13f6:
                case 0x13f7:
                case 0x13f8:
                case 0x13f9:
                case 0x13fa:
                case 0x13fb:
                case 0x13fc:
                case 0x13fd:
                case 0x13fe:
                case 0x13ff:
                case 0x1400:
                case 0x1401:
                case 0x1402:
                case 0x1403:
                case 0x1404:
                case 0x1405:
                    if ((DAT_MenuModalComposition2::instance.activeModalDialogID == UI::Enums::MMT_NONE)
                        && ((DVar5 = timeGetTime(),
                            1000 < DVar5 - DAT_UnknownTime_01::instance || (!DAT_UnknownTime_01::instance)))) {
                        DAT_UnknownTime_01::instance = 0;
                        (&DAT_UnitsState::instance.units[0x9bb]
                                .field_0x3e3)[(DAT_MapPropertiesState::instance.currentEventID * 0x39 + param_1) * 4]
                            = 0;
                        return;
                    }
                }
            }
            return;
        }

    }
}
}
