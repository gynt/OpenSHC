#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    using DE::SHCDE::eTextSections;
    using Rendering::Colors::BGR24;
    using Text::TextAlignment;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0043DC60
    void BuildingMenus::RenderBuildingMenu_Statue()
    {
        char* pcVar3;
        int iVar4;
        TextAlignment TVar5;
        BGR24 BVar6;
        int iVar7;
        BOOLEnum BVar8;
        int iVar9;
        int iVar1 = DAT_BuildingsState::instance.menuSelectedBuildingID;
        iVar9 = 0;
        BVar8 = FALSE;
        iVar7 = 0x11;
        BVar6 = 0;
        TVar5 = Text::TTA_LEFT;
        int iVar2 = DAT_MenuHandlerState::instance.y + 0x1d3;
        iVar4 = DAT_MenuHandlerState::instance.x + 0x19;
        /*
          added by script: "Statue"
         */
        pcVar3 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_IN_STATUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            pcVar3, iVar4, iVar2, TVar5, BVar6, iVar7, BVar8, iVar9);
        if (DAT_BuildingsState::instance.buildings[iVar1].owner == 0) {
            iVar9 = 0;
            BVar8 = FALSE;
            iVar7 = 0x12;
            BVar6 = 0;
            TVar5 = Text::TTA_LEFT;
            iVar2 = DAT_MenuHandlerState::instance.y + 0x1fb;
            iVar4 = DAT_MenuHandlerState::instance.x + 0xaf;
            /*
              added by script: "Here lies the poor bones of"
             */
            pcVar3 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MISC2, 1);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                pcVar3, iVar4, iVar2, TVar5, BVar6, iVar7, BVar8, iVar9);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                DAT_GameSynchronyState::instance.finalResults
                    .names[DAT_BuildingsState::instance.buildings[iVar1].statueCommemoratingPlayerID],
                DAT_MenuHandlerState::instance.x + 0xaf, DAT_MenuHandlerState::instance.y + 0x214,
                Text::TTA_LEFT, 0, 0x12, FALSE, 0);
        }
    }

}
}
