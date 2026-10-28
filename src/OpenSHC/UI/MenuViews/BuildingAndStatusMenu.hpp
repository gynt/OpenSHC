/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/BuildingAndStatusMenu.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace BuildingAndStatusMenu {

            /**
             * DoInitial callback of the building/status menu view: positions the menu at the screen bottom (x =
             * border width; -0x2BA at 640x480), selects the menu texture set (barracks/mercenary post: 3, or 7 in
             * editor; otherwise 1, or 6 in editor) and, when field37_0xdc requests an edge redraw, clears it,
             * clears the strip with magenta and loads the resolution-specific left/right edge graphics at the end
             * of the gfx buffer (backwards index from 99; edge_military_* for barracks/mercenary post, edge*
             * otherwise; editor/Siege That reuse the left image), blitting the left one at x=0 and the right one at
             * a resolution-dependent x (0x10 further left for military edges in editor/Siege That at 1280+ widths).
             */
            void __cdecl MenuView_BuildingAndStatusMenu_DoInitial();

            /**
             * Prepare callback of the building/status menu view: positions the menu, resets user text to index 4
             * and the help/sketch/bink/army-page state. For building tabs (not peasant 70, not status 71..79) loads
             * the selected building's help file, sketch .tgx and (if the file exists and no Bink plays) its Bink
             * video in the panel, and plays its selection speech. Clears the player's timeTaxesOrRationsChange,
             * then per tab: barracks gold check; keep tax-trend speech (gold vs marketGold+beforeLastMonthsGold,
             * +/-40 thresholds); granary empty warning or food-trend speech when rations are on;
             * fletcher/blacksmith/poleturner store the building's produced item in weaponRelated;
             * engineers/tunnelers gold checks; ambient SFX for inn, oil smelter, dairy (cow moo, id 76), mill,
             * stables (horse whinny, id 89), gallows, cesspit, dungeon, stretching rack, chopping block;
             * chapel/church/cathedral bell + wedding_sketch.tgx; mercenary post disables portraits; peasant tab
             * bumps the jester counter and drunkenManStatus and loads the unit's chimp portrait/sketch/help/bink;
             * status tabs load their graphics (shield1/2, popularity, fear, population, food, 26 army bars + unit
             * count, religion) and play popularity/fear-factor speech. Finally resolves the help section id for the
             * loaded help file and sets field37_0xdc (edge redraw).
             */
            void __cdecl MenuView_BuildingAndStatusMenu_Prepare();

            /**
             * Per-frame handler of the in-game bottom panel: draws the GM_INTERFACE_PANELS background (image 3 at
             * 640x480 without clearing; otherwise first fills the panel strip with the COL_MAGENTA colour key and
             * draws image 4 for barracks, 6 for mercenary post, 2 for everything else), draws loaded gfx 0 when
             * DAT_StatusMenuSketchLoaded is set, then dispatches on DAT_GameCore.activeMenuTab.tabType to the matching building
             * or status submenu renderer, and finally redraws the minimap unless a Bink video (game or
             * building/peasant) is playing or the resolution is 640x480.
             */
            void __cdecl MenuView_BuildingAndStatusMenu_DoEveryFrame();

        } // namespace BuildingAndStatusMenu
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
