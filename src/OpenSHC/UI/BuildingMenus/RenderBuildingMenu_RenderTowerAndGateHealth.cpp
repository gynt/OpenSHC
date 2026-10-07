#include "../BuildingMenus.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/COL_LIME.hpp"
#include "OpenSHC/Globals/COL_RED.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
        // FUNCTION: STRONGHOLDCRUSADER 0x0043E350
    void BuildingMenus::RenderBuildingMenu_RenderTowerAndGateHealth()
    {
        int buildingID = DAT_BuildingsState::instance.menuSelectedBuildingID;
        int healthPercent = (int)DAT_BuildingsState::instance.buildings[buildingID].currentHealth;
        short maxHealth = DAT_BuildingsState::instance.buildings[buildingID].maxHealth;
        ColorUnion barColor;
        barColor.shortValue = COL_LIME::instance.shortValue;
        if (healthPercent <= 0 || maxHealth <= 0) {
            healthPercent = 0;
        } else {
            healthPercent = (healthPercent * 100) / (int)maxHealth;
        }
        int left = DAT_MenuHandlerState::instance.x + 0x1d6;
        int top = DAT_MenuHandlerState::instance.y + 0x1d3;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
            left, top, left + 0x33, top + 0xb, (ushort)(COL_BLACK::instance.shortValue));
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
            left + 1, top + 1, left + 0x32, top + 0xa, (ushort)(COL_RED::instance.shortValue));
        if (healthPercent >= 2) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                left + 1, top + 1, (healthPercent >> 1) + left, top + 0xa, barColor.shortValue);
        }
        char healthText[16];
        MACRO_CALL(OpenSHC::OS_Func::_sprintf)(healthText, "%d/%d",
            (int)DAT_BuildingsState::instance.buildings[buildingID].currentHealth,
            (int)DAT_BuildingsState::instance.buildings[buildingID].maxHealth);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(healthText,
            DAT_MenuHandlerState::instance.x + 0x1ef, DAT_MenuHandlerState::instance.y + 0x1e2,
            OpenSHC::Text::TTA_CENTER, 0, 0x12, FALSE, 0);
    }

}
}