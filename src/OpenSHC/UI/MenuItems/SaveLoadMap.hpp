/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/SaveLoadMap.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace SaveLoadMap {

            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            /**
             * Render callback of the load/save dialog buttons (TEXT_GAME_OPTIONS[id]; in multiplayer Load uses text
             * 0x26). Load is greyed when nothing is selected or, in multiplayer, the selected entry's loadable flag
             * is 0; -1/-2 draw the scroll arrows.
             */
            void __cdecl MenuItemRenderFunction_SaveLoadMap_Buttons(int param_1, ...);

            /**
             * Scrollbar callback of the load/save file list: max = fileListTotalCount - fileListVisibleRows,
             * current = scroll offset (DAT_MenuLoadGameRelativeSelectionOffset); 2/3 set it, 4 refreshes, 5/6 step
             * it, 7 returns page step visibleRows-1. The item parameter is unused.
             */
            void __cdecl MenuItemActionHandler_SaveLoadMap_Scrollbar(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            /**
             * Render callback of the load/save list scrollbar: draws the standard scrollbar at the button rect with
             * the given thumb position/size. The item parameter is unused.
             */
            void __cdecl MenuItemRenderFunction_SaveLoadMap_Scrollbar(
                int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged);

            /**
             * Render callback for one row of the load/save file list: draws the cell background (highlighted when
             * selected), the file name and its DOS-packed modification time as 'DD/MM/YY hh:mm' (year = DOS year -
             * 20, i.e. years since 2000); in multiplayer entries whose loadable flag is 0 are greyed.
             */
            void __cdecl MenuItemRenderFunction_SaveLoadMap_TableContent(int param_1, ...);

            /**
             * Sorts the load/save file index list. Column 0 toggles between list order (mode 0) and reversed order
             * (mode 1); column 1 bubble-sorts by mapFileTimes, newest first (mode 2) or oldest first (mode 3),
             * toggling. Negative ids force a mode: -1 -> 0, -2 -> 1, -3 -> 2, -4 -> 3 (used when the dialog is
             * opened). Sets field43_0xa0 to -1 afterwards.
             */
            void __cdecl MenuItemActionHandler_SaveLoadMap_TableHeader(int param_1, ...);

            /**
             * Render callback of the load/save table headers: draws a header cell with TEXT_GAME_OPTIONS
             * 0x1B/0x1C/0x1D for columns 0/1/2.
             */
            void __cdecl MenuItemRenderFunction_SaveLoadMap_TableHeader(int param_1, ...);

            /**
             * Action handler of the load/save dialog buttons. 2 Load: builds the file name of the selected entry
             * (.tmp/.map/.sav/.msv by view and mode) and, if it exists, in multiplayer stores it in shortMapName
             * and queues command 0x28, otherwise opens the progress-bar dialog with action 0x1F (which performs the
             * load) and sets editorMapLoaded. 3 Save (needs non-empty text): builds the name from the typed text;
             * an existing file asks for overwrite confirmation (Yes/No dialog, action 0x1E), else single player
             * opens the progress-bar save (0x20) and multiplayer copies the text to shortMapName and queues
             * GCT_SAVE (map time, unit hash, param2 = 0 = manual save). 0x11 back, -1/-2 scroll.
             */
            void __cdecl MenuItemActionHandler_SaveLoadMap_Buttons(int param_1, ...);

        } // namespace SaveLoadMap
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
