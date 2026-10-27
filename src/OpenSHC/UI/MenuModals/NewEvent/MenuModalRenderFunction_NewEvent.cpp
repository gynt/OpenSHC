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
            int rowY;
            int conditionIndex;
            /*
              added by script: "Event"
             */
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                DAT_PencilRenderCore::ptr)(199, 0x30, x, y, width, height);
            int rowsDrawn = 0;
            conditionIndex = 0;
            rowY = y + 0xa5;
            int eventIndex = DAT_MapPropertiesState::instance.currentEventID;
            do {
                if (*(char*)((int)&DAT_MapPropertiesState::instance.scenarioEvents[0].data
                        + (eventIndex * 0x39 + conditionIndex) * 4 + 0xf)
                    != '\0') {
                    eventIndex = conditionIndex + 0x6a;
                    if (0x7d < eventIndex) {
                        eventIndex = eventIndex + 0x40;
                    }
                    if (eventIndex == 0x6f || eventIndex == 0x70 || eventIndex == 0x71 || eventIndex == 0x7b) {
                        eventIndex = 0x71;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, eventIndex),
                        x + 0x96, rowY, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12, FALSE, 0);
                    if (DAT_MissionAestheticsDefinedData::instance.EventConditionParamKind[conditionIndex] == 1) {
                        int parenX = x + 0x9e;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                            "(", parenX, rowY, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12, TRUE, 0);
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO,
                                (int)(DAT_MissionAestheticsDefinedData::instance.EventConditionOptionTextOffsets[*(
                                    char*)((int)&DAT_MapPropertiesState::instance.scenarioEvents[0].data
                                    + (DAT_MapPropertiesState::instance.currentEventID * 0x39 + conditionIndex) * 4
                                    + 0xe)])),
                            parenX, rowY, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12, TRUE, 0);
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                            ")", parenX, rowY, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12, TRUE, 0);
                    }
                    if (DAT_MissionAestheticsDefinedData::instance.EventConditionParamKind[conditionIndex] == 2) {
                        int parenX = x + 0x9e;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                            "(", parenX, rowY, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12, TRUE, 0);
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO,
                                (int)(DAT_MissionAestheticsDefinedData::instance.field92_0x170[*(
                                    char*)((int)&DAT_MapPropertiesState::instance.scenarioEvents[0].data
                                    + (DAT_MapPropertiesState::instance.currentEventID * 0x39 + conditionIndex) * 4
                                    + 0xe)])),
                            parenX, rowY, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12, TRUE, 0);
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                            ")", parenX, rowY, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12, TRUE, 0);
                    }
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                        (int)*(short*)((int)&DAT_MapPropertiesState::instance.scenarioEvents[0].data
                            + (DAT_MapPropertiesState::instance.currentEventID * 0x39 + conditionIndex) * 4 + 0xc)
                            * DAT_MissionAestheticsDefinedData::instance.EventConditionValueScale[conditionIndex],
                        x + 0x1c2, rowY, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12, FALSE, 0);
                    rowsDrawn = rowsDrawn + 1;
                    rowY = rowY + 0x18;
                    eventIndex = DAT_MapPropertiesState::instance.currentEventID;
                    if (7 <= rowsDrawn)
                        break;
                }
                conditionIndex = conditionIndex + 1;
            } while (conditionIndex < 0x28);
            eventIndex = DAT_MapPropertiesState::instance.scenarioEvents[eventIndex].data.scenario.ScenarioEventType;
            rowY = eventIndex + 0x80;
            if (0x9b < rowY) {
                rowY = rowY + 0x15;
            }
            eventIndex = y + 0x17c;
            x = x + 0x9e;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, rowY),
                x, eventIndex, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12, FALSE, 0);
            return;
        }

    }
}
}
