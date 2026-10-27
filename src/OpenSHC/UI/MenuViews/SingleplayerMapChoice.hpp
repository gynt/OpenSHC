/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/SingleplayerMapChoice.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace SingleplayerMapChoice {

            /**
             * Prepare handler of the single-player custom-map choice view: sets solitary/builder game mode; on
             * first entry (INT_00b95b64 != 0) becomes host in slot 1, resets map selection, map name/description
             * and minimap and requests a map-list reparse, otherwise re-applies the current selection; starts the
             * panel blend animation (strength 0x20, counting down), loads frontend_economics2 or frontend_combat2
             * by mission type, positions the menu, resets text input and sets up map sections.
             */
            void __cdecl MenuView_SingleplayerMapChoice_Prepare();

            /**
             * Per-frame handler of the single-player map choice view: animates the panel blend, and when
             * reparseMaps is set rebuilds the list of single-player maps (mapType 0) whose scenario type (Siege 2,
             * Invasion 3, Economic 1, Just-build 0) equals DAT_MapMissionType and whose lock level is < 2, storing
             * each map id in mapIndexList and in unsortedMapIdsOrLoadableFlags and its savedMapEndInt2 per map;
             * preselects the map named in standaloneFilename (scrolling so it is within the 13 visible rows), calls
             * the map-table handler and clears that name; then draws the blended map-list box and, once the blend
             * is done, its yellow frame lines.
             */
            void __cdecl MenuView_SingleplayerMapChoice_DoEveryFrame();

        } // namespace SingleplayerMapChoice
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
