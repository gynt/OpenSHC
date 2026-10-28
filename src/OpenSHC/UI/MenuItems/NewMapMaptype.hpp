/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/NewMapMaptype.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace NewMapMaptype {

            /**
             * Render callback of the 'new map: type' buttons (no modal open). Button 7 is drawn generically;
             * buttons 1-3 draw the button with hover-sound tracking and their label (TEXT_MAP_TITLES 1,
             * TEXT_SHC_STANDALONE 2, TEXT_MAP_TITLES 2 'New Crusader Map'), using font 0x12 and Y offset 0x14
             * instead of 0x11/0x13 for GL_FRENCH and the next two languages.
             */
            void __cdecl MenuItemRenderFunction_NewMapMaptype_Buttons(int param_1, ...);

            /**
             * Action handler of the 'new map: type' buttons: 1 = Just Build map, 2 = Invasion map (sets
             * MapPropertiesState.SEC_U3_MapType2_1), 3 = 'New Crusader Map' (InitializeBasicMap,
             * GameCore.U2_mapType_singleOrMulti = 1, player unit colours reset to defaults); all three continue to
             * the map-size menu. 7 returns to custom scenarios.
             */
            void __cdecl MenuItemActionHandler_NewMapMaptype_Buttons(int param_1, ...);

        } // namespace NewMapMaptype
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
