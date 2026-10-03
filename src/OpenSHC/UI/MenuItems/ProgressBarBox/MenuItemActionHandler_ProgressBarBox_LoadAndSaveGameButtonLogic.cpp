#include "../ProgressBarBox.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/IO/FilePackager.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/Audio/SFX/SpeechEffectID.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"
#include "OpenSHC/Globals/DAT_WallAndPitchState.hpp"
#include "OpenSHC/Globals/FilePackagerObj.hpp"
#include "OpenSHC/Globals/INT_00b95b64.hpp"
#include "OpenSHC/Globals/INT_00b960e4.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Audio::MSS::enums::SHC_SoundStream;
        using OpenSHC::Audio::SFX::SpeechEffectID;
        using OpenSHC::Commands::GameCommandType;
        using OpenSHC::Game::GameMode;
        using OpenSHC::Game::GameMode2;
        using OpenSHC::IO::FileResourceType;
        using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
        using OpenSHC::UI::Enums::DisplayElementID;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::UI::Enums::MenuViewType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004950B0
        void ProgressBarBox::MenuItemActionHandler_ProgressBarBox_LoadAndSaveGameButtonLogic(int param_1, ...)
        {
            char cVar1;
            char* pcVar2;
            int iVar3;
            undefined4 uVar4;
            char* pcVar5;
            undefined4 uVar6;
            FileResourceType FVar7;
            char local_3f4[4];
            char local_3f0[1004];
            uint local_4;
            int _mapNameIndex;
            local_4 = MSVC_SecurityCookie::instance ^ (uint)local_3f4;
            if (((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY)
                    && (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER))
                && (DAT_GameSynchronyState::instance.saveRelated != 0))
                goto LAB_004957df;
            if (DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter == 0x1f) {
                /*
                  load game logic
                 */
                iVar3 = DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset
                    + DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionIndex;
                DAT_VideoBikQueue::instance.storedMessages_0x924 = 0;
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition2::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_UNUSED_CREATE_SIEGE) {
                    pcVar2 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                        DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + -1]);
                    pcVar5 = local_3f4;
                    do {
                        cVar1 = *pcVar2;
                        *pcVar5 = cVar1;
                        pcVar2 = pcVar2 + 1;
                        pcVar5 = pcVar5 + 1;
                    } while (cVar1 != '\0');
                    MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::setTextEntryAndUpdateCursor,
                        DAT_UserTextHandlerState::ptr)(2,(char *)(local_3f4));
                    pcVar5 = local_3f4 - 1;
                    do {
                        pcVar2 = pcVar5 + 1;
                        pcVar5 = pcVar5 + 1;
                    } while (*pcVar2 != '\0');
                    (*(char*)&uVar6) = '.';
                    (*(char*)((char*)&uVar6 + 1)) = 't';
                    (*(char*)((char*)&uVar6 + 2)) = 'm';
                    (*(char*)((char*)&uVar6 + 3)) = 'p';
                LAB_0049553a:
                    *(undefined4*)pcVar5 = uVar6;
                    pcVar5[4] = '\0';
                    FVar7 = OpenSHC::IO::FRT_MAPS;
                } else {
                    if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_CUSTOM_SCENARIOS) {
                        pcVar2 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                            DAT_ResourceManager::ptr)(
                            DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + -1]);
                        pcVar5 = local_3f4;
                        do {
                            cVar1 = *pcVar2;
                            *pcVar5 = cVar1;
                            pcVar2 = pcVar2 + 1;
                            pcVar5 = pcVar5 + 1;
                        } while (cVar1 != '\0');
                        MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::setTextEntryAndUpdateCursor,
                            DAT_UserTextHandlerState::ptr)(2,(char *)(local_3f4));
                        pcVar5 = local_3f4 - 1;
                        do {
                            pcVar2 = pcVar5 + 1;
                            pcVar5 = pcVar5 + 1;
                        } while (*pcVar2 != '\0');
                        (*(char*)&uVar6) = '.';
                        (*(char*)((char*)&uVar6 + 1)) = 'm';
                        (*(char*)((char*)&uVar6 + 2)) = 'a';
                        (*(char*)((char*)&uVar6 + 3)) = 'p';
                        goto LAB_0049553a;
                    }
                    if ((DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY)
                        || (DAT_GameSynchronyState::instance.currentGameMode
                            == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)) {
                        pcVar2 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                            DAT_ResourceManager::ptr)(
                            DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + -1]);
                        pcVar5 = local_3f4;
                        do {
                            cVar1 = *pcVar2;
                            *pcVar5 = cVar1;
                            pcVar2 = pcVar2 + 1;
                            pcVar5 = pcVar5 + 1;
                        } while (cVar1 != '\0');
                        MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::setTextEntryAndUpdateCursor,
                            DAT_UserTextHandlerState::ptr)(2,(char *)(local_3f4));
                        pcVar5 = local_3f4 - 1;
                        do {
                            pcVar2 = pcVar5;
                            pcVar5 = pcVar2 + 1;
                        } while (pcVar2[1] != '\0');
                        strcpy(pcVar2 + 1, ".sav");
                        FVar7 = OpenSHC::IO::FRT_UNKNOWN;
                    } else {
                        iVar3 = 0;
                        if (DAT_GameSynchronyState::instance.isHost == FALSE) {
                            do {
                                cVar1 = DAT_GameSynchronyState::instance.shortMapName[iVar3];
                                local_3f4[iVar3] = cVar1;
                                iVar3 = iVar3 + 1;
                            } while (cVar1 != '\0');
                            MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::setTextEntryAndUpdateCursor,
                                DAT_UserTextHandlerState::ptr)(2,(char *)(local_3f4));
                            pcVar5 = local_3f4 - 1;
                            do {
                                pcVar2 = pcVar5 + 1;
                                pcVar5 = pcVar5 + 1;
                            } while (*pcVar2 != '\0');
                        } else {
                            do {
                                cVar1 = DAT_GameSynchronyState::instance.shortMapName[iVar3];
                                local_3f4[iVar3] = cVar1;
                                iVar3 = iVar3 + 1;
                            } while (cVar1 != '\0');
                            MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::setTextEntryAndUpdateCursor,
                                DAT_UserTextHandlerState::ptr)(2,(char *)(local_3f4));
                            pcVar5 = local_3f4 - 1;
                            do {
                                pcVar2 = pcVar5 + 1;
                                pcVar5 = pcVar5 + 1;
                            } while (*pcVar2 != '\0');
                        }
                        strcpy(pcVar5, ".msv");
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::TileMapState_Func::setupAllMapSections, DAT_TileMapState::ptr)();
                        FVar7 = OpenSHC::IO::FRT_UNKNOWN;
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                    FVar7, (char const*)((int)(local_3f4)));
                DAT_SoundSystemState::instance.streamFlagsUnkAndLoopCount_0x34[4] = 0;
                DAT_SoundSystemState::instance.streamFlagsUnkAndLoopCount_0x34[3] = 0;
                MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                    OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_1);
                MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                    OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_2);
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_GENERAL_LOADING);
                FilePackagerObj::instance.loadAndSaveBarFunc = MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderLoadAndSaveBar);
                MACRO_CALL_MEMBER(OpenSHC::IO::FilePackager_Func::readMapOrSavFile, FilePackagerObj::ptr)(
                    DAT_MapDefinedData::instance.MapSectionAddressArray);
                INT_00b95b64::instance = 1;
                DAT_GameCore::instance.isBinkVideoPlaying = 0;
                DAT_BuildingsState::instance.DAT_IsBuildingOrPeasantBinkPlaying = FALSE;
                MACRO_CALL_MEMBER(
                    OpenSHC::Rendering::Bink::BinkControlClass_Func::stopAllBinkPlayback, DAT_BinkControlState::ptr)();
                DAT_SoundSystemState::instance.currentSoundID_0x3278 = -1;
                MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::setSomeSoundTime, DAT_SoundSystemState::ptr)();
                if (DAT_SoundSystemState::instance.sec_Section1055_0x3274 < 0) {
                    DAT_SoundSystemState::instance.sec_Section1055_0x3274 = 0;
                }
                MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::setupVolumeAndSoundID,
                    DAT_SoundSystemState::ptr)((OpenSHC::DE::SHCDE::eMusicIDs)(DAT_SoundSystemState::instance.sec_Section1055_0x3274));
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::prepareMap, DAT_TileMapState::ptr)();
                MACRO_CALL_MEMBER(
                    OpenSHC::Rendering::Bink::AIMessageQueue_Func::playNextStoredBinkVideo, DAT_VideoBikQueue::ptr)();
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
                DAT_MenuTextInputState::instance.dialogResult = 1;
                MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(OpenSHC::UI::Enums::DEID_MISSION_WIN_DEFEAT_BANNER, 0);
                MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(OpenSHC::UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO, 0);
                MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(OpenSHC::UI::Enums::DEID_PLAYER_INFO_ON_HOVER, 0);
                MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(OpenSHC::UI::Enums::DEID_WIN_DEFEAT_WINDOW, 0);
                if (DAT_MenuModalComposition2::instance.activeModalDialogID
                    == OpenSHC::UI::Enums::MMT_DISPLAY_AI_LORD_MESSAGE) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition2::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                }
                DAT_UnitsState::instance.lastSelectedUnitID = 0;
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::clearSelectionCountsAndPlayerIDs, DAT_UnitsState::ptr)();
                iVar3 = DAT_SoundSystemState::instance.currentSoundID_0x3278;
                if (DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_UNUSED_CREATE_SIEGE) {
                    if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_CUSTOM_SCENARIOS) {
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_MAP_EDITOR_PROPERTIES, 0);
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[0] = -1;
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[1] = -1;
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[2] = -1;
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[3] = -1;
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[4] = -1;
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[5] = -1;
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[6] = -1;
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[7] = -1;
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[8] = -1;
                        if (DAT_GameSynchronyState::instance.currentPlayerSlotID == 0) {
                            DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                        }
                        DAT_GameSynchronyState::instance
                            .currentPlayerFullIDArray[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 1;
                        INT_00b960e4::instance = 1;
                        DAT_GameCore::instance.gameMode_2 = OpenSHC::Game::GM_EDITOR;
                        DAT_GameState::instance.playerDataArray[1].playerDeathRelated = 0;
                        DAT_GameState::instance.playerDataArray[2].playerDeathRelated = 0;
                        DAT_GameState::instance.playerDataArray[3].playerDeathRelated = 0;
                        DAT_GameState::instance.playerDataArray[4].playerDeathRelated = 0;
                        DAT_GameState::instance.playerDataArray[5].playerDeathRelated = 0;
                        DAT_GameState::instance.playerDataArray[6].playerDeathRelated = 0;
                        DAT_GameState::instance.playerDataArray[7].playerDeathRelated = 0;
                        DAT_GameState::instance.playerDataArray[8].playerDeathRelated = 0;
                    } else if ((DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY)
                        || (DAT_GameSynchronyState::instance.currentGameMode
                            == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)) {
                        DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                            = OpenSHC::UI::Enums::BASMTT_HUNTERSHUT;
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
                        if (0 < iVar3) {
                            DAT_SoundSystemState::instance.currentSoundID_0x3278 = iVar3;
                        }
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[0] = -1;
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[1] = -1;
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[2] = -1;
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[3] = -1;
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[4] = -1;
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[5] = -1;
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[6] = -1;
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[7] = -1;
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[8] = -1;
                        if (DAT_GameSynchronyState::instance.currentPlayerSlotID == 0) {
                            DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                        }
                        DAT_GameSynchronyState::instance
                            .currentPlayerFullIDArray[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 1;
                        if ((DAT_GameSynchronyState::instance.currentGameMode
                                == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)
                            && (DAT_GameCore::instance.lordIcons[1] = DAT_GameCore::instance.lordIconUnk,
                                1 < DAT_GameCore::instance.lordIconUnk)) {
                            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                                DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_SHARE_AIV_HASH);
                        }
                    } else {
                        DAT_GameCore::instance.gameMode_2 = OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER;
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_UNKNOWN_33, 0);
                    }
                }
            } else if ((DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter == 0x20)
                || (DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter == 0x2e)) {
                /*
                  Save logic?
                 */
                DAT_UserTextHandlerState::instance.allowUserTextInput = 0;
                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    2);
                DAT_UserTextHandlerState::instance.allowUserTextInput = 1;
                if (DAT_MenuTextInputState::instance.field49_0xac == 0) {
                    if ((DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_MAP_EDITOR_PROPERTIES)
                        || (DAT_GameCore::instance.currentMenuViewType
                            == OpenSHC::UI::Enums::MVT_UNUSED_CREATE_SIEGE)) {
                        pcVar2 = MACRO_CALL_MEMBER(
                            OpenSHC::Text::UserTextHandler_Func::getCurrentText, DAT_UserTextHandlerState::ptr)();
                        pcVar5 = local_3f4;
                        do {
                            cVar1 = *pcVar2;
                            *pcVar5 = cVar1;
                            pcVar2 = pcVar2 + 1;
                            pcVar5 = pcVar5 + 1;
                        } while (cVar1 != '\0');
                        pcVar5 = local_3f4 - 1;
                        do {
                            pcVar2 = pcVar5 + 1;
                            pcVar5 = pcVar5 + 1;
                        } while (*pcVar2 != '\0');
                        (*(char*)&uVar4) = '.';
                        (*(char*)((char*)&uVar4 + 1)) = 'm';
                        (*(char*)((char*)&uVar4 + 2)) = 'a';
                        (*(char*)((char*)&uVar4 + 3)) = 'p';
                        goto LAB_0049529d;
                    }
                    if ((DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY)
                        || (DAT_GameSynchronyState::instance.currentGameMode
                            == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)) {
                        pcVar2 = MACRO_CALL_MEMBER(
                            OpenSHC::Text::UserTextHandler_Func::getCurrentText, DAT_UserTextHandlerState::ptr)();
                        pcVar5 = local_3f4;
                        do {
                            cVar1 = *pcVar2;
                            *pcVar5 = cVar1;
                            pcVar2 = pcVar2 + 1;
                            pcVar5 = pcVar5 + 1;
                        } while (cVar1 != '\0');
                        pcVar5 = local_3f4 - 1;
                        do {
                            pcVar2 = pcVar5;
                            pcVar5 = pcVar2 + 1;
                        } while (pcVar2[1] != '\0');
                        strcpy(pcVar2 + 1, ".sav");
                        FVar7 = OpenSHC::IO::FRT_UNKNOWN;
                    } else {
                        iVar3 = 0;
                        if (DAT_GameSynchronyState::instance.isHost == FALSE) {
                            do {
                                cVar1 = DAT_GameSynchronyState::instance.shortMapName[iVar3];
                                local_3f4[iVar3] = cVar1;
                                iVar3 = iVar3 + 1;
                            } while (cVar1 != '\0');
                            pcVar5 = local_3f4 - 1;
                            do {
                                pcVar2 = pcVar5;
                                pcVar5 = pcVar2 + 1;
                            } while (pcVar2[1] != '\0');
                            strcpy(pcVar2 + 1, ".msv");
                            FVar7 = OpenSHC::IO::FRT_UNKNOWN;
                        } else {
                            do {
                                cVar1 = DAT_GameSynchronyState::instance.shortMapName[iVar3];
                                local_3f4[iVar3] = cVar1;
                                iVar3 = iVar3 + 1;
                            } while (cVar1 != '\0');
                            pcVar5 = local_3f4 - 1;
                            do {
                                pcVar2 = pcVar5;
                                pcVar5 = pcVar2 + 1;
                            } while (pcVar2[1] != '\0');
                            strcpy(pcVar2 + 1, ".msv");
                            FVar7 = OpenSHC::IO::FRT_UNKNOWN;
                        }
                    }
                } else {
                    pcVar2 = MACRO_CALL_MEMBER(
                        OpenSHC::Text::UserTextHandler_Func::getCurrentText, DAT_UserTextHandlerState::ptr)();
                    pcVar5 = local_3f4;
                    do {
                        cVar1 = *pcVar2;
                        *pcVar5 = cVar1;
                        pcVar2 = pcVar2 + 1;
                        pcVar5 = pcVar5 + 1;
                    } while (cVar1 != '\0');
                    pcVar5 = local_3f4 - 1;
                    do {
                        pcVar2 = pcVar5 + 1;
                        pcVar5 = pcVar5 + 1;
                    } while (*pcVar2 != '\0');
                    (*(char*)&uVar4) = '.';
                    (*(char*)((char*)&uVar4 + 1)) = 't';
                    (*(char*)((char*)&uVar4 + 2)) = 'm';
                    (*(char*)((char*)&uVar4 + 3)) = 'p';
                LAB_0049529d:
                    *(undefined4*)pcVar5 = uVar4;
                    pcVar5[4] = '\0';
                    FVar7 = OpenSHC::IO::FRT_MAPS;
                }
                MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                    FVar7, (char const*)((int)(local_3f4)));
                DAT_UserTextHandlerState::instance.allowUserTextInput = 0;
                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    9);
                DAT_UserTextHandlerState::instance.allowUserTextInput = 1;
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_GENERAL_SAVING);
                FilePackagerObj::instance.loadAndSaveBarFunc = MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderLoadAndSaveBar);
                MACRO_CALL_MEMBER(OpenSHC::IO::FilePackager_Func::writeMapOrSaveFile, FilePackagerObj::ptr)(
                    DAT_MapDefinedData::instance.MapSectionAddressArray);
                INT_00b95b64::instance = 1;
                DAT_WallAndPitchState::instance.countdown = 0;
                DAT_MenuTextInputState::instance.field44_0xa4 = 1;
                if ((DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY)
                    || (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
                }
                if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_MAP_EDITOR_PROPERTIES) {
                    MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::loadMapHeaders, DAT_ResourceManager::ptr)(
                        FALSE);
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
        LAB_004957df:;
            return;
        }

    }
}
}
