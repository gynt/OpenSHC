/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/DisplayElement.hpp'
*/

#pragma once

#include "OpenSHC/UI/DisplayElementRenderFunc.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementIDInt.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifierInt.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eOnScreenText;
    using OpenSHC::UI::DisplayElementRenderFunc;
    using OpenSHC::UI::Enums::DisplayElementIDInt;
    using OpenSHC::UI::Enums::DisplayElementPositionModifier;
    using OpenSHC::UI::Enums::DisplayElementPositionModifierInt;

#pragma pack(push, 1)

    // SIZE: 0x00000024
    class DisplayElement {
    public:
        // Unsigned Double-Word (ddw, 4-bytes)
        int x_0x0; // 0x00000000 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        int y_0x4; // 0x00000004 length: 4
        DisplayElementIDInt elementID_0x8; // 0x00000008 length: 4
        // Unsigned Double-Word (ddw, 4-bytes) [UNK PASS] was elementStateUnk_0xc
        dword displayState_0xc; // 0x0000000C length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        dword activationTime_0x10; // 0x00000010 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        int displayDuration_0x14; // 0x00000014 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        DisplayElementRenderFunc* renderFunction_0x18; // 0x00000018 length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        DisplayElementPositionModifierInt positionModifier_0x1c; // 0x0000001C length: 4
        // Unsigned Double-Word (ddw, 4-bytes)
        DisplayElement* nextDisplayElement_0x20; // 0x00000020 length: 4

    private:
        DisplayElement(DisplayElement const&);
        void operator=(DisplayElement const&);

    public:
        DisplayElement() {};
        ~DisplayElement() {};

        // Constructor
        /**
         * DisplayElement constructor: stores id, position, state, render callback and position modifier, sets
         * activationTime 0 and displayDuration -1, and pushes the element onto the global display-element linked
         * list (DAT_PointerToDisplayElementStackTop). Returns this.
         */
        DisplayElement* Constructor_DisplayElement(eOnScreenText elementID, int xPos, int yPos, dword elementState,
            DisplayElementRenderFunc* renderFunction, DisplayElementPositionModifier positionModifier);
    };

    static_assert_cpp98_obj(sizeof(DisplayElement) == 36, DisplayElement);

#pragma pack(pop)

} // namespace UI
} // namespace OpenSHC
