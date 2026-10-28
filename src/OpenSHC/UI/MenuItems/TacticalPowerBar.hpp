/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/TacticalPowerBar.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace TacticalPowerBar {

            /**
             * Render callback of one tactical-power icon: draws a short separator line and maps the button index to
             * an icon offset; if powers are usable (solitary/single-player skirmish or no-rush time over) and the
             * player's bar level reaches (index+1)*636, draws the active icon (+hover overlay) and on first
             * availability sets the help-text flag; otherwise draws the inactive icon (half-faded while no-rush
             * time runs).
             */
            void __cdecl MenuItemRenderFunction_TacticalPowerBar_Main(int param_1, ...);

            /**
             * Click handler of a tactical-power button: if powers are usable it resets the mouse state; if the bar
             * level suffices and the lord is alive it clears the help text, then power 5 is queued directly as
             * GCT_ACTIVATE_TACTICAL_POWERS (SFX 0x100), other powers are armed for map targeting
             * (TileMapState.field178 = power, mode 5) with a selection SFX for powers 1 (chapel bell), 2/3/4/6
             * (0x104) and 7 (0x105).
             */
            void __cdecl MenuItemActionHandler_TacticalPowerBar_Main(int param_1, ...);

        } // namespace TacticalPowerBar
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
