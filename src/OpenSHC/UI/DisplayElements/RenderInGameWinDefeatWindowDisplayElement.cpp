#include "../DisplayElements.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/GameLanguage.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::Text::GameLanguage;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::UI::Enums::MenuViewType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004AFB30
    void DisplayElements::RenderInGameWinDefeatWindowDisplayElement(int posX, int posY, DWORD elementState)
    {
        char (*textAddress)[250];
        int iVar4;
        int* piVar5;
        ushort* local_8;
        DWORD DVar1 = timeGetTime();
        if (8000 < DVar1 - DAT_GameState::instance.mapAndTime.gameOverTime) {
            if (DAT_GameState::instance.mapAndTime.playerIsAlive[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                != 0) {
                DAT_GameCore::instance.isVictoryOrDefeatUnk = 0;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_MISSION_FINISHED_TRANSITION, 0);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_GAME_LOSTUnk, 0);
            }
        }
        int _alivePlayerCount = 0;
        if (DAT_GameState::instance.mapAndTime.playerIsAlive[1] != 0) {
            _alivePlayerCount = 1;
        }
        if (DAT_GameState::instance.mapAndTime.playerIsAlive[2] != 0) {
            _alivePlayerCount = _alivePlayerCount + 1;
        }
        if (DAT_GameState::instance.mapAndTime.playerIsAlive[3] != 0) {
            _alivePlayerCount = _alivePlayerCount + 1;
        }
        if (DAT_GameState::instance.mapAndTime.playerIsAlive[4] != 0) {
            _alivePlayerCount = _alivePlayerCount + 1;
        }
        if (DAT_GameState::instance.mapAndTime.playerIsAlive[5] != 0) {
            _alivePlayerCount = _alivePlayerCount + 1;
        }
        if (DAT_GameState::instance.mapAndTime.playerIsAlive[6] != 0) {
            _alivePlayerCount = _alivePlayerCount + 1;
        }
        if (DAT_GameState::instance.mapAndTime.playerIsAlive[7] != 0) {
            _alivePlayerCount = _alivePlayerCount + 1;
        }
        if (DAT_GameState::instance.mapAndTime.playerIsAlive[8] != 0) {
            _alivePlayerCount = _alivePlayerCount + 1;
        }
        DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        int iVar3 = _alivePlayerCount * 0x1e - 6;
        iVar3 = iVar3 + (0x1d - (iVar3 + 0x1d) % 0x1e);
        iVar4 = posY + (-0x1c - iVar3 / 2);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderedBoxWithBlendedBackground,
            DAT_PencilRenderCore::ptr)(posX + -0x108, iVar4 + -0x13, 0x210, iVar3 + 0x60);
        DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        /*
          added by script: "Defeat"
         */
        if (DAT_GameState::instance.mapAndTime.playerIsAlive[DAT_GameSynchronyState::instance.currentPlayerSlotID]
            != 0) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, 0x10),
                posX, iVar4, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0xf, FALSE, 0);
        } else {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, 0x11),
                posX, iVar4, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0xf, FALSE, 0);
        }
        iVar4 = iVar4 + 0x39;
        piVar5 = DAT_BlendingDefinedData::instance.PlayerSlotUnitColor + 1;
        textAddress = DAT_GameSynchronyState::instance.DAT_PlayerNames + 1;
        local_8 = DAT_GameState::instance.mapAndTime.playerIsAlive + 1;
        do {
            if (*local_8 != 0) {
                if ((DAT_TextManagerObject::instance.gameLanguage == OpenSHC::Text::GL_ENGLISH)
                    || (DAT_TextManagerObject::instance.gameLanguage == OpenSHC::Text::GL_AMERICAN)) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                        DAT_TextManagerObject::ptr)(*textAddress, posX + -0x1c, iVar4, OpenSHC::Text::TTA_CENTER,
                        (uint)(DAT_RenderingDefinedData::instance.ColorArray[*piVar5]), 0, 0x11, FALSE, 0);
                    /*
                      added by script: "Wins"
                     */
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x40),
                        DAT_TextManagerObject::instance.currentXOffset_0x0 / 2 + -0x16 + posX, iVar4,
                        OpenSHC::Text::TTA_LEFT,
                        (uint)(DAT_RenderingDefinedData::instance.ColorArray[*piVar5]), 0, 0x11, FALSE, 0);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                        DAT_TextManagerObject::ptr)(*textAddress, posX + -0x4e, iVar4, OpenSHC::Text::TTA_CENTER,
                        (uint)(DAT_RenderingDefinedData::instance.ColorArray[*piVar5]), 0, 0x12, FALSE, 0);
                    /*
                      added by script: "Wins"
                     */
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x40),
                        DAT_TextManagerObject::instance.currentXOffset_0x0 / 2 + -0x48 + posX, iVar4,
                        OpenSHC::Text::TTA_LEFT,
                        (uint)(DAT_RenderingDefinedData::instance.ColorArray[*piVar5]), 0, 0x12, FALSE, 0);
                }
                iVar4 = iVar4 + 0x1e;
            }
            local_8 = local_8 + 1;
            piVar5 = piVar5 + 1;
            textAddress = textAddress + 1;
        } while ((int)local_8 < (int)&DAT_GameState::instance + 0x53e9a);
        ;
    }

}
}
