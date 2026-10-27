/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/MapEditorProperties.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace MapEditorProperties {

            /**
             * Prepare handler of the map-editor properties view: closes modal 3, resets text input, loads
             * frontend_builder2.tgx; for multiplayer maps recounts mapU2PlayersCount (players 1.. whose entry at
             * startResources-0x3D8 is nonzero) and zeroes every player's startResources and the map startGoods;
             * then measures the map description height (custom text or TEXT_MAP_NAMES entry) and loads shc_back.
             */
            void __cdecl MenuView_MapEditorProperties_Prepare();

            /**
             * Per-frame handler of the map-editor properties view: draws background and header banner, the map type
             * line (Single-Player - Siege/Invasion/Economic/Landscape or Multi-Player) and map name (or
             * 'Untitled'); if no modal is open also the editor minimap (centred at x+400 single / x+600 multi) with
             * border boxes and a dimmed 'NxN' size label, scaled per map size (100/160/200 drawn 1:1, 300 drawn at
             * 150, 0 treated as 400 and drawn at 200), and hover hint texts for the clicked button (-3..-6:
             * balanced / un-balanced / invasion / economic). Shows 'Game Paused' when halted, then resets the
             * clicked button and, after a completed save, the unsaved-changes flag.
             */
            void __cdecl MenuView_MapEditorProperties_DoEveryFrame();

        } // namespace MapEditorProperties
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
