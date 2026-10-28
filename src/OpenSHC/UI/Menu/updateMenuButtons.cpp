#include "OpenSHC/UI/Menu.func.hpp"
#include "OpenSHC/UI/Enums/MenuItemHandleState.hpp"
#include "OpenSHC/UI/MenuItem.hpp"

#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::MenuItem;
    using OpenSHC::UI::Enums::MenuItemHandleState;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F6470
    void Menu::updateMenuButtons()
    {
        if (this->hoveredItem == NULL) {
            this->tooltipItem = NULL;
        }
        this->hoveredItem = NULL;
        this->hoverSoundPlayedThisFrame = 0;
        DAT_MenuHandlerState::instance.mouseOverMenuItem = 0;
        MACRO_CALL_MEMBER(OpenSHC::UI::Menu_Func::handleMenuItems, this)(
            OpenSHC::UI::Enums::MIHS_HANDLE_INPUT_CALLBACKS);
        this->isFirstFrame = 0;
    }

}
}
