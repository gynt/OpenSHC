#include "../DisplayElements.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    using DE::SHCDE::eTextSections;
    using Text::TextAlignment;
    using UI::Enums::DisplayElementID;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004B1E60
    void DisplayElements::RenderGamePausedTextDisplayElement(int posX, int posY, DWORD elementState)
    {
        char* textAddress;
        TextAlignment alignment;
        uint foregroundColor;
        uint backgroundColor;
        int fontSize;
        BOOLEnum keepOffsetX;
        int blendStrength;
        blendStrength = 0;
        if (!DAT_GameCore::instance.gamePausedLogical) {
            MACRO_CALL(UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                UI::Enums::DEID_GAME_PAUSED_TEXT, 0);
        }
        keepOffsetX = FALSE;
        fontSize = 0x10;
        backgroundColor = 0;
        foregroundColor = 0xc2f0eb;
        alignment = Text::TTA_CENTER;
        /*
          added by script: "Game Paused"
         */
        textAddress = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_FEEDBACK, 0x16);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
            textAddress, posX, posY, alignment, foregroundColor, backgroundColor, fontSize, keepOffsetX, blendStrength);
    }

}
}
