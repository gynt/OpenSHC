#include "../ProgressBarBox.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/GameLanguage.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Game::GameMode;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Text::GameLanguage;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00493560
        void ProgressBarBox::MenuModalRenderFunction_ProgressBarBox(int x, int y, int width, int height)
        {
            int iVar1;
            int yParam;
            int iVar2;
            if ((DAT_TextManagerObject::instance.gameLanguage == OpenSHC::Text::GL_ENGLISH)
                || (DAT_TextManagerObject::instance.gameLanguage == OpenSHC::Text::GL_AMERICAN)) {
                iVar2 = 0x10;
            } else {
                iVar2 = 0x12;
            }
            yParam = y + 0x19;
            iVar1 = width / 2 + x;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS,
                    (int)(DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter)),
                iVar1, yParam, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, iVar2, FALSE, 0);
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                && DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                && DAT_GameSynchronyState::instance.saveRelated != 0) {
                iVar1 = (width + -300) / 2;
                iVar2 = iVar1 + x;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(iVar2,
                    y + 0x41, (x - iVar1) + width, y + 0x50, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
                DAT_MenuTextInputState::instance.progressBarY = y + 0x41;
                DAT_MenuTextInputState::instance.progressBarX = iVar2;
            }
            iVar1 = (width + -300) / 2;
            iVar2 = iVar1 + x;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                iVar2, y + 0x41, (x - iVar1) + width, y + 0x50);
            DAT_MenuTextInputState::instance.progressBarY = y + 0x41;
            DAT_MenuTextInputState::instance.progressBarX = iVar2;
        }

    }
}
}
