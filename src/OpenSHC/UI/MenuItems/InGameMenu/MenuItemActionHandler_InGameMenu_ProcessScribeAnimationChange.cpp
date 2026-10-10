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

        using OpenSHC::Game::GameMode2;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00433370
        void InGameMenu::MenuItemActionHandler_InGameMenu_ProcessScribeAnimationChange(int param_1, ...)
        {
            int iVar1;
            DWORD _currentTime;
            int iVar2;
            int iVar3;
            BOOLEnum BVar4;
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
                return;
            }
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                return;
            }
            iVar1 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            BVar4 = DAT_GameCore::instance.unknownScribeRelatedFlag_0x130;
            iVar3 = DAT_GameCore::instance.scribeAnimationFrame;
            if (DAT_GameCore::instance.taxesSettingUnk != 0) {
                _currentTime = timeGetTime();
                if ((int)(_currentTime - DAT_GameCore::instance.taxestimeUnk) < 0x3c) {
                    return;
                }
                BVar4 = DAT_GameCore::instance.unknownScribeRelatedFlag_0x130;
                DAT_GameCore::instance.taxestimeUnk = _currentTime;
                /*
                  the original dispatches with a `sub eax, K; je` chain (0x4333c2),
                  MSVC's sparse switch, whose arms are written in the reverse of the
                  test order
                 */
                switch (BVar4) {
                case 2:
                    iVar2 = (100 - DAT_GameState::instance.playerDataArray[iVar1].popularity / 100) / 10 + 1;
                    iVar3 = DAT_GameCore::instance.scribeAnimationFrame;
                    if (iVar3 <= 0xb) {
                        if (iVar3 > iVar2) {
                            DAT_GameCore::instance.scribeAnimationFrame = iVar3 + -1;
                        } else if (iVar3 >= iVar2) {
                            DAT_GameCore::instance.taxesSettingUnk = 0;
                        } else {
                            DAT_GameCore::instance.scribeAnimationFrame = iVar3 + 1;
                        }
                    } else {
                        iVar3 = 6;
                        DAT_GameCore::instance.scribeAnimationFrame = 6;
                    }
                    break;
                case TRUE:
                    DAT_GameCore::instance.scribeAnimationFrame2 = DAT_GameCore::instance.scribeAnimationFrame2 + 1;
                    iVar3 = DAT_GameCore::instance.scribeAnimationFrame;
                    break;
                case FALSE:
                    iVar3 = DAT_GameCore::instance.scribeAnimationFrame;
                    if (iVar3 < 6) {
                        DAT_GameCore::instance.scribeAnimationFrame = iVar3 + 1;
                    } else if (iVar3 > 6) {
                        DAT_GameCore::instance.scribeAnimationFrame = iVar3 + -1;
                    } else {
                        BVar4 = TRUE;
                        DAT_GameCore::instance.unknownScribeRelatedFlag_0x130 = TRUE;
                    }
                    break;
                }
            }
            switch (DAT_GameCore::instance.taxesSettingUnk) {
            case 0:
                iVar3 = (100 - DAT_GameState::instance.playerDataArray[iVar1].popularity / 100) / 10 + 1;
                DAT_GameCore::instance.scribeAnimationFrame = iVar3;
                break;
            case 1:
                if (BVar4 == TRUE) {
                    iVar2 = DAT_RenderingDefinedData::instance
                                .field1027_0x5493c[DAT_GameCore::instance.scribeAnimationFrame2];
                    if (iVar2 == 0) {
                        DAT_GameCore::instance.taxesSettingUnk = 0;
                    } else {
                        iVar3 = iVar2;
                        DAT_GameCore::instance.scribeAnimationFrame = iVar2;
                    }
                }
                break;
            case 2:
                if (BVar4 == TRUE) {
                    iVar2 = DAT_RenderingDefinedData::instance
                                .field1028_0x5499c[DAT_GameCore::instance.scribeAnimationFrame2];
                    if (iVar2 == 0) {
                        DAT_GameCore::instance.taxesSettingUnk = 0;
                    } else {
                        iVar3 = iVar2;
                        DAT_GameCore::instance.scribeAnimationFrame = iVar2;
                    }
                }
                break;
            case 3:
                if (BVar4 == TRUE) {
                    iVar2 = DAT_RenderingDefinedData::instance
                                .field1029_0x549fc[DAT_GameCore::instance.scribeAnimationFrame2];
                    if (iVar2 == 0) {
                        DAT_GameCore::instance.taxesSettingUnk = 0;
                    } else {
                        iVar3 = iVar2;
                        DAT_GameCore::instance.scribeAnimationFrame = iVar2;
                    }
                }
                break;
            }
            if ((DAT_GameCore::instance.scribeAnimationFrameCopy != iVar3)
                || (DAT_GameState::instance.mapAndTime.monthChanged != 0)) {
                DAT_GameCore::instance.countdown = 1;
                DAT_GameCore::instance.scribeAnimationFrameCopy = iVar3;
            }
        }

    }
}
}
