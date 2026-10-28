/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/MapEditorProperties.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace MapEditorProperties {

            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            /**
             * Map editor properties main button render (no modal open): item 5 renders as a plain button; hides MP-
             * only items (9 description, -1/-2 arrows) on single-player maps and edit-scenario 0x19 on MP maps or
             * with no map loaded; draws the balanced/unbalanced toggle (-3/-4, MP maps) and the invasion option
             * toggle (-5/-6, SP invasion maps) with the active option's frame +1; up/down arrows for other negative
             * items; text buttons from TEXT_MAPEDIT (item 9 shows text 0x20 when mapDescriptionLocked is set).
             * Records the hovered item in DAT_MapEditorProperties_ClickedButton. The locals
             * textOffsetY/textFontSize are reused as ButtonX/ButtonY for the toggle draws.
             */
            void __cdecl MenuItemRenderFunction_MapEditorProperties_MainButtons(int param_1, ...);

            void __cdecl MenuItemRenderFunction_MapEditorProperties_MapDescriptionBox(int param_1, ...);

            void __cdecl MenuItemActionHandler_MapEditorProperties_MapDescriptionBox();

            void __cdecl MenuItemActionHandler_MapEditorProperties_MapDescriptionScrollbar(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            void __cdecl MenuItemRenderFunction_MapEditorProperties_MapDescriptionScrollbar(
                int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged);

            /**
             * Map editor properties button click handler (no modal open; always sets
             * TileMapState.placeUnitCount): 2 load map, 3 save map, 4 new map, 5 exit (quit confirmation if
             * DAT_EditorUnsavedChanges set), 6 go to landscaping (resets player slots), 9 edit description, 0x19 edit scenario,
             * 0x1F test map (auto-saves auto_backup_map.map, adds the map's Section1067 troop counts to a new
             * attack wave for player 2, copies start goods, siege info, popularity, date, recruitability and trade
             * costs into the game state and starts play in the build menu), -3/-4 balanced flag, -5/-6 mapU3EndInt,
             * -1/-2 scroll description by 14 px.
             */
            void __cdecl MenuItemActionHandler_MapEditorProperties_MainButtons(int param_1, ...);

        } // namespace MapEditorProperties
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
