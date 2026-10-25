#include "../OverlaySlider.func.hpp"

#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004AA600
        void OverlaySlider::MenuItemActionHandler_OverlaySlider_Slider(
            int param_1, int param_2, int* minValue, int* maxValue, int* currentValue)
        {
            int iVar1;
            switch (param_2) {
            case 1:
                iVar1 = DAT_MenuModalComposition2::instance.sliderMaximum
                    - DAT_MenuModalComposition2::instance.sliderMinimum;
                *maxValue = iVar1;
                if (200 < iVar1) {
                    *maxValue = (iVar1 * 3) / 5 + iVar1;
                    *minValue = 0;
                    *currentValue = DAT_MenuModalComposition2::instance.sliderValue;
                    return;
                }
                *minValue = DAT_MenuModalComposition2::instance.sliderMinimum;
                *maxValue = DAT_MenuModalComposition2::instance.sliderMaximum;
                *currentValue = DAT_MenuModalComposition2::instance.sliderValue;
                return;
            case 2:
            case 3:
                /*
                  rebuilt from 0x4aa680: the small-range path returns, and each of the
                  three big-range paths writes either `destination` or `destination2`,
                  never both
                 */
                if ((int)(DAT_MenuModalComposition2::instance.sliderMaximum
                        - DAT_MenuModalComposition2::instance.sliderMinimum)
                    <= 0xc8) {
                    DAT_MenuModalComposition2::instance.sliderValue = *currentValue;
                    if (DAT_MenuModalComposition2::instance.destination != (int*)0x0) {
                        *DAT_MenuModalComposition2::instance.destination = *currentValue;
                        return;
                    }
                    *DAT_MenuModalComposition2::instance.destination2 = (short)*currentValue;
                    return;
                }
                DAT_MenuModalComposition2::instance.sliderValue = *currentValue;
                if (*currentValue <= *maxValue / 2) {
                    iVar1 = *currentValue / 4 + DAT_MenuModalComposition2::instance.sliderMinimum;
                    if (DAT_MenuModalComposition2::instance.destination != (int*)0x0) {
                        *DAT_MenuModalComposition2::instance.destination = iVar1;
                        return;
                    }
                    *DAT_MenuModalComposition2::instance.destination2 = (short)iVar1;
                    return;
                }
                if (DAT_MenuModalComposition2::instance.destination != (int*)0x0) {
                    *DAT_MenuModalComposition2::instance.destination
                        = (*currentValue - (DAT_MenuModalComposition2::instance.sliderMaximum * 3) / 5)
                        + DAT_MenuModalComposition2::instance.sliderMinimum;
                    if (*currentValue == *maxValue) {
                        *DAT_MenuModalComposition2::instance.destination
                            = DAT_MenuModalComposition2::instance.sliderMaximum;
                    }
                    return;
                }
                *DAT_MenuModalComposition2::instance.destination2
                    = ((short)*currentValue - (short)((DAT_MenuModalComposition2::instance.sliderMaximum * 3) / 5))
                    + (short)DAT_MenuModalComposition2::instance.sliderMinimum;
                if (*currentValue == *maxValue) {
                    *DAT_MenuModalComposition2::instance.destination2
                        = (short)DAT_MenuModalComposition2::instance.sliderMaximum;
                }
                return;
            case 4:
            case 5:
            case 6:
                return;
            case 7:
                if (200 < (int)(DAT_MenuModalComposition2::instance.sliderMaximum
                        - DAT_MenuModalComposition2::instance.sliderMinimum)) {
                    *currentValue = (*currentValue <= *maxValue / 2) ? 4 : 1;
                    return;
                }
                *currentValue = 1;
                return;
            default:
                break;
            }
        }

    }
}
}
