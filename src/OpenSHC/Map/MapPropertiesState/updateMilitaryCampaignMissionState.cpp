#include "../../Map.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition3.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::Map::MapType2;
    using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
    using OpenSHC::UI::Enums::DisplayElementID;
    using OpenSHC::UI::Enums::MenuModalType;
    using OpenSHC::UI::Enums::MenuViewType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      Per-frame update for the scripted military campaign missions (16-20). Handles win/loss   conditions, timed
      dialogue video sequences (Bink + WAV), spawn waves via   spawnAttackWaveForPlayer, and enemy kill tracking per
      mission number. Each mission (0x10-0x14)   has its own state machine driven by field3204_0x27d4 and
      monthCopy/yearCopy timers. On win sets   playerDeathRelated=1 and shows the victory banner; on loss sets
      playerDeathRelated=2 and switches   to MVT_GAME_LOSTUnk.      renamed by: Claude Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004C2280
    void MapPropertiesState::updateMilitaryCampaignMissionState()
    {
        short sVar1;
        bool bVar2;
        bool bVar3;
        bool bVar4;
        char* pcVar5;
        bool bVar6;
        int iVar7;
        char* pcVar8;
        char* pcVar9;
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .playerDeathRelated
            != 0) {
            if ((DAT_BinkControlState::instance.binkObjPtrArray[1] == (HBINK)0x0)
                && (DAT_VideoBikQueue::instance.storedMessages_0x924 == 0)) {
                DAT_GameState::instance.mapAndTime.unknownCountdown01
                    = DAT_GameState::instance.mapAndTime.unknownCountdown01 + -1;
            }
            if (DAT_GameState::instance.mapAndTime.unknownCountdown01 == 0) {
                DAT_VideoBikQueue::instance.storedMessages_0x924 = 0;
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition2::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition3::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                DAT_MenuTextInputState::instance.DAT_SomeTextArrayIndex = 9;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION) {
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .playerDeathRelated
                        == 1) {
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::incrementMissionProgress, DAT_GameCore::ptr)();
                        DAT_GameCore::instance.section1066 = 2;
                    }
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .playerDeathRelated
                        == 2) {
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_GAME_LOSTUnk, 0);
                        DAT_GameCore::instance.section1066 = 0;
                    }
                    MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                        OpenSHC::UI::Enums::DEID_MISSION_WIN_DEFEAT_BANNER, 0);
                }
                MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                    OpenSHC::UI::Enums::DEID_MISSION_WIN_DEFEAT_BANNER, 0);
            }
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .lordKilledByPlayerID
            != 0) {
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .playerDeathRelated = 2;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setAIControlStatusTo100000, DAT_UnitsState::ptr)();
            DAT_GameState::instance.mapAndTime.unknownCountdown01 = 0xf0;
            if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk)
                && (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE)) {
                DAT_GameState::instance.mapAndTime.unknownCountdown01 = 0x280;
            }
            MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                OpenSHC::UI::Enums::DEID_MISSION_WIN_DEFEAT_BANNER, 2);
            if ((DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                    == OpenSHC::UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM)
                || (DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                    == OpenSHC::UI::Enums::BASMTT_SIEGETENT_SHIELD)) {
                DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab
                    = DAT_GameCore::instance.tabTypeSiegeSubset;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
            }
            DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_NULL;
            if (0 < DAT_UnitsState::instance.totalUnitsInSelection) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::queueEscapeCommand, DAT_UnitsState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseCursorState, DAT_MouseState::ptr)();
            }
            DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_NULL;
        }
        if (DAT_GameCore::instance.missionNumber1to20 == 0x10) {
            if (DAT_GameState::instance.mapAndTime.field3179_0x27d4 == 0) {
                iVar7 = DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID;
                if (7 < DAT_GameState::instance.mapAndTime.emenyHitArray[2]
                        + DAT_GameState::instance.mapAndTime.emenyHitArray[1]
                        + DAT_GameState::instance.mapAndTime.emenyHitArray[4]
                        + DAT_GameState::instance.mapAndTime.emenyHitArray[5]
                        + DAT_GameState::instance.mapAndTime.emenyHitArray[6]
                        + DAT_GameState::instance.mapAndTime.emenyHitArray[7]
                        + DAT_GameState::instance.mapAndTime.emenyHitArray[8]
                        + DAT_GameState::instance.mapAndTime.emenyHitArray[3]) {
                    pcVar9 = "Ap_Milit21.wav";
                    pcVar8 = "good_soldier_nervous.bik";
                    DAT_GameState::instance.mapAndTime.field3179_0x27d4 = 1;
                    pcVar5 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_NEW_TEXT2, 1);
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                        DAT_VideoBikQueue::ptr)(pcVar5, pcVar8, pcVar9);
                    DAT_GameState::instance.mapAndTime.monthCopy = (short)DAT_GameState::instance.mapAndTime.month + 3;
                    DAT_GameState::instance.mapAndTime.yearCopy = (short)DAT_GameState::instance.mapAndTime.year;
                    iVar7 = DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID;
                    if (0xb < DAT_GameState::instance.mapAndTime.month) {
                        DAT_GameState::instance.mapAndTime.month = DAT_GameState::instance.mapAndTime.month + -0xc;
                        DAT_GameState::instance.mapAndTime.year = DAT_GameState::instance.mapAndTime.year + 1;
                    }
                }
            LAB_004c24df:
                if (iVar7 != 0) {
                    DAT_GameState::instance.mapAndTime.field3179_0x27d4 = 3;
                }
            }
            if (DAT_GameState::instance.mapAndTime.field3179_0x27d4 == 1) {
                if ((DAT_GameState::instance.mapAndTime.month == DAT_GameState::instance.mapAndTime.monthCopy)
                    && (DAT_GameState::instance.mapAndTime.year == DAT_GameState::instance.mapAndTime.yearCopy)) {
                    pcVar9 = "Ap_Milit22.wav";
                    pcVar8 = "good_soldier_nervous.bik";
                    DAT_GameState::instance.mapAndTime.field3179_0x27d4 = 2;
                    pcVar5 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_NEW_TEXT2, 2);
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                        DAT_VideoBikQueue::ptr)(pcVar5, pcVar8, pcVar9);
                    MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::spawnAttackWaveForPlayer, this)(
                        2, 0x18, 5, 0x4b, 10, 3);
                    DAT_GameState::instance.mapAndTime.monthCopy = (short)DAT_GameState::instance.mapAndTime.month + 1;
                    DAT_GameState::instance.playerDataArray[2].currentWaveRandomAttackingStrength = 0;
                    DAT_GameState::instance.mapAndTime.yearCopy = (short)DAT_GameState::instance.mapAndTime.year;
                    if (0xb < DAT_GameState::instance.mapAndTime.month) {
                        DAT_GameState::instance.mapAndTime.month = DAT_GameState::instance.mapAndTime.month + -0xc;
                        DAT_GameState::instance.mapAndTime.year = DAT_GameState::instance.mapAndTime.year + 1;
                    }
                }
            LAB_004c25f4:
                if (DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID != 0) {
                    DAT_GameState::instance.mapAndTime.field3179_0x27d4 = 3;
                }
            }
            if (DAT_GameState::instance.mapAndTime.field3179_0x27d4 == 2) {
                if ((DAT_GameState::instance.mapAndTime.month == DAT_GameState::instance.mapAndTime.monthCopy)
                    && (DAT_GameState::instance.mapAndTime.year == DAT_GameState::instance.mapAndTime.yearCopy)) {
                    pcVar9 = "Ap_Milit23.wav";
                    pcVar8 = "bad_arab_taunt.bik";
                    DAT_GameState::instance.mapAndTime.field3179_0x27d4 = 3;
                    pcVar5 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_NEW_TEXT2, 3);
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                        DAT_VideoBikQueue::ptr)(pcVar5, pcVar8, pcVar9);
                }
                goto LAB_004c25f4;
            }
            if (DAT_GameState::instance.mapAndTime.field3179_0x27d4 == 4) {
                if (((DAT_GameState::instance.mapAndTime.month != DAT_GameState::instance.mapAndTime.monthCopy)
                        || (DAT_GameState::instance.mapAndTime.year != DAT_GameState::instance.mapAndTime.yearCopy))
                    && (DAT_GameState::instance.mapAndTime.year <= DAT_GameState::instance.mapAndTime.yearCopy)) {}
                DAT_GameState::instance.mapAndTime.field3179_0x27d4 = 5;
                goto LAB_004c3082;
            }
            if (DAT_GameState::instance.mapAndTime.field3179_0x27d4 != 3) {}
            if (DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID == 0) {}
            pcVar9 = "Ap_Milit24.wav";
            pcVar8 = "good_soldier_taunt.bik";
            DAT_GameState::instance.mapAndTime.field3179_0x27d4 = 4;
            /*
              added by script: "The old Rat’s made a run for it.  We’ve done it sar!"
             */
            pcVar5 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_NEW_TEXT2, 4);
            MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                pcVar5, pcVar8, pcVar9);
            sVar1 = (short)DAT_GameState::instance.mapAndTime.month;
            DAT_GameState::instance.mapAndTime.yearCopy = (short)DAT_GameState::instance.mapAndTime.year;
            goto LAB_004c2d0b;
        }
        if (DAT_GameCore::instance.missionNumber1to20 == 0x11) {
            if (DAT_GameState::instance.mapAndTime.field3179_0x27d4 == 0) {
                if ((DAT_GameState::instance.mapAndTime.month == DAT_GameState::instance.mapAndTime.monthCopy)
                    && (DAT_GameState::instance.mapAndTime.year == DAT_GameState::instance.mapAndTime.yearCopy)) {
                    pcVar9 = "Ap_Milit25.wav";
                    pcVar8 = "good_soldier_nervous.bik";
                    DAT_GameState::instance.mapAndTime.field3179_0x27d4 = 1;
                    pcVar5 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_NEW_TEXT2, 5);
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                        DAT_VideoBikQueue::ptr)(pcVar5, pcVar8, pcVar9);
                    DAT_GameState::instance.mapAndTime.monthCopy = (short)DAT_GameState::instance.mapAndTime.month + 2;
                    DAT_GameState::instance.mapAndTime.yearCopy = (short)DAT_GameState::instance.mapAndTime.year;
                    if (0xb < DAT_GameState::instance.mapAndTime.month) {
                        DAT_GameState::instance.mapAndTime.month = DAT_GameState::instance.mapAndTime.month + -0xc;
                        DAT_GameState::instance.mapAndTime.year = DAT_GameState::instance.mapAndTime.year + 1;
                    }
                }
            LAB_004c28d6:
                if (DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID == 0) {}
                DAT_GameState::instance.mapAndTime.field3179_0x27d4 = 5;
            }
            if (DAT_GameState::instance.mapAndTime.field3179_0x27d4 == 1) {
                if ((DAT_GameState::instance.mapAndTime.month == DAT_GameState::instance.mapAndTime.monthCopy)
                    && (DAT_GameState::instance.mapAndTime.year == DAT_GameState::instance.mapAndTime.yearCopy)) {
                    pcVar9 = "Ap_Milit26.wav";
                    pcVar8 = "good_soldier_nervous.bik";
                    DAT_GameState::instance.mapAndTime.field3179_0x27d4 = 2;
                    /*
                      added by script: "Here they come sar.  Men, to arms!"
                     */
                    pcVar5 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_NEW_TEXT2, 6);
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                        DAT_VideoBikQueue::ptr)(pcVar5, pcVar8, pcVar9);
                    MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::spawnAttackWaveForPlayer, this)(
                        2, 0x48, 0x32, 0x47, 0x14, 3);
                    DAT_GameState::instance.playerDataArray[2].currentWaveRandomAttackingStrength = 0;
                }
                bVar6 = DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID == 0;
            } else if (DAT_GameState::instance.mapAndTime.field3179_0x27d4 == 2) {
                if (DAT_GameState::instance.playerDataArray[2].aiPlayerState == 4) {
                    pcVar9 = "Ap_Milit27.wav";
                    pcVar8 = "bad_soldier_taunt.bik";
                    DAT_GameState::instance.mapAndTime.field3179_0x27d4 = 3;
                    /*
                      added by script: "It’s now or never men.  Attack!"
                     */
                    pcVar5 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_NEW_TEXT2, 7);
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                        DAT_VideoBikQueue::ptr)(pcVar5, pcVar8, pcVar9);
                }
                bVar6 = DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID == 0;
            } else {
                if (DAT_GameState::instance.mapAndTime.field3179_0x27d4 != 3) {
                    if (DAT_GameState::instance.mapAndTime.field3179_0x27d4 != 4) {
                        if (DAT_GameState::instance.mapAndTime.field3179_0x27d4 != 6) {
                            if (DAT_GameState::instance.mapAndTime.field3179_0x27d4 != 5) {}
                            if (DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID != 0) {
                                pcVar9 = "Ap_Milit29.wav";
                                pcVar8 = "good_soldier_taunt.bik";
                                DAT_GameState::instance.mapAndTime.field3179_0x27d4 = 6;
                                /*
                                  added by script: "The slimy blighters legged it sar!  He’s left his general   in
                                  charge of the castle."
                                 */
                                pcVar5
                                    = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_NEW_TEXT2, 9);
                                MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                                    DAT_VideoBikQueue::ptr)(pcVar5, pcVar8, pcVar9);
                                DAT_GameState::instance.mapAndTime.yearCopy
                                    = (short)DAT_GameState::instance.mapAndTime.year;
                                DAT_GameState::instance.mapAndTime.monthCopy
                                    = (short)DAT_GameState::instance.mapAndTime.month + 1;
                                if (0xb < DAT_GameState::instance.mapAndTime.month) {
                                    DAT_GameState::instance.mapAndTime.year
                                        = DAT_GameState::instance.mapAndTime.year + 1;
                                    DAT_GameState::instance.mapAndTime.month
                                        = DAT_GameState::instance.mapAndTime.month + -0xc;
                                }
                            }
                        }
                        if (((DAT_GameState::instance.mapAndTime.month != DAT_GameState::instance.mapAndTime.monthCopy)
                                || (DAT_GameState::instance.mapAndTime.year
                                    != DAT_GameState::instance.mapAndTime.yearCopy))
                            && (DAT_GameState::instance.mapAndTime.year
                                <= DAT_GameState::instance.mapAndTime.yearCopy)) {}
                        DAT_GameState::instance.mapAndTime.field3179_0x27d4 = 7;
                        goto LAB_004c3082;
                    }
                    if ((DAT_GameState::instance.mapAndTime.month == DAT_GameState::instance.mapAndTime.monthCopy)
                        && (DAT_GameState::instance.mapAndTime.year == DAT_GameState::instance.mapAndTime.yearCopy)) {
                        pcVar9 = "Ap_Milit28.wav";
                        pcVar8 = "good_soldier_taunt.bik";
                        DAT_GameState::instance.mapAndTime.field3179_0x27d4 = 5;
                        /*
                          added by script: "I think we’ve rattled the snake sar!"
                         */
                        pcVar5 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_NEW_TEXT2, 8);
                        MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                            DAT_VideoBikQueue::ptr)(pcVar5, pcVar8, pcVar9);
                    }
                    goto LAB_004c28d6;
                }
                if ((DAT_GameState::instance.playerDataArray[2].aiPlayerState == 8)
                    || (DAT_GameState::instance.playerDataArray[2].aiPlayerState == 9)) {
                    DAT_GameState::instance.mapAndTime.monthCopy = (short)DAT_GameState::instance.mapAndTime.month + 2;
                    DAT_GameState::instance.mapAndTime.field3179_0x27d4 = 4;
                    DAT_GameState::instance.mapAndTime.yearCopy = (short)DAT_GameState::instance.mapAndTime.year;
                    if (0xb < DAT_GameState::instance.mapAndTime.month) {
                        DAT_GameState::instance.mapAndTime.month = DAT_GameState::instance.mapAndTime.month + -0xc;
                        DAT_GameState::instance.mapAndTime.year = DAT_GameState::instance.mapAndTime.year + 1;
                    }
                }
                bVar6 = DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID == 0;
            }
            goto LAB_004c2cc1;
        }
        if (DAT_GameCore::instance.missionNumber1to20 == 0x12) {
            if (DAT_GameState::instance.mapAndTime.field3179_0x27d4 == 0) {
                if (DAT_GameState::instance.mapAndTime.month != DAT_GameState::instance.mapAndTime.monthCopy) {}
                if (DAT_GameState::instance.mapAndTime.year == DAT_GameState::instance.mapAndTime.yearCopy) {
                    DAT_GameState::instance.playerDataArray[2].currentWaveRandomAttackingStrength = 0;
                    DAT_GameState::instance.playerDataArray[3].currentWaveRandomAttackingStrength = 0;
                    DAT_GameState::instance.mapAndTime.field3179_0x27d4 = 1;
                    DAT_GameState::instance.playerDataArray[2].aiAttackCoordinationLevel = 1;
                    DAT_GameState::instance.playerDataArray[3].aiAttackCoordinationLevel = 1;
                }
            }
            if (DAT_GameState::instance.mapAndTime.field3179_0x27d4 == 1) {
                if ((1 < DAT_GameState::instance.playerDataArray[2].aiPlayerState)
                    && (1 < DAT_GameState::instance.playerDataArray[3].aiPlayerState)) {
                    pcVar9 = "Ap_Milit30.wav";
                    pcVar8 = "good_soldier_nervous.bik";
                    DAT_GameState::instance.mapAndTime.field3179_0x27d4 = 2;
                    /*
                      added by script: "Sar, the Truffe brothers are launching a joint attack!  How   are we supposed to
                      hold out against both of them?"
                     */
                    pcVar5 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_NEW_TEXT2, 10);
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                        DAT_VideoBikQueue::ptr)(pcVar5, pcVar8, pcVar9);
                }
                iVar7 = DAT_GameState::instance.playerDataArray[3].lordKilledByPlayerID;
                if (DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID == 0) {}
                goto LAB_004c24df;
            }
            if (DAT_GameState::instance.mapAndTime.field3179_0x27d4 == 2) {
                if ((DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID == 0)
                    && (DAT_GameState::instance.playerDataArray[3].lordKilledByPlayerID == 0)) {}
                pcVar8 = "Ap_Milit32.wav";
                pcVar5 = "good_soldier_taunt.bik";
                DAT_GameState::instance.mapAndTime.field3179_0x27d4 = 3;
                iVar7 = 0xc;
                goto LAB_004c2dc2;
            }
            if (DAT_GameState::instance.mapAndTime.field3179_0x27d4 != 3) {
                if (DAT_GameState::instance.mapAndTime.field3179_0x27d4 != 4) {}
                if (((DAT_GameState::instance.mapAndTime.month != DAT_GameState::instance.mapAndTime.monthCopy)
                        || (DAT_GameState::instance.mapAndTime.year != DAT_GameState::instance.mapAndTime.yearCopy))
                    && (DAT_GameState::instance.mapAndTime.year <= DAT_GameState::instance.mapAndTime.yearCopy)) {}
                DAT_GameState::instance.mapAndTime.field3179_0x27d4 = 5;
                goto LAB_004c3082;
            }
            if (DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID == 0) {}
            if (DAT_GameState::instance.playerDataArray[3].lordKilledByPlayerID == 0) {}
            pcVar9 = "Ap_Milit33.wav";
            pcVar8 = "good_soldier_taunt.bik";
            DAT_GameState::instance.mapAndTime.field3179_0x27d4 = 4;
            /*
              added by script: "Not so bad after all.  Mission accomplished sar!"
             */
            pcVar5 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_NEW_TEXT2, 0xd);
            MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                pcVar5, pcVar8, pcVar9);
            DAT_GameState::instance.mapAndTime.yearCopy = (short)DAT_GameState::instance.mapAndTime.year;
        LAB_004c2cfc:
            sVar1 = (short)DAT_GameState::instance.mapAndTime.month;
        LAB_004c2d0b:
            DAT_GameState::instance.mapAndTime.monthCopy = sVar1 + 1;
            if (0xb < DAT_GameState::instance.mapAndTime.month) {
                DAT_GameState::instance.mapAndTime.year = DAT_GameState::instance.mapAndTime.year + 1;
                DAT_GameState::instance.mapAndTime.month = DAT_GameState::instance.mapAndTime.month + -0xc;
            }
        }
        if (DAT_GameCore::instance.missionNumber1to20 != 0x13) {
            if (DAT_GameCore::instance.missionNumber1to20 != 0x14) {}
            bVar6 = false;
            bVar4 = false;
            if (DAT_GameState::instance.mapAndTime.field3179_0x27d4 != 0) {
                if (DAT_GameState::instance.mapAndTime.field3179_0x27d4 != 1) {}
                if (DAT_GameState::instance.playerDataArray[3].lordKilledByPlayerID != 0) {
                    bVar6 = true;
                    if ((DAT_GameState::instance.mapAndTime.field3180_0x27d6 & 1U) == 0) {
                        DAT_GameState::instance.mapAndTime.field3180_0x27d6
                            = DAT_GameState::instance.mapAndTime.field3180_0x27d6 | 1;
                        DAT_GameState::instance.mapAndTime.yearCopy = (short)DAT_GameState::instance.mapAndTime.year;
                        DAT_GameState::instance.mapAndTime.monthCopy
                            = (short)DAT_GameState::instance.mapAndTime.month + 1;
                        if (0xb < DAT_GameState::instance.mapAndTime.month) {
                            DAT_GameState::instance.mapAndTime.month = DAT_GameState::instance.mapAndTime.month + -0xc;
                            DAT_GameState::instance.mapAndTime.year = DAT_GameState::instance.mapAndTime.year + 1;
                        }
                    } else if ((((DAT_GameState::instance.mapAndTime.field3180_0x27d6 & 0x10U) == 0)
                                   && (DAT_GameState::instance.mapAndTime.month
                                       == DAT_GameState::instance.mapAndTime.monthCopy))
                        && (DAT_GameState::instance.mapAndTime.year == DAT_GameState::instance.mapAndTime.yearCopy)) {
                        pcVar9 = "Ap_Milit40.wav";
                        pcVar8 = "good_soldier_taunt.bik";
                        /*
                          added by script: "Sar!  The Stoat is officially out of commission.  Looks   like we’re making
                          progress sar."
                         */
                        pcVar5 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_NEW_TEXT2, 0x14);
                        MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                            DAT_VideoBikQueue::ptr)(pcVar5, pcVar8, pcVar9);
                        DAT_GameState::instance.mapAndTime.field3180_0x27d6
                            = DAT_GameState::instance.mapAndTime.field3180_0x27d6 | 0x10;
                    }
                }
                bVar2 = false;
                if (DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID != 0) {
                    bVar3 = true;
                    bVar2 = bVar3;
                    if ((DAT_GameState::instance.mapAndTime.field3180_0x27d6 & 2U) == 0) {
                        DAT_GameState::instance.mapAndTime.field3180_0x27d6
                            = DAT_GameState::instance.mapAndTime.field3180_0x27d6 | 2;
                        DAT_GameState::instance.mapAndTime.monthCopy
                            = (short)DAT_GameState::instance.mapAndTime.month + 1;
                        DAT_GameState::instance.mapAndTime.yearCopy = (short)DAT_GameState::instance.mapAndTime.year;
                        bVar2 = true;
                        if (0xb < DAT_GameState::instance.mapAndTime.month) {
                            DAT_GameState::instance.mapAndTime.month = DAT_GameState::instance.mapAndTime.month + -0xc;
                            DAT_GameState::instance.mapAndTime.year = DAT_GameState::instance.mapAndTime.year + 1;
                            bVar2 = bVar3;
                        }
                    } else if ((((DAT_GameState::instance.mapAndTime.field3180_0x27d6 & 0x20U) == 0)
                                   && (DAT_GameState::instance.mapAndTime.month
                                       == DAT_GameState::instance.mapAndTime.monthCopy))
                        && (DAT_GameState::instance.mapAndTime.year == DAT_GameState::instance.mapAndTime.yearCopy)) {
                        if (DAT_GameState::instance.playerDataArray[4].lordKilledByPlayerID == 0) {
                            pcVar9 = "Ap_Milit41.wav";
                            pcVar8 = "good_soldier_taunt.bik";
                            /*
                              added by script: "Another bites the dust sar!  Only one rodent left and we   can get
                              started on the Wolf."
                             */
                            pcVar5 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_NEW_TEXT2, 0x15);
                            MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                                DAT_VideoBikQueue::ptr)(pcVar5, pcVar8, pcVar9);
                        }
                        DAT_GameState::instance.mapAndTime.field3180_0x27d6
                            = DAT_GameState::instance.mapAndTime.field3180_0x27d6 | 0x20;
                    }
                }
                if (DAT_GameState::instance.playerDataArray[4].lordKilledByPlayerID != 0) {
                    bVar4 = true;
                    if ((DAT_GameState::instance.mapAndTime.field3180_0x27d6 & 4U) == 0) {
                        DAT_GameState::instance.mapAndTime.field3180_0x27d6
                            = DAT_GameState::instance.mapAndTime.field3180_0x27d6 | 4;
                        DAT_GameState::instance.mapAndTime.monthCopy
                            = (short)DAT_GameState::instance.mapAndTime.month + 1;
                        DAT_GameState::instance.mapAndTime.yearCopy = (short)DAT_GameState::instance.mapAndTime.year;
                        if (0xb < DAT_GameState::instance.mapAndTime.month) {
                            DAT_GameState::instance.mapAndTime.month = DAT_GameState::instance.mapAndTime.month + -0xc;
                            DAT_GameState::instance.mapAndTime.year = DAT_GameState::instance.mapAndTime.year + 1;
                        }
                    } else if ((((DAT_GameState::instance.mapAndTime.field3180_0x27d6 & 0x40U) == 0)
                                   && (DAT_GameState::instance.mapAndTime.month
                                       == DAT_GameState::instance.mapAndTime.monthCopy))
                        && (DAT_GameState::instance.mapAndTime.year == DAT_GameState::instance.mapAndTime.yearCopy)) {
                        if (DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID == 0) {
                            pcVar9 = "Ap_Milit41.wav";
                            pcVar8 = "good_soldier_taunt.bik";
                            /*
                              added by script: "Another bites the dust sar!  Only one rodent left and we   can get
                              started on the Wolf."
                             */
                            pcVar5 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_NEW_TEXT2, 0x15);
                            MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                                DAT_VideoBikQueue::ptr)(pcVar5, pcVar8, pcVar9);
                        }
                        DAT_GameState::instance.mapAndTime.field3180_0x27d6
                            = DAT_GameState::instance.mapAndTime.field3180_0x27d6 | 0x40;
                    }
                }
                if ((1 < DAT_GameState::instance.playerDataArray[5].aiPlayerState)
                    && (DAT_GameState::instance.mapAndTime.field3183_0x27dc == 0)) {
                    pcVar9 = "Ap_Milit42.wav";
                    pcVar8 = "good_soldier_taunt.bik";
                    DAT_GameState::instance.mapAndTime.field3183_0x27dc = 1;
                    /*
                      added by script: "Sar!  The Wolf is launching a charge.  What are your   orders?"
                     */
                    pcVar5 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_NEW_TEXT2, 0x16);
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                        DAT_VideoBikQueue::ptr)(pcVar5, pcVar8, pcVar9);
                }
                if (!bVar6) {}
                if (!bVar2) {}
                if (!bVar4) {}
                if (DAT_GameState::instance.playerDataArray[5].lordKilledByPlayerID == 0) {}
                DAT_GameState::instance.mapAndTime.field3179_0x27d4
                    = DAT_GameState::instance.mapAndTime.field3179_0x27d4 + 1;
                pcVar9 = "";
                pcVar8 = "";
                /*
                  added by script: "Aftermath."
                 */
                pcVar5 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_NEW_TEXT2, 0x17);
                MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                    DAT_VideoBikQueue::ptr)(pcVar5, pcVar8, pcVar9);
            LAB_004c3082:
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .playerDeathRelated = 1;
                DAT_GameState::instance.mapAndTime.unknownCountdown01 = 0xf0;
                MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                    OpenSHC::UI::Enums::DEID_MISSION_WIN_DEFEAT_BANNER, 1);
                if ((DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                        == OpenSHC::UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM)
                    || (DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                        == OpenSHC::UI::Enums::BASMTT_SIEGETENT_SHIELD)) {
                    DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab
                        = DAT_GameCore::instance.tabTypeSiegeSubset;
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
                }
                DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_NULL;
                if (0 < DAT_UnitsState::instance.totalUnitsInSelection) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::queueEscapeCommand, DAT_UnitsState::ptr)();
                    MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseCursorState, DAT_MouseState::ptr)();
                }
                DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_NULL;
            }
            if (DAT_GameState::instance.mapAndTime.month != DAT_GameState::instance.mapAndTime.monthCopy) {}
            if (DAT_GameState::instance.mapAndTime.year != DAT_GameState::instance.mapAndTime.yearCopy) {}
            pcVar8 = "Ap_Milit39.wav";
            pcVar5 = "good_soldier_nervous.bik";
            DAT_GameState::instance.mapAndTime.field3179_0x27d4 = 1;
            iVar7 = 0x13;
        LAB_004c2dc2:
            /*
              added by script: "Sar!  These odds are impossible.  Four against one, it’s   just not right!"
             */
            pcVar9 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_NEW_TEXT2, iVar7);
            MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                pcVar9, pcVar5, pcVar8);
        }
        if (DAT_GameState::instance.mapAndTime.field3179_0x27d4 == 0) {
            if ((DAT_GameState::instance.mapAndTime.month == DAT_GameState::instance.mapAndTime.monthCopy)
                && (DAT_GameState::instance.mapAndTime.year == DAT_GameState::instance.mapAndTime.yearCopy)) {
                pcVar9 = "Ap_Milit34.wav";
                pcVar8 = "bad_soldier_taunt.bik";
                DAT_GameState::instance.mapAndTime.field3179_0x27d4 = 1;
                /*
                  added by script: "The time for vengeance is upon us.  No surrender!"
                 */
                pcVar5 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_NEW_TEXT2, 0xe);
                MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                    DAT_VideoBikQueue::ptr)(pcVar5, pcVar8, pcVar9);
                MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::spawnAttackWaveForPlayer, this)(
                    2, 0x46, 8, 0x48, 0x16, 2);
                DAT_GameState::instance.playerDataArray[2].currentWaveRandomAttackingStrength = 0;
            }
        } else if (DAT_GameState::instance.mapAndTime.field3179_0x27d4 == 1) {
            if (1 < DAT_GameState::instance.playerDataArray[2].aiPlayerState) {
                pcVar8 = "Ap_Milit35.wav";
                pcVar5 = "good_soldier_nervous.bik";
                DAT_GameState::instance.mapAndTime.field3179_0x27d4 = 2;
                iVar7 = 0xf;
            LAB_004c2c95:
                /*
                  added by script: "Now I’m in charge I can do what I want and take what I   please.  The first thing I
                  want is your corpse on a stick."
                 */
                pcVar9 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_NEW_TEXT2, iVar7);
                MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                    DAT_VideoBikQueue::ptr)(pcVar9, pcVar5, pcVar8);
            }
        } else if (DAT_GameState::instance.mapAndTime.field3179_0x27d4 == 2) {
            if (DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID == 0) {}
            pcVar9 = "Ap_Milit36.wav";
            pcVar8 = "good_soldier_taunt.bik";
            DAT_GameState::instance.mapAndTime.field3179_0x27d4 = 3;
            /*
              added by script: "Sar!  I’m pleased to report that we’ve caught the   slippery eel.  He’s taking the long
              hot walk to our dungeon."
             */
            pcVar5 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_NEW_TEXT2, 0x10);
            MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                pcVar5, pcVar8, pcVar9);
            DAT_GameState::instance.mapAndTime.emenyHitArray[3] = 0;
        } else {
            if (DAT_GameState::instance.mapAndTime.field3179_0x27d4 != 3) {
                if (DAT_GameState::instance.mapAndTime.field3179_0x27d4 != 4) {
                    if (DAT_GameState::instance.mapAndTime.field3179_0x27d4 != 5) {}
                    if (((DAT_GameState::instance.mapAndTime.month != DAT_GameState::instance.mapAndTime.monthCopy)
                            || (DAT_GameState::instance.mapAndTime.year != DAT_GameState::instance.mapAndTime.yearCopy))
                        && (DAT_GameState::instance.mapAndTime.year <= DAT_GameState::instance.mapAndTime.yearCopy)) {}
                    DAT_GameState::instance.mapAndTime.field3179_0x27d4 = 6;
                    goto LAB_004c3082;
                }
                if (DAT_GameState::instance.playerDataArray[3].lordKilledByPlayerID == 0) {}
                DAT_GameState::instance.mapAndTime.field3179_0x27d4 = 5;
                DAT_GameState::instance.mapAndTime.yearCopy = (short)DAT_GameState::instance.mapAndTime.year;
                goto LAB_004c2cfc;
            }
            if (0xe < DAT_GameState::instance.mapAndTime.emenyHitArray[3]) {
                pcVar9 = "Ap_Milit37.wav";
                pcVar8 = "good_soldier_taunt.bik";
                DAT_GameState::instance.mapAndTime.field3179_0x27d4 = 4;
                /*
                  added by script: "Sar!  The Wolf’s retreated into the Kingdom of Jerusalem.   Well have to track him
                  down later sar."
                 */
                pcVar5 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_NEW_TEXT2, 0x11);
                MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                    DAT_VideoBikQueue::ptr)(pcVar5, pcVar8, pcVar9);
                pcVar8 = "Ap_Milit38.wav";
                pcVar5 = "bad_soldier_taunt.bik";
                iVar7 = 0x12;
                goto LAB_004c2c95;
            }
        }
        if (DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID == 0) {}
        bVar6 = DAT_GameState::instance.playerDataArray[3].lordKilledByPlayerID == 0;
    LAB_004c2cc1:
        if (bVar6) {}
        DAT_GameState::instance.mapAndTime.field3179_0x27d4 = 5;
    }

}
}
