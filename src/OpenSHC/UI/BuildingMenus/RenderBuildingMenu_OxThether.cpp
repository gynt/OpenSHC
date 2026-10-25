#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0043BE20
    void BuildingMenus::RenderBuildingMenu_OxThether()
    {
        int iVar3;
        int iVar4;
        int iVar5;
        iVar5 = 0;
        iVar4 = 0x10;
        int iVar1 = DAT_MenuHandlerState::instance.y + 0x1d3;
        iVar3 = DAT_MenuHandlerState::instance.x + 0x19;
        /*
          added by script: "Ox Tether"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_OXEN_BASE, 0),
            iVar3, iVar1, OpenSHC::Text::TTA_LEFT, 0, iVar4, FALSE, iVar5);
        iVar5 = 0x12;
        iVar4 = 0x136;
        iVar1 = DAT_MenuHandlerState::instance.y + 0x1fb;
        iVar3 = DAT_MenuHandlerState::instance.x + 0xaf;
        /*
          added by script: "An Ox will transport stone from here to the stockpile."
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_OXEN_BASE, 3),
            iVar3, iVar1, iVar4, 0, iVar5, 0);
    }

}
}
