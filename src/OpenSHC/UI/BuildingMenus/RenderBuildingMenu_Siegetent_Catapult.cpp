#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    using DE::SHCDE::eTextSections;
    using Rendering::Colors::BGR24;
    using Text::TextAlignment;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0043DE70
    void BuildingMenus::RenderBuildingMenu_Siegetent_Catapult()
    {
        char* pcVar2;
        int iVar3;
        int iVar4;
        TextAlignment TVar5;
        BGR24 BVar6;
        int iVar7;
        BOOLEnum BVar8;
        int blendStrength;
        iVar3 = DAT_BuildingsState::instance.menuSelectedBuildingID;
        blendStrength = 0;
        BVar8 = FALSE;
        iVar7 = 0x11;
        BVar6 = 0;
        TVar5 = Text::TTA_LEFT;
        int iVar1 = DAT_MenuHandlerState::instance.y + 0x1eb;
        iVar4 = DAT_MenuHandlerState::instance.x + 0xb4;
        /*
          added by script: "Catapult"
         */
        pcVar2 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_IN_SIEGE_TENT, 1);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            pcVar2, iVar4, iVar1, TVar5, BVar6, iVar7, BVar8, blendStrength);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            (DAT_BuildingsState::instance.buildings[iVar3].buildingProgress * 100) / 0x140,
            DAT_MenuHandlerState::instance.x + 0xb4, DAT_MenuHandlerState::instance.y + 0x209, Text::TTA_LEFT,
            0, 0x11, FALSE, 0);
        iVar7 = 0;
        BVar8 = TRUE;
        iVar4 = 0x11;
        BVar6 = 0;
        TVar5 = Text::TTA_LEFT;
        iVar3 = DAT_MenuHandlerState::instance.y + 0x209;
        iVar1 = DAT_MenuHandlerState::instance.x + 0xb4;
        /*
          added by script: "% Complete"
         */
        pcVar2 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_IN_SIEGE_TENT, 6);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            pcVar2, iVar1, iVar3, TVar5, BVar6, iVar4, BVar8, iVar7);
    }

}
}
