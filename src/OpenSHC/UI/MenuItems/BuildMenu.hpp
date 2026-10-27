/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/BuildMenu.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace BuildMenu {

            /**
             * Build-menu button action: if the active tab is BASMTT_WITCHHOIST_OR_BM_PLACE_GRANARY and
             * singlePlayerHasKeepAndGranaryCheck() > 0, switches the build menu to the BASMTT_HUNTERSHUT tab (enum
             * names of these tab ids are probably misleading). The button parameter is unused.
             */
            void __cdecl MenuItemActionHandler_BuildMenu_LeaveGranaryPlacementTab(int param_1, ...);

            /**
             * Render function for the keep-subcategory build button: disabled (DAT_ButtonDisabled = 1, not drawn)
             * unless in the map editor or Siege That mode, otherwise renders the button normally. The parameter is
             * unused.
             */
            void __cdecl MenuItemRenderFunction_BuildMenu_BuildingKeepSubcategoryButton(int param_1, ...);

            /**
             * Build-menu minimap render callback: sets DAT_MinimapViewState.mouseOverMinimap to 1 while the button
             * is hovered in MVT_BUILD_MENU and the active tab is BASMTT_SIEGETENT_RAM_OR_BM_TROOP_PANEL or
             * TileMapState.mapInteractionMode == 1; otherwise 0. The menu-item parameter is never read.
             */
            void __cdecl MenuItemRenderFunction_BuildMenu_MiniMapInteraction(int param_1, ...);

            /**
             * Map click handler for the delete mapper (only when not syncing/saving and the mouse is over the map):
             * stores the clicked tile and an enemy-near flag; returns if no click is in progress. In solitary Alt-U
             * dungeon mode an own living non-lord unit under the cursor is killed instantly (stone death, engineers
             * carrying something ignite fire). Otherwise queues command 0x61 (handler 0x00485520
             * FlagsAndBraziersCommandUnk, Param0/1 = tile) if spreadFlagPlacementAlgorithm succeeds at the tile,
             * else evaluates the demolish target and queues GCT_DESTROY_BUILDING (building uid) or GCT_DESTROY_WALL_OR_MOAT
             * (wall/moat tile, marks MiscDisplayLayer 0x400), or shows the placement-failure text. The menu-item
             * parameter is never read.
             */
            void __cdecl MenuItemActionHandler_BuildMenu_DeleteAction(int param_1, ...);

            /**
             * Render callback for the unit-command buttons of the build menu (troops selected), switched on
             * DAT_CurrentButtonGmDataIndex. Hidden when the mapper is unavailable or the selection does not fit:
             * engineer buttons (0xD3-0xD7, 0x22E, 0x178) need a selected engineer; button 0xDB becomes 0xD2 for
             * engineers carrying a pot, 0xDA for tunnelers, 0x177 + max stone-ammo number for catapults/trebuchets
             * (types 0x27/0x28) or 0x177 for ranged-only selections, and is hidden for engineer-only (no pot),
             * laddermen-only or shieldmen-only selections; 0xDC (cow throw) needs a catapult/trebuchet,
             * PlayerData.counter > 0 and (single-player or cow throwing allowed) and prints counter; 0x172-0x174
             * draw the active stance pressed; 0x176 becomes 0x179 for catapults/trebuchets.
             */
            void __cdecl MenuItemRenderFunction_BuildMenu_UnitActionButtons(int mapperValue, ...);

            /**
             * Render callback for one slot of the 'currently selected troops' panel: hidden if no owned unit is
             * selected or the slot is empty; otherwise nudges button X/Y per unit-icon type, selects the icon GM
             * index (0x17C+type, or 0x209+type for types > 0x12), draws the button and the number of selected units
             * of that type (selectionSlots[type-0x1B]) centered below the original position.
             */
            void __cdecl MenuItemRenderFunction_BuildMenu_CurrentlySelectedTroops(int param_1, ...);

            void __cdecl MenuItemRenderFunction_BuildMenu_CurrentlySelectedTroopsDeselectHelper(int param_1, ...);

            /**
             * Action handler for a selected-troops slot button: sets unitControlsRelated = 1, maps the slot's icon
             * type to a unit type via RenderingDefinedData.selectionSlotUnitTypes; slotID < 0x14 queues 'select only
             * this unit type' and filters the local selection to it, slotID >= 0x14 (deselect helper) queues
             * 'deselect this unit type' and removes it; then recounts the selection.
             */
            void __cdecl MenuItemActionHandler_BuildMenu_CurrentlySelectedTroops(int slotID, ...);

            /**
             * Action handler for the unit-command buttons (ignored while syncing/saving, if the local lord was
             * killed, or after own defeat except in MP when gameOver == own slot). Clears the patrol-button state,
             * then: 1, 4, 0x14 (engineer selected) arm a targeting cursor
             * (UnitsState.unitCommandMode/field5_0x14 = mode, TileMapState cursor fields); 5 -> mode 0x14 for
             * engineers carrying a pot, tunnel-construction mapper for tunnelers, otherwise mode 5 unless the first
             * selected catapult/trebuchet is unmanned; 0x16 (cow throw) -> mode 0x16 only if PlayerData.counter > 0
             * and the catapult/trebuchet is manned; 3, 8, 0x1E (+ patrol speech) and 0x1F immediately call
             * queueDisbandAndAttackCommand2Params(currentTribe, id). Failed 0x14/0x1E clear
             * DAT_StopHandlingMenuItems.
             */
            void __cdecl MenuItemActionHandler_BuildMenu_UnitActionButtons(int param_1, ...);

            /**
             * Render callback for building icons in the build menu: draws the button only if the mapper (building
             * placement command) is available on this map, otherwise hides it.
             */
            void __cdecl MenuItemRenderFunction_BuildMenu_BuildingIcons(int param_1, ...);

            /**
             * Render callback for a build-menu subcategory button: draws it only if
             * MapPropertiesState::isMercRecruitableForBuildingType(param) returns nonzero, otherwise hides it.
             */
            void __cdecl MenuItemRenderFunction_BuildMenu_BuildingSubcategoryButton(int param_1, ...);

        } // namespace BuildMenu
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
