/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Enums/MenuItemType.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace Enums {
        typedef enum MenuItemType {

            MIT_NONE = 0, // 0x00000000
            MIT_CALL_WHILE_SCROLLING = 1, // 0x00000001
            MIT_AUTO_REPEAT_BUTTON = 2, // 0x00000002
            MIT_NORMAL_ELEMENT = 3, // 0x00000003
            MIT_RIGHT_CLICK_ELEMENT = 4, // 0x00000004
            MIT_HORIZONTAL_SLIDER = 5, // 0x00000005
            MIT_VERTICAL_SCROLLBAR = 6, // 0x00000006
            MIT_ON_VIEW_OR_TAB_SWITCH_HANDLER = 7, // 0x00000007
            MIT_ENABLE_OR_WRAP_BUILD_MENU_TRANSITION_OFFSET = 8, // 0x00000008
            MIT_STOP_IF_MODAL_OPEN = 9, // 0x00000009
            MIT_PRESS_AND_RELEASE_ELEMENT = 10, // 0x0000000A
            MIT_TAB_CONSIDER_ITEM_SKIP_BECAUSE_OTHER_MENU_TAB = 100, // 0x00000064
            MIT_TAB_CONSIDER_STOP_BECAUSE_IS_CURRENT_MENU_TAB = 101, // 0x00000065
            MIT_LAST_ENTRY = 102, // 0x00000066
            MIT_STOP_HANDLING = 103, // 0x00000067
            MIT_TYPE_ID_MASK = 8388607, // 0x007FFFFF
            MIT_FLAG_RENDER_EVERY_FRAME = 8388608, // 0x00800000
            MIT_SHARED_HANDLER_GROUP_START = 16777216, // 0x01000000
            MIT_SHARED_HANDLER_GROUP_MEMBER = 33554432 // 0x02000000

        } MenuItemType;

        static_assert_cpp98_obj(sizeof(MenuItemType) == 4, MenuItemType);
    } // namespace Enums
} // namespace UI
} // namespace OpenSHC
