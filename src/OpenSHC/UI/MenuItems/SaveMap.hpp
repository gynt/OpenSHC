/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/SaveMap.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace SaveMap {

            /**
             * Click on a row of the save-map list: if the row holds an entry, selects it and copies its map name
             * into the text input.
             */
            void __cdecl MenuItemActionHandler_SaveMap_TableContent(int param_1, ...);

            /**
             * Render callback of the save-map file name input box: rounded box, lime caret at the current cursor
             * width, and the typed text in white with shadow. The item parameter is unused.
             */
            void __cdecl MenuItemRenderFunction_SaveMap_InputTextDisplay(int param_1, ...);

            /**
             * Action handler of the save-map dialog's Return-key item: consumes UserTextHandler.returnPressed and,
             * if it was set, triggers the Save button (SaveLoadMap_Buttons(3)). The item parameter is unused.
             */
            void __cdecl MenuItemActionHandler_SaveMap_ReturnKeySave(int param_1, ...);

        } // namespace SaveMap
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
