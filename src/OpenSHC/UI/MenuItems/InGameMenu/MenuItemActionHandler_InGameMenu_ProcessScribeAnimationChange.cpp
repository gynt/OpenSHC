#include "../InGameMenu.func.hpp"

#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using Game::GameMode2;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00433370
        void InGameMenu::MenuItemActionHandler_InGameMenu_ProcessScribeAnimationChange(int param_1, ...)
        {
            int iVar1;
            DWORD _currentTime;
            int iVar2;
            iVar1 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            if (DAT_GameCore::instance.gameMode_2 == Game::GM_EDITOR) {}
            if (DAT_GameCore::instance.gameMode_2 == Game::GM_SIEGE_THAT) {}
            if (DAT_GameCore::instance.taxesSettingUnk) {
                _currentTime = timeGetTime();
                if ((int)(_currentTime - DAT_GameCore::instance.taxestimeUnk) < 0x3c) {}
                DAT_GameCore::instance.taxestimeUnk = _currentTime;
                if (!DAT_GameCore::instance.unknownScribeRelatedFlag_0x130) {
                    if (DAT_GameCore::instance.scribeAnimationFrame < 6) {
                        DAT_GameCore::instance.scribeAnimationFrame = DAT_GameCore::instance.scribeAnimationFrame + 1;
                    } else if (DAT_GameCore::instance.scribeAnimationFrame < 7) {
                        DAT_GameCore::instance.unknownScribeRelatedFlag_0x130 = TRUE;
                    } else {
                        DAT_GameCore::instance.scribeAnimationFrame = DAT_GameCore::instance.scribeAnimationFrame + -1;
                    }
                } else if (DAT_GameCore::instance.unknownScribeRelatedFlag_0x130 == TRUE) {
                    DAT_GameCore::instance.scribeAnimationFrame2 = DAT_GameCore::instance.scribeAnimationFrame2 + 1;
                } else if (DAT_GameCore::instance.unknownScribeRelatedFlag_0x130 == 2) {
                    iVar2 = (100 - DAT_GameState::instance.playerDataArray[iVar1].popularity / 100) / 10 + 1;
                    if (DAT_GameCore::instance.scribeAnimationFrame < 0xc) {
                        if (iVar2 < DAT_GameCore::instance.scribeAnimationFrame) {
                            DAT_GameCore::instance.scribeAnimationFrame
                                = DAT_GameCore::instance.scribeAnimationFrame + -1;
                        } else if (DAT_GameCore::instance.scribeAnimationFrame < iVar2) {
                            DAT_GameCore::instance.scribeAnimationFrame
                                = DAT_GameCore::instance.scribeAnimationFrame + 1;
                        } else {
                            DAT_GameCore::instance.taxesSettingUnk = 0;
                        }
                    } else {
                        DAT_GameCore::instance.scribeAnimationFrame = 6;
                    }
                }
            }
            iVar2 = DAT_GameCore::instance.scribeAnimationFrame;
            switch (DAT_GameCore::instance.taxesSettingUnk) {
            case 0:
                iVar2 = (100 - DAT_GameState::instance.playerDataArray[iVar1].popularity / 100) / 10 + 1;
                goto switchD_00433499_caseD_4;
            case 1:
                if (DAT_GameCore::instance.unknownScribeRelatedFlag_0x130 != TRUE)
                    goto switchD_00433499_caseD_4;
                iVar2 = DAT_RenderingDefinedData::instance
                            .ScribeAnimationFrames1[DAT_GameCore::instance.scribeAnimationFrame2];
                break;
            case 2:
                if (DAT_GameCore::instance.unknownScribeRelatedFlag_0x130 != TRUE)
                    goto switchD_00433499_caseD_4;
                iVar2 = DAT_RenderingDefinedData::instance
                            .ScribeAnimationFrames2[DAT_GameCore::instance.scribeAnimationFrame2];
                break;
            case 3:
                if (DAT_GameCore::instance.unknownScribeRelatedFlag_0x130 != TRUE)
                    goto switchD_00433499_caseD_4;
                iVar2 = DAT_RenderingDefinedData::instance
                            .ScribeAnimationFrames3[DAT_GameCore::instance.scribeAnimationFrame2];
                break;
            default:
                goto switchD_00433499_caseD_4;
            }
            if (!iVar2) {
                DAT_GameCore::instance.taxesSettingUnk = 0;
                iVar2 = DAT_GameCore::instance.scribeAnimationFrame;
            }
        switchD_00433499_caseD_4:
            DAT_GameCore::instance.scribeAnimationFrame = iVar2;
            if ((DAT_GameCore::instance.scribeAnimationFrameCopy != DAT_GameCore::instance.scribeAnimationFrame)
                || (DAT_GameState::instance.mapAndTime.monthChanged)) {
                DAT_GameCore::instance.countdown = 1;
                DAT_GameCore::instance.scribeAnimationFrameCopy = DAT_GameCore::instance.scribeAnimationFrame;
            }
        }

    }
}
}
