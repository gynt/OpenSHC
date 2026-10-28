/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/OverlaySlider.hpp'
*/

#pragma once

#include "WinDef.h"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace OverlaySlider {

            /**
             * Slider callback of the generic overlay slider (MenuModalComposition2). Event 1 initialises
             * min/max/current from sliderMinimum/Maximum/Value; for ranges > 200 the track is lengthened by 60%
             * (0..range*1.6) and its lower half maps at quarter speed (pos/4 + min) for fine adjustment, the upper
             * half as pos - sliderMaximum*3/5 + min (uses sliderMaximum, not the range, so it only joins the fine
             * half when sliderMinimum is 0; the track end snaps to sliderMaximum). Events 2/3 write the mapped
             * value to the int or short destination. Event 7 returns the step (4 in the fine half, else 1). The
             * item parameter is unused.
             */
            void __cdecl MenuItemActionHandler_OverlaySlider_Slider(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            /**
             * Render callback of the overlay slider: draws a translucent black box, the optional label
             * (textGroup/textIndex) centred on top, and the thumb (lime while dragged); when the thumb fills the
             * whole width the label is redrawn highlighted. The thumbYPos/thumbHeight params are actually the
             * horizontal thumb offset/width; the item parameter is unused.
             */
            void __cdecl MenuItemRenderFunction_OverlaySlider_Slider(
                int param_1, int thumbYPos, int param_3, int thumbHeight, BOOL isDragged);

            /**
             * Deselect handler of the overlay slider: a right click anywhere, or a left click outside the slider's
             * modal rectangle, closes MenuModalComposition2 and invokes the stored sliderCallbackFunction (then
             * sets capturesMouse = -1). The item parameter is unused.
             */
            void __cdecl MenuItemActionHandler_OverlaySlider_Deselect(int param_1, ...);

        } // namespace OverlaySlider
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
