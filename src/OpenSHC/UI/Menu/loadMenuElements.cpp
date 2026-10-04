#include "../Menu.func.hpp"

#include "OpenSHC/UI/Enums/MenuItemType.hpp"

#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"

#include "UCPointerStruct.func.hpp"

namespace OpenSHC {
namespace UI {

    using UI::Enums::MenuItemType;

    /*
      called every time a terrain menu is loaded   decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F69D0
    void Menu::loadMenuElements(int ucPositionIndex)
    {
        MenuItem* _menuItemPtr;
        MenuItemTypeInt _menuItemType;
        _menuItemPtr = this->menuItemArray;
        _menuItemType = _menuItemPtr->menuItemType;
        while (_menuItemType != UI::Enums::MIT_LAST_ENTRY) {
            if (-1 < (short)_menuItemPtr->ucID) {
                MACRO_CALL_MEMBER(UCPointerStruct_Func::setUCValues, &DAT_MenuHandlerState::ptr->ucPtrStruct)(
                    (int)(short)_menuItemPtr->ucID, (int*)&_menuItemPtr->position, &(_menuItemPtr->position).position.y,
                    &_menuItemPtr->iconDeactivatedUnk_0x36, ucPositionIndex);
            }
            _menuItemPtr = _menuItemPtr + 1;
            _menuItemType = _menuItemPtr->menuItemType;
        }
        return;
    }

}
}
