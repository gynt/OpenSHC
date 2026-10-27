#include "../BuildMenu.func.hpp"

#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ActionButtonTooltipOverrideCA.hpp"
#include "OpenSHC/Globals/DAT_ActionButtonTooltipOverride123.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonDisabled.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Game::GameMode;
        using OpenSHC::Game::GameMode2;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::Behavior::UnitStanceEnum;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // Rewritten from the original machine code (regress_fix2): every path leaves with ret / tail jmp. The
        // Ghidra-derived version jumped from the 0xd3..0xd7 / default cases to labels in front of the switch and then
        // re-entered the switch (endless loop, game hang), and never returned after the disabled checks.
        // FUNCTION: STRONGHOLDCRUSADER 0x00438BE0
        void BuildMenu::MenuItemRenderFunction_BuildMenu_UnitActionButtons(int mapperValue, ...)
        {
            BOOLEnum BVar1;
            int iVar2;
            uint uVar3;
            UnitType UVar4;
            BVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::isMapperAvailable,
                DAT_MapPropertiesState::ptr)((OpenSHC::Commands::MappersEnum)mapperValue);
            if (BVar1 == FALSE) {
                DAT_ButtonDisabled::instance = 1;
                return; // 0x438bfd ret
            }
            DAT_ButtonDisabled::instance = 0;
            if (0x22e < (int)DAT_CurrentButtonGmDataIndex::instance) { // 0x438c12 jg: signed
                goto LAB_00439051;
            }
            if (DAT_CurrentButtonGmDataIndex::instance == 0x22e) {
                goto LAB_00439029;
            }
            switch (DAT_CurrentButtonGmDataIndex::instance) {
            case 0xd3:
            case 0xd4:
            case 0xd5:
            case 0xd6:
            case 0xd7:
            LAB_00439029:
                if (DAT_UnitsState::instance.hasEngineerSelected != TRUE) {
                    goto LAB_disabled;
                }
                uVar3 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::returnFirstSelectedEngineer, DAT_UnitsState::ptr)();
                if (uVar3 == 0) {
                    goto LAB_disabled;
                }
                goto LAB_00438ec1;
            case 0xd8:
                // 0x438fee
                if (DAT_UnitsState::instance.hasEngineerSelected != FALSE) {
                    goto LAB_disabled;
                }
                UVar4 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::getUnitTypeOfFirstSelectedUnit, DAT_UnitsState::ptr)();
                if (UVar4 == ((UnitType)0xffffffff)) {
                    goto LAB_disabled;
                }
                if (DAT_TribesState::instance.patrolButtonPressed == FALSE) {
                    goto LAB_00438ec1;
                }
                DAT_ButtonCurrentlyInteracting::instance = TRUE;
                goto LAB_00438ec1;
            case 0xda:
                // 0x438cc1
                if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                    || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)
                    || (DAT_UnitsState::instance.hasEngineerSelected != FALSE)) {
                    goto LAB_disabled;
                }
                uVar3 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::getTunnelerIDOnlyIfFirstSelected, DAT_UnitsState::ptr)();
                if (uVar3 == 0) {
                    goto LAB_disabled;
                }
                goto LAB_00438ec1;
            case 0xdb:
                // 0x438daf
                DAT_ActionButtonTooltipOverrideCA::instance = 0xca;
                if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                    || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)
                    || (DAT_UnitsState::instance.hasEngineerSelected != FALSE)) {
                    goto LAB_disabled;
                }
                BVar1 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::selectionContainsEngineersOnly, DAT_UnitsState::ptr)();
                if (BVar1 != FALSE) {
                    uVar3 = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::UnitsState_Func::getSelectedEngineerCarryingResource, DAT_UnitsState::ptr)();
                    if (uVar3 == 0) {
                        goto LAB_disabled;
                    }
                    DAT_CurrentButtonGmDataIndex::instance = 0xd2;
                    DAT_ActionButtonTooltipOverrideCA::instance = 0xc6;
                    goto LAB_00438ec1;
                }
                iVar2 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::selectionContainsTunnelersOnly, DAT_UnitsState::ptr)();
                if (iVar2 != 0) {
                    DAT_CurrentButtonGmDataIndex::instance = 0xda;
                    DAT_ActionButtonTooltipOverrideCA::instance = 0xc9;
                    goto LAB_00438ec1;
                }
                uVar3 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::getFirstSelectedUnitOfEitherType, DAT_UnitsState::ptr)(
                    0x27, 0x28);
                if (uVar3 != 0) {
                    DAT_CurrentButtonGmDataIndex::instance = 0x177;
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                    iVar2 = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::UnitsState_Func::getMaxStoneAmmoInSelectedSiegeEngines, DAT_UnitsState::ptr)();
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber, DAT_TextManagerObject::ptr)(iVar2,
                        DAT_ButtonX::instance + 2, DAT_ButtonY::instance + 2, 0xffffff, 0, 0x13, FALSE);
                    DAT_ButtonDisabled::instance = 0;
                    return; // 0x438ea8 ret
                }
                BVar1 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::selectionContainsRangedOnlyUnits, DAT_UnitsState::ptr)();
                if (BVar1 != FALSE) {
                    DAT_CurrentButtonGmDataIndex::instance = 0x177;
                    goto LAB_00438ec1;
                }
                iVar2 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::selectionContainsLaddermenOnly, DAT_UnitsState::ptr)();
                if (iVar2 != 0) {
                    goto LAB_disabled;
                }
                iVar2 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::selectionContainsShieldmenOnly, DAT_UnitsState::ptr)();
                if (iVar2 != 0) {
                    goto LAB_disabled;
                }
                goto LAB_00438ec1;
            case 0xdc:
                // 0x438d08
                if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                    || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                    goto LAB_disabled;
                }
                if ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY)
                    && (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)
                    && (DAT_GameState::instance.mapAndTime.skirmishNoCowThrowing != 0)) {
                    goto LAB_disabled;
                }
                if (DAT_UnitsState::instance.hasEngineerSelected != FALSE) {
                    goto LAB_disabled;
                }
                uVar3 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::getFirstSelectedUnitOfEitherType, DAT_UnitsState::ptr)(
                    0x27, 0x28);
                if ((uVar3 == 0)
                    || (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .cowCount
                        < 1)) {
                    goto LAB_disabled;
                }
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .cowCount,
                    DAT_ButtonX::instance + 2, DAT_ButtonY::instance + 2, 0xffffff, 0, 0x13, FALSE);
                DAT_ButtonDisabled::instance = 0;
                return; // 0x438ea8 ret
            case 0x172:
                // 0x438f01: stand ground
                UVar4 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::getUnitTypeOfFirstSelectedUnit, DAT_UnitsState::ptr)();
                if (UVar4 == ((UnitType)0xffffffff)) {
                    goto LAB_disabled;
                }
                if (DAT_TribesState::instance.tribes[DAT_TribesState::instance.DAT_CurrentTribeID].unitStance
                    == OpenSHC::Map::Units::Behavior::USE_STAND_GROUND) {
                    DAT_ButtonY::instance = DAT_ButtonY::instance + -5;
                    DAT_ButtonCurrentlyInteracting::instance = TRUE;
                    goto LAB_00438ec1;
                }
                goto LAB_00438f47;
            case 0x173:
                // 0x438f5b: defensive
                UVar4 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::getUnitTypeOfFirstSelectedUnit, DAT_UnitsState::ptr)();
                if (UVar4 == ((UnitType)0xffffffff)) {
                    goto LAB_disabled;
                }
                if (DAT_TribesState::instance.tribes[DAT_TribesState::instance.DAT_CurrentTribeID].unitStance
                    == OpenSHC::Map::Units::Behavior::USE_DEFENSIVE) {
                    DAT_ButtonY::instance = DAT_ButtonY::instance + -1;
                    DAT_ButtonCurrentlyInteracting::instance = TRUE;
                    goto LAB_00438ec1;
                }
                goto LAB_00438f47;
            case 0x174:
                // 0x438fa2: aggressive
                UVar4 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::getUnitTypeOfFirstSelectedUnit, DAT_UnitsState::ptr)();
                if (UVar4 == ((UnitType)0xffffffff)) {
                    goto LAB_disabled;
                }
                if (DAT_TribesState::instance.tribes[DAT_TribesState::instance.DAT_CurrentTribeID].unitStance
                    == OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE) {
                    DAT_ButtonY::instance = DAT_ButtonY::instance + -1;
                    DAT_ButtonCurrentlyInteracting::instance = TRUE;
                    goto LAB_00438ec1;
                }
            LAB_00438f47:
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
                goto LAB_00438ec1;
            case 0x176:
                // 0x438c54
                DAT_ActionButtonTooltipOverride123::instance = 0x123;
                if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                    || (DAT_UnitsState::instance.hasEngineerSelected != FALSE)) {
                    goto LAB_disabled;
                }
                uVar3 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::returnFirstSelectedEngineer, DAT_UnitsState::ptr)();
                if (uVar3 != 0) {
                    goto LAB_00438ec1;
                }
                iVar2 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::countSelectedCatapultsAndTrebuchets, DAT_UnitsState::ptr)();
                if (iVar2 == 0) {
                    goto LAB_disabled;
                }
                DAT_ActionButtonTooltipOverride123::instance = 0x134;
                DAT_CurrentButtonGmDataIndex::instance = 0x179;
                goto LAB_00438ec1;
            case 0x178:
                // 0x438c3c: tail jmp to the render function, ButtonDisabled stays 0
                if (DAT_UnitsState::instance.hasEngineerSelected != TRUE) {
                    goto LAB_disabled;
                }
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                return;
            default:
            LAB_00439051:
                if (DAT_UnitsState::instance.hasEngineerSelected != FALSE) {
                    goto LAB_disabled;
                }
                UVar4 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::getUnitTypeOfFirstSelectedUnit, DAT_UnitsState::ptr)();
                if (UVar4 == ((UnitType)0xffffffff)) {
                    goto LAB_disabled;
                }
                goto LAB_00438ec1;
            }
        LAB_00438ec1:
            MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                    MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
            DAT_ButtonDisabled::instance = 0;
            return; // 0x438ece ret
        LAB_disabled:
            DAT_ButtonDisabled::instance = 1; // 0x439048 / 0x43906c
        }

    }
}
}
