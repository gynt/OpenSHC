#include "../DisplayElements.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    using DE::SHCDE::eTextSections;
    using Text::TextAlignment;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004B07C0
    void DisplayElements::RenderGameSpeedTextDisplayElement(int posX, int posY, DWORD elementState)
    {
        char* textAddress;
        int xParam;
        int yParam;
        TextAlignment alignment;
        uint foregroundColor;
        uint backgroundColor;
        int fontSize;
        BOOLEnum keepOffsetX;
        int blendStrength;
        blendStrength = 0;
        keepOffsetX = FALSE;
        fontSize = 0x11;
        backgroundColor = 0;
        foregroundColor = 0xc2f0eb;
        alignment = Text::TTA_RIGHT;
        xParam = posX + -3;
        yParam = posY;
        /*
          added by script: "Game Speed"
         */
        textAddress = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_FEEDBACK, 0x17);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
            textAddress, xParam, yParam, alignment, foregroundColor, backgroundColor, fontSize, keepOffsetX,
            blendStrength);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
            DAT_GameCore::instance.gameSpeedLevel, posX, posY, Text::TTA_LEFT, 0xc2f0eb, 0, 0x11, FALSE, 0);
    }

}
}
