/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItem.hpp'
*/

#pragma once

#include "OpenSHC/UI/Callbacks/MenuItemActionHandlerUnion.hpp"
#include "OpenSHC/UI/Callbacks/MenuItemRenderFunctionUnion.hpp"
#include "OpenSHC/UI/Enums/MenuItemRenderFunctionTypeInt.hpp"
#include "OpenSHC/UI/Enums/MenuItemTypeInt.hpp"
#include "OpenSHC/UI/Enums/UserControlIDShort.hpp"
#include "OpenSHC/UI/FwdMenuMenuItem.hpp"
#include "OpenSHC/UI/Menu.hpp"
#include "OpenSHC/UI/MenuItemCallbackParameter.hpp"
#include "OpenSHC/UI/MenuItemFirstItemTypeData.hpp"
#include "OpenSHC/UI/MenuItemPosition.hpp"
#include "OpenSHC/UI/MenuItemSecondItemTypeData.hpp"
#include "OpenSHC/UI/UnknownMenuSubStruct.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Menu;
    using OpenSHC::UI::MenuItemCallbackParameter;
    using OpenSHC::UI::MenuItemFirstItemTypeData;
    using OpenSHC::UI::MenuItemPosition;
    using OpenSHC::UI::MenuItemSecondItemTypeData;
    using OpenSHC::UI::UnknownMenuSubStruct;
    using OpenSHC::UI::Callbacks::MenuItemActionHandlerUnion;
    using OpenSHC::UI::Callbacks::MenuItemRenderFunctionUnion;
    using OpenSHC::UI::Enums::MenuItemRenderFunctionTypeInt;
    using OpenSHC::UI::Enums::MenuItemTypeInt;
    using OpenSHC::UI::Enums::UserControlIDShort;

#pragma pack(push, 1)

    // SIZE: 0x00000050
    class MenuItem {
    public:
        MenuItemTypeInt menuItemType; // 0x00000000 length: 4
        MenuItemPosition position; // 0x00000004 length: 8
        int itemWidth; // 0x0000000C length: 4
        int itemHeight; // 0x00000010 length: 4
        MenuItemActionHandlerUnion menuItemActionHandler; // 0x00000014 length: 4
        MenuItemCallbackParameter callbackParameter; // 0x00000018 length: 4
        MenuItemRenderFunctionUnion menuItemRenderFunction; // 0x0000001C length: 4
        MenuItemFirstItemTypeData firstItemTypeData; // 0x00000020 length: 4
        MenuItemRenderFunctionTypeInt menuItemRenderFunctionType; // 0x00000024 length: 4
        int testNotEqualZero; // 0x00000028 length: 4
        UnknownMenuSubStruct textMessageLookupIndex; // 0x0000002C length: 4
        // ID corresponding to UCArray defining default screen position
        UserControlIDShort ucID; // 0x00000030 length: 2
        short hovering; // 0x00000032 length: 2
        short clicked; // 0x00000034 length: 2
        // [UNK PASS] was iconDeactivatedUnk_0x36
        ushort isDeactivatedInUCLayout; // 0x00000036 length: 2
        // [211 0x004F4290] nonzero disables input handling; written from DAT_ButtonDisabled which render
        // functions set to 1 to hide a button
        // [211 0x004F4290] nonzero disables input handling; written from DAT_ButtonUnknownZero which render
        // functions set to 1 to hide a button
        short isHidden; // 0x00000038 length: 2
        short field16_0x3a; // 0x0000003A length: 2
        MenuItemSecondItemTypeData secondItemTypeData; // 0x0000003C length: 16
        Menu* menuPointer; // 0x0000004C length: 4

    private:
        MenuItem(MenuItem const&);
        void operator=(MenuItem const&);

    public:
        MenuItem() {};
        ~MenuItem() {};

        /**
         * Input handling for one active (not deactivated/hidden) menu item. Type 0 items just call their action
         * handler; type 1 calls it while scrolling. Sliders/scrollbars (skipped on the menu's first frame): clamp
         * value to [min,max], compute thumb size/offset, handle thumb drag, page clicks beside the thumb and wheel
         * events. Other items: mouse hit test (optionally pixel-exact), hover sound, set hovered item, and fire the
         * action handler on left click (right click for MIT_TEXT_OR_STATE_OR_PLAYER_DEPENDENT), drag stop (type
         * 10), wheel on render-type-2 items (handler(2 up / 1 down) x10, x100 with middle button) or auto-repeat
         * while held (type 2, every >39 ms, per UI_DragTicks). Returns DAT_StopHandlingMenuItems after a fired
         * click, else 0.
         */
        int handleMenuElementsCallbacks();

        /**
         * Prepares and renders one non-deactivated menu item: sizes GM-image items from their picture, sets the
         * DAT_Button* globals (position incl. build-menu shift, size, gm index, interacting, hidden flag). During a
         * build-menu transition it skips rendering outside the clip limits or at 46-54 % progress, otherwise sets
         * blend strength (progress-based fade). On the menu's first frame sliders call their handler, reset drag
         * and clamp the value. Calls the render function, stores the GM picture back, resets the tooltip state if
         * the hovered item's interacting state changed, and stores DAT_ButtonDisabled back into the item.
         */
        void prepareAndRenderMenuItems();

        /**
         * Clears a menu item's hover/click flags and button state; for sliders/scrollbars also resets the drag
         * offset to -1000.
         */
        void resetMenuItemState();
    };

    static_assert_cpp98_obj(sizeof(MenuItem) == 80, MenuItem);

#pragma pack(pop)

} // namespace UI
} // namespace OpenSHC
