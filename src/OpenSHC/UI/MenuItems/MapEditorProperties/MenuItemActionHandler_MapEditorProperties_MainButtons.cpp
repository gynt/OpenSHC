#include "../MapEditorProperties.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/IO/FilePackager.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/UI/MenuItems/MapEditorProperties.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/WindowAndDirectDraw.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00b95b74.hpp"
#include "OpenSHC/Globals/DAT_00b960f4.hpp"
#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/FilePackagerObj.hpp"
#include "OpenSHC/Globals/INT_00b95f68.hpp"
#include "OpenSHC/Globals/INT_00b960e4.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Commands::MappersEnum;
        using OpenSHC::Game::GameMode2;
        using OpenSHC::IO::FileResourceType;
        using OpenSHC::Map::MapType2;
        using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::UI::Enums::MenuViewType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00443070
        void MapEditorProperties::MenuItemActionHandler_MapEditorProperties_MainButtons(int param_1, ...)
        {
            byte(*pabVar1)[10];
            byte* pbVar2;
            char cVar3;
            char cVar4;
            char cVar5;
            int iVar6;
            int* piVar7;
            int* piVar8;
            if ((DAT_MenuTextInputState::instance.currentModalDialog == OpenSHC::UI::Enums::MMT_NO_MENU)
                && (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE)) {
                DAT_TileMapState::instance.field105_0x5548ec = 1;
                switch (param_1) {
                case 2:
                    DAT_MenuTextInputState::instance.field42_0x9c = 1;
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::MenuTextInputState_Func::activateLoadOrSaveMapUI, DAT_MenuTextInputState::ptr)(9);
                    return;
                case 3:
                    if ((DAT_GameCore::instance.U2_mapType_singleOrMulti == 0)
                        || (DAT_GameCore::instance.field115_0x1d98 != 0)) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::MapPropertiesState_Func::determineScenarioMissionTypeAndResetEvents,
                            DAT_MapPropertiesState::ptr)();
                        DAT_MenuTextInputState::instance.field42_0x9c = 1;
                        DAT_MenuTextInputState::instance.field44_0xa4 = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateLoadOrSaveMapUI,
                            DAT_MenuTextInputState::ptr)(10);
                        INT_00b960e4::instance = 1;
                        return;
                    }
                    break;
                case 4:
                    INT_00b960e4::instance = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_NEW_MAP_MAPTYPE, 0);
                    return;
                case 5:
                    if (INT_00b95f68::instance != 0) {
                        DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 0x2b;
                        MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                            DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_QUIT_DIALOG);
                        return;
                    }
                    DAT_GameCore::instance.isTimeHalted2 = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_CUSTOM_SCENARIOS, 0);
                    return;
                case 6:
                    if (DAT_GameCore::instance.field115_0x1d98 != 0) {
                        INT_00b95f68::instance = 1;
                        DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_NULL;
                        DAT_GameCore::instance.gameMode_2 = OpenSHC::Game::GM_EDITOR;
                        DAT_GameCore::instance.missionNumber1to20 = 0x1b;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::clearSelectionCountsAndPlayerIDs,
                            DAT_UnitsState::ptr)();
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[0] = -1;
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[2] = -1;
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[3] = -1;
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[4] = -1;
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[5] = -1;
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[6] = -1;
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[7] = -1;
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[8] = -1;
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[1] = 1;
                        DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
                        if (DAT_GameCore::instance.landscapingmenuMenuTabToSwitchTo == 0xed) {
                            if ((int)DAT_GameCore::instance.U2_mapType_singleOrMulti < 1)
                                goto LAB_00443214;
                            DAT_GameCore::instance.landscapingmenuMenuTabToSwitchTo = 0xef;
                        } else if (DAT_GameCore::instance.landscapingmenuMenuTabToSwitchTo != 0xef)
                            goto LAB_00443214;
                        if (DAT_GameCore::instance.U2_mapType_singleOrMulti == 0) {
                            DAT_GameCore::instance.landscapingmenuMenuTabToSwitchTo = 0xed;
                        }
                    LAB_00443214:
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_MAP_EDITOR_LANDSCAPING, 0);
                        return;
                    }
                    break;
                case 9:
                    MACRO_CALL(OpenSHC::UI::MenuItems::MapEditorProperties_Func::
                            MenuItemActionHandler_MapEditorProperties_MapDescriptionBox)();
                    return;
                case 0x19:
                    if ((DAT_GameCore::instance.U2_mapType_singleOrMulti != 1)
                        && (DAT_GameCore::instance.field115_0x1d98 != 0)) {
                        INT_00b95f68::instance = 1;
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_EDIT_SCENARIO, 0);
                        return;
                    }
                    break;
                case 0x1f:
                    if (DAT_GameCore::instance.field115_0x1d98 != 0) {
                        DAT_GameCore::instance.missionNumber1to20 = 27;
                        DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 0x20;
                        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_PROGRESS_BAR_BOX, FALSE);
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::MenuModalComposition_Func::renderMenuModal, DAT_MenuModalComposition1::ptr)();
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::renderBltAndFlip,
                            DAT_WindowAndDirectDraw::ptr)(0);
                        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName,
                            DAT_ResourceManager::ptr)(OpenSHC::IO::FRT_MAPS, "auto_backup_map.map");
                        FilePackagerObj::instance.loadAndSaveBarFunc
                            = MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderLoadAndSaveBar);
                        MACRO_CALL_MEMBER(OpenSHC::IO::FilePackager_Func::writeMapOrSaveFile, FilePackagerObj::ptr)(
                            DAT_MapDefinedData::instance.MapSectionAddressArray);
                        if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE) {
                            DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[1] = 1;
                            DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[2] = 2;
                        }
                        DAT_MenuTextInputState::instance.DAT_SomeTextArrayIndex = 9;
                        MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs,
                            DAT_MenuTextInputState::ptr)();
                        DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[1] = 1;
                        DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_NULL;
                        DAT_GameCore::instance.gameMode_2 = OpenSHC::Game::GM_BUILDERUnk;
                        DAT_GameCore::instance.field24_0x6c = 1;
                        DAT_GameState::instance.mapAndTime.difficulty = 1;
                        DAT_GameCore::instance.section1095 = 0;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::TroopValueState_Func::clearAttackInfo, DAT_TroopValueState::ptr)();
                        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::recomputeAIZonerLayer, DAT_AICState::ptr)();
                        DAT_TroopValueState::instance.attackInfo.inv_count
                            = DAT_TroopValueState::instance.attackInfo.inv_count + 1;
                        if (0x31 < DAT_TroopValueState::instance.attackInfo.inv_count) {
                            DAT_TroopValueState::instance.attackInfo.inv_count = 1;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::initializeAttackWaveSlot,
                            DAT_TroopValueState::ptr)(DAT_TroopValueState::instance.attackInfo.inv_count, 1);
                        cVar3 = (char)DAT_MapPropertiesState::instance.SEC_Section1067.field0_0x0;
                        DAT_TroopValueState::instance.attackInfo
                            .attackWavePlayerIDArray[DAT_TroopValueState::instance.attackInfo.inv_count] = 2;
                        cVar4 = (char)DAT_MapPropertiesState::instance.SEC_Section1067.field1_0x4;
                        pabVar1 = DAT_TroopValueState::instance.attackInfo.someSinglePlayerScore
                            + DAT_TroopValueState::instance.attackInfo.inv_count;
                        (*pabVar1)[0] = (*pabVar1)[0] + cVar3;
                        cVar5 = (char)DAT_MapPropertiesState::instance.SEC_Section1067.field3_0xc;
                        pbVar2 = DAT_TroopValueState::instance.attackInfo
                                     .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count]
                            + 1;
                        *pbVar2 = *pbVar2 + cVar4;
                        cVar3 = (char)DAT_MapPropertiesState::instance.SEC_Section1067.field2_0x8;
                        pbVar2 = DAT_TroopValueState::instance.attackInfo
                                     .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count]
                            + 2;
                        *pbVar2 = *pbVar2 + cVar5;
                        cVar4 = (char)DAT_MapPropertiesState::instance.SEC_Section1067.field4_0x10;
                        pbVar2 = DAT_TroopValueState::instance.attackInfo
                                     .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count]
                            + 3;
                        *pbVar2 = *pbVar2 + cVar3;
                        cVar3 = (char)DAT_MapPropertiesState::instance.SEC_Section1067.field5_0x14;
                        pbVar2 = DAT_TroopValueState::instance.attackInfo
                                     .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count]
                            + 4;
                        *pbVar2 = *pbVar2 + cVar4;
                        pbVar2 = DAT_TroopValueState::instance.attackInfo
                                     .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count]
                            + 8;
                        *pbVar2 = *pbVar2 + cVar3;
                        DAT_GameState::instance.mapAndTime.siegeInformation.archers
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation.archers;
                        piVar7 = DAT_MapPropertiesState::instance.SEC_StartingResources;
                        piVar8 = DAT_GameState::instance.mapAndTime.startGoods;
                        for (iVar6 = 0x19; iVar6 != 0; iVar6 = iVar6 + -1) {
                            *piVar8 = *piVar7;
                            piVar7 = piVar7 + 1;
                            piVar8 = piVar8 + 1;
                        }
                        DAT_GameState::instance.mapAndTime.startGoods[7]
                            = DAT_GameState::instance.mapAndTime.startGoods[8];
                        DAT_GameState::instance.mapAndTime.siegeInformation.field3_0xc
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation.field3_0xc;
                        DAT_GameState::instance.mapAndTime.siegeInformation.field2_0x8
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation.field2_0x8;
                        DAT_GameState::instance.mapAndTime.siegeInformation.field1_0x4
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation.field1_0x4;
                        DAT_GameState::instance.mapAndTime.siegeInformation.field6_0x18
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation.field6_0x18;
                        DAT_GameState::instance.mapAndTime.siegeInformation.field5_0x14
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation.field5_0x14;
                        DAT_GameState::instance.mapAndTime.siegeInformation.field4_0x10
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation.field4_0x10;
                        DAT_GameState::instance.mapAndTime.siegeInformation.field9_0x24
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation.field9_0x24;
                        DAT_GameState::instance.mapAndTime.siegeInformation.field8_0x20
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation.field8_0x20;
                        DAT_GameState::instance.mapAndTime.siegeInformation.field7_0x1c
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation.field7_0x1c;
                        DAT_GameState::instance.mapAndTime.siegeInformation.field12_0x30
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation.field12_0x30;
                        DAT_GameState::instance.mapAndTime.siegeInformation.field11_0x2c
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation.field11_0x2c;
                        DAT_GameState::instance.mapAndTime.siegeInformation.field10_0x28
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation.field10_0x28;
                        DAT_GameState::instance.mapAndTime.siegeInformation.field15_0x3c
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation.field15_0x3c;
                        DAT_GameState::instance.mapAndTime.siegeInformation.field14_0x38
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation.field14_0x38;
                        DAT_GameState::instance.mapAndTime.siegeInformation.field13_0x34
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation.field13_0x34;
                        DAT_GameState::instance.mapAndTime.siegeInformation.field18_0x48
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation.field18_0x48;
                        DAT_GameState::instance.mapAndTime.siegeInformation.field17_0x44
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation.field17_0x44;
                        DAT_GameState::instance.mapAndTime.siegeInformation.field16_0x40
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation.field16_0x40;
                        DAT_GameState::instance.mapAndTime.startGoods[8] = 0;
                        DAT_GameState::instance.mapAndTime.siegeInformation.field19_0x4c
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation.field19_0x4c;
                        DAT_GameState::instance.mapAndTime.startingPopularity
                            = DAT_MapPropertiesState::instance.SEC_StartingPopularity * 10;
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::setMonthAndYear, DAT_GameState::ptr)(
                            DAT_MapPropertiesState::instance.SEC_StartingMonth,
                            DAT_MapPropertiesState::instance.SEC_StartingYear);
                        MACRO_CALL_MEMBER(
                            OpenSHC::Game::GameStateStructures_Func::clearEnemyRelatedStructures, DAT_GameState::ptr)();
                        DAT_GameState::instance.mapAndTime.mercRecruitable[3]
                            = (int)DAT_MapPropertiesState::instance.SEC_MercRecruitable[3];
                        DAT_GameCore::instance.xbowProducible_logic
                            = (int)DAT_MapPropertiesState::instance.SEC_XbowProducible_save;
                        DAT_GameCore::instance.bowProducible_logic
                            = (int)DAT_MapPropertiesState::instance.SEC_BowProducible_save;
                        DAT_GameCore::instance.pikeProducible_logic
                            = (int)DAT_MapPropertiesState::instance.SEC_PikeProducible_save;
                        DAT_GameState::instance.mapAndTime.mercRecruitable[2]
                            = (int)DAT_MapPropertiesState::instance.SEC_MercRecruitable[2];
                        DAT_GameState::instance.mapAndTime.euroRecruitable[4]
                            = (int)DAT_MapPropertiesState::instance.barracksRecruitability.recruitability.macemen;
                        DAT_GameState::instance.mapAndTime.mercRecruitable[4]
                            = (int)DAT_MapPropertiesState::instance.SEC_MercRecruitable[4];
                        DAT_GameState::instance.mapAndTime.euroRecruitable[5]
                            = (int)DAT_MapPropertiesState::instance.barracksRecruitability.recruitability.swordsmen;
                        DAT_GameCore::instance.spearProducible_logic
                            = (int)DAT_MapPropertiesState::instance.SEC_SpearProducible_save;
                        DAT_GameState::instance.mapAndTime.mercRecruitable[5]
                            = (int)DAT_MapPropertiesState::instance.SEC_MercRecruitable[5];
                        DAT_GameState::instance.mapAndTime.mercRecruitable[0]
                            = (int)DAT_MapPropertiesState::instance.SEC_MercRecruitable[0];
                        DAT_GameState::instance.mapAndTime.euroRecruitable[6]
                            = (int)DAT_MapPropertiesState::instance.barracksRecruitability.recruitability.knights;
                        DAT_GameCore::instance.swordProducible_logic
                            = (int)DAT_MapPropertiesState::instance.SEC_SwordProducible_save;
                        DAT_GameCore::instance.maceProducible_logic
                            = (int)DAT_MapPropertiesState::instance.SEC_MaceProducible_save;
                        DAT_GameState::instance.mapAndTime.mercRecruitable[1]
                            = (int)DAT_MapPropertiesState::instance.SEC_MercRecruitable[1];
                        DAT_GameState::instance.mapAndTime.mercRecruitable[6]
                            = (int)DAT_MapPropertiesState::instance.SEC_MercRecruitable[6];
                        DAT_GameState::instance.mapAndTime.euroRecruitable[0]
                            = (int)DAT_MapPropertiesState::instance.barracksRecruitability.recruitability.archers;
                        DAT_GameState::instance.mapAndTime.euroRecruitable[1]
                            = (int)DAT_MapPropertiesState::instance.barracksRecruitability.recruitability.crossbowmen;
                        DAT_GameState::instance.mapAndTime.euroRecruitable[2]
                            = (int)DAT_MapPropertiesState::instance.barracksRecruitability.recruitability.spearmen;
                        DAT_GameState::instance.mapAndTime.euroRecruitable[3]
                            = (int)DAT_MapPropertiesState::instance.barracksRecruitability.recruitability.pikemen;
                        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_0
                            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[0] != 0);
                        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_a
                            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[1] != 0);
                        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_b
                            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[1] != 0);
                        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_2
                            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[2] != 0);
                        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_a_and_6_b
                            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[3] != 0);
                        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_b
                            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[3] != 0);
                        if (DAT_GameState::instance.mapAndTime.euroRecruitable[4] != 0) {
                            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_a = 1;
                        }
                        DAT_GameState::instance.mapAndTime.field2257_0xda8
                            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[4] != 0);
                        if (DAT_GameState::instance.mapAndTime.euroRecruitable[5] != 0) {
                            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_a_and_6_b = 1;
                        }
                        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_a
                            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[5] != 0);
                        if (DAT_GameState::instance.mapAndTime.euroRecruitable[6] != 0) {
                            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_a = 1;
                            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_a_and_6_b = 1;
                        }
                        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_c
                            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[6] != 0);
                        DAT_GameState::instance.mapAndTime.countUpTo201 = 0;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::MapPropertiesState_Func::importTradingCosts, DAT_MapPropertiesState::ptr)();
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::clearSelectionCountsAndPlayerIDs,
                            DAT_UnitsState::ptr)();
                        DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                            = OpenSHC::UI::Enums::BASMTT_HUNTERSHUT;
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
                        return;
                    }
                    break;
                case -6:
                    DAT_GameCore::instance.mapU3EndInt = 1;
                    break;
                case -5:
                    DAT_GameCore::instance.mapU3EndInt = 0;
                    return;
                case -4:
                    DAT_GameCore::instance.mapU4Int3_balanced = 1;
                    return;
                case -3:
                    DAT_GameCore::instance.mapU4Int3_balanced = 0;
                    return;
                case -2:
                    iVar6 = DAT_00b95b74::instance + -0xe7;
                    if ((DAT_00b960f4::instance < iVar6)
                        && (DAT_00b960f4::instance = DAT_00b960f4::instance + 0xe, iVar6 < DAT_00b960f4::instance)) {
                        DAT_00b960f4::instance = iVar6;
                        return;
                    }
                    break;
                case -1:
                    DAT_00b960f4::instance = DAT_00b960f4::instance + -0xe;
                    if (DAT_00b960f4::instance < 0) {
                        DAT_00b960f4::instance = 0;
                        return;
                    }
                }
            }
            return;
        }

    }
}
}
