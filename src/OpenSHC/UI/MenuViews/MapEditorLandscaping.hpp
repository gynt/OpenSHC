/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/MapEditorLandscaping.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace MapEditorLandscaping {

            /**
             * Prepare handler of the map-editor landscaping view: flags the screen-edge graphics for reload
             * (field37_0xdc = 1) and configures display elements (hides people-left-to-place, shows player info on
             * hover).
             */
            void __cdecl MenuView_MapEditorLandscaping_Prepare();

            /**
             * Initial-draw handler of the map-editor landscaping view: positions the menu for the current
             * resolution, at 800x600/1024x768 clears the bottom panel area with magenta (transparent key), sets
             * menu tab gfx 2 unless the active tab is 60/62, and if the edge-reload flag is set clears it, loads
             * the resolution-specific edgeNNNNl.tgx (the same file into both gfx slots 0 and 1) and draws them at
             * the left and right screen edges.
             */
            void __cdecl MenuView_MapEditorLandscaping_DoInitial();

            /**
             * Per-frame handler of the map-editor landscaping view: unless the active tab is 60 or 62, redraws the
             * bottom panel gfx (GM_INTERFACE_PANELS frame 3) when needed and renders the landscaping minimap
             * (128x128) into the panel.
             */
            void __cdecl MenuView_MapEditorLandscaping_DoEveryFrame();

        } // namespace MapEditorLandscaping
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
