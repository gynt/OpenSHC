#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using DE::SHCDE::eTextSections;
        using Text::TextAlignment;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0043A960
        void BuildingAndStatusMenu::MenuItemRenderFunction_BuildingAndStatusMenu_AvailablePeasantsTextDownRight(
            int param_1, ...)
        {
            char* textAddress;
            int xParam;
            TextAlignment alignment;
            uint foregroundColor;
            uint backgroundColor;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            blendStrength = 0;
            keepOffsetX = FALSE;
            fontSize = 0x12;
            backgroundColor = 0;
            foregroundColor = 0xb8eefb;
            alignment = Text::TTA_RIGHT;
            int yParam = DAT_ButtonY::instance + 0x98;
            xParam = DAT_ButtonX::instance + -5;
            /*
              added by script: "Available Peasants"
             */
            textAddress = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_IN_BARRACKS, 3);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                textAddress, xParam, yParam, alignment, foregroundColor, backgroundColor, fontSize, keepOffsetX,
                blendStrength);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .availablePeasantsOrHousedPeasants
                    - DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .count,
                (int)(DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 0x98), Text::TTA_LEFT, 0xb8eefb, 0,
                0x12, FALSE, 0);
        }

    }
}
}
