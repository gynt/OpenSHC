/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/ButtonState.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {

#pragma pack(push, 1)
    // SIZE: 0x00000010
    typedef struct ButtonState {

        // [211 0x004F4290] sliders/scrollbars: minimum value clamp; buttons: time of last auto-repeat step
        int lastRepeatTimeOrMinValue; // 0x00000000 length: 4
        // [211 0x004F4290] sliders/scrollbars: maximum value clamp; buttons: click time (clicked flag cleared after
        // Menu.clickHighlightMs ms)
        // [211 0x004F4290] sliders/scrollbars: maximum value clamp; buttons: click time (clicked flag cleared after
        // Menu.thousand ms)
        int clickTimeOrMaxValue; // 0x00000004 length: 4
        // [211 0x004F4290] slider current value clamped to [min,max]; for buttons the held auto-repeat counter
        // (<=99)
        int repeatCountOrValue; // 0x00000008 length: 4
        // [211 0x004F4290] slider: mouse grab offset inside thumb, -1000 = not dragging; GM buttons: current
        // picture
        int pictureOrDragOffset; // 0x0000000C length: 4

    } ButtonState;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(ButtonState) == 16, ButtonState);
} // namespace UI
} // namespace OpenSHC
