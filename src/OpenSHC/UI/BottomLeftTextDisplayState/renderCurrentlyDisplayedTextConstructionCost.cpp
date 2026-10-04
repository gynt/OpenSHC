#include "../BottomLeftTextDisplayState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/GameLanguage.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/BuildMenuTabType.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00ee1090.hpp"
#include "OpenSHC/Globals/DAT_00ee1094.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_TroopDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

namespace OpenSHC {
namespace UI {

    using Commands::MappersEnum;
    using DE::SHCDE::eGM;
    using DE::SHCDE::eTextSections;
    using Game::GameMode;
    using Game::GameMode2;
    using IO::Graphics::GmID;
    using Rendering::Enums::RenderTarget;
    using Text::GameLanguage;
    using Text::TextAlignment;
    using UI::Enums::BuildingsAndStatusMenuTabType;
    using UI::Enums::BuildMenuTabType;
    using UI::Enums::MenuModalType;
    using UI::Enums::MenuViewType;
    using WindowsHelper::Enums::BOOLEnum;
    using Map::Buildings::BuildingType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F4F60
    void BottomLeftTextDisplayState::renderCurrentlyDisplayedTextConstructionCost(int param_1)
    {
        BuildingType _buildingType;
        uint uVar1;
        int iVar2;
        int integer;
        int _requiredPitch;
        int _requiredGold;
        int local_4;
        int _requiredIron;
        int _requiredWood;
        _requiredIron = DAT_BuildingsState::instance.INT_SelectedBuildingStoneRepairCost;
        _requiredWood = DAT_BuildingsState::instance.INT_SelectedBuildingStoneWoodCost;
        if ((param_1 == 0)
            && (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU)) {
            if (DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM) {}
            if (DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_MERCENARYPOST) {}
        }
        if (this->currentlyDisplayedTextIsDisplayedUnk == 0) {}
        if ((((this->currentlyDisplayedTextIsDisplayedUnk != 6) && (this->currentlyDisplayedTextIsDisplayedUnk != 0xc))
                && (this->currentlyDisplayedTextIsDisplayedUnk != 7))
            && (this->currentlyDisplayedTextIsDisplayedUnk != 0xd)) {
            DAT_ButtonX::instance
                = DAT_ButtonX::instance + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX;
            DAT_ButtonY::instance
                = DAT_ButtonY::instance + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY;
            DAT_TextManagerObject::instance.textSurfaceTarget = Rendering::Enums::RT_MAP_GAME;
        }
        if ((DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILD_MENU)
            && (DAT_GameCore::instance.activeMenuTab.buildMenuTab == UI::Enums::BMTT_SOLDIERS)) {
            DAT_ButtonX::instance = DAT_ButtonX::instance + 0x82;
            DAT_ButtonY::instance = DAT_ButtonY::instance + -2;
        }
        switch (this->currentlyDisplayedTextIsDisplayedUnk) {
        case 1:
            if (this->currentlyDisplayedUnkTextGroupIndex_0x4 == 8) {
                if (this->currentlyDisplayedUnkTextNumInGroup_0x8 == 0xca) {
                    this->currentlyDisplayedUnkTextNumInGroup_0x8 = DAT_00ee1090::instance;
                }
                if (this->currentlyDisplayedUnkTextNumInGroup_0x8 == 0x123) {
                    this->currentlyDisplayedUnkTextNumInGroup_0x8 = DAT_00ee1094::instance;
                }
            }
            if (this->currentlyDisplayedUnkTextGroupIndex_0x4 != 0x4d) {
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                    this->currentlyDisplayedUnkTextGroupIndex_0x4,
                    (int)((int)(this->currentlyDisplayedUnkTextNumInGroup_0x8)), (int)((int)(DAT_ButtonX::instance)),
                    (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT, 0xb8eefb, 0, 0x12, FALSE);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = Rendering::Enums::RT_MAP_GAME;
                DAT_TextManagerObject::instance.textSurfaceTarget = Rendering::Enums::RT_SCREEN_MENU;
            }
            _requiredIron = MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText2,
                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_PANEL_FEEDBACK,
                (int)((int)(this->currentlyDisplayedUnkTextNumInGroup_0x8)), 0x1e0, 0x12);
            _requiredWood = DAT_ButtonX::instance;
            _requiredIron = (DAT_ButtonY::instance - _requiredIron) + 0x18;
            iVar2 = 0x1e0;
            goto LAB_004f5302;
        case 2:
            _buildingType = MACRO_CALL_MEMBER(
                Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                DAT_BuildingsState::ptr)(this->currentlyDisplayedUnktextExtraObject.buildingType);
            param_1 = DAT_BuildingsState::instance.buildingCosts[_buildingType].requiredStone_0x4;
            _requiredWood = DAT_BuildingsState::instance.buildingCosts[_buildingType].requiredWood;
            _requiredIron = DAT_BuildingsState::instance.buildingCosts[_buildingType].requiredIron_0x8;
            _requiredPitch = DAT_BuildingsState::instance.buildingCosts[_buildingType].requiredPitch_0xc;
            _requiredGold = DAT_BuildingsState::instance.buildingCosts[_buildingType].requiredGold;
            integer = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .currentResources[4];
            local_4 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .currentResources[0xf];
            uVar1 = MACRO_CALL_MEMBER(
                Map::Buildings::BuildingsState_Func::hasLessWoodThanTheCostOfAWoodcuttersHutAndNoWoodcutters,
                DAT_BuildingsState::ptr)(
                DAT_GameSynchronyState::instance.currentPlayerSlotID, (int)((int)(_buildingType)));
            if (uVar1 != 0) {
                _requiredWood = 0;
            }
            if (DAT_GameCore::instance.gameMode_2 == Game::GM_EDITOR) {
                _requiredIron = 0;
                _requiredGold = 0;
                _requiredPitch = 0;
                param_1 = 0;
                _requiredWood = 0;
            } else if (DAT_GameCore::instance.gameMode_2 == Game::GM_SIEGE_THAT) {
                local_4 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .startResources[0xf];
                integer = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .startResources[4];
                _requiredWood = 0;
                _requiredPitch = 0;
                _requiredIron = 0;
                MACRO_CALL_MEMBER(
                    Map::Buildings::BuildingsState_Func::getBuildingCost, DAT_BuildingsState::ptr)(
                    this->currentlyDisplayedUnktextExtraObject.buildingType, &param_1, &_requiredGold);
            }
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                this->currentlyDisplayedUnkTextGroupIndex_0x4,
                (int)((int)(this->currentlyDisplayedUnkTextNumInGroup_0x8)), (int)((int)(DAT_ButtonX::instance)),
                (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT, 0xb8eefb, 0, 0x12, FALSE);
            iVar2 = 0x1e;
            if (_requiredWood != 0) {
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    _requiredWood, (int)((int)(DAT_ButtonX::instance + 0x1e)), (int)((int)(DAT_ButtonY::instance)),
                    Text::TTA_LEFT, 0xb8eefb, 0, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(DE::SHCDE::GM_INTERFACE_ICONS2, 0x7e,
                    (int)((int)(DAT_TextManagerObject::instance.currentXOffset_0x0 + 0x20 + DAT_ButtonX::instance)),
                    (int)((int)(DAT_ButtonY::instance + -6)));
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow,
                    DAT_TextManagerObject::ptr)("(", (int)((int)(DAT_ButtonX::instance + 0x40)),
                    (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT, 0xb8eefb, 0, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[2],
                    (int)((int)(DAT_ButtonX::instance + 0x40)), (int)((int)(DAT_ButtonY::instance)),
                    Text::TTA_LEFT, 0xb8eefb, 0, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow,
                    DAT_TextManagerObject::ptr)(")", (int)((int)(DAT_ButtonX::instance + 0x40)),
                    (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT, 0xb8eefb, 0, 0x12, TRUE, 0);
                iVar2 = 0x5e;
            }
            if (param_1 != 0) {
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(param_1,
                    DAT_ButtonX::instance + iVar2, (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT,
                    0xb8eefb, 0, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(DE::SHCDE::GM_INTERFACE_ICONS2, 0x7b,
                    DAT_TextManagerObject::instance.currentXOffset_0x0 + DAT_ButtonX::instance + iVar2 + 2,
                    (int)((int)(DAT_ButtonY::instance + -4)));
                _requiredWood = iVar2 + 0x22;
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow,
                    DAT_TextManagerObject::ptr)("(", DAT_ButtonX::instance + _requiredWood,
                    (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT, 0xb8eefb, 0, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(integer,
                    DAT_ButtonX::instance + _requiredWood, (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT,
                    0xb8eefb, 0, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow,
                    DAT_TextManagerObject::ptr)(")", DAT_ButtonX::instance + _requiredWood,
                    (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT, 0xb8eefb, 0, 0x12, TRUE, 0);
                iVar2 = iVar2 + 0x40;
            }
            if (_requiredIron != 0) {
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    _requiredIron, DAT_ButtonX::instance + iVar2, (int)((int)(DAT_ButtonY::instance)),
                    Text::TTA_LEFT, 0xb8eefb, 0, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(DE::SHCDE::GM_INTERFACE_ICONS2, 0x7d,
                    DAT_TextManagerObject::instance.currentXOffset_0x0 + DAT_ButtonX::instance + iVar2 + 2,
                    (int)((int)(DAT_ButtonY::instance + -4)));
                _requiredWood = iVar2 + 0x22;
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow,
                    DAT_TextManagerObject::ptr)("(", DAT_ButtonX::instance + _requiredWood,
                    (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT, 0xb8eefb, 0, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[6],
                    DAT_ButtonX::instance + _requiredWood, (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT,
                    0xb8eefb, 0, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow,
                    DAT_TextManagerObject::ptr)(")", DAT_ButtonX::instance + _requiredWood,
                    (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT, 0xb8eefb, 0, 0x12, TRUE, 0);
                iVar2 = iVar2 + 0x40;
            }
            if (_requiredPitch != 0) {
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    _requiredPitch, DAT_ButtonX::instance + iVar2, (int)((int)(DAT_ButtonY::instance)),
                    Text::TTA_LEFT, 0xb8eefb, 0, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(DE::SHCDE::GM_INTERFACE_ICONS2, 0x9b,
                    DAT_TextManagerObject::instance.currentXOffset_0x0 + DAT_ButtonX::instance + iVar2 + 2,
                    (int)((int)(DAT_ButtonY::instance + -10)));
                _requiredWood = iVar2 + 0x1c;
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow,
                    DAT_TextManagerObject::ptr)("(", DAT_ButtonX::instance + _requiredWood,
                    (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT, 0xb8eefb, 0, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[7],
                    DAT_ButtonX::instance + _requiredWood, (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT,
                    0xb8eefb, 0, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow,
                    DAT_TextManagerObject::ptr)(")", DAT_ButtonX::instance + _requiredWood,
                    (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT, 0xb8eefb, 0, 0x12, TRUE, 0);
                iVar2 = iVar2 + 0x26;
            }
            if (_requiredGold == 0) {
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = Rendering::Enums::RT_MAP_GAME;
                DAT_TextManagerObject::instance.textSurfaceTarget = Rendering::Enums::RT_SCREEN_MENU;
            }
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(_requiredGold,
                DAT_ButtonX::instance + iVar2, (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT, 0xb8eefb,
                0, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(DE::SHCDE::GM_INTERFACE_ICONS2, 0x7c,
                DAT_TextManagerObject::instance.currentXOffset_0x0 + DAT_ButtonX::instance + iVar2 + 2,
                (int)((int)(DAT_ButtonY::instance + 6)));
            iVar2 = iVar2 + 0x22;
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                "(", DAT_ButtonX::instance + iVar2, (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT,
                0xb8eefb, 0, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(local_4,
                DAT_ButtonX::instance + iVar2, (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT, 0xb8eefb,
                0, 0x12, TRUE, 0);
            iVar2 = DAT_ButtonX::instance + iVar2;
            goto LAB_004f6193;
        case 3:
            _requiredWood = (int)this->countdown / 0xf + DAT_ButtonW::instance;
            if (this->currentlyDisplayedUnkTextNumInGroup_0x8 == 1) {
                MACRO_CALL_MEMBER(Text::TextManager_Func::setTextClipRange, DAT_TextManagerObject::ptr)(
                    DAT_ButtonX::instance + 0x14, (dword)((int)(DAT_ButtonW::instance + DAT_ButtonX::instance)));
                _requiredIron
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .crowding;
                if (_requiredIron < 0x1f) {
                    uVar1 = 2;
                } else {
                    uVar1 = (uint)(_requiredIron < 0x47);
                }
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                    this->currentlyDisplayedUnkTextGroupIndex_0x4,
                    (int)((int)(this->currentlyDisplayedUnkTextNumInGroup_0x8 + uVar1)),
                    DAT_ButtonX::instance + _requiredWood, (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT,
                    0xb8eefb, 0, 0x12, FALSE);
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentPopulation
                    == 0) {
                    _requiredIron = 0;
                } else {
                    _requiredIron
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .crowding;
                    if (_requiredIron < 0x65) {
                        _requiredIron = 0;
                    } else if (_requiredIron < 0x79) {
                        _requiredIron = -0x32;
                    } else if (_requiredIron < 0x8d) {
                        _requiredIron = -100;
                    } else if (_requiredIron < 0xa1) {
                        _requiredIron = -0x96;
                    } else {
                        _requiredIron = ((0xb4 < _requiredIron) - 1 & 0x32) - 0xfa;
                    }
                }
                iVar2
                    = DAT_TextManagerObject::instance.currentXOffset_0x0 + DAT_ButtonX::instance + 0x1c + _requiredWood;
                if ((DAT_TextManagerObject::instance.textClipMin < iVar2 + 0x14)
                    && (iVar2 < DAT_TextManagerObject::instance.textClipMax)) {
                    MACRO_CALL(UI::Rendering_Func::TransformAndRenderPercentage)(
                        iVar2, (int)((int)(DAT_ButtonY::instance)), _requiredIron, FALSE);
                }
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(IO::Graphics::GID_INTERFACE_ICONS_2, 0xce, 0x7c, 0x242,
                    IO::Graphics::GID_INTERFACE_ICONS_2, 0xd0, 0);
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(IO::Graphics::GID_INTERFACE_ICONS_2, 0xcf, 0x20a, 0x242,
                    IO::Graphics::GID_INTERFACE_ICONS_2, 0xd1, 0);
                if (_requiredWood < -300) {
                    this->countdown = 0;
                }
                MACRO_CALL_MEMBER(Text::TextManager_Func::resetTextClipRange, DAT_TextManagerObject::ptr)();
            } else if (this->currentlyDisplayedUnkTextNumInGroup_0x8 == 4) {
                _requiredWood
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .storedPopularityPercent;
                _requiredIron
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .popularity;
                iVar2 = 0;
                if (_requiredWood <= _requiredIron) {
                    iVar2 = (_requiredWood < _requiredIron) + 1;
                }
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                    this->currentlyDisplayedUnkTextGroupIndex_0x4, iVar2 + 4, (int)((int)(DAT_ButtonX::instance)),
                    (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT, 0xb8eefb, 0, 0x12, FALSE);
            }
            break;
        case 4:
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                this->currentlyDisplayedUnkTextGroupIndex_0x4,
                (int)((int)(this->currentlyDisplayedUnkTextNumInGroup_0x8)), (int)((int)(DAT_ButtonX::instance)),
                (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT, 0xb8eefb, 0, 0x12, FALSE);
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(DE::SHCDE::GM_INTERFACE_ICONS2, 0x7b,
                (int)((int)(DAT_TextManagerObject::instance.currentXOffset_0x0 + 0x1e + DAT_ButtonX::instance)),
                (int)((int)(DAT_ButtonY::instance + -4)));
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                "(", (int)((int)(DAT_ButtonX::instance + 0x3e)), (int)((int)(DAT_ButtonY::instance)),
                Text::TTA_LEFT, 0xb8eefb, 0, 0x12, TRUE, 0);
            if (DAT_GameCore::instance.gameMode_2 == Game::GM_SIEGE_THAT) {
                _requiredWood
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .startResources[4];
            } else {
                _requiredWood
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .currentResources[4];
            }
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(_requiredWood,
                (int)((int)(DAT_ButtonX::instance + 0x3e)), (int)((int)(DAT_ButtonY::instance)),
                Text::TTA_LEFT, 0xb8eefb, 0, 0x12, TRUE, 0);
            iVar2 = DAT_ButtonX::instance + 0x3e;
            goto LAB_004f6193;
        case 5:
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                this->currentlyDisplayedUnkTextGroupIndex_0x4,
                (int)((int)(this->currentlyDisplayedUnkTextNumInGroup_0x8)), (int)((int)(DAT_ButtonX::instance)),
                (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT, 0xb8eefb, 0, 0x12, FALSE);
            break;
        case 6:
            if ((int)this->currentlyDisplayedUnktextExtraObject < 10) {
                if ((DAT_GameState::instance.mapAndTime
                            .euroRecruitable[this->currentlyDisplayedUnktextExtraObject.buildingType]
                        != 0)
                    && ((MACRO_CALL_MEMBER(Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                             this->currentlyDisplayedUnkTextGroupIndex_0x4,
                             (int)((int)(this->currentlyDisplayedUnkTextNumInGroup_0x8)),
                             (int)((int)(DAT_ButtonX::instance + 0x104)), (int)((int)(DAT_ButtonY::instance)),
                             Text::TTA_CENTER, 0xb8eefb, 0, 0x12, FALSE),
                        DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY
                            || (DAT_GameSynchronyState::instance.skirmishTroopsCostGold != 0)))) {
                    /*
                      added by script: "Cost"
                     */
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                        DE::SHCDE::TEXT_IN_BARRACKS, 2, (int)((int)(DAT_ButtonX::instance)),
                        (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT, 0xb8eefb, 0, 0x12, FALSE);
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumber, DAT_TextManagerObject::ptr)(
                        DAT_TroopDefinedData::instance
                            .BarracksUnitCost[this->currentlyDisplayedUnktextExtraObject.buildingType],
                        (int)((int)(DAT_ButtonX::instance + 6)), (int)((int)(DAT_ButtonY::instance)), 0xb8eefb, 0, 0x12,
                        TRUE);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(DE::SHCDE::GM_INTERFACE_ICONS2, 0x7c,
                        (int)((int)(DAT_TextManagerObject::instance.currentXOffset_0x0 + 10 + DAT_ButtonX::instance)),
                        (int)((int)(DAT_ButtonY::instance)));
                }
            } else if (DAT_GameState::instance.mapAndTime
                           .euroRecruitable[this->currentlyDisplayedUnktextExtraObject.buildingType
                               - Commands::M_MAPPER_ROCKY]
                != 0) {
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                    this->currentlyDisplayedUnkTextGroupIndex_0x4,
                    (int)((int)(this->currentlyDisplayedUnkTextNumInGroup_0x8)), (int)((int)(DAT_ButtonX::instance)),
                    (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT, 0xb8eefb, 0, 0x12, FALSE);
            }
            break;
        case 7:
            if (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_NONE) {
                if ((this->currentlyDisplayedUnkTextNumInGroup_0x8 < 0x136)
                    || (0x139 < this->currentlyDisplayedUnkTextNumInGroup_0x8)) {
                    DAT_TextManagerObject::instance.field9_0x24 = 1;
                    if ((this->currentlyDisplayedUnkTextGroupIndex_0x4 == 8)
                        && ((this->currentlyDisplayedUnkTextNumInGroup_0x8 == 0xe5
                            && ((int)DAT_GameCore::instance.directDrawStatus < 0x700)))) {
                        MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText3Unk,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_BUBBLE_HELP_TEXT, 0x158,
                            (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance)),
                            (int)((int)(DAT_ButtonW::instance)), 0xccfaff, 0, 0x12, 0);
                    } else {
                        MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText3Unk,
                            DAT_TextManagerObject::ptr)(this->currentlyDisplayedUnkTextGroupIndex_0x4,
                            (int)((int)((DE::SHCDE::eTextSections)(this->currentlyDisplayedUnkTextNumInGroup_0x8))),
                            (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance)),
                            (int)((int)((DE::SHCDE::eTextSections)DAT_ButtonW::instance)), 0xccfaff, 0, 0x11, 0);
                    }
                } else {
                    _requiredWood = MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText2,
                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_BUBBLE_HELP_SUBTEXT,
                        (int)((int)(this->currentlyDisplayedUnkTextNumInGroup_0x8 - 0x135)),
                        (int)((int)(DAT_ButtonW::instance)), 0x12);
                    DAT_TextManagerObject::instance.field9_0x24 = 1;
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText3Unk,
                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_BUBBLE_HELP_SUBTEXT,
                        (int)((int)(this->currentlyDisplayedUnkTextNumInGroup_0x8 - 0x135)),
                        (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance)),
                        (int)((int)(DAT_ButtonW::instance)), 0xccfaff, 0, 0x12, 0);
                    DAT_TextManagerObject::instance.field9_0x24 = 1;
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText3Unk,
                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_SKIRMISH_CHOOSE2,
                        (int)((int)(this->currentlyDisplayedUnkTextNumInGroup_0x8 - 0x12d)),
                        (int)((int)(DAT_ButtonX::instance)), DAT_ButtonY::instance + _requiredWood,
                        (int)((int)(DAT_ButtonW::instance)), 0xccfaff, 0, 0x12, 0);
                }
            } else {
                this->currentlyDisplayedTextIsDisplayedUnk = 0;
            }
            break;
        case 8:
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                this->currentlyDisplayedUnkTextGroupIndex_0x4,
                (int)((int)(this->currentlyDisplayedUnkTextNumInGroup_0x8)), (int)((int)(DAT_ButtonX::instance)),
                (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT, 0xb8eefb, 0, 0x12, FALSE);
            iVar2 = 0x1e;
            if (_requiredWood != 0) {
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    _requiredWood, (int)((int)(DAT_ButtonX::instance + 0x1e)), (int)((int)(DAT_ButtonY::instance)),
                    Text::TTA_LEFT, 0xb8eefb, 0, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(DE::SHCDE::GM_INTERFACE_ICONS2, 0x7e,
                    (int)((int)(DAT_TextManagerObject::instance.currentXOffset_0x0 + 0x20 + DAT_ButtonX::instance)),
                    (int)((int)(DAT_ButtonY::instance + -6)));
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow,
                    DAT_TextManagerObject::ptr)("(", (int)((int)(DAT_ButtonX::instance + 0x40)),
                    (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT, 0xb8eefb, 0, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[2],
                    (int)((int)(DAT_ButtonX::instance + 0x40)), (int)((int)(DAT_ButtonY::instance)),
                    Text::TTA_LEFT, 0xb8eefb, 0, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow,
                    DAT_TextManagerObject::ptr)(")", (int)((int)(DAT_ButtonX::instance + 0x40)),
                    (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT, 0xb8eefb, 0, 0x12, TRUE, 0);
                iVar2 = 0x5e;
            }
            if (_requiredIron == 0) {
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = Rendering::Enums::RT_MAP_GAME;
                DAT_TextManagerObject::instance.textSurfaceTarget = Rendering::Enums::RT_SCREEN_MENU;
            }
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(_requiredIron,
                DAT_ButtonX::instance + iVar2, (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT, 0xb8eefb,
                0, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(DE::SHCDE::GM_INTERFACE_ICONS2, 0x7b,
                DAT_TextManagerObject::instance.currentXOffset_0x0 + DAT_ButtonX::instance + iVar2 + 2,
                (int)((int)(DAT_ButtonY::instance + -4)));
            iVar2 = iVar2 + 0x22;
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                "(", DAT_ButtonX::instance + iVar2, (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT,
                0xb8eefb, 0, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .currentResources[4],
                DAT_ButtonX::instance + iVar2, (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT, 0xb8eefb,
                0, 0x12, TRUE, 0);
            iVar2 = DAT_ButtonX::instance + iVar2;
            goto LAB_004f6193;
        case 9:
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                this->currentlyDisplayedUnkTextGroupIndex_0x4,
                (int)((int)(this->currentlyDisplayedUnkTextNumInGroup_0x8)), (int)((int)(DAT_ButtonX::instance)),
                (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT, 0xb8eefb, 0, 0x12, FALSE);
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(DE::SHCDE::GM_INTERFACE_ICONS2, 0x7e,
                (int)((int)(DAT_TextManagerObject::instance.currentXOffset_0x0 + 0x1e + DAT_ButtonX::instance)),
                (int)((int)(DAT_ButtonY::instance + -4)));
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                "(", (int)((int)(DAT_ButtonX::instance + 0x3e)), (int)((int)(DAT_ButtonY::instance)),
                Text::TTA_LEFT, 0xb8eefb, 0, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .currentResources[2],
                (int)((int)(DAT_ButtonX::instance + 0x3e)), (int)((int)(DAT_ButtonY::instance)),
                Text::TTA_LEFT, 0xb8eefb, 0, 0x12, TRUE, 0);
            iVar2 = DAT_ButtonX::instance + 0x3e;
            goto LAB_004f6193;
        case 10:
            this->currentlyDisplayedUnkTextNumInGroup_0x8
                = DAT_RenderingDefinedData::instance.field114_0x525a4[DAT_UnitsState::instance
                        .selectionSlots[this->currentlyDisplayedUnktextExtraObject.buildingType]];
            if (this->currentlyDisplayedUnkTextNumInGroup_0x8 != 0) {
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                    this->currentlyDisplayedUnkTextGroupIndex_0x4,
                    (int)((int)(this->currentlyDisplayedUnkTextNumInGroup_0x8)), (int)((int)(DAT_ButtonX::instance)),
                    (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT, 0xb8eefb, 0, 0x12, FALSE);
            }
            break;
        case 0xb:
            _requiredWood = 0;
            switch (this->currentlyDisplayedUnktextExtraObject.buildingType) {
            case Commands::M_MAPPER_NULL:
            case Commands::M_MAPPER_RAISE:
                _requiredWood = 0x1e;
                break;
            case Commands::M_MAPPER_AREA:
                _requiredWood = 4;
                break;
            case Commands::M_MAPPER_LOWER:
                _requiredWood = 10;
            }
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                this->currentlyDisplayedUnkTextGroupIndex_0x4,
                (int)((int)(this->currentlyDisplayedUnkTextNumInGroup_0x8)), (int)((int)(DAT_ButtonX::instance)),
                (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT, 0xb8eefb, 0, 0x12, FALSE);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(_requiredWood,
                (int)((int)(DAT_ButtonX::instance + 0x1e)), (int)((int)(DAT_ButtonY::instance)),
                Text::TTA_LEFT, 0xb8eefb, 0, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(DE::SHCDE::GM_INTERFACE_ICONS2, 0x7c,
                (int)((int)(DAT_TextManagerObject::instance.currentXOffset_0x0 + 0x20 + DAT_ButtonX::instance)),
                (int)((int)(DAT_ButtonY::instance + -4)));
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                "(", (int)((int)(DAT_ButtonX::instance + 0x40)), (int)((int)(DAT_ButtonY::instance)),
                Text::TTA_LEFT, 0xb8eefb, 0, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .currentResources[0xf],
                (int)((int)(DAT_ButtonX::instance + 0x40)), (int)((int)(DAT_ButtonY::instance)),
                Text::TTA_LEFT, 0xb8eefb, 0, 0x12, TRUE, 0);
            iVar2 = DAT_ButtonX::instance + 0x40;
        LAB_004f6193:
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                ")", iVar2, (int)((int)(DAT_ButtonY::instance)), Text::TTA_LEFT, 0xb8eefb, 0, 0x12, TRUE, 0);
            break;
        case 0xc:
            if (((int)this->currentlyDisplayedUnktextExtraObject.buildingType < 10)
                && ((MACRO_CALL_MEMBER(Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                         this->currentlyDisplayedUnkTextGroupIndex_0x4,
                         (int)((int)(this->currentlyDisplayedUnkTextNumInGroup_0x8)),
                         (int)((int)(DAT_ButtonX::instance + 0x104)), (int)((int)(DAT_ButtonY::instance + 0x98)),
                         Text::TTA_CENTER, 0xb8eefb, 0, 0x12, FALSE),
                    DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY
                        || (DAT_GameSynchronyState::instance.skirmishTroopsCostGold != 0)))) {
                /*
                  added by script: "Cost"
                 */
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_IN_BARRACKS, 2, (int)((int)(DAT_ButtonX::instance + 10)),
                    (int)((int)(DAT_ButtonY::instance + 0x98)), Text::TTA_LEFT, 0xb8eefb, 0, 0x12, FALSE);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumber, DAT_TextManagerObject::ptr)(
                    DAT_TroopDefinedData::instance
                        .NonEuroUnitCost[this->currentlyDisplayedUnktextExtraObject.buildingType],
                    (int)((int)(DAT_ButtonX::instance + 0x10)), (int)((int)(DAT_ButtonY::instance + 0x98)), 0xb8eefb, 0,
                    0x12, TRUE);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(DE::SHCDE::GM_INTERFACE_ICONS2, 0x7c,
                    (int)((int)(DAT_TextManagerObject::instance.currentXOffset_0x0 + 0x14 + DAT_ButtonX::instance)),
                    (int)((int)(DAT_ButtonY::instance + 0x98)));
            }
            break;
        case 0xd:
            _requiredWood = DAT_ButtonX::instance;
            _requiredIron = DAT_ButtonY::instance;
            iVar2 = DAT_ButtonW::instance;
            if (((DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_LOBBY_MENU)
                    && (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_NONE))
                && ((DAT_TextManagerObject::instance.gameLanguage != Text::GL_ENGLISH
                    && (DAT_TextManagerObject::instance.gameLanguage != Text::GL_AMERICAN)))) {
                _requiredWood = DAT_ButtonX::instance + -0x32;
                iVar2 = DAT_ButtonW::instance + 100;
            }
        LAB_004f5302:
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText3Unk, DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)(this->currentlyDisplayedUnkTextGroupIndex_0x4),
                (int)((int)(this->currentlyDisplayedUnkTextNumInGroup_0x8)), _requiredWood, _requiredIron, iVar2,
                0xb8eefb, 0, 0x12, 0);
        }
        DAT_TextManagerObject::instance.textSurfaceTarget = Rendering::Enums::RT_SCREEN_MENU;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = Rendering::Enums::RT_MAP_GAME;
    }

}
}
