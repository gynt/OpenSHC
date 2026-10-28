/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/NewMapMapsize.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace NewMapMapsize {

            /**
             * Render callback of the 'new map: size' buttons (only when no modal dialog is open). Button 7 (back)
             * is drawn generically; the size buttons draw the button, play the hover sound once when the hovered
             * button changes (tracked in DAT_LastHoveredMenuButtonId) and print '160x160'/'200x200'/'300x300' for ids 1-3 and
             * '400x400' otherwise, with shadow.
             */
            void __cdecl MenuItemRenderFunction_NewMapMapsize_Buttons(int param_1, ...);

            /**
             * Action handler of the 'new map: size' buttons (no modal open). Buttons 1-4 set TileMapState.mapSize
             * to 160/200/300/400, reset heights and borders, rebuild path-finding/building linkage layers, force a
             * full tile-map and macro-layer redraw, run one game tick, call updateWildlifeGrid for 0..39 and the
             * other wildlife updates, rebuild the minimap, fit the viewport, then enter the map-editor properties
             * view with an editable map. Button 7 returns to the custom-scenarios menu.
             */
            void __cdecl MenuItemActionHandler_NewMapMapsize_Buttons(int param_1, ...);

        } // namespace NewMapMapsize
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
