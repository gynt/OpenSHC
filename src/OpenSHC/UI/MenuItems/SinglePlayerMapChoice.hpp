/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/SinglePlayerMapChoice.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace SinglePlayerMapChoice {

            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            void __cdecl MenuItemRenderFunction_SingleplayerMapChoice_ButtonsAndHands(int param_1, ...);

            void __cdecl MenuItemActionHandler_SingleplayerMapChoice_ButtonsAndHands(int param_1, ...);

            /**
             * Render callback for one row of the single-player map list: draws the cell background (selected row
             * highlighted), for non-build map types a per-map flag icon (from DAT_ArrayOfMapU3EndInt2), the map
             * display name (hardcoded-map aware, wrap width 0xE6 for siege / 0x172 otherwise) and the file
             * modification date decoded from a packed DOS date/time as dd/mm/yy hh:mm. Original-game bug: the date
             * column indexes the map list with DAT_MenuLoadGameRelativeSelectionOffset (load/save list scroll, only
             * written by the SaveLoadMap scrollbar/buttons) instead of DAT_MapSelectionScrollOffset used for the
             * name, so once the map list is scrolled the dates belong to other maps. The description index returned
             * by GetStringBasedOnHardcodedMaps is ignored.
             */
            void __cdecl MenuItemRenderFunction_SingleplayerMapChoice_MapTable(int param_1, ...);

            void __cdecl MenuItemRenderFunction_SingleplayerMapChoice_MapTableHeader(int param_1, ...);

            /**
             * Render callback for the single-player map list scrollbar: draws it at the current button rectangle
             * with the given thumb position/height, drag state and the button background blend. The slider value
             * parameter is unused.
             */
            void __cdecl MenuItemRenderFunction_SingleplayerMapChoice_Scrollbar(
                int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged);

            /**
             * Selects a row of the single-player map list (ignored past the end of the list): stores the relative
             * selection, triggers Start (button 0x41) on a double-click (same absolute entry within 500 ms; the
             * click is recorded only on left-click start), loads the selected '<name>.map' header and measures the
             * description text height (own text or TEXT_MAP_NAMES entry), resetting the description scroll. For
             * siege maps it clears the per-difficulty slot armies and reads the siege-army section 0x423. With
             * mapU4Int1_2 == 0: if the current army already holds units it returns at once; otherwise it sets a
             * default army of 70% of the section's 20 counts (tunnelers from SEC_Section1067), remaining points 0,
             * propagates it to the slots and loads the slot for the current difficulty. With the flag set it forces
             * advanced mode, player slot 2 and difficulty 1 (remaining points 2000 and zeroed army if the army was
             * empty), propagates and loads slot 1.
             */
            void __cdecl MenuItemActionHandler_SingleplayerMapChoice_MapTable(int param_1, ...);

            /**
             * Scrollbar callback of the single-player map list: event 1 init (min 0, max total-13, current = scroll
             * offset); 2/3 drag: if the value changed it re-selects the current row and only then stores the new
             * offset (so the loaded map header corresponds to the previous offset); 4 sync (reselect if changed,
             * return offset and max); 5/6 scroll up/down by one and reselect; 7 returns the page size (12).
             */
            void __cdecl MenuItemActionHandler_SingleplayerMapChoice_Scrollbar(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            void __cdecl MenuItemActionHandler_SingleplayerMapChoice_MapTableHeader(int param_1, ...);

        } // namespace SinglePlayerMapChoice
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
