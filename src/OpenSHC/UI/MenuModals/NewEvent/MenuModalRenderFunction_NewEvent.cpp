#include "../NewEvent.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004AB790
        void NewEvent::MenuModalRenderFunction_NewEvent(int x, int y, int width, int height)
        {
            int iVar4;
            int iVar5;
            int iVar6;
            TextAlignment TVar7;
            BGR24 BVar8;
            int iVar9;
            BOOLEnum BVar10;
            int iVar11;
            int iVar12;
            /*
              added by script: "Event"
             */
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                DAT_PencilRenderCore::ptr)(199, 0x30, x, y, width, height);
            int rowsDrawn = 0;
            iVar4 = y + 0xa5;
            iVar5 = 0;
            int iVar1 = DAT_MapPropertiesState::instance.currentEventID;
            do {
                if (*(char*)((int)&DAT_MapPropertiesState::instance.scenarioEvents[iVar1].data + iVar5 * 4 + 0xf)
                    != '\0') {
                    iVar1 = iVar5 + 0x6a;
                    if (0x7d < iVar1) {
                        iVar1 = iVar1 + 0x40;
                    }
                    if (iVar1 == 0x6f || iVar1 == 0x70 || iVar1 == 0x71 || iVar1 == 0x7b) {
                        iVar1 = 0x71;
                    }
                    iVar11 = 0;
                    BVar10 = FALSE;
                    iVar9 = 0x12;
                    BVar8 = 0xccfaff;
                    TVar7 = OpenSHC::Text::TTA_LEFT;
                    iVar12 = x + 0x96;
                    iVar6 = iVar4;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, iVar1),
                        iVar12, iVar6, TVar7, BVar8, iVar9, BVar10, iVar11);
                    if (DAT_MissionAestheticsDefinedData::instance.EventConditionParamKind[iVar5] == 1) {
                        iVar1 = x + 0x9e;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                            "(", iVar1, iVar4, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12, TRUE, 0);
                        iVar11 = 0;
                        BVar10 = TRUE;
                        iVar9 = 0x12;
                        BVar8 = 0xccfaff;
                        TVar7 = OpenSHC::Text::TTA_LEFT;
                        iVar12 = iVar1;
                        iVar6 = iVar4;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO,
                                (int)(DAT_MissionAestheticsDefinedData::instance.EventConditionOptionTextOffsets[*(
                                    char*)(&DAT_MapPropertiesState::instance
                                               .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                               .data
                                    + iVar5 * 4 + 0xe)])),
                            iVar12, iVar6, TVar7, BVar8, iVar9, BVar10, iVar11);
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                            ")", iVar1, iVar4, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12, TRUE, 0);
                    }
                    if (DAT_MissionAestheticsDefinedData::instance.EventConditionParamKind[iVar5] == 2) {
                        iVar1 = x + 0x9e;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                            "(", iVar1, iVar4, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12, TRUE, 0);
                        iVar11 = 0;
                        BVar10 = TRUE;
                        iVar9 = 0x12;
                        BVar8 = 0xccfaff;
                        TVar7 = OpenSHC::Text::TTA_LEFT;
                        iVar12 = iVar1;
                        iVar6 = iVar4;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO,
                                (int)(DAT_MissionAestheticsDefinedData::instance.field92_0x170[*(
                                    char*)(&DAT_MapPropertiesState::instance
                                               .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                               .data
                                    + iVar5 * 4 + 0xe)])),
                            iVar12, iVar6, TVar7, BVar8, iVar9, BVar10, iVar11);
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                            ")", iVar1, iVar4, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12, TRUE, 0);
                    }
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                        (int)*(short*)((int)&DAT_MapPropertiesState::instance
                                           .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                           .data
                            + iVar5 * 4 + 0xc)
                            * DAT_MissionAestheticsDefinedData::instance.EventConditionValueScale[iVar5],
                        x + 0x1c2, iVar4, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12, FALSE, 0);
                    rowsDrawn = rowsDrawn + 1;
                    iVar4 = iVar4 + 0x18;
                    iVar1 = DAT_MapPropertiesState::instance.currentEventID;
                    if (7 <= rowsDrawn)
                        break;
                }
                iVar5 = iVar5 + 1;
            } while (iVar5 < 0x28);
            iVar1 = DAT_MapPropertiesState::instance.scenarioEvents[iVar1].data.scenario.ScenarioEventType;
            iVar4 = iVar1 + 0x80;
            if (0x9b < iVar4) {
                iVar4 = iVar4 + 0x15;
            }
            iVar12 = 0;
            BVar10 = FALSE;
            iVar5 = 0x12;
            BVar8 = 0xccfaff;
            TVar7 = OpenSHC::Text::TTA_LEFT;
            iVar1 = y + 0x17c;
            x = x + 0x9e;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, iVar4),
                x, iVar1, TVar7, BVar8, iVar5, BVar10, iVar12);
            return;
        }

    }
}
}
