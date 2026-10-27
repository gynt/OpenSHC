/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/SoundOptions.hpp'
*/

#pragma once

#include "OpenSHC/UI/Enums/SoundMenuClickType.hpp"

#include "WinDef.h"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace SoundOptions {

            using OpenSHC::UI::Enums::SoundMenuClickType;

            /**
             * Render callback of the sound options buttons: -10 draws a TEXT_SKIRMISH_MISC[12] button, ids >= 0
             * draw TEXT_GAME_OPTIONS[id] buttons (0x23..0x25 as non-interactive labels), -1 / -5 draw only the
             * on/off state text of sound / genie voice (TEXT_GAME_OPTIONS 14 when off, 13 when on), other negative
             * ids draw an empty button.
             */
            void __cdecl MenuItemRenderFunction_SoundOptions_Buttons(int param_1, ...);

            /**
             * Volume slider callback: slider 0 = music (channel 0), 1 = sound effects (channels 1, 2, -1), 2 =
             * speech (channels 3, 4). Event 1 sets range 0..100, 2/3 apply a changed value via setVolumeUnk and
             * store it, 4 returns the stored value.
             */
            void __cdecl MenuItemActionHandler_SoundOptions_VolumeSlider(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            /**
             * Render callback of a horizontal volume slider: draws the slider background, the thumb box (lime while
             * dragged) offset horizontally by the thumb position, and the numeric value to the right of the slider.
             */
            void __cdecl MenuItemRenderFunction_SoundOptions_VolumeSlider(
                int param_1, int thumbYPos, int param_3, int thumbHeight, BOOL isDragged);

            /**
             * Action handler of the sound options menu: return pops the modal, toggle sound activates/deactivates
             * sound from the menu, toggle genie flips the genie voice flag (menu + GameCore), reset buttons set
             * speech/sfx/music volume to 85/80/90 through the volume slider callback (event 3, value passed in the
             * reused parameter slot).
             */
            void __cdecl MenuItemActionHandler_SoundOptions_Buttons(SoundMenuClickType param_1, ...);

        } // namespace SoundOptions
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
