/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/BuildMenu.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace BuildMenu {

            /**
             * Prepare callback of the in-game build menu view: resets user text input to index 4; unless the active
             * or pending build-menu tab is the soldier panel (61 = BMTT_SOLDIERS, or 62 = soldier panel with UI
             * hidden) clears TileMapState.mapInteractionMode and the local player's selected-unit count; sets the
             * keep/granary placement-info display element to state 0; sets WindowAndDirectDraw.menuEdgeRedrawPending = 1
             * (edge graphics need redraw); sets to state 1 the time-until-defeat element if such an event exists,
             * and outside the solitary campaign mode DEID_UNKNOWN_25 (if mapU4Int0), player-info-on-hover, and in
             * multiplayer the no-rush timer if skirmishNoRushTicks != 0. Clears the wait cursor and g_faceBitmapLastSendMs.
             */
            void __cdecl MenuView_BuildMenu_Prepare();

            /**
             * DoInitial callback of the build menu view: positions the menu at the bottom of the screen (x = border
             * width, y = resY-600; x = 0 at 640x480). Tabs 60 (menu hidden) and 62 (soldier panel, hidden) return
             * immediately. Otherwise selects the menu tab texture set (soldier panel 61: 4, or 8 in editor; else 0,
             * 5 in editor, 9 in Siege That) and, if field37_0xdc requests an edge redraw, clears the strip with
             * magenta and loads/blits the resolution-specific left/right edge graphics (edge_military_* for tab 61,
             * edge* otherwise; editor/Siege That use the left image on both sides) into the menu buffer. Original-
             * code quirk: in the tab-61 branches for 1280+ widths the editor/Siege That path resets totalLoadedGfx
             * a second time, so gfx slot 1 is not reloaded before being blitted on the right.
             */
            void __cdecl MenuView_BuildMenu_DoInitial();

            /**
             * Per-frame callback of the build menu view: unless the tab is 60/62 (UI hidden), forces a menu redraw
             * (unk_resetViewportRelated = 2) if MinimapViewState.field3_0xc == 0, advances the build-menu slide
             * transition, and on a redraw draws the bottom panel background into the menu buffer (640x480: panel
             * frame 2; otherwise magenta clear plus panel frame 5 for the soldier panel 61, or panel frame 1 plus
             * the scrolling GID_INTERFACE_BUTTONS frame 7 strip clipped to the menu), then renders the minimap
             * unless a Bink video plays. If isVictoryOrDefeatUnk is set, clears it, marks the game over
             * (gameOverTime = now-6000), sets the local player's playerIsAlive, sets skipStoreSKMasters and shows
             * the win/defeat window.
             */
            void __cdecl MenuView_BuildMenu_DoEveryFrame();

        } // namespace BuildMenu
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
