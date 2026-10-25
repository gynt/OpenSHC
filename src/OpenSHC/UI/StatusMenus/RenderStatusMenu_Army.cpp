#include "../StatusMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00b95b68.hpp"
#include "OpenSHC/Globals/DAT_00b9845c.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UnitTypeRelatedCounter.hpp"
#include "OpenSHC/Map/Units/UnitTypeInt.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eGM;
    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;
    using OpenSHC::Map::Units::UnitTypeInt;
    using OpenSHC::Rendering::Colors::BGR24;

    // FUNCTION: STRONGHOLDCRUSADER 0x00447FA0
    void StatusMenus::RenderStatusMenu_Army()
    {
        uint foregroundColor;
        int _nudge;
        int _xOffset;
        int _groupCount;
        int const _y = DAT_MenuHandlerState::instance.y;
        int _x = DAT_MenuHandlerState::instance.x;
        int const _firstGroupIcon = DAT_00b95b68::instance * 9;
        int _iconY = _y + 0x1bf;
        DAT_00b9845c::instance = DAT_00b9845c::instance + 1;
        _nudge = 0;
        if (0x28 < DAT_00b9845c::instance) {
            DAT_00b9845c::instance = 0;
            MACRO_CALL(OpenSHC::UI::Helpers_Func::CountPlayerUnitsByType)();
        }
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        /*
          added by script: "Army"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 5),
            _x + 0x19, _y + 0x1d3, OpenSHC::Text::TTA_LEFT, 0, 0x11, FALSE, 0);
        if (DAT_00b95b68::instance == 2) {
            _groupCount = 8;
            _nudge = -6;
        } else {
            _groupCount = 9;
        }
        if (0 < _groupCount) {
            int i = 0;
            int _iconX = _x + 0x55;
            UnitTypeInt* pUVar1 = DAT_RenderingDefinedData::instance.UnitTypeGroups[0] + _firstGroupIcon;
            _xOffset = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                    DAT_TextureRenderCoreObject::ptr)(_firstGroupIcon + i + 4, _iconX, _iconY + 0x28);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_UnitTypeRelatedCounter::instance[*pUVar1], _nudge + _xOffset + _x + 0x6f, _iconY + 0x7d,
                    OpenSHC::Text::TTA_CENTER, 0, 0x11, FALSE, 0);
                if (2 < i) {
                    _nudge = 0;
                }
                _iconX = _iconX + 0x2e;
                i = i + 1;
                pUVar1 = pUVar1 + 1;
                _xOffset = _xOffset + 0x2e;
            } while (i < _groupCount);
        }
        if (DAT_00b95b68::instance != 0) {
            _iconY = _iconY + 0x19;
            /*
              added by script: "Total Troops"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x10),
                _x + 0x74, _iconY, OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].armySize,
                _x + 0x7a, _iconY, OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE, 0);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            return;
        }
        if (0 < DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .fearFactorLevel) {
            DAT_TextManagerObject::instance.field8_0x20 = 1;
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, 0xb1, _x + 0x74, _iconY + 0x1b);
            _iconY = _iconY + 0x19;
            /*
              added by script: "Troop combat bonus:"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x1f),
                _x + 0x9c, _iconY, OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .fearFactorLevel
                    * 5,
                _x + 0xa2, _iconY, OpenSHC::Text::TTA_LEFT, 0xff00, 0, 0x12, TRUE, 0);
            foregroundColor = 0xff00;
            _x = _x + 0xa4;
        } else if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                       .fearFactorLevel
            == 0) {
            _iconY = _iconY + 0x19;
            /*
              added by script: "No 'fear factor' bonus."
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x1e),
                _x + 0x74, _iconY, OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE, 0);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            return;
        } else {
            DAT_TextManagerObject::instance.field8_0x20 = 1;
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, 0xb2, _x + 0x74, _iconY + 0x11);
            _iconY = _iconY + 0x19;
            /*
              added by script: "Troop combat bonus:"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x1f),
                _x + 0x92, _iconY, OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .fearFactorLevel
                    * 5,
                _x + 0x98, _iconY, OpenSHC::Text::TTA_LEFT, 0xff, 0, 0x12, TRUE, 0);
            foregroundColor = 0xff;
            _x = _x + 0x9a;
        }
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
            "%", _x, _iconY, OpenSHC::Text::TTA_LEFT, foregroundColor, 0, 0x12, TRUE, 0);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        DAT_TextManagerObject::instance.field8_0x20 = 0;
    }

}
}
