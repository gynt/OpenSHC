#include "../Menu.func.hpp"

#include "OpenSHC/UI/MenuItem.func.hpp"
#include "OpenSHC/UI/Enums/MenuItemHandleState.hpp"
#include "OpenSHC/UI/Enums/MenuItemType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Enums::MenuItemHandleState;
    using OpenSHC::UI::Enums::MenuItemType;
    using OpenSHC::UI::Enums::MenuModalType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      funcIndex is 0 for updating, 2 or 3 for rendering   decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F6280
    void Menu::handleMenuItems(MenuItemHandleState funcIndex)
    {
        MenuItem* _nextMenuItem;
        MenuItemTypeInt _someFlagSet;
        int _stopProcessing;
        MenuItem* _menuItemArray;
        MenuItemTypeInt _nextMenuItemType;
        MenuItem* _currentMenuItemPtr;
        MenuItemTypeInt _menuItemType;
        _menuItemArray = this->menuItemArray;
        this->currentBuildMenuButtonShift = 0;
        _menuItemType = _menuItemArray->menuItemType;
        while (_menuItemType != OpenSHC::UI::Enums::MIT_LAST_ENTRY) {
            _currentMenuItemPtr = _menuItemArray;
            if (_menuItemType == OpenSHC::UI::Enums::MIT_TAB_CONSIDER_ITEM_SKIP_BECAUSE_OTHER_MENU_TAB) {
                if (((_menuItemArray->callbackParameter).activeMenuTab.tabType
                        != DAT_GameCore::instance.activeMenuTab.tabType)
                    && (funcIndex != OpenSHC::UI::Enums::MIHS_RESET_MENU_ITEM_STATE)) {
                    _currentMenuItemPtr = _menuItemArray + (_menuItemArray->firstItemTypeData).itemsToSkip;
                }
            } else if (_menuItemType == OpenSHC::UI::Enums::MIT_TAB_CONSIDER_STOP_BECAUSE_IS_CURRENT_MENU_TAB) {
                if (((_menuItemArray->callbackParameter).activeMenuTab.tabType
                        == DAT_GameCore::instance.activeMenuTab.tabType)
                    && (funcIndex != OpenSHC::UI::Enums::MIHS_RESET_MENU_ITEM_STATE)) {
                    return; // 0x4F62E3
                }
            } else {
                if (_menuItemType == OpenSHC::UI::Enums::MIT_STOP_HANDLING) {
                    return; // 0x4F62F1
                }
                if (_menuItemType == OpenSHC::UI::Enums::MIT_ENABLE_OR_WRAP_BUILD_MENU_TRANSITION_OFFSET) {
                    if ((DAT_MenuHandlerState::instance.isBuildMenuTransitioning_0x18 != FALSE)
                        && (funcIndex == OpenSHC::UI::Enums::MIHS_HANDLE_INPUT_CALLBACKS)) {
                        return; // 0x4F6307
                    }
                    this->currentBuildMenuButtonShift = ~-(uint)(this->currentBuildMenuButtonShift != 0)
                        & DAT_MenuHandlerState::instance.buildMenuItemsLeftShift_0x28;
                } else if (_menuItemType == OpenSHC::UI::Enums::MIT_STOP_IF_MODAL_OPEN) {
                    if (DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_NONE) {
                        return; // 0x4F6330
                    }
                } else if (_menuItemType == ((MenuItemType)0x21000000)) {
                    _nextMenuItem = _menuItemArray + (_menuItemArray->firstItemTypeData).itemsToSkip + 1;
                    _nextMenuItemType = _nextMenuItem->menuItemType;
                    for (; (_currentMenuItemPtr = _menuItemArray,
                           _nextMenuItemType == ((MenuItemType)0x11000000)
                                 && (_currentMenuItemPtr = _nextMenuItem,
                                    _nextMenuItem->testNotEqualZero != DAT_GameCore::instance.unknownAlwaysZero01));
                        _nextMenuItem = _nextMenuItem + (_nextMenuItem->firstItemTypeData).itemsToSkip + 1) {
                        _nextMenuItemType
                            = _nextMenuItem[(_nextMenuItem->firstItemTypeData).itemsToSkip + 1].menuItemType;
                    }
                } else if (_menuItemType == ((MenuItemType)0x11000000)) {
                    _currentMenuItemPtr = _menuItemArray + (_menuItemArray->firstItemTypeData).gmDataIndex;
                } else if (_menuItemType == ((MenuItemType)7)) {
                    DAT_GameCore::instance.onViewOrTabSwitchHandler
                        = (MenuItemActionHandler*)(_menuItemArray->menuItemActionHandler).simple;
                } else if ((_menuItemType != OpenSHC::UI::Enums::MIT_SHARED_HANDLER_GROUP_START)
                    && ((_menuItemType & 0x4000000) == ((MenuItemType)0))) {
                    if ((_menuItemType & 0x8000000) != ((MenuItemType)0)) {
                        _menuItemType = _menuItemArray[1].menuItemType;
                        _nextMenuItem = _menuItemArray + 1;
                        while ((_currentMenuItemPtr = _menuItemArray,
                            (_menuItemType & 0x4000000) != ((MenuItemType)0)
                                && (_currentMenuItemPtr = _nextMenuItem,
                                    _nextMenuItem->testNotEqualZero != DAT_GameCore::instance.unknownAlwaysZero01))) {
                            _nextMenuItem = _nextMenuItem + 1;
                            _menuItemType = _nextMenuItem->menuItemType;
                        }
                    }
                    if ((-1 < (int)_currentMenuItemPtr->menuItemType)
                        && (((_someFlagSet = _currentMenuItemPtr->menuItemType & 0x800000,
                                 _someFlagSet != ((MenuItemType)0)
                                     && (funcIndex == OpenSHC::UI::Enums::MIHS_PREPARE_AND_RENDER_FOR_FLAG_0X800000))
                            || ((((_someFlagSet == ((MenuItemType)0)
                                      && (funcIndex == OpenSHC::UI::Enums::MIHS_PREPARE_AND_RENDER))
                                     || ((funcIndex == OpenSHC::UI::Enums::MIHS_HANDLE_INPUT_CALLBACKS
                                         || (funcIndex == OpenSHC::UI::Enums::MIHS_RESET_MENU_ITEM_STATE))))
                                && (funcIndex < ((MenuItemHandleState)4))))))) {
                        /*
                          WARNING: Switch is manually overridden
                         */
                        /*
                          updates and renders menu
                         */
                        switch (funcIndex) {
                        case OpenSHC::UI::Enums::MIHS_HANDLE_INPUT_CALLBACKS:
                            _stopProcessing = MACRO_CALL_MEMBER(
                                OpenSHC::UI::MenuItem_Func::handleMenuElementsCallbacks, _currentMenuItemPtr)();
                            if (_stopProcessing != 0) {
                                return; // 0x4F642D
                            }
                            break;
                        case OpenSHC::UI::Enums::MIHS_PREPARE_AND_RENDER:
                        case OpenSHC::UI::Enums::MIHS_PREPARE_AND_RENDER_FOR_FLAG_0X800000: // jump table 0x4F6458[3]
                            MACRO_CALL_MEMBER(
                                OpenSHC::UI::MenuItem_Func::prepareAndRenderMenuItems, _currentMenuItemPtr)();
                            break;
                        case OpenSHC::UI::Enums::MIHS_RESET_MENU_ITEM_STATE:
                            MACRO_CALL_MEMBER(OpenSHC::UI::MenuItem_Func::resetMenuItemState, _currentMenuItemPtr)();
                        }
                    }
                }
            }
            _menuItemType = _currentMenuItemPtr[1].menuItemType;
            _menuItemArray = _currentMenuItemPtr + 1;
        }
    }

}
}
