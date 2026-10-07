#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    using DE::SHCDE::eTextSections;
    using Rendering::Colors::BGR24;
    using Text::TextAlignment;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0043D790
    void BuildingMenus::RenderBuildingMenu_KillingPit()
    {
        char* textAddress;
        int xParam;
        TextAlignment alignment;
        BGR24 color;
        int fontSize;
        BOOLEnum keepOffsetX;
        int blendStrength;
        blendStrength = 0;
        keepOffsetX = FALSE;
        fontSize = 0x10;
        color = 0;
        alignment = Text::TTA_LEFT;
        int yParam = DAT_MenuHandlerState::instance.y + 0x1d3;
        xParam = DAT_MenuHandlerState::instance.x + 0x19;
        /*
          added by script: "Killing Pit"
         */
        textAddress = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_IN_KILLING_PIT, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            textAddress, xParam, yParam, alignment, color, fontSize, keepOffsetX, blendStrength);
    }

}
}
