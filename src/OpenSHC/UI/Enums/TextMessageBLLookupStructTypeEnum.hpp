/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Enums/TextMessageBLLookupStructTypeEnum.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace Enums {
        typedef enum TextMessageBLLookupStructTypeEnum {

            TMBLLSTE_END_OF_TABLE = -1, // 0xFFFFFFFF
            TMBLLSTE_NONE = 0, // 0x00000000
            TMBLLSTE_MENU_BUTTON_TEXT = 1, // 0x00000001
            TMBLLSTE_BUTTON_TEXT = 2, // 0x00000002
            TMBLLSTE_BUILDING_TEXT = 3, // 0x00000003
            TMBLLSTE_POPULARITY_HELP_TEXT = 4, // 0x00000004
            TMBLLSTE_WALL_TEXT = 5, // 0x00000005
            TMBLLSTE_UNITS_AND_WEAPONS_TEXT = 6, // 0x00000006
            TMBLLSTE_MENU_DESCRIPTION_TEXT = 7, // 0x00000007
            TMBLLSTE_REPAIR_BUTTON_TEXT = 8, // 0x00000008
            TMBLLSTE_UNIT_GROUP_SELECT_TEXT = 10, // 0x0000000A
            TMBLLSTE_GUILD_UNIT_TEXT = 11, // 0x0000000B
            TMBLLSTE_MERCENARY_UNIT_TEXT = 12, // 0x0000000C
            TMBLLSTE_LOBBY_TEAMS_TEXT = 13 // 0x0000000D

        } TextMessageBLLookupStructTypeEnum;

        static_assert_cpp98_obj(sizeof(TextMessageBLLookupStructTypeEnum) == 4, TextMessageBLLookupStructTypeEnum);
    } // namespace Enums
} // namespace UI
} // namespace OpenSHC
