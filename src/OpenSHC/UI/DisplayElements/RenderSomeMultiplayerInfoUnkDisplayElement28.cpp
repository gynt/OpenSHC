#include "../DisplayElements.func.hpp"

#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Commands::GameCommandType;
    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::UI::Enums::DisplayElementID;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004B2530
    void DisplayElements::RenderSomeMultiplayerInfoUnkDisplayElement28(int posX, int posY, DWORD elementState)
    {
        eTextSections offsetIndex;
        BGR24 BVar5;
        DWORD _currentTime = timeGetTime();
        if (DAT_GameCore::instance.mapU4Int0 != 0) {
            posY = posY + 0x41;
        }
        if (DAT_GameSynchronyState::instance.DAT_SomeTime == 0) {
            if (DAT_GameSynchronyState::instance.isHost != FALSE) {
                if (DAT_GameSynchronyState::instance
                        .currentPlayerFullIDArray[DAT_GameSynchronyState::instance.laggingPlayerIDUnk]
                    == -1) {
                    DAT_GameSynchronyState::instance.DAT_SomeTime = _currentTime;
                    DAT_GameSynchronyState::instance.lagNotificationCode = 0x41;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        (OpenSHC::Commands::GameCommandType)(OpenSHC::Commands::GCT_SEND_RESYNC_TILEMAPDATA2
                            | OpenSHC::Commands::GCT_CHANGE_RATIONS));
                } else if (_currentTime
                        - DAT_GameSynchronyState::instance
                            .connectionLagInfoArray[DAT_GameSynchronyState::instance.laggingPlayerIDUnk]
                            .time
                    <= 10000) {
                    DAT_GameSynchronyState::instance.DAT_SomeTime = _currentTime;
                    DAT_GameSynchronyState::instance.lagNotificationCode = 0x43;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        (OpenSHC::Commands::GameCommandType)(OpenSHC::Commands::GCT_SEND_RESYNC_TILEMAPDATA2
                            | OpenSHC::Commands::GCT_CHANGE_RATIONS));
                }
            }
        } else if (2000 < _currentTime - DAT_GameSynchronyState::instance.DAT_SomeTime) {
            DAT_GameSynchronyState::instance.DAT_SomeTime = 0;
            DAT_GameSynchronyState::instance.laggingPlayerIDUnk = 0;
            MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                OpenSHC::UI::Enums::DEID_SOME_MULTIPLAYER_INFO_Unk_28, 0);
            return;
        }
        DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderedBoxWithBlendedBackground,
            DAT_PencilRenderCore::ptr)(posX + -0xcc, posY, 0x198, 0x60);
        DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        int iVar2 = posY + 0x14;
        int iVar3 = posX + -0xbe;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance.finalResults.names[DAT_GameSynchronyState::instance.laggingPlayerIDUnk],
            iVar3, iVar2, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x12, FALSE, 0);
        /*
          ": Not Responding"   added by script: ": Not Responding"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x40),
            iVar3, iVar2, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x12, TRUE, 0);
        if (DAT_GameSynchronyState::instance.DAT_SomeTime == 0) {
            DAT_ButtonX::instance = posX;
            DAT_ButtonY::instance = posY + 0x34;
            DAT_ButtonW::instance = 0xb4;
            DAT_ButtonH::instance = 0x1c;
            if (DAT_GameSynchronyState::instance.isHost != FALSE) {
                iVar2 = 0x3c
                    - (_currentTime
                          - DAT_GameSynchronyState::instance
                              .connectionLagInfoArray[DAT_GameSynchronyState::instance.laggingPlayerIDUnk]
                              .time)
                        / 1000;
                if (0x32 < iVar2) {
                    iVar2 = 0x32;
                } else if (iVar2 < 0) {
                    iVar2 = 0;
                }
                iVar3 = posY + 0x3a;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    iVar2, posX + -0x66, iVar3, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x12, FALSE, 0);
                BOOLEnum BVar7 = MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::isMouseInsideBox,
                    DAT_MouseState::ptr)(posX - DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX,
                    (posY - DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY) + 0x34, 0xb4, 0x1c);
                if (BVar7 != FALSE) {
                    DAT_ButtonCurrentlyInteracting::instance = TRUE;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    /*
                      "Eject"   added by script: "Eject"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x5b),
                        posX + 0x5a, iVar3, OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x12, FALSE, 0);
                    if (DAT_MouseState::instance.leftClickStart == 0)
                        return;
                    DAT_GameSynchronyState::instance.DAT_SomeTime = timeGetTime();
                    DAT_GameSynchronyState::instance.lagNotificationCode = 0x42;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        (OpenSHC::Commands::GameCommandType)(OpenSHC::Commands::GCT_SEND_RESYNC_TILEMAPDATA2
                            | OpenSHC::Commands::GCT_CHANGE_RATIONS));
                }
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                BVar5 = 0xc2f0eb;
                posX = posX + 0x5a;
                offsetIndex = OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM;
                iVar2 = 0x5b;
            } else {
                BVar5 = 0x7f7f7f;
                posX = posX + 0x5a;
                offsetIndex = OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM;
                iVar2 = 0x5b;
            }
        } else {
            BVar5 = 0xc2f0eb;
            offsetIndex = OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION;
            iVar2 = DAT_GameSynchronyState::instance.lagNotificationCode;
        }
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(offsetIndex, iVar2),
            posX, posY + 0x3a, OpenSHC::Text::TTA_CENTER, BVar5, 0x12, FALSE, 0);
    }

}
}
